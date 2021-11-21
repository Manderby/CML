
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

#include "../CML.h"
#include "CMLColorMachineState.h"


CMLAPI void CMLgetVersion(CMLByte version[4]){
  #ifndef NDEBUG
    version[0] = 1;
    version[1] = 0;
    version[2] = 2;
    version[3] = 1;
  #else
    version[0] = 1;
    version[1] = 0;
    version[2] = 2;
    version[3] = 0;
  #endif
}



CMLAPI CMLColorMachine* CMLcreateColorMachine(){
  CMLint32 i;
  CMLColorMachine* cm = (CMLColorMachine*)cmlAllocate(sizeof(CMLColorMachine));

  CMLIllumination* referenceillumination = cmlCreateIlluminationWithPreset(CML_NULL, CML_ILLUMINATION_D65, 0);
  cmlCreateObserverWithIllumination(  &(cm->observer),
                                              CML_OBSERVER_2DEG_CIE_1931,
                                              referenceillumination,
                                              1.f);

  cmlCreateResponseCurve(&(cm->rgbspace.responseR));
  cmlCreateResponseCurve(&(cm->rgbspace.responseG));
  cmlCreateResponseCurve(&(cm->rgbspace.responseB));
  cmlCreateResponseCurve(&(cm->labspace.responseL));
  cmlCreateResponseCurveWithPreset(&(cm->labspace.responseLStar), CML_RESPONSE_LSTAR);
  
  cm->GraytoChanneledBuffer = &CMLInternalGraytoChanneledBufferLSTAR;
  cm->ChanneledBuffertoGray = &CMLInternalChanneledBuffertoGrayLSTAR;
  cm->XYZtoLab              = &CMLInternalXYZtoLabCIELAB;
  cm->XYZtoLab_SB           = &CMLInternalXYZtoLabCIELAB_SB;
  cm->LabtoXYZ              = &CMLInternalLabtoXYZCIELAB;
  cm->LabtoXYZ_SB           = &CMLInternalLabtoXYZCIELAB_SB;
  cm->RGBtoCMYK             = &CMLInternalRGBtoCMYKStandard;
  cm->RGBtoCMYK_SB          = &CMLInternalRGBtoCMYKStandard_SB;
  cm->CMYKtoRGB             = &CMLInternalCMYKtoRGBStandard;
  cm->CMYKtoRGB_SB          = &CMLInternalCMYKtoRGBStandard_SB;

  // Set the recomputation to zero and start locking for the remaining of this
  // function.
  cm->recomputationlockcount = 0;
  cm->recomputationmask = 0;
  CMLlockRecomputation(cm);

  // Set the default for the integer mapping
  CMLsetIntegerMappingType(cm, CML_DEFAULT_INTEGER_MAPPING);
  for(i=0; i<CML_MAX_NUMBER_OF_CHANNELS; i++){
    cm->inputoutput.offset8bit[i]  = CML_DEFAULT_8BIT_FLOOR_CUTOFF;
    cm->inputoutput.range8bit[i]   = (float)(CML_DEFAULT_8BIT_CEIL_CUTOFF - CML_DEFAULT_8BIT_FLOOR_CUTOFF);
    cm->inputoutput.offset16bit[i] = CML_DEFAULT_16BIT_FLOOR_CUTOFF;
    cm->inputoutput.range16bit[i]  = (float)(CML_DEFAULT_16BIT_CEIL_CUTOFF - CML_DEFAULT_16BIT_FLOOR_CUTOFF);
  }
  
  // Set the default observer.
  CMLsetObserverType(cm, CML_DEFAULT_2DEG_OBSERVER);
//  CMLsetRadiometricComputation(cm, CMLFALSE);

  // Set the default RGB space and the according default illumination.
  CMLsetRGBLUTSize(cm, CML_DEFAULT_RGB_LUT_SIZE);
  CMLsetRGBColorSpace(cm, CML_DEFAULT_RGB_COLORSPACE);

  // Set the chromatic valence parameters manually to the Hunter Lab original
  // values.
  cm->labspace.adamschromaticityvalenceK = 175.f / 100.f;
  cm->labspace.adamschromaticityvalenceke = 70.f / 175.f;
  // But set the default LAB colorspace.
  CMLsetLabLUTSize(cm, CML_DEFAULT_LAB_LUT_SIZE);
  CMLsetLabColorSpace(cm, CML_DEFAULT_LAB_COLORSPACE);

  // Additional state settings.
  CMLsetCMYKTransform(cm, CML_DEFAULT_CMYK_TRANSFORM);
  CMLsetGrayComputationType(cm, CML_DEFAULT_GRAY_COMPUTATION);
  
  // Recompute the whole machine.
  CMLreleaseRecomputation(cm);

  return cm;
}



CMLAPI void CMLreleaseColorMachine(CMLColorMachine* cm){
  cmlClearObserver(&(cm->observer));
  CMLclearResponseCurve(&(cm->rgbspace.responseR));
  CMLclearResponseCurve(&(cm->rgbspace.responseG));
  CMLclearResponseCurve(&(cm->rgbspace.responseB));
  CMLclearResponseCurve(&(cm->labspace.responseL));
  CMLclearResponseCurve(&(cm->labspace.responseLStar));
  free(cm);
}



CMLAPI void CMLlockRecomputation(CMLColorMachine* cm){
  cm->recomputationlockcount ++;
}



CMLAPI void CMLreleaseRecomputation(CMLColorMachine* cm){
  cm->recomputationlockcount --;
  if(cm->recomputationlockcount){return;}
  
  if(cm->recomputationmask & CML_COLORMACHINE_RECOMPUTE_OBSERVER){CMLInternalrecomputeObserver(cm);
  }else if(cm->recomputationmask & CML_COLORMACHINE_RECOMPUTE_ILLUMINATION){CMLInternalrecomputeIllumination(cm);
  }else{
    // note that the following recomputations may occur independant of each
    // other.
    if(cm->recomputationmask & CML_COLORMACHINE_RECOMPUTE_LAB){CMLInternalrecomputeLabColorspace(cm);}
    if(cm->recomputationmask & CML_COLORMACHINE_RECOMPUTE_ADAMS_CHROMATICITY){CMLInternalrecomputeAdamsChromaticityValenceSpace(cm);}
    if(cm->recomputationmask & CML_COLORMACHINE_RECOMPUTE_RGB_RESPONSES){CMLInternalrecomputeRGBResponses(cm);}
    if(cm->recomputationmask & CML_COLORMACHINE_RECOMPUTE_RGB){CMLInternalrecomputeRGBColorspace(cm);}
  }
  cm->recomputationmask = 0;
}


//
//CMLIntegrationMethod CMLgetIntegrationMethod(const CMLColorMachine* cm){
//  return cm->inputoutput.method;
//}
//
//
//void CMLsetIntegrationMethod(CMLColorMachine* cm, CMLIntegrationMethod newtype){
//  cm->inputoutput.method = newtype;
//  CMLInternalrecomputeObserver(cm);
//}



CMLAPI void CMLsetIntegerMappingType(CMLColorMachine* cm, CMLIntegerMappingType newtype){
  switch(newtype){
  case CML_INTEGER_MAPPING_FLOOR:
    cm->float1to8bit          = &CMLInternalfloat1to8bitFloor;
    cm->float3to8bit          = &CMLInternalfloat3to8bitFloor;
    cm->float4to8bit          = &CMLInternalfloat4to8bitFloor;
    cm->float1to16bit         = &CMLInternalfloat1to16bitFloor;
    cm->float3to16bit         = &CMLInternalfloat3to16bitFloor;
    cm->float4to16bit         = &CMLInternalfloat4to16bitFloor;
    break;
  case CML_INTEGER_MAPPING_BOX:
    cm->float1to8bit          = &CMLInternalfloat1to8bitBox;
    cm->float3to8bit          = &CMLInternalfloat3to8bitBox;
    cm->float4to8bit          = &CMLInternalfloat4to8bitBox;
    cm->float1to16bit         = &CMLInternalfloat1to16bitBox;
    cm->float3to16bit         = &CMLInternalfloat3to16bitBox;
    cm->float4to16bit         = &CMLInternalfloat4to16bitBox;
    break;
  case CML_INTEGER_MAPPING_INTERVAL:
    cm->float1to8bit          = &CMLInternalfloat1to8bitInterval;
    cm->float3to8bit          = &CMLInternalfloat3to8bitInterval;
    cm->float4to8bit          = &CMLInternalfloat4to8bitInterval;
    cm->float1to16bit         = &CMLInternalfloat1to16bitInterval;
    cm->float3to16bit         = &CMLInternalfloat3to16bitInterval;
    cm->float4to16bit         = &CMLInternalfloat4to16bitInterval;
    break;
  default:
    #ifndef NDEBUG
      cmlError("CMLsetIntegerMappingType", "Invalid Integer mapping.");
    #endif
    return;
    break;
  }
  cm->inputoutput.integermapping = newtype;
}


CMLAPI CMLIntegerMappingType CMLgetIntegerMappingType(const CMLColorMachine* cm){
  return cm->inputoutput.integermapping;
}


CMLAPI void CMLget8bitCutoffs(const CMLColorMachine* cm, CMLint32* min, CMLint32* max, CMLuint32 channel){
  #ifndef NDEBUG
    if(channel >= CML_MAX_NUMBER_OF_CHANNELS){cmlError("CMLget8bitCutoffs", "Invalid Channel number.");}
  #endif
  *min = (CMLint32)(cm->inputoutput.offset8bit[channel]);
  *max = *min + (CMLint32)(cm->inputoutput.range8bit[channel]);
}


CMLAPI void CMLget16bitCutoffs(const CMLColorMachine* cm, CMLint32* min, CMLint32* max, CMLuint32 channel){
  #ifndef NDEBUG
    if(channel >= CML_MAX_NUMBER_OF_CHANNELS){cmlError("CMLget16bitCutoffs", "Invalid Channel number.");}
  #endif
  *min = (CMLint32)(cm->inputoutput.offset16bit[channel]);
  *max = *min + (CMLint32)(cm->inputoutput.range16bit[channel]);
}


CMLAPI void CMLset8bitCutoffs(CMLColorMachine* cm, CMLint32 min, CMLint32 max, CMLuint32 channel){
  #ifndef NDEBUG
    if(channel >= CML_MAX_NUMBER_OF_CHANNELS){cmlError("CMLset8bitCutoffs", "Invalid Channel number.");}
  #endif
  cm->inputoutput.offset8bit[channel] = (CMLByte)(min);
  cm->inputoutput.range8bit[channel] = (float)(max - min);
}


CMLAPI void cmlSet16bitCutoffs(CMLColorMachine* cm, CMLint32 min, CMLint32 max, CMLuint32 channel){
  #ifndef NDEBUG
    if(channel >= CML_MAX_NUMBER_OF_CHANNELS){cmlError("cmlSet16bitCutoffs", "Invalid Channel number.");}
  #endif
  cm->inputoutput.offset16bit[channel] = (CMLWord)(min);
  cm->inputoutput.range16bit[channel] = (float)(max - min);
}





#include "../CML.h"
#include "CMLColorMachineState.h"


CML_API void CMLgetVersion(CMLByte version[4]){
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



CML_API CMLColorMachine* CMLcreateColorMachine(){
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
    cm->inputoutput.offset8Bit[i]  = CML_DEFAULT_8BIT_FLOOR_CUTOFF;
    cm->inputoutput.range8Bit[i]   = (float)(CML_DEFAULT_8BIT_CEIL_CUTOFF - CML_DEFAULT_8BIT_FLOOR_CUTOFF);
    cm->inputoutput.offset16Bit[i] = CML_DEFAULT_16BIT_FLOOR_CUTOFF;
    cm->inputoutput.range16Bit[i]  = (float)(CML_DEFAULT_16BIT_CEIL_CUTOFF - CML_DEFAULT_16BIT_FLOOR_CUTOFF);
  }
  
  // Set the default observer.
  CMLsetObserverType(cm, CML_DEFAULT_2DEG_OBSERVER);
//  CMLsetRadiometricComputation(cm, CML_FALSE);

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



CML_API void CMLreleaseColorMachine(CMLColorMachine* cm){
  cmlClearObserver(&(cm->observer));
  CMLclearResponseCurve(&(cm->rgbspace.responseR));
  CMLclearResponseCurve(&(cm->rgbspace.responseG));
  CMLclearResponseCurve(&(cm->rgbspace.responseB));
  CMLclearResponseCurve(&(cm->labspace.responseL));
  CMLclearResponseCurve(&(cm->labspace.responseLStar));
  free(cm);
}



CML_API void CMLlockRecomputation(CMLColorMachine* cm){
  cm->recomputationlockcount ++;
}



CML_API void CMLreleaseRecomputation(CMLColorMachine* cm){
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



CML_API CMLIntegerMappingType CMLgetIntegerMappingType(const CMLColorMachine* cm){
  return cm->inputoutput.integermapping;
}


CML_API void CMLget8BitCutoffs(const CMLColorMachine* cm, CMLint32* min, CMLint32* max, CMLuint32 channel){
  #ifndef NDEBUG
    if(channel >= CML_MAX_NUMBER_OF_CHANNELS){cmlError("CMLget8BitCutoffs", "Invalid Channel number.");}
  #endif
  *min = (CMLint32)(cm->inputoutput.offset8Bit[channel]);
  *max = *min + (CMLint32)(cm->inputoutput.range8Bit[channel]);
}


CML_API void CMLget16BitCutoffs(const CMLColorMachine* cm, CMLint32* min, CMLint32* max, CMLuint32 channel){
  #ifndef NDEBUG
    if(channel >= CML_MAX_NUMBER_OF_CHANNELS){cmlError("CMLget16BitCutoffs", "Invalid Channel number.");}
  #endif
  *min = (CMLint32)(cm->inputoutput.offset16Bit[channel]);
  *max = *min + (CMLint32)(cm->inputoutput.range16Bit[channel]);
}


CML_API void CMLset8BitCutoffs(CMLColorMachine* cm, CMLint32 min, CMLint32 max, CMLuint32 channel){
  #ifndef NDEBUG
    if(channel >= CML_MAX_NUMBER_OF_CHANNELS){cmlError("CMLset8BitCutoffs", "Invalid Channel number.");}
  #endif
  cm->inputoutput.offset8Bit[channel] = (CMLByte)(min);
  cm->inputoutput.range8Bit[channel] = (float)(max - min);
}


CML_API void cmlSet16BitCutoffs(CMLColorMachine* cm, CMLint32 min, CMLint32 max, CMLuint32 channel){
  #ifndef NDEBUG
    if(channel >= CML_MAX_NUMBER_OF_CHANNELS){cmlError("cmlSet16BitCutoffs", "Invalid Channel number.");}
  #endif
  cm->inputoutput.offset16Bit[channel] = (CMLWord)(min);
  cm->inputoutput.range16Bit[channel] = (float)(max - min);
}



// This is free and unencumbered software released into the public domain.

// Anyone is free to copy, modify, publish, use, compile, sell, or
// distribute this software, either in source code form or as a compiled
// binary, for any purpose, commercial or non-commercial, and by any
// means.

// In jurisdictions that recognize copyright laws, the author or authors
// of this software dedicate any and all copyright interest in the
// software to the public domain. We make this dedication for the benefit
// of the public at large and to the detriment of our heirs and
// successors. We intend this dedication to be an overt act of
// relinquishment in perpetuity of all present and future rights to this
// software under copyright law.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
// OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.

// For more information, please refer to <http://unlicense.org/>

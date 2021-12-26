
#include "../CML.h"
#include "CMLColorMachineState.h"



#if CML_DEBUG
  CML_DEF void cml_Error(const char* functionSymbol, const char* text){
    fprintf(stderr, "Error in %s: %s", functionSymbol, text);

    // //////////////////////////
    // Set a breakpoint in the following line to debug.
    // //////////////////////////

    fprintf(stderr, "\n");

    // //////////////////////////
  }
#endif



CML_DEF int cmlGetVersion(){
  return 2;
}



CML_DEF CMLColorMachine* cmlCreateColorMachine(){
  CMLColorMachine* cm = (CMLColorMachine*)cml_Malloc(sizeof(CMLColorMachine));

  CMLIllumination* referenceIllumination = cml_Malloc(sizeof(CMLIllumination));
  cml_InitIlluminationWithType(referenceIllumination, CML_ILLUMINATION_D65, 0);
  cml_InitObserver(
    &(cm->observer),
    CML_OBSERVER_2DEG_CIE_1931,
    referenceIllumination,
    1.f);

  cmlInitResponseCurve(&(cm->rgbSpace.responseR));
  cmlInitResponseCurve(&(cm->rgbSpace.responseG));
  cmlInitResponseCurve(&(cm->rgbSpace.responseB));
  
  GammaLinearInputParameters customGammaLinearParameters = {2.2f, .2f, 1.0f, .1f};
  cm->rgbSpace.customParametersR = customGammaLinearParameters;
  cm->rgbSpace.customParametersG = customGammaLinearParameters;
  cm->rgbSpace.customParametersB = customGammaLinearParameters;
  
  cmlInitResponseCurve(&(cm->labSpace.responseL));
  cmlInitResponseCurveWithType(&(cm->labSpace.responseLStar), CML_RESPONSE_LSTAR);
  
  cm->GrayToChanneledBuffer = &cml_GrayToChanneledBufferLSTAR;
  cm->ChanneledBufferToGray = &cml_ChanneledBufferToGrayLSTAR;
  cm->XYZToLab              = &cml_XYZToLabCIELAB;
  cm->XYZToLab_SB           = &cml_XYZToLabCIELAB_SB;
  cm->LabToXYZ              = &cml_LabToXYZCIELAB;
  cm->LabToXYZ_SB           = &cml_LabToXYZCIELAB_SB;
  cm->RGBToCMYK             = &cml_RGBToCMYKStandard;
  cm->RGBToCMYK_SB          = &cml_RGBToCMYKStandard_SB;
  cm->CMYKToRGB             = &cml_CMYKToRGBStandard;
  cm->CMYKToRGB_SB          = &cml_CMYKToRGBStandard_SB;

  // Set the recomputation to zero and start locking for the remaining of this
  // function.
  cm->recomputationLockCount = 0;
  cm->recomputationMask = 0;
  cmlLockRecomputation(cm);

  // Set the default for the integer mapping
  cmlSetIntegerMappingType(cm, CML_DEFAULT_INTEGER_MAPPING);
  for(size_t i = 0; i < CML_MAX_NUMBER_OF_CHANNELS; i++){
    cm->inputoutput.offset8Bit[i]  = CML_DEFAULT_8BIT_FLOOR_CUTOFF;
    cm->inputoutput.range8Bit[i]   = (float)(CML_DEFAULT_8BIT_CEIL_CUTOFF - CML_DEFAULT_8BIT_FLOOR_CUTOFF);
    cm->inputoutput.offset16Bit[i] = CML_DEFAULT_16BIT_FLOOR_CUTOFF;
    cm->inputoutput.range16Bit[i]  = (float)(CML_DEFAULT_16BIT_CEIL_CUTOFF - CML_DEFAULT_16BIT_FLOOR_CUTOFF);
  }
  
  // Set the default observer.
  cmlSetObserverType(cm, CML_DEFAULT_2DEG_OBSERVER);
//  cmlSetRadiometricComputation(cm, CML_FALSE);

  // Set the default RGB space and the according default illumination.
  cmlSetRGBLUTSize(cm, CML_DEFAULT_RGB_LUT_SIZE);
  cmlSetRGBColorSpaceType(cm, CML_DEFAULT_RGB_COLORSPACE);

  // Set the chromatic valence parameters manually to the Hunter Lab original
  // values.
  
  cm->labSpace.adamsChromaticityValenceK = CML_ADAMS_CHROMATICITY_HUNTER_ORIGINAL_K;
  cm->labSpace.adamsChromaticityValenceke = CML_ADAMS_CHROMATICITY_HUNTER_ORIGINAL_KE;
  // But set the default LAB colorspace.
  cmlSetLabLUTSize(cm, CML_DEFAULT_LAB_LUT_SIZE);
  cmlSetLabColorSpace(cm, CML_DEFAULT_LAB_COLORSPACE);

  // Additional state settings.
  cmlSetCMYKTransform(cm, CML_DEFAULT_CMYK_TRANSFORM);
  cmlSetGrayComputationType(cm, CML_DEFAULT_GRAY_COMPUTATION);
  
  // Recompute the whole machine.
  cmlReleaseRecomputation(cm);

  return cm;
}



CML_DEF void cmlReleaseColorMachine(CMLColorMachine* cm){
  cml_ClearObserver(&(cm->observer));
  cmlClearResponseCurve(&(cm->rgbSpace.responseR));
  cmlClearResponseCurve(&(cm->rgbSpace.responseG));
  cmlClearResponseCurve(&(cm->rgbSpace.responseB));
  cmlClearResponseCurve(&(cm->labSpace.responseL));
  cmlClearResponseCurve(&(cm->labSpace.responseLStar));
  free(cm);
}



CML_DEF void cmlLockRecomputation(CMLColorMachine* cm){
  cm->recomputationLockCount ++;
}



CML_DEF void cmlReleaseRecomputation(CMLColorMachine* cm){
  cm->recomputationLockCount --;
  if(cm->recomputationLockCount){return;}
  
  if(cm->recomputationMask & CML_COLORMACHINE_RECOMPUTE_OBSERVER){cml_recomputeObserver(cm);
  }else if(cm->recomputationMask & CML_COLORMACHINE_RECOMPUTE_ILLUMINATION){cml_recomputeIllumination(cm);
  }else{
    // note that the following recomputations may occur independant of each
    // other.
    if(cm->recomputationMask & CML_COLORMACHINE_RECOMPUTE_LAB){cml_recomputeLabColorSpace(cm);}
    if(cm->recomputationMask & CML_COLORMACHINE_RECOMPUTE_ADAMS_CHROMATICITY){cml_recomputeAdamsChromaticityValenceSpace(cm);}
    if(cm->recomputationMask & CML_COLORMACHINE_RECOMPUTE_RGB_RESPONSES){cml_recomputeRGBResponses(cm);}
    if(cm->recomputationMask & CML_COLORMACHINE_RECOMPUTE_RGB){cml_recomputeRGBColorSpace(cm);}
  }
  cm->recomputationMask = 0;
}


//
//CMLIntegrationMethod cmlGetIntegrationMethod(const CMLColorMachine* cm){
//  return cm->inputoutput.method;
//}
//
//
//void cmlSetIntegrationMethod(CMLColorMachine* cm, CMLIntegrationMethod type){
//  cm->inputoutput.method = type;
//  cml_recomputeObserver(cm);
//}



CML_DEF CMLIntegerMappingType cmlGetIntegerMappingType(const CMLColorMachine* cm){
  return cm->inputoutput.integermapping;
}


CML_DEF void cmlGet8BitCutoffs(const CMLColorMachine* cm, uint8* min, uint8* max, size_t channel){
  #if CML_DEBUG
    if(channel >= CML_MAX_NUMBER_OF_CHANNELS){cmlError("Invalid Channel number.");}
  #endif
  *min = (uint8)(cm->inputoutput.offset8Bit[channel]);
  *max = *min + (uint8)(cm->inputoutput.range8Bit[channel]);
}


CML_DEF void cmlGet16BitCutoffs(const CMLColorMachine* cm, uint16* min, uint16* max, size_t channel){
  #if CML_DEBUG
    if(channel >= CML_MAX_NUMBER_OF_CHANNELS){cmlError("Invalid Channel number.");}
  #endif
  *min = (uint16)(cm->inputoutput.offset16Bit[channel]);
  *max = *min + (uint16)(cm->inputoutput.range16Bit[channel]);
}


CML_DEF void cmlSet8BitCutoffs(CMLColorMachine* cm, uint8 min, uint8 max, size_t channel){
  #if CML_DEBUG
    if(channel >= CML_MAX_NUMBER_OF_CHANNELS){cmlError("Invalid Channel number.");}
  #endif
  cm->inputoutput.offset8Bit[channel] = (uint8)(min);
  cm->inputoutput.range8Bit[channel] = (float)(max - min);
}


CML_DEF void cmlSet16BitCutoffs(CMLColorMachine* cm, uint16 min, uint16 max, size_t channel){
  #if CML_DEBUG
    if(channel >= CML_MAX_NUMBER_OF_CHANNELS){cmlError("Invalid Channel number.");}
  #endif
  cm->inputoutput.offset16Bit[channel] = (uint16)(min);
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

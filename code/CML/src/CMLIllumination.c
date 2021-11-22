
#include "CML.h"
#include "StateMachine/CMLColorMachineState.h"


CML_API CMLIllumination* cmlCreateIlluminationDuplicate(CMLIllumination* illumination, const CMLIllumination* src){
  illumination = cmlAllocateIfNull(illumination, sizeof(CMLIllumination));
  illumination->BALFtype = src->BALFtype;
  illumination->BALFtemperature = src->BALFtemperature;
  if(src->BALFspectrum){
    illumination->BALFspectrum = CMLduplicateFunction(src->BALFspectrum);
  }else{
    illumination->BALFspectrum = CML_NULL;
  }
  cmlCpy3(illumination->BALFradiometricXYZ, src->BALFradiometricXYZ);
  return illumination;
}


CML_API CMLIllumination* cmlCreateIlluminationWithPreset(CMLIllumination* illumination, CMLIlluminationType type, float temperature){
  illumination = cmlAllocateIfNull(illumination, sizeof(CMLIllumination));
  illumination->BALFtype = type;
  illumination->BALFtemperature = temperature;
  illumination->BALFspectrum = cmlCreateIlluminationSpectrum(illumination->BALFtype, illumination->BALFtemperature);

  switch(illumination->BALFtype){
  case CML_ILLUMINATION_BLACKBODY:
    // temperature is already set.
    if(!illumination->BALFtemperature){illumination->BALFtemperature = CML_TEMPERATURE_A;}
    break;
  case CML_ILLUMINATION_A_CIE:
    illumination->BALFtemperature = 2848.f;
    break;
  case CML_ILLUMINATION_A_EXACT:
    illumination->BALFtemperature = CML_TEMPERATURE_A;
    break;
  case CML_ILLUMINATION_D_ILLUMINANT:
    // temperature is already set.
    if(!illumination->BALFtemperature){illumination->BALFtemperature = CML_TEMPERATURE_D65;}
    break;
  case CML_ILLUMINATION_D50:
    illumination->BALFtemperature = CML_TEMPERATURE_D50;
    break;
  case CML_ILLUMINATION_D55:
    illumination->BALFtemperature = CML_TEMPERATURE_D55;
    break;
  case CML_ILLUMINATION_D65:
    illumination->BALFtemperature = CML_TEMPERATURE_D65;
    break;
  case CML_ILLUMINATION_D75:
    illumination->BALFtemperature = CML_TEMPERATURE_D75;
    break;
  case CML_ILLUMINATION_D93:
    illumination->BALFtemperature = CML_TEMPERATURE_D93;
    break;
  default:
    // Any other illumination is computed using Robertson
    {
      illumination->BALFtemperature = 0.f;
//      CMLVec3 whitepointYuv;
//      cmlInternalOneYupvptoYuv(whitepointYuv, cm->illumination.whitepointYupvp);
//      cm->illumination.temperature = CMLgetCorrelatedColorTemperature(whitepointYuv);
    }
    break;
  }
  return illumination;
}


CML_API CMLIllumination* cmlCreateIlluminationWithCustomSpectrum(CMLIllumination* illumination, const CMLFunction* spectrum, const CMLObserver* observer){
  illumination = cmlAllocateIfNull(illumination, sizeof(CMLIllumination));
  illumination->BALFtype = CML_ILLUMINATION_CUSTOM_SPECTRUM;
  illumination->BALFtemperature = 0.f;
  illumination->BALFspectrum = CMLduplicateFunction(spectrum);

  cmlInternalOneIlluminationSpectrumtoXYZ(illumination->BALFradiometricXYZ, illumination->BALFspectrum, observer);

  CMLVec3 whitepointYxy;
  CMLVec3 whitepointYupvp;
  CMLVec3 whitepointYuv;
  cmlInternalOneXYZtoYxy(whitepointYxy, illumination->BALFradiometricXYZ, CML_NULL);
  cmlInternalOneYxytoYupvp(whitepointYupvp, whitepointYxy, CML_NULL);
  cmlInternalOneYupvptoYuv(whitepointYuv, whitepointYupvp);
  illumination->BALFtemperature = CMLgetCorrelatedColorTemperature(whitepointYuv);

  return illumination;
}


CML_API CMLIllumination* cmlCreateIlluminationWithCustomWhitepoint(CMLIllumination* illumination, const CMLVec3 whitepointYxy){
  illumination = cmlAllocateIfNull(illumination, sizeof(CMLIllumination));
  illumination->BALFtype = CML_ILLUMINATION_CUSTOM_WHITEPOINT;
  illumination->BALFspectrum = NULL;
  
  cmlInternalOneYxytoXYZ(illumination->BALFradiometricXYZ, whitepointYxy, CML_NULL);

  CMLVec3 whitepointYupvp;
  CMLVec3 whitepointYuv;
  cmlInternalOneYxytoYupvp(whitepointYupvp, whitepointYxy, CML_NULL);
  cmlInternalOneYupvptoYuv(whitepointYuv, whitepointYupvp);
  illumination->BALFtemperature = CMLgetCorrelatedColorTemperature(whitepointYuv);

  return illumination;
}



CML_API void cmlClearIllumination(CMLIllumination* illumination){
  cmlReleaseFunction(illumination->BALFspectrum);
}


CML_API void cmlDestroyIllumination(CMLIllumination* illumination){
  cmlClearIllumination(illumination);
  free(illumination);
}




CML_API CMLIlluminationType cmlGetIlluminationType(const CMLIllumination* illumination){
  return illumination->BALFtype;
}

CML_API const CMLFunction* cmlGetIlluminationSpectrum(const CMLIllumination* illumination){
  return illumination->BALFspectrum;
}


CML_API float cmlGetCorrelatedColorTemperature(const CMLIllumination* illumination){
//  if(!illumination->BALFtemperature){
//    // Computation takes long. Compute on demand.
//    return 0.f;
////    CMLVec3 whitepointYuv;
////    cmlInternalOneYupvptoYuv(whitepointYuv, cm->illumination.whitepointYupvp);
////    cm->illumination.temperature = CMLgetCorrelatedColorTemperature(whitepointYuv);
//  }
  if(!illumination->BALFtemperature){return CML_TEMPERATURE_D65;}
  return illumination->BALFtemperature;
}

CML_API void cmlGetIlluminationRadiometricXYZ(const CMLIllumination* illumination, float* dest, const CMLObserver* observer){
  if(illumination->BALFspectrum){
    cmlInternalOneIlluminationSpectrumtoXYZ(dest, illumination->BALFspectrum, observer);
  }else{
    cmlCpy3(dest, illumination->BALFradiometricXYZ);
  }
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

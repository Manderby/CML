
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.


#include "CML.h"
#include "CMLColorMachineState.h"


CMLAPI CMLIllumination* cmlCreateIlluminationDuplicate(CMLIllumination* illumination, const CMLIllumination* src){
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


CMLAPI CMLIllumination* cmlCreateIlluminationWithPreset(CMLIllumination* illumination, CMLIlluminationType type, float temperature){
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


CMLAPI CMLIllumination* cmlCreateIlluminationWithCustomSpectrum(CMLIllumination* illumination, const CMLFunction* spectrum, const CMLObserver* observer){
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


CMLAPI CMLIllumination* cmlCreateIlluminationWithCustomWhitepoint(CMLIllumination* illumination, const CMLVec3 whitepointYxy){
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



CMLAPI void cmlClearIllumination(CMLIllumination* illumination){
  cmlReleaseFunction(illumination->BALFspectrum);
}


CMLAPI void cmlDestroyIllumination(CMLIllumination* illumination){
  cmlClearIllumination(illumination);
  free(illumination);
}




CMLAPI CMLIlluminationType cmlGetIlluminationType(const CMLIllumination* illumination){
  return illumination->BALFtype;
}

CMLAPI const CMLFunction* cmlGetIlluminationSpectrum(const CMLIllumination* illumination){
  return illumination->BALFspectrum;
}


CMLAPI float cmlGetCorrelatedColorTemperature(const CMLIllumination* illumination){
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

CMLAPI void cmlGetIlluminationRadiometricXYZ(const CMLIllumination* illumination, float* dest, const CMLObserver* observer){
  if(illumination->BALFspectrum){
    cmlInternalOneIlluminationSpectrumtoXYZ(dest, illumination->BALFspectrum, observer);
  }else{
    cmlCpy3(dest, illumination->BALFradiometricXYZ);
  }
}




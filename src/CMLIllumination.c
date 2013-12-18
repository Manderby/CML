
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.


#include "CML.h"
#include "CMLColorMachineState.h"


CMLAPI void cmlDestroyIllumination(void* illum);


CMLAPI CMLIllumination* cmlCreateIlluminationWithPreset(CMLIlluminationType type, float temperature){
  CMLIllumination* illumination = cmlCreateObject(sizeof(CMLIllumination), cmlDestroyIllumination);
  illumination->type = type;
  illumination->temperature = temperature;
  illumination->spectrum = cmlCreateIlluminationSpectrum(illumination->type, illumination->temperature);

  switch(illumination->type){
  case CML_ILLUMINATION_BLACKBODY:
    // temperature is already set.
    if(!illumination->temperature){illumination->temperature = CML_TEMPERATURE_A;}
    break;
  case CML_ILLUMINATION_A_CIE:
    illumination->temperature = 2848.f;
    break;
  case CML_ILLUMINATION_A_EXACT:
    illumination->temperature = CML_TEMPERATURE_A;
    break;
  case CML_ILLUMINATION_D_ILLUMINANT:
    // temperature is already set.
    if(!illumination->temperature){illumination->temperature = CML_TEMPERATURE_D65;}
    break;
  case CML_ILLUMINATION_D50:
    illumination->temperature = CML_TEMPERATURE_D50;
    break;
  case CML_ILLUMINATION_D55:
    illumination->temperature = CML_TEMPERATURE_D55;
    break;
  case CML_ILLUMINATION_D65:
    illumination->temperature = CML_TEMPERATURE_D65;
    break;
  case CML_ILLUMINATION_D75:
    illumination->temperature = CML_TEMPERATURE_D75;
    break;
  case CML_ILLUMINATION_D93:
    illumination->temperature = CML_TEMPERATURE_D93;
    break;
  default:
    // Any other illumination is computed using Robertson on demand.
    {
      illumination->temperature = 0.f;
//      CMLVec3 whitepointYuv;
//      cmlInternalOneYupvptoYuv(whitepointYuv, cm->illumination.whitepointYupvp);
//      cm->illumination.temperature = cmlComputeCorrelatedColorTemperature(whitepointYuv);
    }
    break;
  }
  return illumination;
}


CMLAPI CMLIllumination* cmlCreateIlluminationWithCustomSpectrum(const CMLFunction* spectrum){
  CMLIllumination* illumination = cmlCreateObject(sizeof(CMLIllumination), cmlDestroyIllumination);
  illumination->type = CML_ILLUMINATION_CUSTOM_SPECTRUM;
  illumination->temperature = 0.f;
  illumination->spectrum = (CMLFunction*)cmlRetainObject(spectrum);

//  cmlInternalOneIlluminationSpectrumtoXYZ(illumination->radiometricXYZ, illumination->spectrum, observer);
//
//  CMLVec3 whitepointYxy;
//  CMLVec3 whitepointYupvp;
//  CMLVec3 whitepointYuv;
//  cmlInternalOneXYZtoYxy(whitepointYxy, illumination->radiometricXYZ, CML_NULL);
//  cmlInternalOneYxytoYupvp(whitepointYupvp, whitepointYxy, CML_NULL);
//  cmlInternalOneYupvptoYuv(whitepointYuv, whitepointYupvp);
//  illumination->temperature = cmlComputeCorrelatedColorTemperature(whitepointYuv);

  return illumination;
}


CMLAPI CMLIllumination* cmlCreateIlluminationWithCustomWhitepoint(const CMLVec3 whitepointYxy){
  CMLIllumination* illumination = cmlCreateObject(sizeof(CMLIllumination), cmlDestroyIllumination);
  illumination->type = CML_ILLUMINATION_CUSTOM_WHITEPOINT;
  illumination->spectrum = NULL;
  
  cmlInternalOneYxytoXYZ(illumination->radiometricXYZ, whitepointYxy, CML_NULL);

  CMLVec3 whitepointYupvp;
  CMLVec3 whitepointYuv;
  cmlInternalOneYxytoYupvp(whitepointYupvp, whitepointYxy, CML_NULL);
  cmlInternalOneYupvptoYuv(whitepointYuv, whitepointYupvp);
  illumination->temperature = cmlComputeCorrelatedColorTemperature(whitepointYuv);

  return illumination;
}




CMLAPI void cmlDestroyIllumination(void* illum){
  CMLIllumination* illumination = (CMLIllumination*)illum;
  cmlReleaseObject(illumination->spectrum);
}





CMLAPI CMLIlluminationType cmlGetIlluminationType(const CMLIllumination* illumination){
  return illumination->type;
}

CMLAPI const CMLFunction* cmlGetIlluminationSpectrum(const CMLIllumination* illumination){
  return illumination->spectrum;
}


CMLAPI float cmlGetCorrelatedColorTemperature(const CMLIllumination* illumination){
//  if(!illumination->temperature){
//    // Computation takes long. Compute on demand.
//    return 0.f;
////    CMLVec3 whitepointYuv;
////    cmlInternalOneYupvptoYuv(whitepointYuv, cm->illumination.whitepointYupvp);
////    cm->illumination.temperature = cmlComputeCorrelatedColorTemperature(whitepointYuv);
//  }
  if(!illumination->temperature){return CML_TEMPERATURE_D65;}
  return illumination->temperature;
}

CMLAPI void cmlGetIlluminationRadiometricXYZ(const CMLIllumination* illumination, float* dest, const CMLObserver* observer){
  if(illumination->spectrum){
    cmlInternalOneSpectrumtoRadiometricXYZ(dest, illumination->spectrum, observer);
  }else{
    cmlCpy3(dest, illumination->radiometricXYZ);
  }
}




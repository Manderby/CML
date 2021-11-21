
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.


#include "CML.h"
#include "StateMachine/CMLColorMachineState.h"


CMLAPI CMLObserver* cmlCreateObserverWithIllumination(
                                            CMLObserver* observer,
                                         CMLObserverType type,
                                        CMLIllumination* illumination,
                                                   float colorimetricBase){
  observer = cmlAllocateIfNull(observer, sizeof(CMLObserver));
  observer->BALFtype = type;
  cmlCreateSpecDistFunctions(observer->BALFspecdistfunctions, observer->BALFtype);
  cmlCreateIlluminationDuplicate(&(observer->BALFillumination), illumination);

  // Set the radiometric scale temporarily to 0 to compute the radiometric XYZ.
  observer->BALFradiometricScale = 0.;
  cmlGetIlluminationRadiometricXYZ(illumination, observer->BALFwhitepointXYZ, observer);

  if(colorimetricBase){
    observer->BALFradiometricScale = colorimetricBase / observer->BALFwhitepointXYZ[1];
    cmlSet3(observer->BALFwhitepointXYZ, observer->BALFwhitepointXYZ[0] * observer->BALFradiometricScale,
                                         colorimetricBase,
                                         observer->BALFwhitepointXYZ[2] * observer->BALFradiometricScale);    
  }
  cmlSet3(observer->BALFinverseWhitepointXYZ, cmlInverse(observer->BALFwhitepointXYZ[0]),
                                              cmlInverse(observer->BALFwhitepointXYZ[1]),
                                              cmlInverse(observer->BALFwhitepointXYZ[2]));
  cmlInternalOneXYZtoYxy(observer->BALFwhitepointYxy, observer->BALFwhitepointXYZ, CML_NULL);
  cmlInternalOneYxytoYupvp(observer->BALFwhitepointYupvp, observer->BALFwhitepointYxy, CML_NULL);
  return observer;
}



CMLAPI void cmlClearObserver(CMLObserver* observer){
  cmlReleaseFunction(observer->BALFspecdistfunctions[0]);
  cmlReleaseFunction(observer->BALFspecdistfunctions[1]);
  cmlReleaseFunction(observer->BALFspecdistfunctions[2]);
  cmlClearIllumination(&(observer->BALFillumination));
}

CMLAPI void cmlDestroyObserver(CMLObserver* observer){
  cmlClearObserver(observer);
  free(observer);
}



CMLAPI float cmlGetObserverRadiometricScale(const CMLObserver* observer){
  if(observer->BALFradiometricScale){
    return observer->BALFradiometricScale;
  }else{
    return 1.f; // when radiometricScale is 0, computation is radiometric.
  }
}


CMLAPI float cmlGetObserverColorimetricBase(const CMLObserver* observer){
  if(observer->BALFradiometricScale){
    return observer->BALFwhitepointXYZ[1];
  }else{
    return 0.f; // when radiometricScale is 0, computation is radiometric
  }
}


CMLAPI const CMLFunction* cmlGetObserverSpecDistFunction(const CMLObserver* observer, CMLInt index){
  return observer->BALFspecdistfunctions[index];
}


CMLAPI CMLObserverType cmlGetObserverType(const CMLObserver* observer){
  return observer->BALFtype;
}

CMLAPI const CMLIllumination* cmlGetReferenceIllumination(const CMLObserver* observer){
  return &(observer->BALFillumination);
}

CMLAPI const CMLFunction* cmlGetReferenceIlluminationSpectrum(const CMLObserver* observer){
  return cmlGetIlluminationSpectrum(&(observer->BALFillumination));
}

CMLAPI const float* cmlGetReferenceWhitepointXYZ(const CMLObserver* observer){
  return observer->BALFwhitepointXYZ;
}

CMLAPI const float* cmlGetReferenceInverseWhitepointXYZ(const CMLObserver* observer){
  return observer->BALFinverseWhitepointXYZ;
}

CMLAPI const float* cmlGetReferenceWhitepointYxy(const CMLObserver* observer){
  return observer->BALFwhitepointYxy;
}

CMLAPI const float* cmlGetReferenceWhitepointYupvp(const CMLObserver* observer){
  return observer->BALFwhitepointYupvp;
}





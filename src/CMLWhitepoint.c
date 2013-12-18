
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.


#include "CML.h"
#include "StateMachine/CMLColorMachineState.h"


CMLAPI void cmlDestroyWhitepoint(void* whitepoint);


CMLAPI CMLWhitepoint* cmlCreateWhitepointWithIllumination(
                                  const CMLIllumination* illumination,
                                      const CMLObserver* observer,
                                                   float colorimetricBase){
  CMLWhitepoint* whitepoint = cmlCreateObject(sizeof(CMLWhitepoint), cmlDestroyWhitepoint);
  whitepoint->observer = cmlRetainObject(observer);
  whitepoint->illumination = cmlRetainObject(illumination);

  whitepoint->radiometricScale = colorimetricBase;
  cmlGetIlluminationRadiometricXYZ(illumination, whitepoint->whitepointXYZ, observer);
  if(colorimetricBase){
    whitepoint->radiometricScale /= whitepoint->whitepointXYZ[1];
    cmlSet3(whitepoint->whitepointXYZ, whitepoint->whitepointXYZ[0] * whitepoint->radiometricScale,
                                         colorimetricBase,
                                         whitepoint->whitepointXYZ[2] * whitepoint->radiometricScale);    
  }
  cmlSet3(whitepoint->inverseWhitepointXYZ, cmlInverse(whitepoint->whitepointXYZ[0]),
                                              cmlInverse(whitepoint->whitepointXYZ[1]),
                                              cmlInverse(whitepoint->whitepointXYZ[2]));
  cmlInternalOneXYZtoYxy(whitepoint->whitepointYxy, whitepoint->whitepointXYZ, CML_NULL);
  cmlInternalOneYxytoYupvp(whitepoint->whitepointYupvp, whitepoint->whitepointYxy, CML_NULL);

  return whitepoint;
}


CMLAPI void cmlDestroyWhitepoint(void* wp){
  CMLWhitepoint* whitepoint = (CMLWhitepoint*)wp;
  cmlReleaseObject(whitepoint->observer);
  cmlReleaseObject(whitepoint->illumination);
}



CMLAPI float cmlGetWhitepointRadiometricScale(const CMLWhitepoint* whitepoint){
  if(whitepoint->radiometricScale){
    return whitepoint->radiometricScale;
  }else{
    return 1.f; // when radiometricScale is 0, computation is radiometric.
  }
}


CMLAPI float cmlGetWhitepointColorimetricBase(const CMLWhitepoint* whitepoint){
  if(whitepoint->radiometricScale){
    return whitepoint->whitepointXYZ[1];
  }else{
    return 0.f; // when radiometricScale is 0, computation is radiometric
  }
}


CMLAPI const CMLObserver* cmlGetWhitepointObserver(const CMLWhitepoint* whitepoint){
  return whitepoint->observer;
}


CMLAPI const CMLIllumination* cmlGetWhitepointIllumination(const CMLWhitepoint* whitepoint){
  return whitepoint->illumination;
}



CMLAPI const float* cmlGetWhitepointXYZ(const CMLWhitepoint* whitepoint){
  return whitepoint->whitepointXYZ;
}

CMLAPI const float* cmlGetWhitepointInverseXYZ(const CMLWhitepoint* whitepoint){
  return whitepoint->inverseWhitepointXYZ;
}

CMLAPI const float* cmlGetWhitepointYxy(const CMLWhitepoint* whitepoint){
  return whitepoint->whitepointYxy;
}

CMLAPI const float* cmlGetWhitepointYupvp(const CMLWhitepoint* whitepoint){
  return whitepoint->whitepointYupvp;
}




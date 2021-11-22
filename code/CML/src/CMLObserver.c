
#include "CML.h"
#include "StateMachine/CMLColorMachineState.h"


CML_API CMLObserver* cmlCreateObserverWithIllumination(
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



CML_API void cmlClearObserver(CMLObserver* observer){
  cmlReleaseFunction(observer->BALFspecdistfunctions[0]);
  cmlReleaseFunction(observer->BALFspecdistfunctions[1]);
  cmlReleaseFunction(observer->BALFspecdistfunctions[2]);
  cmlClearIllumination(&(observer->BALFillumination));
}

CML_API void cmlDestroyObserver(CMLObserver* observer){
  cmlClearObserver(observer);
  free(observer);
}



CML_API float cmlGetObserverRadiometricScale(const CMLObserver* observer){
  if(observer->BALFradiometricScale){
    return observer->BALFradiometricScale;
  }else{
    return 1.f; // when radiometricScale is 0, computation is radiometric.
  }
}


CML_API float cmlGetObserverColorimetricBase(const CMLObserver* observer){
  if(observer->BALFradiometricScale){
    return observer->BALFwhitepointXYZ[1];
  }else{
    return 0.f; // when radiometricScale is 0, computation is radiometric
  }
}


CML_API const CMLFunction* cmlGetObserverSpecDistFunction(const CMLObserver* observer, CMLInt index){
  return observer->BALFspecdistfunctions[index];
}


CML_API CMLObserverType cmlGetObserverType(const CMLObserver* observer){
  return observer->BALFtype;
}

CML_API const CMLIllumination* cmlGetReferenceIllumination(const CMLObserver* observer){
  return &(observer->BALFillumination);
}

CML_API const CMLFunction* cmlGetReferenceIlluminationSpectrum(const CMLObserver* observer){
  return cmlGetIlluminationSpectrum(&(observer->BALFillumination));
}

CML_API const float* cmlGetReferenceWhitepointXYZ(const CMLObserver* observer){
  return observer->BALFwhitepointXYZ;
}

CML_API const float* cmlGetReferenceInverseWhitepointXYZ(const CMLObserver* observer){
  return observer->BALFinverseWhitepointXYZ;
}

CML_API const float* cmlGetReferenceWhitepointYxy(const CMLObserver* observer){
  return observer->BALFwhitepointYxy;
}

CML_API const float* cmlGetReferenceWhitepointYupvp(const CMLObserver* observer){
  return observer->BALFwhitepointYupvp;
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

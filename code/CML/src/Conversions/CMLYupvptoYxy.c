
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

#include "../CML.h"
#include "../StateMachine/CMLInternal.h"



#define CMLINTERNALYupvpToYxy(Yxy0, Yxy1, Yxy2, Yupvp0, Yupvp1, Yupvp2, whiteYxy) \
  float divisor;\
  *Yxy0 = *Yupvp0;\
  divisor = 6.f * *Yupvp1 - 16.f * *Yupvp2 + 12.f;\
  if(divisor == 0.f){\
    if(whiteYxy){\
      *Yxy1 = whiteYxy[1];\
      *Yxy2 = whiteYxy[2];\
    }else{\
      *Yxy1 = 0.f;\
      *Yxy2 = 0.f;\
    }\
  }else{\
    float factor = cmlInverse(divisor);\
    *Yxy1 = 9.f * *Yupvp1 * factor;\
    *Yxy2 = 4.f * *Yupvp2 * factor;\
  }




CML_HIDDEN CML_INLINE void cml_OneYupvpToYxy (float* CML_RESTRICT Yxy0, float* CML_RESTRICT Yxy1, float* CML_RESTRICT Yxy2, const float* CML_RESTRICT Yupvp0, const float* CML_RESTRICT Yupvp1, const float* CML_RESTRICT Yupvp2, const float* CML_RESTRICT whiteYxy){
  CMLINTERNALYupvpToYxy(Yxy0, Yxy1, Yxy2, Yupvp0, Yupvp1, Yupvp2, whiteYxy);
}

CML_HIDDEN CML_INLINE void cml_OneYupvpToYxy_SB(float* CML_RESTRICT buf0, float* CML_RESTRICT buf1, float* CML_RESTRICT buf2, const float* CML_RESTRICT whiteYxy){
  CMLINTERNALYupvpToYxy(buf0, buf1, buf2, buf0, buf1, buf2, whiteYxy);
}



CML_HIDDEN void cml_YupvpToYxy (CMLOutput out , CMLInput in, CMLSize count){
  CMLMOBObserver* observer = cmlGetConverterSetting(CML_SETTING_OBSERVER, CML_GET_EQU);
  if(cmlGetConverterError()){return;}

  const float* whiteYxy = cmlGetObserverAdaptationWhiteYxyRadiometric(observer);

  while(count){
    const float* Yupvp0 = cmlNextConstFloatComponent(in);
    const float* Yupvp1 = cmlNextConstFloatComponent(in);
    const float* Yupvp2 = cmlNextConstFloatComponent(in);
    float* Yxy0 = cmlNextMutableFloatComponent(out);
    float* Yxy1 = cmlNextMutableFloatComponent(out);
    float* Yxy2 = cmlNextMutableFloatComponent(out);

    cml_OneYupvpToYxy(Yxy0, Yxy1, Yxy2, Yupvp0, Yupvp1, Yupvp2, whiteYxy);

    count--;
  }

}


CML_HIDDEN void cml_YupvpToYxy_SB(CMLInputOutput buf, CMLSize count){
  CMLMOBObserver* observer = cmlGetConverterSetting(CML_SETTING_OBSERVER, CML_GET_EQU);
  if(cmlGetConverterError()){return;}
  
  const float* whiteYxy = cmlGetObserverAdaptationWhiteYxyRadiometric(observer);

  while(count){
    float* buf0 = cmlNextMutableFloatComponent(buf);
    float* buf1 = cmlNextMutableFloatComponent(buf);
    float* buf2 = cmlNextMutableFloatComponent(buf);

    cml_OneYupvpToYxy_SB(buf0, buf1, buf2, whiteYxy);

    count--;
  }

}




// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

#include "../CML.h"
#include "../StateMachine/CMLInternal.h"




CML_HIDDEN CML_INLINE void cml_OneYxyToYupvp_SB(float* CML_RESTRICT buf0, float* CML_RESTRICT buf1, float* CML_RESTRICT buf2, const float* CML_RESTRICT whiteYupvp){
  CMLINTERNALYxyToYupvp(buf0, buf1, buf2, buf0, buf1, buf2, whiteYupvp);
}





CML_HIDDEN void cml_YxyToYupvp (CMLOutput out , CMLInput in, CMLSize count){
  CMLMOBObserver* observer = cmlGetConverterSetting(CML_SETTING_OBSERVER, CML_GET_EQU);
  if(cmlGetConverterError()){return;}

  const float* whiteYupvp = cmlGetObserverAdaptationWhiteYupvpRadiometric(observer);

  while(count){
    const float* Yxy0 = cmlNextConstFloatComponent(in);
    const float* Yxy1 = cmlNextConstFloatComponent(in);
    const float* Yxy2 = cmlNextConstFloatComponent(in);
    float* Yupvp0 = cmlNextMutableFloatComponent(out);
    float* Yupvp1 = cmlNextMutableFloatComponent(out);
    float* Yupvp2 = cmlNextMutableFloatComponent(out);

    cml_OneYxyToYupvp(Yupvp0, Yupvp1, Yupvp2, Yxy0, Yxy1, Yxy2, whiteYupvp);

    count--;
  }

}

CML_HIDDEN void cml_YxyToYupvp_SB(CMLInputOutput buf, CMLSize count){
  CMLMOBObserver* observer = cmlGetConverterSetting(CML_SETTING_OBSERVER, CML_GET_EQU);
  if(cmlGetConverterError()){return;}

  const float* whiteYupvp = cmlGetObserverAdaptationWhiteYupvpRadiometric(observer);

  while(count){
    float* buf0 = cmlNextMutableFloatComponent(buf);
    float* buf1 = cmlNextMutableFloatComponent(buf);
    float* buf2 = cmlNextMutableFloatComponent(buf);

    cml_OneYxyToYupvp_SB(buf0, buf1, buf2, whiteYupvp);

    count--;
  }

}








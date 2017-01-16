
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

#include "CML.h"
#include "CMLInternal.h"




CML_HIDDEN CML_INLINE void cml_OneXYZToYxy_SB (float* CML_RESTRICT buf0, float* CML_RESTRICT buf1, float* CML_RESTRICT buf2, const float* CML_RESTRICT whiteYxy){
  CMLINTERNALXYZToYxy(buf0, buf1, buf2, buf0, buf1, buf2, whiteYxy);
}


CML_HIDDEN void cml_XYZToYxy(CMLOutput out , CMLInput in, CMLSize count){
  CMLMOBObserver* observer = cmlGetConverterSetting(CML_SETTING_OBSERVER, CML_GET_EQU);
  if(cmlGetConverterError()){return;}

  const float* whiteYxy = cmlGetObserverAdaptationWhiteYxyRadiometric(observer);

  while(count){
    const float* XYZ0 = cmlNextConstFloatComponent(in);
    const float* XYZ1 = cmlNextConstFloatComponent(in);
    const float* XYZ2 = cmlNextConstFloatComponent(in);
    float* Yxy0 = cmlNextMutableFloatComponent(out);
    float* Yxy1 = cmlNextMutableFloatComponent(out);
    float* Yxy2 = cmlNextMutableFloatComponent(out);
    
    cml_OneXYZToYxy(Yxy0, Yxy1, Yxy2, XYZ0, XYZ1, XYZ2, whiteYxy);
    
    count--;
  }
}


CML_HIDDEN void cml_XYZToYxy_SB(CMLInputOutput buf, CMLSize count){
  CMLMOBObserver* observer = cmlGetConverterSetting(CML_SETTING_OBSERVER, CML_GET_EQU);
  if(cmlGetConverterError()){return;}

  const float* whiteYxy = cmlGetObserverAdaptationWhiteYxyRadiometric(observer);

  while(count){
    float* buf0 = cmlNextMutableFloatComponent(buf);
    float* buf1 = cmlNextMutableFloatComponent(buf);
    float* buf2 = cmlNextMutableFloatComponent(buf);

    cml_OneXYZToYxy_SB(buf0, buf1, buf2, whiteYxy);

    count--;
  }
}




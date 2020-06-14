
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

#include "../CML.h"
#include "../StateMachine/CMLInternal.h"



CML_HIDDEN CML_INLINE void cml_OneYxyToXYZ_SB(float* CML_RESTRICT buf0, float* CML_RESTRICT buf1, float* CML_RESTRICT buf2, const float* CML_RESTRICT whiteXYZ){
  CMLINTERNALYxyToXYZ(buf0, buf1, buf2, buf0, buf1, buf2, whiteXYZ);
}






CML_HIDDEN void cml_YxyToXYZ (CMLOutput out , CMLInput in, CMLSize count){
  CMLMOBObserver* observer = cmlGetConverterSetting(CML_SETTING_OBSERVER, CML_GET_EQU);
  if(cmlGetConverterError()){return;}

  const float* whiteXYZ = cmlGetObserverAdaptationWhiteXYZRadiometric(observer);

  while(count){
    const float* Yxy0 = cmlNextConstFloatComponent(in);
    const float* Yxy1 = cmlNextConstFloatComponent(in);
    const float* Yxy2 = cmlNextConstFloatComponent(in);
    float* XYZ0 = cmlNextMutableFloatComponent(out);
    float* XYZ1 = cmlNextMutableFloatComponent(out);
    float* XYZ2 = cmlNextMutableFloatComponent(out);

    cml_OneYxyToXYZ(XYZ0, XYZ1, XYZ2, Yxy0, Yxy1, Yxy2, whiteXYZ);

    count--;
  }

}

CML_HIDDEN void cml_YxyToXYZ_SB(CMLInputOutput buf, CMLSize count){
  CMLMOBObserver* observer = cmlGetConverterSetting(CML_SETTING_OBSERVER, CML_GET_EQU);
  if(cmlGetConverterError()){return;}

  const float* whiteXYZ = cmlGetObserverAdaptationWhiteXYZRadiometric(observer);

  while(count){
    float* buf0 = cmlNextMutableFloatComponent(buf);
    float* buf1 = cmlNextMutableFloatComponent(buf);
    float* buf2 = cmlNextMutableFloatComponent(buf);

    cml_OneYxyToXYZ_SB(buf0, buf1, buf2, whiteXYZ);

    count--;
  }

}






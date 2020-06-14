
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

#include "../CML.h"
#include "../StateMachine/CMLInternal.h"


// todo: make 3 response curves
#define CMLINTERNALXYZtoCIELAB(Lab0, Lab1, Lab2, XYZ0, XYZ1, XYZ2, whiteInvXYZ, LineartoLResponse) \
  float xr = *XYZ0 * whiteInvXYZ[0];\
  float yr = *XYZ1 * whiteInvXYZ[1];\
  float zr = *XYZ2 * whiteInvXYZ[2];\
  float Lr = cml_Eval(LineartoLResponse, yr);\
  float fx = cml_Lrtofy(cml_Eval(LineartoLResponse, xr));\
  float fy = cml_Lrtofy(Lr);\
  float fz = cml_Lrtofy(cml_Eval(LineartoLResponse, zr));\
  *Lab0 = 100.f * Lr;\
  *Lab1 = (fx - fy) * 500.f;\
  *Lab2 = (fy - fz) * 200.f;


CML_HIDDEN CML_INLINE void cml_OneXYZtoCIELAB(float* CML_RESTRICT Lab0, float* CML_RESTRICT Lab1, float* CML_RESTRICT Lab2, const float* CML_RESTRICT XYZ0, const float* CML_RESTRICT XYZ1, const float* CML_RESTRICT XYZ2, const CMLVec3 whiteInvXYZ, CMLMOBFunction* LineartoLResponse){
  CMLINTERNALXYZtoCIELAB(Lab0, Lab1, Lab2, XYZ0, XYZ1, XYZ2, whiteInvXYZ, LineartoLResponse);
}

CML_HIDDEN CML_INLINE void cml_OneXYZtoCIELAB_SB(float* CML_RESTRICT buf0, float* CML_RESTRICT buf1, float* CML_RESTRICT buf2, const CMLVec3 whiteInvXYZ, CMLMOBFunction* LineartoLResponse){
  CMLINTERNALXYZtoCIELAB(buf0, buf1, buf2, buf0, buf1, buf2, whiteInvXYZ, LineartoLResponse);
}



CML_HIDDEN void cml_XYZToLab(CMLOutput out , CMLInput in, CMLSize count){
  MOB* responsecurves = (CMLMOBResponseCurve*)cmlGetConverterSetting(CML_SETTING_CHANNEL_RESPONSE_CURVES, CML_GET_ADD);
  CMLMOBObserver* observer = cmlGetConverterSetting(CML_SETTING_OBSERVER, CML_GET_EQU);
  if(cmlGetConverterError()){return;}

  const float* whiteInvXYZ = cmlGetObserverAdaptationWhiteInvXYZRadiometric(observer);
  CMLMOBFunction* LineartoLResponse = cmlGetResponseCurveForwardFunc(mobGetArrayObject(responsecurves, 1));

  while(count){
    const float* XYZ0 = cmlNextConstFloatComponent(in);
    const float* XYZ1 = cmlNextConstFloatComponent(in);
    const float* XYZ2 = cmlNextConstFloatComponent(in);
    float* Lab0 = cmlNextMutableFloatComponent(out);
    float* Lab1 = cmlNextMutableFloatComponent(out);
    float* Lab2 = cmlNextMutableFloatComponent(out);

    cml_OneXYZtoCIELAB(Lab0, Lab1, Lab2, XYZ0, XYZ1, XYZ2, whiteInvXYZ, LineartoLResponse);

    count--;
  }  
}


CML_HIDDEN void cml_XYZToLab_SB(CMLInputOutput buf, CMLSize count){
  MOB* responsecurves = (CMLMOBFunctionVector*)cmlGetConverterSetting(CML_SETTING_CHANNEL_RESPONSE_CURVES, CML_GET_ADD);
  CMLMOBObserver* observer = cmlGetConverterSetting(CML_SETTING_OBSERVER, CML_GET_EQU);
  if(cmlGetConverterError()){return;}

  const float* whiteInvXYZ = cmlGetObserverAdaptationWhiteInvXYZRadiometric(observer);
  CMLMOBFunction* LineartoLResponse = cmlGetResponseCurveForwardFunc(mobGetArrayObject(responsecurves, 1));

  while(count){
    float* buf0 = cmlNextMutableFloatComponent(buf);
    float* buf1 = cmlNextMutableFloatComponent(buf);
    float* buf2 = cmlNextMutableFloatComponent(buf);

    cml_OneXYZtoCIELAB_SB(buf0, buf1, buf2, whiteInvXYZ, LineartoLResponse);

    count--;
  }
}




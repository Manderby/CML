
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

#include "../CML.h"
#include "../StateMachine/CMLInternal.h"


#define CMLINTERNALCIELABtoXYZ(XYZ0, XYZ1, XYZ2, Lab0, Lab1, Lab2, whiteXYZ, LtoLinearResponse) \
    float Lr = .01f * *Lab0;\
    float fy = cml_Lrtofy(Lr);\
    float fx = fy + *Lab1 * .002f;\
    float fz = fy - *Lab2 * .005f;\
    float xr = cml_Eval(LtoLinearResponse, cml_fytoLr(fx));\
    float yr = cml_Eval(LtoLinearResponse, Lr);\
    float zr = cml_Eval(LtoLinearResponse, cml_fytoLr(fz));\
    *XYZ0 = xr * whiteXYZ[0];\
    *XYZ1 = yr * whiteXYZ[1];\
    *XYZ2 = zr * whiteXYZ[2];


CML_HIDDEN CML_INLINE void cml_OneCIELABtoXYZ (float* CML_RESTRICT XYZ0, float* CML_RESTRICT XYZ1, float* CML_RESTRICT XYZ2, const float* CML_RESTRICT Lab0, const float* CML_RESTRICT Lab1, const float* CML_RESTRICT Lab2, const CMLVec3 whiteXYZ, CMLMOBFunction* LtoLinearResponse){
  CMLINTERNALCIELABtoXYZ(XYZ0, XYZ1, XYZ2, Lab0, Lab1, Lab2, whiteXYZ, LtoLinearResponse);
}



CML_HIDDEN void cml_LabToXYZ (CMLOutput out , CMLInput in, CMLSize count){
  MOB* responsecurves = (CMLMOBFunctionVector*)cmlGetConverterSetting(CML_SETTING_CHANNEL_RESPONSE_CURVES, CML_GET_SUB);
  CMLMOBObserver* observer = cmlGetConverterSetting(CML_SETTING_OBSERVER, CML_GET_EQU);
  if(cmlGetConverterError()){return;}

  CMLMOBFunction* LtoLinearResponse = cmlGetResponseCurveBackwardFunc(mobGetArrayObject(responsecurves, 1));
  const float* whiteXYZ = cmlGetObserverAdaptationWhiteXYZRadiometric(observer);

  while(count){
    const float* Lab0 = cmlNextConstFloatComponent(in);
    const float* Lab1 = cmlNextConstFloatComponent(in);
    const float* Lab2 = cmlNextConstFloatComponent(in);
    float* XYZ0 = cmlNextMutableFloatComponent(out);
    float* XYZ1 = cmlNextMutableFloatComponent(out);
    float* XYZ2 = cmlNextMutableFloatComponent(out);

    cml_OneCIELABtoXYZ(XYZ0, XYZ1, XYZ2, Lab0, Lab1, Lab2, whiteXYZ, LtoLinearResponse);

    count--;
  }
  
}




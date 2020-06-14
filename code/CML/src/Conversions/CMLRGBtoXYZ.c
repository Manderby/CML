
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

#include "../CML.h"
#include "../StateMachine/CMLInternal.h"


#define CMLINTERNALRGBToXYZ(XYZ0, XYZ1, XYZ2, RGB0, RGB1, RGB2, RGBToXYZmatrix, RtoLinearResponse, GtoLinearResponse, BtoLinearResponse) \
  CMLVec3 RGBp;\
  CMLVec3 XYZ;\
  RGBp[0] = cml_Eval(RtoLinearResponse, *RGB0);\
  RGBp[1] = cml_Eval(GtoLinearResponse, *RGB1);\
  RGBp[2] = cml_Eval(BtoLinearResponse, *RGB2);\
  cmlMat33MulVec3(XYZ, RGBToXYZmatrix, RGBp);\
  *XYZ0 = XYZ[0];\
  *XYZ1 = XYZ[1];\
  *XYZ2 = XYZ[2];



CML_HIDDEN CML_INLINE void cml_OneRGBToXYZ (float* CML_RESTRICT XYZ0, float* CML_RESTRICT XYZ1, float* CML_RESTRICT XYZ2, const float* CML_RESTRICT RGB0, const float* CML_RESTRICT RGB1, const float* CML_RESTRICT RGB2, const CMLMat33 RGBToXYZmatrix, CMLMOBFunction* RtoLinearResponse, CMLMOBFunction* GtoLinearResponse, CMLMOBFunction* BtoLinearResponse){
  CMLINTERNALRGBToXYZ(XYZ0, XYZ1, XYZ2, RGB0, RGB1, RGB2, RGBToXYZmatrix, RtoLinearResponse, GtoLinearResponse, BtoLinearResponse);
}



CML_HIDDEN CML_INLINE void cml_OneRGBToXYZ_SB (float* CML_RESTRICT buf0, float* CML_RESTRICT buf1, float* CML_RESTRICT buf2, const CMLMat33 RGBToXYZmatrix, CMLMOBFunction* RtoLinearResponse, CMLMOBFunction* GtoLinearResponse, CMLMOBFunction* BtoLinearResponse){
  CMLINTERNALRGBToXYZ(buf0, buf1, buf2, buf0, buf1, buf2, RGBToXYZmatrix, RtoLinearResponse, GtoLinearResponse, BtoLinearResponse);
}





CML_HIDDEN void cml_RGBToXYZ (CMLOutput out , CMLInput in, CMLSize count){

  MOB* responsecurves = (CMLMOBResponseCurve*)cmlGetConverterSetting(CML_SETTING_CHANNEL_RESPONSE_CURVES, CML_GET_SUB);
  MOB* observerMOB = cmlGetConverterSetting(CML_SETTING_OBSERVER, CML_GET_ADD);
  MOB* generatorMOB = cmlGetConverterSetting(CML_SETTING_GENERATOR, CML_GET_SUB);
  MOB* RGBToXYZmatrixMOB = cmlGetConverterSetting(CML_SETTING_GEN_TO_OBS_MATRIX, CML_GET_CONVERT);
  CML_UNUSED(observerMOB);
  CML_UNUSED(generatorMOB);
  if(cmlGetConverterError()){return;}

  CMLMOBFunction* RtoLinearResponse = cmlGetResponseCurveBackwardFunc(mobGetArrayObject(responsecurves, 0));
  CMLMOBFunction* GtoLinearResponse = cmlGetResponseCurveBackwardFunc(mobGetArrayObject(responsecurves, 1));
  CMLMOBFunction* BtoLinearResponse = cmlGetResponseCurveBackwardFunc(mobGetArrayObject(responsecurves, 2));
  const float* RGBToXYZmatrix = mobConstArrayData(RGBToXYZmatrixMOB);

  while(count){
    const float* RGB0 = cmlNextConstFloatComponent(in);
    const float* RGB1 = cmlNextConstFloatComponent(in);
    const float* RGB2 = cmlNextConstFloatComponent(in);
    float* XYZ0 = cmlNextMutableFloatComponent(out);
    float* XYZ1 = cmlNextMutableFloatComponent(out);
    float* XYZ2 = cmlNextMutableFloatComponent(out);

    cml_OneRGBToXYZ(XYZ0, XYZ1, XYZ2, RGB0, RGB1, RGB2, RGBToXYZmatrix, RtoLinearResponse, GtoLinearResponse, BtoLinearResponse);

    count--;
  }
}



CML_HIDDEN void cml_RGBToXYZ_SB(CMLInputOutput buf, CMLSize count){

  MOB* responsecurves = (CMLMOBResponseCurve*)cmlGetConverterSetting(CML_SETTING_CHANNEL_RESPONSE_CURVES, CML_GET_SUB);
  MOB* observerMOB = cmlGetConverterSetting(CML_SETTING_OBSERVER, CML_GET_ADD);
  MOB* generatorMOB = cmlGetConverterSetting(CML_SETTING_GENERATOR, CML_GET_SUB);
  MOB* RGBToXYZmatrixMOB = cmlGetConverterSetting(CML_SETTING_GEN_TO_OBS_MATRIX, CML_GET_CONVERT);
  CML_UNUSED(observerMOB);
  CML_UNUSED(generatorMOB);
  if(cmlGetConverterError()){return;}

  CMLMOBFunction* RtoLinearResponse = cmlGetResponseCurveBackwardFunc(mobGetArrayObject(responsecurves, 0));
  CMLMOBFunction* GtoLinearResponse = cmlGetResponseCurveBackwardFunc(mobGetArrayObject(responsecurves, 1));
  CMLMOBFunction* BtoLinearResponse = cmlGetResponseCurveBackwardFunc(mobGetArrayObject(responsecurves, 2));
  const float* RGBToXYZmatrix = mobConstArrayData(RGBToXYZmatrixMOB);

  while(count){
    float* buf0 = cmlNextMutableFloatComponent(buf);
    float* buf1 = cmlNextMutableFloatComponent(buf);
    float* buf2 = cmlNextMutableFloatComponent(buf);

    cml_OneRGBToXYZ_SB(buf0, buf1, buf2, RGBToXYZmatrix, RtoLinearResponse, GtoLinearResponse, BtoLinearResponse);

    count--;
  }
}


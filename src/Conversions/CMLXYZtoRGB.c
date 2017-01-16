
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

#include "CML.h"
#include "CMLInternal.h"



#define CMLINTERNALXYZToRGB(RGB0, RGB1, RGB2, XYZ0, XYZ1, XYZ2, XYZToRGBmatrix, LineartoRResponse, LineartoGResponse, LineartoBResponse) \
  CMLVec3 RGBp;\
  cmlMat33MulFloat3(RGBp, XYZToRGBmatrix, *XYZ0, *XYZ1, *XYZ2);\
  *RGB0 = cml_Eval(LineartoRResponse, RGBp[0]);\
  *RGB1 = cml_Eval(LineartoGResponse, RGBp[1]);\
  *RGB2 = cml_Eval(LineartoBResponse, RGBp[2]);



CML_HIDDEN CML_INLINE void cml_OneXYZToRGB (float* CML_RESTRICT RGB0, float* CML_RESTRICT RGB1, float* CML_RESTRICT RGB2, const float* CML_RESTRICT XYZ0, const float* CML_RESTRICT XYZ1, const float* CML_RESTRICT XYZ2, const CMLMat33 XYZToRGBmatrix, CMLMOBFunction* LineartoRResponse, CMLMOBFunction* LineartoGResponse, CMLMOBFunction* LineartoBResponse){
  CMLINTERNALXYZToRGB(RGB0, RGB1, RGB2, XYZ0, XYZ1, XYZ2, XYZToRGBmatrix, LineartoRResponse, LineartoGResponse, LineartoBResponse);
}


CML_HIDDEN CML_INLINE void cml_OneXYZToRGB_SB (float* CML_RESTRICT buf0, float* CML_RESTRICT buf1, float* CML_RESTRICT buf2, const CMLMat33 XYZToRGBmatrix, CMLMOBFunction* LineartoRResponse, CMLMOBFunction* LineartoGResponse, CMLMOBFunction* LineartoBResponse){
  CMLINTERNALXYZToRGB(buf0, buf1, buf2, buf0, buf1, buf2, XYZToRGBmatrix, LineartoRResponse, LineartoGResponse, LineartoBResponse);
}



CML_HIDDEN void cml_XYZToRGB (CMLOutput out , CMLInput in, CMLSize count){
  MOB* responsecurves = (CMLMOBResponseCurve*)cmlGetConverterSetting(CML_SETTING_CHANNEL_RESPONSE_CURVES, CML_GET_ADD);
  MOB* observerMOB = cmlGetConverterSetting(CML_SETTING_OBSERVER, CML_GET_SUB);
  MOB* generatorMOB = cmlGetConverterSetting(CML_SETTING_GENERATOR, CML_GET_ADD);
  MOB* XYZToRGBmatrixMOB = cmlGetConverterSetting(CML_SETTING_OBS_TO_GEN_MATRIX, CML_GET_CONVERT);
  CML_UNUSED(observerMOB);
  CML_UNUSED(generatorMOB);
  if(cmlGetConverterError()){return;}

  CMLMOBFunction* LineartoRResponse = cmlGetResponseCurveForwardFunc(mobGetArrayObject(responsecurves, 0));
  CMLMOBFunction* LineartoGResponse = cmlGetResponseCurveForwardFunc(mobGetArrayObject(responsecurves, 1));
  CMLMOBFunction* LineartoBResponse = cmlGetResponseCurveForwardFunc(mobGetArrayObject(responsecurves, 2));
  const float* XYZToRGBmatrix = mobConstArrayData(XYZToRGBmatrixMOB);

  while(count){
    const float* XYZ0 = cmlNextConstFloatComponent(in);
    const float* XYZ1 = cmlNextConstFloatComponent(in);
    const float* XYZ2 = cmlNextConstFloatComponent(in);
    float* RGB0 = cmlNextMutableFloatComponent(out);
    float* RGB1 = cmlNextMutableFloatComponent(out);
    float* RGB2 = cmlNextMutableFloatComponent(out);

    cml_OneXYZToRGB(RGB0, RGB1, RGB2, XYZ0, XYZ1, XYZ2, XYZToRGBmatrix, LineartoRResponse, LineartoGResponse, LineartoBResponse);

    count--;
  }
}




CML_HIDDEN void cml_XYZToRGB_SB (CMLInputOutput buf, CMLSize count){
  MOB* responsecurves = (CMLMOBResponseCurve*)cmlGetConverterSetting(CML_SETTING_CHANNEL_RESPONSE_CURVES, CML_GET_ADD);
  MOB* observerMOB = cmlGetConverterSetting(CML_SETTING_OBSERVER, CML_GET_SUB);
  MOB* generatorMOB = cmlGetConverterSetting(CML_SETTING_GENERATOR, CML_GET_ADD);
  MOB* XYZToRGBmatrixMOB = cmlGetConverterSetting(CML_SETTING_OBS_TO_GEN_MATRIX, CML_GET_CONVERT);
  CML_UNUSED(observerMOB);
  CML_UNUSED(generatorMOB);
  if(cmlGetConverterError()){return;}

  CMLMOBFunction* LineartoRResponse = cmlGetResponseCurveForwardFunc(mobGetArrayObject(responsecurves, 0));
  CMLMOBFunction* LineartoGResponse = cmlGetResponseCurveForwardFunc(mobGetArrayObject(responsecurves, 1));
  CMLMOBFunction* LineartoBResponse = cmlGetResponseCurveForwardFunc(mobGetArrayObject(responsecurves, 2));
  const float* XYZToRGBmatrix = mobConstArrayData(XYZToRGBmatrixMOB);

  while(count){
    float* buf0 = cmlNextMutableFloatComponent(buf);
    float* buf1 = cmlNextMutableFloatComponent(buf);
    float* buf2 = cmlNextMutableFloatComponent(buf);

    cml_OneXYZToRGB_SB(buf0, buf1, buf2, XYZToRGBmatrix, LineartoRResponse, LineartoGResponse, LineartoBResponse);

    count--;
  }
}



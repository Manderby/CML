
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

#include "CML.h"
#include "CMLInternal.h"


#define CMLINTERNALYupvpToLuv(Luv0, Luv1, Luv2, Yupvp0, Yupvp1, Yupvp2, invmetricScale, whiteYupvp, LineartoLResponse) \
  float yr = *Yupvp0 * invmetricScale;\
  float fy = cml_Eval(LineartoLResponse, yr);\
  *Luv0 = 100.f * fy;\
  *Luv1 = 13.f * *Luv0 * (*Yupvp1 - whiteYupvp[1]);\
  *Luv2 = 13.f * *Luv0 * (*Yupvp2 - whiteYupvp[2]);



CML_HIDDEN CML_INLINE void cml_OneYupvpToLuv (float* CML_RESTRICT Luv0, float* CML_RESTRICT Luv1, float* CML_RESTRICT Luv2, const float* CML_RESTRICT Yupvp0, const float* CML_RESTRICT Yupvp1, const float* CML_RESTRICT Yupvp2, float invmetricScale, const float* CML_RESTRICT whiteYupvp, CMLMOBFunction* LineartoLResponse){
  CMLINTERNALYupvpToLuv(Luv0, Luv1, Luv2, Yupvp0, Yupvp1, Yupvp2, invmetricScale, whiteYupvp, LineartoLResponse);
}

CML_HIDDEN CML_INLINE void cml_OneYupvpToLuv_SB(float* CML_RESTRICT buf0, float* CML_RESTRICT buf1, float* CML_RESTRICT buf2, float invmetricScale, const float* CML_RESTRICT whiteYupvp, CMLMOBFunction* LineartoLResponse){
  CMLINTERNALYupvpToLuv(buf0, buf1, buf2, buf0, buf1, buf2, invmetricScale, whiteYupvp, LineartoLResponse);
}



CML_HIDDEN void cml_YupvpToLuv (CMLOutput out , CMLInput in, CMLSize count){
  MOB* responsecurves = cmlGetConverterSetting(CML_SETTING_CHANNEL_RESPONSE_CURVES, CML_GET_ADD);
  CMLMOBObserver* observer = cmlGetConverterSetting(CML_SETTING_OBSERVER, CML_GET_EQU);
  if(cmlGetConverterError()){return;}

  CMLMOBFunction* forwardresponse = cmlGetResponseCurveForwardFunc(mobGetArrayObject(responsecurves, 1));
  const float* whiteYupvp = cmlGetObserverAdaptationWhiteYupvpRadiometric(observer);
  float metricScale = cmlGetObserverMetricScale(observer);
  float invmetricScale;
  if(metricScale != 0.f){
    invmetricScale = cmlInverse(metricScale);
  }else{
    invmetricScale = cmlInverse(whiteYupvp[0]);
  }

  while(count){
    const float* Yupvp0 = cmlNextConstFloatComponent(in);
    const float* Yupvp1 = cmlNextConstFloatComponent(in);
    const float* Yupvp2 = cmlNextConstFloatComponent(in);
    float* Luv0 = cmlNextMutableFloatComponent(out);
    float* Luv1 = cmlNextMutableFloatComponent(out);
    float* Luv2 = cmlNextMutableFloatComponent(out);

    cml_OneYupvpToLuv(Luv0, Luv1, Luv2, Yupvp0, Yupvp1, Yupvp2, invmetricScale, whiteYupvp, forwardresponse);

    count--;
  }
  
}

CML_HIDDEN void cml_YupvpToLuv_SB(CMLInputOutput buf, CMLSize count){
  MOB* responsecurves = cmlGetConverterSetting(CML_SETTING_CHANNEL_RESPONSE_CURVES, CML_GET_ADD);
  CMLMOBObserver* observer = cmlGetConverterSetting(CML_SETTING_OBSERVER, CML_GET_EQU);
  if(cmlGetConverterError()){return;}

  CMLMOBFunction* forwardresponse = cmlGetResponseCurveForwardFunc(mobGetArrayObject(responsecurves, 1));
  const float* whiteYupvp = cmlGetObserverAdaptationWhiteYupvpRadiometric(observer);
  float metricScale = cmlGetObserverMetricScale(observer);
  float invmetricScale;
  if(metricScale != 0.f){
    invmetricScale = cmlInverse(metricScale);
  }else{
    invmetricScale = cmlInverse(whiteYupvp[0]);
  }


  while(count){
    float* buf0 = cmlNextMutableFloatComponent(buf);
    float* buf1 = cmlNextMutableFloatComponent(buf);
    float* buf2 = cmlNextMutableFloatComponent(buf);

    cml_OneYupvpToLuv_SB(buf0, buf1, buf2, invmetricScale, whiteYupvp, forwardresponse);

    count--;
  }
  
}


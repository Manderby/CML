
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

#include "../CML.h"
#include "../StateMachine/CMLInternal.h"


#define CMLINTERNALLuvToYupvp(Yupvp0, Yupvp1, Yupvp2, Luv0, Luv1, Luv2, metricScale, whiteYupvp, LtoLinearResponse) \
  float divisor;\
  float yr;\
  yr = cml_Eval(LtoLinearResponse, *Luv0 * .01f);\
  divisor = 13.f * *Luv0;\
  *Yupvp0 = yr * metricScale;\
  if(divisor == 0.f){\
    *Yupvp1 = whiteYupvp[1];\
    *Yupvp2 = whiteYupvp[2];\
  }else{\
    float factor = cmlInverse(divisor);\
    *Yupvp1 = (*Luv1 * factor) + whiteYupvp[1];\
    *Yupvp2 = (*Luv2 * factor) + whiteYupvp[2];\
  }



CML_HIDDEN CML_INLINE void cml_OneLuvToYupvp (float* CML_RESTRICT Yupvp0, float* CML_RESTRICT Yupvp1, float* CML_RESTRICT Yupvp2, const float* CML_RESTRICT Luv0, const float* CML_RESTRICT Luv1, const float* CML_RESTRICT Luv2, float metricScale, const float* CML_RESTRICT whiteYupvp, CMLMOBFunction* LtoLinearResponse){
  CMLINTERNALLuvToYupvp(Yupvp0, Yupvp1, Yupvp2, Luv0, Luv1, Luv2, metricScale, whiteYupvp, LtoLinearResponse);
}

CML_HIDDEN CML_INLINE void cml_OneLuvToYupvp_SB(float* CML_RESTRICT buf0, float* CML_RESTRICT buf1, float* CML_RESTRICT buf2, float metricScale, const float* CML_RESTRICT whiteYupvp, CMLMOBFunction* LtoLinearResponse){
  CMLINTERNALLuvToYupvp(buf0, buf1, buf2, buf0, buf1, buf2, metricScale, whiteYupvp, LtoLinearResponse);
}




CML_HIDDEN void cml_LuvToYupvp (CMLOutput out , CMLInput in, CMLSize count){
  MOB* responsecurves = (CMLMOBFunctionVector*)cmlGetConverterSetting(CML_SETTING_CHANNEL_RESPONSE_CURVES, CML_GET_SUB);
  CMLMOBObserver* observer = cmlGetConverterSetting(CML_SETTING_OBSERVER, CML_GET_EQU);
  if(cmlGetConverterError()){return;}

  float metricScale = cmlGetObserverMetricScale(observer);
  CMLMOBFunction* backwardresponse = cmlGetResponseCurveBackwardFunc(mobGetArrayObject(responsecurves, 1));
  const float* whiteYupvp = cmlGetObserverAdaptationWhiteYupvpRadiometric(observer);

  if(!metricScale){
    // Adjust locally
    metricScale = whiteYupvp[0];
  }

  while(count){
    const float* Luv0 = cmlNextConstFloatComponent(in);
    const float* Luv1 = cmlNextConstFloatComponent(in);
    const float* Luv2 = cmlNextConstFloatComponent(in);
    float* Yupvp0 = cmlNextMutableFloatComponent(out);
    float* Yupvp1 = cmlNextMutableFloatComponent(out);
    float* Yupvp2 = cmlNextMutableFloatComponent(out);

    cml_OneLuvToYupvp(Yupvp0, Yupvp1, Yupvp2, Luv0, Luv1, Luv2, metricScale, whiteYupvp, backwardresponse);

    count--;
  }

}



CML_HIDDEN void cml_LuvToYupvp_SB(CMLInputOutput buf, CMLSize count){
  MOB* responsecurves = (CMLMOBFunctionVector*)cmlGetConverterSetting(CML_SETTING_CHANNEL_RESPONSE_CURVES, CML_GET_SUB);
  CMLMOBObserver* observer = cmlGetConverterSetting(CML_SETTING_OBSERVER, CML_GET_EQU);
  if(cmlGetConverterError()){return;}

  float metricScale = cmlGetObserverMetricScale(observer);
  CMLMOBFunction* backwardresponse = cmlGetResponseCurveBackwardFunc(mobGetArrayObject(responsecurves, 1));
  const float* whiteYupvp = cmlGetObserverAdaptationWhiteYupvpRadiometric(observer);

  while(count){
    float* buf0 = cmlNextMutableFloatComponent(buf);
    float* buf1 = cmlNextMutableFloatComponent(buf);
    float* buf2 = cmlNextMutableFloatComponent(buf);

    cml_OneLuvToYupvp_SB(buf0, buf1, buf2, metricScale, whiteYupvp, backwardresponse);

    count--;
  }

}






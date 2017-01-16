
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

#include "CML.h"
#include "StateMachine/CMLInternal.h"



CML_API CMLMOBResponseCurve* cmlCreateResponseCurveWithPreset(CMLResponseCurvePreset preset){
  MOB* curve = mobCreateObject(cml_Key(CML_RESPONSE_CURVE_OBJECT));

  switch(preset){
  case CML_RESPONSE_LINEAR:
    *(CML_KeyID*)mobKeyEnum(curve, cml_Key(CML_RESPONSE_CURVE_TYPE)) = CML_FUNCTION_LINEAR;
    mobSetKeyObject(curve, cml_Key(CML_RESPONSE_CURVE_FORWARD_FUNCTION), cmlCreateLinearResponse(), MOB_FALSE);
    mobSetKeyObject(curve, cml_Key(CML_RESPONSE_CURVE_BACKWARD_FUNCTION), cmlCreateLinearResponse(), MOB_FALSE);
    break;
  case CML_RESPONSE_SQRT:
    *(CML_KeyID*)mobKeyEnum(curve, cml_Key(CML_RESPONSE_CURVE_TYPE)) = CML_FUNCTION_SQRT;
    mobSetKeyObject(curve, cml_Key(CML_RESPONSE_CURVE_FORWARD_FUNCTION), cmlCreateGammaResponse(.5f), MOB_FALSE);
    mobSetKeyObject(curve, cml_Key(CML_RESPONSE_CURVE_BACKWARD_FUNCTION), cmlCreateGammaResponse(2.f), MOB_FALSE);
    break;
  case CML_RESPONSE_GAMMA_ADOBE_98:
    *(CML_KeyID*)mobKeyEnum(curve, cml_Key(CML_RESPONSE_CURVE_TYPE)) = CML_FUNCTION_GAMMA;
    mobSetKeyObject(curve, cml_Key(CML_RESPONSE_CURVE_FORWARD_FUNCTION), cmlCreateGammaResponse(cmlInverse(2.f + 51.f / 256.f)), MOB_FALSE);
    mobSetKeyObject(curve, cml_Key(CML_RESPONSE_CURVE_BACKWARD_FUNCTION), cmlCreateGammaResponse(2.f + 51.f / 256.f), MOB_FALSE);
    break;
  case CML_RESPONSE_GAMMA_1_8:
    *(CML_KeyID*)mobKeyEnum(curve, cml_Key(CML_RESPONSE_CURVE_TYPE)) = CML_FUNCTION_GAMMA;
    mobSetKeyObject(curve, cml_Key(CML_RESPONSE_CURVE_FORWARD_FUNCTION), cmlCreateGammaResponse(cmlInverse(1.8f)), MOB_FALSE);
    mobSetKeyObject(curve, cml_Key(CML_RESPONSE_CURVE_BACKWARD_FUNCTION), cmlCreateGammaResponse(1.8f), MOB_FALSE);
    break;
  case CML_RESPONSE_GAMMA_1_9:
    *(CML_KeyID*)mobKeyEnum(curve, cml_Key(CML_RESPONSE_CURVE_TYPE)) = CML_FUNCTION_GAMMA;
    mobSetKeyObject(curve, cml_Key(CML_RESPONSE_CURVE_FORWARD_FUNCTION), cmlCreateGammaResponse(cmlInverse(1.9f)), MOB_FALSE);
    mobSetKeyObject(curve, cml_Key(CML_RESPONSE_CURVE_BACKWARD_FUNCTION), cmlCreateGammaResponse(1.9f), MOB_FALSE);
    break;
  case CML_RESPONSE_GAMMA_2_2:
    *(CML_KeyID*)mobKeyEnum(curve, cml_Key(CML_RESPONSE_CURVE_TYPE)) = CML_FUNCTION_GAMMA;
    mobSetKeyObject(curve, cml_Key(CML_RESPONSE_CURVE_FORWARD_FUNCTION), cmlCreateGammaResponse(cmlInverse(2.2f)), MOB_FALSE);
    mobSetKeyObject(curve, cml_Key(CML_RESPONSE_CURVE_BACKWARD_FUNCTION), cmlCreateGammaResponse(2.2f), MOB_FALSE);
    break;
  case CML_RESPONSE_GAMMA_LINEAR_REC_BT_10BIT:
    *(CML_KeyID*)mobKeyEnum(curve, cml_Key(CML_RESPONSE_CURVE_TYPE)) = CML_FUNCTION_GAMMA_LINEAR;
    mobSetKeyObject(curve, cml_Key(CML_RESPONSE_CURVE_FORWARD_FUNCTION), cmlCreateGammaLinearResponse(1.f / 0.45f, 0.099f, 4.5f, 0.018f), MOB_FALSE);
    mobSetKeyObject(curve, cml_Key(CML_RESPONSE_CURVE_BACKWARD_FUNCTION), cmlCreateInverseGammaLinearResponse(1.f / 0.45f, 0.099f, 4.5f, 0.018f), MOB_FALSE);
    break;
  case CML_RESPONSE_GAMMA_LINEAR_REC_BT_12BIT:
    *(CML_KeyID*)mobKeyEnum(curve, cml_Key(CML_RESPONSE_CURVE_TYPE)) = CML_FUNCTION_GAMMA_LINEAR;
    mobSetKeyObject(curve, cml_Key(CML_RESPONSE_CURVE_FORWARD_FUNCTION), cmlCreateGammaLinearResponse(1.f / 0.45f, 0.0993f, 4.5f, 0.0181f), MOB_FALSE);
    mobSetKeyObject(curve, cml_Key(CML_RESPONSE_CURVE_BACKWARD_FUNCTION), cmlCreateInverseGammaLinearResponse(1.f / 0.45f, 0.0993f, 4.5f, 0.0181f), MOB_FALSE);
    break;
  case CML_RESPONSE_SRGB:
    *(CML_KeyID*)mobKeyEnum(curve, cml_Key(CML_RESPONSE_CURVE_TYPE)) = CML_FUNCTION_SRGB;
    mobSetKeyObject(curve, cml_Key(CML_RESPONSE_CURVE_FORWARD_FUNCTION), cmlCreateXYZTosRGBResponse(), MOB_FALSE);
    mobSetKeyObject(curve, cml_Key(CML_RESPONSE_CURVE_BACKWARD_FUNCTION), cmlCreatesRGBToXYZResponse(), MOB_FALSE);
    break;
  case CML_RESPONSE_LSTAR:
    *(CML_KeyID*)mobKeyEnum(curve, cml_Key(CML_RESPONSE_CURVE_TYPE)) = CML_FUNCTION_LSTAR;
    mobSetKeyObject(curve, cml_Key(CML_RESPONSE_CURVE_FORWARD_FUNCTION), cmlCreateYToLStarResponse(), MOB_FALSE);
    mobSetKeyObject(curve, cml_Key(CML_RESPONSE_CURVE_BACKWARD_FUNCTION), cmlCreateLStarToYResponse(), MOB_FALSE);
    break;
  case CML_RESPONSE_LSTAR_STANDARD:
    *(CML_KeyID*)mobKeyEnum(curve, cml_Key(CML_RESPONSE_CURVE_TYPE)) = CML_FUNCTION_LSTAR_STANDARD;
    mobSetKeyObject(curve, cml_Key(CML_RESPONSE_CURVE_FORWARD_FUNCTION), cmlCreateYToLStarStandardResponse(), MOB_FALSE);
    mobSetKeyObject(curve, cml_Key(CML_RESPONSE_CURVE_BACKWARD_FUNCTION), cmlCreateLStarToYStandardResponse(), MOB_FALSE);
    break;
  default:
    #ifndef NDEBUG
     *(CML_KeyID*)mobKeyEnum(curve, cml_Key(CML_RESPONSE_CURVE_TYPE)) = CML_FUNCTION_LINEAR;
      mobSetKeyObject(curve, cml_Key(CML_RESPONSE_CURVE_FORWARD_FUNCTION), cmlCreateLinearResponse(), MOB_FALSE);
      mobSetKeyObject(curve, cml_Key(CML_RESPONSE_CURVE_BACKWARD_FUNCTION), cmlCreateLinearResponse(), MOB_FALSE);
      cmlError("cmlCreateResponseCurveWithPreset", "Response preset unknown.");
    #endif
    break;
  }

  return (CMLMOBResponseCurve*)curve;
}



CML_API CMLMOBResponseCurve* cmlCreateResponseCurveGammaLinear(
                                                     float gamma,
                                                     float offset,
                                                     float linscale,
                                                     float split){
  CMLMOBResponseCurve* curve = (CMLMOBResponseCurve*)mobCreateObject(cml_Key(CML_RESPONSE_CURVE_OBJECT));

  *(CML_KeyID*)mobKeyEnum(curve, cml_Key(CML_RESPONSE_CURVE_TYPE)) = CML_FUNCTION_GAMMA_LINEAR;
  mobSetKeyObject(curve, cml_Key(CML_RESPONSE_CURVE_FORWARD_FUNCTION), cmlCreateGammaLinearResponse(gamma, offset, linscale, split), MOB_FALSE);
  mobSetKeyObject(curve, cml_Key(CML_RESPONSE_CURVE_BACKWARD_FUNCTION), cmlCreateInverseGammaLinearResponse(gamma, offset, linscale, split), MOB_FALSE);

  return (CMLMOBResponseCurve*)curve;
}



CML_API CMLMOBFunction* cmlGetResponseCurveForwardFunc(CMLMOBResponseCurve* curve){
  return (CMLMOBFunction*)mobGetKeyObject(curve, cml_Key(CML_RESPONSE_CURVE_FORWARD_FUNCTION));
}
CML_API CMLMOBFunction* cmlGetResponseCurveBackwardFunc(CMLMOBResponseCurve* curve){
  return (CMLMOBFunction*)mobGetKeyObject(curve, cml_Key(CML_RESPONSE_CURVE_BACKWARD_FUNCTION));
}
CML_API CMLFunctionType cmlGetResponseCurveFunctionType(CMLMOBResponseCurve* curve){
  return *(CMLFunctionType*)mobKeyEnum(curve, cml_Key(CML_RESPONSE_CURVE_TYPE));
}


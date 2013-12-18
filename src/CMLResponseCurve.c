
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

#include "CML.h"
#include "StateMachine/CMLInternal.h"


CMLAPI void cmlDestroyResponseCurve(void* curve);



CMLAPI CMLResponseCurve* cmlCreateResponseCurveWithPreset(
                                   CMLResponseCurvePreset preset){
  CMLResponseCurve* curve = cmlCreateObject(sizeof(CMLResponseCurve), cmlDestroyResponseCurve);

  switch(preset){
  case CML_RESPONSE_LINEAR:
    curve->forwardfunc  = cmlCreateLinearResponse();
    curve->backwardfunc = cmlCreateLinearResponse();
    curve->functiontype = CML_FUNCTION_LINEAR;
    break;
  case CML_RESPONSE_SQRT:
    curve->forwardfunc  = cmlCreateGammaResponse(.5f); // todo: create functions
    curve->backwardfunc = cmlCreateGammaResponse(2.f); // for that.
    curve->functiontype = CML_FUNCTION_SQRT;
    break;
  case CML_RESPONSE_GAMMA_ADOBE_98:
    curve->forwardfunc  = cmlCreateGammaResponse(cmlInverse(2.f + 51.f / 256.f));
    curve->backwardfunc = cmlCreateGammaResponse(2.f + 51.f / 256.f);
    curve->functiontype = CML_FUNCTION_GAMMA;
    break;
  case CML_RESPONSE_GAMMA_1_8:
    curve->forwardfunc  = cmlCreateGammaResponse(cmlInverse(1.8f));
    curve->backwardfunc = cmlCreateGammaResponse(1.8f);
    curve->functiontype = CML_FUNCTION_GAMMA;
    break;
  case CML_RESPONSE_GAMMA_1_9:
    curve->forwardfunc  = cmlCreateGammaResponse(cmlInverse(1.9f));
    curve->backwardfunc = cmlCreateGammaResponse(1.9f);
    curve->functiontype = CML_FUNCTION_GAMMA;
    break;
  case CML_RESPONSE_GAMMA_2_2:
    curve->forwardfunc  = cmlCreateGammaResponse(cmlInverse(2.2f));
    curve->backwardfunc = cmlCreateGammaResponse(2.2f);
    curve->functiontype = CML_FUNCTION_GAMMA;
    break;
  case CML_RESPONSE_GAMMA_LINEAR_REC_BT_10BIT:
    curve->forwardfunc  = cmlCreateGammaLinearResponse(1.f / 0.45f, 0.099f, 4.5f, 0.018f);
    curve->backwardfunc = cmlCreateInverseGammaLinearResponse(1.f / 0.45f, 0.099f, 4.5f, 0.018f);
    curve->functiontype = CML_FUNCTION_GAMMA_LINEAR;
    break;
  case CML_RESPONSE_GAMMA_LINEAR_REC_BT_12BIT:
    curve->forwardfunc  = cmlCreateGammaLinearResponse(1.f / 0.45f, 0.0993f, 4.5f, 0.0181f);
    curve->backwardfunc = cmlCreateInverseGammaLinearResponse(1.f / 0.45f, 0.0993f, 4.5f, 0.0181f);
    curve->functiontype = CML_FUNCTION_GAMMA_LINEAR;
    break;
  case CML_RESPONSE_SRGB:
    curve->forwardfunc  = cmlCreateXYZTosRGBResponse();
    curve->backwardfunc = cmlCreatesRGBToXYZResponse();
    curve->functiontype = CML_FUNCTION_SRGB;
    break;
  case CML_RESPONSE_LSTAR:
    curve->forwardfunc  = cmlCreateYToLStarResponse();
    curve->backwardfunc = cmlCreateLStarToYResponse();
    curve->functiontype = CML_FUNCTION_LSTAR;
    break;
  case CML_RESPONSE_LSTAR_STANDARD:
    curve->forwardfunc  = cmlCreateYToLStarStandardResponse();
    curve->backwardfunc = cmlCreateLStarToYStandardResponse();
    curve->functiontype = CML_FUNCTION_LSTAR_STANDARD;
    break;
  default:
    #ifndef NDEBUG
      curve->forwardfunc  = cmlCreateLinearResponse();
      curve->backwardfunc = cmlCreateLinearResponse();
      cmlError("cmlCreateResponseCurveWithPreset", "Response preset unknown.");
    #endif
    break;
  }

  return curve;
}



CMLAPI CMLResponseCurve* cmlCreateResponseCurveWith4ParamsFunction(
                                                     float param0,
                                                     float param1,
                                                     float param2,
                                                     float param3){
  CMLResponseCurve* curve = cmlCreateObject(sizeof(CMLResponseCurve), cmlDestroyResponseCurve);

  curve->functiontype = CML_FUNCTION_GAMMA_LINEAR;
  curve->forwardfunc  = cmlCreateGammaLinearResponse(param0, param1, param2, param3);
  curve->backwardfunc = cmlCreateInverseGammaLinearResponse(param0, param1, param2, param3);
  return curve;
}



CMLAPI void cmlDestroyResponseCurve(void* curve){
  CMLResponseCurve* responsecurve = (CMLResponseCurve*)curve;
  cmlReleaseObject(responsecurve->backwardfunc);
  cmlReleaseObject(responsecurve->forwardfunc);
}



CMLAPI CMLFunction* cmlGetResponseCurveForwardFunc(const CMLResponseCurve* curve){
  return curve->backwardfunc;
}
CMLAPI CMLFunction* cmlGetResponseCurveBackwardFunc(const CMLResponseCurve* curve){
  return curve->forwardfunc;
}
//CMLAPI CMLFunctionType cmlGetResponseCurveForwardFunctionType(const CMLResponseCurve* curve){
//  return curve->type;
//}
CMLAPI float cmlGetResponseCurveParam0(const CMLResponseCurve* curve){
  switch(curve->functiontype){
  case CML_FUNCTION_LINEAR: return 1.0f; break;
  case CML_FUNCTION_SQRT: return 2.0f; break;
  case CML_FUNCTION_GAMMA: return cmlGetFunctionParameter(curve->backwardfunc, 0); break;
  case CML_FUNCTION_GAMMA_LINEAR: return cmlGetFunctionParameter(curve->backwardfunc, 0); break;
  case CML_FUNCTION_SRGB: return 2.4f; break;
  case CML_FUNCTION_LSTAR: return 3.0f; break;
  case CML_FUNCTION_LSTAR_STANDARD: return 3.0f; break;
  default:
    #ifndef NDEBUG
      cmlError("cmlGetResponseCurveParam0", "Function type unknown.");
    #endif
    return 1.0f;
    break;
  }
}
CMLAPI float cmlGetResponseCurveParam1(const CMLResponseCurve* curve){
  switch(curve->functiontype){
  case CML_FUNCTION_LINEAR: return 0.0f; break;
  case CML_FUNCTION_SQRT: return 0.0f; break;
  case CML_FUNCTION_GAMMA: return 0.0f; break;
  case CML_FUNCTION_GAMMA_LINEAR: return cmlGetFunctionParameter(curve->backwardfunc, 1); break;
  case CML_FUNCTION_SRGB: return 0.055f; break;
  case CML_FUNCTION_LSTAR: return 0.16f; break;
  case CML_FUNCTION_LSTAR_STANDARD: return 0.16f; break;
  default:
    #ifndef NDEBUG
      cmlError("cmlGetResponseCurveParam1", "Function type unknown.");
    #endif
    return 0.0f;
    break;
  }
}
CMLAPI float cmlGetResponseCurveParam2(const CMLResponseCurve* curve){
  switch(curve->functiontype){
  case CML_FUNCTION_LINEAR: return 1.0f; break;
  case CML_FUNCTION_SQRT: return 1.0f; break;
  case CML_FUNCTION_GAMMA: return 1.0f; break;
  case CML_FUNCTION_GAMMA_LINEAR: return cmlGetFunctionParameter(curve->backwardfunc, 2); break;
  case CML_FUNCTION_SRGB: return 12.92f; break;
  case CML_FUNCTION_LSTAR: return 9.03296296296296296f; break;
  case CML_FUNCTION_LSTAR_STANDARD: return 9.033f; break;
  default:
    #ifndef NDEBUG
      cmlError("cmlGetResponseCurveParam2", "Function type unknown.");
    #endif
    return 1.0f;
    break;
  }
}
CMLAPI float cmlGetResponseCurveParam3(const CMLResponseCurve* curve){
  switch(curve->functiontype){
  case CML_FUNCTION_LINEAR: return 1.0f; break;
  case CML_FUNCTION_SQRT: return 0.0f; break;
  case CML_FUNCTION_GAMMA: return 0.0f; break;
  case CML_FUNCTION_GAMMA_LINEAR: return cmlGetFunctionParameter(curve->backwardfunc, 3); break;
  case CML_FUNCTION_SRGB: return 0.0031306684425f; break;
  case CML_FUNCTION_LSTAR: return 0.008856451679036f; break;
  case CML_FUNCTION_LSTAR_STANDARD: return 0.008856f; break;
  default:
    #ifndef NDEBUG
      cmlError("cmlGetResponseCurveParam3", "Function type unknown.");
    #endif
    return 0.0f;
    break;
  }
}


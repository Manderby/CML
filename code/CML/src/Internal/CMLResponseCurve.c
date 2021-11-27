
#include "CML.h"
#include "CMLInternal.h"


CML_HIDDEN CMLResponseCurve* cmlCreateResponseCurve(CMLResponseCurve* curve){
  if(!curve){curve = (CMLResponseCurve*)cmlAllocate(sizeof(CMLResponseCurve));}
  curve->forwardfunc = NULL;
  curve->backwardfunc = NULL;
  return curve;
}


CML_API CMLResponseCurve* cmlCreateResponseCurveCopy(CMLResponseCurve* dstcurve, CMLResponseCurve* srccurve){
  if(!dstcurve){dstcurve = (CMLResponseCurve*)cmlAllocate(sizeof(CMLResponseCurve));}
  dstcurve->forwardfunc = cmlDuplicateFunction(srccurve->forwardfunc);
  dstcurve->backwardfunc = cmlDuplicateFunction(srccurve->backwardfunc);
  dstcurve->functiontype = srccurve->functiontype;
  return dstcurve;
}


CML_API CMLResponseCurve* cmlCreateResponseCurveWithPreset(
                                        CMLResponseCurve* curve,
                                   CMLResponseCurvePreset preset){
  if(!curve){curve = (CMLResponseCurve*)cmlAllocate(sizeof(CMLResponseCurve));}
//  curve->type = type;
//  curve->param0 = param0;
//  curve->param1 = param1;
//  curve->param2 = param2;
//  curve->param3 = param3;

//  cmlReleaseFunction(curve->func);
//  cmlReleaseFunction(curve->invfunc);

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
    #if CML_DEBUG
      curve->forwardfunc  = cmlCreateLinearResponse();
      curve->backwardfunc = cmlCreateLinearResponse();
      cmlError("Response preset unknown.");
    #endif
    break;
  }

  return curve;
}

CML_API CMLResponseCurve* cmlCreateResponseCurveWith4ParamsFunction(
                                         CMLResponseCurve* curve,
//                                           CMLFunctionType type,
                                                     float param0,
                                                     float param1,
                                                     float param2,
                                                     float param3){
  if(!curve){curve = (CMLResponseCurve*)cmlAllocate(sizeof(CMLResponseCurve));}
  curve->functiontype = CML_FUNCTION_GAMMA_LINEAR;
  curve->forwardfunc  = cmlCreateGammaLinearResponse(param0, param1, param2, param3);
  curve->backwardfunc = cmlCreateInverseGammaLinearResponse(param0, param1, param2, param3);
  return curve;
}



CML_API void CMLclearResponseCurve(CMLResponseCurve* curve){
  cmlReleaseFunction(curve->backwardfunc);
  cmlReleaseFunction(curve->forwardfunc);
}

CML_API void CMLdestroyResponseCurve(CMLResponseCurve* curve){
  CMLclearResponseCurve(curve);
  free(curve);
}



CML_API CMLFunction* CMLgetResponseCurveFunc(const CMLResponseCurve* curve){
  return curve->backwardfunc;
}
CML_API CMLFunction* CMLgetResponseCurveInvFunc(const CMLResponseCurve* curve){
  return curve->forwardfunc;
}
//CML_API CMLFunctionType CMLgetResponseCurveFunctionType(const CMLResponseCurve* curve){
//  return curve->type;
//}
CML_API float CMLgetResponseCurveParam0(const CMLResponseCurve* curve){
  switch(curve->functiontype){
  case CML_FUNCTION_LINEAR: return 1.0f; break;
  case CML_FUNCTION_SQRT: return 2.0f; break;
  case CML_FUNCTION_GAMMA: return cmlGetFunctionParameter(curve->backwardfunc, 0); break;
  case CML_FUNCTION_GAMMA_LINEAR: return cmlGetFunctionParameter(curve->backwardfunc, 0); break;
  case CML_FUNCTION_SRGB: return 2.4f; break;
  case CML_FUNCTION_LSTAR: return 3.0f; break;
  case CML_FUNCTION_LSTAR_STANDARD: return 3.0f; break;
  default:
    #if CML_DEBUG
      cmlError("Function type unknown.");
    #endif
    return 1.0f;
    break;
  }
}
CML_API float CMLgetResponseCurveParam1(const CMLResponseCurve* curve){
  switch(curve->functiontype){
  case CML_FUNCTION_LINEAR: return 0.0f; break;
  case CML_FUNCTION_SQRT: return 0.0f; break;
  case CML_FUNCTION_GAMMA: return 0.0f; break;
  case CML_FUNCTION_GAMMA_LINEAR: return cmlGetFunctionParameter(curve->backwardfunc, 1); break;
  case CML_FUNCTION_SRGB: return 0.055f; break;
  case CML_FUNCTION_LSTAR: return 0.16f; break;
  case CML_FUNCTION_LSTAR_STANDARD: return 0.16f; break;
  default:
    #if CML_DEBUG
      cmlError("Function type unknown.");
    #endif
    return 0.0f;
    break;
  }
}
CML_API float CMLgetResponseCurveParam2(const CMLResponseCurve* curve){
  switch(curve->functiontype){
  case CML_FUNCTION_LINEAR: return 1.0f; break;
  case CML_FUNCTION_SQRT: return 1.0f; break;
  case CML_FUNCTION_GAMMA: return 1.0f; break;
  case CML_FUNCTION_GAMMA_LINEAR: return cmlGetFunctionParameter(curve->backwardfunc, 2); break;
  case CML_FUNCTION_SRGB: return 12.92f; break;
  case CML_FUNCTION_LSTAR: return 9.03296296296296296f; break;
  case CML_FUNCTION_LSTAR_STANDARD: return 9.033f; break;
  default:
    #if CML_DEBUG
      cmlError("Function type unknown.");
    #endif
    return 1.0f;
    break;
  }
}
CML_API float CMLgetResponseCurveParam3(const CMLResponseCurve* curve){
  switch(curve->functiontype){
  case CML_FUNCTION_LINEAR: return 1.0f; break;
  case CML_FUNCTION_SQRT: return 0.0f; break;
  case CML_FUNCTION_GAMMA: return 0.0f; break;
  case CML_FUNCTION_GAMMA_LINEAR: return cmlGetFunctionParameter(curve->backwardfunc, 3); break;
  case CML_FUNCTION_SRGB: return 0.0031306684425f; break;
  case CML_FUNCTION_LSTAR: return 0.008856451679036f; break;
  case CML_FUNCTION_LSTAR_STANDARD: return 0.008856f; break;
  default:
    #if CML_DEBUG
      cmlError("Function type unknown.");
    #endif
    return 0.0f;
    break;
  }
}



// This is free and unencumbered software released into the public domain.

// Anyone is free to copy, modify, publish, use, compile, sell, or
// distribute this software, either in source code form or as a compiled
// binary, for any purpose, commercial or non-commercial, and by any
// means.

// In jurisdictions that recognize copyright laws, the author or authors
// of this software dedicate any and all copyright interest in the
// software to the public domain. We make this dedication for the benefit
// of the public at large and to the detriment of our heirs and
// successors. We intend this dedication to be an overt act of
// relinquishment in perpetuity of all present and future rights to this
// software under copyright law.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
// OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.

// For more information, please refer to <http://unlicense.org/>

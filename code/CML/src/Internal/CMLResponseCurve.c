
#include "CML.h"
#include "CMLInternal.h"


CML_DEF CMLResponseCurve* cmlAllocResponseCurve(){
  return cml_Allocate(sizeof(CMLResponseCurve));
}



CML_DEF void cmlInitResponseCurve(CMLResponseCurve* curve){
  curve->forwardFunc = NULL;
  curve->backwardFunc = NULL;
  curve->functionType = CML_FUNCTION_UNDEFINED;
}



CML_DEF void cmlInitResponseCurveWithCopy(CMLResponseCurve* dstCurve, CMLResponseCurve* srcCurve){
  dstCurve->forwardFunc = cmlDuplicateFunction(srcCurve->forwardFunc);
  dstCurve->backwardFunc = cmlDuplicateFunction(srcCurve->backwardFunc);
  dstCurve->functionType = srcCurve->functionType;
}



CML_DEF void cmlInitResponseCurveWithPreset(CMLResponseCurve* curve, CMLResponseCurvePreset preset){
  switch(preset){
  case CML_RESPONSE_LINEAR:
    curve->forwardFunc  = cmlCreateLinearResponse();
    curve->backwardFunc = cmlCreateLinearResponse();
    curve->functionType = CML_FUNCTION_LINEAR;
    break;
  case CML_RESPONSE_SQRT:
    curve->forwardFunc  = cmlCreateGammaResponse(.5f);
    curve->backwardFunc = cmlCreateGammaResponse(2.f);
    curve->functionType = CML_FUNCTION_SQRT;
    break;
  case CML_RESPONSE_GAMMA_ADOBE_98:
    curve->forwardFunc  = cmlCreateGammaResponse(cmlInverse(2.f + 51.f / 256.f));
    curve->backwardFunc = cmlCreateGammaResponse(2.f + 51.f / 256.f);
    curve->functionType = CML_FUNCTION_GAMMA;
    break;
  case CML_RESPONSE_GAMMA_1_8:
    curve->forwardFunc  = cmlCreateGammaResponse(cmlInverse(1.8f));
    curve->backwardFunc = cmlCreateGammaResponse(1.8f);
    curve->functionType = CML_FUNCTION_GAMMA;
    break;
  case CML_RESPONSE_GAMMA_1_9:
    curve->forwardFunc  = cmlCreateGammaResponse(cmlInverse(1.9f));
    curve->backwardFunc = cmlCreateGammaResponse(1.9f);
    curve->functionType = CML_FUNCTION_GAMMA;
    break;
  case CML_RESPONSE_GAMMA_2_2:
    curve->forwardFunc  = cmlCreateGammaResponse(cmlInverse(.2f));
    curve->backwardFunc = cmlCreateGammaResponse(2.2f);
    curve->functionType = CML_FUNCTION_GAMMA;
    break;
  case CML_RESPONSE_GAMMA_LINEAR_REC_BT_10BIT:
    curve->forwardFunc  = cmlCreateGammaLinearResponse(1.f / 0.45f, 0.099f, 4.5f, 0.018f);
    curve->backwardFunc = cmlCreateInverseGammaLinearResponse(1.f / 0.45f, 0.099f, 4.5f, 0.018f);
    curve->functionType = CML_FUNCTION_GAMMA_LINEAR;
    break;
  case CML_RESPONSE_GAMMA_LINEAR_REC_BT_12BIT:
    curve->forwardFunc  = cmlCreateGammaLinearResponse(1.f / 0.45f, 0.0993f, 4.5f, 0.0181f);
    curve->backwardFunc = cmlCreateInverseGammaLinearResponse(1.f / 0.45f, 0.0993f, 4.5f, 0.0181f);
    curve->functionType = CML_FUNCTION_GAMMA_LINEAR;
    break;
  case CML_RESPONSE_SRGB:
    curve->forwardFunc  = cmlCreateXYZTosRGBResponse();
    curve->backwardFunc = cmlCreatesRGBToXYZResponse();
    curve->functionType = CML_FUNCTION_SRGB;
    break;
  case CML_RESPONSE_LSTAR:
    curve->forwardFunc  = cmlCreateYToLStarResponse();
    curve->backwardFunc = cmlCreateLStarToYResponse();
    curve->functionType = CML_FUNCTION_LSTAR;
    break;
  case CML_RESPONSE_LSTAR_STANDARD:
    curve->forwardFunc  = cmlCreateYToLStarStandardResponse();
    curve->backwardFunc = cmlCreateLStarToYStandardResponse();
    curve->functionType = CML_FUNCTION_LSTAR_STANDARD;
    break;
  default:
    #if CML_DEBUG
      curve->forwardFunc  = cmlCreateLinearResponse();
      curve->backwardFunc = cmlCreateLinearResponse();
      cmlError("Response preset unknown.");
    #endif
    break;
  }
}

CML_DEF void cmlInitResponseCurveWith4ParamsFunction(
  CMLResponseCurve* curve,
  float gamma,
  float offset,
  float linScale,
  float split)
{
  curve->functionType = CML_FUNCTION_GAMMA_LINEAR;
  curve->forwardFunc  = cmlCreateGammaLinearResponse(gamma, offset, linScale, split);
  curve->backwardFunc = cmlCreateInverseGammaLinearResponse(gamma, offset, linScale, split);
}



CML_DEF void cmlClearResponseCurve(CMLResponseCurve* curve){
  cmlReleaseFunction(curve->forwardFunc);
  cmlReleaseFunction(curve->backwardFunc);
}



CML_DEF const CMLFunction* cmlGetResponseCurveFunc(const CMLResponseCurve* curve){
  return curve->forwardFunc;
}

CML_DEF const CMLFunction* cmlGetResponseCurveInvFunc(const CMLResponseCurve* curve){
  return curve->backwardFunc;
}

CML_DEF CMLFunctionType cmlGetResponseCurveFunctionType(const CMLResponseCurve* curve){
  return curve->functionType;
}



CML_DEF float cmlGetResponseCurveParam0(const CMLResponseCurve* curve){
  switch(curve->functionType){
  case CML_FUNCTION_LINEAR: return 1.0f; break;
  case CML_FUNCTION_SQRT: return 2.0f; break;
  case CML_FUNCTION_GAMMA: return cmlGetFunctionParameter(curve->backwardFunc, 0); break;
  case CML_FUNCTION_GAMMA_LINEAR: return cmlGetFunctionParameter(curve->backwardFunc, 0); break;
  case CML_FUNCTION_SRGB: return 2.4f; break;
  case CML_FUNCTION_LSTAR: return 3.0f; break;
  case CML_FUNCTION_LSTAR_STANDARD: return 3.0f; break;
  default:
    #if CML_DEBUG
      cmlError("Invalid function type.");
    #endif
    return 1.0f;
    break;
  }
}

CML_DEF float cmlGetResponseCurveParam1(const CMLResponseCurve* curve){
  switch(curve->functionType){
  case CML_FUNCTION_LINEAR: return 0.0f; break;
  case CML_FUNCTION_SQRT: return 0.0f; break;
  case CML_FUNCTION_GAMMA: return 0.0f; break;
  case CML_FUNCTION_GAMMA_LINEAR: return cmlGetFunctionParameter(curve->backwardFunc, 1); break;
  case CML_FUNCTION_SRGB: return 0.055f; break;
  case CML_FUNCTION_LSTAR: return 0.16f; break;
  case CML_FUNCTION_LSTAR_STANDARD: return 0.16f; break;
  default:
    #if CML_DEBUG
      cmlError("Invalid function type.");
    #endif
    return 0.0f;
    break;
  }
}

CML_DEF float cmlGetResponseCurveParam2(const CMLResponseCurve* curve){
  switch(curve->functionType){
  case CML_FUNCTION_LINEAR: return 1.0f; break;
  case CML_FUNCTION_SQRT: return 1.0f; break;
  case CML_FUNCTION_GAMMA: return 1.0f; break;
  case CML_FUNCTION_GAMMA_LINEAR: return cmlGetFunctionParameter(curve->backwardFunc, 2); break;
  case CML_FUNCTION_SRGB: return 12.92f; break;
  case CML_FUNCTION_LSTAR: return 9.03296296296296296f; break;
  case CML_FUNCTION_LSTAR_STANDARD: return 9.033f; break;
  default:
    #if CML_DEBUG
      cmlError("Invalid function type.");
    #endif
    return 1.0f;
    break;
  }
}

CML_DEF float cmlGetResponseCurveParam3(const CMLResponseCurve* curve){
  switch(curve->functionType){
  case CML_FUNCTION_LINEAR: return 1.0f; break;
  case CML_FUNCTION_SQRT: return 0.0f; break;
  case CML_FUNCTION_GAMMA: return 0.0f; break;
  case CML_FUNCTION_GAMMA_LINEAR: return cmlGetFunctionParameter(curve->backwardFunc, 3); break;
  case CML_FUNCTION_SRGB: return 0.0031306684425f; break;
  case CML_FUNCTION_LSTAR: return 0.008856451679036f; break;
  case CML_FUNCTION_LSTAR_STANDARD: return 0.008856f; break;
  default:
    #if CML_DEBUG
      cmlError("Invalid function type.");
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

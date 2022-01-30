
#include "../CML.h"
#include "../Internal/CMLColorMachineState.h"


CML_DEF CMLResponseCurve* cmlAllocResponseCurve(){
  return cml_Malloc(sizeof(CMLResponseCurve));
}



CML_DEF void cmlInitResponseCurve(CMLResponseCurve* curve){
  curve->forwardFunc = NULL;
  curve->backwardFunc = NULL;
  curve->responseType = CML_RESPONSE_UNDEFINED;
}



CML_DEF void cmlInitResponseCurveWithCopy(CMLResponseCurve* dstCurve, CMLResponseCurve* srcCurve){
  dstCurve->forwardFunc = cmlDuplicateFunction(srcCurve->forwardFunc);
  dstCurve->backwardFunc = cmlDuplicateFunction(srcCurve->backwardFunc);
  dstCurve->responseType = srcCurve->responseType;
}



CML_DEF void cmlInitResponseCurveWithType(CMLResponseCurve* curve, CMLResponseCurveType type){
  curve->responseType = type;
  switch(type){
  case CML_RESPONSE_LINEAR:
    curve->forwardFunc  = cmlCreateLinearResponse();
    curve->backwardFunc = cmlCreateLinearResponse();
    break;
  case CML_RESPONSE_GAMMA_1_8:
    curve->forwardFunc  = cmlCreateGammaResponse(1.8f);
    curve->backwardFunc = cmlCreateInverseGammaResponse(1.8f);
    break;
  case CML_RESPONSE_GAMMA_1_9:
    curve->forwardFunc  = cmlCreateGammaResponse(1.9f);
    curve->backwardFunc = cmlCreateInverseGammaResponse(1.9f);
    break;
  case CML_RESPONSE_GAMMA_2_0:
    curve->forwardFunc  = cmlCreateGammaResponse(2.f);
    curve->backwardFunc = cmlCreateInverseGammaResponse(2.f);
    break;
  case CML_RESPONSE_GAMMA_ADOBE_98:
    curve->forwardFunc  = cmlCreateGammaResponse(2.f + 51.f / 256.f);
    curve->backwardFunc = cmlCreateInverseGammaResponse(2.f + 51.f / 256.f);
    break;
  case CML_RESPONSE_GAMMA_2_2:
    curve->forwardFunc  = cmlCreateGammaResponse(2.2f);
    curve->backwardFunc = cmlCreateInverseGammaResponse(2.2f);
    break;
  case CML_RESPONSE_GAMMA_LINEAR_REC_BT_10BIT:
    curve->forwardFunc  = cmlCreateGammaLinearResponse(1.f / 0.45f, 0.099f, 4.5f, 0.018f);
    curve->backwardFunc = cmlCreateInverseGammaLinearResponse(1.f / 0.45f, 0.099f, 4.5f, 0.018f);
    break;
  case CML_RESPONSE_GAMMA_LINEAR_REC_BT_12BIT:
    curve->forwardFunc  = cmlCreateGammaLinearResponse(1.f / 0.45f, 0.0993f, 4.5f, 0.0181f);
    curve->backwardFunc = cmlCreateInverseGammaLinearResponse(1.f / 0.45f, 0.0993f, 4.5f, 0.0181f);
    break;
  case CML_RESPONSE_SRGB:
    curve->forwardFunc  = cmlCreateXYZTosRGBResponse();
    curve->backwardFunc = cmlCreatesRGBToXYZResponse();
    break;
  case CML_RESPONSE_LSTAR:
    curve->forwardFunc  = cmlCreateYToLStarResponse();
    curve->backwardFunc = cmlCreateLStarToYResponse();
    break;
  case CML_RESPONSE_LSTAR_STANDARD:
    curve->forwardFunc  = cmlCreateYToLStarStandardResponse();
    curve->backwardFunc = cmlCreateLStarToYStandardResponse();
    break;
  case CML_RESPONSE_CUSTOM_GAMMA:
    #if CML_DEBUG
      cmlError("Use cmlInitResponseCurveWithCustomGamma to initialize a resopnse curve with custom gamma.");
    #endif
    break;
  case CML_RESPONSE_CUSTOM_GAMMA_LINEAR:
    #if CML_DEBUG
      cmlError("Use cmlInitResponseCurveWithCustomGammaLinear to initialize a resopnse curve with custom gamma + linear.");
    #endif
    break;
  default:
    #if CML_DEBUG
      curve->forwardFunc  = cmlCreateLinearResponse();
      curve->backwardFunc = cmlCreateLinearResponse();
      cmlError("Response curve invalid.");
    #endif
    break;
  }
}

CML_DEF void cmlInitResponseCurveWithCustomGamma(CMLResponseCurve* curve, float gamma){
  curve->responseType = CML_RESPONSE_CUSTOM_GAMMA;
  curve->forwardFunc  = cmlCreateGammaResponse(gamma);
  curve->backwardFunc = cmlCreateInverseGammaResponse(gamma);
}

CML_DEF void cmlInitResponseCurveWithCustomGammaLinear(CMLResponseCurve* curve, float gamma, float offset, float linScale, float split)
{
  curve->responseType = CML_RESPONSE_CUSTOM_GAMMA_LINEAR;
  curve->forwardFunc  = cmlCreateGammaLinearResponse(gamma, offset, linScale, split);
  curve->backwardFunc = cmlCreateInverseGammaLinearResponse(gamma, offset, linScale, split);
}



CML_DEF void cmlClearResponseCurve(CMLResponseCurve* curve){
  cmlReleaseFunction(curve->forwardFunc);
  cmlReleaseFunction(curve->backwardFunc);
}



CML_DEF CMLResponseCurveType cmlGetResponseCurveType(const CMLResponseCurve* curve){
  return curve->responseType;
}

CML_DEF const CMLFunction* cmlGetResponseCurveFunc(const CMLResponseCurve* curve){
  return curve->forwardFunc;
}

CML_DEF const CMLFunction* cmlGetResponseCurveInvFunc(const CMLResponseCurve* curve){
  return curve->backwardFunc;
}



CML_DEF void cmlGetRGBResponseTypes(const CMLColorMachine* cm, CMLResponseCurveType types[3]){
  CMLRGBColorSpaceType rgbType = cmlGetRGBColorSpaceType(cm);
  if(rgbType == CML_RGB_CUSTOM){
    types[0] = cmlGetResponseCurveType(&cm->rgbSpace.responseR);
    types[0] = cmlGetResponseCurveType(&cm->rgbSpace.responseG);
    types[0] = cmlGetResponseCurveType(&cm->rgbSpace.responseB);
  }else{
    CMLResponseCurveType responseType = cmlGetRGBColorSpaceResponseCurveType(rgbType);;
    types[0] = responseType;
    types[1] = responseType;
    types[2] = responseType;
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

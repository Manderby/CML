
#include "CMLColorMachineState.h"




//CML_HIDDEN void cml_setResponseR(CMLColorMachine* cm, CMLResponseCurveType type, float param0, float param1, float param2){
//  setupResponse(  &(cm->rgbSpace.RGBToLinearResponses[0]),
//                  &(cm->rgbSpace.LineartoRGBResponses[0]),
//                  &(cm->rgbSpace.responsetypes[0]),
//                  &(cm->rgbSpace.responseparams0[0]),
//                  &(cm->rgbSpace.responseparams1[0]),
//                  &(cm->rgbSpace.responseparams2[0]),
//                  cm->rgbSpace.lutsize,
//                  type,
//                  param0, param1, param2);
//}
//CML_HIDDEN void cml_setResponseG(CMLColorMachine* cm, CMLResponseCurveType type, float param0, float param1, float param2){
//  setupResponse(  &(cm->rgbSpace.RGBToLinearResponses[1]),
//                  &(cm->rgbSpace.LineartoRGBResponses[1]),
//                  &(cm->rgbSpace.responsetypes[1]),
//                  &(cm->rgbSpace.responseparams0[1]),
//                  &(cm->rgbSpace.responseparams1[1]),
//                  &(cm->rgbSpace.responseparams2[1]),
//                  cm->rgbSpace.lutsize,
//                  type,
//                  param0, param1, param2);
//}
//CML_HIDDEN void cml_setResponseB(CMLColorMachine* cm, CMLResponseCurveType type, float param0, float param1, float param2){
//  setupResponse(  &(cm->rgbSpace.RGBToLinearResponses[2]),
//                  &(cm->rgbSpace.LineartoRGBResponses[2]),
//                  &(cm->rgbSpace.responsetypes[2]),
//                  &(cm->rgbSpace.responseparams0[2]),
//                  &(cm->rgbSpace.responseparams1[2]),
//                  &(cm->rgbSpace.responseparams2[2]),
//                  cm->rgbSpace.lutsize,
//                  type,
//                  param0, param1, param2);
//}
//CML_HIDDEN void cml_setResponseL(CMLColorMachine* cm, CMLResponseCurveType type, float param0, float param1, float param2){
//  setupResponse(  &(cm->labSpace.LtoLinearResponse),
//                  &(cm->labSpace.LineartoLResponse),
//                  &(cm->labSpace.responseLtype),
//                  &(cm->labSpace.responseparam0),
//                  &(cm->labSpace.responseparam1),
//                  &(cm->labSpace.responseparam2),
//                  cm->labSpace.lutsize,
//                  type,
//                  param0, param1, param2);
//}


//CML_HIDDEN void setupResponse(
//                    CMLFunction** toxyzfunc,
//                    CMLFunction** fromxyzfunc,
//                    CMLResponseCurveType* typevar,
//                    float* gammavar0,
//                    float* gammavar1,
//                    float* gammavar2,
//                    CMLuint8 lutsize,
//                    CMLResponseCurveType type,
//                    float param0, float param1, float param2){
//  
//  if(param0 == 0.f){
//    switch(type){
//    case CML_RESPONSE_LINEAR:
//      param0 = 1.f;
//      param1 = 0.f;
//      param2 = 1.f;
//      break;
//    case CML_RESPONSE_SQRT:
//      param0 = 2.f;
//      param1 = 0.f;
//      param2 = 1.f;
//      break;
//    case CML_RESPONSE_GAMMA:
//      param0 = *gammavar0;
//      param1 = 0.f;
//      param2 = 1.f;
//      break;
//    case CML_RESPONSE_GAMMA_LINEAR:
//      param0 = *gammavar0;
//      param1 = *gammavar1;
//      param2 = *gammavar2;
//      break;
//    case CML_RESPONSE_SRGB:
//      param0 = 2.2f;
//      param1 = 0.f;
//      param2 = 1.f;
//      break;
//    case CML_RESPONSE_LSTAR:
//      param0 = 2.2f;
//      param1 = 0.f;
//      param2 = 1.f;
//      break;
//    case CML_RESPONSE_LSTAR_STANDARD:
//      param0 = 2.2f;
//      param1 = 0.f;
//      param2 = 1.f;
//      break;
//    default:
//      #if CML_DEBUG
//        param0 = 2.2f;
//        param1 = 0.f;
//        param2 = 1.f;
//        CMLError("Error in libcml: Response Curve type unknown.\n");
//      #endif
//      break;
//    }
//  }
//  
//  *typevar = type;
//  *gammavar0 = param0;
//  *gammavar1 = param1;
//  *gammavar2 = param2;
//  cmlReleaseFunction(*toxyzfunc);
//  cmlReleaseFunction(*fromxyzfunc);
//  
//  switch(type){
//  case CML_RESPONSE_LINEAR:
//    *toxyzfunc  = cmlCreateLinearResponse();
//    *fromxyzfunc = cmlCreateLinearResponse();
//    break;
//  case CML_RESPONSE_SQRT:
//    *toxyzfunc  = cmlCreateGammaResponse(2.f);
//    *fromxyzfunc = cmlCreateGammaResponse(.5f);
//    break;
//  case CML_RESPONSE_GAMMA:
//    *toxyzfunc  = cmlCreateGammaResponse(param0);
//    *fromxyzfunc = cmlCreateGammaResponse(cmlInverse(param0));
//    break;
//  case CML_RESPONSE_GAMMA_LINEAR:
//    *toxyzfunc  = cmlCreateGammaLinearResponse(param0, param1, param2);
//    *fromxyzfunc = cmlCreateGammaLinearResponse(cmlInverse(param0), param1, param2);
//    break;
//  case CML_RESPONSE_SRGB:
//    *toxyzfunc  = cmlCreatesRGBToXYZResponse();
//    *fromxyzfunc = cmlCreateXYZTosRGBResponse();
//    break;
//  case CML_RESPONSE_LSTAR:
//    *toxyzfunc  = cmlCreateLStarToYResponse();
//    *fromxyzfunc = cmlCreateYToLStarResponse();
//    break;
//  case CML_RESPONSE_LSTAR_STANDARD:
//    *toxyzfunc  = cmlCreateLStarToYStandardResponse();
//    *fromxyzfunc = cmlCreateYToLStarStandardResponse();
//    break;
//  default:
//    #if CML_DEBUG
//      *toxyzfunc  = cmlCreateLinearResponse();
//      *fromxyzfunc = cmlCreateLinearResponse();
//      CMLError("Error in libcml: Response Curve type unknown.\n");
//    #endif
//    break;
//  }
//  
//  // Create LUT if needed.
//  if(lutsize < 32){
//    CMLFunction* toxyzfunction = cmlSampleArrayFunction(*toxyzfunc, 0.f, 1.f, 1 << (CMLuint8)lutsize, CML_INTERPOLATION_INTERVAL, CML_EXTRAPOLATION_CLAMP_VALUE, CML_EXTRAPOLATION_CLAMP_VALUE);
//    CMLFunction* fromxyzfunction = cmlSampleArrayFunction(*fromxyzfunc, 0.f, 1.f, 1 << (CMLuint8)lutsize, CML_INTERPOLATION_INTERVAL, CML_EXTRAPOLATION_CLAMP_VALUE, CML_EXTRAPOLATION_CLAMP_VALUE);
//    cmlReleaseFunction(*toxyzfunc);
//    cmlReleaseFunction(*fromxyzfunc);
//    *toxyzfunc = toxyzfunction;
//    *fromxyzfunc = fromxyzfunction;
//  }
//}



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

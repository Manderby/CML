
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

#include "CMLColorMachineState.h"




//CMLHIDDEN void CMLInternalsetResponseR(CMLColorMachine* cm, CMLResponseCurveType type, float param0, float param1, float param2){
//  setupResponse(  &(cm->rgbspace.RGBtoLinearResponses[0]),
//                  &(cm->rgbspace.LineartoRGBResponses[0]),
//                  &(cm->rgbspace.responsetypes[0]),
//                  &(cm->rgbspace.responseparams0[0]),
//                  &(cm->rgbspace.responseparams1[0]),
//                  &(cm->rgbspace.responseparams2[0]),
//                  cm->rgbspace.lutsize,
//                  type,
//                  param0, param1, param2);
//}
//CMLHIDDEN void CMLInternalsetResponseG(CMLColorMachine* cm, CMLResponseCurveType type, float param0, float param1, float param2){
//  setupResponse(  &(cm->rgbspace.RGBtoLinearResponses[1]),
//                  &(cm->rgbspace.LineartoRGBResponses[1]),
//                  &(cm->rgbspace.responsetypes[1]),
//                  &(cm->rgbspace.responseparams0[1]),
//                  &(cm->rgbspace.responseparams1[1]),
//                  &(cm->rgbspace.responseparams2[1]),
//                  cm->rgbspace.lutsize,
//                  type,
//                  param0, param1, param2);
//}
//CMLHIDDEN void CMLInternalsetResponseB(CMLColorMachine* cm, CMLResponseCurveType type, float param0, float param1, float param2){
//  setupResponse(  &(cm->rgbspace.RGBtoLinearResponses[2]),
//                  &(cm->rgbspace.LineartoRGBResponses[2]),
//                  &(cm->rgbspace.responsetypes[2]),
//                  &(cm->rgbspace.responseparams0[2]),
//                  &(cm->rgbspace.responseparams1[2]),
//                  &(cm->rgbspace.responseparams2[2]),
//                  cm->rgbspace.lutsize,
//                  type,
//                  param0, param1, param2);
//}
//CMLHIDDEN void CMLInternalsetResponseL(CMLColorMachine* cm, CMLResponseCurveType type, float param0, float param1, float param2){
//  setupResponse(  &(cm->labspace.LtoLinearResponse),
//                  &(cm->labspace.LineartoLResponse),
//                  &(cm->labspace.responseLtype),
//                  &(cm->labspace.responseparam0),
//                  &(cm->labspace.responseparam1),
//                  &(cm->labspace.responseparam2),
//                  cm->labspace.lutsize,
//                  type,
//                  param0, param1, param2);
//}


//CMLHIDDEN void setupResponse(
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
//      #ifndef NDEBUG
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
//    *toxyzfunc  = CMLcreateLinearResponse();
//    *fromxyzfunc = CMLcreateLinearResponse();
//    break;
//  case CML_RESPONSE_SQRT:
//    *toxyzfunc  = CMLcreateGammaResponse(2.f);
//    *fromxyzfunc = CMLcreateGammaResponse(.5f);
//    break;
//  case CML_RESPONSE_GAMMA:
//    *toxyzfunc  = CMLcreateGammaResponse(param0);
//    *fromxyzfunc = CMLcreateGammaResponse(cmlInverse(param0));
//    break;
//  case CML_RESPONSE_GAMMA_LINEAR:
//    *toxyzfunc  = CMLcreateGammaLinearResponse(param0, param1, param2);
//    *fromxyzfunc = CMLcreateGammaLinearResponse(cmlInverse(param0), param1, param2);
//    break;
//  case CML_RESPONSE_SRGB:
//    *toxyzfunc  = CMLcreatesRGBToXYZResponse();
//    *fromxyzfunc = CMLcreateXYZTosRGBResponse();
//    break;
//  case CML_RESPONSE_LSTAR:
//    *toxyzfunc  = CMLcreateLStarToYResponse();
//    *fromxyzfunc = CMLcreateYToLStarResponse();
//    break;
//  case CML_RESPONSE_LSTAR_STANDARD:
//    *toxyzfunc  = CMLcreateLStarToYStandardResponse();
//    *fromxyzfunc = CMLcreateYToLStarStandardResponse();
//    break;
//  default:
//    #ifndef NDEBUG
//      *toxyzfunc  = CMLcreateLinearResponse();
//      *fromxyzfunc = CMLcreateLinearResponse();
//      CMLError("Error in libcml: Response Curve type unknown.\n");
//    #endif
//    break;
//  }
//  
//  // Create LUT if needed.
//  if(lutsize < 32){
//    CMLFunction* toxyzfunction = CMLsampleArrayFunction(*toxyzfunc, 0.f, 1.f, 1 << (CMLuint8)lutsize, CML_INTERPOLATION_INTERVAL, CML_EXTRAPOLATION_CLAMP_VALUE, CML_EXTRAPOLATION_CLAMP_VALUE);
//    CMLFunction* fromxyzfunction = CMLsampleArrayFunction(*fromxyzfunc, 0.f, 1.f, 1 << (CMLuint8)lutsize, CML_INTERPOLATION_INTERVAL, CML_EXTRAPOLATION_CLAMP_VALUE, CML_EXTRAPOLATION_CLAMP_VALUE);
//    cmlReleaseFunction(*toxyzfunc);
//    cmlReleaseFunction(*fromxyzfunc);
//    *toxyzfunc = toxyzfunction;
//    *fromxyzfunc = fromxyzfunction;
//  }
//}



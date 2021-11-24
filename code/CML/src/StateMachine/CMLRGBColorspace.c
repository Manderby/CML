
#include "../CML.h"
#include "CMLColorMachineState.h"


CML_HIDDEN static const CMLIlluminationType rgbspaceilluminations[CML_NUMBER_OF_RGB_SPACES] = {
  CML_ILLUMINATION_D65,     // CML_RGB_ADOBE_98
  CML_ILLUMINATION_D65,     // CML_RGB_APPLE
  CML_ILLUMINATION_D50,     // CML_RGB_BEST
  CML_ILLUMINATION_D50,     // CML_RGB_BETA
  CML_ILLUMINATION_D65,     // CML_RGB_BRUCE
  CML_ILLUMINATION_E  ,     // CML_RGB_CIE
  CML_ILLUMINATION_D50,     // CML_RGB_COLORMATCH
  CML_ILLUMINATION_D50,     // CML_RGB_DON4
  CML_ILLUMINATION_D50,     // CML_RGB_EBU_MONITOR
  CML_ILLUMINATION_D50,     // CML_RGB_ECI
  CML_ILLUMINATION_D50,     // CML_RGB_EKTA_SPACE_PS5
  CML_ILLUMINATION_D65,     // CML_RGB_HDTV
  CML_ILLUMINATION_D65,     // CML_RGB_REC_BT_601_525
  CML_ILLUMINATION_D65,     // CML_RGB_REC_BT_601_625
  CML_ILLUMINATION_D65,     // CML_RGB_REC_BT_709
  CML_ILLUMINATION_D65,     // CML_RGB_REC_BT_2020
  CML_ILLUMINATION_D50,     // CML_RGB_KODAK_DC
  CML_ILLUMINATION_C  ,     // CML_RGB_NTSC_53
  CML_ILLUMINATION_D65,     // CML_RGB_PAL_SECAM_EBU
  CML_ILLUMINATION_D50,     // CML_RGB_ROMM_PROPHOTO
  CML_ILLUMINATION_D65,     // CML_RGB_SMPTE_C
  CML_ILLUMINATION_D65,     // CML_RGB_SRGB
  CML_ILLUMINATION_D50,     // CML_RGB_WIDE_GAMUT
  CML_ILLUMINATION_D65,     // CML_RGB_CUSTOM
};

CML_HIDDEN static const CMLResponseCurvePreset rgbspaceresponsepresets[CML_NUMBER_OF_RGB_SPACES] = {
  CML_RESPONSE_GAMMA_ADOBE_98,         // CML_RGB_ADOBE_98
  CML_RESPONSE_GAMMA_1_8,         // CML_RGB_APPLE
  CML_RESPONSE_GAMMA_2_2,         // CML_RGB_BEST
  CML_RESPONSE_GAMMA_2_2,         // CML_RGB_BETA
  CML_RESPONSE_GAMMA_2_2,         // CML_RGB_BRUCE
  CML_RESPONSE_LINEAR,        // CML_RGB_CIE
  CML_RESPONSE_GAMMA_1_8,         // CML_RGB_COLORMATCH
  CML_RESPONSE_GAMMA_2_2,         // CML_RGB_DON4
  CML_RESPONSE_GAMMA_1_9,         // CML_RGB_EBU_MONITOR
  CML_RESPONSE_GAMMA_1_8,         // CML_RGB_ECI
  CML_RESPONSE_GAMMA_2_2,         // CML_RGB_EKTA_SPACE_PS5
  CML_RESPONSE_GAMMA_2_2,         // CML_RGB_HDTV
  CML_RESPONSE_GAMMA_LINEAR_REC_BT_10BIT,      // CML_RGB_REC_BT_601_525
  CML_RESPONSE_GAMMA_LINEAR_REC_BT_10BIT,  // CML_RGB_REC_BT_601_625
  CML_RESPONSE_GAMMA_LINEAR_REC_BT_10BIT,  // CML_RGB_REC_BT_709
  CML_RESPONSE_GAMMA_LINEAR_REC_BT_12BIT,  // CML_RGB_REC_BT_2020
  CML_RESPONSE_GAMMA_2_2,         // CML_RGB_KODAK_DC
  CML_RESPONSE_GAMMA_2_2,         // CML_RGB_NTSC_53
  CML_RESPONSE_SRGB,          // CML_RGB_PAL_SECAM_EBU
  CML_RESPONSE_GAMMA_1_8,         // CML_RGB_ROMM_PROPHOTO
  CML_RESPONSE_SRGB,          // CML_RGB_SMPTE_C
  CML_RESPONSE_SRGB,          // CML_RGB_SRGB
  CML_RESPONSE_GAMMA_2_2,         // CML_RGB_WIDE_GAMUT
  CML_RESPONSE_GAMMA_2_2,         // CML_RGB_CUSTOM
};



// gamma, offset, linscale for R, G and B
// with the following computation:
// (1+offset) * powf(x, 1/gamma) - offset   if x => split
// x * linscale                              if x < split
// split will be computed automatically.

//CML_HIDDEN static const float rgbspaceresponseparams[CML_NUMBER_OF_RGB_SPACES][12] = {
//  { 2.f + 51.f / 256.f, 0.f, 1.f, 0.f,
//    2.f + 51.f / 256.f, 0.f, 1.f, 0.f,
//    2.f + 51.f / 256.f, 0.f, 1.f, 0.f},   // CML_RGB_ADOBE_98
//  { 1.8f              , 0.f, 1.f, 0.f,
//    1.8f              , 0.f, 1.f, 0.f,
//    1.8f              , 0.f, 1.f, 0.f},   // CML_RGB_APPLE
//  { 2.2f              , 0.f, 1.f, 0.f,
//    2.2f              , 0.f, 1.f, 0.f,
//    2.2f              , 0.f, 1.f, 0.f},   // CML_RGB_BEST
//  { 2.2f              , 0.f, 1.f, 0.f,
//    2.2f              , 0.f, 1.f, 0.f,
//    2.2f              , 0.f, 1.f, 0.f},   // CML_RGB_BETA
//  { 2.2f              , 0.f, 1.f, 0.f,
//    2.2f              , 0.f, 1.f, 0.f,
//    2.2f              , 0.f, 1.f, 0.f},   // CML_RGB_BRUCE
//  { 1.0f              , 0.f, 1.f, 0.f,
//    1.0f              , 0.f, 1.f, 0.f,
//    1.0f              , 0.f, 1.f, 0.f},   // CML_RGB_CIE
//  { 1.8f              , 0.f, 1.f, 0.f,
//    1.8f              , 0.f, 1.f, 0.f,
//    1.8f              , 0.f, 1.f, 0.f},   // CML_RGB_COLORMATCH
//  { 2.2f              , 0.f, 1.f, 0.f,
//    2.2f              , 0.f, 1.f, 0.f,
//    2.2f              , 0.f, 1.f, 0.f},   // CML_RGB_DON4
//  { 1.9f              , 0.f, 1.f, 0.f,
//    1.9f              , 0.f, 1.f, 0.f,
//    1.9f              , 0.f, 1.f, 0.f},   // CML_RGB_EBU_MONITOR
//  { 1.8f              , 0.f, 1.f, 0.f,
//    1.8f              , 0.f, 1.f, 0.f,
//    1.8f              , 0.f, 1.f, 0.f},   // CML_RGB_ECI
//  { 2.2f              , 0.f, 1.f, 0.f,
//    2.2f              , 0.f, 1.f, 0.f,
//    2.2f              , 0.f, 1.f, 0.f},   // CML_RGB_EKTA_SPACE_PS5
//  { 2.2f              , 0.f, 1.f, 0.f,
//    2.2f              , 0.f, 1.f, 0.f,
//    2.2f              , 0.f, 1.f, 0.f},   // CML_RGB_HDTV
//  { 1.f / 0.45f       , 0.099f, 4.5f, 0.018f,
//    1.f / 0.45f       , 0.099f, 4.5f, 0.018f,
//    1.f / 0.45f       , 0.099f, 4.5f, 0.018f},   // CML_RGB_REC_BT_601_525
//  { 1.f / 0.45f       , 0.099f, 4.5f, 0.018f,
//    1.f / 0.45f       , 0.099f, 4.5f, 0.018f,
//    1.f / 0.45f       , 0.099f, 4.5f, 0.018f},   // CML_RGB_REC_BT_601_625
//  { 1.f / 0.45f       , 0.099f, 4.5f, 0.018f,
//    1.f / 0.45f       , 0.099f, 4.5f, 0.018f,
//    1.f / 0.45f       , 0.099f, 4.5f, 0.018f},   // CML_RGB_REC_BT_709
//  { 1.f / 0.45f       , 0.0993f, 4.5f, 0.0181f,
//    1.f / 0.45f       , 0.0993f, 4.5f, 0.0181f,
//    1.f / 0.45f       , 0.0993f, 4.5f, 0.0181f},   // CML_RGB_REC_BT_2020
//  { 2.2f              , 0.f, 1.f, 0.f,
//    2.2f              , 0.f, 1.f, 0.f,
//    2.2f              , 0.f, 1.f, 0.f},   // CML_RGB_KODAK_DC
//  { 2.2f              , 0.f, 1.f, 0.f,
//    2.2f              , 0.f, 1.f, 0.f,
//    2.2f              , 0.f, 1.f, 0.f},   // CML_RGB_NTSC_53
//  { 2.2f              , 0.055f, 12.92f, 0.0031306684425f,
//    2.2f              , 0.055f, 12.92f, 0.0031306684425f,
//    2.2f              , 0.055f, 12.92f, 0.0031306684425f},   // CML_RGB_PAL_SECAM_EBU
//  { 1.8f              , 0.f, 1.f, 0.f,
//    1.8f              , 0.f, 1.f, 0.f,
//    1.8f              , 0.f, 1.f, 0.f},   // CML_RGB_ROMM_PROPHOTO
//  { 2.2f              , 0.055f, 12.92f, 0.0031306684425f,
//    2.2f              , 0.055f, 12.92f, 0.0031306684425f,
//    2.2f              , 0.055f, 12.92f, 0.0031306684425f},   // CML_RGB_SMPTE_C
//  { 2.4f              , 0.055f, 12.92f, 0.0031306684425f,
//    2.4f              , 0.055f, 12.92f, 0.0031306684425f,
//    2.4f              , 0.055f, 12.92f, 0.0031306684425f},   // CML_RGB_SRGB
//  { 2.2f              , 0.f, 1.f, 0.f,
//    2.2f              , 0.f, 1.f, 0.f,
//    2.2f              , 0.f, 1.f, 0.f},   // CML_RGB_WIDE_GAMUT
//  { 2.2f              , 0.f, 1.f, 0.f,
//    2.2f              , 0.f, 1.f, 0.f,
//    2.2f              , 0.f, 1.f, 0.f},   // CML_RGB_CUSTOM
//};

// array usage:
// xr, yr, xg, yg, xb, yb
// gamma, offset, linscale,
CML_HIDDEN static const float rgbspaceprimaries[CML_NUMBER_OF_RGB_SPACES][9] = {
  {0.6400f  , 0.3300f  , 0.2100f  , 0.7100f  , 0.1500f  , 0.0600f},   // CML_RGB_ADOBE_98
  {0.6250f  , 0.3400f  , 0.2800f  , 0.5950f  , 0.1550f  , 0.0700f},   // CML_RGB_APPLE
  {0.7347f  , 0.2653f  , 0.2150f  , 0.7750f  , 0.1300f  , 0.0350f},   // CML_RGB_BEST
  {0.6888f  , 0.3112f  , 0.1986f  , 0.7551f  , 0.1265f  , 0.0352f},   // CML_RGB_BETA
  {0.6400f  , 0.3300f  , 0.2800f  , 0.6500f  , 0.1500f  , 0.0600f},   // CML_RGB_BRUCE
  {0.734690f, 0.265310f, 0.272958f, 0.718062f, 0.166446f, 0.008964f},   // CML_RGB_CIE
  {0.6300f  , 0.3400f  , 0.2950f  , 0.6050f  , 0.1500f  , 0.0750f},   // CML_RGB_COLORMATCH
  {0.6960f  , 0.3000f  , 0.2150f  , 0.7650f  , 0.1300f  , 0.0350f},   // CML_RGB_DON4
  {0.6314f  , 0.3391f  , 0.2809f  , 0.5971f  , 0.1487f  , 0.0645f},   // CML_RGB_EBU_MONITOR
  {0.6700f  , 0.3300f  , 0.2100f  , 0.7100f  , 0.1400f  , 0.0800f},   // CML_RGB_ECI
  {0.6950f  , 0.3050f  , 0.2600f  , 0.7000f  , 0.1100f  , 0.0050f},   // CML_RGB_EKTA_SPACE_PS5
  {0.6400f  , 0.3300f  , 0.3297f  , 0.6593f  , 0.1500f  , 0.0600f},   // CML_RGB_HDTV
 {0.6300f  , 0.3400f  , 0.3100f  , 0.5950f  , 0.1550f  , 0.0700f},   // CML_RGB_REC_BT_601_525
 {0.6400f  , 0.3300f  , 0.2900f  , 0.6000f  , 0.1500f  , 0.0600f},   // CML_RGB_REC_BT_601_625
 {0.6400f  , 0.3300f  , 0.3000f  , 0.6000f  , 0.1500f  , 0.0600f},   // CML_RGB_REC_BT_709
 {0.7080f  , 0.2920f  , 0.1700f  , 0.7970f  , 0.1310f  , 0.0460f},   // CML_RGB_REC_BT_2020
  {0.6492f  , 0.3314f  , 0.3219f  , 0.5997f  , 0.1548f  , 0.0646f},   // CML_RGB_KODAK_DC
  {0.6700f  , 0.3300f  , 0.2100f  , 0.7100f  , 0.1400f  , 0.0800f},   // CML_RGB_NTSC_53
  {0.6400f  , 0.3300f  , 0.2900f  , 0.6000f  , 0.1500f  , 0.0600f},   // CML_RGB_PAL_SECAM_EBU
  {0.7347f  , 0.2653f  , 0.1596f  , 0.8404f  , 0.0366f  , 0.0001f},   // CML_RGB_ROMM_PROPHOTO
  {0.6300f  , 0.3400f  , 0.3100f  , 0.5950f  , 0.1550f  , 0.0700f},   // CML_RGB_SMPTE_C
  {0.6400f  , 0.3300f  , 0.3000f  , 0.6000f  , 0.1500f  , 0.0600f},   // CML_RGB_SRGB
  {0.734690f, 0.265310f, 0.114161f, 0.826207f, 0.156641f, 0.017705f},   // CML_RGB_WIDE_GAMUT
  {0.6400f  , 0.3300f  , 0.3000f  , 0.6000f  , 0.1500f  , 0.0600f}   // CML_RGB_CUSTOM
};



CML_HIDDEN void CMLInternalrecomputeRGBResponses(CMLColorMachine* cm){
  if(cm->recomputationlockcount){cm->recomputationmask |= CML_COLORMACHINE_RECOMPUTE_RGB_RESPONSES; return;}
  
  CMLResponseCurve* responseR = cmlCreateResponseCurveWithPreset(NULL, rgbspaceresponsepresets[cm->rgbspace.state]);
  CMLResponseCurve* responseG = cmlCreateResponseCurveWithPreset(NULL, rgbspaceresponsepresets[cm->rgbspace.state]);
  CMLResponseCurve* responseB = cmlCreateResponseCurveWithPreset(NULL, rgbspaceresponsepresets[cm->rgbspace.state]);
  CMLsetResponseR(cm, responseR);
  CMLsetResponseG(cm, responseG);
  CMLsetResponseB(cm, responseB);
  CMLdestroyResponseCurve(responseR);
  CMLdestroyResponseCurve(responseG);
  CMLdestroyResponseCurve(responseB);
  
}


CML_HIDDEN void CMLInternalrecomputeRGBColorspace(CMLColorMachine* cm){
  CMLVec3 normedwhitepointYxy;

  if(cm->recomputationlockcount){cm->recomputationmask |= CML_COLORMACHINE_RECOMPUTE_RGB; return;}

  if(cmlGetIlluminationType(cmlGetReferenceIllumination(&(cm->observer))) != rgbspaceilluminations[cm->rgbspace.state]){
    cm->rgbspace.state = CML_RGB_CUSTOM;
  }

  cmlCpy3(normedwhitepointYxy, cmlGetReferenceWhitepointYxy(&(cm->observer)));
//  if(!cm->observer.radiometric){
//    normedwhitepointYxy[0] = 1.f;
//  }
  
  CMLcomputeRGBtoXYZMatrix(cm->rgbspace.matrix, cm->rgbspace.primariesYxy[0], cm->rgbspace.primariesYxy[1], cm->rgbspace.primariesYxy[2], normedwhitepointYxy);
  cmlMat33Inverse(cm->rgbspace.matrixinv, cm->rgbspace.matrix);
  
  CMLInternalrecomputeRGBResponses(cm);
}



CML_API CMLRGBColorSpace CMLgetRGBColorSpace(const CMLColorMachine* cm){
  return cm->rgbspace.state;
}


CML_API void CMLsetRGBColorSpace(CMLColorMachine* cm, CMLRGBColorSpace colorspacetype){    
  // Multiple changes need to be made. (Illumination and RGBspace)
  CMLlockRecomputation(cm);
  
  cm->rgbspace.state = colorspacetype;
  if(cm->rgbspace.state != CML_RGB_CUSTOM){
    CMLgetRGBColorSpacePrimaries(colorspacetype, cm->rgbspace.primariesYxy[0], cm->rgbspace.primariesYxy[1], cm->rgbspace.primariesYxy[2]);
    CMLsetIlluminationType(cm, rgbspaceilluminations[cm->rgbspace.state]);
  }
  CMLInternalrecomputeRGBColorspace(cm);
  
  CMLreleaseRecomputation(cm);
}


CML_API void CMLgetRGBPrimariesYxy(const CMLColorMachine* cm, CMLVec3 primaries[3]){
  cmlCpy3(primaries[0], cm->rgbspace.primariesYxy[0]);
  cmlCpy3(primaries[1], cm->rgbspace.primariesYxy[1]);
  cmlCpy3(primaries[2], cm->rgbspace.primariesYxy[2]);
}


CML_API void CMLsetRGBPrimariesYxy(CMLColorMachine* cm, CMLVec3 primaries[3]){
  cm->rgbspace.state = CML_RGB_CUSTOM;
  cm->rgbspace.primariesYxy[0][1] = primaries[0][1];
  cm->rgbspace.primariesYxy[0][2] = primaries[0][2];
  cm->rgbspace.primariesYxy[1][1] = primaries[1][1];
  cm->rgbspace.primariesYxy[1][2] = primaries[1][2];
  cm->rgbspace.primariesYxy[2][1] = primaries[2][1];
  cm->rgbspace.primariesYxy[2][2] = primaries[2][2];
  CMLInternalrecomputeRGBColorspace(cm);
}


//CML_API void CMLgetRGBtoLinearResponses(const CMLColorMachine* cm, const CMLFunction* responses[3]){
//  responses[0] = cm->rgbspace.responseR.backwardfunc;
//  responses[1] = cm->rgbspace.responseG.backwardfunc;
//  responses[2] = cm->rgbspace.responseB.backwardfunc;
//}


//CML_API void CMLgetLineartoRGBResponses(const CMLColorMachine* cm, const CMLFunction* responses[3]){
//  responses[0] = cm->rgbspace.responseR.forwardfunc;
//  responses[1] = cm->rgbspace.responseG.forwardfunc;
//  responses[2] = cm->rgbspace.responseB.forwardfunc;
//}


//CML_API void CMLgetRGBResponseTypes(const CMLColorMachine* cm, CMLResponseCurveType responsetypes[3]){
//  responsetypes[0] = cm->rgbspace.responseR.type;
//  responsetypes[1] = cm->rgbspace.responseG.type;
//  responsetypes[2] = cm->rgbspace.responseB.type;
//}


//CML_API void CMLgetRGBGammas(const CMLColorMachine* cm, float gammas[3]){
//  gammas[0] = cm->rgbspace.responseR.param0;
//  gammas[1] = cm->rgbspace.responseG.param0;
//  gammas[2] = cm->rgbspace.responseB.param0;
//}


CML_API void CMLsetResponseRGB(CMLColorMachine* cm, CMLResponseCurve* response){
  CMLsetResponseR(cm, response);
  CMLsetResponseG(cm, response);
  CMLsetResponseB(cm, response);
}

CML_API const CMLResponseCurve* CMLgetResponseR  (CMLColorMachine* cm){
  return &(cm->rgbspace.responseR);
}
CML_API const CMLResponseCurve* CMLgetResponseG  (CMLColorMachine* cm){
  return &(cm->rgbspace.responseG);
}
CML_API const CMLResponseCurve* CMLgetResponseB  (CMLColorMachine* cm){
  return &(cm->rgbspace.responseB);
}

CML_API void CMLsetResponseR(CMLColorMachine* cm, CMLResponseCurve* response){
  CMLclearResponseCurve(&(cm->rgbspace.responseR));
  cmlCreateResponseCurveCopy((&cm->rgbspace.responseR), response);
//  cm->rgbspace.responseR.forwardfunc = CMLduplicateFunction(response->forwardfunc);
//  cm->rgbspace.responseR.backwardfunc = CMLduplicateFunction(response->backwardfunc);
//  cmlCreateResponseCurveWithParamFunction(&(cm->rgbspace.responseR), type, param0, param1, param2, param3);
}


CML_API void CMLsetResponseG(CMLColorMachine* cm, CMLResponseCurve* response){
  CMLclearResponseCurve(&(cm->rgbspace.responseG));
  cmlCreateResponseCurveCopy((&cm->rgbspace.responseG), response);
//  cm->rgbspace.responseG.forwardfunc = CMLduplicateFunction(response->forwardfunc);
//  cm->rgbspace.responseG.backwardfunc = CMLduplicateFunction(response->backwardfunc);
//  cmlCreateResponseCurveWithParamFunction(&(cm->rgbspace.responseG), type, param0, param1, param2, param3);
}


CML_API void CMLsetResponseB(CMLColorMachine* cm, CMLResponseCurve* response){
  CMLclearResponseCurve(&(cm->rgbspace.responseB));
  cmlCreateResponseCurveCopy((&cm->rgbspace.responseB), response);
//  cm->rgbspace.responseB.forwardfunc = CMLduplicateFunction(response->forwardfunc);
//  cm->rgbspace.responseB.backwardfunc = CMLduplicateFunction(response->backwardfunc);
//  cmlCreateResponseCurveWithParamFunction(&(cm->rgbspace.responseB), type, param0, param1, param2, param3);
}



CML_API CMLuint8 CMLgetRGBLUTSize(const CMLColorMachine* cm){
  return cm->rgbspace.lutsize;
}


CML_API void CMLsetRGBLUTSize(CMLColorMachine* cm, CMLuint8 bits){
  if((bits < 1) || (bits > 16)){bits = 32;}
  cm->rgbspace.lutsize = bits;
  CMLInternalrecomputeRGBResponses(cm);
}


CML_API void CMLgetRGBColorSpacePrimaries(CMLRGBColorSpace colorspacetype, CMLVec3 primaryRYxy, CMLVec3 primaryGYxy, CMLVec3 primaryBYxy){
  if(colorspacetype < CML_RGB_CUSTOM){
    primaryRYxy[0] = 1.f;
    primaryRYxy[1]  = rgbspaceprimaries[colorspacetype][0];
    primaryRYxy[2]  = rgbspaceprimaries[colorspacetype][1];
    primaryGYxy[0] = 1.f;
    primaryGYxy[1]  = rgbspaceprimaries[colorspacetype][2];
    primaryGYxy[2]  = rgbspaceprimaries[colorspacetype][3];
    primaryBYxy[0] = 1.f;
    primaryBYxy[1]  = rgbspaceprimaries[colorspacetype][4];
    primaryBYxy[2]  = rgbspaceprimaries[colorspacetype][5];
  }else{
    #ifndef NDEBUG
      cmlError("Invalid RGB colorspace.");
    #endif
  }
}


CML_API CMLIlluminationType CMLgetRGBColorSpaceIlluminationType(
                                  CMLRGBColorSpace      colorspacetype){
  if(colorspacetype < CML_RGB_CUSTOM){
    return rgbspaceilluminations[colorspacetype];
  }else{
    #ifndef NDEBUG
      cmlError("Invalid RGB colorspace.");
    #endif
    return CML_ILLUMINATION_CUSTOM_WHITEPOINT;
  }
}

CML_API CMLResponseCurvePreset CMLgetRGBColorSpaceResponseCurvePreset
                                      (CMLRGBColorSpace colorspacetype){
  if(colorspacetype < CML_RGB_CUSTOM){
    return rgbspaceresponsepresets[colorspacetype];
  }else{
    #ifndef NDEBUG
      cmlError("Invalid RGB colorspace.");
    #endif
    return CML_RESPONSE_LINEAR;
  }
}

CML_API void CMLcomputeRGBtoXYZMatrix(CMLMat33 rgbtoxyzmatrix, CMLVec3 primaryRYxy, CMLVec3 primaryGYxy, CMLVec3 primaryBYxy, const CMLVec3 whitepointYxy){
  CMLVec3 redXYZ;
  CMLVec3 greenXYZ;
  CMLVec3 blueXYZ;

  float xr = primaryRYxy[1];
  float yr = primaryRYxy[2];
  float xg = primaryGYxy[1];
  float yg = primaryGYxy[2];
  float xb = primaryBYxy[1];
  float yb = primaryBYxy[2];
  float Yw = whitepointYxy[0];
  float xw = whitepointYxy[1];
  float yw = whitepointYxy[2];

  // Computation of the matrix
  float ybxg = yb*xg;
  float ygxb = yg*xb;
  float yrxb = yr*xb;
  float xryb = xr*yb;
  float yrxg = yr*xg;
  float xryg = xr*yg;
  float diff1 = ybxg-ygxb;
  float diff2 = xryb-yrxb;
  float diff3 = xryg-yrxg;
  float div1 = diff3-diff2+diff1;
  float zw = 1.f - xw - yw;
  float div2 = div1 * yw;
  
  primaryRYxy[0] = Yw * yr*(+(yg-yb+diff1)*xw/div2+(xb-xg+diff1)/div1+diff1*zw/div2);
  primaryGYxy[0] = Yw * yg*(-(yr-yb+diff2)*xw/div2-(xb-xr+diff2)/div1-diff2*zw/div2);
  primaryBYxy[0] = Yw * yb*(+(yr-yg+diff3)*xw/div2+(xg-xr+diff3)/div1+diff3*zw/div2);

  // todo: can the whitepoint be used?
  cmlInternalYxytoXYZ(redXYZ  , primaryRYxy, CML_NULL, 1);
  cmlInternalYxytoXYZ(greenXYZ, primaryGYxy, CML_NULL, 1);
  cmlInternalYxytoXYZ(blueXYZ , primaryBYxy, CML_NULL, 1);

  CMLMat33setVec3(rgbtoxyzmatrix, redXYZ, greenXYZ, blueXYZ);
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

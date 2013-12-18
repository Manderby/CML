
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.


#include "CML.h"
#include "StateMachine/CMLColorMachineState.h"

CMLAPI void cmlDestroyRGBSpace(void* rgbspace);


CMLHIDDEN static const CMLIlluminationType rgbspaceilluminations[CML_NUMBER_OF_RGB_SPACES] = {
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


CMLHIDDEN static const CMLResponseCurvePreset rgbspaceresponsepresets[CML_NUMBER_OF_RGB_SPACES] = {
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


// array usage:
// xr, yr, xg, yg, xb, yb
// gamma, offset, linscale,
CMLHIDDEN static const float rgbspaceprimaries[CML_NUMBER_OF_RGB_SPACES][9] = {
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



CMLAPI CMLRGBSpace* cmlCreateRGBSpaceWithPreset(CMLRGBSpaceType type, const CMLObserver* observer){
  CMLRGBSpace* rgbspace = cmlCreateObject(sizeof(CMLRGBSpace), cmlDestroyRGBSpace);

  rgbspace->type = type;
  if(rgbspace->type != CML_RGB_CUSTOM){
    CMLIllumination* newillumination = cmlCreateIlluminationWithPreset(rgbspaceilluminations[rgbspace->type], 0.f);
    rgbspace->whitepoint = cmlCreateWhitepointWithIllumination(newillumination, observer, 1.f);
    cmlReleaseObject(newillumination);
    cmlGetRGBSpacePrimaries(type, rgbspace->primariesYxy[0], rgbspace->primariesYxy[1], rgbspace->primariesYxy[2]);
    rgbspace->responsecurves[0] = cmlCreateResponseCurveWithPreset(rgbspaceresponsepresets[type]);
    rgbspace->responsecurves[1] = cmlCreateResponseCurveWithPreset(rgbspaceresponsepresets[type]);
    rgbspace->responsecurves[2] = cmlCreateResponseCurveWithPreset(rgbspaceresponsepresets[type]);
  }
  CMLcomputeRGBtoXYZMatrix(rgbspace->matrix, rgbspace->primariesYxy[0], rgbspace->primariesYxy[1], rgbspace->primariesYxy[2], cmlGetWhitepointYxy(cmlGetRGBSpaceWhitepoint(rgbspace)));
  cmlMat33Inverse(rgbspace->matrixinv, rgbspace->matrix);
  return rgbspace;
}



CMLAPI void cmlDestroyRGBSpace(void* rgbsp){
  CMLRGBSpace* rgbspace = (CMLRGBSpace*)rgbsp;
  cmlReleaseObject(rgbspace->whitepoint);
  cmlReleaseObject(rgbspace->responsecurves[0]);
  cmlReleaseObject(rgbspace->responsecurves[1]);
  cmlReleaseObject(rgbspace->responsecurves[2]);
}



CMLAPI const float* cmlGetRGBSpaceInverseMatrix(const CMLRGBSpace* rgbspace){
  return rgbspace->matrixinv;
}


CMLAPI const float* cmlGetRGBSpacePrimaryYxy(const CMLRGBSpace* rgbspace, CMLInt index){
  return rgbspace->primariesYxy[index];
}



CMLAPI const CMLResponseCurve* cmlGetRGBSpaceResponseCurve(const CMLRGBSpace* rgbspace, CMLInt index){
  return rgbspace->responsecurves[index];
}


CMLAPI const CMLWhitepoint* cmlGetRGBSpaceWhitepoint(const CMLRGBSpace* rgbspace){
  return rgbspace->whitepoint;
}

CMLAPI CMLRGBSpaceType cmlGetRGBSpaceType(const CMLRGBSpace* rgbspace){
  return rgbspace->type;
}


CMLAPI CMLIlluminationType cmlGetRGBSpaceIlluminationType(
                                  CMLRGBSpaceType      colorspacetype){
  if(colorspacetype < CML_RGB_CUSTOM){
    return rgbspaceilluminations[colorspacetype];
  }else{
    #ifndef NDEBUG
      cmlError("cmlGetRGBSpaceIlluminationType", "Invalid RGB colorspace.");
    #endif
    return CML_ILLUMINATION_CUSTOM_WHITEPOINT;
  }
}

CMLAPI CMLResponseCurvePreset cmlGetRGBSpaceResponseCurvePreset
                                      (CMLRGBSpaceType colorspacetype){
  if(colorspacetype < CML_RGB_CUSTOM){
    return rgbspaceresponsepresets[colorspacetype];
  }else{
    #ifndef NDEBUG
      cmlError("cmlGetRGBSpaceResponseCurvePreset", "Invalid RGB colorspace.");
    #endif
    return CML_RESPONSE_LINEAR;
  }
}


CMLAPI void cmlGetRGBSpacePrimaries(CMLRGBSpaceType colorspacetype, CMLVec3 primaryRYxy, CMLVec3 primaryGYxy, CMLVec3 primaryBYxy){
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
      cmlError("cmlGetRGBSpacePrimaries", "Invalid RGB colorspace.");
    #endif
  }
}



CMLAPI void CMLcomputeRGBtoXYZMatrix(CMLMat33 rgbtoxyzmatrix, CMLVec3 primaryRYxy, CMLVec3 primaryGYxy, CMLVec3 primaryBYxy, const CMLVec3 whitepointYxy){
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
  cmlInternalOneYxytoXYZ(redXYZ  , primaryRYxy, CML_NULL);
  cmlInternalOneYxytoXYZ(greenXYZ, primaryGYxy, CML_NULL);
  cmlInternalOneYxytoXYZ(blueXYZ , primaryBYxy, CML_NULL);

  CMLMat33setVec3(rgbtoxyzmatrix, redXYZ, greenXYZ, blueXYZ);
}


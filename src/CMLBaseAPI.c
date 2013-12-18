
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

#include "CML.h"
#include "StateMachine/CMLColorMachineState.h"



CMLAPI void CMLconvertXYZtoYxy (CMLVec3 Yxy , const CMLVec3 XYZ, const CMLVec3 whitepointYxy){
  cmlInternalOneXYZtoYxy(Yxy, XYZ, whitepointYxy);
}

CMLAPI void CMLconvertYxytoXYZ (CMLVec3 XYZ , const CMLVec3 Yxy, const CMLVec3 whitepointXYZ){
  cmlInternalOneYxytoXYZ(XYZ, Yxy, whitepointXYZ);
}

CMLAPI void CMLconvertYxytoYupvp(CMLVec3 Yupvp , const CMLVec3 Yxy, const CMLVec3 whitepointYupvp){
  cmlInternalOneYxytoYupvp(Yupvp, Yxy, whitepointYupvp);
}

CMLAPI void CMLconvertYupvptoYxy (CMLVec3 Yxy , const CMLVec3 Yupvp, const CMLVec3 whitepointYxy){
  cmlInternalOneYupvptoYxy(Yxy, Yupvp, whitepointYxy);
}

CMLAPI void CMLconvertYupvptoYuv (CMLVec3 Yuv , const CMLVec3 Yupvp){
  cmlInternalOneYupvptoYuv(Yuv, Yupvp);
}

CMLAPI void CMLconvertYuvtoYupvp (CMLVec3 Yupvp , const CMLVec3 Yuv){
  cmlInternalOneYuvtoYupvp(Yupvp, Yuv);
}

CMLAPI void CMLconvertYupvptoLuv (CMLVec3 Luv , const CMLVec3 Yupvp, const CMLVec3 whitepointYupvp){
  CMLFunction* lineartoLStarResponse = cmlCreateYToLStarResponse();
  cmlInternalOneYupvptoLuv(Luv, Yupvp, whitepointYupvp, lineartoLStarResponse);
  cmlReleaseObject(lineartoLStarResponse);
}

CMLAPI void CMLconvertLuvtoYupvp (CMLVec3 Yupvp , const CMLVec3 Luv, const CMLVec3 whitepointYupvp){
  CMLFunction* LStartoLinearResponse = cmlCreateLStarToYResponse();
  cmlInternalOneLuvtoYupvp(Yupvp, Luv, whitepointYupvp, LStartoLinearResponse);
  cmlReleaseObject(LStartoLinearResponse);
}

CMLAPI void CMLconvertXYZtoLab(CMLVec3 Lab , const CMLVec3 XYZ , const CMLVec3 whitepointXYZ){
  CMLFunction* lineartoLStarResponse = cmlCreateYToLStarResponse();
  CMLVec3 inverseWhitepointXYZ = {cmlInverse(whitepointXYZ[0]), cmlInverse(whitepointXYZ[1]), cmlInverse(whitepointXYZ[2])};
  cmlInternalOneXYZtoCIELAB(Lab, XYZ, inverseWhitepointXYZ, lineartoLStarResponse);
  cmlReleaseObject(lineartoLStarResponse);
}

CMLAPI void CMLconvertLabtoXYZ(CMLVec3 XYZ , const CMLVec3 Lab , const CMLVec3 whitepointXYZ){
  CMLFunction* LStartoLinearResponse = cmlCreateLStarToYResponse();
  cmlInternalOneCIELABtoXYZ(XYZ, Lab, whitepointXYZ, LStartoLinearResponse);
  cmlReleaseObject(LStartoLinearResponse);
}

CMLAPI void CMLconvertLabtoLch (CMLVec3 Lch , const CMLVec3 Lab ){
  cmlInternalOneLabtoLch(Lch, Lab);
}

CMLAPI void CMLconvertLchtoLab (CMLVec3 Lab , const CMLVec3 Lch ){
  cmlInternalOneLchtoLab(Lab, Lch);
}

CMLAPI void CMLconvertXYZtoRGB (CMLVec3 RGB , const CMLVec3 XYZ, const CMLMat33 XYZtoRGBmatrix, const CMLFunction* LineartoRResponse, const CMLFunction* LineartoGResponse, const CMLFunction* LineartoBResponse){
  cmlInternalOneXYZtoRGB(RGB, XYZ, XYZtoRGBmatrix, LineartoRResponse, LineartoGResponse, LineartoBResponse);
}

CMLAPI void CMLconvertRGBtoXYZ (CMLVec3 XYZ , const CMLVec3 RGB, const CMLMat33 RGBtoXYZmatrix, const CMLFunction* RtoLinearResponse, const CMLFunction* GtoLinearResponse, const CMLFunction* BtoLinearResponse){
  cmlInternalOneRGBtoXYZ(XYZ, RGB, RGBtoXYZmatrix, RtoLinearResponse, GtoLinearResponse, BtoLinearResponse);
}

CMLAPI void CMLconvertRGBtoYCbCr (CMLVec3 YCbCr , const CMLVec3 RGB, const CMLVec3 redprimaryYxy, const CMLVec3 blueprimaryYxy, const CMLVec3 whitepointXYZ){
  CMLVec3 inversewhitepointXYZ;
  cmlSet3(inversewhitepointXYZ, cmlInverse(whitepointXYZ[0]), cmlInverse(whitepointXYZ[1]), cmlInverse(whitepointXYZ[2]));
  cmlInternalOneRGBtoYCbCr(YCbCr, RGB, redprimaryYxy, blueprimaryYxy, inversewhitepointXYZ);
}

CMLAPI void CMLconvertYCbCrtoRGB (CMLVec3 RGB , const CMLVec3 YCbCr, const CMLVec3 redprimaryYxy, const CMLVec3 blueprimaryYxy, const CMLVec3 whitepointXYZ){
  CMLVec3 inversewhitepointXYZ;
  cmlSet3(inversewhitepointXYZ, cmlInverse(whitepointXYZ[0]), cmlInverse(whitepointXYZ[1]), cmlInverse(whitepointXYZ[2]));
  cmlInternalOneYCbCrtoRGB(RGB, YCbCr, redprimaryYxy, blueprimaryYxy, inversewhitepointXYZ);
}

CMLAPI void CMLconvertRGBtoHSV (CMLVec3 HSV , const CMLVec3 RGB){
  cmlInternalOneRGBtoHSV(HSV, RGB);
}

CMLAPI void CMLconvertHSVtoRGB (CMLVec3 RGB , const CMLVec3 HSV){
  cmlInternalOneHSVtoRGB(RGB, HSV);
}

CMLAPI void CMLconvertHSVtoHSL (CMLVec3 HSL , const CMLVec3 HSV){
  cmlInternalOneHSVtoHSL(HSL, HSV);
}

CMLAPI void CMLconvertHSLtoHSV (CMLVec3 HSV , const CMLVec3 HSL){
  cmlInternalOneHSLtoHSV(HSV, HSL);
}


CMLAPI void CMLconvertSpectrumtoRadiometricXYZ (CMLVec3 XYZ , const CMLFunction* spectrum, const CMLObserver* observer){
  cmlInternalOneSpectrumtoRadiometricXYZ(XYZ, spectrum, observer);
}

CMLAPI void CMLconvertIlluminationSpectrumtoXYZ (CMLVec3 XYZ , const CMLFunction* spectrum, const CMLWhitepoint* whitepoint){
  cmlInternalOneIlluminationSpectrumtoXYZ(XYZ, spectrum, whitepoint);
}

CMLAPI void CMLconvertRemissionSpectrumtoXYZ (CMLVec3 XYZ, const CMLFunction* spectrum, const CMLWhitepoint* whitepoint){
  cmlInternalOneRemissionSpectrumtoXYZ(XYZ, spectrum, whitepoint);
}




CMLAPI void CMLconvertXYZtoChromaticAdaptedXYZ(CMLVec3 aXYZ, const CMLVec3 XYZ, const CMLMat33 matrix){
  cmlMat33MulVec3(aXYZ, matrix, XYZ);
}




CMLAPI CMLuint32 cmlGetNumChannels(CMLColorType colortype){
  switch(colortype){
  case CML_COLOR_GRAY:  return CML_GRAY_NUMCHANNELS; break;
  case CML_COLOR_XYZ:   return CML_XYZ_NUMCHANNELS; break;
  case CML_COLOR_Yxy:   return CML_Yxy_NUMCHANNELS; break;
  case CML_COLOR_Yuv:   return CML_Yuv_NUMCHANNELS; break;
  case CML_COLOR_Yupvp: return CML_Yupvp_NUMCHANNELS; break;
  case CML_COLOR_Lab:   return CML_Lab_NUMCHANNELS; break;
  case CML_COLOR_Lch:   return CML_Lch_NUMCHANNELS; break;
  case CML_COLOR_Luv:   return CML_Luv_NUMCHANNELS; break;
  case CML_COLOR_RGB:   return CML_RGB_NUMCHANNELS; break;
  case CML_COLOR_YCbCr: return CML_YCbCr_NUMCHANNELS; break;
  case CML_COLOR_HSV:   return CML_HSV_NUMCHANNELS; break;
  case CML_COLOR_HSL:   return CML_HSL_NUMCHANNELS; break;
  case CML_COLOR_CMYK:  return CML_CMYK_NUMCHANNELS; break;
  default:
    #ifndef NDEBUG
    cmlError("cmlGetNumChannels", "Invalid Channeled Color Type.");
    #endif
    return 0;
    break;
  }

}


CMLAPI void cmlGetMinBounds(float* buffer, CMLColorType colortype){
  switch(colortype){
  case CML_COLOR_GRAY:  cmlSet1(buffer, CML_GRAY_MIN); break;
  case CML_COLOR_XYZ:   cmlSet3(buffer, CML_XYZ_X_MIN, CML_XYZ_Y_MIN, CML_XYZ_Z_MIN); break;
  case CML_COLOR_Yxy:   cmlSet3(buffer, CML_Yxy_Y_MIN, CML_Yxy_x_MIN, CML_Yxy_y_MIN); break;
  case CML_COLOR_Yuv:   cmlSet3(buffer, CML_Yuv_Y_MIN, CML_Yuv_u_MIN, CML_Yuv_v_MIN); break;
  case CML_COLOR_Yupvp: cmlSet3(buffer, CML_Yupvp_Y_MIN, CML_Yupvp_up_MIN, CML_Yupvp_vp_MIN); break;
  case CML_COLOR_Lab:   cmlSet3(buffer, CML_Lab_L_MIN, CML_Lab_a_MIN, CML_Lab_b_MIN); break;
  case CML_COLOR_Lch:   cmlSet3(buffer, CML_Lch_L_MIN, CML_Lch_c_MIN, CML_Lch_h_MIN); break;
  case CML_COLOR_Luv:   cmlSet3(buffer, CML_Luv_L_MIN, CML_Luv_u_MIN, CML_Luv_v_MIN); break;
  case CML_COLOR_RGB:   cmlSet3(buffer, CML_RGB_R_MIN, CML_RGB_G_MIN, CML_RGB_B_MIN); break;
  case CML_COLOR_YCbCr: cmlSet3(buffer, CML_YCbCr_Y_MIN, CML_YCbCr_Cb_MIN, CML_YCbCr_Cr_MIN); break;
  case CML_COLOR_HSV:   cmlSet3(buffer, CML_HSV_H_MIN, CML_HSV_S_MIN, CML_HSV_V_MIN); break;
  case CML_COLOR_HSL:   cmlSet3(buffer, CML_HSL_H_MIN, CML_HSL_S_MIN, CML_HSL_L_MIN); break;
  case CML_COLOR_CMYK:  cmlSet4(buffer, CML_CMYK_C_MIN, CML_CMYK_M_MIN, CML_CMYK_Y_MIN, CML_CMYK_K_MIN); break;
  default:
    #ifndef NDEBUG
      cmlError("cmlGetMinBounds", "Invalid Channeled Color Type.");
    #endif
    break;
  }
}


CMLAPI void cmlGetMaxBounds(float* buffer, CMLColorType colortype){
  switch(colortype){
  case CML_COLOR_GRAY:  cmlSet1(buffer, CML_GRAY_MAX); break;
  case CML_COLOR_XYZ:   cmlSet3(buffer, CML_XYZ_X_MAX, CML_XYZ_Y_MAX, CML_XYZ_Z_MAX); break;
  case CML_COLOR_Yxy:   cmlSet3(buffer, CML_Yxy_Y_MAX, CML_Yxy_x_MAX, CML_Yxy_y_MAX); break;
  case CML_COLOR_Yuv:   cmlSet3(buffer, CML_Yuv_Y_MAX, CML_Yuv_u_MAX, CML_Yuv_v_MAX); break;
  case CML_COLOR_Yupvp: cmlSet3(buffer, CML_Yupvp_Y_MAX, CML_Yupvp_up_MAX, CML_Yupvp_vp_MAX); break;
  case CML_COLOR_Lab:   cmlSet3(buffer, CML_Lab_L_MAX, CML_Lab_a_MAX, CML_Lab_b_MAX); break;
  case CML_COLOR_Lch:   cmlSet3(buffer, CML_Lch_L_MAX, CML_Lch_c_MAX, CML_Lch_h_MAX); break;
  case CML_COLOR_Luv:   cmlSet3(buffer, CML_Luv_L_MAX, CML_Luv_u_MAX, CML_Luv_v_MAX); break;
  case CML_COLOR_RGB:   cmlSet3(buffer, CML_RGB_R_MAX, CML_RGB_G_MAX, CML_RGB_B_MAX); break;
  case CML_COLOR_YCbCr: cmlSet3(buffer, CML_YCbCr_Y_MAX, CML_YCbCr_Cb_MAX, CML_YCbCr_Cr_MAX); break;
  case CML_COLOR_HSV:   cmlSet3(buffer, CML_HSV_H_MAX, CML_HSV_S_MAX, CML_HSV_V_MAX); break;
  case CML_COLOR_HSL:   cmlSet3(buffer, CML_HSL_H_MAX, CML_HSL_S_MAX, CML_HSL_L_MAX); break;
  case CML_COLOR_CMYK:  cmlSet4(buffer, CML_CMYK_C_MAX, CML_CMYK_M_MAX, CML_CMYK_Y_MAX, CML_CMYK_K_MAX); break;
  default:
    #ifndef NDEBUG
      cmlError("cmlGetMaxBounds", "Invalid Channeled Color Type.");
    #endif
    break;
  }
}






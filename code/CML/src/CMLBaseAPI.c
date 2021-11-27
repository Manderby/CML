
#include "CML.h"
#include "StateMachine/CMLColorMachineState.h"



CML_API void CMLconvertXYZtoYxy (CMLVec3 yxy , const CMLVec3 xyz, const CMLVec3 whitepointYxy){
  cmlInternalOneXYZtoYxy(yxy, xyz, whitepointYxy);
}

CML_API void CMLconvertYxytoXYZ (CMLVec3 xyz , const CMLVec3 yxy, const CMLVec3 whitepointXYZ){
  cmlInternalOneYxytoXYZ(xyz, yxy, whitepointXYZ);
}

CML_API void CMLconvertYxytoYupvp(CMLVec3 yupvp , const CMLVec3 yxy, const CMLVec3 whitepointYupvp){
  cmlInternalOneYxytoYupvp(yupvp, yxy, whitepointYupvp);
}

CML_API void CMLconvertYupvptoYxy (CMLVec3 yxy , const CMLVec3 yupvp, const CMLVec3 whitepointYxy){
  cmlInternalOneYupvptoYxy(yxy, yupvp, whitepointYxy);
}

CML_API void CMLconvertYupvptoYuv (CMLVec3 yuv , const CMLVec3 yupvp){
  cmlInternalOneYupvptoYuv(yuv, yupvp);
}

CML_API void CMLconvertYuvtoYupvp (CMLVec3 yupvp , const CMLVec3 yuv){
  cmlInternalOneYuvtoYupvp(yupvp, yuv);
}

CML_API void CMLconvertYupvptoLuv (CMLVec3 luv , const CMLVec3 yupvp, const CMLVec3 whitepointYupvp){
  CMLFunction* lineartoLStarResponse = CMLcreateYToLStarResponse();
  cmlInternalOneYupvptoLuv(luv, yupvp, whitepointYupvp, lineartoLStarResponse);
  cmlReleaseFunction(lineartoLStarResponse);
}

CML_API void CMLconvertLuvtoYupvp (CMLVec3 yupvp , const CMLVec3 luv, const CMLVec3 whitepointYupvp){
  CMLFunction* LStartoLinearResponse = CMLcreateLStarToYResponse();
  cmlInternalOneLuvtoYupvp(yupvp, luv, whitepointYupvp, LStartoLinearResponse);
  cmlReleaseFunction(LStartoLinearResponse);
}

CML_API void CMLconvertXYZtoLab(CMLVec3 lab , const CMLVec3 xyz , const CMLVec3 whitepointXYZ){
  CMLFunction* lineartoLStarResponse = CMLcreateYToLStarResponse();
  CMLVec3 inverseWhitepointXYZ = {cmlInverse(whitepointXYZ[0]), cmlInverse(whitepointXYZ[1]), cmlInverse(whitepointXYZ[2])};
  cmlInternalOneXYZtoCIELAB(lab, xyz, inverseWhitepointXYZ, lineartoLStarResponse);
  cmlReleaseFunction(lineartoLStarResponse);
}

CML_API void CMLconvertLabtoXYZ(CMLVec3 xyz , const CMLVec3 lab , const CMLVec3 whitepointXYZ){
  CMLFunction* LStartoLinearResponse = CMLcreateLStarToYResponse();
  cmlInternalOneCIELABtoXYZ(xyz, lab, whitepointXYZ, LStartoLinearResponse);
  cmlReleaseFunction(LStartoLinearResponse);
}

CML_API void CMLconvertLabtoLch (CMLVec3 lch , const CMLVec3 lab ){
  cmlInternalOneLabtoLch(lch, lab);
}

CML_API void CMLconvertLchtoLab (CMLVec3 lab , const CMLVec3 lch ){
  cmlInternalOneLchtoLab(lab, lch);
}

CML_API void CMLconvertXYZtoRGB (CMLVec3 rgb , const CMLVec3 xyz, const CMLMat33 XYZtoRGBmatrix, const CMLFunction* LineartoRResponse, const CMLFunction* LineartoGResponse, const CMLFunction* LineartoBResponse){
  cmlInternalOneXYZtoRGB(rgb, xyz, XYZtoRGBmatrix, LineartoRResponse, LineartoGResponse, LineartoBResponse);
}

CML_API void CMLconvertRGBtoXYZ (CMLVec3 xyz , const CMLVec3 rgb, const CMLMat33 RGBtoXYZmatrix, const CMLFunction* RtoLinearResponse, const CMLFunction* GtoLinearResponse, const CMLFunction* BtoLinearResponse){
  cmlInternalOneRGBtoXYZ(xyz, rgb, RGBtoXYZmatrix, RtoLinearResponse, GtoLinearResponse, BtoLinearResponse);
}

CML_API void CMLconvertRGBtoYCbCr (CMLVec3 ycbcr , const CMLVec3 rgb, const CMLVec3 redprimaryYxy, const CMLVec3 blueprimaryYxy, const CMLVec3 whitepointXYZ){
  CMLVec3 inversewhitepointXYZ;
  cmlSet3(inversewhitepointXYZ, cmlInverse(whitepointXYZ[0]), cmlInverse(whitepointXYZ[1]), cmlInverse(whitepointXYZ[2]));
  cmlInternalOneRGBtoYCbCr(ycbcr, rgb, redprimaryYxy, blueprimaryYxy, inversewhitepointXYZ);
}

CML_API void CMLconvertYCbCrtoRGB (CMLVec3 rgb , const CMLVec3 ycbcr, const CMLVec3 redprimaryYxy, const CMLVec3 blueprimaryYxy, const CMLVec3 whitepointXYZ){
  CMLVec3 inversewhitepointXYZ;
  cmlSet3(inversewhitepointXYZ, cmlInverse(whitepointXYZ[0]), cmlInverse(whitepointXYZ[1]), cmlInverse(whitepointXYZ[2]));
  cmlInternalOneYCbCrtoRGB(rgb, ycbcr, redprimaryYxy, blueprimaryYxy, inversewhitepointXYZ);
}

CML_API void CMLconvertRGBtoHSV (CMLVec3 hsv , const CMLVec3 rgb){
  cmlInternalOneRGBtoHSV(hsv, rgb);
}

CML_API void CMLconvertHSVtoRGB (CMLVec3 rgb , const CMLVec3 hsv){
  cmlInternalOneHSVtoRGB(rgb, hsv);
}

CML_API void CMLconvertHSVtoHSL (CMLVec3 hsl , const CMLVec3 hsv){
  cmlInternalOneHSVtoHSL(hsl, hsv);
}

CML_API void CMLconvertHSLtoHSV (CMLVec3 hsv , const CMLVec3 hsl){
  cmlInternalOneHSLtoHSV(hsv, hsl);
}


CML_API void CMLconvertIlluminationSpectrumtoXYZ (CMLVec3 xyz , const CMLFunction* specIll, const CMLObserver* observer){
  cmlInternalOneIlluminationSpectrumtoXYZ(xyz, specIll, observer);
}

CML_API void CMLconvertRemissionSpectrumtoXYZ (CMLVec3 xyz, const CMLFunction* specRem, const CMLFunction* specIll, const CMLObserver* observer){
  cmlInternalOneRemissionSpectrumtoXYZ(xyz, specRem, specIll, observer);
}




CML_API void CMLconvertXYZtoChromaticAdaptedXYZ(CMLVec3 adaptxyz, const CMLVec3 xyz, const CMLMat33 matrix){
  cmlMat33MulVec3(adaptxyz, matrix, xyz);
}




CML_API CMLuint32 CMLgetNumChannels(CMLColorType colorType){
  switch(colorType){
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
    cmlError("Invalid Channeled Color Type.");
    #endif
    return 0;
    break;
  }

}


CML_API void CMLgetMinBounds(float* buffer, CMLColorType colorType){
  switch(colorType){
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
      cmlError("Invalid Channeled Color Type.");
    #endif
    break;
  }
}


CML_API void CMLgetMaxBounds(float* buffer, CMLColorType colorType){
  switch(colorType){
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
      cmlError("Invalid Channeled Color Type.");
    #endif
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

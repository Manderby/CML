
#include "../CML.h"
#include "CMLColorMachineState.h"



CML_DEF void cmlConvertXYZToYxy(CMLVec3 yxy, const CMLVec3 xyz, const CMLVec3 whitePointYxy){
  cml_OneXYZToYxy(yxy, xyz, whitePointYxy);
}

CML_DEF void cmlConvertYxyToXYZ(CMLVec3 xyz, const CMLVec3 yxy, const CMLVec3 whitePointXYZ){
  cml_OneYxyToXYZ(xyz, yxy, whitePointXYZ);
}

CML_DEF void cmlConvertYxyToYupvp(CMLVec3 yupvp, const CMLVec3 yxy, const CMLVec3 whitePointYupvp){
  cml_OneYxyToYupvp(yupvp, yxy, whitePointYupvp);
}

CML_DEF void cmlConvertYupvpToYxy(CMLVec3 yxy, const CMLVec3 yupvp, const CMLVec3 whitePointYxy){
  cml_OneYupvpToYxy(yxy, yupvp, whitePointYxy);
}

CML_DEF void cmlConvertYupvpToYuv(CMLVec3 yuv, const CMLVec3 yupvp){
  cml_OneYupvpToYuv(yuv, yupvp);
}

CML_DEF void cmlConvertYuvToYupvp(CMLVec3 yupvp, const CMLVec3 yuv){
  cml_OneYuvToYupvp(yupvp, yuv);
}

CML_DEF void cmlConvertYupvpToLuv(CMLVec3 luv, const CMLVec3 yupvp, const CMLVec3 whitePointYupvp){
  CMLFunction* linearToLStarResponse = cmlCreateYToLStarResponse();
  cml_OneYupvpToLuv(luv, yupvp, whitePointYupvp, linearToLStarResponse);
  cmlReleaseFunction(linearToLStarResponse);
}

CML_DEF void cmlConvertLuvToYupvp(CMLVec3 yupvp, const CMLVec3 luv, const CMLVec3 whitePointYupvp){
  CMLFunction* LStarToLinearResponse = cmlCreateLStarToYResponse();
  cml_OneLuvToYupvp(yupvp, luv, whitePointYupvp, LStarToLinearResponse);
  cmlReleaseFunction(LStarToLinearResponse);
}

CML_DEF void cmlConvertXYZToLab(CMLVec3 lab, const CMLVec3 xyz, const CMLVec3 whitePointXYZ){
  CMLFunction* linearToLStarResponse = cmlCreateYToLStarResponse();
  CMLVec3 inverseWhitePointXYZ = {cmlInverse(whitePointXYZ[0]), cmlInverse(whitePointXYZ[1]), cmlInverse(whitePointXYZ[2])};
  cml_OneXYZToCIELAB(lab, xyz, inverseWhitePointXYZ, linearToLStarResponse);
  cmlReleaseFunction(linearToLStarResponse);
}

CML_DEF void cmlConvertLabToXYZ(CMLVec3 xyz, const CMLVec3 lab, const CMLVec3 whitePointXYZ){
  CMLFunction* LStarToLinearResponse = cmlCreateLStarToYResponse();
  cml_OneCIELABToXYZ(xyz, lab, whitePointXYZ, LStarToLinearResponse);
  cmlReleaseFunction(LStarToLinearResponse);
}

CML_DEF void cmlConvertLabToLch(CMLVec3 lch, const CMLVec3 lab){
  cml_OneLabToLch(lch, lab);
}

CML_DEF void cmlConvertLchToLab(CMLVec3 lab, const CMLVec3 lch){
  cml_OneLchToLab(lab, lch);
}

CML_DEF void cmlConvertXYZToRGB(CMLVec3 rgb, const CMLVec3 xyz, const CMLMat33 XYZToRGBMatrix, const CMLFunction* linearToRResponse, const CMLFunction* linearToGResponse, const CMLFunction* linearToBResponse){
  cml_OneXYZToRGB(rgb, xyz, XYZToRGBMatrix, linearToRResponse, linearToGResponse, linearToBResponse);
}

CML_DEF void cmlConvertRGBToXYZ(CMLVec3 xyz, const CMLVec3 rgb, const CMLMat33 RGBToXYZMatrix, const CMLFunction* RToLinearResponse, const CMLFunction* GToLinearResponse, const CMLFunction* BToLinearResponse){
  cml_OneRGBToXYZ(xyz, rgb, RGBToXYZMatrix, RToLinearResponse, GToLinearResponse, BToLinearResponse);
}

CML_DEF void cmlConvertRGBToYCbCr(CMLVec3 ycbcr, const CMLVec3 rgb, const CMLVec3 redPrimaryYxy, const CMLVec3 bluePrimaryYxy, const CMLVec3 whitePointXYZ){
  CMLVec3 inverseWhitePointXYZ;
  cmlSet3(inverseWhitePointXYZ, cmlInverse(whitePointXYZ[0]), cmlInverse(whitePointXYZ[1]), cmlInverse(whitePointXYZ[2]));
  cml_OneRGBToYCbCr(ycbcr, rgb, redPrimaryYxy, bluePrimaryYxy, inverseWhitePointXYZ);
}

CML_DEF void cmlConvertYCbCrToRGB(CMLVec3 rgb, const CMLVec3 ycbcr, const CMLVec3 redPrimaryYxy, const CMLVec3 bluePrimaryYxy, const CMLVec3 whitePointXYZ){
  CMLVec3 inverseWhitePointXYZ;
  cmlSet3(inverseWhitePointXYZ, cmlInverse(whitePointXYZ[0]), cmlInverse(whitePointXYZ[1]), cmlInverse(whitePointXYZ[2]));
  cml_OneYCbCrToRGB(rgb, ycbcr, redPrimaryYxy, bluePrimaryYxy, inverseWhitePointXYZ);
}

CML_DEF void cmlConvertRGBToHSV(CMLVec3 hsv, const CMLVec3 rgb){
  cml_OneRGBToHSV(hsv, rgb);
}

CML_DEF void cmlConvertHSVToRGB(CMLVec3 rgb, const CMLVec3 hsv){
  cml_OneHSVToRGB(rgb, hsv);
}

CML_DEF void cmlConvertHSVToHSL(CMLVec3 hsl, const CMLVec3 hsv){
  cml_OneHSVToHSL(hsl, hsv);
}

CML_DEF void cmlConvertHSLToHSV(CMLVec3 hsv, const CMLVec3 hsl){
  cml_OneHSLToHSV(hsv, hsl);
}

CML_DEF void cmlConvertIlluminationSpectrumToXYZ(CMLVec3 xyz, const CMLFunction* specIll, const CMLObserver* observer){
  cml_OneIlluminationSpectrumToXYZ(xyz, specIll, observer);
}

CML_DEF void cmlConvertRemissionSpectrumToXYZ(CMLVec3 xyz, const CMLFunction* specRem, const CMLFunction* specIll, const CMLObserver* observer){
  cml_OneRemissionSpectrumToXYZ(xyz, specRem, specIll, observer);
}

CML_DEF void cmlConvertXYZToChromaticAdaptedXYZ(CMLVec3 adaptXYZ, const CMLVec3 xyz, const CMLMat33 matrix){
  cmlMulMat33Vec3(adaptXYZ, matrix, xyz);
}



CML_DEF size_t cmlGetNumChannels(CMLColorType colorType){
  switch(colorType){
  case CML_COLOR_GRAY:  return CML_GRAY_NUMCHANNELS;  break;
  case CML_COLOR_XYZ:   return CML_XYZ_NUMCHANNELS;   break;
  case CML_COLOR_Yxy:   return CML_Yxy_NUMCHANNELS;   break;
  case CML_COLOR_Yuv:   return CML_Yuv_NUMCHANNELS;   break;
  case CML_COLOR_Yupvp: return CML_Yupvp_NUMCHANNELS; break;
  case CML_COLOR_Lab:   return CML_Lab_NUMCHANNELS;   break;
  case CML_COLOR_Lch:   return CML_Lch_NUMCHANNELS;   break;
  case CML_COLOR_Luv:   return CML_Luv_NUMCHANNELS;   break;
  case CML_COLOR_RGB:   return CML_RGB_NUMCHANNELS;   break;
  case CML_COLOR_YCbCr: return CML_YCbCr_NUMCHANNELS; break;
  case CML_COLOR_HSV:   return CML_HSV_NUMCHANNELS;   break;
  case CML_COLOR_HSL:   return CML_HSL_NUMCHANNELS;   break;
  case CML_COLOR_CMYK:  return CML_CMYK_NUMCHANNELS;  break;
  default:
    #if CML_DEBUG
      cmlError("Invalid channeled color type.");
    #endif
    return 0;
    break;
  }
}



CML_DEF void cmlGetMinBounds(float* buffer, CMLColorType colorType){
  switch(colorType){
  case CML_COLOR_GRAY:  cmlSet1(buffer, CML_GRAY_MIN); break;
  case CML_COLOR_XYZ:   cmlSet3(buffer, CML_XYZ_X_MIN,   CML_XYZ_Y_MIN,    CML_XYZ_Z_MIN);    break;
  case CML_COLOR_Yxy:   cmlSet3(buffer, CML_Yxy_Y_MIN,   CML_Yxy_x_MIN,    CML_Yxy_y_MIN);    break;
  case CML_COLOR_Yuv:   cmlSet3(buffer, CML_Yuv_Y_MIN,   CML_Yuv_u_MIN,    CML_Yuv_v_MIN);    break;
  case CML_COLOR_Yupvp: cmlSet3(buffer, CML_Yupvp_Y_MIN, CML_Yupvp_up_MIN, CML_Yupvp_vp_MIN); break;
  case CML_COLOR_Lab:   cmlSet3(buffer, CML_Lab_L_MIN,   CML_Lab_a_MIN,    CML_Lab_b_MIN);    break;
  case CML_COLOR_Lch:   cmlSet3(buffer, CML_Lch_L_MIN,   CML_Lch_c_MIN,    CML_Lch_h_MIN);    break;
  case CML_COLOR_Luv:   cmlSet3(buffer, CML_Luv_L_MIN,   CML_Luv_u_MIN,    CML_Luv_v_MIN);    break;
  case CML_COLOR_RGB:   cmlSet3(buffer, CML_RGB_R_MIN,   CML_RGB_G_MIN,    CML_RGB_B_MIN);    break;
  case CML_COLOR_YCbCr: cmlSet3(buffer, CML_YCbCr_Y_MIN, CML_YCbCr_Cb_MIN, CML_YCbCr_Cr_MIN); break;
  case CML_COLOR_HSV:   cmlSet3(buffer, CML_HSV_H_MIN,   CML_HSV_S_MIN,    CML_HSV_V_MIN);    break;
  case CML_COLOR_HSL:   cmlSet3(buffer, CML_HSL_H_MIN,   CML_HSL_S_MIN,    CML_HSL_L_MIN);    break;
  case CML_COLOR_CMYK:  cmlSet4(buffer, CML_CMYK_C_MIN,  CML_CMYK_M_MIN,   CML_CMYK_Y_MIN, CML_CMYK_K_MIN); break;
  default:
    #if CML_DEBUG
      cmlError("Invalid Channeled Color Type.");
    #endif
    break;
  }
}



CML_DEF void cmlGetMaxBounds(float* buffer, CMLColorType colorType){
  switch(colorType){
  case CML_COLOR_GRAY:  cmlSet1(buffer, CML_GRAY_MAX); break;
  case CML_COLOR_XYZ:   cmlSet3(buffer, CML_XYZ_X_MAX,   CML_XYZ_Y_MAX,    CML_XYZ_Z_MAX);    break;
  case CML_COLOR_Yxy:   cmlSet3(buffer, CML_Yxy_Y_MAX,   CML_Yxy_x_MAX,    CML_Yxy_y_MAX);    break;
  case CML_COLOR_Yuv:   cmlSet3(buffer, CML_Yuv_Y_MAX,   CML_Yuv_u_MAX,    CML_Yuv_v_MAX);    break;
  case CML_COLOR_Yupvp: cmlSet3(buffer, CML_Yupvp_Y_MAX, CML_Yupvp_up_MAX, CML_Yupvp_vp_MAX); break;
  case CML_COLOR_Lab:   cmlSet3(buffer, CML_Lab_L_MAX,   CML_Lab_a_MAX,    CML_Lab_b_MAX);    break;
  case CML_COLOR_Lch:   cmlSet3(buffer, CML_Lch_L_MAX,   CML_Lch_c_MAX,    CML_Lch_h_MAX);    break;
  case CML_COLOR_Luv:   cmlSet3(buffer, CML_Luv_L_MAX,   CML_Luv_u_MAX,    CML_Luv_v_MAX);    break;
  case CML_COLOR_RGB:   cmlSet3(buffer, CML_RGB_R_MAX,   CML_RGB_G_MAX,    CML_RGB_B_MAX);    break;
  case CML_COLOR_YCbCr: cmlSet3(buffer, CML_YCbCr_Y_MAX, CML_YCbCr_Cb_MAX, CML_YCbCr_Cr_MAX); break;
  case CML_COLOR_HSV:   cmlSet3(buffer, CML_HSV_H_MAX,   CML_HSV_S_MAX,    CML_HSV_V_MAX);    break;
  case CML_COLOR_HSL:   cmlSet3(buffer, CML_HSL_H_MAX,   CML_HSL_S_MAX,    CML_HSL_L_MAX);    break;
  case CML_COLOR_CMYK:  cmlSet4(buffer, CML_CMYK_C_MAX,  CML_CMYK_M_MAX,   CML_CMYK_Y_MAX, CML_CMYK_K_MAX); break;
  default:
    #if CML_DEBUG
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

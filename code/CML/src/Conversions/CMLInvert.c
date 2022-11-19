
#include "../CML.h"
#include "../Internal/CMLColorMachineState.h"



CML_HIDEF void cml_InvertOneCMYK(float* cmyk){
  cmyk[0] = CML_CMYK_C_MAX - cmyk[0];
  cmyk[1] = CML_CMYK_M_MAX - cmyk[1];
  cmyk[2] = CML_CMYK_Y_MAX - cmyk[2];
  cmyk[3] = CML_CMYK_K_MAX - cmyk[3];
}

CML_HIDEF void cml_InvertOneGray(float* gray){
  gray[0] = CML_GRAY_MAX - gray[0];
}

CML_HIDEF void cml_InvertOneHSL(float* hsl){
  hsl[0] = hsl[0] - 180.f;
  if(hsl[0] < 0.f){hsl[0] += 360.f;}
  hsl[1] = hsl[1];
  hsl[2] = CML_HSL_L_MAX - hsl[2];
}

CML_HIDEF void cml_InvertOneHSV(float* hsv){
  hsv[0] = hsv[0] - 180.f;
  if(hsv[0] < 0.f){hsv[0] += 360.f;}
  hsv[1] = hsv[1];
  hsv[2] = CML_HSV_V_MAX - hsv[2];
}

CML_HIDEF void cml_InvertOneLab(float* lab){
  lab[0] = CML_Lab_L_MAX - lab[0];
  lab[1] = -lab[1];
  lab[2] = -lab[2];
}

CML_HIDEF void cml_InvertOneLch(float* lch){
  lch[0] = CML_Lch_L_MAX - lch[0];
  lch[1] = lch[1];
  lch[2] = lch[2] - 180.f;
  if(lch[2] < 0.f){lch[2] += 360.f;}
}

CML_HIDEF void cml_InvertOneLuv(float* luv){
  luv[0] = CML_Luv_L_MAX - luv[0];
  luv[1] = -luv[1];
  luv[2] = -luv[2];
}

CML_HIDEF void cml_InvertOneRGB(float* rgb){
  rgb[0] = CML_RGB_R_MAX - rgb[0];
  rgb[1] = CML_RGB_G_MAX - rgb[1];
  rgb[2] = CML_RGB_B_MAX - rgb[2];
}

CML_HIDEF void cml_InvertOneUVW(float* uvw){
  uvw[0] = CML_UVW_U_MAX - uvw[0];
  uvw[1] = CML_UVW_V_MAX - uvw[1];
  uvw[2] = CML_UVW_W_MAX - uvw[2];
}

CML_HIDEF void cml_InvertOneXYZ(float* xyz){
  xyz[0] = CML_XYZ_X_MAX - xyz[0];
  xyz[1] = CML_XYZ_Y_MAX - xyz[1];
  xyz[2] = CML_XYZ_Z_MAX - xyz[2];
}

CML_HIDEF void cml_InvertOneYCbCr(float* Ycbcr){
  Ycbcr[0] = CML_YCbCr_Y_MAX - Ycbcr[0];
  Ycbcr[1] = -Ycbcr[1];
  Ycbcr[2] = -Ycbcr[2];
}

CML_HIDEF void cml_InvertOneYcd(float* ycd){
  ycd[0] = CML_Ycd_Y_MAX - ycd[0];
  ycd[1] = CML_Ycd_c_MAX - ycd[1];
  ycd[2] = CML_Ycd_d_MAX - ycd[2];
}

CML_HIDEF void cml_InvertOneYupvp(float* yupvp){
  yupvp[0] = CML_Yupvp_Y_MAX  - yupvp[0];
  yupvp[1] = CML_Yupvp_up_MAX - yupvp[1];
  yupvp[2] = CML_Yupvp_vp_MAX - yupvp[2];
}

CML_HIDEF void cml_InvertOneYuv(float* yuv){
  yuv[0] = CML_Yuv_Y_MAX - yuv[0];
  yuv[1] = CML_Yuv_u_MAX - yuv[1];
  yuv[2] = CML_Yuv_v_MAX - yuv[2];
}

CML_HIDEF void cml_InvertOneYxy(float* yxy){
  yxy[0] = CML_Yxy_Y_MAX - yxy[0];
  yxy[1] = CML_Yxy_x_MAX - yxy[1];
  yxy[2] = CML_Yxy_y_MAX - yxy[2];
}





CML_DEF void cmlInvertCMYK(CMLInputOutput cmyk, size_t count){
  float* inout = (float*)cmyk;
  for(size_t i = 0; i < count; ++i){
    cml_InvertOneCMYK(inout);
    inout += CML_CMYK_CHANNEL_COUNT;
  }
}

CML_DEF void cmlInvertGray(CMLInputOutput gray, size_t count){
  float* inout = (float*)gray;
  for(size_t i = 0; i < count; ++i){
    cml_InvertOneGray(inout);
    inout += CML_GRAY_CHANNEL_COUNT;
  }
}

CML_DEF void cmlInvertHSL(CMLInputOutput hsl, size_t count){
  float* inout = (float*)hsl;
  for(size_t i = 0; i < count; ++i){
    cml_InvertOneHSL(inout);
    inout += CML_HSL_CHANNEL_COUNT;
  }
}

CML_DEF void cmlInvertHSV(CMLInputOutput hsv, size_t count){
  float* inout = (float*)hsv;
  for(size_t i = 0; i < count; ++i){
    cml_InvertOneHSV(inout);
    inout += CML_HSV_CHANNEL_COUNT;
  }
}

CML_DEF void cmlInvertLab(CMLInputOutput lab, size_t count){
  float* inout = (float*)lab;
  for(size_t i = 0; i < count; ++i){
    cml_InvertOneLab(inout);
    inout += CML_Lab_CHANNEL_COUNT;
  }
}

CML_DEF void cmlInvertLch(CMLInputOutput lch, size_t count){
  float* inout = (float*)lch;
  for(size_t i = 0; i < count; ++i){
    cml_InvertOneLch(inout);
    inout += CML_Lch_CHANNEL_COUNT;
  }
}

CML_DEF void cmlInvertLuv(CMLInputOutput luv, size_t count){
  float* inout = (float*)luv;
  for(size_t i = 0; i < count; ++i){
    cml_InvertOneLuv(inout);
    inout += CML_Luv_CHANNEL_COUNT;
  }
}

CML_DEF void cmlInvertRGB(CMLInputOutput rgb, size_t count){
  float* inout = (float*)rgb;
  for(size_t i = 0; i < count; ++i){
    cml_InvertOneRGB(inout);
    inout += CML_RGB_CHANNEL_COUNT;
  }
}

CML_DEF void cmlInvertUVW(CMLInputOutput uvw, size_t count){
  float* inout = (float*)uvw;
  for(size_t i = 0; i < count; ++i){
    cml_InvertOneUVW(inout);
    inout += CML_UVW_CHANNEL_COUNT;
  }
}

CML_DEF void cmlInvertXYZ(CMLInputOutput xyz, size_t count){
  float* inout = (float*)xyz;
  for(size_t i = 0; i < count; ++i){
    cml_InvertOneXYZ(inout);
    inout += CML_XYZ_CHANNEL_COUNT;
  }
}

CML_DEF void cmlInvertYCbCr(CMLInputOutput Ycbcr, size_t count){
  float* inout = (float*)Ycbcr;
  for(size_t i = 0; i < count; ++i){
    cml_InvertOneYCbCr(inout);
    inout += CML_YCbCr_CHANNEL_COUNT;
  }
}

CML_DEF void cmlInvertYcd(CMLInputOutput ycd, size_t count){
  float* inout = (float*)ycd;
  for(size_t i = 0; i < count; ++i){
    cml_InvertOneYcd(inout);
    inout += CML_Ycd_CHANNEL_COUNT;
  }
}

CML_DEF void cmlInvertYupvp(CMLInputOutput yupvp, size_t count){
  float* inout = (float*)yupvp;
  for(size_t i = 0; i < count; ++i){
    cml_InvertOneYupvp(inout);
    inout += CML_Yupvp_CHANNEL_COUNT;
  }
}

CML_DEF void cmlInvertYuv(CMLInputOutput yuv, size_t count){
  float* inout = (float*)yuv;
  for(size_t i = 0; i < count; ++i){
    cml_InvertOneYuv(inout);
    inout += CML_Yuv_CHANNEL_COUNT;
  }
}

CML_DEF void cmlInvertYxy(CMLInputOutput yxy, size_t count){
  float* inout = (float*)yxy;
  for(size_t i = 0; i < count; ++i){
    cml_InvertOneYxy(inout);
    inout += CML_Yxy_CHANNEL_COUNT;
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

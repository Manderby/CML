
#include "../CML.h"
#include "../Internal/CMLColorMachineState.h"


CML_HIDEF CMLBool cml_ClampToRange(float* x, float a, float b){
  if(*x < a){*x = a; return CML_FALSE;}
  if(*x > b){*x = b; return CML_FALSE;}
  return CML_TRUE;
}


CML_HIDEF void cml_ClampGray(float* gray){
  cml_ClampToRange(&(gray[0]), CML_GRAY_MIN, CML_GRAY_MAX);
}

CML_HIDEF void cml_ClampXYZ(float* xyz){
  cml_ClampToRange(&(xyz[0]), CML_XYZ_X_MIN, CML_XYZ_X_MAX);
  cml_ClampToRange(&(xyz[1]), CML_XYZ_Y_MIN, CML_XYZ_Y_MAX);
  cml_ClampToRange(&(xyz[2]), CML_XYZ_Z_MIN, CML_XYZ_Z_MAX);
}

CML_HIDEF void cml_ClampYxy(float* yxy){
  cml_ClampToRange(&(yxy[0]), CML_Yxy_Y_MIN, CML_Yxy_Y_MAX);
  cml_ClampToRange(&(yxy[1]), CML_Yxy_x_MIN, CML_Yxy_x_MAX);
  cml_ClampToRange(&(yxy[2]), CML_Yxy_y_MIN, CML_Yxy_y_MAX);
}

CML_HIDEF void cml_ClampYuv(float* yuv){
  cml_ClampToRange(&(yuv[0]), CML_Yuv_Y_MIN, CML_Yuv_Y_MAX);
  cml_ClampToRange(&(yuv[1]), CML_Yuv_u_MIN, CML_Yuv_u_MAX);
  cml_ClampToRange(&(yuv[2]), CML_Yuv_v_MIN, CML_Yuv_v_MAX);
}

CML_HIDEF void cml_ClampYupvp(float* yuv){
  cml_ClampToRange(&(yuv[0]), CML_Yupvp_Y_MIN, CML_Yupvp_Y_MAX);
  cml_ClampToRange(&(yuv[1]), CML_Yupvp_up_MIN, CML_Yupvp_up_MAX);
  cml_ClampToRange(&(yuv[2]), CML_Yupvp_vp_MIN, CML_Yupvp_vp_MAX);
}

CML_HIDEF void cml_ClampLab(float* lab){
  cml_ClampToRange(&(lab[0]), CML_Lab_L_MIN, CML_Lab_L_MAX);
  cml_ClampToRange(&(lab[1]), CML_Lab_a_MIN, CML_Lab_a_MAX);
  cml_ClampToRange(&(lab[2]), CML_Lab_b_MIN, CML_Lab_b_MAX);
}

CML_HIDEF void cml_ClampLch(float* lch){
  int fullangles;
  cml_ClampToRange(&(lch[0]), CML_Lch_L_MIN, CML_Lch_L_MAX);
  cml_ClampToRange(&(lch[1]), CML_Lch_c_MIN, CML_Lch_c_MAX);
  fullangles = (int)floorf(lch[2] / CML_Lch_h_MAX);
  lch[2] -= fullangles * CML_Lch_h_MAX;
}

CML_HIDEF void cml_ClampLuv(float* luv){
  cml_ClampToRange(&(luv[0]), CML_Luv_L_MIN, CML_Luv_L_MAX);
  cml_ClampToRange(&(luv[1]), CML_Luv_u_MIN, CML_Luv_u_MAX);
  cml_ClampToRange(&(luv[2]), CML_Luv_v_MIN, CML_Luv_v_MAX);
}

CML_HIDEF void cml_ClampRGB(float* rgb){
  cml_ClampToRange(&(rgb[0]), CML_RGB_R_MIN, CML_RGB_R_MAX);
  cml_ClampToRange(&(rgb[1]), CML_RGB_G_MIN, CML_RGB_G_MAX);
  cml_ClampToRange(&(rgb[2]), CML_RGB_B_MIN, CML_RGB_B_MAX);
}

CML_HIDEF void cml_ClampYCbCr(float* ycbcr){
  cml_ClampToRange(&(ycbcr[0]), CML_YCbCr_Y_MIN, CML_YCbCr_Y_MAX);
  cml_ClampToRange(&(ycbcr[1]), CML_YCbCr_Cb_MIN, CML_YCbCr_Cb_MAX);
  cml_ClampToRange(&(ycbcr[2]), CML_YCbCr_Cr_MIN, CML_YCbCr_Cr_MAX);
}

CML_HIDEF void cml_ClampHSV(float* hsv){
  int fullangles = (int)floorf(hsv[0] / CML_HSV_H_MAX);
  hsv[0] -= fullangles * CML_HSV_H_MAX;
  cml_ClampToRange(&(hsv[1]), CML_HSV_S_MIN, CML_HSV_S_MAX);
  cml_ClampToRange(&(hsv[2]), CML_HSV_V_MIN, CML_HSV_V_MAX);
}

CML_HIDEF void cml_ClampHSL(float* hsl){
  int fullangles = (int)floorf(hsl[0] / CML_HSL_H_MAX);
  hsl[0] -= fullangles * CML_HSL_H_MAX;
  cml_ClampToRange(&(hsl[1]), CML_HSL_S_MIN, CML_HSL_S_MAX);
  cml_ClampToRange(&(hsl[2]), CML_HSL_L_MIN, CML_HSL_L_MAX);
}

CML_HIDEF void cml_ClampCMYK(float* cmyk){
  cml_ClampToRange(&(cmyk[0]), CML_CMYK_C_MIN, CML_CMYK_C_MAX);
  cml_ClampToRange(&(cmyk[1]), CML_CMYK_M_MIN, CML_CMYK_M_MAX);
  cml_ClampToRange(&(cmyk[2]), CML_CMYK_Y_MIN, CML_CMYK_Y_MAX);
  cml_ClampToRange(&(cmyk[3]), CML_CMYK_K_MIN, CML_CMYK_K_MAX);
}



CML_DEF void cmlClampGray(CMLInputOutput gray, size_t count){
  float* inout = (float*)gray;
  for(size_t i = 0; i < count; i++){
    cml_ClampGray(inout);
    inout++;
  }
}

CML_DEF void cmlClampXYZ(CMLInputOutput xyz, size_t count){
  float* inout = (float*)xyz;
  for(size_t i = 0; i < count; i++){
    cml_ClampXYZ(inout);
    inout += 3;
  }
}

CML_DEF void cmlClampYxy(CMLInputOutput yxy, size_t count){
  float* inout = (float*)yxy;
  for(size_t i = 0; i < count; i++){
    cml_ClampYxy(inout);
    inout += 3;
  }
}

CML_DEF void cmlClampYuv(CMLInputOutput yuv, size_t count){
  float* inout = (float*)yuv;
  for(size_t i = 0; i < count; i++){
    cml_ClampYuv(inout);
    inout += 3;
  }
}

CML_DEF void cmlClampYupvp(CMLInputOutput yupvp, size_t count){
  float* inout = (float*)yupvp;
  for(size_t i = 0; i < count; i++){
    cml_ClampYupvp(inout);
    inout += 3;
  }
}

CML_DEF void cmlClampLab(CMLInputOutput lab, size_t count){
  float* inout = (float*)lab;
  for(size_t i = 0; i < count; i++){
    cml_ClampLab(inout);
    inout += 3;
  }
}

CML_DEF void cmlClampLch(CMLInputOutput lch, size_t count){
  float* inout = (float*)lch;
  for(size_t i = 0; i < count; i++){
    cml_ClampLch(inout);
    inout += 3;
  }
}

CML_DEF void cmlClampLuv(CMLInputOutput luv, size_t count){
  float* inout = (float*)luv;
  for(size_t i = 0; i < count; i++){
    cml_ClampLuv(inout);
    inout += 3;
  }
}

CML_DEF void cmlClampRGB(CMLInputOutput rgb, size_t count){
  float* inout = (float*)rgb;
  for(size_t i = 0; i < count; i++){
    cml_ClampRGB(inout);
    inout += 3;
  }
}

CML_DEF void cmlClampYCbCr(CMLInputOutput ycbcr, size_t count){
  float* inout = (float*)ycbcr;
  for(size_t i = 0; i < count; i++){
    cml_ClampYCbCr(inout);
    inout += 3;
  }
}

CML_DEF void cmlClampHSV(CMLInputOutput hsv, size_t count){
  float* inout = (float*)hsv;
  for(size_t i = 0; i < count; i++){
    cml_ClampHSV(inout);
    inout += 3;
  }
}

CML_DEF void cmlClampHSL(CMLInputOutput hsl, size_t count){
  float* inout = (float*)hsl;
  for(size_t i = 0; i < count; i++){
    cml_ClampHSL(inout);
    inout += 3;
  }
}

CML_DEF void cmlClampCMYK(CMLInputOutput cmyk, size_t count){
  float* inout = (float*)cmyk;
  for(size_t i = 0; i < count; i++){
    cml_ClampCMYK(inout);
    inout += 4;
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

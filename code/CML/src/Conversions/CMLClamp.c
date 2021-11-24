
#include "../CML.h"
#include "../StateMachine/CMLColorMachineState.h"


CML_HIDDEN CML_INLINE static CMLBool CMLClampToRange(float* x, float a, float b){
  if(*x<a){*x = a; return CML_FALSE;}
  if(*x>b){*x = b; return CML_FALSE;}
  return CML_TRUE;
}


CML_HIDDEN CML_INLINE static void InternalclampGray(float* gray){
  CMLClampToRange(&(gray[0]), CML_GRAY_MIN, CML_GRAY_MAX);
}
CML_HIDDEN CML_INLINE static void InternalclampXYZ(float* xyz){
  CMLClampToRange(&(xyz[0]), CML_XYZ_X_MIN, CML_XYZ_X_MAX);
  CMLClampToRange(&(xyz[1]), CML_XYZ_Y_MIN, CML_XYZ_Y_MAX);
  CMLClampToRange(&(xyz[2]), CML_XYZ_Z_MIN, CML_XYZ_Z_MAX);
}
CML_HIDDEN CML_INLINE static void InternalclampYxy(float* yxy){
  CMLClampToRange(&(yxy[0]), CML_Yxy_Y_MIN, CML_Yxy_Y_MAX);
  CMLClampToRange(&(yxy[1]), CML_Yxy_x_MIN, CML_Yxy_x_MAX);
  CMLClampToRange(&(yxy[2]), CML_Yxy_y_MIN, CML_Yxy_y_MAX);
}
CML_HIDDEN CML_INLINE static void InternalclampYuv(float* yuv){
  CMLClampToRange(&(yuv[0]), CML_Yuv_Y_MIN, CML_Yuv_Y_MAX);
  CMLClampToRange(&(yuv[1]), CML_Yuv_u_MIN, CML_Yuv_u_MAX);
  CMLClampToRange(&(yuv[2]), CML_Yuv_v_MIN, CML_Yuv_v_MAX);
}
CML_HIDDEN CML_INLINE static void InternalclampYupvp(float* yuv){
  CMLClampToRange(&(yuv[0]), CML_Yupvp_Y_MIN, CML_Yupvp_Y_MAX);
  CMLClampToRange(&(yuv[1]), CML_Yupvp_up_MIN, CML_Yupvp_up_MAX);
  CMLClampToRange(&(yuv[2]), CML_Yupvp_vp_MIN, CML_Yupvp_vp_MAX);
}
CML_HIDDEN CML_INLINE static void InternalclampLab(float* lab){
  CMLClampToRange(&(lab[0]), CML_Lab_L_MIN, CML_Lab_L_MAX);
  CMLClampToRange(&(lab[1]), CML_Lab_a_MIN, CML_Lab_a_MAX);
  CMLClampToRange(&(lab[2]), CML_Lab_b_MIN, CML_Lab_b_MAX);
}
CML_HIDDEN CML_INLINE static void InternalclampLch(float* lch){
  CMLint32 fullangles;
  CMLClampToRange(&(lch[0]), CML_Lch_L_MIN, CML_Lch_L_MAX);
  CMLClampToRange(&(lch[1]), CML_Lch_c_MIN, CML_Lch_c_MAX);
  fullangles = (CMLint32)floorf(lch[2] / CML_Lch_h_MAX);
  lch[2] -= fullangles * CML_Lch_h_MAX;
}
CML_HIDDEN CML_INLINE static void InternalclampLuv(float* luv){
  CMLClampToRange(&(luv[0]), CML_Luv_L_MIN, CML_Luv_L_MAX);
  CMLClampToRange(&(luv[1]), CML_Luv_u_MIN, CML_Luv_u_MAX);
  CMLClampToRange(&(luv[2]), CML_Luv_v_MIN, CML_Luv_v_MAX);
}
CML_HIDDEN CML_INLINE static void InternalclampRGB(float* rgb){
  CMLClampToRange(&(rgb[0]), CML_RGB_R_MIN, CML_RGB_R_MAX);
  CMLClampToRange(&(rgb[1]), CML_RGB_G_MIN, CML_RGB_G_MAX);
  CMLClampToRange(&(rgb[2]), CML_RGB_B_MIN, CML_RGB_B_MAX);
}
CML_HIDDEN CML_INLINE static void InternalclampYCbCr(float* ycbcr){
  CMLClampToRange(&(ycbcr[0]), CML_YCbCr_Y_MIN, CML_YCbCr_Y_MAX);
  CMLClampToRange(&(ycbcr[1]), CML_YCbCr_Cb_MIN, CML_YCbCr_Cb_MAX);
  CMLClampToRange(&(ycbcr[2]), CML_YCbCr_Cr_MIN, CML_YCbCr_Cr_MAX);
}
CML_HIDDEN CML_INLINE static void InternalclampHSV(float* hsv){
  CMLint32 fullangles = (CMLint32)floorf(hsv[0] / CML_HSV_H_MAX);
  hsv[0] -= fullangles * CML_HSV_H_MAX;
  CMLClampToRange(&(hsv[1]), CML_HSV_S_MIN, CML_HSV_S_MAX);
  CMLClampToRange(&(hsv[2]), CML_HSV_V_MIN, CML_HSV_V_MAX);
}
CML_HIDDEN CML_INLINE static void InternalclampHSL(float* hsl){
  CMLint32 fullangles = (CMLint32)floorf(hsl[0] / CML_HSL_H_MAX);
  hsl[0] -= fullangles * CML_HSL_H_MAX;
  CMLClampToRange(&(hsl[1]), CML_HSL_S_MIN, CML_HSL_S_MAX);
  CMLClampToRange(&(hsl[2]), CML_HSL_L_MIN, CML_HSL_L_MAX);
}
CML_HIDDEN CML_INLINE static void InternalclampCMYK(float* cmyk){
  CMLClampToRange(&(cmyk[0]), CML_CMYK_C_MIN, CML_CMYK_C_MAX);
  CMLClampToRange(&(cmyk[1]), CML_CMYK_M_MIN, CML_CMYK_M_MAX);
  CMLClampToRange(&(cmyk[2]), CML_CMYK_Y_MIN, CML_CMYK_Y_MAX);
  CMLClampToRange(&(cmyk[3]), CML_CMYK_K_MIN, CML_CMYK_K_MAX);
}


CML_API void CMLclampGray (CMLInputOutput gray , size_t count){
  float* inout = (float*)gray;
  for(size_t i = 0; i < count; i++){
    InternalclampGray (inout);
    inout++;
  }
}
CML_API void CMLclampXYZ  (CMLInputOutput xyz  , size_t count){
  float* inout = (float*)xyz;
  for(size_t i = 0; i < count; i++){
    InternalclampXYZ  (inout);
    inout += 3;
  }
}
CML_API void CMLclampYxy  (CMLInputOutput yxy  , size_t count){
  float* inout = (float*)yxy;
  for(size_t i = 0; i < count; i++){
    InternalclampYxy  (inout);
    inout += 3;
  }
}
CML_API void CMLclampYuv  (CMLInputOutput yuv  , size_t count){
  float* inout = (float*)yuv;
  for(size_t i = 0; i < count; i++){
    InternalclampYuv  (inout);
    inout += 3;
  }
}
CML_API void CMLclampYupvp  (CMLInputOutput yupvp  , size_t count){
  float* inout = (float*)yupvp;
  for(size_t i = 0; i < count; i++){
    InternalclampYupvp  (inout);
    inout += 3;
  }
}
CML_API void CMLclampLab  (CMLInputOutput lab  , size_t count){
  float* inout = (float*)lab;
  for(size_t i = 0; i < count; i++){
    InternalclampLab  (inout);
    inout += 3;
  }
}
CML_API void CMLclampLch  (CMLInputOutput lch  , size_t count){
  float* inout = (float*)lch;
  for(size_t i = 0; i < count; i++){
    InternalclampLch  (inout);
    inout += 3;
  }
}
CML_API void CMLclampLuv  (CMLInputOutput luv  , size_t count){
  float* inout = (float*)luv;
  for(size_t i = 0; i < count; i++){
    InternalclampLuv  (inout);
    inout += 3;
  }
}
CML_API void CMLclampRGB  (CMLInputOutput rgb  , size_t count){
  float* inout = (float*)rgb;
  for(size_t i = 0; i < count; i++){
    InternalclampRGB  (inout);
    inout += 3;
  }
}
CML_API void CMLclampYCbCr(CMLInputOutput ycbcr, size_t count){
  float* inout = (float*)ycbcr;
  for(size_t i = 0; i < count; i++){
    InternalclampYCbCr(inout);
    inout += 3;
  }
}
CML_API void CMLclampHSV  (CMLInputOutput hsv  , size_t count){
  float* inout = (float*)hsv;
  for(size_t i = 0; i < count; i++){
    InternalclampHSV  (inout);
    inout += 3;
  }
}
CML_API void CMLclampHSL  (CMLInputOutput hsl  , size_t count){
  float* inout = (float*)hsl;
  for(size_t i = 0; i < count; i++){
    InternalclampHSL  (inout);
    inout += 3;
  }
}
CML_API void CMLclampCMYK (CMLInputOutput cmyk , size_t count){
  float* inout = (float*)cmyk;
  for(size_t i = 0; i < count; i++){
    InternalclampCMYK (inout);
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

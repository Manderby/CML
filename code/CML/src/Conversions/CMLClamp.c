
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

#include "../CML.h"
#include "../StateMachine/CMLColorMachineState.h"


CMLHIDDEN CML_INLINE static CMLBool CMLClampToRange(float* x, float a, float b){
  if(*x<a){*x = a; return CMLFALSE;}
  if(*x>b){*x = b; return CMLFALSE;}
  return CMLTRUE;
}


CMLHIDDEN CML_INLINE static void InternalclampGray(float* gray){
  CMLClampToRange(&(gray[0]), CML_GRAY_MIN, CML_GRAY_MAX);
}
CMLHIDDEN CML_INLINE static void InternalclampXYZ(float* xyz){
  CMLClampToRange(&(xyz[0]), CML_XYZ_X_MIN, CML_XYZ_X_MAX);
  CMLClampToRange(&(xyz[1]), CML_XYZ_Y_MIN, CML_XYZ_Y_MAX);
  CMLClampToRange(&(xyz[2]), CML_XYZ_Z_MIN, CML_XYZ_Z_MAX);
}
CMLHIDDEN CML_INLINE static void InternalclampYxy(float* yxy){
  CMLClampToRange(&(yxy[0]), CML_Yxy_Y_MIN, CML_Yxy_Y_MAX);
  CMLClampToRange(&(yxy[1]), CML_Yxy_x_MIN, CML_Yxy_x_MAX);
  CMLClampToRange(&(yxy[2]), CML_Yxy_y_MIN, CML_Yxy_y_MAX);
}
CMLHIDDEN CML_INLINE static void InternalclampYuv(float* Yuv){
  CMLClampToRange(&(Yuv[0]), CML_Yuv_Y_MIN, CML_Yuv_Y_MAX);
  CMLClampToRange(&(Yuv[1]), CML_Yuv_u_MIN, CML_Yuv_u_MAX);
  CMLClampToRange(&(Yuv[2]), CML_Yuv_v_MIN, CML_Yuv_v_MAX);
}
CMLHIDDEN CML_INLINE static void InternalclampYupvp(float* Yuv){
  CMLClampToRange(&(Yuv[0]), CML_Yupvp_Y_MIN, CML_Yupvp_Y_MAX);
  CMLClampToRange(&(Yuv[1]), CML_Yupvp_up_MIN, CML_Yupvp_up_MAX);
  CMLClampToRange(&(Yuv[2]), CML_Yupvp_vp_MIN, CML_Yupvp_vp_MAX);
}
CMLHIDDEN CML_INLINE static void InternalclampLab(float* lab){
  CMLClampToRange(&(lab[0]), CML_Lab_L_MIN, CML_Lab_L_MAX);
  CMLClampToRange(&(lab[1]), CML_Lab_a_MIN, CML_Lab_a_MAX);
  CMLClampToRange(&(lab[2]), CML_Lab_b_MIN, CML_Lab_b_MAX);
}
CMLHIDDEN CML_INLINE static void InternalclampLch(float* lch){
  CMLint32 fullangles;
  CMLClampToRange(&(lch[0]), CML_Lch_L_MIN, CML_Lch_L_MAX);
  CMLClampToRange(&(lch[1]), CML_Lch_c_MIN, CML_Lch_c_MAX);
  fullangles = (CMLint32)floorf(lch[2] / CML_Lch_h_MAX);
  lch[2] -= fullangles * CML_Lch_h_MAX;
}
CMLHIDDEN CML_INLINE static void InternalclampLuv(float* luv){
  CMLClampToRange(&(luv[0]), CML_Luv_L_MIN, CML_Luv_L_MAX);
  CMLClampToRange(&(luv[1]), CML_Luv_u_MIN, CML_Luv_u_MAX);
  CMLClampToRange(&(luv[2]), CML_Luv_v_MIN, CML_Luv_v_MAX);
}
CMLHIDDEN CML_INLINE static void InternalclampRGB(float* rgb){
  CMLClampToRange(&(rgb[0]), CML_RGB_R_MIN, CML_RGB_R_MAX);
  CMLClampToRange(&(rgb[1]), CML_RGB_G_MIN, CML_RGB_G_MAX);
  CMLClampToRange(&(rgb[2]), CML_RGB_B_MIN, CML_RGB_B_MAX);
}
CMLHIDDEN CML_INLINE static void InternalclampYCbCr(float* ycbcr){
  CMLClampToRange(&(ycbcr[0]), CML_YCbCr_Y_MIN, CML_YCbCr_Y_MAX);
  CMLClampToRange(&(ycbcr[1]), CML_YCbCr_Cb_MIN, CML_YCbCr_Cb_MAX);
  CMLClampToRange(&(ycbcr[2]), CML_YCbCr_Cr_MIN, CML_YCbCr_Cr_MAX);
}
CMLHIDDEN CML_INLINE static void InternalclampHSV(float* hsv){
  CMLint32 fullangles = (CMLint32)floorf(hsv[0] / CML_HSV_H_MAX);
  hsv[0] -= fullangles * CML_HSV_H_MAX;
  CMLClampToRange(&(hsv[1]), CML_HSV_S_MIN, CML_HSV_S_MAX);
  CMLClampToRange(&(hsv[2]), CML_HSV_V_MIN, CML_HSV_V_MAX);
}
CMLHIDDEN CML_INLINE static void InternalclampHSL(float* hsl){
  CMLint32 fullangles = (CMLint32)floorf(hsl[0] / CML_HSL_H_MAX);
  hsl[0] -= fullangles * CML_HSL_H_MAX;
  CMLClampToRange(&(hsl[1]), CML_HSL_S_MIN, CML_HSL_S_MAX);
  CMLClampToRange(&(hsl[2]), CML_HSL_L_MIN, CML_HSL_L_MAX);
}
CMLHIDDEN CML_INLINE static void InternalclampCMYK(float* cmyk){
  CMLClampToRange(&(cmyk[0]), CML_CMYK_C_MIN, CML_CMYK_C_MAX);
  CMLClampToRange(&(cmyk[1]), CML_CMYK_M_MIN, CML_CMYK_M_MAX);
  CMLClampToRange(&(cmyk[2]), CML_CMYK_Y_MIN, CML_CMYK_Y_MAX);
  CMLClampToRange(&(cmyk[3]), CML_CMYK_K_MIN, CML_CMYK_K_MAX);
}


CMLAPI void CMLclampGray (CMLInputOutput gray , CMLSize count){
  CMLSize i;
  float* inout = (float*)gray;
  for(i=0; i<count; i++){
    InternalclampGray (inout);
    inout++;
  }
}
CMLAPI void CMLclampXYZ  (CMLInputOutput xyz  , CMLSize count){
  CMLSize i;
  float* inout = (float*)xyz;
  for(i=0; i<count; i++){
    InternalclampXYZ  (inout);
    inout += 3;
  }
}
CMLAPI void CMLclampYxy  (CMLInputOutput yxy  , CMLSize count){
  CMLSize i;
  float* inout = (float*)yxy;
  for(i=0; i<count; i++){
    InternalclampYxy  (inout);
    inout += 3;
  }
}
CMLAPI void CMLclampYuv  (CMLInputOutput Yuv  , CMLSize count){
  CMLSize i;
  float* inout = (float*)Yuv;
  for(i=0; i<count; i++){
    InternalclampYuv  (inout);
    inout += 3;
  }
}
CMLAPI void CMLclampYupvp  (CMLInputOutput Yupvp  , CMLSize count){
  CMLSize i;
  float* inout = (float*)Yupvp;
  for(i=0; i<count; i++){
    InternalclampYupvp  (inout);
    inout += 3;
  }
}
CMLAPI void CMLclampLab  (CMLInputOutput lab  , CMLSize count){
  CMLSize i;
  float* inout = (float*)lab;
  for(i=0; i<count; i++){
    InternalclampLab  (inout);
    inout += 3;
  }
}
CMLAPI void CMLclampLch  (CMLInputOutput lch  , CMLSize count){
  CMLSize i;
  float* inout = (float*)lch;
  for(i=0; i<count; i++){
    InternalclampLch  (inout);
    inout += 3;
  }
}
CMLAPI void CMLclampLuv  (CMLInputOutput luv  , CMLSize count){
  CMLSize i;
  float* inout = (float*)luv;
  for(i=0; i<count; i++){
    InternalclampLuv  (inout);
    inout += 3;
  }
}
CMLAPI void CMLclampRGB  (CMLInputOutput rgb  , CMLSize count){
  CMLSize i;
  float* inout = (float*)rgb;
  for(i=0; i<count; i++){
    InternalclampRGB  (inout);
    inout += 3;
  }
}
CMLAPI void CMLclampYCbCr(CMLInputOutput ycbcr, CMLSize count){
  CMLSize i;
  float* inout = (float*)ycbcr;
  for(i=0; i<count; i++){
    InternalclampYCbCr(inout);
    inout += 3;
  }
}
CMLAPI void CMLclampHSV  (CMLInputOutput hsv  , CMLSize count){
  CMLSize i;
  float* inout = (float*)hsv;
  for(i=0; i<count; i++){
    InternalclampHSV  (inout);
    inout += 3;
  }
}
CMLAPI void CMLclampHSL  (CMLInputOutput hsl  , CMLSize count){
  CMLSize i;
  float* inout = (float*)hsl;
  for(i=0; i<count; i++){
    InternalclampHSL  (inout);
    inout += 3;
  }
}
CMLAPI void CMLclampCMYK (CMLInputOutput cmyk , CMLSize count){
  CMLSize i;
  float* inout = (float*)cmyk;
  for(i=0; i<count; i++){
    InternalclampCMYK (inout);
    inout += 4;
  }
}



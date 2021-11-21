
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

#include "../CML.h"
#include "../StateMachine/CMLColorMachineState.h"

CMLHIDDEN CML_INLINE static void InternalinvertGray(float* gray){
  gray[0] = CML_GRAY_MAX - gray[0];
}
CMLHIDDEN CML_INLINE static void InternalinvertXYZ(float* xyz){
  xyz[0] = CML_XYZ_X_MAX - xyz[0];
  xyz[1] = CML_XYZ_Y_MAX - xyz[1];
  xyz[2] = CML_XYZ_Z_MAX - xyz[2];
}
CMLHIDDEN CML_INLINE static void InternalinvertYxy(float* yxy){
  yxy[0] = CML_Yxy_Y_MAX - yxy[0];
  yxy[1] = CML_Yxy_x_MAX - yxy[1];
  yxy[2] = CML_Yxy_y_MAX - yxy[2];
}
CMLHIDDEN CML_INLINE static void InternalinvertYuv(float* Yuv){
  Yuv[0] = CML_Yuv_Y_MAX - Yuv[0];
  Yuv[1] = CML_Yuv_u_MAX - Yuv[1];
  Yuv[2] = CML_Yuv_v_MAX - Yuv[2];
}
CMLHIDDEN CML_INLINE static void InternalinvertYupvp(float* Yupvp){
  Yupvp[0] = CML_Yupvp_Y_MAX - Yupvp[0];
  Yupvp[1] = CML_Yupvp_up_MAX - Yupvp[1];
  Yupvp[2] = CML_Yupvp_vp_MAX - Yupvp[2];
}
CMLHIDDEN CML_INLINE static void InternalinvertLab(float* lab){
  lab[0] = CML_Lab_L_MAX - lab[0];
  lab[1] = -lab[1];
  lab[2] = -lab[2];
}
CMLHIDDEN CML_INLINE static void InternalinvertLch(float* lch){
  lch[0] = CML_Lch_L_MAX - lch[0];
  lch[1] = lch[1];
  lch[2] = lch[2] - 180.f;
  if(lch[2] < 0.f){lch[2] += 360.f;}
}
CMLHIDDEN CML_INLINE static void InternalinvertLuv(float* luv){
  luv[0] = CML_Luv_L_MAX - luv[0];
  luv[1] = -luv[1];
  luv[2] = -luv[2];
}
CMLHIDDEN CML_INLINE static void InternalinvertRGB(float* rgb){
  rgb[0] = CML_RGB_R_MAX - rgb[0];
  rgb[1] = CML_RGB_G_MAX - rgb[1];
  rgb[2] = CML_RGB_B_MAX - rgb[2];
}
CMLHIDDEN CML_INLINE static void InternalinvertYCbCr(float* ycbcr){
  ycbcr[0] = CML_YCbCr_Y_MAX - ycbcr[0];
  ycbcr[1] = -ycbcr[1];
  ycbcr[2] = -ycbcr[2];
}
CMLHIDDEN CML_INLINE static void InternalinvertHSV(float* hsv){
  hsv[0] = hsv[0] - 180.f;
  if(hsv[0] < 0.f){hsv[0] += 360.f;}
  hsv[1] = hsv[1];
  hsv[2] = CML_HSV_V_MAX - hsv[2];
}
CMLHIDDEN CML_INLINE static void InternalinvertHSL(float* hsl){
  hsl[0] = hsl[0] - 180.f;
  if(hsl[0] < 0.f){hsl[0] += 360.f;}
  hsl[1] = hsl[1];
  hsl[2] = CML_HSL_L_MAX - hsl[2];
}
CMLHIDDEN CML_INLINE static void InternalinvertCMYK(float* cmyk){
  cmyk[0] = CML_CMYK_C_MAX - cmyk[0];
  cmyk[1] = CML_CMYK_M_MAX - cmyk[1];
  cmyk[2] = CML_CMYK_Y_MAX - cmyk[2];
  cmyk[3] = CML_CMYK_K_MAX - cmyk[3];
}


CMLAPI void CMLinvertGray (CMLInputOutput gray , CMLSize count){
  CMLSize i;
  float* inout = (float*)gray;
  for(i=0; i<count; i++){
    InternalinvertGray (inout);
    inout++;
  }
}
CMLAPI void CMLinvertXYZ  (CMLInputOutput xyz  , CMLSize count){
  CMLSize i;
  float* inout = (float*)xyz;
  for(i=0; i<count; i++){
    InternalinvertXYZ  (inout);
    inout += 3;
  }
}
CMLAPI void CMLinvertYxy  (CMLInputOutput yxy  , CMLSize count){
  CMLSize i;
  float* inout = (float*)yxy;
  for(i=0; i<count; i++){
    InternalinvertYxy  (inout);
    inout += 3;
  }
}
CMLAPI void CMLinvertYuv  (CMLInputOutput Yuv  , CMLSize count){
  CMLSize i;
  float* inout = (float*)Yuv;
  for(i=0; i<count; i++){
    InternalinvertYuv  (inout);
    inout += 3;
  }
}
CMLAPI void CMLinvertYupvp  (CMLInputOutput Yupvp  , CMLSize count){
  CMLSize i;
  float* inout = (float*)Yupvp;
  for(i=0; i<count; i++){
    InternalinvertYupvp  (inout);
    inout += 3;
  }
}
CMLAPI void CMLinvertLab  (CMLInputOutput lab  , CMLSize count){
  CMLSize i;
  float* inout = (float*)lab;
  for(i=0; i<count; i++){
    InternalinvertLab  (inout);
    inout += 3;
  }
}
CMLAPI void CMLinvertLch  (CMLInputOutput lch  , CMLSize count){
  CMLSize i;
  float* inout = (float*)lch;
  for(i=0; i<count; i++){
    InternalinvertLch  (inout);
    inout += 3;
  }
}
CMLAPI void CMLinvertLuv  (CMLInputOutput luv  , CMLSize count){
  CMLSize i;
  float* inout = (float*)luv;
  for(i=0; i<count; i++){
    InternalinvertLuv  (inout);
    inout += 3;
  }
}
CMLAPI void CMLinvertRGB  (CMLInputOutput rgb  , CMLSize count){
  CMLSize i;
  float* inout = (float*)rgb;
  for(i=0; i<count; i++){
    InternalinvertRGB  (inout);
    inout += 3;
  }
}
CMLAPI void CMLinvertYCbCr(CMLInputOutput ycbcr, CMLSize count){
  CMLSize i;
  float* inout = (float*)ycbcr;
  for(i=0; i<count; i++){
    InternalinvertYCbCr(inout);
    inout += 3;
  }
}
CMLAPI void CMLinvertHSV  (CMLInputOutput hsv  , CMLSize count){
  CMLSize i;
  float* inout = (float*)hsv;
  for(i=0; i<count; i++){
    InternalinvertHSV  (inout);
    inout += 3;
  }
}
CMLAPI void CMLinvertHSL  (CMLInputOutput hsl  , CMLSize count){
  CMLSize i;
  float* inout = (float*)hsl;
  for(i=0; i<count; i++){
    InternalinvertHSL  (inout);
    inout += 3;
  }
}
CMLAPI void CMLinvertCMYK (CMLInputOutput cmyk , CMLSize count){
  CMLSize i;
  float* inout = (float*)cmyk;
  for(i=0; i<count; i++){
    InternalinvertCMYK (inout);
    inout += 4;
  }
}




#define CML_Yuv_u_RANGE       (2.f / 3.f)
#define CML_Yuv_u_INVRANGE    (3.f / 2.f)
#define CML_Yuv_v_RANGE       (4.f / 9.f)
#define CML_Yuv_v_INVRANGE    (9.f / 4.f)

#define CML_Yupvp_up_RANGE       (2.f / 3.f)
#define CML_Yupvp_up_INVRANGE    (3.f / 2.f)
#define CML_Yupvp_vp_RANGE       (2.f / 3.f)
#define CML_Yupvp_vp_INVRANGE    (3.f / 2.f)

#define CML_Lab_L_RANGE       100.f
#define CML_Lab_a_RANGE       256.f
#define CML_Lab_b_RANGE       256.f
#define CML_Lab_L_INVRANGE    0.01f
#define CML_Lab_a_INVRANGE    0.00390625f // = 1/256
#define CML_Lab_b_INVRANGE    0.00390625f // = 1/256

#define CML_Lch_L_RANGE       100.f
#define CML_Lch_c_RANGE       128.f
#define CML_Lch_h_RANGE       360.f
#define CML_Lch_L_INVRANGE    0.01f
#define CML_Lch_c_INVRANGE    0.0078125f  // = 1/128
#define CML_Lch_h_INVRANGE    (1.f / 360.f)

#define CML_Luv_L_RANGE       100.f
#define CML_Luv_u_RANGE       200.f
#define CML_Luv_v_RANGE       200.f
#define CML_Luv_L_INVRANGE    0.01f
#define CML_Luv_u_INVRANGE    0.005f
#define CML_Luv_v_INVRANGE    0.005f

#define CML_HSV_H_RANGE       360.f
#define CML_HSV_H_INVRANGE    (1.f / 360.f)

#define CML_HSL_H_RANGE       360.f
#define CML_HSL_H_INVRANGE    (1.f / 360.f)



// //////////////////////////
// float Input Conversions from normed range (0,1)
// //////////////////////////

// Warning if a genius developer stumbles here and thinks that it may be a
// good idea to enhance this implementation by default with offset and range:
// It's not a good idea.  The compiler can not optimize this.

CML_HIDDEN CML_INLINE static void cml_GrayWithNormedInput(float* CML_RESTRICT gray, const float* CML_RESTRICT input){
  gray[0] =                     input[0];
}

CML_HIDDEN CML_INLINE static void cml_XYZWithNormedInput(float* CML_RESTRICT xyz, const float* CML_RESTRICT input){
  xyz[0] =                      input[0];
  xyz[1] =                      input[1];
  xyz[2] =                      input[2];
}

CML_HIDDEN CML_INLINE static void cml_YxyWithNormedInput(float* CML_RESTRICT yxy, const float* CML_RESTRICT input){
  yxy[0] =                      input[0];
  yxy[1] =                      input[1];
  yxy[2] =                      input[2];
}

CML_HIDDEN CML_INLINE static void cml_YuvWithNormedInput(float* CML_RESTRICT yuv, const float* CML_RESTRICT input){
  yuv[0] =                      input[0];
  yuv[1] =                      input[1] * CML_Yuv_u_RANGE;
  yuv[2] =                      input[2] * CML_Yuv_v_RANGE;
}

CML_HIDDEN CML_INLINE static void cml_YupvpWithNormedInput(float* CML_RESTRICT yupvp, const float* CML_RESTRICT input){
  yupvp[0] =                    input[0];
  yupvp[1] =                    input[1] * CML_Yupvp_up_RANGE;
  yupvp[2] =                    input[2] * CML_Yupvp_vp_RANGE;
}

CML_HIDDEN CML_INLINE static void cml_LabWithNormedInput(float* CML_RESTRICT lab, const float* CML_RESTRICT input){
  lab[0] =                      input[0] * CML_Lab_L_RANGE;
  lab[1] = CML_Lab_a_MIN      + input[1] * CML_Lab_a_RANGE;
  lab[2] = CML_Lab_b_MIN      + input[2] * CML_Lab_b_RANGE;
}

CML_HIDDEN CML_INLINE static void cml_LchWithNormedInput(float* CML_RESTRICT lch, const float* CML_RESTRICT input){
  lch[0] =                      input[0] * CML_Lch_L_RANGE;
  lch[1] =                      input[1] * CML_Lch_c_RANGE;
  lch[2] =                      input[2] * CML_Lch_h_RANGE;
}

CML_HIDDEN CML_INLINE static void cml_LuvWithNormedInput(float* CML_RESTRICT luv, const float* CML_RESTRICT input){
  luv[0] =                      input[0] * CML_Luv_L_RANGE;
  luv[1] = CML_Luv_u_MIN      + input[1] * CML_Luv_u_RANGE;
  luv[2] = CML_Luv_v_MIN      + input[2] * CML_Luv_v_RANGE;
}

CML_HIDDEN CML_INLINE static void cml_RGBWithNormedInput(float* CML_RESTRICT rgb, const float* CML_RESTRICT input){
  rgb[0] =                      input[0];
  rgb[1] =                      input[1];
  rgb[2] =                      input[2];
}

CML_HIDDEN CML_INLINE static void cml_YCbCrWithNormedInput(float* CML_RESTRICT ycbcr, const float* CML_RESTRICT input){
  ycbcr[0] =                    input[0];
  ycbcr[1] = CML_YCbCr_Cb_MIN + input[1];
  ycbcr[2] = CML_YCbCr_Cr_MIN + input[2];
}

CML_HIDDEN CML_INLINE static void cml_HSVWithNormedInput(float* CML_RESTRICT hsv, const float* CML_RESTRICT input){
  hsv[0] =                      input[0] * CML_HSV_H_RANGE;
  hsv[1] =                      input[1];
  hsv[2] =                      input[2];
}

CML_HIDDEN CML_INLINE static void cml_HSLWithNormedInput(float* CML_RESTRICT hsl, const float* CML_RESTRICT input){
  hsl[0] =                      input[0] * CML_HSL_H_RANGE;
  hsl[1] =                      input[1];
  hsl[2] =                      input[2];
}

CML_HIDDEN CML_INLINE static void cml_CMYKWithNormedInput(float* CML_RESTRICT cmyk, const float* CML_RESTRICT input){
  cmyk[0] =                     input[0];
  cmyk[1] =                     input[1];
  cmyk[2] =                     input[2];
  cmyk[3] =                     input[3];
}



// //////////////////////////
// Output Conversions to normed range (0,1)
// //////////////////////////

CML_HIDDEN CML_INLINE static void cml_NormedOutputWithGray(float* CML_RESTRICT output, const float* CML_RESTRICT gray){
  output[0] = gray[0];
}

CML_HIDDEN CML_INLINE static void cml_NormedOutputWithXYZ(float* CML_RESTRICT output, const float* CML_RESTRICT xyz){
  output[0] = xyz[0];
  output[1] = xyz[1];
  output[2] = xyz[2];
}

CML_HIDDEN CML_INLINE static void cml_NormedOutputWithYxy(float* CML_RESTRICT output, const float* CML_RESTRICT yxy){
  output[0] = yxy[0];
  output[1] = yxy[1];
  output[2] = yxy[2];
}

CML_HIDDEN CML_INLINE static void cml_NormedOutputWithYuv(float* CML_RESTRICT output, const float* CML_RESTRICT yuv){
  output[0] = yuv[0];
  output[1] = yuv[1] * CML_Yuv_u_INVRANGE;
  output[2] = yuv[2] * CML_Yuv_v_INVRANGE;
}

CML_HIDDEN CML_INLINE static void cml_NormedOutputWithYupvp(float* CML_RESTRICT output, const float* CML_RESTRICT yupvp){
  output[0] = yupvp[0];
  output[1] = yupvp[1] * CML_Yupvp_up_INVRANGE;
  output[2] = yupvp[2] * CML_Yupvp_vp_INVRANGE;
}

CML_HIDDEN CML_INLINE static void cml_NormedOutputWithLab(float* CML_RESTRICT output, const float* CML_RESTRICT lab){
  output[0] = (lab[0]                ) * CML_Lab_L_INVRANGE;
  output[1] = (lab[1] - CML_Lab_a_MIN) * CML_Lab_a_INVRANGE;
  output[2] = (lab[2] - CML_Lab_b_MIN) * CML_Lab_b_INVRANGE;
}

CML_HIDDEN CML_INLINE static void cml_NormedOutputWithLch(float* CML_RESTRICT output, const float* CML_RESTRICT lch){
  output[0] = (lch[0]                ) * CML_Lch_L_INVRANGE;
  output[1] = (lch[1]                ) * CML_Lch_c_INVRANGE;
  output[2] = (lch[2]                ) * CML_Lch_h_INVRANGE;
}

CML_HIDDEN CML_INLINE static void cml_NormedOutputWithLuv(float* CML_RESTRICT output, const float* CML_RESTRICT luv){
  output[0] =  luv[0]                  * CML_Luv_L_INVRANGE;
  output[1] = (luv[1] - CML_Luv_u_MIN) * CML_Luv_u_INVRANGE;
  output[2] = (luv[2] - CML_Luv_v_MIN) * CML_Luv_v_INVRANGE;
}

CML_HIDDEN CML_INLINE static void cml_NormedOutputWithRGB(float* CML_RESTRICT output, const float* CML_RESTRICT rgb){
  output[0] = rgb[0];
  output[1] = rgb[1];
  output[2] = rgb[2];
}

CML_HIDDEN CML_INLINE static void cml_NormedOutputWithYCbCr(float* CML_RESTRICT output, const float* CML_RESTRICT ycbcr){
  output[0] =  ycbcr[0];
  output[1] = (ycbcr[1] - CML_YCbCr_Cb_MIN);
  output[2] = (ycbcr[2] - CML_YCbCr_Cr_MIN);
}

CML_HIDDEN CML_INLINE static void cml_NormedOutputWithHSV(float* CML_RESTRICT output, const float* CML_RESTRICT hsv){
  output[0] =  hsv[0]                  * CML_HSV_H_INVRANGE;
  output[1] =  hsv[1];
  output[2] =  hsv[2];
}

CML_HIDDEN CML_INLINE static void cml_NormedOutputWithHSL(float* CML_RESTRICT output, const float* CML_RESTRICT hsl){
  output[0] =  hsl[0]                  * CML_HSL_H_INVRANGE;
  output[1] =  hsl[1];
  output[2] =  hsl[2];
}

CML_HIDDEN CML_INLINE static void cml_NormedOutputWithCMYK(float* CML_RESTRICT output, const float* CML_RESTRICT cmyk){
  output[0] = cmyk[0];
  output[1] = cmyk[1];
  output[2] = cmyk[2];
  output[3] = cmyk[3];
}



// /////////////////////////////////////
// Normed Cartesian methods
// /////////////////////////////////////

CML_HIDDEN CML_INLINE static void cml_LchWithNormedCartesianInput(float* CML_RESTRICT lch, const float* CML_RESTRICT input){
  float vec[2] = {input[1] * 2.f - 1.f, input[2] * 2.f - 1.f};
  lch[0] = input[0] * CML_Lch_L_RANGE;
  cmlPolarWithCartesian(&(lch[1]), vec);
  lch[1] *= CML_Lch_c_RANGE;
  lch[2] = cmlDegWithRad(lch[2]);
  if(lch[2] < 0.f){lch[2] += 360.f;}
}

CML_HIDDEN CML_INLINE static void cml_HSVWithNormedCartesianInput(float* CML_RESTRICT hsv, const float* CML_RESTRICT input){
  float vec[2] = {input[0] * 2.f - 1.f, input[1] * 2.f - 1.f};
  cmlPolarWithCartesian(&(hsv[1]), vec);
  hsv[0] = cmlDegWithRad(hsv[2]);
  if(hsv[0] < 0.f){hsv[0] += 360.f;}
  hsv[1] = hsv[1];
  hsv[2] = input[2];
}

CML_HIDDEN CML_INLINE static void cml_HSLWithNormedCartesianInput(float* CML_RESTRICT hsl, const float* CML_RESTRICT input){
  float vec[2] = {input[0] * 2.f - 1.f, input[1] * 2.f - 1.f};
  cmlPolarWithCartesian(&(hsl[1]), vec);
  hsl[0] = cmlDegWithRad(hsl[2]);
  if(hsl[0] < 0.f){hsl[0] += 360.f;}
  hsl[1] = hsl[1];
  hsl[2] = input[2];
}



CML_HIDDEN CML_INLINE static void cml_NormedCartesianOutputWithLch(float* CML_RESTRICT output, const float* CML_RESTRICT lch){
  float vec[2] = {lch[1] * CML_Lch_c_INVRANGE, cmlRadWithDeg(lch[2])};
  output[0] = lch[0] * CML_Lch_L_INVRANGE;
  cmlCartesianWithPolar(&(output[1]), vec);
  output[1] = .5f * (output[1] + 1.f);
  output[2] = .5f * (output[2] + 1.f);
}

CML_HIDDEN CML_INLINE static void cml_NormedCartesianOutputWithHSV(float* CML_RESTRICT output, const float* CML_RESTRICT hsv){
  float vec[2] = {hsv[1], cmlRadWithDeg(hsv[0])};
  cmlCartesianWithPolar(&(output[0]), vec);
  output[0] = .5f * (output[0] + 1.f);
  output[1] = .5f * (output[1] + 1.f);
  output[2] = hsv[2];
}

CML_HIDDEN CML_INLINE static void cml_NormedCartesianOutputWithHSL(float* CML_RESTRICT output, const float* CML_RESTRICT hsl){
  float vec[2] = {hsl[1], cmlRadWithDeg(hsl[0])};
  cmlCartesianWithPolar(&(output[0]), vec);
  output[0] = .5f * (output[0] + 1.f);
  output[1] = .5f * (output[1] + 1.f);
  output[2] = hsl[2];
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


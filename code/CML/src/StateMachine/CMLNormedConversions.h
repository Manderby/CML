
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

CML_HIDDEN CML_INLINE static void CMLInternalGrayfromNormedInput(float* CML_RESTRICT gray, const float* CML_RESTRICT input){
  gray[0] =                     input[0];
}
CML_HIDDEN CML_INLINE static void CMLInternalXYZfromNormedInput(float* CML_RESTRICT XYZ, const float* CML_RESTRICT input){
  XYZ[0] =                      input[0];
  XYZ[1] =                      input[1];
  XYZ[2] =                      input[2];
}
CML_HIDDEN CML_INLINE static void CMLInternalYxyfromNormedInput(float* CML_RESTRICT Yxy, const float* CML_RESTRICT input){
  Yxy[0] =                      input[0];
  Yxy[1] =                      input[1];
  Yxy[2] =                      input[2];
}
CML_HIDDEN CML_INLINE static void CMLInternalYuvfromNormedInput(float* CML_RESTRICT Yuv, const float* CML_RESTRICT input){
  Yuv[0] =                      input[0];
  Yuv[1] =                      input[1] * CML_Yuv_u_RANGE;
  Yuv[2] =                      input[2] * CML_Yuv_v_RANGE;
}
CML_HIDDEN CML_INLINE static void CMLInternalYupvpfromNormedInput(float* CML_RESTRICT Yupvp, const float* CML_RESTRICT input){
  Yupvp[0] =                    input[0];
  Yupvp[1] =                    input[1] * CML_Yupvp_up_RANGE;
  Yupvp[2] =                    input[2] * CML_Yupvp_vp_RANGE;
}
CML_HIDDEN CML_INLINE static void CMLInternalLabfromNormedInput(float* CML_RESTRICT Lab, const float* CML_RESTRICT input){
  Lab[0] =                      input[0] * CML_Lab_L_RANGE;
  Lab[1] = CML_Lab_a_MIN      + input[1] * CML_Lab_a_RANGE;
  Lab[2] = CML_Lab_b_MIN      + input[2] * CML_Lab_b_RANGE;
}
CML_HIDDEN CML_INLINE static void CMLInternalLchfromNormedInput(float* CML_RESTRICT Lch, const float* CML_RESTRICT input){
  Lch[0] =                      input[0] * CML_Lch_L_RANGE;
  Lch[1] =                      input[1] * CML_Lch_c_RANGE;
  Lch[2] =                      input[2] * CML_Lch_h_RANGE;
}
CML_HIDDEN CML_INLINE static void CMLInternalLuvfromNormedInput(float* CML_RESTRICT Luv, const float* CML_RESTRICT input){
  Luv[0] =                      input[0] * CML_Luv_L_RANGE;
  Luv[1] = CML_Luv_u_MIN      + input[1] * CML_Luv_u_RANGE;
  Luv[2] = CML_Luv_v_MIN      + input[2] * CML_Luv_v_RANGE;
}
CML_HIDDEN CML_INLINE static void CMLInternalRGBfromNormedInput(float* CML_RESTRICT RGB, const float* CML_RESTRICT input){
  RGB[0] =                      input[0];
  RGB[1] =                      input[1];
  RGB[2] =                      input[2];
}
CML_HIDDEN CML_INLINE static void CMLInternalYCbCrfromNormedInput(float* CML_RESTRICT YCbCr, const float* CML_RESTRICT input){
  YCbCr[0] =                    input[0];
  YCbCr[1] = CML_YCbCr_Cb_MIN + input[1];
  YCbCr[2] = CML_YCbCr_Cr_MIN + input[2];
}
CML_HIDDEN CML_INLINE static void CMLInternalHSVfromNormedInput(float* CML_RESTRICT HSV, const float* CML_RESTRICT input){
  HSV[0] =                      input[0] * CML_HSV_H_RANGE;
  HSV[1] =                      input[1];
  HSV[2] =                      input[2];
}
CML_HIDDEN CML_INLINE static void CMLInternalHSLfromNormedInput(float* CML_RESTRICT HSL, const float* CML_RESTRICT input){
  HSL[0] =                      input[0] * CML_HSL_H_RANGE;
  HSL[1] =                      input[1];
  HSL[2] =                      input[2];
}
CML_HIDDEN CML_INLINE static void CMLInternalCMYKfromNormedInput(float* CML_RESTRICT CMYK, const float* CML_RESTRICT input){
  CMYK[0] =                     input[0];
  CMYK[1] =                     input[1];
  CMYK[2] =                     input[2];
  CMYK[3] =                     input[3];
}







// //////////////////////////
// Output Conversions to normed range (0,1)
// //////////////////////////


CML_HIDDEN CML_INLINE static void CMLInternalGraytoNormedOutput(float* CML_RESTRICT output, const float* CML_RESTRICT gray){
  output[0] = gray[0];
}
CML_HIDDEN CML_INLINE static void CMLInternalXYZtoNormedOutput(float* CML_RESTRICT output, const float* CML_RESTRICT XYZ){
  output[0] = XYZ[0];
  output[1] = XYZ[1];
  output[2] = XYZ[2];
}
CML_HIDDEN CML_INLINE static void CMLInternalYxytoNormedOutput(float* CML_RESTRICT output, const float* CML_RESTRICT Yxy){
  output[0] = Yxy[0];
  output[1] = Yxy[1];
  output[2] = Yxy[2];
}
CML_HIDDEN CML_INLINE static void CMLInternalYuvtoNormedOutput(float* CML_RESTRICT output, const float* CML_RESTRICT Yuv){
  output[0] = Yuv[0];
  output[1] = Yuv[1] * CML_Yuv_u_INVRANGE;
  output[2] = Yuv[2] * CML_Yuv_v_INVRANGE;
}
CML_HIDDEN CML_INLINE static void CMLInternalYupvptoNormedOutput(float* CML_RESTRICT output, const float* CML_RESTRICT Yupvp){
  output[0] = Yupvp[0];
  output[1] = Yupvp[1] * CML_Yupvp_up_INVRANGE;
  output[2] = Yupvp[2] * CML_Yupvp_vp_INVRANGE;
}
CML_HIDDEN CML_INLINE static void CMLInternalLabtoNormedOutput(float* CML_RESTRICT output, const float* CML_RESTRICT Lab){
  output[0] = (Lab[0]                ) * CML_Lab_L_INVRANGE;
  output[1] = (Lab[1] - CML_Lab_a_MIN) * CML_Lab_a_INVRANGE;
  output[2] = (Lab[2] - CML_Lab_b_MIN) * CML_Lab_b_INVRANGE;
}
CML_HIDDEN CML_INLINE static void CMLInternalLchtoNormedOutput(float* CML_RESTRICT output, const float* CML_RESTRICT Lch){
  output[0] = (Lch[0]                ) * CML_Lch_L_INVRANGE;
  output[1] = (Lch[1]                ) * CML_Lch_c_INVRANGE;
  output[2] = (Lch[2]                ) * CML_Lch_h_INVRANGE;
}
CML_HIDDEN CML_INLINE static void CMLInternalLuvtoNormedOutput(float* CML_RESTRICT output, const float* CML_RESTRICT Luv){
  output[0] =  Luv[0]                  * CML_Luv_L_INVRANGE;
  output[1] = (Luv[1] - CML_Luv_u_MIN) * CML_Luv_u_INVRANGE;
  output[2] = (Luv[2] - CML_Luv_v_MIN) * CML_Luv_v_INVRANGE;
}
CML_HIDDEN CML_INLINE static void CMLInternalRGBtoNormedOutput(float* CML_RESTRICT output, const float* CML_RESTRICT RGB){
  output[0] = RGB[0];
  output[1] = RGB[1];
  output[2] = RGB[2];
}
CML_HIDDEN CML_INLINE static void CMLInternalYCbCrtoNormedOutput(float* CML_RESTRICT output, const float* CML_RESTRICT YCbCr){
  output[0] =  YCbCr[0];
  output[1] = (YCbCr[1] - CML_YCbCr_Cb_MIN);
  output[2] = (YCbCr[2] - CML_YCbCr_Cr_MIN);
}
CML_HIDDEN CML_INLINE static void CMLInternalHSVtoNormedOutput(float* CML_RESTRICT output, const float* CML_RESTRICT HSV){
  output[0] =  HSV[0]                  * CML_HSV_H_INVRANGE;
  output[1] =  HSV[1];
  output[2] =  HSV[2];
}
CML_HIDDEN CML_INLINE static void CMLInternalHSLtoNormedOutput(float* CML_RESTRICT output, const float* CML_RESTRICT HSL){
  output[0] =  HSL[0]                  * CML_HSL_H_INVRANGE;
  output[1] =  HSL[1];
  output[2] =  HSL[2];
}
CML_HIDDEN CML_INLINE static void CMLInternalCMYKtoNormedOutput(float* CML_RESTRICT output, const float* CML_RESTRICT CMYK){
  output[0] = CMYK[0];
  output[1] = CMYK[1];
  output[2] = CMYK[2];
  output[3] = CMYK[3];
}





// /////////////////////////////////////
// Normed Cartesian methods
// /////////////////////////////////////

CML_HIDDEN CML_INLINE static void CMLInternalLchfromNormedCartesianInput(float* CML_RESTRICT Lch, const float* CML_RESTRICT input){
  float vec[2] = {input[1] * 2.f - 1.f, input[2] * 2.f - 1.f};
  Lch[0] = input[0] * CML_Lch_L_RANGE;
  CMLCartesiantoPolar(&(Lch[1]), vec);
  Lch[1] *= CML_Lch_c_RANGE;
  Lch[2] = CMLRadtoDeg(Lch[2]);
  if(Lch[2] < 0.f){Lch[2] += 360.f;}
}

CML_HIDDEN CML_INLINE static void CMLInternalHSVfromNormedCartesianInput(float* CML_RESTRICT HSV, const float* CML_RESTRICT input){
  float vec[2] = {input[0] * 2.f - 1.f, input[1] * 2.f - 1.f};
  CMLCartesiantoPolar(&(HSV[1]), vec);
  HSV[0] = CMLRadtoDeg(HSV[2]);
  if(HSV[0] < 0.f){HSV[0] += 360.f;}
  HSV[1] = HSV[1];
  HSV[2] = input[2];
}
CML_HIDDEN CML_INLINE static void CMLInternalHSLfromNormedCartesianInput(float* CML_RESTRICT HSL, const float* CML_RESTRICT input){
  float vec[2] = {input[0] * 2.f - 1.f, input[1] * 2.f - 1.f};
  CMLCartesiantoPolar(&(HSL[1]), vec);
  HSL[0] = CMLRadtoDeg(HSL[2]);
  if(HSL[0] < 0.f){HSL[0] += 360.f;}
  HSL[1] = HSL[1];
  HSL[2] = input[2];
}




CML_HIDDEN CML_INLINE static void CMLInternalLchtoNormedCartesianOutput(float* CML_RESTRICT output, const float* CML_RESTRICT Lch){
  float vec[2] = {Lch[1] * CML_Lch_c_INVRANGE, CMLDegtoRad(Lch[2])};
  output[0] = Lch[0] * CML_Lch_L_INVRANGE;
  CMLPolartoCartesian(&(output[1]), vec);
  output[1] = .5f * (output[1] + 1.f);
  output[2] = .5f * (output[2] + 1.f);
}
CML_HIDDEN CML_INLINE static void CMLInternalHSVtoNormedCartesianOutput(float* CML_RESTRICT output, const float* CML_RESTRICT HSV){
  float vec[2] = {HSV[1], CMLDegtoRad(HSV[0])};
  CMLPolartoCartesian(&(output[0]), vec);
  output[0] = .5f * (output[0] + 1.f);
  output[1] = .5f * (output[1] + 1.f);
  output[2] = HSV[2];
}
CML_HIDDEN CML_INLINE static void CMLInternalHSLtoNormedCartesianOutput(float* CML_RESTRICT output, const float* CML_RESTRICT HSL){
  float vec[2] = {HSL[1], CMLDegtoRad(HSL[0])};
  CMLPolartoCartesian(&(output[0]), vec);
  output[0] = .5f * (output[0] + 1.f);
  output[1] = .5f * (output[1] + 1.f);
  output[2] = HSL[2];
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


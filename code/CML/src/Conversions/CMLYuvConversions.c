
#include "../CML.h"
#include "../StateMachine/CMLColorMachineState.h"
#include "../StateMachine/CMLConverterMacros.h"






// //////////////////////////
// Identity converter
// //////////////////////////

CML_API void CMLYuvtoYuv (const CMLColorMachine* cm, CMLOutput Yuvd , CMLInput Yuvs, CMLSize count){
  cm = cm; // no warning
  CML_CONVERTER_INOUT_PARAMETER(Yuvd, Yuvs, CML_Yuv_NUMCHANNELS, CML_Yuv_NUMCHANNELS);
  CML_CONVERTER_MEMCPY(CML_Yuv_NUMCHANNELS);
  CML_CONVERTER_RETURN;
}



// //////////////////////////
// Yuv to anything
// //////////////////////////

CML_API void CMLYuvtoXYZ (const CMLColorMachine* cm, CMLOutput XYZ , CMLInput Yuv , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(XYZ, Yuv, CML_XYZ_NUMCHANNELS, CML_Yuv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYuvtoYupvp);
  CMLCMYupvptoYxy_SB(cm, out, count, floatalign);
  CMLCMYxytoXYZ_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLYuvtoYxy (const CMLColorMachine* cm, CMLOutput Yxy , CMLInput Yuv , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(Yxy, Yuv, CML_Yxy_NUMCHANNELS, CML_Yuv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYuvtoYupvp);
  CMLCMYupvptoYxy_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLYuvtoYupvp (const CMLColorMachine* cm, CMLOutput Yupvp , CMLInput Yuv , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(Yupvp, Yuv, CML_Yupvp_NUMCHANNELS, CML_Yuv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYuvtoYupvp);
  CML_CONVERTER_RETURN;
}

CML_API void CMLYuvtoLab (const CMLColorMachine* cm, CMLOutput Lab , CMLInput Yuv , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(Lab, Yuv, CML_Lab_NUMCHANNELS, CML_Yuv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYuvtoYupvp);
  CMLCMYupvptoYxy_SB(cm, out, count, floatalign);
  CMLCMYxytoXYZ_SB(cm, out, count, floatalign);
  (*cm->XYZtoLab_SB)(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLYuvtoLch (const CMLColorMachine* cm, CMLOutput Lch , CMLInput Yuv , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(Lch, Yuv, CML_Lch_NUMCHANNELS, CML_Yuv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYuvtoYupvp);
  CMLCMYupvptoYxy_SB(cm, out, count, floatalign);
  CMLCMYxytoXYZ_SB(cm, out, count, floatalign);
  (*cm->XYZtoLab_SB)(cm, out, count, floatalign);
  CMLCMLabtoLch_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLYuvtoLuv (const CMLColorMachine* cm, CMLOutput Luv , CMLInput Yuv , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(Luv, Yuv, CML_Luv_NUMCHANNELS, CML_Yuv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYuvtoYupvp);
  CMLCMYupvptoLuv_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLYuvtoRGB (const CMLColorMachine* cm, CMLOutput RGB , CMLInput Yuv , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(RGB, Yuv, CML_RGB_NUMCHANNELS, CML_Yuv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYuvtoYupvp);
  CMLCMYupvptoYxy_SB(cm, out, count, floatalign);
  CMLCMYxytoXYZ_SB(cm, out, count, floatalign);
  CMLCMXYZtoRGB_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLYuvtoYCbCr (const CMLColorMachine* cm, CMLOutput YCbCr , CMLInput Yuv , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(YCbCr, Yuv, CML_YCbCr_NUMCHANNELS, CML_Yuv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYuvtoYupvp);
  CMLCMYupvptoYxy_SB(cm, out, count, floatalign);
  CMLCMYxytoXYZ_SB(cm, out, count, floatalign);
  CMLCMXYZtoRGB_SB(cm, out, count, floatalign);
  CMLCMRGBtoYCbCr_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLYuvtoHSV (const CMLColorMachine* cm, CMLOutput HSV , CMLInput Yuv , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(HSV, Yuv, CML_HSV_NUMCHANNELS, CML_Yuv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYuvtoYupvp);
  CMLCMYupvptoYxy_SB(cm, out, count, floatalign);
  CMLCMYxytoXYZ_SB(cm, out, count, floatalign);
  CMLCMXYZtoRGB_SB(cm, out, count, floatalign);
  CMLCMRGBtoHSV_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLYuvtoHSL (const CMLColorMachine* cm, CMLOutput HSL , CMLInput Yuv , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(HSL, Yuv, CML_HSL_NUMCHANNELS, CML_Yuv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYuvtoYupvp);
  CMLCMYupvptoYxy_SB(cm, out, count, floatalign);
  CMLCMYxytoXYZ_SB(cm, out, count, floatalign);
  CMLCMXYZtoRGB_SB(cm, out, count, floatalign);
  CMLCMRGBtoHSV_SB(cm, out, count, floatalign);
  CMLCMHSVtoHSL_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLYuvtoCMYK(const CMLColorMachine* cm, CMLOutput CMYK, CMLInput Yuv , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(CMYK, Yuv, CML_CMYK_NUMCHANNELS, CML_Yuv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYuvtoYupvp);
  CMLCMYupvptoYxy_SB(cm, out, count, floatalign);
  CMLCMYxytoXYZ_SB(cm, out, count, floatalign);
  CMLCMXYZtoRGB_SB(cm, out, count, floatalign);
  (*cm->RGBtoCMYK_SB)(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
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

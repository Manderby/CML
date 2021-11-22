
#include "../CML.h"
#include "../StateMachine/CMLColorMachineState.h"
#include "../StateMachine/CMLConverterMacros.h"




// //////////////////////////
// Identity converter
// //////////////////////////

CML_API void CMLLuvtoLuv (const CMLColorMachine* cm, CMLOutput Luvd , CMLInput Luvs, CMLSize count){
  cm = cm; // no warning
  CML_CONVERTER_INOUT_PARAMETER(Luvd, Luvs, CML_Luv_NUMCHANNELS, CML_Luv_NUMCHANNELS);
  CML_CONVERTER_MEMCPY(CML_Luv_NUMCHANNELS);
  CML_CONVERTER_RETURN;
}

// //////////////////////////
// Luv to anything
// //////////////////////////

CML_API void CMLLuvtoXYZ (const CMLColorMachine* cm, CMLOutput XYZ , CMLInput Luv , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(XYZ, Luv, CML_XYZ_NUMCHANNELS, CML_Luv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMLuvtoYupvp);
  CMLCMYupvptoYxy_SB(cm, out, count, floatalign);
  CMLCMYxytoXYZ_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLLuvtoYxy (const CMLColorMachine* cm, CMLOutput Yxy , CMLInput Luv , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(Yxy, Luv, CML_Yxy_NUMCHANNELS, CML_Luv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMLuvtoYupvp);
  CMLCMYupvptoYxy_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLLuvtoYuv (const CMLColorMachine* cm, CMLOutput Yuv , CMLInput Luv , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(Yuv, Luv, CML_Yuv_NUMCHANNELS, CML_Luv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMLuvtoYupvp);
  CMLCMYupvptoYuv_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLLuvtoYupvp (const CMLColorMachine* cm, CMLOutput Yupvp , CMLInput Luv , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(Yupvp, Luv, CML_Yupvp_NUMCHANNELS, CML_Luv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMLuvtoYupvp);
  CML_CONVERTER_RETURN;
}

CML_API void CMLLuvtoLab (const CMLColorMachine* cm, CMLOutput Lab , CMLInput Luv , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(Lab, Luv, CML_Lab_NUMCHANNELS, CML_Luv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMLuvtoYupvp);
  CMLCMYupvptoYxy_SB(cm, out, count, floatalign);
  CMLCMYxytoXYZ_SB(cm, out, count, floatalign);
  (*cm->XYZtoLab_SB)(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLLuvtoLch (const CMLColorMachine* cm, CMLOutput Lch , CMLInput Luv , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(Lch, Luv, CML_Lch_NUMCHANNELS, CML_Luv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMLuvtoYupvp);
  CMLCMYupvptoYxy_SB(cm, out, count, floatalign);
  CMLCMYxytoXYZ_SB(cm, out, count, floatalign);
  (*cm->XYZtoLab_SB)(cm, out, count, floatalign);
  CMLCMLabtoLch_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLLuvtoRGB (const CMLColorMachine* cm, CMLOutput RGB , CMLInput Luv , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(RGB, Luv, CML_RGB_NUMCHANNELS, CML_Luv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMLuvtoYupvp);
  CMLCMYupvptoYxy_SB(cm, out, count, floatalign);
  CMLCMYxytoXYZ_SB(cm, out, count, floatalign);
  CMLCMXYZtoRGB_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLLuvtoYCbCr (const CMLColorMachine* cm, CMLOutput YCbCr , CMLInput Luv , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(YCbCr, Luv, CML_YCbCr_NUMCHANNELS, CML_Luv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMLuvtoYupvp);
  CMLCMYupvptoYxy_SB(cm, out, count, floatalign);
  CMLCMYxytoXYZ_SB(cm, out, count, floatalign);
  CMLCMXYZtoRGB_SB(cm, out, count, floatalign);
  CMLCMRGBtoYCbCr_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLLuvtoHSV (const CMLColorMachine* cm, CMLOutput HSV , CMLInput Luv , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(HSV, Luv, CML_HSV_NUMCHANNELS, CML_Luv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMLuvtoYupvp);
  CMLCMYupvptoYxy_SB(cm, out, count, floatalign);
  CMLCMYxytoXYZ_SB(cm, out, count, floatalign);
  CMLCMXYZtoRGB_SB(cm, out, count, floatalign);
  CMLCMRGBtoHSV_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLLuvtoHSL (const CMLColorMachine* cm, CMLOutput HSL , CMLInput Luv , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(HSL, Luv, CML_HSL_NUMCHANNELS, CML_Luv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMLuvtoYupvp);
  CMLCMYupvptoYxy_SB(cm, out, count, floatalign);
  CMLCMYxytoXYZ_SB(cm, out, count, floatalign);
  CMLCMXYZtoRGB_SB(cm, out, count, floatalign);
  CMLCMRGBtoHSV_SB(cm, out, count, floatalign);
  CMLCMHSVtoHSL_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLLuvtoCMYK(const CMLColorMachine* cm, CMLOutput CMYK, CMLInput Luv , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(CMYK, Luv, CML_CMYK_NUMCHANNELS, CML_Luv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMLuvtoYupvp);
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

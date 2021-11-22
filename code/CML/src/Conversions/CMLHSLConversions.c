
#include "../CML.h"
#include "../StateMachine/CMLColorMachineState.h"
#include "../StateMachine/CMLConverterMacros.h"


// //////////////////////////
// Identity converter
// //////////////////////////

CML_API void CMLHSLtoHSL (const CMLColorMachine* cm, CMLOutput HSLd , CMLInput HSLs, CMLSize count){
  cm = cm; // no warning
  CML_CONVERTER_INOUT_PARAMETER(HSLd, HSLs, CML_HSL_NUMCHANNELS, CML_HSL_NUMCHANNELS);
  CML_CONVERTER_MEMCPY(CML_HSL_NUMCHANNELS);
  CML_CONVERTER_RETURN;
}


// //////////////////////////
// HSL to anything
// //////////////////////////

CML_API void CMLHSLtoXYZ (const CMLColorMachine* cm, CMLOutput XYZ , CMLInput HSL , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(XYZ, HSL, CML_XYZ_NUMCHANNELS, CML_HSL_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMHSLtoHSV);
  CMLCMHSVtoRGB_SB(cm, out, count, floatalign);
  CMLCMRGBtoXYZ_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLHSLtoYuv (const CMLColorMachine* cm, CMLOutput Yuv , CMLInput HSL , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(Yuv, HSL, CML_Yuv_NUMCHANNELS, CML_HSL_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMHSLtoHSV);
  CMLCMHSVtoRGB_SB(cm, out, count, floatalign);
  CMLCMRGBtoXYZ_SB(cm, out, count, floatalign);
  CMLCMXYZtoYxy_SB(cm, out, count, floatalign);
  CMLCMYxytoYupvp_SB(cm, out, count, floatalign);
  CMLCMYupvptoYuv_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLHSLtoYupvp (const CMLColorMachine* cm, CMLOutput Yupvp , CMLInput HSL , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(Yupvp, HSL, CML_Yupvp_NUMCHANNELS, CML_HSL_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMHSLtoHSV);
  CMLCMHSVtoRGB_SB(cm, out, count, floatalign);
  CMLCMRGBtoXYZ_SB(cm, out, count, floatalign);
  CMLCMXYZtoYxy_SB(cm, out, count, floatalign);
  CMLCMYxytoYupvp_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLHSLtoYxy (const CMLColorMachine* cm, CMLOutput Yxy , CMLInput HSL , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(Yxy, HSL, CML_Yxy_NUMCHANNELS, CML_HSL_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMHSLtoHSV);
  CMLCMHSVtoRGB_SB(cm, out, count, floatalign);
  CMLCMRGBtoXYZ_SB(cm, out, count, floatalign);
  CMLCMXYZtoYxy_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLHSLtoLab (const CMLColorMachine* cm, CMLOutput Lab , CMLInput HSL , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(Lab, HSL, CML_Lab_NUMCHANNELS, CML_HSL_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMHSLtoHSV);
  CMLCMHSVtoRGB_SB(cm, out, count, floatalign);
  CMLCMRGBtoXYZ_SB(cm, out, count, floatalign);
  (*cm->XYZtoLab_SB)(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLHSLtoLch (const CMLColorMachine* cm, CMLOutput Lch , CMLInput HSL , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(Lch, HSL, CML_Lch_NUMCHANNELS, CML_HSL_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMHSLtoHSV);
  CMLCMHSVtoRGB_SB(cm, out, count, floatalign);
  CMLCMRGBtoXYZ_SB(cm, out, count, floatalign);
  (*cm->XYZtoLab_SB)(cm, out, count, floatalign);
  CMLCMLabtoLch_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLHSLtoLuv (const CMLColorMachine* cm, CMLOutput Luv , CMLInput HSL , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(Luv, HSL, CML_Luv_NUMCHANNELS, CML_HSL_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMHSLtoHSV);
  CMLCMHSVtoRGB_SB(cm, out, count, floatalign);
  CMLCMRGBtoXYZ_SB(cm, out, count, floatalign);
  CMLCMXYZtoYxy_SB(cm, out, count, floatalign);
  CMLCMYxytoYupvp_SB(cm, out, count, floatalign);
  CMLCMYupvptoLuv_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLHSLtoRGB (const CMLColorMachine* cm, CMLOutput RGB , CMLInput HSL , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(RGB, HSL, CML_RGB_NUMCHANNELS, CML_HSL_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMHSLtoHSV);
  CMLCMHSVtoRGB_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLHSLtoYCbCr (const CMLColorMachine* cm, CMLOutput YCbCr , CMLInput HSL , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(YCbCr, HSL, CML_YCbCr_NUMCHANNELS, CML_HSL_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMHSLtoHSV);
  CMLCMHSVtoRGB_SB(cm, out, count, floatalign);
  CMLCMRGBtoYCbCr_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLHSLtoHSV (const CMLColorMachine* cm, CMLOutput HSV , CMLInput HSL , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(HSV, HSL, CML_HSV_NUMCHANNELS, CML_HSL_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMHSLtoHSV);
  CML_CONVERTER_RETURN;
}

CML_API void CMLHSLtoCMYK(const CMLColorMachine* cm, CMLOutput CMYK, CMLInput HSL , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(CMYK, HSL, CML_CMYK_NUMCHANNELS, CML_HSL_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMHSLtoHSV);
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

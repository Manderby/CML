
#include "../CML.h"
#include "../StateMachine/CMLColorMachineState.h"
#include "../StateMachine/CMLConverterMacros.h"

// //////////////////////////
// Identity converter
// //////////////////////////

CML_API void CMLHSVtoHSV (const CMLColorMachine* cm, CMLOutput HSVd , CMLInput HSVs, CMLSize count){
  cm = cm; // no warning
  CML_CONVERTER_INOUT_PARAMETER(HSVd, HSVs, CML_HSV_NUMCHANNELS, CML_HSV_NUMCHANNELS);
  CML_CONVERTER_MEMCPY(CML_HSV_NUMCHANNELS);
  CML_CONVERTER_RETURN;
}


// //////////////////////////
// HSV to anything
// //////////////////////////

CML_API void CMLHSVtoXYZ (const CMLColorMachine* cm, CMLOutput XYZ , CMLInput HSV , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(XYZ, HSV, CML_XYZ_NUMCHANNELS, CML_HSV_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMHSVtoRGB);
  CMLCMRGBtoXYZ_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLHSVtoYuv (const CMLColorMachine* cm, CMLOutput Yuv , CMLInput HSV , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(Yuv, HSV, CML_Yuv_NUMCHANNELS, CML_HSV_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMHSVtoRGB);
  CMLCMRGBtoXYZ_SB(cm, out, count, floatalign);
  CMLCMXYZtoYxy_SB(cm, out, count, floatalign);
  CMLCMYxytoYupvp_SB(cm, out, count, floatalign);
  CMLCMYupvptoYuv_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLHSVtoYupvp (const CMLColorMachine* cm, CMLOutput Yupvp , CMLInput HSV , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(Yupvp, HSV, CML_Yupvp_NUMCHANNELS, CML_HSV_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMHSVtoRGB);
  CMLCMRGBtoXYZ_SB(cm, out, count, floatalign);
  CMLCMXYZtoYxy_SB(cm, out, count, floatalign);
  CMLCMYxytoYupvp_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLHSVtoYxy (const CMLColorMachine* cm, CMLOutput Yxy , CMLInput HSV , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(Yxy, HSV, CML_Yxy_NUMCHANNELS, CML_HSV_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMHSVtoRGB);
  CMLCMRGBtoXYZ_SB(cm, out, count, floatalign);
  CMLCMXYZtoYxy_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLHSVtoLab (const CMLColorMachine* cm, CMLOutput Lab , CMLInput HSV , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(Lab, HSV, CML_Lab_NUMCHANNELS, CML_HSV_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMHSVtoRGB);
  CMLCMRGBtoXYZ_SB(cm, out, count, floatalign);
  (*cm->XYZtoLab_SB)(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLHSVtoLch (const CMLColorMachine* cm, CMLOutput Lch , CMLInput HSV , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(Lch, HSV, CML_Lch_NUMCHANNELS, CML_HSV_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMHSVtoRGB);
  CMLCMRGBtoXYZ_SB(cm, out, count, floatalign);
  (*cm->XYZtoLab_SB)(cm, out, count, floatalign);
  CMLCMLabtoLch_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLHSVtoLuv (const CMLColorMachine* cm, CMLOutput Luv , CMLInput HSV , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(Luv, HSV, CML_Luv_NUMCHANNELS, CML_HSV_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMHSVtoRGB);
  CMLCMRGBtoXYZ_SB(cm, out, count, floatalign);
  CMLCMXYZtoYxy_SB(cm, out, count, floatalign);
  CMLCMYxytoYupvp_SB(cm, out, count, floatalign);
  CMLCMYupvptoLuv_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLHSVtoRGB (const CMLColorMachine* cm, CMLOutput RGB , CMLInput HSV , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(RGB, HSV, CML_RGB_NUMCHANNELS, CML_HSV_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMHSVtoRGB);
  CML_CONVERTER_RETURN;
}

CML_API void CMLHSVtoYCbCr (const CMLColorMachine* cm, CMLOutput YCbCr , CMLInput HSV , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(YCbCr, HSV, CML_YCbCr_NUMCHANNELS, CML_HSV_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMHSVtoRGB);
  CMLCMRGBtoYCbCr_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLHSVtoHSL (const CMLColorMachine* cm, CMLOutput HSL , CMLInput HSV , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(HSL, HSV, CML_HSL_NUMCHANNELS, CML_HSV_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMHSVtoHSL);
  CML_CONVERTER_RETURN;
}

CML_API void CMLHSVtoCMYK(const CMLColorMachine* cm, CMLOutput CMYK, CMLInput HSV , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(CMYK, HSV, CML_CMYK_NUMCHANNELS, CML_HSV_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMHSVtoRGB);
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

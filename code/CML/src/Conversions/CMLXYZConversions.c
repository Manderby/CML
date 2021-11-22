
#include "../CML.h"
#include "../StateMachine/CMLColorMachineState.h"
#include "../StateMachine/CMLConverterMacros.h"


// //////////////////////////
// Identity converter
// //////////////////////////

CML_API void CMLXYZtoXYZ (const CMLColorMachine* cm, CMLOutput XYZd , CMLInput XYZs, CMLSize count){
  cm = cm; // no warning
  CML_CONVERTER_INOUT_PARAMETER(XYZd, XYZs, CML_XYZ_NUMCHANNELS, CML_XYZ_NUMCHANNELS);
  CML_CONVERTER_MEMCPY(CML_XYZ_NUMCHANNELS);
  CML_CONVERTER_RETURN;
}

// //////////////////////////
// XYZ to anything
// //////////////////////////

CML_API void CMLXYZtoYxy (const CMLColorMachine* cm, CMLOutput Yxy , CMLInput XYZ , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(Yxy, XYZ, CML_Yxy_NUMCHANNELS, CML_XYZ_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMXYZtoYxy);
  CML_CONVERTER_RETURN;
}

CML_API void CMLXYZtoYuv (const CMLColorMachine* cm, CMLOutput Yuv , CMLInput XYZ , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(Yuv, XYZ, CML_Yuv_NUMCHANNELS, CML_XYZ_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMXYZtoYxy);
  CMLCMYxytoYupvp_SB(cm, out, count, floatalign);
  CMLCMYupvptoYuv_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLXYZtoYupvp (const CMLColorMachine* cm, CMLOutput Yupvp , CMLInput XYZ , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(Yupvp, XYZ, CML_Yupvp_NUMCHANNELS, CML_XYZ_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMXYZtoYxy);
  CMLCMYxytoYupvp_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLXYZtoLab (const CMLColorMachine* cm, CMLOutput Lab , CMLInput XYZ , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(Lab, XYZ, CML_Lab_NUMCHANNELS, CML_XYZ_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(*cm->XYZtoLab);
  CML_CONVERTER_RETURN;
}

CML_API void CMLXYZtoLch (const CMLColorMachine* cm, CMLOutput Lch , CMLInput XYZ , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(Lch, XYZ, CML_Lch_NUMCHANNELS, CML_XYZ_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(*cm->XYZtoLab);
  CMLCMLabtoLch_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLXYZtoLuv (const CMLColorMachine* cm, CMLOutput Luv , CMLInput XYZ , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(Luv, XYZ, CML_Luv_NUMCHANNELS, CML_XYZ_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMXYZtoYxy);
  CMLCMYxytoYupvp_SB(cm, out, count, floatalign);
  CMLCMYupvptoLuv_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLXYZtoRGB (const CMLColorMachine* cm, CMLOutput RGB , CMLInput XYZ , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(RGB, XYZ, CML_RGB_NUMCHANNELS, CML_XYZ_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMXYZtoRGB);
  CML_CONVERTER_RETURN;
}

CML_API void CMLXYZtoYCbCr (const CMLColorMachine* cm, CMLOutput YCbCr, CMLInput XYZ , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(YCbCr, XYZ, CML_YCbCr_NUMCHANNELS, CML_XYZ_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMXYZtoRGB);
  CMLCMRGBtoYCbCr_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLXYZtoHSV (const CMLColorMachine* cm, CMLOutput HSV , CMLInput XYZ , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(HSV, XYZ, CML_HSV_NUMCHANNELS, CML_XYZ_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMXYZtoRGB);
  CMLCMRGBtoHSV_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLXYZtoHSL (const CMLColorMachine* cm, CMLOutput HSL , CMLInput XYZ , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(HSL, XYZ, CML_HSL_NUMCHANNELS, CML_XYZ_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMXYZtoRGB);
  CMLCMRGBtoHSV_SB(cm, out, count, floatalign);
  CMLCMHSVtoHSL_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLXYZtoCMYK(const CMLColorMachine* cm, CMLOutput CMYK, CMLInput XYZ , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(CMYK, XYZ, CML_CMYK_NUMCHANNELS, CML_XYZ_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMXYZtoRGB);
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

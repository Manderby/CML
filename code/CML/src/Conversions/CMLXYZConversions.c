
#include "../CML.h"
#include "../StateMachine/CMLColorMachineState.h"
#include "../StateMachine/CMLConverterMacros.h"


// //////////////////////////
// Identity converter
// //////////////////////////

CML_API void CMLXYZtoXYZ (const CMLColorMachine* cm, CMLOutput XYZd , CMLInput XYZs, size_t count){
  cm = cm; // no warning
  CML_CONVERTER_INOUT_PARAMETER(XYZd, XYZs, CML_XYZ_NUMCHANNELS, CML_XYZ_NUMCHANNELS);
  CML_CONVERTER_MEMCPY(CML_XYZ_NUMCHANNELS);
  CML_CONVERTER_RETURN;
}

// //////////////////////////
// XYZ to anything
// //////////////////////////

CML_API void CMLXYZtoYxy (const CMLColorMachine* cm, CMLOutput yxy , CMLInput xyz , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(yxy, xyz, CML_Yxy_NUMCHANNELS, CML_XYZ_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMXYZtoYxy);
  CML_CONVERTER_RETURN;
}

CML_API void CMLXYZtoYuv (const CMLColorMachine* cm, CMLOutput yuv , CMLInput xyz , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(yuv, xyz, CML_Yuv_NUMCHANNELS, CML_XYZ_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMXYZtoYxy);
  CMLCMYxytoYupvp_SB(cm, out, count, floatalign);
  CMLCMYupvptoYuv_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLXYZtoYupvp (const CMLColorMachine* cm, CMLOutput yupvp , CMLInput xyz , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(yupvp, xyz, CML_Yupvp_NUMCHANNELS, CML_XYZ_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMXYZtoYxy);
  CMLCMYxytoYupvp_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLXYZtoLab (const CMLColorMachine* cm, CMLOutput lab , CMLInput xyz , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(lab, xyz, CML_Lab_NUMCHANNELS, CML_XYZ_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(*cm->XYZtoLab);
  CML_CONVERTER_RETURN;
}

CML_API void CMLXYZtoLch (const CMLColorMachine* cm, CMLOutput lch , CMLInput xyz , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(lch, xyz, CML_Lch_NUMCHANNELS, CML_XYZ_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(*cm->XYZtoLab);
  CMLCMLabtoLch_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLXYZtoLuv (const CMLColorMachine* cm, CMLOutput luv , CMLInput xyz , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(luv, xyz, CML_Luv_NUMCHANNELS, CML_XYZ_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMXYZtoYxy);
  CMLCMYxytoYupvp_SB(cm, out, count, floatalign);
  CMLCMYupvptoLuv_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLXYZtoRGB (const CMLColorMachine* cm, CMLOutput rgb , CMLInput xyz , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(rgb, xyz, CML_RGB_NUMCHANNELS, CML_XYZ_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMXYZtoRGB);
  CML_CONVERTER_RETURN;
}

CML_API void CMLXYZtoYCbCr (const CMLColorMachine* cm, CMLOutput ycbcr, CMLInput xyz , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(ycbcr, xyz, CML_YCbCr_NUMCHANNELS, CML_XYZ_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMXYZtoRGB);
  CMLCMRGBtoYCbCr_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLXYZtoHSV (const CMLColorMachine* cm, CMLOutput hsv , CMLInput xyz , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(hsv, xyz, CML_HSV_NUMCHANNELS, CML_XYZ_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMXYZtoRGB);
  CMLCMRGBtoHSV_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLXYZtoHSL (const CMLColorMachine* cm, CMLOutput hsl , CMLInput xyz , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(hsl, xyz, CML_HSL_NUMCHANNELS, CML_XYZ_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMXYZtoRGB);
  CMLCMRGBtoHSV_SB(cm, out, count, floatalign);
  CMLCMHSVtoHSL_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLXYZtoCMYK(const CMLColorMachine* cm, CMLOutput cmyk, CMLInput xyz , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(cmyk, xyz, CML_CMYK_NUMCHANNELS, CML_XYZ_NUMCHANNELS);
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

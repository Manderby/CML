
#include "../CML.h"
#include "../StateMachine/CMLColorMachineState.h"
#include "../StateMachine/CMLConverterMacros.h"

// //////////////////////////
// Identity converter
// //////////////////////////

CML_API void CMLYCbCrtoYCbCr (const CMLColorMachine* cm, CMLOutput YCbCrd , CMLInput YCbCrs, CMLSize count){
  cm = cm; // no warning
  CML_CONVERTER_INOUT_PARAMETER(YCbCrd, YCbCrs, CML_YCbCr_NUMCHANNELS, CML_YCbCr_NUMCHANNELS);
  CML_CONVERTER_MEMCPY(CML_YCbCr_NUMCHANNELS);
  CML_CONVERTER_RETURN;
}


// //////////////////////////
// YCbCr to anything
// //////////////////////////

CML_API void CMLYCbCrtoXYZ (const CMLColorMachine* cm, CMLOutput xyz , CMLInput ycbcr , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(xyz, ycbcr, CML_XYZ_NUMCHANNELS, CML_YCbCr_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYCbCrtoRGB);
  CMLCMRGBtoXYZ_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLYCbCrtoYxy (const CMLColorMachine* cm, CMLOutput yxy , CMLInput ycbcr , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(yxy, ycbcr, CML_Yxy_NUMCHANNELS, CML_YCbCr_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYCbCrtoRGB);
  CMLCMRGBtoXYZ_SB(cm, out, count, floatalign);
  CMLCMXYZtoYxy_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLYCbCrtoYuv (const CMLColorMachine* cm, CMLOutput yuv , CMLInput ycbcr , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(yuv, ycbcr, CML_Yuv_NUMCHANNELS, CML_YCbCr_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYCbCrtoRGB);
  CMLCMRGBtoXYZ_SB(cm, out, count, floatalign);
  CMLCMXYZtoYxy_SB(cm, out, count, floatalign);
  CMLCMYxytoYupvp_SB(cm, out, count, floatalign);
  CMLCMYupvptoYuv_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLYCbCrtoYupvp (const CMLColorMachine* cm, CMLOutput yupvp , CMLInput ycbcr , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(yupvp, ycbcr, CML_Yupvp_NUMCHANNELS, CML_YCbCr_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYCbCrtoRGB);
  CMLCMRGBtoXYZ_SB(cm, out, count, floatalign);
  CMLCMXYZtoYxy_SB(cm, out, count, floatalign);
  CMLCMYxytoYupvp_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLYCbCrtoLab (const CMLColorMachine* cm, CMLOutput lab , CMLInput ycbcr , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(lab, ycbcr, CML_Lab_NUMCHANNELS, CML_YCbCr_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYCbCrtoRGB);
  CMLCMRGBtoXYZ_SB(cm, out, count, floatalign);
  (*cm->XYZtoLab_SB)(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLYCbCrtoLch (const CMLColorMachine* cm, CMLOutput lch , CMLInput ycbcr , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(lch, ycbcr, CML_Lch_NUMCHANNELS, CML_YCbCr_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYCbCrtoRGB);
  CMLCMRGBtoXYZ_SB(cm, out, count, floatalign);
  (*cm->XYZtoLab_SB)(cm, out, count, floatalign);
  CMLCMLabtoLch_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLYCbCrtoLuv (const CMLColorMachine* cm, CMLOutput luv , CMLInput ycbcr , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(luv, ycbcr, CML_Luv_NUMCHANNELS, CML_YCbCr_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYCbCrtoRGB);
  CMLCMRGBtoXYZ_SB(cm, out, count, floatalign);
  CMLCMXYZtoYxy_SB(cm, out, count, floatalign);
  CMLCMYxytoYupvp_SB(cm, out, count, floatalign);
  CMLCMYupvptoLuv_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLYCbCrtoRGB (const CMLColorMachine* cm, CMLOutput rgb , CMLInput ycbcr , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(rgb, ycbcr, CML_RGB_NUMCHANNELS, CML_YCbCr_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYCbCrtoRGB);
  CML_CONVERTER_RETURN;
}

CML_API void CMLYCbCrtoHSV (const CMLColorMachine* cm, CMLOutput hsv , CMLInput ycbcr , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(hsv, ycbcr, CML_HSV_NUMCHANNELS, CML_YCbCr_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYCbCrtoRGB);
  CMLCMRGBtoHSV_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLYCbCrtoHSL (const CMLColorMachine* cm, CMLOutput hsl , CMLInput ycbcr , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(hsl, ycbcr, CML_HSL_NUMCHANNELS, CML_YCbCr_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYCbCrtoRGB);
  CMLCMRGBtoHSV_SB(cm, out, count, floatalign);
  CMLCMHSVtoHSL_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLYCbCrtoCMYK(const CMLColorMachine* cm, CMLOutput cmyk, CMLInput ycbcr , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(cmyk, ycbcr, CML_CMYK_NUMCHANNELS, CML_YCbCr_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYCbCrtoRGB);
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


#include "../CML.h"
#include "../StateMachine/CMLColorMachineState.h"
#include "../StateMachine/CMLConverterMacros.h"







// //////////////////////////
// Identity converter
// //////////////////////////

CML_API void CMLYxytoYxy (const CMLColorMachine* cm, CMLOutput Yxyd , CMLInput Yxys, CMLSize count){
  cm = cm; // no warning
  CML_CONVERTER_INOUT_PARAMETER(Yxyd, Yxys, CML_Yxy_NUMCHANNELS, CML_Yxy_NUMCHANNELS);
  CML_CONVERTER_MEMCPY(CML_Yxy_NUMCHANNELS);
  CML_CONVERTER_RETURN;
}


// //////////////////////////
// Yxy to anything
// //////////////////////////

CML_API void CMLYxytoXYZ (const CMLColorMachine* cm, CMLOutput xyz , CMLInput yxy , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(xyz, yxy, CML_XYZ_NUMCHANNELS, CML_Yxy_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYxytoXYZ);
  CML_CONVERTER_RETURN;
}

CML_API void CMLYxytoYuv (const CMLColorMachine* cm, CMLOutput yuv , CMLInput yxy , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(yuv, yxy, CML_Yuv_NUMCHANNELS, CML_Yxy_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYxytoYupvp);
  CMLCMYupvptoYuv_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLYxytoYupvp (const CMLColorMachine* cm, CMLOutput yupvp , CMLInput yxy , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(yupvp, yxy, CML_Yupvp_NUMCHANNELS, CML_Yxy_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYxytoYupvp);
  CML_CONVERTER_RETURN;
}

CML_API void CMLYxytoLab (const CMLColorMachine* cm, CMLOutput lab , CMLInput yxy , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(lab, yxy, CML_Lab_NUMCHANNELS, CML_Yxy_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYxytoXYZ);
  (*cm->XYZtoLab_SB)(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLYxytoLch (const CMLColorMachine* cm, CMLOutput lch , CMLInput yxy , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(lch, yxy, CML_Lch_NUMCHANNELS, CML_Yxy_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYxytoXYZ);
  (*cm->XYZtoLab_SB)(cm, out, count, floatalign);
  CMLCMLabtoLch_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLYxytoLuv (const CMLColorMachine* cm, CMLOutput luv , CMLInput yxy , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(luv, yxy, CML_Luv_NUMCHANNELS, CML_Yxy_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYxytoYupvp);
  CMLCMYupvptoLuv_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLYxytoRGB (const CMLColorMachine* cm, CMLOutput rgb , CMLInput yxy , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(rgb, yxy, CML_RGB_NUMCHANNELS, CML_Yxy_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYxytoXYZ);
  CMLCMXYZtoRGB_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLYxytoYCbCr (const CMLColorMachine* cm, CMLOutput ycbcr , CMLInput yxy , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(ycbcr, yxy, CML_YCbCr_NUMCHANNELS, CML_Yxy_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYxytoXYZ);
  CMLCMXYZtoRGB_SB(cm, out, count, floatalign);
  CMLCMRGBtoYCbCr_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLYxytoHSV (const CMLColorMachine* cm, CMLOutput hsv , CMLInput yxy , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(hsv, yxy, CML_HSV_NUMCHANNELS, CML_Yxy_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYxytoXYZ);
  CMLCMXYZtoRGB_SB(cm, out, count, floatalign);
  CMLCMRGBtoHSV_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLYxytoHSL (const CMLColorMachine* cm, CMLOutput hsl , CMLInput yxy , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(hsl, yxy, CML_HSL_NUMCHANNELS, CML_Yxy_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYxytoXYZ);
  CMLCMXYZtoRGB_SB(cm, out, count, floatalign);
  CMLCMRGBtoHSV_SB(cm, out, count, floatalign);
  CMLCMHSVtoHSL_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLYxytoCMYK(const CMLColorMachine* cm, CMLOutput cmyk, CMLInput yxy , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(cmyk, yxy, CML_CMYK_NUMCHANNELS, CML_Yxy_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYxytoXYZ);
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

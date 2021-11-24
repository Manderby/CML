
#include "../CML.h"
#include "../StateMachine/CMLColorMachineState.h"
#include "../StateMachine/CMLConverterMacros.h"






// //////////////////////////
// Identity converter
// //////////////////////////

CML_API void CMLYupvptoYupvp (const CMLColorMachine* cm, CMLOutput Yupvpd , CMLInput Yupvps, size_t count){
  cm = cm; // no warning
  CML_CONVERTER_INOUT_PARAMETER(Yupvpd, Yupvps, CML_Yupvp_NUMCHANNELS, CML_Yupvp_NUMCHANNELS);
  CML_CONVERTER_MEMCPY(CML_Yupvp_NUMCHANNELS);
  CML_CONVERTER_RETURN;
}



// //////////////////////////
// Yupvp to anything
// //////////////////////////

CML_API void CMLYupvptoXYZ (const CMLColorMachine* cm, CMLOutput xyz , CMLInput yupvp , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(xyz, yupvp, CML_XYZ_NUMCHANNELS, CML_Yupvp_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYupvptoYxy);
  CMLCMYxytoXYZ_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLYupvptoYxy (const CMLColorMachine* cm, CMLOutput yxy , CMLInput yupvp , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(yxy, yupvp, CML_Yxy_NUMCHANNELS, CML_Yupvp_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYupvptoYxy);
  CML_CONVERTER_RETURN;
}

CML_API void CMLYupvptoYuv (const CMLColorMachine* cm, CMLOutput yuv , CMLInput yupvp , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(yuv, yupvp, CML_Yuv_NUMCHANNELS, CML_Yupvp_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYupvptoYuv);
  CML_CONVERTER_RETURN;
}

CML_API void CMLYupvptoLab (const CMLColorMachine* cm, CMLOutput lab , CMLInput yupvp , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(lab, yupvp, CML_Lab_NUMCHANNELS, CML_Yupvp_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYupvptoYxy);
  CMLCMYxytoXYZ_SB(cm, out, count, floatalign);
  (*cm->XYZtoLab_SB)(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLYupvptoLch (const CMLColorMachine* cm, CMLOutput lch , CMLInput yupvp , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(lch, yupvp, CML_Lch_NUMCHANNELS, CML_Yupvp_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYupvptoYxy);
  CMLCMYxytoXYZ_SB(cm, out, count, floatalign);
  (*cm->XYZtoLab_SB)(cm, out, count, floatalign);
  CMLCMLabtoLch_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLYupvptoLuv (const CMLColorMachine* cm, CMLOutput luv , CMLInput yupvp , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(luv, yupvp, CML_Luv_NUMCHANNELS, CML_Yupvp_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYupvptoLuv);
  CML_CONVERTER_RETURN;
}

CML_API void CMLYupvptoRGB (const CMLColorMachine* cm, CMLOutput rgb , CMLInput yupvp , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(rgb, yupvp, CML_RGB_NUMCHANNELS, CML_Yupvp_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYupvptoYxy);
  CMLCMYxytoXYZ_SB(cm, out, count, floatalign);
  CMLCMXYZtoRGB_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLYupvptoYCbCr (const CMLColorMachine* cm, CMLOutput ycbcr , CMLInput yupvp , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(ycbcr, yupvp, CML_YCbCr_NUMCHANNELS, CML_Yupvp_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYupvptoYxy);
  CMLCMYxytoXYZ_SB(cm, out, count, floatalign);
  CMLCMXYZtoRGB_SB(cm, out, count, floatalign);
  CMLCMRGBtoYCbCr_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLYupvptoHSV (const CMLColorMachine* cm, CMLOutput hsv , CMLInput yupvp , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(hsv, yupvp, CML_HSV_NUMCHANNELS, CML_Yupvp_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYupvptoYxy);
  CMLCMYxytoXYZ_SB(cm, out, count, floatalign);
  CMLCMXYZtoRGB_SB(cm, out, count, floatalign);
  CMLCMRGBtoHSV_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLYupvptoHSL (const CMLColorMachine* cm, CMLOutput hsl , CMLInput yupvp , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(hsl, yupvp, CML_HSL_NUMCHANNELS, CML_Yupvp_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYupvptoYxy);
  CMLCMYxytoXYZ_SB(cm, out, count, floatalign);
  CMLCMXYZtoRGB_SB(cm, out, count, floatalign);
  CMLCMRGBtoHSV_SB(cm, out, count, floatalign);
  CMLCMHSVtoHSL_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLYupvptoCMYK(const CMLColorMachine* cm, CMLOutput cmyk, CMLInput yupvp , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(cmyk, yupvp, CML_CMYK_NUMCHANNELS, CML_Yupvp_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYupvptoYxy);
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

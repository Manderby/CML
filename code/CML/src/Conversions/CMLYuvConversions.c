
#include "../CML.h"
#include "../StateMachine/CMLColorMachineState.h"
#include "../StateMachine/CMLConverterMacros.h"






// //////////////////////////
// Identity converter
// //////////////////////////

CML_API void CMLYuvtoYuv (const CMLColorMachine* cm, CMLOutput Yuvd , CMLInput Yuvs, size_t count){
  cm = cm; // no warning
  CML_CONVERTER_INOUT_PARAMETER(Yuvd, Yuvs, CML_Yuv_NUMCHANNELS, CML_Yuv_NUMCHANNELS);
  CML_CONVERTER_MEMCPY(CML_Yuv_NUMCHANNELS);
  CML_CONVERTER_RETURN;
}



// //////////////////////////
// Yuv to anything
// //////////////////////////

CML_API void CMLYuvtoXYZ (const CMLColorMachine* cm, CMLOutput xyz , CMLInput yuv , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(xyz, yuv, CML_XYZ_NUMCHANNELS, CML_Yuv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYuvtoYupvp);
  CMLCMYupvptoYxy_SB(cm, out, count, floatalign);
  CMLCMYxytoXYZ_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLYuvtoYxy (const CMLColorMachine* cm, CMLOutput yxy , CMLInput yuv , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(yxy, yuv, CML_Yxy_NUMCHANNELS, CML_Yuv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYuvtoYupvp);
  CMLCMYupvptoYxy_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLYuvtoYupvp (const CMLColorMachine* cm, CMLOutput yupvp , CMLInput yuv , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(yupvp, yuv, CML_Yupvp_NUMCHANNELS, CML_Yuv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYuvtoYupvp);
  CML_CONVERTER_RETURN;
}

CML_API void CMLYuvtoLab (const CMLColorMachine* cm, CMLOutput lab , CMLInput yuv , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(lab, yuv, CML_Lab_NUMCHANNELS, CML_Yuv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYuvtoYupvp);
  CMLCMYupvptoYxy_SB(cm, out, count, floatalign);
  CMLCMYxytoXYZ_SB(cm, out, count, floatalign);
  (*cm->XYZtoLab_SB)(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLYuvtoLch (const CMLColorMachine* cm, CMLOutput lch , CMLInput yuv , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(lch, yuv, CML_Lch_NUMCHANNELS, CML_Yuv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYuvtoYupvp);
  CMLCMYupvptoYxy_SB(cm, out, count, floatalign);
  CMLCMYxytoXYZ_SB(cm, out, count, floatalign);
  (*cm->XYZtoLab_SB)(cm, out, count, floatalign);
  CMLCMLabtoLch_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLYuvtoLuv (const CMLColorMachine* cm, CMLOutput luv , CMLInput yuv , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(luv, yuv, CML_Luv_NUMCHANNELS, CML_Yuv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYuvtoYupvp);
  CMLCMYupvptoLuv_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLYuvtoRGB (const CMLColorMachine* cm, CMLOutput rgb , CMLInput yuv , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(rgb, yuv, CML_RGB_NUMCHANNELS, CML_Yuv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYuvtoYupvp);
  CMLCMYupvptoYxy_SB(cm, out, count, floatalign);
  CMLCMYxytoXYZ_SB(cm, out, count, floatalign);
  CMLCMXYZtoRGB_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLYuvtoYCbCr (const CMLColorMachine* cm, CMLOutput ycbcr , CMLInput yuv , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(ycbcr, yuv, CML_YCbCr_NUMCHANNELS, CML_Yuv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYuvtoYupvp);
  CMLCMYupvptoYxy_SB(cm, out, count, floatalign);
  CMLCMYxytoXYZ_SB(cm, out, count, floatalign);
  CMLCMXYZtoRGB_SB(cm, out, count, floatalign);
  CMLCMRGBtoYCbCr_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLYuvtoHSV (const CMLColorMachine* cm, CMLOutput hsv , CMLInput yuv , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(hsv, yuv, CML_HSV_NUMCHANNELS, CML_Yuv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYuvtoYupvp);
  CMLCMYupvptoYxy_SB(cm, out, count, floatalign);
  CMLCMYxytoXYZ_SB(cm, out, count, floatalign);
  CMLCMXYZtoRGB_SB(cm, out, count, floatalign);
  CMLCMRGBtoHSV_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLYuvtoHSL (const CMLColorMachine* cm, CMLOutput hsl , CMLInput yuv , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(hsl, yuv, CML_HSL_NUMCHANNELS, CML_Yuv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYuvtoYupvp);
  CMLCMYupvptoYxy_SB(cm, out, count, floatalign);
  CMLCMYxytoXYZ_SB(cm, out, count, floatalign);
  CMLCMXYZtoRGB_SB(cm, out, count, floatalign);
  CMLCMRGBtoHSV_SB(cm, out, count, floatalign);
  CMLCMHSVtoHSL_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLYuvtoCMYK(const CMLColorMachine* cm, CMLOutput cmyk, CMLInput yuv , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(cmyk, yuv, CML_CMYK_NUMCHANNELS, CML_Yuv_NUMCHANNELS);
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


#include "../CML.h"
#include "../StateMachine/CMLColorMachineState.h"
#include "../StateMachine/CMLConverterMacros.h"



// //////////////////////////
// Identity converter
// //////////////////////////

CML_API void cmlYuvToYuv (const CMLColorMachine* cm, CMLOutput yuvd , CMLInput yuvs, size_t count){
  CML_UNUSED(cm);
  CML_CONVERTER_INOUT_PARAMETER(yuvd, yuvs, CML_Yuv_NUMCHANNELS, CML_Yuv_NUMCHANNELS);
  CML_CONVERTER_MEMCPY(CML_Yuv_NUMCHANNELS);
}



// //////////////////////////
// Yuv to anything
// //////////////////////////

CML_API void cmlYuvToXYZ (const CMLColorMachine* cm, CMLOutput xyz , CMLInput yuv , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(xyz, yuv, CML_XYZ_NUMCHANNELS, CML_Yuv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYuvtoYupvp);
  CMLCMYupvptoYxy_SB(cm, out, count, floatAlign);
  CMLCMYxytoXYZ_SB(cm, out, count, floatAlign);
}

CML_API void cmlYuvToYxy (const CMLColorMachine* cm, CMLOutput yxy , CMLInput yuv , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(yxy, yuv, CML_Yxy_NUMCHANNELS, CML_Yuv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYuvtoYupvp);
  CMLCMYupvptoYxy_SB(cm, out, count, floatAlign);
}

CML_API void cmlYuvToYupvp (const CMLColorMachine* cm, CMLOutput yupvp , CMLInput yuv , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(yupvp, yuv, CML_Yupvp_NUMCHANNELS, CML_Yuv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYuvtoYupvp);
}

CML_API void cmlYuvToLab (const CMLColorMachine* cm, CMLOutput lab , CMLInput yuv , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(lab, yuv, CML_Lab_NUMCHANNELS, CML_Yuv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYuvtoYupvp);
  CMLCMYupvptoYxy_SB(cm, out, count, floatAlign);
  CMLCMYxytoXYZ_SB(cm, out, count, floatAlign);
  (*cm->XYZtoLab_SB)(cm, out, count, floatAlign);
}

CML_API void cmlYuvToLch (const CMLColorMachine* cm, CMLOutput lch , CMLInput yuv , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(lch, yuv, CML_Lch_NUMCHANNELS, CML_Yuv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYuvtoYupvp);
  CMLCMYupvptoYxy_SB(cm, out, count, floatAlign);
  CMLCMYxytoXYZ_SB(cm, out, count, floatAlign);
  (*cm->XYZtoLab_SB)(cm, out, count, floatAlign);
  CMLCMLabtoLch_SB(cm, out, count, floatAlign);
}

CML_API void cmlYuvToLuv (const CMLColorMachine* cm, CMLOutput luv , CMLInput yuv , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(luv, yuv, CML_Luv_NUMCHANNELS, CML_Yuv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYuvtoYupvp);
  CMLCMYupvptoLuv_SB(cm, out, count, floatAlign);
}

CML_API void cmlYuvToRGB (const CMLColorMachine* cm, CMLOutput rgb , CMLInput yuv , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(rgb, yuv, CML_RGB_NUMCHANNELS, CML_Yuv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYuvtoYupvp);
  CMLCMYupvptoYxy_SB(cm, out, count, floatAlign);
  CMLCMYxytoXYZ_SB(cm, out, count, floatAlign);
  CMLCMXYZtoRGB_SB(cm, out, count, floatAlign);
}

CML_API void cmlYuvToYCbCr (const CMLColorMachine* cm, CMLOutput ycbcr , CMLInput yuv , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(ycbcr, yuv, CML_YCbCr_NUMCHANNELS, CML_Yuv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYuvtoYupvp);
  CMLCMYupvptoYxy_SB(cm, out, count, floatAlign);
  CMLCMYxytoXYZ_SB(cm, out, count, floatAlign);
  CMLCMXYZtoRGB_SB(cm, out, count, floatAlign);
  CMLCMRGBtoYCbCr_SB(cm, out, count, floatAlign);
}

CML_API void cmlYuvToHSV (const CMLColorMachine* cm, CMLOutput hsv , CMLInput yuv , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(hsv, yuv, CML_HSV_NUMCHANNELS, CML_Yuv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYuvtoYupvp);
  CMLCMYupvptoYxy_SB(cm, out, count, floatAlign);
  CMLCMYxytoXYZ_SB(cm, out, count, floatAlign);
  CMLCMXYZtoRGB_SB(cm, out, count, floatAlign);
  CMLCMRGBtoHSV_SB(cm, out, count, floatAlign);
}

CML_API void cmlYuvToHSL (const CMLColorMachine* cm, CMLOutput hsl , CMLInput yuv , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(hsl, yuv, CML_HSL_NUMCHANNELS, CML_Yuv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYuvtoYupvp);
  CMLCMYupvptoYxy_SB(cm, out, count, floatAlign);
  CMLCMYxytoXYZ_SB(cm, out, count, floatAlign);
  CMLCMXYZtoRGB_SB(cm, out, count, floatAlign);
  CMLCMRGBtoHSV_SB(cm, out, count, floatAlign);
  CMLCMHSVtoHSL_SB(cm, out, count, floatAlign);
}

CML_API void cmlYuvToCMYK(const CMLColorMachine* cm, CMLOutput cmyk, CMLInput yuv , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(cmyk, yuv, CML_CMYK_NUMCHANNELS, CML_Yuv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYuvtoYupvp);
  CMLCMYupvptoYxy_SB(cm, out, count, floatAlign);
  CMLCMYxytoXYZ_SB(cm, out, count, floatAlign);
  CMLCMXYZtoRGB_SB(cm, out, count, floatAlign);
  (*cm->RGBtoCMYK_SB)(cm, out, count, floatAlign);
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

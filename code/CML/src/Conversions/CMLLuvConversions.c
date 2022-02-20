
#include "../CML.h"
#include "../Internal/CMLColorMachineState.h"
#include "../Internal/CMLConverterMacros.h"



// //////////////////////////
// Identity converter
// //////////////////////////

CML_API void cmlLuvToLuv(const CMLColorMachine* cm, CMLOutput luvd, CMLInput luvs, size_t count){
  CML_UNUSED(cm);
  CML_CONVERTER_INOUT_PARAMETER(luvd, luvs, CML_Luv_NUMCHANNELS, CML_Luv_NUMCHANNELS);
  CML_CONVERTER_MEMCPY(CML_Luv_NUMCHANNELS);
}



// //////////////////////////
// Luv to anything
// //////////////////////////

CML_API void cmlLuvToXYZ(const CMLColorMachine* cm, CMLOutput xyz, CMLInput luv, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(xyz, luv, CML_XYZ_NUMCHANNELS, CML_Luv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(cml_CMLuvToYupvp);
  cml_CMYupvpToYxy_SB(cm, out, count, floatAlign);
  cml_CMYxyToXYZ_SB(cm, out, count, floatAlign);
}

CML_API void cmlLuvToYxy(const CMLColorMachine* cm, CMLOutput yxy, CMLInput luv, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(yxy, luv, CML_Yxy_NUMCHANNELS, CML_Luv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(cml_CMLuvToYupvp);
  cml_CMYupvpToYxy_SB(cm, out, count, floatAlign);
}

CML_API void cmlLuvToYuv(const CMLColorMachine* cm, CMLOutput yuv, CMLInput luv, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(yuv, luv, CML_Yuv_NUMCHANNELS, CML_Luv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(cml_CMLuvToYupvp);
  cml_CMYupvpToYuv_SB(cm, out, count, floatAlign);
}

CML_API void cmlLuvToYupvp(const CMLColorMachine* cm, CMLOutput yupvp, CMLInput luv, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(yupvp, luv, CML_Yupvp_NUMCHANNELS, CML_Luv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(cml_CMLuvToYupvp);
}

CML_API void cmlLuvToLab(const CMLColorMachine* cm, CMLOutput lab, CMLInput luv, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(lab, luv, CML_Lab_NUMCHANNELS, CML_Luv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(cml_CMLuvToYupvp);
  cml_CMYupvpToYxy_SB(cm, out, count, floatAlign);
  cml_CMYxyToXYZ_SB(cm, out, count, floatAlign);
  (*cm->XYZToLab_SB)(cm, out, count, floatAlign);
}

CML_API void cmlLuvToLch(const CMLColorMachine* cm, CMLOutput lch, CMLInput luv, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(lch, luv, CML_Lch_NUMCHANNELS, CML_Luv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(cml_CMLuvToYupvp);
  cml_CMYupvpToYxy_SB(cm, out, count, floatAlign);
  cml_CMYxyToXYZ_SB(cm, out, count, floatAlign);
  (*cm->XYZToLab_SB)(cm, out, count, floatAlign);
  cml_CMLabToLch_SB(cm, out, count, floatAlign);
}

CML_API void cmlLuvToRGB(const CMLColorMachine* cm, CMLOutput rgb, CMLInput luv, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(rgb, luv, CML_RGB_NUMCHANNELS, CML_Luv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(cml_CMLuvToYupvp);
  cml_CMYupvpToYxy_SB(cm, out, count, floatAlign);
  cml_CMYxyToXYZ_SB(cm, out, count, floatAlign);
  cml_CMXYZToRGB_SB(cm, out, count, floatAlign);
}

CML_API void cmlLuvToYCbCr(const CMLColorMachine* cm, CMLOutput ycbcr, CMLInput luv, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(ycbcr, luv, CML_YCbCr_NUMCHANNELS, CML_Luv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(cml_CMLuvToYupvp);
  cml_CMYupvpToYxy_SB(cm, out, count, floatAlign);
  cml_CMYxyToXYZ_SB(cm, out, count, floatAlign);
  cml_CMXYZToRGB_SB(cm, out, count, floatAlign);
  cml_CMRGBToYCbCr_SB(cm, out, count, floatAlign);
}

CML_API void cmlLuvToHSV(const CMLColorMachine* cm, CMLOutput hsv, CMLInput luv, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(hsv, luv, CML_HSV_NUMCHANNELS, CML_Luv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(cml_CMLuvToYupvp);
  cml_CMYupvpToYxy_SB(cm, out, count, floatAlign);
  cml_CMYxyToXYZ_SB(cm, out, count, floatAlign);
  cml_CMXYZToRGB_SB(cm, out, count, floatAlign);
  cml_CMRGBToHSV_SB(cm, out, count, floatAlign);
}

CML_API void cmlLuvToHSL(const CMLColorMachine* cm, CMLOutput hsl, CMLInput luv, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(hsl, luv, CML_HSL_NUMCHANNELS, CML_Luv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(cml_CMLuvToYupvp);
  cml_CMYupvpToYxy_SB(cm, out, count, floatAlign);
  cml_CMYxyToXYZ_SB(cm, out, count, floatAlign);
  cml_CMXYZToRGB_SB(cm, out, count, floatAlign);
  cml_CMRGBToHSV_SB(cm, out, count, floatAlign);
  cml_CMHSVToHSL_SB(cm, out, count, floatAlign);
}

CML_API void cmlLuvToCMYK(const CMLColorMachine* cm, CMLOutput cmyk, CMLInput luv, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(cmyk, luv, CML_CMYK_NUMCHANNELS, CML_Luv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(cml_CMLuvToYupvp);
  cml_CMYupvpToYxy_SB(cm, out, count, floatAlign);
  cml_CMYxyToXYZ_SB(cm, out, count, floatAlign);
  cml_CMXYZToRGB_SB(cm, out, count, floatAlign);
  (*cm->RGBToCMYK_SB)(cm, out, count, floatAlign);
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

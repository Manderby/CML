
#include "../CML.h"
#include "../Internal/CMLColorMachineState.h"
#include "../Internal/CMLConverterMacros.h"



// //////////////////////////
// Identity converter
// //////////////////////////

CML_API void cmlYcdToYcd(const CMLColorMachine* cm, CMLOutput ycdd, CMLInput ycds, size_t count){
  CML_UNUSED(cm);
  CML_CONVERTER_INOUT_PARAMETER(ycdd, ycds, CML_Ycd_NUMCHANNELS, CML_Ycd_NUMCHANNELS);
  CML_CONVERTER_MEMCPY(CML_Ycd_NUMCHANNELS);
}



// //////////////////////////
// Ycd to anything
// //////////////////////////

CML_API void cmlYcdToXYZ(const CMLColorMachine* cm, CMLOutput xyz, CMLInput ycd, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(xyz, ycd, CML_XYZ_NUMCHANNELS, CML_Ycd_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(cml_CMYcdToYuv);
  cml_CMYuvToYupvp_SB(cm, out, count, floatAlign);
  cml_CMYupvpToYxy_SB(cm, out, count, floatAlign);
  cml_CMYxyToXYZ_SB(cm, out, count, floatAlign);
}

CML_API void cmlYcdToYxy(const CMLColorMachine* cm, CMLOutput yxy, CMLInput ycd, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(yxy, ycd, CML_Yxy_NUMCHANNELS, CML_Ycd_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(cml_CMYcdToYuv);
  cml_CMYuvToYupvp_SB(cm, out, count, floatAlign);
  cml_CMYupvpToYxy_SB(cm, out, count, floatAlign);
}

CML_API void cmlYcdToYuv(const CMLColorMachine* cm, CMLOutput yuv, CMLInput ycd, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(yuv, ycd, CML_Ycd_NUMCHANNELS, CML_Ycd_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(cml_CMYcdToYuv);
}

CML_API void cmlYcdToYupvp(const CMLColorMachine* cm, CMLOutput yupvp, CMLInput ycd, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(yupvp, ycd, CML_Yupvp_NUMCHANNELS, CML_Ycd_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(cml_CMYcdToYuv);
  cml_CMYuvToYupvp_SB(cm, out, count, floatAlign);
}

CML_API void cmlYcdToLab(const CMLColorMachine* cm, CMLOutput lab, CMLInput ycd, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(lab, ycd, CML_Lab_NUMCHANNELS, CML_Ycd_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(cml_CMYcdToYuv);
  cml_CMYuvToYupvp_SB(cm, out, count, floatAlign);
  cml_CMYupvpToYxy_SB(cm, out, count, floatAlign);
  cml_CMYxyToXYZ_SB(cm, out, count, floatAlign);
  (*cm->XYZToLab_SB)(cm, out, count, floatAlign);
}

CML_API void cmlYcdToLch(const CMLColorMachine* cm, CMLOutput lch, CMLInput ycd, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(lch, ycd, CML_Lch_NUMCHANNELS, CML_Ycd_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(cml_CMYcdToYuv);
  cml_CMYuvToYupvp_SB(cm, out, count, floatAlign);
  cml_CMYupvpToYxy_SB(cm, out, count, floatAlign);
  cml_CMYxyToXYZ_SB(cm, out, count, floatAlign);
  (*cm->XYZToLab_SB)(cm, out, count, floatAlign);
  cml_CMLabToLch_SB(cm, out, count, floatAlign);
}

CML_API void cmlYcdToLuv(const CMLColorMachine* cm, CMLOutput luv, CMLInput ycd, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(luv, ycd, CML_Luv_NUMCHANNELS, CML_Ycd_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(cml_CMYcdToYuv);
  cml_CMYuvToYupvp_SB(cm, out, count, floatAlign);
  cml_CMYupvpToLuv_SB(cm, out, count, floatAlign);
}

CML_API void cmlYcdToRGB(const CMLColorMachine* cm, CMLOutput rgb, CMLInput ycd, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(rgb, ycd, CML_RGB_NUMCHANNELS, CML_Ycd_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(cml_CMYcdToYuv);
  cml_CMYuvToYupvp_SB(cm, out, count, floatAlign);
  cml_CMYupvpToYxy_SB(cm, out, count, floatAlign);
  cml_CMYxyToXYZ_SB(cm, out, count, floatAlign);
  cml_CMXYZToRGB_SB(cm, out, count, floatAlign);
}

CML_API void cmlYcdToYCbCr(const CMLColorMachine* cm, CMLOutput ycbcr, CMLInput ycd, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(ycbcr, ycd, CML_YCbCr_NUMCHANNELS, CML_Ycd_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(cml_CMYcdToYuv);
  cml_CMYuvToYupvp_SB(cm, out, count, floatAlign);
  cml_CMYupvpToYxy_SB(cm, out, count, floatAlign);
  cml_CMYxyToXYZ_SB(cm, out, count, floatAlign);
  cml_CMXYZToRGB_SB(cm, out, count, floatAlign);
  cml_CMRGBToYCbCr_SB(cm, out, count, floatAlign);
}

CML_API void cmlYcdToHSV(const CMLColorMachine* cm, CMLOutput hsv, CMLInput ycd, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(hsv, ycd, CML_HSV_NUMCHANNELS, CML_Ycd_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(cml_CMYcdToYuv);
  cml_CMYuvToYupvp_SB(cm, out, count, floatAlign);
  cml_CMYupvpToYxy_SB(cm, out, count, floatAlign);
  cml_CMYxyToXYZ_SB(cm, out, count, floatAlign);
  cml_CMXYZToRGB_SB(cm, out, count, floatAlign);
  cml_CMRGBToHSV_SB(cm, out, count, floatAlign);
}

CML_API void cmlYcdToHSL(const CMLColorMachine* cm, CMLOutput hsl, CMLInput ycd, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(hsl, ycd, CML_HSL_NUMCHANNELS, CML_Ycd_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(cml_CMYcdToYuv);
  cml_CMYuvToYupvp_SB(cm, out, count, floatAlign);
  cml_CMYupvpToYxy_SB(cm, out, count, floatAlign);
  cml_CMYxyToXYZ_SB(cm, out, count, floatAlign);
  cml_CMXYZToRGB_SB(cm, out, count, floatAlign);
  cml_CMRGBToHSV_SB(cm, out, count, floatAlign);
  cml_CMHSVToHSL_SB(cm, out, count, floatAlign);
}

CML_API void cmlYcdToCMYK(const CMLColorMachine* cm, CMLOutput cmyk, CMLInput ycd, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(cmyk, ycd, CML_CMYK_NUMCHANNELS, CML_Ycd_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(cml_CMYcdToYuv);
  cml_CMYuvToYupvp_SB(cm, out, count, floatAlign);
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

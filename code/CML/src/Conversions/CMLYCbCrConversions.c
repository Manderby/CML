
#include "../CML.h"
#include "../Internal/CMLColorMachineState.h"
#include "../Internal/CMLConverterMacros.h"



// //////////////////////////
// Identity converter
// //////////////////////////

CML_API void cmlYCbCrToYCbCr(const CMLColorMachine* cm, CMLOutput ycbcrd, CMLInput ycbcrs, size_t count){
  CML_UNUSED(cm);
  CML_CONVERTER_INOUT_PARAMETER(ycbcrd, ycbcrs, CML_YCbCr_NUMCHANNELS, CML_YCbCr_NUMCHANNELS);
  CML_CONVERTER_MEMCPY(CML_YCbCr_NUMCHANNELS);
}



// //////////////////////////
// YCbCr to anything
// //////////////////////////

CML_API void cmlYCbCrToXYZ(const CMLColorMachine* cm, CMLOutput xyz, CMLInput ycbcr, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(xyz, ycbcr, CML_XYZ_NUMCHANNELS, CML_YCbCr_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(cml_CMYCbCrToRGB);
  cml_CMRGBToXYZ_SB(cm, out, count, floatAlign);
}

CML_API void cmlYCbCrToYxy(const CMLColorMachine* cm, CMLOutput yxy, CMLInput ycbcr, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(yxy, ycbcr, CML_Yxy_NUMCHANNELS, CML_YCbCr_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(cml_CMYCbCrToRGB);
  cml_CMRGBToXYZ_SB(cm, out, count, floatAlign);
  cml_CMXYZToYxy_SB(cm, out, count, floatAlign);
}

CML_API void cmlYCbCrToYuv(const CMLColorMachine* cm, CMLOutput yuv, CMLInput ycbcr, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(yuv, ycbcr, CML_Yuv_NUMCHANNELS, CML_YCbCr_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(cml_CMYCbCrToRGB);
  cml_CMRGBToXYZ_SB(cm, out, count, floatAlign);
  cml_CMXYZToYxy_SB(cm, out, count, floatAlign);
  cml_CMYxyToYupvp_SB(cm, out, count, floatAlign);
  cml_CMYupvpToYuv_SB(cm, out, count, floatAlign);
}

CML_API void cmlYCbCrToYupvp(const CMLColorMachine* cm, CMLOutput yupvp, CMLInput ycbcr, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(yupvp, ycbcr, CML_Yupvp_NUMCHANNELS, CML_YCbCr_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(cml_CMYCbCrToRGB);
  cml_CMRGBToXYZ_SB(cm, out, count, floatAlign);
  cml_CMXYZToYxy_SB(cm, out, count, floatAlign);
  cml_CMYxyToYupvp_SB(cm, out, count, floatAlign);
}

CML_API void cmlYCbCrToLab(const CMLColorMachine* cm, CMLOutput lab, CMLInput ycbcr, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(lab, ycbcr, CML_Lab_NUMCHANNELS, CML_YCbCr_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(cml_CMYCbCrToRGB);
  cml_CMRGBToXYZ_SB(cm, out, count, floatAlign);
  (*cm->XYZToLab_SB)(cm, out, count, floatAlign);
}

CML_API void cmlYCbCrToLch(const CMLColorMachine* cm, CMLOutput lch, CMLInput ycbcr, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(lch, ycbcr, CML_Lch_NUMCHANNELS, CML_YCbCr_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(cml_CMYCbCrToRGB);
  cml_CMRGBToXYZ_SB(cm, out, count, floatAlign);
  (*cm->XYZToLab_SB)(cm, out, count, floatAlign);
  cml_CMLabToLch_SB(cm, out, count, floatAlign);
}

CML_API void cmlYCbCrToLuv(const CMLColorMachine* cm, CMLOutput luv, CMLInput ycbcr, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(luv, ycbcr, CML_Luv_NUMCHANNELS, CML_YCbCr_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(cml_CMYCbCrToRGB);
  cml_CMRGBToXYZ_SB(cm, out, count, floatAlign);
  cml_CMXYZToYxy_SB(cm, out, count, floatAlign);
  cml_CMYxyToYupvp_SB(cm, out, count, floatAlign);
  cml_CMYupvpToLuv_SB(cm, out, count, floatAlign);
}

CML_API void cmlYCbCrToRGB(const CMLColorMachine* cm, CMLOutput rgb, CMLInput ycbcr, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(rgb, ycbcr, CML_RGB_NUMCHANNELS, CML_YCbCr_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(cml_CMYCbCrToRGB);
}

CML_API void cmlYCbCrToHSV(const CMLColorMachine* cm, CMLOutput hsv, CMLInput ycbcr, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(hsv, ycbcr, CML_HSV_NUMCHANNELS, CML_YCbCr_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(cml_CMYCbCrToRGB);
  cml_CMRGBToHSV_SB(cm, out, count, floatAlign);
}

CML_API void cmlYCbCrToHSL(const CMLColorMachine* cm, CMLOutput hsl, CMLInput ycbcr, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(hsl, ycbcr, CML_HSL_NUMCHANNELS, CML_YCbCr_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(cml_CMYCbCrToRGB);
  cml_CMRGBToHSV_SB(cm, out, count, floatAlign);
  cml_CMHSVToHSL_SB(cm, out, count, floatAlign);
}

CML_API void cmlYCbCrToCMYK(const CMLColorMachine* cm, CMLOutput cmyk, CMLInput ycbcr, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(cmyk, ycbcr, CML_CMYK_NUMCHANNELS, CML_YCbCr_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(cml_CMYCbCrToRGB);
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

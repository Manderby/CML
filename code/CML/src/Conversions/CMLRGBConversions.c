
#include "../CML.h"
#include "../Internal/CMLColorMachineState.h"
#include "../Internal/CMLConverterMacros.h"



// //////////////////////////
// Identity converter
// //////////////////////////

CML_API void cmlRGBToRGB(const CMLColorMachine* cm, CMLOutput rgbd, CMLInput rgbs, size_t count){
  CML_UNUSED(cm);
  CML_CONVERTER_INOUT_PARAMETER(rgbd, rgbs, CML_RGB_CHANNEL_COUNT, CML_RGB_CHANNEL_COUNT);
  CML_CONVERTER_MEMCPY(CML_RGB_CHANNEL_COUNT);
}



// //////////////////////////
// RGB to anything
// //////////////////////////

CML_API void cmlRGBToCMYK(const CMLColorMachine* cm, CMLOutput cmyk, CMLInput rgb, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(cmyk, rgb, CML_CMYK_CHANNEL_COUNT, CML_RGB_CHANNEL_COUNT);
  CML_CONVERTER_FIRST_STEP(*cm->RGBToCMYK);
}

CML_API void cmlRGBToHSL(const CMLColorMachine* cm, CMLOutput hsl, CMLInput rgb, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(hsl, rgb, CML_HSL_CHANNEL_COUNT, CML_RGB_CHANNEL_COUNT);
  CML_CONVERTER_FIRST_STEP(cml_CMRGBToHSV);
  cml_CMHSVToHSL_SB(cm, out, count, floatAlign);
}

CML_API void cmlRGBToHSV(const CMLColorMachine* cm, CMLOutput hsv, CMLInput rgb, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(hsv, rgb, CML_HSV_CHANNEL_COUNT, CML_RGB_CHANNEL_COUNT);
  CML_CONVERTER_FIRST_STEP(cml_CMRGBToHSV);
}

CML_API void cmlRGBToLab(const CMLColorMachine* cm, CMLOutput lab, CMLInput rgb, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(lab, rgb, CML_Lab_CHANNEL_COUNT, CML_RGB_CHANNEL_COUNT);
  CML_CONVERTER_FIRST_STEP(cml_CMRGBToXYZ);
  (*cm->XYZToLab_SB)(cm, out, count, floatAlign);
}

CML_API void cmlRGBToLch(const CMLColorMachine* cm, CMLOutput lch, CMLInput rgb, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(lch, rgb, CML_Lch_CHANNEL_COUNT, CML_RGB_CHANNEL_COUNT);
  CML_CONVERTER_FIRST_STEP(cml_CMRGBToXYZ);
  (*cm->XYZToLab_SB)(cm, out, count, floatAlign);
  cml_CMLabToLch_SB(cm, out, count, floatAlign);
}

CML_API void cmlRGBToLuv(const CMLColorMachine* cm, CMLOutput luv, CMLInput rgb, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(luv, rgb, CML_Luv_CHANNEL_COUNT, CML_RGB_CHANNEL_COUNT);
  CML_CONVERTER_FIRST_STEP(cml_CMRGBToXYZ);
  cml_CMXYZToYxy_SB(cm, out, count, floatAlign);
  cml_CMYxyToYupvp_SB(cm, out, count, floatAlign);
  cml_CMYupvpToLuv_SB(cm, out, count, floatAlign);
}

CML_API void cmlRGBToXYZ(const CMLColorMachine* cm, CMLOutput xyz, CMLInput rgb, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(xyz, rgb, CML_XYZ_CHANNEL_COUNT, CML_RGB_CHANNEL_COUNT);
  CML_CONVERTER_FIRST_STEP(cml_CMRGBToXYZ);
}

CML_API void cmlRGBToYCbCr(const CMLColorMachine* cm, CMLOutput ycbcr, CMLInput rgb, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(ycbcr, rgb, CML_YCbCr_CHANNEL_COUNT, CML_RGB_CHANNEL_COUNT);
  CML_CONVERTER_FIRST_STEP(cml_CMRGBToYCbCr);
}

CML_API void cmlRGBToYcd(const CMLColorMachine* cm, CMLOutput ycd, CMLInput rgb, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(ycd, rgb, CML_Ycd_CHANNEL_COUNT, CML_RGB_CHANNEL_COUNT);
  CML_CONVERTER_FIRST_STEP(cml_CMRGBToXYZ);
  cml_CMXYZToYxy_SB(cm, out, count, floatAlign);
  cml_CMYxyToYupvp_SB(cm, out, count, floatAlign);
  cml_CMYupvpToYuv_SB(cm, out, count, floatAlign);
  cml_CMYuvToYcd_SB(cm, out, count, floatAlign);
}

CML_API void cmlRGBToYupvp(const CMLColorMachine* cm, CMLOutput yupvp, CMLInput rgb, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(yupvp, rgb, CML_Yupvp_CHANNEL_COUNT, CML_RGB_CHANNEL_COUNT);
  CML_CONVERTER_FIRST_STEP(cml_CMRGBToXYZ);
  cml_CMXYZToYxy_SB(cm, out, count, floatAlign);
  cml_CMYxyToYupvp_SB(cm, out, count, floatAlign);
}

CML_API void cmlRGBToYuv(const CMLColorMachine* cm, CMLOutput yuv, CMLInput rgb, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(yuv, rgb, CML_Yuv_CHANNEL_COUNT, CML_RGB_CHANNEL_COUNT);
  CML_CONVERTER_FIRST_STEP(cml_CMRGBToXYZ);
  cml_CMXYZToYxy_SB(cm, out, count, floatAlign);
  cml_CMYxyToYupvp_SB(cm, out, count, floatAlign);
  cml_CMYupvpToYuv_SB(cm, out, count, floatAlign);
}

CML_API void cmlRGBToYxy(const CMLColorMachine* cm, CMLOutput yxy, CMLInput rgb, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(yxy, rgb, CML_Yxy_CHANNEL_COUNT, CML_RGB_CHANNEL_COUNT);
  CML_CONVERTER_FIRST_STEP(cml_CMRGBToXYZ);
  cml_CMXYZToYxy_SB(cm, out, count, floatAlign);
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

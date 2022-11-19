
#include "../CML.h"
#include "../Internal/CMLColorMachineState.h"
#include "../Internal/CMLConverterMacros.h"



// //////////////////////////
// Identity converter
// //////////////////////////

CML_API void cmlCMYKToCMYK(const CMLColorMachine* cm, CMLOutput cmykd, CMLInput cmyks, size_t count){
  CML_UNUSED(cm);
  CML_CONVERTER_INOUT_PARAMETER(cmykd, cmyks, CML_CMYK_CHANNEL_COUNT, CML_CMYK_CHANNEL_COUNT);
  CML_CONVERTER_MEMCPY(CML_CMYK_CHANNEL_COUNT);
}



// //////////////////////////
// CMYK to anything
// //////////////////////////

CML_API void cmlCMYKToHSL(const CMLColorMachine* cm, CMLOutput hsl, CMLInput cmyk, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(hsl, cmyk, CML_HSL_CHANNEL_COUNT, CML_CMYK_CHANNEL_COUNT);
  CML_CONVERTER_FIRST_STEP(*cm->CMYKToRGB);
  cml_CMRGBToHSV_SB(cm, out, count, floatAlign);
  cml_CMHSVToHSL_SB(cm, out, count, floatAlign);
}

CML_API void cmlCMYKToHSV(const CMLColorMachine* cm, CMLOutput hsv, CMLInput cmyk, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(hsv, cmyk, CML_HSV_CHANNEL_COUNT, CML_CMYK_CHANNEL_COUNT);
  CML_CONVERTER_FIRST_STEP(*cm->CMYKToRGB);
  cml_CMRGBToHSV_SB(cm, out, count, floatAlign);
}

CML_API void cmlCMYKToLab(const CMLColorMachine* cm, CMLOutput lab, CMLInput cmyk, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(lab, cmyk, CML_Lab_CHANNEL_COUNT, CML_CMYK_CHANNEL_COUNT);
  CML_CONVERTER_FIRST_STEP(*cm->CMYKToRGB);
  cml_CMRGBToXYZ_SB(cm, out, count, floatAlign);
  (*cm->XYZToLab_SB)(cm, out, count, floatAlign);
}

CML_API void cmlCMYKToLch(const CMLColorMachine* cm, CMLOutput lch, CMLInput cmyk, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(lch, cmyk, CML_Lch_CHANNEL_COUNT, CML_CMYK_CHANNEL_COUNT);
  CML_CONVERTER_FIRST_STEP(*cm->CMYKToRGB);
  cml_CMRGBToXYZ_SB(cm, out, count, floatAlign);
  (*cm->XYZToLab_SB)(cm, out, count, floatAlign);
  cml_CMLabToLch_SB(cm, out, count, floatAlign);
}

CML_API void cmlCMYKToLuv(const CMLColorMachine* cm, CMLOutput luv, CMLInput cmyk, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(luv, cmyk, CML_Luv_CHANNEL_COUNT, CML_CMYK_CHANNEL_COUNT);
  CML_CONVERTER_FIRST_STEP(*cm->CMYKToRGB);
  cml_CMRGBToXYZ_SB(cm, out, count, floatAlign);
  cml_CMXYZToYxy_SB(cm, out, count, floatAlign);
  cml_CMYxyToYupvp_SB(cm, out, count, floatAlign);
  cml_CMYupvpToLuv_SB(cm, out, count, floatAlign);
}

CML_API void cmlCMYKToRGB(const CMLColorMachine* cm, CMLOutput rgb, CMLInput cmyk, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(rgb, cmyk, CML_RGB_CHANNEL_COUNT, CML_CMYK_CHANNEL_COUNT);
  CML_CONVERTER_FIRST_STEP(*cm->CMYKToRGB);
}

CML_API void cmlCMYKToUVW(const CMLColorMachine* cm, CMLOutput uvw, CMLInput cmyk, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(uvw, cmyk, CML_RGB_CHANNEL_COUNT, CML_CMYK_CHANNEL_COUNT);
  CML_CONVERTER_FIRST_STEP(*cm->CMYKToRGB);
  cml_CMRGBToXYZ_SB(cm, out, count, floatAlign);
  cml_CMXYZToYxy_SB(cm, out, count, floatAlign);
  cml_CMYxyToYupvp_SB(cm, out, count, floatAlign);
  cml_CMYupvpToYuv_SB(cm, out, count, floatAlign);
  cml_CMYuvToUVW_SB(cm, out, count, floatAlign);
}

CML_API void cmlCMYKToXYZ(const CMLColorMachine* cm, CMLOutput xyz, CMLInput cmyk, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(xyz, cmyk, CML_XYZ_CHANNEL_COUNT, CML_CMYK_CHANNEL_COUNT);
  CML_CONVERTER_FIRST_STEP(*cm->CMYKToRGB);
  cml_CMRGBToXYZ_SB(cm, out, count, floatAlign);
}

CML_API void cmlCMYKToYCbCr(const CMLColorMachine* cm, CMLOutput ycbcr, CMLInput cmyk, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(ycbcr, cmyk, CML_YCbCr_CHANNEL_COUNT, CML_CMYK_CHANNEL_COUNT);
  CML_CONVERTER_FIRST_STEP(*cm->CMYKToRGB);
  cml_CMRGBToYCbCr_SB(cm, out, count, floatAlign);
}

CML_API void cmlCMYKToYcd(const CMLColorMachine* cm, CMLOutput ycd, CMLInput cmyk, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(ycd, cmyk, CML_Ycd_CHANNEL_COUNT, CML_CMYK_CHANNEL_COUNT);
  CML_CONVERTER_FIRST_STEP(*cm->CMYKToRGB);
  cml_CMRGBToXYZ_SB(cm, out, count, floatAlign);
  cml_CMXYZToYxy_SB(cm, out, count, floatAlign);
  cml_CMYxyToYupvp_SB(cm, out, count, floatAlign);
  cml_CMYupvpToYuv_SB(cm, out, count, floatAlign);
  cml_CMYuvToYcd_SB(cm, out, count, floatAlign);
}

CML_API void cmlCMYKToYupvp(const CMLColorMachine* cm, CMLOutput yupvp, CMLInput cmyk, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(yupvp, cmyk, CML_Yupvp_CHANNEL_COUNT, CML_CMYK_CHANNEL_COUNT);
  CML_CONVERTER_FIRST_STEP(*cm->CMYKToRGB);
  cml_CMRGBToXYZ_SB(cm, out, count, floatAlign);
  cml_CMXYZToYxy_SB(cm, out, count, floatAlign);
  cml_CMYxyToYupvp_SB(cm, out, count, floatAlign);
}

CML_API void cmlCMYKToYuv(const CMLColorMachine* cm, CMLOutput yuv, CMLInput cmyk, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(yuv, cmyk, CML_Yuv_CHANNEL_COUNT, CML_CMYK_CHANNEL_COUNT);
  CML_CONVERTER_FIRST_STEP(*cm->CMYKToRGB);
  cml_CMRGBToXYZ_SB(cm, out, count, floatAlign);
  cml_CMXYZToYxy_SB(cm, out, count, floatAlign);
  cml_CMYxyToYupvp_SB(cm, out, count, floatAlign);
  cml_CMYupvpToYuv_SB(cm, out, count, floatAlign);
}

CML_API void cmlCMYKToYxy(const CMLColorMachine* cm, CMLOutput yxy, CMLInput cmyk, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(yxy, cmyk, CML_Yxy_CHANNEL_COUNT, CML_CMYK_CHANNEL_COUNT);
  CML_CONVERTER_FIRST_STEP(*cm->CMYKToRGB);
  cml_CMRGBToXYZ_SB(cm, out, count, floatAlign);
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


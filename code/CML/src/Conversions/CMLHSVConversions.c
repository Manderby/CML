
#include "../CML.h"
#include "../Internal/CMLColorMachineState.h"
#include "../Internal/CMLConverterMacros.h"



// //////////////////////////
// Identity converter
// //////////////////////////

CML_API void cmlHSVToHSV (const CMLColorMachine* cm, CMLOutput hsvd, CMLInput hsvs, size_t count){
  CML_UNUSED(cm);
  CML_CONVERTER_INOUT_PARAMETER(hsvd, hsvs, CML_HSV_NUMCHANNELS, CML_HSV_NUMCHANNELS);
  CML_CONVERTER_MEMCPY(CML_HSV_NUMCHANNELS);
}



// //////////////////////////
// HSV to anything
// //////////////////////////

CML_API void cmlHSVToXYZ (const CMLColorMachine* cm, CMLOutput xyz, CMLInput hsv, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(xyz, hsv, CML_XYZ_NUMCHANNELS, CML_HSV_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMHSVToRGB);
  CMLCMRGBToXYZ_SB(cm, out, count, floatAlign);
}

CML_API void cmlHSVToYuv (const CMLColorMachine* cm, CMLOutput yuv, CMLInput hsv, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(yuv, hsv, CML_Yuv_NUMCHANNELS, CML_HSV_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMHSVToRGB);
  CMLCMRGBToXYZ_SB(cm, out, count, floatAlign);
  CMLCMXYZToYxy_SB(cm, out, count, floatAlign);
  CMLCMYxyToYupvp_SB(cm, out, count, floatAlign);
  CMLCMYupvpToYuv_SB(cm, out, count, floatAlign);
}

CML_API void cmlHSVToYupvp (const CMLColorMachine* cm, CMLOutput yupvp, CMLInput hsv, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(yupvp, hsv, CML_Yupvp_NUMCHANNELS, CML_HSV_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMHSVToRGB);
  CMLCMRGBToXYZ_SB(cm, out, count, floatAlign);
  CMLCMXYZToYxy_SB(cm, out, count, floatAlign);
  CMLCMYxyToYupvp_SB(cm, out, count, floatAlign);
}

CML_API void cmlHSVToYxy (const CMLColorMachine* cm, CMLOutput yxy, CMLInput hsv, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(yxy, hsv, CML_Yxy_NUMCHANNELS, CML_HSV_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMHSVToRGB);
  CMLCMRGBToXYZ_SB(cm, out, count, floatAlign);
  CMLCMXYZToYxy_SB(cm, out, count, floatAlign);
}

CML_API void cmlHSVToLab (const CMLColorMachine* cm, CMLOutput lab, CMLInput hsv, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(lab, hsv, CML_Lab_NUMCHANNELS, CML_HSV_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMHSVToRGB);
  CMLCMRGBToXYZ_SB(cm, out, count, floatAlign);
  (*cm->XYZToLab_SB)(cm, out, count, floatAlign);
}

CML_API void cmlHSVToLch (const CMLColorMachine* cm, CMLOutput lch, CMLInput hsv, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(lch, hsv, CML_Lch_NUMCHANNELS, CML_HSV_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMHSVToRGB);
  CMLCMRGBToXYZ_SB(cm, out, count, floatAlign);
  (*cm->XYZToLab_SB)(cm, out, count, floatAlign);
  CMLCMLabToLch_SB(cm, out, count, floatAlign);
}

CML_API void cmlHSVToLuv (const CMLColorMachine* cm, CMLOutput luv, CMLInput hsv, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(luv, hsv, CML_Luv_NUMCHANNELS, CML_HSV_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMHSVToRGB);
  CMLCMRGBToXYZ_SB(cm, out, count, floatAlign);
  CMLCMXYZToYxy_SB(cm, out, count, floatAlign);
  CMLCMYxyToYupvp_SB(cm, out, count, floatAlign);
  CMLCMYupvpToLuv_SB(cm, out, count, floatAlign);
}

CML_API void cmlHSVToRGB (const CMLColorMachine* cm, CMLOutput rgb, CMLInput hsv, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(rgb, hsv, CML_RGB_NUMCHANNELS, CML_HSV_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMHSVToRGB);
}

CML_API void cmlHSVToYCbCr (const CMLColorMachine* cm, CMLOutput ycbcr, CMLInput hsv, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(ycbcr, hsv, CML_YCbCr_NUMCHANNELS, CML_HSV_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMHSVToRGB);
  CMLCMRGBToYCbCr_SB(cm, out, count, floatAlign);
}

CML_API void cmlHSVToHSL (const CMLColorMachine* cm, CMLOutput hsl, CMLInput hsv, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(hsl, hsv, CML_HSL_NUMCHANNELS, CML_HSV_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMHSVToHSL);
}

CML_API void cmlHSVToCMYK(const CMLColorMachine* cm, CMLOutput cmyk, CMLInput hsv, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(cmyk, hsv, CML_CMYK_NUMCHANNELS, CML_HSV_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMHSVToRGB);
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

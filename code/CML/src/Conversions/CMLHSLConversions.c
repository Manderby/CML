
#include "../CML.h"
#include "../Internal/CMLColorMachineState.h"
#include "../Internal/CMLConverterMacros.h"



// //////////////////////////
// Identity converter
// //////////////////////////

CML_API void cmlHSLToHSL (const CMLColorMachine* cm, CMLOutput hsld, CMLInput hsls, size_t count){
  CML_UNUSED(cm);
  CML_CONVERTER_INOUT_PARAMETER(hsld, hsls, CML_HSL_NUMCHANNELS, CML_HSL_NUMCHANNELS);
  CML_CONVERTER_MEMCPY(CML_HSL_NUMCHANNELS);
}



// //////////////////////////
// HSL to anything
// //////////////////////////

CML_API void cmlHSLToXYZ (const CMLColorMachine* cm, CMLOutput xyz, CMLInput hsl, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(xyz, hsl, CML_XYZ_NUMCHANNELS, CML_HSL_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMHSLToHSV);
  CMLCMHSVToRGB_SB(cm, out, count, floatAlign);
  CMLCMRGBToXYZ_SB(cm, out, count, floatAlign);
}

CML_API void cmlHSLToYuv (const CMLColorMachine* cm, CMLOutput yuv, CMLInput hsl, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(yuv, hsl, CML_Yuv_NUMCHANNELS, CML_HSL_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMHSLToHSV);
  CMLCMHSVToRGB_SB(cm, out, count, floatAlign);
  CMLCMRGBToXYZ_SB(cm, out, count, floatAlign);
  CMLCMXYZToYxy_SB(cm, out, count, floatAlign);
  CMLCMYxyToYupvp_SB(cm, out, count, floatAlign);
  CMLCMYupvpToYuv_SB(cm, out, count, floatAlign);
}

CML_API void cmlHSLToYupvp (const CMLColorMachine* cm, CMLOutput yupvp, CMLInput hsl, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(yupvp, hsl, CML_Yupvp_NUMCHANNELS, CML_HSL_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMHSLToHSV);
  CMLCMHSVToRGB_SB(cm, out, count, floatAlign);
  CMLCMRGBToXYZ_SB(cm, out, count, floatAlign);
  CMLCMXYZToYxy_SB(cm, out, count, floatAlign);
  CMLCMYxyToYupvp_SB(cm, out, count, floatAlign);
}

CML_API void cmlHSLToYxy (const CMLColorMachine* cm, CMLOutput yxy, CMLInput hsl, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(yxy, hsl, CML_Yxy_NUMCHANNELS, CML_HSL_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMHSLToHSV);
  CMLCMHSVToRGB_SB(cm, out, count, floatAlign);
  CMLCMRGBToXYZ_SB(cm, out, count, floatAlign);
  CMLCMXYZToYxy_SB(cm, out, count, floatAlign);
}

CML_API void cmlHSLToLab (const CMLColorMachine* cm, CMLOutput lab, CMLInput hsl, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(lab, hsl, CML_Lab_NUMCHANNELS, CML_HSL_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMHSLToHSV);
  CMLCMHSVToRGB_SB(cm, out, count, floatAlign);
  CMLCMRGBToXYZ_SB(cm, out, count, floatAlign);
  (*cm->XYZToLab_SB)(cm, out, count, floatAlign);
}

CML_API void cmlHSLToLch (const CMLColorMachine* cm, CMLOutput lch, CMLInput hsl, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(lch, hsl, CML_Lch_NUMCHANNELS, CML_HSL_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMHSLToHSV);
  CMLCMHSVToRGB_SB(cm, out, count, floatAlign);
  CMLCMRGBToXYZ_SB(cm, out, count, floatAlign);
  (*cm->XYZToLab_SB)(cm, out, count, floatAlign);
  CMLCMLabToLch_SB(cm, out, count, floatAlign);
}

CML_API void cmlHSLToLuv (const CMLColorMachine* cm, CMLOutput luv, CMLInput hsl, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(luv, hsl, CML_Luv_NUMCHANNELS, CML_HSL_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMHSLToHSV);
  CMLCMHSVToRGB_SB(cm, out, count, floatAlign);
  CMLCMRGBToXYZ_SB(cm, out, count, floatAlign);
  CMLCMXYZToYxy_SB(cm, out, count, floatAlign);
  CMLCMYxyToYupvp_SB(cm, out, count, floatAlign);
  CMLCMYupvpToLuv_SB(cm, out, count, floatAlign);
}

CML_API void cmlHSLToRGB (const CMLColorMachine* cm, CMLOutput rgb, CMLInput hsl, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(rgb, hsl, CML_RGB_NUMCHANNELS, CML_HSL_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMHSLToHSV);
  CMLCMHSVToRGB_SB(cm, out, count, floatAlign);
}

CML_API void cmlHSLToYCbCr (const CMLColorMachine* cm, CMLOutput ycbcr, CMLInput hsl, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(ycbcr, hsl, CML_YCbCr_NUMCHANNELS, CML_HSL_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMHSLToHSV);
  CMLCMHSVToRGB_SB(cm, out, count, floatAlign);
  CMLCMRGBToYCbCr_SB(cm, out, count, floatAlign);
}

CML_API void cmlHSLToHSV (const CMLColorMachine* cm, CMLOutput hsv, CMLInput hsl, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(hsv, hsl, CML_HSV_NUMCHANNELS, CML_HSL_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMHSLToHSV);
}

CML_API void cmlHSLToCMYK(const CMLColorMachine* cm, CMLOutput cmyk, CMLInput hsl, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(cmyk, hsl, CML_CMYK_NUMCHANNELS, CML_HSL_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMHSLToHSV);
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

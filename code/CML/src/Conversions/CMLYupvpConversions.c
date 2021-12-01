
#include "../CML.h"
#include "../Internal/CMLColorMachineState.h"
#include "../Internal/CMLConverterMacros.h"



// //////////////////////////
// Identity converter
// //////////////////////////

CML_API void cmlYupvpToYupvp (const CMLColorMachine* cm, CMLOutput yupvpd, CMLInput yupvps, size_t count){
  CML_UNUSED(cm);
  CML_CONVERTER_INOUT_PARAMETER(yupvpd, yupvps, CML_Yupvp_NUMCHANNELS, CML_Yupvp_NUMCHANNELS);
  CML_CONVERTER_MEMCPY(CML_Yupvp_NUMCHANNELS);
}



// //////////////////////////
// Yupvp to anything
// //////////////////////////

CML_API void cmlYupvpToXYZ (const CMLColorMachine* cm, CMLOutput xyz, CMLInput yupvp, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(xyz, yupvp, CML_XYZ_NUMCHANNELS, CML_Yupvp_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYupvpToYxy);
  CMLCMYxyToXYZ_SB(cm, out, count, floatAlign);
}

CML_API void cmlYupvpToYxy (const CMLColorMachine* cm, CMLOutput yxy, CMLInput yupvp, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(yxy, yupvp, CML_Yxy_NUMCHANNELS, CML_Yupvp_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYupvpToYxy);
}

CML_API void cmlYupvpToYuv (const CMLColorMachine* cm, CMLOutput yuv, CMLInput yupvp, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(yuv, yupvp, CML_Yuv_NUMCHANNELS, CML_Yupvp_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYupvpToYuv);
}

CML_API void cmlYupvpToLab (const CMLColorMachine* cm, CMLOutput lab, CMLInput yupvp, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(lab, yupvp, CML_Lab_NUMCHANNELS, CML_Yupvp_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYupvpToYxy);
  CMLCMYxyToXYZ_SB(cm, out, count, floatAlign);
  (*cm->XYZToLab_SB)(cm, out, count, floatAlign);
}

CML_API void cmlYupvpToLch (const CMLColorMachine* cm, CMLOutput lch, CMLInput yupvp, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(lch, yupvp, CML_Lch_NUMCHANNELS, CML_Yupvp_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYupvpToYxy);
  CMLCMYxyToXYZ_SB(cm, out, count, floatAlign);
  (*cm->XYZToLab_SB)(cm, out, count, floatAlign);
  CMLCMLabToLch_SB(cm, out, count, floatAlign);
}

CML_API void cmlYupvpToLuv (const CMLColorMachine* cm, CMLOutput luv, CMLInput yupvp, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(luv, yupvp, CML_Luv_NUMCHANNELS, CML_Yupvp_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYupvpToLuv);
}

CML_API void cmlYupvpToRGB (const CMLColorMachine* cm, CMLOutput rgb, CMLInput yupvp, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(rgb, yupvp, CML_RGB_NUMCHANNELS, CML_Yupvp_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYupvpToYxy);
  CMLCMYxyToXYZ_SB(cm, out, count, floatAlign);
  CMLCMXYZToRGB_SB(cm, out, count, floatAlign);
}

CML_API void cmlYupvpToYCbCr (const CMLColorMachine* cm, CMLOutput ycbcr, CMLInput yupvp, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(ycbcr, yupvp, CML_YCbCr_NUMCHANNELS, CML_Yupvp_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYupvpToYxy);
  CMLCMYxyToXYZ_SB(cm, out, count, floatAlign);
  CMLCMXYZToRGB_SB(cm, out, count, floatAlign);
  CMLCMRGBToYCbCr_SB(cm, out, count, floatAlign);
}

CML_API void cmlYupvpToHSV (const CMLColorMachine* cm, CMLOutput hsv, CMLInput yupvp, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(hsv, yupvp, CML_HSV_NUMCHANNELS, CML_Yupvp_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYupvpToYxy);
  CMLCMYxyToXYZ_SB(cm, out, count, floatAlign);
  CMLCMXYZToRGB_SB(cm, out, count, floatAlign);
  CMLCMRGBToHSV_SB(cm, out, count, floatAlign);
}

CML_API void cmlYupvpToHSL (const CMLColorMachine* cm, CMLOutput hsl, CMLInput yupvp, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(hsl, yupvp, CML_HSL_NUMCHANNELS, CML_Yupvp_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYupvpToYxy);
  CMLCMYxyToXYZ_SB(cm, out, count, floatAlign);
  CMLCMXYZToRGB_SB(cm, out, count, floatAlign);
  CMLCMRGBToHSV_SB(cm, out, count, floatAlign);
  CMLCMHSVToHSL_SB(cm, out, count, floatAlign);
}

CML_API void cmlYupvpToCMYK(const CMLColorMachine* cm, CMLOutput cmyk, CMLInput yupvp, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(cmyk, yupvp, CML_CMYK_NUMCHANNELS, CML_Yupvp_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYupvpToYxy);
  CMLCMYxyToXYZ_SB(cm, out, count, floatAlign);
  CMLCMXYZToRGB_SB(cm, out, count, floatAlign);
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

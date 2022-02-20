
#include "../CML.h"
#include "../Internal/CMLColorMachineState.h"
#include "../Internal/CMLConverterMacros.h"



// //////////////////////////
// Identity converter
// //////////////////////////

CML_API void cmlXYZToXYZ(const CMLColorMachine* cm, CMLOutput xyzd, CMLInput xyzs, size_t count){
  CML_UNUSED(cm);
  CML_CONVERTER_INOUT_PARAMETER(xyzd, xyzs, CML_XYZ_NUMCHANNELS, CML_XYZ_NUMCHANNELS);
  CML_CONVERTER_MEMCPY(CML_XYZ_NUMCHANNELS);
}



// //////////////////////////
// XYZ to anything
// //////////////////////////

CML_API void cmlXYZToYxy(const CMLColorMachine* cm, CMLOutput yxy, CMLInput xyz, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(yxy, xyz, CML_Yxy_NUMCHANNELS, CML_XYZ_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(cml_CMXYZToYxy);
}

CML_API void cmlXYZToYuv(const CMLColorMachine* cm, CMLOutput yuv, CMLInput xyz, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(yuv, xyz, CML_Yuv_NUMCHANNELS, CML_XYZ_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(cml_CMXYZToYxy);
  cml_CMYxyToYupvp_SB(cm, out, count, floatAlign);
  cml_CMYupvpToYuv_SB(cm, out, count, floatAlign);
}

CML_API void cmlXYZToYupvp(const CMLColorMachine* cm, CMLOutput yupvp, CMLInput xyz, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(yupvp, xyz, CML_Yupvp_NUMCHANNELS, CML_XYZ_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(cml_CMXYZToYxy);
  cml_CMYxyToYupvp_SB(cm, out, count, floatAlign);
}

CML_API void cmlXYZToLab(const CMLColorMachine* cm, CMLOutput lab, CMLInput xyz, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(lab, xyz, CML_Lab_NUMCHANNELS, CML_XYZ_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(*cm->XYZToLab);
}

CML_API void cmlXYZToLch(const CMLColorMachine* cm, CMLOutput lch, CMLInput xyz, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(lch, xyz, CML_Lch_NUMCHANNELS, CML_XYZ_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(*cm->XYZToLab);
  cml_CMLabToLch_SB(cm, out, count, floatAlign);
}

CML_API void cmlXYZToLuv(const CMLColorMachine* cm, CMLOutput luv, CMLInput xyz, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(luv, xyz, CML_Luv_NUMCHANNELS, CML_XYZ_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(cml_CMXYZToYxy);
  cml_CMYxyToYupvp_SB(cm, out, count, floatAlign);
  cml_CMYupvpToLuv_SB(cm, out, count, floatAlign);
}

CML_API void cmlXYZToRGB(const CMLColorMachine* cm, CMLOutput rgb, CMLInput xyz, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(rgb, xyz, CML_RGB_NUMCHANNELS, CML_XYZ_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(cml_CMXYZToRGB);
}

CML_API void cmlXYZToYCbCr(const CMLColorMachine* cm, CMLOutput ycbcr, CMLInput xyz, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(ycbcr, xyz, CML_YCbCr_NUMCHANNELS, CML_XYZ_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(cml_CMXYZToRGB);
  cml_CMRGBToYCbCr_SB(cm, out, count, floatAlign);
}

CML_API void cmlXYZToHSV(const CMLColorMachine* cm, CMLOutput hsv, CMLInput xyz, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(hsv, xyz, CML_HSV_NUMCHANNELS, CML_XYZ_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(cml_CMXYZToRGB);
  cml_CMRGBToHSV_SB(cm, out, count, floatAlign);
}

CML_API void cmlXYZToHSL(const CMLColorMachine* cm, CMLOutput hsl, CMLInput xyz, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(hsl, xyz, CML_HSL_NUMCHANNELS, CML_XYZ_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(cml_CMXYZToRGB);
  cml_CMRGBToHSV_SB(cm, out, count, floatAlign);
  cml_CMHSVToHSL_SB(cm, out, count, floatAlign);
}

CML_API void cmlXYZToCMYK(const CMLColorMachine* cm, CMLOutput cmyk, CMLInput xyz, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(cmyk, xyz, CML_CMYK_NUMCHANNELS, CML_XYZ_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(cml_CMXYZToRGB);
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

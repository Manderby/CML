
#include "../CML.h"
#include "../Internal/CMLColorMachineState.h"
#include "../Internal/CMLConverterMacros.h"



// //////////////////////////
// Identity converter
// //////////////////////////

CML_API void cmlUVWToUVW(const CMLColorMachine* cm, CMLOutput uvwd, CMLInput uvws, size_t count){
  CML_UNUSED(cm);
  CML_CONVERTER_INOUT_PARAMETER(uvwd, uvws, CML_UVW_CHANNEL_COUNT, CML_UVW_CHANNEL_COUNT);
  CML_CONVERTER_MEMCPY(CML_UVW_CHANNEL_COUNT);
}



// //////////////////////////
// UVW to anything
// //////////////////////////

CML_API void cmlUVWToCMYK(const CMLColorMachine* cm, CMLOutput cmyk, CMLInput uvw, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(cmyk, uvw, CML_CMYK_CHANNEL_COUNT, CML_UVW_CHANNEL_COUNT);
  CML_CONVERTER_FIRST_STEP(cml_CMUVWToYuv);
  cml_CMYuvToYupvp_SB(cm, out, count, floatAlign);
  cml_CMYupvpToYxy_SB(cm, out, count, floatAlign);
  cml_CMYxyToXYZ_SB(cm, out, count, floatAlign);
  cml_CMXYZToRGB_SB(cm, out, count, floatAlign);
  (*cm->RGBToCMYK_SB)(cm, out, count, floatAlign);
}

CML_API void cmlUVWToHSL(const CMLColorMachine* cm, CMLOutput hsl, CMLInput uvw, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(hsl, uvw, CML_HSL_CHANNEL_COUNT, CML_UVW_CHANNEL_COUNT);
  CML_CONVERTER_FIRST_STEP(cml_CMUVWToYuv);
  cml_CMYuvToYupvp_SB(cm, out, count, floatAlign);
  cml_CMYupvpToYxy_SB(cm, out, count, floatAlign);
  cml_CMYxyToXYZ_SB(cm, out, count, floatAlign);
  cml_CMXYZToRGB_SB(cm, out, count, floatAlign);
  cml_CMRGBToHSV_SB(cm, out, count, floatAlign);
  cml_CMHSVToHSL_SB(cm, out, count, floatAlign);
}

CML_API void cmlUVWToHSV(const CMLColorMachine* cm, CMLOutput hsv, CMLInput uvw, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(hsv, uvw, CML_HSV_CHANNEL_COUNT, CML_UVW_CHANNEL_COUNT);
  CML_CONVERTER_FIRST_STEP(cml_CMUVWToYuv);
  cml_CMYuvToYupvp_SB(cm, out, count, floatAlign);
  cml_CMYupvpToYxy_SB(cm, out, count, floatAlign);
  cml_CMYxyToXYZ_SB(cm, out, count, floatAlign);
  cml_CMXYZToRGB_SB(cm, out, count, floatAlign);
  cml_CMRGBToHSV_SB(cm, out, count, floatAlign);
}

CML_API void cmlUVWToLab(const CMLColorMachine* cm, CMLOutput lab, CMLInput uvw, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(lab, uvw, CML_Lab_CHANNEL_COUNT, CML_UVW_CHANNEL_COUNT);
  CML_CONVERTER_FIRST_STEP(cml_CMUVWToYuv);
  cml_CMYuvToYupvp_SB(cm, out, count, floatAlign);
  cml_CMYupvpToYxy_SB(cm, out, count, floatAlign);
  cml_CMYxyToXYZ_SB(cm, out, count, floatAlign);
  (*cm->XYZToLab_SB)(cm, out, count, floatAlign);
}

CML_API void cmlUVWToLch(const CMLColorMachine* cm, CMLOutput lch, CMLInput uvw, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(lch, uvw, CML_Lch_CHANNEL_COUNT, CML_UVW_CHANNEL_COUNT);
  CML_CONVERTER_FIRST_STEP(cml_CMUVWToYuv);
  cml_CMYuvToYupvp_SB(cm, out, count, floatAlign);
  cml_CMYupvpToYxy_SB(cm, out, count, floatAlign);
  cml_CMYxyToXYZ_SB(cm, out, count, floatAlign);
  (*cm->XYZToLab_SB)(cm, out, count, floatAlign);
  cml_CMLabToLch_SB(cm, out, count, floatAlign);
}

CML_API void cmlUVWToLuv(const CMLColorMachine* cm, CMLOutput luv, CMLInput uvw, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(luv, uvw, CML_Luv_CHANNEL_COUNT, CML_UVW_CHANNEL_COUNT);
  CML_CONVERTER_FIRST_STEP(cml_CMUVWToYuv);
  cml_CMYuvToYupvp_SB(cm, out, count, floatAlign);
  cml_CMYupvpToLuv_SB(cm, out, count, floatAlign);
}

CML_API void cmlUVWToRGB(const CMLColorMachine* cm, CMLOutput rgb, CMLInput uvw, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(rgb, uvw, CML_RGB_CHANNEL_COUNT, CML_UVW_CHANNEL_COUNT);
  CML_CONVERTER_FIRST_STEP(cml_CMUVWToYuv);
  cml_CMYuvToYupvp_SB(cm, out, count, floatAlign);
  cml_CMYupvpToYxy_SB(cm, out, count, floatAlign);
  cml_CMYxyToXYZ_SB(cm, out, count, floatAlign);
  cml_CMXYZToRGB_SB(cm, out, count, floatAlign);
}

CML_API void cmlUVWToXYZ(const CMLColorMachine* cm, CMLOutput xyz, CMLInput uvw, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(xyz, uvw, CML_XYZ_CHANNEL_COUNT, CML_UVW_CHANNEL_COUNT);
  CML_CONVERTER_FIRST_STEP(cml_CMUVWToYuv);
  cml_CMYuvToYupvp_SB(cm, out, count, floatAlign);
  cml_CMYupvpToYxy_SB(cm, out, count, floatAlign);
  cml_CMYxyToXYZ_SB(cm, out, count, floatAlign);
}

CML_API void cmlUVWToYCbCr(const CMLColorMachine* cm, CMLOutput ycbcr, CMLInput uvw, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(ycbcr, uvw, CML_YCbCr_CHANNEL_COUNT, CML_UVW_CHANNEL_COUNT);
  CML_CONVERTER_FIRST_STEP(cml_CMUVWToYuv);
  cml_CMYuvToYupvp_SB(cm, out, count, floatAlign);
  cml_CMYupvpToYxy_SB(cm, out, count, floatAlign);
  cml_CMYxyToXYZ_SB(cm, out, count, floatAlign);
  cml_CMXYZToRGB_SB(cm, out, count, floatAlign);
  cml_CMRGBToYCbCr_SB(cm, out, count, floatAlign);
}

CML_API void cmlUVWToYcd(const CMLColorMachine* cm, CMLOutput ycd, CMLInput uvw, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(ycd, uvw, CML_Ycd_CHANNEL_COUNT, CML_UVW_CHANNEL_COUNT);
  CML_CONVERTER_FIRST_STEP(cml_CMUVWToYuv);
  cml_CMYuvToYcd_SB(cm, out, count, floatAlign);
}

CML_API void cmlUVWToYupvp(const CMLColorMachine* cm, CMLOutput yupvp, CMLInput uvw, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(yupvp, uvw, CML_Yupvp_CHANNEL_COUNT, CML_UVW_CHANNEL_COUNT);
  CML_CONVERTER_FIRST_STEP(cml_CMUVWToYuv);
  cml_CMYuvToYupvp_SB(cm, out, count, floatAlign);
}

CML_API void cmlUVWToYuv(const CMLColorMachine* cm, CMLOutput yuv, CMLInput uvw, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(yuv, uvw, CML_Yupvp_CHANNEL_COUNT, CML_UVW_CHANNEL_COUNT);
  CML_CONVERTER_FIRST_STEP(cml_CMUVWToYuv);
}

CML_API void cmlUVWToYxy(const CMLColorMachine* cm, CMLOutput yxy, CMLInput uvw, size_t count){
  CML_CONVERTER_INOUT_PARAMETER(yxy, uvw, CML_Yxy_CHANNEL_COUNT, CML_UVW_CHANNEL_COUNT);
  CML_CONVERTER_FIRST_STEP(cml_CMUVWToYuv);
  cml_CMYuvToYupvp_SB(cm, out, count, floatAlign);
  cml_CMYupvpToYxy_SB(cm, out, count, floatAlign);
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

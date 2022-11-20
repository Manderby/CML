
#include "../CML.h"
#include "../Internal/CMLColorMachineState.h"
#include "../Internal/CMLConverterMacros.h"



// //////////////////////////
// Spectrum Illumination to anything
// //////////////////////////

CML_API void cmlSpectrumIlluminationToCMYK(const CMLColorMachine* cm, CMLOutput cmyk, CMLInput specIll, size_t count){
  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(cmyk, specIll, CML_CMYK_CHANNEL_COUNT);
  cml_CMIlluminationSpectrumToXYZ(cm, xyzbuf, in, count, floatAlign);
  cmlXYZToCMYK(cm, out, xyzbuf, count);
  CML_CONVERTER_SPECTRUM_RETURN;
}

CML_API void cmlSpectrumIlluminationToHSL(const CMLColorMachine* cm, CMLOutput hsl, CMLInput specIll, size_t count){
  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(hsl, specIll, CML_HSL_CHANNEL_COUNT);
  cml_CMIlluminationSpectrumToXYZ(cm, xyzbuf, in, count, floatAlign);
  cmlXYZToHSL(cm, out, xyzbuf, count);
  CML_CONVERTER_SPECTRUM_RETURN;
}

CML_API void cmlSpectrumIlluminationToHSV(const CMLColorMachine* cm, CMLOutput hsv, CMLInput specIll, size_t count){
  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(hsv, specIll, CML_HSV_CHANNEL_COUNT);
  cml_CMIlluminationSpectrumToXYZ(cm, xyzbuf, in, count, floatAlign);
  cmlXYZToHSV(cm, out, xyzbuf, count);
  CML_CONVERTER_SPECTRUM_RETURN;
}

CML_API void cmlSpectrumIlluminationToLab(const CMLColorMachine* cm, CMLOutput lab, CMLInput specIll, size_t count){
  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(lab, specIll, CML_Lab_CHANNEL_COUNT);
  cml_CMIlluminationSpectrumToXYZ(cm, xyzbuf, in, count, floatAlign);
  cmlXYZToLab(cm, out, xyzbuf, count);
  CML_CONVERTER_SPECTRUM_RETURN;
}

CML_API void cmlSpectrumIlluminationToLch(const CMLColorMachine* cm, CMLOutput lch, CMLInput specIll, size_t count){
  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(lch, specIll, CML_Lch_CHANNEL_COUNT);
  cml_CMIlluminationSpectrumToXYZ(cm, xyzbuf, in, count, floatAlign);
  cmlXYZToLch(cm, out, xyzbuf, count);
  CML_CONVERTER_SPECTRUM_RETURN;
}

CML_API void cmlSpectrumIlluminationToLuv(const CMLColorMachine* cm, CMLOutput luv, CMLInput specIll, size_t count){
  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(luv, specIll, CML_Luv_CHANNEL_COUNT);
  cml_CMIlluminationSpectrumToXYZ(cm, xyzbuf, in, count, floatAlign);
  cmlXYZToLuv(cm, out, xyzbuf, count);
  CML_CONVERTER_SPECTRUM_RETURN;
}

CML_API void cmlSpectrumIlluminationToRGB(const CMLColorMachine* cm, CMLOutput rgb, CMLInput specIll, size_t count){
  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(rgb, specIll, CML_RGB_CHANNEL_COUNT);
  cml_CMIlluminationSpectrumToXYZ(cm, xyzbuf, in, count, floatAlign);
  cmlXYZToRGB(cm, out, xyzbuf, count);
  CML_CONVERTER_SPECTRUM_RETURN;
}

CML_API void cmlSpectrumIlluminationToUVW(const CMLColorMachine* cm, CMLOutput uvw, CMLInput specIll, size_t count){
  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(uvw, specIll, CML_UVW_CHANNEL_COUNT);
  cml_CMIlluminationSpectrumToXYZ(cm, xyzbuf, in, count, floatAlign);
  cmlXYZToUVW(cm, out, xyzbuf, count);
  CML_CONVERTER_SPECTRUM_RETURN;
}

CML_API void cmlSpectrumIlluminationToXYZ(const CMLColorMachine* cm, CMLOutput xyz, CMLInput specIll, size_t count){
  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(xyz, specIll, CML_XYZ_CHANNEL_COUNT);
  cml_CMIlluminationSpectrumToXYZ(cm, xyzbuf, in, count, floatAlign);
  CML_CONVERTER_SPECTRUM_RETURN;
}

CML_API void cmlSpectrumIlluminationToYCbCr(const CMLColorMachine* cm, CMLOutput ycbcr, CMLInput specIll, size_t count){
  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(ycbcr, specIll, CML_YCbCr_CHANNEL_COUNT);
  cml_CMIlluminationSpectrumToXYZ(cm, xyzbuf, in, count, floatAlign);
  cmlXYZToYCbCr(cm, out, xyzbuf, count);
  CML_CONVERTER_SPECTRUM_RETURN;
}

CML_API void cmlSpectrumIlluminationToYcd(const CMLColorMachine* cm, CMLOutput ycd, CMLInput specIll, size_t count){
  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(ycd, specIll, CML_Ycd_CHANNEL_COUNT);
  cml_CMIlluminationSpectrumToXYZ(cm, xyzbuf, in, count, floatAlign);
  cmlXYZToYcd(cm, out, xyzbuf, count);
  CML_CONVERTER_SPECTRUM_RETURN;
}

CML_API void cmlSpectrumIlluminationToYupvp(const CMLColorMachine* cm, CMLOutput yupvp, CMLInput specIll, size_t count){
  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(yupvp, specIll, CML_Yupvp_CHANNEL_COUNT);
  cml_CMIlluminationSpectrumToXYZ(cm, xyzbuf, in, count, floatAlign);
  cmlXYZToYupvp(cm, out, xyzbuf, count);
  CML_CONVERTER_SPECTRUM_RETURN;
}

CML_API void cmlSpectrumIlluminationToYuv(const CMLColorMachine* cm, CMLOutput yuv, CMLInput specIll, size_t count){
  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(yuv, specIll, CML_Yuv_CHANNEL_COUNT);
  cml_CMIlluminationSpectrumToXYZ(cm, xyzbuf, in, count, floatAlign);
  cmlXYZToYuv(cm, out, xyzbuf, count);
  CML_CONVERTER_SPECTRUM_RETURN;
}

CML_API void cmlSpectrumIlluminationToYxy(const CMLColorMachine* cm, CMLOutput yxy, CMLInput specIll, size_t count){
  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(yxy, specIll, CML_Yxy_CHANNEL_COUNT);
  cml_CMIlluminationSpectrumToXYZ(cm, xyzbuf, in, count, floatAlign);
  cmlXYZToYxy(cm, out, xyzbuf, count);
  CML_CONVERTER_SPECTRUM_RETURN;
}





// //////////////////////////
// Spectrum Remission to anything
// //////////////////////////

CML_API void cmlSpectrumRemissionToCMYK(const CMLColorMachine* cm, CMLOutput cmyk, CMLInput specRem, size_t count){
  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(cmyk, specRem, CML_CMYK_CHANNEL_COUNT);
  cml_CMRemissionSpectrumToXYZ(cm, xyzbuf, in, count, floatAlign);
  cmlXYZToCMYK(cm, out, xyzbuf, count);
  CML_CONVERTER_SPECTRUM_RETURN;
}

CML_API void cmlSpectrumRemissionToHSL(const CMLColorMachine* cm, CMLOutput hsl, CMLInput specRem, size_t count){
  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(hsl, specRem, CML_HSL_CHANNEL_COUNT);
  cml_CMRemissionSpectrumToXYZ(cm, xyzbuf, in, count, floatAlign);
  cmlXYZToHSL(cm, out, xyzbuf, count);
  CML_CONVERTER_SPECTRUM_RETURN;
}

CML_API void cmlSpectrumRemissionToHSV(const CMLColorMachine* cm, CMLOutput hsv, CMLInput specRem, size_t count){
  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(hsv, specRem, CML_HSV_CHANNEL_COUNT);
  cml_CMRemissionSpectrumToXYZ(cm, xyzbuf, in, count, floatAlign);
  cmlXYZToHSV(cm, out, xyzbuf, count);
  CML_CONVERTER_SPECTRUM_RETURN;
}

CML_API void cmlSpectrumRemissionToLab(const CMLColorMachine* cm, CMLOutput lab, CMLInput specRem, size_t count){
  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(lab, specRem, CML_Lab_CHANNEL_COUNT);
  cml_CMRemissionSpectrumToXYZ(cm, xyzbuf, in, count, floatAlign);
  cmlXYZToLab(cm, out, xyzbuf, count);
  CML_CONVERTER_SPECTRUM_RETURN;
}

CML_API void cmlSpectrumRemissionToLch(const CMLColorMachine* cm, CMLOutput lch, CMLInput specRem, size_t count){
  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(lch, specRem, CML_Lch_CHANNEL_COUNT);
  cml_CMRemissionSpectrumToXYZ(cm, xyzbuf, in, count, floatAlign);
  cmlXYZToLch(cm, out, xyzbuf, count);
  CML_CONVERTER_SPECTRUM_RETURN;
}

CML_API void cmlSpectrumRemissionToLuv(const CMLColorMachine* cm, CMLOutput luv, CMLInput specRem, size_t count){
  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(luv, specRem, CML_Luv_CHANNEL_COUNT);
  cml_CMRemissionSpectrumToXYZ(cm, xyzbuf, in, count, floatAlign);
  cmlXYZToLuv(cm, out, xyzbuf, count);
  CML_CONVERTER_SPECTRUM_RETURN;
}

CML_API void cmlSpectrumRemissionToRGB(const CMLColorMachine* cm, CMLOutput rgb, CMLInput specRem, size_t count){
  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(rgb, specRem, CML_RGB_CHANNEL_COUNT);
  cml_CMRemissionSpectrumToXYZ(cm, xyzbuf, in, count, floatAlign);
  cmlXYZToRGB(cm, out, xyzbuf, count);
  CML_CONVERTER_SPECTRUM_RETURN;
}

CML_API void cmlSpectrumRemissionToUVW(const CMLColorMachine* cm, CMLOutput uvw, CMLInput specRem, size_t count){
  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(uvw, specRem, CML_UVW_CHANNEL_COUNT);
  cml_CMRemissionSpectrumToXYZ(cm, xyzbuf, in, count, floatAlign);
  cmlXYZToUVW(cm, out, xyzbuf, count);
  CML_CONVERTER_SPECTRUM_RETURN;
}

CML_API void cmlSpectrumRemissionToXYZ(const CMLColorMachine* cm, CMLOutput xyz, CMLInput specRem, size_t count){
  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(xyz, specRem, CML_XYZ_CHANNEL_COUNT);
  cml_CMRemissionSpectrumToXYZ(cm, xyzbuf, in, count, floatAlign);
  CML_CONVERTER_SPECTRUM_RETURN;
}

CML_API void cmlSpectrumRemissionToYCbCr(const CMLColorMachine* cm, CMLOutput ycbcr, CMLInput specRem, size_t count){
  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(ycbcr, specRem, CML_YCbCr_CHANNEL_COUNT);
  cml_CMRemissionSpectrumToXYZ(cm, xyzbuf, in, count, floatAlign);
  cmlXYZToYCbCr(cm, out, xyzbuf, count);
  CML_CONVERTER_SPECTRUM_RETURN;
}

CML_API void cmlSpectrumRemissionToYcd(const CMLColorMachine* cm, CMLOutput ycd, CMLInput specRem, size_t count){
  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(ycd, specRem, CML_Ycd_CHANNEL_COUNT);
  cml_CMRemissionSpectrumToXYZ(cm, xyzbuf, in, count, floatAlign);
  cmlXYZToYcd(cm, out, xyzbuf, count);
  CML_CONVERTER_SPECTRUM_RETURN;
}

CML_API void cmlSpectrumRemissionToYupvp(const CMLColorMachine* cm, CMLOutput yupvp, CMLInput specRem, size_t count){
  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(yupvp, specRem, CML_Yupvp_CHANNEL_COUNT);
  cml_CMRemissionSpectrumToXYZ(cm, xyzbuf, in, count, floatAlign);
  cmlXYZToYupvp(cm, out, xyzbuf, count);
  CML_CONVERTER_SPECTRUM_RETURN;
}

CML_API void cmlSpectrumRemissionToYuv(const CMLColorMachine* cm, CMLOutput yuv, CMLInput specRem, size_t count){
  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(yuv, specRem, CML_Yuv_CHANNEL_COUNT);
  cml_CMRemissionSpectrumToXYZ(cm, xyzbuf, in, count, floatAlign);
  cmlXYZToYuv(cm, out, xyzbuf, count);
  CML_CONVERTER_SPECTRUM_RETURN;
}

CML_API void cmlSpectrumRemissionToYxy(const CMLColorMachine* cm, CMLOutput yxy, CMLInput specRem, size_t count){
  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(yxy, specRem, CML_Yxy_CHANNEL_COUNT);
  cml_CMRemissionSpectrumToXYZ(cm, xyzbuf, in, count, floatAlign);
  cmlXYZToYxy(cm, out, xyzbuf, count);
  CML_CONVERTER_SPECTRUM_RETURN;
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

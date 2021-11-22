
#include "../CML.h"
#include "../StateMachine/CMLColorMachineState.h"
#include "../StateMachine/CMLConverterMacros.h"


// //////////////////////////
// Spectrum Illumination to anything
// //////////////////////////

CML_API void CMLSpectrumIlluminationtoXYZ (const CMLColorMachine* cm, CMLOutput XYZ , CMLInput specill, CMLSize count){
  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(XYZ, specill, CML_XYZ_NUMCHANNELS);
  CMLCMIlluminationSpectrumtoXYZ(cm, xyzbuf, in, count, floatalign);
  CML_CONVERTER_SPECTRUM_RETURN;
}

CML_API void CMLSpectrumIlluminationtoYuv (const CMLColorMachine* cm, CMLOutput Yuv , CMLInput specill, CMLSize count){
  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(Yuv, specill, CML_Yuv_NUMCHANNELS);
  CMLCMIlluminationSpectrumtoXYZ(cm, xyzbuf, in, count, floatalign);
  CMLXYZtoYuv(cm, out, xyzbuf, count);
  CML_CONVERTER_SPECTRUM_RETURN;
}

CML_API void CMLSpectrumIlluminationtoYupvp (const CMLColorMachine* cm, CMLOutput Yupvp , CMLInput specill, CMLSize count){
  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(Yupvp, specill, CML_Yupvp_NUMCHANNELS);
  CMLCMIlluminationSpectrumtoXYZ(cm, xyzbuf, in, count, floatalign);
  CMLXYZtoYupvp(cm, out, xyzbuf, count);
  CML_CONVERTER_SPECTRUM_RETURN;
}

CML_API void CMLSpectrumIlluminationtoYxy (const CMLColorMachine* cm, CMLOutput Yxy , CMLInput specill, CMLSize count){
  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(Yxy, specill, CML_Yxy_NUMCHANNELS);
  CMLCMIlluminationSpectrumtoXYZ(cm, xyzbuf, in, count, floatalign);
  CMLXYZtoYxy(cm, out, xyzbuf, count);
  CML_CONVERTER_SPECTRUM_RETURN;
}

CML_API void CMLSpectrumIlluminationtoLab (const CMLColorMachine* cm, CMLOutput Lab , CMLInput specill, CMLSize count){
  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(Lab, specill, CML_Lab_NUMCHANNELS);
  CMLCMIlluminationSpectrumtoXYZ(cm, xyzbuf, in, count, floatalign);
  CMLXYZtoLab(cm, out, xyzbuf, count);
  CML_CONVERTER_SPECTRUM_RETURN;
}

CML_API void CMLSpectrumIlluminationtoLch (const CMLColorMachine* cm, CMLOutput Lch , CMLInput specill, CMLSize count){
  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(Lch, specill, CML_Lch_NUMCHANNELS);
  CMLCMIlluminationSpectrumtoXYZ(cm, xyzbuf, in, count, floatalign);
  CMLXYZtoLch(cm, out, xyzbuf, count);
  CML_CONVERTER_SPECTRUM_RETURN;
}

CML_API void CMLSpectrumIlluminationtoLuv (const CMLColorMachine* cm, CMLOutput Luv , CMLInput specill, CMLSize count){
  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(Luv, specill, CML_Luv_NUMCHANNELS);
  CMLCMIlluminationSpectrumtoXYZ(cm, xyzbuf, in, count, floatalign);
  CMLXYZtoLuv(cm, out, xyzbuf, count);
  CML_CONVERTER_SPECTRUM_RETURN;
}

CML_API void CMLSpectrumIlluminationtoRGB (const CMLColorMachine* cm, CMLOutput RGB , CMLInput specill, CMLSize count){
  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(RGB, specill, CML_RGB_NUMCHANNELS);
  CMLCMIlluminationSpectrumtoXYZ(cm, xyzbuf, in, count, floatalign);
  CMLXYZtoRGB(cm, out, xyzbuf, count);
  CML_CONVERTER_SPECTRUM_RETURN;
}

CML_API void CMLSpectrumIlluminationtoYCbCr (const CMLColorMachine* cm, CMLOutput YCbCr , CMLInput specill, CMLSize count){
  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(YCbCr, specill, CML_YCbCr_NUMCHANNELS);
  CMLCMIlluminationSpectrumtoXYZ(cm, xyzbuf, in, count, floatalign);
  CMLXYZtoYCbCr(cm, out, xyzbuf, count);
  CML_CONVERTER_SPECTRUM_RETURN;
}

CML_API void CMLSpectrumIlluminationtoHSV (const CMLColorMachine* cm, CMLOutput HSV , CMLInput specill, CMLSize count){
  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(HSV, specill, CML_HSV_NUMCHANNELS);
  CMLCMIlluminationSpectrumtoXYZ(cm, xyzbuf, in, count, floatalign);
  CMLXYZtoHSV(cm, out, xyzbuf, count);
  CML_CONVERTER_SPECTRUM_RETURN;
}

CML_API void CMLSpectrumIlluminationtoHSL (const CMLColorMachine* cm, CMLOutput HSL , CMLInput specill, CMLSize count){
  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(HSL, specill, CML_HSL_NUMCHANNELS);
  CMLCMIlluminationSpectrumtoXYZ(cm, xyzbuf, in, count, floatalign);
  CMLXYZtoHSL(cm, out, xyzbuf, count);
  CML_CONVERTER_SPECTRUM_RETURN;
}

CML_API void CMLSpectrumIlluminationtoCMYK(const CMLColorMachine* cm, CMLOutput CMYK, CMLInput specill, CMLSize count){
  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(CMYK, specill, CML_CMYK_NUMCHANNELS);
  CMLCMIlluminationSpectrumtoXYZ(cm, xyzbuf, in, count, floatalign);
  CMLXYZtoCMYK(cm, out, xyzbuf, count);
  CML_CONVERTER_SPECTRUM_RETURN;
}








// //////////////////////////
// Spectrum Remission to anything
// //////////////////////////

CML_API void CMLSpectrumRemissiontoXYZ (const CMLColorMachine* cm, CMLOutput XYZ , CMLInput specrem, CMLSize count){
  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(XYZ, specrem, CML_XYZ_NUMCHANNELS);
  CMLCMRemissionSpectrumtoXYZ(cm, xyzbuf, in, count, floatalign);
  CML_CONVERTER_SPECTRUM_RETURN;
}

CML_API void CMLSpectrumRemissiontoYuv (const CMLColorMachine* cm, CMLOutput Yuv , CMLInput specrem, CMLSize count){
  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(Yuv, specrem, CML_Yuv_NUMCHANNELS);
  CMLCMRemissionSpectrumtoXYZ(cm, xyzbuf, in, count, floatalign);
  CMLXYZtoYuv(cm, out, xyzbuf, count);
  CML_CONVERTER_SPECTRUM_RETURN;
}

CML_API void CMLSpectrumRemissiontoYupvp (const CMLColorMachine* cm, CMLOutput Yupvp , CMLInput specrem, CMLSize count){
  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(Yupvp, specrem, CML_Yupvp_NUMCHANNELS);
  CMLCMRemissionSpectrumtoXYZ(cm, xyzbuf, in, count, floatalign);
  CMLXYZtoYupvp(cm, out, xyzbuf, count);
  CML_CONVERTER_SPECTRUM_RETURN;
}

CML_API void CMLSpectrumRemissiontoYxy (const CMLColorMachine* cm, CMLOutput Yxy , CMLInput specrem, CMLSize count){
  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(Yxy, specrem, CML_Yxy_NUMCHANNELS);
  CMLCMRemissionSpectrumtoXYZ(cm, xyzbuf, in, count, floatalign);
  CMLXYZtoYxy(cm, out, xyzbuf, count);
  CML_CONVERTER_SPECTRUM_RETURN;
}

CML_API void CMLSpectrumRemissiontoLab (const CMLColorMachine* cm, CMLOutput Lab , CMLInput specrem, CMLSize count){
  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(Lab, specrem, CML_Lab_NUMCHANNELS);
  CMLCMRemissionSpectrumtoXYZ(cm, xyzbuf, in, count, floatalign);
  CMLXYZtoLab(cm, out, xyzbuf, count);
  CML_CONVERTER_SPECTRUM_RETURN;
}

CML_API void CMLSpectrumRemissiontoLch (const CMLColorMachine* cm, CMLOutput Lch , CMLInput specrem, CMLSize count){
  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(Lch, specrem, CML_Lch_NUMCHANNELS);
  CMLCMRemissionSpectrumtoXYZ(cm, xyzbuf, in, count, floatalign);
  CMLXYZtoLch(cm, out, xyzbuf, count);
  CML_CONVERTER_SPECTRUM_RETURN;
}

CML_API void CMLSpectrumRemissiontoLuv (const CMLColorMachine* cm, CMLOutput Luv , CMLInput specrem, CMLSize count){
  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(Luv, specrem, CML_Luv_NUMCHANNELS);
  CMLCMRemissionSpectrumtoXYZ(cm, xyzbuf, in, count, floatalign);
  CMLXYZtoLuv(cm, out, xyzbuf, count);
  CML_CONVERTER_SPECTRUM_RETURN;
}

CML_API void CMLSpectrumRemissiontoRGB (const CMLColorMachine* cm, CMLOutput RGB , CMLInput specrem, CMLSize count){
  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(RGB, specrem, CML_RGB_NUMCHANNELS);
  CMLCMRemissionSpectrumtoXYZ(cm, xyzbuf, in, count, floatalign);
  CMLXYZtoRGB(cm, out, xyzbuf, count);
  CML_CONVERTER_SPECTRUM_RETURN;
}

CML_API void CMLSpectrumRemissiontoYCbCr (const CMLColorMachine* cm, CMLOutput YCbCr , CMLInput specrem, CMLSize count){
  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(YCbCr, specrem, CML_YCbCr_NUMCHANNELS);
  CMLCMRemissionSpectrumtoXYZ(cm, xyzbuf, in, count, floatalign);
  CMLXYZtoYCbCr(cm, out, xyzbuf, count);
  CML_CONVERTER_SPECTRUM_RETURN;
}

CML_API void CMLSpectrumRemissiontoHSV (const CMLColorMachine* cm, CMLOutput HSV , CMLInput specrem, CMLSize count){
  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(HSV, specrem, CML_HSV_NUMCHANNELS);
  CMLCMRemissionSpectrumtoXYZ(cm, xyzbuf, in, count, floatalign);
  CMLXYZtoHSV(cm, out, xyzbuf, count);
  CML_CONVERTER_SPECTRUM_RETURN;
}

CML_API void CMLSpectrumRemissiontoHSL (const CMLColorMachine* cm, CMLOutput HSL , CMLInput specrem, CMLSize count){
  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(HSL, specrem, CML_HSL_NUMCHANNELS);
  CMLCMRemissionSpectrumtoXYZ(cm, xyzbuf, in, count, floatalign);
  CMLXYZtoHSL(cm, out, xyzbuf, count);
  CML_CONVERTER_SPECTRUM_RETURN;
}

CML_API void CMLSpectrumRemissiontoCMYK(const CMLColorMachine* cm, CMLOutput CMYK, CMLInput specrem, CMLSize count){
  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(CMYK, specrem, CML_CMYK_NUMCHANNELS);
  CMLCMRemissionSpectrumtoXYZ(cm, xyzbuf, in, count, floatalign);
  CMLXYZtoCMYK(cm, out, xyzbuf, count);
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


#include "../CML.h"
#include "../StateMachine/CMLColorMachineState.h"
#include "../StateMachine/CMLConverterMacros.h"

// //////////////////////////
// Identity converter
// //////////////////////////

CML_API void CMLLabtoLab (const CMLColorMachine* cm, CMLOutput Labd , CMLInput Labs, CMLSize count){
  cm = cm; // no warning
  CML_CONVERTER_INOUT_PARAMETER(Labd, Labs, CML_Lab_NUMCHANNELS, CML_Lab_NUMCHANNELS);
  CML_CONVERTER_MEMCPY(CML_Lab_NUMCHANNELS);
  CML_CONVERTER_RETURN;
}


// //////////////////////////
// Lab to anything
// //////////////////////////

CML_API void CMLLabtoXYZ (const CMLColorMachine* cm, CMLOutput XYZ , CMLInput Lab , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(XYZ, Lab, CML_XYZ_NUMCHANNELS, CML_Lab_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(*cm->LabtoXYZ);
  CML_CONVERTER_RETURN;
}

CML_API void CMLLabtoYuv (const CMLColorMachine* cm, CMLOutput Yuv , CMLInput Lab , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(Yuv, Lab, CML_Yuv_NUMCHANNELS, CML_Lab_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(*cm->LabtoXYZ);
  CMLCMXYZtoYxy_SB(cm, out, count, floatalign);
  CMLCMYxytoYupvp_SB(cm, out, count, floatalign);
  CMLCMYupvptoYuv_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLLabtoYxy (const CMLColorMachine* cm, CMLOutput Yxy , CMLInput Lab , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(Yxy, Lab, CML_Yxy_NUMCHANNELS, CML_Lab_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(*cm->LabtoXYZ);
  CMLCMXYZtoYxy_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLLabtoLch (const CMLColorMachine* cm, CMLOutput Lch , CMLInput Lab , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(Lch, Lab, CML_Lch_NUMCHANNELS, CML_Lab_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMLabtoLch);
  CML_CONVERTER_RETURN;
}

CML_API void CMLLabtoLuv (const CMLColorMachine* cm, CMLOutput Luv , CMLInput Lab , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(Luv, Lab, CML_Luv_NUMCHANNELS, CML_Lab_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(*cm->LabtoXYZ);
  CMLCMXYZtoYxy_SB(cm, out, count, floatalign);
  CMLCMYxytoYupvp_SB(cm, out, count, floatalign);
  CMLCMYupvptoLuv_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLLabtoYupvp (const CMLColorMachine* cm, CMLOutput Yupvp , CMLInput Lab , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(Yupvp, Lab, CML_Yupvp_NUMCHANNELS, CML_Lab_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(*cm->LabtoXYZ);
  CMLCMXYZtoYxy_SB(cm, out, count, floatalign);
  CMLCMYxytoYupvp_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLLabtoRGB (const CMLColorMachine* cm, CMLOutput RGB , CMLInput Lab , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(RGB, Lab, CML_RGB_NUMCHANNELS, CML_Lab_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(*cm->LabtoXYZ);
  CMLCMXYZtoRGB_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLLabtoYCbCr (const CMLColorMachine* cm, CMLOutput YCbCr , CMLInput Lab , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(YCbCr, Lab, CML_YCbCr_NUMCHANNELS, CML_Lab_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(*cm->LabtoXYZ);
  CMLCMXYZtoRGB_SB(cm, out, count, floatalign);
  CMLCMRGBtoYCbCr_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLLabtoHSV (const CMLColorMachine* cm, CMLOutput HSV , CMLInput Lab , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(HSV, Lab, CML_HSV_NUMCHANNELS, CML_Lab_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(*cm->LabtoXYZ);
  CMLCMXYZtoRGB_SB(cm, out, count, floatalign);
  CMLCMRGBtoHSV_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLLabtoHSL (const CMLColorMachine* cm, CMLOutput HSL , CMLInput Lab , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(HSL, Lab, CML_HSL_NUMCHANNELS, CML_Lab_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(*cm->LabtoXYZ);
  CMLCMXYZtoRGB_SB(cm, out, count, floatalign);
  CMLCMRGBtoHSV_SB(cm, out, count, floatalign);
  CMLCMHSVtoHSL_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLLabtoCMYK(const CMLColorMachine* cm, CMLOutput CMYK, CMLInput Lab , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(CMYK, Lab, CML_CMYK_NUMCHANNELS, CML_Lab_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(*cm->LabtoXYZ);
  CMLCMXYZtoRGB_SB(cm, out, count, floatalign);
  (*cm->RGBtoCMYK_SB)(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
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

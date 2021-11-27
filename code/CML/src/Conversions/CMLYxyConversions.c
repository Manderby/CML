
#include "../CML.h"
#include "../StateMachine/CMLColorMachineState.h"
#include "../StateMachine/CMLConverterMacros.h"



// //////////////////////////
// Identity converter
// //////////////////////////

CML_API void cmlYxyToYxy (const CMLColorMachine* cm, CMLOutput yxyd , CMLInput yxys, size_t count){
  CML_UNUSED(cm);
  CML_CONVERTER_INOUT_PARAMETER(yxyd, yxys, CML_Yxy_NUMCHANNELS, CML_Yxy_NUMCHANNELS);
  CML_CONVERTER_MEMCPY(CML_Yxy_NUMCHANNELS);
}



// //////////////////////////
// Yxy to anything
// //////////////////////////

CML_API void cmlYxyToXYZ (const CMLColorMachine* cm, CMLOutput xyz , CMLInput yxy , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(xyz, yxy, CML_XYZ_NUMCHANNELS, CML_Yxy_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYxytoXYZ);
}

CML_API void cmlYxyToYuv (const CMLColorMachine* cm, CMLOutput yuv , CMLInput yxy , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(yuv, yxy, CML_Yuv_NUMCHANNELS, CML_Yxy_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYxytoYupvp);
  CMLCMYupvptoYuv_SB(cm, out, count, floatAlign);
}

CML_API void cmlYxyToYupvp (const CMLColorMachine* cm, CMLOutput yupvp , CMLInput yxy , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(yupvp, yxy, CML_Yupvp_NUMCHANNELS, CML_Yxy_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYxytoYupvp);
}

CML_API void cmlYxyToLab (const CMLColorMachine* cm, CMLOutput lab , CMLInput yxy , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(lab, yxy, CML_Lab_NUMCHANNELS, CML_Yxy_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYxytoXYZ);
  (*cm->XYZtoLab_SB)(cm, out, count, floatAlign);
}

CML_API void cmlYxyToLch (const CMLColorMachine* cm, CMLOutput lch , CMLInput yxy , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(lch, yxy, CML_Lch_NUMCHANNELS, CML_Yxy_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYxytoXYZ);
  (*cm->XYZtoLab_SB)(cm, out, count, floatAlign);
  CMLCMLabtoLch_SB(cm, out, count, floatAlign);
}

CML_API void cmlYxyToLuv (const CMLColorMachine* cm, CMLOutput luv , CMLInput yxy , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(luv, yxy, CML_Luv_NUMCHANNELS, CML_Yxy_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYxytoYupvp);
  CMLCMYupvptoLuv_SB(cm, out, count, floatAlign);
}

CML_API void cmlYxyToRGB (const CMLColorMachine* cm, CMLOutput rgb , CMLInput yxy , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(rgb, yxy, CML_RGB_NUMCHANNELS, CML_Yxy_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYxytoXYZ);
  CMLCMXYZtoRGB_SB(cm, out, count, floatAlign);
}

CML_API void cmlYxyToYCbCr (const CMLColorMachine* cm, CMLOutput ycbcr , CMLInput yxy , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(ycbcr, yxy, CML_YCbCr_NUMCHANNELS, CML_Yxy_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYxytoXYZ);
  CMLCMXYZtoRGB_SB(cm, out, count, floatAlign);
  CMLCMRGBtoYCbCr_SB(cm, out, count, floatAlign);
}

CML_API void cmlYxyToHSV (const CMLColorMachine* cm, CMLOutput hsv , CMLInput yxy , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(hsv, yxy, CML_HSV_NUMCHANNELS, CML_Yxy_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYxytoXYZ);
  CMLCMXYZtoRGB_SB(cm, out, count, floatAlign);
  CMLCMRGBtoHSV_SB(cm, out, count, floatAlign);
}

CML_API void cmlYxyToHSL (const CMLColorMachine* cm, CMLOutput hsl , CMLInput yxy , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(hsl, yxy, CML_HSL_NUMCHANNELS, CML_Yxy_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYxytoXYZ);
  CMLCMXYZtoRGB_SB(cm, out, count, floatAlign);
  CMLCMRGBtoHSV_SB(cm, out, count, floatAlign);
  CMLCMHSVtoHSL_SB(cm, out, count, floatAlign);
}

CML_API void cmlYxyToCMYK(const CMLColorMachine* cm, CMLOutput cmyk, CMLInput yxy , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(cmyk, yxy, CML_CMYK_NUMCHANNELS, CML_Yxy_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYxytoXYZ);
  CMLCMXYZtoRGB_SB(cm, out, count, floatAlign);
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

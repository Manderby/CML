
#include "../CML.h"
#include "../StateMachine/CMLColorMachineState.h"
#include "../StateMachine/CMLConverterMacros.h"



// //////////////////////////
// Identity converter
// //////////////////////////

CML_API void cmlLchToLch (const CMLColorMachine* cm, CMLOutput lchd , CMLInput lchs, size_t count){
  CML_UNUSED(cm);
  CML_CONVERTER_INOUT_PARAMETER(lchd, lchs, CML_Lch_NUMCHANNELS, CML_Lch_NUMCHANNELS);
  CML_CONVERTER_MEMCPY(CML_Luv_NUMCHANNELS);
}



// //////////////////////////
// Lch to anything
// //////////////////////////

CML_API void cmlLchToXYZ (const CMLColorMachine* cm, CMLOutput xyz , CMLInput lch , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(xyz, lch, CML_XYZ_NUMCHANNELS, CML_Lch_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMLchtoLab);
  (*cm->LabtoXYZ_SB)(cm, out, count, floatAlign);
}

CML_API void cmlLchToYuv (const CMLColorMachine* cm, CMLOutput yuv , CMLInput lch , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(yuv, lch, CML_Yuv_NUMCHANNELS, CML_Lch_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMLchtoLab);
  (*cm->LabtoXYZ_SB)(cm, out, count, floatAlign);
  CMLCMXYZtoYxy_SB(cm, out, count, floatAlign);
  CMLCMYxytoYupvp_SB(cm, out, count, floatAlign);
  CMLCMYupvptoYuv_SB(cm, out, count, floatAlign);
}

CML_API void cmlLchToYxy (const CMLColorMachine* cm, CMLOutput yxy , CMLInput lch , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(yxy, lch, CML_Yxy_NUMCHANNELS, CML_Lch_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMLchtoLab);
  (*cm->LabtoXYZ_SB)(cm, out, count, floatAlign);
  CMLCMXYZtoYxy_SB(cm, out, count, floatAlign);
}

CML_API void cmlLchToLab (const CMLColorMachine* cm, CMLOutput lab , CMLInput lch , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(lab, lch, CML_Lab_NUMCHANNELS, CML_Lch_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMLchtoLab);
}

CML_API void cmlLchToLuv (const CMLColorMachine* cm, CMLOutput luv , CMLInput lch , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(luv, lch, CML_Luv_NUMCHANNELS, CML_Lch_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMLchtoLab);
  (*cm->LabtoXYZ_SB)(cm, out, count, floatAlign);
  CMLCMXYZtoYxy_SB(cm, out, count, floatAlign);
  CMLCMYxytoYupvp_SB(cm, out, count, floatAlign);
  CMLCMYupvptoLuv_SB(cm, out, count, floatAlign);
}

CML_API void cmlLchToYupvp (const CMLColorMachine* cm, CMLOutput yupvp , CMLInput lch , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(yupvp, lch, CML_Yupvp_NUMCHANNELS, CML_Lch_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMLchtoLab);
  (*cm->LabtoXYZ_SB)(cm, out, count, floatAlign);
  CMLCMXYZtoYxy_SB(cm, out, count, floatAlign);
  CMLCMYxytoYupvp_SB(cm, out, count, floatAlign);
}

CML_API void cmlLchToRGB (const CMLColorMachine* cm, CMLOutput rgb , CMLInput lch , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(rgb, lch, CML_RGB_NUMCHANNELS, CML_Lch_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMLchtoLab);
  (*cm->LabtoXYZ_SB)(cm, out, count, floatAlign);
  CMLCMXYZtoRGB_SB(cm, out, count, floatAlign);
}

CML_API void cmlLchToYCbCr (const CMLColorMachine* cm, CMLOutput ycbcr , CMLInput lch , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(ycbcr, lch, CML_YCbCr_NUMCHANNELS, CML_Lch_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMLchtoLab);
  (*cm->LabtoXYZ_SB)(cm, out, count, floatAlign);
  CMLCMXYZtoRGB_SB(cm, out, count, floatAlign);
  CMLCMRGBtoYCbCr_SB(cm, out, count, floatAlign);
}

CML_API void cmlLchToHSV (const CMLColorMachine* cm, CMLOutput hsv , CMLInput lch , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(hsv, lch, CML_HSV_NUMCHANNELS, CML_Lch_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMLchtoLab);
  (*cm->LabtoXYZ_SB)(cm, out, count, floatAlign);
  CMLCMXYZtoRGB_SB(cm, out, count, floatAlign);
  CMLCMRGBtoHSV_SB(cm, out, count, floatAlign);
}

CML_API void cmlLchToHSL (const CMLColorMachine* cm, CMLOutput hsl , CMLInput lch , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(hsl, lch, CML_HSL_NUMCHANNELS, CML_Lch_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMLchtoLab);
  (*cm->LabtoXYZ_SB)(cm, out, count, floatAlign);
  CMLCMXYZtoRGB_SB(cm, out, count, floatAlign);
  CMLCMRGBtoHSV_SB(cm, out, count, floatAlign);
  CMLCMHSVtoHSL_SB(cm, out, count, floatAlign);
}

CML_API void cmlLchToCMYK(const CMLColorMachine* cm, CMLOutput cmyk, CMLInput lch , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(cmyk, lch, CML_CMYK_NUMCHANNELS, CML_Lch_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMLchtoLab);
  (*cm->LabtoXYZ_SB)(cm, out, count, floatAlign);
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

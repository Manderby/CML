
#include "../CML.h"
#include "../StateMachine/CMLColorMachineState.h"
#include "../StateMachine/CMLConverterMacros.h"

// //////////////////////////
// Identity converter
// //////////////////////////

CML_API void CMLLchtoLch (const CMLColorMachine* cm, CMLOutput Lchd , CMLInput Lchs, size_t count){
  cm = cm; // no warning
  CML_CONVERTER_INOUT_PARAMETER(Lchd, Lchs, CML_Lch_NUMCHANNELS, CML_Lch_NUMCHANNELS);
  CML_CONVERTER_MEMCPY(CML_Luv_NUMCHANNELS);
  CML_CONVERTER_RETURN;
}


// //////////////////////////
// Lch to anything
// //////////////////////////

CML_API void CMLLchtoXYZ (const CMLColorMachine* cm, CMLOutput xyz , CMLInput lch , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(xyz, lch, CML_XYZ_NUMCHANNELS, CML_Lch_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMLchtoLab);
  (*cm->LabtoXYZ_SB)(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLLchtoYuv (const CMLColorMachine* cm, CMLOutput yuv , CMLInput lch , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(yuv, lch, CML_Yuv_NUMCHANNELS, CML_Lch_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMLchtoLab);
  (*cm->LabtoXYZ_SB)(cm, out, count, floatalign);
  CMLCMXYZtoYxy_SB(cm, out, count, floatalign);
  CMLCMYxytoYupvp_SB(cm, out, count, floatalign);
  CMLCMYupvptoYuv_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLLchtoYxy (const CMLColorMachine* cm, CMLOutput yxy , CMLInput lch , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(yxy, lch, CML_Yxy_NUMCHANNELS, CML_Lch_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMLchtoLab);
  (*cm->LabtoXYZ_SB)(cm, out, count, floatalign);
  CMLCMXYZtoYxy_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLLchtoLab (const CMLColorMachine* cm, CMLOutput lab , CMLInput lch , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(lab, lch, CML_Lab_NUMCHANNELS, CML_Lch_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMLchtoLab);
  CML_CONVERTER_RETURN;
}

CML_API void CMLLchtoLuv (const CMLColorMachine* cm, CMLOutput luv , CMLInput lch , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(luv, lch, CML_Luv_NUMCHANNELS, CML_Lch_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMLchtoLab);
  (*cm->LabtoXYZ_SB)(cm, out, count, floatalign);
  CMLCMXYZtoYxy_SB(cm, out, count, floatalign);
  CMLCMYxytoYupvp_SB(cm, out, count, floatalign);
  CMLCMYupvptoLuv_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLLchtoYupvp (const CMLColorMachine* cm, CMLOutput yupvp , CMLInput lch , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(yupvp, lch, CML_Yupvp_NUMCHANNELS, CML_Lch_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMLchtoLab);
  (*cm->LabtoXYZ_SB)(cm, out, count, floatalign);
  CMLCMXYZtoYxy_SB(cm, out, count, floatalign);
  CMLCMYxytoYupvp_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLLchtoRGB (const CMLColorMachine* cm, CMLOutput rgb , CMLInput lch , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(rgb, lch, CML_RGB_NUMCHANNELS, CML_Lch_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMLchtoLab);
  (*cm->LabtoXYZ_SB)(cm, out, count, floatalign);
  CMLCMXYZtoRGB_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLLchtoYCbCr (const CMLColorMachine* cm, CMLOutput ycbcr , CMLInput lch , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(ycbcr, lch, CML_YCbCr_NUMCHANNELS, CML_Lch_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMLchtoLab);
  (*cm->LabtoXYZ_SB)(cm, out, count, floatalign);
  CMLCMXYZtoRGB_SB(cm, out, count, floatalign);
  CMLCMRGBtoYCbCr_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLLchtoHSV (const CMLColorMachine* cm, CMLOutput hsv , CMLInput lch , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(hsv, lch, CML_HSV_NUMCHANNELS, CML_Lch_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMLchtoLab);
  (*cm->LabtoXYZ_SB)(cm, out, count, floatalign);
  CMLCMXYZtoRGB_SB(cm, out, count, floatalign);
  CMLCMRGBtoHSV_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLLchtoHSL (const CMLColorMachine* cm, CMLOutput hsl , CMLInput lch , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(hsl, lch, CML_HSL_NUMCHANNELS, CML_Lch_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMLchtoLab);
  (*cm->LabtoXYZ_SB)(cm, out, count, floatalign);
  CMLCMXYZtoRGB_SB(cm, out, count, floatalign);
  CMLCMRGBtoHSV_SB(cm, out, count, floatalign);
  CMLCMHSVtoHSL_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLLchtoCMYK(const CMLColorMachine* cm, CMLOutput cmyk, CMLInput lch , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(cmyk, lch, CML_CMYK_NUMCHANNELS, CML_Lch_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMLchtoLab);
  (*cm->LabtoXYZ_SB)(cm, out, count, floatalign);
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

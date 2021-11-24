
#include "../CML.h"
#include "../StateMachine/CMLColorMachineState.h"
#include "../StateMachine/CMLConverterMacros.h"

// //////////////////////////
// Identity converter
// //////////////////////////

CML_API void CMLLabtoLab (const CMLColorMachine* cm, CMLOutput Labd , CMLInput Labs, size_t count){
  cm = cm; // no warning
  CML_CONVERTER_INOUT_PARAMETER(Labd, Labs, CML_Lab_NUMCHANNELS, CML_Lab_NUMCHANNELS);
  CML_CONVERTER_MEMCPY(CML_Lab_NUMCHANNELS);
  CML_CONVERTER_RETURN;
}


// //////////////////////////
// Lab to anything
// //////////////////////////

CML_API void CMLLabtoXYZ (const CMLColorMachine* cm, CMLOutput xyz , CMLInput lab , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(xyz, lab, CML_XYZ_NUMCHANNELS, CML_Lab_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(*cm->LabtoXYZ);
  CML_CONVERTER_RETURN;
}

CML_API void CMLLabtoYuv (const CMLColorMachine* cm, CMLOutput yuv , CMLInput lab , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(yuv, lab, CML_Yuv_NUMCHANNELS, CML_Lab_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(*cm->LabtoXYZ);
  CMLCMXYZtoYxy_SB(cm, out, count, floatalign);
  CMLCMYxytoYupvp_SB(cm, out, count, floatalign);
  CMLCMYupvptoYuv_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLLabtoYxy (const CMLColorMachine* cm, CMLOutput yxy , CMLInput lab , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(yxy, lab, CML_Yxy_NUMCHANNELS, CML_Lab_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(*cm->LabtoXYZ);
  CMLCMXYZtoYxy_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLLabtoLch (const CMLColorMachine* cm, CMLOutput lch , CMLInput lab , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(lch, lab, CML_Lch_NUMCHANNELS, CML_Lab_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMLabtoLch);
  CML_CONVERTER_RETURN;
}

CML_API void CMLLabtoLuv (const CMLColorMachine* cm, CMLOutput luv , CMLInput lab , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(luv, lab, CML_Luv_NUMCHANNELS, CML_Lab_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(*cm->LabtoXYZ);
  CMLCMXYZtoYxy_SB(cm, out, count, floatalign);
  CMLCMYxytoYupvp_SB(cm, out, count, floatalign);
  CMLCMYupvptoLuv_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLLabtoYupvp (const CMLColorMachine* cm, CMLOutput yupvp , CMLInput lab , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(yupvp, lab, CML_Yupvp_NUMCHANNELS, CML_Lab_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(*cm->LabtoXYZ);
  CMLCMXYZtoYxy_SB(cm, out, count, floatalign);
  CMLCMYxytoYupvp_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLLabtoRGB (const CMLColorMachine* cm, CMLOutput rgb , CMLInput lab , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(rgb, lab, CML_RGB_NUMCHANNELS, CML_Lab_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(*cm->LabtoXYZ);
  CMLCMXYZtoRGB_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLLabtoYCbCr (const CMLColorMachine* cm, CMLOutput ycbcr , CMLInput lab , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(ycbcr, lab, CML_YCbCr_NUMCHANNELS, CML_Lab_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(*cm->LabtoXYZ);
  CMLCMXYZtoRGB_SB(cm, out, count, floatalign);
  CMLCMRGBtoYCbCr_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLLabtoHSV (const CMLColorMachine* cm, CMLOutput hsv , CMLInput lab , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(hsv, lab, CML_HSV_NUMCHANNELS, CML_Lab_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(*cm->LabtoXYZ);
  CMLCMXYZtoRGB_SB(cm, out, count, floatalign);
  CMLCMRGBtoHSV_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLLabtoHSL (const CMLColorMachine* cm, CMLOutput hsl , CMLInput lab , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(hsl, lab, CML_HSL_NUMCHANNELS, CML_Lab_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(*cm->LabtoXYZ);
  CMLCMXYZtoRGB_SB(cm, out, count, floatalign);
  CMLCMRGBtoHSV_SB(cm, out, count, floatalign);
  CMLCMHSVtoHSL_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CML_API void CMLLabtoCMYK(const CMLColorMachine* cm, CMLOutput cmyk, CMLInput lab , size_t count){
  CML_CONVERTER_INOUT_PARAMETER(cmyk, lab, CML_CMYK_NUMCHANNELS, CML_Lab_NUMCHANNELS);
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

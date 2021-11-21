
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

#include "../CML.h"
#include "../StateMachine/CMLColorMachineState.h"
#include "../StateMachine/CMLConverterMacros.h"






// //////////////////////////
// Identity converter
// //////////////////////////

CMLAPI void CMLYuvtoYuv (const CMLColorMachine* cm, CMLOutput Yuvd , CMLInput Yuvs, CMLSize count){
  cm = cm; // no warning
  CML_CONVERTER_INOUT_PARAMETER(Yuvd, Yuvs, CML_Yuv_NUMCHANNELS, CML_Yuv_NUMCHANNELS);
  CML_CONVERTER_MEMCPY(CML_Yuv_NUMCHANNELS);
  CML_CONVERTER_RETURN;
}



// //////////////////////////
// Yuv to anything
// //////////////////////////

CMLAPI void CMLYuvtoXYZ (const CMLColorMachine* cm, CMLOutput XYZ , CMLInput Yuv , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(XYZ, Yuv, CML_XYZ_NUMCHANNELS, CML_Yuv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYuvtoYupvp);
  CMLCMYupvptoYxy_SB(cm, out, count, floatalign);
  CMLCMYxytoXYZ_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CMLAPI void CMLYuvtoYxy (const CMLColorMachine* cm, CMLOutput Yxy , CMLInput Yuv , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(Yxy, Yuv, CML_Yxy_NUMCHANNELS, CML_Yuv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYuvtoYupvp);
  CMLCMYupvptoYxy_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CMLAPI void CMLYuvtoYupvp (const CMLColorMachine* cm, CMLOutput Yupvp , CMLInput Yuv , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(Yupvp, Yuv, CML_Yupvp_NUMCHANNELS, CML_Yuv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYuvtoYupvp);
  CML_CONVERTER_RETURN;
}

CMLAPI void CMLYuvtoLab (const CMLColorMachine* cm, CMLOutput Lab , CMLInput Yuv , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(Lab, Yuv, CML_Lab_NUMCHANNELS, CML_Yuv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYuvtoYupvp);
  CMLCMYupvptoYxy_SB(cm, out, count, floatalign);
  CMLCMYxytoXYZ_SB(cm, out, count, floatalign);
  (*cm->XYZtoLab_SB)(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CMLAPI void CMLYuvtoLch (const CMLColorMachine* cm, CMLOutput Lch , CMLInput Yuv , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(Lch, Yuv, CML_Lch_NUMCHANNELS, CML_Yuv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYuvtoYupvp);
  CMLCMYupvptoYxy_SB(cm, out, count, floatalign);
  CMLCMYxytoXYZ_SB(cm, out, count, floatalign);
  (*cm->XYZtoLab_SB)(cm, out, count, floatalign);
  CMLCMLabtoLch_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CMLAPI void CMLYuvtoLuv (const CMLColorMachine* cm, CMLOutput Luv , CMLInput Yuv , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(Luv, Yuv, CML_Luv_NUMCHANNELS, CML_Yuv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYuvtoYupvp);
  CMLCMYupvptoLuv_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CMLAPI void CMLYuvtoRGB (const CMLColorMachine* cm, CMLOutput RGB , CMLInput Yuv , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(RGB, Yuv, CML_RGB_NUMCHANNELS, CML_Yuv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYuvtoYupvp);
  CMLCMYupvptoYxy_SB(cm, out, count, floatalign);
  CMLCMYxytoXYZ_SB(cm, out, count, floatalign);
  CMLCMXYZtoRGB_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CMLAPI void CMLYuvtoYCbCr (const CMLColorMachine* cm, CMLOutput YCbCr , CMLInput Yuv , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(YCbCr, Yuv, CML_YCbCr_NUMCHANNELS, CML_Yuv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYuvtoYupvp);
  CMLCMYupvptoYxy_SB(cm, out, count, floatalign);
  CMLCMYxytoXYZ_SB(cm, out, count, floatalign);
  CMLCMXYZtoRGB_SB(cm, out, count, floatalign);
  CMLCMRGBtoYCbCr_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CMLAPI void CMLYuvtoHSV (const CMLColorMachine* cm, CMLOutput HSV , CMLInput Yuv , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(HSV, Yuv, CML_HSV_NUMCHANNELS, CML_Yuv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYuvtoYupvp);
  CMLCMYupvptoYxy_SB(cm, out, count, floatalign);
  CMLCMYxytoXYZ_SB(cm, out, count, floatalign);
  CMLCMXYZtoRGB_SB(cm, out, count, floatalign);
  CMLCMRGBtoHSV_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CMLAPI void CMLYuvtoHSL (const CMLColorMachine* cm, CMLOutput HSL , CMLInput Yuv , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(HSL, Yuv, CML_HSL_NUMCHANNELS, CML_Yuv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYuvtoYupvp);
  CMLCMYupvptoYxy_SB(cm, out, count, floatalign);
  CMLCMYxytoXYZ_SB(cm, out, count, floatalign);
  CMLCMXYZtoRGB_SB(cm, out, count, floatalign);
  CMLCMRGBtoHSV_SB(cm, out, count, floatalign);
  CMLCMHSVtoHSL_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CMLAPI void CMLYuvtoCMYK(const CMLColorMachine* cm, CMLOutput CMYK, CMLInput Yuv , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(CMYK, Yuv, CML_CMYK_NUMCHANNELS, CML_Yuv_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYuvtoYupvp);
  CMLCMYupvptoYxy_SB(cm, out, count, floatalign);
  CMLCMYxytoXYZ_SB(cm, out, count, floatalign);
  CMLCMXYZtoRGB_SB(cm, out, count, floatalign);
  (*cm->RGBtoCMYK_SB)(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}



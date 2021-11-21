
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

CMLAPI void CMLHSVtoHSV (const CMLColorMachine* cm, CMLOutput HSVd , CMLInput HSVs, CMLSize count){
  cm = cm; // no warning
  CML_CONVERTER_INOUT_PARAMETER(HSVd, HSVs, CML_HSV_NUMCHANNELS, CML_HSV_NUMCHANNELS);
  CML_CONVERTER_MEMCPY(CML_HSV_NUMCHANNELS);
  CML_CONVERTER_RETURN;
}


// //////////////////////////
// HSV to anything
// //////////////////////////

CMLAPI void CMLHSVtoXYZ (const CMLColorMachine* cm, CMLOutput XYZ , CMLInput HSV , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(XYZ, HSV, CML_XYZ_NUMCHANNELS, CML_HSV_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMHSVtoRGB);
  CMLCMRGBtoXYZ_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CMLAPI void CMLHSVtoYuv (const CMLColorMachine* cm, CMLOutput Yuv , CMLInput HSV , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(Yuv, HSV, CML_Yuv_NUMCHANNELS, CML_HSV_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMHSVtoRGB);
  CMLCMRGBtoXYZ_SB(cm, out, count, floatalign);
  CMLCMXYZtoYxy_SB(cm, out, count, floatalign);
  CMLCMYxytoYupvp_SB(cm, out, count, floatalign);
  CMLCMYupvptoYuv_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CMLAPI void CMLHSVtoYupvp (const CMLColorMachine* cm, CMLOutput Yupvp , CMLInput HSV , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(Yupvp, HSV, CML_Yupvp_NUMCHANNELS, CML_HSV_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMHSVtoRGB);
  CMLCMRGBtoXYZ_SB(cm, out, count, floatalign);
  CMLCMXYZtoYxy_SB(cm, out, count, floatalign);
  CMLCMYxytoYupvp_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CMLAPI void CMLHSVtoYxy (const CMLColorMachine* cm, CMLOutput Yxy , CMLInput HSV , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(Yxy, HSV, CML_Yxy_NUMCHANNELS, CML_HSV_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMHSVtoRGB);
  CMLCMRGBtoXYZ_SB(cm, out, count, floatalign);
  CMLCMXYZtoYxy_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CMLAPI void CMLHSVtoLab (const CMLColorMachine* cm, CMLOutput Lab , CMLInput HSV , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(Lab, HSV, CML_Lab_NUMCHANNELS, CML_HSV_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMHSVtoRGB);
  CMLCMRGBtoXYZ_SB(cm, out, count, floatalign);
  (*cm->XYZtoLab_SB)(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CMLAPI void CMLHSVtoLch (const CMLColorMachine* cm, CMLOutput Lch , CMLInput HSV , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(Lch, HSV, CML_Lch_NUMCHANNELS, CML_HSV_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMHSVtoRGB);
  CMLCMRGBtoXYZ_SB(cm, out, count, floatalign);
  (*cm->XYZtoLab_SB)(cm, out, count, floatalign);
  CMLCMLabtoLch_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CMLAPI void CMLHSVtoLuv (const CMLColorMachine* cm, CMLOutput Luv , CMLInput HSV , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(Luv, HSV, CML_Luv_NUMCHANNELS, CML_HSV_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMHSVtoRGB);
  CMLCMRGBtoXYZ_SB(cm, out, count, floatalign);
  CMLCMXYZtoYxy_SB(cm, out, count, floatalign);
  CMLCMYxytoYupvp_SB(cm, out, count, floatalign);
  CMLCMYupvptoLuv_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CMLAPI void CMLHSVtoRGB (const CMLColorMachine* cm, CMLOutput RGB , CMLInput HSV , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(RGB, HSV, CML_RGB_NUMCHANNELS, CML_HSV_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMHSVtoRGB);
  CML_CONVERTER_RETURN;
}

CMLAPI void CMLHSVtoYCbCr (const CMLColorMachine* cm, CMLOutput YCbCr , CMLInput HSV , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(YCbCr, HSV, CML_YCbCr_NUMCHANNELS, CML_HSV_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMHSVtoRGB);
  CMLCMRGBtoYCbCr_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CMLAPI void CMLHSVtoHSL (const CMLColorMachine* cm, CMLOutput HSL , CMLInput HSV , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(HSL, HSV, CML_HSL_NUMCHANNELS, CML_HSV_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMHSVtoHSL);
  CML_CONVERTER_RETURN;
}

CMLAPI void CMLHSVtoCMYK(const CMLColorMachine* cm, CMLOutput CMYK, CMLInput HSV , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(CMYK, HSV, CML_CMYK_NUMCHANNELS, CML_HSV_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMHSVtoRGB);
  (*cm->RGBtoCMYK_SB)(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}



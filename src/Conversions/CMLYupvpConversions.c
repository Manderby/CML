
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

CMLAPI void CMLYupvptoYupvp (const CMLColorMachine* cm, CMLOutput Yupvpd , CMLInput Yupvps, CMLSize count){
  cm = cm; // no warning
  CML_CONVERTER_INOUT_PARAMETER(Yupvpd, Yupvps, CML_Yupvp_NUMCHANNELS, CML_Yupvp_NUMCHANNELS);
  CML_CONVERTER_MEMCPY(CML_Yupvp_NUMCHANNELS);
  CML_CONVERTER_RETURN;
}



// //////////////////////////
// Yupvp to anything
// //////////////////////////

CMLAPI void CMLYupvptoXYZ (const CMLColorMachine* cm, CMLOutput XYZ , CMLInput Yupvp , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(XYZ, Yupvp, CML_XYZ_NUMCHANNELS, CML_Yupvp_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYupvptoYxy);
  CMLCMYxytoXYZ_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CMLAPI void CMLYupvptoYxy (const CMLColorMachine* cm, CMLOutput Yxy , CMLInput Yupvp , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(Yxy, Yupvp, CML_Yxy_NUMCHANNELS, CML_Yupvp_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYupvptoYxy);
  CML_CONVERTER_RETURN;
}

CMLAPI void CMLYupvptoYuv (const CMLColorMachine* cm, CMLOutput Yuv , CMLInput Yupvp , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(Yuv, Yupvp, CML_Yuv_NUMCHANNELS, CML_Yupvp_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYupvptoYuv);
  CML_CONVERTER_RETURN;
}

CMLAPI void CMLYupvptoLab (const CMLColorMachine* cm, CMLOutput Lab , CMLInput Yupvp , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(Lab, Yupvp, CML_Lab_NUMCHANNELS, CML_Yupvp_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYupvptoYxy);
  CMLCMYxytoXYZ_SB(cm, out, count, floatalign);
  (*cm->XYZtoLab_SB)(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CMLAPI void CMLYupvptoLch (const CMLColorMachine* cm, CMLOutput Lch , CMLInput Yupvp , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(Lch, Yupvp, CML_Lch_NUMCHANNELS, CML_Yupvp_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYupvptoYxy);
  CMLCMYxytoXYZ_SB(cm, out, count, floatalign);
  (*cm->XYZtoLab_SB)(cm, out, count, floatalign);
  CMLCMLabtoLch_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CMLAPI void CMLYupvptoLuv (const CMLColorMachine* cm, CMLOutput Luv , CMLInput Yupvp , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(Luv, Yupvp, CML_Luv_NUMCHANNELS, CML_Yupvp_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYupvptoLuv);
  CML_CONVERTER_RETURN;
}

CMLAPI void CMLYupvptoRGB (const CMLColorMachine* cm, CMLOutput RGB , CMLInput Yupvp , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(RGB, Yupvp, CML_RGB_NUMCHANNELS, CML_Yupvp_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYupvptoYxy);
  CMLCMYxytoXYZ_SB(cm, out, count, floatalign);
  CMLCMXYZtoRGB_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CMLAPI void CMLYupvptoYCbCr (const CMLColorMachine* cm, CMLOutput YCbCr , CMLInput Yupvp , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(YCbCr, Yupvp, CML_YCbCr_NUMCHANNELS, CML_Yupvp_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYupvptoYxy);
  CMLCMYxytoXYZ_SB(cm, out, count, floatalign);
  CMLCMXYZtoRGB_SB(cm, out, count, floatalign);
  CMLCMRGBtoYCbCr_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CMLAPI void CMLYupvptoHSV (const CMLColorMachine* cm, CMLOutput HSV , CMLInput Yupvp , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(HSV, Yupvp, CML_HSV_NUMCHANNELS, CML_Yupvp_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYupvptoYxy);
  CMLCMYxytoXYZ_SB(cm, out, count, floatalign);
  CMLCMXYZtoRGB_SB(cm, out, count, floatalign);
  CMLCMRGBtoHSV_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CMLAPI void CMLYupvptoHSL (const CMLColorMachine* cm, CMLOutput HSL , CMLInput Yupvp , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(HSL, Yupvp, CML_HSL_NUMCHANNELS, CML_Yupvp_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYupvptoYxy);
  CMLCMYxytoXYZ_SB(cm, out, count, floatalign);
  CMLCMXYZtoRGB_SB(cm, out, count, floatalign);
  CMLCMRGBtoHSV_SB(cm, out, count, floatalign);
  CMLCMHSVtoHSL_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CMLAPI void CMLYupvptoCMYK(const CMLColorMachine* cm, CMLOutput CMYK, CMLInput Yupvp , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(CMYK, Yupvp, CML_CMYK_NUMCHANNELS, CML_Yupvp_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYupvptoYxy);
  CMLCMYxytoXYZ_SB(cm, out, count, floatalign);
  CMLCMXYZtoRGB_SB(cm, out, count, floatalign);
  (*cm->RGBtoCMYK_SB)(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}




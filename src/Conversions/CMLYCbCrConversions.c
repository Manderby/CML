
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

CMLAPI void CMLYCbCrtoYCbCr (const CMLColorMachine* cm, CMLOutput YCbCrd , CMLInput YCbCrs, CMLSize count){
  cm = cm; // no warning
  CML_CONVERTER_INOUT_PARAMETER(YCbCrd, YCbCrs, CML_YCbCr_NUMCHANNELS, CML_YCbCr_NUMCHANNELS);
  CML_CONVERTER_MEMCPY(CML_YCbCr_NUMCHANNELS);
  CML_CONVERTER_RETURN;
}


// //////////////////////////
// YCbCr to anything
// //////////////////////////

CMLAPI void CMLYCbCrtoXYZ (const CMLColorMachine* cm, CMLOutput XYZ , CMLInput YCbCr , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(XYZ, YCbCr, CML_XYZ_NUMCHANNELS, CML_YCbCr_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYCbCrtoRGB);
  CMLCMRGBtoXYZ_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CMLAPI void CMLYCbCrtoYxy (const CMLColorMachine* cm, CMLOutput Yxy , CMLInput YCbCr , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(Yxy, YCbCr, CML_Yxy_NUMCHANNELS, CML_YCbCr_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYCbCrtoRGB);
  CMLCMRGBtoXYZ_SB(cm, out, count, floatalign);
  CMLCMXYZtoYxy_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CMLAPI void CMLYCbCrtoYuv (const CMLColorMachine* cm, CMLOutput Yuv , CMLInput YCbCr , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(Yuv, YCbCr, CML_Yuv_NUMCHANNELS, CML_YCbCr_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYCbCrtoRGB);
  CMLCMRGBtoXYZ_SB(cm, out, count, floatalign);
  CMLCMXYZtoYxy_SB(cm, out, count, floatalign);
  CMLCMYxytoYupvp_SB(cm, out, count, floatalign);
  CMLCMYupvptoYuv_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CMLAPI void CMLYCbCrtoYupvp (const CMLColorMachine* cm, CMLOutput Yupvp , CMLInput YCbCr , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(Yupvp, YCbCr, CML_Yupvp_NUMCHANNELS, CML_YCbCr_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYCbCrtoRGB);
  CMLCMRGBtoXYZ_SB(cm, out, count, floatalign);
  CMLCMXYZtoYxy_SB(cm, out, count, floatalign);
  CMLCMYxytoYupvp_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CMLAPI void CMLYCbCrtoLab (const CMLColorMachine* cm, CMLOutput Lab , CMLInput YCbCr , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(Lab, YCbCr, CML_Lab_NUMCHANNELS, CML_YCbCr_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYCbCrtoRGB);
  CMLCMRGBtoXYZ_SB(cm, out, count, floatalign);
  (*cm->XYZtoLab_SB)(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CMLAPI void CMLYCbCrtoLch (const CMLColorMachine* cm, CMLOutput Lch , CMLInput YCbCr , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(Lch, YCbCr, CML_Lch_NUMCHANNELS, CML_YCbCr_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYCbCrtoRGB);
  CMLCMRGBtoXYZ_SB(cm, out, count, floatalign);
  (*cm->XYZtoLab_SB)(cm, out, count, floatalign);
  CMLCMLabtoLch_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CMLAPI void CMLYCbCrtoLuv (const CMLColorMachine* cm, CMLOutput Luv , CMLInput YCbCr , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(Luv, YCbCr, CML_Luv_NUMCHANNELS, CML_YCbCr_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYCbCrtoRGB);
  CMLCMRGBtoXYZ_SB(cm, out, count, floatalign);
  CMLCMXYZtoYxy_SB(cm, out, count, floatalign);
  CMLCMYxytoYupvp_SB(cm, out, count, floatalign);
  CMLCMYupvptoLuv_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CMLAPI void CMLYCbCrtoRGB (const CMLColorMachine* cm, CMLOutput RGB , CMLInput YCbCr , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(RGB, YCbCr, CML_RGB_NUMCHANNELS, CML_YCbCr_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYCbCrtoRGB);
  CML_CONVERTER_RETURN;
}

CMLAPI void CMLYCbCrtoHSV (const CMLColorMachine* cm, CMLOutput HSV , CMLInput YCbCr , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(HSV, YCbCr, CML_HSV_NUMCHANNELS, CML_YCbCr_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYCbCrtoRGB);
  CMLCMRGBtoHSV_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CMLAPI void CMLYCbCrtoHSL (const CMLColorMachine* cm, CMLOutput HSL , CMLInput YCbCr , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(HSL, YCbCr, CML_HSL_NUMCHANNELS, CML_YCbCr_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYCbCrtoRGB);
  CMLCMRGBtoHSV_SB(cm, out, count, floatalign);
  CMLCMHSVtoHSL_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CMLAPI void CMLYCbCrtoCMYK(const CMLColorMachine* cm, CMLOutput CMYK, CMLInput YCbCr , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(CMYK, YCbCr, CML_CMYK_NUMCHANNELS, CML_YCbCr_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMYCbCrtoRGB);
  (*cm->RGBtoCMYK_SB)(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}




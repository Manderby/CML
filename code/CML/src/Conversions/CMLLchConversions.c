
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

CMLAPI void CMLLchtoLch (const CMLColorMachine* cm, CMLOutput Lchd , CMLInput Lchs, CMLSize count){
  cm = cm; // no warning
  CML_CONVERTER_INOUT_PARAMETER(Lchd, Lchs, CML_Lch_NUMCHANNELS, CML_Lch_NUMCHANNELS);
  CML_CONVERTER_MEMCPY(CML_Luv_NUMCHANNELS);
  CML_CONVERTER_RETURN;
}


// //////////////////////////
// Lch to anything
// //////////////////////////

CMLAPI void CMLLchtoXYZ (const CMLColorMachine* cm, CMLOutput XYZ , CMLInput Lch , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(XYZ, Lch, CML_XYZ_NUMCHANNELS, CML_Lch_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMLchtoLab);
  (*cm->LabtoXYZ_SB)(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CMLAPI void CMLLchtoYuv (const CMLColorMachine* cm, CMLOutput Yuv , CMLInput Lch , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(Yuv, Lch, CML_Yuv_NUMCHANNELS, CML_Lch_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMLchtoLab);
  (*cm->LabtoXYZ_SB)(cm, out, count, floatalign);
  CMLCMXYZtoYxy_SB(cm, out, count, floatalign);
  CMLCMYxytoYupvp_SB(cm, out, count, floatalign);
  CMLCMYupvptoYuv_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CMLAPI void CMLLchtoYxy (const CMLColorMachine* cm, CMLOutput Yxy , CMLInput Lch , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(Yxy, Lch, CML_Yxy_NUMCHANNELS, CML_Lch_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMLchtoLab);
  (*cm->LabtoXYZ_SB)(cm, out, count, floatalign);
  CMLCMXYZtoYxy_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CMLAPI void CMLLchtoLab (const CMLColorMachine* cm, CMLOutput Lab , CMLInput Lch , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(Lab, Lch, CML_Lab_NUMCHANNELS, CML_Lch_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMLchtoLab);
  CML_CONVERTER_RETURN;
}

CMLAPI void CMLLchtoLuv (const CMLColorMachine* cm, CMLOutput Luv , CMLInput Lch , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(Luv, Lch, CML_Luv_NUMCHANNELS, CML_Lch_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMLchtoLab);
  (*cm->LabtoXYZ_SB)(cm, out, count, floatalign);
  CMLCMXYZtoYxy_SB(cm, out, count, floatalign);
  CMLCMYxytoYupvp_SB(cm, out, count, floatalign);
  CMLCMYupvptoLuv_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CMLAPI void CMLLchtoYupvp (const CMLColorMachine* cm, CMLOutput Yupvp , CMLInput Lch , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(Yupvp, Lch, CML_Yupvp_NUMCHANNELS, CML_Lch_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMLchtoLab);
  (*cm->LabtoXYZ_SB)(cm, out, count, floatalign);
  CMLCMXYZtoYxy_SB(cm, out, count, floatalign);
  CMLCMYxytoYupvp_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CMLAPI void CMLLchtoRGB (const CMLColorMachine* cm, CMLOutput RGB , CMLInput Lch , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(RGB, Lch, CML_RGB_NUMCHANNELS, CML_Lch_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMLchtoLab);
  (*cm->LabtoXYZ_SB)(cm, out, count, floatalign);
  CMLCMXYZtoRGB_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CMLAPI void CMLLchtoYCbCr (const CMLColorMachine* cm, CMLOutput YCbCr , CMLInput Lch , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(YCbCr, Lch, CML_YCbCr_NUMCHANNELS, CML_Lch_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMLchtoLab);
  (*cm->LabtoXYZ_SB)(cm, out, count, floatalign);
  CMLCMXYZtoRGB_SB(cm, out, count, floatalign);
  CMLCMRGBtoYCbCr_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CMLAPI void CMLLchtoHSV (const CMLColorMachine* cm, CMLOutput HSV , CMLInput Lch , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(HSV, Lch, CML_HSV_NUMCHANNELS, CML_Lch_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMLchtoLab);
  (*cm->LabtoXYZ_SB)(cm, out, count, floatalign);
  CMLCMXYZtoRGB_SB(cm, out, count, floatalign);
  CMLCMRGBtoHSV_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CMLAPI void CMLLchtoHSL (const CMLColorMachine* cm, CMLOutput HSL , CMLInput Lch , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(HSL, Lch, CML_HSL_NUMCHANNELS, CML_Lch_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMLchtoLab);
  (*cm->LabtoXYZ_SB)(cm, out, count, floatalign);
  CMLCMXYZtoRGB_SB(cm, out, count, floatalign);
  CMLCMRGBtoHSV_SB(cm, out, count, floatalign);
  CMLCMHSVtoHSL_SB(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}

CMLAPI void CMLLchtoCMYK(const CMLColorMachine* cm, CMLOutput CMYK, CMLInput Lch , CMLSize count){
  CML_CONVERTER_INOUT_PARAMETER(CMYK, Lch, CML_CMYK_NUMCHANNELS, CML_Lch_NUMCHANNELS);
  CML_CONVERTER_FIRST_STEP(CMLCMLchtoLab);
  (*cm->LabtoXYZ_SB)(cm, out, count, floatalign);
  CMLCMXYZtoRGB_SB(cm, out, count, floatalign);
  (*cm->RGBtoCMYK_SB)(cm, out, count, floatalign);
  CML_CONVERTER_RETURN;
}





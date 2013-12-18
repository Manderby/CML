
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

//CMLAPI void CMLCMYKtoCMYK (const CMLColorMachine* cm, CMLOutput CMYKd , CMLInput CMYKs, CMLSize count){
//  cm = cm; // no warning
//  CML_CONVERTER_INOUT_PARAMETER(CMYKd, CMYKs, CML_CMYK_NUMCHANNELS, CML_CMYK_NUMCHANNELS);
//  CML_CONVERTER_MEMCPY(CML_CMYK_NUMCHANNELS);
//  CML_CONVERTER_RETURN;
//}
//
//// //////////////////////////
//// CMYK to anything
//// //////////////////////////
//
//CMLAPI void CMLCMYKtoXYZ (const CMLColorMachine* cm, CMLOutput XYZ , CMLInput CMYK, CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(XYZ, CMYK, CML_XYZ_NUMCHANNELS, CML_CMYK_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(*cm->CMYKtoRGB);
//  CMLCMRGBtoXYZ_SB(cm, out, count);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLCMYKtoYuv (const CMLColorMachine* cm, CMLOutput Yuv , CMLInput CMYK, CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(Yuv, CMYK, CML_Yuv_NUMCHANNELS, CML_CMYK_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(*cm->CMYKtoRGB);
//  CMLCMRGBtoXYZ_SB(cm, out, count);
//  CMLCMXYZtoYxy_SB(cm, out, count);
//  CMLCMYxytoYupvp_SB(cm, out, count);
//  CMLCMYupvptoYuv_SB(cm, out, count);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLCMYKtoYupvp (const CMLColorMachine* cm, CMLOutput Yupvp , CMLInput CMYK, CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(Yupvp, CMYK, CML_Yupvp_NUMCHANNELS, CML_CMYK_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(*cm->CMYKtoRGB);
//  CMLCMRGBtoXYZ_SB(cm, out, count);
//  CMLCMXYZtoYxy_SB(cm, out, count);
//  CMLCMYxytoYupvp_SB(cm, out, count);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLCMYKtoYxy (const CMLColorMachine* cm, CMLOutput Yxy , CMLInput CMYK, CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(Yxy, CMYK, CML_Yxy_NUMCHANNELS, CML_CMYK_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(*cm->CMYKtoRGB);
//  CMLCMRGBtoXYZ_SB(cm, out, count);
//  CMLCMXYZtoYxy_SB(cm, out, count);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLCMYKtoLab (const CMLColorMachine* cm, CMLOutput Lab , CMLInput CMYK, CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(Lab, CMYK, CML_Lab_NUMCHANNELS, CML_CMYK_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(*cm->CMYKtoRGB);
//  CMLCMRGBtoXYZ_SB(cm, out, count);
//  (*cm->XYZtoLab_SB)(cm, out, count);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLCMYKtoLch (const CMLColorMachine* cm, CMLOutput Lch , CMLInput CMYK, CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(Lch, CMYK, CML_Lch_NUMCHANNELS, CML_CMYK_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(*cm->CMYKtoRGB);
//  CMLCMRGBtoXYZ_SB(cm, out, count);
//  (*cm->XYZtoLab_SB)(cm, out, count);
//  CMLCMLabtoLch_SB(cm, out, count);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLCMYKtoLuv (const CMLColorMachine* cm, CMLOutput Luv , CMLInput CMYK, CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(Luv, CMYK, CML_Luv_NUMCHANNELS, CML_CMYK_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(*cm->CMYKtoRGB);
//  CMLCMRGBtoXYZ_SB(cm, out, count);
//  CMLCMXYZtoYxy_SB(cm, out, count);
//  CMLCMYxytoYupvp_SB(cm, out, count);
//  CMLCMYupvptoLuv_SB(cm, out, count);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLCMYKtoRGB (const CMLColorMachine* cm, CMLOutput RGB , CMLInput CMYK, CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(RGB, CMYK, CML_RGB_NUMCHANNELS, CML_CMYK_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(*cm->CMYKtoRGB);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLCMYKtoYCbCr (const CMLColorMachine* cm, CMLOutput YCbCr , CMLInput CMYK, CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(YCbCr, CMYK, CML_YCbCr_NUMCHANNELS, CML_CMYK_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(*cm->CMYKtoRGB);
//  CMLCMRGBtoYCbCr_SB(cm, out, count);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLCMYKtoHSV (const CMLColorMachine* cm, CMLOutput HSV , CMLInput CMYK, CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(HSV, CMYK, CML_HSV_NUMCHANNELS, CML_CMYK_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(*cm->CMYKtoRGB);
//  CMLCMRGBtoHSV_SB(cm, out, count);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLCMYKtoHSL (const CMLColorMachine* cm, CMLOutput HSL , CMLInput CMYK, CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(HSL, CMYK, CML_HSL_NUMCHANNELS, CML_CMYK_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(*cm->CMYKtoRGB);
//  CMLCMRGBtoHSV_SB(cm, out, count);
//  CMLCMHSVtoHSL_SB(cm, out, count);
//  CML_CONVERTER_RETURN;
//}


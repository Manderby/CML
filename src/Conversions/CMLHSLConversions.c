
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

//CMLAPI void CMLHSLtoHSL (const CMLColorMachine* cm, CMLOutput HSLd , CMLInput HSLs, CMLSize count){
//  cm = cm; // no warning
//  CML_CONVERTER_INOUT_PARAMETER(HSLd, HSLs, CML_HSL_NUMCHANNELS, CML_HSL_NUMCHANNELS);
//  CML_CONVERTER_MEMCPY(CML_HSL_NUMCHANNELS);
//  CML_CONVERTER_RETURN;
//}


// //////////////////////////
// HSL to anything
// //////////////////////////

//CMLAPI void CMLHSLtoXYZ (const CMLColorMachine* cm, CMLOutput XYZ , CMLInput HSL , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(XYZ, HSL, CML_XYZ_NUMCHANNELS, CML_HSL_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(CMLCMHSLtoHSV);
//  CMLCMHSVtoRGB_SB(cm, out, count);
//  CMLCMRGBtoXYZ_SB(cm, out, count);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLHSLtoYuv (const CMLColorMachine* cm, CMLOutput Yuv , CMLInput HSL , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(Yuv, HSL, CML_Yuv_NUMCHANNELS, CML_HSL_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(CMLCMHSLtoHSV);
//  CMLCMHSVtoRGB_SB(cm, out, count);
//  CMLCMRGBtoXYZ_SB(cm, out, count);
//  CMLCMXYZtoYxy_SB(cm, out, count);
//  CMLCMYxytoYupvp_SB(cm, out, count);
//  CMLCMYupvptoYuv_SB(cm, out, count);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLHSLtoYupvp (const CMLColorMachine* cm, CMLOutput Yupvp , CMLInput HSL , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(Yupvp, HSL, CML_Yupvp_NUMCHANNELS, CML_HSL_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(CMLCMHSLtoHSV);
//  CMLCMHSVtoRGB_SB(cm, out, count);
//  CMLCMRGBtoXYZ_SB(cm, out, count);
//  CMLCMXYZtoYxy_SB(cm, out, count);
//  CMLCMYxytoYupvp_SB(cm, out, count);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLHSLtoYxy (const CMLColorMachine* cm, CMLOutput Yxy , CMLInput HSL , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(Yxy, HSL, CML_Yxy_NUMCHANNELS, CML_HSL_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(CMLCMHSLtoHSV);
//  CMLCMHSVtoRGB_SB(cm, out, count);
//  CMLCMRGBtoXYZ_SB(cm, out, count);
//  CMLCMXYZtoYxy_SB(cm, out, count);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLHSLtoLab (const CMLColorMachine* cm, CMLOutput Lab , CMLInput HSL , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(Lab, HSL, CML_Lab_NUMCHANNELS, CML_HSL_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(CMLCMHSLtoHSV);
//  CMLCMHSVtoRGB_SB(cm, out, count);
//  CMLCMRGBtoXYZ_SB(cm, out, count);
//  (*cm->XYZtoLab_SB)(cm, out, count);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLHSLtoLch (const CMLColorMachine* cm, CMLOutput Lch , CMLInput HSL , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(Lch, HSL, CML_Lch_NUMCHANNELS, CML_HSL_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(CMLCMHSLtoHSV);
//  CMLCMHSVtoRGB_SB(cm, out, count);
//  CMLCMRGBtoXYZ_SB(cm, out, count);
//  (*cm->XYZtoLab_SB)(cm, out, count);
//  CMLCMLabtoLch_SB(cm, out, count);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLHSLtoLuv (const CMLColorMachine* cm, CMLOutput Luv , CMLInput HSL , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(Luv, HSL, CML_Luv_NUMCHANNELS, CML_HSL_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(CMLCMHSLtoHSV);
//  CMLCMHSVtoRGB_SB(cm, out, count);
//  CMLCMRGBtoXYZ_SB(cm, out, count);
//  CMLCMXYZtoYxy_SB(cm, out, count);
//  CMLCMYxytoYupvp_SB(cm, out, count);
//  CMLCMYupvptoLuv_SB(cm, out, count);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLHSLtoRGB (const CMLColorMachine* cm, CMLOutput RGB , CMLInput HSL , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(RGB, HSL, CML_RGB_NUMCHANNELS, CML_HSL_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(CMLCMHSLtoHSV);
//  CMLCMHSVtoRGB_SB(cm, out, count);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLHSLtoYCbCr (const CMLColorMachine* cm, CMLOutput YCbCr , CMLInput HSL , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(YCbCr, HSL, CML_YCbCr_NUMCHANNELS, CML_HSL_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(CMLCMHSLtoHSV);
//  CMLCMHSVtoRGB_SB(cm, out, count);
//  CMLCMRGBtoYCbCr_SB(cm, out, count);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLHSLtoHSV (const CMLColorMachine* cm, CMLOutput HSV , CMLInput HSL , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(HSV, HSL, CML_HSV_NUMCHANNELS, CML_HSL_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(CMLCMHSLtoHSV);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLHSLtoCMYK(const CMLColorMachine* cm, CMLOutput CMYK, CMLInput HSL , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(CMYK, HSL, CML_CMYK_NUMCHANNELS, CML_HSL_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(CMLCMHSLtoHSV);
//  (*cm->RGBtoCMYK_SB)(cm, out, count);
//  CML_CONVERTER_RETURN;
//}





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

//CMLAPI void CMLYxytoYxy (const CMLColorMachine* cm, CMLOutput Yxyd , CMLInput Yxys, CMLSize count){
//  cm = cm; // no warning
//  CML_CONVERTER_INOUT_PARAMETER(Yxyd, Yxys, CML_Yxy_NUMCHANNELS, CML_Yxy_NUMCHANNELS);
//  CML_CONVERTER_MEMCPY(CML_Yxy_NUMCHANNELS);
//  CML_CONVERTER_RETURN;
//}


// //////////////////////////
// Yxy to anything
// //////////////////////////

//CMLAPI void CMLYxytoXYZ (const CMLColorMachine* cm, CMLOutput XYZ , CMLInput Yxy , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(XYZ, Yxy, CML_XYZ_NUMCHANNELS, CML_Yxy_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(CMLCMYxytoXYZ);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLYxytoYuv (const CMLColorMachine* cm, CMLOutput Yuv , CMLInput Yxy , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(Yuv, Yxy, CML_Yuv_NUMCHANNELS, CML_Yxy_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(CMLCMYxytoYupvp);
//  CMLCMYupvptoYuv_SB(cm, out, count);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLYxytoYupvp (const CMLColorMachine* cm, CMLOutput Yupvp , CMLInput Yxy , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(Yupvp, Yxy, CML_Yupvp_NUMCHANNELS, CML_Yxy_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(CMLCMYxytoYupvp);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLYxytoLab (const CMLColorMachine* cm, CMLOutput Lab , CMLInput Yxy , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(Lab, Yxy, CML_Lab_NUMCHANNELS, CML_Yxy_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(CMLCMYxytoXYZ);
//  (*cm->XYZtoLab_SB)(cm, out, count);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLYxytoLch (const CMLColorMachine* cm, CMLOutput Lch , CMLInput Yxy , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(Lch, Yxy, CML_Lch_NUMCHANNELS, CML_Yxy_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(CMLCMYxytoXYZ);
//  (*cm->XYZtoLab_SB)(cm, out, count);
//  CMLCMLabtoLch_SB(cm, out, count);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLYxytoLuv (const CMLColorMachine* cm, CMLOutput Luv , CMLInput Yxy , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(Luv, Yxy, CML_Luv_NUMCHANNELS, CML_Yxy_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(CMLCMYxytoYupvp);
//  CMLCMYupvptoLuv_SB(cm, out, count);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLYxytoRGB (const CMLColorMachine* cm, CMLOutput RGB , CMLInput Yxy , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(RGB, Yxy, CML_RGB_NUMCHANNELS, CML_Yxy_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(CMLCMYxytoXYZ);
//  CMLCMXYZtoRGB_SB(cm, out, count);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLYxytoYCbCr (const CMLColorMachine* cm, CMLOutput YCbCr , CMLInput Yxy , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(YCbCr, Yxy, CML_YCbCr_NUMCHANNELS, CML_Yxy_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(CMLCMYxytoXYZ);
//  CMLCMXYZtoRGB_SB(cm, out, count);
//  CMLCMRGBtoYCbCr_SB(cm, out, count);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLYxytoHSV (const CMLColorMachine* cm, CMLOutput HSV , CMLInput Yxy , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(HSV, Yxy, CML_HSV_NUMCHANNELS, CML_Yxy_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(CMLCMYxytoXYZ);
//  CMLCMXYZtoRGB_SB(cm, out, count);
//  CMLCMRGBtoHSV_SB(cm, out, count);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLYxytoHSL (const CMLColorMachine* cm, CMLOutput HSL , CMLInput Yxy , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(HSL, Yxy, CML_HSL_NUMCHANNELS, CML_Yxy_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(CMLCMYxytoXYZ);
//  CMLCMXYZtoRGB_SB(cm, out, count);
//  CMLCMRGBtoHSV_SB(cm, out, count);
//  CMLCMHSVtoHSL_SB(cm, out, count);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLYxytoCMYK(const CMLColorMachine* cm, CMLOutput CMYK, CMLInput Yxy , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(CMYK, Yxy, CML_CMYK_NUMCHANNELS, CML_Yxy_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(CMLCMYxytoXYZ);
//  CMLCMXYZtoRGB_SB(cm, out, count);
//  (*cm->RGBtoCMYK_SB)(cm, out, count);
//  CML_CONVERTER_RETURN;
//}





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

//CMLAPI void CMLXYZtoXYZ (const CMLColorMachine* cm, CMLOutput XYZd , CMLInput XYZs, CMLSize count){
//  cm = cm; // no warning
//  CML_CONVERTER_INOUT_PARAMETER(XYZd, XYZs, CML_XYZ_NUMCHANNELS, CML_XYZ_NUMCHANNELS);
//  CML_CONVERTER_MEMCPY(CML_XYZ_NUMCHANNELS);
//  CML_CONVERTER_RETURN;
//}

// //////////////////////////
// XYZ to anything
// //////////////////////////

//CMLAPI void CMLXYZtoYxy (const CMLColorMachine* cm, CMLOutput Yxy , CMLInput XYZ , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(Yxy, XYZ, CML_Yxy_NUMCHANNELS, CML_XYZ_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(CMLCMXYZtoYxy);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLXYZtoYuv (const CMLColorMachine* cm, CMLOutput Yuv , CMLInput XYZ , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(Yuv, XYZ, CML_Yuv_NUMCHANNELS, CML_XYZ_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(CMLCMXYZtoYxy);
//  CMLCMYxytoYupvp_SB(cm, out, count);
//  CMLCMYupvptoYuv_SB(cm, out, count);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLXYZtoYupvp (const CMLColorMachine* cm, CMLOutput Yupvp , CMLInput XYZ , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(Yupvp, XYZ, CML_Yupvp_NUMCHANNELS, CML_XYZ_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(CMLCMXYZtoYxy);
//  CMLCMYxytoYupvp_SB(cm, out, count);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLXYZtoLab (const CMLColorMachine* cm, CMLOutput Lab , CMLInput XYZ , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(Lab, XYZ, CML_Lab_NUMCHANNELS, CML_XYZ_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(*cm->XYZtoLab);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLXYZtoLch (const CMLColorMachine* cm, CMLOutput Lch , CMLInput XYZ , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(Lch, XYZ, CML_Lch_NUMCHANNELS, CML_XYZ_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(*cm->XYZtoLab);
//  CMLCMLabtoLch_SB(cm, out, count);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLXYZtoLuv (const CMLColorMachine* cm, CMLOutput Luv , CMLInput XYZ , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(Luv, XYZ, CML_Luv_NUMCHANNELS, CML_XYZ_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(CMLCMXYZtoYxy);
//  CMLCMYxytoYupvp_SB(cm, out, count);
//  CMLCMYupvptoLuv_SB(cm, out, count);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLXYZtoRGB (const CMLColorMachine* cm, CMLOutput RGB , CMLInput XYZ , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(RGB, XYZ, CML_RGB_NUMCHANNELS, CML_XYZ_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(CMLCMXYZtoRGB);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLXYZtoYCbCr (const CMLColorMachine* cm, CMLOutput YCbCr, CMLInput XYZ , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(YCbCr, XYZ, CML_YCbCr_NUMCHANNELS, CML_XYZ_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(CMLCMXYZtoRGB);
//  CMLCMRGBtoYCbCr_SB(cm, out, count);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLXYZtoHSV (const CMLColorMachine* cm, CMLOutput HSV , CMLInput XYZ , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(HSV, XYZ, CML_HSV_NUMCHANNELS, CML_XYZ_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(CMLCMXYZtoRGB);
//  CMLCMRGBtoHSV_SB(cm, out, count);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLXYZtoHSL (const CMLColorMachine* cm, CMLOutput HSL , CMLInput XYZ , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(HSL, XYZ, CML_HSL_NUMCHANNELS, CML_XYZ_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(CMLCMXYZtoRGB);
//  CMLCMRGBtoHSV_SB(cm, out, count);
//  CMLCMHSVtoHSL_SB(cm, out, count);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLXYZtoCMYK(const CMLColorMachine* cm, CMLOutput CMYK, CMLInput XYZ , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(CMYK, XYZ, CML_CMYK_NUMCHANNELS, CML_XYZ_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(CMLCMXYZtoRGB);
//  (*cm->RGBtoCMYK_SB)(cm, out, count);
//  CML_CONVERTER_RETURN;
//}



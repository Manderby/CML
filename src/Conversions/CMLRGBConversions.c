
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

//CMLAPI void CMLRGBtoRGB (const CMLColorMachine* cm, CMLOutput RGBd , CMLInput RGBs, CMLSize count){
//  cm = cm; // no warning
//  CML_CONVERTER_INOUT_PARAMETER(RGBd, RGBs, CML_RGB_NUMCHANNELS, CML_RGB_NUMCHANNELS);
//  CML_CONVERTER_MEMCPY(CML_RGB_NUMCHANNELS);
//  CML_CONVERTER_RETURN;
//}

// //////////////////////////
// RGB to anything
// //////////////////////////

//CMLAPI void CMLRGBtoXYZ (const CMLColorMachine* cm, CMLOutput XYZ , CMLInput RGB , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(XYZ, RGB, CML_XYZ_NUMCHANNELS, CML_RGB_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(CMLCMRGBtoXYZ);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLRGBtoYxy (const CMLColorMachine* cm, CMLOutput Yxy , CMLInput RGB , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(Yxy, RGB, CML_Yxy_NUMCHANNELS, CML_RGB_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(CMLCMRGBtoXYZ);
//  CMLCMXYZtoYxy_SB(cm, out, count);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLRGBtoYuv (const CMLColorMachine* cm, CMLOutput Yuv , CMLInput RGB , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(Yuv, RGB, CML_Yuv_NUMCHANNELS, CML_RGB_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(CMLCMRGBtoXYZ);
//  CMLCMXYZtoYxy_SB(cm, out, count);
//  CMLCMYxytoYupvp_SB(cm, out, count);
//  CMLCMYupvptoYuv_SB(cm, out, count);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLRGBtoYupvp (const CMLColorMachine* cm, CMLOutput Yupvp , CMLInput RGB , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(Yupvp, RGB, CML_Yupvp_NUMCHANNELS, CML_RGB_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(CMLCMRGBtoXYZ);
//  CMLCMXYZtoYxy_SB(cm, out, count);
//  CMLCMYxytoYupvp_SB(cm, out, count);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLRGBtoLab (const CMLColorMachine* cm, CMLOutput Lab , CMLInput RGB , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(Lab, RGB, CML_Lab_NUMCHANNELS, CML_RGB_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(CMLCMRGBtoXYZ);
//  (*cm->XYZtoLab_SB)(cm, out, count);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLRGBtoLch (const CMLColorMachine* cm, CMLOutput Lch , CMLInput RGB , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(Lch, RGB, CML_Lch_NUMCHANNELS, CML_RGB_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(CMLCMRGBtoXYZ);
//  (*cm->XYZtoLab_SB)(cm, out, count);
//  CMLCMLabtoLch_SB(cm, out, count);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLRGBtoLuv (const CMLColorMachine* cm, CMLOutput Luv , CMLInput RGB , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(Luv, RGB, CML_Luv_NUMCHANNELS, CML_RGB_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(CMLCMRGBtoXYZ);
//  CMLCMXYZtoYxy_SB(cm, out, count);
//  CMLCMYxytoYupvp_SB(cm, out, count);
//  CMLCMYupvptoLuv_SB(cm, out, count);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLRGBtoYCbCr (const CMLColorMachine* cm, CMLOutput YCbCr , CMLInput RGB , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(YCbCr, RGB, CML_YCbCr_NUMCHANNELS, CML_RGB_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(CMLCMRGBtoYCbCr);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLRGBtoHSV (const CMLColorMachine* cm, CMLOutput HSV , CMLInput RGB , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(HSV, RGB, CML_HSV_NUMCHANNELS, CML_RGB_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(CMLCMRGBtoHSV);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLRGBtoHSL (const CMLColorMachine* cm, CMLOutput HSL , CMLInput RGB , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(HSL, RGB, CML_HSL_NUMCHANNELS, CML_RGB_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(CMLCMRGBtoHSV);
//  CMLCMHSVtoHSL_SB(cm, out, count);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLRGBtoCMYK(const CMLColorMachine* cm, CMLOutput CMYK, CMLInput RGB , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(CMYK, RGB, CML_CMYK_NUMCHANNELS, CML_RGB_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(*cm->RGBtoCMYK);
//  CML_CONVERTER_RETURN;
//}




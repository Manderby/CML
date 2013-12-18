
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

//CMLAPI void CMLLuvtoLuv (const CMLColorMachine* cm, CMLOutput Luvd , CMLInput Luvs, CMLSize count){
//  cm = cm; // no warning
//  CML_CONVERTER_INOUT_PARAMETER(Luvd, Luvs, CML_Luv_NUMCHANNELS, CML_Luv_NUMCHANNELS);
//  CML_CONVERTER_MEMCPY(CML_Luv_NUMCHANNELS);
//  CML_CONVERTER_RETURN;
//}

// //////////////////////////
// Luv to anything
// //////////////////////////

//CMLAPI void CMLLuvtoXYZ (const CMLColorMachine* cm, CMLOutput XYZ , CMLInput Luv , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(XYZ, Luv, CML_XYZ_NUMCHANNELS, CML_Luv_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(CMLCMLuvtoYupvp);
//  CMLCMYupvptoYxy_SB(cm, out, count);
//  CMLCMYxytoXYZ_SB(cm, out, count);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLLuvtoYxy (const CMLColorMachine* cm, CMLOutput Yxy , CMLInput Luv , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(Yxy, Luv, CML_Yxy_NUMCHANNELS, CML_Luv_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(CMLCMLuvtoYupvp);
//  CMLCMYupvptoYxy_SB(cm, out, count);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLLuvtoYuv (const CMLColorMachine* cm, CMLOutput Yuv , CMLInput Luv , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(Yuv, Luv, CML_Yuv_NUMCHANNELS, CML_Luv_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(CMLCMLuvtoYupvp);
//  CMLCMYupvptoYuv_SB(cm, out, count);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLLuvtoYupvp (const CMLColorMachine* cm, CMLOutput Yupvp , CMLInput Luv , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(Yupvp, Luv, CML_Yupvp_NUMCHANNELS, CML_Luv_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(CMLCMLuvtoYupvp);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLLuvtoLab (const CMLColorMachine* cm, CMLOutput Lab , CMLInput Luv , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(Lab, Luv, CML_Lab_NUMCHANNELS, CML_Luv_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(CMLCMLuvtoYupvp);
//  CMLCMYupvptoYxy_SB(cm, out, count);
//  CMLCMYxytoXYZ_SB(cm, out, count);
//  (*cm->XYZtoLab_SB)(cm, out, count);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLLuvtoLch (const CMLColorMachine* cm, CMLOutput Lch , CMLInput Luv , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(Lch, Luv, CML_Lch_NUMCHANNELS, CML_Luv_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(CMLCMLuvtoYupvp);
//  CMLCMYupvptoYxy_SB(cm, out, count);
//  CMLCMYxytoXYZ_SB(cm, out, count);
//  (*cm->XYZtoLab_SB)(cm, out, count);
//  CMLCMLabtoLch_SB(cm, out, count);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLLuvtoRGB (const CMLColorMachine* cm, CMLOutput RGB , CMLInput Luv , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(RGB, Luv, CML_RGB_NUMCHANNELS, CML_Luv_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(CMLCMLuvtoYupvp);
//  CMLCMYupvptoYxy_SB(cm, out, count);
//  CMLCMYxytoXYZ_SB(cm, out, count);
//  CMLCMXYZtoRGB_SB(cm, out, count);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLLuvtoYCbCr (const CMLColorMachine* cm, CMLOutput YCbCr , CMLInput Luv , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(YCbCr, Luv, CML_YCbCr_NUMCHANNELS, CML_Luv_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(CMLCMLuvtoYupvp);
//  CMLCMYupvptoYxy_SB(cm, out, count);
//  CMLCMYxytoXYZ_SB(cm, out, count);
//  CMLCMXYZtoRGB_SB(cm, out, count);
//  CMLCMRGBtoYCbCr_SB(cm, out, count);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLLuvtoHSV (const CMLColorMachine* cm, CMLOutput HSV , CMLInput Luv , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(HSV, Luv, CML_HSV_NUMCHANNELS, CML_Luv_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(CMLCMLuvtoYupvp);
//  CMLCMYupvptoYxy_SB(cm, out, count);
//  CMLCMYxytoXYZ_SB(cm, out, count);
//  CMLCMXYZtoRGB_SB(cm, out, count);
//  CMLCMRGBtoHSV_SB(cm, out, count);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLLuvtoHSL (const CMLColorMachine* cm, CMLOutput HSL , CMLInput Luv , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(HSL, Luv, CML_HSL_NUMCHANNELS, CML_Luv_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(CMLCMLuvtoYupvp);
//  CMLCMYupvptoYxy_SB(cm, out, count);
//  CMLCMYxytoXYZ_SB(cm, out, count);
//  CMLCMXYZtoRGB_SB(cm, out, count);
//  CMLCMRGBtoHSV_SB(cm, out, count);
//  CMLCMHSVtoHSL_SB(cm, out, count);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLLuvtoCMYK(const CMLColorMachine* cm, CMLOutput CMYK, CMLInput Luv , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(CMYK, Luv, CML_CMYK_NUMCHANNELS, CML_Luv_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(CMLCMLuvtoYupvp);
//  CMLCMYupvptoYxy_SB(cm, out, count);
//  CMLCMYxytoXYZ_SB(cm, out, count);
//  CMLCMXYZtoRGB_SB(cm, out, count);
//  (*cm->RGBtoCMYK_SB)(cm, out, count);
//  CML_CONVERTER_RETURN;
//}





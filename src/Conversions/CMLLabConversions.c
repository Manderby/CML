
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

//CMLAPI void CMLLabtoLab (const CMLColorMachine* cm, CMLOutput Labd , CMLInput Labs, CMLSize count){
//  cm = cm; // no warning
//  CML_CONVERTER_INOUT_PARAMETER(Labd, Labs, CML_Lab_NUMCHANNELS, CML_Lab_NUMCHANNELS);
//  CML_CONVERTER_MEMCPY(CML_Lab_NUMCHANNELS);
//  CML_CONVERTER_RETURN;
//}


// //////////////////////////
// Lab to anything
// //////////////////////////

//CMLAPI void CMLLabtoXYZ (const CMLColorMachine* cm, CMLOutput XYZ , CMLInput Lab , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(XYZ, Lab, CML_XYZ_NUMCHANNELS, CML_Lab_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(*cm->LabtoXYZ);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLLabtoYuv (const CMLColorMachine* cm, CMLOutput Yuv , CMLInput Lab , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(Yuv, Lab, CML_Yuv_NUMCHANNELS, CML_Lab_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(*cm->LabtoXYZ);
//  CMLCMXYZtoYxy_SB(cm, out, count);
//  CMLCMYxytoYupvp_SB(cm, out, count);
//  CMLCMYupvptoYuv_SB(cm, out, count);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLLabtoYxy (const CMLColorMachine* cm, CMLOutput Yxy , CMLInput Lab , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(Yxy, Lab, CML_Yxy_NUMCHANNELS, CML_Lab_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(*cm->LabtoXYZ);
//  CMLCMXYZtoYxy_SB(cm, out, count);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLLabtoLch (const CMLColorMachine* cm, CMLOutput Lch , CMLInput Lab , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(Lch, Lab, CML_Lch_NUMCHANNELS, CML_Lab_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(CMLCMLabtoLch);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLLabtoLuv (const CMLColorMachine* cm, CMLOutput Luv , CMLInput Lab , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(Luv, Lab, CML_Luv_NUMCHANNELS, CML_Lab_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(*cm->LabtoXYZ);
//  CMLCMXYZtoYxy_SB(cm, out, count);
//  CMLCMYxytoYupvp_SB(cm, out, count);
//  CMLCMYupvptoLuv_SB(cm, out, count);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLLabtoYupvp (const CMLColorMachine* cm, CMLOutput Yupvp , CMLInput Lab , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(Yupvp, Lab, CML_Yupvp_NUMCHANNELS, CML_Lab_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(*cm->LabtoXYZ);
//  CMLCMXYZtoYxy_SB(cm, out, count);
//  CMLCMYxytoYupvp_SB(cm, out, count);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLLabtoRGB (const CMLColorMachine* cm, CMLOutput RGB , CMLInput Lab , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(RGB, Lab, CML_RGB_NUMCHANNELS, CML_Lab_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(*cm->LabtoXYZ);
//  CMLCMXYZtoRGB_SB(cm, out, count);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLLabtoYCbCr (const CMLColorMachine* cm, CMLOutput YCbCr , CMLInput Lab , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(YCbCr, Lab, CML_YCbCr_NUMCHANNELS, CML_Lab_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(*cm->LabtoXYZ);
//  CMLCMXYZtoRGB_SB(cm, out, count);
//  CMLCMRGBtoYCbCr_SB(cm, out, count);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLLabtoHSV (const CMLColorMachine* cm, CMLOutput HSV , CMLInput Lab , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(HSV, Lab, CML_HSV_NUMCHANNELS, CML_Lab_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(*cm->LabtoXYZ);
//  CMLCMXYZtoRGB_SB(cm, out, count);
//  CMLCMRGBtoHSV_SB(cm, out, count);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLLabtoHSL (const CMLColorMachine* cm, CMLOutput HSL , CMLInput Lab , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(HSL, Lab, CML_HSL_NUMCHANNELS, CML_Lab_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(*cm->LabtoXYZ);
//  CMLCMXYZtoRGB_SB(cm, out, count);
//  CMLCMRGBtoHSV_SB(cm, out, count);
//  CMLCMHSVtoHSL_SB(cm, out, count);
//  CML_CONVERTER_RETURN;
//}
//
//CMLAPI void CMLLabtoCMYK(const CMLColorMachine* cm, CMLOutput CMYK, CMLInput Lab , CMLSize count){
//  CML_CONVERTER_INOUT_PARAMETER(CMYK, Lab, CML_CMYK_NUMCHANNELS, CML_Lab_NUMCHANNELS);
//  CML_CONVERTER_FIRST_STEP(*cm->LabtoXYZ);
//  CMLCMXYZtoRGB_SB(cm, out, count);
//  (*cm->RGBtoCMYK_SB)(cm, out, count);
//  CML_CONVERTER_RETURN;
//}






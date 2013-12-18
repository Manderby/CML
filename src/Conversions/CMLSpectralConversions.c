
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

#include "../CML.h"
#include "../StateMachine/CMLColorMachineState.h"
#include "../StateMachine/CMLConverterMacros.h"


// //////////////////////////
// Spectrum Illumination to anything
// //////////////////////////

//CMLAPI void CMLSpectrumIlluminationtoXYZ (const CMLColorMachine* cm, CMLOutput XYZ , CMLInput specill, CMLSize count){
//  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(XYZ, specill, CML_XYZ_NUMCHANNELS);
//  CMLCMIlluminationSpectrumtoXYZ(cm, xyzbuf, in, count);
//  CML_CONVERTER_SPECTRUM_RETURN;
//}
//
//CMLAPI void CMLSpectrumIlluminationtoYuv (const CMLColorMachine* cm, CMLOutput Yuv , CMLInput specill, CMLSize count){
//  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(Yuv, specill, CML_Yuv_NUMCHANNELS);
//  CMLCMIlluminationSpectrumtoXYZ(cm, xyzbuf, in, count);
//  CMLXYZtoYuv(cm, out, xyzbuf, count);
//  CML_CONVERTER_SPECTRUM_RETURN;
//}
//
//CMLAPI void CMLSpectrumIlluminationtoYupvp (const CMLColorMachine* cm, CMLOutput Yupvp , CMLInput specill, CMLSize count){
//  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(Yupvp, specill, CML_Yupvp_NUMCHANNELS);
//  CMLCMIlluminationSpectrumtoXYZ(cm, xyzbuf, in, count);
//  CMLXYZtoYupvp(cm, out, xyzbuf, count);
//  CML_CONVERTER_SPECTRUM_RETURN;
//}
//
//CMLAPI void CMLSpectrumIlluminationtoYxy (const CMLColorMachine* cm, CMLOutput Yxy , CMLInput specill, CMLSize count){
//  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(Yxy, specill, CML_Yxy_NUMCHANNELS);
//  CMLCMIlluminationSpectrumtoXYZ(cm, xyzbuf, in, count);
//  CMLXYZtoYxy(cm, out, xyzbuf, count);
//  CML_CONVERTER_SPECTRUM_RETURN;
//}
//
//CMLAPI void CMLSpectrumIlluminationtoLab (const CMLColorMachine* cm, CMLOutput Lab , CMLInput specill, CMLSize count){
//  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(Lab, specill, CML_Lab_NUMCHANNELS);
//  CMLCMIlluminationSpectrumtoXYZ(cm, xyzbuf, in, count);
//  CMLXYZtoLab(cm, out, xyzbuf, count);
//  CML_CONVERTER_SPECTRUM_RETURN;
//}
//
//CMLAPI void CMLSpectrumIlluminationtoLch (const CMLColorMachine* cm, CMLOutput Lch , CMLInput specill, CMLSize count){
//  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(Lch, specill, CML_Lch_NUMCHANNELS);
//  CMLCMIlluminationSpectrumtoXYZ(cm, xyzbuf, in, count);
//  CMLXYZtoLch(cm, out, xyzbuf, count);
//  CML_CONVERTER_SPECTRUM_RETURN;
//}
//
//CMLAPI void CMLSpectrumIlluminationtoLuv (const CMLColorMachine* cm, CMLOutput Luv , CMLInput specill, CMLSize count){
//  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(Luv, specill, CML_Luv_NUMCHANNELS);
//  CMLCMIlluminationSpectrumtoXYZ(cm, xyzbuf, in, count);
//  CMLXYZtoLuv(cm, out, xyzbuf, count);
//  CML_CONVERTER_SPECTRUM_RETURN;
//}
//
//CMLAPI void CMLSpectrumIlluminationtoRGB (const CMLColorMachine* cm, CMLOutput RGB , CMLInput specill, CMLSize count){
//  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(RGB, specill, CML_RGB_NUMCHANNELS);
//  CMLCMIlluminationSpectrumtoXYZ(cm, xyzbuf, in, count);
//  CMLXYZtoRGB(cm, out, xyzbuf, count);
//  CML_CONVERTER_SPECTRUM_RETURN;
//}
//
//CMLAPI void CMLSpectrumIlluminationtoYCbCr (const CMLColorMachine* cm, CMLOutput YCbCr , CMLInput specill, CMLSize count){
//  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(YCbCr, specill, CML_YCbCr_NUMCHANNELS);
//  CMLCMIlluminationSpectrumtoXYZ(cm, xyzbuf, in, count);
//  CMLXYZtoYCbCr(cm, out, xyzbuf, count);
//  CML_CONVERTER_SPECTRUM_RETURN;
//}
//
//CMLAPI void CMLSpectrumIlluminationtoHSV (const CMLColorMachine* cm, CMLOutput HSV , CMLInput specill, CMLSize count){
//  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(HSV, specill, CML_HSV_NUMCHANNELS);
//  CMLCMIlluminationSpectrumtoXYZ(cm, xyzbuf, in, count);
//  CMLXYZtoHSV(cm, out, xyzbuf, count);
//  CML_CONVERTER_SPECTRUM_RETURN;
//}
//
//CMLAPI void CMLSpectrumIlluminationtoHSL (const CMLColorMachine* cm, CMLOutput HSL , CMLInput specill, CMLSize count){
//  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(HSL, specill, CML_HSL_NUMCHANNELS);
//  CMLCMIlluminationSpectrumtoXYZ(cm, xyzbuf, in, count);
//  CMLXYZtoHSL(cm, out, xyzbuf, count);
//  CML_CONVERTER_SPECTRUM_RETURN;
//}
//
//CMLAPI void CMLSpectrumIlluminationtoCMYK(const CMLColorMachine* cm, CMLOutput CMYK, CMLInput specill, CMLSize count){
//  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(CMYK, specill, CML_CMYK_NUMCHANNELS);
//  CMLCMIlluminationSpectrumtoXYZ(cm, xyzbuf, in, count);
//  CMLXYZtoCMYK(cm, out, xyzbuf, count);
//  CML_CONVERTER_SPECTRUM_RETURN;
//}








// //////////////////////////
// Spectrum Remission to anything
// //////////////////////////

//CMLAPI void CMLSpectrumRemissiontoXYZ (const CMLColorMachine* cm, CMLOutput XYZ , CMLInput specrem, CMLSize count){
//  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(XYZ, specrem, CML_XYZ_NUMCHANNELS);
//  CMLCMRemissionSpectrumtoXYZ(cm, xyzbuf, in, count);
//  CML_CONVERTER_SPECTRUM_RETURN;
//}
//
//CMLAPI void CMLSpectrumRemissiontoYuv (const CMLColorMachine* cm, CMLOutput Yuv , CMLInput specrem, CMLSize count){
//  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(Yuv, specrem, CML_Yuv_NUMCHANNELS);
//  CMLCMRemissionSpectrumtoXYZ(cm, xyzbuf, in, count);
//  CMLXYZtoYuv(cm, out, xyzbuf, count);
//  CML_CONVERTER_SPECTRUM_RETURN;
//}
//
//CMLAPI void CMLSpectrumRemissiontoYupvp (const CMLColorMachine* cm, CMLOutput Yupvp , CMLInput specrem, CMLSize count){
//  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(Yupvp, specrem, CML_Yupvp_NUMCHANNELS);
//  CMLCMRemissionSpectrumtoXYZ(cm, xyzbuf, in, count);
//  CMLXYZtoYupvp(cm, out, xyzbuf, count);
//  CML_CONVERTER_SPECTRUM_RETURN;
//}
//
//CMLAPI void CMLSpectrumRemissiontoYxy (const CMLColorMachine* cm, CMLOutput Yxy , CMLInput specrem, CMLSize count){
//  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(Yxy, specrem, CML_Yxy_NUMCHANNELS);
//  CMLCMRemissionSpectrumtoXYZ(cm, xyzbuf, in, count);
//  CMLXYZtoYxy(cm, out, xyzbuf, count);
//  CML_CONVERTER_SPECTRUM_RETURN;
//}
//
//CMLAPI void CMLSpectrumRemissiontoLab (const CMLColorMachine* cm, CMLOutput Lab , CMLInput specrem, CMLSize count){
//  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(Lab, specrem, CML_Lab_NUMCHANNELS);
//  CMLCMRemissionSpectrumtoXYZ(cm, xyzbuf, in, count);
//  CMLXYZtoLab(cm, out, xyzbuf, count);
//  CML_CONVERTER_SPECTRUM_RETURN;
//}
//
//CMLAPI void CMLSpectrumRemissiontoLch (const CMLColorMachine* cm, CMLOutput Lch , CMLInput specrem, CMLSize count){
//  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(Lch, specrem, CML_Lch_NUMCHANNELS);
//  CMLCMRemissionSpectrumtoXYZ(cm, xyzbuf, in, count);
//  CMLXYZtoLch(cm, out, xyzbuf, count);
//  CML_CONVERTER_SPECTRUM_RETURN;
//}
//
//CMLAPI void CMLSpectrumRemissiontoLuv (const CMLColorMachine* cm, CMLOutput Luv , CMLInput specrem, CMLSize count){
//  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(Luv, specrem, CML_Luv_NUMCHANNELS);
//  CMLCMRemissionSpectrumtoXYZ(cm, xyzbuf, in, count);
//  CMLXYZtoLuv(cm, out, xyzbuf, count);
//  CML_CONVERTER_SPECTRUM_RETURN;
//}
//
//CMLAPI void CMLSpectrumRemissiontoRGB (const CMLColorMachine* cm, CMLOutput RGB , CMLInput specrem, CMLSize count){
//  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(RGB, specrem, CML_RGB_NUMCHANNELS);
//  CMLCMRemissionSpectrumtoXYZ(cm, xyzbuf, in, count);
//  CMLXYZtoRGB(cm, out, xyzbuf, count);
//  CML_CONVERTER_SPECTRUM_RETURN;
//}
//
//CMLAPI void CMLSpectrumRemissiontoYCbCr (const CMLColorMachine* cm, CMLOutput YCbCr , CMLInput specrem, CMLSize count){
//  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(YCbCr, specrem, CML_YCbCr_NUMCHANNELS);
//  CMLCMRemissionSpectrumtoXYZ(cm, xyzbuf, in, count);
//  CMLXYZtoYCbCr(cm, out, xyzbuf, count);
//  CML_CONVERTER_SPECTRUM_RETURN;
//}
//
//CMLAPI void CMLSpectrumRemissiontoHSV (const CMLColorMachine* cm, CMLOutput HSV , CMLInput specrem, CMLSize count){
//  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(HSV, specrem, CML_HSV_NUMCHANNELS);
//  CMLCMRemissionSpectrumtoXYZ(cm, xyzbuf, in, count);
//  CMLXYZtoHSV(cm, out, xyzbuf, count);
//  CML_CONVERTER_SPECTRUM_RETURN;
//}
//
//CMLAPI void CMLSpectrumRemissiontoHSL (const CMLColorMachine* cm, CMLOutput HSL , CMLInput specrem, CMLSize count){
//  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(HSL, specrem, CML_HSL_NUMCHANNELS);
//  CMLCMRemissionSpectrumtoXYZ(cm, xyzbuf, in, count);
//  CMLXYZtoHSL(cm, out, xyzbuf, count);
//  CML_CONVERTER_SPECTRUM_RETURN;
//}
//
//CMLAPI void CMLSpectrumRemissiontoCMYK(const CMLColorMachine* cm, CMLOutput CMYK, CMLInput specrem, CMLSize count){
//  CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(CMYK, specrem, CML_CMYK_NUMCHANNELS);
//  CMLCMRemissionSpectrumtoXYZ(cm, xyzbuf, in, count);
//  CMLXYZtoCMYK(cm, out, xyzbuf, count);
//  CML_CONVERTER_SPECTRUM_RETURN;
//}




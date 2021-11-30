
#include "../CML.h"

#include "cml_.h"


// Enumeration for internal recomputation consistency. Will be used with the
// calls to lockRecomputation and releaseRecomputation.
typedef enum{
  CML_COLORMACHINE_RECOMPUTE_RGB                 = 0x01,
  CML_COLORMACHINE_RECOMPUTE_RGB_RESPONSES       = 0x02,
  CML_COLORMACHINE_RECOMPUTE_LAB                 = 0x04,
  CML_COLORMACHINE_RECOMPUTE_ADAMS_CHROMATICITY  = 0x08,
  CML_COLORMACHINE_RECOMPUTE_ILLUMINATION        = 0x10,
  CML_COLORMACHINE_RECOMPUTE_OBSERVER            = 0x20
} ColorMachineRecomputation;



struct CML_HIDDEN CMLColorMachine{

  size_t recomputationlockcount;
  CMLuint8 recomputationmask;

  struct inputoutput_struct{
    CMLIntegerMappingType         integermapping;
    CMLByte                       offset8Bit[CML_MAX_NUMBER_OF_CHANNELS];
    float                         range8Bit[CML_MAX_NUMBER_OF_CHANNELS];
    CMLWord                       offset16Bit[CML_MAX_NUMBER_OF_CHANNELS];
    float                         range16Bit[CML_MAX_NUMBER_OF_CHANNELS];
  } inputoutput;
  
//  struct observer_struct{
//    CMLObserverType               state;
//    CMLFunction*                  functions[3];
//    CMLBool                       radiometric;
//  } observer;
  
  CMLObserver observer;
//  CMLIllumination illumination;
  
//  struct illumination_struct{
//    CMLIlluminationType           state;
//    CMLFunction*                  spectrum;
//    CMLVec3                       inverseWhitepointXYZ;
//    CMLVec3                       whitePointXYZ;
//    CMLVec3                       whitePointYxy;
//    CMLVec3                       whitePointYupvp;
//    float                         temperature;
//  } illumination;
  
  struct rgbspace_struct{
    CMLRGBColorSpace              state;
    CMLVec3                       primariesYxy[3];
    CMLResponseCurve              responseR;
    CMLResponseCurve              responseG;
    CMLResponseCurve              responseB;
    CMLMat33                      matrix;
    CMLMat33                      matrixinv;
    CMLuint8                      lutsize;
  } rgbspace;
  
  struct cmykspace_struct{
    CMLCMYKTransformType          transform;
  } cmykspace;
  
  struct labspace_struct{
    CMLLabColorSpaceType          state;
    CMLResponseCurve              responseL;
    CMLResponseCurve              responseLStar;    // used for Luv
    CMLuint8                      lutsize;
    float                         adamschromaticityvalenceK;
    float                         adamschromaticityvalenceke;
//    CMLDeltaEComputationType      deltaecomputation;
  } labspace;
  
  struct grayspace_struct{
    CMLGrayComputationType        computation;
  } grayspace;

  void (*float1ToData8)          (const CMLColorMachine* cm, CMLByte* CML_RESTRICT out, const float* CML_RESTRICT in);
  void (*float3ToData8)          (const CMLColorMachine* cm, CMLByte* CML_RESTRICT out, const float* CML_RESTRICT in);
  void (*float4ToData8)          (const CMLColorMachine* cm, CMLByte* CML_RESTRICT out, const float* CML_RESTRICT in);
  void (*float1ToData16)         (const CMLColorMachine* cm, CMLWord* CML_RESTRICT out, const float* CML_RESTRICT in);
  void (*float3ToData16)         (const CMLColorMachine* cm, CMLWord* CML_RESTRICT out, const float* CML_RESTRICT in);
  void (*float4ToData16)         (const CMLColorMachine* cm, CMLWord* CML_RESTRICT out, const float* CML_RESTRICT in);
  void (*GraytoChanneledBuffer) (const CMLColorMachine* cm, float* CML_RESTRICT buffer , const float* CML_RESTRICT gray);
  void (*ChanneledBuffertoGray) (const CMLColorMachine* cm, float* CML_RESTRICT gray , const float* CML_RESTRICT buffer);
  void (*XYZtoLab)              (const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, size_t count);
  void (*XYZtoLab_SB)           (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign);
  void (*LabtoXYZ)              (const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, size_t count);
  void (*LabtoXYZ_SB)           (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign);
  void (*RGBtoCMYK)             (const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, size_t count);
  void (*RGBtoCMYK_SB)          (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign);
  void (*CMYKtoRGB)             (const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, size_t count);
  void (*CMYKtoRGB_SB)          (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign);
};


CML_HIDDEN void cml_GraytoChanneledBufferHSL(const CMLColorMachine* cm, float* CML_RESTRICT buffer , const float* CML_RESTRICT gray);
CML_HIDDEN void cml_GraytoChanneledBufferHSV(const CMLColorMachine* cm, float* CML_RESTRICT buffer , const float* CML_RESTRICT gray);
CML_HIDDEN void cml_GraytoChanneledBufferG(const CMLColorMachine* cm, float* CML_RESTRICT buffer , const float* CML_RESTRICT gray);
CML_HIDDEN void cml_GraytoChanneledBufferLSTAR(const CMLColorMachine* cm, float* CML_RESTRICT buffer , const float* CML_RESTRICT gray);
CML_HIDDEN void cml_GraytoChanneledBufferL(const CMLColorMachine* cm, float* CML_RESTRICT buffer , const float* CML_RESTRICT gray);
CML_HIDDEN void cml_GraytoChanneledBufferY(const CMLColorMachine* cm, float* CML_RESTRICT buffer , const float* CML_RESTRICT gray);
CML_HIDDEN void cml_GraytoChanneledBufferYPRIME(const CMLColorMachine* cm, float* CML_RESTRICT buffer , const float* CML_RESTRICT gray);
CML_HIDDEN void cml_ChanneledBuffertoGrayHSL(const CMLColorMachine* cm, float* CML_RESTRICT gray , const float* CML_RESTRICT buffer);
CML_HIDDEN void cml_ChanneledBuffertoGrayHSV(const CMLColorMachine* cm, float* CML_RESTRICT gray , const float* CML_RESTRICT buffer);
CML_HIDDEN void cml_ChanneledBuffertoGrayG(const CMLColorMachine* cm, float* CML_RESTRICT gray , const float* CML_RESTRICT buffer);
CML_HIDDEN void cml_ChanneledBuffertoGrayLSTAR(const CMLColorMachine* cm, float* CML_RESTRICT gray , const float* CML_RESTRICT buffer);
CML_HIDDEN void cml_ChanneledBuffertoGrayL(const CMLColorMachine* cm, float* CML_RESTRICT gray , const float* CML_RESTRICT buffer);
CML_HIDDEN void cml_ChanneledBuffertoGrayY(const CMLColorMachine* cm, float* CML_RESTRICT gray , const float* CML_RESTRICT buffer);
CML_HIDDEN void cml_ChanneledBuffertoGrayYPRIME(const CMLColorMachine* cm, float* CML_RESTRICT gray , const float* CML_RESTRICT buffer);
CML_HIDDEN void cml_XYZtoLabCIELAB (const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, size_t count);
CML_HIDDEN void cml_XYZtoLabCIELAB_SB (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign);
CML_HIDDEN void cml_XYZtoLabChromaticValence (const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, size_t count);
CML_HIDDEN void cml_XYZtoLabChromaticValence_SB (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign);
CML_HIDDEN void cml_LabtoXYZCIELAB (const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, size_t count);
CML_HIDDEN void cml_LabtoXYZCIELAB_SB (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign);
CML_HIDDEN void cml_LabtoXYZChromaticValence (const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, size_t count);
CML_HIDDEN void cml_LabtoXYZChromaticValence_SB (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign);
CML_HIDDEN void cml_RGBtoCMYKStandard (const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, size_t count);
CML_HIDDEN void cml_RGBtoCMYKStandard_SB (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign);
CML_HIDDEN void cml_RGBtoCMYKUCR (const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, size_t count);
CML_HIDDEN void cml_RGBtoCMYKUCR_SB (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign);
CML_HIDDEN void cml_CMYKtoRGBStandard (const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, size_t count);
CML_HIDDEN void cml_CMYKtoRGBStandard_SB (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign);
CML_HIDDEN void cml_CMYKtoRGBUCR (const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, size_t count);
CML_HIDDEN void cml_CMYKtoRGBUCR_SB (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign);
 
CML_HIDDEN void cml_recomputeObserver(CMLColorMachine* cm);
CML_HIDDEN void cml_recomputeIllumination(CMLColorMachine* cm);
CML_HIDDEN void cml_recomputeLabColorspace(CMLColorMachine* cm);
CML_HIDDEN void cml_recomputeAdamsChromaticityValenceSpace(CMLColorMachine* cm);
CML_HIDDEN void cml_recomputeRGBResponses(CMLColorMachine* cm);
CML_HIDDEN void cml_recomputeRGBColorspace(CMLColorMachine* cm);

CML_HIDEF void CMLCMXYZtoYxy   (const CMLColorMachine* cm, float* CML_RESTRICT yxy , const float* CML_RESTRICT xyz, size_t count)
  {cml_XYZtoYxy(yxy, xyz, cmlGetReferenceWhitepointYxy(&(cm->observer)), count);}
CML_HIDEF void CMLCMXYZtoYxy_SB   (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign)
  {cml_XYZtoYxy_SB(buf, cmlGetReferenceWhitepointYxy(&(cm->observer)), count, floatAlign);}
CML_HIDEF void CMLCMYxytoXYZ   (const CMLColorMachine* cm, float* CML_RESTRICT xyz , const float* CML_RESTRICT yxy, size_t count)
  {cml_YxytoXYZ(xyz, yxy, cmlGetReferenceWhitepointXYZ(&(cm->observer)), count);}
CML_HIDEF void CMLCMYxytoXYZ_SB(const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign)
  {cml_YxytoXYZ_SB(buf, cmlGetReferenceWhitepointXYZ(&(cm->observer)), count, floatAlign);}
CML_HIDEF void CMLCMYxytoYupvp (const CMLColorMachine* cm, float* CML_RESTRICT yupvp , const float* CML_RESTRICT yxy, size_t count)
  {cml_YxytoYupvp(yupvp, yxy, cmlGetReferenceWhitepointYupvp(&(cm->observer)), count);}
CML_HIDEF void CMLCMYxytoYupvp_SB (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign)
  {cml_YxytoYupvp_SB(buf, cmlGetReferenceWhitepointYupvp(&(cm->observer)), count, floatAlign);}
CML_HIDEF void CMLCMYupvptoYxy (const CMLColorMachine* cm, float* CML_RESTRICT yxy , const float* CML_RESTRICT yupvp, size_t count)
  {cml_YupvptoYxy(yxy, yupvp, cmlGetReferenceWhitepointYxy(&(cm->observer)), count);}
CML_HIDEF void CMLCMYupvptoYxy_SB (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign)
  {cml_YupvptoYxy_SB(buf, cmlGetReferenceWhitepointYxy(&(cm->observer)), count, floatAlign);}
CML_HIDEF void CMLCMYupvptoYuv (const CMLColorMachine* cm, float* CML_RESTRICT yuv , const float* CML_RESTRICT yupvp, size_t count)
  {cm = cm; cml_YupvptoYuv(yuv, yupvp, count);}
CML_HIDEF void CMLCMYupvptoYuv_SB (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign)
  {cm = cm; cml_YupvptoYuv_SB(buf, count, floatAlign);}
CML_HIDEF void CMLCMYuvtoYupvp (const CMLColorMachine* cm, float* CML_RESTRICT yupvp , const float* CML_RESTRICT yuv, size_t count)
  {cm = cm; cml_YuvtoYupvp(yupvp, yuv, count);}
CML_HIDEF void CMLCMYuvtoYupvp_SB (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign)
  {cm = cm; cml_YuvtoYupvp_SB(buf, count, floatAlign);}
CML_HIDEF void CMLCMYupvptoLuv (const CMLColorMachine* cm, float* CML_RESTRICT luv , const float* CML_RESTRICT yupvp, size_t count)
  {cml_YupvptoLuv(luv, yupvp, count, cmlGetReferenceWhitepointYupvp(&(cm->observer)), cm->labspace.responseLStar.forwardfunc);}
CML_HIDEF void CMLCMYupvptoLuv_SB (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign)
  {cml_YupvptoLuv_SB(buf, count, floatAlign, cmlGetReferenceWhitepointYupvp(&(cm->observer)), cm->labspace.responseLStar.forwardfunc);}
CML_HIDEF void CMLCMLuvtoYupvp (const CMLColorMachine* cm, float* CML_RESTRICT yupvp , const float* CML_RESTRICT luv, size_t count)
  {cml_LuvtoYupvp(yupvp, luv, count, cmlGetReferenceWhitepointYupvp(&(cm->observer)), cm->labspace.responseLStar.backwardfunc);}
CML_HIDEF void CMLCMLuvtoYupvp_SB (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign)
  {cml_LuvtoYupvp_SB(buf, count, floatAlign, cmlGetReferenceWhitepointYupvp(&(cm->observer)), cm->labspace.responseLStar.backwardfunc);}
CML_HIDEF void CMLCMLabtoLch   (const CMLColorMachine* cm, float* CML_RESTRICT lch , const float* CML_RESTRICT lab, size_t count)
  {cm = cm; cml_LabtoLch(lch, lab, count);}
CML_HIDEF void CMLCMLabtoLch_SB   (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign)
  {cm = cm; cml_LabtoLch_SB(buf, count, floatAlign);}
CML_HIDEF void CMLCMLchtoLab   (const CMLColorMachine* cm, float* CML_RESTRICT lab , const float* CML_RESTRICT lch, size_t count)
  {cm = cm; cml_LchtoLab(lab, lch, count);}
CML_HIDEF void CMLCMLchtoLab_SB   (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign)
  {cm = cm; cml_LchtoLab_SB(buf, count, floatAlign);}
CML_HIDEF void CMLCMXYZtoRGB   (const CMLColorMachine* cm, float* CML_RESTRICT rgb , const float* CML_RESTRICT xyz, size_t count)
  {cml_XYZtoRGB(rgb, xyz, count, cm->rgbspace.matrixinv, cm->rgbspace.responseR.forwardfunc, cm->rgbspace.responseG.forwardfunc, cm->rgbspace.responseB.forwardfunc);}
CML_HIDEF void CMLCMXYZtoRGB_SB   (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign)
  {cml_XYZtoRGB_SB(buf, count, floatAlign, cm->rgbspace.matrixinv, cm->rgbspace.responseR.forwardfunc, cm->rgbspace.responseG.forwardfunc, cm->rgbspace.responseB.forwardfunc);}
CML_HIDEF void CMLCMRGBtoXYZ   (const CMLColorMachine* cm, float* CML_RESTRICT xyz , const float* CML_RESTRICT rgb, size_t count)
  {cml_RGBtoXYZ(xyz, rgb, count, cm->rgbspace.matrix, cm->rgbspace.responseR.backwardfunc, cm->rgbspace.responseG.backwardfunc, cm->rgbspace.responseB.backwardfunc);}
CML_HIDEF void CMLCMRGBtoXYZ_SB   (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign)
  {cml_RGBtoXYZ_SB(buf, count, floatAlign, cm->rgbspace.matrix, cm->rgbspace.responseR.backwardfunc, cm->rgbspace.responseG.backwardfunc, cm->rgbspace.responseB.backwardfunc);}
CML_HIDEF void CMLCMRGBtoYCbCr (const CMLColorMachine* cm, float* CML_RESTRICT ycbcr , const float* CML_RESTRICT rgb, size_t count)
  {cml_RGBtoYCbCr(ycbcr, rgb, count, cm->rgbspace.primariesYxy[0], cm->rgbspace.primariesYxy[2], cmlGetReferenceInverseWhitepointXYZ(&(cm->observer)));}
CML_HIDEF void CMLCMRGBtoYCbCr_SB (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign)
  {cml_RGBtoYCbCr_SB(buf, count, floatAlign, cm->rgbspace.primariesYxy[0], cm->rgbspace.primariesYxy[2], cmlGetReferenceInverseWhitepointXYZ(&(cm->observer)));}
CML_HIDEF void CMLCMYCbCrtoRGB (const CMLColorMachine* cm, float* CML_RESTRICT rgb , const float* CML_RESTRICT ycbcr, size_t count)
  {cml_YCbCrtoRGB(rgb, ycbcr, count, cm->rgbspace.primariesYxy[0], cm->rgbspace.primariesYxy[2], cmlGetReferenceInverseWhitepointXYZ(&(cm->observer)));}
CML_HIDEF void CMLCMYCbCrtoRGB_SB (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign)
  {cml_YCbCrtoRGB_SB(buf, count, floatAlign, cm->rgbspace.primariesYxy[0], cm->rgbspace.primariesYxy[2], cmlGetReferenceInverseWhitepointXYZ(&(cm->observer)));}
CML_HIDEF void CMLCMRGBtoHSV (const CMLColorMachine* cm, float* CML_RESTRICT hsv , const float* CML_RESTRICT rgb, size_t count)
  {cm = cm; cml_RGBtoHSV(hsv, rgb, count);}
CML_HIDEF void CMLCMRGBtoHSV_SB (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign)
  {cm = cm; cml_RGBtoHSV_SB(buf, count, floatAlign);}
CML_HIDEF void CMLCMHSVtoRGB (const CMLColorMachine* cm, float* CML_RESTRICT rgb , const float* CML_RESTRICT hsv, size_t count)
  {cm = cm; cml_HSVtoRGB(rgb, hsv, count);}
CML_HIDEF void CMLCMHSVtoRGB_SB (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign)
  {cm = cm; cml_HSVtoRGB_SB(buf, count, floatAlign);}
CML_HIDEF void CMLCMHSVtoHSL (const CMLColorMachine* cm, float* CML_RESTRICT hsl , const float* CML_RESTRICT hsv, size_t count)
  {cm = cm; cml_HSVtoHSL(hsl, hsv, count);}
CML_HIDEF void CMLCMHSVtoHSL_SB (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign)
  {cm = cm; cml_HSVtoHSL_SB(buf, count, floatAlign);}
CML_HIDEF void CMLCMHSLtoHSV (const CMLColorMachine* cm, float* CML_RESTRICT hsv , const float* CML_RESTRICT hsl, size_t count)
  {cm = cm; cml_HSLtoHSV(hsv, hsl, count);}
CML_HIDEF void CMLCMHSLtoHSV_SB (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign)
  {cm = cm; cml_HSLtoHSV_SB(buf, count, floatAlign);}


CML_HIDEF void CMLCMIlluminationSpectrumtoXYZ(const CMLColorMachine* cm, float* CML_RESTRICT xyz , const CMLFunction* CML_RESTRICT specIll, size_t count, CMLuint32 floatAlign)
  {cml_IlluminationSpectrumtoXYZ(xyz, specIll, count, floatAlign, &(cm->observer));}
CML_HIDEF void CMLCMRemissionSpectrumtoXYZ(const CMLColorMachine* cm, float* CML_RESTRICT xyz , const CMLFunction* CML_RESTRICT specRem, size_t count, CMLuint32 floatAlign)
  {cml_RemissionSpectrumtoXYZ(xyz, specRem, count, floatAlign, cmlGetReferenceIlluminationSpectrum(&(cm->observer)), &(cm->observer));}



#include "CMLNormedConversions.h"



// This is free and unencumbered software released into the public domain.

// Anyone is free to copy, modify, publish, use, compile, sell, or
// distribute this software, either in source code form or as a compiled
// binary, for any purpose, commercial or non-commercial, and by any
// means.

// In jurisdictions that recognize copyright laws, the author or authors
// of this software dedicate any and all copyright interest in the
// software to the public domain. We make this dedication for the benefit
// of the public at large and to the detriment of our heirs and
// successors. We intend this dedication to be an overt act of
// relinquishment in perpetuity of all present and future rights to this
// software under copyright law.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
// OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.

// For more information, please refer to <http://unlicense.org/>


#include "../CML.h"

#include "CMLInternal.h"


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

  size_t recomputationLockCount;
  CMLuint8 recomputationMask;

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
//    CMLVec3                       inverseWhitePointXYZ;
//    CMLVec3                       whitePointXYZ;
//    CMLVec3                       whitePointYxy;
//    CMLVec3                       whitePointYupvp;
//    float                         temperature;
//  } illumination;
  
  struct rgbSpace_struct{
    CMLRGBColorSpace              state;
    CMLVec3                       primariesYxy[3];
    CMLResponseCurve              responseR;
    CMLResponseCurve              responseG;
    CMLResponseCurve              responseB;
    CMLMat33                      matrix;
    CMLMat33                      matrixinv;
    CMLuint8                      lutsize;
  } rgbSpace;
  
  struct cmykSpace_struct{
    CMLCMYKTransformType          transform;
  } cmykSpace;
  
  struct labSpace_struct{
    CMLLabColorSpaceType          state;
    CMLResponseCurve              responseL;
    CMLResponseCurve              responseLStar;    // used for Luv
    CMLuint8                      lutsize;
    float                         adamsChromaticityValenceK;
    float                         adamsChromaticityValenceke;
//    CMLDeltaEComputationType      deltaecomputation;
  } labSpace;
  
  struct graySpace_struct{
    CMLGrayComputationType        computation;
  } graySpace;

  void (*Float1ToData8)          (const CMLColorMachine* cm, CMLByte* CML_RESTRICT out, const float* CML_RESTRICT in);
  void (*Float3ToData8)          (const CMLColorMachine* cm, CMLByte* CML_RESTRICT out, const float* CML_RESTRICT in);
  void (*Float4ToData8)          (const CMLColorMachine* cm, CMLByte* CML_RESTRICT out, const float* CML_RESTRICT in);
  void (*Float1ToData16)         (const CMLColorMachine* cm, CMLWord* CML_RESTRICT out, const float* CML_RESTRICT in);
  void (*Float3ToData16)         (const CMLColorMachine* cm, CMLWord* CML_RESTRICT out, const float* CML_RESTRICT in);
  void (*Float4ToData16)         (const CMLColorMachine* cm, CMLWord* CML_RESTRICT out, const float* CML_RESTRICT in);
  void (*GrayToChanneledBuffer) (const CMLColorMachine* cm, float* CML_RESTRICT buffer, const float* CML_RESTRICT gray);
  void (*ChanneledBufferToGray) (const CMLColorMachine* cm, float* CML_RESTRICT gray, const float* CML_RESTRICT buffer);
  void (*XYZToLab)              (const CMLColorMachine* cm, float* CML_RESTRICT out, const float* CML_RESTRICT in, size_t count);
  void (*XYZToLab_SB)           (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign);
  void (*LabToXYZ)              (const CMLColorMachine* cm, float* CML_RESTRICT out, const float* CML_RESTRICT in, size_t count);
  void (*LabToXYZ_SB)           (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign);
  void (*RGBToCMYK)             (const CMLColorMachine* cm, float* CML_RESTRICT out, const float* CML_RESTRICT in, size_t count);
  void (*RGBToCMYK_SB)          (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign);
  void (*CMYKToRGB)             (const CMLColorMachine* cm, float* CML_RESTRICT out, const float* CML_RESTRICT in, size_t count);
  void (*CMYKToRGB_SB)          (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign);
};


CML_HIDDEN void cml_GrayToChanneledBufferHSL(const CMLColorMachine* cm, float* CML_RESTRICT buffer, const float* CML_RESTRICT gray);
CML_HIDDEN void cml_GrayToChanneledBufferHSV(const CMLColorMachine* cm, float* CML_RESTRICT buffer, const float* CML_RESTRICT gray);
CML_HIDDEN void cml_GrayToChanneledBufferG(const CMLColorMachine* cm, float* CML_RESTRICT buffer, const float* CML_RESTRICT gray);
CML_HIDDEN void cml_GrayToChanneledBufferLSTAR(const CMLColorMachine* cm, float* CML_RESTRICT buffer, const float* CML_RESTRICT gray);
CML_HIDDEN void cml_GrayToChanneledBufferL(const CMLColorMachine* cm, float* CML_RESTRICT buffer, const float* CML_RESTRICT gray);
CML_HIDDEN void cml_GrayToChanneledBufferY(const CMLColorMachine* cm, float* CML_RESTRICT buffer, const float* CML_RESTRICT gray);
CML_HIDDEN void cml_GrayToChanneledBufferYPRIME(const CMLColorMachine* cm, float* CML_RESTRICT buffer, const float* CML_RESTRICT gray);
CML_HIDDEN void cml_ChanneledBufferToGrayHSL(const CMLColorMachine* cm, float* CML_RESTRICT gray, const float* CML_RESTRICT buffer);
CML_HIDDEN void cml_ChanneledBufferToGrayHSV(const CMLColorMachine* cm, float* CML_RESTRICT gray, const float* CML_RESTRICT buffer);
CML_HIDDEN void cml_ChanneledBufferToGrayG(const CMLColorMachine* cm, float* CML_RESTRICT gray, const float* CML_RESTRICT buffer);
CML_HIDDEN void cml_ChanneledBufferToGrayLSTAR(const CMLColorMachine* cm, float* CML_RESTRICT gray, const float* CML_RESTRICT buffer);
CML_HIDDEN void cml_ChanneledBufferToGrayL(const CMLColorMachine* cm, float* CML_RESTRICT gray, const float* CML_RESTRICT buffer);
CML_HIDDEN void cml_ChanneledBufferToGrayY(const CMLColorMachine* cm, float* CML_RESTRICT gray, const float* CML_RESTRICT buffer);
CML_HIDDEN void cml_ChanneledBufferToGrayYPRIME(const CMLColorMachine* cm, float* CML_RESTRICT gray, const float* CML_RESTRICT buffer);
CML_HIDDEN void cml_XYZToLabCIELAB (const CMLColorMachine* cm, float* CML_RESTRICT out, const float* CML_RESTRICT in, size_t count);
CML_HIDDEN void cml_XYZToLabCIELAB_SB (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign);
CML_HIDDEN void cml_XYZToLabChromaticValence (const CMLColorMachine* cm, float* CML_RESTRICT out, const float* CML_RESTRICT in, size_t count);
CML_HIDDEN void cml_XYZToLabChromaticValence_SB (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign);
CML_HIDDEN void cml_LabToXYZCIELAB (const CMLColorMachine* cm, float* CML_RESTRICT out, const float* CML_RESTRICT in, size_t count);
CML_HIDDEN void cml_LabToXYZCIELAB_SB (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign);
CML_HIDDEN void cml_LabToXYZChromaticValence (const CMLColorMachine* cm, float* CML_RESTRICT out, const float* CML_RESTRICT in, size_t count);
CML_HIDDEN void cml_LabToXYZChromaticValence_SB (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign);
CML_HIDDEN void cml_RGBToCMYKStandard (const CMLColorMachine* cm, float* CML_RESTRICT out, const float* CML_RESTRICT in, size_t count);
CML_HIDDEN void cml_RGBToCMYKStandard_SB (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign);
CML_HIDDEN void cml_RGBToCMYKUCR (const CMLColorMachine* cm, float* CML_RESTRICT out, const float* CML_RESTRICT in, size_t count);
CML_HIDDEN void cml_RGBToCMYKUCR_SB (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign);
CML_HIDDEN void cml_CMYKToRGBStandard (const CMLColorMachine* cm, float* CML_RESTRICT out, const float* CML_RESTRICT in, size_t count);
CML_HIDDEN void cml_CMYKToRGBStandard_SB (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign);
CML_HIDDEN void cml_CMYKToRGBUCR (const CMLColorMachine* cm, float* CML_RESTRICT out, const float* CML_RESTRICT in, size_t count);
CML_HIDDEN void cml_CMYKToRGBUCR_SB (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign);
 
CML_HIDDEN void cml_recomputeObserver(CMLColorMachine* cm);
CML_HIDDEN void cml_recomputeIllumination(CMLColorMachine* cm);
CML_HIDDEN void cml_recomputeLabColorspace(CMLColorMachine* cm);
CML_HIDDEN void cml_recomputeAdamsChromaticityValenceSpace(CMLColorMachine* cm);
CML_HIDDEN void cml_recomputeRGBResponses(CMLColorMachine* cm);
CML_HIDDEN void cml_recomputeRGBColorspace(CMLColorMachine* cm);

CML_HIDEF void CMLCMXYZToYxy   (const CMLColorMachine* cm, float* CML_RESTRICT yxy, const float* CML_RESTRICT xyz, size_t count)
  {cml_XYZToYxy(yxy, xyz, cmlGetReferenceWhitePointYxy(&(cm->observer)), count);}
CML_HIDEF void CMLCMXYZToYxy_SB   (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign)
  {cml_XYZToYxy_SB(buf, cmlGetReferenceWhitePointYxy(&(cm->observer)), count, floatAlign);}
CML_HIDEF void CMLCMYxyToXYZ   (const CMLColorMachine* cm, float* CML_RESTRICT xyz, const float* CML_RESTRICT yxy, size_t count)
  {cml_YxyToXYZ(xyz, yxy, cmlGetReferenceWhitePointXYZ(&(cm->observer)), count);}
CML_HIDEF void CMLCMYxyToXYZ_SB(const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign)
  {cml_YxyToXYZ_SB(buf, cmlGetReferenceWhitePointXYZ(&(cm->observer)), count, floatAlign);}
CML_HIDEF void CMLCMYxyToYupvp (const CMLColorMachine* cm, float* CML_RESTRICT yupvp, const float* CML_RESTRICT yxy, size_t count)
  {cml_YxyToYupvp(yupvp, yxy, cmlGetReferenceWhitePointYupvp(&(cm->observer)), count);}
CML_HIDEF void CMLCMYxyToYupvp_SB (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign)
  {cml_YxyToYupvp_SB(buf, cmlGetReferenceWhitePointYupvp(&(cm->observer)), count, floatAlign);}
CML_HIDEF void CMLCMYupvpToYxy (const CMLColorMachine* cm, float* CML_RESTRICT yxy, const float* CML_RESTRICT yupvp, size_t count)
  {cml_YupvpToYxy(yxy, yupvp, cmlGetReferenceWhitePointYxy(&(cm->observer)), count);}
CML_HIDEF void CMLCMYupvpToYxy_SB (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign)
  {cml_YupvpToYxy_SB(buf, cmlGetReferenceWhitePointYxy(&(cm->observer)), count, floatAlign);}
CML_HIDEF void CMLCMYupvpToYuv (const CMLColorMachine* cm, float* CML_RESTRICT yuv, const float* CML_RESTRICT yupvp, size_t count)
  {cm = cm; cml_YupvpToYuv(yuv, yupvp, count);}
CML_HIDEF void CMLCMYupvpToYuv_SB (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign)
  {cm = cm; cml_YupvpToYuv_SB(buf, count, floatAlign);}
CML_HIDEF void CMLCMYuvToYupvp (const CMLColorMachine* cm, float* CML_RESTRICT yupvp, const float* CML_RESTRICT yuv, size_t count)
  {cm = cm; cml_YuvToYupvp(yupvp, yuv, count);}
CML_HIDEF void CMLCMYuvToYupvp_SB (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign)
  {cm = cm; cml_YuvToYupvp_SB(buf, count, floatAlign);}
CML_HIDEF void CMLCMYupvpToLuv (const CMLColorMachine* cm, float* CML_RESTRICT luv, const float* CML_RESTRICT yupvp, size_t count)
  {cml_YupvpToLuv(luv, yupvp, count, cmlGetReferenceWhitePointYupvp(&(cm->observer)), cm->labSpace.responseLStar.forwardfunc);}
CML_HIDEF void CMLCMYupvpToLuv_SB (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign)
  {cml_YupvpToLuv_SB(buf, count, floatAlign, cmlGetReferenceWhitePointYupvp(&(cm->observer)), cm->labSpace.responseLStar.forwardfunc);}
CML_HIDEF void CMLCMLuvToYupvp (const CMLColorMachine* cm, float* CML_RESTRICT yupvp, const float* CML_RESTRICT luv, size_t count)
  {cml_LuvToYupvp(yupvp, luv, count, cmlGetReferenceWhitePointYupvp(&(cm->observer)), cm->labSpace.responseLStar.backwardfunc);}
CML_HIDEF void CMLCMLuvToYupvp_SB (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign)
  {cml_LuvToYupvp_SB(buf, count, floatAlign, cmlGetReferenceWhitePointYupvp(&(cm->observer)), cm->labSpace.responseLStar.backwardfunc);}
CML_HIDEF void CMLCMLabToLch   (const CMLColorMachine* cm, float* CML_RESTRICT lch, const float* CML_RESTRICT lab, size_t count)
  {cm = cm; cml_LabToLch(lch, lab, count);}
CML_HIDEF void CMLCMLabToLch_SB   (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign)
  {cm = cm; cml_LabToLch_SB(buf, count, floatAlign);}
CML_HIDEF void CMLCMLchToLab   (const CMLColorMachine* cm, float* CML_RESTRICT lab, const float* CML_RESTRICT lch, size_t count)
  {cm = cm; cml_LchToLab(lab, lch, count);}
CML_HIDEF void CMLCMLchToLab_SB   (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign)
  {cm = cm; cml_LchToLab_SB(buf, count, floatAlign);}
CML_HIDEF void CMLCMXYZToRGB   (const CMLColorMachine* cm, float* CML_RESTRICT rgb, const float* CML_RESTRICT xyz, size_t count)
  {cml_XYZToRGB(rgb, xyz, count, cm->rgbSpace.matrixinv, cm->rgbSpace.responseR.forwardfunc, cm->rgbSpace.responseG.forwardfunc, cm->rgbSpace.responseB.forwardfunc);}
CML_HIDEF void CMLCMXYZToRGB_SB   (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign)
  {cml_XYZToRGB_SB(buf, count, floatAlign, cm->rgbSpace.matrixinv, cm->rgbSpace.responseR.forwardfunc, cm->rgbSpace.responseG.forwardfunc, cm->rgbSpace.responseB.forwardfunc);}
CML_HIDEF void CMLCMRGBToXYZ   (const CMLColorMachine* cm, float* CML_RESTRICT xyz, const float* CML_RESTRICT rgb, size_t count)
  {cml_RGBToXYZ(xyz, rgb, count, cm->rgbSpace.matrix, cm->rgbSpace.responseR.backwardfunc, cm->rgbSpace.responseG.backwardfunc, cm->rgbSpace.responseB.backwardfunc);}
CML_HIDEF void CMLCMRGBToXYZ_SB   (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign)
  {cml_RGBToXYZ_SB(buf, count, floatAlign, cm->rgbSpace.matrix, cm->rgbSpace.responseR.backwardfunc, cm->rgbSpace.responseG.backwardfunc, cm->rgbSpace.responseB.backwardfunc);}
CML_HIDEF void CMLCMRGBToYCbCr (const CMLColorMachine* cm, float* CML_RESTRICT ycbcr, const float* CML_RESTRICT rgb, size_t count)
  {cml_RGBToYCbCr(ycbcr, rgb, count, cm->rgbSpace.primariesYxy[0], cm->rgbSpace.primariesYxy[2], cmlGetReferenceInverseWhitePointXYZ(&(cm->observer)));}
CML_HIDEF void CMLCMRGBToYCbCr_SB (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign)
  {cml_RGBToYCbCr_SB(buf, count, floatAlign, cm->rgbSpace.primariesYxy[0], cm->rgbSpace.primariesYxy[2], cmlGetReferenceInverseWhitePointXYZ(&(cm->observer)));}
CML_HIDEF void CMLCMYCbCrToRGB (const CMLColorMachine* cm, float* CML_RESTRICT rgb, const float* CML_RESTRICT ycbcr, size_t count)
  {cml_YCbCrToRGB(rgb, ycbcr, count, cm->rgbSpace.primariesYxy[0], cm->rgbSpace.primariesYxy[2], cmlGetReferenceInverseWhitePointXYZ(&(cm->observer)));}
CML_HIDEF void CMLCMYCbCrToRGB_SB (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign)
  {cml_YCbCrToRGB_SB(buf, count, floatAlign, cm->rgbSpace.primariesYxy[0], cm->rgbSpace.primariesYxy[2], cmlGetReferenceInverseWhitePointXYZ(&(cm->observer)));}
CML_HIDEF void CMLCMRGBToHSV (const CMLColorMachine* cm, float* CML_RESTRICT hsv, const float* CML_RESTRICT rgb, size_t count)
  {cm = cm; cml_RGBToHSV(hsv, rgb, count);}
CML_HIDEF void CMLCMRGBToHSV_SB (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign)
  {cm = cm; cml_RGBToHSV_SB(buf, count, floatAlign);}
CML_HIDEF void CMLCMHSVToRGB (const CMLColorMachine* cm, float* CML_RESTRICT rgb, const float* CML_RESTRICT hsv, size_t count)
  {cm = cm; cml_HSVToRGB(rgb, hsv, count);}
CML_HIDEF void CMLCMHSVToRGB_SB (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign)
  {cm = cm; cml_HSVToRGB_SB(buf, count, floatAlign);}
CML_HIDEF void CMLCMHSVToHSL (const CMLColorMachine* cm, float* CML_RESTRICT hsl, const float* CML_RESTRICT hsv, size_t count)
  {cm = cm; cml_HSVToHSL(hsl, hsv, count);}
CML_HIDEF void CMLCMHSVToHSL_SB (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign)
  {cm = cm; cml_HSVToHSL_SB(buf, count, floatAlign);}
CML_HIDEF void CMLCMHSLToHSV (const CMLColorMachine* cm, float* CML_RESTRICT hsv, const float* CML_RESTRICT hsl, size_t count)
  {cm = cm; cml_HSLToHSV(hsv, hsl, count);}
CML_HIDEF void CMLCMHSLToHSV_SB (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign)
  {cm = cm; cml_HSLToHSV_SB(buf, count, floatAlign);}


CML_HIDEF void CMLCMIlluminationSpectrumToXYZ(const CMLColorMachine* cm, float* CML_RESTRICT xyz, const CMLFunction* CML_RESTRICT specIll, size_t count, CMLuint32 floatAlign)
  {cml_IlluminationSpectrumToXYZ(xyz, specIll, count, floatAlign, &(cm->observer));}
CML_HIDEF void CMLCMRemissionSpectrumToXYZ(const CMLColorMachine* cm, float* CML_RESTRICT xyz, const CMLFunction* CML_RESTRICT specRem, size_t count, CMLuint32 floatAlign)
  {cml_RemissionSpectrumToXYZ(xyz, specRem, count, floatAlign, cmlGetReferenceIlluminationSpectrum(&(cm->observer)), &(cm->observer));}



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

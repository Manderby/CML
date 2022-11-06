
#include "../CML.h"

#include "CMLInternal.h"


// Enumeration for internal recomputation consistency. Will be used with the
// calls to lockRecomputation and releaseRecomputation.
typedef enum{
  CML_COLORMACHINE_RECOMPUTE_RGB                    = 0x01,
  CML_COLORMACHINE_RECOMPUTE_RGB_RESPONSES          = 0x02,
  CML_COLORMACHINE_RECOMPUTE_LAB                    = 0x04,
  CML_COLORMACHINE_RECOMPUTE_ADAMS_CHROMATICITY     = 0x08,
  CML_COLORMACHINE_RECOMPUTE_REFERENCE_ILLUMINATION = 0x10,
  CML_COLORMACHINE_RECOMPUTE_OBSERVER               = 0x20
} ColorMachineRecomputation;



struct CMLColorMachine{

  size_t recomputationLockCount;
  uint16 recomputationMask;

  CMLIntegration integration;

  struct serialization_struct{
    CMLIntegerMappingType         integerMapping;
    uint8                         offset8Bit [CML_MAX_NUMBER_OF_CHANNELS];
    float                         range8Bit  [CML_MAX_NUMBER_OF_CHANNELS];
    uint16                        offset16Bit[CML_MAX_NUMBER_OF_CHANNELS];
    float                         range16Bit [CML_MAX_NUMBER_OF_CHANNELS];
  } serialization;
  
  CMLObserver                     observer;
  CMLIllumination                 referenceIllumination;

  float                           colorimetricBase;
  float                           radiometricScale;
  CMLVec3                         whitePointXYZ;
  CMLVec3                         whitePointXYZInverse;
  CMLVec3                         whitePointYxy;
  CMLVec3                         whitePointYupvp;
  
  struct rgbSpace_struct{
    CMLRGBColorSpaceType          type;
    CMLVec3                       primariesYxy[3];
    CMLResponseCurve              responseR;
    CMLResponseCurve              responseG;
    CMLResponseCurve              responseB;
    GammaLinearInputParameters    customParametersR;
    GammaLinearInputParameters    customParametersG;
    GammaLinearInputParameters    customParametersB;
    CMLMat33                      matrix;
    CMLMat33                      matrixInv;
    uint8                         lutSize;
  } rgbSpace;
  
  struct cmykSpace_struct{
    cml_CMYKTransformType          transform;
  } cmykSpace;
  
  struct labSpace_struct{
    CMLLabColorSpaceType          state;
    CMLResponseCurve              responseL;
    CMLResponseCurve              responseLStar;    // used for Luv
    uint8                         lutSize;
    float                         adamsChromaticityValenceK;
    float                         adamsChromaticityValenceke;
    CMLDeltaEComputationType      deltaEComputation;
  } labSpace;
  
  struct graySpace_struct{
    CMLGrayComputationType        computation;
  } graySpace;

  void (*Float1ToData8)         (const CMLColorMachine* cm, uint8* CML_RESTRICT out, const float* CML_RESTRICT in);
  void (*Float3ToData8)         (const CMLColorMachine* cm, uint8* CML_RESTRICT out, const float* CML_RESTRICT in);
  void (*Float4ToData8)         (const CMLColorMachine* cm, uint8* CML_RESTRICT out, const float* CML_RESTRICT in);
  void (*Float1ToData16)        (const CMLColorMachine* cm, uint16* CML_RESTRICT out, const float* CML_RESTRICT in);
  void (*Float3ToData16)        (const CMLColorMachine* cm, uint16* CML_RESTRICT out, const float* CML_RESTRICT in);
  void (*Float4ToData16)        (const CMLColorMachine* cm, uint16* CML_RESTRICT out, const float* CML_RESTRICT in);
  void (*GrayToChanneledBuffer) (const CMLColorMachine* cm, float* CML_RESTRICT buffer, const float* CML_RESTRICT gray);
  void (*ChanneledBufferToGray) (const CMLColorMachine* cm, float* CML_RESTRICT gray, const float* CML_RESTRICT buffer);
  void (*XYZToLab)              (const CMLColorMachine* cm, float* CML_RESTRICT out, const float* CML_RESTRICT in, size_t count);
  void (*XYZToLab_SB)           (const CMLColorMachine* cm, float* buf, size_t count, size_t floatAlign);
  void (*LabToXYZ)              (const CMLColorMachine* cm, float* CML_RESTRICT out, const float* CML_RESTRICT in, size_t count);
  void (*LabToXYZ_SB)           (const CMLColorMachine* cm, float* buf, size_t count, size_t floatAlign);
  void (*RGBToCMYK)             (const CMLColorMachine* cm, float* CML_RESTRICT out, const float* CML_RESTRICT in, size_t count);
  void (*RGBToCMYK_SB)          (const CMLColorMachine* cm, float* buf, size_t count, size_t floatAlign);
  void (*CMYKToRGB)             (const CMLColorMachine* cm, float* CML_RESTRICT out, const float* CML_RESTRICT in, size_t count);
  void (*CMYKToRGB_SB)          (const CMLColorMachine* cm, float* buf, size_t count, size_t floatAlign);
};


CML_HAPI void cml_GrayToChanneledBufferHSL(const CMLColorMachine* cm, float* CML_RESTRICT buffer, const float* CML_RESTRICT gray);
CML_HAPI void cml_GrayToChanneledBufferHSV(const CMLColorMachine* cm, float* CML_RESTRICT buffer, const float* CML_RESTRICT gray);
CML_HAPI void cml_GrayToChanneledBufferG(const CMLColorMachine* cm, float* CML_RESTRICT buffer, const float* CML_RESTRICT gray);
CML_HAPI void cml_GrayToChanneledBufferLStar(const CMLColorMachine* cm, float* CML_RESTRICT buffer, const float* CML_RESTRICT gray);
CML_HAPI void cml_GrayToChanneledBufferL(const CMLColorMachine* cm, float* CML_RESTRICT buffer, const float* CML_RESTRICT gray);
CML_HAPI void cml_GrayToChanneledBufferY(const CMLColorMachine* cm, float* CML_RESTRICT buffer, const float* CML_RESTRICT gray);
CML_HAPI void cml_GrayToChanneledBufferYPrime(const CMLColorMachine* cm, float* CML_RESTRICT buffer, const float* CML_RESTRICT gray);
CML_HAPI void cml_ChanneledBufferToGrayHSL(const CMLColorMachine* cm, float* CML_RESTRICT gray, const float* CML_RESTRICT buffer);
CML_HAPI void cml_ChanneledBufferToGrayHSV(const CMLColorMachine* cm, float* CML_RESTRICT gray, const float* CML_RESTRICT buffer);
CML_HAPI void cml_ChanneledBufferToGrayG(const CMLColorMachine* cm, float* CML_RESTRICT gray, const float* CML_RESTRICT buffer);
CML_HAPI void cml_ChanneledBufferToGrayLStar(const CMLColorMachine* cm, float* CML_RESTRICT gray, const float* CML_RESTRICT buffer);
CML_HAPI void cml_ChanneledBufferToGrayL(const CMLColorMachine* cm, float* CML_RESTRICT gray, const float* CML_RESTRICT buffer);
CML_HAPI void cml_ChanneledBufferToGrayY(const CMLColorMachine* cm, float* CML_RESTRICT gray, const float* CML_RESTRICT buffer);
CML_HAPI void cml_ChanneledBufferToGrayYPrime(const CMLColorMachine* cm, float* CML_RESTRICT gray, const float* CML_RESTRICT buffer);
CML_HAPI void cml_XYZToLabCIELAB(const CMLColorMachine* cm, float* CML_RESTRICT out, const float* CML_RESTRICT in, size_t count);
CML_HAPI void cml_XYZToLabCIELAB_SB(const CMLColorMachine* cm, float* buf, size_t count, size_t floatAlign);
CML_HAPI void cml_XYZToLabChromaticValence(const CMLColorMachine* cm, float* CML_RESTRICT out, const float* CML_RESTRICT in, size_t count);
CML_HAPI void cml_XYZToLabChromaticValence_SB(const CMLColorMachine* cm, float* buf, size_t count, size_t floatAlign);
CML_HAPI void cml_LabToXYZCIELAB(const CMLColorMachine* cm, float* CML_RESTRICT out, const float* CML_RESTRICT in, size_t count);
CML_HAPI void cml_LabToXYZCIELAB_SB(const CMLColorMachine* cm, float* buf, size_t count, size_t floatAlign);
CML_HAPI void cml_LabToXYZChromaticValence(const CMLColorMachine* cm, float* CML_RESTRICT out, const float* CML_RESTRICT in, size_t count);
CML_HAPI void cml_LabToXYZChromaticValence_SB(const CMLColorMachine* cm, float* buf, size_t count, size_t floatAlign);
CML_HAPI void cml_RGBToCMYKStandard(const CMLColorMachine* cm, float* CML_RESTRICT out, const float* CML_RESTRICT in, size_t count);
CML_HAPI void cml_RGBToCMYKStandard_SB(const CMLColorMachine* cm, float* buf, size_t count, size_t floatAlign);
CML_HAPI void cml_RGBToCMYKUCR(const CMLColorMachine* cm, float* CML_RESTRICT out, const float* CML_RESTRICT in, size_t count);
CML_HAPI void cml_RGBToCMYKUCR_SB(const CMLColorMachine* cm, float* buf, size_t count, size_t floatAlign);
CML_HAPI void cml_CMYKToRGBStandard(const CMLColorMachine* cm, float* CML_RESTRICT out, const float* CML_RESTRICT in, size_t count);
CML_HAPI void cml_CMYKToRGBStandard_SB(const CMLColorMachine* cm, float* buf, size_t count, size_t floatAlign);
CML_HAPI void cml_CMYKToRGBUCR(const CMLColorMachine* cm, float* CML_RESTRICT out, const float* CML_RESTRICT in, size_t count);
CML_HAPI void cml_CMYKToRGBUCR_SB(const CMLColorMachine* cm, float* buf, size_t count, size_t floatAlign);
 
CML_HAPI void cml_recomputeObserver(CMLColorMachine* cm);
CML_HAPI void cml_recomputeReferenceIllumination(CMLColorMachine* cm);
CML_HAPI void cml_recomputeLabColorSpace(CMLColorMachine* cm);
CML_HAPI void cml_recomputeAdamsChromaticityValenceSpace(CMLColorMachine* cm);
CML_HAPI void cml_recomputeRGBResponses(CMLColorMachine* cm);
CML_HAPI void cml_recomputeRGBColorSpace(CMLColorMachine* cm);

CML_HIDEF void cml_CMXYZToYxy(const CMLColorMachine* cm, float* CML_RESTRICT yxy, const float* CML_RESTRICT xyz, size_t count){
  cml_XYZToYxy(yxy, xyz, cmlGetReferenceWhitePointYxy(cm), count);
}
CML_HIDEF void cml_CMXYZToYxy_SB(const CMLColorMachine* cm, float* buf, size_t count, size_t floatAlign){
  cml_XYZToYxy_SB(buf, cmlGetReferenceWhitePointYxy(cm), count, floatAlign);
}
CML_HIDEF void cml_CMYxyToXYZ(const CMLColorMachine* cm, float* CML_RESTRICT xyz, const float* CML_RESTRICT yxy, size_t count){
  cml_YxyToXYZ(xyz, yxy, cmlGetReferenceWhitePointXYZ(cm), count);
}
CML_HIDEF void cml_CMYxyToXYZ_SB(const CMLColorMachine* cm, float* buf, size_t count, size_t floatAlign){
  cml_YxyToXYZ_SB(buf, cmlGetReferenceWhitePointXYZ(cm), count, floatAlign);
}
CML_HIDEF void cml_CMYxyToYupvp(const CMLColorMachine* cm, float* CML_RESTRICT yupvp, const float* CML_RESTRICT yxy, size_t count){
  cml_YxyToYupvp(yupvp, yxy, cmlGetReferenceWhitePointYupvp(cm), count);
}
CML_HIDEF void cml_CMYxyToYupvp_SB(const CMLColorMachine* cm, float* buf, size_t count, size_t floatAlign){
  cml_YxyToYupvp_SB(buf, cmlGetReferenceWhitePointYupvp(cm), count, floatAlign);
}
CML_HIDEF void cml_CMYupvpToYxy(const CMLColorMachine* cm, float* CML_RESTRICT yxy, const float* CML_RESTRICT yupvp, size_t count){
  cml_YupvpToYxy(yxy, yupvp, cmlGetReferenceWhitePointYxy(cm), count);
}
CML_HIDEF void cml_CMYupvpToYxy_SB(const CMLColorMachine* cm, float* buf, size_t count, size_t floatAlign){
  cml_YupvpToYxy_SB(buf, cmlGetReferenceWhitePointYxy(cm), count, floatAlign);
}
CML_HIDEF void cml_CMYupvpToYuv(const CMLColorMachine* cm, float* CML_RESTRICT yuv, const float* CML_RESTRICT yupvp, size_t count){
  cm = cm; cml_YupvpToYuv(yuv, yupvp, count);
}
CML_HIDEF void cml_CMYupvpToYuv_SB(const CMLColorMachine* cm, float* buf, size_t count, size_t floatAlign){
  cm = cm; cml_YupvpToYuv_SB(buf, count, floatAlign);
}
CML_HIDEF void cml_CMYuvToYupvp(const CMLColorMachine* cm, float* CML_RESTRICT yupvp, const float* CML_RESTRICT yuv, size_t count){
  cm = cm; cml_YuvToYupvp(yupvp, yuv, count);
}
CML_HIDEF void cml_CMYuvToYupvp_SB(const CMLColorMachine* cm, float* buf, size_t count, size_t floatAlign){
  cm = cm; cml_YuvToYupvp_SB(buf, count, floatAlign);
}
CML_HIDEF void cml_CMYupvpToLuv(const CMLColorMachine* cm, float* CML_RESTRICT luv, const float* CML_RESTRICT yupvp, size_t count){
  cml_YupvpToLuv(luv, yupvp, count, cmlGetReferenceWhitePointYupvp(cm), cm->labSpace.responseLStar.forwardFunc);
}
CML_HIDEF void cml_CMYupvpToLuv_SB(const CMLColorMachine* cm, float* buf, size_t count, size_t floatAlign){
  cml_YupvpToLuv_SB(buf, count, floatAlign, cmlGetReferenceWhitePointYupvp(cm), cm->labSpace.responseLStar.forwardFunc);
}
CML_HIDEF void cml_CMYuvToYcd(const CMLColorMachine* cm, float* CML_RESTRICT ycd, const float* CML_RESTRICT yuv, size_t count){
  cml_YuvToYcd(ycd, yuv, count);
}
CML_HIDEF void cml_CMYuvToYcd_SB(const CMLColorMachine* cm, float* buf, size_t count, size_t floatAlign){
  cm = cm; cml_YuvToYcd_SB(buf, count, floatAlign);
}
CML_HIDEF void cml_CMYcdToYuv(const CMLColorMachine* cm, float* CML_RESTRICT yuv, const float* CML_RESTRICT ycd, size_t count){
  cml_YcdToYuv(yuv, ycd, count);
}
CML_HIDEF void cml_CMYcdToYuv_SB(const CMLColorMachine* cm, float* buf, size_t count, size_t floatAlign){
  cm = cm; cml_YcdToYuv_SB(buf, count, floatAlign);
}
CML_HIDEF void cml_CMLuvToYupvp(const CMLColorMachine* cm, float* CML_RESTRICT yupvp, const float* CML_RESTRICT luv, size_t count){
  cml_LuvToYupvp(yupvp, luv, count, cmlGetReferenceWhitePointYupvp(cm), cm->labSpace.responseLStar.backwardFunc);
}
CML_HIDEF void cml_CMLuvToYupvp_SB(const CMLColorMachine* cm, float* buf, size_t count, size_t floatAlign){
  cml_LuvToYupvp_SB(buf, count, floatAlign, cmlGetReferenceWhitePointYupvp(cm), cm->labSpace.responseLStar.backwardFunc);
}
CML_HIDEF void cml_CMLabToLch(const CMLColorMachine* cm, float* CML_RESTRICT lch, const float* CML_RESTRICT lab, size_t count){
  cm = cm; cml_LabToLch(lch, lab, count);
}
CML_HIDEF void cml_CMLabToLch_SB(const CMLColorMachine* cm, float* buf, size_t count, size_t floatAlign){
  cm = cm; cml_LabToLch_SB(buf, count, floatAlign);
}
CML_HIDEF void cml_CMLchToLab(const CMLColorMachine* cm, float* CML_RESTRICT lab, const float* CML_RESTRICT lch, size_t count){
  cm = cm; cml_LchToLab(lab, lch, count);
}
CML_HIDEF void cml_CMLchToLab_SB(const CMLColorMachine* cm, float* buf, size_t count, size_t floatAlign){
  cm = cm; cml_LchToLab_SB(buf, count, floatAlign);
}
CML_HIDEF void cml_CMXYZToRGB(const CMLColorMachine* cm, float* CML_RESTRICT rgb, const float* CML_RESTRICT xyz, size_t count){
  cml_XYZToRGB(rgb, xyz, count, cm->rgbSpace.matrixInv, cm->rgbSpace.responseR.forwardFunc, cm->rgbSpace.responseG.forwardFunc, cm->rgbSpace.responseB.forwardFunc);
}
CML_HIDEF void cml_CMXYZToRGB_SB(const CMLColorMachine* cm, float* buf, size_t count, size_t floatAlign){
  cml_XYZToRGB_SB(buf, count, floatAlign, cm->rgbSpace.matrixInv, cm->rgbSpace.responseR.forwardFunc, cm->rgbSpace.responseG.forwardFunc, cm->rgbSpace.responseB.forwardFunc);
}
CML_HIDEF void cml_CMRGBToXYZ(const CMLColorMachine* cm, float* CML_RESTRICT xyz, const float* CML_RESTRICT rgb, size_t count){
  cml_RGBToXYZ(xyz, rgb, count, cm->rgbSpace.matrix, cm->rgbSpace.responseR.backwardFunc, cm->rgbSpace.responseG.backwardFunc, cm->rgbSpace.responseB.backwardFunc);
}
CML_HIDEF void cml_CMRGBToXYZ_SB(const CMLColorMachine* cm, float* buf, size_t count, size_t floatAlign){
  cml_RGBToXYZ_SB(buf, count, floatAlign, cm->rgbSpace.matrix, cm->rgbSpace.responseR.backwardFunc, cm->rgbSpace.responseG.backwardFunc, cm->rgbSpace.responseB.backwardFunc);
}
CML_HIDEF void cml_CMRGBToYCbCr(const CMLColorMachine* cm, float* CML_RESTRICT ycbcr, const float* CML_RESTRICT rgb, size_t count){
  cml_RGBToYCbCr(ycbcr, rgb, count, cm->rgbSpace.primariesYxy[0], cm->rgbSpace.primariesYxy[2], cmlGetReferenceWhitePointXYZInverse(cm));
}
CML_HIDEF void cml_CMRGBToYCbCr_SB(const CMLColorMachine* cm, float* buf, size_t count, size_t floatAlign){
  cml_RGBToYCbCr_SB(buf, count, floatAlign, cm->rgbSpace.primariesYxy[0], cm->rgbSpace.primariesYxy[2], cmlGetReferenceWhitePointXYZInverse(cm));
}
CML_HIDEF void cml_CMYCbCrToRGB(const CMLColorMachine* cm, float* CML_RESTRICT rgb, const float* CML_RESTRICT ycbcr, size_t count){
  cml_YCbCrToRGB(rgb, ycbcr, count, cm->rgbSpace.primariesYxy[0], cm->rgbSpace.primariesYxy[2], cmlGetReferenceWhitePointXYZInverse(cm));
}
CML_HIDEF void cml_CMYCbCrToRGB_SB(const CMLColorMachine* cm, float* buf, size_t count, size_t floatAlign){
  cml_YCbCrToRGB_SB(buf, count, floatAlign, cm->rgbSpace.primariesYxy[0], cm->rgbSpace.primariesYxy[2], cmlGetReferenceWhitePointXYZInverse(cm));
}
CML_HIDEF void cml_CMRGBToHSV(const CMLColorMachine* cm, float* CML_RESTRICT hsv, const float* CML_RESTRICT rgb, size_t count){
  cm = cm; cml_RGBToHSV(hsv, rgb, count);
}
CML_HIDEF void cml_CMRGBToHSV_SB(const CMLColorMachine* cm, float* buf, size_t count, size_t floatAlign){
  cm = cm; cml_RGBToHSV_SB(buf, count, floatAlign);
}
CML_HIDEF void cml_CMHSVToRGB(const CMLColorMachine* cm, float* CML_RESTRICT rgb, const float* CML_RESTRICT hsv, size_t count){
  cm = cm; cml_HSVToRGB(rgb, hsv, count);
}
CML_HIDEF void cml_CMHSVToRGB_SB(const CMLColorMachine* cm, float* buf, size_t count, size_t floatAlign){
  cm = cm; cml_HSVToRGB_SB(buf, count, floatAlign);
}
CML_HIDEF void cml_CMHSVToHSL(const CMLColorMachine* cm, float* CML_RESTRICT hsl, const float* CML_RESTRICT hsv, size_t count){
  cm = cm; cml_HSVToHSL(hsl, hsv, count);
}
CML_HIDEF void cml_CMHSVToHSL_SB(const CMLColorMachine* cm, float* buf, size_t count, size_t floatAlign){
  cm = cm; cml_HSVToHSL_SB(buf, count, floatAlign);
}
CML_HIDEF void cml_CMHSLToHSV(const CMLColorMachine* cm, float* CML_RESTRICT hsv, const float* CML_RESTRICT hsl, size_t count){
  cm = cm; cml_HSLToHSV(hsv, hsl, count);
}
CML_HIDEF void cml_CMHSLToHSV_SB(const CMLColorMachine* cm, float* buf, size_t count, size_t floatAlign){
  cm = cm; cml_HSLToHSV_SB(buf, count, floatAlign);
}


CML_HIDEF void cml_CMIlluminationSpectrumToXYZ(const CMLColorMachine* cm, float* CML_RESTRICT xyz, const CMLFunction* CML_RESTRICT specIll, size_t count, size_t floatAlign){
  cml_IlluminationSpectrumToXYZ(xyz, specIll, count, floatAlign, &(cm->observer), cm->radiometricScale, &(cm->integration));
}

CML_HIDEF void cml_CMRemissionSpectrumToXYZ(const CMLColorMachine* cm, float* CML_RESTRICT xyz, const CMLFunction* CML_RESTRICT specRem, size_t count, size_t floatAlign){
  const CMLFunction* spec = cmlGetReferenceIlluminationSpectrum(cm);
  cml_RemissionSpectrumToXYZ(xyz, specRem, count, floatAlign, spec, &(cm->observer), cm->radiometricScale, &(cm->integration));
}



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

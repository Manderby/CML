
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

  CMLSize recomputationlockcount;
  CMLuint8 recomputationmask;

  struct inputoutput_struct{
    CMLIntegerMappingType         integermapping;
    CMLByte                       offset8bit[CML_MAX_NUMBER_OF_CHANNELS];
    float                         range8bit[CML_MAX_NUMBER_OF_CHANNELS];
    CMLWord                       offset16bit[CML_MAX_NUMBER_OF_CHANNELS];
    float                         range16bit[CML_MAX_NUMBER_OF_CHANNELS];
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
//    CMLVec3                       whitepointXYZ;
//    CMLVec3                       whitepointYxy;
//    CMLVec3                       whitepointYupvp;
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

  void (*float1to8bit)          (const CMLColorMachine* cm, CMLByte* CML_RESTRICT out, const float* CML_RESTRICT in);
  void (*float3to8bit)          (const CMLColorMachine* cm, CMLByte* CML_RESTRICT out, const float* CML_RESTRICT in);
  void (*float4to8bit)          (const CMLColorMachine* cm, CMLByte* CML_RESTRICT out, const float* CML_RESTRICT in);
  void (*float1to16bit)         (const CMLColorMachine* cm, CMLWord* CML_RESTRICT out, const float* CML_RESTRICT in);
  void (*float3to16bit)         (const CMLColorMachine* cm, CMLWord* CML_RESTRICT out, const float* CML_RESTRICT in);
  void (*float4to16bit)         (const CMLColorMachine* cm, CMLWord* CML_RESTRICT out, const float* CML_RESTRICT in);
  void (*GraytoChanneledBuffer) (const CMLColorMachine* cm, float* CML_RESTRICT buffer , const float* CML_RESTRICT gray);
  void (*ChanneledBuffertoGray) (const CMLColorMachine* cm, float* CML_RESTRICT gray , const float* CML_RESTRICT buffer);
  void (*XYZtoLab)              (const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count);
  void (*XYZtoLab_SB)           (const CMLColorMachine* cm, float* buf, CMLuint32 count, CMLuint32 floatalign);
  void (*LabtoXYZ)              (const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count);
  void (*LabtoXYZ_SB)           (const CMLColorMachine* cm, float* buf, CMLuint32 count, CMLuint32 floatalign);
  void (*RGBtoCMYK)             (const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count);
  void (*RGBtoCMYK_SB)          (const CMLColorMachine* cm, float* buf, CMLuint32 count, CMLuint32 floatalign);
  void (*CMYKtoRGB)             (const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count);
  void (*CMYKtoRGB_SB)          (const CMLColorMachine* cm, float* buf, CMLuint32 count, CMLuint32 floatalign);
};


CML_HIDDEN void CMLInternalfloat1to8bitFloor(const CMLColorMachine* cm, CMLByte* CML_RESTRICT out, const float* CML_RESTRICT in);
CML_HIDDEN void CMLInternalfloat3to8bitFloor(const CMLColorMachine* cm, CMLByte* CML_RESTRICT out, const float* CML_RESTRICT in);
CML_HIDDEN void CMLInternalfloat4to8bitFloor(const CMLColorMachine* cm, CMLByte* CML_RESTRICT out, const float* CML_RESTRICT in);
CML_HIDDEN void CMLInternalfloat1to8bitBox(const CMLColorMachine* cm, CMLByte* CML_RESTRICT out, const float* CML_RESTRICT in);
CML_HIDDEN void CMLInternalfloat3to8bitBox(const CMLColorMachine* cm, CMLByte* CML_RESTRICT out, const float* CML_RESTRICT in);
CML_HIDDEN void CMLInternalfloat4to8bitBox(const CMLColorMachine* cm, CMLByte* CML_RESTRICT out, const float* CML_RESTRICT in);
CML_HIDDEN void CMLInternalfloat1to8bitInterval(const CMLColorMachine* cm, CMLByte* CML_RESTRICT out, const float* CML_RESTRICT in);
CML_HIDDEN void CMLInternalfloat3to8bitInterval(const CMLColorMachine* cm, CMLByte* CML_RESTRICT out, const float* CML_RESTRICT in);
CML_HIDDEN void CMLInternalfloat4to8bitInterval(const CMLColorMachine* cm, CMLByte* CML_RESTRICT out, const float* CML_RESTRICT in);
CML_HIDDEN void CMLInternalfloat1to16bitFloor(const CMLColorMachine* cm, CMLWord* CML_RESTRICT out, const float* CML_RESTRICT in);
CML_HIDDEN void CMLInternalfloat3to16bitFloor(const CMLColorMachine* cm, CMLWord* CML_RESTRICT out, const float* CML_RESTRICT in);
CML_HIDDEN void CMLInternalfloat4to16bitFloor(const CMLColorMachine* cm, CMLWord* CML_RESTRICT out, const float* CML_RESTRICT in);
CML_HIDDEN void CMLInternalfloat1to16bitBox(const CMLColorMachine* cm, CMLWord* CML_RESTRICT out, const float* CML_RESTRICT in);
CML_HIDDEN void CMLInternalfloat3to16bitBox(const CMLColorMachine* cm, CMLWord* CML_RESTRICT out, const float* CML_RESTRICT in);
CML_HIDDEN void CMLInternalfloat4to16bitBox(const CMLColorMachine* cm, CMLWord* CML_RESTRICT out, const float* CML_RESTRICT in);
CML_HIDDEN void CMLInternalfloat1to16bitInterval(const CMLColorMachine* cm, CMLWord* CML_RESTRICT out, const float* CML_RESTRICT in);
CML_HIDDEN void CMLInternalfloat3to16bitInterval(const CMLColorMachine* cm, CMLWord* CML_RESTRICT out, const float* CML_RESTRICT in);
CML_HIDDEN void CMLInternalfloat4to16bitInterval(const CMLColorMachine* cm, CMLWord* CML_RESTRICT out, const float* CML_RESTRICT in);
CML_HIDDEN void CMLInternalGraytoChanneledBufferHSL(const CMLColorMachine* cm, float* CML_RESTRICT buffer , const float* CML_RESTRICT gray);
CML_HIDDEN void CMLInternalGraytoChanneledBufferHSV(const CMLColorMachine* cm, float* CML_RESTRICT buffer , const float* CML_RESTRICT gray);
CML_HIDDEN void CMLInternalGraytoChanneledBufferG(const CMLColorMachine* cm, float* CML_RESTRICT buffer , const float* CML_RESTRICT gray);
CML_HIDDEN void CMLInternalGraytoChanneledBufferLSTAR(const CMLColorMachine* cm, float* CML_RESTRICT buffer , const float* CML_RESTRICT gray);
CML_HIDDEN void CMLInternalGraytoChanneledBufferL(const CMLColorMachine* cm, float* CML_RESTRICT buffer , const float* CML_RESTRICT gray);
CML_HIDDEN void CMLInternalGraytoChanneledBufferY(const CMLColorMachine* cm, float* CML_RESTRICT buffer , const float* CML_RESTRICT gray);
CML_HIDDEN void CMLInternalGraytoChanneledBufferYPRIME(const CMLColorMachine* cm, float* CML_RESTRICT buffer , const float* CML_RESTRICT gray);
CML_HIDDEN void CMLInternalChanneledBuffertoGrayHSL(const CMLColorMachine* cm, float* CML_RESTRICT gray , const float* CML_RESTRICT buffer);
CML_HIDDEN void CMLInternalChanneledBuffertoGrayHSV(const CMLColorMachine* cm, float* CML_RESTRICT gray , const float* CML_RESTRICT buffer);
CML_HIDDEN void CMLInternalChanneledBuffertoGrayG(const CMLColorMachine* cm, float* CML_RESTRICT gray , const float* CML_RESTRICT buffer);
CML_HIDDEN void CMLInternalChanneledBuffertoGrayLSTAR(const CMLColorMachine* cm, float* CML_RESTRICT gray , const float* CML_RESTRICT buffer);
CML_HIDDEN void CMLInternalChanneledBuffertoGrayL(const CMLColorMachine* cm, float* CML_RESTRICT gray , const float* CML_RESTRICT buffer);
CML_HIDDEN void CMLInternalChanneledBuffertoGrayY(const CMLColorMachine* cm, float* CML_RESTRICT gray , const float* CML_RESTRICT buffer);
CML_HIDDEN void CMLInternalChanneledBuffertoGrayYPRIME(const CMLColorMachine* cm, float* CML_RESTRICT gray , const float* CML_RESTRICT buffer);
CML_HIDDEN void CMLInternalXYZtoLabCIELAB (const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count);
CML_HIDDEN void CMLInternalXYZtoLabCIELAB_SB (const CMLColorMachine* cm, float* buf, CMLuint32 count, CMLuint32 floatalign);
CML_HIDDEN void CMLInternalXYZtoLabChromaticValence (const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count);
CML_HIDDEN void CMLInternalXYZtoLabChromaticValence_SB (const CMLColorMachine* cm, float* buf, CMLuint32 count, CMLuint32 floatalign);
CML_HIDDEN void CMLInternalLabtoXYZCIELAB (const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count);
CML_HIDDEN void CMLInternalLabtoXYZCIELAB_SB (const CMLColorMachine* cm, float* buf, CMLuint32 count, CMLuint32 floatalign);
CML_HIDDEN void CMLInternalLabtoXYZChromaticValence (const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count);
CML_HIDDEN void CMLInternalLabtoXYZChromaticValence_SB (const CMLColorMachine* cm, float* buf, CMLuint32 count, CMLuint32 floatalign);
CML_HIDDEN void CMLInternalRGBtoCMYKStandard (const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count);
CML_HIDDEN void CMLInternalRGBtoCMYKStandard_SB (const CMLColorMachine* cm, float* buf, CMLuint32 count, CMLuint32 floatalign);
CML_HIDDEN void CMLInternalRGBtoCMYKUCR (const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count);
CML_HIDDEN void CMLInternalRGBtoCMYKUCR_SB (const CMLColorMachine* cm, float* buf, CMLuint32 count, CMLuint32 floatalign);
CML_HIDDEN void CMLInternalCMYKtoRGBStandard (const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count);
CML_HIDDEN void CMLInternalCMYKtoRGBStandard_SB (const CMLColorMachine* cm, float* buf, CMLuint32 count, CMLuint32 floatalign);
CML_HIDDEN void CMLInternalCMYKtoRGBUCR (const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count);
CML_HIDDEN void CMLInternalCMYKtoRGBUCR_SB (const CMLColorMachine* cm, float* buf, CMLuint32 count, CMLuint32 floatalign);
 
CML_HIDDEN void CMLInternalrecomputeObserver(CMLColorMachine* cm);
CML_HIDDEN void CMLInternalrecomputeIllumination(CMLColorMachine* cm);
CML_HIDDEN void CMLInternalrecomputeLabColorspace(CMLColorMachine* cm);
CML_HIDDEN void CMLInternalrecomputeAdamsChromaticityValenceSpace(CMLColorMachine* cm);
CML_HIDDEN void CMLInternalrecomputeRGBResponses(CMLColorMachine* cm);
CML_HIDDEN void CMLInternalrecomputeRGBColorspace(CMLColorMachine* cm);

CML_HIDDEN CML_INLINE static void CMLCMXYZtoYxy   (const CMLColorMachine* cm, float* CML_RESTRICT Yxy , const float* CML_RESTRICT XYZ, CMLuint32 count)
  {cmlInternalXYZtoYxy(Yxy, XYZ, cmlGetReferenceWhitepointYxy(&(cm->observer)), count);}
CML_HIDDEN CML_INLINE static void CMLCMXYZtoYxy_SB   (const CMLColorMachine* cm, float* buf, CMLuint32 count, CMLuint32 floatalign)
  {cmlInternalXYZtoYxy_SB(buf, cmlGetReferenceWhitepointYxy(&(cm->observer)), count, floatalign);}
CML_HIDDEN CML_INLINE static void CMLCMYxytoXYZ   (const CMLColorMachine* cm, float* CML_RESTRICT XYZ , const float* CML_RESTRICT Yxy, CMLuint32 count)
  {cmlInternalYxytoXYZ(XYZ, Yxy, cmlGetReferenceWhitepointXYZ(&(cm->observer)), count);}
CML_HIDDEN CML_INLINE static void CMLCMYxytoXYZ_SB(const CMLColorMachine* cm, float* buf, CMLuint32 count, CMLuint32 floatalign)
  {cmlInternalYxytoXYZ_SB(buf, cmlGetReferenceWhitepointXYZ(&(cm->observer)), count, floatalign);}
CML_HIDDEN CML_INLINE static void CMLCMYxytoYupvp (const CMLColorMachine* cm, float* CML_RESTRICT Yupvp , const float* CML_RESTRICT Yxy, CMLuint32 count)
  {cmlInternalYxytoYupvp(Yupvp, Yxy, cmlGetReferenceWhitepointYupvp(&(cm->observer)), count);}
CML_HIDDEN CML_INLINE static void CMLCMYxytoYupvp_SB (const CMLColorMachine* cm, float* buf, CMLuint32 count, CMLuint32 floatalign)
  {cmlInternalYxytoYupvp_SB(buf, cmlGetReferenceWhitepointYupvp(&(cm->observer)), count, floatalign);}
CML_HIDDEN CML_INLINE static void CMLCMYupvptoYxy (const CMLColorMachine* cm, float* CML_RESTRICT Yxy , const float* CML_RESTRICT Yupvp, CMLuint32 count)
  {cmlInternalYupvptoYxy(Yxy, Yupvp, cmlGetReferenceWhitepointYxy(&(cm->observer)), count);}
CML_HIDDEN CML_INLINE static void CMLCMYupvptoYxy_SB (const CMLColorMachine* cm, float* buf, CMLuint32 count, CMLuint32 floatalign)
  {cmlInternalYupvptoYxy_SB(buf, cmlGetReferenceWhitepointYxy(&(cm->observer)), count, floatalign);}
CML_HIDDEN CML_INLINE static void CMLCMYupvptoYuv (const CMLColorMachine* cm, float* CML_RESTRICT Yuv , const float* CML_RESTRICT Yupvp, CMLuint32 count)
  {cm = cm; cmlInternalYupvptoYuv(Yuv, Yupvp, count);}
CML_HIDDEN CML_INLINE static void CMLCMYupvptoYuv_SB (const CMLColorMachine* cm, float* buf, CMLuint32 count, CMLuint32 floatalign)
  {cm = cm; cmlInternalYupvptoYuv_SB(buf, count, floatalign);}
CML_HIDDEN CML_INLINE static void CMLCMYuvtoYupvp (const CMLColorMachine* cm, float* CML_RESTRICT Yupvp , const float* CML_RESTRICT Yuv, CMLuint32 count)
  {cm = cm; cmlInternalYuvtoYupvp(Yupvp, Yuv, count);}
CML_HIDDEN CML_INLINE static void CMLCMYuvtoYupvp_SB (const CMLColorMachine* cm, float* buf, CMLuint32 count, CMLuint32 floatalign)
  {cm = cm; cmlInternalYuvtoYupvp_SB(buf, count, floatalign);}
CML_HIDDEN CML_INLINE static void CMLCMYupvptoLuv (const CMLColorMachine* cm, float* CML_RESTRICT Luv , const float* CML_RESTRICT Yupvp, CMLuint32 count)
  {cmlInternalYupvptoLuv(Luv, Yupvp, count, cmlGetReferenceWhitepointYupvp(&(cm->observer)), cm->labspace.responseLStar.forwardfunc);}
CML_HIDDEN CML_INLINE static void CMLCMYupvptoLuv_SB (const CMLColorMachine* cm, float* buf, CMLuint32 count, CMLuint32 floatalign)
  {cmlInternalYupvptoLuv_SB(buf, count, floatalign, cmlGetReferenceWhitepointYupvp(&(cm->observer)), cm->labspace.responseLStar.forwardfunc);}
CML_HIDDEN CML_INLINE static void CMLCMLuvtoYupvp (const CMLColorMachine* cm, float* CML_RESTRICT Yupvp , const float* CML_RESTRICT Luv, CMLuint32 count)
  {cmlInternalLuvtoYupvp(Yupvp, Luv, count, cmlGetReferenceWhitepointYupvp(&(cm->observer)), cm->labspace.responseLStar.backwardfunc);}
CML_HIDDEN CML_INLINE static void CMLCMLuvtoYupvp_SB (const CMLColorMachine* cm, float* buf, CMLuint32 count, CMLuint32 floatalign)
  {cmlInternalLuvtoYupvp_SB(buf, count, floatalign, cmlGetReferenceWhitepointYupvp(&(cm->observer)), cm->labspace.responseLStar.backwardfunc);}
CML_HIDDEN CML_INLINE static void CMLCMLabtoLch   (const CMLColorMachine* cm, float* CML_RESTRICT Lch , const float* CML_RESTRICT Lab, CMLuint32 count)
  {cm = cm; cmlInternalLabtoLch(Lch, Lab, count);}
CML_HIDDEN CML_INLINE static void CMLCMLabtoLch_SB   (const CMLColorMachine* cm, float* buf, CMLuint32 count, CMLuint32 floatalign)
  {cm = cm; cmlInternalLabtoLch_SB(buf, count, floatalign);}
CML_HIDDEN CML_INLINE static void CMLCMLchtoLab   (const CMLColorMachine* cm, float* CML_RESTRICT Lab , const float* CML_RESTRICT Lch, CMLuint32 count)
  {cm = cm; cmlInternalLchtoLab(Lab, Lch, count);}
CML_HIDDEN CML_INLINE static void CMLCMLchtoLab_SB   (const CMLColorMachine* cm, float* buf, CMLuint32 count, CMLuint32 floatalign)
  {cm = cm; cmlInternalLchtoLab_SB(buf, count, floatalign);}
CML_HIDDEN CML_INLINE static void CMLCMXYZtoRGB   (const CMLColorMachine* cm, float* CML_RESTRICT RGB , const float* CML_RESTRICT XYZ, CMLuint32 count)
  {cmlInternalXYZtoRGB(RGB, XYZ, count, cm->rgbspace.matrixinv, cm->rgbspace.responseR.forwardfunc, cm->rgbspace.responseG.forwardfunc, cm->rgbspace.responseB.forwardfunc);}
CML_HIDDEN CML_INLINE static void CMLCMXYZtoRGB_SB   (const CMLColorMachine* cm, float* buf, CMLuint32 count, CMLuint32 floatalign)
  {cmlInternalXYZtoRGB_SB(buf, count, floatalign, cm->rgbspace.matrixinv, cm->rgbspace.responseR.forwardfunc, cm->rgbspace.responseG.forwardfunc, cm->rgbspace.responseB.forwardfunc);}
CML_HIDDEN CML_INLINE static void CMLCMRGBtoXYZ   (const CMLColorMachine* cm, float* CML_RESTRICT XYZ , const float* CML_RESTRICT RGB, CMLuint32 count)
  {cmlInternalRGBtoXYZ(XYZ, RGB, count, cm->rgbspace.matrix, cm->rgbspace.responseR.backwardfunc, cm->rgbspace.responseG.backwardfunc, cm->rgbspace.responseB.backwardfunc);}
CML_HIDDEN CML_INLINE static void CMLCMRGBtoXYZ_SB   (const CMLColorMachine* cm, float* buf, CMLuint32 count, CMLuint32 floatalign)
  {cmlInternalRGBtoXYZ_SB(buf, count, floatalign, cm->rgbspace.matrix, cm->rgbspace.responseR.backwardfunc, cm->rgbspace.responseG.backwardfunc, cm->rgbspace.responseB.backwardfunc);}
CML_HIDDEN CML_INLINE static void CMLCMRGBtoYCbCr (const CMLColorMachine* cm, float* CML_RESTRICT YCbCr , const float* CML_RESTRICT RGB, CMLuint32 count)
  {cmlInternalRGBtoYCbCr(YCbCr, RGB, count, cm->rgbspace.primariesYxy[0], cm->rgbspace.primariesYxy[2], cmlGetReferenceInverseWhitepointXYZ(&(cm->observer)));}
CML_HIDDEN CML_INLINE static void CMLCMRGBtoYCbCr_SB (const CMLColorMachine* cm, float* buf, CMLuint32 count, CMLuint32 floatalign)
  {cmlInternalRGBtoYCbCr_SB(buf, count, floatalign, cm->rgbspace.primariesYxy[0], cm->rgbspace.primariesYxy[2], cmlGetReferenceInverseWhitepointXYZ(&(cm->observer)));}
CML_HIDDEN CML_INLINE static void CMLCMYCbCrtoRGB (const CMLColorMachine* cm, float* CML_RESTRICT RGB , const float* CML_RESTRICT YCbCr, CMLuint32 count)
  {cmlInternalYCbCrtoRGB(RGB, YCbCr, count, cm->rgbspace.primariesYxy[0], cm->rgbspace.primariesYxy[2], cmlGetReferenceInverseWhitepointXYZ(&(cm->observer)));}
CML_HIDDEN CML_INLINE static void CMLCMYCbCrtoRGB_SB (const CMLColorMachine* cm, float* buf, CMLuint32 count, CMLuint32 floatalign)
  {cmlInternalYCbCrtoRGB_SB(buf, count, floatalign, cm->rgbspace.primariesYxy[0], cm->rgbspace.primariesYxy[2], cmlGetReferenceInverseWhitepointXYZ(&(cm->observer)));}
CML_HIDDEN CML_INLINE static void CMLCMRGBtoHSV (const CMLColorMachine* cm, float* CML_RESTRICT HSV , const float* CML_RESTRICT RGB, CMLuint32 count)
  {cm = cm; cmlInternalRGBtoHSV(HSV, RGB, count);}
CML_HIDDEN CML_INLINE static void CMLCMRGBtoHSV_SB (const CMLColorMachine* cm, float* buf, CMLuint32 count, CMLuint32 floatalign)
  {cm = cm; cmlInternalRGBtoHSV_SB(buf, count, floatalign);}
CML_HIDDEN CML_INLINE static void CMLCMHSVtoRGB (const CMLColorMachine* cm, float* CML_RESTRICT RGB , const float* CML_RESTRICT HSV, CMLuint32 count)
  {cm = cm; cmlInternalHSVtoRGB(RGB, HSV, count);}
CML_HIDDEN CML_INLINE static void CMLCMHSVtoRGB_SB (const CMLColorMachine* cm, float* buf, CMLuint32 count, CMLuint32 floatalign)
  {cm = cm; cmlInternalHSVtoRGB_SB(buf, count, floatalign);}
CML_HIDDEN CML_INLINE static void CMLCMHSVtoHSL (const CMLColorMachine* cm, float* CML_RESTRICT HSL , const float* CML_RESTRICT HSV, CMLuint32 count)
  {cm = cm; cmlInternalHSVtoHSL(HSL, HSV, count);}
CML_HIDDEN CML_INLINE static void CMLCMHSVtoHSL_SB (const CMLColorMachine* cm, float* buf, CMLuint32 count, CMLuint32 floatalign)
  {cm = cm; cmlInternalHSVtoHSL_SB(buf, count, floatalign);}
CML_HIDDEN CML_INLINE static void CMLCMHSLtoHSV (const CMLColorMachine* cm, float* CML_RESTRICT HSV , const float* CML_RESTRICT HSL, CMLuint32 count)
  {cm = cm; cmlInternalHSLtoHSV(HSV, HSL, count);}
CML_HIDDEN CML_INLINE static void CMLCMHSLtoHSV_SB (const CMLColorMachine* cm, float* buf, CMLuint32 count, CMLuint32 floatalign)
  {cm = cm; cmlInternalHSLtoHSV_SB(buf, count, floatalign);}


CML_HIDDEN CML_INLINE static void CMLCMIlluminationSpectrumtoXYZ(const CMLColorMachine* cm, float* CML_RESTRICT XYZ , const CMLFunction* CML_RESTRICT specill, CMLuint32 count, CMLuint32 floatalign)
  {cmlInternalIlluminationSpectrumtoXYZ(XYZ, specill, count, floatalign, &(cm->observer));}
CML_HIDDEN CML_INLINE static void CMLCMRemissionSpectrumtoXYZ(const CMLColorMachine* cm, float* CML_RESTRICT XYZ , const CMLFunction* CML_RESTRICT specrem, CMLuint32 count, CMLuint32 floatalign)
  {cmlInternalRemissionSpectrumtoXYZ(XYZ, specrem, count, floatalign, cmlGetReferenceIlluminationSpectrum(&(cm->observer)), &(cm->observer));}



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

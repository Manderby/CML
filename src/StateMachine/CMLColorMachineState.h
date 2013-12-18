
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

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



struct CMLHIDDEN CMLColorMachine{

  CMLSize recomputationlockcount;
  CMLuint8 recomputationmask;

  struct inputoutput_struct{
    CMLIntegerMappingType         integermapping;
    CMLByte                       offset8bit[CML_MAX_NUMBER_OF_CHANNELS];
    float                         range8bit[CML_MAX_NUMBER_OF_CHANNELS];
    CMLWord                       offset16bit[CML_MAX_NUMBER_OF_CHANNELS];
    float                         range16bit[CML_MAX_NUMBER_OF_CHANNELS];
  } inputoutput;
  
  CMLObserver* observer;
  CMLRGBSpace* rgbspace;
  
  struct cmykspace_struct{
    CMLCMYKTransformType          transform;
  } cmykspace;
  
  struct labspace_struct{
    CMLLabSpaceType          state;
    CMLResponseCurve*             responseL;
    CMLResponseCurve*             responseLStar;    // used for Luv
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
//  void (*GraytoChanneledBuffer) (const CMLColorMachine* cm, float* CML_RESTRICT buffer , const float* CML_RESTRICT gray);
//  void (*ChanneledBuffertoGray) (const CMLColorMachine* cm, float* CML_RESTRICT gray , const float* CML_RESTRICT buffer);
  void (*XYZtoLab)              (const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count);
  void (*XYZtoLab_SB)           (const CMLColorMachine* cm, float* buf, CMLuint32 count);
  void (*LabtoXYZ)              (const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count);
  void (*LabtoXYZ_SB)           (const CMLColorMachine* cm, float* buf, CMLuint32 count);
  void (*RGBtoCMYK)             (const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count);
  void (*RGBtoCMYK_SB)          (const CMLColorMachine* cm, float* buf, CMLuint32 count);
  void (*CMYKtoRGB)             (const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count);
  void (*CMYKtoRGB_SB)          (const CMLColorMachine* cm, float* buf, CMLuint32 count);
};


CMLHIDDEN void CMLInternalfloat1to8bitFloor(const CMLColorMachine* cm, CMLByte* CML_RESTRICT out, const float* CML_RESTRICT in);
CMLHIDDEN void CMLInternalfloat3to8bitFloor(const CMLColorMachine* cm, CMLByte* CML_RESTRICT out, const float* CML_RESTRICT in);
CMLHIDDEN void CMLInternalfloat4to8bitFloor(const CMLColorMachine* cm, CMLByte* CML_RESTRICT out, const float* CML_RESTRICT in);
CMLHIDDEN void CMLInternalfloat1to8bitBox(const CMLColorMachine* cm, CMLByte* CML_RESTRICT out, const float* CML_RESTRICT in);
CMLHIDDEN void CMLInternalfloat3to8bitBox(const CMLColorMachine* cm, CMLByte* CML_RESTRICT out, const float* CML_RESTRICT in);
CMLHIDDEN void CMLInternalfloat4to8bitBox(const CMLColorMachine* cm, CMLByte* CML_RESTRICT out, const float* CML_RESTRICT in);
CMLHIDDEN void CMLInternalfloat1to8bitInterval(const CMLColorMachine* cm, CMLByte* CML_RESTRICT out, const float* CML_RESTRICT in);
CMLHIDDEN void CMLInternalfloat3to8bitInterval(const CMLColorMachine* cm, CMLByte* CML_RESTRICT out, const float* CML_RESTRICT in);
CMLHIDDEN void CMLInternalfloat4to8bitInterval(const CMLColorMachine* cm, CMLByte* CML_RESTRICT out, const float* CML_RESTRICT in);
CMLHIDDEN void CMLInternalfloat1to16bitFloor(const CMLColorMachine* cm, CMLWord* CML_RESTRICT out, const float* CML_RESTRICT in);
CMLHIDDEN void CMLInternalfloat3to16bitFloor(const CMLColorMachine* cm, CMLWord* CML_RESTRICT out, const float* CML_RESTRICT in);
CMLHIDDEN void CMLInternalfloat4to16bitFloor(const CMLColorMachine* cm, CMLWord* CML_RESTRICT out, const float* CML_RESTRICT in);
CMLHIDDEN void CMLInternalfloat1to16bitBox(const CMLColorMachine* cm, CMLWord* CML_RESTRICT out, const float* CML_RESTRICT in);
CMLHIDDEN void CMLInternalfloat3to16bitBox(const CMLColorMachine* cm, CMLWord* CML_RESTRICT out, const float* CML_RESTRICT in);
CMLHIDDEN void CMLInternalfloat4to16bitBox(const CMLColorMachine* cm, CMLWord* CML_RESTRICT out, const float* CML_RESTRICT in);
CMLHIDDEN void CMLInternalfloat1to16bitInterval(const CMLColorMachine* cm, CMLWord* CML_RESTRICT out, const float* CML_RESTRICT in);
CMLHIDDEN void CMLInternalfloat3to16bitInterval(const CMLColorMachine* cm, CMLWord* CML_RESTRICT out, const float* CML_RESTRICT in);
CMLHIDDEN void CMLInternalfloat4to16bitInterval(const CMLColorMachine* cm, CMLWord* CML_RESTRICT out, const float* CML_RESTRICT in);
//CMLHIDDEN void CMLInternalGraytoChanneledBufferHSL(const CMLColorMachine* cm, float* CML_RESTRICT buffer , const float* CML_RESTRICT gray);
//CMLHIDDEN void CMLInternalGraytoChanneledBufferHSV(const CMLColorMachine* cm, float* CML_RESTRICT buffer , const float* CML_RESTRICT gray);
//CMLHIDDEN void CMLInternalGraytoChanneledBufferG(const CMLColorMachine* cm, float* CML_RESTRICT buffer , const float* CML_RESTRICT gray);
//CMLHIDDEN void CMLInternalGraytoChanneledBufferLSTAR(const CMLColorMachine* cm, float* CML_RESTRICT buffer , const float* CML_RESTRICT gray);
//CMLHIDDEN void CMLInternalGraytoChanneledBufferL(const CMLColorMachine* cm, float* CML_RESTRICT buffer , const float* CML_RESTRICT gray);
//CMLHIDDEN void CMLInternalGraytoChanneledBufferY(const CMLColorMachine* cm, float* CML_RESTRICT buffer , const float* CML_RESTRICT gray);
//CMLHIDDEN void CMLInternalGraytoChanneledBufferYPRIME(const CMLColorMachine* cm, float* CML_RESTRICT buffer , const float* CML_RESTRICT gray);
//CMLHIDDEN void CMLInternalChanneledBuffertoGrayHSL(const CMLColorMachine* cm, float* CML_RESTRICT gray , const float* CML_RESTRICT buffer);
//CMLHIDDEN void CMLInternalChanneledBuffertoGrayHSV(const CMLColorMachine* cm, float* CML_RESTRICT gray , const float* CML_RESTRICT buffer);
//CMLHIDDEN void CMLInternalChanneledBuffertoGrayG(const CMLColorMachine* cm, float* CML_RESTRICT gray , const float* CML_RESTRICT buffer);
//CMLHIDDEN void CMLInternalChanneledBuffertoGrayLSTAR(const CMLColorMachine* cm, float* CML_RESTRICT gray , const float* CML_RESTRICT buffer);
//CMLHIDDEN void CMLInternalChanneledBuffertoGrayL(const CMLColorMachine* cm, float* CML_RESTRICT gray , const float* CML_RESTRICT buffer);
//CMLHIDDEN void CMLInternalChanneledBuffertoGrayY(const CMLColorMachine* cm, float* CML_RESTRICT gray , const float* CML_RESTRICT buffer);
//CMLHIDDEN void CMLInternalChanneledBuffertoGrayYPRIME(const CMLColorMachine* cm, float* CML_RESTRICT gray , const float* CML_RESTRICT buffer);
//CMLHIDDEN void CMLInternalXYZtoLabCIELAB (const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count);
//CMLHIDDEN void CMLInternalXYZtoLabCIELAB_SB (const CMLColorMachine* cm, float* buf, CMLuint32 count);
//CMLHIDDEN void CMLInternalXYZtoLabChromaticValence (const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count);
//CMLHIDDEN void CMLInternalXYZtoLabChromaticValence_SB (const CMLColorMachine* cm, float* buf, CMLuint32 count);
CMLHIDDEN void CMLInternalLabtoXYZCIELAB (const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count);
CMLHIDDEN void CMLInternalLabtoXYZCIELAB_SB (const CMLColorMachine* cm, float* buf, CMLuint32 count);
CMLHIDDEN void CMLInternalLabtoXYZChromaticValence (const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count);
CMLHIDDEN void CMLInternalLabtoXYZChromaticValence_SB (const CMLColorMachine* cm, float* buf, CMLuint32 count);
CMLHIDDEN void CMLInternalRGBtoCMYKStandard (const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count);
CMLHIDDEN void CMLInternalRGBtoCMYKStandard_SB (const CMLColorMachine* cm, float* buf, CMLuint32 count);
CMLHIDDEN void CMLInternalRGBtoCMYKUCR (const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count);
CMLHIDDEN void CMLInternalRGBtoCMYKUCR_SB (const CMLColorMachine* cm, float* buf, CMLuint32 count);
CMLHIDDEN void CMLInternalCMYKtoRGBStandard (const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count);
CMLHIDDEN void CMLInternalCMYKtoRGBStandard_SB (const CMLColorMachine* cm, float* buf, CMLuint32 count);
CMLHIDDEN void CMLInternalCMYKtoRGBUCR (const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count);
CMLHIDDEN void CMLInternalCMYKtoRGBUCR_SB (const CMLColorMachine* cm, float* buf, CMLuint32 count);
 
//CMLHIDDEN void CMLInternalrecomputeObserver(CMLColorMachine* cm);
CMLHIDDEN void CMLInternalrecomputeIllumination(CMLColorMachine* cm);
CMLHIDDEN void CMLInternalrecomputeLabColorspace(CMLColorMachine* cm);
CMLHIDDEN void CMLInternalrecomputeAdamsChromaticityValenceSpace(CMLColorMachine* cm);
CMLHIDDEN void CMLInternalrecomputeRGBResponses(CMLColorMachine* cm);
CMLHIDDEN void CMLInternalrecomputeRGBColorspace(CMLColorMachine* cm);

//CMLHIDDEN CML_INLINE static void CMLCMXYZtoYxy   (const CMLColorMachine* cm, float* CML_RESTRICT Yxy , const float* CML_RESTRICT XYZ, CMLuint32 count)
//  {cmlInternalXYZtoYxy(Yxy, XYZ, count, cmlGetWhitepointYxy(cmlGetLabSpaceWhitepoint(cm->labspace)));}
//CMLHIDDEN CML_INLINE static void CMLCMXYZtoYxy_SB   (const CMLColorMachine* cm, float* buf, CMLuint32 count)
//  {cmlInternalXYZtoYxy_SB(buf, count, cmlGetWhitepointYxy(cmlGetLabSpaceWhitepoint(cm->labspace)));}
//CMLHIDDEN CML_INLINE static void CMLCMYxytoXYZ   (const CMLColorMachine* cm, float* CML_RESTRICT XYZ , const float* CML_RESTRICT Yxy, CMLuint32 count)
//  {cmlInternalYxytoXYZ(XYZ, Yxy, count, cmlGetWhitepointXYZ(cmlGetLabSpaceWhitepoint(cm->labspace)));}
//CMLHIDDEN CML_INLINE static void CMLCMYxytoXYZ_SB(const CMLColorMachine* cm, float* buf, CMLuint32 count)
//  {cmlInternalYxytoXYZ_SB(buf, count, cmlGetWhitepointXYZ(cmlGetLabSpaceWhitepoint(cm->labspace)));}
//CMLHIDDEN CML_INLINE static void CMLCMYxytoYupvp (const CMLColorMachine* cm, float* CML_RESTRICT Yupvp , const float* CML_RESTRICT Yxy, CMLuint32 count)
//  {cmlInternalYxytoYupvp(Yupvp, Yxy, cmlGetWhitepointYupvp(cmlGetLabSpaceWhitepoint(cm->labspace)), count);}
//CMLHIDDEN CML_INLINE static void CMLCMYxytoYupvp_SB (const CMLColorMachine* cm, float* buf, CMLuint32 count)
//  {cmlInternalYxytoYupvp_SB(buf, cmlGetWhitepointYupvp(cmlGetLabSpaceWhitepoint(cm->labspace)), count);}
//CMLHIDDEN CML_INLINE static void CMLCMYupvptoYxy (const CMLColorMachine* cm, float* CML_RESTRICT Yxy , const float* CML_RESTRICT Yupvp, CMLuint32 count)
//  {cmlInternalYupvptoYxy(Yxy, Yupvp, cmlGetWhitepointYxy(cmlGetLabSpaceWhitepoint(cm->labspace)), count);}
//CMLHIDDEN CML_INLINE static void CMLCMYupvptoYxy_SB (const CMLColorMachine* cm, float* buf, CMLuint32 count)
//  {cmlInternalYupvptoYxy_SB(buf, cmlGetWhitepointYxy(cmlGetLabSpaceWhitepoint(cm->labspace)), count);}
//CMLHIDDEN CML_INLINE static void CMLCMYupvptoYuv (const CMLColorMachine* cm, float* CML_RESTRICT Yuv , const float* CML_RESTRICT Yupvp, CMLuint32 count)
//  {cm = cm; cmlInternalYupvptoYuv(Yuv, Yupvp, count);}
//CMLHIDDEN CML_INLINE static void CMLCMYupvptoYuv_SB (const CMLColorMachine* cm, float* buf, CMLuint32 count)
//  {cm = cm; cmlInternalYupvptoYuv_SB(buf, count);}
//CMLHIDDEN CML_INLINE static void CMLCMYuvtoYupvp (const CMLColorMachine* cm, float* CML_RESTRICT Yupvp , const float* CML_RESTRICT Yuv, CMLuint32 count)
//  {cm = cm; cmlInternalYuvtoYupvp(Yupvp, Yuv, count);}
//CMLHIDDEN CML_INLINE static void CMLCMYuvtoYupvp_SB (const CMLColorMachine* cm, float* buf, CMLuint32 count)
//  {cm = cm; cmlInternalYuvtoYupvp_SB(buf, count);}
//CMLHIDDEN CML_INLINE static void CMLCMYupvptoLuv (const CMLColorMachine* cm, float* CML_RESTRICT Luv , const float* CML_RESTRICT Yupvp, CMLuint32 count)
//  {cmlInternalYupvptoLuv(Luv, Yupvp, count, cmlGetWhitepointYupvp(cmlGetLabSpaceWhitepoint(cm->labspace)), cmlGetResponseCurveForwardFunc(cm->labspace.responseLStar));}
//CMLHIDDEN CML_INLINE static void CMLCMYupvptoLuv_SB (const CMLColorMachine* cm, float* buf, CMLuint32 count)
//  {cmlInternalYupvptoLuv_SB(buf, count, cmlGetWhitepointYupvp(cmlGetLabSpaceWhitepoint(cm->labspace)), cmlGetResponseCurveForwardFunc(cm->labspace.responseLStar));}
//CMLHIDDEN CML_INLINE static void CMLCMLuvtoYupvp (const CMLColorMachine* cm, float* CML_RESTRICT Yupvp , const float* CML_RESTRICT Luv, CMLuint32 count)
//  {cmlInternalLuvtoYupvp(Yupvp, Luv, count, cmlGetWhitepointYupvp(cmlGetLabSpaceWhitepoint(cm->labspace)), cmlGetResponseCurveBackwardFunc(cm->labspace.responseLStar));}
//CMLHIDDEN CML_INLINE static void CMLCMLuvtoYupvp_SB (const CMLColorMachine* cm, float* buf, CMLuint32 count)
//  {cmlInternalLuvtoYupvp_SB(buf, count, cmlGetWhitepointYupvp(cmlGetLabSpaceWhitepoint(cm->labspace)), cmlGetResponseCurveBackwardFunc(cm->labspace.responseLStar));}
//CMLHIDDEN CML_INLINE static void CMLCMLabtoLch   (const CMLColorMachine* cm, float* CML_RESTRICT Lch , const float* CML_RESTRICT Lab, CMLuint32 count)
//  {cm = cm; cmlInternalLabtoLch(Lch, Lab, count);}
//CMLHIDDEN CML_INLINE static void CMLCMLabtoLch_SB   (const CMLColorMachine* cm, float* buf, CMLuint32 count)
//  {cm = cm; cmlInternalLabtoLch_SB(buf, count);}
//CMLHIDDEN CML_INLINE static void CMLCMLchtoLab   (const CMLColorMachine* cm, float* CML_RESTRICT Lab , const float* CML_RESTRICT Lch, CMLuint32 count)
//  {cm = cm; cmlInternalLchtoLab(Lab, Lch, count);}
//CMLHIDDEN CML_INLINE static void CMLCMLchtoLab_SB   (const CMLColorMachine* cm, float* buf, CMLuint32 count)
//  {cm = cm; cmlInternalLchtoLab_SB(buf, count);}
//CMLHIDDEN CML_INLINE static void CMLCMXYZtoRGB   (const CMLColorMachine* cm, float* CML_RESTRICT RGB , const float* CML_RESTRICT XYZ, CMLuint32 count)
//  {cmlInternalXYZtoRGB(RGB, XYZ, count, cm->rgbspace);}
//CMLHIDDEN CML_INLINE static void CMLCMXYZtoRGB_SB   (const CMLColorMachine* cm, float* buf, CMLuint32 count)
//  {cmlInternalXYZtoRGB_SB(buf, count, cm->rgbspace);}
//CMLHIDDEN CML_INLINE static void CMLCMRGBtoXYZ   (const CMLColorMachine* cm, float* CML_RESTRICT XYZ , const float* CML_RESTRICT RGB, CMLuint32 count)
//  {cmlInternalRGBtoXYZ(XYZ, RGB, count, cm->rgbspace);}
//CMLHIDDEN CML_INLINE static void CMLCMRGBtoXYZ_SB   (const CMLColorMachine* cm, float* buf, CMLuint32 count)
//  {cmlInternalRGBtoXYZ_SB(buf, count, cm->rgbspace);}
//CMLHIDDEN CML_INLINE static void CMLCMRGBtoYCbCr (const CMLColorMachine* cm, float* CML_RESTRICT YCbCr , const float* CML_RESTRICT RGB, CMLuint32 count)
//  {cmlInternalRGBtoYCbCr(YCbCr, RGB, count, cm->rgbspace);}
//CMLHIDDEN CML_INLINE static void CMLCMRGBtoYCbCr_SB (const CMLColorMachine* cm, float* buf, CMLuint32 count)
//  {cmlInternalRGBtoYCbCr_SB(buf, count, cm->rgbspace);}
//CMLHIDDEN CML_INLINE static void CMLCMYCbCrtoRGB (const CMLColorMachine* cm, float* CML_RESTRICT RGB , const float* CML_RESTRICT YCbCr, CMLuint32 count)
//  {cmlInternalYCbCrtoRGB(RGB, YCbCr, count, cm->rgbspace);}
//CMLHIDDEN CML_INLINE static void CMLCMYCbCrtoRGB_SB (const CMLColorMachine* cm, float* buf, CMLuint32 count)
//  {cmlInternalYCbCrtoRGB_SB(buf, count, cm->rgbspace);}
//CMLHIDDEN CML_INLINE static void CMLCMRGBtoHSV (const CMLColorMachine* cm, float* CML_RESTRICT HSV , const float* CML_RESTRICT RGB, CMLuint32 count)
//  {cm = cm; cmlInternalRGBtoHSV(HSV, RGB, count);}
//CMLHIDDEN CML_INLINE static void CMLCMRGBtoHSV_SB (const CMLColorMachine* cm, float* buf, CMLuint32 count)
//  {cm = cm; cmlInternalRGBtoHSV_SB(buf, count);}
//CMLHIDDEN CML_INLINE static void CMLCMHSVtoRGB (const CMLColorMachine* cm, float* CML_RESTRICT RGB , const float* CML_RESTRICT HSV, CMLuint32 count)
//  {cm = cm; cmlInternalHSVtoRGB(RGB, HSV, count);}
//CMLHIDDEN CML_INLINE static void CMLCMHSVtoRGB_SB (const CMLColorMachine* cm, float* buf, CMLuint32 count)
//  {cm = cm; cmlInternalHSVtoRGB_SB(buf, count);}
//CMLHIDDEN CML_INLINE static void CMLCMHSVtoHSL (const CMLColorMachine* cm, float* CML_RESTRICT HSL , const float* CML_RESTRICT HSV, CMLuint32 count)
//  {cm = cm; cmlInternalHSVtoHSL(HSL, HSV, count);}
//CMLHIDDEN CML_INLINE static void CMLCMHSVtoHSL_SB (const CMLColorMachine* cm, float* buf, CMLuint32 count)
//  {cm = cm; cmlInternalHSVtoHSL_SB(buf, count);}
//CMLHIDDEN CML_INLINE static void CMLCMHSLtoHSV (const CMLColorMachine* cm, float* CML_RESTRICT HSV , const float* CML_RESTRICT HSL, CMLuint32 count)
//  {cm = cm; cmlInternalHSLtoHSV(HSV, HSL, count);}
//CMLHIDDEN CML_INLINE static void CMLCMHSLtoHSV_SB (const CMLColorMachine* cm, float* buf, CMLuint32 count)
//  {cm = cm; cmlInternalHSLtoHSV_SB(buf, count);}
//
//
//CMLHIDDEN CML_INLINE static void CMLCMIlluminationSpectrumtoXYZ(const CMLColorMachine* cm, float* CML_RESTRICT XYZ , const CMLFunction* CML_RESTRICT specill, CMLuint32 count)
//  {cmlInternalIlluminationSpectrumtoXYZ(XYZ, specill, count, cmlGetRGBSpaceWhitepoint(cm->rgbspace));}
//CMLHIDDEN CML_INLINE static void CMLCMRemissionSpectrumtoXYZ(const CMLColorMachine* cm, float* CML_RESTRICT XYZ , const CMLFunction* CML_RESTRICT specrem, CMLuint32 count)
//  {cmlInternalRemissionSpectrumtoXYZ(XYZ, specrem, count, cmlGetObserverIlluminationSpectrum(cm->observer), cmlGetRGBSpaceWhitepoint(cm->rgbspace));}



#include "CMLNormedConversions.h"


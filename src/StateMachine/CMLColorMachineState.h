//
//// (c) Manderim GmbH
//// This is proprietary software. Any use without the explicit acknowledgement
//// of the author of this software is prohibited and any liability is disclamed.
//// Terms of a separate contract may apply.
//
//#include "../CML.h"
//
#include "CMLInternal.h"
#include "../CML.h"
//
//
//// Enumeration for internal recomputation consistency. Will be used with the
//// calls to lockRecomputation and releaseRecomputation.
//typedef enum{
//  CML_COLORMACHINE_RECOMPUTE_RGB                 = 0x01,
//  CML_COLORMACHINE_RECOMPUTE_RGB_RESPONSES       = 0x02,
//  CML_COLORMACHINE_RECOMPUTE_LAB                 = 0x04,
//  CML_COLORMACHINE_RECOMPUTE_ADAMS_CHROMATICITY  = 0x08,
//  CML_COLORMACHINE_RECOMPUTE_ILLUMINATION        = 0x10,
//  CML_COLORMACHINE_RECOMPUTE_OBSERVER            = 0x20
//} ColorMachineRecomputation;
//
//
//
//struct CML_HIDDEN CMLColorMachine{
//
//  CMLSize recomputationlockcount;
//  CMLuint8 recomputationmask;
//
//  struct inputoutput_struct{
//    CMLIntegerMappingType         integermapping;
//    CMLByte                       offset8bit[CML_MAX_NUMBER_OF_CHANNELS];
//    float                         range8bit[CML_MAX_NUMBER_OF_CHANNELS];
//    CMLWord                       offset16bit[CML_MAX_NUMBER_OF_CHANNELS];
//    float                         range16bit[CML_MAX_NUMBER_OF_CHANNELS];
//  } inputoutput;
//  
//  CMLObserver* observer;
//  CMLRGBSpace* rgbspace;
//  
//  struct cmykspace_struct{
//    CMLCMYKTransformType          transform;
//  } cmykspace;
//  
//  struct labspace_struct{
//    CMLLabSpaceType          state;
//    CMLResponseCurve*             responseL;
//    CMLResponseCurve*             responseLStar;    // used for Luv
//    CMLuint8                      lutsize;
//    float                         adamschromaticityvalenceK;
//    float                         adamschromaticityvalenceke;
////    CMLDeltaEComputationType      deltaecomputation;
//  } labspace;
//  
//  struct grayspace_struct{
//    CMLGrayComputationType        computation;
//  } grayspace;
//
//  void (*float1to8bit)          (const CMLColorMachine* cm, CMLByte* CML_RESTRICT out, const float* CML_RESTRICT in);
//  void (*float3to8bit)          (const CMLColorMachine* cm, CMLByte* CML_RESTRICT out, const float* CML_RESTRICT in);
//  void (*float4to8bit)          (const CMLColorMachine* cm, CMLByte* CML_RESTRICT out, const float* CML_RESTRICT in);
//  void (*float1to16bit)         (const CMLColorMachine* cm, CMLWord* CML_RESTRICT out, const float* CML_RESTRICT in);
//  void (*float3to16bit)         (const CMLColorMachine* cm, CMLWord* CML_RESTRICT out, const float* CML_RESTRICT in);
//  void (*float4to16bit)         (const CMLColorMachine* cm, CMLWord* CML_RESTRICT out, const float* CML_RESTRICT in);
////  void (*GraytoChanneledBuffer) (const CMLColorMachine* cm, float* CML_RESTRICT buffer , const float* CML_RESTRICT gray);
////  void (*ChanneledBuffertoGray) (const CMLColorMachine* cm, float* CML_RESTRICT gray , const float* CML_RESTRICT buffer);
//  void (*XYZToLab)              (const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count);
//  void (*XYZToLab_SB)           (const CMLColorMachine* cm, float* buf, CMLuint32 count);
//  void (*LabToXYZ)              (const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count);
//  void (*LabToXYZ_SB)           (const CMLColorMachine* cm, float* buf, CMLuint32 count);
//  void (*RGBtoCMYK)             (const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count);
//  void (*RGBtoCMYK_SB)          (const CMLColorMachine* cm, float* buf, CMLuint32 count);
//  void (*CMYKtoRGB)             (const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count);
//  void (*CMYKtoRGB_SB)          (const CMLColorMachine* cm, float* buf, CMLuint32 count);
//};
//
//
//CML_HIDDEN void CMLInternalfloat1to8bitFloor(const CMLColorMachine* cm, CMLByte* CML_RESTRICT out, const float* CML_RESTRICT in);
//CML_HIDDEN void CMLInternalfloat3to8bitFloor(const CMLColorMachine* cm, CMLByte* CML_RESTRICT out, const float* CML_RESTRICT in);
//CML_HIDDEN void CMLInternalfloat4to8bitFloor(const CMLColorMachine* cm, CMLByte* CML_RESTRICT out, const float* CML_RESTRICT in);
//CML_HIDDEN void CMLInternalfloat1to8bitBox(const CMLColorMachine* cm, CMLByte* CML_RESTRICT out, const float* CML_RESTRICT in);
//CML_HIDDEN void CMLInternalfloat3to8bitBox(const CMLColorMachine* cm, CMLByte* CML_RESTRICT out, const float* CML_RESTRICT in);
//CML_HIDDEN void CMLInternalfloat4to8bitBox(const CMLColorMachine* cm, CMLByte* CML_RESTRICT out, const float* CML_RESTRICT in);
//CML_HIDDEN void CMLInternalfloat1to8bitInterval(const CMLColorMachine* cm, CMLByte* CML_RESTRICT out, const float* CML_RESTRICT in);
//CML_HIDDEN void CMLInternalfloat3to8bitInterval(const CMLColorMachine* cm, CMLByte* CML_RESTRICT out, const float* CML_RESTRICT in);
//CML_HIDDEN void CMLInternalfloat4to8bitInterval(const CMLColorMachine* cm, CMLByte* CML_RESTRICT out, const float* CML_RESTRICT in);
//CML_HIDDEN void CMLInternalfloat1to16bitFloor(const CMLColorMachine* cm, CMLWord* CML_RESTRICT out, const float* CML_RESTRICT in);
//CML_HIDDEN void CMLInternalfloat3to16bitFloor(const CMLColorMachine* cm, CMLWord* CML_RESTRICT out, const float* CML_RESTRICT in);
//CML_HIDDEN void CMLInternalfloat4to16bitFloor(const CMLColorMachine* cm, CMLWord* CML_RESTRICT out, const float* CML_RESTRICT in);
//CML_HIDDEN void CMLInternalfloat1to16bitBox(const CMLColorMachine* cm, CMLWord* CML_RESTRICT out, const float* CML_RESTRICT in);
//CML_HIDDEN void CMLInternalfloat3to16bitBox(const CMLColorMachine* cm, CMLWord* CML_RESTRICT out, const float* CML_RESTRICT in);
//CML_HIDDEN void CMLInternalfloat4to16bitBox(const CMLColorMachine* cm, CMLWord* CML_RESTRICT out, const float* CML_RESTRICT in);
//CML_HIDDEN void CMLInternalfloat1to16bitInterval(const CMLColorMachine* cm, CMLWord* CML_RESTRICT out, const float* CML_RESTRICT in);
//CML_HIDDEN void CMLInternalfloat3to16bitInterval(const CMLColorMachine* cm, CMLWord* CML_RESTRICT out, const float* CML_RESTRICT in);
//CML_HIDDEN void CMLInternalfloat4to16bitInterval(const CMLColorMachine* cm, CMLWord* CML_RESTRICT out, const float* CML_RESTRICT in);
////CML_HIDDEN void CMLInternalGraytoChanneledBufferHSL(const CMLColorMachine* cm, float* CML_RESTRICT buffer , const float* CML_RESTRICT gray);
////CML_HIDDEN void CMLInternalGraytoChanneledBufferHSV(const CMLColorMachine* cm, float* CML_RESTRICT buffer , const float* CML_RESTRICT gray);
////CML_HIDDEN void CMLInternalGraytoChanneledBufferG(const CMLColorMachine* cm, float* CML_RESTRICT buffer , const float* CML_RESTRICT gray);
////CML_HIDDEN void CMLInternalGraytoChanneledBufferLSTAR(const CMLColorMachine* cm, float* CML_RESTRICT buffer , const float* CML_RESTRICT gray);
////CML_HIDDEN void CMLInternalGraytoChanneledBufferL(const CMLColorMachine* cm, float* CML_RESTRICT buffer , const float* CML_RESTRICT gray);
////CML_HIDDEN void CMLInternalGraytoChanneledBufferY(const CMLColorMachine* cm, float* CML_RESTRICT buffer , const float* CML_RESTRICT gray);
////CML_HIDDEN void CMLInternalGraytoChanneledBufferYPRIME(const CMLColorMachine* cm, float* CML_RESTRICT buffer , const float* CML_RESTRICT gray);
////CML_HIDDEN void CMLInternalChanneledBuffertoGrayHSL(const CMLColorMachine* cm, float* CML_RESTRICT gray , const float* CML_RESTRICT buffer);
////CML_HIDDEN void CMLInternalChanneledBuffertoGrayHSV(const CMLColorMachine* cm, float* CML_RESTRICT gray , const float* CML_RESTRICT buffer);
////CML_HIDDEN void CMLInternalChanneledBuffertoGrayG(const CMLColorMachine* cm, float* CML_RESTRICT gray , const float* CML_RESTRICT buffer);
////CML_HIDDEN void CMLInternalChanneledBuffertoGrayLSTAR(const CMLColorMachine* cm, float* CML_RESTRICT gray , const float* CML_RESTRICT buffer);
////CML_HIDDEN void CMLInternalChanneledBuffertoGrayL(const CMLColorMachine* cm, float* CML_RESTRICT gray , const float* CML_RESTRICT buffer);
////CML_HIDDEN void CMLInternalChanneledBuffertoGrayY(const CMLColorMachine* cm, float* CML_RESTRICT gray , const float* CML_RESTRICT buffer);
////CML_HIDDEN void CMLInternalChanneledBuffertoGrayYPRIME(const CMLColorMachine* cm, float* CML_RESTRICT gray , const float* CML_RESTRICT buffer);
////CML_HIDDEN void CMLInternalXYZToLabCIELAB (const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count);
////CML_HIDDEN void CMLInternalXYZToLabCIELAB_SB (const CMLColorMachine* cm, float* buf, CMLuint32 count);
////CML_HIDDEN void CMLInternalXYZToLabChromaticValence (const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count);
////CML_HIDDEN void CMLInternalXYZToLabChromaticValence_SB (const CMLColorMachine* cm, float* buf, CMLuint32 count);
//CML_HIDDEN void CMLInternalLabToXYZCIELAB (const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count);
//CML_HIDDEN void CMLInternalLabToXYZCIELAB_SB (const CMLColorMachine* cm, float* buf, CMLuint32 count);
//CML_HIDDEN void CMLInternalLabToXYZChromaticValence (const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count);
//CML_HIDDEN void CMLInternalLabToXYZChromaticValence_SB (const CMLColorMachine* cm, float* buf, CMLuint32 count);
//CML_HIDDEN void CMLInternalRGBtoCMYKStandard (const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count);
//CML_HIDDEN void CMLInternalRGBtoCMYKStandard_SB (const CMLColorMachine* cm, float* buf, CMLuint32 count);
//CML_HIDDEN void CMLInternalRGBtoCMYKUCR (const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count);
//CML_HIDDEN void CMLInternalRGBtoCMYKUCR_SB (const CMLColorMachine* cm, float* buf, CMLuint32 count);
//CML_HIDDEN void CMLInternalCMYKtoRGBStandard (const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count);
//CML_HIDDEN void CMLInternalCMYKtoRGBStandard_SB (const CMLColorMachine* cm, float* buf, CMLuint32 count);
//CML_HIDDEN void CMLInternalCMYKtoRGBUCR (const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count);
//CML_HIDDEN void CMLInternalCMYKtoRGBUCR_SB (const CMLColorMachine* cm, float* buf, CMLuint32 count);
// 
////CML_HIDDEN void CMLInternalrecomputeObserver(CMLColorMachine* cm);
//CML_HIDDEN void CMLInternalrecomputeIllumination(CMLColorMachine* cm);
//CML_HIDDEN void CMLInternalrecomputeLabColorspace(CMLColorMachine* cm);
//CML_HIDDEN void CMLInternalrecomputeAdamsChromaticityValenceSpace(CMLColorMachine* cm);
//CML_HIDDEN void CMLInternalrecomputeRGBResponses(CMLColorMachine* cm);
//CML_HIDDEN void CMLInternalrecomputeRGBColorspace(CMLColorMachine* cm);
//
////
////CML_HIDDEN CML_INLINE void CMLCMIlluminationSpectrumtoXYZ(const CMLColorMachine* cm, float* CML_RESTRICT XYZ , const CMLFunction* CML_RESTRICT specill, CMLuint32 count)
////  {cml_IlluminationSpectrumtoXYZ(XYZ, specill, count, cmlGetRGBSpaceWhite(cm->rgbspace));}
////CML_HIDDEN CML_INLINE void CMLCMRemissionSpectrumtoXYZ(const CMLColorMachine* cm, float* CML_RESTRICT XYZ , const CMLFunction* CML_RESTRICT specrem, CMLuint32 count)
////  {cml_RemissionSpectrumtoXYZ(XYZ, specrem, count, cmlGetObserverIlluminationSpectrum(cm->observer), cmlGetRGBSpaceWhite(cm->rgbspace));}
//
//
//
//#include "CMLNormedConversions.h"
//


// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

#include "../CML.h"
#include "CMLInternal.h"


//CML_HIDDEN CML_INLINE CMLColorConverter CMLInternalGetGrayToAnythingColorConverter(const CMLColorMachine* cm, CMLColorType outputsystem){
//  switch(cm->grayspace.computation){
//  case CML_GRAY_FROM_HSL    : return cmlGetColorConverter(outputsystem, CML_COLOR_HSL); break;
//  case CML_GRAY_FROM_HSV    : return cmlGetColorConverter(outputsystem, CML_COLOR_HSV); break;
//  case CML_GRAY_FROM_G      : return cmlGetColorConverter(outputsystem, CML_COLOR_RGB); break;
//  case CML_GRAY_FROM_LSTAR  : return cmlGetColorConverter(outputsystem, CML_COLOR_Luv); break;
//  case CML_GRAY_FROM_L      : return cmlGetColorConverter(outputsystem, CML_COLOR_Lab); break;
//  case CML_GRAY_FROM_Y      : return cmlGetColorConverter(outputsystem, CML_COLOR_Yxy); break;
//  case CML_GRAY_FROM_YPRIME : return cmlGetColorConverter(outputsystem, CML_COLOR_YCbCr); break;
//  default:
//    #ifndef NDEBUG
//      cmlError("CMLInternalGetGrayToAnythingColorConverter", "Undefined Gray conversion.");
//    #endif
//    // Although it is virtually impossible to reach here, give the compiler
//    // a reason to be happy and return L*
//    return cmlGetColorConverter(outputsystem, CML_COLOR_Luv);
//    break;
//  }
//}
//
//CML_HIDDEN CML_INLINE CMLColorConverter CMLInternalGetAnythingToGrayColorConverter(const CMLColorMachine* cm, CMLColorType inputsystem){
//  switch(cm->grayspace.computation){
//  case CML_GRAY_FROM_HSL    : return cmlGetColorConverter(CML_COLOR_HSL, inputsystem); break;
//  case CML_GRAY_FROM_HSV    : return cmlGetColorConverter(CML_COLOR_HSV, inputsystem); break;
//  case CML_GRAY_FROM_G      : return cmlGetColorConverter(CML_COLOR_RGB, inputsystem); break;
//  case CML_GRAY_FROM_LSTAR  : return cmlGetColorConverter(CML_COLOR_Luv, inputsystem); break;
//  case CML_GRAY_FROM_L      : return cmlGetColorConverter(CML_COLOR_Lab, inputsystem); break;
//  case CML_GRAY_FROM_Y      : return cmlGetColorConverter(CML_COLOR_Yxy, inputsystem); break;
//  case CML_GRAY_FROM_YPRIME : return cmlGetColorConverter(CML_COLOR_YCbCr, inputsystem); break;
//  default:
//    #ifndef NDEBUG
//      cmlError("CMLInternalGetAnythingToGrayColorConverter", "Undefined Gray conversion.");
//    #endif
//    // Although it is virtually impossible to reach here, give the compiler
//    // a reason to be happy and return L*
//    return cmlGetColorConverter(CML_COLOR_Luv, inputsystem);
//    break;
//  }
//}



// //////////////////////////
// Identity converter
// //////////////////////////

//CML_API void CMLGraytoGray(const CMLColorMachine* cm, CMLOutput grayd , CMLInput grays, CMLSize count){
//  cm = cm; // no warning
//  memcpy(grayd, grays, count * sizeof(CMLVec1));
//}


//////////////////////////////
// Gray to anything
//////////////////////////////


//CML_HIDDEN CML_INLINE void CMLInternalConvertGrayToColorspace(const CMLColorMachine* cm, float* out, const float* in, CMLSize count, CMLColorType outputsystem, CMLSize outputchannelcount){
//  CMLSize i;
//  float c[CML_MAX_NUMBER_OF_CHANNELS];
//  CMLColorConverter grayconverter = CMLInternalGetGrayToAnythingColorConverter(cm, outputsystem);
//  for(i=0; i<count; i++){
//    cm->GraytoChanneledBuffer(cm, c, in);
//    (*grayconverter)(cm, out, c, 1);
//    in +=1;
//    out += outputchannelcount;
//  }
//}




//////////////////////////////
// Anything to Gray
//////////////////////////////

//CML_HIDDEN CML_INLINE void CMLInternalConvertColorspaceToGray(const CMLColorMachine* cm, float* out, const float* in, CMLSize count, CMLColorType inputsystem, CMLSize inputchannelcount){
//  CMLSize i;
//  float c[CML_MAX_NUMBER_OF_CHANNELS];
//  CMLColorConverter grayconverter = CMLInternalGetAnythingToGrayColorConverter(cm, inputsystem);
//  for(i=0; i<count; i++){
//    (*grayconverter)(cm, c, in, 1);
//    cm->ChanneledBuffertoGray(cm, out, c);
//    in += inputchannelcount;
//    out += 1;
//  }
//}

//CML_API void CMLSpectrumIlluminationtoGray(const CMLColorMachine* cm, CMLOutput gray, CMLInput specill, CMLSize count){
//  CMLSize i;
//  const CMLFunction* in  = (const CMLFunction*)specill;
//  float* out = (float*)gray;
//  float c[CML_MAX_NUMBER_OF_CHANNELS];
//  CMLColorConverter grayconverter = CMLInternalGetAnythingToGrayColorConverter(cm, CML_COLOR_SPECTRUM_ILLUMINATION);
//  for(i=0; i<count; i++){
//    (*grayconverter)(cm, c, in, 1);
//    cm->ChanneledBuffertoGray(cm, out, c);
//    in += 1;
//    out += 1;
//  }
//}

//CML_API void CMLRemissiontoGray(const CMLColorMachine* cm, CMLOutput gray, CMLInput specrem, CMLSize count){
//  CMLSize i;
//  const CMLFunction* in  = (const CMLFunction*)specrem;
//  float* out = (float*)gray;
//  float c[CML_MAX_NUMBER_OF_CHANNELS];
//  CMLColorConverter grayconverter = CMLInternalGetAnythingToGrayColorConverter(cm, CML_COLOR_SPECTRUM_REMISSION);
//  for(i=0; i<count; i++){
//    (*grayconverter)(cm, c, in, 1);
//    cm->ChanneledBuffertoGray(cm, out, c);
//    in += 1;
//    out += 1;
//  }
//}



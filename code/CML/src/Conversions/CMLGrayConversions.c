
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

#include "../CML.h"
#include "../StateMachine/CMLColorMachineState.h"


CMLHIDDEN CML_INLINE static CMLColorConverter CMLInternalGetGrayToAnythingColorConverter(const CMLColorMachine* cm, CMLColorType outputsystem){
  switch(cm->grayspace.computation){
  case CML_GRAY_FROM_HSL    : return CMLgetColorConverter(outputsystem, CML_COLOR_HSL); break;
  case CML_GRAY_FROM_HSV    : return CMLgetColorConverter(outputsystem, CML_COLOR_HSV); break;
  case CML_GRAY_FROM_G      : return CMLgetColorConverter(outputsystem, CML_COLOR_RGB); break;
  case CML_GRAY_FROM_LSTAR  : return CMLgetColorConverter(outputsystem, CML_COLOR_Luv); break;
  case CML_GRAY_FROM_L      : return CMLgetColorConverter(outputsystem, CML_COLOR_Lab); break;
  case CML_GRAY_FROM_Y      : return CMLgetColorConverter(outputsystem, CML_COLOR_Yxy); break;
  case CML_GRAY_FROM_YPRIME : return CMLgetColorConverter(outputsystem, CML_COLOR_YCbCr); break;
  default:
    #ifndef NDEBUG
      cmlError("CMLInternalGetGrayToAnythingColorConverter", "Undefined Gray conversion.");
    #endif
    // Although it is virtually impossible to reach here, give the compiler
    // a reason to be happy and return L*
    return CMLgetColorConverter(outputsystem, CML_COLOR_Luv);
    break;
  }
}

CMLHIDDEN CML_INLINE static CMLColorConverter CMLInternalGetAnythingToGrayColorConverter(const CMLColorMachine* cm, CMLColorType inputsystem){
  switch(cm->grayspace.computation){
  case CML_GRAY_FROM_HSL    : return CMLgetColorConverter(CML_COLOR_HSL, inputsystem); break;
  case CML_GRAY_FROM_HSV    : return CMLgetColorConverter(CML_COLOR_HSV, inputsystem); break;
  case CML_GRAY_FROM_G      : return CMLgetColorConverter(CML_COLOR_RGB, inputsystem); break;
  case CML_GRAY_FROM_LSTAR  : return CMLgetColorConverter(CML_COLOR_Luv, inputsystem); break;
  case CML_GRAY_FROM_L      : return CMLgetColorConverter(CML_COLOR_Lab, inputsystem); break;
  case CML_GRAY_FROM_Y      : return CMLgetColorConverter(CML_COLOR_Yxy, inputsystem); break;
  case CML_GRAY_FROM_YPRIME : return CMLgetColorConverter(CML_COLOR_YCbCr, inputsystem); break;
  default:
    #ifndef NDEBUG
      cmlError("CMLInternalGetAnythingToGrayColorConverter", "Undefined Gray conversion.");
    #endif
    // Although it is virtually impossible to reach here, give the compiler
    // a reason to be happy and return L*
    return CMLgetColorConverter(CML_COLOR_Luv, inputsystem);
    break;
  }
}



// //////////////////////////
// Identity converter
// //////////////////////////

CMLAPI void CMLGraytoGray(const CMLColorMachine* cm, CMLOutput grayd , CMLInput grays, CMLSize count){
  cm = cm; // no warning
  memcpy(grayd, grays, count * sizeof(CMLVec1));
}


//////////////////////////////
// Gray to anything
//////////////////////////////


CMLHIDDEN CML_INLINE static void CMLInternalConvertGrayToColorspace(const CMLColorMachine* cm, float* out, const float* in, CMLSize count, CMLColorType outputsystem, CMLSize outputchannelcount){
  CMLSize i;
  float c[CML_MAX_NUMBER_OF_CHANNELS];
  CMLColorConverter grayconverter = CMLInternalGetGrayToAnythingColorConverter(cm, outputsystem);
  for(i=0; i<count; i++){
    cm->GraytoChanneledBuffer(cm, c, in);
    (*grayconverter)(cm, out, c, 1);
    in +=1;
    out += outputchannelcount;
  }
}


CMLAPI void CMLGraytoXYZ (const CMLColorMachine* cm, CMLOutput XYZ , CMLInput gray, CMLSize count){
  CMLInternalConvertGrayToColorspace(cm, (float*)XYZ, (float*)gray, count, CML_COLOR_XYZ, 3);
}
CMLAPI void CMLGraytoYuv (const CMLColorMachine* cm, CMLOutput Yuv , CMLInput gray, CMLSize count){
  CMLInternalConvertGrayToColorspace(cm, (float*)Yuv, (float*)gray, count, CML_COLOR_Yuv, 3);
}
CMLAPI void CMLGraytoYupvp (const CMLColorMachine* cm, CMLOutput Yupvp , CMLInput gray, CMLSize count){
  CMLInternalConvertGrayToColorspace(cm, (float*)Yupvp, (float*)gray, count, CML_COLOR_Yupvp, 3);
}
CMLAPI void CMLGraytoYxy (const CMLColorMachine* cm, CMLOutput Yxy , CMLInput gray, CMLSize count){
  CMLInternalConvertGrayToColorspace(cm, (float*)Yxy, (float*)gray, count, CML_COLOR_Yxy, 3);
}
CMLAPI void CMLGraytoLab (const CMLColorMachine* cm, CMLOutput Lab , CMLInput gray, CMLSize count){
  CMLInternalConvertGrayToColorspace(cm, (float*)Lab, (float*)gray, count, CML_COLOR_Lab, 3);
}
CMLAPI void CMLGraytoLch (const CMLColorMachine* cm, CMLOutput Lch , CMLInput gray, CMLSize count){
  CMLInternalConvertGrayToColorspace(cm, (float*)Lch, (float*)gray, count, CML_COLOR_Lch, 3);
}
CMLAPI void CMLGraytoLuv (const CMLColorMachine* cm, CMLOutput Luv , CMLInput gray, CMLSize count){
  CMLInternalConvertGrayToColorspace(cm, (float*)Luv, (float*)gray, count, CML_COLOR_Luv, 3);
}
CMLAPI void CMLGraytoRGB (const CMLColorMachine* cm, CMLOutput RGB , CMLInput gray, CMLSize count){
  CMLInternalConvertGrayToColorspace(cm, (float*)RGB, (float*)gray, count, CML_COLOR_RGB, 3);
}
CMLAPI void CMLGraytoYCbCr (const CMLColorMachine* cm, CMLOutput YCbCr , CMLInput gray, CMLSize count){
  CMLInternalConvertGrayToColorspace(cm, (float*)YCbCr, (float*)gray, count, CML_COLOR_YCbCr, 3);
}
CMLAPI void CMLGraytoHSV (const CMLColorMachine* cm, CMLOutput HSV , CMLInput gray, CMLSize count){
  CMLInternalConvertGrayToColorspace(cm, (float*)HSV, (float*)gray, count, CML_COLOR_HSV, 3);
}
CMLAPI void CMLGraytoHSL (const CMLColorMachine* cm, CMLOutput HSL , CMLInput gray, CMLSize count){
  CMLInternalConvertGrayToColorspace(cm, (float*)HSL, (float*)gray, count, CML_COLOR_HSL, 3);
}
CMLAPI void CMLGraytoCMYK(const CMLColorMachine* cm, CMLOutput CMYK, CMLInput gray, CMLSize count){
  CMLInternalConvertGrayToColorspace(cm, (float*)CMYK, (float*)gray, count, CML_COLOR_CMYK, 4);
}






//////////////////////////////
// Anything to Gray
//////////////////////////////

CMLHIDDEN CML_INLINE static void CMLInternalConvertColorspaceToGray(const CMLColorMachine* cm, float* out, const float* in, CMLSize count, CMLColorType inputsystem, CMLSize inputchannelcount){
  CMLSize i;
  float c[CML_MAX_NUMBER_OF_CHANNELS];
  CMLColorConverter grayconverter = CMLInternalGetAnythingToGrayColorConverter(cm, inputsystem);
  for(i=0; i<count; i++){
    (*grayconverter)(cm, c, in, 1);
    cm->ChanneledBuffertoGray(cm, out, c);
    in += inputchannelcount;
    out += 1;
  }
}

CMLAPI void CMLXYZtoGray(const CMLColorMachine* cm, CMLOutput gray, CMLInput XYZ , CMLSize count){
  CMLInternalConvertColorspaceToGray(cm, (float*)gray, (float*)XYZ, count, CML_COLOR_XYZ, 3);
}

CMLAPI void CMLYuvtoGray(const CMLColorMachine* cm, CMLOutput gray, CMLInput Yuv , CMLSize count){
  CMLInternalConvertColorspaceToGray(cm, (float*)gray, (float*)Yuv, count, CML_COLOR_Yuv, 3);
}

CMLAPI void CMLYupvptoGray(const CMLColorMachine* cm, CMLOutput gray, CMLInput Yupvp , CMLSize count){
  CMLInternalConvertColorspaceToGray(cm, (float*)gray, (float*)Yupvp, count, CML_COLOR_Yupvp, 3);
}

CMLAPI void CMLYxytoGray(const CMLColorMachine* cm, CMLOutput gray, CMLInput Yxy , CMLSize count){
  CMLInternalConvertColorspaceToGray(cm, (float*)gray, (float*)Yxy, count, CML_COLOR_Yxy, 3);
}

CMLAPI void CMLLabtoGray(const CMLColorMachine* cm, CMLOutput gray, CMLInput Lab , CMLSize count){
  CMLInternalConvertColorspaceToGray(cm, (float*)gray, (float*)Lab, count, CML_COLOR_Lab, 3);
}

CMLAPI void CMLLchtoGray(const CMLColorMachine* cm, CMLOutput gray, CMLInput Lch , CMLSize count){
  CMLInternalConvertColorspaceToGray(cm, (float*)gray, (float*)Lch, count, CML_COLOR_Lch, 3);
}

CMLAPI void CMLLuvtoGray(const CMLColorMachine* cm, CMLOutput gray, CMLInput Luv , CMLSize count){
  CMLInternalConvertColorspaceToGray(cm, (float*)gray, (float*)Luv, count, CML_COLOR_Luv, 3);
}

CMLAPI void CMLRGBtoGray(const CMLColorMachine* cm, CMLOutput gray, CMLInput RGB , CMLSize count){
  CMLInternalConvertColorspaceToGray(cm, (float*)gray, (float*)RGB, count, CML_COLOR_RGB, 3);
}

CMLAPI void CMLYCbCrtoGray(const CMLColorMachine* cm, CMLOutput gray, CMLInput YCbCr , CMLSize count){
  CMLInternalConvertColorspaceToGray(cm, (float*)gray, (float*)YCbCr, count, CML_COLOR_YCbCr, 3);
}

CMLAPI void CMLHSVtoGray(const CMLColorMachine* cm, CMLOutput gray, CMLInput HSV , CMLSize count){
  CMLInternalConvertColorspaceToGray(cm, (float*)gray, (float*)HSV, count, CML_COLOR_HSV, 3);
}

CMLAPI void CMLHSLtoGray(const CMLColorMachine* cm, CMLOutput gray, CMLInput HSL , CMLSize count){
  CMLInternalConvertColorspaceToGray(cm, (float*)gray, (float*)HSL, count, CML_COLOR_HSL, 3);
}

CMLAPI void CMLCMYKtoGray(const CMLColorMachine* cm, CMLOutput gray, CMLInput CMYK, CMLSize count){
  CMLInternalConvertColorspaceToGray(cm, (float*)gray, (float*)CMYK, count, CML_COLOR_CMYK, 4);
}

CMLAPI void CMLSpectrumIlluminationtoGray(const CMLColorMachine* cm, CMLOutput gray, CMLInput specill, CMLSize count){
  CMLSize i;
  const CMLFunction* in  = (const CMLFunction*)specill;
  float* out = (float*)gray;
  float c[CML_MAX_NUMBER_OF_CHANNELS];
  CMLColorConverter grayconverter = CMLInternalGetAnythingToGrayColorConverter(cm, CML_COLOR_SPECTRUM_ILLUMINATION);
  for(i=0; i<count; i++){
    (*grayconverter)(cm, c, in, 1);
    cm->ChanneledBuffertoGray(cm, out, c);
    in += 1;
    out += 1;
  }
}

CMLAPI void CMLSpectrumRemissiontoGray(const CMLColorMachine* cm, CMLOutput gray, CMLInput specrem, CMLSize count){
  CMLSize i;
  const CMLFunction* in  = (const CMLFunction*)specrem;
  float* out = (float*)gray;
  float c[CML_MAX_NUMBER_OF_CHANNELS];
  CMLColorConverter grayconverter = CMLInternalGetAnythingToGrayColorConverter(cm, CML_COLOR_SPECTRUM_REMISSION);
  for(i=0; i<count; i++){
    (*grayconverter)(cm, c, in, 1);
    cm->ChanneledBuffertoGray(cm, out, c);
    in += 1;
    out += 1;
  }
}



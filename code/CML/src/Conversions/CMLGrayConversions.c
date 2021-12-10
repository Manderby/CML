
#include "../CML.h"
#include "../Internal/CMLColorMachineState.h"



CML_HIDEF CMLColorConverter cml_GetGrayToAnythingColorConverter(const CMLColorMachine* cm, CMLColorType outputSystem){
  switch(cm->graySpace.computation){
  case CML_GRAY_FROM_HSL    : return cmlGetColorConverter(outputSystem, CML_COLOR_HSL);
  case CML_GRAY_FROM_HSV    : return cmlGetColorConverter(outputSystem, CML_COLOR_HSV);
  case CML_GRAY_FROM_G      : return cmlGetColorConverter(outputSystem, CML_COLOR_RGB);
  case CML_GRAY_FROM_LSTAR  : return cmlGetColorConverter(outputSystem, CML_COLOR_Luv);
  case CML_GRAY_FROM_L      : return cmlGetColorConverter(outputSystem, CML_COLOR_Lab);
  case CML_GRAY_FROM_Y      : return cmlGetColorConverter(outputSystem, CML_COLOR_Yxy);
  case CML_GRAY_FROM_YPRIME : return cmlGetColorConverter(outputSystem, CML_COLOR_YCbCr);
  default:
    #if CML_DEBUG
      cmlError("Undefined Gray conversion.");
    #endif
    return cmlGetColorConverter(outputSystem, CML_COLOR_Luv);
  }
}

CML_HIDEF CMLColorConverter cml_GetAnythingColorToGrayColorConverter(const CMLColorMachine* cm, CMLColorType inputSystem){
  switch(cm->graySpace.computation){
  case CML_GRAY_FROM_HSL    : return cmlGetColorConverter(CML_COLOR_HSL, inputSystem);
  case CML_GRAY_FROM_HSV    : return cmlGetColorConverter(CML_COLOR_HSV, inputSystem);
  case CML_GRAY_FROM_G      : return cmlGetColorConverter(CML_COLOR_RGB, inputSystem);
  case CML_GRAY_FROM_LSTAR  : return cmlGetColorConverter(CML_COLOR_Luv, inputSystem);
  case CML_GRAY_FROM_L      : return cmlGetColorConverter(CML_COLOR_Lab, inputSystem);
  case CML_GRAY_FROM_Y      : return cmlGetColorConverter(CML_COLOR_Yxy, inputSystem);
  case CML_GRAY_FROM_YPRIME : return cmlGetColorConverter(CML_COLOR_YCbCr, inputSystem);
  default:
    #if CML_DEBUG
      cmlError("Undefined Gray conversion.");
    #endif
    return cmlGetColorConverter(CML_COLOR_Luv, inputSystem);
  }
}



// //////////////////////////
// Identity converter
// //////////////////////////

CML_API void cmlGrayToGray(const CMLColorMachine* cm, CMLOutput grayd, CMLInput grays, size_t count){
  CML_UNUSED(cm);
  memcpy(grayd, grays, count * sizeof(CMLVec1));
}



// ////////////////////////////
// Gray to anything
// ////////////////////////////

CML_HIDEF void cml_ConvertGrayToColorSpace(const CMLColorMachine* cm, float* out, const float* in, size_t count, CMLColorType outputSystem, size_t outputChannelCount){
  float c[CML_MAX_NUMBER_OF_CHANNELS];
  CMLColorConverter grayConverter = cml_GetGrayToAnythingColorConverter(cm, outputSystem);
  for(size_t i = 0; i < count; i++){
    cm->GrayToChanneledBuffer(cm, c, in);
    (*grayConverter)(cm, out, c, 1);
    in +=1;
    out += outputChannelCount;
  }
}

CML_API void cmlGrayToXYZ (const CMLColorMachine* cm, CMLOutput xyz, CMLInput gray, size_t count){
  cml_ConvertGrayToColorSpace(cm, (float*)xyz, (float*)gray, count, CML_COLOR_XYZ, 3);
}

CML_API void cmlGrayToYxy (const CMLColorMachine* cm, CMLOutput yxy, CMLInput gray, size_t count){
  cml_ConvertGrayToColorSpace(cm, (float*)yxy, (float*)gray, count, CML_COLOR_Yxy, 3);
}

CML_API void cmlGrayToYuv (const CMLColorMachine* cm, CMLOutput yuv, CMLInput gray, size_t count){
  cml_ConvertGrayToColorSpace(cm, (float*)yuv, (float*)gray, count, CML_COLOR_Yuv, 3);
}

CML_API void cmlGrayToYupvp (const CMLColorMachine* cm, CMLOutput yupvp, CMLInput gray, size_t count){
  cml_ConvertGrayToColorSpace(cm, (float*)yupvp, (float*)gray, count, CML_COLOR_Yupvp, 3);
}

CML_API void cmlGrayToLab (const CMLColorMachine* cm, CMLOutput lab, CMLInput gray, size_t count){
  cml_ConvertGrayToColorSpace(cm, (float*)lab, (float*)gray, count, CML_COLOR_Lab, 3);
}

CML_API void cmlGrayToLch (const CMLColorMachine* cm, CMLOutput lch, CMLInput gray, size_t count){
  cml_ConvertGrayToColorSpace(cm, (float*)lch, (float*)gray, count, CML_COLOR_Lch, 3);
}

CML_API void cmlGrayToLuv (const CMLColorMachine* cm, CMLOutput luv, CMLInput gray, size_t count){
  cml_ConvertGrayToColorSpace(cm, (float*)luv, (float*)gray, count, CML_COLOR_Luv, 3);
}

CML_API void cmlGrayToRGB (const CMLColorMachine* cm, CMLOutput rgb, CMLInput gray, size_t count){
  cml_ConvertGrayToColorSpace(cm, (float*)rgb, (float*)gray, count, CML_COLOR_RGB, 3);
}

CML_API void cmlGrayToYCbCr (const CMLColorMachine* cm, CMLOutput ycbcr, CMLInput gray, size_t count){
  cml_ConvertGrayToColorSpace(cm, (float*)ycbcr, (float*)gray, count, CML_COLOR_YCbCr, 3);
}

CML_API void cmlGrayToHSV (const CMLColorMachine* cm, CMLOutput hsv, CMLInput gray, size_t count){
  cml_ConvertGrayToColorSpace(cm, (float*)hsv, (float*)gray, count, CML_COLOR_HSV, 3);
}

CML_API void cmlGrayToHSL (const CMLColorMachine* cm, CMLOutput hsl, CMLInput gray, size_t count){
  cml_ConvertGrayToColorSpace(cm, (float*)hsl, (float*)gray, count, CML_COLOR_HSL, 3);
}

CML_API void cmlGrayToCMYK(const CMLColorMachine* cm, CMLOutput cmyk, CMLInput gray, size_t count){
  cml_ConvertGrayToColorSpace(cm, (float*)cmyk, (float*)gray, count, CML_COLOR_CMYK, 4);
}



// ////////////////////////////
// Anything to Gray
// ////////////////////////////

CML_HIDEF void cml_ConvertColorSpaceToGray(const CMLColorMachine* cm, float* out, const float* in, size_t count, CMLColorType inputSystem, size_t inputChannelCount){
  float c[CML_MAX_NUMBER_OF_CHANNELS];
  CMLColorConverter grayConverter = cml_GetAnythingColorToGrayColorConverter(cm, inputSystem);
  for(size_t i = 0; i < count; i++){
    (*grayConverter)(cm, c, in, 1);
    cm->ChanneledBufferToGray(cm, out, c);
    in += inputChannelCount;
    out += 1;
  }
}

CML_API void cmlXYZToGray(const CMLColorMachine* cm, CMLOutput gray, CMLInput xyz, size_t count){
  cml_ConvertColorSpaceToGray(cm, (float*)gray, (float*)xyz, count, CML_COLOR_XYZ, 3);
}

CML_API void cmlYxyToGray(const CMLColorMachine* cm, CMLOutput gray, CMLInput yxy, size_t count){
  cml_ConvertColorSpaceToGray(cm, (float*)gray, (float*)yxy, count, CML_COLOR_Yxy, 3);
}

CML_API void cmlYuvToGray(const CMLColorMachine* cm, CMLOutput gray, CMLInput yuv, size_t count){
  cml_ConvertColorSpaceToGray(cm, (float*)gray, (float*)yuv, count, CML_COLOR_Yuv, 3);
}

CML_API void cmlYupvpToGray(const CMLColorMachine* cm, CMLOutput gray, CMLInput yupvp, size_t count){
  cml_ConvertColorSpaceToGray(cm, (float*)gray, (float*)yupvp, count, CML_COLOR_Yupvp, 3);
}

CML_API void cmlLabToGray(const CMLColorMachine* cm, CMLOutput gray, CMLInput lab, size_t count){
  cml_ConvertColorSpaceToGray(cm, (float*)gray, (float*)lab, count, CML_COLOR_Lab, 3);
}

CML_API void cmlLchToGray(const CMLColorMachine* cm, CMLOutput gray, CMLInput lch, size_t count){
  cml_ConvertColorSpaceToGray(cm, (float*)gray, (float*)lch, count, CML_COLOR_Lch, 3);
}

CML_API void cmlLuvToGray(const CMLColorMachine* cm, CMLOutput gray, CMLInput luv, size_t count){
  cml_ConvertColorSpaceToGray(cm, (float*)gray, (float*)luv, count, CML_COLOR_Luv, 3);
}

CML_API void cmlRGBToGray(const CMLColorMachine* cm, CMLOutput gray, CMLInput rgb, size_t count){
  cml_ConvertColorSpaceToGray(cm, (float*)gray, (float*)rgb, count, CML_COLOR_RGB, 3);
}

CML_API void cmlYCbCrToGray(const CMLColorMachine* cm, CMLOutput gray, CMLInput ycbcr, size_t count){
  cml_ConvertColorSpaceToGray(cm, (float*)gray, (float*)ycbcr, count, CML_COLOR_YCbCr, 3);
}

CML_API void cmlHSVToGray(const CMLColorMachine* cm, CMLOutput gray, CMLInput hsv, size_t count){
  cml_ConvertColorSpaceToGray(cm, (float*)gray, (float*)hsv, count, CML_COLOR_HSV, 3);
}

CML_API void cmlHSLToGray(const CMLColorMachine* cm, CMLOutput gray, CMLInput hsl, size_t count){
  cml_ConvertColorSpaceToGray(cm, (float*)gray, (float*)hsl, count, CML_COLOR_HSL, 3);
}

CML_API void cmlCMYKToGray(const CMLColorMachine* cm, CMLOutput gray, CMLInput cmyk, size_t count){
  cml_ConvertColorSpaceToGray(cm, (float*)gray, (float*)cmyk, count, CML_COLOR_CMYK, 4);
}

CML_API void cmlSpectrumIlluminationToGray(const CMLColorMachine* cm, CMLOutput gray, CMLInput specIll, size_t count){
  const CMLFunction* in  = (const CMLFunction*)specIll;
  float* out = (float*)gray;
  float c[CML_MAX_NUMBER_OF_CHANNELS];
  CMLColorConverter grayConverter = cml_GetAnythingColorToGrayColorConverter(cm, CML_COLOR_SPECTRUM_ILLUMINATION);
  for(size_t i = 0; i < count; i++){
    (*grayConverter)(cm, c, in, 1);
    cm->ChanneledBufferToGray(cm, out, c);
    in += 1;
    out += 1;
  }
}

CML_API void cmlSpectrumRemissionToGray(const CMLColorMachine* cm, CMLOutput gray, CMLInput specRem, size_t count){
  const CMLFunction* in  = (const CMLFunction*)specRem;
  float* out = (float*)gray;
  float c[CML_MAX_NUMBER_OF_CHANNELS];
  CMLColorConverter grayConverter = cml_GetAnythingColorToGrayColorConverter(cm, CML_COLOR_SPECTRUM_REMISSION);
  for(size_t i = 0; i < count; i++){
    (*grayConverter)(cm, c, in, 1);
    cm->ChanneledBufferToGray(cm, out, c);
    in += 1;
    out += 1;
  }
}



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

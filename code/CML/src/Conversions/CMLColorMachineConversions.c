
#include "../CML.h"
#include "../StateMachine/CMLColorMachineState.h"



CML_DEF CMLColorConverter cmlGetColorConverter(CMLColorType outputSystem, CMLColorType inputSystem){
  switch(inputSystem){
  case CML_COLOR_GRAY:
    switch(outputSystem){
      case CML_COLOR_GRAY:  return &CMLGraytoGray;
      case CML_COLOR_XYZ:   return &CMLGraytoXYZ;
      case CML_COLOR_Yxy:   return &CMLGraytoYxy;
      case CML_COLOR_Yuv:   return &CMLGraytoYuv;
      case CML_COLOR_Yupvp: return &CMLGraytoYupvp;
      case CML_COLOR_Lab:   return &CMLGraytoLab;
      case CML_COLOR_Lch:   return &CMLGraytoLch;
      case CML_COLOR_Luv:   return &CMLGraytoLuv;
      case CML_COLOR_RGB:   return &CMLGraytoRGB;
      case CML_COLOR_YCbCr: return &CMLGraytoYCbCr;
      case CML_COLOR_HSV:   return &CMLGraytoHSV;
      case CML_COLOR_HSL:   return &CMLGraytoHSL;
      case CML_COLOR_CMYK:  return &CMLGraytoCMYK;
      default: break;
    }
  case CML_COLOR_XYZ:
    switch(outputSystem){
      case CML_COLOR_GRAY:  return &CMLXYZtoGray;
      case CML_COLOR_XYZ:   return &CMLXYZtoXYZ;
      case CML_COLOR_Yxy:   return &CMLXYZtoYxy;
      case CML_COLOR_Yuv:   return &CMLXYZtoYuv;
      case CML_COLOR_Yupvp: return &CMLXYZtoYupvp;
      case CML_COLOR_Lab:   return &CMLXYZtoLab;
      case CML_COLOR_Lch:   return &CMLXYZtoLch;
      case CML_COLOR_Luv:   return &CMLXYZtoLuv;
      case CML_COLOR_RGB:   return &CMLXYZtoRGB;
      case CML_COLOR_YCbCr: return &CMLXYZtoYCbCr;
      case CML_COLOR_HSV:   return &CMLXYZtoHSV;
      case CML_COLOR_HSL:   return &CMLXYZtoHSL;
      case CML_COLOR_CMYK:  return &CMLXYZtoCMYK;
      default: break;
    }
  case CML_COLOR_Yxy:
    switch(outputSystem){
      case CML_COLOR_GRAY:  return &CMLYxytoGray;
      case CML_COLOR_XYZ:   return &CMLYxytoXYZ;
      case CML_COLOR_Yxy:   return &CMLYxytoYxy;
      case CML_COLOR_Yuv:   return &CMLYxytoYuv;
      case CML_COLOR_Yupvp: return &CMLYxytoYupvp;
      case CML_COLOR_Lab:   return &CMLYxytoLab;
      case CML_COLOR_Lch:   return &CMLYxytoLch;
      case CML_COLOR_Luv:   return &CMLYxytoLuv;
      case CML_COLOR_RGB:   return &CMLYxytoRGB;
      case CML_COLOR_YCbCr: return &CMLYxytoYCbCr;
      case CML_COLOR_HSV:   return &CMLYxytoHSV;
      case CML_COLOR_HSL:   return &CMLYxytoHSL;
      case CML_COLOR_CMYK:  return &CMLYxytoCMYK;
      default: break;
    }
  case CML_COLOR_Yuv:
    switch(outputSystem){
      case CML_COLOR_GRAY:  return &CMLYuvtoGray;
      case CML_COLOR_XYZ:   return &CMLYuvtoXYZ;
      case CML_COLOR_Yxy:   return &CMLYuvtoYxy;
      case CML_COLOR_Yuv:   return &CMLYuvtoYuv;
      case CML_COLOR_Yupvp: return &CMLYuvtoYupvp;
      case CML_COLOR_Lab:   return &CMLYuvtoLab;
      case CML_COLOR_Lch:   return &CMLYuvtoLch;
      case CML_COLOR_Luv:   return &CMLYuvtoLuv;
      case CML_COLOR_RGB:   return &CMLYuvtoRGB;
      case CML_COLOR_YCbCr: return &CMLYuvtoYCbCr;
      case CML_COLOR_HSV:   return &CMLYuvtoHSV;
      case CML_COLOR_HSL:   return &CMLYuvtoHSL;
      case CML_COLOR_CMYK:  return &CMLYuvtoCMYK;
      default: break;
    }
  case CML_COLOR_Yupvp:
    switch(outputSystem){
      case CML_COLOR_GRAY:  return &CMLYupvptoGray;
      case CML_COLOR_XYZ:   return &CMLYupvptoXYZ;
      case CML_COLOR_Yxy:   return &CMLYupvptoYxy;
      case CML_COLOR_Yuv:   return &CMLYupvptoYuv;
      case CML_COLOR_Yupvp: return &CMLYupvptoYupvp;
      case CML_COLOR_Lab:   return &CMLYupvptoLab;
      case CML_COLOR_Lch:   return &CMLYupvptoLch;
      case CML_COLOR_Luv:   return &CMLYupvptoLuv;
      case CML_COLOR_RGB:   return &CMLYupvptoRGB;
      case CML_COLOR_YCbCr: return &CMLYupvptoYCbCr;
      case CML_COLOR_HSV:   return &CMLYupvptoHSV;
      case CML_COLOR_HSL:   return &CMLYupvptoHSL;
      case CML_COLOR_CMYK:  return &CMLYupvptoCMYK;
      default: break;
    }
  case CML_COLOR_Lab:
    switch(outputSystem){
      case CML_COLOR_GRAY:  return &CMLLabtoGray;
      case CML_COLOR_XYZ:   return &CMLLabtoXYZ;
      case CML_COLOR_Yxy:   return &CMLLabtoYxy;
      case CML_COLOR_Yuv:   return &CMLLabtoYuv;
      case CML_COLOR_Yupvp: return &CMLLabtoYupvp;
      case CML_COLOR_Lab:   return &CMLLabtoLab;
      case CML_COLOR_Lch:   return &CMLLabtoLch;
      case CML_COLOR_Luv:   return &CMLLabtoLuv;
      case CML_COLOR_RGB:   return &CMLLabtoRGB;
      case CML_COLOR_YCbCr: return &CMLLabtoYCbCr;
      case CML_COLOR_HSV:   return &CMLLabtoHSV;
      case CML_COLOR_HSL:   return &CMLLabtoHSL;
      case CML_COLOR_CMYK:  return &CMLLabtoCMYK;
      default: break;
    }
  case CML_COLOR_Lch:
    switch(outputSystem){
      case CML_COLOR_GRAY:  return &CMLLchtoGray;
      case CML_COLOR_XYZ:   return &CMLLchtoXYZ;
      case CML_COLOR_Yxy:   return &CMLLchtoYxy;
      case CML_COLOR_Yuv:   return &CMLLchtoYuv;
      case CML_COLOR_Yupvp: return &CMLLchtoYupvp;
      case CML_COLOR_Lab:   return &CMLLchtoLab;
      case CML_COLOR_Lch:   return &CMLLchtoLch;
      case CML_COLOR_Luv:   return &CMLLchtoLuv;
      case CML_COLOR_RGB:   return &CMLLchtoRGB;
      case CML_COLOR_YCbCr: return &CMLLchtoYCbCr;
      case CML_COLOR_HSV:   return &CMLLchtoHSV;
      case CML_COLOR_HSL:   return &CMLLchtoHSL;
      case CML_COLOR_CMYK:  return &CMLLchtoCMYK;
      default: break;
    }
  case CML_COLOR_Luv:
    switch(outputSystem){
      case CML_COLOR_GRAY:  return &CMLLuvtoGray;
      case CML_COLOR_XYZ:   return &CMLLuvtoXYZ;
      case CML_COLOR_Yxy:   return &CMLLuvtoYxy;
      case CML_COLOR_Yuv:   return &CMLLuvtoYuv;
      case CML_COLOR_Yupvp: return &CMLLuvtoYupvp;
      case CML_COLOR_Lab:   return &CMLLuvtoLab;
      case CML_COLOR_Lch:   return &CMLLuvtoLch;
      case CML_COLOR_Luv:   return &CMLLuvtoLuv;
      case CML_COLOR_RGB:   return &CMLLuvtoRGB;
      case CML_COLOR_YCbCr: return &CMLLuvtoYCbCr;
      case CML_COLOR_HSV:   return &CMLLuvtoHSV;
      case CML_COLOR_HSL:   return &CMLLuvtoHSL;
      case CML_COLOR_CMYK:  return &CMLLuvtoCMYK;
      default: break;
    }
  case CML_COLOR_RGB:
    switch(outputSystem){
      case CML_COLOR_GRAY:  return &CMLRGBtoGray;
      case CML_COLOR_XYZ:   return &CMLRGBtoXYZ;
      case CML_COLOR_Yxy:   return &CMLRGBtoYxy;
      case CML_COLOR_Yuv:   return &CMLRGBtoYuv;
      case CML_COLOR_Yupvp: return &CMLRGBtoYupvp;
      case CML_COLOR_Lab:   return &CMLRGBtoLab;
      case CML_COLOR_Lch:   return &CMLRGBtoLch;
      case CML_COLOR_Luv:   return &CMLRGBtoLuv;
      case CML_COLOR_RGB:   return &CMLRGBtoRGB;
      case CML_COLOR_YCbCr: return &CMLRGBtoYCbCr;
      case CML_COLOR_HSV:   return &CMLRGBtoHSV;
      case CML_COLOR_HSL:   return &CMLRGBtoHSL;
      case CML_COLOR_CMYK:  return &CMLRGBtoCMYK;
      default: break;
    }
  case CML_COLOR_YCbCr:
    switch(outputSystem){
      case CML_COLOR_GRAY:  return &CMLYCbCrtoGray;
      case CML_COLOR_XYZ:   return &CMLYCbCrtoXYZ;
      case CML_COLOR_Yxy:   return &CMLYCbCrtoYxy;
      case CML_COLOR_Yuv:   return &CMLYCbCrtoYuv;
      case CML_COLOR_Yupvp: return &CMLYCbCrtoYupvp;
      case CML_COLOR_Lab:   return &CMLYCbCrtoLab;
      case CML_COLOR_Lch:   return &CMLYCbCrtoLch;
      case CML_COLOR_Luv:   return &CMLYCbCrtoLuv;
      case CML_COLOR_RGB:   return &CMLYCbCrtoRGB;
      case CML_COLOR_YCbCr: return &CMLYCbCrtoYCbCr;
      case CML_COLOR_HSV:   return &CMLYCbCrtoHSV;
      case CML_COLOR_HSL:   return &CMLYCbCrtoHSL;
      case CML_COLOR_CMYK:  return &CMLYCbCrtoCMYK;
      default: break;
    }
  case CML_COLOR_HSV:
    switch(outputSystem){
      case CML_COLOR_GRAY:  return &CMLHSVtoGray;
      case CML_COLOR_XYZ:   return &CMLHSVtoXYZ;
      case CML_COLOR_Yxy:   return &CMLHSVtoYxy;
      case CML_COLOR_Yuv:   return &CMLHSVtoYuv;
      case CML_COLOR_Yupvp: return &CMLHSVtoYupvp;
      case CML_COLOR_Lab:   return &CMLHSVtoLab;
      case CML_COLOR_Lch:   return &CMLHSVtoLch;
      case CML_COLOR_Luv:   return &CMLHSVtoLuv;
      case CML_COLOR_RGB:   return &CMLHSVtoRGB;
      case CML_COLOR_YCbCr: return &CMLHSVtoYCbCr;
      case CML_COLOR_HSV:   return &CMLHSVtoHSV;
      case CML_COLOR_HSL:   return &CMLHSVtoHSL;
      case CML_COLOR_CMYK:  return &CMLHSVtoCMYK;
      default: break;
    }
  case CML_COLOR_HSL:
    switch(outputSystem){
      case CML_COLOR_GRAY:  return &CMLHSLtoGray;
      case CML_COLOR_XYZ:   return &CMLHSLtoXYZ;
      case CML_COLOR_Yxy:   return &CMLHSLtoYxy;
      case CML_COLOR_Yuv:   return &CMLHSLtoYuv;
      case CML_COLOR_Yupvp: return &CMLHSLtoYupvp;
      case CML_COLOR_Lab:   return &CMLHSLtoLab;
      case CML_COLOR_Lch:   return &CMLHSLtoLch;
      case CML_COLOR_Luv:   return &CMLHSLtoLuv;
      case CML_COLOR_RGB:   return &CMLHSLtoRGB;
      case CML_COLOR_YCbCr: return &CMLHSLtoYCbCr;
      case CML_COLOR_HSV:   return &CMLHSLtoHSV;
      case CML_COLOR_HSL:   return &CMLHSLtoHSL;
      case CML_COLOR_CMYK:  return &CMLHSLtoCMYK;
      default: break;
    }
  case CML_COLOR_CMYK:
    switch(outputSystem){
      case CML_COLOR_GRAY:  return &CMLCMYKtoGray;
      case CML_COLOR_XYZ:   return &CMLCMYKtoXYZ;
      case CML_COLOR_Yxy:   return &CMLCMYKtoYxy;
      case CML_COLOR_Yuv:   return &CMLCMYKtoYuv;
      case CML_COLOR_Yupvp: return &CMLCMYKtoYupvp;
      case CML_COLOR_Lab:   return &CMLCMYKtoLab;
      case CML_COLOR_Lch:   return &CMLCMYKtoLch;
      case CML_COLOR_Luv:   return &CMLCMYKtoLuv;
      case CML_COLOR_RGB:   return &CMLCMYKtoRGB;
      case CML_COLOR_YCbCr: return &CMLCMYKtoYCbCr;
      case CML_COLOR_HSV:   return &CMLCMYKtoHSV;
      case CML_COLOR_HSL:   return &CMLCMYKtoHSL;
      case CML_COLOR_CMYK:  return &CMLCMYKtoCMYK;
      default: break;
    }
  case CML_COLOR_SPECTRUM_ILLUMINATION:
    switch(outputSystem){
      case CML_COLOR_GRAY:  return &CMLSpectrumIlluminationtoGray;
      case CML_COLOR_XYZ:   return &CMLSpectrumIlluminationtoXYZ;
      case CML_COLOR_Yxy:   return &CMLSpectrumIlluminationtoYxy;
      case CML_COLOR_Yuv:   return &CMLSpectrumIlluminationtoYuv;
      case CML_COLOR_Yupvp: return &CMLSpectrumIlluminationtoYupvp;
      case CML_COLOR_Lab:   return &CMLSpectrumIlluminationtoLab;
      case CML_COLOR_Lch:   return &CMLSpectrumIlluminationtoLch;
      case CML_COLOR_Luv:   return &CMLSpectrumIlluminationtoLuv;
      case CML_COLOR_RGB:   return &CMLSpectrumIlluminationtoRGB;
      case CML_COLOR_YCbCr: return &CMLSpectrumIlluminationtoYCbCr;
      case CML_COLOR_HSV:   return &CMLSpectrumIlluminationtoHSV;
      case CML_COLOR_HSL:   return &CMLSpectrumIlluminationtoHSL;
      case CML_COLOR_CMYK:  return &CMLSpectrumIlluminationtoCMYK;
      default: break;
    }
  case CML_COLOR_SPECTRUM_REMISSION:
    switch(outputSystem){
      case CML_COLOR_GRAY:  return &CMLSpectrumRemissiontoGray;
      case CML_COLOR_XYZ:   return &CMLSpectrumRemissiontoXYZ;
      case CML_COLOR_Yxy:   return &CMLSpectrumRemissiontoYxy;
      case CML_COLOR_Yuv:   return &CMLSpectrumRemissiontoYuv;
      case CML_COLOR_Yupvp: return &CMLSpectrumRemissiontoYupvp;
      case CML_COLOR_Lab:   return &CMLSpectrumRemissiontoLab;
      case CML_COLOR_Lch:   return &CMLSpectrumRemissiontoLch;
      case CML_COLOR_Luv:   return &CMLSpectrumRemissiontoLuv;
      case CML_COLOR_RGB:   return &CMLSpectrumRemissiontoRGB;
      case CML_COLOR_YCbCr: return &CMLSpectrumRemissiontoYCbCr;
      case CML_COLOR_HSV:   return &CMLSpectrumRemissiontoHSV;
      case CML_COLOR_HSL:   return &CMLSpectrumRemissiontoHSL;
      case CML_COLOR_CMYK:  return &CMLSpectrumRemissiontoCMYK;
      default: break;
    }
  default:
    #ifndef NDEBUG
      cmlError("Input-ColorType unknown.");
    #endif
    return CML_NULL; break;
  }
  // Reaching here, a default inside the inner switch has been reached.
  #ifndef NDEBUG
    cmlError("Output-ColorType unknown.");
  #endif
  return CML_NULL;
}

CML_DEF CMLNormedConverter cmlGetNormedInputConverter(CMLColorType colorType){
  switch(colorType){
    case CML_COLOR_GRAY:  return &cmlGrayWithNormedInput;
    case CML_COLOR_XYZ:   return &cmlXYZWithNormedInput;
    case CML_COLOR_Yxy:   return &cmlYxyWithNormedInput;
    case CML_COLOR_Yuv:   return &cmlYuvWithNormedInput;
    case CML_COLOR_Yupvp: return &cmlYupvpWithNormedInput;
    case CML_COLOR_Lab:   return &cmlLabWithNormedInput;
    case CML_COLOR_Lch:   return &cmlLchWithNormedInput;
    case CML_COLOR_Luv:   return &cmlLuvWithNormedInput;
    case CML_COLOR_RGB:   return &cmlRGBWithNormedInput;
    case CML_COLOR_YCbCr: return &cmlYCbCrWithNormedInput;
    case CML_COLOR_HSV:   return &cmlHSVWithNormedInput;
    case CML_COLOR_HSL:   return &cmlHSLWithNormedInput;
    case CML_COLOR_CMYK:  return &cmlCMYKWithNormedInput;
    default: break;
  }
  #ifndef NDEBUG
    cmlError("ColorType unknown.");
  #endif
  return CML_NULL;
}

CML_DEF CMLNormedConverter cmlGetNormedOutputConverter(CMLColorType colorType){
  switch(colorType){
    case CML_COLOR_GRAY:  return &cmlNormedOutputWithGray;
    case CML_COLOR_XYZ:   return &cmlNormedOutputWithXYZ;
    case CML_COLOR_Yxy:   return &cmlNormedOutputWithYxy;
    case CML_COLOR_Yuv:   return &cmlNormedOutputWithYuv;
    case CML_COLOR_Yupvp: return &cmlNormedOutputWithYupvp;
    case CML_COLOR_Lab:   return &cmlNormedOutputWithLab;
    case CML_COLOR_Lch:   return &cmlNormedOutputWithLch;
    case CML_COLOR_Luv:   return &cmlNormedOutputWithLuv;
    case CML_COLOR_RGB:   return &cmlNormedOutputWithRGB;
    case CML_COLOR_YCbCr: return &cmlNormedOutputWithYCbCr;
    case CML_COLOR_HSV:   return &cmlNormedOutputWithHSV;
    case CML_COLOR_HSL:   return &cmlNormedOutputWithHSL;
    case CML_COLOR_CMYK:  return &cmlNormedOutputWithCMYK;
    default: break;
  }
  #ifndef NDEBUG
    cmlError("ColorType unknown.");
  #endif
  return CML_NULL;
}

CML_DEF CMLNormedConverter cmlGetNormedCartesianInputConverter(CMLColorType colorType){
  switch(colorType){
    case CML_COLOR_GRAY:  return &cmlGrayWithNormedInput;
    case CML_COLOR_XYZ:   return &cmlXYZWithNormedInput;
    case CML_COLOR_Yxy:   return &cmlYxyWithNormedInput;
    case CML_COLOR_Yuv:   return &cmlYuvWithNormedInput;
    case CML_COLOR_Yupvp: return &cmlYupvpWithNormedInput;
    case CML_COLOR_Lab:   return &cmlLabWithNormedInput;
    case CML_COLOR_Lch:   return &cmlLchWithNormedCartesianInput;
    case CML_COLOR_Luv:   return &cmlLuvWithNormedInput;
    case CML_COLOR_RGB:   return &cmlRGBWithNormedInput;
    case CML_COLOR_YCbCr: return &cmlYCbCrWithNormedInput;
    case CML_COLOR_HSV:   return &cmlHSVWithNormedCartesianInput;
    case CML_COLOR_HSL:   return &cmlHSLWithNormedCartesianInput;
    case CML_COLOR_CMYK:  return &cmlCMYKWithNormedInput;
    default: break;
  }
  #ifndef NDEBUG
    cmlError("ColorType unknown.");
  #endif
  return CML_NULL;
}

CML_DEF CMLNormedConverter cmlGetNormedCartesianOutputConverter(CMLColorType colorType){
  switch(colorType){
    case CML_COLOR_GRAY:  return &cmlNormedOutputWithGray;
    case CML_COLOR_XYZ:   return &cmlNormedOutputWithXYZ;
    case CML_COLOR_Yxy:   return &cmlNormedOutputWithYxy;
    case CML_COLOR_Yuv:   return &cmlNormedOutputWithYuv;
    case CML_COLOR_Yupvp: return &cmlNormedOutputWithYupvp;
    case CML_COLOR_Lab:   return &cmlNormedOutputWithLab;
    case CML_COLOR_Lch:   return &cmlNormedCartesianOutputWithLch;
    case CML_COLOR_Luv:   return &cmlNormedOutputWithLuv;
    case CML_COLOR_RGB:   return &cmlNormedOutputWithRGB;
    case CML_COLOR_YCbCr: return &cmlNormedOutputWithYCbCr;
    case CML_COLOR_HSV:   return &cmlNormedCartesianOutputWithHSV;
    case CML_COLOR_HSL:   return &cmlNormedCartesianOutputWithHSL;
    case CML_COLOR_CMYK:  return &cmlNormedOutputWithCMYK;
    default: break;
  }
  #ifndef NDEBUG
    cmlError("ColorType unknown.");
  #endif
  return CML_NULL;
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

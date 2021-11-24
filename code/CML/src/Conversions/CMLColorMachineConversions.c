
#include "../CML.h"
#include "../StateMachine/CMLColorMachineState.h"


CML_API CMLColorConverter CMLgetColorConverter(CMLColorType outputsystem, CMLColorType inputsystem){
  switch(inputsystem){
  case CML_COLOR_GRAY:
    switch(outputsystem){
      case CML_COLOR_GRAY:  return &CMLGraytoGray; break;
      case CML_COLOR_XYZ:   return &CMLGraytoXYZ; break;
      case CML_COLOR_Yxy:   return &CMLGraytoYxy; break;
      case CML_COLOR_Yuv:   return &CMLGraytoYuv; break;
      case CML_COLOR_Yupvp: return &CMLGraytoYupvp; break;
      case CML_COLOR_Lab:   return &CMLGraytoLab; break;
      case CML_COLOR_Lch:   return &CMLGraytoLch; break;
      case CML_COLOR_Luv:   return &CMLGraytoLuv; break;
      case CML_COLOR_RGB:   return &CMLGraytoRGB; break;
      case CML_COLOR_YCbCr: return &CMLGraytoYCbCr; break;
      case CML_COLOR_HSV:   return &CMLGraytoHSV; break;
      case CML_COLOR_HSL:   return &CMLGraytoHSL; break;
      case CML_COLOR_CMYK:  return &CMLGraytoCMYK; break;
      default: break;
    }
  case CML_COLOR_XYZ:
    switch(outputsystem){
      case CML_COLOR_GRAY:  return &CMLXYZtoGray; break;
      case CML_COLOR_XYZ:   return &CMLXYZtoXYZ; break;
      case CML_COLOR_Yxy:   return &CMLXYZtoYxy; break;
      case CML_COLOR_Yuv:   return &CMLXYZtoYuv; break;
      case CML_COLOR_Yupvp: return &CMLXYZtoYupvp; break;
      case CML_COLOR_Lab:   return &CMLXYZtoLab; break;
      case CML_COLOR_Lch:   return &CMLXYZtoLch; break;
      case CML_COLOR_Luv:   return &CMLXYZtoLuv; break;
      case CML_COLOR_RGB:   return &CMLXYZtoRGB; break;
      case CML_COLOR_YCbCr: return &CMLXYZtoYCbCr; break;
      case CML_COLOR_HSV:   return &CMLXYZtoHSV; break;
      case CML_COLOR_HSL:   return &CMLXYZtoHSL; break;
      case CML_COLOR_CMYK:  return &CMLXYZtoCMYK; break;
      default: break;
    }
  case CML_COLOR_Yxy:
    switch(outputsystem){
      case CML_COLOR_GRAY:  return &CMLYxytoGray; break;
      case CML_COLOR_XYZ:   return &CMLYxytoXYZ; break;
      case CML_COLOR_Yxy:   return &CMLYxytoYxy; break;
      case CML_COLOR_Yuv:   return &CMLYxytoYuv; break;
      case CML_COLOR_Yupvp: return &CMLYxytoYupvp; break;
      case CML_COLOR_Lab:   return &CMLYxytoLab; break;
      case CML_COLOR_Lch:   return &CMLYxytoLch; break;
      case CML_COLOR_Luv:   return &CMLYxytoLuv; break;
      case CML_COLOR_RGB:   return &CMLYxytoRGB; break;
      case CML_COLOR_YCbCr: return &CMLYxytoYCbCr; break;
      case CML_COLOR_HSV:   return &CMLYxytoHSV; break;
      case CML_COLOR_HSL:   return &CMLYxytoHSL; break;
      case CML_COLOR_CMYK:  return &CMLYxytoCMYK; break;
      default: break;
    }
  case CML_COLOR_Yuv:
    switch(outputsystem){
      case CML_COLOR_GRAY:  return &CMLYuvtoGray; break;
      case CML_COLOR_XYZ:   return &CMLYuvtoXYZ; break;
      case CML_COLOR_Yxy:   return &CMLYuvtoYxy; break;
      case CML_COLOR_Yuv:   return &CMLYuvtoYuv; break;
      case CML_COLOR_Yupvp: return &CMLYuvtoYupvp; break;
      case CML_COLOR_Lab:   return &CMLYuvtoLab; break;
      case CML_COLOR_Lch:   return &CMLYuvtoLch; break;
      case CML_COLOR_Luv:   return &CMLYuvtoLuv; break;
      case CML_COLOR_RGB:   return &CMLYuvtoRGB; break;
      case CML_COLOR_YCbCr: return &CMLYuvtoYCbCr; break;
      case CML_COLOR_HSV:   return &CMLYuvtoHSV; break;
      case CML_COLOR_HSL:   return &CMLYuvtoHSL; break;
      case CML_COLOR_CMYK:  return &CMLYuvtoCMYK; break;
      default: break;
    }
  case CML_COLOR_Yupvp:
    switch(outputsystem){
      case CML_COLOR_GRAY:  return &CMLYupvptoGray; break;
      case CML_COLOR_XYZ:   return &CMLYupvptoXYZ; break;
      case CML_COLOR_Yxy:   return &CMLYupvptoYxy; break;
      case CML_COLOR_Yuv:   return &CMLYupvptoYuv; break;
      case CML_COLOR_Yupvp: return &CMLYupvptoYupvp; break;
      case CML_COLOR_Lab:   return &CMLYupvptoLab; break;
      case CML_COLOR_Lch:   return &CMLYupvptoLch; break;
      case CML_COLOR_Luv:   return &CMLYupvptoLuv; break;
      case CML_COLOR_RGB:   return &CMLYupvptoRGB; break;
      case CML_COLOR_YCbCr: return &CMLYupvptoYCbCr; break;
      case CML_COLOR_HSV:   return &CMLYupvptoHSV; break;
      case CML_COLOR_HSL:   return &CMLYupvptoHSL; break;
      case CML_COLOR_CMYK:  return &CMLYupvptoCMYK; break;
      default: break;
    }
  case CML_COLOR_Lab:
    switch(outputsystem){
      case CML_COLOR_GRAY:  return &CMLLabtoGray; break;
      case CML_COLOR_XYZ:   return &CMLLabtoXYZ; break;
      case CML_COLOR_Yxy:   return &CMLLabtoYxy; break;
      case CML_COLOR_Yuv:   return &CMLLabtoYuv; break;
      case CML_COLOR_Yupvp: return &CMLLabtoYupvp; break;
      case CML_COLOR_Lab:   return &CMLLabtoLab; break;
      case CML_COLOR_Lch:   return &CMLLabtoLch; break;
      case CML_COLOR_Luv:   return &CMLLabtoLuv; break;
      case CML_COLOR_RGB:   return &CMLLabtoRGB; break;
      case CML_COLOR_YCbCr: return &CMLLabtoYCbCr; break;
      case CML_COLOR_HSV:   return &CMLLabtoHSV; break;
      case CML_COLOR_HSL:   return &CMLLabtoHSL; break;
      case CML_COLOR_CMYK:  return &CMLLabtoCMYK; break;
      default: break;
    }
  case CML_COLOR_Lch:
    switch(outputsystem){
      case CML_COLOR_GRAY:  return &CMLLchtoGray; break;
      case CML_COLOR_XYZ:   return &CMLLchtoXYZ; break;
      case CML_COLOR_Yxy:   return &CMLLchtoYxy; break;
      case CML_COLOR_Yuv:   return &CMLLchtoYuv; break;
      case CML_COLOR_Yupvp: return &CMLLchtoYupvp; break;
      case CML_COLOR_Lab:   return &CMLLchtoLab; break;
      case CML_COLOR_Lch:   return &CMLLchtoLch; break;
      case CML_COLOR_Luv:   return &CMLLchtoLuv; break;
      case CML_COLOR_RGB:   return &CMLLchtoRGB; break;
      case CML_COLOR_YCbCr: return &CMLLchtoYCbCr; break;
      case CML_COLOR_HSV:   return &CMLLchtoHSV; break;
      case CML_COLOR_HSL:   return &CMLLchtoHSL; break;
      case CML_COLOR_CMYK:  return &CMLLchtoCMYK; break;
      default: break;
    }
  case CML_COLOR_Luv:
    switch(outputsystem){
      case CML_COLOR_GRAY:  return &CMLLuvtoGray; break;
      case CML_COLOR_XYZ:   return &CMLLuvtoXYZ; break;
      case CML_COLOR_Yxy:   return &CMLLuvtoYxy; break;
      case CML_COLOR_Yuv:   return &CMLLuvtoYuv; break;
      case CML_COLOR_Yupvp: return &CMLLuvtoYupvp; break;
      case CML_COLOR_Lab:   return &CMLLuvtoLab; break;
      case CML_COLOR_Lch:   return &CMLLuvtoLch; break;
      case CML_COLOR_Luv:   return &CMLLuvtoLuv; break;
      case CML_COLOR_RGB:   return &CMLLuvtoRGB; break;
      case CML_COLOR_YCbCr: return &CMLLuvtoYCbCr; break;
      case CML_COLOR_HSV:   return &CMLLuvtoHSV; break;
      case CML_COLOR_HSL:   return &CMLLuvtoHSL; break;
      case CML_COLOR_CMYK:  return &CMLLuvtoCMYK; break;
      default: break;
    }
  case CML_COLOR_RGB:
    switch(outputsystem){
      case CML_COLOR_GRAY:  return &CMLRGBtoGray; break;
      case CML_COLOR_XYZ:   return &CMLRGBtoXYZ; break;
      case CML_COLOR_Yxy:   return &CMLRGBtoYxy; break;
      case CML_COLOR_Yuv:   return &CMLRGBtoYuv; break;
      case CML_COLOR_Yupvp: return &CMLRGBtoYupvp; break;
      case CML_COLOR_Lab:   return &CMLRGBtoLab; break;
      case CML_COLOR_Lch:   return &CMLRGBtoLch; break;
      case CML_COLOR_Luv:   return &CMLRGBtoLuv; break;
      case CML_COLOR_RGB:   return &CMLRGBtoRGB; break;
      case CML_COLOR_YCbCr: return &CMLRGBtoYCbCr; break;
      case CML_COLOR_HSV:   return &CMLRGBtoHSV; break;
      case CML_COLOR_HSL:   return &CMLRGBtoHSL; break;
      case CML_COLOR_CMYK:  return &CMLRGBtoCMYK; break;
      default: break;
    }
  case CML_COLOR_YCbCr:
    switch(outputsystem){
      case CML_COLOR_GRAY:  return &CMLYCbCrtoGray; break;
      case CML_COLOR_XYZ:   return &CMLYCbCrtoXYZ; break;
      case CML_COLOR_Yxy:   return &CMLYCbCrtoYxy; break;
      case CML_COLOR_Yuv:   return &CMLYCbCrtoYuv; break;
      case CML_COLOR_Yupvp: return &CMLYCbCrtoYupvp; break;
      case CML_COLOR_Lab:   return &CMLYCbCrtoLab; break;
      case CML_COLOR_Lch:   return &CMLYCbCrtoLch; break;
      case CML_COLOR_Luv:   return &CMLYCbCrtoLuv; break;
      case CML_COLOR_RGB:   return &CMLYCbCrtoRGB; break;
      case CML_COLOR_YCbCr: return &CMLYCbCrtoYCbCr; break;
      case CML_COLOR_HSV:   return &CMLYCbCrtoHSV; break;
      case CML_COLOR_HSL:   return &CMLYCbCrtoHSL; break;
      case CML_COLOR_CMYK:  return &CMLYCbCrtoCMYK; break;
      default: break;
    }
  case CML_COLOR_HSV:
    switch(outputsystem){
      case CML_COLOR_GRAY:  return &CMLHSVtoGray; break;
      case CML_COLOR_XYZ:   return &CMLHSVtoXYZ; break;
      case CML_COLOR_Yxy:   return &CMLHSVtoYxy; break;
      case CML_COLOR_Yuv:   return &CMLHSVtoYuv; break;
      case CML_COLOR_Yupvp: return &CMLHSVtoYupvp; break;
      case CML_COLOR_Lab:   return &CMLHSVtoLab; break;
      case CML_COLOR_Lch:   return &CMLHSVtoLch; break;
      case CML_COLOR_Luv:   return &CMLHSVtoLuv; break;
      case CML_COLOR_RGB:   return &CMLHSVtoRGB; break;
      case CML_COLOR_YCbCr: return &CMLHSVtoYCbCr; break;
      case CML_COLOR_HSV:   return &CMLHSVtoHSV; break;
      case CML_COLOR_HSL:   return &CMLHSVtoHSL; break;
      case CML_COLOR_CMYK:  return &CMLHSVtoCMYK; break;
      default: break;
    }
  case CML_COLOR_HSL:
    switch(outputsystem){
      case CML_COLOR_GRAY:  return &CMLHSLtoGray; break;
      case CML_COLOR_XYZ:   return &CMLHSLtoXYZ; break;
      case CML_COLOR_Yxy:   return &CMLHSLtoYxy; break;
      case CML_COLOR_Yuv:   return &CMLHSLtoYuv; break;
      case CML_COLOR_Yupvp: return &CMLHSLtoYupvp; break;
      case CML_COLOR_Lab:   return &CMLHSLtoLab; break;
      case CML_COLOR_Lch:   return &CMLHSLtoLch; break;
      case CML_COLOR_Luv:   return &CMLHSLtoLuv; break;
      case CML_COLOR_RGB:   return &CMLHSLtoRGB; break;
      case CML_COLOR_YCbCr: return &CMLHSLtoYCbCr; break;
      case CML_COLOR_HSV:   return &CMLHSLtoHSV; break;
      case CML_COLOR_HSL:   return &CMLHSLtoHSL; break;
      case CML_COLOR_CMYK:  return &CMLHSLtoCMYK; break;
      default: break;
    }
  case CML_COLOR_SPECTRUM_ILLUMINATION:
    switch(outputsystem){
      case CML_COLOR_GRAY:  return &CMLSpectrumIlluminationtoGray; break;
      case CML_COLOR_XYZ:   return &CMLSpectrumIlluminationtoXYZ; break;
      case CML_COLOR_Yxy:   return &CMLSpectrumIlluminationtoYxy; break;
      case CML_COLOR_Yuv:   return &CMLSpectrumIlluminationtoYuv; break;
      case CML_COLOR_Yupvp: return &CMLSpectrumIlluminationtoYupvp; break;
      case CML_COLOR_Lab:   return &CMLSpectrumIlluminationtoLab; break;
      case CML_COLOR_Lch:   return &CMLSpectrumIlluminationtoLch; break;
      case CML_COLOR_Luv:   return &CMLSpectrumIlluminationtoLuv; break;
      case CML_COLOR_RGB:   return &CMLSpectrumIlluminationtoRGB; break;
      case CML_COLOR_YCbCr: return &CMLSpectrumIlluminationtoYCbCr; break;
      case CML_COLOR_HSV:   return &CMLSpectrumIlluminationtoHSV; break;
      case CML_COLOR_HSL:   return &CMLSpectrumIlluminationtoHSL; break;
      case CML_COLOR_CMYK:  return &CMLSpectrumIlluminationtoCMYK; break;
      default: break;
    }
  case CML_COLOR_SPECTRUM_REMISSION:
    switch(outputsystem){
      case CML_COLOR_GRAY:  return &CMLSpectrumRemissiontoGray; break;
      case CML_COLOR_XYZ:   return &CMLSpectrumRemissiontoXYZ; break;
      case CML_COLOR_Yxy:   return &CMLSpectrumRemissiontoYxy; break;
      case CML_COLOR_Yuv:   return &CMLSpectrumRemissiontoYuv; break;
      case CML_COLOR_Yupvp: return &CMLSpectrumRemissiontoYupvp; break;
      case CML_COLOR_Lab:   return &CMLSpectrumRemissiontoLab; break;
      case CML_COLOR_Lch:   return &CMLSpectrumRemissiontoLch; break;
      case CML_COLOR_Luv:   return &CMLSpectrumRemissiontoLuv; break;
      case CML_COLOR_RGB:   return &CMLSpectrumRemissiontoRGB; break;
      case CML_COLOR_YCbCr: return &CMLSpectrumRemissiontoYCbCr; break;
      case CML_COLOR_HSV:   return &CMLSpectrumRemissiontoHSV; break;
      case CML_COLOR_HSL:   return &CMLSpectrumRemissiontoHSL; break;
      case CML_COLOR_CMYK:  return &CMLSpectrumRemissiontoCMYK; break;
      default: break;
    }
  case CML_COLOR_CMYK:
    switch(outputsystem){
      case CML_COLOR_GRAY:  return &CMLCMYKtoGray; break;
      case CML_COLOR_XYZ:   return &CMLCMYKtoXYZ; break;
      case CML_COLOR_Yxy:   return &CMLCMYKtoYxy; break;
      case CML_COLOR_Yuv:   return &CMLCMYKtoYuv; break;
      case CML_COLOR_Yupvp: return &CMLCMYKtoYupvp; break;
      case CML_COLOR_Lab:   return &CMLCMYKtoLab; break;
      case CML_COLOR_Lch:   return &CMLCMYKtoLch; break;
      case CML_COLOR_Luv:   return &CMLCMYKtoLuv; break;
      case CML_COLOR_RGB:   return &CMLCMYKtoRGB; break;
      case CML_COLOR_YCbCr: return &CMLCMYKtoYCbCr; break;
      case CML_COLOR_HSV:   return &CMLCMYKtoHSV; break;
      case CML_COLOR_HSL:   return &CMLCMYKtoHSL; break;
      case CML_COLOR_CMYK:  return &CMLCMYKtoCMYK; break;
      default: break;
    }
  default:
    #ifndef NDEBUG
      cmlError("CMLgetColorConverter", "Input-ColorType unknown.");
    #endif
    return CML_NULL; break;
  }
  // Reaching here, a default inside the inner switch has been reached.
  #ifndef NDEBUG
    cmlError("CMLgetColorConverter", "Output-ColorType unknown.");
  #endif
  return CML_NULL;
}

CML_API CMLNormedConverter CMLgetNormedInputConverter(CMLColorType colortype){
  switch(colortype){
    case CML_COLOR_GRAY:  return &cmlGrayWithNormedInput; break;
    case CML_COLOR_XYZ:   return &cmlXYZWithNormedInput; break;
    case CML_COLOR_Yxy:   return &cmlYxyWithNormedInput; break;
    case CML_COLOR_Yuv:   return &cmlYuvWithNormedInput; break;
    case CML_COLOR_Yupvp: return &cmlYupvpWithNormedInput; break;
    case CML_COLOR_Lab:   return &cmlLabWithNormedInput; break;
    case CML_COLOR_Lch:   return &cmlLchWithNormedInput; break;
    case CML_COLOR_Luv:   return &cmlLuvWithNormedInput; break;
    case CML_COLOR_RGB:   return &cmlRGBWithNormedInput; break;
    case CML_COLOR_YCbCr: return &cmlYCbCrWithNormedInput; break;
    case CML_COLOR_HSV:   return &cmlHSVWithNormedInput; break;
    case CML_COLOR_HSL:   return &cmlHSLWithNormedInput; break;
    case CML_COLOR_CMYK:  return &cmlCMYKWithNormedInput; break;
    default: break;
  }
  #ifndef NDEBUG
    cmlError("CMLgetNormedInputConverter", "ColorType unknown.");
  #endif
  return CML_NULL;
}

CML_API CMLNormedConverter CMLgetNormedOutputConverter(CMLColorType colortype){
  switch(colortype){
    case CML_COLOR_GRAY:  return &cmlNormedOutputWithGray; break;
    case CML_COLOR_XYZ:   return &cmlNormedOutputWithXYZ; break;
    case CML_COLOR_Yxy:   return &cmlNormedOutputWithYxy; break;
    case CML_COLOR_Yuv:   return &cmlNormedOutputWithYuv; break;
    case CML_COLOR_Yupvp: return &cmlNormedOutputWithYupvp; break;
    case CML_COLOR_Lab:   return &cmlNormedOutputWithLab; break;
    case CML_COLOR_Lch:   return &cmlNormedOutputWithLch; break;
    case CML_COLOR_Luv:   return &cmlNormedOutputWithLuv; break;
    case CML_COLOR_RGB:   return &cmlNormedOutputWithRGB; break;
    case CML_COLOR_YCbCr: return &cmlNormedOutputWithYCbCr; break;
    case CML_COLOR_HSV:   return &cmlNormedOutputWithHSV; break;
    case CML_COLOR_HSL:   return &cmlNormedOutputWithHSL; break;
    case CML_COLOR_CMYK:  return &cmlNormedOutputWithCMYK; break;
    default: break;
  }
  #ifndef NDEBUG
    cmlError("CMLgetNormedOutputConverter", "ColorType unknown.");
  #endif
  return CML_NULL;
}

CML_API CMLNormedConverter CMLgetNormedCartesianInputConverter(CMLColorType colortype){
  switch(colortype){
    case CML_COLOR_GRAY:  return &cmlGrayWithNormedInput; break;
    case CML_COLOR_XYZ:   return &cmlXYZWithNormedInput; break;
    case CML_COLOR_Yxy:   return &cmlYxyWithNormedInput; break;
    case CML_COLOR_Yuv:   return &cmlYuvWithNormedInput; break;
    case CML_COLOR_Yupvp: return &cmlYupvpWithNormedInput; break;
    case CML_COLOR_Lab:   return &cmlLabWithNormedInput; break;
    case CML_COLOR_Lch:   return &cmlLchWithNormedCartesianInput; break;
    case CML_COLOR_Luv:   return &cmlLuvWithNormedInput; break;
    case CML_COLOR_RGB:   return &cmlRGBWithNormedInput; break;
    case CML_COLOR_YCbCr: return &cmlYCbCrWithNormedInput; break;
    case CML_COLOR_HSV:   return &cmlHSVWithNormedCartesianInput; break;
    case CML_COLOR_HSL:   return &cmlHSLWithNormedCartesianInput; break;
    case CML_COLOR_CMYK:  return &cmlCMYKWithNormedInput; break;
    default: break;
  }
  #ifndef NDEBUG
    cmlError("CMLgetNormedCartesianInputConverter", "ColorType unknown.");
  #endif
  return CML_NULL;
}

CML_API CMLNormedConverter CMLgetNormedCartesianOutputConverter(CMLColorType colortype){
  switch(colortype){
    case CML_COLOR_GRAY:  return &cmlNormedOutputWithGray; break;
    case CML_COLOR_XYZ:   return &cmlNormedOutputWithXYZ; break;
    case CML_COLOR_Yxy:   return &cmlNormedOutputWithYxy; break;
    case CML_COLOR_Yuv:   return &cmlNormedOutputWithYuv; break;
    case CML_COLOR_Yupvp: return &cmlNormedOutputWithYupvp; break;
    case CML_COLOR_Lab:   return &cmlNormedOutputWithLab; break;
    case CML_COLOR_Lch:   return &cmlNormedCartesianOutputWithLch; break;
    case CML_COLOR_Luv:   return &cmlNormedOutputWithLuv; break;
    case CML_COLOR_RGB:   return &cmlNormedOutputWithRGB; break;
    case CML_COLOR_YCbCr: return &cmlNormedOutputWithYCbCr; break;
    case CML_COLOR_HSV:   return &cmlNormedCartesianOutputWithHSV; break;
    case CML_COLOR_HSL:   return &cmlNormedCartesianOutputWithHSL; break;
    case CML_COLOR_CMYK:  return &cmlNormedOutputWithCMYK; break;
    default: break;
  }
  #ifndef NDEBUG
    cmlError("CMLgetNormedCartesianOutputConverter", "ColorType unknown.");
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

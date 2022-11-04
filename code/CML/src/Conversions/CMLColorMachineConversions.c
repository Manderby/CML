
#include "../CML.h"
#include "../Internal/CMLColorMachineState.h"



CML_DEF CMLColorConverter cmlGetColorConverter(CMLColorType outputSystem, CMLColorType inputSystem){
  switch(inputSystem){
  case CML_COLOR_GRAY:
    switch(outputSystem){
      case CML_COLOR_GRAY:  return &cmlGrayToGray;
      case CML_COLOR_XYZ:   return &cmlGrayToXYZ;
      case CML_COLOR_Yxy:   return &cmlGrayToYxy;
      case CML_COLOR_Yuv:   return &cmlGrayToYuv;
      case CML_COLOR_Yupvp: return &cmlGrayToYupvp;
      case CML_COLOR_Lab:   return &cmlGrayToLab;
      case CML_COLOR_Lch:   return &cmlGrayToLch;
      case CML_COLOR_Luv:   return &cmlGrayToLuv;
      case CML_COLOR_RGB:   return &cmlGrayToRGB;
      case CML_COLOR_YCbCr: return &cmlGrayToYCbCr;
      case CML_COLOR_HSV:   return &cmlGrayToHSV;
      case CML_COLOR_HSL:   return &cmlGrayToHSL;
      case CML_COLOR_CMYK:  return &cmlGrayToCMYK;
      default: break;
    }
  case CML_COLOR_XYZ:
    switch(outputSystem){
      case CML_COLOR_GRAY:  return &cmlXYZToGray;
      case CML_COLOR_XYZ:   return &cmlXYZToXYZ;
      case CML_COLOR_Yxy:   return &cmlXYZToYxy;
      case CML_COLOR_Yuv:   return &cmlXYZToYuv;
      case CML_COLOR_Yupvp: return &cmlXYZToYupvp;
      case CML_COLOR_Lab:   return &cmlXYZToLab;
      case CML_COLOR_Lch:   return &cmlXYZToLch;
      case CML_COLOR_Luv:   return &cmlXYZToLuv;
      case CML_COLOR_RGB:   return &cmlXYZToRGB;
      case CML_COLOR_YCbCr: return &cmlXYZToYCbCr;
      case CML_COLOR_HSV:   return &cmlXYZToHSV;
      case CML_COLOR_HSL:   return &cmlXYZToHSL;
      case CML_COLOR_CMYK:  return &cmlXYZToCMYK;
      default: break;
    }
  case CML_COLOR_Yxy:
    switch(outputSystem){
      case CML_COLOR_GRAY:  return &cmlYxyToGray;
      case CML_COLOR_XYZ:   return &cmlYxyToXYZ;
      case CML_COLOR_Yxy:   return &cmlYxyToYxy;
      case CML_COLOR_Yuv:   return &cmlYxyToYuv;
      case CML_COLOR_Yupvp: return &cmlYxyToYupvp;
      case CML_COLOR_Lab:   return &cmlYxyToLab;
      case CML_COLOR_Lch:   return &cmlYxyToLch;
      case CML_COLOR_Luv:   return &cmlYxyToLuv;
      case CML_COLOR_RGB:   return &cmlYxyToRGB;
      case CML_COLOR_YCbCr: return &cmlYxyToYCbCr;
      case CML_COLOR_HSV:   return &cmlYxyToHSV;
      case CML_COLOR_HSL:   return &cmlYxyToHSL;
      case CML_COLOR_CMYK:  return &cmlYxyToCMYK;
      default: break;
    }
  case CML_COLOR_Yuv:
    switch(outputSystem){
      case CML_COLOR_GRAY:  return &cmlYuvToGray;
      case CML_COLOR_XYZ:   return &cmlYuvToXYZ;
      case CML_COLOR_Yxy:   return &cmlYuvToYxy;
      case CML_COLOR_Yuv:   return &cmlYuvToYuv;
      case CML_COLOR_Yupvp: return &cmlYuvToYupvp;
      case CML_COLOR_Lab:   return &cmlYuvToLab;
      case CML_COLOR_Lch:   return &cmlYuvToLch;
      case CML_COLOR_Luv:   return &cmlYuvToLuv;
      case CML_COLOR_RGB:   return &cmlYuvToRGB;
      case CML_COLOR_YCbCr: return &cmlYuvToYCbCr;
      case CML_COLOR_HSV:   return &cmlYuvToHSV;
      case CML_COLOR_HSL:   return &cmlYuvToHSL;
      case CML_COLOR_CMYK:  return &cmlYuvToCMYK;
      default: break;
    }
  case CML_COLOR_Yupvp:
    switch(outputSystem){
      case CML_COLOR_GRAY:  return &cmlYupvpToGray;
      case CML_COLOR_XYZ:   return &cmlYupvpToXYZ;
      case CML_COLOR_Yxy:   return &cmlYupvpToYxy;
      case CML_COLOR_Yuv:   return &cmlYupvpToYuv;
      case CML_COLOR_Yupvp: return &cmlYupvpToYupvp;
      case CML_COLOR_Lab:   return &cmlYupvpToLab;
      case CML_COLOR_Lch:   return &cmlYupvpToLch;
      case CML_COLOR_Luv:   return &cmlYupvpToLuv;
      case CML_COLOR_RGB:   return &cmlYupvpToRGB;
      case CML_COLOR_YCbCr: return &cmlYupvpToYCbCr;
      case CML_COLOR_HSV:   return &cmlYupvpToHSV;
      case CML_COLOR_HSL:   return &cmlYupvpToHSL;
      case CML_COLOR_CMYK:  return &cmlYupvpToCMYK;
      default: break;
    }
  case CML_COLOR_Lab:
    switch(outputSystem){
      case CML_COLOR_GRAY:  return &cmlLabToGray;
      case CML_COLOR_XYZ:   return &cmlLabToXYZ;
      case CML_COLOR_Yxy:   return &cmlLabToYxy;
      case CML_COLOR_Yuv:   return &cmlLabToYuv;
      case CML_COLOR_Yupvp: return &cmlLabToYupvp;
      case CML_COLOR_Lab:   return &cmlLabToLab;
      case CML_COLOR_Lch:   return &cmlLabToLch;
      case CML_COLOR_Luv:   return &cmlLabToLuv;
      case CML_COLOR_RGB:   return &cmlLabToRGB;
      case CML_COLOR_YCbCr: return &cmlLabToYCbCr;
      case CML_COLOR_HSV:   return &cmlLabToHSV;
      case CML_COLOR_HSL:   return &cmlLabToHSL;
      case CML_COLOR_CMYK:  return &cmlLabToCMYK;
      default: break;
    }
  case CML_COLOR_Lch:
    switch(outputSystem){
      case CML_COLOR_GRAY:  return &cmlLchToGray;
      case CML_COLOR_XYZ:   return &cmlLchToXYZ;
      case CML_COLOR_Yxy:   return &cmlLchToYxy;
      case CML_COLOR_Yuv:   return &cmlLchToYuv;
      case CML_COLOR_Yupvp: return &cmlLchToYupvp;
      case CML_COLOR_Lab:   return &cmlLchToLab;
      case CML_COLOR_Lch:   return &cmlLchToLch;
      case CML_COLOR_Luv:   return &cmlLchToLuv;
      case CML_COLOR_RGB:   return &cmlLchToRGB;
      case CML_COLOR_YCbCr: return &cmlLchToYCbCr;
      case CML_COLOR_HSV:   return &cmlLchToHSV;
      case CML_COLOR_HSL:   return &cmlLchToHSL;
      case CML_COLOR_CMYK:  return &cmlLchToCMYK;
      default: break;
    }
  case CML_COLOR_Luv:
    switch(outputSystem){
      case CML_COLOR_GRAY:  return &cmlLuvToGray;
      case CML_COLOR_XYZ:   return &cmlLuvToXYZ;
      case CML_COLOR_Yxy:   return &cmlLuvToYxy;
      case CML_COLOR_Yuv:   return &cmlLuvToYuv;
      case CML_COLOR_Yupvp: return &cmlLuvToYupvp;
      case CML_COLOR_Lab:   return &cmlLuvToLab;
      case CML_COLOR_Lch:   return &cmlLuvToLch;
      case CML_COLOR_Luv:   return &cmlLuvToLuv;
      case CML_COLOR_RGB:   return &cmlLuvToRGB;
      case CML_COLOR_YCbCr: return &cmlLuvToYCbCr;
      case CML_COLOR_HSV:   return &cmlLuvToHSV;
      case CML_COLOR_HSL:   return &cmlLuvToHSL;
      case CML_COLOR_CMYK:  return &cmlLuvToCMYK;
      default: break;
    }
  case CML_COLOR_RGB:
    switch(outputSystem){
      case CML_COLOR_GRAY:  return &cmlRGBToGray;
      case CML_COLOR_XYZ:   return &cmlRGBToXYZ;
      case CML_COLOR_Yxy:   return &cmlRGBToYxy;
      case CML_COLOR_Yuv:   return &cmlRGBToYuv;
      case CML_COLOR_Yupvp: return &cmlRGBToYupvp;
      case CML_COLOR_Lab:   return &cmlRGBToLab;
      case CML_COLOR_Lch:   return &cmlRGBToLch;
      case CML_COLOR_Luv:   return &cmlRGBToLuv;
      case CML_COLOR_RGB:   return &cmlRGBToRGB;
      case CML_COLOR_YCbCr: return &cmlRGBToYCbCr;
      case CML_COLOR_HSV:   return &cmlRGBToHSV;
      case CML_COLOR_HSL:   return &cmlRGBToHSL;
      case CML_COLOR_CMYK:  return &cmlRGBToCMYK;
      default: break;
    }
  case CML_COLOR_YCbCr:
    switch(outputSystem){
      case CML_COLOR_GRAY:  return &cmlYCbCrToGray;
      case CML_COLOR_XYZ:   return &cmlYCbCrToXYZ;
      case CML_COLOR_Yxy:   return &cmlYCbCrToYxy;
      case CML_COLOR_Yuv:   return &cmlYCbCrToYuv;
      case CML_COLOR_Yupvp: return &cmlYCbCrToYupvp;
      case CML_COLOR_Lab:   return &cmlYCbCrToLab;
      case CML_COLOR_Lch:   return &cmlYCbCrToLch;
      case CML_COLOR_Luv:   return &cmlYCbCrToLuv;
      case CML_COLOR_RGB:   return &cmlYCbCrToRGB;
      case CML_COLOR_YCbCr: return &cmlYCbCrToYCbCr;
      case CML_COLOR_HSV:   return &cmlYCbCrToHSV;
      case CML_COLOR_HSL:   return &cmlYCbCrToHSL;
      case CML_COLOR_CMYK:  return &cmlYCbCrToCMYK;
      default: break;
    }
  case CML_COLOR_HSV:
    switch(outputSystem){
      case CML_COLOR_GRAY:  return &cmlHSVToGray;
      case CML_COLOR_XYZ:   return &cmlHSVToXYZ;
      case CML_COLOR_Yxy:   return &cmlHSVToYxy;
      case CML_COLOR_Yuv:   return &cmlHSVToYuv;
      case CML_COLOR_Yupvp: return &cmlHSVToYupvp;
      case CML_COLOR_Lab:   return &cmlHSVToLab;
      case CML_COLOR_Lch:   return &cmlHSVToLch;
      case CML_COLOR_Luv:   return &cmlHSVToLuv;
      case CML_COLOR_RGB:   return &cmlHSVToRGB;
      case CML_COLOR_YCbCr: return &cmlHSVToYCbCr;
      case CML_COLOR_HSV:   return &cmlHSVToHSV;
      case CML_COLOR_HSL:   return &cmlHSVToHSL;
      case CML_COLOR_CMYK:  return &cmlHSVToCMYK;
      default: break;
    }
  case CML_COLOR_HSL:
    switch(outputSystem){
      case CML_COLOR_GRAY:  return &cmlHSLToGray;
      case CML_COLOR_XYZ:   return &cmlHSLToXYZ;
      case CML_COLOR_Yxy:   return &cmlHSLToYxy;
      case CML_COLOR_Yuv:   return &cmlHSLToYuv;
      case CML_COLOR_Yupvp: return &cmlHSLToYupvp;
      case CML_COLOR_Lab:   return &cmlHSLToLab;
      case CML_COLOR_Lch:   return &cmlHSLToLch;
      case CML_COLOR_Luv:   return &cmlHSLToLuv;
      case CML_COLOR_RGB:   return &cmlHSLToRGB;
      case CML_COLOR_YCbCr: return &cmlHSLToYCbCr;
      case CML_COLOR_HSV:   return &cmlHSLToHSV;
      case CML_COLOR_HSL:   return &cmlHSLToHSL;
      case CML_COLOR_CMYK:  return &cmlHSLToCMYK;
      default: break;
    }
  case CML_COLOR_CMYK:
    switch(outputSystem){
      case CML_COLOR_GRAY:  return &cmlCMYKToGray;
      case CML_COLOR_XYZ:   return &cmlCMYKToXYZ;
      case CML_COLOR_Yxy:   return &cmlCMYKToYxy;
      case CML_COLOR_Yuv:   return &cmlCMYKToYuv;
      case CML_COLOR_Yupvp: return &cmlCMYKToYupvp;
      case CML_COLOR_Lab:   return &cmlCMYKToLab;
      case CML_COLOR_Lch:   return &cmlCMYKToLch;
      case CML_COLOR_Luv:   return &cmlCMYKToLuv;
      case CML_COLOR_RGB:   return &cmlCMYKToRGB;
      case CML_COLOR_YCbCr: return &cmlCMYKToYCbCr;
      case CML_COLOR_HSV:   return &cmlCMYKToHSV;
      case CML_COLOR_HSL:   return &cmlCMYKToHSL;
      case CML_COLOR_CMYK:  return &cmlCMYKToCMYK;
      default: break;
    }
  case CML_COLOR_SPECTRUM_ILLUMINATION:
    switch(outputSystem){
      case CML_COLOR_GRAY:  return &cmlSpectrumIlluminationToGray;
      case CML_COLOR_XYZ:   return &cmlSpectrumIlluminationToXYZ;
      case CML_COLOR_Yxy:   return &cmlSpectrumIlluminationToYxy;
      case CML_COLOR_Yuv:   return &cmlSpectrumIlluminationToYuv;
      case CML_COLOR_Yupvp: return &cmlSpectrumIlluminationToYupvp;
      case CML_COLOR_Lab:   return &cmlSpectrumIlluminationToLab;
      case CML_COLOR_Lch:   return &cmlSpectrumIlluminationToLch;
      case CML_COLOR_Luv:   return &cmlSpectrumIlluminationToLuv;
      case CML_COLOR_RGB:   return &cmlSpectrumIlluminationToRGB;
      case CML_COLOR_YCbCr: return &cmlSpectrumIlluminationToYCbCr;
      case CML_COLOR_HSV:   return &cmlSpectrumIlluminationToHSV;
      case CML_COLOR_HSL:   return &cmlSpectrumIlluminationToHSL;
      case CML_COLOR_CMYK:  return &cmlSpectrumIlluminationToCMYK;
      default: break;
    }
  case CML_COLOR_SPECTRUM_REMISSION:
    switch(outputSystem){
      case CML_COLOR_GRAY:  return &cmlSpectrumRemissionToGray;
      case CML_COLOR_XYZ:   return &cmlSpectrumRemissionToXYZ;
      case CML_COLOR_Yxy:   return &cmlSpectrumRemissionToYxy;
      case CML_COLOR_Yuv:   return &cmlSpectrumRemissionToYuv;
      case CML_COLOR_Yupvp: return &cmlSpectrumRemissionToYupvp;
      case CML_COLOR_Lab:   return &cmlSpectrumRemissionToLab;
      case CML_COLOR_Lch:   return &cmlSpectrumRemissionToLch;
      case CML_COLOR_Luv:   return &cmlSpectrumRemissionToLuv;
      case CML_COLOR_RGB:   return &cmlSpectrumRemissionToRGB;
      case CML_COLOR_YCbCr: return &cmlSpectrumRemissionToYCbCr;
      case CML_COLOR_HSV:   return &cmlSpectrumRemissionToHSV;
      case CML_COLOR_HSL:   return &cmlSpectrumRemissionToHSL;
      case CML_COLOR_CMYK:  return &cmlSpectrumRemissionToCMYK;
      default: break;
    }
  default:
    #if CML_DEBUG
      cmlError("Input-ColorType unknown.");
    #endif
    return CML_NULL; break;
  }
  // Reaching here, a default inside the inner switch has been reached.
  #if CML_DEBUG
    cmlError("Output-ColorType unknown.");
  #endif
  return CML_NULL;
}

CML_DEF CMLColorConverter cmlGetData8InputConverter(CMLColorType colorType){
  switch(colorType){
    case CML_COLOR_GRAY:  return &cmlData8ToGray;
    case CML_COLOR_XYZ:   return &cmlData8ToXYZ;
    case CML_COLOR_Yxy:   return &cmlData8ToYxy;
    case CML_COLOR_Yuv:   return &cmlData8ToYuv;
    case CML_COLOR_Yupvp: return &cmlData8ToYupvp;
    case CML_COLOR_Lab:   return &cmlData8ToLab;
    case CML_COLOR_Lch:   return &cmlData8ToLch;
    case CML_COLOR_Luv:   return &cmlData8ToLuv;
    case CML_COLOR_RGB:   return &cmlData8ToRGB;
    case CML_COLOR_YCbCr: return &cmlData8ToYCbCr;
    case CML_COLOR_HSV:   return &cmlData8ToHSV;
    case CML_COLOR_HSL:   return &cmlData8ToHSL;
    case CML_COLOR_CMYK:  return &cmlData8ToCMYK;
    default: break;
  }
  #if CML_DEBUG
    cmlError("ColorType unknown.");
  #endif
  return CML_NULL;
}

CML_DEF CMLColorConverter cmlGetData16InputConverter(CMLColorType colorType){
  switch(colorType){
    case CML_COLOR_GRAY:  return &cmlData16ToGray;
    case CML_COLOR_XYZ:   return &cmlData16ToXYZ;
    case CML_COLOR_Yxy:   return &cmlData16ToYxy;
    case CML_COLOR_Yuv:   return &cmlData16ToYuv;
    case CML_COLOR_Yupvp: return &cmlData16ToYupvp;
    case CML_COLOR_Lab:   return &cmlData16ToLab;
    case CML_COLOR_Lch:   return &cmlData16ToLch;
    case CML_COLOR_Luv:   return &cmlData16ToLuv;
    case CML_COLOR_RGB:   return &cmlData16ToRGB;
    case CML_COLOR_YCbCr: return &cmlData16ToYCbCr;
    case CML_COLOR_HSV:   return &cmlData16ToHSV;
    case CML_COLOR_HSL:   return &cmlData16ToHSL;
    case CML_COLOR_CMYK:  return &cmlData16ToCMYK;
    default: break;
  }
  #if CML_DEBUG
    cmlError("ColorType unknown.");
  #endif
  return CML_NULL;
}

CML_DEF CMLColorConverter cmlGetData8OutputConverter(CMLColorType colorType){
  switch(colorType){
    case CML_COLOR_GRAY:  return &cmlGrayToData8;
    case CML_COLOR_XYZ:   return &cmlXYZToData8;
    case CML_COLOR_Yxy:   return &cmlYxyToData8;
    case CML_COLOR_Yuv:   return &cmlYuvToData8;
    case CML_COLOR_Yupvp: return &cmlYupvpToData8;
    case CML_COLOR_Lab:   return &cmlLabToData8;
    case CML_COLOR_Lch:   return &cmlLchToData8;
    case CML_COLOR_Luv:   return &cmlLuvToData8;
    case CML_COLOR_RGB:   return &cmlRGBToData8;
    case CML_COLOR_YCbCr: return &cmlYCbCrToData8;
    case CML_COLOR_HSV:   return &cmlHSVToData8;
    case CML_COLOR_HSL:   return &cmlHSLToData8;
    case CML_COLOR_CMYK:  return &cmlCMYKToData8;
    default: break;
  }
  #if CML_DEBUG
    cmlError("ColorType unknown.");
  #endif
  return CML_NULL;
}

CML_DEF CMLColorConverter cmlGetData16OutputConverter(CMLColorType colorType){
  switch(colorType){
    case CML_COLOR_GRAY:  return &cmlGrayToData16;
    case CML_COLOR_XYZ:   return &cmlXYZToData16;
    case CML_COLOR_Yxy:   return &cmlYxyToData16;
    case CML_COLOR_Yuv:   return &cmlYuvToData16;
    case CML_COLOR_Yupvp: return &cmlYupvpToData16;
    case CML_COLOR_Lab:   return &cmlLabToData16;
    case CML_COLOR_Lch:   return &cmlLchToData16;
    case CML_COLOR_Luv:   return &cmlLuvToData16;
    case CML_COLOR_RGB:   return &cmlRGBToData16;
    case CML_COLOR_YCbCr: return &cmlYCbCrToData16;
    case CML_COLOR_HSV:   return &cmlHSVToData16;
    case CML_COLOR_HSL:   return &cmlHSLToData16;
    case CML_COLOR_CMYK:  return &cmlCMYKToData16;
    default: break;
  }
  #if CML_DEBUG
    cmlError("ColorType unknown.");
  #endif
  return CML_NULL;
}

CML_DEF CMLColorMutator cmlGetInverter(CMLColorType colorType){
  switch(colorType){
    case CML_COLOR_GRAY:  return &cmlInvertGray;
    case CML_COLOR_XYZ:   return &cmlInvertXYZ;
    case CML_COLOR_Yxy:   return &cmlInvertYxy;
    case CML_COLOR_Yuv:   return &cmlInvertYuv;
    case CML_COLOR_Yupvp: return &cmlInvertYupvp;
    case CML_COLOR_Lab:   return &cmlInvertLab;
    case CML_COLOR_Lch:   return &cmlInvertLch;
    case CML_COLOR_Luv:   return &cmlInvertLuv;
    case CML_COLOR_RGB:   return &cmlInvertRGB;
    case CML_COLOR_YCbCr: return &cmlInvertYCbCr;
    case CML_COLOR_HSV:   return &cmlInvertHSV;
    case CML_COLOR_HSL:   return &cmlInvertHSL;
    case CML_COLOR_CMYK:  return &cmlInvertCMYK;
    default: break;
  }
  #if CML_DEBUG
    cmlError("ColorType unknown.");
  #endif
  return CML_NULL;
}

CML_DEF CMLColorMutator cmlGetClamper(CMLColorType colorType){
  switch(colorType){
    case CML_COLOR_GRAY:  return &cmlClampGray;
    case CML_COLOR_XYZ:   return &cmlClampXYZ;
    case CML_COLOR_Yxy:   return &cmlClampYxy;
    case CML_COLOR_Yuv:   return &cmlClampYuv;
    case CML_COLOR_Yupvp: return &cmlClampYupvp;
    case CML_COLOR_Lab:   return &cmlClampLab;
    case CML_COLOR_Lch:   return &cmlClampLch;
    case CML_COLOR_Luv:   return &cmlClampLuv;
    case CML_COLOR_RGB:   return &cmlClampRGB;
    case CML_COLOR_YCbCr: return &cmlClampYCbCr;
    case CML_COLOR_HSV:   return &cmlClampHSV;
    case CML_COLOR_HSL:   return &cmlClampHSL;
    case CML_COLOR_CMYK:  return &cmlClampCMYK;
    default: break;
  }
  #if CML_DEBUG
    cmlError("ColorType unknown.");
  #endif
  return CML_NULL;
}

CML_DEF CMLNormedConverter cmlGetNormedInputConverter(CMLColorType colorType){
  switch(colorType){
    case CML_COLOR_GRAY:  return &cmlNormedInputToGray;
    case CML_COLOR_XYZ:   return &cmlNormedInputToXYZ;
    case CML_COLOR_Yxy:   return &cmlNormedInputToYxy;
    case CML_COLOR_Yuv:   return &cmlNormedInputToYuv;
    case CML_COLOR_Yupvp: return &cmlNormedInputToYupvp;
    case CML_COLOR_Lab:   return &cmlNormedInputToLab;
    case CML_COLOR_Lch:   return &cmlNormedInputToLch;
    case CML_COLOR_Luv:   return &cmlNormedInputToLuv;
    case CML_COLOR_RGB:   return &cmlNormedInputToRGB;
    case CML_COLOR_YCbCr: return &cmlNormedInputToYCbCr;
    case CML_COLOR_HSV:   return &cmlNormedInputToHSV;
    case CML_COLOR_HSL:   return &cmlNormedInputToHSL;
    case CML_COLOR_CMYK:  return &cmlNormedInputToCMYK;
    default: break;
  }
  #if CML_DEBUG
    cmlError("ColorType unknown.");
  #endif
  return CML_NULL;
}

CML_DEF CMLNormedConverter cmlGetNormedOutputConverter(CMLColorType colorType){
  switch(colorType){
    case CML_COLOR_GRAY:  return &cmlGrayToNormedOutput;
    case CML_COLOR_XYZ:   return &cmlXYZToNormedOutput;
    case CML_COLOR_Yxy:   return &cmlYxyToNormedOutput;
    case CML_COLOR_Yuv:   return &cmlYuvToNormedOutput;
    case CML_COLOR_Yupvp: return &cmlYupvpToNormedOutput;
    case CML_COLOR_Lab:   return &cmlLabToNormedOutput;
    case CML_COLOR_Lch:   return &cmlLchToNormedOutput;
    case CML_COLOR_Luv:   return &cmlLuvToNormedOutput;
    case CML_COLOR_RGB:   return &cmlRGBToNormedOutput;
    case CML_COLOR_YCbCr: return &cmlYCbCrToNormedOutput;
    case CML_COLOR_HSV:   return &cmlHSVToNormedOutput;
    case CML_COLOR_HSL:   return &cmlHSLToNormedOutput;
    case CML_COLOR_CMYK:  return &cmlCMYKToNormedOutput;
    default: break;
  }
  #if CML_DEBUG
    cmlError("ColorType unknown.");
  #endif
  return CML_NULL;
}

CML_DEF CMLNormedConverter cmlGetNormedCartesianInputConverter(CMLColorType colorType){
  switch(colorType){
    case CML_COLOR_GRAY:  return &cmlNormedInputToGray;
    case CML_COLOR_XYZ:   return &cmlNormedInputToXYZ;
    case CML_COLOR_Yxy:   return &cmlNormedInputToYxy;
    case CML_COLOR_Yuv:   return &cmlNormedInputToYuv;
    case CML_COLOR_Yupvp: return &cmlNormedInputToYupvp;
    case CML_COLOR_Lab:   return &cmlNormedInputToLab;
    case CML_COLOR_Lch:   return &cmlNormedCartesianInputToLch;
    case CML_COLOR_Luv:   return &cmlNormedInputToLuv;
    case CML_COLOR_RGB:   return &cmlNormedInputToRGB;
    case CML_COLOR_YCbCr: return &cmlNormedInputToYCbCr;
    case CML_COLOR_HSV:   return &cmlNormedCartesianInputToHSV;
    case CML_COLOR_HSL:   return &cmlNormedCartesianInputToHSL;
    case CML_COLOR_CMYK:  return &cmlNormedInputToCMYK;
    default: break;
  }
  #if CML_DEBUG
    cmlError("ColorType unknown.");
  #endif
  return CML_NULL;
}

CML_DEF CMLNormedConverter cmlGetNormedCartesianOutputConverter(CMLColorType colorType){
  switch(colorType){
    case CML_COLOR_GRAY:  return &cmlGrayToNormedOutput;
    case CML_COLOR_XYZ:   return &cmlXYZToNormedOutput;
    case CML_COLOR_Yxy:   return &cmlYxyToNormedOutput;
    case CML_COLOR_Yuv:   return &cmlYuvToNormedOutput;
    case CML_COLOR_Yupvp: return &cmlYupvpToNormedOutput;
    case CML_COLOR_Lab:   return &cmlLabToNormedOutput;
    case CML_COLOR_Lch:   return &cmlLchToNormedCartesianOutput;
    case CML_COLOR_Luv:   return &cmlLuvToNormedOutput;
    case CML_COLOR_RGB:   return &cmlRGBToNormedOutput;
    case CML_COLOR_YCbCr: return &cmlYCbCrToNormedOutput;
    case CML_COLOR_HSV:   return &cmlHSVToNormedCartesianOutput;
    case CML_COLOR_HSL:   return &cmlHSLToNormedCartesianOutput;
    case CML_COLOR_CMYK:  return &cmlCMYKToNormedOutput;
    default: break;
  }
  #if CML_DEBUG
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

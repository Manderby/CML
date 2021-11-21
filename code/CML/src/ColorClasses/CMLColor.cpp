
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

#include "CMLColor.h"

CMLColorMachine* cmlcm = CML_NULL;

void CMLsetMachineForColorClasses(CMLColorMachine* cm){
  cmlcm = cm;
}

// ////////////////////////////////////
// Color
// ////////////////////////////////////

Color::Color(){}
Color::~Color(){}

GrayColor     Color::toGray() const   {return GrayColor(*this);}
XYZColor      Color::toXYZ() const    {return XYZColor(*this);}
YuvColor      Color::toYuv() const    {return YuvColor(*this);}
YupvpColor    Color::toYupvp() const  {return YupvpColor(*this);}
YxyColor      Color::toYxy() const    {return YxyColor(*this);}
LabColor      Color::toLab() const    {return LabColor(*this);}
LchColor      Color::toLch() const    {return LchColor(*this);}
LuvColor      Color::toLuv() const    {return LuvColor(*this);}
RGBColor      Color::toRGB() const    {return RGBColor(*this);}
YCbCrColor    Color::toYCbCr() const  {return YCbCrColor(*this);}
HSVColor      Color::toHSV() const    {return HSVColor(*this);}
HSLColor      Color::toHSL() const    {return HSLColor(*this);}
CMYKColor     Color::toCMYK() const   {return CMYKColor(*this);}
SpectralColor Color::toSpectral() const  {
  return SpectralColor();
  // This function is not yet implemented as there is not really a valid
  // method to do this. But it may be done one day or another. Currently,
  // this method only exists for the purpose of having a complete interface
  // and hence being able to do cartesian operations on any color, even the
  // spectral ones. But as only spectral colors themselves can be converted
  // to spectral colors without problems, this method remains a todo.
}


void Color::fromBuffer(const float* src, CMLColorType inputtype){
  switch(inputtype){
  case CML_COLOR_GRAY:  fromGrayBuffer(src); break;
  case CML_COLOR_XYZ:   fromXYZBuffer(src); break;
  case CML_COLOR_Yxy:   fromYxyBuffer(src); break;
  case CML_COLOR_Yuv:   fromYuvBuffer(src); break;
  case CML_COLOR_Yupvp: fromYupvpBuffer(src); break;
  case CML_COLOR_Lab:   fromLabBuffer(src); break;
  case CML_COLOR_Lch:   fromLchBuffer(src); break;
  case CML_COLOR_Luv:   fromLuvBuffer(src); break;
  case CML_COLOR_RGB:   fromRGBBuffer(src); break;
  case CML_COLOR_YCbCr: fromYCbCrBuffer(src); break;
  case CML_COLOR_HSV:   fromHSVBuffer(src); break;
  case CML_COLOR_HSL:   fromHSLBuffer(src); break;
  case CML_COLOR_CMYK:  fromCMYKBuffer(src); break;
  default:
    #ifndef NDEBUG
      cmlError("Color::fromBuffer", "Undefined Colorspace.");
    #endif
    break;
  }
}

void Color::toBuffer(float* dest, CMLColorType outputtype) const{
  switch(outputtype){
  case CML_COLOR_GRAY:  toGrayBuffer(dest); break;
  case CML_COLOR_XYZ:   toXYZBuffer(dest); break;
  case CML_COLOR_Yxy:   toYxyBuffer(dest); break;
  case CML_COLOR_Yuv:   toYuvBuffer(dest); break;
  case CML_COLOR_Yupvp: toYupvpBuffer(dest); break;
  case CML_COLOR_Lab:   toLabBuffer(dest); break;
  case CML_COLOR_Lch:   toLchBuffer(dest); break;
  case CML_COLOR_Luv:   toLuvBuffer(dest); break;
  case CML_COLOR_RGB:   toRGBBuffer(dest); break;
  case CML_COLOR_YCbCr: toYCbCrBuffer(dest); break;
  case CML_COLOR_HSV:   toHSVBuffer(dest); break;
  case CML_COLOR_HSL:   toHSLBuffer(dest); break;
  case CML_COLOR_CMYK:  toCMYKBuffer(dest); break;
  default:
    #ifndef NDEBUG
      cmlError("Color::toBuffer", "Undefined Colorspace.");
    #endif
    break;
  }
}

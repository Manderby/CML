
#include "CMLColor.h"

CMLColorMachine* cmlcm = CML_NULL;

void cmlSetMachineForColorClasses(CMLColorMachine* cm){
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
    #if CML_DEBUG
      cmlError("Undefined ColorSpace.");
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
    #if CML_DEBUG
      cmlError("Undefined ColorSpace.");
    #endif
    break;
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


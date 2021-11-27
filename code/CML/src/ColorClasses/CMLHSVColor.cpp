
#include "CMLColor.h"

// ///////////////////////////////////////
// Constructors and initialization methods
// ///////////////////////////////////////

HSVColor::HSVColor(){}
HSVColor::~HSVColor(){}

HSVColor::HSVColor(float H, float S, float V){
  init(H, S, V);
}

 HSVColor::HSVColor(const Color& anycolor){
  operator =(anycolor);
}

 HSVColor::HSVColor(const HSVColor& hsv){
  operator =(hsv);
}

void HSVColor::init(float H, float S, float V){
  cmlSet3(color, H, S, V);
}

HSVColor& HSVColor::operator =(const Color& anycolor){
  anycolor.toHSVBuffer(color);
  return *this;
}

HSVColor& HSVColor::operator =(const HSVColor& hsv){
  cmlCpy3(color, hsv);
  return *this;
}

// ///////////////////////////////////////
// Mathematical operators in cartesian space
// As HSV is not a cartesian space, the HSV values will be converted to RGB
// first if necessary.
// ///////////////////////////////////////

HSVColor HSVColor::operator +() const {
  return HSVColor(*this);
}

HSVColor HSVColor::operator -() const {
  RGBColor rgb(*this);
  return (HSVColor)(-rgb);
}

HSVColor HSVColor::operator +(const Color& anycolor) const{
  RGBColor rgb1(*this);
  RGBColor rgb2(anycolor);
  return (HSVColor)(rgb1 + rgb2);
}

HSVColor HSVColor::operator -(const Color& anycolor) const{
  RGBColor rgb1(*this);
  RGBColor rgb2(anycolor);
  return (HSVColor)(rgb1 - rgb2);
}

HSVColor HSVColor::operator *(const float factor) const{
  return HSVColor(color[0], color[1] * factor, color[2] * factor);
}

HSVColor HSVColor::operator /(const float divisor) const{
  float factor = cmlInverse(divisor);
  return HSVColor(color[0], color[1] * factor, color[2] * factor);
}

HSVColor& HSVColor::operator +=(const Color& anycolor){
  RGBColor rgb1(*this);
  RGBColor rgb2(anycolor);
  operator =(rgb1 + rgb2);
  return *this;
}

HSVColor& HSVColor::operator -=(const Color& anycolor){
  RGBColor rgb1(*this);
  RGBColor rgb2(anycolor);
  operator =(rgb1 - rgb2);
  return *this;
}

HSVColor& HSVColor::operator *=(const float factor){
  color[1] *= factor;
  color[2] *= factor;
  return *this;
}

HSVColor& HSVColor::operator /=(const float divisor){
  float factor = cmlInverse(divisor);
  color[1] *= factor;
  color[2] *= factor;
  return *this;
}

float HSVColor::dot(const HSVColor& hsv) const{
  RGBColor rgb1(*this);
  RGBColor rgb2(hsv);
  return rgb1.dot(rgb2);
}

float HSVColor::length() const {
  RGBColor rgb(*this);
  return cmlLength3(rgb);
}

CMLBool HSVColor::operator ==(const HSVColor& hsv) const{
  return cmlEqual3(color, hsv.color);
}

CMLBool HSVColor::operator !=(const HSVColor& hsv) const{
  return !cmlEqual3(color, hsv.color);
}

// ///////////////////////////////////////
// various methods
// ///////////////////////////////////////

HSVColor::operator const float*() const {return color;}
HSVColor::operator       float*()       {return color;}

HSVColor HSVColor::getInverse(){
  float buf[3];
  cmlCpy3(buf, color);
  cmlInvertHSV(buf, 1);
  return HSVColor(buf[0], buf[1], buf[2]);
}

void HSVColor::invert(){
  cmlInvertHSV(color, 1);
}

CMLBool HSVColor::insideH() {
  return CMLInRange(color[0], CML_HSV_H_MIN, CML_HSV_H_MAX);
}

CMLBool HSVColor::insideS() {
  return CMLInRange(color[1], CML_HSV_S_MIN, CML_HSV_S_MAX);
}

CMLBool HSVColor::insideV() {
  return CMLInRange(color[2], CML_HSV_V_MIN, CML_HSV_V_MAX);
}

CMLBool HSVColor::inside()  {
  return (insideH() && insideS() && insideV());
}

void HSVColor::clamp(){
  cmlClampHSV(color, 1);
}

CMLuint32 HSVColor::getNumChannels() const {return 3;}

// ///////////////////////////////////////
// Converting to different color spaces
// ///////////////////////////////////////

CMLColorType HSVColor::getColorType() const{
  return CML_COLOR_HSV;
}

void HSVColor::from8BitBuffer(const CMLByte* input){
  cmlData8ToHSV(cmlcm, color, input, 1);
}
void HSVColor::from16BitBuffer(const CMLWord* input){
  cmlData16ToHSV(cmlcm, color, input, 1);
}
void HSVColor::fromFloatBuffer(const float* input){
  cmlCpy3(color, input);
}
void HSVColor::to8BitBuffer(CMLByte* output) const {
  cmlHSVToData8(cmlcm, output, color, 1);
}
void HSVColor::to16BitBuffer(CMLWord* output) const {
  cmlHSVToData16(cmlcm, output, color, 1);
}
void HSVColor::toFloatBuffer(float* output) const {
  cmlCpy3(output, color);
}


void HSVColor::fromNormedBuffer(const float* input){
  cmlNormedInputToHSV(color, input, 1);
}
void HSVColor::toNormedBuffer(float* output) const {
  cmlHSVToNormedOutput(output, color, 1);
}
void HSVColor::fromNormedCartesianBuffer(const float* input){
  cmlNormedCartesianInputToHSV(color, input, 1);
}
void HSVColor::toNormedCartesianBuffer(float* output) const {
  cmlHSVToNormedCartesianOutput(output, color, 1);
}


void HSVColor::fromGrayBuffer(const float* src) {cmlGrayToHSV (cmlcm, color, src, 1);}
void HSVColor::fromXYZBuffer(const float* src)  {cmlXYZToHSV  (cmlcm, color, src, 1);}
void HSVColor::fromYuvBuffer(const float* src)  {cmlYuvToHSV  (cmlcm, color, src, 1);}
void HSVColor::fromYupvpBuffer(const float* src){cmlYupvpToHSV(cmlcm, color, src, 1);}
void HSVColor::fromYxyBuffer(const float* src)  {cmlYxyToHSV  (cmlcm, color, src, 1);}
void HSVColor::fromLabBuffer(const float* src)  {cmlLabToHSV  (cmlcm, color, src, 1);}
void HSVColor::fromLchBuffer(const float* src)  {cmlLchToHSV  (cmlcm, color, src, 1);}
void HSVColor::fromLuvBuffer(const float* src)  {cmlLuvToHSV  (cmlcm, color, src, 1);}
void HSVColor::fromRGBBuffer(const float* src)  {cmlRGBToHSV  (cmlcm, color, src, 1);}
void HSVColor::fromYCbCrBuffer(const float* src){cmlYCbCrToHSV(cmlcm, color, src, 1);}
void HSVColor::fromHSVBuffer(const float* src)  {cmlHSVToHSV  (cmlcm, color, src, 1);}
void HSVColor::fromHSLBuffer(const float* src)  {cmlHSLToHSV  (cmlcm, color, src, 1);}
void HSVColor::fromCMYKBuffer(const float* src) {cmlCMYKToHSV (cmlcm, color, src, 1);}


void HSVColor::toGrayBuffer(float* dest) const {cmlHSVToGray (cmlcm, dest, color, 1);}
void HSVColor::toXYZBuffer(float* dest) const  {cmlHSVToXYZ  (cmlcm, dest, color, 1);}
void HSVColor::toYuvBuffer(float* dest) const  {cmlHSVToYuv  (cmlcm, dest, color, 1);}
void HSVColor::toYupvpBuffer(float* dest) const{cmlHSVToYupvp(cmlcm, dest, color, 1);}
void HSVColor::toYxyBuffer(float* dest) const  {cmlHSVToYxy  (cmlcm, dest, color, 1);}
void HSVColor::toLabBuffer(float* dest) const  {cmlHSVToLab  (cmlcm, dest, color, 1);}
void HSVColor::toLchBuffer(float* dest) const  {cmlHSVToLch  (cmlcm, dest, color, 1);}
void HSVColor::toLuvBuffer(float* dest) const  {cmlHSVToLuv  (cmlcm, dest, color, 1);}
void HSVColor::toRGBBuffer(float* dest) const  {cmlHSVToRGB  (cmlcm, dest, color, 1);}
void HSVColor::toYCbCrBuffer(float* dest) const{cmlHSVToYCbCr(cmlcm, dest, color, 1);}
void HSVColor::toHSVBuffer(float* dest) const  {cmlHSVToHSV  (cmlcm, dest, color, 1);}
void HSVColor::toHSLBuffer(float* dest) const  {cmlHSVToHSL  (cmlcm, dest, color, 1);}
void HSVColor::toCMYKBuffer(float* dest) const {cmlHSVToCMYK (cmlcm, dest, color, 1);}



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

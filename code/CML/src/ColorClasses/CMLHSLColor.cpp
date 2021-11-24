
#include "CMLColor.h"

// ///////////////////////////////////////
// Constructors and initialization methods
// ///////////////////////////////////////

HSLColor::HSLColor(){}
HSLColor::~HSLColor(){}

HSLColor::HSLColor(float H, float S, float L){
  init(H, S, L);
}

HSLColor::HSLColor(const Color& anycolor){
  operator =(anycolor);
}

HSLColor::HSLColor(const HSLColor& hsl){
  operator =(hsl);
}

void HSLColor::init(float H, float S, float L){
  cmlSet3(color, H, S, L);
}

HSLColor& HSLColor::operator =(const Color& anycolor){
  anycolor.toHSLBuffer(color);
  return *this;
}

HSLColor& HSLColor::operator =(const HSLColor& hsl){
  cmlCpy3(color, hsl);
  return *this;
}

// ///////////////////////////////////////
// Mathematical operators in cartesian space
// As HSL is not a cartesian space, the HSL values will be converted to RGB
// first if necessary.
// ///////////////////////////////////////

HSLColor HSLColor::operator +() const {
  return HSLColor(*this);
}

HSLColor HSLColor::operator -() const {
  RGBColor rgb(*this);
  return (HSLColor)(-rgb);
}

HSLColor HSLColor::operator +(const Color& anycolor) const{
  RGBColor rgb1(*this);
  RGBColor rgb2(anycolor);
  return (HSLColor)(rgb1 + rgb2);
}

HSLColor HSLColor::operator -(const Color& anycolor) const{
  RGBColor rgb1(*this);
  RGBColor rgb2(anycolor);
  return (HSLColor)(rgb1 - rgb2);
}

HSLColor HSLColor::operator *(const float factor) const{
  return HSLColor(color[0], color[1] * factor, color[2] * factor);
}

HSLColor HSLColor::operator /(const float divisor) const{
  float factor = cmlInverse(divisor);
  return HSLColor(color[0], color[1] * factor, color[2] * factor);
}

HSLColor& HSLColor::operator +=(const Color& anycolor){
  RGBColor rgb1(*this);
  RGBColor rgb2(anycolor);
  operator =(rgb1 + rgb2);
  return *this;
}

HSLColor& HSLColor::operator -=(const Color& anycolor){
  RGBColor rgb1(*this);
  RGBColor rgb2(anycolor);
  operator =(rgb1 - rgb2);
  return *this;
}

HSLColor& HSLColor::operator *=(const float factor){
  color[1] *= factor;
  color[2] *= factor;
  return *this;
}

HSLColor& HSLColor::operator /=(const float divisor){
  float factor = cmlInverse(divisor);
  color[1] *= factor;
  color[2] *= factor;
  return *this;
}

float HSLColor::dot(const HSLColor& hsl) const{
  RGBColor rgb1(*this);
  RGBColor rgb2(hsl);
  return rgb1.dot(rgb2);
}

float HSLColor::length() const {
  RGBColor rgb(*this);
  return cmlLength3(rgb);
}

CMLBool HSLColor::operator ==(const HSLColor& hsl) const{
  return cmlEqual3(color, hsl.color);
}

CMLBool HSLColor::operator !=(const HSLColor& hsl) const{
  return !cmlEqual3(color, hsl.color);
}

// ///////////////////////////////////////
// various methods
// ///////////////////////////////////////

HSLColor::operator const float*() const {return color;}
HSLColor::operator       float*()       {return color;}

HSLColor HSLColor::getInverse(){
  float buf[3];
  cmlCpy3(buf, color);
  cmlInvertHSL(buf, 1);
  return HSLColor(buf[0], buf[1], buf[2]);
}

void HSLColor::invert(){
  cmlInvertHSL(color, 1);
}

CMLBool HSLColor::insideH(){
  return CMLInRange(color[0], CML_HSL_H_MIN, CML_HSL_H_MAX);
}

CMLBool HSLColor::insideS(){
  return CMLInRange(color[1], CML_HSL_S_MIN, CML_HSL_S_MAX);
}

CMLBool HSLColor::insideL(){
  return CMLInRange(color[2], CML_HSL_L_MIN, CML_HSL_L_MAX);
}

CMLBool HSLColor::inside(){
  return (insideH() && insideS() && insideL());
}

void HSLColor::clamp(){
  cmlClampHSL(color, 1);
}

CMLuint32 HSLColor::getNumChannels() const {return 3;}

// ///////////////////////////////////////
// Converting to different color spaces
// ///////////////////////////////////////

CMLColorType HSLColor::getColorType() const{
  return CML_COLOR_HSL;
}

void HSLColor::from8BitBuffer(const CMLByte* input){
  cmlHSLWithData8(cmlcm, color, input, 1);
}
void HSLColor::from16BitBuffer(const CMLWord* input){
  cmlHSLWithData16(cmlcm, color, input, 1);
}
void HSLColor::fromFloatBuffer(const float* input){
  cmlCpy3(color, input);
}
void HSLColor::to8BitBuffer(CMLByte* output) const {
  cmlData8WithHSL(cmlcm, output, color, 1);
}
void HSLColor::to16BitBuffer(CMLWord* output) const {
  cmlData16WithHSL(cmlcm, output, color, 1);
}
void HSLColor::toFloatBuffer(float* output) const {
  cmlCpy3(output, color);
}


void HSLColor::fromNormedBuffer(const float* input){
  cmlHSLWithNormedInput(color, input, 1);
}
void HSLColor::toNormedBuffer(float* output) const {
  cmlNormedOutputWithHSL(output, color, 1);
}
void HSLColor::fromNormedCartesianBuffer(const float* input){
  cmlHSLWithNormedCartesianInput(color, input, 1);
}
void HSLColor::toNormedCartesianBuffer(float* output) const {
  cmlNormedCartesianOutputWithHSL(output, color, 1);
}


void HSLColor::fromGrayBuffer(const float* src) {CMLGraytoHSL (cmlcm, color, src, 1);}
void HSLColor::fromXYZBuffer(const float* src)  {CMLXYZtoHSL  (cmlcm, color, src, 1);}
void HSLColor::fromYuvBuffer(const float* src)  {CMLYuvtoHSL  (cmlcm, color, src, 1);}
void HSLColor::fromYupvpBuffer(const float* src){CMLYupvptoHSL(cmlcm, color, src, 1);}
void HSLColor::fromYxyBuffer(const float* src)  {CMLYxytoHSL  (cmlcm, color, src, 1);}
void HSLColor::fromLabBuffer(const float* src)  {CMLLabtoHSL  (cmlcm, color, src, 1);}
void HSLColor::fromLchBuffer(const float* src)  {CMLLchtoHSL  (cmlcm, color, src, 1);}
void HSLColor::fromLuvBuffer(const float* src)  {CMLLuvtoHSL  (cmlcm, color, src, 1);}
void HSLColor::fromRGBBuffer(const float* src)  {CMLRGBtoHSL  (cmlcm, color, src, 1);}
void HSLColor::fromYCbCrBuffer(const float* src){CMLYCbCrtoHSL(cmlcm, color, src, 1);}
void HSLColor::fromHSVBuffer(const float* src)  {CMLHSVtoHSL  (cmlcm, color, src, 1);}
void HSLColor::fromHSLBuffer(const float* src)  {CMLHSLtoHSL  (cmlcm, color, src, 1);}
void HSLColor::fromCMYKBuffer(const float* src) {CMLCMYKtoHSL (cmlcm, color, src, 1);}

void HSLColor::toGrayBuffer(float* dest) const {CMLHSLtoGray (cmlcm, dest, color, 1);}
void HSLColor::toXYZBuffer(float* dest) const  {CMLHSLtoXYZ  (cmlcm, dest, color, 1);}
void HSLColor::toYuvBuffer(float* dest) const  {CMLHSLtoYuv  (cmlcm, dest, color, 1);}
void HSLColor::toYupvpBuffer(float* dest) const{CMLHSLtoYupvp(cmlcm, dest, color, 1);}
void HSLColor::toYxyBuffer(float* dest) const  {CMLHSLtoYxy  (cmlcm, dest, color, 1);}
void HSLColor::toLabBuffer(float* dest) const  {CMLHSLtoLab  (cmlcm, dest, color, 1);}
void HSLColor::toLchBuffer(float* dest) const  {CMLHSLtoLch  (cmlcm, dest, color, 1);}
void HSLColor::toLuvBuffer(float* dest) const  {CMLHSLtoLuv  (cmlcm, dest, color, 1);}
void HSLColor::toRGBBuffer(float* dest) const  {CMLHSLtoRGB  (cmlcm, dest, color, 1);}
void HSLColor::toYCbCrBuffer(float* dest) const{CMLHSLtoYCbCr(cmlcm, dest, color, 1);}
void HSLColor::toHSVBuffer(float* dest) const  {CMLHSLtoHSV  (cmlcm, dest, color, 1);}
void HSLColor::toHSLBuffer(float* dest) const  {CMLHSLtoHSL  (cmlcm, dest, color, 1);}
void HSLColor::toCMYKBuffer(float* dest) const {CMLHSLtoCMYK (cmlcm, dest, color, 1);}



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

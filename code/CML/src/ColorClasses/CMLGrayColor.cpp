
#include "CMLColor.h"

// ///////////////////////////////////////
// Constructors and initialization methods
// ///////////////////////////////////////

GrayColor::GrayColor(){}
GrayColor::~GrayColor(){}

GrayColor::GrayColor(float gray){
  init(gray);
}

GrayColor::GrayColor(const Color& anycolor){
  operator =(anycolor);
}

GrayColor::GrayColor(const GrayColor& gray){
  operator =(gray);
}

void GrayColor::init(float gray){
  color[0] = gray;
}

GrayColor& GrayColor::operator =(const Color& anycolor){
  anycolor.toGrayBuffer(color);
  return *this;
}

GrayColor& GrayColor::operator =(const GrayColor& gray){
  color[0] = gray.color[0];
  return *this;
}

// ///////////////////////////////////////
// Mathematical operators in cartesian space
// ///////////////////////////////////////

GrayColor GrayColor::operator +() const {
  return GrayColor(*this);
}

GrayColor GrayColor::operator -() const {
  return GrayColor(-color[0]);
}

GrayColor GrayColor::operator +(const Color& anycolor) const {
  float buf[1];
  anycolor.toGrayBuffer(buf);
  return GrayColor(color[0]+buf[0]);
}

GrayColor GrayColor::operator -(const Color& anycolor) const {
  float buf[1];
  anycolor.toGrayBuffer(buf);
  return GrayColor(color[0]-buf[0]);
}

GrayColor GrayColor::operator *(const float factor) const {
  return GrayColor(color[0]*factor);
}

GrayColor GrayColor::operator /(const float divisor) const {
  float factor = cmlInverse(divisor);
  return GrayColor(color[0]*factor);
}

GrayColor& GrayColor::operator +=(const Color& anycolor){
  float buf[1];
  anycolor.toGrayBuffer(buf);
  color[0] += buf[0];
  return *this;
}
GrayColor& GrayColor::operator -=(const Color& anycolor){
  float buf[1];
  anycolor.toGrayBuffer(buf);
  color[0] -= buf[0];
  return *this;
}

GrayColor& GrayColor::operator *=(const float factor){
  color[0] *= factor;
  return *this;
}

GrayColor& GrayColor::operator /=(const float divisor){
  float factor = cmlInverse(divisor);
  color[0] *= factor;
  return *this;
}

float GrayColor::dot(const GrayColor& gray) const {
  return color[0] * gray.color[0];
}

float GrayColor::length() const {
  return cmlLength1(color);
}

CMLBool GrayColor::operator ==(const GrayColor& gray) const {
  return (color[0] == gray.color[0]);
}

CMLBool GrayColor::operator !=(const GrayColor& gray) const {
  return (color[0] != gray.color[0]);
}

// ///////////////////////////////////////
// various methods
// ///////////////////////////////////////

GrayColor::operator const float*() const {return color;}
GrayColor::operator       float*()       {return color;}

GrayColor GrayColor::getInverse() const {
  float buf[1];
  cmlCpy1(buf, color);
  cmlInvertGray(buf, 1);
  return GrayColor(buf[0]);
}

void GrayColor::invert(){
  cmlInvertGray(color, 1);
}

CMLBool GrayColor::inside() const {
  return CMLInRange(color[0], CML_GRAY_MIN, CML_GRAY_MAX);
}

void GrayColor::clamp(){
  cmlClampGray(color, 1);
}

CMLuint32 GrayColor::getNumChannels() const {return 1;}

// ///////////////////////////////////////
// Converting to different color spaces
// ///////////////////////////////////////

CMLColorType GrayColor::getColorType() const{
  return CML_COLOR_GRAY;
}

void GrayColor::from8BitBuffer(const CMLByte* input){
  cmlData8ToGray(cmlcm, color, input, 1);
}
void GrayColor::from16BitBuffer(const CMLWord* input){
  cmlData16ToGray(cmlcm, color, input, 1);
}
void GrayColor::fromFloatBuffer(const float* input){
  color[0] = input[0];
}
void GrayColor::to8BitBuffer(CMLByte* output) const {
  cmlGrayToData8(cmlcm, output, color, 1);
}
void GrayColor::to16BitBuffer(CMLWord* output) const {
  cmlGrayToData16(cmlcm, output, color, 1);
}
void GrayColor::toFloatBuffer(float* output) const {
  output[0] = color[0];
}


void GrayColor::fromNormedBuffer(const float* input){
  cmlNormedInputToGray(color, input, 1);
}
void GrayColor::toNormedBuffer(float* output) const {
  cmlGrayToNormedOutput(output, color, 1);
}
void GrayColor::fromNormedCartesianBuffer(const float* input){
  cmlNormedInputToGray(color, input, 1);
}
void GrayColor::toNormedCartesianBuffer(float* output) const {
  cmlGrayToNormedOutput(output, color, 1);
}


void GrayColor::fromGrayBuffer(const float* src) {CMLGraytoGray (cmlcm, color, src, 1);}
void GrayColor::fromXYZBuffer(const float* src)  {CMLXYZtoGray  (cmlcm, color, src, 1);}
void GrayColor::fromYuvBuffer(const float* src)  {CMLYuvtoGray  (cmlcm, color, src, 1);}
void GrayColor::fromYupvpBuffer(const float* src){CMLYupvptoGray(cmlcm, color, src, 1);}
void GrayColor::fromYxyBuffer(const float* src)  {CMLYxytoGray  (cmlcm, color, src, 1);}
void GrayColor::fromLabBuffer(const float* src)  {CMLLabtoGray  (cmlcm, color, src, 1);}
void GrayColor::fromLchBuffer(const float* src)  {CMLLchtoGray  (cmlcm, color, src, 1);}
void GrayColor::fromLuvBuffer(const float* src)  {CMLLuvtoGray  (cmlcm, color, src, 1);}
void GrayColor::fromRGBBuffer(const float* src)  {CMLRGBtoGray  (cmlcm, color, src, 1);}
void GrayColor::fromYCbCrBuffer(const float* src){CMLYCbCrtoGray(cmlcm, color, src, 1);}
void GrayColor::fromHSVBuffer(const float* src)  {CMLHSVtoGray  (cmlcm, color, src, 1);}
void GrayColor::fromHSLBuffer(const float* src)  {CMLHSLtoGray  (cmlcm, color, src, 1);}
void GrayColor::fromCMYKBuffer(const float* src) {CMLCMYKtoGray (cmlcm, color, src, 1);}


void GrayColor::toGrayBuffer(float* dest) const {CMLGraytoGray (cmlcm, dest, color, 1);}
void GrayColor::toXYZBuffer(float* dest) const  {CMLGraytoXYZ  (cmlcm, dest, color, 1);}
void GrayColor::toYuvBuffer(float* dest) const  {CMLGraytoYuv  (cmlcm, dest, color, 1);}
void GrayColor::toYupvpBuffer(float* dest) const{CMLGraytoYupvp(cmlcm, dest, color, 1);}
void GrayColor::toYxyBuffer(float* dest) const  {CMLGraytoYxy  (cmlcm, dest, color, 1);}
void GrayColor::toLabBuffer(float* dest) const  {CMLGraytoLab  (cmlcm, dest, color, 1);}
void GrayColor::toLchBuffer(float* dest) const  {CMLGraytoLch  (cmlcm, dest, color, 1);}
void GrayColor::toLuvBuffer(float* dest) const  {CMLGraytoLuv  (cmlcm, dest, color, 1);}
void GrayColor::toRGBBuffer(float* dest) const  {CMLGraytoRGB  (cmlcm, dest, color, 1);}
void GrayColor::toYCbCrBuffer(float* dest) const{CMLGraytoYCbCr(cmlcm, dest, color, 1);}
void GrayColor::toHSVBuffer(float* dest) const  {CMLGraytoHSV  (cmlcm, dest, color, 1);}
void GrayColor::toHSLBuffer(float* dest) const  {CMLGraytoHSL  (cmlcm, dest, color, 1);}
void GrayColor::toCMYKBuffer(float* dest) const {CMLGraytoCMYK (cmlcm, dest, color, 1);}



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

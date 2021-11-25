
#include "CMLColor.h"

// ///////////////////////////////////////
// Constructors and initialization methods
// ///////////////////////////////////////

YxyColor::YxyColor(){}
YxyColor::~YxyColor(){}

YxyColor::YxyColor(float Y, float x, float y){
  init(Y, x, y);
}

YxyColor::YxyColor(const Color& anycolor){
  operator =(anycolor);
}

YxyColor::YxyColor(const YxyColor& yxy){
  operator =(yxy);
}

void YxyColor::init(float Y, float x, float y){
  cmlSet3(color, Y, x, y);
}

YxyColor& YxyColor::operator =(const Color& anycolor){
  anycolor.toYxyBuffer(color);
  return *this;
}

YxyColor& YxyColor::operator =(const YxyColor& yxy){
  cmlCpy3(color, yxy);
  return *this;
}

// ///////////////////////////////////////
// Mathematical operators in cartesian space
// ///////////////////////////////////////

YxyColor YxyColor::operator +() const {
  return YxyColor(*this);
}

YxyColor YxyColor::operator -() const {
  return YxyColor(-color[0], -color[1], -color[2]);
}

YxyColor YxyColor::operator +(const Color& anycolor) const {
  float buf[3];
  anycolor.toYxyBuffer(buf);
  return YxyColor(color[0]+buf[0], color[1]+buf[1], color[2]+buf[2]);
}

YxyColor YxyColor::operator -(const Color& anycolor) const {
  float buf[3];
  anycolor.toYxyBuffer(buf);
  return YxyColor(color[0]-buf[0], color[1]-buf[1], color[2]-buf[2]);
}

YxyColor YxyColor::operator *(const float factor) const {
  return YxyColor(color[0]*factor, color[1]*factor, color[2]*factor);
}

YxyColor YxyColor::operator /(const float divisor) const {
  float factor = cmlInverse(divisor);
  return YxyColor(color[0]*factor, color[1]*factor, color[2]*factor);
}

YxyColor& YxyColor::operator +=(const Color& anycolor){
  float buf[3];
  anycolor.toYxyBuffer(buf);
  cmlAdd3(color, buf);
  return *this;
}

YxyColor& YxyColor::operator -=(const Color& anycolor){
  float buf[3];
  anycolor.toYxyBuffer(buf);
  cmlSub3(color, buf);
  return *this;
}

YxyColor& YxyColor::operator *=(const float factor){
  cmlMul3(color, factor);
  return *this;
}

YxyColor& YxyColor::operator /=(const float divisor){
  cmlDiv3(color, divisor);
  return *this;
}

float YxyColor::dot(const YxyColor& yxy) const {
  return cmlDot3(color, yxy.color);
}

float YxyColor::length() const {
  return cmlLength3(color);
}

CMLBool YxyColor::operator ==(const YxyColor& yxy) const {
  return cmlEqual3(color, yxy.color);
}

CMLBool YxyColor::operator !=(const YxyColor& yxy) const {
  return !cmlEqual3(color, yxy.color);
}

// ///////////////////////////////////////
// various methods
// ///////////////////////////////////////

YxyColor::operator const float*() const {return color;}
YxyColor::operator       float*()       {return color;}

YxyColor YxyColor::getInverse(){
  float buf[3];
  cmlCpy3(buf, color);
  cmlInvertYxy(buf, 1);
  return YxyColor(buf[0], buf[1], buf[2]);
}

void YxyColor::invert(){
  cmlInvertYxy(color, 1);
}

CMLBool YxyColor::insideY(){
  return CMLInRange(color[0], CML_Yxy_Y_MIN, CML_Yxy_Y_MAX);
}

CMLBool YxyColor::insidex() {
  return CMLInRange(color[1], CML_Yxy_x_MIN, CML_Yxy_x_MAX);
}

CMLBool YxyColor::insidey(){
  return CMLInRange(color[2], CML_Yxy_y_MIN, CML_Yxy_y_MAX);
}

CMLBool YxyColor::inside(){
  return (insideY() && insidex() && insidey());
}

void YxyColor::clamp(){
  cmlClampYxy(color, 1);
}

CMLuint32 YxyColor::getNumChannels() const {return 3;}

// ///////////////////////////////////////
// Converting to different color spaces
// ///////////////////////////////////////

CMLColorType YxyColor::getColorType() const{
  return CML_COLOR_Yxy;
}

void YxyColor::from8BitBuffer(const CMLByte* input){
  cmlData8ToYxy(cmlcm, color, input, 1);
}
void YxyColor::from16BitBuffer(const CMLWord* input){
  cmlData16ToYxy(cmlcm, color, input, 1);
}
void YxyColor::fromFloatBuffer(const float* input){
  cmlCpy3(color, input);
}
void YxyColor::to8BitBuffer(CMLByte* output) const {
  cmlYxyToData8(cmlcm, output, color, 1);
}
void YxyColor::to16BitBuffer(CMLWord* output) const {
  cmlYxyToData16(cmlcm, output, color, 1);
}
void YxyColor::toFloatBuffer(float* output) const {
  cmlCpy3(output, color);
}


void YxyColor::fromNormedBuffer(const float* input){
  cmlNormedInputToYxy(color, input, 1);
}
void YxyColor::toNormedBuffer(float* output) const {
  cmlYxyToNormedOutput(output, color, 1);
}
void YxyColor::fromNormedCartesianBuffer(const float* input){
  cmlNormedInputToYxy(color, input, 1);
}
void YxyColor::toNormedCartesianBuffer(float* output) const {
  cmlYxyToNormedOutput(output, color, 1);
}


void YxyColor::fromGrayBuffer(const float* src) {CMLGraytoYxy (cmlcm, color, src, 1);}
void YxyColor::fromXYZBuffer(const float* src)  {CMLXYZtoYxy  (cmlcm, color, src, 1);}
void YxyColor::fromYuvBuffer(const float* src)  {CMLYuvtoYxy  (cmlcm, color, src, 1);}
void YxyColor::fromYupvpBuffer(const float* src){CMLYupvptoYxy(cmlcm, color, src, 1);}
void YxyColor::fromYxyBuffer(const float* src)  {CMLYxytoYxy  (cmlcm, color, src, 1);}
void YxyColor::fromLabBuffer(const float* src)  {CMLLabtoYxy  (cmlcm, color, src, 1);}
void YxyColor::fromLchBuffer(const float* src)  {CMLLchtoYxy  (cmlcm, color, src, 1);}
void YxyColor::fromLuvBuffer(const float* src)  {CMLLuvtoYxy  (cmlcm, color, src, 1);}
void YxyColor::fromRGBBuffer(const float* src)  {CMLRGBtoYxy  (cmlcm, color, src, 1);}
void YxyColor::fromYCbCrBuffer(const float* src){CMLYCbCrtoYxy(cmlcm, color, src, 1);}
void YxyColor::fromHSVBuffer(const float* src)  {CMLHSVtoYxy  (cmlcm, color, src, 1);}
void YxyColor::fromHSLBuffer(const float* src)  {CMLHSLtoYxy  (cmlcm, color, src, 1);}
void YxyColor::fromCMYKBuffer(const float* src) {CMLCMYKtoYxy (cmlcm, color, src, 1);}

void YxyColor::toGrayBuffer(float* dest) const {CMLYxytoGray (cmlcm, dest, color, 1);}
void YxyColor::toXYZBuffer(float* dest) const  {CMLYxytoXYZ  (cmlcm, dest, color, 1);}
void YxyColor::toYuvBuffer(float* dest) const  {CMLYxytoYuv  (cmlcm, dest, color, 1);}
void YxyColor::toYupvpBuffer(float* dest) const{CMLYxytoYupvp(cmlcm, dest, color, 1);}
void YxyColor::toYxyBuffer(float* dest) const  {CMLYxytoYxy  (cmlcm, dest, color, 1);}
void YxyColor::toLabBuffer(float* dest) const  {CMLYxytoLab  (cmlcm, dest, color, 1);}
void YxyColor::toLchBuffer(float* dest) const  {CMLYxytoLch  (cmlcm, dest, color, 1);}
void YxyColor::toLuvBuffer(float* dest) const  {CMLYxytoLuv  (cmlcm, dest, color, 1);}
void YxyColor::toRGBBuffer(float* dest) const  {CMLYxytoRGB  (cmlcm, dest, color, 1);}
void YxyColor::toYCbCrBuffer(float* dest) const{CMLYxytoYCbCr(cmlcm, dest, color, 1);}
void YxyColor::toHSVBuffer(float* dest) const  {CMLYxytoHSV  (cmlcm, dest, color, 1);}
void YxyColor::toHSLBuffer(float* dest) const  {CMLYxytoHSL  (cmlcm, dest, color, 1);}
void YxyColor::toCMYKBuffer(float* dest) const {CMLYxytoCMYK (cmlcm, dest, color, 1);}



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

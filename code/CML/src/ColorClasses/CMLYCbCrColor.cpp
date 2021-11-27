
#include "CMLColor.h"

// ///////////////////////////////////////
// Constructors and initialization methods
// ///////////////////////////////////////

YCbCrColor::YCbCrColor(){}
YCbCrColor::~YCbCrColor(){}

YCbCrColor::YCbCrColor(float Y, float Cb, float Cr){
  init(Y, Cb, Cr);
}

YCbCrColor::YCbCrColor(const Color& anycolor){
  operator =(anycolor);
}

YCbCrColor::YCbCrColor(const YCbCrColor& ycbcr){
  operator =(ycbcr);
}

void YCbCrColor::init(float Y, float Cb, float Cr){
  cmlSet3(color, Y, Cb, Cr);
}

YCbCrColor& YCbCrColor::operator =(const Color& anycolor){
  anycolor.toYCbCrBuffer(color);
  return *this;
}

YCbCrColor& YCbCrColor::operator =(const YCbCrColor& ycbcr){
  cmlCpy3(color, ycbcr);
  return *this;
}

// ///////////////////////////////////////
// Mathematical operators in cartesian space
// ///////////////////////////////////////

YCbCrColor YCbCrColor::operator +() const {
  return YCbCrColor(*this);
}

YCbCrColor YCbCrColor::operator -() const {
  return YCbCrColor(-color[0], -color[1], -color[2]);
}

YCbCrColor YCbCrColor::operator +(const Color& anycolor) const {
  float buf[3];
  anycolor.toYCbCrBuffer(buf);
  return YCbCrColor(color[0]+buf[0], color[1]+buf[1], color[2]+buf[2]);
}

YCbCrColor YCbCrColor::operator -(const Color& anycolor) const {
  float buf[3];
  anycolor.toYCbCrBuffer(buf);
  return YCbCrColor(color[0]-buf[0], color[1]-buf[1], color[2]-buf[2]);
}

YCbCrColor YCbCrColor::operator *(const float factor) const {
  return YCbCrColor(color[0]*factor, color[1]*factor, color[2]*factor);
}

YCbCrColor YCbCrColor::operator /(const float divisor) const {
  float factor = cmlInverse(divisor);
  return YCbCrColor(color[0]*factor, color[1]*factor, color[2]*factor);
}

YCbCrColor& YCbCrColor::operator +=(const Color& anycolor){
  float buf[3];
  anycolor.toYCbCrBuffer(buf);
  cmlAdd3(color, buf);
  return *this;
}

YCbCrColor& YCbCrColor::operator -=(const Color& anycolor){
  float buf[3];
  anycolor.toYCbCrBuffer(buf);
  cmlSub3(color, buf);
  return *this;
}

YCbCrColor& YCbCrColor::operator *=(const float factor){
  cmlMul3(color, factor);
  return *this;
}

YCbCrColor& YCbCrColor::operator /=(const float divisor){
  cmlDiv3(color, divisor);
  return *this;
}

float YCbCrColor::dot(const YCbCrColor& luv) const {
  return cmlDot3(color, luv.color);
}

float YCbCrColor::length() const {
  return cmlLength3(color);
}

CMLBool YCbCrColor::operator ==(const YCbCrColor& ycbcr) const {
  return cmlEqual3(color, ycbcr.color);
}

CMLBool YCbCrColor::operator !=(const YCbCrColor& ycbcr) const {
  return !cmlEqual3(color, ycbcr.color);
}

// ///////////////////////////////////////
// various methods
// ///////////////////////////////////////

YCbCrColor::operator const float*() const {return color;}
YCbCrColor::operator       float*()       {return color;}

YCbCrColor YCbCrColor::getInverse() {
  float buf[3];
  cmlCpy3(buf, color);
  cmlInvertYCbCr(buf, 1);
  return YCbCrColor(buf[0], buf[1], buf[2]);
}

void YCbCrColor::invert(){
  cmlInvertYCbCr(color, 1);
}

CMLBool YCbCrColor::insideY() {
  return cmlInRange(color[0], CML_YCbCr_Y_MIN, CML_YCbCr_Y_MAX);
}

CMLBool YCbCrColor::insideCb() {
  return cmlInRange(color[1], CML_YCbCr_Cb_MIN, CML_YCbCr_Cb_MAX);
}

CMLBool YCbCrColor::insideCr() {
  return cmlInRange(color[2], CML_YCbCr_Cr_MIN, CML_YCbCr_Cr_MAX);
}

CMLBool YCbCrColor::inside()  {
  return (insideY() && insideCb() && insideCr());
}

void YCbCrColor::clamp(){
  cmlClampYCbCr(color, 1);
}

CMLuint32 YCbCrColor::getNumChannels() const {return 3;}

// ///////////////////////////////////////
// Converting to different color spaces
// ///////////////////////////////////////

CMLColorType YCbCrColor::getColorType() const{
  return CML_COLOR_YCbCr;
}

void YCbCrColor::from8BitBuffer(const CMLByte* input){
  cmlData8ToYCbCr(cmlcm, color, input, 1);
}
void YCbCrColor::from16BitBuffer(const CMLWord* input){
  cmlData16ToYCbCr(cmlcm, color, input, 1);
}
void YCbCrColor::fromFloatBuffer(const float* input){
  cmlCpy3(color, input);
}
void YCbCrColor::to8BitBuffer(CMLByte* output) const {
  cmlYCbCrToData8(cmlcm, output, color, 1);
}
void YCbCrColor::to16BitBuffer(CMLWord* output) const {
  cmlYCbCrToData16(cmlcm, output, color, 1);
}
void YCbCrColor::toFloatBuffer(float* output) const {
  cmlCpy3(output, color);
}


void YCbCrColor::fromNormedBuffer(const float* input){
  cmlNormedInputToYCbCr(color, input, 1);
}
void YCbCrColor::toNormedBuffer(float* output) const {
  cmlYCbCrToNormedOutput(output, color, 1);
}
void YCbCrColor::fromNormedCartesianBuffer(const float* input){
  cmlNormedInputToYCbCr(color, input, 1);
}
void YCbCrColor::toNormedCartesianBuffer(float* output) const {
  cmlYCbCrToNormedOutput(output, color, 1);
}


void YCbCrColor::fromGrayBuffer(const float* src) {cmlGrayToYCbCr (cmlcm, color, src, 1);}
void YCbCrColor::fromXYZBuffer(const float* src)  {cmlXYZToYCbCr  (cmlcm, color, src, 1);}
void YCbCrColor::fromYuvBuffer(const float* src)  {cmlYuvToYCbCr  (cmlcm, color, src, 1);}
void YCbCrColor::fromYupvpBuffer(const float* src){cmlYupvpToYCbCr(cmlcm, color, src, 1);}
void YCbCrColor::fromYxyBuffer(const float* src)  {cmlYxyToYCbCr  (cmlcm, color, src, 1);}
void YCbCrColor::fromLabBuffer(const float* src)  {cmlLabToYCbCr  (cmlcm, color, src, 1);}
void YCbCrColor::fromLchBuffer(const float* src)  {cmlLchToYCbCr  (cmlcm, color, src, 1);}
void YCbCrColor::fromLuvBuffer(const float* src)  {cmlLuvToYCbCr  (cmlcm, color, src, 1);}
void YCbCrColor::fromRGBBuffer(const float* src)  {cmlRGBToYCbCr  (cmlcm, color, src, 1);}
void YCbCrColor::fromYCbCrBuffer(const float* src){cmlYCbCrToYCbCr(cmlcm, color, src, 1);}
void YCbCrColor::fromHSVBuffer(const float* src)  {cmlHSVToYCbCr  (cmlcm, color, src, 1);}
void YCbCrColor::fromHSLBuffer(const float* src)  {cmlHSLToYCbCr  (cmlcm, color, src, 1);}
void YCbCrColor::fromCMYKBuffer(const float* src) {cmlCMYKToYCbCr (cmlcm, color, src, 1);}

void YCbCrColor::toGrayBuffer(float* dest) const {cmlYCbCrToGray (cmlcm, dest, color, 1);}
void YCbCrColor::toXYZBuffer(float* dest) const  {cmlYCbCrToXYZ  (cmlcm, dest, color, 1);}
void YCbCrColor::toYuvBuffer(float* dest) const  {cmlYCbCrToYuv  (cmlcm, dest, color, 1);}
void YCbCrColor::toYupvpBuffer(float* dest) const{cmlYCbCrToYupvp(cmlcm, dest, color, 1);}
void YCbCrColor::toYxyBuffer(float* dest) const  {cmlYCbCrToYxy  (cmlcm, dest, color, 1);}
void YCbCrColor::toLabBuffer(float* dest) const  {cmlYCbCrToLab  (cmlcm, dest, color, 1);}
void YCbCrColor::toLchBuffer(float* dest) const  {cmlYCbCrToLch  (cmlcm, dest, color, 1);}
void YCbCrColor::toLuvBuffer(float* dest) const  {cmlYCbCrToLuv  (cmlcm, dest, color, 1);}
void YCbCrColor::toRGBBuffer(float* dest) const  {cmlYCbCrToRGB  (cmlcm, dest, color, 1);}
void YCbCrColor::toYCbCrBuffer(float* dest) const{cmlYCbCrToYCbCr(cmlcm, dest, color, 1);}
void YCbCrColor::toHSVBuffer(float* dest) const  {cmlYCbCrToHSV  (cmlcm, dest, color, 1);}
void YCbCrColor::toHSLBuffer(float* dest) const  {cmlYCbCrToHSL  (cmlcm, dest, color, 1);}
void YCbCrColor::toCMYKBuffer(float* dest) const {cmlYCbCrToCMYK (cmlcm, dest, color, 1);}



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

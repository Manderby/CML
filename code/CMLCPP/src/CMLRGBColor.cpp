
#include "CMLColor.h"

// ///////////////////////////////////////
// Constructors and initialization methods
// ///////////////////////////////////////

RGBColor::RGBColor(){}
RGBColor::~RGBColor(){}

RGBColor::RGBColor(float R, float G, float B){
  init(R, G, B);
}

RGBColor::RGBColor(const Color& anycolor){
  operator =(anycolor);
}

RGBColor::RGBColor(const RGBColor& rgb){
  operator =(rgb);
}

void RGBColor::init(float R, float G, float B){
  cmlSet3(color, R, G, B);
}

RGBColor& RGBColor::operator =(const Color& anycolor){
  anycolor.toRGBBuffer(color);
  return *this;
}

RGBColor& RGBColor::operator =(const RGBColor& rgb){
  cmlCpy3(color, rgb);
  return *this;
}

// ///////////////////////////////////////
// Mathematical operators in cartesian space
// ///////////////////////////////////////

RGBColor RGBColor::operator +() const {
  return RGBColor(*this);
}

RGBColor RGBColor::operator -() const {
  return RGBColor(-color[0], -color[1], -color[2]);
}

RGBColor RGBColor::operator +(const Color& anycolor) const {
  float buf[3];
  anycolor.toRGBBuffer(buf);
  return RGBColor(color[0]+buf[0], color[1]+buf[1], color[2]+buf[2]);
}

RGBColor RGBColor::operator -(const Color& anycolor) const {
  float buf[3];
  anycolor.toRGBBuffer(buf);
  return RGBColor(color[0]-buf[0], color[1]-buf[1], color[2]-buf[2]);
}

RGBColor RGBColor::operator *(const float factor) const {
  return RGBColor(color[0]*factor, color[1]*factor, color[2]*factor);
}

RGBColor RGBColor::operator /(const float divisor) const {
  float factor = cmlInverse(divisor);
  return RGBColor(color[0]*factor, color[1]*factor, color[2]*factor);
}

RGBColor& RGBColor::operator +=(const Color& anycolor){
  float buf[3];
  anycolor.toRGBBuffer(buf);
  cmlAdd3(color, buf);
  return *this;
}

RGBColor& RGBColor::operator -=(const Color& anycolor){
  float buf[3];
  anycolor.toRGBBuffer(buf);
  cmlSub3(color, buf);
  return *this;
}

RGBColor& RGBColor::operator *=(const float factor){
  cmlMul3(color, factor);
  return *this;
}

RGBColor& RGBColor::operator /=(const float divisor){
  cmlDiv3(color, divisor);
  return *this;
}

float RGBColor::dot(const RGBColor& rgb) const{
  return cmlDot3(color, rgb.color);
}

float RGBColor::length() const {
  return cmlLength3(color);
}

CMLBool RGBColor::operator ==(const RGBColor& rgb) const {
  return cmlEqual3(color, rgb.color);
}

CMLBool RGBColor::operator !=(const RGBColor& rgb) const {
  return !cmlEqual3(color, rgb.color);
}

// ///////////////////////////////////////
// various methods
// ///////////////////////////////////////

RGBColor::operator const float*() const {return color;}
RGBColor::operator       float*()       {return color;}

RGBColor RGBColor::getInverse() {
  float buf[3];
  cmlCpy3(buf, color);
  cmlInvertRGB(buf, 1);
  return RGBColor(buf[0], buf[1], buf[2]);
}

void RGBColor::invert(){
  cmlInvertRGB(color, 1);
}

CMLBool RGBColor::insideR() {
  return cmlInRange(color[0], CML_RGB_R_MIN, CML_RGB_R_MAX);
}

CMLBool RGBColor::insideG() {
  return cmlInRange(color[1], CML_RGB_G_MIN, CML_RGB_G_MAX);
}

CMLBool RGBColor::insideB() {
  return cmlInRange(color[2], CML_RGB_B_MIN, CML_RGB_B_MAX);
}

CMLBool RGBColor::inside(){
  return (insideR() && insideG() && insideB());
}

void RGBColor::clamp(){
  cmlClampRGB(color, 1);
}

size_t RGBColor::getNumChannels() const {return 3;}

// ///////////////////////////////////////
// Converting to different color spaces
// ///////////////////////////////////////

CMLColorType RGBColor::getColorType() const{
  return CML_COLOR_RGB;
}

void RGBColor::from8BitBuffer(const uint8* input){
  cmlData8ToRGB(cmlcm, color, input, 1);
}
void RGBColor::from16BitBuffer(const uint16* input){
  cmlData16ToRGB(cmlcm, color, input, 1);
}
void RGBColor::fromFloatBuffer(const float* input){
  cmlCpy3(color, input);
}
void RGBColor::to8BitBuffer(uint8* output) const {
  cmlRGBToData8(cmlcm, output, color, 1);
}
void RGBColor::to16BitBuffer(uint16* output) const {
  cmlRGBToData16(cmlcm, output, color, 1);
}
void RGBColor::toFloatBuffer(float* output) const {
  cmlCpy3(output, color);
}


void RGBColor::fromNormedBuffer(const float* input){
  cmlNormedInputToRGB(color, input, 1);
}
void RGBColor::toNormedBuffer(float* output) const {
  cmlRGBToNormedOutput(output, color, 1);
}
void RGBColor::fromNormedCartesianBuffer(const float* input){
  cmlNormedInputToRGB(color, input, 1);
}
void RGBColor::toNormedCartesianBuffer(float* output) const {
  cmlRGBToNormedOutput(output, color, 1);
}


void RGBColor::fromGrayBuffer(const float* src) {cmlGrayToRGB (cmlcm, color, src, 1);}
void RGBColor::fromXYZBuffer(const float* src)  {cmlXYZToRGB  (cmlcm, color, src, 1);}
void RGBColor::fromYuvBuffer(const float* src)  {cmlYuvToRGB  (cmlcm, color, src, 1);}
void RGBColor::fromYupvpBuffer(const float* src){cmlYupvpToRGB(cmlcm, color, src, 1);}
void RGBColor::fromYxyBuffer(const float* src)  {cmlYxyToRGB  (cmlcm, color, src, 1);}
void RGBColor::fromLabBuffer(const float* src)  {cmlLabToRGB  (cmlcm, color, src, 1);}
void RGBColor::fromLchBuffer(const float* src)  {cmlLchToRGB  (cmlcm, color, src, 1);}
void RGBColor::fromLuvBuffer(const float* src)  {cmlLuvToRGB  (cmlcm, color, src, 1);}
void RGBColor::fromRGBBuffer(const float* src)  {cmlRGBToRGB  (cmlcm, color, src, 1);}
void RGBColor::fromYCbCrBuffer(const float* src){cmlYCbCrToRGB(cmlcm, color, src, 1);}
void RGBColor::fromHSVBuffer(const float* src)  {cmlHSVToRGB  (cmlcm, color, src, 1);}
void RGBColor::fromHSLBuffer(const float* src)  {cmlHSLToRGB  (cmlcm, color, src, 1);}
void RGBColor::fromCMYKBuffer(const float* src) {cmlCMYKToRGB (cmlcm, color, src, 1);}

void RGBColor::toGrayBuffer(float* dest) const {cmlRGBToGray (cmlcm, dest, color, 1);}
void RGBColor::toXYZBuffer(float* dest) const  {cmlRGBToXYZ  (cmlcm, dest, color, 1);}
void RGBColor::toYuvBuffer(float* dest) const  {cmlRGBToYuv  (cmlcm, dest, color, 1);}
void RGBColor::toYupvpBuffer(float* dest) const{cmlRGBToYupvp(cmlcm, dest, color, 1);}
void RGBColor::toYxyBuffer(float* dest) const  {cmlRGBToYxy  (cmlcm, dest, color, 1);}
void RGBColor::toLabBuffer(float* dest) const  {cmlRGBToLab  (cmlcm, dest, color, 1);}
void RGBColor::toLchBuffer(float* dest) const  {cmlRGBToLch  (cmlcm, dest, color, 1);}
void RGBColor::toLuvBuffer(float* dest) const  {cmlRGBToLuv  (cmlcm, dest, color, 1);}
void RGBColor::toRGBBuffer(float* dest) const  {cmlRGBToRGB  (cmlcm, dest, color, 1);}
void RGBColor::toYCbCrBuffer(float* dest) const{cmlRGBToYCbCr(cmlcm, dest, color, 1);}
void RGBColor::toHSVBuffer(float* dest) const  {cmlRGBToHSV  (cmlcm, dest, color, 1);}
void RGBColor::toHSLBuffer(float* dest) const  {cmlRGBToHSL  (cmlcm, dest, color, 1);}
void RGBColor::toCMYKBuffer(float* dest) const {cmlRGBToCMYK (cmlcm, dest, color, 1);}



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

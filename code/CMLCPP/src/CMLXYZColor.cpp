
#include "CMLColor.h"

// ///////////////////////////////////////
// Constructors and initialization methods
// ///////////////////////////////////////

XYZColor::XYZColor(){}
XYZColor::~XYZColor(){}

XYZColor::XYZColor(float X, float Y, float Z){
  init(X, Y, Z);
}

XYZColor::XYZColor(const Color& anycolor){
  operator =(anycolor);
}

XYZColor::XYZColor(const XYZColor& xyz){
  operator =(xyz);
}

void XYZColor::init(float X, float Y, float Z){
  cmlSet3(color, X, Y, Z);
}

XYZColor& XYZColor::operator =(const Color& anycolor){
  anycolor.toXYZBuffer(color);
  return *this;
}

XYZColor& XYZColor::operator =(const XYZColor& xyz){
  cmlCpy3(color, xyz);
  return *this;
}

// ///////////////////////////////////////
// Mathematical operators in cartesian space
// ///////////////////////////////////////

XYZColor XYZColor::operator +() const {
  return XYZColor(*this);
}

XYZColor XYZColor::operator -() const {
  return XYZColor(-color[0], -color[1], -color[2]);
}

XYZColor XYZColor::operator +(const Color& anycolor) const {
  float buf[3];
  anycolor.toXYZBuffer(buf);
  return XYZColor(color[0]+buf[0], color[1]+buf[1], color[2]+buf[2]);
}

XYZColor XYZColor::operator -(const Color& anycolor) const {
  float buf[3];
  anycolor.toXYZBuffer(buf);
  return XYZColor(color[0]-buf[0], color[1]-buf[1], color[2]-buf[2]);
}

XYZColor XYZColor::operator *(const float factor) const {
  return XYZColor(color[0]*factor, color[1]*factor, color[2]*factor);
}

XYZColor XYZColor::operator /(const float divisor) const {
  float factor = cmlInverse(divisor);
  return XYZColor(color[0]*factor, color[1]*factor, color[2]*factor);
}

XYZColor& XYZColor::operator +=(const Color& anycolor){
  float buf[3];
  anycolor.toXYZBuffer(buf);
  cmlAdd3(color, buf);
  return *this;
}

XYZColor& XYZColor::operator -=(const Color& anycolor){
  float buf[3];
  anycolor.toXYZBuffer(buf);
  cmlSub3(color, buf);
  return *this;
}

XYZColor& XYZColor::operator *=(const float factor){
  cmlMul3(color, factor);
  return *this;
}

XYZColor& XYZColor::operator /=(const float divisor){
  cmlDiv3(color, divisor);
  return *this;
}

float XYZColor::dot(const XYZColor& xyz) const {
  return cmlDot3(color, xyz.color);
}

float XYZColor::length() const {
  return cmlLength3(color);
}

CMLBool XYZColor::operator ==(const XYZColor& xyz) const {
  return cmlEqual3(color, xyz.color);
}

CMLBool XYZColor::operator !=(const XYZColor& xyz) const {
  return !cmlEqual3(color, xyz.color);
}

// ///////////////////////////////////////
// various methods
// ///////////////////////////////////////

XYZColor::operator const float*() const {return color;}
XYZColor::operator       float*()       {return color;}

XYZColor XYZColor::getInverse() {
  float buf[3];
  cmlCpy3(buf, color);
  cmlInvertXYZ(buf, 1);
  return XYZColor(buf[0], buf[1], buf[2]);
}

void XYZColor::invert(){
  cmlInvertXYZ(color, 1);
}

CMLBool XYZColor::insideX(){
  return cmlInRange(color[0], CML_XYZ_X_MIN, CML_XYZ_X_MAX);
}

CMLBool XYZColor::insideY(){
  return cmlInRange(color[1], CML_XYZ_Y_MIN, CML_XYZ_Y_MAX);
}

CMLBool XYZColor::insideZ(){
  return cmlInRange(color[2], CML_XYZ_Z_MIN, CML_XYZ_Z_MAX);
}

CMLBool XYZColor::inside(){
  return (insideX() && insideY() && insideZ());
}

void XYZColor::clamp(){
  cmlClampXYZ(color, 1);
}

size_t XYZColor::getNumChannels() const {return 3;}

// ///////////////////////////////////////
// Converting to different color spaces
// ///////////////////////////////////////

CMLColorType XYZColor::getColorType() const{
  return CML_COLOR_XYZ;
}

void XYZColor::from8BitBuffer(const uint8* input){
  cmlData8ToXYZ(cmlcm, color, input, 1);
}
void XYZColor::from16BitBuffer(const uint16* input){
  cmlData16ToXYZ(cmlcm, color, input, 1);
}
void XYZColor::fromFloatBuffer(const float* input){
  cmlCpy3(color, input);
}
void XYZColor::to8BitBuffer(uint8* output) const {
  cmlXYZToData8(cmlcm, output, color, 1);
}
void XYZColor::to16BitBuffer(uint16* output) const {
  cmlXYZToData16(cmlcm, output, color, 1);
}
void XYZColor::toFloatBuffer(float* output) const {
  cmlCpy3(output, color);
}


void XYZColor::fromNormedBuffer(const float* input){
  cmlNormedInputToXYZ(color, input, 1);
}
void XYZColor::toNormedBuffer(float* output) const {
  cmlXYZToNormedOutput(output, color, 1);
}
void XYZColor::fromNormedCartesianBuffer(const float* input){
  cmlNormedInputToXYZ(color, input, 1);
}
void XYZColor::toNormedCartesianBuffer(float* output) const {
  cmlXYZToNormedOutput(output, color, 1);
}


void XYZColor::fromGrayBuffer(const float* src) {cmlGrayToXYZ (cmlcm, color, src, 1);}
void XYZColor::fromXYZBuffer(const float* src)  {cmlXYZToXYZ  (cmlcm, color, src, 1);}
void XYZColor::fromYuvBuffer(const float* src)  {cmlYuvToXYZ  (cmlcm, color, src, 1);}
void XYZColor::fromYupvpBuffer(const float* src){cmlYupvpToXYZ(cmlcm, color, src, 1);}
void XYZColor::fromYxyBuffer(const float* src)  {cmlYxyToXYZ  (cmlcm, color, src, 1);}
void XYZColor::fromLabBuffer(const float* src)  {cmlLabToXYZ  (cmlcm, color, src, 1);}
void XYZColor::fromLchBuffer(const float* src)  {cmlLchToXYZ  (cmlcm, color, src, 1);}
void XYZColor::fromLuvBuffer(const float* src)  {cmlLuvToXYZ  (cmlcm, color, src, 1);}
void XYZColor::fromRGBBuffer(const float* src)  {cmlRGBToXYZ  (cmlcm, color, src, 1);}
void XYZColor::fromYCbCrBuffer(const float* src){cmlYCbCrToXYZ(cmlcm, color, src, 1);}
void XYZColor::fromHSVBuffer(const float* src)  {cmlHSVToXYZ  (cmlcm, color, src, 1);}
void XYZColor::fromHSLBuffer(const float* src)  {cmlHSLToXYZ  (cmlcm, color, src, 1);}
void XYZColor::fromCMYKBuffer(const float* src) {cmlCMYKToXYZ (cmlcm, color, src, 1);}

void XYZColor::toGrayBuffer(float* dest) const {cmlXYZToGray (cmlcm, dest, color, 1);}
void XYZColor::toXYZBuffer(float* dest) const  {cmlXYZToXYZ  (cmlcm, dest, color, 1);}
void XYZColor::toYuvBuffer(float* dest) const  {cmlXYZToYuv  (cmlcm, dest, color, 1);}
void XYZColor::toYupvpBuffer(float* dest) const{cmlXYZToYupvp(cmlcm, dest, color, 1);}
void XYZColor::toYxyBuffer(float* dest) const  {cmlXYZToYxy  (cmlcm, dest, color, 1);}
void XYZColor::toLabBuffer(float* dest) const  {cmlXYZToLab  (cmlcm, dest, color, 1);}
void XYZColor::toLchBuffer(float* dest) const  {cmlXYZToLch  (cmlcm, dest, color, 1);}
void XYZColor::toLuvBuffer(float* dest) const  {cmlXYZToLuv  (cmlcm, dest, color, 1);}
void XYZColor::toRGBBuffer(float* dest) const  {cmlXYZToRGB  (cmlcm, dest, color, 1);}
void XYZColor::toYCbCrBuffer(float* dest) const{cmlXYZToYCbCr(cmlcm, dest, color, 1);}
void XYZColor::toHSVBuffer(float* dest) const  {cmlXYZToHSV  (cmlcm, dest, color, 1);}
void XYZColor::toHSLBuffer(float* dest) const  {cmlXYZToHSL  (cmlcm, dest, color, 1);}
void XYZColor::toCMYKBuffer(float* dest) const {cmlXYZToCMYK (cmlcm, dest, color, 1);}



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

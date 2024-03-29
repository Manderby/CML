
#include "CMLColor.h"

// ///////////////////////////////////////
// Constructors and initialization methods
// ///////////////////////////////////////

YupvpColor::YupvpColor(){}
YupvpColor::~YupvpColor(){}

YupvpColor::YupvpColor(float Y, float U, float V){
  init(Y, U, V);
}

YupvpColor::YupvpColor(const Color& anycolor){
  operator =(anycolor);
}

YupvpColor::YupvpColor(const YupvpColor& yupvp){
  operator =(yupvp);
}

void YupvpColor::init(float Y, float U, float V){
  cmlSet3(color, Y, U, V);
}

YupvpColor& YupvpColor::operator =(const Color& anycolor){
  anycolor.toYupvpBuffer(color);
  return *this;
}

YupvpColor& YupvpColor::operator =(const YupvpColor& yupvp){
  cmlCpy3(color, yupvp);
  return *this;
}

// ///////////////////////////////////////
// Mathematical operators in cartesian space
// ///////////////////////////////////////

YupvpColor YupvpColor::operator +() const {
  return YupvpColor(*this);
}

YupvpColor YupvpColor::operator -() const {
  return YupvpColor(-color[0], -color[1], -color[2]);
}

YupvpColor YupvpColor::operator +(const Color& anycolor) const {
  float buf[3];
  anycolor.toYupvpBuffer(buf);
  return YupvpColor(color[0]+buf[0], color[1]+buf[1], color[2]+buf[2]);
}

YupvpColor YupvpColor::operator -(const Color& anycolor) const {
  float buf[3];
  anycolor.toYupvpBuffer(buf);
  return YupvpColor(color[0]-buf[0], color[1]-buf[1], color[2]-buf[2]);
}

YupvpColor YupvpColor::operator *(const float factor) const {
  return YupvpColor(color[0]*factor, color[1]*factor, color[2]*factor);
}

YupvpColor YupvpColor::operator /(const float divisor) const {
  float factor = cmlInverse(divisor);
  return YupvpColor(color[0]*factor, color[1]*factor, color[2]*factor);
}

YupvpColor& YupvpColor::operator +=(const Color& anycolor){
  float buf[3];
  anycolor.toYupvpBuffer(buf);
  cmlAdd3(color, buf);
  return *this;
}

YupvpColor& YupvpColor::operator -=(const Color& anycolor){
  float buf[3];
  anycolor.toYupvpBuffer(buf);
  cmlSub3(color, buf);
  return *this;
}

YupvpColor& YupvpColor::operator *=(const float factor){
  cmlMul3(color, factor);
  return *this;
}

YupvpColor& YupvpColor::operator /=(const float divisor){
  cmlDiv3(color, divisor);
  return *this;
}

float YupvpColor::dot(const YupvpColor& yupvp) const {
  return cmlDot3(color, yupvp.color);
}

float YupvpColor::length() const {
  return cmlLength3(color);
}

CMLBool YupvpColor::operator ==(const YupvpColor& yupvp) const {
  return cmlEqual3(color, yupvp.color);
}

CMLBool YupvpColor::operator !=(const YupvpColor& yupvp) const {
  return !cmlEqual3(color, yupvp.color);
}

// ///////////////////////////////////////
// various methods
// ///////////////////////////////////////

YupvpColor::operator const float*() const {return color;}
YupvpColor::operator       float*()       {return color;}

YupvpColor YupvpColor::getInverse(){
  float buf[3];
  cmlCpy3(buf, color);
  cmlInvertYupvp(buf, 1);
  return YupvpColor(buf[0], buf[1], buf[2]);
}

void YupvpColor::invert(){
  cmlInvertYupvp(color, 1);
}

CMLBool YupvpColor::insideY(){
  return cmlInRange(color[0], CML_Yupvp_Y_MIN, CML_Yupvp_Y_MAX);
}

CMLBool YupvpColor::insideU() {
  return cmlInRange(color[1], CML_Yupvp_up_MIN, CML_Yupvp_up_MAX);
}

CMLBool YupvpColor::insideV(){
  return cmlInRange(color[2], CML_Yupvp_vp_MIN, CML_Yupvp_vp_MAX);
}

CMLBool YupvpColor::inside(){
  return (insideY() && insideU() && insideV());
}

void YupvpColor::clamp(){
  cmlClampYupvp(color, 1);
}

size_t YupvpColor::getNumChannels() const {return 3;}

// ///////////////////////////////////////
// Converting to different color spaces
// ///////////////////////////////////////

CMLColorType YupvpColor::getColorType() const{
  return CML_COLOR_Yupvp;
}

void YupvpColor::from8BitBuffer(const uint8* input){
  cmlData8ToYupvp(cmlcm, color, input, 1);
}
void YupvpColor::from16BitBuffer(const uint16* input){
  cmlData16ToYupvp(cmlcm, color, input, 1);
}
void YupvpColor::fromFloatBuffer(const float* input){
  cmlCpy3(color, input);
}
void YupvpColor::to8BitBuffer(uint8* output) const {
  cmlYupvpToData8(cmlcm, output, color, 1);
}
void YupvpColor::to16BitBuffer(uint16* output) const {
  cmlYupvpToData16(cmlcm, output, color, 1);
}
void YupvpColor::toFloatBuffer(float* output) const {
  cmlCpy3(output, color);
}


void YupvpColor::fromNormedBuffer(const float* input){
  cmlNormedInputToYupvp(color, input, 1);
}
void YupvpColor::toNormedBuffer(float* output) const {
  cmlYupvpToNormedOutput(output, color, 1);
}
void YupvpColor::fromNormedCartesianBuffer(const float* input){
  cmlNormedInputToYupvp(color, input, 1);
}
void YupvpColor::toNormedCartesianBuffer(float* output) const {
  cmlYupvpToNormedOutput(output, color, 1);
}


void YupvpColor::fromGrayBuffer(const float* src) {cmlGrayToYupvp (cmlcm, color, src, 1);}
void YupvpColor::fromXYZBuffer(const float* src)  {cmlXYZToYupvp  (cmlcm, color, src, 1);}
void YupvpColor::fromYuvBuffer(const float* src)  {cmlYuvToYupvp  (cmlcm, color, src, 1);}
void YupvpColor::fromYupvpBuffer(const float* src){cmlYupvpToYupvp(cmlcm, color, src, 1);}
void YupvpColor::fromYxyBuffer(const float* src)  {cmlYxyToYupvp  (cmlcm, color, src, 1);}
void YupvpColor::fromLabBuffer(const float* src)  {cmlLabToYupvp  (cmlcm, color, src, 1);}
void YupvpColor::fromLchBuffer(const float* src)  {cmlLchToYupvp  (cmlcm, color, src, 1);}
void YupvpColor::fromLuvBuffer(const float* src)  {cmlLuvToYupvp  (cmlcm, color, src, 1);}
void YupvpColor::fromRGBBuffer(const float* src)  {cmlRGBToYupvp  (cmlcm, color, src, 1);}
void YupvpColor::fromYCbCrBuffer(const float* src){cmlYCbCrToYupvp(cmlcm, color, src, 1);}
void YupvpColor::fromHSVBuffer(const float* src)  {cmlHSVToYupvp  (cmlcm, color, src, 1);}
void YupvpColor::fromHSLBuffer(const float* src)  {cmlHSLToYupvp  (cmlcm, color, src, 1);}
void YupvpColor::fromCMYKBuffer(const float* src) {cmlCMYKToYupvp (cmlcm, color, src, 1);}

void YupvpColor::toGrayBuffer(float* dest) const {cmlYupvpToGray (cmlcm, dest, color, 1);}
void YupvpColor::toXYZBuffer(float* dest) const  {cmlYupvpToXYZ  (cmlcm, dest, color, 1);}
void YupvpColor::toYuvBuffer(float* dest) const  {cmlYupvpToYuv  (cmlcm, dest, color, 1);}
void YupvpColor::toYupvpBuffer(float* dest) const{cmlYupvpToYupvp(cmlcm, dest, color, 1);}
void YupvpColor::toYxyBuffer(float* dest) const  {cmlYupvpToYxy  (cmlcm, dest, color, 1);}
void YupvpColor::toLabBuffer(float* dest) const  {cmlYupvpToLab  (cmlcm, dest, color, 1);}
void YupvpColor::toLchBuffer(float* dest) const  {cmlYupvpToLch  (cmlcm, dest, color, 1);}
void YupvpColor::toLuvBuffer(float* dest) const  {cmlYupvpToLuv  (cmlcm, dest, color, 1);}
void YupvpColor::toRGBBuffer(float* dest) const  {cmlYupvpToRGB  (cmlcm, dest, color, 1);}
void YupvpColor::toYCbCrBuffer(float* dest) const{cmlYupvpToYCbCr(cmlcm, dest, color, 1);}
void YupvpColor::toHSVBuffer(float* dest) const  {cmlYupvpToHSV  (cmlcm, dest, color, 1);}
void YupvpColor::toHSLBuffer(float* dest) const  {cmlYupvpToHSL  (cmlcm, dest, color, 1);}
void YupvpColor::toCMYKBuffer(float* dest) const {cmlYupvpToCMYK (cmlcm, dest, color, 1);}



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

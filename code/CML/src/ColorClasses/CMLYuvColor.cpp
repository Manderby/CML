
#include "CMLColor.h"

// ///////////////////////////////////////
// Constructors and initialization methods
// ///////////////////////////////////////

YuvColor::YuvColor(){}
YuvColor::~YuvColor(){}

YuvColor::YuvColor(float Y, float U, float V){
  init(Y, U, V);
}

YuvColor::YuvColor(const Color& anycolor){
  operator =(anycolor);
}

YuvColor::YuvColor(const YuvColor& yuv){
  operator =(yuv);
}

void YuvColor::init(float Y, float U, float V){
  cmlSet3(color, Y, U, V);
}

YuvColor& YuvColor::operator =(const Color& anycolor){
  anycolor.toYuvBuffer(color);
  return *this;
}

YuvColor& YuvColor::operator =(const YuvColor& yuv){
  cmlCpy3(color, yuv);
  return *this;
}

// ///////////////////////////////////////
// Mathematical operators in cartesian space
// ///////////////////////////////////////

YuvColor YuvColor::operator +() const {
  return YuvColor(*this);
}

YuvColor YuvColor::operator -() const {
  return YuvColor(-color[0], -color[1], -color[2]);
}

YuvColor YuvColor::operator +(const Color& anycolor) const {
  float buf[3];
  anycolor.toYuvBuffer(buf);
  return YuvColor(color[0]+buf[0], color[1]+buf[1], color[2]+buf[2]);
}

YuvColor YuvColor::operator -(const Color& anycolor) const {
  float buf[3];
  anycolor.toYuvBuffer(buf);
  return YuvColor(color[0]-buf[0], color[1]-buf[1], color[2]-buf[2]);
}

YuvColor YuvColor::operator *(const float factor) const {
  return YuvColor(color[0]*factor, color[1]*factor, color[2]*factor);
}

YuvColor YuvColor::operator /(const float divisor) const {
  float factor = cmlInverse(divisor);
  return YuvColor(color[0]*factor, color[1]*factor, color[2]*factor);
}

YuvColor& YuvColor::operator +=(const Color& anycolor){
  float buf[3];
  anycolor.toYuvBuffer(buf);
  cmlAdd3(color, buf);
  return *this;
}

YuvColor& YuvColor::operator -=(const Color& anycolor){
  float buf[3];
  anycolor.toYuvBuffer(buf);
  cmlSub3(color, buf);
  return *this;
}

YuvColor& YuvColor::operator *=(const float factor){
  cmlMul3(color, factor);
  return *this;
}

YuvColor& YuvColor::operator /=(const float divisor){
  cmlDiv3(color, divisor);
  return *this;
}

float YuvColor::dot(const YuvColor& yuv) const {
  return cmlDot3(color, yuv.color);
}

float YuvColor::length() const {
  return cmlLength3(color);
}

CMLBool YuvColor::operator ==(const YuvColor& yuv) const {
  return cmlEqual3(color, yuv.color);
}

CMLBool YuvColor::operator !=(const YuvColor& yuv) const {
  return !cmlEqual3(color, yuv.color);
}

// ///////////////////////////////////////
// various methods
// ///////////////////////////////////////

YuvColor::operator const float*() const {return color;}
YuvColor::operator       float*()       {return color;}

YuvColor YuvColor::getInverse(){
  float buf[3];
  cmlCpy3(buf, color);
  cmlInvertYuv(buf, 1);
  return YuvColor(buf[0], buf[1], buf[2]);
}

void YuvColor::invert(){
  cmlInvertYuv(color, 1);
}

CMLBool YuvColor::insideY(){
  return CMLInRange(color[0], CML_Yuv_Y_MIN, CML_Yuv_Y_MAX);
}

CMLBool YuvColor::insideU() {
  return CMLInRange(color[1], CML_Yuv_u_MIN, CML_Yuv_u_MAX);
}

CMLBool YuvColor::insideV(){
  return CMLInRange(color[2], CML_Yuv_v_MIN, CML_Yuv_v_MAX);
}

CMLBool YuvColor::inside(){
  return (insideY() && insideU() && insideV());
}

void YuvColor::clamp(){
  cmlClampYuv(color, 1);
}

CMLuint32 YuvColor::getNumChannels() const {return 3;}

// ///////////////////////////////////////
// Converting to different color spaces
// ///////////////////////////////////////

CMLColorType YuvColor::getColorType() const{
  return CML_COLOR_Yuv;
}

void YuvColor::from8BitBuffer(const CMLByte* input){
  cmlYuvWithData8(cmlcm, color, input, 1);
}
void YuvColor::from16BitBuffer(const CMLWord* input){
  cmlYuvWithData16(cmlcm, color, input, 1);
}
void YuvColor::fromFloatBuffer(const float* input){
  cmlCpy3(color, input);
}
void YuvColor::to8BitBuffer(CMLByte* output) const {
  cmlData8WithYuv(cmlcm, output, color, 1);
}
void YuvColor::to16BitBuffer(CMLWord* output) const {
  cmlData16WithYuv(cmlcm, output, color, 1);
}
void YuvColor::toFloatBuffer(float* output) const {
  cmlCpy3(output, color);
}


void YuvColor::fromNormedBuffer(const float* input){
  cmlYuvWithNormedInput(color, input, 1);
}
void YuvColor::toNormedBuffer(float* output) const {
  cmlNormedOutputWithYuv(output, color, 1);
}
void YuvColor::fromNormedCartesianBuffer(const float* input){
  cmlYuvWithNormedInput(color, input, 1);
}
void YuvColor::toNormedCartesianBuffer(float* output) const {
  cmlNormedOutputWithYuv(output, color, 1);
}


void YuvColor::fromGrayBuffer(const float* src) {CMLGraytoYuv (cmlcm, color, src, 1);}
void YuvColor::fromXYZBuffer(const float* src)  {CMLXYZtoYuv  (cmlcm, color, src, 1);}
void YuvColor::fromYuvBuffer(const float* src)  {CMLYuvtoYuv  (cmlcm, color, src, 1);}
void YuvColor::fromYupvpBuffer(const float* src){CMLYupvptoYuv(cmlcm, color, src, 1);}
void YuvColor::fromYxyBuffer(const float* src)  {CMLYxytoYuv  (cmlcm, color, src, 1);}
void YuvColor::fromLabBuffer(const float* src)  {CMLLabtoYuv  (cmlcm, color, src, 1);}
void YuvColor::fromLchBuffer(const float* src)  {CMLLchtoYuv  (cmlcm, color, src, 1);}
void YuvColor::fromLuvBuffer(const float* src)  {CMLLuvtoYuv  (cmlcm, color, src, 1);}
void YuvColor::fromRGBBuffer(const float* src)  {CMLRGBtoYuv  (cmlcm, color, src, 1);}
void YuvColor::fromYCbCrBuffer(const float* src){CMLYCbCrtoYuv(cmlcm, color, src, 1);}
void YuvColor::fromHSVBuffer(const float* src)  {CMLHSVtoYuv  (cmlcm, color, src, 1);}
void YuvColor::fromHSLBuffer(const float* src)  {CMLHSLtoYuv  (cmlcm, color, src, 1);}
void YuvColor::fromCMYKBuffer(const float* src) {CMLCMYKtoYuv (cmlcm, color, src, 1);}

void YuvColor::toGrayBuffer(float* dest) const {CMLYuvtoGray (cmlcm, dest, color, 1);}
void YuvColor::toXYZBuffer(float* dest) const  {CMLYuvtoXYZ  (cmlcm, dest, color, 1);}
void YuvColor::toYuvBuffer(float* dest) const  {CMLYuvtoYuv  (cmlcm, dest, color, 1);}
void YuvColor::toYupvpBuffer(float* dest) const{CMLYuvtoYupvp(cmlcm, dest, color, 1);}
void YuvColor::toYxyBuffer(float* dest) const  {CMLYuvtoYxy  (cmlcm, dest, color, 1);}
void YuvColor::toLabBuffer(float* dest) const  {CMLYuvtoLab  (cmlcm, dest, color, 1);}
void YuvColor::toLchBuffer(float* dest) const  {CMLYuvtoLch  (cmlcm, dest, color, 1);}
void YuvColor::toLuvBuffer(float* dest) const  {CMLYuvtoLuv  (cmlcm, dest, color, 1);}
void YuvColor::toRGBBuffer(float* dest) const  {CMLYuvtoRGB  (cmlcm, dest, color, 1);}
void YuvColor::toYCbCrBuffer(float* dest) const{CMLYuvtoYCbCr(cmlcm, dest, color, 1);}
void YuvColor::toHSVBuffer(float* dest) const  {CMLYuvtoHSV  (cmlcm, dest, color, 1);}
void YuvColor::toHSLBuffer(float* dest) const  {CMLYuvtoHSL  (cmlcm, dest, color, 1);}
void YuvColor::toCMYKBuffer(float* dest) const {CMLYuvtoCMYK (cmlcm, dest, color, 1);}



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

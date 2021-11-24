
#include "CMLColor.h"

// ///////////////////////////////////////
// Constructors and initialization methods
// ///////////////////////////////////////

LabColor::LabColor(){}
LabColor::~LabColor(){}

LabColor::LabColor(float L){
  init(L, 0, 0);
}

LabColor::LabColor(float L, float a, float b){
  init(L, a, b);
}

LabColor::LabColor(const Color& anycolor){
  operator =(anycolor);
}

LabColor::LabColor(const LabColor& lab){
  operator =(lab);
}

void LabColor::init(float L, float a, float b){
  cmlSet3(color, L, a, b);
}

LabColor& LabColor::operator =(const Color& anycolor){
  anycolor.toLabBuffer(color);
  return *this;
}

LabColor& LabColor::operator =(const LabColor& lab){
  cmlCpy3(color, lab);
  return *this;
}

// ///////////////////////////////////////
// Mathematical operators in cartesian space
// ///////////////////////////////////////

LabColor LabColor::operator +() const {
  return LabColor(*this);
}

LabColor LabColor::operator -() const {
  return LabColor(-color[0], -color[1], -color[2]);
}

LabColor LabColor::operator +(const Color& anycolor) const {
  float buf[3];
  anycolor.toLabBuffer(buf);
  return LabColor(color[0]+buf[0], color[1]+buf[1], color[2]+buf[2]);
}

LabColor LabColor::operator -(const Color& anycolor) const {
  float buf[3];
  anycolor.toLabBuffer(buf);
  return LabColor(color[0]-buf[0], color[1]-buf[1], color[2]-buf[2]);
}

LabColor LabColor::operator *(const float factor) const {
  return LabColor(color[0]*factor, color[1]*factor, color[2]*factor);
}

LabColor LabColor::operator /(const float divisor) const {
  float factor = cmlInverse(divisor);
  return LabColor(color[0]*factor, color[1]*factor, color[2]*factor);
}

LabColor& LabColor::operator +=(const Color& anycolor){
  float buf[3];
  anycolor.toLabBuffer(buf);
  cmlAdd3(color, buf);
  return *this;
}

LabColor& LabColor::operator -=(const Color& anycolor){
  float buf[3];
  anycolor.toLabBuffer(buf);
  cmlSub3(color, buf);
  return *this;
}

LabColor& LabColor::operator *=(const float factor){
  cmlMul3(color, factor);
  return *this;
}

LabColor& LabColor::operator /=(const float divisor){
  cmlDiv3(color, divisor);
  return *this;
}

float LabColor::dot(const LabColor& lab) const {
  return cmlDot3(color, lab.color);
}

float LabColor::length() const {
  return cmlLength3(color);
}

CMLBool LabColor::operator ==(const LabColor& lab) const {
  return cmlEqual3(color, lab.color);
}

CMLBool LabColor::operator !=(const LabColor& lab) const {
  return !cmlEqual3(color, lab.color);
}


// ///////////////////////////////////////
// various methods
// ///////////////////////////////////////

LabColor::operator const float*() const {return color;}
LabColor::operator       float*()       {return color;}

LabColor LabColor::getInverse() {
  float buf[3];
  cmlCpy3(buf, color);
  cmlInvertLab(buf, 1);
  return LabColor(buf[0], buf[1], buf[2]);
}

void LabColor::invert(){
  cmlInvertLab(color, 1);
}

CMLBool LabColor::insideL() {
  return CMLInRange(color[0], CML_Lab_L_MIN, CML_Lab_L_MAX);
}

CMLBool LabColor::insidea() {
  return CMLInRange(color[1], CML_Lab_a_MIN, CML_Lab_a_MAX);
}

CMLBool LabColor::insideb() {
  return CMLInRange(color[2], CML_Lab_b_MIN, CML_Lab_b_MAX);
}

CMLBool LabColor::inside()  {
  return (insideL() && insidea() && insideb());
}

void LabColor::clamp(){
  CMLclampLab(color, 1);
}

CMLuint32 LabColor::getNumChannels() const {return 3;}

// ///////////////////////////////////////
// Converting to different color spaces
// ///////////////////////////////////////

CMLColorType LabColor::getColorType() const{
  return CML_COLOR_Lab;
}

void LabColor::from8BitBuffer(const CMLByte* input){
  cmlLabWithData8(cmlcm, color, input, 1);
}
void LabColor::from16BitBuffer(const CMLWord* input){
  cmlLabWithData16(cmlcm, color, input, 1);
}
void LabColor::fromFloatBuffer(const float* input){
  cmlCpy3(color, input);
}
void LabColor::to8BitBuffer(CMLByte* output) const {
  cmlData8WithLab(cmlcm, output, color, 1);
}
void LabColor::to16BitBuffer(CMLWord* output) const {
  cmlData16WithLab(cmlcm, output, color, 1);
}
void LabColor::toFloatBuffer(float* output) const {
  cmlCpy3(output, color);
}


void LabColor::fromNormedBuffer(const float* input){
  cmlLabWithNormedInput(color, input, 1);
}
void LabColor::toNormedBuffer(float* output) const {
  cmlNormedOutputWithLab(output, color, 1);
}
void LabColor::fromNormedCartesianBuffer(const float* input){
  cmlLabWithNormedInput(color, input, 1);
}
void LabColor::toNormedCartesianBuffer(float* output) const {
  cmlNormedOutputWithLab(output, color, 1);
}


void LabColor::fromGrayBuffer(const float* src) {CMLGraytoLab (cmlcm, color, src, 1);}
void LabColor::fromXYZBuffer(const float* src)  {CMLXYZtoLab  (cmlcm, color, src, 1);}
void LabColor::fromYuvBuffer(const float* src)  {CMLYuvtoLab  (cmlcm, color, src, 1);}
void LabColor::fromYupvpBuffer(const float* src){CMLYupvptoLab(cmlcm, color, src, 1);}
void LabColor::fromYxyBuffer(const float* src)  {CMLYxytoLab  (cmlcm, color, src, 1);}
void LabColor::fromLabBuffer(const float* src)  {CMLLabtoLab  (cmlcm, color, src, 1);}
void LabColor::fromLchBuffer(const float* src)  {CMLLchtoLab  (cmlcm, color, src, 1);}
void LabColor::fromLuvBuffer(const float* src)  {CMLLuvtoLab  (cmlcm, color, src, 1);}
void LabColor::fromRGBBuffer(const float* src)  {CMLRGBtoLab  (cmlcm, color, src, 1);}
void LabColor::fromYCbCrBuffer(const float* src){CMLYCbCrtoLab(cmlcm, color, src, 1);}
void LabColor::fromHSVBuffer(const float* src)  {CMLHSVtoLab  (cmlcm, color, src, 1);}
void LabColor::fromHSLBuffer(const float* src)  {CMLHSLtoLab  (cmlcm, color, src, 1);}
void LabColor::fromCMYKBuffer(const float* src) {CMLCMYKtoLab (cmlcm, color, src, 1);}


void LabColor::toGrayBuffer(float* dest) const {CMLLabtoGray (cmlcm, dest, color, 1);}
void LabColor::toXYZBuffer(float* dest) const  {CMLLabtoXYZ  (cmlcm, dest, color, 1);}
void LabColor::toYuvBuffer(float* dest) const  {CMLLabtoYuv  (cmlcm, dest, color, 1);}
void LabColor::toYupvpBuffer(float* dest) const{CMLLabtoYupvp(cmlcm, dest, color, 1);}
void LabColor::toYxyBuffer(float* dest) const  {CMLLabtoYxy  (cmlcm, dest, color, 1);}
void LabColor::toLabBuffer(float* dest) const  {CMLLabtoLab  (cmlcm, dest, color, 1);}
void LabColor::toLchBuffer(float* dest) const  {CMLLabtoLch  (cmlcm, dest, color, 1);}
void LabColor::toLuvBuffer(float* dest) const  {CMLLabtoLuv  (cmlcm, dest, color, 1);}
void LabColor::toRGBBuffer(float* dest) const  {CMLLabtoRGB  (cmlcm, dest, color, 1);}
void LabColor::toYCbCrBuffer(float* dest) const{CMLLabtoYCbCr(cmlcm, dest, color, 1);}
void LabColor::toHSVBuffer(float* dest) const  {CMLLabtoHSV  (cmlcm, dest, color, 1);}
void LabColor::toHSLBuffer(float* dest) const  {CMLLabtoHSL  (cmlcm, dest, color, 1);}
void LabColor::toCMYKBuffer(float* dest) const {CMLLabtoCMYK (cmlcm, dest, color, 1);}



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

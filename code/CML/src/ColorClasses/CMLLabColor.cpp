
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
  cmlClampLab(color, 1);
}

CMLuint32 LabColor::getNumChannels() const {return 3;}

// ///////////////////////////////////////
// Converting to different color spaces
// ///////////////////////////////////////

CMLColorType LabColor::getColorType() const{
  return CML_COLOR_Lab;
}

void LabColor::from8BitBuffer(const CMLByte* input){
  cmlData8ToLab(cmlcm, color, input, 1);
}
void LabColor::from16BitBuffer(const CMLWord* input){
  cmlData16ToLab(cmlcm, color, input, 1);
}
void LabColor::fromFloatBuffer(const float* input){
  cmlCpy3(color, input);
}
void LabColor::to8BitBuffer(CMLByte* output) const {
  cmlLabToData8(cmlcm, output, color, 1);
}
void LabColor::to16BitBuffer(CMLWord* output) const {
  cmlLabToData16(cmlcm, output, color, 1);
}
void LabColor::toFloatBuffer(float* output) const {
  cmlCpy3(output, color);
}


void LabColor::fromNormedBuffer(const float* input){
  cmlNormedInputToLab(color, input, 1);
}
void LabColor::toNormedBuffer(float* output) const {
  cmlLabToNormedOutput(output, color, 1);
}
void LabColor::fromNormedCartesianBuffer(const float* input){
  cmlNormedInputToLab(color, input, 1);
}
void LabColor::toNormedCartesianBuffer(float* output) const {
  cmlLabToNormedOutput(output, color, 1);
}


void LabColor::fromGrayBuffer(const float* src) {cmlGrayToLab (cmlcm, color, src, 1);}
void LabColor::fromXYZBuffer(const float* src)  {cmlXYZToLab  (cmlcm, color, src, 1);}
void LabColor::fromYuvBuffer(const float* src)  {cmlYuvToLab  (cmlcm, color, src, 1);}
void LabColor::fromYupvpBuffer(const float* src){cmlYupvpToLab(cmlcm, color, src, 1);}
void LabColor::fromYxyBuffer(const float* src)  {cmlYxyToLab  (cmlcm, color, src, 1);}
void LabColor::fromLabBuffer(const float* src)  {cmlLabToLab  (cmlcm, color, src, 1);}
void LabColor::fromLchBuffer(const float* src)  {cmlLchToLab  (cmlcm, color, src, 1);}
void LabColor::fromLuvBuffer(const float* src)  {cmlLuvToLab  (cmlcm, color, src, 1);}
void LabColor::fromRGBBuffer(const float* src)  {cmlRGBToLab  (cmlcm, color, src, 1);}
void LabColor::fromYCbCrBuffer(const float* src){cmlYCbCrToLab(cmlcm, color, src, 1);}
void LabColor::fromHSVBuffer(const float* src)  {cmlHSVToLab  (cmlcm, color, src, 1);}
void LabColor::fromHSLBuffer(const float* src)  {cmlHSLToLab  (cmlcm, color, src, 1);}
void LabColor::fromCMYKBuffer(const float* src) {cmlCMYKToLab (cmlcm, color, src, 1);}


void LabColor::toGrayBuffer(float* dest) const {cmlLabToGray (cmlcm, dest, color, 1);}
void LabColor::toXYZBuffer(float* dest) const  {cmlLabToXYZ  (cmlcm, dest, color, 1);}
void LabColor::toYuvBuffer(float* dest) const  {cmlLabToYuv  (cmlcm, dest, color, 1);}
void LabColor::toYupvpBuffer(float* dest) const{cmlLabToYupvp(cmlcm, dest, color, 1);}
void LabColor::toYxyBuffer(float* dest) const  {cmlLabToYxy  (cmlcm, dest, color, 1);}
void LabColor::toLabBuffer(float* dest) const  {cmlLabToLab  (cmlcm, dest, color, 1);}
void LabColor::toLchBuffer(float* dest) const  {cmlLabToLch  (cmlcm, dest, color, 1);}
void LabColor::toLuvBuffer(float* dest) const  {cmlLabToLuv  (cmlcm, dest, color, 1);}
void LabColor::toRGBBuffer(float* dest) const  {cmlLabToRGB  (cmlcm, dest, color, 1);}
void LabColor::toYCbCrBuffer(float* dest) const{cmlLabToYCbCr(cmlcm, dest, color, 1);}
void LabColor::toHSVBuffer(float* dest) const  {cmlLabToHSV  (cmlcm, dest, color, 1);}
void LabColor::toHSLBuffer(float* dest) const  {cmlLabToHSL  (cmlcm, dest, color, 1);}
void LabColor::toCMYKBuffer(float* dest) const {cmlLabToCMYK (cmlcm, dest, color, 1);}



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

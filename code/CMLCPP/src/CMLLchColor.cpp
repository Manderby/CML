
#include "CMLColor.h"

// ///////////////////////////////////////
// Constructors and initialization methods
// ///////////////////////////////////////

LchColor::LchColor(){}
LchColor::~LchColor(){}

LchColor::LchColor(float L, float c, float h){
  init(L, c, h);
}

LchColor::LchColor(const Color& anycolor){
  operator =(anycolor);
}

LchColor::LchColor(const LchColor& lch){
  operator =(lch);
}

void LchColor::init(float L, float c, float h){
  cmlSet3(color, L, c, h);
}

LchColor& LchColor::operator =(const Color& anycolor){
  anycolor.toLchBuffer(color);
  return *this;
}

LchColor& LchColor::operator =(const LchColor& lch){
  cmlCpy3(color, lch);
  return *this;
}

// ///////////////////////////////////////
// Mathematical operators in cartesian space
// As Lch is not a cartesian space, the Lch values will be converted to Lab
// first if necessary.
// ///////////////////////////////////////

LchColor LchColor::operator +() const {
  return LchColor(*this);
}

LchColor LchColor::operator -() const {
  LabColor lab(*this);
  return (LchColor)(-lab);
}

LchColor LchColor::operator +(const Color& anycolor) const{
  LabColor lab1(*this);
  LabColor lab2(anycolor);
  return (LchColor)(lab1 + lab2);
}

LchColor LchColor::operator -(const Color& anycolor) const{
  LabColor lab1(*this);
  LabColor lab2(anycolor);
  return (LchColor)(lab1 - lab2);
}

LchColor LchColor::operator *(const float factor) const{
  return LchColor(color[0] * factor, color[1] * factor, color[2]);
}

LchColor LchColor::operator /(const float divisor) const{
  float factor = cmlInverse(divisor);
  return LchColor(color[0] * factor, color[1] * factor, color[2]);
}

LchColor& LchColor::operator +=(const Color& anycolor){
  LabColor lab1(*this);
  LabColor lab2(anycolor);
  operator =(lab1 + lab2);
  return *this;
}

LchColor& LchColor::operator -=(const Color& anycolor){
  LabColor lab1(*this);
  LabColor lab2(anycolor);
  operator =(lab1 - lab2);
  return *this;
}

LchColor& LchColor::operator *=(const float factor){
  color[0] *= factor;
  color[1] *= factor;
  return *this;
}

LchColor& LchColor::operator /=(const float divisor){
  float factor = cmlInverse(divisor);
  color[0] *= factor;
  color[1] *= factor;
  return *this;
}

float LchColor::dot(const LchColor& lch) const{
  LabColor lab1(*this);
  LabColor lab2(lch);
  return lab1.dot(lab2);
}

float LchColor::length() const {
  LabColor lab(*this);
  return cmlLength3(lab);
}

CMLBool LchColor::operator ==(const LchColor& lch) const {
  return cmlEqual3(color, lch.color);
}

CMLBool LchColor::operator !=(const LchColor& lch) const {
  return !cmlEqual3(color, lch.color);
}

// ///////////////////////////////////////
// various methods
// ///////////////////////////////////////

LchColor::operator const float*() const {return color;}
LchColor::operator       float*()       {return color;}

LchColor LchColor::getInverse(){
  float buf[3];
  cmlCpy3(buf, color);
  cmlInvertLch(buf, 1);
  return LchColor(buf[0], buf[1], buf[2]);
}

void LchColor::invert(){
  cmlInvertLch(color, 1);
}

CMLBool LchColor::insideL(){
  return cmlInRange(color[0], CML_Lch_L_MIN, CML_Lch_L_MAX);
}

CMLBool LchColor::insidec(){
  return cmlInRange(color[1], CML_Lch_c_MIN, CML_Lch_c_MAX);
}

CMLBool LchColor::insideh(){
  return cmlInRange(color[2], CML_Lch_h_MIN, CML_Lch_h_MAX);
}

CMLBool LchColor::inside(){
  return (insideL() && insidec() && insideh());
}

void LchColor::clamp(){
  cmlClampLch(color, 1);
}

size_t LchColor::getNumChannels() const {return 3;}

// ///////////////////////////////////////
// Converting to different color spaces
// ///////////////////////////////////////

CMLColorType LchColor::getColorType() const{
  return CML_COLOR_Lch;
}

void LchColor::from8BitBuffer(const uint8* input){
  cmlData8ToLch(cmlcm, color, input, 1);
}
void LchColor::from16BitBuffer(const uint16* input){
  cmlData16ToLch(cmlcm, color, input, 1);
}
void LchColor::fromFloatBuffer(const float* input){
  cmlCpy3(color, input);
}
void LchColor::to8BitBuffer(uint8* output) const {
  cmlLchToData8(cmlcm, output, color, 1);
}
void LchColor::to16BitBuffer(uint16* output) const {
  cmlLchToData16(cmlcm, output, color, 1);
}
void LchColor::toFloatBuffer(float* output) const {
  cmlCpy3(output, color);
}


void LchColor::fromNormedBuffer(const float* input){
  cmlNormedInputToLch(color, input, 1);
}
void LchColor::toNormedBuffer(float* output) const {
  cmlLchToNormedOutput(output, color, 1);
}
void LchColor::fromNormedCartesianBuffer(const float* input){
  cmlNormedCartesianInputToLch(color, input, 1);
}
void LchColor::toNormedCartesianBuffer(float* output) const {
  cmlLchToNormedCartesianOutput(output, color, 1);
}


void LchColor::fromGrayBuffer(const float* src) {cmlGrayToLch (cmlcm, color, src, 1);}
void LchColor::fromXYZBuffer(const float* src)  {cmlXYZToLch  (cmlcm, color, src, 1);}
void LchColor::fromYuvBuffer(const float* src)  {cmlYuvToLch  (cmlcm, color, src, 1);}
void LchColor::fromYupvpBuffer(const float* src){cmlYupvpToLch(cmlcm, color, src, 1);}
void LchColor::fromYxyBuffer(const float* src)  {cmlYxyToLch  (cmlcm, color, src, 1);}
void LchColor::fromLabBuffer(const float* src)  {cmlLabToLch  (cmlcm, color, src, 1);}
void LchColor::fromLchBuffer(const float* src)  {cmlLchToLch  (cmlcm, color, src, 1);}
void LchColor::fromLuvBuffer(const float* src)  {cmlLuvToLch  (cmlcm, color, src, 1);}
void LchColor::fromRGBBuffer(const float* src)  {cmlRGBToLch  (cmlcm, color, src, 1);}
void LchColor::fromYCbCrBuffer(const float* src){cmlYCbCrToLch(cmlcm, color, src, 1);}
void LchColor::fromHSVBuffer(const float* src)  {cmlHSVToLch  (cmlcm, color, src, 1);}
void LchColor::fromHSLBuffer(const float* src)  {cmlHSLToLch  (cmlcm, color, src, 1);}
void LchColor::fromCMYKBuffer(const float* src) {cmlCMYKToLch (cmlcm, color, src, 1);}

void LchColor::toGrayBuffer(float* dest) const {cmlLchToGray (cmlcm, dest, color, 1);}
void LchColor::toXYZBuffer(float* dest) const  {cmlLchToXYZ  (cmlcm, dest, color, 1);}
void LchColor::toYuvBuffer(float* dest) const  {cmlLchToYuv  (cmlcm, dest, color, 1);}
void LchColor::toYupvpBuffer(float* dest) const{cmlLchToYupvp(cmlcm, dest, color, 1);}
void LchColor::toYxyBuffer(float* dest) const  {cmlLchToYxy  (cmlcm, dest, color, 1);}
void LchColor::toLabBuffer(float* dest) const  {cmlLchToLab  (cmlcm, dest, color, 1);}
void LchColor::toLchBuffer(float* dest) const  {cmlLchToLch  (cmlcm, dest, color, 1);}
void LchColor::toLuvBuffer(float* dest) const  {cmlLchToLuv  (cmlcm, dest, color, 1);}
void LchColor::toRGBBuffer(float* dest) const  {cmlLchToRGB  (cmlcm, dest, color, 1);}
void LchColor::toYCbCrBuffer(float* dest) const{cmlLchToYCbCr(cmlcm, dest, color, 1);}
void LchColor::toHSVBuffer(float* dest) const  {cmlLchToHSV  (cmlcm, dest, color, 1);}
void LchColor::toHSLBuffer(float* dest) const  {cmlLchToHSL  (cmlcm, dest, color, 1);}
void LchColor::toCMYKBuffer(float* dest) const {cmlLchToCMYK (cmlcm, dest, color, 1);}



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

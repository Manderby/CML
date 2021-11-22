
#include "CMLColor.h"

// ///////////////////////////////////////
// Constructors and initialization methods
// ///////////////////////////////////////

LuvColor::LuvColor(){}
LuvColor::~LuvColor(){}

LuvColor::LuvColor(float L, float u, float v){
  init( L, u, v);
}

LuvColor::LuvColor(const Color& anycolor){
  operator =(anycolor);
}

LuvColor::LuvColor(const LuvColor& luv){
  operator =(luv);
}

void LuvColor::init(float L, float u, float v){
  cmlSet3(color, L, u, v);
}

LuvColor& LuvColor::operator =(const Color& anycolor){
  anycolor.toLuvBuffer(color);
  return *this;
}

LuvColor& LuvColor::operator =(const LuvColor& luv){
  cmlCpy3(color, luv);
  return *this;
}

// ///////////////////////////////////////
// Mathematical operators in cartesian space
// ///////////////////////////////////////

LuvColor LuvColor::operator +() const {
  return LuvColor(*this);
}

LuvColor LuvColor::operator -() const {
  return LuvColor(-color[0], -color[1], -color[2]);
}

LuvColor LuvColor::operator +(const Color& anycolor) const {
  float buf[3];
  anycolor.toLuvBuffer(buf);
  return LuvColor(color[0]+buf[0], color[1]+buf[1], color[2]+buf[2]);
}

LuvColor LuvColor::operator -(const Color& anycolor) const {
  float buf[3];
  anycolor.toLuvBuffer(buf);
  return LuvColor(color[0]-buf[0], color[1]-buf[1], color[2]-buf[2]);
}

LuvColor LuvColor::operator *(const float factor) const {
  return LuvColor(color[0]*factor, color[1]*factor, color[2]*factor);
}

LuvColor LuvColor::operator /(const float divisor) const {
  float factor = cmlInverse(divisor);
  return LuvColor(color[0]*factor, color[1]*factor, color[2]*factor);
}

LuvColor& LuvColor::operator +=(const Color& anycolor){
  float buf[3];
  anycolor.toLuvBuffer(buf);
  cmlAdd3(color, buf);
  return *this;
}

LuvColor& LuvColor::operator -=(const Color& anycolor){
  float buf[3];
  anycolor.toLuvBuffer(buf);
  cmlSub3(color, buf);
  return *this;
}

LuvColor& LuvColor::operator *=(const float factor){
  cmlMul3(color, factor);
  return *this;
}

LuvColor& LuvColor::operator /=(const float divisor){
  cmlDiv3(color, divisor);
  return *this;
}

float LuvColor::dot(const LuvColor& luv) const {
  return cmlDot3(color, luv.color);
}

float LuvColor::length() const {
  return cmlLength3(color);
}

CMLBool LuvColor::operator ==(const LuvColor& luv) const {
  return cmlEqual3(color, luv.color);
}

CMLBool LuvColor::operator !=(const LuvColor& luv) const {
  return !cmlEqual3(color, luv.color);
}

// ///////////////////////////////////////
// various methods
// ///////////////////////////////////////

LuvColor::operator const float*() const {return color;}
LuvColor::operator       float*()       {return color;}

LuvColor LuvColor::getInverse() {
  float buf[3];
  cmlCpy3(buf, color);
  cmlInvertLuv(buf, 1);
  return LuvColor(buf[0], buf[1], buf[2]);
}

void LuvColor::invert(){
  cmlInvertLuv(color, 1);
}

CMLBool LuvColor::insideL() {
  return CMLInRange(color[0], CML_Luv_L_MIN, CML_Luv_L_MAX);
}

CMLBool LuvColor::insideu() {
  return CMLInRange(color[1], CML_Luv_u_MIN, CML_Luv_u_MAX);
}

CMLBool LuvColor::insidev() {
  return CMLInRange(color[2], CML_Luv_v_MIN, CML_Luv_v_MAX);
}

CMLBool LuvColor::inside()  {
  return (insideL() && insideu() && insidev());
}

void LuvColor::clamp(){
  CMLclampLuv(color, 1);
}

CMLuint32 LuvColor::getNumChannels() const {return 3;}

// ///////////////////////////////////////
// Converting to different color spaces
// ///////////////////////////////////////

CMLColorType LuvColor::getColorType() const{
  return CML_COLOR_Luv;
}

void LuvColor::from8bitBuffer(const CMLByte* input){
  CMLLuvfrom8bitInput(cmlcm, color, input, 1);
}
void LuvColor::from16bitBuffer(const CMLWord* input){
  CMLLuvfrom16bitInput(cmlcm, color, input, 1);
}
void LuvColor::fromFloatBuffer(const float* input){
  cmlCpy3(color, input);
}
void LuvColor::to8bitBuffer(CMLByte* output) const {
  CMLLuvto8bitOutput(cmlcm, output, color, 1);
}
void LuvColor::to16bitBuffer(CMLWord* output) const {
  CMLLuvto16bitOutput(cmlcm, output, color, 1);
}
void LuvColor::toFloatBuffer(float* output) const {
  cmlCpy3(output, color);
}


void LuvColor::fromNormedBuffer(const float* input){
  CMLLuvfromNormedInput(color, input, 1);
}
void LuvColor::toNormedBuffer(float* output) const {
  CMLLuvtoNormedOutput(output, color, 1);
}
void LuvColor::fromNormedCartesianBuffer(const float* input){
  CMLLuvfromNormedInput(color, input, 1);
}
void LuvColor::toNormedCartesianBuffer(float* output) const {
  CMLLuvtoNormedOutput(output, color, 1);
}


void LuvColor::fromGrayBuffer(const float* src) {CMLGraytoLuv (cmlcm, color, src, 1);}
void LuvColor::fromXYZBuffer(const float* src)  {CMLXYZtoLuv  (cmlcm, color, src, 1);}
void LuvColor::fromYuvBuffer(const float* src)  {CMLYuvtoLuv  (cmlcm, color, src, 1);}
void LuvColor::fromYupvpBuffer(const float* src){CMLYupvptoLuv(cmlcm, color, src, 1);}
void LuvColor::fromYxyBuffer(const float* src)  {CMLYxytoLuv  (cmlcm, color, src, 1);}
void LuvColor::fromLabBuffer(const float* src)  {CMLLabtoLuv  (cmlcm, color, src, 1);}
void LuvColor::fromLchBuffer(const float* src)  {CMLLchtoLuv  (cmlcm, color, src, 1);}
void LuvColor::fromLuvBuffer(const float* src)  {CMLLuvtoLuv  (cmlcm, color, src, 1);}
void LuvColor::fromRGBBuffer(const float* src)  {CMLRGBtoLuv  (cmlcm, color, src, 1);}
void LuvColor::fromYCbCrBuffer(const float* src){CMLYCbCrtoLuv(cmlcm, color, src, 1);}
void LuvColor::fromHSVBuffer(const float* src)  {CMLHSVtoLuv  (cmlcm, color, src, 1);}
void LuvColor::fromHSLBuffer(const float* src)  {CMLHSLtoLuv  (cmlcm, color, src, 1);}
void LuvColor::fromCMYKBuffer(const float* src) {CMLCMYKtoLuv (cmlcm, color, src, 1);}


void LuvColor::toGrayBuffer(float* dest) const {CMLLuvtoGray (cmlcm, dest, color, 1);}
void LuvColor::toXYZBuffer(float* dest) const  {CMLLuvtoXYZ  (cmlcm, dest, color, 1);}
void LuvColor::toYuvBuffer(float* dest) const  {CMLLuvtoYuv  (cmlcm, dest, color, 1);}
void LuvColor::toYupvpBuffer(float* dest) const{CMLLuvtoYupvp(cmlcm, dest, color, 1);}
void LuvColor::toYxyBuffer(float* dest) const  {CMLLuvtoYxy  (cmlcm, dest, color, 1);}
void LuvColor::toLabBuffer(float* dest) const  {CMLLuvtoLab  (cmlcm, dest, color, 1);}
void LuvColor::toLchBuffer(float* dest) const  {CMLLuvtoLch  (cmlcm, dest, color, 1);}
void LuvColor::toLuvBuffer(float* dest) const  {CMLLuvtoLuv  (cmlcm, dest, color, 1);}
void LuvColor::toRGBBuffer(float* dest) const  {CMLLuvtoRGB  (cmlcm, dest, color, 1);}
void LuvColor::toYCbCrBuffer(float* dest) const{CMLLuvtoYCbCr(cmlcm, dest, color, 1);}
void LuvColor::toHSVBuffer(float* dest) const  {CMLLuvtoHSV  (cmlcm, dest, color, 1);}
void LuvColor::toHSLBuffer(float* dest) const  {CMLLuvtoHSL  (cmlcm, dest, color, 1);}
void LuvColor::toCMYKBuffer(float* dest) const {CMLLuvtoCMYK (cmlcm, dest, color, 1);}



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


// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

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
  CMLinvertYxy(buf, 1);
  return YxyColor(buf[0], buf[1], buf[2]);
}

void YxyColor::invert(){
  CMLinvertYxy(color, 1);
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
  CMLclampYxy(color, 1);
}

CMLuint32 YxyColor::getNumChannels() const {return 3;}

// ///////////////////////////////////////
// Converting to different color spaces
// ///////////////////////////////////////

CMLColorType YxyColor::getColorType() const{
  return CML_COLOR_Yxy;
}

void YxyColor::from8bitBuffer(const CMLByte* input){
  CMLYxyfrom8bitInput(cmlcm, color, input, 1);
}
void YxyColor::from16bitBuffer(const CMLWord* input){
  CMLYxyfrom16bitInput(cmlcm, color, input, 1);
}
void YxyColor::fromFloatBuffer(const float* input){
  cmlCpy3(color, input);
}
void YxyColor::to8bitBuffer(CMLByte* output) const {
  CMLYxyto8bitOutput(cmlcm, output, color, 1);
}
void YxyColor::to16bitBuffer(CMLWord* output) const {
  CMLYxyto16bitOutput(cmlcm, output, color, 1);
}
void YxyColor::toFloatBuffer(float* output) const {
  cmlCpy3(output, color);
}


void YxyColor::fromNormedBuffer(const float* input){
  CMLYxyfromNormedInput(color, input, 1);
}
void YxyColor::toNormedBuffer(float* output) const {
  CMLYxytoNormedOutput(output, color, 1);
}
void YxyColor::fromNormedCartesianBuffer(const float* input){
  CMLYxyfromNormedInput(color, input, 1);
}
void YxyColor::toNormedCartesianBuffer(float* output) const {
  CMLYxytoNormedOutput(output, color, 1);
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



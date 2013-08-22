
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

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

YupvpColor::YupvpColor(const YupvpColor& Yupvp){
  operator =(Yupvp);
}

void YupvpColor::init(float Y, float U, float V){
  cmlSet3(color, Y, U, V);
}

YupvpColor& YupvpColor::operator =(const Color& anycolor){
  anycolor.toYupvpBuffer(color);
  return *this;
}

YupvpColor& YupvpColor::operator =(const YupvpColor& Yupvp){
  cmlCpy3(color, Yupvp);
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

float YupvpColor::dot(const YupvpColor& Yupvp) const {
  return cmlDot3(color, Yupvp.color);
}

float YupvpColor::length() const {
  return cmlLength3(color);
}

CMLBool YupvpColor::operator ==(const YupvpColor& Yupvp) const {
  return cmlEqual3(color, Yupvp.color);
}

CMLBool YupvpColor::operator !=(const YupvpColor& Yupvp) const {
  return !cmlEqual3(color, Yupvp.color);
}

// ///////////////////////////////////////
// various methods
// ///////////////////////////////////////

YupvpColor::operator const float*() const {return color;}
YupvpColor::operator       float*()       {return color;}

YupvpColor YupvpColor::getInverse(){
  float buf[3];
  cmlCpy3(buf, color);
  CMLinvertYupvp(buf, 1);
  return YupvpColor(buf[0], buf[1], buf[2]);
}

void YupvpColor::invert(){
  CMLinvertYupvp(color, 1);
}

CMLBool YupvpColor::insideY(){
  return CMLInRange(color[0], CML_Yupvp_Y_MIN, CML_Yupvp_Y_MAX);
}

CMLBool YupvpColor::insideU() {
  return CMLInRange(color[1], CML_Yupvp_up_MIN, CML_Yupvp_up_MAX);
}

CMLBool YupvpColor::insideV(){
  return CMLInRange(color[2], CML_Yupvp_vp_MIN, CML_Yupvp_vp_MAX);
}

CMLBool YupvpColor::inside(){
  return (insideY() && insideU() && insideV());
}

void YupvpColor::clamp(){
  CMLclampYupvp(color, 1);
}

CMLuint32 YupvpColor::getNumChannels() const {return 3;}

// ///////////////////////////////////////
// Converting to different color spaces
// ///////////////////////////////////////

CMLColorType YupvpColor::getColorType() const{
  return CML_COLOR_Yupvp;
}

void YupvpColor::from8bitBuffer(const CMLByte* input){
  CMLYupvpfrom8bitInput(cmlcm, color, input, 1);
}
void YupvpColor::from16bitBuffer(const CMLWord* input){
  CMLYupvpfrom16bitInput(cmlcm, color, input, 1);
}
void YupvpColor::fromFloatBuffer(const float* input){
  cmlCpy3(color, input);
}
void YupvpColor::to8bitBuffer(CMLByte* output) const {
  CMLYupvpto8bitOutput(cmlcm, output, color, 1);
}
void YupvpColor::to16bitBuffer(CMLWord* output) const {
  CMLYupvpto16bitOutput(cmlcm, output, color, 1);
}
void YupvpColor::toFloatBuffer(float* output) const {
  cmlCpy3(output, color);
}


void YupvpColor::fromNormedBuffer(const float* input){
  CMLYupvpfromNormedInput(color, input, 1);
}
void YupvpColor::toNormedBuffer(float* output) const {
  CMLYupvptoNormedOutput(output, color, 1);
}
void YupvpColor::fromNormedCartesianBuffer(const float* input){
  CMLYupvpfromNormedInput(color, input, 1);
}
void YupvpColor::toNormedCartesianBuffer(float* output) const {
  CMLYupvptoNormedOutput(output, color, 1);
}


void YupvpColor::fromGrayBuffer(const float* src) {CMLGraytoYupvp (cmlcm, color, src, 1);}
void YupvpColor::fromXYZBuffer(const float* src)  {CMLXYZtoYupvp  (cmlcm, color, src, 1);}
void YupvpColor::fromYuvBuffer(const float* src)  {CMLYuvtoYupvp  (cmlcm, color, src, 1);}
void YupvpColor::fromYupvpBuffer(const float* src){CMLYupvptoYupvp(cmlcm, color, src, 1);}
void YupvpColor::fromYxyBuffer(const float* src)  {CMLYxytoYupvp  (cmlcm, color, src, 1);}
void YupvpColor::fromLabBuffer(const float* src)  {CMLLabtoYupvp  (cmlcm, color, src, 1);}
void YupvpColor::fromLchBuffer(const float* src)  {CMLLchtoYupvp  (cmlcm, color, src, 1);}
void YupvpColor::fromLuvBuffer(const float* src)  {CMLLuvtoYupvp  (cmlcm, color, src, 1);}
void YupvpColor::fromRGBBuffer(const float* src)  {CMLRGBtoYupvp  (cmlcm, color, src, 1);}
void YupvpColor::fromYCbCrBuffer(const float* src){CMLYCbCrtoYupvp(cmlcm, color, src, 1);}
void YupvpColor::fromHSVBuffer(const float* src)  {CMLHSVtoYupvp  (cmlcm, color, src, 1);}
void YupvpColor::fromHSLBuffer(const float* src)  {CMLHSLtoYupvp  (cmlcm, color, src, 1);}
void YupvpColor::fromCMYKBuffer(const float* src) {CMLCMYKtoYupvp (cmlcm, color, src, 1);}

void YupvpColor::toGrayBuffer(float* dest) const {CMLYupvptoGray (cmlcm, dest, color, 1);}
void YupvpColor::toXYZBuffer(float* dest) const  {CMLYupvptoXYZ  (cmlcm, dest, color, 1);}
void YupvpColor::toYuvBuffer(float* dest) const  {CMLYupvptoYuv  (cmlcm, dest, color, 1);}
void YupvpColor::toYupvpBuffer(float* dest) const{CMLYupvptoYupvp(cmlcm, dest, color, 1);}
void YupvpColor::toYxyBuffer(float* dest) const  {CMLYupvptoYxy  (cmlcm, dest, color, 1);}
void YupvpColor::toLabBuffer(float* dest) const  {CMLYupvptoLab  (cmlcm, dest, color, 1);}
void YupvpColor::toLchBuffer(float* dest) const  {CMLYupvptoLch  (cmlcm, dest, color, 1);}
void YupvpColor::toLuvBuffer(float* dest) const  {CMLYupvptoLuv  (cmlcm, dest, color, 1);}
void YupvpColor::toRGBBuffer(float* dest) const  {CMLYupvptoRGB  (cmlcm, dest, color, 1);}
void YupvpColor::toYCbCrBuffer(float* dest) const{CMLYupvptoYCbCr(cmlcm, dest, color, 1);}
void YupvpColor::toHSVBuffer(float* dest) const  {CMLYupvptoHSV  (cmlcm, dest, color, 1);}
void YupvpColor::toHSLBuffer(float* dest) const  {CMLYupvptoHSL  (cmlcm, dest, color, 1);}
void YupvpColor::toCMYKBuffer(float* dest) const {CMLYupvptoCMYK (cmlcm, dest, color, 1);}


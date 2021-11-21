
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

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
  CMLinvertXYZ(buf, 1);
  return XYZColor(buf[0], buf[1], buf[2]);
}

void XYZColor::invert(){
  CMLinvertXYZ(color, 1);
}

CMLBool XYZColor::insideX(){
  return CMLInRange(color[0], CML_XYZ_X_MIN, CML_XYZ_X_MAX);
}

CMLBool XYZColor::insideY(){
  return CMLInRange(color[1], CML_XYZ_Y_MIN, CML_XYZ_Y_MAX);
}

CMLBool XYZColor::insideZ(){
  return CMLInRange(color[2], CML_XYZ_Z_MIN, CML_XYZ_Z_MAX);
}

CMLBool XYZColor::inside(){
  return (insideX() && insideY() && insideZ());
}

void XYZColor::clamp(){
  CMLclampXYZ(color, 1);
}

CMLuint32 XYZColor::getNumChannels() const {return 3;}

// ///////////////////////////////////////
// Converting to different color spaces
// ///////////////////////////////////////

CMLColorType XYZColor::getColorType() const{
  return CML_COLOR_XYZ;
}

void XYZColor::from8bitBuffer(const CMLByte* input){
  CMLXYZfrom8bitInput(cmlcm, color, input, 1);
}
void XYZColor::from16bitBuffer(const CMLWord* input){
  CMLXYZfrom16bitInput(cmlcm, color, input, 1);
}
void XYZColor::fromFloatBuffer(const float* input){
  cmlCpy3(color, input);
}
void XYZColor::to8bitBuffer(CMLByte* output) const {
  CMLXYZto8bitOutput(cmlcm, output, color, 1);
}
void XYZColor::to16bitBuffer(CMLWord* output) const {
  CMLXYZto16bitOutput(cmlcm, output, color, 1);
}
void XYZColor::toFloatBuffer(float* output) const {
  cmlCpy3(output, color);
}


void XYZColor::fromNormedBuffer(const float* input){
  CMLXYZfromNormedInput(color, input, 1);
}
void XYZColor::toNormedBuffer(float* output) const {
  CMLXYZtoNormedOutput(output, color, 1);
}
void XYZColor::fromNormedCartesianBuffer(const float* input){
  CMLXYZfromNormedInput(color, input, 1);
}
void XYZColor::toNormedCartesianBuffer(float* output) const {
  CMLXYZtoNormedOutput(output, color, 1);
}


void XYZColor::fromGrayBuffer(const float* src) {CMLGraytoXYZ (cmlcm, color, src, 1);}
void XYZColor::fromXYZBuffer(const float* src)  {CMLXYZtoXYZ  (cmlcm, color, src, 1);}
void XYZColor::fromYuvBuffer(const float* src)  {CMLYuvtoXYZ  (cmlcm, color, src, 1);}
void XYZColor::fromYupvpBuffer(const float* src){CMLYupvptoXYZ(cmlcm, color, src, 1);}
void XYZColor::fromYxyBuffer(const float* src)  {CMLYxytoXYZ  (cmlcm, color, src, 1);}
void XYZColor::fromLabBuffer(const float* src)  {CMLLabtoXYZ  (cmlcm, color, src, 1);}
void XYZColor::fromLchBuffer(const float* src)  {CMLLchtoXYZ  (cmlcm, color, src, 1);}
void XYZColor::fromLuvBuffer(const float* src)  {CMLLuvtoXYZ  (cmlcm, color, src, 1);}
void XYZColor::fromRGBBuffer(const float* src)  {CMLRGBtoXYZ  (cmlcm, color, src, 1);}
void XYZColor::fromYCbCrBuffer(const float* src){CMLYCbCrtoXYZ(cmlcm, color, src, 1);}
void XYZColor::fromHSVBuffer(const float* src)  {CMLHSVtoXYZ  (cmlcm, color, src, 1);}
void XYZColor::fromHSLBuffer(const float* src)  {CMLHSLtoXYZ  (cmlcm, color, src, 1);}
void XYZColor::fromCMYKBuffer(const float* src) {CMLCMYKtoXYZ (cmlcm, color, src, 1);}

void XYZColor::toGrayBuffer(float* dest) const {CMLXYZtoGray (cmlcm, dest, color, 1);}
void XYZColor::toXYZBuffer(float* dest) const  {CMLXYZtoXYZ  (cmlcm, dest, color, 1);}
void XYZColor::toYuvBuffer(float* dest) const  {CMLXYZtoYuv  (cmlcm, dest, color, 1);}
void XYZColor::toYupvpBuffer(float* dest) const{CMLXYZtoYupvp(cmlcm, dest, color, 1);}
void XYZColor::toYxyBuffer(float* dest) const  {CMLXYZtoYxy  (cmlcm, dest, color, 1);}
void XYZColor::toLabBuffer(float* dest) const  {CMLXYZtoLab  (cmlcm, dest, color, 1);}
void XYZColor::toLchBuffer(float* dest) const  {CMLXYZtoLch  (cmlcm, dest, color, 1);}
void XYZColor::toLuvBuffer(float* dest) const  {CMLXYZtoLuv  (cmlcm, dest, color, 1);}
void XYZColor::toRGBBuffer(float* dest) const  {CMLXYZtoRGB  (cmlcm, dest, color, 1);}
void XYZColor::toYCbCrBuffer(float* dest) const{CMLXYZtoYCbCr(cmlcm, dest, color, 1);}
void XYZColor::toHSVBuffer(float* dest) const  {CMLXYZtoHSV  (cmlcm, dest, color, 1);}
void XYZColor::toHSLBuffer(float* dest) const  {CMLXYZtoHSL  (cmlcm, dest, color, 1);}
void XYZColor::toCMYKBuffer(float* dest) const {CMLXYZtoCMYK (cmlcm, dest, color, 1);}



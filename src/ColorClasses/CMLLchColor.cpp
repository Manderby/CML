//
//// (c) Manderim GmbH
//// This is proprietary software. Any use without the explicit acknowledgement
//// of the author of this software is prohibited and any liability is disclamed.
//// Terms of a separate contract may apply.
//
//#include "CMLColor.h"
//
//// ///////////////////////////////////////
//// Constructors and initialization methods
//// ///////////////////////////////////////
//
//LchColor::LchColor(){}
//LchColor::~LchColor(){}
//
//LchColor::LchColor(float L, float c, float h){
//  init(L, c, h);
//}
//
//LchColor::LchColor(const Color& anycolor){
//  operator =(anycolor);
//}
//
//LchColor::LchColor(const LchColor& lch){
//  operator =(lch);
//}
//
//void LchColor::init(float L, float c, float h){
//  cmlSet3(color, L, c, h);
//}
//
//LchColor& LchColor::operator =(const Color& anycolor){
//  anycolor.toLchBuffer(color);
//  return *this;
//}
//
//LchColor& LchColor::operator =(const LchColor& lch){
//  cmlCpy3(color, lch);
//  return *this;
//}
//
//// ///////////////////////////////////////
//// Mathematical operators in cartesian space
//// As Lch is not a cartesian space, the Lch values will be converted to Lab
//// first if necessary.
//// ///////////////////////////////////////
//
//LchColor LchColor::operator +() const {
//  return LchColor(*this);
//}
//
//LchColor LchColor::operator -() const {
//  LabColor lab(*this);
//  return (LchColor)(-lab);
//}
//
//LchColor LchColor::operator +(const Color& anycolor) const{
//  LabColor lab1(*this);
//  LabColor lab2(anycolor);
//  return (LchColor)(lab1 + lab2);
//}
//
//LchColor LchColor::operator -(const Color& anycolor) const{
//  LabColor lab1(*this);
//  LabColor lab2(anycolor);
//  return (LchColor)(lab1 - lab2);
//}
//
//LchColor LchColor::operator *(const float factor) const{
//  return LchColor(color[0] * factor, color[1] * factor, color[2]);
//}
//
//LchColor LchColor::operator /(const float divisor) const{
//  float factor = cmlInverse(divisor);
//  return LchColor(color[0] * factor, color[1] * factor, color[2]);
//}
//
//LchColor& LchColor::operator +=(const Color& anycolor){
//  LabColor lab1(*this);
//  LabColor lab2(anycolor);
//  operator =(lab1 + lab2);
//  return *this;
//}
//
//LchColor& LchColor::operator -=(const Color& anycolor){
//  LabColor lab1(*this);
//  LabColor lab2(anycolor);
//  operator =(lab1 - lab2);
//  return *this;
//}
//
//LchColor& LchColor::operator *=(const float factor){
//  color[0] *= factor;
//  color[1] *= factor;
//  return *this;
//}
//
//LchColor& LchColor::operator /=(const float divisor){
//  float factor = cmlInverse(divisor);
//  color[0] *= factor;
//  color[1] *= factor;
//  return *this;
//}
//
//float LchColor::dot(const LchColor& lch) const{
//  LabColor lab1(*this);
//  LabColor lab2(lch);
//  return lab1.dot(lab2);
//}
//
//float LchColor::length() const {
//  LabColor lab(*this);
//  return cmlLength3(lab);
//}
//
//CMLBool LchColor::operator ==(const LchColor& lch) const {
//  return cmlEqual3(color, lch.color);
//}
//
//CMLBool LchColor::operator !=(const LchColor& lch) const {
//  return !cmlEqual3(color, lch.color);
//}
//
//// ///////////////////////////////////////
//// various methods
//// ///////////////////////////////////////
//
//LchColor::operator const float*() const {return color;}
//LchColor::operator       float*()       {return color;}
//
//LchColor LchColor::getInverse(){
//  float buf[3];
//  cmlCpy3(buf, color);
//  CMLinvertLch(buf, 1);
//  return LchColor(buf[0], buf[1], buf[2]);
//}
//
//void LchColor::invert(){
//  CMLinvertLch(color, 1);
//}
//
//CMLBool LchColor::insideL(){
//  return CMLInRange(color[0], CML_Lch_L_MIN, CML_Lch_L_MAX);
//}
//
//CMLBool LchColor::insidec(){
//  return CMLInRange(color[1], CML_Lch_c_MIN, CML_Lch_c_MAX);
//}
//
//CMLBool LchColor::insideh(){
//  return CMLInRange(color[2], CML_Lch_h_MIN, CML_Lch_h_MAX);
//}
//
//CMLBool LchColor::inside(){
//  return (insideL() && insidec() && insideh());
//}
//
//void LchColor::clamp(){
//  CMLclampLch(color, 1);
//}
//
//CMLuint32 LchColor::getNumChannels() const {return 3;}
//
//// ///////////////////////////////////////
//// Converting to different color spaces
//// ///////////////////////////////////////
//
//CMLColorType LchColor::getColorType() const{
//  return CML_COLOR_Lch;
//}
//
//void LchColor::from8bitBuffer(const CMLByte* input){
//  CMLLchfrom8bitInput(cmlcm, color, input, 1);
//}
//void LchColor::from16bitBuffer(const CMLWord* input){
//  CMLLchfrom16bitInput(cmlcm, color, input, 1);
//}
//void LchColor::fromFloatBuffer(const float* input){
//  cmlCpy3(color, input);
//}
//void LchColor::to8bitBuffer(CMLByte* output) const {
//  CMLLchto8bitOutput(cmlcm, output, color, 1);
//}
//void LchColor::to16bitBuffer(CMLWord* output) const {
//  CMLLchto16bitOutput(cmlcm, output, color, 1);
//}
//void LchColor::toFloatBuffer(float* output) const {
//  cmlCpy3(output, color);
//}
//
//
//void LchColor::fromNormedBuffer(const float* input){
//  CMLLchfromNormedInput(color, input, 1);
//}
//void LchColor::toNormedBuffer(float* output) const {
//  CMLLchtoNormedOutput(output, color, 1);
//}
//void LchColor::fromNormedCartesianBuffer(const float* input){
//  CMLLchfromNormedCartesianInput(color, input, 1);
//}
//void LchColor::toNormedCartesianBuffer(float* output) const {
//  CMLLchtoNormedCartesianOutput(output, color, 1);
//}
//
//
//void LchColor::fromGrayBuffer(const float* src) {CMLGraytoLch (cmlcm, color, src, 1);}
//void LchColor::fromXYZBuffer(const float* src)  {CMLXYZtoLch  (cmlcm, color, src, 1);}
//void LchColor::fromYuvBuffer(const float* src)  {CMLYuvtoLch  (cmlcm, color, src, 1);}
//void LchColor::fromYupvpBuffer(const float* src){CMLYupvptoLch(cmlcm, color, src, 1);}
//void LchColor::fromYxyBuffer(const float* src)  {CMLYxytoLch  (cmlcm, color, src, 1);}
//void LchColor::fromLabBuffer(const float* src)  {CMLLabtoLch  (cmlcm, color, src, 1);}
//void LchColor::fromLchBuffer(const float* src)  {CMLLchtoLch  (cmlcm, color, src, 1);}
//void LchColor::fromLuvBuffer(const float* src)  {CMLLuvtoLch  (cmlcm, color, src, 1);}
//void LchColor::fromRGBBuffer(const float* src)  {CMLRGBtoLch  (cmlcm, color, src, 1);}
//void LchColor::fromYCbCrBuffer(const float* src){CMLYCbCrtoLch(cmlcm, color, src, 1);}
//void LchColor::fromHSVBuffer(const float* src)  {CMLHSVtoLch  (cmlcm, color, src, 1);}
//void LchColor::fromHSLBuffer(const float* src)  {CMLHSLtoLch  (cmlcm, color, src, 1);}
//void LchColor::fromCMYKBuffer(const float* src) {CMLCMYKtoLch (cmlcm, color, src, 1);}
//
//void LchColor::toGrayBuffer(float* dest) const {CMLLchtoGray (cmlcm, dest, color, 1);}
//void LchColor::toXYZBuffer(float* dest) const  {CMLLchtoXYZ  (cmlcm, dest, color, 1);}
//void LchColor::toYuvBuffer(float* dest) const  {CMLLchtoYuv  (cmlcm, dest, color, 1);}
//void LchColor::toYupvpBuffer(float* dest) const{CMLLchtoYupvp(cmlcm, dest, color, 1);}
//void LchColor::toYxyBuffer(float* dest) const  {CMLLchtoYxy  (cmlcm, dest, color, 1);}
//void LchColor::toLabBuffer(float* dest) const  {CMLLchtoLab  (cmlcm, dest, color, 1);}
//void LchColor::toLchBuffer(float* dest) const  {CMLLchtoLch  (cmlcm, dest, color, 1);}
//void LchColor::toLuvBuffer(float* dest) const  {CMLLchtoLuv  (cmlcm, dest, color, 1);}
//void LchColor::toRGBBuffer(float* dest) const  {CMLLchtoRGB  (cmlcm, dest, color, 1);}
//void LchColor::toYCbCrBuffer(float* dest) const{CMLLchtoYCbCr(cmlcm, dest, color, 1);}
//void LchColor::toHSVBuffer(float* dest) const  {CMLLchtoHSV  (cmlcm, dest, color, 1);}
//void LchColor::toHSLBuffer(float* dest) const  {CMLLchtoHSL  (cmlcm, dest, color, 1);}
//void LchColor::toCMYKBuffer(float* dest) const {CMLLchtoCMYK (cmlcm, dest, color, 1);}
//

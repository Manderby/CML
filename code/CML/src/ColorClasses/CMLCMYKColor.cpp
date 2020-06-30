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
//CMYKColor::CMYKColor(){}
//CMYKColor::~CMYKColor(){}
//
//CMYKColor::CMYKColor(float C, float M, float Y, float K){
//  init(C, M, Y, K);
//}
//
//CMYKColor::CMYKColor(const Color& anycolor){
//  operator =(anycolor);
//}
//
//CMYKColor::CMYKColor(const CMYKColor& cmyk){
//  operator =(cmyk);
//}
//
//void CMYKColor::init(float C, float M, float Y, float K){
//  cmlSet4(color, C, M, Y, K);
//}
//
//CMYKColor& CMYKColor::operator =(const Color& anycolor){
//  anycolor.toCMYKBuffer(color);
//  return *this;
//}
//
//CMYKColor& CMYKColor::operator =(const CMYKColor& cmyk){
//  cmlCpy4(color, cmyk);
//  return *this;
//}
//
//// ///////////////////////////////////////
//// Mathematical operators in cartesian space
//// ///////////////////////////////////////
//
//CMYKColor CMYKColor::operator +() const {
//  return CMYKColor(*this);
//}
//
//CMYKColor CMYKColor::operator -() const {
//  return CMYKColor(-color[0], -color[1], -color[2], -color[3]);
//}
//
//CMYKColor CMYKColor::operator +(const Color& anycolor) const {
//  float buf[4];
//  anycolor.toCMYKBuffer(buf);
//  return CMYKColor(color[0]+buf[0], color[1]+buf[1], color[2]+buf[2], color[3]+buf[3]);
//}
//CMYKColor CMYKColor::operator -(const Color& anycolor) const {
//  float buf[4];
//  anycolor.toCMYKBuffer(buf);
//  return CMYKColor(color[0]-buf[0], color[1]-buf[1], color[2]-buf[2], color[3]-buf[3]);
//}
//CMYKColor CMYKColor::operator *(const float factor) const {
//  return CMYKColor(color[0]*factor, color[1]*factor, color[2]*factor, color[3]*factor);
//}
//CMYKColor CMYKColor::operator /(const float divisor) const {
//  float factor = cmlInverse(divisor);
//  return CMYKColor(color[0]*factor, color[1]*factor, color[2]*factor, color[3]*factor);
//}
//
//CMYKColor& CMYKColor::operator +=(const Color& anycolor){
//  float buf[4];
//  anycolor.toCMYKBuffer(buf);
//  cmlAdd4(color, buf);
//  return *this;
//}
//
//CMYKColor& CMYKColor::operator -=(const Color& anycolor){
//  float buf[4];
//  anycolor.toCMYKBuffer(buf);
//  cmlSub4(color, buf);
//  return *this;
//}
//
//CMYKColor& CMYKColor::operator *=(const float factor){
//  cmlMul4(color, factor);
//  return *this;
//}
//
//CMYKColor& CMYKColor::operator /=(const float divisor){
//  cmlDiv4(color, divisor);
//  return *this;
//}
//
//float CMYKColor::dot(const CMYKColor& cmyk) const {
//  return cmlDot4(color, cmyk.color);
//}
//
//float CMYKColor::length() const {
//  return cmlLength4(color);
//}
//
//CMLBool CMYKColor::operator ==(const CMYKColor& cmyk) const {
//  return cmlEqual4(color, cmyk.color);
//}
//CMLBool CMYKColor::operator !=(const CMYKColor& cmyk) const {
//  return !cmlEqual4(color, cmyk.color);
//}
//
//// ///////////////////////////////////////
//// various methods
//// ///////////////////////////////////////
//
//CMYKColor::operator const float*() const {return color;}
//CMYKColor::operator       float*()       {return color;}
//
//CMYKColor CMYKColor::getInverse() const{
//  float buf[4];
//  cmlCpy4(buf, color);
//  CMLinvertCMYK(buf, 1);
//  return CMYKColor(buf[0], buf[1], buf[2], buf[3]);
//}
//
//void CMYKColor::invert(){
//  CMLinvertCMYK(color, 1);
//}
//
//CMLBool CMYKColor::insideC(){
//  return CMLInRange(color[0], CML_CMYK_C_MIN, CML_CMYK_C_MAX);
//}
//
//CMLBool CMYKColor::insideM(){
//  return CMLInRange(color[1], CML_CMYK_M_MIN, CML_CMYK_M_MAX);
//}
//
//CMLBool CMYKColor::insideY(){
//  return CMLInRange(color[2], CML_CMYK_Y_MIN, CML_CMYK_Y_MAX);
//}
//
//CMLBool CMYKColor::insideK(){
//  return CMLInRange(color[3], CML_CMYK_K_MIN, CML_CMYK_K_MAX);
//}
//
//CMLBool CMYKColor::inside(){
//  return (insideC() && insideM() && insideY() && insideK());
//}
//
//void CMYKColor::clamp(){
//  CMLclampCMYK(color, 1);
//}
//
//CMLuint32 CMYKColor::getNumChannels() const {return 4;}
//
//// ///////////////////////////////////////
//// Converting to different color spaces
//// ///////////////////////////////////////
//
//CMLColorType CMYKColor::getColorType() const{
//  return CML_COLOR_CMYK;
//}
//
//void CMYKColor::from8bitBuffer(const CMLByte* input){
//  CMLCMYKfrom8bitInput(cmlcm, color, input, 1);
//}
//void CMYKColor::from16bitBuffer(const CMLWord* input){
//  CMLCMYKfrom16bitInput(cmlcm, color, input, 1);
//}
//void CMYKColor::fromFloatBuffer(const float* input){
//  cmlCpy4(color, input);
//}
//void CMYKColor::to8bitBuffer(CMLByte* output) const {
//  CMLCMYKto8bitOutput(cmlcm, output, color, 1);
//}
//void CMYKColor::to16bitBuffer(CMLWord* output) const {
//  CMLCMYKto16bitOutput(cmlcm, output, color, 1);
//}
//void CMYKColor::toFloatBuffer(float* output) const {
//  cmlCpy4(output, color);
//}
//
//
//void CMYKColor::fromNormedBuffer(const float* input){
//  CMLCMYKfromNormedInput(color, input, 1);
//}
//void CMYKColor::toNormedBuffer(float* output) const {
//  CMLCMYKtoNormedOutput(output, color, 1);
//}
//void CMYKColor::fromNormedCartesianBuffer(const float* input){
//  CMLCMYKfromNormedInput(color, input, 1);
//}
//void CMYKColor::toNormedCartesianBuffer(float* output) const {
//  CMLCMYKtoNormedOutput(output, color, 1);
//}
//
//
//void CMYKColor::fromGrayBuffer(const float* src) {CMLGraytoCMYK (cmlcm, color, src, 1);}
//void CMYKColor::fromXYZBuffer(const float* src)  {CMLXYZtoCMYK  (cmlcm, color, src, 1);}
//void CMYKColor::fromYuvBuffer(const float* src)  {CMLYuvtoCMYK  (cmlcm, color, src, 1);}
//void CMYKColor::fromYupvpBuffer(const float* src){CMLYupvptoCMYK(cmlcm, color, src, 1);}
//void CMYKColor::fromYxyBuffer(const float* src)  {CMLYxytoCMYK  (cmlcm, color, src, 1);}
//void CMYKColor::fromLabBuffer(const float* src)  {CMLLabtoCMYK  (cmlcm, color, src, 1);}
//void CMYKColor::fromLchBuffer(const float* src)  {CMLLchtoCMYK  (cmlcm, color, src, 1);}
//void CMYKColor::fromLuvBuffer(const float* src)  {CMLLuvtoCMYK  (cmlcm, color, src, 1);}
//void CMYKColor::fromRGBBuffer(const float* src)  {CMLRGBtoCMYK  (cmlcm, color, src, 1);}
//void CMYKColor::fromYCbCrBuffer(const float* src){CMLYCbCrtoCMYK(cmlcm, color, src, 1);}
//void CMYKColor::fromHSVBuffer(const float* src)  {CMLHSVtoCMYK  (cmlcm, color, src, 1);}
//void CMYKColor::fromHSLBuffer(const float* src)  {CMLHSLtoCMYK  (cmlcm, color, src, 1);}
//void CMYKColor::fromCMYKBuffer(const float* src) {CMLCMYKtoCMYK (cmlcm, color, src, 1);}
//
//
//void CMYKColor::toGrayBuffer(float* dest) const {CMLCMYKtoGray (cmlcm, dest, color, 1);}
//void CMYKColor::toXYZBuffer(float* dest) const  {CMLCMYKtoXYZ  (cmlcm, dest, color, 1);}
//void CMYKColor::toYuvBuffer(float* dest) const  {CMLCMYKtoYuv  (cmlcm, dest, color, 1);}
//void CMYKColor::toYupvpBuffer(float* dest) const{CMLCMYKtoYupvp(cmlcm, dest, color, 1);}
//void CMYKColor::toYxyBuffer(float* dest) const  {CMLCMYKtoYxy  (cmlcm, dest, color, 1);}
//void CMYKColor::toLabBuffer(float* dest) const  {CMLCMYKtoLab  (cmlcm, dest, color, 1);}
//void CMYKColor::toLchBuffer(float* dest) const  {CMLCMYKtoLch  (cmlcm, dest, color, 1);}
//void CMYKColor::toLuvBuffer(float* dest) const  {CMLCMYKtoLuv  (cmlcm, dest, color, 1);}
//void CMYKColor::toRGBBuffer(float* dest) const  {CMLCMYKtoRGB  (cmlcm, dest, color, 1);}
//void CMYKColor::toYCbCrBuffer(float* dest) const{CMLCMYKtoYCbCr(cmlcm, dest, color, 1);}
//void CMYKColor::toHSVBuffer(float* dest) const  {CMLCMYKtoHSV  (cmlcm, dest, color, 1);}
//void CMYKColor::toHSLBuffer(float* dest) const  {CMLCMYKtoHSL  (cmlcm, dest, color, 1);}
//void CMYKColor::toCMYKBuffer(float* dest) const {CMLCMYKtoCMYK (cmlcm, dest, color, 1);}
//
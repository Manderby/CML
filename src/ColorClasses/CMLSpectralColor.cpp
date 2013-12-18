
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

#include "CMLColor.h"

// ///////////////////////////////////////
// Constructors and initialization methods
// ///////////////////////////////////////

SpectralColor::SpectralColor() :
  spectrum(CML_NULL), bodycolor(CMLFALSE){
  CMLFunction* fun = cmlCreateConstFilter(0.f);
  init(fun, CMLFALSE);
  cmlReleaseFunction(fun);
}

SpectralColor::~SpectralColor(){
  cmlReleaseFunction(spectrum);
}

SpectralColor::SpectralColor(float value) :
  spectrum(CML_NULL), bodycolor(CMLFALSE){
  CMLFunction* fun = cmlCreateConstFilter(value);
  init(fun, CMLFALSE);
  cmlReleaseFunction(fun);
}

SpectralColor::SpectralColor(CMLFunction* newspectrum, CMLBool newbodycolor) :
  spectrum(CML_NULL), bodycolor(CMLFALSE){
  init(newspectrum, newbodycolor);
}

SpectralColor::SpectralColor(const Color& anycolor) :
  spectrum(CML_NULL), bodycolor(CMLFALSE){
  operator =(anycolor);
}

SpectralColor::SpectralColor(const SpectralColor& speccolor) :
  spectrum(CML_NULL), bodycolor(CMLFALSE){
  operator =(speccolor);
}

SpectralColor& SpectralColor::init(CMLFunction* newspectrum, CMLBool newbodycolor){
  #ifndef NDEBUG
    if(!newspectrum){
      cmlError("SpectralColor::init", "spectrum is NULL.");
    }
  #endif
  cmlReleaseFunction(spectrum);
  spectrum = cmlDuplicateFunction(newspectrum);
  #ifndef NDEBUG
    if(!spectrum){
      cmlError("SpectralColor::init", "Function duplicate returned NULL.");
    }
  #endif
  bodycolor = newbodycolor;
  return *this;
}

SpectralColor& SpectralColor::operator =(const Color& anycolor){
  SpectralColor newcolor = anycolor.toSpectral();
  return operator =(newcolor);
}

SpectralColor& SpectralColor::operator =(const SpectralColor& speccolor){
  #ifndef NDEBUG
    if(!speccolor.spectrum){
      cmlError("SpectralColor::operator =", "spectrum is NULL");
    }
  #endif
  cmlReleaseFunction(spectrum);
  spectrum = cmlDuplicateFunction(speccolor.spectrum);
  #ifndef NDEBUG
    if(!spectrum){
      cmlError("SpectralColor::operator =", "Function duplicate returned NULL.");
    }
  #endif
  bodycolor = speccolor.bodycolor;
  return *this;
}

// ///////////////////////////////////////
// Mathematical operators in cartesian space
// ///////////////////////////////////////

  SpectralColor SpectralColor::operator +() const{
    return *this;
  }

  SpectralColor SpectralColor::operator -() const{
    CMLFunction* newfunction = cmlCreateFunctionMulScalar(spectrum, -1.f);
    return SpectralColor(newfunction, bodycolor);
  }

  SpectralColor SpectralColor::operator +(const SpectralColor& speccolor) const{
    #ifndef NDEBUG
      if(isBodyColor() != speccolor.isBodyColor()){
        cmlError("SpectralColor::operator +", "Adding spectral bodycolor with non-bodycolor.");
      }
    #endif

    CMLFunction* newfunction = cmlCreateFunctionAddFunction(spectrum, speccolor.spectrum);
    return SpectralColor(newfunction, bodycolor);
  }

  SpectralColor SpectralColor::operator -(const SpectralColor& speccolor) const{
    #ifndef NDEBUG
      if(isBodyColor() != speccolor.isBodyColor()){
        cmlError("SpectralColor::operator -", "Subtracting spectral bodycolor with non-bodycolor.");
      }
    #endif

    CMLFunction* newfunction = cmlCreateFunctionSubFunction(spectrum, speccolor.spectrum);
    return SpectralColor(newfunction, bodycolor);
  }

  SpectralColor SpectralColor::operator *(float factor) const{
    CMLFunction* newfunction = cmlCreateFunctionMulScalar(spectrum, factor);
    return SpectralColor(newfunction, bodycolor);
  }

  SpectralColor SpectralColor::operator /(float divisor) const{
    // note: do not redirect this implementation to the * operator. It slows
    // down the implementation as more constructors need to be called.
    float factor = cmlInverse(divisor);
    CMLFunction* newfunction = cmlCreateFunctionMulScalar(spectrum, factor);
    return SpectralColor(newfunction, bodycolor);
  }

  SpectralColor& SpectralColor::operator +=(const Color& anycolor){
    SpectralColor speccolor = anycolor.toSpectral();
    #ifndef NDEBUG
      if(isBodyColor() != speccolor.isBodyColor()){
        cmlError("SpectralColor::operator +=", "Adding spectral bodycolor with non-bodycolor.");
      }
    #endif

    CMLFunction* newfunction = cmlCreateFunctionAddFunction(spectrum, speccolor.spectrum);
    cmlReleaseFunction(spectrum);
    spectrum = newfunction;
    return *this;
  }

  SpectralColor& SpectralColor::operator -=(const Color& anycolor){
    SpectralColor speccolor = anycolor.toSpectral();
    #ifndef NDEBUG
      if(isBodyColor() != speccolor.isBodyColor()){
        cmlError("SpectralColor::operator -=", "Subtracting spectral bodycolor with non-bodycolor.");
      }
    #endif

    CMLFunction* newfunction = cmlCreateFunctionSubFunction(spectrum, speccolor.spectrum);
    cmlReleaseFunction(spectrum);
    spectrum = newfunction;
    return *this;
  }

  SpectralColor& SpectralColor::operator *=(float factor){
    CMLFunction* newfunction = cmlCreateFunctionMulScalar(spectrum, factor);
    cmlReleaseFunction(spectrum);
    spectrum = newfunction;
    return *this;
  }

  SpectralColor& SpectralColor::operator /=(float divisor){
    return operator *= (cmlInverse(divisor));
  }



// ///////////////////////////////////////
// various methods
// ///////////////////////////////////////

CMLBool SpectralColor::isBodyColor() const {return bodycolor;}

//float SpectralColor::getMaxValue() const{
//  float max = -CML_INFINITY;
//  for(float x = 300.f; x < 800.f; x += 1.f){
//    float value = color->operator ()(x);
//    if(value > max){max = value;}
//  }
//  return max;
//}


const CMLFunction* SpectralColor::getSpectrum() const {return spectrum;}

SpectralColor::operator const float*() const{return CML_NULL;}
SpectralColor::operator       float*(){return CML_NULL;}

// ///////////////////////////////////////
// Converting to different color spaces
// ///////////////////////////////////////

CMLColorType SpectralColor::getColorType() const{
  if(bodycolor){
    return CML_COLOR_SPECTRUM_REMISSION;
  }else{
    return CML_COLOR_SPECTRUM_ILLUMINATION;
  }
}

SpectralColor SpectralColor::toSpectral() const  {
  return *this;
}


void SpectralColor::from8bitBuffer(const CMLByte* input){
  input = input;  // no warning
}
void SpectralColor::from16bitBuffer(const CMLWord* input){
  input = input;  // no warning
}
void SpectralColor::fromFloatBuffer(const float* input){
  input = input;  // no warning
}
void SpectralColor::to8bitBuffer(CMLByte* output) const {
  output = output;  // no warning
}
void SpectralColor::to16bitBuffer(CMLWord* output) const {
  output = output;  // no warning
}
void SpectralColor::toFloatBuffer(float* output) const {
  output = output;  // no warning
}


void SpectralColor::fromNormedBuffer(const float* input){
  input = input;  // no warning
}
void SpectralColor::toNormedBuffer(float* output) const {
  output = output;  // no warning
}
void SpectralColor::fromNormedCartesianBuffer(const float* input){
  input = input;  // no warning
}
void SpectralColor::toNormedCartesianBuffer(float* output) const {
  output = output;  // no warning
}


void SpectralColor::fromGrayBuffer(const float* src) {src = src;}
void SpectralColor::fromXYZBuffer(const float* src)  {src = src;}
void SpectralColor::fromYuvBuffer(const float* src)  {src = src;}
void SpectralColor::fromYupvpBuffer(const float* src){src = src;}
void SpectralColor::fromYxyBuffer(const float* src)  {src = src;}
void SpectralColor::fromLabBuffer(const float* src)  {src = src;}
void SpectralColor::fromLchBuffer(const float* src)  {src = src;}
void SpectralColor::fromLuvBuffer(const float* src)  {src = src;}
void SpectralColor::fromRGBBuffer(const float* src)  {src = src;}
void SpectralColor::fromYCbCrBuffer(const float* src){src = src;}
void SpectralColor::fromHSVBuffer(const float* src)  {src = src;}
void SpectralColor::fromHSLBuffer(const float* src)  {src = src;}
void SpectralColor::fromCMYKBuffer(const float* src) {src = src;}

void SpectralColor::toGrayBuffer(float* dest) const {
  if(bodycolor){
    CMLSpectrumRemissiontoGray(cmlcm, dest, spectrum, 1);
  }else{
    CMLSpectrumIlluminationtoGray(cmlcm, dest, spectrum, 1);
  }
}
void SpectralColor::toXYZBuffer(float* dest) const  {
  if(bodycolor){
    CMLSpectrumRemissiontoXYZ (cmlcm, dest, spectrum, 1);
  }else{
    CMLSpectrumIlluminationtoXYZ (cmlcm, dest, spectrum, 1);
  }
}
void SpectralColor::toYuvBuffer(float* dest) const  {
  if(bodycolor){
    CMLSpectrumRemissiontoYuv (cmlcm, dest, spectrum, 1);
  }else{
    CMLSpectrumIlluminationtoYuv (cmlcm, dest, spectrum, 1);
  }
}
void SpectralColor::toYupvpBuffer(float* dest) const{
  if(bodycolor){
    CMLSpectrumRemissiontoYupvp(cmlcm, dest, spectrum, 1);
  }else{
    CMLSpectrumIlluminationtoYupvp(cmlcm, dest, spectrum, 1);
  }
}
void SpectralColor::toYxyBuffer(float* dest) const  {
  if(bodycolor){
    CMLSpectrumRemissiontoYxy (cmlcm, dest, spectrum, 1);
  }else{
    CMLSpectrumIlluminationtoYxy (cmlcm, dest, spectrum, 1);
  }
}
void SpectralColor::toLabBuffer(float* dest) const  {
  if(bodycolor){
    CMLSpectrumRemissiontoLab (cmlcm, dest, spectrum, 1);
  }else{
    CMLSpectrumIlluminationtoLab (cmlcm, dest, spectrum, 1);
  }
}
void SpectralColor::toLchBuffer(float* dest) const  {
  if(bodycolor){
    CMLSpectrumRemissiontoLch (cmlcm, dest, spectrum, 1);
  }else{
    CMLSpectrumIlluminationtoLch (cmlcm, dest, spectrum, 1);
  }
}
void SpectralColor::toLuvBuffer(float* dest) const  {
  if(bodycolor){
    CMLSpectrumRemissiontoLuv (cmlcm, dest, spectrum, 1);
  }else{
    CMLSpectrumIlluminationtoLuv (cmlcm, dest, spectrum, 1);
  }
}
void SpectralColor::toRGBBuffer(float* dest) const  {
  if(bodycolor){
    CMLSpectrumRemissiontoRGB (cmlcm, dest, spectrum, 1);
  }else{
    CMLSpectrumIlluminationtoRGB (cmlcm, dest, spectrum, 1);
  }
}
void SpectralColor::toYCbCrBuffer(float* dest) const{
  if(bodycolor){
    CMLSpectrumRemissiontoYCbCr(cmlcm, dest, spectrum, 1);
  }else{
    CMLSpectrumIlluminationtoYCbCr(cmlcm, dest, spectrum, 1);
  }
}
void SpectralColor::toHSVBuffer(float* dest) const  {
  if(bodycolor){
    CMLSpectrumRemissiontoHSV (cmlcm, dest, spectrum, 1);
  }else{
    CMLSpectrumIlluminationtoHSV (cmlcm, dest, spectrum, 1);
  }
}
void SpectralColor::toHSLBuffer(float* dest) const  {
  if(bodycolor){
    CMLSpectrumRemissiontoHSL (cmlcm, dest, spectrum, 1);
  }else{
    CMLSpectrumIlluminationtoHSL (cmlcm, dest, spectrum, 1);
  }
}
void SpectralColor::toCMYKBuffer(float* dest) const {
  if(bodycolor){
    CMLSpectrumRemissiontoCMYK(cmlcm, dest, spectrum, 1);
  }else{
    CMLSpectrumIlluminationtoCMYK(cmlcm, dest, spectrum, 1);
  }
}



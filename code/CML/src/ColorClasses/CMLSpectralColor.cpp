
#include "CMLColor.h"

// ///////////////////////////////////////
// Constructors and initialization methods
// ///////////////////////////////////////

SpectralColor::SpectralColor() :
  spectrum(CML_NULL), bodycolor(CML_FALSE){
  CMLFunction* fun = cmlCreateConstFilter(0.f);
  init(fun, CML_FALSE);
  cmlReleaseFunction(fun);
}

SpectralColor::~SpectralColor(){
  cmlReleaseFunction(spectrum);
}

SpectralColor::SpectralColor(float value) :
  spectrum(CML_NULL), bodycolor(CML_FALSE){
  CMLFunction* fun = cmlCreateConstFilter(value);
  init(fun, CML_FALSE);
  cmlReleaseFunction(fun);
}

SpectralColor::SpectralColor(CMLFunction* newspectrum, CMLBool newbodycolor) :
  spectrum(CML_NULL), bodycolor(CML_FALSE){
  init(newspectrum, newbodycolor);
}

SpectralColor::SpectralColor(const Color& anycolor) :
  spectrum(CML_NULL), bodycolor(CML_FALSE){
  operator =(anycolor);
}

SpectralColor::SpectralColor(const SpectralColor& speccolor) :
  spectrum(CML_NULL), bodycolor(CML_FALSE){
  operator =(speccolor);
}

SpectralColor& SpectralColor::init(CMLFunction* newspectrum, CMLBool newbodycolor){
  #if CML_DEBUG
    if(!newspectrum){
      cmlError("spectrum is NULL.");
    }
  #endif
  cmlReleaseFunction(spectrum);
  spectrum = cmlDuplicateFunction(newspectrum);
  #if CML_DEBUG
    if(!spectrum){
      cmlError("Function duplicate returned NULL.");
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
  #if CML_DEBUG
    if(!speccolor.spectrum){
      cmlError("spectrum is NULL");
    }
  #endif
  cmlReleaseFunction(spectrum);
  spectrum = cmlDuplicateFunction(speccolor.spectrum);
  #if CML_DEBUG
    if(!spectrum){
      cmlError("Function duplicate returned NULL.");
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
    CMLFunction* newFunction = cmlCreateFunctionMulScalar(spectrum, -1.f);
    return SpectralColor(newFunction, bodycolor);
  }

  SpectralColor SpectralColor::operator +(const SpectralColor& speccolor) const{
    #if CML_DEBUG
      if(isBodyColor() != speccolor.isBodyColor()){
        cmlError("Adding spectral bodycolor with non-bodycolor.");
      }
    #endif

    CMLFunction* newFunction = cmlCreateFunctionAddFunction(spectrum, speccolor.spectrum);
    return SpectralColor(newFunction, bodycolor);
  }

  SpectralColor SpectralColor::operator -(const SpectralColor& speccolor) const{
    #if CML_DEBUG
      if(isBodyColor() != speccolor.isBodyColor()){
        cmlError("Subtracting spectral bodycolor with non-bodycolor.");
      }
    #endif

    CMLFunction* newFunction = cmlCreateFunctionSubFunction(spectrum, speccolor.spectrum);
    return SpectralColor(newFunction, bodycolor);
  }

  SpectralColor SpectralColor::operator *(float factor) const{
    CMLFunction* newFunction = cmlCreateFunctionMulScalar(spectrum, factor);
    return SpectralColor(newFunction, bodycolor);
  }

  SpectralColor SpectralColor::operator /(float divisor) const{
    // note: do not redirect this implementation to the * operator. It slows
    // down the implementation as more constructors need to be called.
    float factor = cmlInverse(divisor);
    CMLFunction* newFunction = cmlCreateFunctionMulScalar(spectrum, factor);
    return SpectralColor(newFunction, bodycolor);
  }

  SpectralColor& SpectralColor::operator +=(const Color& anycolor){
    SpectralColor speccolor = anycolor.toSpectral();
    #if CML_DEBUG
      if(isBodyColor() != speccolor.isBodyColor()){
        cmlError("Adding spectral bodycolor with non-bodycolor.");
      }
    #endif

    CMLFunction* newFunction = cmlCreateFunctionAddFunction(spectrum, speccolor.spectrum);
    cmlReleaseFunction(spectrum);
    spectrum = newFunction;
    return *this;
  }

  SpectralColor& SpectralColor::operator -=(const Color& anycolor){
    SpectralColor speccolor = anycolor.toSpectral();
    #if CML_DEBUG
      if(isBodyColor() != speccolor.isBodyColor()){
        cmlError("Subtracting spectral bodycolor with non-bodycolor.");
      }
    #endif

    CMLFunction* newFunction = cmlCreateFunctionSubFunction(spectrum, speccolor.spectrum);
    cmlReleaseFunction(spectrum);
    spectrum = newFunction;
    return *this;
  }

  SpectralColor& SpectralColor::operator *=(float factor){
    CMLFunction* newFunction = cmlCreateFunctionMulScalar(spectrum, factor);
    cmlReleaseFunction(spectrum);
    spectrum = newFunction;
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


void SpectralColor::from8BitBuffer(const uint8* input){
  CML_UNUSED(input);
}
void SpectralColor::from16BitBuffer(const uint16* input){
  CML_UNUSED(input);
}
void SpectralColor::fromFloatBuffer(const float* input){
  CML_UNUSED(input);
}
void SpectralColor::to8BitBuffer(uint8* output) const {
  CML_UNUSED(output);
}
void SpectralColor::to16BitBuffer(uint16* output) const {
  CML_UNUSED(output);
}
void SpectralColor::toFloatBuffer(float* output) const {
  CML_UNUSED(output);
}


void SpectralColor::fromNormedBuffer(const float* input){
  CML_UNUSED(input);
}
void SpectralColor::toNormedBuffer(float* output) const {
  CML_UNUSED(output);
}
void SpectralColor::fromNormedCartesianBuffer(const float* input){
  CML_UNUSED(input);
}
void SpectralColor::toNormedCartesianBuffer(float* output) const {
  CML_UNUSED(output);
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
    cmlSpectrumRemissionToGray(cmlcm, dest, spectrum, 1);
  }else{
    cmlSpectrumIlluminationToGray(cmlcm, dest, spectrum, 1);
  }
}
void SpectralColor::toXYZBuffer(float* dest) const  {
  if(bodycolor){
    cmlSpectrumRemissionToXYZ (cmlcm, dest, spectrum, 1);
  }else{
    cmlSpectrumIlluminationToXYZ (cmlcm, dest, spectrum, 1);
  }
}
void SpectralColor::toYuvBuffer(float* dest) const  {
  if(bodycolor){
    cmlSpectrumRemissionToYuv (cmlcm, dest, spectrum, 1);
  }else{
    cmlSpectrumIlluminationToYuv (cmlcm, dest, spectrum, 1);
  }
}
void SpectralColor::toYupvpBuffer(float* dest) const{
  if(bodycolor){
    cmlSpectrumRemissionToYupvp(cmlcm, dest, spectrum, 1);
  }else{
    cmlSpectrumIlluminationToYupvp(cmlcm, dest, spectrum, 1);
  }
}
void SpectralColor::toYxyBuffer(float* dest) const  {
  if(bodycolor){
    cmlSpectrumRemissionToYxy (cmlcm, dest, spectrum, 1);
  }else{
    cmlSpectrumIlluminationToYxy (cmlcm, dest, spectrum, 1);
  }
}
void SpectralColor::toLabBuffer(float* dest) const  {
  if(bodycolor){
    cmlSpectrumRemissionToLab (cmlcm, dest, spectrum, 1);
  }else{
    cmlSpectrumIlluminationToLab (cmlcm, dest, spectrum, 1);
  }
}
void SpectralColor::toLchBuffer(float* dest) const  {
  if(bodycolor){
    cmlSpectrumRemissionToLch (cmlcm, dest, spectrum, 1);
  }else{
    cmlSpectrumIlluminationToLch (cmlcm, dest, spectrum, 1);
  }
}
void SpectralColor::toLuvBuffer(float* dest) const  {
  if(bodycolor){
    cmlSpectrumRemissionToLuv (cmlcm, dest, spectrum, 1);
  }else{
    cmlSpectrumIlluminationToLuv (cmlcm, dest, spectrum, 1);
  }
}
void SpectralColor::toRGBBuffer(float* dest) const  {
  if(bodycolor){
    cmlSpectrumRemissionToRGB (cmlcm, dest, spectrum, 1);
  }else{
    cmlSpectrumIlluminationToRGB (cmlcm, dest, spectrum, 1);
  }
}
void SpectralColor::toYCbCrBuffer(float* dest) const{
  if(bodycolor){
    cmlSpectrumRemissionToYCbCr(cmlcm, dest, spectrum, 1);
  }else{
    cmlSpectrumIlluminationToYCbCr(cmlcm, dest, spectrum, 1);
  }
}
void SpectralColor::toHSVBuffer(float* dest) const  {
  if(bodycolor){
    cmlSpectrumRemissionToHSV (cmlcm, dest, spectrum, 1);
  }else{
    cmlSpectrumIlluminationToHSV (cmlcm, dest, spectrum, 1);
  }
}
void SpectralColor::toHSLBuffer(float* dest) const  {
  if(bodycolor){
    cmlSpectrumRemissionToHSL (cmlcm, dest, spectrum, 1);
  }else{
    cmlSpectrumIlluminationToHSL (cmlcm, dest, spectrum, 1);
  }
}
void SpectralColor::toCMYKBuffer(float* dest) const {
  if(bodycolor){
    cmlSpectrumRemissionToCMYK(cmlcm, dest, spectrum, 1);
  }else{
    cmlSpectrumIlluminationToCMYK(cmlcm, dest, spectrum, 1);
  }
}



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

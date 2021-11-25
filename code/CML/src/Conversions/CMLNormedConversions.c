
#include "../CML.h"
#include "../StateMachine/CMLColorMachineState.h"


// ////////////////////////////
// Normed Input
// ////////////////////////////

CML_DEF void cmlNormedInputToGray(CMLOutput gray, CMLInput input, size_t count){
  const float* in  = (float*)input;
  float* out = (float*)gray;
  for(size_t i = 0; i < count; i++){
    cml_NormedInputToGray(out, in);
    out++;
    in++;
  }
}
CML_DEF void cmlNormedInputToXYZ(CMLOutput xyz, CMLInput input, size_t count){
  const float* in  = (float*)input;
  float* out = (float*)xyz;
  for(size_t i = 0; i < count; i++){
    cml_NormedInputToXYZ(out, in);
    out += 3;
    in += 3;
  }
}
CML_DEF void cmlNormedInputToYxy(CMLOutput yxy, CMLInput input, size_t count){
  const float* in  = (float*)input;
  float* out = (float*)yxy;
  for(size_t i = 0; i < count; i++){
    cml_NormedInputToYxy(out, in);
    out += 3;
    in += 3;
  }
}
CML_DEF void cmlNormedInputToYuv(CMLOutput yuv, CMLInput input, size_t count){
  const float* in  = (float*)input;
  float* out = (float*)yuv;
  for(size_t i = 0; i < count; i++){
    cml_NormedInputToYuv(out, in);
    out += 3;
    in += 3;
  }
}
CML_DEF void cmlNormedInputToYupvp(CMLOutput yupvp, CMLInput input, size_t count){
  const float* in  = (float*)input;
  float* out = (float*)yupvp;
  for(size_t i = 0; i < count; i++){
    cml_NormedInputToYupvp(out, in);
    out += 3;
    in += 3;
  }
}
CML_DEF void cmlNormedInputToLab(CMLOutput lab, CMLInput input, size_t count){
  const float* in  = (float*)input;
  float* out = (float*)lab;
  for(size_t i = 0; i < count; i++){
    cml_NormedInputToLab(out, in);
    out += 3;
    in += 3;
  }
}
CML_DEF void cmlNormedInputToLch(CMLOutput lch, CMLInput input, size_t count){
  const float* in  = (float*)input;
  float* out = (float*)lch;
  for(size_t i = 0; i < count; i++){
    cml_NormedInputToLch(out, in);
    out += 3;
    in += 3;
  }
}
CML_DEF void cmlNormedInputToLuv(CMLOutput luv, CMLInput input, size_t count){
  const float* in  = (float*)input;
  float* out = (float*)luv;
  for(size_t i = 0; i < count; i++){
    cml_NormedInputToLuv(out, in);
    out += 3;
    in += 3;
  }
}
CML_DEF void cmlNormedInputToRGB(CMLOutput rgb, CMLInput input, size_t count){
  const float* in  = (float*)input;
  float* out = (float*)rgb;
  for(size_t i = 0; i < count; i++){
    cml_NormedInputToRGB(out, in);
    out += 3;
    in += 3;
  }
}
CML_DEF void cmlNormedInputToYCbCr(CMLOutput ycbcr, CMLInput input, size_t count){
  const float* in  = (float*)input;
  float* out = (float*)ycbcr;
  for(size_t i = 0; i < count; i++){
    cml_NormedInputToYCbCr(out, in);
    out += 3;
    in += 3;
  }
}
CML_DEF void cmlNormedInputToHSV(CMLOutput hsv, CMLInput input, size_t count){
  const float* in  = (float*)input;
  float* out = (float*)hsv;
  for(size_t i = 0; i < count; i++){
    cml_NormedInputToHSV(out, in);
    out += 3;
    in += 3;
  }
}
CML_DEF void cmlNormedInputToHSL(CMLOutput hsl, CMLInput input, size_t count){
  const float* in  = (float*)input;
  float* out = (float*)hsl;
  for(size_t i = 0; i < count; i++){
    cml_NormedInputToHSL(out, in);
    out += 3;
    in += 3;
  }
}
CML_DEF void cmlNormedInputToCMYK(CMLOutput cmyk, CMLInput input, size_t count){
  const float* in  = (float*)input;
  float* out = (float*)cmyk;
  for(size_t i = 0; i < count; i++){
    cml_NormedInputToCMYK(out, in);
    out += 4;
    in += 4;
  }
}



// ////////////////////////////
// Normed Output
// ////////////////////////////

CML_DEF void cmlGrayToNormedOutput(CMLOutput output, CMLInput gray, size_t count){
  const float* in  = (float*)gray;
  float* out = (float*)output;
  for(size_t i = 0; i < count; i++){
    cml_GrayToNormedOutput(out, in);
    out++;
    in++;
  }
}
CML_DEF void cmlXYZToNormedOutput(CMLOutput output, CMLInput xyz, size_t count){
  const float* in  = (float*)xyz;
  float* out = (float*)output;
  for(size_t i = 0; i < count; i++){
    cml_XYZToNormedOutput(out, in);
    out += 3;
    in += 3;
  }
}
CML_DEF void cmlYxyToNormedOutput(CMLOutput output, CMLInput yxy, size_t count){
  const float* in  = (float*)yxy;
  float* out = (float*)output;
  for(size_t i = 0; i < count; i++){
    cml_YxyToNormedOutput(out, in);
    out += 3;
    in += 3;
  }
}
CML_DEF void cmlYuvToNormedOutput(CMLOutput output, CMLInput yuv, size_t count){
  const float* in  = (float*)yuv;
  float* out = (float*)output;
  for(size_t i = 0; i < count; i++){
    cml_YuvToNormedOutput(out, in);
    out += 3;
    in += 3;
  }
}
CML_DEF void cmlYupvpToNormedOutput(CMLOutput output, CMLInput yupvp, size_t count){
  const float* in  = (float*)yupvp;
  float* out = (float*)output;
  for(size_t i = 0; i < count; i++){
    cml_YupvpToNormedOutput(out, in);
    out += 3;
    in += 3;
  }
}
CML_DEF void cmlLabToNormedOutput(CMLOutput output, CMLInput lab, size_t count){
  const float* in  = (float*)lab;
  float* out = (float*)output;
  for(size_t i = 0; i < count; i++){
    cml_LabToNormedOutput(out, in);
    out += 3;
    in += 3;
  }
}
CML_DEF void cmlLchToNormedOutput(CMLOutput output, CMLInput lch, size_t count){
  const float* in  = (float*)lch;
  float* out = (float*)output;
  for(size_t i = 0; i < count; i++){
    cml_LchToNormedOutput(out, in);
    out += 3;
    in += 3;
  }
}
CML_DEF void cmlLuvToNormedOutput(CMLOutput output, CMLInput luv, size_t count){
  const float* in  = (float*)luv;
  float* out = (float*)output;
  for(size_t i = 0; i < count; i++){
    cml_LuvToNormedOutput(out, in);
    out += 3;
    in += 3;
  }
}
CML_DEF void cmlRGBToNormedOutput(CMLOutput output, CMLInput rgb, size_t count){
  const float* in  = (float*)rgb;
  float* out = (float*)output;
  for(size_t i = 0; i < count; i++){
    cml_RGBToNormedOutput(out, in);
    out += 3;
    in += 3;
  }
}
CML_DEF void cmlYCbCrToNormedOutput(CMLOutput output, CMLInput ycbcr, size_t count){
  const float* in  = (float*)ycbcr;
  float* out = (float*)output;
  for(size_t i = 0; i < count; i++){
    cml_YCbCrToNormedOutput(out, in);
    out += 3;
    in += 3;
  }
}
CML_DEF void cmlHSVToNormedOutput(CMLOutput output, CMLInput hsv, size_t count){
  const float* in  = (float*)hsv;
  float* out = (float*)output;
  for(size_t i = 0; i < count; i++){
    cml_HSVToNormedOutput(out, in);
    out += 3;
    in += 3;
  }
}
CML_DEF void cmlHSLToNormedOutput(CMLOutput output, CMLInput hsl, size_t count){
  const float* in  = (float*)hsl;
  float* out = (float*)output;
  for(size_t i = 0; i < count; i++){
    cml_HSLToNormedOutput(out, in);
    out += 3;
    in += 3;
  }
}
CML_DEF void cmlCMYKToNormedOutput(CMLOutput output, CMLInput cmyk, size_t count){
  const float* in  = (float*)cmyk;
  float* out = (float*)output;
  for(size_t i = 0; i < count; i++){
    cml_CMYKToNormedOutput(out, in);
    out += 4;
    in += 4;
  }
}



// ////////////////////////////
// Normed Cartesian Input
// ////////////////////////////

CML_DEF void cmlNormedCartesianInputToLch(CMLOutput lch, CMLInput input, size_t count){
  const float* in  = (float*)input;
  float* out = (float*)lch;
  for(size_t i = 0; i < count; i++){
    cml_NormedCartesianInputToLch(out, in);
    out += 3;
    in += 3;
  }
}
CML_DEF void cmlNormedCartesianInputToHSV(CMLOutput hsv, CMLInput input, size_t count){
  const float* in  = (float*)input;
  float* out = (float*)hsv;
  for(size_t i = 0; i < count; i++){
    cml_NormedCartesianInputToHSV(out, in);
    out += 3;
    in += 3;
  }
}
CML_DEF void cmlNormedCartesianInputToHSL(CMLOutput hsl, CMLInput input, size_t count){
  const float* in  = (float*)input;
  float* out = (float*)hsl;
  for(size_t i = 0; i < count; i++){
    cml_NormedCartesianInputToHSL(out, in);
    out += 3;
    in += 3;
  }
}



// ////////////////////////////
// Normed Cartesian Output
// ////////////////////////////

CML_DEF void cmlLchToNormedCartesianOutput(CMLOutput output, CMLInput lch, size_t count){
  const float* in  = (float*)lch;
  float* out = (float*)output;
  for(size_t i = 0; i < count; i++){
    cml_LchToNormedCartesianOutput(out, in);
    out += 3;
    in += 3;
  }
}
CML_DEF void cmlHSVToNormedCartesianOutput(CMLOutput output, CMLInput hsv, size_t count){
  const float* in  = (float*)hsv;
  float* out = (float*)output;
  for(size_t i = 0; i < count; i++){
    cml_HSVToNormedCartesianOutput(out, in);
    out += 3;
    in += 3;
  }
}
CML_DEF void cmlHSLToNormedCartesianOutput(CMLOutput output, CMLInput hsl, size_t count){
  const float* in  = (float*)hsl;
  float* out = (float*)output;
  for(size_t i = 0; i < count; i++){
    cml_HSLToNormedCartesianOutput(out, in);
    out += 3;
    in += 3;
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

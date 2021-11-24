
#include "../CML.h"
#include "../StateMachine/CMLColorMachineState.h"


// ////////////////////////////
// Normed Input
// ////////////////////////////

CML_DEF void cmlGrayWithNormedInput(CMLOutput gray, CMLInput input, size_t count){
  const float* in  = (float*)input;
  float* out = (float*)gray;
  for(size_t i = 0; i < count; i++){
    cml_GrayWithNormedInput(out, in);
    out++;
    in++;
  }
}
CML_DEF void cmlXYZWithNormedInput(CMLOutput xyz, CMLInput input, size_t count){
  const float* in  = (float*)input;
  float* out = (float*)xyz;
  for(size_t i = 0; i < count; i++){
    cml_XYZWithNormedInput(out, in);
    out += 3;
    in += 3;
  }
}
CML_DEF void cmlYxyWithNormedInput(CMLOutput yxy, CMLInput input, size_t count){
  const float* in  = (float*)input;
  float* out = (float*)yxy;
  for(size_t i = 0; i < count; i++){
    cml_YxyWithNormedInput(out, in);
    out += 3;
    in += 3;
  }
}
CML_DEF void cmlYuvWithNormedInput(CMLOutput yuv, CMLInput input, size_t count){
  const float* in  = (float*)input;
  float* out = (float*)yuv;
  for(size_t i = 0; i < count; i++){
    cml_YuvWithNormedInput(out, in);
    out += 3;
    in += 3;
  }
}
CML_DEF void cmlYupvpWithNormedInput(CMLOutput yupvp, CMLInput input, size_t count){
  const float* in  = (float*)input;
  float* out = (float*)yupvp;
  for(size_t i = 0; i < count; i++){
    cml_YupvpWithNormedInput(out, in);
    out += 3;
    in += 3;
  }
}
CML_DEF void cmlLabWithNormedInput(CMLOutput lab, CMLInput input, size_t count){
  const float* in  = (float*)input;
  float* out = (float*)lab;
  for(size_t i = 0; i < count; i++){
    cml_LabWithNormedInput(out, in);
    out += 3;
    in += 3;
  }
}
CML_DEF void cmlLchWithNormedInput(CMLOutput lch, CMLInput input, size_t count){
  const float* in  = (float*)input;
  float* out = (float*)lch;
  for(size_t i = 0; i < count; i++){
    cml_LchWithNormedInput(out, in);
    out += 3;
    in += 3;
  }
}
CML_DEF void cmlLuvWithNormedInput(CMLOutput luv, CMLInput input, size_t count){
  const float* in  = (float*)input;
  float* out = (float*)luv;
  for(size_t i = 0; i < count; i++){
    cml_LuvWithNormedInput(out, in);
    out += 3;
    in += 3;
  }
}
CML_DEF void cmlRGBWithNormedInput(CMLOutput rgb, CMLInput input, size_t count){
  const float* in  = (float*)input;
  float* out = (float*)rgb;
  for(size_t i = 0; i < count; i++){
    cml_RGBWithNormedInput(out, in);
    out += 3;
    in += 3;
  }
}
CML_DEF void cmlYCbCrWithNormedInput(CMLOutput ycbcr, CMLInput input, size_t count){
  const float* in  = (float*)input;
  float* out = (float*)ycbcr;
  for(size_t i = 0; i < count; i++){
    cml_YCbCrWithNormedInput(out, in);
    out += 3;
    in += 3;
  }
}
CML_DEF void cmlHSVWithNormedInput(CMLOutput hsv, CMLInput input, size_t count){
  const float* in  = (float*)input;
  float* out = (float*)hsv;
  for(size_t i = 0; i < count; i++){
    cml_HSVWithNormedInput(out, in);
    out += 3;
    in += 3;
  }
}
CML_DEF void cmlHSLWithNormedInput(CMLOutput hsl, CMLInput input, size_t count){
  const float* in  = (float*)input;
  float* out = (float*)hsl;
  for(size_t i = 0; i < count; i++){
    cml_HSLWithNormedInput(out, in);
    out += 3;
    in += 3;
  }
}
CML_DEF void cmlCMYKWithNormedInput(CMLOutput cmyk, CMLInput input, size_t count){
  const float* in  = (float*)input;
  float* out = (float*)cmyk;
  for(size_t i = 0; i < count; i++){
    cml_CMYKWithNormedInput(out, in);
    out += 4;
    in += 4;
  }
}



// ////////////////////////////
// Normed Output
// ////////////////////////////

CML_DEF void cmlNormedOutputWithGray(CMLOutput output, CMLInput gray, size_t count){
  const float* in  = (float*)gray;
  float* out = (float*)output;
  for(size_t i = 0; i < count; i++){
    cml_NormedOutputWithGray(out, in);
    out++;
    in++;
  }
}
CML_DEF void cmlNormedOutputWithXYZ(CMLOutput output, CMLInput xyz, size_t count){
  const float* in  = (float*)xyz;
  float* out = (float*)output;
  for(size_t i = 0; i < count; i++){
    cml_NormedOutputWithXYZ(out, in);
    out += 3;
    in += 3;
  }
}
CML_DEF void cmlNormedOutputWithYxy(CMLOutput output, CMLInput yxy, size_t count){
  const float* in  = (float*)yxy;
  float* out = (float*)output;
  for(size_t i = 0; i < count; i++){
    cml_NormedOutputWithYxy(out, in);
    out += 3;
    in += 3;
  }
}
CML_DEF void cmlNormedOutputWithYuv(CMLOutput output, CMLInput yuv, size_t count){
  const float* in  = (float*)yuv;
  float* out = (float*)output;
  for(size_t i = 0; i < count; i++){
    cml_NormedOutputWithYuv(out, in);
    out += 3;
    in += 3;
  }
}
CML_DEF void cmlNormedOutputWithYupvp(CMLOutput output, CMLInput yupvp, size_t count){
  const float* in  = (float*)yupvp;
  float* out = (float*)output;
  for(size_t i = 0; i < count; i++){
    cml_NormedOutputWithYupvp(out, in);
    out += 3;
    in += 3;
  }
}
CML_DEF void cmlNormedOutputWithLab(CMLOutput output, CMLInput lab, size_t count){
  const float* in  = (float*)lab;
  float* out = (float*)output;
  for(size_t i = 0; i < count; i++){
    cml_NormedOutputWithLab(out, in);
    out += 3;
    in += 3;
  }
}
CML_DEF void cmlNormedOutputWithLch(CMLOutput output, CMLInput lch, size_t count){
  const float* in  = (float*)lch;
  float* out = (float*)output;
  for(size_t i = 0; i < count; i++){
    cml_NormedOutputWithLch(out, in);
    out += 3;
    in += 3;
  }
}
CML_DEF void cmlNormedOutputWithLuv(CMLOutput output, CMLInput luv, size_t count){
  const float* in  = (float*)luv;
  float* out = (float*)output;
  for(size_t i = 0; i < count; i++){
    cml_NormedOutputWithLuv(out, in);
    out += 3;
    in += 3;
  }
}
CML_DEF void cmlNormedOutputWithRGB(CMLOutput output, CMLInput rgb, size_t count){
  const float* in  = (float*)rgb;
  float* out = (float*)output;
  for(size_t i = 0; i < count; i++){
    cml_NormedOutputWithRGB(out, in);
    out += 3;
    in += 3;
  }
}
CML_DEF void cmlNormedOutputWithYCbCr(CMLOutput output, CMLInput ycbcr, size_t count){
  const float* in  = (float*)ycbcr;
  float* out = (float*)output;
  for(size_t i = 0; i < count; i++){
    cml_NormedOutputWithYCbCr(out, in);
    out += 3;
    in += 3;
  }
}
CML_DEF void cmlNormedOutputWithHSV(CMLOutput output, CMLInput hsv, size_t count){
  const float* in  = (float*)hsv;
  float* out = (float*)output;
  for(size_t i = 0; i < count; i++){
    cml_NormedOutputWithHSV(out, in);
    out += 3;
    in += 3;
  }
}
CML_DEF void cmlNormedOutputWithHSL(CMLOutput output, CMLInput hsl, size_t count){
  const float* in  = (float*)hsl;
  float* out = (float*)output;
  for(size_t i = 0; i < count; i++){
    cml_NormedOutputWithHSL(out, in);
    out += 3;
    in += 3;
  }
}
CML_DEF void cmlNormedOutputWithCMYK(CMLOutput output, CMLInput cmyk, size_t count){
  const float* in  = (float*)cmyk;
  float* out = (float*)output;
  for(size_t i = 0; i < count; i++){
    cml_NormedOutputWithCMYK(out, in);
    out += 4;
    in += 4;
  }
}



// ////////////////////////////
// Normed Cartesian Input
// ////////////////////////////

CML_DEF void cmlLchWithNormedCartesianInput(CMLOutput lch, CMLInput input, size_t count){
  const float* in  = (float*)input;
  float* out = (float*)lch;
  for(size_t i = 0; i < count; i++){
    cml_LchWithNormedCartesianInput(out, in);
    out += 3;
    in += 3;
  }
}
CML_DEF void cmlHSVWithNormedCartesianInput(CMLOutput hsv, CMLInput input, size_t count){
  const float* in  = (float*)input;
  float* out = (float*)hsv;
  for(size_t i = 0; i < count; i++){
    cml_HSVWithNormedCartesianInput(out, in);
    out += 3;
    in += 3;
  }
}
CML_DEF void cmlHSLWithNormedCartesianInput(CMLOutput hsl, CMLInput input, size_t count){
  const float* in  = (float*)input;
  float* out = (float*)hsl;
  for(size_t i = 0; i < count; i++){
    cml_HSLWithNormedCartesianInput(out, in);
    out += 3;
    in += 3;
  }
}



// ////////////////////////////
// Normed Cartesian Output
// ////////////////////////////

CML_DEF void cmlNormedCartesianOutputWithLch(CMLOutput output, CMLInput lch, size_t count){
  const float* in  = (float*)lch;
  float* out = (float*)output;
  for(size_t i = 0; i < count; i++){
    cml_NormedCartesianOutputWithLch(out, in);
    out += 3;
    in += 3;
  }
}
CML_DEF void cmlNormedCartesianOutputWithHSV(CMLOutput output, CMLInput hsv, size_t count){
  const float* in  = (float*)hsv;
  float* out = (float*)output;
  for(size_t i = 0; i < count; i++){
    cml_NormedCartesianOutputWithHSV(out, in);
    out += 3;
    in += 3;
  }
}
CML_DEF void cmlNormedCartesianOutputWithHSL(CMLOutput output, CMLInput hsl, size_t count){
  const float* in  = (float*)hsl;
  float* out = (float*)output;
  for(size_t i = 0; i < count; i++){
    cml_NormedCartesianOutputWithHSL(out, in);
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

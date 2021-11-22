
#include "../CML.h"
#include "../StateMachine/CMLColorMachineState.h"


// ////////////////////////////
// Normed Input
// ////////////////////////////

CML_API void CMLGrayfromNormedInput (CMLOutput gray , CMLInput input, CMLSize count){
  CMLSize i;
  const float* in  = (float*)input;
  float* out = (float*)gray;
  for(i=0; i<count; i++){
    CMLInternalGrayfromNormedInput (out, in);
    out++;
    in++;
  }
}
CML_API void CMLXYZfromNormedInput  (CMLOutput xyz  , CMLInput input, CMLSize count){
  CMLSize i;
  const float* in  = (float*)input;
  float* out = (float*)xyz;
  for(i=0; i<count; i++){
    CMLInternalXYZfromNormedInput  (out, in);
    out += 3;
    in += 3;
  }
}
CML_API void CMLYxyfromNormedInput  (CMLOutput yxy  , CMLInput input, CMLSize count){
  CMLSize i;
  const float* in  = (float*)input;
  float* out = (float*)yxy;
  for(i=0; i<count; i++){
    CMLInternalYxyfromNormedInput  (out, in);
    out += 3;
    in += 3;
  }
}
CML_API void CMLYuvfromNormedInput  (CMLOutput yuv  , CMLInput input, CMLSize count){
  CMLSize i;
  const float* in  = (float*)input;
  float* out = (float*)yuv;
  for(i=0; i<count; i++){
    CMLInternalYuvfromNormedInput  (out, in);
    out += 3;
    in += 3;
  }
}
CML_API void CMLYupvpfromNormedInput  (CMLOutput yupvp  , CMLInput input, CMLSize count){
  CMLSize i;
  const float* in  = (float*)input;
  float* out = (float*)yupvp;
  for(i=0; i<count; i++){
    CMLInternalYupvpfromNormedInput  (out, in);
    out += 3;
    in += 3;
  }
}
CML_API void CMLLabfromNormedInput  (CMLOutput lab  , CMLInput input, CMLSize count){
  CMLSize i;
  const float* in  = (float*)input;
  float* out = (float*)lab;
  for(i=0; i<count; i++){
    CMLInternalLabfromNormedInput  (out, in);
    out += 3;
    in += 3;
  }
}
CML_API void CMLLchfromNormedInput  (CMLOutput lch  , CMLInput input, CMLSize count){
  CMLSize i;
  const float* in  = (float*)input;
  float* out = (float*)lch;
  for(i=0; i<count; i++){
    CMLInternalLchfromNormedInput  (out, in);
    out += 3;
    in += 3;
  }
}
CML_API void CMLLuvfromNormedInput  (CMLOutput luv  , CMLInput input, CMLSize count){
  CMLSize i;
  const float* in  = (float*)input;
  float* out = (float*)luv;
  for(i=0; i<count; i++){
    CMLInternalLuvfromNormedInput  (out, in);
    out += 3;
    in += 3;
  }
}
CML_API void CMLRGBfromNormedInput  (CMLOutput rgb  , CMLInput input, CMLSize count){
  CMLSize i;
  const float* in  = (float*)input;
  float* out = (float*)rgb;
  for(i=0; i<count; i++){
    CMLInternalRGBfromNormedInput  (out, in);
    out += 3;
    in += 3;
  }
}
CML_API void CMLYCbCrfromNormedInput(CMLOutput ycbcr, CMLInput input, CMLSize count){
  CMLSize i;
  const float* in  = (float*)input;
  float* out = (float*)ycbcr;
  for(i=0; i<count; i++){
    CMLInternalYCbCrfromNormedInput(out, in);
    out += 3;
    in += 3;
  }
}
CML_API void CMLHSVfromNormedInput  (CMLOutput hsv  , CMLInput input, CMLSize count){
  CMLSize i;
  const float* in  = (float*)input;
  float* out = (float*)hsv;
  for(i=0; i<count; i++){
    CMLInternalHSVfromNormedInput  (out, in);
    out += 3;
    in += 3;
  }
}
CML_API void CMLHSLfromNormedInput  (CMLOutput hsl  , CMLInput input, CMLSize count){
  CMLSize i;
  const float* in  = (float*)input;
  float* out = (float*)hsl;
  for(i=0; i<count; i++){
    CMLInternalHSLfromNormedInput  (out, in);
    out += 3;
    in += 3;
  }
}
CML_API void CMLCMYKfromNormedInput (CMLOutput cmyk , CMLInput input, CMLSize count){
  CMLSize i;
  const float* in  = (float*)input;
  float* out = (float*)cmyk;
  for(i=0; i<count; i++){
    CMLInternalCMYKfromNormedInput (out, in);
    out += 4;
    in += 4;
  }
}







// ////////////////////////////
// Normed Output
// ////////////////////////////

CML_API void CMLGraytoNormedOutput (CMLOutput output, CMLInput gray , CMLSize count){
  CMLSize i;
  const float* in  = (float*)gray;
  float* out = (float*)output;
  for(i=0; i<count; i++){
    CMLInternalGraytoNormedOutput (out, in);
    out++;
    in++;
  }
}
CML_API void CMLXYZtoNormedOutput  (CMLOutput output, CMLInput xyz  , CMLSize count){
  CMLSize i;
  const float* in  = (float*)xyz;
  float* out = (float*)output;
  for(i=0; i<count; i++){
    CMLInternalXYZtoNormedOutput  (out, in);
    out += 3;
    in += 3;
  }
}
CML_API void CMLYxytoNormedOutput  (CMLOutput output, CMLInput yxy  , CMLSize count){
  CMLSize i;
  const float* in  = (float*)yxy;
  float* out = (float*)output;
  for(i=0; i<count; i++){
    CMLInternalYxytoNormedOutput  (out, in);
    out += 3;
    in += 3;
  }
}
CML_API void CMLYuvtoNormedOutput  (CMLOutput output, CMLInput yuv  , CMLSize count){
  CMLSize i;
  const float* in  = (float*)yuv;
  float* out = (float*)output;
  for(i=0; i<count; i++){
    CMLInternalYuvtoNormedOutput  (out, in);
    out += 3;
    in += 3;
  }
}
CML_API void CMLYupvptoNormedOutput  (CMLOutput output, CMLInput yupvp  , CMLSize count){
  CMLSize i;
  const float* in  = (float*)yupvp;
  float* out = (float*)output;
  for(i=0; i<count; i++){
    CMLInternalYupvptoNormedOutput  (out, in);
    out += 3;
    in += 3;
  }
}
CML_API void CMLLabtoNormedOutput  (CMLOutput output, CMLInput lab  , CMLSize count){
  CMLSize i;
  const float* in  = (float*)lab;
  float* out = (float*)output;
  for(i=0; i<count; i++){
    CMLInternalLabtoNormedOutput  (out, in);
    out += 3;
    in += 3;
  }
}
CML_API void CMLLchtoNormedOutput  (CMLOutput output, CMLInput lch  , CMLSize count){
  CMLSize i;
  const float* in  = (float*)lch;
  float* out = (float*)output;
  for(i=0; i<count; i++){
    CMLInternalLchtoNormedOutput  (out, in);
    out += 3;
    in += 3;
  }
}
CML_API void CMLLuvtoNormedOutput  (CMLOutput output, CMLInput luv  , CMLSize count){
  CMLSize i;
  const float* in  = (float*)luv;
  float* out = (float*)output;
  for(i=0; i<count; i++){
    CMLInternalLuvtoNormedOutput  (out, in);
    out += 3;
    in += 3;
  }
}
CML_API void CMLRGBtoNormedOutput  (CMLOutput output, CMLInput rgb  , CMLSize count){
  CMLSize i;
  const float* in  = (float*)rgb;
  float* out = (float*)output;
  for(i=0; i<count; i++){
    CMLInternalRGBtoNormedOutput  (out, in);
    out += 3;
    in += 3;
  }
}
CML_API void CMLYCbCrtoNormedOutput(CMLOutput output, CMLInput ycbcr, CMLSize count){
  CMLSize i;
  const float* in  = (float*)ycbcr;
  float* out = (float*)output;
  for(i=0; i<count; i++){
    CMLInternalYCbCrtoNormedOutput(out, in);
    out += 3;
    in += 3;
  }
}
CML_API void CMLHSVtoNormedOutput  (CMLOutput output, CMLInput hsv  , CMLSize count){
  CMLSize i;
  const float* in  = (float*)hsv;
  float* out = (float*)output;
  for(i=0; i<count; i++){
    CMLInternalHSVtoNormedOutput  (out, in);
    out += 3;
    in += 3;
  }
}
CML_API void CMLHSLtoNormedOutput  (CMLOutput output, CMLInput hsl  , CMLSize count){
  CMLSize i;
  const float* in  = (float*)hsl;
  float* out = (float*)output;
  for(i=0; i<count; i++){
    CMLInternalHSLtoNormedOutput  (out, in);
    out += 3;
    in += 3;
  }
}
CML_API void CMLCMYKtoNormedOutput (CMLOutput output, CMLInput cmyk , CMLSize count){
  CMLSize i;
  const float* in  = (float*)cmyk;
  float* out = (float*)output;
  for(i=0; i<count; i++){
    CMLInternalCMYKtoNormedOutput (out, in);
    out += 4;
    in += 4;
  }
}






// ////////////////////////////
// Normed Cartesian Input
// ////////////////////////////


CML_API void CMLLchfromNormedCartesianInput  (CMLOutput lch  , CMLInput input, CMLSize count){
  CMLSize i;
  const float* in  = (float*)input;
  float* out = (float*)lch;
  for(i=0; i<count; i++){
    CMLInternalLchfromNormedCartesianInput  (out, in);
    out += 3;
    in += 3;
  }
}
CML_API void CMLHSVfromNormedCartesianInput  (CMLOutput hsv  , CMLInput input, CMLSize count){
  CMLSize i;
  const float* in  = (float*)input;
  float* out = (float*)hsv;
  for(i=0; i<count; i++){
    CMLInternalHSVfromNormedCartesianInput  (out, in);
    out += 3;
    in += 3;
  }
}
CML_API void CMLHSLfromNormedCartesianInput  (CMLOutput hsl  , CMLInput input, CMLSize count){
  CMLSize i;
  const float* in  = (float*)input;
  float* out = (float*)hsl;
  for(i=0; i<count; i++){
    CMLInternalHSLfromNormedCartesianInput  (out, in);
    out += 3;
    in += 3;
  }
}








// ////////////////////////////
// Normed Cartesian Output
// ////////////////////////////

CML_API void CMLLchtoNormedCartesianOutput  (CMLOutput output, CMLInput lch  , CMLSize count){
  CMLSize i;
  const float* in  = (float*)lch;
  float* out = (float*)output;
  for(i=0; i<count; i++){
    CMLInternalLchtoNormedCartesianOutput  (out, in);
    out += 3;
    in += 3;
  }
}
CML_API void CMLHSVtoNormedCartesianOutput  (CMLOutput output, CMLInput hsv  , CMLSize count){
  CMLSize i;
  const float* in  = (float*)hsv;
  float* out = (float*)output;
  for(i=0; i<count; i++){
    CMLInternalHSVtoNormedCartesianOutput  (out, in);
    out += 3;
    in += 3;
  }
}
CML_API void CMLHSLtoNormedCartesianOutput  (CMLOutput output, CMLInput hsl  , CMLSize count){
  CMLSize i;
  const float* in  = (float*)hsl;
  float* out = (float*)output;
  for(i=0; i<count; i++){
    CMLInternalHSLtoNormedCartesianOutput  (out, in);
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

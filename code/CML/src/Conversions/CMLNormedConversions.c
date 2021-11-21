
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.


#include "../CML.h"
#include "../StateMachine/CMLColorMachineState.h"


// ////////////////////////////
// Normed Input
// ////////////////////////////

CMLAPI void CMLGrayfromNormedInput (CMLOutput gray , CMLInput input, CMLSize count){
  CMLSize i;
  const float* in  = (float*)input;
  float* out = (float*)gray;
  for(i=0; i<count; i++){
    CMLInternalGrayfromNormedInput (out, in);
    out++;
    in++;
  }
}
CMLAPI void CMLXYZfromNormedInput  (CMLOutput XYZ  , CMLInput input, CMLSize count){
  CMLSize i;
  const float* in  = (float*)input;
  float* out = (float*)XYZ;
  for(i=0; i<count; i++){
    CMLInternalXYZfromNormedInput  (out, in);
    out += 3;
    in += 3;
  }
}
CMLAPI void CMLYxyfromNormedInput  (CMLOutput Yxy  , CMLInput input, CMLSize count){
  CMLSize i;
  const float* in  = (float*)input;
  float* out = (float*)Yxy;
  for(i=0; i<count; i++){
    CMLInternalYxyfromNormedInput  (out, in);
    out += 3;
    in += 3;
  }
}
CMLAPI void CMLYuvfromNormedInput  (CMLOutput Yuv  , CMLInput input, CMLSize count){
  CMLSize i;
  const float* in  = (float*)input;
  float* out = (float*)Yuv;
  for(i=0; i<count; i++){
    CMLInternalYuvfromNormedInput  (out, in);
    out += 3;
    in += 3;
  }
}
CMLAPI void CMLYupvpfromNormedInput  (CMLOutput Yupvp  , CMLInput input, CMLSize count){
  CMLSize i;
  const float* in  = (float*)input;
  float* out = (float*)Yupvp;
  for(i=0; i<count; i++){
    CMLInternalYupvpfromNormedInput  (out, in);
    out += 3;
    in += 3;
  }
}
CMLAPI void CMLLabfromNormedInput  (CMLOutput Lab  , CMLInput input, CMLSize count){
  CMLSize i;
  const float* in  = (float*)input;
  float* out = (float*)Lab;
  for(i=0; i<count; i++){
    CMLInternalLabfromNormedInput  (out, in);
    out += 3;
    in += 3;
  }
}
CMLAPI void CMLLchfromNormedInput  (CMLOutput Lch  , CMLInput input, CMLSize count){
  CMLSize i;
  const float* in  = (float*)input;
  float* out = (float*)Lch;
  for(i=0; i<count; i++){
    CMLInternalLchfromNormedInput  (out, in);
    out += 3;
    in += 3;
  }
}
CMLAPI void CMLLuvfromNormedInput  (CMLOutput Luv  , CMLInput input, CMLSize count){
  CMLSize i;
  const float* in  = (float*)input;
  float* out = (float*)Luv;
  for(i=0; i<count; i++){
    CMLInternalLuvfromNormedInput  (out, in);
    out += 3;
    in += 3;
  }
}
CMLAPI void CMLRGBfromNormedInput  (CMLOutput RGB  , CMLInput input, CMLSize count){
  CMLSize i;
  const float* in  = (float*)input;
  float* out = (float*)RGB;
  for(i=0; i<count; i++){
    CMLInternalRGBfromNormedInput  (out, in);
    out += 3;
    in += 3;
  }
}
CMLAPI void CMLYCbCrfromNormedInput(CMLOutput YCbCr, CMLInput input, CMLSize count){
  CMLSize i;
  const float* in  = (float*)input;
  float* out = (float*)YCbCr;
  for(i=0; i<count; i++){
    CMLInternalYCbCrfromNormedInput(out, in);
    out += 3;
    in += 3;
  }
}
CMLAPI void CMLHSVfromNormedInput  (CMLOutput HSV  , CMLInput input, CMLSize count){
  CMLSize i;
  const float* in  = (float*)input;
  float* out = (float*)HSV;
  for(i=0; i<count; i++){
    CMLInternalHSVfromNormedInput  (out, in);
    out += 3;
    in += 3;
  }
}
CMLAPI void CMLHSLfromNormedInput  (CMLOutput HSL  , CMLInput input, CMLSize count){
  CMLSize i;
  const float* in  = (float*)input;
  float* out = (float*)HSL;
  for(i=0; i<count; i++){
    CMLInternalHSLfromNormedInput  (out, in);
    out += 3;
    in += 3;
  }
}
CMLAPI void CMLCMYKfromNormedInput (CMLOutput CMYK , CMLInput input, CMLSize count){
  CMLSize i;
  const float* in  = (float*)input;
  float* out = (float*)CMYK;
  for(i=0; i<count; i++){
    CMLInternalCMYKfromNormedInput (out, in);
    out += 4;
    in += 4;
  }
}







// ////////////////////////////
// Normed Output
// ////////////////////////////

CMLAPI void CMLGraytoNormedOutput (CMLOutput output, CMLInput gray , CMLSize count){
  CMLSize i;
  const float* in  = (float*)gray;
  float* out = (float*)output;
  for(i=0; i<count; i++){
    CMLInternalGraytoNormedOutput (out, in);
    out++;
    in++;
  }
}
CMLAPI void CMLXYZtoNormedOutput  (CMLOutput output, CMLInput XYZ  , CMLSize count){
  CMLSize i;
  const float* in  = (float*)XYZ;
  float* out = (float*)output;
  for(i=0; i<count; i++){
    CMLInternalXYZtoNormedOutput  (out, in);
    out += 3;
    in += 3;
  }
}
CMLAPI void CMLYxytoNormedOutput  (CMLOutput output, CMLInput Yxy  , CMLSize count){
  CMLSize i;
  const float* in  = (float*)Yxy;
  float* out = (float*)output;
  for(i=0; i<count; i++){
    CMLInternalYxytoNormedOutput  (out, in);
    out += 3;
    in += 3;
  }
}
CMLAPI void CMLYuvtoNormedOutput  (CMLOutput output, CMLInput Yuv  , CMLSize count){
  CMLSize i;
  const float* in  = (float*)Yuv;
  float* out = (float*)output;
  for(i=0; i<count; i++){
    CMLInternalYuvtoNormedOutput  (out, in);
    out += 3;
    in += 3;
  }
}
CMLAPI void CMLYupvptoNormedOutput  (CMLOutput output, CMLInput Yupvp  , CMLSize count){
  CMLSize i;
  const float* in  = (float*)Yupvp;
  float* out = (float*)output;
  for(i=0; i<count; i++){
    CMLInternalYupvptoNormedOutput  (out, in);
    out += 3;
    in += 3;
  }
}
CMLAPI void CMLLabtoNormedOutput  (CMLOutput output, CMLInput Lab  , CMLSize count){
  CMLSize i;
  const float* in  = (float*)Lab;
  float* out = (float*)output;
  for(i=0; i<count; i++){
    CMLInternalLabtoNormedOutput  (out, in);
    out += 3;
    in += 3;
  }
}
CMLAPI void CMLLchtoNormedOutput  (CMLOutput output, CMLInput Lch  , CMLSize count){
  CMLSize i;
  const float* in  = (float*)Lch;
  float* out = (float*)output;
  for(i=0; i<count; i++){
    CMLInternalLchtoNormedOutput  (out, in);
    out += 3;
    in += 3;
  }
}
CMLAPI void CMLLuvtoNormedOutput  (CMLOutput output, CMLInput Luv  , CMLSize count){
  CMLSize i;
  const float* in  = (float*)Luv;
  float* out = (float*)output;
  for(i=0; i<count; i++){
    CMLInternalLuvtoNormedOutput  (out, in);
    out += 3;
    in += 3;
  }
}
CMLAPI void CMLRGBtoNormedOutput  (CMLOutput output, CMLInput RGB  , CMLSize count){
  CMLSize i;
  const float* in  = (float*)RGB;
  float* out = (float*)output;
  for(i=0; i<count; i++){
    CMLInternalRGBtoNormedOutput  (out, in);
    out += 3;
    in += 3;
  }
}
CMLAPI void CMLYCbCrtoNormedOutput(CMLOutput output, CMLInput YCbCr, CMLSize count){
  CMLSize i;
  const float* in  = (float*)YCbCr;
  float* out = (float*)output;
  for(i=0; i<count; i++){
    CMLInternalYCbCrtoNormedOutput(out, in);
    out += 3;
    in += 3;
  }
}
CMLAPI void CMLHSVtoNormedOutput  (CMLOutput output, CMLInput HSV  , CMLSize count){
  CMLSize i;
  const float* in  = (float*)HSV;
  float* out = (float*)output;
  for(i=0; i<count; i++){
    CMLInternalHSVtoNormedOutput  (out, in);
    out += 3;
    in += 3;
  }
}
CMLAPI void CMLHSLtoNormedOutput  (CMLOutput output, CMLInput HSL  , CMLSize count){
  CMLSize i;
  const float* in  = (float*)HSL;
  float* out = (float*)output;
  for(i=0; i<count; i++){
    CMLInternalHSLtoNormedOutput  (out, in);
    out += 3;
    in += 3;
  }
}
CMLAPI void CMLCMYKtoNormedOutput (CMLOutput output, CMLInput CMYK , CMLSize count){
  CMLSize i;
  const float* in  = (float*)CMYK;
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


CMLAPI void CMLLchfromNormedCartesianInput  (CMLOutput Lch  , CMLInput input, CMLSize count){
  CMLSize i;
  const float* in  = (float*)input;
  float* out = (float*)Lch;
  for(i=0; i<count; i++){
    CMLInternalLchfromNormedCartesianInput  (out, in);
    out += 3;
    in += 3;
  }
}
CMLAPI void CMLHSVfromNormedCartesianInput  (CMLOutput HSV  , CMLInput input, CMLSize count){
  CMLSize i;
  const float* in  = (float*)input;
  float* out = (float*)HSV;
  for(i=0; i<count; i++){
    CMLInternalHSVfromNormedCartesianInput  (out, in);
    out += 3;
    in += 3;
  }
}
CMLAPI void CMLHSLfromNormedCartesianInput  (CMLOutput HSL  , CMLInput input, CMLSize count){
  CMLSize i;
  const float* in  = (float*)input;
  float* out = (float*)HSL;
  for(i=0; i<count; i++){
    CMLInternalHSLfromNormedCartesianInput  (out, in);
    out += 3;
    in += 3;
  }
}








// ////////////////////////////
// Normed Cartesian Output
// ////////////////////////////

CMLAPI void CMLLchtoNormedCartesianOutput  (CMLOutput output, CMLInput Lch  , CMLSize count){
  CMLSize i;
  const float* in  = (float*)Lch;
  float* out = (float*)output;
  for(i=0; i<count; i++){
    CMLInternalLchtoNormedCartesianOutput  (out, in);
    out += 3;
    in += 3;
  }
}
CMLAPI void CMLHSVtoNormedCartesianOutput  (CMLOutput output, CMLInput HSV  , CMLSize count){
  CMLSize i;
  const float* in  = (float*)HSV;
  float* out = (float*)output;
  for(i=0; i<count; i++){
    CMLInternalHSVtoNormedCartesianOutput  (out, in);
    out += 3;
    in += 3;
  }
}
CMLAPI void CMLHSLtoNormedCartesianOutput  (CMLOutput output, CMLInput HSL  , CMLSize count){
  CMLSize i;
  const float* in  = (float*)HSL;
  float* out = (float*)output;
  for(i=0; i<count; i++){
    CMLInternalHSLtoNormedCartesianOutput  (out, in);
    out += 3;
    in += 3;
  }
}



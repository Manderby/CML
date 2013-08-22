
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

#include "../CML.h"
#include "../StateMachine/CMLColorMachineState.h"


// In CML, all color computations are done in floating point precision. When
// importing or exporting color values on the other hand, very often 8-bit or
// 16-bit values are expected. Mapping integers to floats is rather straight-
// forward: floatvalue = intvalue / maxintvalue
// When looking for example at a 2-bit integer, the following mapping will be
// performed:
//            0                 1                 2                 3
//   |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|
//   0                      1/3                     2/3                      1
//
// When mapping from floats to integers on the other hand, the conversion is
// not straight forward. In the following diagram, three methods A, B and C are
// shown. Method A is the most common found method:
// A: intvalue = floor(floatvalue * maxintvalue)
// Unfortunately with this method, only the input value 1 will be mapped to
// maxintvalue. A value even slightly smaller than 1 (0.99999) will be mapped
// to maxintvalue - 1. Some implementations therefore perform the shifted
// mapping B:
// B: intvalue = floor(floatvalue * maxintvalue + 0.5)
// This mapping method maps values around 0 and 1 better to the corresponding
// integer value. To get a fully even distribution in the mapping, the method C
// is performed:
// C: intvalue = floor(floatvalue * (maxintvalue + 1))   if floatvalue < 1
//    intvalue = maxintvalue                             if floatvalue == 1
// This last method evenly distributes all values but takes a longer time to
// convert.
//
//   0    1/12  2/12  3/12  4/12  5/12  6/12  7/12  8/12  9/12 10/12 11/12   1
//   |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|
// A |            0          |           1           |          2            3
//   |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|
// B |     0     |           1           |          2            |     3     |
//   |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|
// C |        0        |        1        |        2        |        3        |
//   |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|


CMLHIDDEN CML_INLINE static void CMLInternal8bittofloat(float* out, CMLByte in, CMLByte offset, float range){
  *out = (float)(in - offset) / range;
}
CMLHIDDEN CML_INLINE static void CMLInternal16bittofloat(float* out, CMLWord in, CMLWord offset, float range){
  *out = (float)(in - offset) / range;
}


CMLHIDDEN CML_INLINE static void CMLInternal8bittofloat1(const CMLColorMachine* cm, float* CML_RESTRICT out, const CMLByte* CML_RESTRICT in){
  CMLInternal8bittofloat(&(out[0]), in[0], cm->inputoutput.offset8bit[0], cm->inputoutput.range8bit[0]);
}
CMLHIDDEN CML_INLINE static void CMLInternal8bittofloat3(const CMLColorMachine* cm, float* CML_RESTRICT out, const CMLByte* CML_RESTRICT in){
  CMLInternal8bittofloat(&(out[0]), in[0], cm->inputoutput.offset8bit[0], cm->inputoutput.range8bit[0]);
  CMLInternal8bittofloat(&(out[1]), in[1], cm->inputoutput.offset8bit[1], cm->inputoutput.range8bit[1]);
  CMLInternal8bittofloat(&(out[2]), in[2], cm->inputoutput.offset8bit[2], cm->inputoutput.range8bit[2]);
}
CMLHIDDEN CML_INLINE static void CMLInternal8bittofloat4(const CMLColorMachine* cm, float* CML_RESTRICT out, const CMLByte* CML_RESTRICT in){
  CMLInternal8bittofloat(&(out[0]), in[0], cm->inputoutput.offset8bit[0], cm->inputoutput.range8bit[0]);
  CMLInternal8bittofloat(&(out[1]), in[1], cm->inputoutput.offset8bit[1], cm->inputoutput.range8bit[1]);
  CMLInternal8bittofloat(&(out[2]), in[2], cm->inputoutput.offset8bit[2], cm->inputoutput.range8bit[2]);
  CMLInternal8bittofloat(&(out[3]), in[3], cm->inputoutput.offset8bit[3], cm->inputoutput.range8bit[3]);
}


CMLHIDDEN CML_INLINE static void CMLInternal16bittofloat1(const CMLColorMachine* cm, float* CML_RESTRICT out, const CMLWord* CML_RESTRICT in){
  CMLInternal16bittofloat(&(out[0]), in[0], cm->inputoutput.offset16bit[0], cm->inputoutput.range16bit[0]);
}
CMLHIDDEN CML_INLINE static void CMLInternal16bittofloat3(const CMLColorMachine* cm, float* CML_RESTRICT out, const CMLWord* CML_RESTRICT in){
  CMLInternal16bittofloat(&(out[0]), in[0], cm->inputoutput.offset16bit[0], cm->inputoutput.range16bit[0]);
  CMLInternal16bittofloat(&(out[1]), in[1], cm->inputoutput.offset16bit[1], cm->inputoutput.range16bit[1]);
  CMLInternal16bittofloat(&(out[2]), in[2], cm->inputoutput.offset16bit[2], cm->inputoutput.range16bit[2]);
}
CMLHIDDEN CML_INLINE static void CMLInternal16bittofloat4(const CMLColorMachine* cm, float* CML_RESTRICT out, const CMLWord* CML_RESTRICT in){
  CMLInternal16bittofloat(&(out[0]), in[0], cm->inputoutput.offset16bit[0], cm->inputoutput.range16bit[0]);
  CMLInternal16bittofloat(&(out[1]), in[1], cm->inputoutput.offset16bit[1], cm->inputoutput.range16bit[1]);
  CMLInternal16bittofloat(&(out[2]), in[2], cm->inputoutput.offset16bit[2], cm->inputoutput.range16bit[2]);
  CMLInternal16bittofloat(&(out[3]), in[3], cm->inputoutput.offset16bit[3], cm->inputoutput.range16bit[3]);
}



// //////////////////////////
// 8 bit Input Conversions
// //////////////////////////


CMLAPI void CMLGrayfrom8bitInput (const CMLColorMachine* cm, CMLOutput gray , CMLInput input, CMLSize count){
  CMLSize i;
  const CMLByte* in  = (CMLByte*)input;
  float* out = (float*)gray;
  float tmp[1];
  for(i=0; i<count; i++){
    CMLInternal8bittofloat1(cm, tmp, in);
    CMLInternalGrayfromNormedInput(out, tmp);
    out++;
    in++;
  }
}
CMLAPI void CMLXYZfrom8bitInput  (const CMLColorMachine* cm, CMLOutput XYZ  , CMLInput input, CMLSize count){
  CMLSize i;
  const CMLByte* in  = (CMLByte*)input;
  float* out = (float*)XYZ;
  float tmp[3];
  for(i=0; i<count; i++){
    CMLInternal8bittofloat3(cm, tmp, in);
    CMLInternalXYZfromNormedInput(out, tmp);
    out += 3;
    in += 3;
  }
}
CMLAPI void CMLYxyfrom8bitInput  (const CMLColorMachine* cm, CMLOutput Yxy  , CMLInput input, CMLSize count){
  CMLSize i;
  const CMLByte* in  = (CMLByte*)input;
  float* out = (float*)Yxy;
  float tmp[3];
  for(i=0; i<count; i++){
    CMLInternal8bittofloat3(cm, tmp, in);
    CMLInternalYxyfromNormedInput(out, tmp);
    out += 3;
    in += 3;
  }
}
CMLAPI void CMLYuvfrom8bitInput  (const CMLColorMachine* cm, CMLOutput Yuv  , CMLInput input, CMLSize count){
  CMLSize i;
  const CMLByte* in  = (CMLByte*)input;
  float* out = (float*)Yuv;
  float tmp[3];
  for(i=0; i<count; i++){
    CMLInternal8bittofloat3(cm, tmp, in);
    CMLInternalYuvfromNormedInput(out, tmp);
    out += 3;
    in += 3;
  }
}
CMLAPI void CMLYupvpfrom8bitInput  (const CMLColorMachine* cm, CMLOutput Yupvp  , CMLInput input, CMLSize count){
  CMLSize i;
  const CMLByte* in  = (CMLByte*)input;
  float* out = (float*)Yupvp;
  float tmp[3];
  for(i=0; i<count; i++){
    CMLInternal8bittofloat3(cm, tmp, in);
    CMLInternalYupvpfromNormedInput(out, tmp);
    out += 3;
    in += 3;
  }
}
CMLAPI void CMLLabfrom8bitInput  (const CMLColorMachine* cm, CMLOutput Lab  , CMLInput input, CMLSize count){
  CMLSize i;
  const CMLByte* in  = (CMLByte*)input;
  float* out = (float*)Lab;
  float tmp[3];
  for(i=0; i<count; i++){
    CMLInternal8bittofloat3(cm, tmp, in);
    CMLInternalLabfromNormedInput(out, tmp);
    out += 3;
    in += 3;
  }
}
CMLAPI void CMLLchfrom8bitInput  (const CMLColorMachine* cm, CMLOutput Lch  , CMLInput input, CMLSize count){
  CMLSize i;
  const CMLByte* in  = (CMLByte*)input;
  float* out = (float*)Lch;
  float tmp[3];
  for(i=0; i<count; i++){
    CMLInternal8bittofloat3(cm, tmp, in);
    CMLInternalLchfromNormedInput(out, tmp);
    out += 3;
    in += 3;
  }
}
CMLAPI void CMLLuvfrom8bitInput  (const CMLColorMachine* cm, CMLOutput Luv  , CMLInput input, CMLSize count){
  CMLSize i;
  const CMLByte* in  = (CMLByte*)input;
  float* out = (float*)Luv;
  float tmp[3];
  for(i=0; i<count; i++){
    CMLInternal8bittofloat3(cm, tmp, in);
    CMLInternalLuvfromNormedInput(out, tmp);
    out += 3;
    in += 3;
  }
}
CMLAPI void CMLRGBfrom8bitInput  (const CMLColorMachine* cm, CMLOutput RGB  , CMLInput input, CMLSize count){
  CMLSize i;
  const CMLByte* in  = (CMLByte*)input;
  float* out = (float*)RGB;
  float tmp[3];
  for(i=0; i<count; i++){
    CMLInternal8bittofloat3(cm, tmp, in);
    CMLInternalRGBfromNormedInput(out, tmp);
    out += 3;
    in += 3;
  }
}
CMLAPI void CMLYCbCrfrom8bitInput(const CMLColorMachine* cm, CMLOutput YCbCr, CMLInput input, CMLSize count){
  CMLSize i;
  const CMLByte* in  = (CMLByte*)input;
  float* out = (float*)YCbCr;
  float tmp[3];
  for(i=0; i<count; i++){
    CMLInternal8bittofloat3(cm, tmp, in);
    CMLInternalYCbCrfromNormedInput(out, tmp);
    out += 3;
    in += 3;
  }
}
CMLAPI void CMLHSVfrom8bitInput  (const CMLColorMachine* cm, CMLOutput HSV  , CMLInput input, CMLSize count){
  CMLSize i;
  const CMLByte* in  = (CMLByte*)input;
  float* out = (float*)HSV;
  float tmp[3];
  for(i=0; i<count; i++){
    CMLInternal8bittofloat3(cm, tmp, in);
    CMLInternalHSVfromNormedInput(out, tmp);
    out += 3;
    in += 3;
  }
}
CMLAPI void CMLHSLfrom8bitInput  (const CMLColorMachine* cm, CMLOutput HSL  , CMLInput input, CMLSize count){
  CMLSize i;
  const CMLByte* in  = (CMLByte*)input;
  float* out = (float*)HSL;
  float tmp[3];
  for(i=0; i<count; i++){
    CMLInternal8bittofloat3(cm, tmp, in);
    CMLInternalHSLfromNormedInput(out, tmp);
    out += 3;
    in += 3;
  }
}
CMLAPI void CMLCMYKfrom8bitInput (const CMLColorMachine* cm, CMLOutput CMYK , CMLInput input, CMLSize count){
  CMLSize i;
  const CMLByte* in  = (CMLByte*)input;
  float* out = (float*)CMYK;
  float tmp[4];
  for(i=0; i<count; i++){
    CMLInternal8bittofloat4(cm, tmp, in);
    CMLInternalCMYKfromNormedInput(out, tmp);
    out += 4;
    in += 4;
  }
}






// //////////////////////////
// 16 bit Input Conversions
// //////////////////////////


CMLAPI void CMLGrayfrom16bitInput (const CMLColorMachine* cm, CMLOutput gray , CMLInput input, CMLSize count){
  CMLSize i;
  const CMLWord* in  = (CMLWord*)input;
  float* out = (float*)gray;
  float tmp[1];
  for(i=0; i<count; i++){
    CMLInternal16bittofloat1(cm, tmp, in);
    CMLInternalGrayfromNormedInput(out, tmp);
    out++;
    in++;
  }
}
CMLAPI void CMLXYZfrom16bitInput  (const CMLColorMachine* cm, CMLOutput XYZ  , CMLInput input, CMLSize count){
  CMLSize i;
  const CMLWord* in  = (CMLWord*)input;
  float* out = (float*)XYZ;
  float tmp[3];
  for(i=0; i<count; i++){
    CMLInternal16bittofloat3(cm, tmp, in);
    CMLInternalXYZfromNormedInput(out, tmp);
    out += 3;
    in += 3;
  }
}
CMLAPI void CMLYxyfrom16bitInput  (const CMLColorMachine* cm, CMLOutput Yxy  , CMLInput input, CMLSize count){
  CMLSize i;
  const CMLWord* in  = (CMLWord*)input;
  float* out = (float*)Yxy;
  float tmp[3];
  for(i=0; i<count; i++){
    CMLInternal16bittofloat3(cm, tmp, in);
    CMLInternalYxyfromNormedInput(out, tmp);
    out += 3;
    in += 3;
  }
}
CMLAPI void CMLYuvfrom16bitInput  (const CMLColorMachine* cm, CMLOutput Yuv  , CMLInput input, CMLSize count){
  CMLSize i;
  const CMLWord* in  = (CMLWord*)input;
  float* out = (float*)Yuv;
  float tmp[3];
  for(i=0; i<count; i++){
    CMLInternal16bittofloat3(cm, tmp, in);
    CMLInternalYuvfromNormedInput(out, tmp);
    out += 3;
    in += 3;
  }
}
CMLAPI void CMLYupvpfrom16bitInput  (const CMLColorMachine* cm, CMLOutput Yupvp  , CMLInput input, CMLSize count){
  CMLSize i;
  const CMLWord* in  = (CMLWord*)input;
  float* out = (float*)Yupvp;
  float tmp[3];
  for(i=0; i<count; i++){
    CMLInternal16bittofloat3(cm, tmp, in);
    CMLInternalYupvpfromNormedInput(out, tmp);
    out += 3;
    in += 3;
  }
}
CMLAPI void CMLLabfrom16bitInput  (const CMLColorMachine* cm, CMLOutput Lab  , CMLInput input, CMLSize count){
  CMLSize i;
  const CMLWord* in  = (CMLWord*)input;
  float* out = (float*)Lab;
  float tmp[3];
  for(i=0; i<count; i++){
    CMLInternal16bittofloat3(cm, tmp, in);
    CMLInternalLabfromNormedInput(out, tmp);
    out += 3;
    in += 3;
  }
}
CMLAPI void CMLLchfrom16bitInput  (const CMLColorMachine* cm, CMLOutput Lch  , CMLInput input, CMLSize count){
  CMLSize i;
  const CMLWord* in  = (CMLWord*)input;
  float* out = (float*)Lch;
  float tmp[3];
  for(i=0; i<count; i++){
    CMLInternal16bittofloat3(cm, tmp, in);
    CMLInternalLchfromNormedInput(out, tmp);
    out += 3;
    in += 3;
  }
}
CMLAPI void CMLLuvfrom16bitInput  (const CMLColorMachine* cm, CMLOutput Luv  , CMLInput input, CMLSize count){
  CMLSize i;
  const CMLWord* in  = (CMLWord*)input;
  float* out = (float*)Luv;
  float tmp[3];
  for(i=0; i<count; i++){
    CMLInternal16bittofloat3(cm, tmp, in);
    CMLInternalLuvfromNormedInput(out, tmp);
    out += 3;
    in += 3;
  }
}
CMLAPI void CMLRGBfrom16bitInput  (const CMLColorMachine* cm, CMLOutput RGB  , CMLInput input, CMLSize count){
  CMLSize i;
  const CMLWord* in  = (CMLWord*)input;
  float* out = (float*)RGB;
  float tmp[3];
  for(i=0; i<count; i++){
    CMLInternal16bittofloat3(cm, tmp, in);
    CMLInternalRGBfromNormedInput(out, tmp);
    out += 3;
    in += 3;
  }
}
CMLAPI void CMLYCbCrfrom16bitInput(const CMLColorMachine* cm, CMLOutput YCbCr, CMLInput input, CMLSize count){
  CMLSize i;
  const CMLWord* in  = (CMLWord*)input;
  float* out = (float*)YCbCr;
  float tmp[3];
  for(i=0; i<count; i++){
    CMLInternal16bittofloat3(cm, tmp, in);
    CMLInternalYCbCrfromNormedInput(out, tmp);
    out += 3;
    in += 3;
  }
}
CMLAPI void CMLHSVfrom16bitInput  (const CMLColorMachine* cm, CMLOutput HSV  , CMLInput input, CMLSize count){
  CMLSize i;
  const CMLWord* in  = (CMLWord*)input;
  float* out = (float*)HSV;
  float tmp[3];
  for(i=0; i<count; i++){
    CMLInternal16bittofloat3(cm, tmp, in);
    CMLInternalHSVfromNormedInput(out, tmp);
    out += 3;
    in += 3;
  }
}
CMLAPI void CMLHSLfrom16bitInput  (const CMLColorMachine* cm, CMLOutput HSL  , CMLInput input, CMLSize count){
  CMLSize i;
  const CMLWord* in  = (CMLWord*)input;
  float* out = (float*)HSL;
  float tmp[3];
  for(i=0; i<count; i++){
    CMLInternal16bittofloat3(cm, tmp, in);
    CMLInternalHSLfromNormedInput(out, tmp);
    out += 3;
    in += 3;
  }
}
CMLAPI void CMLCMYKfrom16bitInput (const CMLColorMachine* cm, CMLOutput CMYK , CMLInput input, CMLSize count){
  CMLSize i;
  const CMLWord* in  = (CMLWord*)input;
  float* out = (float*)CMYK;
  float tmp[4];
  for(i=0; i<count; i++){
    CMLInternal16bittofloat4(cm, tmp, in);
    CMLInternalCMYKfromNormedInput(out, tmp);
    out += 4;
    in += 4;
  }
}







CMLHIDDEN CML_INLINE static void CMLInternalfloatto8bitFloor(CMLByte* out, float in, CMLByte offset, float range){
  *out = offset + (CMLByte)(in*range);
}
CMLHIDDEN CML_INLINE static void CMLInternalfloatto16bitFloor(CMLWord* out, float in, CMLWord offset, float range){
  *out = offset + (CMLByte)(in*range);
}
CMLHIDDEN CML_INLINE static void CMLInternalfloatto8bitBox(CMLByte* out, float in, CMLByte offset, float range){
  *out = offset + (CMLByte)(in*range + .5f);
}
CMLHIDDEN CML_INLINE static void CMLInternalfloatto16bitBox(CMLWord* out, float in, CMLWord offset, float range){
  *out = offset + (CMLByte)(in*range + .5f);
}
CMLHIDDEN CML_INLINE static void CMLInternalfloatto8bitInterval(CMLByte* out, float in, CMLByte offset, float range){
  *out = offset + ((in == 1.f) ? (CMLByte)range : (CMLByte)(in*(range + 1.f)));
}
CMLHIDDEN CML_INLINE static void CMLInternalfloatto16bitInterval(CMLWord* out, float in, CMLWord offset, float range){
  *out = offset + ((in == 1.f) ? (CMLWord)range : (CMLWord)(in*(range + 1.f)));
}

CMLHIDDEN void CMLInternalfloat1to8bitFloor(const CMLColorMachine* cm, CMLByte* CML_RESTRICT out, const float* CML_RESTRICT in){
  CMLInternalfloatto8bitFloor(&(out[0]), in[0], cm->inputoutput.offset8bit[0], cm->inputoutput.range8bit[0]);
}
CMLHIDDEN void CMLInternalfloat3to8bitFloor(const CMLColorMachine* cm, CMLByte* CML_RESTRICT out, const float* CML_RESTRICT in){
  CMLInternalfloatto8bitFloor(&(out[0]), in[0], cm->inputoutput.offset8bit[0], cm->inputoutput.range8bit[0]);
  CMLInternalfloatto8bitFloor(&(out[1]), in[1], cm->inputoutput.offset8bit[1], cm->inputoutput.range8bit[1]);
  CMLInternalfloatto8bitFloor(&(out[2]), in[2], cm->inputoutput.offset8bit[2], cm->inputoutput.range8bit[2]);
}
CMLHIDDEN void CMLInternalfloat4to8bitFloor(const CMLColorMachine* cm, CMLByte* CML_RESTRICT out, const float* CML_RESTRICT in){
  CMLInternalfloatto8bitFloor(&(out[0]), in[0], cm->inputoutput.offset8bit[0], cm->inputoutput.range8bit[0]);
  CMLInternalfloatto8bitFloor(&(out[1]), in[1], cm->inputoutput.offset8bit[1], cm->inputoutput.range8bit[1]);
  CMLInternalfloatto8bitFloor(&(out[2]), in[2], cm->inputoutput.offset8bit[2], cm->inputoutput.range8bit[2]);
  CMLInternalfloatto8bitFloor(&(out[3]), in[3], cm->inputoutput.offset8bit[3], cm->inputoutput.range8bit[3]);
}

CMLHIDDEN void CMLInternalfloat1to8bitBox(const CMLColorMachine* cm, CMLByte* CML_RESTRICT out, const float* CML_RESTRICT in){
  CMLInternalfloatto8bitBox(&(out[0]), in[0], cm->inputoutput.offset8bit[0], cm->inputoutput.range8bit[0]);
}
CMLHIDDEN void CMLInternalfloat3to8bitBox(const CMLColorMachine* cm, CMLByte* CML_RESTRICT out, const float* CML_RESTRICT in){
  CMLInternalfloatto8bitBox(&(out[0]), in[0], cm->inputoutput.offset8bit[0], cm->inputoutput.range8bit[0]);
  CMLInternalfloatto8bitBox(&(out[1]), in[1], cm->inputoutput.offset8bit[1], cm->inputoutput.range8bit[1]);
  CMLInternalfloatto8bitBox(&(out[2]), in[2], cm->inputoutput.offset8bit[2], cm->inputoutput.range8bit[2]);
}
CMLHIDDEN void CMLInternalfloat4to8bitBox(const CMLColorMachine* cm, CMLByte* CML_RESTRICT out, const float* CML_RESTRICT in){
  CMLInternalfloatto8bitBox(&(out[0]), in[0], cm->inputoutput.offset8bit[0], cm->inputoutput.range8bit[0]);
  CMLInternalfloatto8bitBox(&(out[1]), in[1], cm->inputoutput.offset8bit[1], cm->inputoutput.range8bit[1]);
  CMLInternalfloatto8bitBox(&(out[2]), in[2], cm->inputoutput.offset8bit[2], cm->inputoutput.range8bit[2]);
  CMLInternalfloatto8bitBox(&(out[3]), in[3], cm->inputoutput.offset8bit[3], cm->inputoutput.range8bit[3]);
}

CMLHIDDEN void CMLInternalfloat1to8bitInterval(const CMLColorMachine* cm, CMLByte* CML_RESTRICT out, const float* CML_RESTRICT in){
  CMLInternalfloatto8bitInterval(&(out[0]), in[0], cm->inputoutput.offset8bit[0], cm->inputoutput.range8bit[0]);
}
CMLHIDDEN void CMLInternalfloat3to8bitInterval(const CMLColorMachine* cm, CMLByte* CML_RESTRICT out, const float* CML_RESTRICT in){
  CMLInternalfloatto8bitInterval(&(out[0]), in[0], cm->inputoutput.offset8bit[0], cm->inputoutput.range8bit[0]);
  CMLInternalfloatto8bitInterval(&(out[1]), in[1], cm->inputoutput.offset8bit[1], cm->inputoutput.range8bit[1]);
  CMLInternalfloatto8bitInterval(&(out[2]), in[2], cm->inputoutput.offset8bit[2], cm->inputoutput.range8bit[2]);
}
CMLHIDDEN void CMLInternalfloat4to8bitInterval(const CMLColorMachine* cm, CMLByte* CML_RESTRICT out, const float* CML_RESTRICT in){
  CMLInternalfloatto8bitInterval(&(out[0]), in[0], cm->inputoutput.offset8bit[0], cm->inputoutput.range8bit[0]);
  CMLInternalfloatto8bitInterval(&(out[1]), in[1], cm->inputoutput.offset8bit[1], cm->inputoutput.range8bit[1]);
  CMLInternalfloatto8bitInterval(&(out[2]), in[2], cm->inputoutput.offset8bit[2], cm->inputoutput.range8bit[2]);
  CMLInternalfloatto8bitInterval(&(out[3]), in[3], cm->inputoutput.offset8bit[3], cm->inputoutput.range8bit[3]);
}


CMLHIDDEN void CMLInternalfloat1to16bitFloor(const CMLColorMachine* cm, CMLWord* CML_RESTRICT out, const float* CML_RESTRICT in){
  CMLInternalfloatto16bitFloor(&(out[0]), in[0], cm->inputoutput.offset16bit[0], cm->inputoutput.range16bit[0]);
}
CMLHIDDEN void CMLInternalfloat3to16bitFloor(const CMLColorMachine* cm, CMLWord* CML_RESTRICT out, const float* CML_RESTRICT in){
  CMLInternalfloatto16bitFloor(&(out[0]), in[0], cm->inputoutput.offset16bit[0], cm->inputoutput.range16bit[0]);
  CMLInternalfloatto16bitFloor(&(out[1]), in[1], cm->inputoutput.offset16bit[1], cm->inputoutput.range16bit[1]);
  CMLInternalfloatto16bitFloor(&(out[2]), in[2], cm->inputoutput.offset16bit[2], cm->inputoutput.range16bit[2]);
}
CMLHIDDEN void CMLInternalfloat4to16bitFloor(const CMLColorMachine* cm, CMLWord* CML_RESTRICT out, const float* CML_RESTRICT in){
  CMLInternalfloatto16bitFloor(&(out[0]), in[0], cm->inputoutput.offset16bit[0], cm->inputoutput.range16bit[0]);
  CMLInternalfloatto16bitFloor(&(out[1]), in[1], cm->inputoutput.offset16bit[1], cm->inputoutput.range16bit[1]);
  CMLInternalfloatto16bitFloor(&(out[2]), in[2], cm->inputoutput.offset16bit[2], cm->inputoutput.range16bit[2]);
  CMLInternalfloatto16bitFloor(&(out[3]), in[3], cm->inputoutput.offset16bit[3], cm->inputoutput.range16bit[3]);
}

CMLHIDDEN void CMLInternalfloat1to16bitBox(const CMLColorMachine* cm, CMLWord* CML_RESTRICT out, const float* CML_RESTRICT in){
  CMLInternalfloatto16bitBox(&(out[0]), in[0], cm->inputoutput.offset16bit[0], cm->inputoutput.range16bit[0]);
}
CMLHIDDEN void CMLInternalfloat3to16bitBox(const CMLColorMachine* cm, CMLWord* CML_RESTRICT out, const float* CML_RESTRICT in){
  CMLInternalfloatto16bitBox(&(out[0]), in[0], cm->inputoutput.offset16bit[0], cm->inputoutput.range16bit[0]);
  CMLInternalfloatto16bitBox(&(out[1]), in[1], cm->inputoutput.offset16bit[1], cm->inputoutput.range16bit[1]);
  CMLInternalfloatto16bitBox(&(out[2]), in[2], cm->inputoutput.offset16bit[2], cm->inputoutput.range16bit[2]);
}
CMLHIDDEN void CMLInternalfloat4to16bitBox(const CMLColorMachine* cm, CMLWord* CML_RESTRICT out, const float* CML_RESTRICT in){
  CMLInternalfloatto16bitBox(&(out[0]), in[0], cm->inputoutput.offset16bit[0], cm->inputoutput.range16bit[0]);
  CMLInternalfloatto16bitBox(&(out[1]), in[1], cm->inputoutput.offset16bit[1], cm->inputoutput.range16bit[1]);
  CMLInternalfloatto16bitBox(&(out[2]), in[2], cm->inputoutput.offset16bit[2], cm->inputoutput.range16bit[2]);
  CMLInternalfloatto16bitBox(&(out[3]), in[3], cm->inputoutput.offset16bit[3], cm->inputoutput.range16bit[3]);
}

CMLHIDDEN void CMLInternalfloat1to16bitInterval(const CMLColorMachine* cm, CMLWord* CML_RESTRICT out, const float* CML_RESTRICT in){
  CMLInternalfloatto16bitInterval(&(out[0]), in[0], cm->inputoutput.offset16bit[0], cm->inputoutput.range16bit[0]);
}
CMLHIDDEN void CMLInternalfloat3to16bitInterval(const CMLColorMachine* cm, CMLWord* CML_RESTRICT out, const float* CML_RESTRICT in){
  CMLInternalfloatto16bitInterval(&(out[0]), in[0], cm->inputoutput.offset16bit[0], cm->inputoutput.range16bit[0]);
  CMLInternalfloatto16bitInterval(&(out[1]), in[1], cm->inputoutput.offset16bit[1], cm->inputoutput.range16bit[1]);
  CMLInternalfloatto16bitInterval(&(out[2]), in[2], cm->inputoutput.offset16bit[2], cm->inputoutput.range16bit[2]);
}
CMLHIDDEN void CMLInternalfloat4to16bitInterval(const CMLColorMachine* cm, CMLWord* CML_RESTRICT out, const float* CML_RESTRICT in){
  CMLInternalfloatto16bitInterval(&(out[0]), in[0], cm->inputoutput.offset16bit[0], cm->inputoutput.range16bit[0]);
  CMLInternalfloatto16bitInterval(&(out[1]), in[1], cm->inputoutput.offset16bit[1], cm->inputoutput.range16bit[1]);
  CMLInternalfloatto16bitInterval(&(out[2]), in[2], cm->inputoutput.offset16bit[2], cm->inputoutput.range16bit[2]);
  CMLInternalfloatto16bitInterval(&(out[3]), in[3], cm->inputoutput.offset16bit[3], cm->inputoutput.range16bit[3]);
}




// //////////////////////////
// 8 bit Output Conversions
// //////////////////////////

CMLAPI void CMLGrayto8bitOutput (const CMLColorMachine* cm, CMLOutput output, CMLInput gray , CMLSize count){
  CMLSize i;
  const float* in  = (float*)gray;
  CMLByte* out = (CMLByte*)output;
  float tmp[1];
  for(i=0; i<count; i++){
    CMLInternalGraytoNormedOutput(tmp, in);
    (*cm->float1to8bit)(cm, out, tmp);
    in++;
    out++;
  }
}
CMLAPI void CMLXYZto8bitOutput  (const CMLColorMachine* cm, CMLOutput output, CMLInput XYZ  , CMLSize count){
  CMLSize i;
  const float* in  = (float*)XYZ;
  CMLByte* out = (CMLByte*)output;
  float tmp[3];
  for(i=0; i<count; i++){
    CMLInternalXYZtoNormedOutput(tmp, in);
    (*cm->float3to8bit)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}
CMLAPI void CMLYxyto8bitOutput  (const CMLColorMachine* cm, CMLOutput output, CMLInput Yxy  , CMLSize count){
  CMLSize i;
  const float* in  = (float*)Yxy;
  CMLByte* out = (CMLByte*)output;
  float tmp[3];
  for(i=0; i<count; i++){
    CMLInternalYxytoNormedOutput(tmp, in);
    (*cm->float3to8bit)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}
CMLAPI void CMLYuvto8bitOutput  (const CMLColorMachine* cm, CMLOutput output, CMLInput Yuv  , CMLSize count){
  CMLSize i;
  const float* in  = (float*)Yuv;
  CMLByte* out = (CMLByte*)output;
  float tmp[3];
  for(i=0; i<count; i++){
    CMLInternalYuvtoNormedOutput(tmp, in);
    (*cm->float3to8bit)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}
CMLAPI void CMLYupvpto8bitOutput  (const CMLColorMachine* cm, CMLOutput output, CMLInput Yupvp  , CMLSize count){
  CMLSize i;
  const float* in  = (float*)Yupvp;
  CMLByte* out = (CMLByte*)output;
  float tmp[3];
  for(i=0; i<count; i++){
    CMLInternalYupvptoNormedOutput(tmp, in);
    (*cm->float3to8bit)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}
CMLAPI void CMLLabto8bitOutput  (const CMLColorMachine* cm, CMLOutput output, CMLInput Lab  , CMLSize count){
  CMLSize i;
  const float* in  = (float*)Lab;
  CMLByte* out = (CMLByte*)output;
  float tmp[3];
  for(i=0; i<count; i++){
    CMLInternalLabtoNormedOutput(tmp, in);
    (*cm->float3to8bit)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}
CMLAPI void CMLLchto8bitOutput  (const CMLColorMachine* cm, CMLOutput output, CMLInput Lch  , CMLSize count){
  CMLSize i;
  const float* in  = (float*)Lch;
  CMLByte* out = (CMLByte*)output;
  float tmp[3];
  for(i=0; i<count; i++){
    CMLInternalLchtoNormedOutput(tmp, in);
    (*cm->float3to8bit)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}
CMLAPI void CMLLuvto8bitOutput  (const CMLColorMachine* cm, CMLOutput output, CMLInput Luv  , CMLSize count){
  CMLSize i;
  const float* in  = (float*)Luv;
  CMLByte* out = (CMLByte*)output;
  float tmp[3];
  for(i=0; i<count; i++){
    CMLInternalLuvtoNormedOutput(tmp, in);
    (*cm->float3to8bit)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}
CMLAPI void CMLRGBto8bitOutput  (const CMLColorMachine* cm, CMLOutput output, CMLInput RGB  , CMLSize count){
  CMLSize i;
  const float* in  = (float*)RGB;
  CMLByte* out = (CMLByte*)output;
  float tmp[3];
  for(i=0; i<count; i++){
    CMLInternalRGBtoNormedOutput(tmp, in);
    (*cm->float3to8bit)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}
CMLAPI void CMLYCbCrto8bitOutput(const CMLColorMachine* cm, CMLOutput output, CMLInput YCbCr, CMLSize count){
  CMLSize i;
  const float* in  = (float*)YCbCr;
  CMLByte* out = (CMLByte*)output;
  float tmp[3];
  for(i=0; i<count; i++){
    CMLInternalYCbCrtoNormedOutput(tmp, in);
    (*cm->float3to8bit)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}
CMLAPI void CMLHSVto8bitOutput  (const CMLColorMachine* cm, CMLOutput output, CMLInput HSV  , CMLSize count){
  CMLSize i;
  const float* in  = (float*)HSV;
  CMLByte* out = (CMLByte*)output;
  float tmp[3];
  for(i=0; i<count; i++){
    CMLInternalHSVtoNormedOutput(tmp, in);
    (*cm->float3to8bit)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}
CMLAPI void CMLHSLto8bitOutput  (const CMLColorMachine* cm, CMLOutput output, CMLInput HSL  , CMLSize count){
  CMLSize i;
  const float* in  = (float*)HSL;
  CMLByte* out = (CMLByte*)output;
  float tmp[3];
  for(i=0; i<count; i++){
    CMLInternalHSLtoNormedOutput(tmp, in);
    (*cm->float3to8bit)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}
CMLAPI void CMLCMYKto8bitOutput (const CMLColorMachine* cm, CMLOutput output, CMLInput CMYK , CMLSize count){
  CMLSize i;
  const float* in  = (float*)CMYK;
  CMLByte* out = (CMLByte*)output;
  float tmp[4];
  for(i=0; i<count; i++){
    CMLInternalCMYKtoNormedOutput(tmp, in);
    (*cm->float4to8bit)(cm, out, tmp);
    in += 4;
    out += 4;
  }
}





// //////////////////////////
// 16 bit Output Conversions
// //////////////////////////


CMLAPI void CMLGrayto16bitOutput (const CMLColorMachine* cm, CMLOutput output, CMLInput gray , CMLSize count){
  CMLSize i;
  const float* in  = (float*)gray;
  CMLWord* out = (CMLWord*)output;
  float tmp[1];
  for(i=0; i<count; i++){
    CMLInternalGraytoNormedOutput(tmp, in);
    (*cm->float1to16bit)(cm, out, tmp);
    in++;
    out++;
  }
}
CMLAPI void CMLXYZto16bitOutput  (const CMLColorMachine* cm, CMLOutput output, CMLInput XYZ  , CMLSize count){
  CMLSize i;
  const float* in  = (float*)XYZ;
  CMLWord* out = (CMLWord*)output;
  float tmp[3];
  for(i=0; i<count; i++){
    CMLInternalXYZtoNormedOutput(tmp, in);
    (*cm->float3to16bit)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}
CMLAPI void CMLYxyto16bitOutput  (const CMLColorMachine* cm, CMLOutput output, CMLInput Yxy  , CMLSize count){
  CMLSize i;
  const float* in  = (float*)Yxy;
  CMLWord* out = (CMLWord*)output;
  float tmp[3];
  for(i=0; i<count; i++){
    CMLInternalYxytoNormedOutput(tmp, in);
    (*cm->float3to16bit)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}
CMLAPI void CMLYuvto16bitOutput  (const CMLColorMachine* cm, CMLOutput output, CMLInput Yuv  , CMLSize count){
  CMLSize i;
  const float* in  = (float*)Yuv;
  CMLWord* out = (CMLWord*)output;
  float tmp[3];
  for(i=0; i<count; i++){
    CMLInternalYuvtoNormedOutput(tmp, in);
    (*cm->float3to16bit)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}
CMLAPI void CMLYupvpto16bitOutput  (const CMLColorMachine* cm, CMLOutput output, CMLInput Yupvp  , CMLSize count){
  CMLSize i;
  const float* in  = (float*)Yupvp;
  CMLWord* out = (CMLWord*)output;
  float tmp[3];
  for(i=0; i<count; i++){
    CMLInternalYupvptoNormedOutput(tmp, in);
    (*cm->float3to16bit)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}
CMLAPI void CMLLabto16bitOutput  (const CMLColorMachine* cm, CMLOutput output, CMLInput Lab  , CMLSize count){
  CMLSize i;
  const float* in  = (float*)Lab;
  CMLWord* out = (CMLWord*)output;
  float tmp[3];
  for(i=0; i<count; i++){
    CMLInternalLabtoNormedOutput(tmp, in);
    (*cm->float3to16bit)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}
CMLAPI void CMLLchto16bitOutput  (const CMLColorMachine* cm, CMLOutput output, CMLInput Lch  , CMLSize count){
  CMLSize i;
  const float* in  = (float*)Lch;
  CMLWord* out = (CMLWord*)output;
  float tmp[3];
  for(i=0; i<count; i++){
    CMLInternalLchtoNormedOutput(tmp, in);
    (*cm->float3to16bit)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}
CMLAPI void CMLLuvto16bitOutput  (const CMLColorMachine* cm, CMLOutput output, CMLInput Luv  , CMLSize count){
  CMLSize i;
  const float* in  = (float*)Luv;
  CMLWord* out = (CMLWord*)output;
  float tmp[3];
  for(i=0; i<count; i++){
    CMLInternalLuvtoNormedOutput(tmp, in);
    (*cm->float3to16bit)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}
CMLAPI void CMLRGBto16bitOutput  (const CMLColorMachine* cm, CMLOutput output, CMLInput RGB  , CMLSize count){
  CMLSize i;
  const float* in  = (float*)RGB;
  CMLWord* out = (CMLWord*)output;
  float tmp[3];
  for(i=0; i<count; i++){
    CMLInternalRGBtoNormedOutput(tmp, in);
    (*cm->float3to16bit)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}
CMLAPI void CMLYCbCrto16bitOutput(const CMLColorMachine* cm, CMLOutput output, CMLInput YCbCr, CMLSize count){
  CMLSize i;
  const float* in  = (float*)YCbCr;
  CMLWord* out = (CMLWord*)output;
  float tmp[3];
  for(i=0; i<count; i++){
    CMLInternalYCbCrtoNormedOutput(tmp, in);
    (*cm->float3to16bit)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}
CMLAPI void CMLHSVto16bitOutput  (const CMLColorMachine* cm, CMLOutput output, CMLInput HSV  , CMLSize count){
  CMLSize i;
  const float* in  = (float*)HSV;
  CMLWord* out = (CMLWord*)output;
  float tmp[3];
  for(i=0; i<count; i++){
    CMLInternalHSVtoNormedOutput(tmp, in);
    (*cm->float3to16bit)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}
CMLAPI void CMLHSLto16bitOutput  (const CMLColorMachine* cm, CMLOutput output, CMLInput HSL  , CMLSize count){
  CMLSize i;
  const float* in  = (float*)HSL;
  CMLWord* out = (CMLWord*)output;
  float tmp[3];
  for(i=0; i<count; i++){
    CMLInternalHSLtoNormedOutput(tmp, in);
    (*cm->float3to16bit)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}
CMLAPI void CMLCMYKto16bitOutput (const CMLColorMachine* cm, CMLOutput output, CMLInput CMYK , CMLSize count){
  CMLSize i;
  const float* in  = (float*)CMYK;
  CMLWord* out = (CMLWord*)output;
  float tmp[4];
  for(i=0; i<count; i++){
    CMLInternalCMYKtoNormedOutput(tmp, in);
    (*cm->float4to16bit)(cm, out, tmp);
    in += 4;
    out += 4;
  }
}



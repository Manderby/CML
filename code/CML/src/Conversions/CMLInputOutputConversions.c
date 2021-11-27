
#include "../CML.h"
#include "../Internal/CMLColorMachineState.h"


// In CML, all color computations are done in floating point precision. When
// importing or exporting color values on the other hand, very often 8-bit or
// 16-bit integer values are expected. Mapping integers to floats is rather
// straight-forward: floatvalue = intvalue / maxintvalue
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


CML_HIDEF void cml_Data8ToFloat(float* out, CMLByte in, CMLByte offset, float range){
  *out = (float)(in - offset) / range;
}
CML_HIDEF void cml_Data16ToFloat(float* out, CMLWord in, CMLWord offset, float range){
  *out = (float)(in - offset) / range;
}


CML_HIDEF void cml_Data8ToFloat1(const CMLColorMachine* cm, float* CML_RESTRICT out, const CMLByte* CML_RESTRICT in){
  cml_Data8ToFloat(&(out[0]), in[0], cm->inputoutput.offset8Bit[0], cm->inputoutput.range8Bit[0]);
}
CML_HIDEF void cml_Data8ToFloat3(const CMLColorMachine* cm, float* CML_RESTRICT out, const CMLByte* CML_RESTRICT in){
  cml_Data8ToFloat(&(out[0]), in[0], cm->inputoutput.offset8Bit[0], cm->inputoutput.range8Bit[0]);
  cml_Data8ToFloat(&(out[1]), in[1], cm->inputoutput.offset8Bit[1], cm->inputoutput.range8Bit[1]);
  cml_Data8ToFloat(&(out[2]), in[2], cm->inputoutput.offset8Bit[2], cm->inputoutput.range8Bit[2]);
}
CML_HIDEF void cml_Data8ToFloat4(const CMLColorMachine* cm, float* CML_RESTRICT out, const CMLByte* CML_RESTRICT in){
  cml_Data8ToFloat(&(out[0]), in[0], cm->inputoutput.offset8Bit[0], cm->inputoutput.range8Bit[0]);
  cml_Data8ToFloat(&(out[1]), in[1], cm->inputoutput.offset8Bit[1], cm->inputoutput.range8Bit[1]);
  cml_Data8ToFloat(&(out[2]), in[2], cm->inputoutput.offset8Bit[2], cm->inputoutput.range8Bit[2]);
  cml_Data8ToFloat(&(out[3]), in[3], cm->inputoutput.offset8Bit[3], cm->inputoutput.range8Bit[3]);
}


CML_HIDEF void cml_Data16ToFloat1(const CMLColorMachine* cm, float* CML_RESTRICT out, const CMLWord* CML_RESTRICT in){
  cml_Data16ToFloat(&(out[0]), in[0], cm->inputoutput.offset16Bit[0], cm->inputoutput.range16Bit[0]);
}
CML_HIDEF void cml_Data16ToFloat3(const CMLColorMachine* cm, float* CML_RESTRICT out, const CMLWord* CML_RESTRICT in){
  cml_Data16ToFloat(&(out[0]), in[0], cm->inputoutput.offset16Bit[0], cm->inputoutput.range16Bit[0]);
  cml_Data16ToFloat(&(out[1]), in[1], cm->inputoutput.offset16Bit[1], cm->inputoutput.range16Bit[1]);
  cml_Data16ToFloat(&(out[2]), in[2], cm->inputoutput.offset16Bit[2], cm->inputoutput.range16Bit[2]);
}
CML_HIDEF void cml_Data16ToFloat4(const CMLColorMachine* cm, float* CML_RESTRICT out, const CMLWord* CML_RESTRICT in){
  cml_Data16ToFloat(&(out[0]), in[0], cm->inputoutput.offset16Bit[0], cm->inputoutput.range16Bit[0]);
  cml_Data16ToFloat(&(out[1]), in[1], cm->inputoutput.offset16Bit[1], cm->inputoutput.range16Bit[1]);
  cml_Data16ToFloat(&(out[2]), in[2], cm->inputoutput.offset16Bit[2], cm->inputoutput.range16Bit[2]);
  cml_Data16ToFloat(&(out[3]), in[3], cm->inputoutput.offset16Bit[3], cm->inputoutput.range16Bit[3]);
}



// //////////////////////////
// 8 bit Input Conversions
// //////////////////////////

CML_DEF void cmlData8ToGray(const CMLColorMachine* cm, CMLOutput gray, CMLInput input, size_t count){
  const CMLByte* in  = (CMLByte*)input;
  float* out = (float*)gray;
  for(size_t i = 0; i < count; i++){
    float tmp[1];
    cml_Data8ToFloat1(cm, tmp, in);
    cml_NormedInputToGray(out, tmp);
    out += 1;
    in += 1;
  }
}

CML_DEF void cmlData8ToXYZ(const CMLColorMachine* cm, CMLOutput xyz, CMLInput input, size_t count){
  const CMLByte* in  = (CMLByte*)input;
  float* out = (float*)xyz;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_Data8ToFloat3(cm, tmp, in);
    cml_NormedInputToXYZ(out, tmp);
    out += 3;
    in += 3;
  }
}

CML_DEF void cmlData8ToYxy(const CMLColorMachine* cm, CMLOutput yxy, CMLInput input, size_t count){
  const CMLByte* in  = (CMLByte*)input;
  float* out = (float*)yxy;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_Data8ToFloat3(cm, tmp, in);
    cml_NormedInputToYxy(out, tmp);
    out += 3;
    in += 3;
  }
}

CML_DEF void cmlData8ToYuv(const CMLColorMachine* cm, CMLOutput yuv, CMLInput input, size_t count){
  const CMLByte* in  = (CMLByte*)input;
  float* out = (float*)yuv;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_Data8ToFloat3(cm, tmp, in);
    cml_NormedInputToYuv(out, tmp);
    out += 3;
    in += 3;
  }
}

CML_DEF void cmlData8ToYupvp(const CMLColorMachine* cm, CMLOutput yupvp, CMLInput input, size_t count){
  const CMLByte* in  = (CMLByte*)input;
  float* out = (float*)yupvp;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_Data8ToFloat3(cm, tmp, in);
    cml_NormedInputToYupvp(out, tmp);
    out += 3;
    in += 3;
  }
}

CML_DEF void cmlData8ToLab(const CMLColorMachine* cm, CMLOutput lab, CMLInput input, size_t count){
  const CMLByte* in  = (CMLByte*)input;
  float* out = (float*)lab;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_Data8ToFloat3(cm, tmp, in);
    cml_NormedInputToLab(out, tmp);
    out += 3;
    in += 3;
  }
}

CML_DEF void cmlData8ToLch(const CMLColorMachine* cm, CMLOutput lch, CMLInput input, size_t count){
  const CMLByte* in  = (CMLByte*)input;
  float* out = (float*)lch;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_Data8ToFloat3(cm, tmp, in);
    cml_NormedInputToLch(out, tmp);
    out += 3;
    in += 3;
  }
}

CML_DEF void cmlData8ToLuv(const CMLColorMachine* cm, CMLOutput luv, CMLInput input, size_t count){
  const CMLByte* in  = (CMLByte*)input;
  float* out = (float*)luv;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_Data8ToFloat3(cm, tmp, in);
    cml_NormedInputToLuv(out, tmp);
    out += 3;
    in += 3;
  }
}

CML_DEF void cmlData8ToRGB(const CMLColorMachine* cm, CMLOutput rgb, CMLInput input, size_t count){
  const CMLByte* in  = (CMLByte*)input;
  float* out = (float*)rgb;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_Data8ToFloat3(cm, tmp, in);
    cml_NormedInputToRGB(out, tmp);
    out += 3;
    in += 3;
  }
}

CML_DEF void cmlData8ToYCbCr(const CMLColorMachine* cm, CMLOutput ycbcr, CMLInput input, size_t count){
  const CMLByte* in  = (CMLByte*)input;
  float* out = (float*)ycbcr;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_Data8ToFloat3(cm, tmp, in);
    cml_NormedInputToYCbCr(out, tmp);
    out += 3;
    in += 3;
  }
}

CML_DEF void cmlData8ToHSV(const CMLColorMachine* cm, CMLOutput hsv, CMLInput input, size_t count){
  const CMLByte* in  = (CMLByte*)input;
  float* out = (float*)hsv;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_Data8ToFloat3(cm, tmp, in);
    cml_NormedInputToHSV(out, tmp);
    out += 3;
    in += 3;
  }
}

CML_DEF void cmlData8ToHSL(const CMLColorMachine* cm, CMLOutput hsl, CMLInput input, size_t count){
  const CMLByte* in  = (CMLByte*)input;
  float* out = (float*)hsl;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_Data8ToFloat3(cm, tmp, in);
    cml_NormedInputToHSL(out, tmp);
    out += 3;
    in += 3;
  }
}

CML_DEF void cmlData8ToCMYK(const CMLColorMachine* cm, CMLOutput cmyk, CMLInput input, size_t count){
  const CMLByte* in  = (CMLByte*)input;
  float* out = (float*)cmyk;
  for(size_t i = 0; i < count; i++){
    float tmp[4];
    cml_Data8ToFloat4(cm, tmp, in);
    cml_NormedInputToCMYK(out, tmp);
    out += 4;
    in += 4;
  }
}



// //////////////////////////
// 16 bit Input Conversions
// //////////////////////////

CML_DEF void cmlData16ToGray(const CMLColorMachine* cm, CMLOutput gray, CMLInput input, size_t count){
  const CMLWord* in  = (CMLWord*)input;
  float* out = (float*)gray;
  for(size_t i = 0; i < count; i++){
    float tmp[1];
    cml_Data16ToFloat1(cm, tmp, in);
    cml_NormedInputToGray(out, tmp);
    out += 1;
    in += 1;
  }
}

CML_DEF void cmlData16ToXYZ(const CMLColorMachine* cm, CMLOutput xyz, CMLInput input, size_t count){
  const CMLWord* in  = (CMLWord*)input;
  float* out = (float*)xyz;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_Data16ToFloat3(cm, tmp, in);
    cml_NormedInputToXYZ(out, tmp);
    out += 3;
    in += 3;
  }
}

CML_DEF void cmlData16ToYxy(const CMLColorMachine* cm, CMLOutput yxy, CMLInput input, size_t count){
  const CMLWord* in  = (CMLWord*)input;
  float* out = (float*)yxy;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_Data16ToFloat3(cm, tmp, in);
    cml_NormedInputToYxy(out, tmp);
    out += 3;
    in += 3;
  }
}

CML_DEF void cmlData16ToYuv(const CMLColorMachine* cm, CMLOutput yuv, CMLInput input, size_t count){
  const CMLWord* in  = (CMLWord*)input;
  float* out = (float*)yuv;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_Data16ToFloat3(cm, tmp, in);
    cml_NormedInputToYuv(out, tmp);
    out += 3;
    in += 3;
  }
}

CML_DEF void cmlData16ToYupvp(const CMLColorMachine* cm, CMLOutput yupvp, CMLInput input, size_t count){
  const CMLWord* in  = (CMLWord*)input;
  float* out = (float*)yupvp;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_Data16ToFloat3(cm, tmp, in);
    cml_NormedInputToYupvp(out, tmp);
    out += 3;
    in += 3;
  }
}

CML_DEF void cmlData16ToLab(const CMLColorMachine* cm, CMLOutput lab, CMLInput input, size_t count){
  const CMLWord* in  = (CMLWord*)input;
  float* out = (float*)lab;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_Data16ToFloat3(cm, tmp, in);
    cml_NormedInputToLab(out, tmp);
    out += 3;
    in += 3;
  }
}

CML_DEF void cmlData16ToLch(const CMLColorMachine* cm, CMLOutput lch, CMLInput input, size_t count){
  const CMLWord* in  = (CMLWord*)input;
  float* out = (float*)lch;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_Data16ToFloat3(cm, tmp, in);
    cml_NormedInputToLch(out, tmp);
    out += 3;
    in += 3;
  }
}

CML_DEF void cmlData16ToLuv(const CMLColorMachine* cm, CMLOutput luv, CMLInput input, size_t count){
  const CMLWord* in  = (CMLWord*)input;
  float* out = (float*)luv;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_Data16ToFloat3(cm, tmp, in);
    cml_NormedInputToLuv(out, tmp);
    out += 3;
    in += 3;
  }
}

CML_DEF void cmlData16ToRGB(const CMLColorMachine* cm, CMLOutput rgb, CMLInput input, size_t count){
  const CMLWord* in  = (CMLWord*)input;
  float* out = (float*)rgb;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_Data16ToFloat3(cm, tmp, in);
    cml_NormedInputToRGB(out, tmp);
    out += 3;
    in += 3;
  }
}

CML_DEF void cmlData16ToYCbCr(const CMLColorMachine* cm, CMLOutput ycbcr, CMLInput input, size_t count){
  const CMLWord* in  = (CMLWord*)input;
  float* out = (float*)ycbcr;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_Data16ToFloat3(cm, tmp, in);
    cml_NormedInputToYCbCr(out, tmp);
    out += 3;
    in += 3;
  }
}

CML_DEF void cmlData16ToHSV(const CMLColorMachine* cm, CMLOutput hsv, CMLInput input, size_t count){
  const CMLWord* in  = (CMLWord*)input;
  float* out = (float*)hsv;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_Data16ToFloat3(cm, tmp, in);
    cml_NormedInputToHSV(out, tmp);
    out += 3;
    in += 3;
  }
}

CML_DEF void cmlData16ToHSL(const CMLColorMachine* cm, CMLOutput hsl, CMLInput input, size_t count){
  const CMLWord* in  = (CMLWord*)input;
  float* out = (float*)hsl;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_Data16ToFloat3(cm, tmp, in);
    cml_NormedInputToHSL(out, tmp);
    out += 3;
    in += 3;
  }
}

CML_DEF void cmlData16ToCMYK(const CMLColorMachine* cm, CMLOutput cmyk, CMLInput input, size_t count){
  const CMLWord* in  = (CMLWord*)input;
  float* out = (float*)cmyk;
  for(size_t i = 0; i < count; i++){
    float tmp[4];
    cml_Data16ToFloat4(cm, tmp, in);
    cml_NormedInputToCMYK(out, tmp);
    out += 4;
    in += 4;
  }
}









// //////////////////////////
// 8 bit Output Conversions
// //////////////////////////

CML_DEF void cmlGrayToData8(const CMLColorMachine* cm, CMLOutput output, CMLInput gray, size_t count){
  const float* in  = (float*)gray;
  CMLByte* out = (CMLByte*)output;
  for(size_t i = 0; i < count; i++){
    float tmp[1];
    cml_GrayToNormedOutput(tmp, in);
    (*cm->float1ToData8)(cm, out, tmp);
    in += 1;
    out += 1;
  }
}

CML_DEF void cmlXYZToData8(const CMLColorMachine* cm, CMLOutput output, CMLInput xyz, size_t count){
  const float* in  = (float*)xyz;
  CMLByte* out = (CMLByte*)output;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_XYZToNormedOutput(tmp, in);
    (*cm->float3ToData8)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}

CML_DEF void cmlYxyToData8(const CMLColorMachine* cm, CMLOutput output, CMLInput yxy, size_t count){
  const float* in  = (float*)yxy;
  CMLByte* out = (CMLByte*)output;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_YxyToNormedOutput(tmp, in);
    (*cm->float3ToData8)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}

CML_DEF void cmlYuvToData8(const CMLColorMachine* cm, CMLOutput output, CMLInput yuv, size_t count){
  const float* in  = (float*)yuv;
  CMLByte* out = (CMLByte*)output;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_YuvToNormedOutput(tmp, in);
    (*cm->float3ToData8)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}

CML_DEF void cmlYupvpToData8(const CMLColorMachine* cm, CMLOutput output, CMLInput yupvp, size_t count){
  const float* in  = (float*)yupvp;
  CMLByte* out = (CMLByte*)output;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_YupvpToNormedOutput(tmp, in);
    (*cm->float3ToData8)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}

CML_DEF void cmlLabToData8(const CMLColorMachine* cm, CMLOutput output, CMLInput lab, size_t count){
  const float* in  = (float*)lab;
  CMLByte* out = (CMLByte*)output;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_LabToNormedOutput(tmp, in);
    (*cm->float3ToData8)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}

CML_DEF void cmlLchToData8(const CMLColorMachine* cm, CMLOutput output, CMLInput lch, size_t count){
  const float* in  = (float*)lch;
  CMLByte* out = (CMLByte*)output;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_LchToNormedOutput(tmp, in);
    (*cm->float3ToData8)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}

CML_DEF void cmlLuvToData8(const CMLColorMachine* cm, CMLOutput output, CMLInput luv, size_t count){
  const float* in  = (float*)luv;
  CMLByte* out = (CMLByte*)output;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_LuvToNormedOutput(tmp, in);
    (*cm->float3ToData8)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}

CML_DEF void cmlRGBToData8(const CMLColorMachine* cm, CMLOutput output, CMLInput rgb, size_t count){
  const float* in  = (float*)rgb;
  CMLByte* out = (CMLByte*)output;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_RGBToNormedOutput(tmp, in);
    (*cm->float3ToData8)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}

CML_DEF void cmlYCbCrToData8(const CMLColorMachine* cm, CMLOutput output, CMLInput ycbcr, size_t count){
  const float* in  = (float*)ycbcr;
  CMLByte* out = (CMLByte*)output;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_YCbCrToNormedOutput(tmp, in);
    (*cm->float3ToData8)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}

CML_DEF void cmlHSVToData8(const CMLColorMachine* cm, CMLOutput output, CMLInput hsv, size_t count){
  const float* in  = (float*)hsv;
  CMLByte* out = (CMLByte*)output;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_HSVToNormedOutput(tmp, in);
    (*cm->float3ToData8)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}

CML_DEF void cmlHSLToData8(const CMLColorMachine* cm, CMLOutput output, CMLInput hsl, size_t count){
  const float* in  = (float*)hsl;
  CMLByte* out = (CMLByte*)output;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_HSLToNormedOutput(tmp, in);
    (*cm->float3ToData8)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}

CML_DEF void cmlCMYKToData8(const CMLColorMachine* cm, CMLOutput output, CMLInput cmyk, size_t count){
  const float* in  = (float*)cmyk;
  CMLByte* out = (CMLByte*)output;
  for(size_t i = 0; i < count; i++){
    float tmp[4];
    cml_CMYKToNormedOutput(tmp, in);
    (*cm->float4ToData8)(cm, out, tmp);
    in += 4;
    out += 4;
  }
}



// //////////////////////////
// 16 bit Output Conversions
// //////////////////////////

CML_DEF void cmlGrayToData16(const CMLColorMachine* cm, CMLOutput output, CMLInput gray, size_t count){
  const float* in  = (float*)gray;
  CMLWord* out = (CMLWord*)output;
  for(size_t i = 0; i < count; i++){
    float tmp[1];
    cml_GrayToNormedOutput(tmp, in);
    (*cm->float1ToData16)(cm, out, tmp);
    in += 1;
    out += 1;
  }
}

CML_DEF void cmlXYZToData16(const CMLColorMachine* cm, CMLOutput output, CMLInput xyz, size_t count){
  const float* in  = (float*)xyz;
  CMLWord* out = (CMLWord*)output;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_XYZToNormedOutput(tmp, in);
    (*cm->float3ToData16)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}

CML_DEF void cmlYxyToData16(const CMLColorMachine* cm, CMLOutput output, CMLInput yxy, size_t count){
  const float* in  = (float*)yxy;
  CMLWord* out = (CMLWord*)output;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_YxyToNormedOutput(tmp, in);
    (*cm->float3ToData16)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}

CML_DEF void cmlYuvToData16(const CMLColorMachine* cm, CMLOutput output, CMLInput yuv, size_t count){
  const float* in  = (float*)yuv;
  CMLWord* out = (CMLWord*)output;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_YuvToNormedOutput(tmp, in);
    (*cm->float3ToData16)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}

CML_DEF void cmlYupvpToData16(const CMLColorMachine* cm, CMLOutput output, CMLInput yupvp, size_t count){
  const float* in  = (float*)yupvp;
  CMLWord* out = (CMLWord*)output;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_YupvpToNormedOutput(tmp, in);
    (*cm->float3ToData16)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}

CML_DEF void cmlLabToData16(const CMLColorMachine* cm, CMLOutput output, CMLInput lab, size_t count){
  const float* in  = (float*)lab;
  CMLWord* out = (CMLWord*)output;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_LabToNormedOutput(tmp, in);
    (*cm->float3ToData16)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}

CML_DEF void cmlLchToData16(const CMLColorMachine* cm, CMLOutput output, CMLInput lch, size_t count){
  const float* in  = (float*)lch;
  CMLWord* out = (CMLWord*)output;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_LchToNormedOutput(tmp, in);
    (*cm->float3ToData16)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}

CML_DEF void cmlLuvToData16(const CMLColorMachine* cm, CMLOutput output, CMLInput luv, size_t count){
  const float* in  = (float*)luv;
  CMLWord* out = (CMLWord*)output;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_LuvToNormedOutput(tmp, in);
    (*cm->float3ToData16)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}

CML_DEF void cmlRGBToData16(const CMLColorMachine* cm, CMLOutput output, CMLInput rgb, size_t count){
  const float* in  = (float*)rgb;
  CMLWord* out = (CMLWord*)output;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_RGBToNormedOutput(tmp, in);
    (*cm->float3ToData16)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}

CML_DEF void cmlYCbCrToData16(const CMLColorMachine* cm, CMLOutput output, CMLInput ycbcr, size_t count){
  const float* in  = (float*)ycbcr;
  CMLWord* out = (CMLWord*)output;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_YCbCrToNormedOutput(tmp, in);
    (*cm->float3ToData16)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}

CML_DEF void cmlHSVToData16(const CMLColorMachine* cm, CMLOutput output, CMLInput hsv, size_t count){
  const float* in  = (float*)hsv;
  CMLWord* out = (CMLWord*)output;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_HSVToNormedOutput(tmp, in);
    (*cm->float3ToData16)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}

CML_DEF void cmlHSLToData16(const CMLColorMachine* cm, CMLOutput output, CMLInput hsl, size_t count){
  const float* in  = (float*)hsl;
  CMLWord* out = (CMLWord*)output;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_HSLToNormedOutput(tmp, in);
    (*cm->float3ToData16)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}

CML_DEF void cmlCMYKToData16(const CMLColorMachine* cm, CMLOutput output, CMLInput cmyk, size_t count){
  const float* in  = (float*)cmyk;
  CMLWord* out = (CMLWord*)output;
  for(size_t i = 0; i < count; i++){
    float tmp[4];
    cml_CMYKToNormedOutput(tmp, in);
    (*cm->float4ToData16)(cm, out, tmp);
    in += 4;
    out += 4;
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

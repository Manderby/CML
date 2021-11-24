
#include "../CML.h"
#include "../StateMachine/CMLColorMachineState.h"


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


CML_HIDDEN CML_INLINE static void cml_FloatWithData8(float* out, CMLByte in, CMLByte offset, float range){
  *out = (float)(in - offset) / range;
}
CML_HIDDEN CML_INLINE static void cml_FloatWithData16(float* out, CMLWord in, CMLWord offset, float range){
  *out = (float)(in - offset) / range;
}


CML_HIDDEN CML_INLINE static void cml_Float1WithData8(const CMLColorMachine* cm, float* CML_RESTRICT out, const CMLByte* CML_RESTRICT in){
  cml_FloatWithData8(&(out[0]), in[0], cm->inputoutput.offset8Bit[0], cm->inputoutput.range8Bit[0]);
}
CML_HIDDEN CML_INLINE static void cml_Float3WithData8(const CMLColorMachine* cm, float* CML_RESTRICT out, const CMLByte* CML_RESTRICT in){
  cml_FloatWithData8(&(out[0]), in[0], cm->inputoutput.offset8Bit[0], cm->inputoutput.range8Bit[0]);
  cml_FloatWithData8(&(out[1]), in[1], cm->inputoutput.offset8Bit[1], cm->inputoutput.range8Bit[1]);
  cml_FloatWithData8(&(out[2]), in[2], cm->inputoutput.offset8Bit[2], cm->inputoutput.range8Bit[2]);
}
CML_HIDDEN CML_INLINE static void cml_Float4WithData8(const CMLColorMachine* cm, float* CML_RESTRICT out, const CMLByte* CML_RESTRICT in){
  cml_FloatWithData8(&(out[0]), in[0], cm->inputoutput.offset8Bit[0], cm->inputoutput.range8Bit[0]);
  cml_FloatWithData8(&(out[1]), in[1], cm->inputoutput.offset8Bit[1], cm->inputoutput.range8Bit[1]);
  cml_FloatWithData8(&(out[2]), in[2], cm->inputoutput.offset8Bit[2], cm->inputoutput.range8Bit[2]);
  cml_FloatWithData8(&(out[3]), in[3], cm->inputoutput.offset8Bit[3], cm->inputoutput.range8Bit[3]);
}


CML_HIDDEN CML_INLINE static void cml_Float1WithData16(const CMLColorMachine* cm, float* CML_RESTRICT out, const CMLWord* CML_RESTRICT in){
  cml_FloatWithData16(&(out[0]), in[0], cm->inputoutput.offset16Bit[0], cm->inputoutput.range16Bit[0]);
}
CML_HIDDEN CML_INLINE static void cml_Float3WithData16(const CMLColorMachine* cm, float* CML_RESTRICT out, const CMLWord* CML_RESTRICT in){
  cml_FloatWithData16(&(out[0]), in[0], cm->inputoutput.offset16Bit[0], cm->inputoutput.range16Bit[0]);
  cml_FloatWithData16(&(out[1]), in[1], cm->inputoutput.offset16Bit[1], cm->inputoutput.range16Bit[1]);
  cml_FloatWithData16(&(out[2]), in[2], cm->inputoutput.offset16Bit[2], cm->inputoutput.range16Bit[2]);
}
CML_HIDDEN CML_INLINE static void cml_Float4WithData16(const CMLColorMachine* cm, float* CML_RESTRICT out, const CMLWord* CML_RESTRICT in){
  cml_FloatWithData16(&(out[0]), in[0], cm->inputoutput.offset16Bit[0], cm->inputoutput.range16Bit[0]);
  cml_FloatWithData16(&(out[1]), in[1], cm->inputoutput.offset16Bit[1], cm->inputoutput.range16Bit[1]);
  cml_FloatWithData16(&(out[2]), in[2], cm->inputoutput.offset16Bit[2], cm->inputoutput.range16Bit[2]);
  cml_FloatWithData16(&(out[3]), in[3], cm->inputoutput.offset16Bit[3], cm->inputoutput.range16Bit[3]);
}



// //////////////////////////
// 8 bit Input Conversions
// //////////////////////////

CML_API void cmlGrayWithData8(const CMLColorMachine* cm, CMLOutput gray, CMLInput input, size_t count){
  const CMLByte* in  = (CMLByte*)input;
  float* out = (float*)gray;
  for(size_t i = 0; i < count; i++){
    float tmp[1];
    cml_Float1WithData8(cm, tmp, in);
    cml_GrayWithNormedInput(out, tmp);
    out += 1;
    in += 1;
  }
}

CML_API void cmlXYZWithData8(const CMLColorMachine* cm, CMLOutput xyz, CMLInput input, size_t count){
  const CMLByte* in  = (CMLByte*)input;
  float* out = (float*)xyz;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_Float3WithData8(cm, tmp, in);
    cml_XYZWithNormedInput(out, tmp);
    out += 3;
    in += 3;
  }
}

CML_API void cmlYxyWithData8(const CMLColorMachine* cm, CMLOutput yxy, CMLInput input, size_t count){
  const CMLByte* in  = (CMLByte*)input;
  float* out = (float*)yxy;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_Float3WithData8(cm, tmp, in);
    cml_YxyWithNormedInput(out, tmp);
    out += 3;
    in += 3;
  }
}

CML_API void cmlYuvWithData8(const CMLColorMachine* cm, CMLOutput yuv, CMLInput input, size_t count){
  const CMLByte* in  = (CMLByte*)input;
  float* out = (float*)yuv;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_Float3WithData8(cm, tmp, in);
    cml_YuvWithNormedInput(out, tmp);
    out += 3;
    in += 3;
  }
}

CML_API void cmlYupvpWithData8(const CMLColorMachine* cm, CMLOutput yupvp, CMLInput input, size_t count){
  const CMLByte* in  = (CMLByte*)input;
  float* out = (float*)yupvp;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_Float3WithData8(cm, tmp, in);
    cml_YupvpWithNormedInput(out, tmp);
    out += 3;
    in += 3;
  }
}

CML_API void cmlLabWithData8(const CMLColorMachine* cm, CMLOutput lab, CMLInput input, size_t count){
  const CMLByte* in  = (CMLByte*)input;
  float* out = (float*)lab;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_Float3WithData8(cm, tmp, in);
    cml_LabWithNormedInput(out, tmp);
    out += 3;
    in += 3;
  }
}

CML_API void cmlLchWithData8(const CMLColorMachine* cm, CMLOutput lch, CMLInput input, size_t count){
  const CMLByte* in  = (CMLByte*)input;
  float* out = (float*)lch;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_Float3WithData8(cm, tmp, in);
    cml_LchWithNormedInput(out, tmp);
    out += 3;
    in += 3;
  }
}

CML_API void cmlLuvWithData8(const CMLColorMachine* cm, CMLOutput luv, CMLInput input, size_t count){
  const CMLByte* in  = (CMLByte*)input;
  float* out = (float*)luv;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_Float3WithData8(cm, tmp, in);
    cml_LuvWithNormedInput(out, tmp);
    out += 3;
    in += 3;
  }
}

CML_API void cmlRGBWithData8(const CMLColorMachine* cm, CMLOutput rgb, CMLInput input, size_t count){
  const CMLByte* in  = (CMLByte*)input;
  float* out = (float*)rgb;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_Float3WithData8(cm, tmp, in);
    cml_RGBWithNormedInput(out, tmp);
    out += 3;
    in += 3;
  }
}

CML_API void cmlYCbCrWithData8(const CMLColorMachine* cm, CMLOutput ycbcr, CMLInput input, size_t count){
  const CMLByte* in  = (CMLByte*)input;
  float* out = (float*)ycbcr;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_Float3WithData8(cm, tmp, in);
    cml_YCbCrWithNormedInput(out, tmp);
    out += 3;
    in += 3;
  }
}

CML_API void cmlHSVWithData8(const CMLColorMachine* cm, CMLOutput hsv, CMLInput input, size_t count){
  const CMLByte* in  = (CMLByte*)input;
  float* out = (float*)hsv;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_Float3WithData8(cm, tmp, in);
    cml_HSVWithNormedInput(out, tmp);
    out += 3;
    in += 3;
  }
}

CML_API void cmlHSLWithData8(const CMLColorMachine* cm, CMLOutput hsl, CMLInput input, size_t count){
  const CMLByte* in  = (CMLByte*)input;
  float* out = (float*)hsl;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_Float3WithData8(cm, tmp, in);
    cml_HSLWithNormedInput(out, tmp);
    out += 3;
    in += 3;
  }
}

CML_API void cmlCMYKWithData8(const CMLColorMachine* cm, CMLOutput cmyk, CMLInput input, size_t count){
  const CMLByte* in  = (CMLByte*)input;
  float* out = (float*)cmyk;
  for(size_t i = 0; i < count; i++){
    float tmp[4];
    cml_Float4WithData8(cm, tmp, in);
    cml_CMYKWithNormedInput(out, tmp);
    out += 4;
    in += 4;
  }
}



// //////////////////////////
// 16 bit Input Conversions
// //////////////////////////

CML_API void cmlGrayWithData16(const CMLColorMachine* cm, CMLOutput gray, CMLInput input, size_t count){
  const CMLWord* in  = (CMLWord*)input;
  float* out = (float*)gray;
  for(size_t i = 0; i < count; i++){
    float tmp[1];
    cml_Float1WithData16(cm, tmp, in);
    cml_GrayWithNormedInput(out, tmp);
    out += 1;
    in += 1;
  }
}

CML_API void cmlXYZWithData16(const CMLColorMachine* cm, CMLOutput xyz, CMLInput input, size_t count){
  const CMLWord* in  = (CMLWord*)input;
  float* out = (float*)xyz;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_Float3WithData16(cm, tmp, in);
    cml_XYZWithNormedInput(out, tmp);
    out += 3;
    in += 3;
  }
}

CML_API void cmlYxyWithData16(const CMLColorMachine* cm, CMLOutput yxy, CMLInput input, size_t count){
  const CMLWord* in  = (CMLWord*)input;
  float* out = (float*)yxy;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_Float3WithData16(cm, tmp, in);
    cml_YxyWithNormedInput(out, tmp);
    out += 3;
    in += 3;
  }
}

CML_API void cmlYuvWithData16(const CMLColorMachine* cm, CMLOutput yuv, CMLInput input, size_t count){
  const CMLWord* in  = (CMLWord*)input;
  float* out = (float*)yuv;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_Float3WithData16(cm, tmp, in);
    cml_YuvWithNormedInput(out, tmp);
    out += 3;
    in += 3;
  }
}

CML_API void cmlYupvpWithData16(const CMLColorMachine* cm, CMLOutput yupvp, CMLInput input, size_t count){
  const CMLWord* in  = (CMLWord*)input;
  float* out = (float*)yupvp;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_Float3WithData16(cm, tmp, in);
    cml_YupvpWithNormedInput(out, tmp);
    out += 3;
    in += 3;
  }
}

CML_API void cmlLabWithData16(const CMLColorMachine* cm, CMLOutput lab, CMLInput input, size_t count){
  const CMLWord* in  = (CMLWord*)input;
  float* out = (float*)lab;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_Float3WithData16(cm, tmp, in);
    cml_LabWithNormedInput(out, tmp);
    out += 3;
    in += 3;
  }
}

CML_API void cmlLchWithData16(const CMLColorMachine* cm, CMLOutput lch, CMLInput input, size_t count){
  const CMLWord* in  = (CMLWord*)input;
  float* out = (float*)lch;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_Float3WithData16(cm, tmp, in);
    cml_LchWithNormedInput(out, tmp);
    out += 3;
    in += 3;
  }
}

CML_API void cmlLuvWithData16(const CMLColorMachine* cm, CMLOutput luv, CMLInput input, size_t count){
  const CMLWord* in  = (CMLWord*)input;
  float* out = (float*)luv;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_Float3WithData16(cm, tmp, in);
    cml_LuvWithNormedInput(out, tmp);
    out += 3;
    in += 3;
  }
}

CML_API void cmlRGBWithData16(const CMLColorMachine* cm, CMLOutput rgb, CMLInput input, size_t count){
  const CMLWord* in  = (CMLWord*)input;
  float* out = (float*)rgb;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_Float3WithData16(cm, tmp, in);
    cml_RGBWithNormedInput(out, tmp);
    out += 3;
    in += 3;
  }
}

CML_API void cmlYCbCrWithData16(const CMLColorMachine* cm, CMLOutput ycbcr, CMLInput input, size_t count){
  const CMLWord* in  = (CMLWord*)input;
  float* out = (float*)ycbcr;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_Float3WithData16(cm, tmp, in);
    cml_YCbCrWithNormedInput(out, tmp);
    out += 3;
    in += 3;
  }
}

CML_API void cmlHSVWithData16(const CMLColorMachine* cm, CMLOutput hsv, CMLInput input, size_t count){
  const CMLWord* in  = (CMLWord*)input;
  float* out = (float*)hsv;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_Float3WithData16(cm, tmp, in);
    cml_HSVWithNormedInput(out, tmp);
    out += 3;
    in += 3;
  }
}

CML_API void cmlHSLWithData16(const CMLColorMachine* cm, CMLOutput hsl, CMLInput input, size_t count){
  const CMLWord* in  = (CMLWord*)input;
  float* out = (float*)hsl;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_Float3WithData16(cm, tmp, in);
    cml_HSLWithNormedInput(out, tmp);
    out += 3;
    in += 3;
  }
}

CML_API void cmlCMYKWithData16(const CMLColorMachine* cm, CMLOutput cmyk, CMLInput input, size_t count){
  const CMLWord* in  = (CMLWord*)input;
  float* out = (float*)cmyk;
  for(size_t i = 0; i < count; i++){
    float tmp[4];
    cml_Float4WithData16(cm, tmp, in);
    cml_CMYKWithNormedInput(out, tmp);
    out += 4;
    in += 4;
  }
}







CML_HIDDEN CML_INLINE static void cml_Data8WithFloatFloor(CMLByte* out, float in, CMLByte offset, float range){
  *out = offset + (CMLByte)(in*range);
}
CML_HIDDEN CML_INLINE static void cml_Data16WithFloatFloor(CMLWord* out, float in, CMLWord offset, float range){
  *out = offset + (CMLByte)(in*range);
}
CML_HIDDEN CML_INLINE static void cml_Data8WithFloatBox(CMLByte* out, float in, CMLByte offset, float range){
  *out = offset + (CMLByte)(in*range + .5f);
}
CML_HIDDEN CML_INLINE static void cml_Data16WithFloatBox(CMLWord* out, float in, CMLWord offset, float range){
  *out = offset + (CMLByte)(in*range + .5f);
}
CML_HIDDEN CML_INLINE static void cml_Data8WithFloatInterval(CMLByte* out, float in, CMLByte offset, float range){
  *out = offset + ((in == 1.f) ? (CMLByte)range : (CMLByte)(in*(range + 1.f)));
}
CML_HIDDEN CML_INLINE static void cml_Data16WithFloatInterval(CMLWord* out, float in, CMLWord offset, float range){
  *out = offset + ((in == 1.f) ? (CMLWord)range : (CMLWord)(in*(range + 1.f)));
}

CML_HIDDEN void cml_Data8WithFloat1Floor(const CMLColorMachine* cm, CMLByte* CML_RESTRICT out, const float* CML_RESTRICT in){
  cml_Data8WithFloatFloor(&(out[0]), in[0], cm->inputoutput.offset8Bit[0], cm->inputoutput.range8Bit[0]);
}
CML_HIDDEN void cml_Data8WithFloat3Floor(const CMLColorMachine* cm, CMLByte* CML_RESTRICT out, const float* CML_RESTRICT in){
  cml_Data8WithFloatFloor(&(out[0]), in[0], cm->inputoutput.offset8Bit[0], cm->inputoutput.range8Bit[0]);
  cml_Data8WithFloatFloor(&(out[1]), in[1], cm->inputoutput.offset8Bit[1], cm->inputoutput.range8Bit[1]);
  cml_Data8WithFloatFloor(&(out[2]), in[2], cm->inputoutput.offset8Bit[2], cm->inputoutput.range8Bit[2]);
}
CML_HIDDEN void cml_Data8WithFloat4Floor(const CMLColorMachine* cm, CMLByte* CML_RESTRICT out, const float* CML_RESTRICT in){
  cml_Data8WithFloatFloor(&(out[0]), in[0], cm->inputoutput.offset8Bit[0], cm->inputoutput.range8Bit[0]);
  cml_Data8WithFloatFloor(&(out[1]), in[1], cm->inputoutput.offset8Bit[1], cm->inputoutput.range8Bit[1]);
  cml_Data8WithFloatFloor(&(out[2]), in[2], cm->inputoutput.offset8Bit[2], cm->inputoutput.range8Bit[2]);
  cml_Data8WithFloatFloor(&(out[3]), in[3], cm->inputoutput.offset8Bit[3], cm->inputoutput.range8Bit[3]);
}

CML_HIDDEN void cml_Data8WithFloat1Box(const CMLColorMachine* cm, CMLByte* CML_RESTRICT out, const float* CML_RESTRICT in){
  cml_Data8WithFloatBox(&(out[0]), in[0], cm->inputoutput.offset8Bit[0], cm->inputoutput.range8Bit[0]);
}
CML_HIDDEN void cml_Data8WithFloat3Box(const CMLColorMachine* cm, CMLByte* CML_RESTRICT out, const float* CML_RESTRICT in){
  cml_Data8WithFloatBox(&(out[0]), in[0], cm->inputoutput.offset8Bit[0], cm->inputoutput.range8Bit[0]);
  cml_Data8WithFloatBox(&(out[1]), in[1], cm->inputoutput.offset8Bit[1], cm->inputoutput.range8Bit[1]);
  cml_Data8WithFloatBox(&(out[2]), in[2], cm->inputoutput.offset8Bit[2], cm->inputoutput.range8Bit[2]);
}
CML_HIDDEN void cml_Data8WithFloat4Box(const CMLColorMachine* cm, CMLByte* CML_RESTRICT out, const float* CML_RESTRICT in){
  cml_Data8WithFloatBox(&(out[0]), in[0], cm->inputoutput.offset8Bit[0], cm->inputoutput.range8Bit[0]);
  cml_Data8WithFloatBox(&(out[1]), in[1], cm->inputoutput.offset8Bit[1], cm->inputoutput.range8Bit[1]);
  cml_Data8WithFloatBox(&(out[2]), in[2], cm->inputoutput.offset8Bit[2], cm->inputoutput.range8Bit[2]);
  cml_Data8WithFloatBox(&(out[3]), in[3], cm->inputoutput.offset8Bit[3], cm->inputoutput.range8Bit[3]);
}

CML_HIDDEN void cml_Data8WithFloat1Interval(const CMLColorMachine* cm, CMLByte* CML_RESTRICT out, const float* CML_RESTRICT in){
  cml_Data8WithFloatInterval(&(out[0]), in[0], cm->inputoutput.offset8Bit[0], cm->inputoutput.range8Bit[0]);
}
CML_HIDDEN void cml_Data8WithFloat3Interval(const CMLColorMachine* cm, CMLByte* CML_RESTRICT out, const float* CML_RESTRICT in){
  cml_Data8WithFloatInterval(&(out[0]), in[0], cm->inputoutput.offset8Bit[0], cm->inputoutput.range8Bit[0]);
  cml_Data8WithFloatInterval(&(out[1]), in[1], cm->inputoutput.offset8Bit[1], cm->inputoutput.range8Bit[1]);
  cml_Data8WithFloatInterval(&(out[2]), in[2], cm->inputoutput.offset8Bit[2], cm->inputoutput.range8Bit[2]);
}
CML_HIDDEN void cml_Data8WithFloat4Interval(const CMLColorMachine* cm, CMLByte* CML_RESTRICT out, const float* CML_RESTRICT in){
  cml_Data8WithFloatInterval(&(out[0]), in[0], cm->inputoutput.offset8Bit[0], cm->inputoutput.range8Bit[0]);
  cml_Data8WithFloatInterval(&(out[1]), in[1], cm->inputoutput.offset8Bit[1], cm->inputoutput.range8Bit[1]);
  cml_Data8WithFloatInterval(&(out[2]), in[2], cm->inputoutput.offset8Bit[2], cm->inputoutput.range8Bit[2]);
  cml_Data8WithFloatInterval(&(out[3]), in[3], cm->inputoutput.offset8Bit[3], cm->inputoutput.range8Bit[3]);
}


CML_HIDDEN void cml_Data16WithFloat1Floor(const CMLColorMachine* cm, CMLWord* CML_RESTRICT out, const float* CML_RESTRICT in){
  cml_Data16WithFloatFloor(&(out[0]), in[0], cm->inputoutput.offset16Bit[0], cm->inputoutput.range16Bit[0]);
}
CML_HIDDEN void cml_Data16WithFloat3Floor(const CMLColorMachine* cm, CMLWord* CML_RESTRICT out, const float* CML_RESTRICT in){
  cml_Data16WithFloatFloor(&(out[0]), in[0], cm->inputoutput.offset16Bit[0], cm->inputoutput.range16Bit[0]);
  cml_Data16WithFloatFloor(&(out[1]), in[1], cm->inputoutput.offset16Bit[1], cm->inputoutput.range16Bit[1]);
  cml_Data16WithFloatFloor(&(out[2]), in[2], cm->inputoutput.offset16Bit[2], cm->inputoutput.range16Bit[2]);
}
CML_HIDDEN void cml_Data16WithFloat4Floor(const CMLColorMachine* cm, CMLWord* CML_RESTRICT out, const float* CML_RESTRICT in){
  cml_Data16WithFloatFloor(&(out[0]), in[0], cm->inputoutput.offset16Bit[0], cm->inputoutput.range16Bit[0]);
  cml_Data16WithFloatFloor(&(out[1]), in[1], cm->inputoutput.offset16Bit[1], cm->inputoutput.range16Bit[1]);
  cml_Data16WithFloatFloor(&(out[2]), in[2], cm->inputoutput.offset16Bit[2], cm->inputoutput.range16Bit[2]);
  cml_Data16WithFloatFloor(&(out[3]), in[3], cm->inputoutput.offset16Bit[3], cm->inputoutput.range16Bit[3]);
}

CML_HIDDEN void cml_Data16WithFloat1Box(const CMLColorMachine* cm, CMLWord* CML_RESTRICT out, const float* CML_RESTRICT in){
  cml_Data16WithFloatBox(&(out[0]), in[0], cm->inputoutput.offset16Bit[0], cm->inputoutput.range16Bit[0]);
}
CML_HIDDEN void cml_Data16WithFloat3Box(const CMLColorMachine* cm, CMLWord* CML_RESTRICT out, const float* CML_RESTRICT in){
  cml_Data16WithFloatBox(&(out[0]), in[0], cm->inputoutput.offset16Bit[0], cm->inputoutput.range16Bit[0]);
  cml_Data16WithFloatBox(&(out[1]), in[1], cm->inputoutput.offset16Bit[1], cm->inputoutput.range16Bit[1]);
  cml_Data16WithFloatBox(&(out[2]), in[2], cm->inputoutput.offset16Bit[2], cm->inputoutput.range16Bit[2]);
}
CML_HIDDEN void cml_Data16WithFloat4Box(const CMLColorMachine* cm, CMLWord* CML_RESTRICT out, const float* CML_RESTRICT in){
  cml_Data16WithFloatBox(&(out[0]), in[0], cm->inputoutput.offset16Bit[0], cm->inputoutput.range16Bit[0]);
  cml_Data16WithFloatBox(&(out[1]), in[1], cm->inputoutput.offset16Bit[1], cm->inputoutput.range16Bit[1]);
  cml_Data16WithFloatBox(&(out[2]), in[2], cm->inputoutput.offset16Bit[2], cm->inputoutput.range16Bit[2]);
  cml_Data16WithFloatBox(&(out[3]), in[3], cm->inputoutput.offset16Bit[3], cm->inputoutput.range16Bit[3]);
}

CML_HIDDEN void cml_Data16WithFloat1Interval(const CMLColorMachine* cm, CMLWord* CML_RESTRICT out, const float* CML_RESTRICT in){
  cml_Data16WithFloatInterval(&(out[0]), in[0], cm->inputoutput.offset16Bit[0], cm->inputoutput.range16Bit[0]);
}
CML_HIDDEN void cml_Data16WithFloat3Interval(const CMLColorMachine* cm, CMLWord* CML_RESTRICT out, const float* CML_RESTRICT in){
  cml_Data16WithFloatInterval(&(out[0]), in[0], cm->inputoutput.offset16Bit[0], cm->inputoutput.range16Bit[0]);
  cml_Data16WithFloatInterval(&(out[1]), in[1], cm->inputoutput.offset16Bit[1], cm->inputoutput.range16Bit[1]);
  cml_Data16WithFloatInterval(&(out[2]), in[2], cm->inputoutput.offset16Bit[2], cm->inputoutput.range16Bit[2]);
}
CML_HIDDEN void cml_Data16WithFloat4Interval(const CMLColorMachine* cm, CMLWord* CML_RESTRICT out, const float* CML_RESTRICT in){
  cml_Data16WithFloatInterval(&(out[0]), in[0], cm->inputoutput.offset16Bit[0], cm->inputoutput.range16Bit[0]);
  cml_Data16WithFloatInterval(&(out[1]), in[1], cm->inputoutput.offset16Bit[1], cm->inputoutput.range16Bit[1]);
  cml_Data16WithFloatInterval(&(out[2]), in[2], cm->inputoutput.offset16Bit[2], cm->inputoutput.range16Bit[2]);
  cml_Data16WithFloatInterval(&(out[3]), in[3], cm->inputoutput.offset16Bit[3], cm->inputoutput.range16Bit[3]);
}



// //////////////////////////
// 8 bit Output Conversions
// //////////////////////////

CML_API void cmlData8WithGray(const CMLColorMachine* cm, CMLOutput output, CMLInput gray, size_t count){
  const float* in  = (float*)gray;
  CMLByte* out = (CMLByte*)output;
  for(size_t i = 0; i < count; i++){
    float tmp[1];
    cml_NormedOutputWithGray(tmp, in);
    (*cm->data8WithFloat1)(cm, out, tmp);
    in += 1;
    out += 1;
  }
}

CML_API void cmlData8WithXYZ(const CMLColorMachine* cm, CMLOutput output, CMLInput xyz, size_t count){
  const float* in  = (float*)xyz;
  CMLByte* out = (CMLByte*)output;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_NormedOutputWithXYZ(tmp, in);
    (*cm->data8WithFloat3)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}

CML_API void cmlData8WithYxy(const CMLColorMachine* cm, CMLOutput output, CMLInput yxy, size_t count){
  const float* in  = (float*)yxy;
  CMLByte* out = (CMLByte*)output;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_NormedOutputWithYxy(tmp, in);
    (*cm->data8WithFloat3)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}

CML_API void cmlData8WithYuv(const CMLColorMachine* cm, CMLOutput output, CMLInput yuv, size_t count){
  const float* in  = (float*)yuv;
  CMLByte* out = (CMLByte*)output;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_NormedOutputWithYuv(tmp, in);
    (*cm->data8WithFloat3)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}

CML_API void cmlData8WithYupvp(const CMLColorMachine* cm, CMLOutput output, CMLInput yupvp, size_t count){
  const float* in  = (float*)yupvp;
  CMLByte* out = (CMLByte*)output;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_NormedOutputWithYupvp(tmp, in);
    (*cm->data8WithFloat3)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}

CML_API void cmlData8WithLab(const CMLColorMachine* cm, CMLOutput output, CMLInput lab, size_t count){
  const float* in  = (float*)lab;
  CMLByte* out = (CMLByte*)output;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_NormedOutputWithLab(tmp, in);
    (*cm->data8WithFloat3)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}

CML_API void cmlData8WithLch(const CMLColorMachine* cm, CMLOutput output, CMLInput lch, size_t count){
  const float* in  = (float*)lch;
  CMLByte* out = (CMLByte*)output;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_NormedOutputWithLch(tmp, in);
    (*cm->data8WithFloat3)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}

CML_API void cmlData8WithLuv(const CMLColorMachine* cm, CMLOutput output, CMLInput luv, size_t count){
  const float* in  = (float*)luv;
  CMLByte* out = (CMLByte*)output;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_NormedOutputWithLuv(tmp, in);
    (*cm->data8WithFloat3)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}

CML_API void cmlData8WithRGB(const CMLColorMachine* cm, CMLOutput output, CMLInput rgb, size_t count){
  const float* in  = (float*)rgb;
  CMLByte* out = (CMLByte*)output;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_NormedOutputWithRGB(tmp, in);
    (*cm->data8WithFloat3)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}

CML_API void cmlData8WithYCbCr(const CMLColorMachine* cm, CMLOutput output, CMLInput ycbcr, size_t count){
  const float* in  = (float*)ycbcr;
  CMLByte* out = (CMLByte*)output;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_NormedOutputWithYCbCr(tmp, in);
    (*cm->data8WithFloat3)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}

CML_API void cmlData8WithHSV(const CMLColorMachine* cm, CMLOutput output, CMLInput hsv, size_t count){
  const float* in  = (float*)hsv;
  CMLByte* out = (CMLByte*)output;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_NormedOutputWithHSV(tmp, in);
    (*cm->data8WithFloat3)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}

CML_API void cmlData8WithHSL(const CMLColorMachine* cm, CMLOutput output, CMLInput hsl, size_t count){
  const float* in  = (float*)hsl;
  CMLByte* out = (CMLByte*)output;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_NormedOutputWithHSL(tmp, in);
    (*cm->data8WithFloat3)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}

CML_API void cmlData8WithCMYK(const CMLColorMachine* cm, CMLOutput output, CMLInput cmyk, size_t count){
  const float* in  = (float*)cmyk;
  CMLByte* out = (CMLByte*)output;
  for(size_t i = 0; i < count; i++){
    float tmp[4];
    cml_NormedOutputWithCMYK(tmp, in);
    (*cm->data8WithFloat4)(cm, out, tmp);
    in += 4;
    out += 4;
  }
}



// //////////////////////////
// 16 bit Output Conversions
// //////////////////////////

CML_API void cmlData16WithGray(const CMLColorMachine* cm, CMLOutput output, CMLInput gray, size_t count){
  const float* in  = (float*)gray;
  CMLWord* out = (CMLWord*)output;
  for(size_t i = 0; i < count; i++){
    float tmp[1];
    cml_NormedOutputWithGray(tmp, in);
    (*cm->data16WithFloat1)(cm, out, tmp);
    in += 1;
    out += 1;
  }
}

CML_API void cmlData16WithXYZ(const CMLColorMachine* cm, CMLOutput output, CMLInput xyz, size_t count){
  const float* in  = (float*)xyz;
  CMLWord* out = (CMLWord*)output;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_NormedOutputWithXYZ(tmp, in);
    (*cm->data16WithFloat3)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}

CML_API void cmlData16WithYxy(const CMLColorMachine* cm, CMLOutput output, CMLInput yxy, size_t count){
  const float* in  = (float*)yxy;
  CMLWord* out = (CMLWord*)output;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_NormedOutputWithYxy(tmp, in);
    (*cm->data16WithFloat3)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}

CML_API void cmlData16WithYuv(const CMLColorMachine* cm, CMLOutput output, CMLInput yuv, size_t count){
  const float* in  = (float*)yuv;
  CMLWord* out = (CMLWord*)output;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_NormedOutputWithYuv(tmp, in);
    (*cm->data16WithFloat3)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}

CML_API void cmlData16WithYupvp(const CMLColorMachine* cm, CMLOutput output, CMLInput yupvp, size_t count){
  const float* in  = (float*)yupvp;
  CMLWord* out = (CMLWord*)output;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_NormedOutputWithYupvp(tmp, in);
    (*cm->data16WithFloat3)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}

CML_API void cmlData16WithLab(const CMLColorMachine* cm, CMLOutput output, CMLInput lab, size_t count){
  const float* in  = (float*)lab;
  CMLWord* out = (CMLWord*)output;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_NormedOutputWithLab(tmp, in);
    (*cm->data16WithFloat3)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}

CML_API void cmlData16WithLch(const CMLColorMachine* cm, CMLOutput output, CMLInput lch, size_t count){
  const float* in  = (float*)lch;
  CMLWord* out = (CMLWord*)output;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_NormedOutputWithLch(tmp, in);
    (*cm->data16WithFloat3)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}

CML_API void cmlData16WithLuv(const CMLColorMachine* cm, CMLOutput output, CMLInput luv, size_t count){
  const float* in  = (float*)luv;
  CMLWord* out = (CMLWord*)output;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_NormedOutputWithLuv(tmp, in);
    (*cm->data16WithFloat3)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}

CML_API void cmlData16WithRGB(const CMLColorMachine* cm, CMLOutput output, CMLInput rgb, size_t count){
  const float* in  = (float*)rgb;
  CMLWord* out = (CMLWord*)output;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_NormedOutputWithRGB(tmp, in);
    (*cm->data16WithFloat3)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}

CML_API void cmlData16WithYCbCr(const CMLColorMachine* cm, CMLOutput output, CMLInput ycbcr, size_t count){
  const float* in  = (float*)ycbcr;
  CMLWord* out = (CMLWord*)output;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_NormedOutputWithYCbCr(tmp, in);
    (*cm->data16WithFloat3)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}

CML_API void cmlData16WithHSV(const CMLColorMachine* cm, CMLOutput output, CMLInput hsv, size_t count){
  const float* in  = (float*)hsv;
  CMLWord* out = (CMLWord*)output;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_NormedOutputWithHSV(tmp, in);
    (*cm->data16WithFloat3)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}

CML_API void cmlData16WithHSL(const CMLColorMachine* cm, CMLOutput output, CMLInput hsl, size_t count){
  const float* in  = (float*)hsl;
  CMLWord* out = (CMLWord*)output;
  for(size_t i = 0; i < count; i++){
    float tmp[3];
    cml_NormedOutputWithHSL(tmp, in);
    (*cm->data16WithFloat3)(cm, out, tmp);
    in += 3;
    out += 3;
  }
}

CML_API void cmlData16WithCMYK(const CMLColorMachine* cm, CMLOutput output, CMLInput cmyk, size_t count){
  const float* in  = (float*)cmyk;
  CMLWord* out = (CMLWord*)output;
  for(size_t i = 0; i < count; i++){
    float tmp[4];
    cml_NormedOutputWithCMYK(tmp, in);
    (*cm->data16WithFloat4)(cm, out, tmp);
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

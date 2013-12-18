
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.


// todo: Make it SB
#define CMLINTERNALRGBtoHSV(out, in) \
  float min;\
  float range;\
  CMLVec3 RGB;\
  cmlCpy3(RGB, in);\
  if(RGB[0] < RGB[1]){min = RGB[0]; out[2] = RGB[1];}else{min = RGB[1]; out[2] = RGB[0];}\
  if(RGB[2] < min){min = RGB[2];}\
  if(RGB[2] > out[2]){out[2] = RGB[2];}\
  range = out[2] - min;\
  if(out[2] == 0.f){\
    out[1] = 0.f;\
  }else{\
    out[1] = range / out[2];\
  }\
  if(CMLAlmostZero(range)){\
    out[0] = 0.f;\
  }else{\
    float invrange = cmlInverse(range);\
    if(out[2] == RGB[0])      {out[0] = 60.f * (0.f + (RGB[1]-RGB[2]) * invrange);}\
    else if(out[2] == RGB[1]) {out[0] = 60.f * (2.f + (RGB[2]-RGB[0]) * invrange);}\
    else                      {out[0] = 60.f * (4.f + (RGB[0]-RGB[1]) * invrange);}\
    if(out[0] < 0.f){out[0] += 360.f;}\
  }



CMLHIDDEN CML_INLINE static void cmlInternalOneRGBtoHSV (float* CML_RESTRICT out , const float* CML_RESTRICT in){
  CMLINTERNALRGBtoHSV(out, in);
}

CMLHIDDEN CML_INLINE static void cmlInternalOneRGBtoHSV_SB(float* buf){
  CMLINTERNALRGBtoHSV(buf, buf);
}

CMLHIDDEN CML_INLINE static void cmlInternalRGBtoHSV (float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count){
  while(count){
    cmlInternalOneRGBtoHSV(out, in);
    out += CML_HSV_NUMCHANNELS;
    in += CML_RGB_NUMCHANNELS;
    count--;
  }
}

CMLHIDDEN CML_INLINE static void cmlInternalRGBtoHSV_SB(float* buf, CMLuint32 count){
  while(count){
    cmlInternalOneRGBtoHSV_SB(buf);
    buf += CML_HSV_NUMCHANNELS;
    count--;
  }
}





CMLHIDDEN CML_INLINE static CMLOutput cmlInternalConvertRGBtoHSV(CMLOutput out, CMLInput in, CMLSize count, const void* data){
  data = data; // no warnings
  out = cmlAllocateIfNull(out, count * sizeof(float) * CML_HSV_NUMCHANNELS);
  if(in == out){
    cmlInternalRGBtoHSV_SB(out, count);
  }else{
    cmlInternalRGBtoHSV(out, in, count);
  }
  return out;
}




CMLHIDDEN CML_INLINE static CMLConverter* cmlCreateRGBtoHSV(){
  return cmlCreateConverter(cmlInternalConvertRGBtoHSV, CML_NULL, CML_NULL, CML_NULL);
}


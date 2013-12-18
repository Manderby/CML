
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.


#define CMLINTERNALRGBtoYCbCr(out, in, redprimaryYxy, blueprimaryYxy, inversewhitepointXYZ) \
  float Kr = redprimaryYxy[0] * inversewhitepointXYZ[1];\
  float Kb = blueprimaryYxy[0] * inversewhitepointXYZ[1];\
  float Y = Kr * in[0] + (1.f - Kr - Kb) * in[1] + Kb * in[2];\
  out[1] = .5f * (in[2] - Y) / (1.f - Kb);\
  out[2] = .5f * (in[0] - Y) / (1.f - Kr);\
  out[0] = Y;



CMLHIDDEN CML_INLINE static void cmlInternalOneRGBtoYCbCr (float* CML_RESTRICT out , const float* CML_RESTRICT in, const CMLVec3 redprimaryYxy, const CMLVec3 blueprimaryYxy, const CMLVec3 inversewhitepointXYZ){
  CMLINTERNALRGBtoYCbCr(out, in, redprimaryYxy, blueprimaryYxy, inversewhitepointXYZ);
}
CMLHIDDEN CML_INLINE static void cmlInternalOneRGBtoYCbCr_SB (float* buf, const CMLVec3 redprimaryYxy, const CMLVec3 blueprimaryYxy, const CMLVec3 inversewhitepointXYZ){
  CMLINTERNALRGBtoYCbCr(buf, buf, redprimaryYxy, blueprimaryYxy, inversewhitepointXYZ);
}

CMLHIDDEN CML_INLINE static void cmlInternalRGBtoYCbCr (float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count, const CMLRGBSpace* rgbspace){

  const float* redprimaryYxy  = cmlGetRGBSpacePrimaryYxy(rgbspace, 0);
  const float* blueprimaryYxy = cmlGetRGBSpacePrimaryYxy(rgbspace, 2);
  const float* inversewhitepointXYZ = cmlGetWhitepointInverseXYZ(cmlGetRGBSpaceWhitepoint(rgbspace));

  while(count){
    cmlInternalOneRGBtoYCbCr(out, in, redprimaryYxy, blueprimaryYxy, inversewhitepointXYZ);
    out += CML_YCbCr_NUMCHANNELS;
    in += CML_RGB_NUMCHANNELS;
    count--;
  }
}

CMLHIDDEN CML_INLINE static void cmlInternalRGBtoYCbCr_SB (float* buf, CMLuint32 count, const CMLRGBSpace* rgbspace){

  const float* redprimaryYxy  = cmlGetRGBSpacePrimaryYxy(rgbspace, 0);
  const float* blueprimaryYxy = cmlGetRGBSpacePrimaryYxy(rgbspace, 2);
  const float* inversewhitepointXYZ = cmlGetWhitepointInverseXYZ(cmlGetRGBSpaceWhitepoint(rgbspace));

  while(count){
    cmlInternalOneRGBtoYCbCr_SB(buf, redprimaryYxy, blueprimaryYxy, inversewhitepointXYZ);
    buf += CML_YCbCr_NUMCHANNELS;
    count--;
  }
}




CMLHIDDEN CML_INLINE static void cmlInternalConstructRGBtoYCbCr(void** data, const void* input){
  *data = cmlRetainObject(input);
}


CMLHIDDEN CML_INLINE static CMLOutput cmlInternalConvertRGBtoYCbCr(CMLOutput out, CMLInput in, CMLSize count, const void* data){
  const CMLRGBSpace* rgbspace = (const CMLRGBSpace*)data;
  out = cmlAllocateIfNull(out, count * sizeof(float) * CML_YCbCr_NUMCHANNELS);
  if(in == out){
    cmlInternalRGBtoYCbCr_SB(out, count, rgbspace);
  }else{
    cmlInternalRGBtoYCbCr(out, in, count, rgbspace);
  }
  return out;
}


CMLHIDDEN CML_INLINE static void cmlInternalDestructRGBtoYCbCr(void* data){
  cmlReleaseObject(data);
}



CMLHIDDEN CML_INLINE static CMLConverter* cmlCreateRGBtoYCbCr(const CMLRGBSpace* rgbspace){
  return cmlCreateConverter(cmlInternalConvertRGBtoYCbCr, cmlInternalConstructRGBtoYCbCr, cmlInternalDestructRGBtoYCbCr, rgbspace);
}


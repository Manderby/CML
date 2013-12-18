
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.


#define CMLINTERNALYCbCrtoRGB(out, in, redprimaryYxy, blueprimaryYxy, inversewhitepointXYZ) \
  float Kr = redprimaryYxy[0] * inversewhitepointXYZ[1];\
  float Kb = blueprimaryYxy[0] * inversewhitepointXYZ[1];\
  float Y = in[0];\
  out[0] = 2.f * in[2] * (1.f - Kr) + Y;\
  out[2] = 2.f * in[1] * (1.f - Kb) + Y;\
  out[1] = (Y - Kr * out[0] - Kb * out[2]) / (1.f - Kr - Kb);



CMLHIDDEN CML_INLINE static void cmlInternalOneYCbCrtoRGB (float* CML_RESTRICT out , const float* CML_RESTRICT in, const CMLVec3 redprimaryYxy, const CMLVec3 blueprimaryYxy, const CMLVec3 inversewhitepointXYZ){
  CMLINTERNALYCbCrtoRGB(out, in, redprimaryYxy, blueprimaryYxy, inversewhitepointXYZ);
}
CMLHIDDEN CML_INLINE static void cmlInternalOneYCbCrtoRGB_SB (float* buf, const CMLVec3 redprimaryYxy, const CMLVec3 blueprimaryYxy, const CMLVec3 inversewhitepointXYZ){
  CMLINTERNALYCbCrtoRGB(buf, buf, redprimaryYxy, blueprimaryYxy, inversewhitepointXYZ);
}

CMLHIDDEN CML_INLINE static void cmlInternalYCbCrtoRGB (float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count, const CMLRGBSpace* rgbspace){

  const float* redprimaryYxy  = cmlGetRGBSpacePrimaryYxy(rgbspace, 0);
  const float* blueprimaryYxy = cmlGetRGBSpacePrimaryYxy(rgbspace, 2);
  const float* inversewhitepointXYZ = cmlGetWhitepointInverseXYZ(cmlGetRGBSpaceWhitepoint(rgbspace));

  while(count){
    cmlInternalOneYCbCrtoRGB(out, in, redprimaryYxy, blueprimaryYxy, inversewhitepointXYZ);
    out += CML_RGB_NUMCHANNELS;
    in += CML_YCbCr_NUMCHANNELS;
    count--;
  }
}

CMLHIDDEN CML_INLINE static void cmlInternalYCbCrtoRGB_SB (float* buf, CMLuint32 count, const CMLRGBSpace* rgbspace){

  const float* redprimaryYxy  = cmlGetRGBSpacePrimaryYxy(rgbspace, 0);
  const float* blueprimaryYxy = cmlGetRGBSpacePrimaryYxy(rgbspace, 2);
  const float* inversewhitepointXYZ = cmlGetWhitepointInverseXYZ(cmlGetRGBSpaceWhitepoint(rgbspace));

  while(count){
    cmlInternalOneYCbCrtoRGB_SB(buf, redprimaryYxy, blueprimaryYxy, inversewhitepointXYZ);
    buf += CML_RGB_NUMCHANNELS;
    count--;
  }
}




CMLHIDDEN CML_INLINE static void cmlInternalConstructYCbCrtoRGB(void** data, const void* input){
  *data = cmlRetainObject(input);
}


CMLHIDDEN CML_INLINE static CMLOutput cmlInternalConvertYCbCrtoRGB(CMLOutput out, CMLInput in, CMLSize count, const void* data){
  const CMLRGBSpace* rgbspace = (const CMLRGBSpace*)data;
  out = cmlAllocateIfNull(out, count * sizeof(float) * CML_RGB_NUMCHANNELS);
  if(in == out){
    cmlInternalYCbCrtoRGB_SB(out, count, rgbspace);
  }else{
    cmlInternalYCbCrtoRGB(out, in, count, rgbspace);
  }
  return out;
}


CMLHIDDEN CML_INLINE static void cmlInternalDestructYCbCrtoRGB(void* data){
  cmlReleaseObject(data);
}



CMLHIDDEN CML_INLINE static CMLConverter* cmlCreateYCbCrtoRGB(const CMLRGBSpace* rgbspace){
  return cmlCreateConverter(cmlInternalConvertYCbCrtoRGB, cmlInternalConstructYCbCrtoRGB, cmlInternalDestructYCbCrtoRGB, rgbspace);
}



// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.


#define CMLINTERNALXYZtoYxy(out, in, whitepointYxy) \
  float divisor;\
  divisor = (in[0] + in[1] + in[2]);\
  float Y = in[1];\
  if(divisor == 0.f){\
    if(whitepointYxy){\
      out[2] = whitepointYxy[2];\
      out[1] = whitepointYxy[1];\
    }else{\
      out[2] = 0.f;\
      out[1] = 0.f;\
    }\
  }else{\
    float factor = cmlInverse(divisor);\
    out[2] = in[1] * factor;\
    out[1] = in[0] * factor;\
  }\
  out[0] = Y;



CMLHIDDEN CML_INLINE static void cmlInternalOneXYZtoYxy (float* CML_RESTRICT out, const float* CML_RESTRICT in, const CMLVec3 whitepointYxy){
  CMLINTERNALXYZtoYxy(out, in, whitepointYxy);
}

CMLHIDDEN CML_INLINE static void cmlInternalOneXYZtoYxy_SB (float* CML_RESTRICT buf, const CMLVec3 whitepointYxy){
  CMLINTERNALXYZtoYxy(buf, buf, whitepointYxy);
}

CMLHIDDEN CML_INLINE static void cmlInternalXYZtoYxy (float* CML_RESTRICT out, const float* CML_RESTRICT in, CMLuint32 count, const CMLVec3 whitepointYxy){
  while(count){
    cmlInternalOneXYZtoYxy(out, in, whitepointYxy);
    out += CML_Yxy_NUMCHANNELS;
    in += CML_XYZ_NUMCHANNELS;
    count--;
  }
}

CMLHIDDEN CML_INLINE static void cmlInternalXYZtoYxy_SB (float* CML_RESTRICT buf, CMLuint32 count, const CMLVec3 whitepointYxy){
  while(count){
    cmlInternalOneXYZtoYxy_SB(buf, whitepointYxy);
    buf += CML_Yxy_NUMCHANNELS;
    count--;
  }
}




CMLHIDDEN CML_INLINE static void cmlInternalConstructXYZtoYxy(void** data, const void* input){
  *data = cmlRetainObject(input);
}


CMLHIDDEN CML_INLINE static CMLOutput cmlInternalConvertXYZtoYxy(CMLOutput out, CMLInput in, CMLSize count, const void* data){
  const CMLWhitepoint* whitepoint = (const CMLWhitepoint*)data;
  out = cmlAllocateIfNull(out, count * sizeof(float) * CML_Yxy_NUMCHANNELS);
  const float* whitepointYxy = cmlGetWhitepointYxy(whitepoint);
  if(in == out){
    if(whitepointYxy){
      cmlInternalXYZtoYxy_SB(out, count, whitepointYxy);
    }else{
      cmlInternalXYZtoYxy_SB(out, count, CML_NULL);
    }
  }else{
    if(whitepointYxy){
      cmlInternalXYZtoYxy(out, in, count, whitepointYxy);
    }else{
      cmlInternalXYZtoYxy(out, in, count, CML_NULL);
    }
  }
  return out;
}


CMLHIDDEN CML_INLINE static void cmlInternalDestructXYZtoYxy(void* data){
  cmlReleaseObject(data);
}



CMLHIDDEN CML_INLINE static CMLConverter* cmlCreateXYZtoYxy(const CMLWhitepoint* whitepoint){
  return cmlCreateConverter(cmlInternalConvertXYZtoYxy, cmlInternalConstructXYZtoYxy, cmlInternalDestructXYZtoYxy, whitepoint);
}


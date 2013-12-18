
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.


#define CMLINTERNALYupvptoYxy(out, in, whitepointYxy) \
  float divisor;\
  out[0] = in[0];\
  divisor = 6.f * in[1] - 16.f * in[2] + 12.f;\
  if(divisor == 0.f){\
    if(whitepointYxy){\
      out[1] = whitepointYxy[1];\
      out[2] = whitepointYxy[2];\
    }else{\
      out[1] = 0.f;\
      out[2] = 0.f;\
    }\
  }else{\
    float factor = cmlInverse(divisor);\
    out[1] = 9.f * in[1] * factor;\
    out[2] = 4.f * in[2] * factor;\
  }



CMLHIDDEN CML_INLINE static void cmlInternalOneYupvptoYxy (float* CML_RESTRICT out , const float* CML_RESTRICT in, const CMLVec3 whitepointYxy){
  CMLINTERNALYupvptoYxy(out, in, whitepointYxy);
}

CMLHIDDEN CML_INLINE static void cmlInternalOneYupvptoYxy_SB(float* buf, const CMLVec3 whitepointYxy){
  CMLINTERNALYupvptoYxy(buf, buf, whitepointYxy);
}

CMLHIDDEN CML_INLINE static void cmlInternalYupvptoYxy (float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count, const CMLVec3 whitepointYxy){
  while(count){
    cmlInternalOneYupvptoYxy(out, in, whitepointYxy);
    out += CML_Yxy_NUMCHANNELS;
    in += CML_Yupvp_NUMCHANNELS;
    count--;
  }
}

CMLHIDDEN CML_INLINE static void cmlInternalYupvptoYxy_SB(float* buf, CMLuint32 count, const CMLVec3 whitepointYxy){
  while(count){
    cmlInternalOneYupvptoYxy_SB(buf, whitepointYxy);
    buf += CML_Yxy_NUMCHANNELS;
    count--;
  }
}




CMLHIDDEN CML_INLINE static void cmlInternalConstructYupvptoYxy(void** data, const void* input){
  *data = cmlRetainObject(input);
}


CMLHIDDEN CML_INLINE static CMLOutput cmlInternalConvertYupvptoYxy(CMLOutput out, CMLInput in, CMLSize count, const void* data){
  const CMLWhitepoint* whitepoint = (const CMLWhitepoint*)data;
  out = cmlAllocateIfNull(out, count * sizeof(float) * CML_Yxy_NUMCHANNELS);
  const float* whitepointYxy = cmlGetWhitepointYxy(whitepoint);
  if(in == out){
    if(whitepointYxy){
      cmlInternalYupvptoYxy_SB(out, count, whitepointYxy);
    }else{
      cmlInternalYupvptoYxy_SB(out, count, CML_NULL);
    }
  }else{
    if(whitepointYxy){
      cmlInternalYupvptoYxy(out, in, count, whitepointYxy);
    }else{
      cmlInternalYupvptoYxy(out, in, count, CML_NULL);
    }
  }
  return out;
}


CMLHIDDEN CML_INLINE static void cmlInternalDestructYupvptoYxy(void* data){
  cmlReleaseObject(data);
}



CMLHIDDEN CML_INLINE static CMLConverter* cmlCreateYupvptoYxy(const CMLWhitepoint* whitepoint){
  return cmlCreateConverter(cmlInternalConvertYupvptoYxy, cmlInternalConstructYupvptoYxy, cmlInternalDestructYupvptoYxy, whitepoint);
}


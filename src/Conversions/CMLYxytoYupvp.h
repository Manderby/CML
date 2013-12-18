
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.


#define CMLINTERNALYxytoYupvp(out, in, whitepointYupvp) \
  float divisor;\
  out[0] = in[0];\
  divisor = -2.f * in[1] + 12.f * in[2] + 3.f;\
  if(divisor == 0.f){\
    if(whitepointYupvp){\
      out[1] = whitepointYupvp[1];\
      out[2] = whitepointYupvp[2];\
    }else{\
      out[1] = 0.f;\
      out[2] = 0.f;\
    }\
  }else{\
    float factor = cmlInverse(divisor);\
    out[1] = 4.f * in[1] * factor;\
    out[2] = 9.f * in[2] * factor;\
  }\



CMLHIDDEN CML_INLINE static void cmlInternalOneYxytoYupvp (float* CML_RESTRICT out , const float* CML_RESTRICT in, const CMLVec3 whitepointYupvp){
  CMLINTERNALYxytoYupvp(out, in, whitepointYupvp);
}

CMLHIDDEN CML_INLINE static void cmlInternalOneYxytoYupvp_SB(float* buf, const CMLVec3 whitepointYupvp){
  CMLINTERNALYxytoYupvp(buf, buf, whitepointYupvp);
}

CMLHIDDEN CML_INLINE static void cmlInternalYxytoYupvp (float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count, const CMLVec3 whitepointYupvp){
  while(count){
    cmlInternalOneYxytoYupvp(out, in, whitepointYupvp);
    out += CML_Yupvp_NUMCHANNELS;
    in += CML_Yxy_NUMCHANNELS;
    count--;
  }
}

CMLHIDDEN CML_INLINE static void cmlInternalYxytoYupvp_SB(float* buf, CMLuint32 count, const CMLVec3 whitepointYupvp){
  while(count){
    cmlInternalOneYxytoYupvp_SB(buf, whitepointYupvp);
    buf += CML_Yupvp_NUMCHANNELS;
    count--;
  }
}




CMLHIDDEN CML_INLINE static void cmlInternalConstructYxytoYupvp(void** data, const void* input){
  *data = cmlRetainObject(input);
}


CMLHIDDEN CML_INLINE static CMLOutput cmlInternalConvertYxytoYupvp(CMLOutput out, CMLInput in, CMLSize count, const void* data){
  const CMLWhitepoint* whitepoint = (const CMLWhitepoint*)data;
  out = cmlAllocateIfNull(out, count * sizeof(float) * CML_Yupvp_NUMCHANNELS);
  const float* whitepointYupvp = cmlGetWhitepointYupvp(whitepoint);
  if(in == out){
    if(whitepointYupvp){
      cmlInternalYxytoYupvp_SB(out, count, whitepointYupvp);
    }else{
      cmlInternalYxytoYupvp_SB(out, count, CML_NULL);
    }
  }else{
    if(whitepointYupvp){
      cmlInternalYxytoYupvp(out, in, count, whitepointYupvp);
    }else{
      cmlInternalYxytoYupvp(out, in, count, CML_NULL);
    }
  }
  return out;
}


CMLHIDDEN CML_INLINE static void cmlInternalDestructYxytoYupvp(void* data){
  cmlReleaseObject(data);
}



CMLHIDDEN CML_INLINE static CMLConverter* cmlCreateYxytoYupvp(const CMLWhitepoint* whitepoint){
  return cmlCreateConverter(cmlInternalConvertYxytoYupvp, cmlInternalConstructYxytoYupvp, cmlInternalDestructYxytoYupvp, whitepoint);
}


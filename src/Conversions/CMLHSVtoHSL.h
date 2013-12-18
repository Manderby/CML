
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.


#define CMLINTERNALHSVtoHSL(out, in) \
  out[0] = in[0];\
  out[1] = in[1] * in[2];\
  out[2] = in[2] - 0.5f * out[1];



CMLHIDDEN CML_INLINE static void cmlInternalOneHSVtoHSL (float* CML_RESTRICT out , const float* CML_RESTRICT in){
  CMLINTERNALHSVtoHSL(out, in);
}

CMLHIDDEN CML_INLINE static void cmlInternalOneHSVtoHSL_SB(float* buf){
  CMLINTERNALHSVtoHSL(buf, buf);
}

CMLHIDDEN CML_INLINE static void cmlInternalHSVtoHSL (float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count){
  while(count){
    cmlInternalOneHSVtoHSL(out, in);
    out += CML_HSL_NUMCHANNELS;
    in += CML_HSV_NUMCHANNELS;
    count--;
  }
}

CMLHIDDEN CML_INLINE static void cmlInternalHSVtoHSL_SB(float* buf, CMLuint32 count){
  while(count){
    cmlInternalOneHSVtoHSL_SB(buf);
    buf += CML_HSL_NUMCHANNELS;
    count--;
  }
}





CMLHIDDEN CML_INLINE static CMLOutput cmlInternalConvertHSVtoHSL(CMLOutput out, CMLInput in, CMLSize count, const void* data){
  data = data; // no warnings
  out = cmlAllocateIfNull(out, count * sizeof(float) * CML_HSL_NUMCHANNELS);
  if(in == out){
    cmlInternalHSVtoHSL_SB(out, count);
  }else{
    cmlInternalHSVtoHSL(out, in, count);
  }
  return out;
}




CMLHIDDEN CML_INLINE static CMLConverter* cmlCreateHSVtoHSL(){
  return cmlCreateConverter(cmlInternalConvertHSVtoHSL, CML_NULL, CML_NULL, CML_NULL);
}


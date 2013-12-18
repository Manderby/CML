
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.


#define CMLINTERNALHSLtoHSV(out, in) \
  out[0] = in[0];\
  out[2] = in[2] + .5f * in[1];\
  if(out[2] == 0.f){\
    out[1] = in[1] / CML_SINGULARITY;\
  }else{\
    out[1] = in[1] / out[2];\
  }



CMLHIDDEN CML_INLINE static void cmlInternalOneHSLtoHSV (float* CML_RESTRICT out , const float* CML_RESTRICT in){
  CMLINTERNALHSLtoHSV(out, in);
}

CMLHIDDEN CML_INLINE static void cmlInternalOneHSLtoHSV_SB(float* buf){
  CMLINTERNALHSLtoHSV(buf, buf);
}

CMLHIDDEN CML_INLINE static void cmlInternalHSLtoHSV (float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count){
  while(count){
    cmlInternalOneHSLtoHSV(out, in);
    out += CML_HSV_NUMCHANNELS;
    in += CML_HSL_NUMCHANNELS;
    count--;
  }
}

CMLHIDDEN CML_INLINE static void cmlInternalHSLtoHSV_SB(float* buf, CMLuint32 count){
  while(count){
    cmlInternalOneHSLtoHSV_SB(buf);
    buf += CML_HSV_NUMCHANNELS;
    count--;
  }
}





CMLHIDDEN CML_INLINE static CMLOutput cmlInternalConvertHSLtoHSV(CMLOutput out, CMLInput in, CMLSize count, const void* data){
  data = data; // no warnings
  out = cmlAllocateIfNull(out, count * sizeof(float) * CML_HSV_NUMCHANNELS);
  if(in == out){
    cmlInternalHSLtoHSV_SB(out, count);
  }else{
    cmlInternalHSLtoHSV(out, in, count);
  }
  return out;
}




CMLHIDDEN CML_INLINE static CMLConverter* cmlCreateHSLtoHSV(){
  return cmlCreateConverter(cmlInternalConvertHSLtoHSV, CML_NULL, CML_NULL, CML_NULL);
}


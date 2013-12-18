
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.


#define CMLINTERNALYupvptoYuv(out, in) \
  out[0] = in[0];\
  out[1] = in[1];\
  out[2] = in[2] * 0.666666666666667f;



CMLHIDDEN CML_INLINE static void cmlInternalOneYupvptoYuv (float* CML_RESTRICT out , const float* CML_RESTRICT in){
  CMLINTERNALYupvptoYuv(out, in);
}

CMLHIDDEN CML_INLINE static void cmlInternalOneYupvptoYuv_SB(float* buf){
  CMLINTERNALYupvptoYuv(buf, buf);
}

CMLHIDDEN CML_INLINE static void cmlInternalYupvptoYuv (float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count){
  while(count){
    cmlInternalOneYupvptoYuv(out, in);
    out += CML_Yuv_NUMCHANNELS;
    in += CML_Yupvp_NUMCHANNELS;
    count--;
  }
}

CMLHIDDEN CML_INLINE static void cmlInternalYupvptoYuv_SB(float* buf, CMLuint32 count){
  while(count){
    cmlInternalOneYupvptoYuv_SB(buf);
    buf += CML_Yuv_NUMCHANNELS;
    count--;
  }
}





CMLHIDDEN CML_INLINE static CMLOutput cmlInternalConvertYupvptoYuv(CMLOutput out, CMLInput in, CMLSize count, const void* data){
  data = data; // no warnings
  out = cmlAllocateIfNull(out, count * sizeof(float) * CML_Yuv_NUMCHANNELS);
  if(in == out){
    cmlInternalYupvptoYuv_SB(out, count);
  }else{
    cmlInternalYupvptoYuv(out, in, count);
  }
  return out;
}




CMLHIDDEN CML_INLINE static CMLConverter* cmlCreateYupvptoYuv(){
  return cmlCreateConverter(cmlInternalConvertYupvptoYuv, CML_NULL, CML_NULL, CML_NULL);
}


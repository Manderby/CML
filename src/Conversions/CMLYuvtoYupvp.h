
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.


#define CMLINTERNALYuvtoYupvp(out, in) \
  out[0] = in[0];\
  out[1] = in[1];\
  out[2] = in[2] * 1.5f;



CMLHIDDEN CML_INLINE static void cmlInternalOneYuvtoYupvp (float* CML_RESTRICT out , const float* CML_RESTRICT in){
  CMLINTERNALYuvtoYupvp(out, in);
}

CMLHIDDEN CML_INLINE static void cmlInternalOneYuvtoYupvp_SB(float* buf){
  CMLINTERNALYuvtoYupvp(buf, buf);
}

CMLHIDDEN CML_INLINE static void cmlInternalYuvtoYupvp (float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count){
  while(count){
    cmlInternalOneYuvtoYupvp(out, in);
    out += CML_Yupvp_NUMCHANNELS;
    in += CML_Yuv_NUMCHANNELS;
    count--;
  }
}

CMLHIDDEN CML_INLINE static void cmlInternalYuvtoYupvp_SB(float* buf, CMLuint32 count){
  while(count){
    cmlInternalOneYuvtoYupvp_SB(buf);
    buf += CML_Yupvp_NUMCHANNELS;
    count--;
  }
}





CMLHIDDEN CML_INLINE static CMLOutput cmlInternalConvertYuvtoYupvp(CMLOutput out, CMLInput in, CMLSize count, const void* data){
  data = data; // no warnings
  out = cmlAllocateIfNull(out, count * sizeof(float) * CML_Yupvp_NUMCHANNELS);
  if(in == out){
    cmlInternalYuvtoYupvp_SB(out, count);
  }else{
    cmlInternalYuvtoYupvp(out, in, count);
  }
  return out;
}




CMLHIDDEN CML_INLINE static CMLConverter* cmlCreateYuvtoYupvp(){
  return cmlCreateConverter(cmlInternalConvertYuvtoYupvp, CML_NULL, CML_NULL, CML_NULL);
}


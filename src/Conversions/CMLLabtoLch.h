
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.


#define CMLINTERNALLabtoLch(out, in) \
  out[0] = in[0];\
  float length = cmlLength2(&(in[1]));\
  if(length == 0.f){\
    out[2] = 0.f;\
  }else{\
    out[2] = CMLRadtoDeg(atan2f(in[2], in[1]));\
    if(out[2] < 0.f){out[2] += 360.f;}\
  }\
  out[1] = length;



CMLHIDDEN CML_INLINE static void cmlInternalOneLabtoLch (float* CML_RESTRICT out , const float* CML_RESTRICT in){
  CMLINTERNALLabtoLch(out, in);
}

CMLHIDDEN CML_INLINE static void cmlInternalOneLabtoLch_SB(float* buf){
  CMLINTERNALLabtoLch(buf, buf);
}

CMLHIDDEN CML_INLINE static void cmlInternalLabtoLch (float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count){
  while(count){
    cmlInternalOneLabtoLch(out, in);
    out += CML_Lch_NUMCHANNELS;
    in += CML_Lab_NUMCHANNELS;
    count--;
  }
}

CMLHIDDEN CML_INLINE static void cmlInternalLabtoLch_SB(float* buf, CMLuint32 count){
  while(count){
    cmlInternalOneLabtoLch_SB(buf);
    buf += CML_Lch_NUMCHANNELS;
    count--;
  }
}





CMLHIDDEN CML_INLINE static CMLOutput cmlInternalConvertLabtoLch(CMLOutput out, CMLInput in, CMLSize count, const void* data){
  data = data; // no warnings
  out = cmlAllocateIfNull(out, count * sizeof(float) * CML_Lch_NUMCHANNELS);
  if(in == out){
    cmlInternalLabtoLch_SB(out, count);
  }else{
    cmlInternalLabtoLch(out, in, count);
  }
  return out;
}




CMLHIDDEN CML_INLINE static CMLConverter* cmlCreateLabtoLch(){
  return cmlCreateConverter(cmlInternalConvertLabtoLch, CML_NULL, CML_NULL, CML_NULL);
}


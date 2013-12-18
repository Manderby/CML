
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.


#define CMLINTERNALLchtoLab(out, in) \
  if(in[1] == 0.f){\
    out[2] = 0.f;\
    out[1] = 0.f;\
  }else{\
    float hue = CMLDegtoRad(in[2]);\
    out[2] = sinf(hue) * in[1];\
    out[1] = cosf(hue) * in[1];\
  }\
  out[0] = in[0];



CMLHIDDEN CML_INLINE static void cmlInternalOneLchtoLab (float* CML_RESTRICT out , const float* CML_RESTRICT in){
  CMLINTERNALLchtoLab(out, in);
}

CMLHIDDEN CML_INLINE static void cmlInternalOneLchtoLab_SB(float* buf){
  CMLINTERNALLchtoLab(buf, buf);
}

CMLHIDDEN CML_INLINE static void cmlInternalLchtoLab (float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count){
  while(count){
    cmlInternalOneLchtoLab(out, in);
    out += CML_Lab_NUMCHANNELS;
    in += CML_Lch_NUMCHANNELS;
    count--;
  }
}

CMLHIDDEN CML_INLINE static void cmlInternalLchtoLab_SB(float* buf, CMLuint32 count){
  while(count){
    cmlInternalOneLchtoLab_SB(buf);
    buf += CML_Lab_NUMCHANNELS;
    count--;
  }
}





CMLHIDDEN CML_INLINE static CMLOutput cmlInternalConvertLchtoLab(CMLOutput out, CMLInput in, CMLSize count, const void* data){
  data = data; // no warnings
  out = cmlAllocateIfNull(out, count * sizeof(float) * CML_Lab_NUMCHANNELS);
  if(in == out){
    cmlInternalLchtoLab_SB(out, count);
  }else{
    cmlInternalLchtoLab(out, in, count);
  }
  return out;
}




CMLHIDDEN CML_INLINE static CMLConverter* cmlCreateLchtoLab(){
  return cmlCreateConverter(cmlInternalConvertLchtoLab, CML_NULL, CML_NULL, CML_NULL);
}


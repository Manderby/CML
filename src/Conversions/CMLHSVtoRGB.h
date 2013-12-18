
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.


// todo: Make it SB
#define CMLINTERNALHSVtoRGB(out, in) \
  CMLVec3 HSV;\
  cmlCpy3(HSV, in);\
  CMLint8 h0 = (CMLint8)floorf(HSV[0] / 60.f);\
  CMLuint8 h1 = (CMLuint8)((h0 % 6) + 6) % 6;\
  float f = (HSV[0] / 60.f) - h0;\
  float range = HSV[2] * HSV[1];\
  float min = HSV[2] - range;\
  float inc = f * range;\
  float dec = (1.f - f) * range;\
  inc += min;\
  dec += min;\
  switch(h1){\
  case 0: out[0] = HSV[2] ; out[1] = inc    ; out[2] = min    ; break;\
  case 1: out[0] = dec    ; out[1] = HSV[2] ; out[2] = min    ; break;\
  case 2: out[0] = min    ; out[1] = HSV[2] ; out[2] = inc    ; break;\
  case 3: out[0] = min    ; out[1] = dec    ; out[2] = HSV[2] ; break;\
  case 4: out[0] = inc    ; out[1] = min    ; out[2] = HSV[2] ; break;\
  case 5: out[0] = HSV[2] ; out[1] = min    ; out[2] = dec    ; break;\
  default:\
    out[0] = 0.f; out[1] = 0.f; out[2] = 0.f;\
  }



CMLHIDDEN CML_INLINE static void cmlInternalOneHSVtoRGB (float* CML_RESTRICT out , const float* CML_RESTRICT in){
  CMLINTERNALHSVtoRGB(out, in);
}

CMLHIDDEN CML_INLINE static void cmlInternalOneHSVtoRGB_SB(float* buf){
  CMLINTERNALHSVtoRGB(buf, buf);
}

CMLHIDDEN CML_INLINE static void cmlInternalHSVtoRGB (float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count){
  while(count){
    cmlInternalOneHSVtoRGB(out, in);
    out += CML_RGB_NUMCHANNELS;
    in += CML_HSV_NUMCHANNELS;
    count--;
  }
}

CMLHIDDEN CML_INLINE static void cmlInternalHSVtoRGB_SB(float* buf, CMLuint32 count){
  while(count){
    cmlInternalOneHSVtoRGB_SB(buf);
    buf += CML_RGB_NUMCHANNELS;
    count--;
  }
}





CMLHIDDEN CML_INLINE static CMLOutput cmlInternalConvertHSVtoRGB(CMLOutput out, CMLInput in, CMLSize count, const void* data){
  data = data; // no warnings
  out = cmlAllocateIfNull(out, count * sizeof(float) * CML_RGB_NUMCHANNELS);
  if(in == out){
    cmlInternalHSVtoRGB_SB(out, count);
  }else{
    cmlInternalHSVtoRGB(out, in, count);
  }
  return out;
}




CMLHIDDEN CML_INLINE static CMLConverter* cmlCreateHSVtoRGB(){
  return cmlCreateConverter(cmlInternalConvertHSVtoRGB, CML_NULL, CML_NULL, CML_NULL);
}



// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.


#define CMLINTERNALYupvptoLuv(out, in, whitepointYupvp, LineartoLResponse) \
  float yr = in[0] / whitepointYupvp[0];\
  float fy = cmlInternalEval(LineartoLResponse, yr);\
  out[0] = 100.f * fy;\
  out[1] = 13.f * out[0] * (in[1] - whitepointYupvp[1]);\
  out[2] = 13.f * out[0] * (in[2] - whitepointYupvp[2]);



CMLHIDDEN CML_INLINE static void cmlInternalOneYupvptoLuv (float* CML_RESTRICT out , const float* CML_RESTRICT in, const CMLVec3 whitepointYupvp, const CMLFunction* LineartoLResponse){
  CMLINTERNALYupvptoLuv(out, in, whitepointYupvp, LineartoLResponse);
}

CMLHIDDEN CML_INLINE static void cmlInternalOneYupvptoLuv_SB(float* buf, const CMLVec3 whitepointYupvp, const CMLFunction* LineartoLResponse){
  CMLINTERNALYupvptoLuv(buf, buf, whitepointYupvp, LineartoLResponse);
}

CMLHIDDEN CML_INLINE static void cmlInternalYupvptoLuv (float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count, const CMLVec3 whitepointYupvp, const CMLFunction* LineartoLResponse){
  while(count){
    cmlInternalOneYupvptoLuv(out, in, whitepointYupvp, LineartoLResponse);
    out += CML_Luv_NUMCHANNELS;
    in += CML_Yupvp_NUMCHANNELS;
    count--;
  }
}

CMLHIDDEN CML_INLINE static void cmlInternalYupvptoLuv_SB(float* buf, CMLuint32 count, const CMLVec3 whitepointYupvp, const CMLFunction* LineartoLResponse){
  while(count){
    cmlInternalOneYupvptoLuv_SB(buf, whitepointYupvp, LineartoLResponse);
    buf += CML_Luv_NUMCHANNELS;
    count--;
  }
}




CMLHIDDEN CML_INLINE static void cmlInternalConstructYupvptoLuv(void** data, const void* input){
  *data = cmlRetainObject(input);
}


CMLHIDDEN CML_INLINE static CMLOutput cmlInternalConvertYupvptoLuv(CMLOutput out, CMLInput in, CMLSize count, const void* data){
  const CMLLabSpace* labspace = (const CMLLabSpace*)data;
  out = cmlAllocateIfNull(out, count * sizeof(float) * CML_Luv_NUMCHANNELS);
  const float* whitepointYupvp = cmlGetWhitepointYupvp(cmlGetLabSpaceWhitepoint(labspace));
  const CMLFunction* LineartoLResponse = cmlGetResponseCurveForwardFunc(cmlGetLabSpaceResponseCurve(labspace));
  if(in == out){
    cmlInternalYupvptoLuv_SB(out, count, whitepointYupvp, LineartoLResponse);
  }else{
    cmlInternalYupvptoLuv(out, in, count, whitepointYupvp, LineartoLResponse);
  }
  return out;
}


CMLHIDDEN CML_INLINE static void cmlInternalDestructYupvptoLuv(void* data){
  cmlReleaseObject(data);
}



CMLHIDDEN CML_INLINE static CMLConverter* cmlCreateYupvptoLuv(const CMLLabSpace* labspace){
  return cmlCreateConverter(cmlInternalConvertYupvptoLuv, cmlInternalConstructYupvptoLuv, cmlInternalDestructYupvptoLuv, labspace);
}


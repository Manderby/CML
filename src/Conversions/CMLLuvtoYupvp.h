
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.


#define CMLINTERNALLuvtoYupvp(out, in, whitepointYupvp, LtoLinearResponse) \
  float divisor;\
  float yr;\
  yr = cmlInternalEval(LtoLinearResponse, in[0] * .01f);\
  divisor = 13.f * in[0];\
  out[0] = yr * whitepointYupvp[0];\
  if(divisor == 0.f){\
    out[1] = whitepointYupvp[1];\
    out[2] = whitepointYupvp[2];\
  }else{\
    float factor = cmlInverse(divisor);\
    out[1] = (in[1] * factor) + whitepointYupvp[1];\
    out[2] = (in[2] * factor) + whitepointYupvp[2];\
  }



CMLHIDDEN CML_INLINE static void cmlInternalOneLuvtoYupvp (float* CML_RESTRICT out , const float* CML_RESTRICT in, const CMLVec3 whitepointYupvp, const CMLFunction* LtoLinearResponse){
  CMLINTERNALLuvtoYupvp(out, in, whitepointYupvp, LtoLinearResponse);
}

CMLHIDDEN CML_INLINE static void cmlInternalOneLuvtoYupvp_SB(float* buf, const CMLVec3 whitepointYupvp, const CMLFunction* LtoLinearResponse){
  CMLINTERNALLuvtoYupvp(buf, buf, whitepointYupvp, LtoLinearResponse);
}

CMLHIDDEN CML_INLINE static void cmlInternalLuvtoYupvp (float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count, const CMLVec3 whitepointYupvp, const CMLFunction* LtoLinearResponse){
  while(count){
    cmlInternalOneLuvtoYupvp(out, in, whitepointYupvp, LtoLinearResponse);
    out += CML_Yupvp_NUMCHANNELS;
    in += CML_Luv_NUMCHANNELS;
    count--;
  }
}

CMLHIDDEN CML_INLINE static void cmlInternalLuvtoYupvp_SB(float* buf, CMLuint32 count, const CMLVec3 whitepointYupvp, const CMLFunction* LtoLinearResponse){
  while(count){
    cmlInternalOneLuvtoYupvp_SB(buf, whitepointYupvp, LtoLinearResponse);
    buf += CML_Yupvp_NUMCHANNELS;
    count--;
  }
}




CMLHIDDEN CML_INLINE static void cmlInternalConstructLuvtoYupvp(void** data, const void* input){
  *data = cmlRetainObject(input);
}


CMLHIDDEN CML_INLINE static CMLOutput cmlInternalConvertLuvtoYupvp(CMLOutput out, CMLInput in, CMLSize count, const void* data){
  const CMLLabSpace* labspace = (const CMLLabSpace*)data;
  out = cmlAllocateIfNull(out, count * sizeof(float) * CML_Yupvp_NUMCHANNELS);
  const float* whitepointYupvp = cmlGetWhitepointYupvp(cmlGetLabSpaceWhitepoint(labspace));
  const CMLFunction* LtoLinearResponse = cmlGetResponseCurveBackwardFunc(cmlGetLabSpaceResponseCurve(labspace));
  if(in == out){
    cmlInternalLuvtoYupvp_SB(out, count, whitepointYupvp, LtoLinearResponse);
  }else{
    cmlInternalLuvtoYupvp(out, in, count, whitepointYupvp, LtoLinearResponse);
  }
  return out;
}


CMLHIDDEN CML_INLINE static void cmlInternalDestructLuvtoYupvp(void* data){
  cmlReleaseObject(data);
}



CMLHIDDEN CML_INLINE static CMLConverter* cmlCreateLuvtoYupvp(const CMLLabSpace* labspace){
  return cmlCreateConverter(cmlInternalConvertLuvtoYupvp, cmlInternalConstructLuvtoYupvp, cmlInternalDestructLuvtoYupvp, labspace);
}


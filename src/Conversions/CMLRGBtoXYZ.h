
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.


// todo: make mulVec SB
#define CMLINTERNALRGBtoXYZ(out, in, RGBtoXYZmatrix, RtoLinearResponse, GtoLinearResponse, BtoLinearResponse) \
  float RGBp[3];\
  RGBp[0] = cmlInternalEval(RtoLinearResponse, in[0]);\
  RGBp[1] = cmlInternalEval(GtoLinearResponse, in[1]);\
  RGBp[2] = cmlInternalEval(BtoLinearResponse, in[2]);\
  cmlMat33MulVec3(out, RGBtoXYZmatrix, RGBp);



CMLHIDDEN CML_INLINE static void cmlInternalOneRGBtoXYZ (float* CML_RESTRICT out , const float* CML_RESTRICT in, const CMLMat33 RGBtoXYZmatrix, const CMLFunction* RtoLinearResponse, const CMLFunction* GtoLinearResponse, const CMLFunction* BtoLinearResponse){
  CMLINTERNALRGBtoXYZ(out, in, RGBtoXYZmatrix, RtoLinearResponse, GtoLinearResponse, BtoLinearResponse);
}
CMLHIDDEN CML_INLINE static void cmlInternalOneRGBtoXYZ_SB (float* buf, const CMLMat33 RGBtoXYZmatrix, const CMLFunction* RtoLinearResponse, const CMLFunction* GtoLinearResponse, const CMLFunction* BtoLinearResponse){
  CMLINTERNALRGBtoXYZ(buf, buf, RGBtoXYZmatrix, RtoLinearResponse, GtoLinearResponse, BtoLinearResponse);
}

CMLHIDDEN CML_INLINE static void cmlInternalRGBtoXYZ (float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count, const CMLRGBSpace* rgbspace){

  const float* RGBtoXYZmatrix = cmlGetRGBSpaceInverseMatrix(rgbspace);
  const CMLFunction* RtoLinearResponse = cmlGetResponseCurveForwardFunc(cmlGetRGBSpaceResponseCurve(rgbspace, 0));
  const CMLFunction* GtoLinearResponse = cmlGetResponseCurveForwardFunc(cmlGetRGBSpaceResponseCurve(rgbspace, 1));
  const CMLFunction* BtoLinearResponse = cmlGetResponseCurveForwardFunc(cmlGetRGBSpaceResponseCurve(rgbspace, 2));

  while(count){
    cmlInternalOneRGBtoXYZ(out, in, RGBtoXYZmatrix, RtoLinearResponse, GtoLinearResponse, BtoLinearResponse);
    out += CML_XYZ_NUMCHANNELS;
    in += CML_RGB_NUMCHANNELS;
    count--;
  }
}

CMLHIDDEN CML_INLINE static void cmlInternalRGBtoXYZ_SB (float* buf, CMLuint32 count, const CMLRGBSpace* rgbspace){

  const float* RGBtoXYZmatrix = cmlGetRGBSpaceInverseMatrix(rgbspace);
  const CMLFunction* RtoLinearResponse = cmlGetResponseCurveForwardFunc(cmlGetRGBSpaceResponseCurve(rgbspace, 0));
  const CMLFunction* GtoLinearResponse = cmlGetResponseCurveForwardFunc(cmlGetRGBSpaceResponseCurve(rgbspace, 1));
  const CMLFunction* BtoLinearResponse = cmlGetResponseCurveForwardFunc(cmlGetRGBSpaceResponseCurve(rgbspace, 2));

  while(count){
    cmlInternalOneRGBtoXYZ_SB(buf, RGBtoXYZmatrix, RtoLinearResponse, GtoLinearResponse, BtoLinearResponse);
    buf += CML_XYZ_NUMCHANNELS;
    count--;
  }
}




CMLHIDDEN CML_INLINE static void cmlInternalConstructRGBtoXYZ(void** data, const void* input){
  *data = cmlRetainObject(input);
}


CMLHIDDEN CML_INLINE static CMLOutput cmlInternalConvertRGBtoXYZ(CMLOutput out, CMLInput in, CMLSize count, const void* data){
  const CMLRGBSpace* rgbspace = (const CMLRGBSpace*)data;
  out = cmlAllocateIfNull(out, count * sizeof(float) * CML_XYZ_NUMCHANNELS);
  if(in == out){
    cmlInternalRGBtoXYZ_SB(out, count, rgbspace);
  }else{
    cmlInternalRGBtoXYZ(out, in, count, rgbspace);
  }
  return out;
}


CMLHIDDEN CML_INLINE static void cmlInternalDestructRGBtoXYZ(void* data){
  cmlReleaseObject(data);
}



CMLHIDDEN CML_INLINE static CMLConverter* cmlCreateRGBtoXYZ(const CMLRGBSpace* rgbspace){
  return cmlCreateConverter(cmlInternalConvertRGBtoXYZ, cmlInternalConstructRGBtoXYZ, cmlInternalDestructRGBtoXYZ, rgbspace);
}


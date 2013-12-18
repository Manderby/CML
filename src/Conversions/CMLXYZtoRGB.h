
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.


// todo: make mulVec SB
#define CMLINTERNALXYZtoRGB(out, in, XYZtoRGBmatrix, LineartoRResponse, LineartoGResponse, LineartoBResponse) \
  CMLVec3 RGBp;\
  cmlMat33MulVec3(RGBp, XYZtoRGBmatrix, in);\
  out[0] = cmlInternalEval(LineartoRResponse, RGBp[0]);\
  out[1] = cmlInternalEval(LineartoGResponse, RGBp[1]);\
  out[2] = cmlInternalEval(LineartoBResponse, RGBp[2]);



CMLHIDDEN CML_INLINE static void cmlInternalOneXYZtoRGB (float* CML_RESTRICT out , const float* CML_RESTRICT in, const CMLMat33 XYZtoRGBmatrix, const CMLFunction* LineartoRResponse, const CMLFunction* LineartoGResponse, const CMLFunction* LineartoBResponse){
  CMLINTERNALXYZtoRGB(out, in, XYZtoRGBmatrix, LineartoRResponse, LineartoGResponse, LineartoBResponse);
}

CMLHIDDEN CML_INLINE static void cmlInternalOneXYZtoRGB_SB (float* buf, const CMLMat33 XYZtoRGBmatrix, const CMLFunction* LineartoRResponse, const CMLFunction* LineartoGResponse, const CMLFunction* LineartoBResponse){
  CMLINTERNALXYZtoRGB(buf, buf, XYZtoRGBmatrix, LineartoRResponse, LineartoGResponse, LineartoBResponse);
}

CMLHIDDEN CML_INLINE static void cmlInternalXYZtoRGB (float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count, const CMLRGBSpace* rgbspace){

  const float* XYZtoRGBmatrix = cmlGetRGBSpaceInverseMatrix(rgbspace);
  const CMLFunction* LineartoRResponse = cmlGetResponseCurveForwardFunc(cmlGetRGBSpaceResponseCurve(rgbspace, 0));
  const CMLFunction* LineartoGResponse = cmlGetResponseCurveForwardFunc(cmlGetRGBSpaceResponseCurve(rgbspace, 1));
  const CMLFunction* LineartoBResponse = cmlGetResponseCurveForwardFunc(cmlGetRGBSpaceResponseCurve(rgbspace, 2));

  while(count){
    cmlInternalOneXYZtoRGB(out, in, XYZtoRGBmatrix, LineartoRResponse, LineartoGResponse, LineartoBResponse);
    out += CML_RGB_NUMCHANNELS;
    in += CML_XYZ_NUMCHANNELS;
    count--;
  }
}

CMLHIDDEN CML_INLINE static void cmlInternalXYZtoRGB_SB (float* buf, CMLuint32 count, const CMLRGBSpace* rgbspace){

  const float* XYZtoRGBmatrix = cmlGetRGBSpaceInverseMatrix(rgbspace);
  const CMLFunction* LineartoRResponse = cmlGetResponseCurveForwardFunc(cmlGetRGBSpaceResponseCurve(rgbspace, 0));
  const CMLFunction* LineartoGResponse = cmlGetResponseCurveForwardFunc(cmlGetRGBSpaceResponseCurve(rgbspace, 1));
  const CMLFunction* LineartoBResponse = cmlGetResponseCurveForwardFunc(cmlGetRGBSpaceResponseCurve(rgbspace, 2));

  while(count){
    cmlInternalOneXYZtoRGB_SB(buf, XYZtoRGBmatrix, LineartoRResponse, LineartoGResponse, LineartoBResponse);
    buf += CML_RGB_NUMCHANNELS;
    count--;
  }
}




CMLHIDDEN CML_INLINE static void cmlInternalConstructXYZtoRGB(void** data, const void* input){
  *data = cmlRetainObject(input);
}


CMLHIDDEN CML_INLINE static CMLOutput cmlInternalConvertXYZtoRGB(CMLOutput out, CMLInput in, CMLSize count, const void* data){
  const CMLRGBSpace* rgbspace = (const CMLRGBSpace*)data;
  out = cmlAllocateIfNull(out, count * sizeof(float) * CML_RGB_NUMCHANNELS);
  if(in == out){
    cmlInternalXYZtoRGB_SB(out, count, rgbspace);
  }else{
    cmlInternalXYZtoRGB(out, in, count, rgbspace);
  }
  return out;
}


CMLHIDDEN CML_INLINE static void cmlInternalDestructXYZtoRGB(void* data){
  cmlReleaseObject(data);
}



CMLHIDDEN CML_INLINE static CMLConverter* cmlCreateXYZtoRGB(const CMLRGBSpace* rgbspace){
  return cmlCreateConverter(cmlInternalConvertXYZtoRGB, cmlInternalConstructXYZtoRGB, cmlInternalDestructXYZtoRGB, rgbspace);
}


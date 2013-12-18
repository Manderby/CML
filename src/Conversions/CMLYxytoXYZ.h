
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.


#define CMLINTERNALYxytoXYZ(out, in, whitepointXYZ) \
  if(in[2] == 0.f){\
    if(whitepointXYZ){\
      out[0] = ((float*)whitepointXYZ)[0];\
      out[2] = ((float*)whitepointXYZ)[2];\
    }else{\
      out[0] = 0.f;\
      out[2] = 0.f;\
    }\
    out[1] = 0.f;\
  }else{\
    out[2]  = in[0] / in[2];\
    float Y = out[2] * in[1];\
    out[1]  = in[0];\
    out[0]  = Y;\
    out[2] -= out[0] + out[1];\
  }



CMLHIDDEN CML_INLINE static void cmlInternalOneYxytoXYZ (float* CML_RESTRICT out , const float* CML_RESTRICT in, const CMLVec3 whitepointXYZ){
  CMLINTERNALYxytoXYZ(out, in, whitepointXYZ);
}

CMLHIDDEN CML_INLINE static void cmlInternalOneYxytoXYZ_SB(float* buf, const CMLVec3 whitepointXYZ){
  CMLINTERNALYxytoXYZ(buf, buf, whitepointXYZ);
}

CMLHIDDEN CML_INLINE static void cmlInternalYxytoXYZ (float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count, const CMLVec3 whitepointXYZ){
  while(count){
    cmlInternalOneYxytoXYZ(out, in, whitepointXYZ);
    out += CML_XYZ_NUMCHANNELS;
    in += CML_Yxy_NUMCHANNELS;
    count--;
  }
}

CMLHIDDEN CML_INLINE static void cmlInternalYxytoXYZ_SB(float* buf, CMLuint32 count, const CMLVec3 whitepointXYZ){
  while(count){
    cmlInternalOneYxytoXYZ_SB(buf, whitepointXYZ);
    buf += CML_XYZ_NUMCHANNELS;
    count--;
  }
}




CMLHIDDEN CML_INLINE static void cmlInternalConstructYxytoXYZ(void** data, const void* input){
  *data = cmlRetainObject(input);
}


CMLHIDDEN CML_INLINE static CMLOutput cmlInternalConvertYxytoXYZ(CMLOutput out, CMLInput in, CMLSize count, const void* data){
  const CMLWhitepoint* whitepoint = (const CMLWhitepoint*)data;
  out = cmlAllocateIfNull(out, count * sizeof(float) * CML_Yxy_NUMCHANNELS);
  const float* whitepointXYZ = cmlGetWhitepointXYZ(whitepoint);
  if(in == out){
    if(whitepointXYZ){
      cmlInternalYxytoXYZ_SB(out, count, whitepointXYZ);
    }else{
      cmlInternalYxytoXYZ_SB(out, count, CML_NULL);
    }
  }else{
    if(whitepointXYZ){
      cmlInternalYxytoXYZ(out, in, count, whitepointXYZ);
    }else{
      cmlInternalYxytoXYZ(out, in, count, CML_NULL);
    }
  }
  return out;
}


CMLHIDDEN CML_INLINE static void cmlInternalDestructYxytoXYZ(void* data){
  cmlReleaseObject(data);
}



CMLHIDDEN CML_INLINE static CMLConverter* cmlCreateYxytoXYZ(const CMLWhitepoint* whitepoint){
  return cmlCreateConverter(cmlInternalConvertYxytoXYZ, cmlInternalConstructYxytoXYZ, cmlInternalDestructYxytoXYZ, whitepoint);
}


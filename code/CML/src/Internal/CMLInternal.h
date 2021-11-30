
#include <stdlib.h>

#if CML_COMPILE_ON_WIN
  #define CML_HIDDEN
  #define CML_RESTRICT    __restrict
#elif CML_COMPILE_ON_MAC_OSX
  #define CML_HIDDEN      __attribute__ ((visibility("hidden")))
  #define CML_RESTRICT    __restrict__
#else
  #define CML_HIDDEN      __attribute__ ((visibility("hidden")))
  #define CML_RESTRICT
#endif


// todo: make inline functions or ranges
#define CML_MAX(a, b) (((a)>(b))?(a):(b))
#define CML_MIN(a, b) (((a)<(b))?(a):(b))



struct CML_HIDDEN CMLFunction{
  size_t refcount;
  size_t paramcount;
  float* params;
  void* data;
  CMLDefinitionRange defRange;
  CMLFunctionEvaluator getValue;
  CMLFunctionDesctructor destruct;
};


struct CMLResponseCurve{
  CMLFunction* forwardfunc;     // converting from luminance space
  CMLFunction* backwardfunc;    // converting to luminance space
  CMLFunctionType functionType;
};


struct CMLIllumination{
  CMLIlluminationType           BALFtype;
  CMLFunction*                  BALFspectrum;
  float                         BALFtemperature;
  CMLVec3                       BALFradiometricXYZ;
};


struct CMLObserver{
  CMLObserverType               BALFtype;
  CMLFunction*                  BALFspecdistfunctions[3];
  CMLIllumination               BALFillumination;
  float                         BALFradiometricScale;
  CMLVec3                       BALFwhitePointXYZ;
  CMLVec3                       BALFinverseWhitepointXYZ;
  CMLVec3                       BALFwhitePointYxy;
  CMLVec3                       BALFwhitePointYupvp;
};


CML_HIDDEN CMLResponseCurve* cmlCreateResponseCurve(CMLResponseCurve* curve);


CML_HIDEF float cml_Eval(const CMLFunction* function, float x){
  return function->getValue(function->params, function->data, x);
}






CML_IDEF void* cmlAllocate(size_t size){
  void* ptr; // Declaration before implementation.
  #if CML_DEBUG
    if(size < 1)
      cmlError("size is smaller than 1 .");
  #endif
  ptr = malloc(size);
  #if CML_DEBUG
    if(!ptr)
      {cmlError("out of memory."); exit(1); return CML_NULL;}
    // The exit call has been introduced as this is such a severe problem
    // that all functions rely on its functionality. Here, the debug version
    // differs from the non-debug version.
  #endif
  return ptr;
}


CML_IDEF void* cmlAllocateIfNull(void* ptr, size_t size){
  #if CML_DEBUG
    if(size < 1)
      cmlError("size is smaller than 1 .");
  #endif
  if(ptr == CML_NULL){
    return cmlAllocate(size);
  }else{
    return ptr;
  }
}


#define cml__START_COUNT_LOOP(count)\
  while(count){

#define cml__END_COUNT_LOOP(outchannels, inchannels)\
    out += outchannels;\
    in += inchannels;\
    count--;\
  }
  
#define cml__END_COUNT_LOOP_SB(numchannels)\
    buf += numchannels;\
    count--;\
  }


// ////////////////////////////////////
// XYZ to Yxy
// ////////////////////////////////////

#define cml_XYZtoYxy(out, in, whitePointYxy) \
  float divisor;\
  divisor = (in[0] + in[1] + in[2]);\
  float Y = in[1];\
  if(divisor == 0.f){\
    if(whitePointYxy){\
      out[2] = whitePointYxy[2];\
      out[1] = whitePointYxy[1];\
    }else{\
      out[2] = 0.f;\
      out[1] = 0.f;\
    }\
  }else{\
    float factor = cmlInverse(divisor);\
    out[2] = in[1] * factor;\
    out[1] = in[0] * factor;\
  }\
  out[0] = Y;

CML_HIDEF void cml_OneXYZtoYxy (float* CML_RESTRICT out, const float* CML_RESTRICT in, const CMLVec3 whitePointYxy){
  cml_XYZtoYxy(out, in, whitePointYxy);
}

CML_HIDEF void cml_OneXYZtoYxy_SB (float* CML_RESTRICT buf, const CMLVec3 whitePointYxy){
  cml_XYZtoYxy(buf, buf, whitePointYxy);
}

CML_HIDEF void cml_XYZtoYxy (float* CML_RESTRICT out, const float* CML_RESTRICT in, const CMLVec3 whitePointYxy, size_t count){
  cml__START_COUNT_LOOP(count);
  cml_OneXYZtoYxy(out, in, whitePointYxy);
  cml__END_COUNT_LOOP(CML_Yxy_NUMCHANNELS, CML_XYZ_NUMCHANNELS);
}

CML_HIDEF void cml_XYZtoYxy_SB (float* CML_RESTRICT buf, const CMLVec3 whitePointYxy, size_t count, CMLuint32 floatAlign){
  cml__START_COUNT_LOOP(count);
  cml_OneXYZtoYxy_SB(buf, whitePointYxy);
  cml__END_COUNT_LOOP_SB(floatAlign);
}


// ////////////////////////////////////
// XYZ to RGB
// ////////////////////////////////////

// todo: make mulVec SB
#define cml_XYZtoRGB(out, in, XYZtoRGBmatrix, LineartoRResponse, LineartoGResponse, LineartoBResponse) \
  CMLVec3 RGBp;\
  cmlMulMat33Vec3(RGBp, XYZtoRGBmatrix, in);\
  out[0] = cml_Eval(LineartoRResponse, RGBp[0]);\
  out[1] = cml_Eval(LineartoGResponse, RGBp[1]);\
  out[2] = cml_Eval(LineartoBResponse, RGBp[2]);

CML_HIDEF void cml_OneXYZtoRGB (float* CML_RESTRICT out , const float* CML_RESTRICT in, const CMLMat33 XYZtoRGBmatrix, const CMLFunction* LineartoRResponse, const CMLFunction* LineartoGResponse, const CMLFunction* LineartoBResponse){
  cml_XYZtoRGB(out, in, XYZtoRGBmatrix, LineartoRResponse, LineartoGResponse, LineartoBResponse);
}

CML_HIDEF void cml_OneXYZtoRGB_SB (float* buf, const CMLMat33 XYZtoRGBmatrix, const CMLFunction* LineartoRResponse, const CMLFunction* LineartoGResponse, const CMLFunction* LineartoBResponse){
  cml_XYZtoRGB(buf, buf, XYZtoRGBmatrix, LineartoRResponse, LineartoGResponse, LineartoBResponse);
}

CML_HIDEF void cml_XYZtoRGB (float* CML_RESTRICT out , const float* CML_RESTRICT in, size_t count, const CMLMat33 XYZtoRGBmatrix, const CMLFunction* LineartoRResponse, const CMLFunction* LineartoGResponse, const CMLFunction* LineartoBResponse){
  cml__START_COUNT_LOOP(count);
  cml_OneXYZtoRGB(out, in, XYZtoRGBmatrix, LineartoRResponse, LineartoGResponse, LineartoBResponse);
  cml__END_COUNT_LOOP(CML_RGB_NUMCHANNELS, CML_XYZ_NUMCHANNELS);
}

CML_HIDEF void cml_XYZtoRGB_SB (float* buf, size_t count, CMLuint32 floatAlign, const CMLMat33 XYZtoRGBmatrix, const CMLFunction* LineartoRResponse, const CMLFunction* LineartoGResponse, const CMLFunction* LineartoBResponse){
  cml__START_COUNT_LOOP(count);
  cml_OneXYZtoRGB_SB(buf, XYZtoRGBmatrix, LineartoRResponse, LineartoGResponse, LineartoBResponse);
  cml__END_COUNT_LOOP_SB(floatAlign);
}


// ////////////////////////////////////
// Yxy to XYZ
// ////////////////////////////////////

#define cml_YxytoXYZ(out, in, whitePointXYZ) \
  if(in[2] == 0.f){\
    if(whitePointXYZ){\
      out[0] = ((float*)whitePointXYZ)[0];\
      out[2] = ((float*)whitePointXYZ)[2];\
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

CML_HIDEF void cml_OneYxytoXYZ (float* CML_RESTRICT out , const float* CML_RESTRICT in, const CMLVec3 whitePointXYZ){
  cml_YxytoXYZ(out, in, whitePointXYZ);
}

CML_HIDEF void cml_OneYxytoXYZ_SB(float* buf, const CMLVec3 whitePointXYZ){
  cml_YxytoXYZ(buf, buf, whitePointXYZ);
}

CML_HIDEF void cml_YxytoXYZ (float* CML_RESTRICT out , const float* CML_RESTRICT in, const CMLVec3 whitePointXYZ, size_t count){
  cml__START_COUNT_LOOP(count);
  cml_OneYxytoXYZ(out, in, whitePointXYZ);
  cml__END_COUNT_LOOP(CML_XYZ_NUMCHANNELS, CML_Yxy_NUMCHANNELS);
}

CML_HIDEF void cml_YxytoXYZ_SB(float* buf, const CMLVec3 whitePointXYZ, size_t count, CMLuint32 floatAlign){
  cml__START_COUNT_LOOP(count);
  cml_OneYxytoXYZ_SB(buf, whitePointXYZ);
  cml__END_COUNT_LOOP_SB(floatAlign);
}

// ////////////////////////////////////
// Yupvp to Yxy
// ////////////////////////////////////


#define cml_YupvptoYxy(out, in, whitePointYxy) \
  float divisor;\
  out[0] = in[0];\
  divisor = 6.f * in[1] - 16.f * in[2] + 12.f;\
  if(divisor == 0.f){\
    if(whitePointYxy){\
      out[1] = whitePointYxy[1];\
      out[2] = whitePointYxy[2];\
    }else{\
      out[1] = 0.f;\
      out[2] = 0.f;\
    }\
  }else{\
    float factor = cmlInverse(divisor);\
    out[1] = 9.f * in[1] * factor;\
    out[2] = 4.f * in[2] * factor;\
  }

CML_HIDEF void cml_OneYupvptoYxy (float* CML_RESTRICT out , const float* CML_RESTRICT in, const CMLVec3 whitePointYxy){
  cml_YupvptoYxy(out, in, whitePointYxy);
}
CML_HIDEF void cml_OneYupvptoYxy_SB(float* buf, const CMLVec3 whitePointYxy){
  cml_YupvptoYxy(buf, buf, whitePointYxy);
}

CML_HIDEF void cml_YupvptoYxy (float* CML_RESTRICT out , const float* CML_RESTRICT in, const CMLVec3 whitePointYxy, size_t count){
  cml__START_COUNT_LOOP(count);
  cml_OneYupvptoYxy(out, in, whitePointYxy);
  cml__END_COUNT_LOOP(CML_Yxy_NUMCHANNELS, CML_Yupvp_NUMCHANNELS);
}

CML_HIDEF void cml_YupvptoYxy_SB(float* buf, const CMLVec3 whitePointYxy, size_t count, CMLuint32 floatAlign){
  cml__START_COUNT_LOOP(count);
  cml_OneYupvptoYxy_SB(buf, whitePointYxy);
  cml__END_COUNT_LOOP_SB(floatAlign);
}


// ////////////////////////////////////
// Luv to Yupvp
// ////////////////////////////////////

#define cml_LuvtoYupvp(out, in, whitePointYupvp, LtoLinearResponse) \
  float divisor;\
  float yr;\
  yr = cml_Eval(LtoLinearResponse, in[0] * .01f);\
  divisor = 13.f * in[0];\
  out[0] = yr * whitePointYupvp[0];\
  if(divisor == 0.f){\
    out[1] = whitePointYupvp[1];\
    out[2] = whitePointYupvp[2];\
  }else{\
    float factor = cmlInverse(divisor);\
    out[1] = (in[1] * factor) + whitePointYupvp[1];\
    out[2] = (in[2] * factor) + whitePointYupvp[2];\
  }

CML_HIDEF void cml_OneLuvtoYupvp (float* CML_RESTRICT out , const float* CML_RESTRICT in, const CMLVec3 whitePointYupvp, const CMLFunction* LtoLinearResponse){
  cml_LuvtoYupvp(out, in, whitePointYupvp, LtoLinearResponse);
}
CML_HIDEF void cml_OneLuvtoYupvp_SB (float* buf, const CMLVec3 whitePointYupvp, const CMLFunction* LtoLinearResponse){
  cml_LuvtoYupvp(buf, buf, whitePointYupvp, LtoLinearResponse);
}

CML_HIDEF void cml_LuvtoYupvp (float* CML_RESTRICT out , const float* CML_RESTRICT in, size_t count, const CMLVec3 whitePointYupvp, const CMLFunction* LtoLinearResponse){
  cml__START_COUNT_LOOP(count);
  cml_OneLuvtoYupvp(out, in, whitePointYupvp, LtoLinearResponse);
  cml__END_COUNT_LOOP(CML_Yupvp_NUMCHANNELS, CML_Luv_NUMCHANNELS);
}

CML_HIDEF void cml_LuvtoYupvp_SB (float* buf, size_t count, CMLuint32 floatAlign, const CMLVec3 whitePointYupvp, const CMLFunction* LtoLinearResponse){
  cml__START_COUNT_LOOP(count);
  cml_OneLuvtoYupvp_SB(buf, whitePointYupvp, LtoLinearResponse);
  cml__END_COUNT_LOOP_SB(floatAlign);
}



// ////////////////////////////////////
// Yxy to Yupvp
// ////////////////////////////////////


#define cml_YxytoYupvp(out, in, whitePointYupvp) \
  float divisor;\
  out[0] = in[0];\
  divisor = -2.f * in[1] + 12.f * in[2] + 3.f;\
  if(divisor == 0.f){\
    if(whitePointYupvp){\
      out[1] = whitePointYupvp[1];\
      out[2] = whitePointYupvp[2];\
    }else{\
      out[1] = 0.f;\
      out[2] = 0.f;\
    }\
  }else{\
    float factor = cmlInverse(divisor);\
    out[1] = 4.f * in[1] * factor;\
    out[2] = 9.f * in[2] * factor;\
  }\

CML_HIDEF void cml_OneYxytoYupvp(float* CML_RESTRICT out , const float* CML_RESTRICT in, const CMLVec3 whitePointYupvp){
  cml_YxytoYupvp(out, in, whitePointYupvp);
}

CML_HIDEF void cml_OneYxytoYupvp_SB(float* buf, const CMLVec3 whitePointYupvp){
  cml_YxytoYupvp(buf, buf, whitePointYupvp);
}

CML_HIDEF void cml_YxytoYupvp(float* CML_RESTRICT out , const float* CML_RESTRICT in, const CMLVec3 whitePointYupvp, size_t count){
  cml__START_COUNT_LOOP(count);
  cml_OneYxytoYupvp(out, in, whitePointYupvp);
  cml__END_COUNT_LOOP(CML_Yupvp_NUMCHANNELS, CML_Yxy_NUMCHANNELS);
}

CML_HIDEF void cml_YxytoYupvp_SB(float* buf, const CMLVec3 whitePointYupvp, size_t count, CMLuint32 floatAlign){
  cml__START_COUNT_LOOP(count);
  cml_OneYxytoYupvp_SB(buf, whitePointYupvp);
  cml__END_COUNT_LOOP_SB(floatAlign);
}



// ////////////////////////////////////
// Yupvp to Luv
// ////////////////////////////////////

#define cml_YupvptoLuv(out, in, whitePointYupvp, LineartoLResponse) \
  float yr = in[0] / whitePointYupvp[0];\
  float fy = cml_Eval(LineartoLResponse, yr);\
  out[0] = 100.f * fy;\
  out[1] = 13.f * out[0] * (in[1] - whitePointYupvp[1]);\
  out[2] = 13.f * out[0] * (in[2] - whitePointYupvp[2]);

CML_HIDEF void cml_OneYupvptoLuv (float* CML_RESTRICT out , const float* CML_RESTRICT in, const CMLVec3 whitePointYupvp, const CMLFunction* LineartoLResponse){
  cml_YupvptoLuv(out, in, whitePointYupvp, LineartoLResponse);
}

CML_HIDEF void cml_OneYupvptoLuv_SB (float* buf, const CMLVec3 whitePointYupvp, const CMLFunction* LineartoLResponse){
  cml_YupvptoLuv(buf, buf, whitePointYupvp, LineartoLResponse);
}

CML_HIDEF void cml_YupvptoLuv (float* CML_RESTRICT out , const float* CML_RESTRICT in, size_t count, const CMLVec3 whitePointYupvp, const CMLFunction* LineartoLResponse){
  cml__START_COUNT_LOOP(count);
  cml_OneYupvptoLuv(out, in, whitePointYupvp, LineartoLResponse);
  cml__END_COUNT_LOOP(CML_Luv_NUMCHANNELS, CML_Yupvp_NUMCHANNELS);
}

CML_HIDEF void cml_YupvptoLuv_SB (float* buf, size_t count, CMLuint32 floatAlign, const CMLVec3 whitePointYupvp, const CMLFunction* LineartoLResponse){
  cml__START_COUNT_LOOP(count);
  cml_OneYupvptoLuv_SB(buf, whitePointYupvp, LineartoLResponse);
  cml__END_COUNT_LOOP_SB(floatAlign);
}


// ////////////////////////////////////
// Yupvp to Luv
// ////////////////////////////////////

#define cml_YuvtoYupvp(out, in) \
  out[0] = in[0];\
  out[1] = in[1];\
  out[2] = in[2] * 1.5f;

CML_HIDEF void cml_OneYuvtoYupvp (float* CML_RESTRICT out , const float* CML_RESTRICT in){
  cml_YuvtoYupvp(out, in);
}
CML_HIDEF void cml_OneYuvtoYupvp_SB (float* buf){
  cml_YuvtoYupvp(buf, buf);
}

CML_HIDEF void cml_YuvtoYupvp (float* CML_RESTRICT out , const float* CML_RESTRICT in, size_t count){
  cml__START_COUNT_LOOP(count);
  cml_OneYuvtoYupvp(out, in);
  cml__END_COUNT_LOOP(CML_Yupvp_NUMCHANNELS, CML_Yuv_NUMCHANNELS);
}

CML_HIDEF void cml_YuvtoYupvp_SB (float* buf, size_t count, CMLuint32 floatAlign){
  cml__START_COUNT_LOOP(count);
  cml_OneYuvtoYupvp_SB(buf);
  cml__END_COUNT_LOOP_SB(floatAlign);
}


// ////////////////////////////////////
// Luv to Yupvp
// ////////////////////////////////////

#define cml_YupvptoYuv(out, in) \
  out[0] = in[0];\
  out[1] = in[1];\
  out[2] = in[2] * 0.666666666666667f;

CML_HIDEF void cml_OneYupvptoYuv (float* CML_RESTRICT out , const float* CML_RESTRICT in){
  cml_YupvptoYuv(out, in);
}
CML_HIDEF void cml_OneYupvptoYuv_SB (float* buf){
  cml_YupvptoYuv(buf, buf);
}

CML_HIDEF void cml_YupvptoYuv (float* CML_RESTRICT out , const float* CML_RESTRICT in, size_t count){
  cml__START_COUNT_LOOP(count);
  cml_OneYupvptoYuv(out, in);
  cml__END_COUNT_LOOP(CML_Yuv_NUMCHANNELS, CML_Yupvp_NUMCHANNELS);
}

CML_HIDEF void cml_YupvptoYuv_SB (float* buf, size_t count, CMLuint32 floatAlign){
  cml__START_COUNT_LOOP(count);
  cml_OneYupvptoYuv_SB(buf);
  cml__END_COUNT_LOOP_SB(floatAlign);
}


// ////////////////////////////////////
// Lab to Lch
// ////////////////////////////////////

#define cml_LabtoLch(out, in) \
  out[0] = in[0];\
  float length = cmlLength2(&(in[1]));\
  if(length == 0.f){\
    out[2] = 0.f;\
  }else{\
    out[2] = cmlRadToDeg(atan2f(in[2], in[1]));\
    if(out[2] < 0.f){out[2] += 360.f;}\
  }\
  out[1] = length;

CML_HIDEF void cml_OneLabtoLch (float* CML_RESTRICT out , const float* CML_RESTRICT in){
  cml_LabtoLch(out, in);
}
CML_HIDEF void cml_OneLabtoLch_SB (float* buf){
  cml_LabtoLch(buf, buf);
}

CML_HIDEF void cml_LabtoLch (float* CML_RESTRICT out , const float* CML_RESTRICT in, size_t count ){
  cml__START_COUNT_LOOP(count);
  cml_OneLabtoLch(out, in);
  cml__END_COUNT_LOOP(CML_Lch_NUMCHANNELS, CML_Lab_NUMCHANNELS);
}

CML_HIDEF void cml_LabtoLch_SB (float* buf, size_t count, CMLuint32 floatAlign){
  cml__START_COUNT_LOOP(count);
  cml_OneLabtoLch_SB(buf);
  cml__END_COUNT_LOOP_SB(floatAlign);
}


// ////////////////////////////////////
// RGB to XYZ
// ////////////////////////////////////

// todo: make mulVec SB
#define cml_RGBtoXYZ(out, in, RGBtoXYZmatrix, RtoLinearResponse, GtoLinearResponse, BtoLinearResponse) \
  float RGBp[3];\
  RGBp[0] = cml_Eval(RtoLinearResponse, in[0]);\
  RGBp[1] = cml_Eval(GtoLinearResponse, in[1]);\
  RGBp[2] = cml_Eval(BtoLinearResponse, in[2]);\
  cmlMulMat33Vec3(out, RGBtoXYZmatrix, RGBp);

CML_HIDEF void cml_OneRGBtoXYZ (float* CML_RESTRICT out , const float* CML_RESTRICT in, const CMLMat33 RGBtoXYZmatrix, const CMLFunction* RtoLinearResponse, const CMLFunction* GtoLinearResponse, const CMLFunction* BtoLinearResponse){
  cml_RGBtoXYZ(out, in, RGBtoXYZmatrix, RtoLinearResponse, GtoLinearResponse, BtoLinearResponse);
}
CML_HIDEF void cml_OneRGBtoXYZ_SB (float* buf, const CMLMat33 RGBtoXYZmatrix, const CMLFunction* RtoLinearResponse, const CMLFunction* GtoLinearResponse, const CMLFunction* BtoLinearResponse){
  cml_RGBtoXYZ(buf, buf, RGBtoXYZmatrix, RtoLinearResponse, GtoLinearResponse, BtoLinearResponse);
}

CML_HIDEF void cml_RGBtoXYZ (float* CML_RESTRICT out , const float* CML_RESTRICT in, size_t count, const CMLMat33 RGBtoXYZmatrix, const CMLFunction* RtoLinearResponse, const CMLFunction* GtoLinearResponse, const CMLFunction* BtoLinearResponse){
  cml__START_COUNT_LOOP(count);
  cml_OneRGBtoXYZ(out, in, RGBtoXYZmatrix, RtoLinearResponse, GtoLinearResponse, BtoLinearResponse);
  cml__END_COUNT_LOOP(CML_XYZ_NUMCHANNELS, CML_RGB_NUMCHANNELS);
}

CML_HIDEF void cml_RGBtoXYZ_SB (float* buf, size_t count, CMLuint32 floatAlign, const CMLMat33 RGBtoXYZmatrix, const CMLFunction* RtoLinearResponse, const CMLFunction* GtoLinearResponse, const CMLFunction* BtoLinearResponse){
  cml__START_COUNT_LOOP(count);
  cml_OneRGBtoXYZ_SB(buf, RGBtoXYZmatrix, RtoLinearResponse, GtoLinearResponse, BtoLinearResponse);
  cml__END_COUNT_LOOP_SB(floatAlign);
}


// ////////////////////////////////////
// RGB to YCbCr
// ////////////////////////////////////

#define cml_RGBtoYCbCr(out, in, redprimaryYxy, blueprimaryYxy, inversewhitePointXYZ) \
  float Kr = redprimaryYxy[0] * inversewhitePointXYZ[1];\
  float Kb = blueprimaryYxy[0] * inversewhitePointXYZ[1];\
  float Y = Kr * in[0] + (1.f - Kr - Kb) * in[1] + Kb * in[2];\
  out[1] = .5f * (in[2] - Y) / (1.f - Kb);\
  out[2] = .5f * (in[0] - Y) / (1.f - Kr);\
  out[0] = Y;

CML_HIDEF void cml_OneRGBtoYCbCr (float* CML_RESTRICT out , const float* CML_RESTRICT in, const CMLVec3 redprimaryYxy, const CMLVec3 blueprimaryYxy, const CMLVec3 inversewhitePointXYZ){
  cml_RGBtoYCbCr(out, in, redprimaryYxy, blueprimaryYxy, inversewhitePointXYZ);
}
CML_HIDEF void cml_OneRGBtoYCbCr_SB (float* buf, const CMLVec3 redprimaryYxy, const CMLVec3 blueprimaryYxy, const CMLVec3 inversewhitePointXYZ){
  cml_RGBtoYCbCr(buf, buf, redprimaryYxy, blueprimaryYxy, inversewhitePointXYZ);
}

CML_HIDEF void cml_RGBtoYCbCr (float* CML_RESTRICT out , const float* CML_RESTRICT in, size_t count, const CMLVec3 redprimaryYxy, const CMLVec3 blueprimaryYxy, const CMLVec3 inversewhitePointXYZ){
  cml__START_COUNT_LOOP(count);
  cml_OneRGBtoYCbCr(out, in, redprimaryYxy, blueprimaryYxy, inversewhitePointXYZ);
  cml__END_COUNT_LOOP(CML_YCbCr_NUMCHANNELS, CML_RGB_NUMCHANNELS);
}

CML_HIDEF void cml_RGBtoYCbCr_SB (float* buf, size_t count, CMLuint32 floatAlign, const CMLVec3 redprimaryYxy, const CMLVec3 blueprimaryYxy, const CMLVec3 inversewhitePointXYZ){
  cml__START_COUNT_LOOP(count);
  cml_OneRGBtoYCbCr_SB(buf, redprimaryYxy, blueprimaryYxy, inversewhitePointXYZ);
  cml__END_COUNT_LOOP_SB(floatAlign);
}


// ////////////////////////////////////
// HSV to HSL
// ////////////////////////////////////

#define cml_HSVtoHSL(out, in) \
  out[0] = in[0];\
  out[1] = in[1] * in[2];\
  out[2] = in[2] - 0.5f * out[1];


CML_HIDEF void cml_OneHSVtoHSL (float* CML_RESTRICT out , const float* CML_RESTRICT in){
  cml_HSVtoHSL(out, in);
}
CML_HIDEF void cml_OneHSVtoHSL_SB (float* buf){
  cml_HSVtoHSL(buf, buf);
}

CML_HIDEF void cml_HSVtoHSL (float* CML_RESTRICT out , const float* CML_RESTRICT in, size_t count ){
  cml__START_COUNT_LOOP(count);
  cml_OneHSVtoHSL(out, in);
  cml__END_COUNT_LOOP(CML_HSL_NUMCHANNELS, CML_HSV_NUMCHANNELS);
}

CML_HIDEF void cml_HSVtoHSL_SB (float* buf, size_t count, CMLuint32 floatAlign){
  cml__START_COUNT_LOOP(count);
  cml_OneHSVtoHSL_SB(buf);
  cml__END_COUNT_LOOP_SB(floatAlign);
}


// ////////////////////////////////////
// Lch to Lab
// ////////////////////////////////////

#define cml_LchtoLab(out, in) \
  if(in[1] == 0.f){\
    out[2] = 0.f;\
    out[1] = 0.f;\
  }else{\
    float hue = cmlDegToRad(in[2]);\
    out[2] = sinf(hue) * in[1];\
    out[1] = cosf(hue) * in[1];\
  }\
  out[0] = in[0];

CML_HIDEF void cml_OneLchtoLab(float* CML_RESTRICT out , const float* CML_RESTRICT in){
  cml_LchtoLab(out, in);
}
CML_HIDEF void cml_OneLchtoLab_SB(float* buf){
  cml_LchtoLab(buf, buf);
}

CML_HIDEF void cml_LchtoLab(float* CML_RESTRICT out , const float* CML_RESTRICT in, size_t count){
  cml__START_COUNT_LOOP(count);
  cml_OneLchtoLab(out, in);
  cml__END_COUNT_LOOP(CML_Lab_NUMCHANNELS, CML_Lch_NUMCHANNELS);
}

CML_HIDEF void cml_LchtoLab_SB(float* buf, size_t count, CMLuint32 floatAlign){
  cml__START_COUNT_LOOP(count);
  cml_OneLchtoLab_SB(buf);
  cml__END_COUNT_LOOP_SB(floatAlign);
}


// ////////////////////////////////////
// YCbCr to RGB
// ////////////////////////////////////

#define cml_YCbCrtoRGB(out, in, redprimaryYxy, blueprimaryYxy, inversewhitePointXYZ) \
  float Kr = redprimaryYxy[0] * inversewhitePointXYZ[1];\
  float Kb = blueprimaryYxy[0] * inversewhitePointXYZ[1];\
  float Y = in[0];\
  out[0] = 2.f * in[2] * (1.f - Kr) + Y;\
  out[2] = 2.f * in[1] * (1.f - Kb) + Y;\
  out[1] = (Y - Kr * out[0] - Kb * out[2]) / (1.f - Kr - Kb);


CML_HIDEF void cml_OneYCbCrtoRGB (float* CML_RESTRICT out , const float* CML_RESTRICT in, const CMLVec3 redprimaryYxy, const CMLVec3 blueprimaryYxy, const CMLVec3 inversewhitePointXYZ){
  cml_YCbCrtoRGB(out, in, redprimaryYxy, blueprimaryYxy, inversewhitePointXYZ);
}
CML_HIDEF void cml_OneYCbCrtoRGB_SB (float* buf, const CMLVec3 redprimaryYxy, const CMLVec3 blueprimaryYxy, const CMLVec3 inversewhitePointXYZ){
  cml_YCbCrtoRGB(buf, buf, redprimaryYxy, blueprimaryYxy, inversewhitePointXYZ);
}

CML_HIDEF void cml_YCbCrtoRGB (float* CML_RESTRICT out , const float* CML_RESTRICT in, size_t count, const CMLVec3 redprimaryYxy, const CMLVec3 blueprimaryYxy, const CMLVec3 inversewhitePointXYZ){
  cml__START_COUNT_LOOP(count);
  cml_OneYCbCrtoRGB(out, in, redprimaryYxy, blueprimaryYxy, inversewhitePointXYZ);
  cml__END_COUNT_LOOP(CML_RGB_NUMCHANNELS, CML_YCbCr_NUMCHANNELS);
}

CML_HIDEF void cml_YCbCrtoRGB_SB (float* buf, size_t count, CMLuint32 floatAlign, const CMLVec3 redprimaryYxy, const CMLVec3 blueprimaryYxy, const CMLVec3 inversewhitePointXYZ){
  cml__START_COUNT_LOOP(count);
  cml_OneYCbCrtoRGB_SB(buf, redprimaryYxy, blueprimaryYxy, inversewhitePointXYZ);
  cml__END_COUNT_LOOP_SB(floatAlign);
}


// ////////////////////////////////////
// HSL to HSV
// ////////////////////////////////////

#define cml_HSLtoHSV(out, in) \
  out[0] = in[0];\
  out[2] = in[2] + .5f * in[1];\
  if(out[2] == 0.f){\
    out[1] = in[1] / CML_SINGULARITY;\
  }else{\
    out[1] = in[1] / out[2];\
  }

CML_HIDEF void cml_OneHSLtoHSV (float* CML_RESTRICT out , const float* CML_RESTRICT in){
  cml_HSLtoHSV(out, in);
}
CML_HIDEF void cml_OneHSLtoHSV_SB (float* buf){
  cml_HSLtoHSV(buf, buf);
}

CML_HIDEF void cml_HSLtoHSV (float* CML_RESTRICT out , const float* CML_RESTRICT in, size_t count){
  cml__START_COUNT_LOOP(count);
  cml_OneHSLtoHSV(out, in);
  cml__END_COUNT_LOOP(CML_HSV_NUMCHANNELS, CML_HSL_NUMCHANNELS);
}

CML_HIDEF void cml_HSLtoHSV_SB (float* buf, size_t count, CMLuint32 floatAlign){
  cml__START_COUNT_LOOP(count);
  cml_OneHSLtoHSV_SB(buf);
  cml__END_COUNT_LOOP_SB(floatAlign);
}


// ////////////////////////////////////
// RGB to HSV
// ////////////////////////////////////

// todo: Make it SB
#define cml_RGBtoHSV(out, in) \
  float min;\
  float range;\
  CMLVec3 rgb;\
  cmlCpy3(rgb, in);\
  if(rgb[0] < rgb[1]){min = rgb[0]; out[2] = rgb[1];}else{min = rgb[1]; out[2] = rgb[0];}\
  if(rgb[2] < min){min = rgb[2];}\
  if(rgb[2] > out[2]){out[2] = rgb[2];}\
  range = out[2] - min;\
  if(out[2] == 0.f){\
    out[1] = 0.f;\
  }else{\
    out[1] = range / out[2];\
  }\
  if(cmlAlmostZero(range)){\
    out[0] = 0.f;\
  }else{\
    float invrange = cmlInverse(range);\
    if(out[2] == rgb[0])      {out[0] = 60.f * (0.f + (rgb[1]-rgb[2]) * invrange);}\
    else if(out[2] == rgb[1]) {out[0] = 60.f * (2.f + (rgb[2]-rgb[0]) * invrange);}\
    else                      {out[0] = 60.f * (4.f + (rgb[0]-rgb[1]) * invrange);}\
    if(out[0] < 0.f){out[0] += 360.f;}\
  }

CML_HIDEF void cml_OneRGBtoHSV (float* CML_RESTRICT out , const float* CML_RESTRICT in){
  cml_RGBtoHSV(out, in);
}
CML_HIDEF void cml_OneRGBtoHSV_SB (float* buf){
  cml_RGBtoHSV(buf, buf);
}

CML_HIDEF void cml_RGBtoHSV (float* CML_RESTRICT out , const float* CML_RESTRICT in, size_t count){
  cml__START_COUNT_LOOP(count);
  cml_OneRGBtoHSV(out, in);
  cml__END_COUNT_LOOP(CML_HSV_NUMCHANNELS, CML_RGB_NUMCHANNELS);
}

CML_HIDEF void cml_RGBtoHSV_SB (float* buf, size_t count, CMLuint32 floatAlign){
  cml__START_COUNT_LOOP(count);
  cml_OneRGBtoHSV_SB(buf);
  cml__END_COUNT_LOOP_SB(floatAlign);
}


// ////////////////////////////////////
// HSV to RGB
// ////////////////////////////////////

// todo: Make it SB
#define cml_HSVtoRGB(out, in) \
  CMLVec3 hsv;\
  cmlCpy3(hsv, in);\
  CMLint8 h0 = (CMLint8)floorf(hsv[0] / 60.f);\
  CMLuint8 h1 = (CMLuint8)((h0 % 6) + 6) % 6;\
  float f = (hsv[0] / 60.f) - h0;\
  float range = hsv[2] * hsv[1];\
  float min = hsv[2] - range;\
  float inc = f * range;\
  float dec = (1.f - f) * range;\
  inc += min;\
  dec += min;\
  switch(h1){\
  case 0: out[0] = hsv[2] ; out[1] = inc    ; out[2] = min    ; break;\
  case 1: out[0] = dec    ; out[1] = hsv[2] ; out[2] = min    ; break;\
  case 2: out[0] = min    ; out[1] = hsv[2] ; out[2] = inc    ; break;\
  case 3: out[0] = min    ; out[1] = dec    ; out[2] = hsv[2] ; break;\
  case 4: out[0] = inc    ; out[1] = min    ; out[2] = hsv[2] ; break;\
  case 5: out[0] = hsv[2] ; out[1] = min    ; out[2] = dec    ; break;\
  default:\
    out[0] = 0.f; out[1] = 0.f; out[2] = 0.f;\
  }

CML_HIDEF void cml_OneHSVtoRGB (float* CML_RESTRICT out , const float* CML_RESTRICT in){
  cml_HSVtoRGB(out, in);
}
CML_HIDEF void cml_OneHSVtoRGB_SB (float* buf){
  cml_HSVtoRGB(buf, buf);
}

CML_HIDEF void cml_HSVtoRGB (float* CML_RESTRICT out , const float* CML_RESTRICT in, size_t count){
  cml__START_COUNT_LOOP(count);
  cml_OneHSVtoRGB(out, in);
  cml__END_COUNT_LOOP(CML_RGB_NUMCHANNELS, CML_HSV_NUMCHANNELS);
}

CML_HIDEF void cml_HSVtoRGB_SB (float* buf, size_t count, CMLuint32 floatAlign){
  cml__START_COUNT_LOOP(count);
  cml_OneHSVtoRGB_SB(buf);
  cml__END_COUNT_LOOP_SB(floatAlign);
}


// ////////////////////////////////////
// Lr to fy and fy to Lr
// ////////////////////////////////////

#define CML_LSTAR_TRANSFORM_OFFSET    0.16f
#define CML_LSTAR_TRANSFORM_SCALE     1.16f
#define CML_LSTAR_TRANSFORM_INV_SCALE 0.8620689655172f

CML_HIDEF float cml_Lrtofy(float Lr){
  return (Lr + CML_LSTAR_TRANSFORM_OFFSET) * CML_LSTAR_TRANSFORM_INV_SCALE;
}

CML_HIDEF float cml_fytoLr(float fy){
  return fy * CML_LSTAR_TRANSFORM_SCALE - CML_LSTAR_TRANSFORM_OFFSET;
}


// ////////////////////////////////////
// XYZ to CIELAB
// ////////////////////////////////////

#define cml_XYZtoCIELAB(out, in, inverseWhitepointXYZ, LineartoLResponse) \
  float xr = in[0] * inverseWhitepointXYZ[0];\
  float yr = in[1] * inverseWhitepointXYZ[1];\
  float zr = in[2] * inverseWhitepointXYZ[2];\
  float fx = cml_Lrtofy(cml_Eval(LineartoLResponse, xr));\
  float fy = cml_Lrtofy(cml_Eval(LineartoLResponse, yr));\
  float fz = cml_Lrtofy(cml_Eval(LineartoLResponse, zr));\
  out[0] = 100.f * cml_fytoLr(fy);\
  out[1] = (fx - fy) * 500.f;\
  out[2] = (fy - fz) * 200.f;


CML_HIDEF void cml_OneXYZtoCIELAB(float* CML_RESTRICT out, const float* CML_RESTRICT in , const CMLVec3 inverseWhitepointXYZ, const CMLFunction* LineartoLResponse){
  cml_XYZtoCIELAB(out, in, inverseWhitepointXYZ, LineartoLResponse);
}
CML_HIDEF void cml_OneXYZtoCIELAB_SB(float* buf, const CMLVec3 inverseWhitepointXYZ, const CMLFunction* LineartoLResponse){
  cml_XYZtoCIELAB(buf, buf, inverseWhitepointXYZ, LineartoLResponse);
}

CML_HIDEF void cml_XYZtoCIELAB(float* CML_RESTRICT out, const float* CML_RESTRICT in, size_t count , const CMLVec3 inverseWhitepointXYZ, const CMLFunction* LineartoLResponse){
  cml__START_COUNT_LOOP(count);
  cml_OneXYZtoCIELAB(out, in, inverseWhitepointXYZ, LineartoLResponse);
  cml__END_COUNT_LOOP(CML_Lab_NUMCHANNELS, CML_XYZ_NUMCHANNELS);
}

CML_HIDEF void cml_XYZtoCIELAB_SB(float* buf, size_t count, CMLuint32 floatAlign, const CMLVec3 inverseWhitepointXYZ, const CMLFunction* LineartoLResponse){
  cml__START_COUNT_LOOP(count);
  cml_OneXYZtoCIELAB_SB(buf, inverseWhitepointXYZ, LineartoLResponse);
  cml__END_COUNT_LOOP_SB(floatAlign);
}


// ////////////////////////////////////
// CIELAB to XYZ
// ////////////////////////////////////

#define cml_CIELABtoXYZ(out, in, whitePointXYZ, LtoLinearResponse) \
    float fy = cml_Lrtofy(.01f * in[0]);\
    float fx = fy + in[1] * .002f;\
    float fz = fy - in[2] * .005f;\
    float xr = cml_Eval(LtoLinearResponse, cml_fytoLr(fx));\
    float yr = cml_Eval(LtoLinearResponse, cml_fytoLr(fy));\
    float zr = cml_Eval(LtoLinearResponse, cml_fytoLr(fz));\
    out[0] = xr * whitePointXYZ[0];\
    out[1] = yr * whitePointXYZ[1];\
    out[2] = zr * whitePointXYZ[2];


CML_HIDEF void cml_OneCIELABtoXYZ (float* CML_RESTRICT out , const float* CML_RESTRICT in, const CMLVec3 whitePointXYZ, const CMLFunction* LtoLinearResponse){
  cml_CIELABtoXYZ(out, in, whitePointXYZ, LtoLinearResponse);
}
CML_HIDEF void cml_OneCIELABtoXYZ_SB (float* buf, const CMLVec3 whitePointXYZ, const CMLFunction* LtoLinearResponse){
  cml_CIELABtoXYZ(buf, buf, whitePointXYZ, LtoLinearResponse);
}

CML_HIDEF void cml_CIELABtoXYZ (float* CML_RESTRICT out , const float* CML_RESTRICT in, size_t count, const CMLVec3 whitePointXYZ, const CMLFunction* LtoLinearResponse){
  cml__START_COUNT_LOOP(count);
  cml_OneCIELABtoXYZ(out, in, whitePointXYZ, LtoLinearResponse);
  cml__END_COUNT_LOOP(CML_XYZ_NUMCHANNELS, CML_Lab_NUMCHANNELS);
}


CML_HIDEF void cml_CIELABtoXYZ_SB (float* buf , size_t count, CMLuint32 floatAlign, const CMLVec3 whitePointXYZ, const CMLFunction* LtoLinearResponse){
  cml__START_COUNT_LOOP(count);
  cml_OneCIELABtoXYZ_SB(buf, whitePointXYZ, LtoLinearResponse);
  cml__END_COUNT_LOOP_SB(floatAlign);
}





// ////////////////////////////////////
// Spectrum to XYZ
// ////////////////////////////////////

#define cml_SpectrumtoXYZ(out, in, observer) \
  out[0] = cmlFilterFunction(in, cmlGetObserverSpecDistFunction(observer, 0));\
  out[1] = cmlFilterFunction(in, cmlGetObserverSpecDistFunction(observer, 1));\
  out[2] = cmlFilterFunction(in, cmlGetObserverSpecDistFunction(observer, 2));\
  cmlMul3(out, cmlGetObserverRadiometricScale(observer));    

CML_HIDEF void cml_OneIlluminationSpectrumtoXYZ (CMLVec3 out, const CMLFunction* in, const CMLObserver* observer){
  cml_SpectrumtoXYZ(out, in, observer);
}

CML_HIDEF void cml_IlluminationSpectrumtoXYZ (CMLVec3 out, const CMLFunction* in, size_t count, CMLuint32 floatAlign, const CMLObserver* observer){
  cml__START_COUNT_LOOP(count);
  cml_OneIlluminationSpectrumtoXYZ(out, in, observer);
  cml__END_COUNT_LOOP(floatAlign, 1);
}

CML_HIDEF void cml_OneRemissionSpectrumtoXYZ (CMLVec3 out, const CMLFunction* in, const CMLFunction* specIll, const CMLObserver* observer){
  CMLFunction* remillfunction = cmlCreateFunctionMulFunction(in, specIll);
  cml_OneIlluminationSpectrumtoXYZ(out, remillfunction, observer);
  cmlReleaseFunction(remillfunction);
}

CML_HIDEF void cml_RemissionSpectrumtoXYZ (CMLVec3 out, const CMLFunction* in, size_t count, CMLuint32 floatAlign, const CMLFunction* specIll, const CMLObserver* observer){
  if(specIll){
    cml__START_COUNT_LOOP(count);
    cml_OneRemissionSpectrumtoXYZ(out, in, specIll, observer);
    cml__END_COUNT_LOOP(floatAlign, 1);
  }else{
    float base = cmlGetObserverColorimetricBase(observer) * .5f;
    cml__START_COUNT_LOOP(count);
    cmlSet3(out, base, base, base);
    cml__END_COUNT_LOOP(floatAlign, 1);
  }
}



// This is free and unencumbered software released into the public domain.

// Anyone is free to copy, modify, publish, use, compile, sell, or
// distribute this software, either in source code form or as a compiled
// binary, for any purpose, commercial or non-commercial, and by any
// means.

// In jurisdictions that recognize copyright laws, the author or authors
// of this software dedicate any and all copyright interest in the
// software to the public domain. We make this dedication for the benefit
// of the public at large and to the detriment of our heirs and
// successors. We intend this dedication to be an overt act of
// relinquishment in perpetuity of all present and future rights to this
// software under copyright law.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
// OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.

// For more information, please refer to <http://unlicense.org/>


#include <stdlib.h>

#if CML_COMPILE_ON_WIN
  #define CML_HIDDEN
  #define CML_RESTRICT    __restrict
#elif CML_COMPILE_ON_MAC
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
  CMLSize refcount;
  CMLSize paramcount;
  float* params;
  void* data;
  CMLDefinitionRange defrange;
  CMLFunctionEvaluator getValue;
  CMLFunctionDesctructor destruct;
};


struct CMLResponseCurve{
  CMLFunction* forwardfunc;     // converting from luminance space
  CMLFunction* backwardfunc;    // converting to luminance space
  CMLFunctionType functiontype;
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
  CMLVec3                       BALFwhitepointXYZ;
  CMLVec3                       BALFinverseWhitepointXYZ;
  CMLVec3                       BALFwhitepointYxy;
  CMLVec3                       BALFwhitepointYupvp;
};


CML_HIDDEN CMLResponseCurve* cmlCreateResponseCurve(CMLResponseCurve* curve);


CML_HIDDEN CML_INLINE static float cmlInternalEval(const CMLFunction* function, float x){
  return function->getValue(function->params, function->data, x);
}






static CML_INLINE void* cmlAllocate(CMLInt size){
  void* ptr; // Declaration before implementation.
  #ifndef NDEBUG
    if(size < 1)
      cmlError("cmlAllocate", "size is smaller than 1 .");
  #endif
  ptr = malloc(size);
  #ifndef NDEBUG
    if(!ptr)
      {cmlCrash("cmlAllocate", "out of memory."); exit(1); return CML_NULL;}
    // The exit call has been introduced as this is such a severe problem
    // that all functions rely on its functionality. Here, the debug version
    // differs from the non-debug version.
  #endif
  return ptr;
}


static CML_INLINE void* cmlAllocateIfNull(void* ptr, CMLInt size){
  #ifndef NDEBUG
    if(size < 1)
      cmlError("naAllocateIfNull", "size is smaller than 1 .");
  #endif
  if(ptr == CML_NULL){
    return cmlAllocate(size);
  }else{
    return ptr;
  }
}


#define CMLINTERNAL_START_COUNT_LOOP(count)\
  while(count){

#define CMLINTERNAL_END_COUNT_LOOP(outchannels, inchannels)\
    out += outchannels;\
    in += inchannels;\
    count--;\
  }
  
#define CMLINTERNAL_END_COUNT_LOOP_SB(numchannels)\
    buf += numchannels;\
    count--;\
  }


// ////////////////////////////////////
// XYZ to Yxy
// ////////////////////////////////////

#define CMLINTERNALXYZtoYxy(out, in, whitepointYxy) \
  float divisor;\
  divisor = (in[0] + in[1] + in[2]);\
  float Y = in[1];\
  if(divisor == 0.f){\
    if(whitepointYxy){\
      out[2] = whitepointYxy[2];\
      out[1] = whitepointYxy[1];\
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

CML_HIDDEN CML_INLINE static void cmlInternalOneXYZtoYxy (float* CML_RESTRICT out, const float* CML_RESTRICT in, const CMLVec3 whitepointYxy){
  CMLINTERNALXYZtoYxy(out, in, whitepointYxy);
}

CML_HIDDEN CML_INLINE static void cmlInternalOneXYZtoYxy_SB (float* CML_RESTRICT buf, const CMLVec3 whitepointYxy){
  CMLINTERNALXYZtoYxy(buf, buf, whitepointYxy);
}

CML_HIDDEN CML_INLINE static void cmlInternalXYZtoYxy (float* CML_RESTRICT out, const float* CML_RESTRICT in, const CMLVec3 whitepointYxy, CMLuint32 count){
  CMLINTERNAL_START_COUNT_LOOP(count);
  cmlInternalOneXYZtoYxy(out, in, whitepointYxy);
  CMLINTERNAL_END_COUNT_LOOP(CML_Yxy_NUMCHANNELS, CML_XYZ_NUMCHANNELS);
}

CML_HIDDEN CML_INLINE static void cmlInternalXYZtoYxy_SB (float* CML_RESTRICT buf, const CMLVec3 whitepointYxy, CMLuint32 count, CMLuint32 floatalign){
  CMLINTERNAL_START_COUNT_LOOP(count);
  cmlInternalOneXYZtoYxy_SB(buf, whitepointYxy);
  CMLINTERNAL_END_COUNT_LOOP_SB(floatalign);
}


// ////////////////////////////////////
// XYZ to RGB
// ////////////////////////////////////

// todo: make mulVec SB
#define CMLINTERNALXYZtoRGB(out, in, XYZtoRGBmatrix, LineartoRResponse, LineartoGResponse, LineartoBResponse) \
  CMLVec3 RGBp;\
  cmlMat33MulVec3(RGBp, XYZtoRGBmatrix, in);\
  out[0] = cmlInternalEval(LineartoRResponse, RGBp[0]);\
  out[1] = cmlInternalEval(LineartoGResponse, RGBp[1]);\
  out[2] = cmlInternalEval(LineartoBResponse, RGBp[2]);

CML_HIDDEN CML_INLINE static void cmlInternalOneXYZtoRGB (float* CML_RESTRICT out , const float* CML_RESTRICT in, const CMLMat33 XYZtoRGBmatrix, const CMLFunction* LineartoRResponse, const CMLFunction* LineartoGResponse, const CMLFunction* LineartoBResponse){
  CMLINTERNALXYZtoRGB(out, in, XYZtoRGBmatrix, LineartoRResponse, LineartoGResponse, LineartoBResponse);
}

CML_HIDDEN CML_INLINE static void cmlInternalOneXYZtoRGB_SB (float* buf, const CMLMat33 XYZtoRGBmatrix, const CMLFunction* LineartoRResponse, const CMLFunction* LineartoGResponse, const CMLFunction* LineartoBResponse){
  CMLINTERNALXYZtoRGB(buf, buf, XYZtoRGBmatrix, LineartoRResponse, LineartoGResponse, LineartoBResponse);
}

CML_HIDDEN CML_INLINE static void cmlInternalXYZtoRGB (float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count, const CMLMat33 XYZtoRGBmatrix, const CMLFunction* LineartoRResponse, const CMLFunction* LineartoGResponse, const CMLFunction* LineartoBResponse){
  CMLINTERNAL_START_COUNT_LOOP(count);
  cmlInternalOneXYZtoRGB(out, in, XYZtoRGBmatrix, LineartoRResponse, LineartoGResponse, LineartoBResponse);
  CMLINTERNAL_END_COUNT_LOOP(CML_RGB_NUMCHANNELS, CML_XYZ_NUMCHANNELS);
}

CML_HIDDEN CML_INLINE static void cmlInternalXYZtoRGB_SB (float* buf, CMLuint32 count, CMLuint32 floatalign, const CMLMat33 XYZtoRGBmatrix, const CMLFunction* LineartoRResponse, const CMLFunction* LineartoGResponse, const CMLFunction* LineartoBResponse){
  CMLINTERNAL_START_COUNT_LOOP(count);
  cmlInternalOneXYZtoRGB_SB(buf, XYZtoRGBmatrix, LineartoRResponse, LineartoGResponse, LineartoBResponse);
  CMLINTERNAL_END_COUNT_LOOP_SB(floatalign);
}


// ////////////////////////////////////
// Yxy to XYZ
// ////////////////////////////////////

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

CML_HIDDEN CML_INLINE static void cmlInternalOneYxytoXYZ (float* CML_RESTRICT out , const float* CML_RESTRICT in, const CMLVec3 whitepointXYZ){
  CMLINTERNALYxytoXYZ(out, in, whitepointXYZ);
}

CML_HIDDEN CML_INLINE static void cmlInternalOneYxytoXYZ_SB(float* buf, const CMLVec3 whitepointXYZ){
  CMLINTERNALYxytoXYZ(buf, buf, whitepointXYZ);
}

CML_HIDDEN CML_INLINE static void cmlInternalYxytoXYZ (float* CML_RESTRICT out , const float* CML_RESTRICT in, const CMLVec3 whitepointXYZ, CMLuint32 count){
  CMLINTERNAL_START_COUNT_LOOP(count);
  cmlInternalOneYxytoXYZ(out, in, whitepointXYZ);
  CMLINTERNAL_END_COUNT_LOOP(CML_XYZ_NUMCHANNELS, CML_Yxy_NUMCHANNELS);
}

CML_HIDDEN CML_INLINE static void cmlInternalYxytoXYZ_SB(float* buf, const CMLVec3 whitepointXYZ, CMLuint32 count, CMLuint32 floatalign){
  CMLINTERNAL_START_COUNT_LOOP(count);
  cmlInternalOneYxytoXYZ_SB(buf, whitepointXYZ);
  CMLINTERNAL_END_COUNT_LOOP_SB(floatalign);
}

// ////////////////////////////////////
// Yupvp to Yxy
// ////////////////////////////////////


#define CMLINTERNALYupvptoYxy(out, in, whitepointYxy) \
  float divisor;\
  out[0] = in[0];\
  divisor = 6.f * in[1] - 16.f * in[2] + 12.f;\
  if(divisor == 0.f){\
    if(whitepointYxy){\
      out[1] = whitepointYxy[1];\
      out[2] = whitepointYxy[2];\
    }else{\
      out[1] = 0.f;\
      out[2] = 0.f;\
    }\
  }else{\
    float factor = cmlInverse(divisor);\
    out[1] = 9.f * in[1] * factor;\
    out[2] = 4.f * in[2] * factor;\
  }

CML_HIDDEN CML_INLINE static void cmlInternalOneYupvptoYxy (float* CML_RESTRICT out , const float* CML_RESTRICT in, const CMLVec3 whitepointYxy){
  CMLINTERNALYupvptoYxy(out, in, whitepointYxy);
}
CML_HIDDEN CML_INLINE static void cmlInternalOneYupvptoYxy_SB(float* buf, const CMLVec3 whitepointYxy){
  CMLINTERNALYupvptoYxy(buf, buf, whitepointYxy);
}

CML_HIDDEN CML_INLINE static void cmlInternalYupvptoYxy (float* CML_RESTRICT out , const float* CML_RESTRICT in, const CMLVec3 whitepointYxy, CMLuint32 count){
  CMLINTERNAL_START_COUNT_LOOP(count);
  cmlInternalOneYupvptoYxy(out, in, whitepointYxy);
  CMLINTERNAL_END_COUNT_LOOP(CML_Yxy_NUMCHANNELS, CML_Yupvp_NUMCHANNELS);
}

CML_HIDDEN CML_INLINE static void cmlInternalYupvptoYxy_SB(float* buf, const CMLVec3 whitepointYxy, CMLuint32 count, CMLuint32 floatalign){
  CMLINTERNAL_START_COUNT_LOOP(count);
  cmlInternalOneYupvptoYxy_SB(buf, whitepointYxy);
  CMLINTERNAL_END_COUNT_LOOP_SB(floatalign);
}


// ////////////////////////////////////
// Luv to Yupvp
// ////////////////////////////////////

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

CML_HIDDEN CML_INLINE static void cmlInternalOneLuvtoYupvp (float* CML_RESTRICT out , const float* CML_RESTRICT in, const CMLVec3 whitepointYupvp, const CMLFunction* LtoLinearResponse){
  CMLINTERNALLuvtoYupvp(out, in, whitepointYupvp, LtoLinearResponse);
}
CML_HIDDEN CML_INLINE static void cmlInternalOneLuvtoYupvp_SB (float* buf, const CMLVec3 whitepointYupvp, const CMLFunction* LtoLinearResponse){
  CMLINTERNALLuvtoYupvp(buf, buf, whitepointYupvp, LtoLinearResponse);
}

CML_HIDDEN CML_INLINE static void cmlInternalLuvtoYupvp (float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count, const CMLVec3 whitepointYupvp, const CMLFunction* LtoLinearResponse){
  CMLINTERNAL_START_COUNT_LOOP(count);
  cmlInternalOneLuvtoYupvp(out, in, whitepointYupvp, LtoLinearResponse);
  CMLINTERNAL_END_COUNT_LOOP(CML_Yupvp_NUMCHANNELS, CML_Luv_NUMCHANNELS);
}

CML_HIDDEN CML_INLINE static void cmlInternalLuvtoYupvp_SB (float* buf, CMLuint32 count, CMLuint32 floatalign, const CMLVec3 whitepointYupvp, const CMLFunction* LtoLinearResponse){
  CMLINTERNAL_START_COUNT_LOOP(count);
  cmlInternalOneLuvtoYupvp_SB(buf, whitepointYupvp, LtoLinearResponse);
  CMLINTERNAL_END_COUNT_LOOP_SB(floatalign);
}



// ////////////////////////////////////
// Yxy to Yupvp
// ////////////////////////////////////


#define CMLINTERNALYxytoYupvp(out, in, whitepointYupvp) \
  float divisor;\
  out[0] = in[0];\
  divisor = -2.f * in[1] + 12.f * in[2] + 3.f;\
  if(divisor == 0.f){\
    if(whitepointYupvp){\
      out[1] = whitepointYupvp[1];\
      out[2] = whitepointYupvp[2];\
    }else{\
      out[1] = 0.f;\
      out[2] = 0.f;\
    }\
  }else{\
    float factor = cmlInverse(divisor);\
    out[1] = 4.f * in[1] * factor;\
    out[2] = 9.f * in[2] * factor;\
  }\

CML_HIDDEN CML_INLINE static void cmlInternalOneYxytoYupvp(float* CML_RESTRICT out , const float* CML_RESTRICT in, const CMLVec3 whitepointYupvp){
  CMLINTERNALYxytoYupvp(out, in, whitepointYupvp);
}

CML_HIDDEN CML_INLINE static void cmlInternalOneYxytoYupvp_SB(float* buf, const CMLVec3 whitepointYupvp){
  CMLINTERNALYxytoYupvp(buf, buf, whitepointYupvp);
}

CML_HIDDEN CML_INLINE static void cmlInternalYxytoYupvp(float* CML_RESTRICT out , const float* CML_RESTRICT in, const CMLVec3 whitepointYupvp, CMLuint32 count){
  CMLINTERNAL_START_COUNT_LOOP(count);
  cmlInternalOneYxytoYupvp(out, in, whitepointYupvp);
  CMLINTERNAL_END_COUNT_LOOP(CML_Yupvp_NUMCHANNELS, CML_Yxy_NUMCHANNELS);
}

CML_HIDDEN CML_INLINE static void cmlInternalYxytoYupvp_SB(float* buf, const CMLVec3 whitepointYupvp, CMLuint32 count, CMLuint32 floatalign){
  CMLINTERNAL_START_COUNT_LOOP(count);
  cmlInternalOneYxytoYupvp_SB(buf, whitepointYupvp);
  CMLINTERNAL_END_COUNT_LOOP_SB(floatalign);
}



// ////////////////////////////////////
// Yupvp to Luv
// ////////////////////////////////////

#define CMLINTERNALYupvptoLuv(out, in, whitepointYupvp, LineartoLResponse) \
  float yr = in[0] / whitepointYupvp[0];\
  float fy = cmlInternalEval(LineartoLResponse, yr);\
  out[0] = 100.f * fy;\
  out[1] = 13.f * out[0] * (in[1] - whitepointYupvp[1]);\
  out[2] = 13.f * out[0] * (in[2] - whitepointYupvp[2]);

CML_HIDDEN CML_INLINE static void cmlInternalOneYupvptoLuv (float* CML_RESTRICT out , const float* CML_RESTRICT in, const CMLVec3 whitepointYupvp, const CMLFunction* LineartoLResponse){
  CMLINTERNALYupvptoLuv(out, in, whitepointYupvp, LineartoLResponse);
}

CML_HIDDEN CML_INLINE static void cmlInternalOneYupvptoLuv_SB (float* buf, const CMLVec3 whitepointYupvp, const CMLFunction* LineartoLResponse){
  CMLINTERNALYupvptoLuv(buf, buf, whitepointYupvp, LineartoLResponse);
}

CML_HIDDEN CML_INLINE static void cmlInternalYupvptoLuv (float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count, const CMLVec3 whitepointYupvp, const CMLFunction* LineartoLResponse){
  CMLINTERNAL_START_COUNT_LOOP(count);
  cmlInternalOneYupvptoLuv(out, in, whitepointYupvp, LineartoLResponse);
  CMLINTERNAL_END_COUNT_LOOP(CML_Luv_NUMCHANNELS, CML_Yupvp_NUMCHANNELS);
}

CML_HIDDEN CML_INLINE static void cmlInternalYupvptoLuv_SB (float* buf, CMLuint32 count, CMLuint32 floatalign, const CMLVec3 whitepointYupvp, const CMLFunction* LineartoLResponse){
  CMLINTERNAL_START_COUNT_LOOP(count);
  cmlInternalOneYupvptoLuv_SB(buf, whitepointYupvp, LineartoLResponse);
  CMLINTERNAL_END_COUNT_LOOP_SB(floatalign);
}


// ////////////////////////////////////
// Yupvp to Luv
// ////////////////////////////////////

#define CMLINTERNALYuvtoYupvp(out, in) \
  out[0] = in[0];\
  out[1] = in[1];\
  out[2] = in[2] * 1.5f;

CML_HIDDEN CML_INLINE static void cmlInternalOneYuvtoYupvp (float* CML_RESTRICT out , const float* CML_RESTRICT in){
  CMLINTERNALYuvtoYupvp(out, in);
}
CML_HIDDEN CML_INLINE static void cmlInternalOneYuvtoYupvp_SB (float* buf){
  CMLINTERNALYuvtoYupvp(buf, buf);
}

CML_HIDDEN CML_INLINE static void cmlInternalYuvtoYupvp (float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count){
  CMLINTERNAL_START_COUNT_LOOP(count);
  cmlInternalOneYuvtoYupvp(out, in);
  CMLINTERNAL_END_COUNT_LOOP(CML_Yupvp_NUMCHANNELS, CML_Yuv_NUMCHANNELS);
}

CML_HIDDEN CML_INLINE static void cmlInternalYuvtoYupvp_SB (float* buf, CMLuint32 count, CMLuint32 floatalign){
  CMLINTERNAL_START_COUNT_LOOP(count);
  cmlInternalOneYuvtoYupvp_SB(buf);
  CMLINTERNAL_END_COUNT_LOOP_SB(floatalign);
}


// ////////////////////////////////////
// Luv to Yupvp
// ////////////////////////////////////

#define CMLINTERNALYupvptoYuv(out, in) \
  out[0] = in[0];\
  out[1] = in[1];\
  out[2] = in[2] * 0.666666666666667f;

CML_HIDDEN CML_INLINE static void cmlInternalOneYupvptoYuv (float* CML_RESTRICT out , const float* CML_RESTRICT in){
  CMLINTERNALYupvptoYuv(out, in);
}
CML_HIDDEN CML_INLINE static void cmlInternalOneYupvptoYuv_SB (float* buf){
  CMLINTERNALYupvptoYuv(buf, buf);
}

CML_HIDDEN CML_INLINE static void cmlInternalYupvptoYuv (float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count){
  CMLINTERNAL_START_COUNT_LOOP(count);
  cmlInternalOneYupvptoYuv(out, in);
  CMLINTERNAL_END_COUNT_LOOP(CML_Yuv_NUMCHANNELS, CML_Yupvp_NUMCHANNELS);
}

CML_HIDDEN CML_INLINE static void cmlInternalYupvptoYuv_SB (float* buf, CMLuint32 count, CMLuint32 floatalign){
  CMLINTERNAL_START_COUNT_LOOP(count);
  cmlInternalOneYupvptoYuv_SB(buf);
  CMLINTERNAL_END_COUNT_LOOP_SB(floatalign);
}


// ////////////////////////////////////
// Lab to Lch
// ////////////////////////////////////

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

CML_HIDDEN CML_INLINE static void cmlInternalOneLabtoLch (float* CML_RESTRICT out , const float* CML_RESTRICT in){
  CMLINTERNALLabtoLch(out, in);
}
CML_HIDDEN CML_INLINE static void cmlInternalOneLabtoLch_SB (float* buf){
  CMLINTERNALLabtoLch(buf, buf);
}

CML_HIDDEN CML_INLINE static void cmlInternalLabtoLch (float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count ){
  CMLINTERNAL_START_COUNT_LOOP(count);
  cmlInternalOneLabtoLch(out, in);
  CMLINTERNAL_END_COUNT_LOOP(CML_Lch_NUMCHANNELS, CML_Lab_NUMCHANNELS);
}

CML_HIDDEN CML_INLINE static void cmlInternalLabtoLch_SB (float* buf, CMLuint32 count, CMLuint32 floatalign){
  CMLINTERNAL_START_COUNT_LOOP(count);
  cmlInternalOneLabtoLch_SB(buf);
  CMLINTERNAL_END_COUNT_LOOP_SB(floatalign);
}


// ////////////////////////////////////
// RGB to XYZ
// ////////////////////////////////////

// todo: make mulVec SB
#define CMLINTERNALRGBtoXYZ(out, in, RGBtoXYZmatrix, RtoLinearResponse, GtoLinearResponse, BtoLinearResponse) \
  float RGBp[3];\
  RGBp[0] = cmlInternalEval(RtoLinearResponse, in[0]);\
  RGBp[1] = cmlInternalEval(GtoLinearResponse, in[1]);\
  RGBp[2] = cmlInternalEval(BtoLinearResponse, in[2]);\
  cmlMat33MulVec3(out, RGBtoXYZmatrix, RGBp);

CML_HIDDEN CML_INLINE static void cmlInternalOneRGBtoXYZ (float* CML_RESTRICT out , const float* CML_RESTRICT in, const CMLMat33 RGBtoXYZmatrix, const CMLFunction* RtoLinearResponse, const CMLFunction* GtoLinearResponse, const CMLFunction* BtoLinearResponse){
  CMLINTERNALRGBtoXYZ(out, in, RGBtoXYZmatrix, RtoLinearResponse, GtoLinearResponse, BtoLinearResponse);
}
CML_HIDDEN CML_INLINE static void cmlInternalOneRGBtoXYZ_SB (float* buf, const CMLMat33 RGBtoXYZmatrix, const CMLFunction* RtoLinearResponse, const CMLFunction* GtoLinearResponse, const CMLFunction* BtoLinearResponse){
  CMLINTERNALRGBtoXYZ(buf, buf, RGBtoXYZmatrix, RtoLinearResponse, GtoLinearResponse, BtoLinearResponse);
}

CML_HIDDEN CML_INLINE static void cmlInternalRGBtoXYZ (float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count, const CMLMat33 RGBtoXYZmatrix, const CMLFunction* RtoLinearResponse, const CMLFunction* GtoLinearResponse, const CMLFunction* BtoLinearResponse){
  CMLINTERNAL_START_COUNT_LOOP(count);
  cmlInternalOneRGBtoXYZ(out, in, RGBtoXYZmatrix, RtoLinearResponse, GtoLinearResponse, BtoLinearResponse);
  CMLINTERNAL_END_COUNT_LOOP(CML_XYZ_NUMCHANNELS, CML_RGB_NUMCHANNELS);
}

CML_HIDDEN CML_INLINE static void cmlInternalRGBtoXYZ_SB (float* buf, CMLuint32 count, CMLuint32 floatalign, const CMLMat33 RGBtoXYZmatrix, const CMLFunction* RtoLinearResponse, const CMLFunction* GtoLinearResponse, const CMLFunction* BtoLinearResponse){
  CMLINTERNAL_START_COUNT_LOOP(count);
  cmlInternalOneRGBtoXYZ_SB(buf, RGBtoXYZmatrix, RtoLinearResponse, GtoLinearResponse, BtoLinearResponse);
  CMLINTERNAL_END_COUNT_LOOP_SB(floatalign);
}


// ////////////////////////////////////
// RGB to YCbCr
// ////////////////////////////////////

#define CMLINTERNALRGBtoYCbCr(out, in, redprimaryYxy, blueprimaryYxy, inversewhitepointXYZ) \
  float Kr = redprimaryYxy[0] * inversewhitepointXYZ[1];\
  float Kb = blueprimaryYxy[0] * inversewhitepointXYZ[1];\
  float Y = Kr * in[0] + (1.f - Kr - Kb) * in[1] + Kb * in[2];\
  out[1] = .5f * (in[2] - Y) / (1.f - Kb);\
  out[2] = .5f * (in[0] - Y) / (1.f - Kr);\
  out[0] = Y;

CML_HIDDEN CML_INLINE static void cmlInternalOneRGBtoYCbCr (float* CML_RESTRICT out , const float* CML_RESTRICT in, const CMLVec3 redprimaryYxy, const CMLVec3 blueprimaryYxy, const CMLVec3 inversewhitepointXYZ){
  CMLINTERNALRGBtoYCbCr(out, in, redprimaryYxy, blueprimaryYxy, inversewhitepointXYZ);
}
CML_HIDDEN CML_INLINE static void cmlInternalOneRGBtoYCbCr_SB (float* buf, const CMLVec3 redprimaryYxy, const CMLVec3 blueprimaryYxy, const CMLVec3 inversewhitepointXYZ){
  CMLINTERNALRGBtoYCbCr(buf, buf, redprimaryYxy, blueprimaryYxy, inversewhitepointXYZ);
}

CML_HIDDEN CML_INLINE static void cmlInternalRGBtoYCbCr (float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count, const CMLVec3 redprimaryYxy, const CMLVec3 blueprimaryYxy, const CMLVec3 inversewhitepointXYZ){
  CMLINTERNAL_START_COUNT_LOOP(count);
  cmlInternalOneRGBtoYCbCr(out, in, redprimaryYxy, blueprimaryYxy, inversewhitepointXYZ);
  CMLINTERNAL_END_COUNT_LOOP(CML_YCbCr_NUMCHANNELS, CML_RGB_NUMCHANNELS);
}

CML_HIDDEN CML_INLINE static void cmlInternalRGBtoYCbCr_SB (float* buf, CMLuint32 count, CMLuint32 floatalign, const CMLVec3 redprimaryYxy, const CMLVec3 blueprimaryYxy, const CMLVec3 inversewhitepointXYZ){
  CMLINTERNAL_START_COUNT_LOOP(count);
  cmlInternalOneRGBtoYCbCr_SB(buf, redprimaryYxy, blueprimaryYxy, inversewhitepointXYZ);
  CMLINTERNAL_END_COUNT_LOOP_SB(floatalign);
}


// ////////////////////////////////////
// HSV to HSL
// ////////////////////////////////////

#define CMLINTERNALHSVtoHSL(out, in) \
  out[0] = in[0];\
  out[1] = in[1] * in[2];\
  out[2] = in[2] - 0.5f * out[1];


CML_HIDDEN CML_INLINE static void cmlInternalOneHSVtoHSL (float* CML_RESTRICT out , const float* CML_RESTRICT in){
  CMLINTERNALHSVtoHSL(out, in);
}
CML_HIDDEN CML_INLINE static void cmlInternalOneHSVtoHSL_SB (float* buf){
  CMLINTERNALHSVtoHSL(buf, buf);
}

CML_HIDDEN CML_INLINE static void cmlInternalHSVtoHSL (float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count ){
  CMLINTERNAL_START_COUNT_LOOP(count);
  cmlInternalOneHSVtoHSL(out, in);
  CMLINTERNAL_END_COUNT_LOOP(CML_HSL_NUMCHANNELS, CML_HSV_NUMCHANNELS);
}

CML_HIDDEN CML_INLINE static void cmlInternalHSVtoHSL_SB (float* buf, CMLuint32 count, CMLuint32 floatalign){
  CMLINTERNAL_START_COUNT_LOOP(count);
  cmlInternalOneHSVtoHSL_SB(buf);
  CMLINTERNAL_END_COUNT_LOOP_SB(floatalign);
}


// ////////////////////////////////////
// Lch to Lab
// ////////////////////////////////////

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

CML_HIDDEN CML_INLINE static void cmlInternalOneLchtoLab(float* CML_RESTRICT out , const float* CML_RESTRICT in){
  CMLINTERNALLchtoLab(out, in);
}
CML_HIDDEN CML_INLINE static void cmlInternalOneLchtoLab_SB(float* buf){
  CMLINTERNALLchtoLab(buf, buf);
}

CML_HIDDEN CML_INLINE static void cmlInternalLchtoLab(float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count){
  CMLINTERNAL_START_COUNT_LOOP(count);
  cmlInternalOneLchtoLab(out, in);
  CMLINTERNAL_END_COUNT_LOOP(CML_Lab_NUMCHANNELS, CML_Lch_NUMCHANNELS);
}

CML_HIDDEN CML_INLINE static void cmlInternalLchtoLab_SB(float* buf, CMLuint32 count, CMLuint32 floatalign){
  CMLINTERNAL_START_COUNT_LOOP(count);
  cmlInternalOneLchtoLab_SB(buf);
  CMLINTERNAL_END_COUNT_LOOP_SB(floatalign);
}


// ////////////////////////////////////
// YCbCr to RGB
// ////////////////////////////////////

#define CMLINTERNALYCbCrtoRGB(out, in, redprimaryYxy, blueprimaryYxy, inversewhitepointXYZ) \
  float Kr = redprimaryYxy[0] * inversewhitepointXYZ[1];\
  float Kb = blueprimaryYxy[0] * inversewhitepointXYZ[1];\
  float Y = in[0];\
  out[0] = 2.f * in[2] * (1.f - Kr) + Y;\
  out[2] = 2.f * in[1] * (1.f - Kb) + Y;\
  out[1] = (Y - Kr * out[0] - Kb * out[2]) / (1.f - Kr - Kb);


CML_HIDDEN CML_INLINE static void cmlInternalOneYCbCrtoRGB (float* CML_RESTRICT out , const float* CML_RESTRICT in, const CMLVec3 redprimaryYxy, const CMLVec3 blueprimaryYxy, const CMLVec3 inversewhitepointXYZ){
  CMLINTERNALYCbCrtoRGB(out, in, redprimaryYxy, blueprimaryYxy, inversewhitepointXYZ);
}
CML_HIDDEN CML_INLINE static void cmlInternalOneYCbCrtoRGB_SB (float* buf, const CMLVec3 redprimaryYxy, const CMLVec3 blueprimaryYxy, const CMLVec3 inversewhitepointXYZ){
  CMLINTERNALYCbCrtoRGB(buf, buf, redprimaryYxy, blueprimaryYxy, inversewhitepointXYZ);
}

CML_HIDDEN CML_INLINE static void cmlInternalYCbCrtoRGB (float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count, const CMLVec3 redprimaryYxy, const CMLVec3 blueprimaryYxy, const CMLVec3 inversewhitepointXYZ){
  CMLINTERNAL_START_COUNT_LOOP(count);
  cmlInternalOneYCbCrtoRGB(out, in, redprimaryYxy, blueprimaryYxy, inversewhitepointXYZ);
  CMLINTERNAL_END_COUNT_LOOP(CML_RGB_NUMCHANNELS, CML_YCbCr_NUMCHANNELS);
}

CML_HIDDEN CML_INLINE static void cmlInternalYCbCrtoRGB_SB (float* buf, CMLuint32 count, CMLuint32 floatalign, const CMLVec3 redprimaryYxy, const CMLVec3 blueprimaryYxy, const CMLVec3 inversewhitepointXYZ){
  CMLINTERNAL_START_COUNT_LOOP(count);
  cmlInternalOneYCbCrtoRGB_SB(buf, redprimaryYxy, blueprimaryYxy, inversewhitepointXYZ);
  CMLINTERNAL_END_COUNT_LOOP_SB(floatalign);
}


// ////////////////////////////////////
// HSL to HSV
// ////////////////////////////////////

#define CMLINTERNALHSLtoHSV(out, in) \
  out[0] = in[0];\
  out[2] = in[2] + .5f * in[1];\
  if(out[2] == 0.f){\
    out[1] = in[1] / CML_SINGULARITY;\
  }else{\
    out[1] = in[1] / out[2];\
  }

CML_HIDDEN CML_INLINE static void cmlInternalOneHSLtoHSV (float* CML_RESTRICT out , const float* CML_RESTRICT in){
  CMLINTERNALHSLtoHSV(out, in);
}
CML_HIDDEN CML_INLINE static void cmlInternalOneHSLtoHSV_SB (float* buf){
  CMLINTERNALHSLtoHSV(buf, buf);
}

CML_HIDDEN CML_INLINE static void cmlInternalHSLtoHSV (float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count){
  CMLINTERNAL_START_COUNT_LOOP(count);
  cmlInternalOneHSLtoHSV(out, in);
  CMLINTERNAL_END_COUNT_LOOP(CML_HSV_NUMCHANNELS, CML_HSL_NUMCHANNELS);
}

CML_HIDDEN CML_INLINE static void cmlInternalHSLtoHSV_SB (float* buf, CMLuint32 count, CMLuint32 floatalign){
  CMLINTERNAL_START_COUNT_LOOP(count);
  cmlInternalOneHSLtoHSV_SB(buf);
  CMLINTERNAL_END_COUNT_LOOP_SB(floatalign);
}


// ////////////////////////////////////
// RGB to HSV
// ////////////////////////////////////

// todo: Make it SB
#define CMLINTERNALRGBtoHSV(out, in) \
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
  if(CMLAlmostZero(range)){\
    out[0] = 0.f;\
  }else{\
    float invrange = cmlInverse(range);\
    if(out[2] == rgb[0])      {out[0] = 60.f * (0.f + (rgb[1]-rgb[2]) * invrange);}\
    else if(out[2] == rgb[1]) {out[0] = 60.f * (2.f + (rgb[2]-rgb[0]) * invrange);}\
    else                      {out[0] = 60.f * (4.f + (rgb[0]-rgb[1]) * invrange);}\
    if(out[0] < 0.f){out[0] += 360.f;}\
  }

CML_HIDDEN CML_INLINE static void cmlInternalOneRGBtoHSV (float* CML_RESTRICT out , const float* CML_RESTRICT in){
  CMLINTERNALRGBtoHSV(out, in);
}
CML_HIDDEN CML_INLINE static void cmlInternalOneRGBtoHSV_SB (float* buf){
  CMLINTERNALRGBtoHSV(buf, buf);
}

CML_HIDDEN CML_INLINE static void cmlInternalRGBtoHSV (float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count){
  CMLINTERNAL_START_COUNT_LOOP(count);
  cmlInternalOneRGBtoHSV(out, in);
  CMLINTERNAL_END_COUNT_LOOP(CML_HSV_NUMCHANNELS, CML_RGB_NUMCHANNELS);
}

CML_HIDDEN CML_INLINE static void cmlInternalRGBtoHSV_SB (float* buf, CMLuint32 count, CMLuint32 floatalign){
  CMLINTERNAL_START_COUNT_LOOP(count);
  cmlInternalOneRGBtoHSV_SB(buf);
  CMLINTERNAL_END_COUNT_LOOP_SB(floatalign);
}


// ////////////////////////////////////
// HSV to RGB
// ////////////////////////////////////

// todo: Make it SB
#define CMLINTERNALHSVtoRGB(out, in) \
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

CML_HIDDEN CML_INLINE static void cmlInternalOneHSVtoRGB (float* CML_RESTRICT out , const float* CML_RESTRICT in){
  CMLINTERNALHSVtoRGB(out, in);
}
CML_HIDDEN CML_INLINE static void cmlInternalOneHSVtoRGB_SB (float* buf){
  CMLINTERNALHSVtoRGB(buf, buf);
}

CML_HIDDEN CML_INLINE static void cmlInternalHSVtoRGB (float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count){
  CMLINTERNAL_START_COUNT_LOOP(count);
  cmlInternalOneHSVtoRGB(out, in);
  CMLINTERNAL_END_COUNT_LOOP(CML_RGB_NUMCHANNELS, CML_HSV_NUMCHANNELS);
}

CML_HIDDEN CML_INLINE static void cmlInternalHSVtoRGB_SB (float* buf, CMLuint32 count, CMLuint32 floatalign){
  CMLINTERNAL_START_COUNT_LOOP(count);
  cmlInternalOneHSVtoRGB_SB(buf);
  CMLINTERNAL_END_COUNT_LOOP_SB(floatalign);
}


// ////////////////////////////////////
// Lr to fy and fy to Lr
// ////////////////////////////////////

#define CML_LSTAR_TRANSFORM_OFFSET    0.16f
#define CML_LSTAR_TRANSFORM_SCALE     1.16f
#define CML_LSTAR_TRANSFORM_INV_SCALE 0.8620689655172f

CML_HIDDEN CML_INLINE static float cmlInternalLrtofy(float Lr){
  return (Lr + CML_LSTAR_TRANSFORM_OFFSET) * CML_LSTAR_TRANSFORM_INV_SCALE;
}

CML_HIDDEN CML_INLINE static float cmlInternalfytoLr(float fy){
  return fy * CML_LSTAR_TRANSFORM_SCALE - CML_LSTAR_TRANSFORM_OFFSET;
}


// ////////////////////////////////////
// XYZ to CIELAB
// ////////////////////////////////////

#define CMLINTERNALXYZtoCIELAB(out, in, inverseWhitepointXYZ, LineartoLResponse) \
  float xr = in[0] * inverseWhitepointXYZ[0];\
  float yr = in[1] * inverseWhitepointXYZ[1];\
  float zr = in[2] * inverseWhitepointXYZ[2];\
  float fx = cmlInternalLrtofy(cmlInternalEval(LineartoLResponse, xr));\
  float fy = cmlInternalLrtofy(cmlInternalEval(LineartoLResponse, yr));\
  float fz = cmlInternalLrtofy(cmlInternalEval(LineartoLResponse, zr));\
  out[0] = 100.f * cmlInternalfytoLr(fy);\
  out[1] = (fx - fy) * 500.f;\
  out[2] = (fy - fz) * 200.f;


CML_HIDDEN CML_INLINE static void cmlInternalOneXYZtoCIELAB(float* CML_RESTRICT out, const float* CML_RESTRICT in , const CMLVec3 inverseWhitepointXYZ, const CMLFunction* LineartoLResponse){
  CMLINTERNALXYZtoCIELAB(out, in, inverseWhitepointXYZ, LineartoLResponse);
}
CML_HIDDEN CML_INLINE static void cmlInternalOneXYZtoCIELAB_SB(float* buf, const CMLVec3 inverseWhitepointXYZ, const CMLFunction* LineartoLResponse){
  CMLINTERNALXYZtoCIELAB(buf, buf, inverseWhitepointXYZ, LineartoLResponse);
}

CML_HIDDEN CML_INLINE static void cmlInternalXYZtoCIELAB(float* CML_RESTRICT out, const float* CML_RESTRICT in, CMLuint32 count , const CMLVec3 inverseWhitepointXYZ, const CMLFunction* LineartoLResponse){
  CMLINTERNAL_START_COUNT_LOOP(count);
  cmlInternalOneXYZtoCIELAB(out, in, inverseWhitepointXYZ, LineartoLResponse);
  CMLINTERNAL_END_COUNT_LOOP(CML_Lab_NUMCHANNELS, CML_XYZ_NUMCHANNELS);
}

CML_HIDDEN CML_INLINE static void cmlInternalXYZtoCIELAB_SB(float* buf, CMLuint32 count, CMLuint32 floatalign, const CMLVec3 inverseWhitepointXYZ, const CMLFunction* LineartoLResponse){
  CMLINTERNAL_START_COUNT_LOOP(count);
  cmlInternalOneXYZtoCIELAB_SB(buf, inverseWhitepointXYZ, LineartoLResponse);
  CMLINTERNAL_END_COUNT_LOOP_SB(floatalign);
}


// ////////////////////////////////////
// CIELAB to XYZ
// ////////////////////////////////////

#define CMLINTERNALCIELABtoXYZ(out, in, whitepointXYZ, LtoLinearResponse) \
    float fy = cmlInternalLrtofy(.01f * in[0]);\
    float fx = fy + in[1] * .002f;\
    float fz = fy - in[2] * .005f;\
    float xr = cmlInternalEval(LtoLinearResponse, cmlInternalfytoLr(fx));\
    float yr = cmlInternalEval(LtoLinearResponse, cmlInternalfytoLr(fy));\
    float zr = cmlInternalEval(LtoLinearResponse, cmlInternalfytoLr(fz));\
    out[0] = xr * whitepointXYZ[0];\
    out[1] = yr * whitepointXYZ[1];\
    out[2] = zr * whitepointXYZ[2];


CML_HIDDEN CML_INLINE static void cmlInternalOneCIELABtoXYZ (float* CML_RESTRICT out , const float* CML_RESTRICT in, const CMLVec3 whitepointXYZ, const CMLFunction* LtoLinearResponse){
  CMLINTERNALCIELABtoXYZ(out, in, whitepointXYZ, LtoLinearResponse);
}
CML_HIDDEN CML_INLINE static void cmlInternalOneCIELABtoXYZ_SB (float* buf, const CMLVec3 whitepointXYZ, const CMLFunction* LtoLinearResponse){
  CMLINTERNALCIELABtoXYZ(buf, buf, whitepointXYZ, LtoLinearResponse);
}

CML_HIDDEN CML_INLINE static void cmlInternalCIELABtoXYZ (float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count, const CMLVec3 whitepointXYZ, const CMLFunction* LtoLinearResponse){
  CMLINTERNAL_START_COUNT_LOOP(count);
  cmlInternalOneCIELABtoXYZ(out, in, whitepointXYZ, LtoLinearResponse);
  CMLINTERNAL_END_COUNT_LOOP(CML_XYZ_NUMCHANNELS, CML_Lab_NUMCHANNELS);
}


CML_HIDDEN CML_INLINE static void cmlInternalCIELABtoXYZ_SB (float* buf , CMLuint32 count, CMLuint32 floatalign, const CMLVec3 whitepointXYZ, const CMLFunction* LtoLinearResponse){
  CMLINTERNAL_START_COUNT_LOOP(count);
  cmlInternalOneCIELABtoXYZ_SB(buf, whitepointXYZ, LtoLinearResponse);
  CMLINTERNAL_END_COUNT_LOOP_SB(floatalign);
}





// ////////////////////////////////////
// Spectrum to XYZ
// ////////////////////////////////////

#define CMLINTERNALSpectrumtoXYZ(out, in, observer) \
  out[0] = CMLfilterFunction(in, cmlGetObserverSpecDistFunction(observer, 0));\
  out[1] = CMLfilterFunction(in, cmlGetObserverSpecDistFunction(observer, 1));\
  out[2] = CMLfilterFunction(in, cmlGetObserverSpecDistFunction(observer, 2));\
  cmlMul3(out, cmlGetObserverRadiometricScale(observer));    

CML_HIDDEN CML_INLINE static void cmlInternalOneIlluminationSpectrumtoXYZ (CMLVec3 out, const CMLFunction* in, const CMLObserver* observer){
  CMLINTERNALSpectrumtoXYZ(out, in, observer);
}

CML_HIDDEN CML_INLINE static void cmlInternalIlluminationSpectrumtoXYZ (CMLVec3 out, const CMLFunction* in, CMLuint32 count, CMLuint32 floatalign, const CMLObserver* observer){
  CMLINTERNAL_START_COUNT_LOOP(count);
  cmlInternalOneIlluminationSpectrumtoXYZ(out, in, observer);
  CMLINTERNAL_END_COUNT_LOOP(floatalign, 1);
}

CML_HIDDEN CML_INLINE static void cmlInternalOneRemissionSpectrumtoXYZ (CMLVec3 out, const CMLFunction* in, const CMLFunction* specill, const CMLObserver* observer){
  CMLFunction* remillfunction = CMLcreateFunctionMulFunction(in, specill);
  cmlInternalOneIlluminationSpectrumtoXYZ(out, remillfunction, observer);
  cmlReleaseFunction(remillfunction);
}

CML_HIDDEN CML_INLINE static void cmlInternalRemissionSpectrumtoXYZ (CMLVec3 out, const CMLFunction* in, CMLuint32 count, CMLuint32 floatalign, const CMLFunction* specill, const CMLObserver* observer){
  if(specill){
    CMLINTERNAL_START_COUNT_LOOP(count);
    cmlInternalOneRemissionSpectrumtoXYZ(out, in, specill, observer);
    CMLINTERNAL_END_COUNT_LOOP(floatalign, 1);
  }else{
    float base = cmlGetObserverColorimetricBase(observer) * .5f;
    CMLINTERNAL_START_COUNT_LOOP(count);
    cmlSet3(out, base, base, base);
    CMLINTERNAL_END_COUNT_LOOP(floatalign, 1);
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

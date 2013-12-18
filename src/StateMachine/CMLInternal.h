
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.


#if CML_COMPILE_ON_WIN
  #define CMLHIDDEN
  #define CML_RESTRICT    __restrict
#elif CML_COMPILE_ON_MAC
  #define CMLHIDDEN       __attribute__ ((visibility("hidden")))
  #define CML_RESTRICT    __restrict__
#else
  #define CMLHIDDEN       __attribute__ ((visibility("hidden")))
  #define CML_RESTRICT
#endif


// todo: make inline functions or ranges
#define CML_MAX(a, b) (((a)>(b))?(a):(b))
#define CML_MIN(a, b) (((a)<(b))?(a):(b))


typedef void(*CMLObjectDesctructor)(void* object);

typedef struct CMLObject CMLObject;
struct CMLHIDDEN CMLObject{
  CMLSize refcount;
  CMLObjectDesctructor destructor;
};




struct CMLHIDDEN CMLFunction{
  CMLObject object;
  CMLSize paramcount;
  float* params;
  void* data;
  CMLDefinitionRange defrange;
  CMLFunctionEvaluator getValue;
  CMLFunctionDesctructor destruct;
};


struct CMLHIDDEN CMLResponseCurve{
  CMLObject object;
  CMLFunction* forwardfunc;     // converting from luminance space
  CMLFunction* backwardfunc;    // converting to luminance space
  CMLFunctionType functiontype;
};


struct CMLHIDDEN CMLIllumination{
  CMLObject                     object;
  CMLIlluminationType           type;
  CMLFunction*                  spectrum;
  float                         temperature;
  CMLVec3                       radiometricXYZ;
};

struct CMLHIDDEN CMLObserver{
  CMLObject                     object;
  CMLObserverType               type;
  CMLFunction*                  specdistfunctions[3];
};

struct CMLHIDDEN CMLWhitepoint{
  CMLObject                     object;
  CMLObserver*                  observer;
  CMLIllumination*              illumination;
  float                         radiometricScale;
  CMLVec3                       whitepointXYZ;
  CMLVec3                       inverseWhitepointXYZ;
  CMLVec3                       whitepointYxy;
  CMLVec3                       whitepointYupvp;
};

struct CMLHIDDEN CMLRGBSpace{
  CMLObject                     object;
  CMLRGBSpaceType               type;
  CMLWhitepoint*                whitepoint;
  CMLVec3                       primariesYxy[3];
  CMLResponseCurve*             responsecurves[3];
  CMLMat33                      matrix;
  CMLMat33                      matrixinv;
//  CMLuint8                      lutsize;
};

struct CMLHIDDEN CMLLabSpace{
  CMLObject                     object;
  CMLLabSpaceType               type;
  CMLWhitepoint*                whitepoint;
  CMLResponseCurve*             responsecurve;
//    float                         K;
//    float                         ke;
//  CMLuint8                      lutsize;
};

struct CMLHIDDEN CMLColorCodec{
  CMLColorCodecType     type;
};

struct CMLHIDDEN CMLConverter{
  CMLColorCodec*          srccodec;
  CMLColorCodec*          dstcodec;
  void* data;
  CMLConverterEvaluator   convert;
  CMLConverterDesctructor destruct;
};




CMLHIDDEN CML_INLINE static float cmlInternalEval(const CMLFunction* function, float x){
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




static CMLAPI CML_INLINE void* cmlCreateObject(CMLSize size, CMLObjectDesctructor destructor){
  void* newobject = cmlAllocate(size);
  ((CMLObject*)newobject)->refcount = 1;
  ((CMLObject*)newobject)->destructor = destructor;
  return newobject;
}



static CMLAPI CML_INLINE void* cmlRetainObject(const void* object){
  CMLSize* mutablerefcount = (CMLSize*)(&(((CMLObject*)object)->refcount));
  #ifndef NDEBUG
    if(*mutablerefcount == 0)
      cmlError("cmlRetainObject", "refcount is 0.");
  #endif
  // Beware the parantheses!!!
  (*mutablerefcount)++;
  return (void*)object;
}


static CMLAPI CML_INLINE void cmlReleaseObject(void* object){
  #ifndef NDEBUG
    if(!object)
      cmlError("cmlReleaseObject", "Object is a NULL-Pointer");
  #endif
  CMLSize* mutablerefcount = (CMLSize*)(&(((CMLObject*)object)->refcount));
  #ifndef NDEBUG
    if(*mutablerefcount == 0)
      cmlError("cmlReleaseObject", "refcount is 0.");
  #endif
  // Beware the parantheses!!!
  (*mutablerefcount)--;
  if(*mutablerefcount == 0){
    if(((CMLObject*)object)->destructor){((CMLObject*)object)->destructor(object);}
    free(object);
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




#include "CMLXYZtoYxy.h"
#include "CMLYxytoXYZ.h"
#include "CMLXYZtoRGB.h"
#include "CMLRGBtoXYZ.h"
#include "CMLRGBtoYCbCr.h"
#include "CMLYCbCrtoRGB.h"
#include "CMLYupvptoYxy.h"
#include "CMLLuvtoYupvp.h"
#include "CMLYxytoYupvp.h"
#include "CMLYupvptoLuv.h"
#include "CMLYuvtoYupvp.h"
#include "CMLYupvptoYuv.h"
#include "CMLLabtoLch.h"
#include "CMLHSVtoHSL.h"
#include "CMLLchtoLab.h"
#include "CMLHSLtoHSV.h"
#include "CMLRGBtoHSV.h"
#include "CMLHSVtoRGB.h"



// ////////////////////////////////////
// Lr to fy and fy to Lr
// ////////////////////////////////////

#define CML_LSTAR_TRANSFORM_OFFSET    0.16f
#define CML_LSTAR_TRANSFORM_SCALE     1.16f
#define CML_LSTAR_TRANSFORM_INV_SCALE 0.8620689655172f

CMLHIDDEN CML_INLINE static float cmlInternalLrtofy(float Lr){
  return (Lr + CML_LSTAR_TRANSFORM_OFFSET) * CML_LSTAR_TRANSFORM_INV_SCALE;
}

CMLHIDDEN CML_INLINE static float cmlInternalfytoLr(float fy){
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


CMLHIDDEN CML_INLINE static void cmlInternalOneXYZtoCIELAB(float* CML_RESTRICT out, const float* CML_RESTRICT in , const CMLVec3 inverseWhitepointXYZ, const CMLFunction* LineartoLResponse){
  CMLINTERNALXYZtoCIELAB(out, in, inverseWhitepointXYZ, LineartoLResponse);
}
CMLHIDDEN CML_INLINE static void cmlInternalOneXYZtoCIELAB_SB(float* buf, const CMLVec3 inverseWhitepointXYZ, const CMLFunction* LineartoLResponse){
  CMLINTERNALXYZtoCIELAB(buf, buf, inverseWhitepointXYZ, LineartoLResponse);
}

CMLHIDDEN CML_INLINE static void cmlInternalXYZtoCIELAB(float* CML_RESTRICT out, const float* CML_RESTRICT in, CMLuint32 count , const CMLVec3 inverseWhitepointXYZ, const CMLFunction* LineartoLResponse){
  CMLINTERNAL_START_COUNT_LOOP(count);
  cmlInternalOneXYZtoCIELAB(out, in, inverseWhitepointXYZ, LineartoLResponse);
  CMLINTERNAL_END_COUNT_LOOP(CML_Lab_NUMCHANNELS, CML_XYZ_NUMCHANNELS);
}

CMLHIDDEN CML_INLINE static void cmlInternalXYZtoCIELAB_SB(float* buf, CMLuint32 count, const CMLVec3 inverseWhitepointXYZ, const CMLFunction* LineartoLResponse){
  CMLINTERNAL_START_COUNT_LOOP(count);
  cmlInternalOneXYZtoCIELAB_SB(buf, inverseWhitepointXYZ, LineartoLResponse);
  CMLINTERNAL_END_COUNT_LOOP_SB(CML_Lab_NUMCHANNELS);
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


CMLHIDDEN CML_INLINE static void cmlInternalOneCIELABtoXYZ (float* CML_RESTRICT out , const float* CML_RESTRICT in, const CMLVec3 whitepointXYZ, const CMLFunction* LtoLinearResponse){
  CMLINTERNALCIELABtoXYZ(out, in, whitepointXYZ, LtoLinearResponse);
}
CMLHIDDEN CML_INLINE static void cmlInternalOneCIELABtoXYZ_SB (float* buf, const CMLVec3 whitepointXYZ, const CMLFunction* LtoLinearResponse){
  CMLINTERNALCIELABtoXYZ(buf, buf, whitepointXYZ, LtoLinearResponse);
}

CMLHIDDEN CML_INLINE static void cmlInternalCIELABtoXYZ (float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count, const CMLVec3 whitepointXYZ, const CMLFunction* LtoLinearResponse){
  CMLINTERNAL_START_COUNT_LOOP(count);
  cmlInternalOneCIELABtoXYZ(out, in, whitepointXYZ, LtoLinearResponse);
  CMLINTERNAL_END_COUNT_LOOP(CML_XYZ_NUMCHANNELS, CML_Lab_NUMCHANNELS);
}


CMLHIDDEN CML_INLINE static void cmlInternalCIELABtoXYZ_SB (float* buf , CMLuint32 count, const CMLVec3 whitepointXYZ, const CMLFunction* LtoLinearResponse){
  CMLINTERNAL_START_COUNT_LOOP(count);
  cmlInternalOneCIELABtoXYZ_SB(buf, whitepointXYZ, LtoLinearResponse);
  CMLINTERNAL_END_COUNT_LOOP_SB(CML_XYZ_NUMCHANNELS);
}





// ////////////////////////////////////
// Spectrum to XYZ
// ////////////////////////////////////

#define CMLINTERNALSpectrumtoRadiometricXYZ(out, in, observer) \
  out[0] = cmlFilterFunction(in, cmlGetObserverSpectralDistributionFunction(observer, 0));\
  out[1] = cmlFilterFunction(in, cmlGetObserverSpectralDistributionFunction(observer, 1));\
  out[2] = cmlFilterFunction(in, cmlGetObserverSpectralDistributionFunction(observer, 2));\

CMLHIDDEN CML_INLINE static void cmlInternalOneSpectrumtoRadiometricXYZ (CMLVec3 out, const CMLFunction* in, const CMLObserver* observer){
  CMLINTERNALSpectrumtoRadiometricXYZ(out, in, observer);
}

CMLHIDDEN CML_INLINE static void cmlInternalSpectrumtoRadiometricXYZ (CMLVec3 out, const CMLFunction* in, CMLuint32 count, const CMLObserver* observer){
  CMLINTERNAL_START_COUNT_LOOP(count);
  cmlInternalOneSpectrumtoRadiometricXYZ(out, in, observer);
  CMLINTERNAL_END_COUNT_LOOP(CML_XYZ_NUMCHANNELS, 1);
}

CMLHIDDEN CML_INLINE static void cmlInternalOneIlluminationSpectrumtoXYZ (CMLVec3 out, const CMLFunction* in, const CMLWhitepoint* whitepoint){
  CMLINTERNALSpectrumtoRadiometricXYZ(out, in, cmlGetWhitepointObserver(whitepoint));
  cmlMul3(out, cmlGetWhitepointRadiometricScale(whitepoint));    
}

CMLHIDDEN CML_INLINE static void cmlInternalIlluminationSpectrumtoXYZ (CMLVec3 out, const CMLFunction* in, CMLuint32 count, const CMLWhitepoint* whitepoint){
  CMLINTERNAL_START_COUNT_LOOP(count);
  cmlInternalOneIlluminationSpectrumtoXYZ(out, in, whitepoint);
  CMLINTERNAL_END_COUNT_LOOP(CML_XYZ_NUMCHANNELS, 1);
}

CMLHIDDEN CML_INLINE static void cmlInternalOneRemissionSpectrumtoXYZ (CMLVec3 out, const CMLFunction* in, const CMLWhitepoint* whitepoint){
  CMLFunction* remillfunction = cmlCreateFunctionMulFunction(in, cmlGetIlluminationSpectrum(cmlGetWhitepointIllumination(whitepoint)));
  cmlInternalOneIlluminationSpectrumtoXYZ(out, remillfunction, whitepoint);
  cmlReleaseObject(remillfunction);
}

CMLHIDDEN CML_INLINE static void cmlInternalRemissionSpectrumtoXYZ (CMLVec3 out, const CMLFunction* in, CMLuint32 count, const CMLWhitepoint* whitepoint){
  const CMLFunction* specill = cmlGetIlluminationSpectrum(cmlGetWhitepointIllumination(whitepoint));
  if(specill){
    CMLINTERNAL_START_COUNT_LOOP(count);
    cmlInternalOneRemissionSpectrumtoXYZ(out, in, whitepoint);
    CMLINTERNAL_END_COUNT_LOOP(CML_XYZ_NUMCHANNELS, 1);
  }else{
    float base = cmlGetWhitepointColorimetricBase(whitepoint) * .5f;
    CMLINTERNAL_START_COUNT_LOOP(count);
    cmlSet3(out, base, base, base);
    CMLINTERNAL_END_COUNT_LOOP(CML_XYZ_NUMCHANNELS, 1);
  }
}




// Base definitions of CML
// Defines some useful types, macros and functions. Default stuff.



// ////////////////////////////////////////////
// Definitions for Debugging. Use NDEBUG!
// ////////////////////////////////////////////

#include <sys/types.h>  // base types


#if (defined _WIN64) || (defined _WIN32) || (defined WIN32)
  #define CML_COMPILE_ON_WIN 1
  #define CML_INLINE      _inline
#elif (defined __APPLE__)
  #define CML_COMPILE_ON_MAC 1
  #define CML_INLINE      inline
#else
  #define CML_INLINE      inline
#endif


#ifndef NDEBUG
  #if CML_COMPILE_ON_WIN
    typedef __int64 CMLFileSize;
    #include <io.h>
    #include <share.h>
    #include <direct.h>
    #include "windows.h"
    CML_INLINE static CMLFileSize CMLWrite(int fd, const void* buffer, CMLFileSize count){
      return (CMLFileSize)_write(fd, buffer, (unsigned int)count);
    }
    
  #elif CML_COMPILE_ON_MAC
    typedef off_t CMLFileSize;
    #include <unistd.h>
    CML_INLINE static CMLFileSize CMLWrite(int fd, const void* buffer, CMLFileSize count){
      return (CMLFileSize)write(fd, buffer, (size_t)count);
    }
    
  #else
    #warning This system may not be supported by CML
    typedef off_t CMLFileSize;
    #include <unistd.h>
    CML_INLINE static CMLFileSize CMLWrite(int fd, const void* buffer, CMLFileSize count){
      return (CMLFileSize)write(fd, buffer, (size_t)count);
    }
  #endif
  
  #include <string.h>
  #include <stdio.h>
  static CML_INLINE void cmlError(  const char* functionsymbol,
                                    const char* message){
    fprintf(stderr, "Error in %s: %s\n", functionsymbol, message);
  }
  static CML_INLINE void cmlCrash(  const char* functionsymbol,
                                    const char* message){
    fprintf(stderr, "Critical Error in %s: %s\n", functionsymbol, message);
    fprintf(stderr, "The application will likely crash...\n");
  }
#endif



// ////////////////////////////////////////////
// System dependant macros and type definitions
// ////////////////////////////////////////////

#if defined __STDC_VERSION__
  #if __STDC_VERSION__ >= 201112L // This indicates the C++11 standard
    #define CML_NULL NULL
  #endif
#endif
#ifndef CML_NULL
  #include <stdlib.h>    // Just for the NULL
  #define CML_NULL NULL
#endif

#include <string.h>     // memset and memcpy


#if CML_COMPILE_ON_WIN
  #define CML_API __declspec(dllexport)
  #ifndef CML_INLINE
    #define CML_INLINE        __CML_INLINE
  #endif
  typedef signed __int32    CMLint32;
  typedef unsigned __int32  CMLuint32;
  typedef unsigned __int16  CMLuint16;
  typedef unsigned __int8   CMLuint8;
  typedef signed __int8     CMLint8;
  
#elif CML_COMPILE_ON_MAC
  #define CML_API __attribute__ ((visibility("default")))
  typedef int32_t           CMLint32;
  typedef u_int32_t         CMLuint32;
  typedef u_int16_t         CMLuint16;
  typedef u_int8_t          CMLuint8;
  typedef int8_t            CMLint8;
  
#else
  #define CML_API __attribute__ ((visibility("default")))
  #warning This system may not be supported by CML
  typedef signed int        CMLint32;
  typedef unsigned int      CMLuint32;
  typedef unsigned short    CMLuint16;
  typedef unsigned char     CMLuint8;
  typedef signed char       CMLint8;
#endif

typedef CMLint32      CMLInt;
typedef CMLuint32     CMLSize;
typedef CMLuint16     CMLWord;
typedef CMLuint8      CMLByte;

typedef CMLuint8      CMLBool;
#define CML_TRUE      1
#define CML_FALSE     0



// ////////////////////////////////////////////
// Mathematical operators
// ////////////////////////////////////////////

#include <math.h>

#if CML_COMPILE_ON_WIN
  #define CMLCbrt(x) (powf(x, 1.f/3.f))
  #define CMLRound(x) (floorf(x+.5f))
#elif CML_COMPILE_ON_MAC
  #define CMLCbrt(x) (cbrtf(x))
  #define CMLRound(x) (roundf(x))
#else
  #define CMLCbrt(x) (powf(x, 1.f/3.f))
  #define CMLRound(x) (floorf(x+.5f))
#endif


// The physical constants are directly from NIST based on CODATA 2006:
// http://physics.nist.gov/constants
#define CML_PLANCK          6.62606896e-34f
#define CML_LIGHT_SPEED_VAC 299792458.f
#define CML_BOLTZMANN       1.3806504e-23f
#define CML_SECOND_RAD      1.4387752e-2f
#define CML_2PI             6.2831853f

#define CML_SINGULARITY   1e-6f
#ifndef HUGE_VALF    
  #define HUGE_VALF ((float)(HUGE_VAL))
#endif
#define CML_INFINITY      HUGE_VALF


CML_INLINE static CMLBool CMLAlmostZero(float x){
  return ((x < CML_SINGULARITY) && (x > -CML_SINGULARITY));
}

CML_INLINE static CMLBool CMLInRange(float x, float a, float b){
  return !((x < a) || (x > b));
}

CML_INLINE static float cmlInverse(float x){
  #ifndef NDEBUG
    if(x == 0.f){
      cmlError("cmlInverse", "Division by zero.");
      return CML_INFINITY;
    }
    if(CMLAlmostZero(x)){
      cmlError("cmlInverse", "Division by almost zero.");
    }
  #endif
  return 1.f / x;
}




CML_INLINE static CMLSize CMLgetSampleCount(float min, float max, float stepsize){
  return (CMLSize)(CMLRound((max-min) * cmlInverse(stepsize))) + 1;
}

CML_INLINE static float CMLgetStepSize(float min, float max, CMLSize samplecount){
  return (max-min) * cmlInverse((float)samplecount - 1);
}




// ////////////////////////////////////////////
// Vector algebra
// ////////////////////////////////////////////

typedef float   CMLVec1[1];
typedef float   CMLVec2[2];
typedef float   CMLVec3[3];
typedef float   CMLVec4[4];

CML_INLINE static void     cmlSet1(CMLVec1 d, float a0) {d[0]=a0;}
CML_INLINE static void     cmlSet2(CMLVec2 d, float a0, float a1) {d[0]=a0;d[1]=a1;}
CML_INLINE static void     cmlSet3(CMLVec3 d, float a0, float a1, float a2) {d[0]=a0;d[1]=a1;d[2]=a2;}
CML_INLINE static void     cmlSet4(CMLVec4 d, float a0, float a1, float a2, float a3) {d[0]=a0;d[1]=a1;d[2]=a2;d[3]=a3;}

CML_INLINE static void     cmlCpy1(CMLVec1 d, const CMLVec1 a) {d[0]=a[0];}
CML_INLINE static void     cmlCpy2(CMLVec2 d, const CMLVec2 a) {d[0]=a[0];d[1]=a[1];}
CML_INLINE static void     cmlCpy3(CMLVec3 d, const CMLVec3 a) {d[0]=a[0];d[1]=a[1];d[2]=a[2];}
CML_INLINE static void     cmlCpy4(CMLVec4 d, const CMLVec4 a) {d[0]=a[0];d[1]=a[1];d[2]=a[2];d[3]=a[3];}

CML_INLINE static void     cmlAdd2(CMLVec2 d, const CMLVec2 a) {d[0]+=a[0];d[1]+=a[1];}
CML_INLINE static void     cmlAdd3(CMLVec3 d, const CMLVec3 a) {d[0]+=a[0];d[1]+=a[1];d[2]+=a[2];}
CML_INLINE static void     cmlAdd4(CMLVec4 d, const CMLVec4 a) {d[0]+=a[0];d[1]+=a[1];d[2]+=a[2];d[3]+=a[3];} 

CML_INLINE static void     cmlSub2(CMLVec2 d, const CMLVec2 a) {d[0]-=a[0];d[1]-=a[1];}
CML_INLINE static void     cmlSub3(CMLVec3 d, const CMLVec3 a) {d[0]-=a[0];d[1]-=a[1];d[2]-=a[2];}
CML_INLINE static void     cmlSub4(CMLVec4 d, const CMLVec4 a) {d[0]-=a[0];d[1]-=a[1];d[2]-=a[2];d[3]-=a[3];}

CML_INLINE static void     cmlMul2(CMLVec2 d, const float f) {d[0]*=f;d[1]*=f;}
CML_INLINE static void     cmlMul3(CMLVec3 d, const float f) {d[0]*=f;d[1]*=f;d[2]*=f;}
CML_INLINE static void     cmlMul4(CMLVec4 d, const float f) {d[0]*=f;d[1]*=f;d[2]*=f;d[3]*=f;}

CML_INLINE static void     cmlDiv2(CMLVec2 d, const float divisor) {cmlMul2(d, cmlInverse(divisor));}
CML_INLINE static void     cmlDiv3(CMLVec3 d, const float divisor) {cmlMul3(d, cmlInverse(divisor));}
CML_INLINE static void     cmlDiv4(CMLVec4 d, const float divisor) {cmlMul4(d, cmlInverse(divisor));}

CML_INLINE static void     cmlDiv2componentwise(CMLVec2 d, const CMLVec2 a) {d[0]/=a[0];d[1]/=a[1];}
CML_INLINE static void     cmlDiv3componentwise(CMLVec3 d, const CMLVec3 a) {d[0]/=a[0];d[1]/=a[1];d[2]/=a[2];}
CML_INLINE static void     cmlDiv4componentwise(CMLVec4 d, const CMLVec4 a) {d[0]/=a[0];d[1]/=a[1];d[2]/=a[2];d[3]/=a[3];}

CML_INLINE static CMLBool  cmlEqual2(const CMLVec2 a, const CMLVec2 b) {return ((a[0]==b[0])&&(a[1]==b[1]));}
CML_INLINE static CMLBool  cmlEqual3(const CMLVec3 a, const CMLVec3 b) {return ((a[0]==b[0])&&(a[1]==b[1])&&(a[2]==b[2]));}
CML_INLINE static CMLBool  cmlEqual4(const CMLVec4 a, const CMLVec4 b) {return ((a[0]==b[0])&&(a[1]==b[1])&&(a[2]==b[2])&&(a[3]==b[3]));}

CML_INLINE static float    cmlDot2(const CMLVec2 a, const CMLVec2 b) {return a[0]*b[0]+a[1]*b[1];}
CML_INLINE static float    cmlDot3(const CMLVec3 a, const CMLVec3 b) {return a[0]*b[0]+a[1]*b[1]+a[2]*b[2];}
CML_INLINE static float    cmlDot4(const CMLVec4 a, const CMLVec4 b) {return a[0]*b[0]+a[1]*b[1]+a[2]*b[2]+a[3]*b[3];}

CML_INLINE static float    cmlLength1(const CMLVec1 a) {return fabsf(a[0]);}
CML_INLINE static float    cmlLength2(const CMLVec2 a) {return sqrtf(cmlDot2(a, a));}
CML_INLINE static float    cmlLength3(const CMLVec3 a) {return sqrtf(cmlDot3(a, a));}
CML_INLINE static float    cmlLength4(const CMLVec4 a) {return sqrtf(cmlDot4(a, a));}

CML_INLINE static float    cmlAngle(const CMLVec2 a) {return atan2f(a[1], a[0]);}



// ////////////////////////////////////////////
// 3x3 matrix algebra, stored in COLUMN-FIRST order
// ////////////////////////////////////////////

typedef float CMLMat33[9];

// Warning: The set method expects the values in COLUMN-FIRST order!
CML_INLINE static void CMLMat33set(CMLMat33 m, float a0, float a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8){
  m[0]=a0;m[1]=a1;m[2]=a2;m[3]=a3;m[4]=a4;m[5]=a5;m[6]=a6;m[7]=a7;m[8]=a8;}
CML_INLINE static void CMLMat33setVec3(CMLMat33 m, const CMLVec3 v0, const CMLVec3 v1, const CMLVec3 v2){
  CMLMat33set(m, v0[0],v0[1],v0[2],v1[0],v1[1],v1[2],v2[0],v2[1],v2[2]);}
CML_INLINE static void cmlMat33MulVec3(CMLVec3 d, const CMLMat33 m, const CMLVec3 v){
  d[0] = m[0]*v[0] + m[3]*v[1] + m[6]*v[2];
  d[1] = m[1]*v[0] + m[4]*v[1] + m[7]*v[2];
  d[2] = m[2]*v[0] + m[5]*v[1] + m[8]*v[2];
}
CML_INLINE static void cmlMat33ScaleVec3(CMLMat33 m, const CMLVec3 v){
  m[0]*=v[0]; m[1]*=v[0]; m[2]*=v[0];
  m[3]*=v[1]; m[4]*=v[1]; m[5]*=v[1];
  m[6]*=v[2]; m[7]*=v[2]; m[8]*=v[2];
}
CML_INLINE static void cmlMat33MulMat33(CMLMat33 d, const CMLMat33 m, const CMLMat33 a){
  CMLMat33set(d,  m[0]*a[0] + m[3]*a[1] + m[6]*a[2],
                  m[1]*a[0] + m[4]*a[1] + m[7]*a[2],
                  m[2]*a[0] + m[5]*a[1] + m[8]*a[2],
                  m[0]*a[3] + m[3]*a[4] + m[6]*a[5],
                  m[1]*a[3] + m[4]*a[4] + m[7]*a[5],
                  m[2]*a[3] + m[5]*a[4] + m[8]*a[5],
                  m[0]*a[6] + m[3]*a[7] + m[6]*a[8],
                  m[1]*a[6] + m[4]*a[7] + m[7]*a[8],
                  m[2]*a[6] + m[5]*a[7] + m[8]*a[8]);
}
CML_INLINE static void cmlMat33Inverse(CMLMat33 d, const CMLMat33 m){
  float d0 = m[4]*m[8] - m[5]*m[7];
  float d1 = m[2]*m[7] - m[1]*m[8];
  float d2 = m[1]*m[5] - m[2]*m[4];
  float discriminant = m[0]*d0 + m[3]*d1 + m[6]*d2;
  float divisor = cmlInverse(discriminant);
  CMLMat33set(d,  d0 * divisor, d1 * divisor, d2 * divisor,
                  (m[5]*m[6] - m[3]*m[8]) * divisor, (m[0]*m[8] - m[2]*m[6]) * divisor, (m[2]*m[3] - m[0]*m[5]) * divisor,
                  (m[3]*m[7] - m[4]*m[6]) * divisor, (m[1]*m[6] - m[0]*m[7]) * divisor, (m[0]*m[4] - m[1]*m[3]) * divisor);
}



// ////////////////////////////////////////////
// Angle functions
// ////////////////////////////////////////////

CML_INLINE static float CMLDegtoRad(float deg) {return deg * (CML_2PI / 360.f);}
CML_INLINE static float CMLRadtoDeg(float rad) {return rad * (360.f / CML_2PI);}

CML_INLINE static void CMLPolartoCartesian(float* xy, const float* r_theta){
  float r = r_theta[0];
  xy[0] = r * cosf(r_theta[1]);
  xy[1] = r * sinf(r_theta[1]);
}

CML_INLINE static void CMLCartesiantoPolar(float* r_theta, const float* xy){
  float length = cmlLength2(xy);
  r_theta[1] = (length == 0.) ? 0.f : cmlAngle(xy);
  r_theta[0] = length;
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


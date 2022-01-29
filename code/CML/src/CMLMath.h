
// ////////////////////////////////////////////
// Mathematical operators
// ////////////////////////////////////////////

#include <math.h>

#if CML_COMPILE_ON_WINDOWS
  #define cmlCbrt(x)  (powf(x, 1.f / 3.f))
  #define cmlRound(x) (floorf(x + .5f))
#elif CML_COMPILE_ON_MAC_OSX
  #define cmlCbrt(x)  (cbrtf(x))
  #define cmlRound(x) (roundf(x))
#else
  #define cmlCbrt(x)  (powf(x, 1.f / 3.f))
  #define cmlRound(x) (floorf(x + .5f))
#endif



// The physical constants are directly from NIST based on CODATA 2006:
// http://physics.nist.gov/constants
// todo: update to latest values and make it chosable by year.

#define CML_PLANCK          6.62606896e-34f
#define CML_LIGHT_SPEED_VAC 299792458.f
#define CML_BOLTZMANN       1.3806504e-23f
#define CML_SECOND_RAD      1.4387752e-2f
#define CML_PI2             6.2831853f

#define CML_SINGULARITY     1e-6f
#ifndef HUGE_VALF
  #define HUGE_VALF         ((float)(HUGE_VAL))
#endif
#define CML_INFINITY        HUGE_VALF



CML_IDEF CMLBool cmlAlmostZero(float x){
  return ((x < CML_SINGULARITY) && (x > -CML_SINGULARITY));
}

CML_IDEF float cmlInverse(float x){
  #if CML_DEBUG
    if(x == 0.f){
      cmlError("Division by zero.");
      return CML_INFINITY;
    }
    if(cmlAlmostZero(x)){
      cmlError("Division by almost zero.");
    }
  #endif
  return 1.f / x;
}

CML_IDEF CMLBool cmlInRange(float x, float a, float b){
  return !((x < a) || (x > b));
}

CML_IDEF size_t cmlGetSampleCount(float min, float max, float stepSize){
  return (size_t)(cmlRound((max - min) * cmlInverse(stepSize))) + 1;
}

CML_IDEF float cmlGetStepSize(float min, float max, size_t sampleCount){
  return (max-min) * cmlInverse((float)sampleCount - 1);
}

CML_IDEF float cmlAngle(const float* a) {return atan2f(a[1], a[0]);}



// ////////////////////////////////////////////
// Vector algebra
// ////////////////////////////////////////////

typedef float CMLVec1[1];
typedef float CMLVec2[2];
typedef float CMLVec3[3];
typedef float CMLVec4[4];

CML_IDEF void    cmlSet1(CMLVec1 d, float a0) {d[0] = a0;}
CML_IDEF void    cmlSet2(CMLVec2 d, float a0, float a1) {d[0] = a0; d[1] = a1;}
CML_IDEF void    cmlSet3(CMLVec3 d, float a0, float a1, float a2) {d[0] = a0; d[1] = a1; d[2] = a2;}
CML_IDEF void    cmlSet4(CMLVec4 d, float a0, float a1, float a2, float a3) {d[0] = a0; d[1] = a1; d[2] = a2; d[3] = a3;}

CML_IDEF void    cmlCpy1(CMLVec1 d, const CMLVec1 a) {d[0] = a[0];}
CML_IDEF void    cmlCpy2(CMLVec2 d, const CMLVec2 a) {d[0] = a[0]; d[1] = a[1];}
CML_IDEF void    cmlCpy3(CMLVec3 d, const CMLVec3 a) {d[0] = a[0]; d[1] = a[1]; d[2] = a[2];}
CML_IDEF void    cmlCpy4(CMLVec4 d, const CMLVec4 a) {d[0] = a[0]; d[1] = a[1]; d[2] = a[2]; d[3] = a[3];}

CML_IDEF void    cmlAdd2(CMLVec2 d, const CMLVec2 a) {d[0] += a[0]; d[1] += a[1];}
CML_IDEF void    cmlAdd3(CMLVec3 d, const CMLVec3 a) {d[0] += a[0]; d[1] += a[1]; d[2] += a[2];}
CML_IDEF void    cmlAdd4(CMLVec4 d, const CMLVec4 a) {d[0] += a[0]; d[1] += a[1]; d[2] += a[2]; d[3] += a[3];}

CML_IDEF void    cmlSub2(CMLVec2 d, const CMLVec2 a) {d[0] -= a[0]; d[1] -= a[1];}
CML_IDEF void    cmlSub3(CMLVec3 d, const CMLVec3 a) {d[0] -= a[0]; d[1] -= a[1]; d[2] -= a[2];}
CML_IDEF void    cmlSub4(CMLVec4 d, const CMLVec4 a) {d[0] -= a[0]; d[1] -= a[1]; d[2] -= a[2]; d[3] -= a[3];}

CML_IDEF void    cmlMul2(CMLVec2 d, const float f) {d[0] *= f; d[1] *= f;}
CML_IDEF void    cmlMul3(CMLVec3 d, const float f) {d[0] *= f; d[1] *= f; d[2] *= f;}
CML_IDEF void    cmlMul4(CMLVec4 d, const float f) {d[0] *= f; d[1] *= f; d[2] *= f; d[3] *= f;}

CML_IDEF void    cmlDiv2(CMLVec2 d, const float divisor) {cmlMul2(d, cmlInverse(divisor));}
CML_IDEF void    cmlDiv3(CMLVec3 d, const float divisor) {cmlMul3(d, cmlInverse(divisor));}
CML_IDEF void    cmlDiv4(CMLVec4 d, const float divisor) {cmlMul4(d, cmlInverse(divisor));}

CML_IDEF void    cmlDiv2componentwise(CMLVec2 d, const CMLVec2 a) {d[0] /= a[0]; d[1] /= a[1];}
CML_IDEF void    cmlDiv3componentwise(CMLVec3 d, const CMLVec3 a) {d[0] /= a[0]; d[1] /= a[1]; d[2] /= a[2];}
CML_IDEF void    cmlDiv4componentwise(CMLVec4 d, const CMLVec4 a) {d[0] /= a[0]; d[1] /= a[1]; d[2] /= a[2]; d[3] /= a[3];}

CML_IDEF CMLBool cmlEqual2(const CMLVec2 a, const CMLVec2 b) {return ((a[0] == b[0]) && (a[1] == b[1]));}
CML_IDEF CMLBool cmlEqual3(const CMLVec3 a, const CMLVec3 b) {return ((a[0] == b[0]) && (a[1] == b[1]) && (a[2] == b[2]));}
CML_IDEF CMLBool cmlEqual4(const CMLVec4 a, const CMLVec4 b) {return ((a[0] == b[0]) && (a[1] == b[1]) && (a[2] == b[2]) && (a[3] == b[3]));}

CML_IDEF float   cmlDot2(const CMLVec2 a, const CMLVec2 b) {return a[0] * b[0] + a[1] * b[1];}
CML_IDEF float   cmlDot3(const CMLVec3 a, const CMLVec3 b) {return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];}
CML_IDEF float   cmlDot4(const CMLVec4 a, const CMLVec4 b) {return a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3];}

CML_IDEF float   cmlLength1(const CMLVec1 a) {return fabsf(a[0]);}
CML_IDEF float   cmlLength2(const CMLVec2 a) {return sqrtf(cmlDot2(a, a));}
CML_IDEF float   cmlLength3(const CMLVec3 a) {return sqrtf(cmlDot3(a, a));}
CML_IDEF float   cmlLength4(const CMLVec4 a) {return sqrtf(cmlDot4(a, a));}



// ////////////////////////////////////////////
// 3x3 matrix algebra, stored in COLUMN-FIRST order
// ////////////////////////////////////////////

typedef float CMLMat33[9];

// Warning: The set method expects the values in COLUMN-FIRST order!
CML_IDEF void cmlSetMat33(CMLMat33 m, float a0, float a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8){
  m[0] = a0; m[1] = a1; m[2] = a2; m[3] = a3; m[4] = a4; m[5] = a5; m[6] = a6; m[7] = a7; m[8] = a8;}
CML_IDEF void cmlSetMat33Vec3(CMLMat33 m, const CMLVec3 v0, const CMLVec3 v1, const CMLVec3 v2){
  cmlSetMat33(m, v0[0], v0[1], v0[2], v1[0], v1[1], v1[2], v2[0], v2[1], v2[2]);}
CML_IDEF void cmlMulMat33Vec3(CMLVec3 d, const CMLMat33 m, const CMLVec3 v){
  d[0] = m[0] * v[0] + m[3] * v[1] + m[6] * v[2];
  d[1] = m[1] * v[0] + m[4] * v[1] + m[7] * v[2];
  d[2] = m[2] * v[0] + m[5] * v[1] + m[8] * v[2];
}
CML_IDEF void cmlScaleMat33Vec3(CMLMat33 m, const CMLVec3 v){
  m[0] *= v[0]; m[1] *= v[0]; m[2] *= v[0];
  m[3] *= v[1]; m[4] *= v[1]; m[5] *= v[1];
  m[6] *= v[2]; m[7] *= v[2]; m[8] *= v[2];
}
CML_IDEF void cmlMulMat33Mat33(CMLMat33 d, const CMLMat33 m, const CMLMat33 a){
  cmlSetMat33(d,
    m[0] * a[0] + m[3] * a[1] + m[6] * a[2],
    m[1] * a[0] + m[4] * a[1] + m[7] * a[2],
    m[2] * a[0] + m[5] * a[1] + m[8] * a[2],
    m[0] * a[3] + m[3] * a[4] + m[6] * a[5],
    m[1] * a[3] + m[4] * a[4] + m[7] * a[5],
    m[2] * a[3] + m[5] * a[4] + m[8] * a[5],
    m[0] * a[6] + m[3] * a[7] + m[6] * a[8],
    m[1] * a[6] + m[4] * a[7] + m[7] * a[8],
    m[2] * a[6] + m[5] * a[7] + m[8] * a[8]);
}
CML_IDEF void cmlInvertMat33(CMLMat33 d, const CMLMat33 m){
  float d0 = m[4] * m[8] - m[5] * m[7];
  float d1 = m[2] * m[7] - m[1] * m[8];
  float d2 = m[1] * m[5] - m[2] * m[4];
  float discriminant = m[0] * d0 + m[3] * d1 + m[6] * d2;
  float divisor = cmlInverse(discriminant);
  cmlSetMat33(d,
    d0 * divisor, d1 * divisor, d2 * divisor,
    (m[5] * m[6] - m[3] * m[8]) * divisor, (m[0] * m[8] - m[2] * m[6]) * divisor, (m[2] * m[3] - m[0] * m[5]) * divisor,
    (m[3] * m[7] - m[4] * m[6]) * divisor, (m[1] * m[6] - m[0] * m[7]) * divisor, (m[0] * m[4] - m[1] * m[3]) * divisor);
}



// ////////////////////////////////////////////
// Angle functions
// ////////////////////////////////////////////

CML_IDEF float cmlDegToRad(float deg) {return deg * (CML_PI2 / 360.f);}
CML_IDEF float cmlRadToDeg(float rad) {return rad * (360.f / CML_PI2);}

CML_IDEF void cmlPolarToCartesian(float* xy, const float* r_theta){
  float r = r_theta[0];
  xy[0] = r * cosf(r_theta[1]);
  xy[1] = r * sinf(r_theta[1]);
}

CML_IDEF void cmlCartesianToPolar(float* r_theta, const float* xy){
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


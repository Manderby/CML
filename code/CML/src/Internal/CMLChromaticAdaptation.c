
#include "../CML.h"
#include "CMLColorMachineState.h"


CML_API void cmlComputeChromaticAdaptationMatrix(  CMLMat33 matrix,
                                CMLChromaticAdaptationType adaptationType,
                                                   CMLVec3 adaptedWhitePointYxy,
                                                   CMLVec3 whitePointYxy){

  CMLMat33 M;
  CMLVec3  whitePointXYZ;
  CMLVec3  adaptedwhitePointXYZ;
  CMLMat33 Minv;
  CMLVec3  cs;
  CMLVec3  cd;
  
  #if CML_DEBUG
    if(adaptationType != CML_CHROMATIC_ADAPTATION_NONE){
      if(whitePointYxy[2] == 0.f)
        cmlError("WhitePoint invalid.");
      if(adaptedWhitePointYxy[2] == 0.f)
        cmlError("Adapted whitePoint invalid.");
    }
  #endif

  // Note that the matrices are stored column first!
  switch(adaptationType){
  case CML_CHROMATIC_ADAPTATION_NONE:
    {
      float scale = adaptedWhitePointYxy[0] / whitePointYxy[0];
      cmlSetMat33(matrix,
            scale,     0.f,       0.f,
            0.f,       scale,     0.f,
            0.f,       0.f,       scale);
      return;
      break;
    }
  default:
  case CML_CHROMATIC_ADAPTATION_XYZ_SCALING: cmlSetMat33(M,
          1.f,       0.f,       0.f,
          0.f,       1.f,       0.f,
          0.f,       0.f,       1.f);
    break;
  case CML_CHROMATIC_ADAPTATION_BRADFORD: cmlSetMat33(M,
          0.8951f,  -0.7502f,   0.0389f,
          0.2664f,   1.7135f,  -0.0685f,
         -0.1614f,   0.0367f,   1.0296f);
    break;
  case CML_CHROMATIC_ADAPTATION_VON_KRIES: cmlSetMat33(M,
          0.40024f, -0.22630f,  0.f,
          0.70760f,  1.16532f,  0.f,
         -0.08081f,  0.04570f,  0.91822f);
    break;
  }
  cml_OneYxyToXYZ(whitePointXYZ, whitePointYxy, CML_NULL);
  cml_OneYxyToXYZ(adaptedwhitePointXYZ, adaptedWhitePointYxy, CML_NULL);
  cmlInvertMat33(Minv, M);
  cmlMulMat33Vec3(cs, M, whitePointXYZ);
  cmlMulMat33Vec3(cd, M, adaptedwhitePointXYZ);
  cmlDiv3componentwise(cd, cs);
  cmlScaleMat33Vec3(Minv, cd);
  cmlMulMat33Mat33(matrix, Minv, M);
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

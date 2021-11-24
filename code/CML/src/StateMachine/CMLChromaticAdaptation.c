
#include "../CML.h"
#include "CMLColorMachineState.h"


CML_API void cmlComputeChromaticAdaptationMatrix(  CMLMat33 matrix,
                                CMLChromaticAdaptationType adaptationtype,
                                                   CMLVec3 adaptedwhitepointYxy,
                                                   CMLVec3 whitepointYxy){

  CMLMat33 M;
  CMLVec3  whitepointXYZ;
  CMLVec3  adaptedwhitepointXYZ;
  CMLMat33 Minv;
  CMLVec3  cs;
  CMLVec3  cd;
  
  #ifndef NDEBUG
    if(adaptationtype != CML_CHROMATIC_ADAPTATION_NONE){
      if(whitepointYxy[2] == 0.f)
        cmlError("Whitepoint invalid.");
      if(adaptedwhitepointYxy[2] == 0.f)
        cmlError("Adapted whitepoint invalid.");
    }
  #endif

  // Note that the matrices are stored column first!
  switch(adaptationtype){
  case CML_CHROMATIC_ADAPTATION_NONE:
    {
      float scale = adaptedwhitepointYxy[0] / whitepointYxy[0];
      CMLMat33set(matrix,
            scale,     0.f,       0.f,
            0.f,       scale,     0.f,
            0.f,       0.f,       scale);
      return;
      break;
    }
  default:
  case CML_CHROMATIC_ADAPTATION_XYZ_SCALING: CMLMat33set(M,
          1.f,       0.f,       0.f,
          0.f,       1.f,       0.f,
          0.f,       0.f,       1.f);
    break;
  case CML_CHROMATIC_ADAPTATION_BRADFORD: CMLMat33set(M,
          0.8951f,  -0.7502f,   0.0389f,
          0.2664f,   1.7135f,  -0.0685f,
         -0.1614f,   0.0367f,   1.0296f);
    break;
  case CML_CHROMATIC_ADAPTATION_VON_KRIES: CMLMat33set(M,
          0.40024f, -0.22630f,  0.f,
          0.70760f,  1.16532f,  0.f,
         -0.08081f,  0.04570f,  0.91822f);
    break;
  }
  cmlInternalOneYxytoXYZ(whitepointXYZ, whitepointYxy, CML_NULL);
  cmlInternalOneYxytoXYZ(adaptedwhitepointXYZ, adaptedwhitepointYxy, CML_NULL);
  cmlMat33Inverse(Minv, M);
  cmlMat33MulVec3(cs, M, whitepointXYZ);
  cmlMat33MulVec3(cd, M, adaptedwhitepointXYZ);
  cmlDiv3componentwise(cd, cs);
  cmlMat33ScaleVec3(Minv, cd);
  cmlMat33MulMat33(matrix, Minv, M);
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

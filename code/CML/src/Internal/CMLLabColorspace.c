
#include "../CML.h"
#include "CMLColorMachineState.h"


  
//  // There exist different Delta-E computations, simple and complex ones.
//  // Initial setting is Delta-E-1976 (the euclidian distance).
//  // After setting the compuation model, all subsequent delta-E computations
//  // will be computed accordingly.
//  float DeltaE(const float* CML_RESTRICT Lab1, const float* CML_RESTRICT Lab2) const;






CML_API CMLLabColorSpaceType cmlGetLabColorSpace(const CMLColorMachine* cm){
  return cm->labspace.state;
}


CML_API void cmlSetLabColorSpace(CMLColorMachine* cm, CMLLabColorSpaceType labspace){
  cm->labspace.state = labspace;
  cml_recomputeLabColorspace(cm);
  cml_recomputeAdamsChromaticityValenceSpace(cm);
}


CML_API void cmlGetAdamsChromaticityValenceParameters(CMLColorMachine* cm, float* K, float* ke){
  *K = cm->labspace.adamschromaticityvalenceK;
  *ke = cm->labspace.adamschromaticityvalenceke;
}


CML_API void cmlSetAdamsChromaticityValenceParameters(CMLColorMachine* cm, float K, float ke){
  if(cm->labspace.state == CML_LAB_ADAMS_CROMATIC_VALENCE){
    cm->labspace.adamschromaticityvalenceK = K;
    cm->labspace.adamschromaticityvalenceke = ke;
  #if CML_DEBUG
  }else{
    cmlError("call ineffective.");
  #endif
  }
}


CML_API CMLuint8 cmlGetLabLUTSize(const CMLColorMachine* cm){
  return cm->labspace.lutsize;
}


CML_API void cmlSetLabLUTSize(CMLColorMachine* cm, CMLuint8 bits){
  CMLLabColorSpaceType curtype;
  if((bits < 1) || (bits > 16)){bits = 32;}
  cm->labspace.lutsize = bits;
  curtype = cm->labspace.state;
  cm->labspace.state = CML_LAB_CUSTOM_L;
  cmlSetLabColorSpace(cm, curtype);
}


CML_API const CMLFunction* cmlGetLtoLinearResponse(const CMLColorMachine* cm){
  return cm->labspace.responseL.backwardfunc;
}


CML_API const CMLFunction* cmlGetLineartoLResponse(const CMLColorMachine* cm){
  return cm->labspace.responseL.forwardfunc;
}


CML_API const CMLResponseCurve* cmlGetResponseL  (CMLColorMachine* cm){
  return &(cm->labspace.responseL);
}


//CML_API CMLResponseCurveType cmlGetLabResponseCurveFunctionType(const CMLColorMachine* cm){
//  return cm->labspace.responseL.type;
//}


CML_API void cmlSetResponseL(CMLColorMachine* cm, CMLResponseCurve* response){
  cmlClearResponseCurve(&(cm->labspace.responseL));
  cmlCreateResponseCurveCopy((&cm->labspace.responseL), response);
//  cm->labspace.responseL.forwardfunc = cmlDuplicateFunction(response->forwardfunc);
//  cm->labspace.responseL.backwardfunc = cmlDuplicateFunction(response->backwardfunc);
//  cmlCreateResponseCurveWithParamFunction(&(cm->labspace.responseL), type, param0, param1, param2, param3);
}


//CML_API float cmlGetLabGamma(const CMLColorMachine* cm){
//  return cm->labspace.responseL.param0;
//}


CML_HIDDEN void cml_recomputeAdamsChromaticityValenceSpace(CMLColorMachine* cm){
  float Ka;
  float Kb;
  const float* whitePointXYZ;

  if(cm->recomputationlockcount){cm->recomputationmask |= CML_COLORMACHINE_RECOMPUTE_ADAMS_CHROMATICITY; return;}

  switch(cm->labspace.state){
  case CML_LAB_HUNTER_APPROXIMATE:
    whitePointXYZ = cmlGetReferenceWhitePointXYZ(&(cm->observer));
    Ka = (175.f / 198.04f) * (whitePointXYZ[0] + whitePointXYZ[1]);
    Kb = (70.f  / 218.11f) * (whitePointXYZ[1] + whitePointXYZ[2]);
    cm->labspace.adamschromaticityvalenceK = Ka;
    cm->labspace.adamschromaticityvalenceke = Kb / Ka;
    break;
  case CML_LAB_HUNTER_ORIGINAL:
    cm->labspace.adamschromaticityvalenceK = 175.f / 100.f;
    cm->labspace.adamschromaticityvalenceke = 70.f / 175.f;
    break;
  default: break;
  }
}




CML_HIDDEN void cml_recomputeLabColorspace(CMLColorMachine* cm){
  if(cm->recomputationlockcount){cm->recomputationmask |= CML_COLORMACHINE_RECOMPUTE_LAB; return;}
  CMLResponseCurve* responseL;

  switch(cm->labspace.state){
  case CML_LAB_CIELAB:
    cm->XYZToLab = &cml_XYZToLabCIELAB;
    cm->XYZToLab_SB = &cml_XYZToLabCIELAB_SB;
    cm->LabToXYZ = &cml_LabToXYZCIELAB;
    cm->LabToXYZ_SB = &cml_LabToXYZCIELAB_SB;
//    cmlClearResponseCurve(&(cm->labspace.responseL));
    responseL = cmlCreateResponseCurveWithPreset(NULL, CML_RESPONSE_LSTAR);
    cmlSetResponseL(cm, responseL);
    cmlDestroyResponseCurve(responseL);
//    cml_setResponseL(cm, CML_RESPONSE_LSTAR, 0.f, 0.f, 0.f);
    break;
  case CML_LAB_CUSTOM_L:
    cm->XYZToLab = &cml_XYZToLabCIELAB;
    cm->XYZToLab_SB = &cml_XYZToLabCIELAB_SB;
    cm->LabToXYZ = &cml_LabToXYZCIELAB;
    cm->LabToXYZ_SB = &cml_LabToXYZCIELAB_SB;
    break;
  case CML_LAB_HUNTER_APPROXIMATE:
    cm->XYZToLab = &cml_XYZToLabChromaticValence;
    cm->XYZToLab_SB = &cml_XYZToLabChromaticValence_SB;
    cm->LabToXYZ = &cml_LabToXYZChromaticValence;
    cm->LabToXYZ_SB = &cml_LabToXYZChromaticValence_SB;
//    cmlClearResponseCurve(&(cm->labspace.responseL));
//    cmlCreateResponseCurveWithParamFunction(&(cm->labspace.responseL), CML_RESPONSE_SQRT, 2.f, 0.f, 1.f, 0.f);
    responseL = cmlCreateResponseCurveWithPreset(NULL, CML_RESPONSE_SQRT);
    cmlSetResponseL(cm, responseL);
    cmlDestroyResponseCurve(responseL);
//    cml_setResponseL(cm, CML_RESPONSE_SQRT, 0.f, 0.f, 0.f);
    break;
  case CML_LAB_HUNTER_ORIGINAL:
    cm->XYZToLab = &cml_XYZToLabChromaticValence;
    cm->XYZToLab_SB = &cml_XYZToLabChromaticValence_SB;
    cm->LabToXYZ = &cml_LabToXYZChromaticValence;
    cm->LabToXYZ_SB = &cml_LabToXYZChromaticValence_SB;
//    cmlClearResponseCurve(&(cm->labspace.responseL));
//    cmlCreateResponseCurveWithParamFunction(&(cm->labspace.responseL), CML_RESPONSE_SQRT, 2.f, 0.f, 1.f, 0.f);
    responseL = cmlCreateResponseCurveWithPreset(NULL, CML_RESPONSE_SQRT);
    cmlSetResponseL(cm, responseL);
    cmlDestroyResponseCurve(responseL);
//    cml_setResponseL(cm, CML_RESPONSE_SQRT, 0.f, 0.f, 0.f);
    break;
  case CML_LAB_ADAMS_CROMATIC_VALENCE:
    cm->XYZToLab = &cml_XYZToLabChromaticValence;
    cm->XYZToLab_SB = &cml_XYZToLabChromaticValence_SB;
    cm->LabToXYZ = &cml_LabToXYZChromaticValence;
    cm->LabToXYZ_SB = &cml_LabToXYZChromaticValence_SB;
//    cmlClearResponseCurve(&(cm->labspace.responseL));
//    cmlCreateResponseCurveWithParamFunction(&(cm->labspace.responseL), CML_RESPONSE_SQRT, 2.f, 0.f, 1.f, 0.f);
    responseL = cmlCreateResponseCurveWithPreset(NULL, CML_RESPONSE_SQRT);
    cmlSetResponseL(cm, responseL);
    cmlDestroyResponseCurve(responseL);
//    cml_setResponseL(cm, CML_RESPONSE_SQRT, 0.f, 0.f, 0.f);
    break;
  default:
    #if CML_DEBUG
      cmlError("Undefined Lab space.");
    #endif
    break;
  }

}



//void cmlSetDeltaEComputation(CMLColorMachine* cm, CMLDeltaEComputationType computation){
//  cm->labspace.deltaecomputation = computation;
//}


//float ColorMachine::DeltaE(const float* CML_RESTRICT Lab1, const float* CML_RESTRICT Lab2) const{
//  float delta[3];
//  switch(s->labspace.deltaecomputation){
//  case CML_DELTA_E_1976:
//    cmlCpy3(delta, Lab1);
//    cmlSub3(delta, Lab2);
//    return cmlLength3(delta);
//    break;
//  default: break;
//  }
//  return 0;
//}
//



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

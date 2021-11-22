
#include "../CML.h"
#include "CMLColorMachineState.h"


  
//  // There exist different Delta-E computations, simple and complex ones.
//  // Initial setting is Delta-E-1976 (the euclidian distance).
//  // After setting the compuation model, all subsequent delta-E computations
//  // will be computed accordingly.
//  float DeltaE(const float* CML_RESTRICT Lab1, const float* CML_RESTRICT Lab2) const;






CML_API CMLLabColorSpaceType CMLgetLabColorSpace(const CMLColorMachine* cm){
  return cm->labspace.state;
}


CML_API void CMLsetLabColorSpace(CMLColorMachine* cm, CMLLabColorSpaceType labspace){
  cm->labspace.state = labspace;
  CMLInternalrecomputeLabColorspace(cm);
  CMLInternalrecomputeAdamsChromaticityValenceSpace(cm);
}


CML_API void CMLgetAdamsChromaticityValenceParameters(CMLColorMachine* cm, float* K, float* ke){
  *K = cm->labspace.adamschromaticityvalenceK;
  *ke = cm->labspace.adamschromaticityvalenceke;
}


CML_API void CMLsetAdamsChromaticityValenceParameters(CMLColorMachine* cm, float K, float ke){
  if(cm->labspace.state == CML_LAB_ADAMS_CROMATIC_VALENCE){
    cm->labspace.adamschromaticityvalenceK = K;
    cm->labspace.adamschromaticityvalenceke = ke;
  #ifndef NDEBUG
  }else{
    cmlError("CMLsetAdamsChromaticityValenceParameters", "call ineffective.");
  #endif
  }
}


CML_API CMLuint8 CMLgetLabLUTSize(const CMLColorMachine* cm){
  return cm->labspace.lutsize;
}


CML_API void CMLsetLabLUTSize(CMLColorMachine* cm, CMLuint8 bits){
  CMLLabColorSpaceType curtype;
  if((bits < 1) || (bits > 16)){bits = 32;}
  cm->labspace.lutsize = bits;
  curtype = cm->labspace.state;
  cm->labspace.state = CML_LAB_CUSTOM_L;
  CMLsetLabColorSpace(cm, curtype);
}


CML_API const CMLFunction* CMLgetLtoLinearResponse(const CMLColorMachine* cm){
  return cm->labspace.responseL.backwardfunc;
}


CML_API const CMLFunction* CMLgetLineartoLResponse(const CMLColorMachine* cm){
  return cm->labspace.responseL.forwardfunc;
}


CML_API const CMLResponseCurve* CMLgetResponseL  (CMLColorMachine* cm){
  return &(cm->labspace.responseL);
}


//CML_API CMLResponseCurveType CMLgetLabResponseCurveFunctionType(const CMLColorMachine* cm){
//  return cm->labspace.responseL.type;
//}


CML_API void CMLsetResponseL(CMLColorMachine* cm, CMLResponseCurve* response){
  CMLclearResponseCurve(&(cm->labspace.responseL));
  cmlCreateResponseCurveCopy((&cm->labspace.responseL), response);
//  cm->labspace.responseL.forwardfunc = CMLduplicateFunction(response->forwardfunc);
//  cm->labspace.responseL.backwardfunc = CMLduplicateFunction(response->backwardfunc);
//  cmlCreateResponseCurveWithParamFunction(&(cm->labspace.responseL), type, param0, param1, param2, param3);
}


//CML_API float CMLgetLabGamma(const CMLColorMachine* cm){
//  return cm->labspace.responseL.param0;
//}


CML_HIDDEN void CMLInternalrecomputeAdamsChromaticityValenceSpace(CMLColorMachine* cm){
  float Ka;
  float Kb;
  const float* whitepointXYZ;

  if(cm->recomputationlockcount){cm->recomputationmask |= CML_COLORMACHINE_RECOMPUTE_ADAMS_CHROMATICITY; return;}

  switch(cm->labspace.state){
  case CML_LAB_HUNTER_APPROXIMATE:
    whitepointXYZ = cmlGetReferenceWhitepointXYZ(&(cm->observer));
    Ka = (175.f / 198.04f) * (whitepointXYZ[0] + whitepointXYZ[1]);
    Kb = (70.f  / 218.11f) * (whitepointXYZ[1] + whitepointXYZ[2]);
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




CML_HIDDEN void CMLInternalrecomputeLabColorspace(CMLColorMachine* cm){
  if(cm->recomputationlockcount){cm->recomputationmask |= CML_COLORMACHINE_RECOMPUTE_LAB; return;}
  CMLResponseCurve* responseL;

  switch(cm->labspace.state){
  case CML_LAB_CIELAB:
    cm->XYZtoLab = &CMLInternalXYZtoLabCIELAB;
    cm->XYZtoLab_SB = &CMLInternalXYZtoLabCIELAB_SB;
    cm->LabtoXYZ = &CMLInternalLabtoXYZCIELAB;
    cm->LabtoXYZ_SB = &CMLInternalLabtoXYZCIELAB_SB;
//    CMLclearResponseCurve(&(cm->labspace.responseL));
    responseL = cmlCreateResponseCurveWithPreset(NULL, CML_RESPONSE_LSTAR);
    CMLsetResponseL(cm, responseL);
    CMLdestroyResponseCurve(responseL);
//    CMLInternalsetResponseL(cm, CML_RESPONSE_LSTAR, 0.f, 0.f, 0.f);
    break;
  case CML_LAB_CUSTOM_L:
    cm->XYZtoLab = &CMLInternalXYZtoLabCIELAB;
    cm->XYZtoLab_SB = &CMLInternalXYZtoLabCIELAB_SB;
    cm->LabtoXYZ = &CMLInternalLabtoXYZCIELAB;
    cm->LabtoXYZ_SB = &CMLInternalLabtoXYZCIELAB_SB;
    break;
  case CML_LAB_HUNTER_APPROXIMATE:
    cm->XYZtoLab = &CMLInternalXYZtoLabChromaticValence;
    cm->XYZtoLab_SB = &CMLInternalXYZtoLabChromaticValence_SB;
    cm->LabtoXYZ = &CMLInternalLabtoXYZChromaticValence;
    cm->LabtoXYZ_SB = &CMLInternalLabtoXYZChromaticValence_SB;
//    CMLclearResponseCurve(&(cm->labspace.responseL));
//    cmlCreateResponseCurveWithParamFunction(&(cm->labspace.responseL), CML_RESPONSE_SQRT, 2.f, 0.f, 1.f, 0.f);
    responseL = cmlCreateResponseCurveWithPreset(NULL, CML_RESPONSE_SQRT);
    CMLsetResponseL(cm, responseL);
    CMLdestroyResponseCurve(responseL);
//    CMLInternalsetResponseL(cm, CML_RESPONSE_SQRT, 0.f, 0.f, 0.f);
    break;
  case CML_LAB_HUNTER_ORIGINAL:
    cm->XYZtoLab = &CMLInternalXYZtoLabChromaticValence;
    cm->XYZtoLab_SB = &CMLInternalXYZtoLabChromaticValence_SB;
    cm->LabtoXYZ = &CMLInternalLabtoXYZChromaticValence;
    cm->LabtoXYZ_SB = &CMLInternalLabtoXYZChromaticValence_SB;
//    CMLclearResponseCurve(&(cm->labspace.responseL));
//    cmlCreateResponseCurveWithParamFunction(&(cm->labspace.responseL), CML_RESPONSE_SQRT, 2.f, 0.f, 1.f, 0.f);
    responseL = cmlCreateResponseCurveWithPreset(NULL, CML_RESPONSE_SQRT);
    CMLsetResponseL(cm, responseL);
    CMLdestroyResponseCurve(responseL);
//    CMLInternalsetResponseL(cm, CML_RESPONSE_SQRT, 0.f, 0.f, 0.f);
    break;
  case CML_LAB_ADAMS_CROMATIC_VALENCE:
    cm->XYZtoLab = &CMLInternalXYZtoLabChromaticValence;
    cm->XYZtoLab_SB = &CMLInternalXYZtoLabChromaticValence_SB;
    cm->LabtoXYZ = &CMLInternalLabtoXYZChromaticValence;
    cm->LabtoXYZ_SB = &CMLInternalLabtoXYZChromaticValence_SB;
//    CMLclearResponseCurve(&(cm->labspace.responseL));
//    cmlCreateResponseCurveWithParamFunction(&(cm->labspace.responseL), CML_RESPONSE_SQRT, 2.f, 0.f, 1.f, 0.f);
    responseL = cmlCreateResponseCurveWithPreset(NULL, CML_RESPONSE_SQRT);
    CMLsetResponseL(cm, responseL);
    CMLdestroyResponseCurve(responseL);
//    CMLInternalsetResponseL(cm, CML_RESPONSE_SQRT, 0.f, 0.f, 0.f);
    break;
  default:
    #ifndef NDEBUG
      cmlError("CMLInternalrecomputeLabColorspace", "Undefined Lab space.");
    #endif
    break;
  }

}



//void CMLsetDeltaEComputation(CMLColorMachine* cm, CMLDeltaEComputationType computation){
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


#include "../CML.h"
#include "CMLColorMachineState.h"


  





CML_DEF CMLLabColorSpaceType cmlGetLabColorSpace(const CMLColorMachine* cm){
  return cm->labSpace.state;
}


CML_DEF void cmlSetLabColorSpace(CMLColorMachine* cm, CMLLabColorSpaceType labSpace){
  cm->labSpace.state = labSpace;
  cml_recomputeLabColorSpace(cm);
  cml_recomputeAdamsChromaticityValenceSpace(cm);
}


CML_DEF void cmlGetAdamsChromaticityValenceParameters(CMLColorMachine* cm, float* K, float* ke){
  *K = cm->labSpace.adamsChromaticityValenceK;
  *ke = cm->labSpace.adamsChromaticityValenceke;
}


CML_DEF void cmlSetAdamsChromaticityValenceParameters(CMLColorMachine* cm, float K, float ke){
  if(cm->labSpace.state == CML_LAB_ADAMS_CROMATIC_VALENCE){
    cm->labSpace.adamsChromaticityValenceK = K;
    cm->labSpace.adamsChromaticityValenceke = ke;
  #if CML_DEBUG
  }else{
    cmlError("call ineffective.");
  #endif
  }
}


CML_DEF uint8 cmlGetLabLUTSize(const CMLColorMachine* cm){
  return cm->labSpace.lutSize;
}


CML_DEF void cmlSetLabLUTSize(CMLColorMachine* cm, uint8 bits){
  CMLLabColorSpaceType curtype;
  if((bits < 1) || (bits > 16)){bits = 32;}
  cm->labSpace.lutSize = bits;
  curtype = cm->labSpace.state;
  cm->labSpace.state = CML_LAB_CUSTOM_L;
  cmlSetLabColorSpace(cm, curtype);
}


CML_DEF const CMLFunction* cmlGetLtoLinearResponse(const CMLColorMachine* cm){
  return cm->labSpace.responseL.backwardFunc;
}


CML_DEF const CMLFunction* cmlGetLineartoLResponse(const CMLColorMachine* cm){
  return cm->labSpace.responseL.forwardFunc;
}


CML_DEF const CMLResponseCurve* cmlGetResponseL(CMLColorMachine* cm){
  return &(cm->labSpace.responseL);
}


//CML_DEF CMLResponseCurveType cmlGetLabResponseCurveFunctionType(const CMLColorMachine* cm){
//  return cm->labSpace.responseL.type;
//}


CML_DEF void cmlSetResponseL(CMLColorMachine* cm, CMLResponseCurve* response){
  cmlClearResponseCurve(&(cm->labSpace.responseL));
  cmlInitResponseCurveWithCopy((&cm->labSpace.responseL), response);
//  cm->labSpace.responseL.forwardFunc = cmlDuplicateFunction(response->forwardFunc);
//  cm->labSpace.responseL.backwardFunc = cmlDuplicateFunction(response->backwardFunc);
//  cml_CreateResponseCurveWithParamFunction(&(cm->labSpace.responseL), type, param0, param1, param2, param3);
}


CML_HDEF void cml_recomputeAdamsChromaticityValenceSpace(CMLColorMachine* cm){
  if(cm->recomputationLockCount){
    cm->recomputationMask |= CML_COLORMACHINE_RECOMPUTE_ADAMS_CHROMATICITY;
    return;
  }
  
  const float* whitePointXYZ;

  switch(cm->labSpace.state){
  case CML_LAB_HUNTER_APPROXIMATE:
    whitePointXYZ = cmlGetReferenceWhitePointXYZ(cm);
    float Ka = CML_ADAMS_CHROMATICITY_HUNTER_APPROX_K * (whitePointXYZ[0] + whitePointXYZ[1]);
    float Kb = CML_ADAMS_CHROMATICITY_HUNTER_APPROX_KE * (whitePointXYZ[1] + whitePointXYZ[2]);
    cm->labSpace.adamsChromaticityValenceK = Ka;
    cm->labSpace.adamsChromaticityValenceke = Kb / Ka;
    break;
  case CML_LAB_HUNTER_ORIGINAL:
    cm->labSpace.adamsChromaticityValenceK = CML_ADAMS_CHROMATICITY_HUNTER_ORIGINAL_K;
    cm->labSpace.adamsChromaticityValenceke = CML_ADAMS_CHROMATICITY_HUNTER_ORIGINAL_KE;
    break;
  default: break;
  }
}



CML_HDEF void cml_recomputeLabColorSpace(CMLColorMachine* cm){
  if(cm->recomputationLockCount){cm->recomputationMask |= CML_COLORMACHINE_RECOMPUTE_LAB; return;}
  CMLResponseCurve responseL;

  switch(cm->labSpace.state){
  case CML_LAB_CIELAB:
    cm->XYZToLab = &cml_XYZToLabCIELAB;
    cm->XYZToLab_SB = &cml_XYZToLabCIELAB_SB;
    cm->LabToXYZ = &cml_LabToXYZCIELAB;
    cm->LabToXYZ_SB = &cml_LabToXYZCIELAB_SB;
//    cmlClearResponseCurve(&(cm->labSpace.responseL));
    cmlInitResponseCurveWithType(&responseL, CML_RESPONSE_LSTAR);
    cmlSetResponseL(cm, &responseL);
    cmlClearResponseCurve(&responseL);
//    cml_setResponseL(cm, CML_RESPONSE_LSTAR, 0.f, 0.f, 0.f);
    break;
  case CML_LAB_CUSTOM_L:
    cm->XYZToLab =    &cml_XYZToLabCIELAB;
    cm->XYZToLab_SB = &cml_XYZToLabCIELAB_SB;
    cm->LabToXYZ =    &cml_LabToXYZCIELAB;
    cm->LabToXYZ_SB = &cml_LabToXYZCIELAB_SB;
    break;
  case CML_LAB_HUNTER_APPROXIMATE:
    cm->XYZToLab =    &cml_XYZToLabChromaticValence;
    cm->XYZToLab_SB = &cml_XYZToLabChromaticValence_SB;
    cm->LabToXYZ =    &cml_LabToXYZChromaticValence;
    cm->LabToXYZ_SB = &cml_LabToXYZChromaticValence_SB;
    cmlInitResponseCurveWithType(&responseL, CML_RESPONSE_GAMMA_2_0);
    cmlSetResponseL(cm, &responseL);
    cmlClearResponseCurve(&responseL);
    break;
  case CML_LAB_HUNTER_ORIGINAL:
    cm->XYZToLab =    &cml_XYZToLabChromaticValence;
    cm->XYZToLab_SB = &cml_XYZToLabChromaticValence_SB;
    cm->LabToXYZ =    &cml_LabToXYZChromaticValence;
    cm->LabToXYZ_SB = &cml_LabToXYZChromaticValence_SB;
    cmlInitResponseCurveWithType(&responseL, CML_RESPONSE_GAMMA_2_0);
    cmlSetResponseL(cm, &responseL);
    cmlClearResponseCurve(&responseL);
    break;
  case CML_LAB_ADAMS_CROMATIC_VALENCE:
    cm->XYZToLab = &cml_XYZToLabChromaticValence;
    cm->XYZToLab_SB = &cml_XYZToLabChromaticValence_SB;
    cm->LabToXYZ = &cml_LabToXYZChromaticValence;
    cm->LabToXYZ_SB = &cml_LabToXYZChromaticValence_SB;
    cmlInitResponseCurveWithType(&responseL, CML_RESPONSE_GAMMA_2_0);
    cmlSetResponseL(cm, &responseL);
    cmlClearResponseCurve(&responseL);
    break;
  default:
    #if CML_DEBUG
      cmlError("Undefined Lab space.");
    #endif
    break;
  }

}



void cmlSetDeltaEComputation(CMLColorMachine* cm, CMLDeltaEComputationType computation){
  cm->labSpace.deltaEComputation = computation;
}


float deltaE(CMLColorMachine* cm, const float* CML_RESTRICT lab1, const float* CML_RESTRICT lab2){
  float delta[3];
  switch(cm->labSpace.deltaEComputation){
  case CML_DELTA_E_1976:
    cmlCpy3(delta, lab1);
    cmlSub3(delta, lab2);
    return cmlLength3(delta);
    break;
  default: break;
  }
  return 0;
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

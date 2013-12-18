
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

#include "../CML.h"
#include "CMLColorMachineState.h"


  
//  // There exist different Delta-E computations, simple and complex ones.
//  // Initial setting is Delta-E-1976 (the euclidian distance).
//  // After setting the compuation model, all subsequent delta-E computations
//  // will be computed accordingly.
//  float DeltaE(const float* CML_RESTRICT Lab1, const float* CML_RESTRICT Lab2) const;






//CMLAPI CMLLabSpaceType cmlGetLabColorSpace(const CMLColorMachine* cm){
//  return cm->labspace.state;
//}
//
//
////CMLAPI void cmlSetLabColorSpace(CMLColorMachine* cm, CMLLabSpaceType labspace){
////  cm->labspace.state = labspace;
////  CMLInternalrecomputeLabColorspace(cm);
////  CMLInternalrecomputeAdamsChromaticityValenceSpace(cm);
////}
//
//
//CMLAPI void cmlGetAdamsChromaticityValenceParameters(CMLColorMachine* cm, float* K, float* ke){
//  *K = cm->labspace.adamschromaticityvalenceK;
//  *ke = cm->labspace.adamschromaticityvalenceke;
//}
//
//
//CMLAPI void cmlSetAdamsChromaticityValenceParameters(CMLColorMachine* cm, float K, float ke){
//  if(cm->labspace.state == CML_LAB_ADAMS_CROMATIC_VALENCE){
//    cm->labspace.adamschromaticityvalenceK = K;
//    cm->labspace.adamschromaticityvalenceke = ke;
//  #ifndef NDEBUG
//  }else{
//    cmlError("cmlSetAdamsChromaticityValenceParameters", "call ineffective.");
//  #endif
//  }
//}
//
//
//CMLAPI CMLuint8 cmlGetLabLUTSize(const CMLColorMachine* cm){
//  return cm->labspace.lutsize;
//}
//
//
//CMLAPI void cmlSetLabLUTSize(CMLColorMachine* cm, CMLuint8 bits){
//  CMLLabSpaceType curtype;
//  if((bits < 1) || (bits > 16)){bits = 32;}
//  cm->labspace.lutsize = bits;
//  curtype = cm->labspace.state;
//  cm->labspace.state = CML_LAB_CUSTOM_L;
//  cmlSetLabColorSpace(cm, curtype);
//}
//
//
//CMLAPI const CMLFunction* cmlGetLtoLinearResponse(const CMLColorMachine* cm){
//  return cmlGetResponseCurveBackwardFunc(cm->labspace.responseL);
//}
//
//
//CMLAPI const CMLFunction* cmlGetLineartoLResponse(const CMLColorMachine* cm){
//  return cmlGetResponseCurveForwardFunc(cm->labspace.responseL);
//}
//
//
//CMLAPI const CMLResponseCurve* cmlGetResponseL  (CMLColorMachine* cm){
//  return cm->labspace.responseL;
//}
//
//
////CMLAPI CMLResponseCurveType cmlGetLabResponseCurveFunctionType(const CMLColorMachine* cm){
////  return cm->labspace.responseL.type;
////}
//
//
//CMLAPI void cmlSetResponseL(CMLColorMachine* cm, CMLResponseCurve* response){
//  cmlReleaseResponseCurve(cm->labspace.responseL);
//  cm->labspace.responseL = cmlDuplicateResponseCurve(response);
////  cm->labspace.responseL.forwardfunc = cmlDuplicateFunction(response->forwardfunc);
////  cm->labspace.responseL.backwardfunc = cmlDuplicateFunction(response->backwardfunc);
////  cmlCreateResponseCurveWithParamFunction(&(cm->labspace.responseL), type, param0, param1, param2, param3);
//}
//
//
////CMLAPI float cmlGetLabGamma(const CMLColorMachine* cm){
////  return cm->labspace.responseL.param0;
////}
//
//
//CMLHIDDEN void CMLInternalrecomputeAdamsChromaticityValenceSpace(CMLColorMachine* cm){
//  cm = cm;
////  float Ka;
////  float Kb;
////  const float* whitepointXYZ;
////
////  if(cm->recomputationlockcount){cm->recomputationmask |= CML_COLORMACHINE_RECOMPUTE_ADAMS_CHROMATICITY; return;}
////
////  switch(cm->labspace.state){
////  case CML_LAB_HUNTER_APPROXIMATE:
////    whitepointXYZ = cmlGetWhitepointXYZ(cm->observer);
////    Ka = (175.f / 198.04f) * (whitepointXYZ[0] + whitepointXYZ[1]);
////    Kb = (70.f  / 218.11f) * (whitepointXYZ[1] + whitepointXYZ[2]);
////    cm->labspace.adamschromaticityvalenceK = Ka;
////    cm->labspace.adamschromaticityvalenceke = Kb / Ka;
////    break;
////  case CML_LAB_HUNTER_ORIGINAL:
////    cm->labspace.adamschromaticityvalenceK = 175.f / 100.f;
////    cm->labspace.adamschromaticityvalenceke = 70.f / 175.f;
////    break;
////  default: break;
////  }
//}
//
//
//
//
//CMLHIDDEN void CMLInternalrecomputeLabColorspace(CMLColorMachine* cm){
//  if(cm->recomputationlockcount){cm->recomputationmask |= CML_COLORMACHINE_RECOMPUTE_LAB; return;}
//  CMLResponseCurve* responseL;
//
//  switch(cm->labspace.state){
//  case CML_LAB_CIELAB:
//    cm->XYZtoLab = &CMLInternalXYZtoLabCIELAB;
//    cm->XYZtoLab_SB = &CMLInternalXYZtoLabCIELAB_SB;
//    cm->LabtoXYZ = &CMLInternalLabtoXYZCIELAB;
//    cm->LabtoXYZ_SB = &CMLInternalLabtoXYZCIELAB_SB;
////    CMLclearResponseCurve(&(cm->labspace.responseL));
//    responseL = cmlCreateResponseCurveWithPreset(CML_RESPONSE_LSTAR);
//    cmlSetResponseL(cm, responseL);
//    cmlReleaseResponseCurve(responseL);
////    CMLInternalsetResponseL(cm, CML_RESPONSE_LSTAR, 0.f, 0.f, 0.f);
//    break;
//  case CML_LAB_CUSTOM_L:
//    cm->XYZtoLab = &CMLInternalXYZtoLabCIELAB;
//    cm->XYZtoLab_SB = &CMLInternalXYZtoLabCIELAB_SB;
//    cm->LabtoXYZ = &CMLInternalLabtoXYZCIELAB;
//    cm->LabtoXYZ_SB = &CMLInternalLabtoXYZCIELAB_SB;
//    break;
//  case CML_LAB_HUNTER_APPROXIMATE:
//    cm->XYZtoLab = &CMLInternalXYZtoLabChromaticValence;
//    cm->XYZtoLab_SB = &CMLInternalXYZtoLabChromaticValence_SB;
//    cm->LabtoXYZ = &CMLInternalLabtoXYZChromaticValence;
//    cm->LabtoXYZ_SB = &CMLInternalLabtoXYZChromaticValence_SB;
////    CMLclearResponseCurve(&(cm->labspace.responseL));
////    cmlCreateResponseCurveWithParamFunction(&(cm->labspace.responseL), CML_RESPONSE_SQRT, 2.f, 0.f, 1.f, 0.f);
//    responseL = cmlCreateResponseCurveWithPreset(CML_RESPONSE_SQRT);
//    cmlSetResponseL(cm, responseL);
//    cmlReleaseResponseCurve(responseL);
////    CMLInternalsetResponseL(cm, CML_RESPONSE_SQRT, 0.f, 0.f, 0.f);
//    break;
//  case CML_LAB_HUNTER_ORIGINAL:
//    cm->XYZtoLab = &CMLInternalXYZtoLabChromaticValence;
//    cm->XYZtoLab_SB = &CMLInternalXYZtoLabChromaticValence_SB;
//    cm->LabtoXYZ = &CMLInternalLabtoXYZChromaticValence;
//    cm->LabtoXYZ_SB = &CMLInternalLabtoXYZChromaticValence_SB;
////    CMLclearResponseCurve(&(cm->labspace.responseL));
////    cmlCreateResponseCurveWithParamFunction(&(cm->labspace.responseL), CML_RESPONSE_SQRT, 2.f, 0.f, 1.f, 0.f);
//    responseL = cmlCreateResponseCurveWithPreset(CML_RESPONSE_SQRT);
//    cmlSetResponseL(cm, responseL);
//    cmlReleaseResponseCurve(responseL);
////    CMLInternalsetResponseL(cm, CML_RESPONSE_SQRT, 0.f, 0.f, 0.f);
//    break;
//  case CML_LAB_ADAMS_CROMATIC_VALENCE:
//    cm->XYZtoLab = &CMLInternalXYZtoLabChromaticValence;
//    cm->XYZtoLab_SB = &CMLInternalXYZtoLabChromaticValence_SB;
//    cm->LabtoXYZ = &CMLInternalLabtoXYZChromaticValence;
//    cm->LabtoXYZ_SB = &CMLInternalLabtoXYZChromaticValence_SB;
////    CMLclearResponseCurve(&(cm->labspace.responseL));
////    cmlCreateResponseCurveWithParamFunction(&(cm->labspace.responseL), CML_RESPONSE_SQRT, 2.f, 0.f, 1.f, 0.f);
//    responseL = cmlCreateResponseCurveWithPreset(CML_RESPONSE_SQRT);
//    cmlSetResponseL(cm, responseL);
//    cmlReleaseResponseCurve(responseL);
////    CMLInternalsetResponseL(cm, CML_RESPONSE_SQRT, 0.f, 0.f, 0.f);
//    break;
//  default:
//    #ifndef NDEBUG
//      cmlError("CMLInternalrecomputeLabColorspace", "Undefined Lab space.");
//    #endif
//    break;
//  }
//
//}



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


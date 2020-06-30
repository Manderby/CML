
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.


#include "CML.h"
#include "StateMachine/CMLColorMachineState.h"


void computeGenToObsMatrix(CMLMat33 mat, CMLMOBFunctionVector* filters, CMLMOBFunctionVector* generators){
  mat[0] = cmlFilterFunction(cmlGetFunctionVectorFunction(generators, 0), cmlGetFunctionVectorFunction(filters, 0));
  mat[1] = cmlFilterFunction(cmlGetFunctionVectorFunction(generators, 0), cmlGetFunctionVectorFunction(filters, 1));
  mat[2] = cmlFilterFunction(cmlGetFunctionVectorFunction(generators, 0), cmlGetFunctionVectorFunction(filters, 2));
  mat[3] = cmlFilterFunction(cmlGetFunctionVectorFunction(generators, 1), cmlGetFunctionVectorFunction(filters, 0));
  mat[4] = cmlFilterFunction(cmlGetFunctionVectorFunction(generators, 1), cmlGetFunctionVectorFunction(filters, 1));
  mat[5] = cmlFilterFunction(cmlGetFunctionVectorFunction(generators, 1), cmlGetFunctionVectorFunction(filters, 2));
  mat[6] = cmlFilterFunction(cmlGetFunctionVectorFunction(generators, 2), cmlGetFunctionVectorFunction(filters, 0));
  mat[7] = cmlFilterFunction(cmlGetFunctionVectorFunction(generators, 2), cmlGetFunctionVectorFunction(filters, 1));
  mat[8] = cmlFilterFunction(cmlGetFunctionVectorFunction(generators, 2), cmlGetFunctionVectorFunction(filters, 2));
}

MOB* cml_CreateGenToObsMatrix(CMLMOBFunctionVector* filters, CMLMOBFunctionVector* generators){
  MOB* retmatrix = mobCreateFloatArray(9);
  float* storage = mobArrayFloat(retmatrix, 0);
  if((cmlGetFunctionVectorCount(filters) != 3) || (cmlGetFunctionVectorCount(generators) != 3)){
    CMLMat33set(storage, 1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f);
  }else{
    CMLMat33 mat;
    computeGenToObsMatrix(mat, filters, generators);
    CMLMat33cpy(storage, mat);
  }
  return retmatrix;
}


MOB* cml_CreateObsToGenMatrix(CMLMOBFunctionVector* filters, CMLMOBFunctionVector* generators){
  MOB* retmatrix = mobCreateFloatArray(9);
  float* storage = mobArrayFloat(retmatrix, 0);
  if((cmlGetFunctionVectorCount(filters) != 3) || (cmlGetFunctionVectorCount(generators) != 3)){
    CMLMat33set(storage, 1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f);
  }else{
    CMLMat33 mat;
    computeGenToObsMatrix(mat, filters, generators);
    cmlMat33Inverse(storage, mat);
  }
  return retmatrix;
}

//
//void cmlUpdateObserverNormalization(void* listener, const void* sender){
//  CML_UNUSED(sender);
//  CMLObserver* observer = (CMLObserver*)listener;
//  if(observer->white){
//    cmlDiv3(observer->whiteXYZ, observer->whiteScale);
//    
//    if(observer->metricScale){
//      observer->whiteScale = cmlInverse(observer->whiteXYZ[1]);
//      observer->totalScale = observer->whiteScale * observer->metricScale;
//      cmlMul3(observer->whiteXYZ, observer->totalScale);
//    }else{
//      observer->whiteScale = 1.f;
//    }
//
//    cmlSet3(observer->whiteInvXYZ,  cmlInverse(observer->whiteXYZ[0]),
//                                    cmlInverse(observer->whiteXYZ[1]),
//                                    cmlInverse(observer->whiteXYZ[2]));
//    cml_OneXYZToYxy(observer->whiteYxy, observer->whiteXYZ, CML_NULL);
//    cml_OneYxyToYupvp(observer->whiteYupvp, observer->whiteYxy, CML_NULL);
//  }else{
//    if(observer->metricScale){
//      observer->totalScale = observer->metricScale;
//    }else{
//      observer->totalScale = 1.f;
//    }
//  }
//}
//
//
//
//void cmlUpdateObserverWhite(void* listener, const void* sender){
//  CML_UNUSED(sender);
//  CMLObserver* observer = (CMLObserver*)listener;
//  observer->totalScale = 1.f;
//  observer->whiteScale = 1.f;
//  if(observer->white){
////    cml_OneIlluminationSpectrumtoXYZ(observer->whiteXYZ, &(observer->white), observer->filters, &(observer->totalScale));
//  }
//  cmlUpdateObserverNormalization(observer, CML_NULL);
//}
//
//
//
//void cmlUpdateObserver(void* listener, const void* sender){
//  CML_UNUSED(listener);
//  CML_UNUSED(sender);
//}
//
//
//
//
//CML_API CMLObserver* cmlCreateObserverWithPresetAndWhite(CMLFunctionVectorPreset preset, CMLIllumination* white, float metricScale){
//  if((preset <= CML_FUNVEC_OBSERVER_CUSTOM) || (preset >= CML_NUMBER_OF_OBSERVERS)){
//    #ifndef NDEBUG
//      cmlError("cmlCreateObserverWithPresetAndWhite", "Observer type invalid");
//    #endif
//    return CML_NULL;
//  }
//
//  CMLObserver* observer = cmlCreateCMOB(CMLDT_Observer);
//  observer->filters = cmlRetainCMOB(cmlCreateFunctionVector(preset), observer, cmlUpdateObserver);
//  observer->generators = cmlRetainCMOB(observer->filters, observer, cmlUpdateObserver);
//  cmlUpdateObserverMatrix(observer, CML_NULL);
//  
//  observer->metricScale = metricScale;
//
//  if(white){
//    observer->white = cmlRetainCMOB(white->spectrum, observer, cmlUpdateObserverWhite);
//  }else{
//    observer->white = CML_NULL;
//  }
//  cmlUpdateObserverWhite(observer, observer->white);
//  
//  return observer;
//}
//
//
//
//
//
//
//CML_API const CMLFunction* cmlGetObserverWhite(const CMLObserver* observer){
//  return observer->white;
//}
//CML_API void cmlSetObserverWhite(CMLObserver* observer, CMLIllumination* white){
//  cmlReleaseCMOB(observer->white, observer);
//  observer->white = cmlRetainCMOB(white, observer, cmlUpdateObserverWhite);
//  cmlUpdateObserverWhite(observer, white);
//  cmlNotify(observer);
//}
//


CML_API float cmlGetObserverMetricScale(CMLMOBObserver* observer){
  MOB* metricScaleMOB = mobGetKeyObject(observer, cml_Key(CML_OBSERVER_METRIC_SCALE));
  return *mobFloat(metricScaleMOB);
}



CML_API void cmlSetObserverMetricScale(CMLMOBObserver* observer, float metricScale){
  MOB* metricScaleMOB = mobGetKeyObject(observer, cml_Key(CML_OBSERVER_METRIC_SCALE));
  *mobFloat(metricScaleMOB) = metricScale;
}



CML_API CMLMOBFunctionVector* cmlGetObserverFunctions(CMLMOBObserver* observer){
  return mobGetKeyObject(observer, cml_Key(CML_OBSERVER_FUNCTIONS));
}


CML_API const float* cmlGetObserverAdaptationWhiteXYZRadiometric(CMLMOBObserver* observer){
  MOB* whiteXYZ = mobGetKeyObject(observer, cml_Key(CML_OBSERVER_ADAPTATION_WHITE_XYZ));
  if(!whiteXYZ){
    CMLMOBFunction* whiteSpectrum = mobGetKeyObject(observer, cml_Key(CML_OBSERVER_ADAPTATION_WHITE_SPECTRUM));
    CMLMOBFunctionVector* filters = cmlGetObserverFunctions(observer);
    CMLMOBFunction* filter0 = cmlGetFunctionVectorFunction(filters, 0);
    CMLMOBFunction* filter1 = cmlGetFunctionVectorFunction(filters, 1);
    CMLMOBFunction* filter2 = cmlGetFunctionVectorFunction(filters, 2);
    whiteXYZ = mobCreateFloatArray(3);
    float* storage = mobArrayFloat(whiteXYZ, 0);
    cml_OneRadiometricToXYZRadiometric(&(storage[0]), &(storage[1]), &(storage[2]), &whiteSpectrum, filter0, filter1, filter2);
    mobSetKeyObject(observer, cml_Key(CML_OBSERVER_ADAPTATION_WHITE_XYZ), whiteXYZ, MOB_FALSE);
  }
  return mobConstArrayData(whiteXYZ);
}


CML_API const float* cmlGetObserverAdaptationWhiteInvXYZRadiometric(CMLMOBObserver* observer){
  MOB* whiteInvXYZ = mobGetKeyObject(observer, cml_Key(CML_OBSERVER_ADAPTATION_WHITE_InvXYZ));
  if(!whiteInvXYZ){
    const float* whiteXYZ = cmlGetObserverAdaptationWhiteXYZRadiometric(observer);
    whiteInvXYZ = mobCreateFloatArray(3);
    float* storage = mobArrayFloat(whiteInvXYZ, 0);
    cmlSet3(storage, cmlInverse(whiteXYZ[0]), cmlInverse(whiteXYZ[1]), cmlInverse(whiteXYZ[2]));
    mobSetKeyObject(observer, cml_Key(CML_OBSERVER_ADAPTATION_WHITE_InvXYZ), whiteInvXYZ, MOB_FALSE);
  }
  return mobConstArrayData(whiteInvXYZ);
}


CML_API const float* cmlGetObserverAdaptationWhiteYxyRadiometric(CMLMOBObserver* observer){
  MOB* whiteYxy = mobGetKeyObject(observer, cml_Key(CML_OBSERVER_ADAPTATION_WHITE_Yxy));
  if(!whiteYxy){
    const float* whiteXYZ = cmlGetObserverAdaptationWhiteXYZRadiometric(observer);
    whiteYxy = mobCreateFloatArray(3);
    float* storage = mobArrayFloat(whiteYxy, 0);
    cml_OneXYZToYxy(&(storage[0]), &(storage[1]), &(storage[2]), &(whiteXYZ[0]), &(whiteXYZ[1]), &(whiteXYZ[2]), CML_NULL);
    mobSetKeyObject(observer, cml_Key(CML_OBSERVER_ADAPTATION_WHITE_Yxy), whiteYxy, MOB_FALSE);
  }
  return mobConstArrayData(whiteYxy);
}


CML_API const float* cmlGetObserverAdaptationWhiteYupvpRadiometric(CMLMOBObserver* observer){
  MOB* whiteYupvp = mobGetKeyObject(observer, cml_Key(CML_OBSERVER_ADAPTATION_WHITE_Yupvp));
  if(!whiteYupvp){
    const float* whiteYxy = cmlGetObserverAdaptationWhiteYxyRadiometric(observer);
    whiteYupvp = mobCreateFloatArray(3);
    float* storage = mobArrayFloat(whiteYupvp, 0);
    cml_OneYxyToYupvp(&(storage[0]), &(storage[1]), &(storage[2]), &(whiteYxy[0]), &(whiteYxy[1]), &(whiteYxy[2]), CML_NULL);
    mobSetKeyObject(observer, cml_Key(CML_OBSERVER_ADAPTATION_WHITE_Yupvp), whiteYupvp, MOB_FALSE);
  }
  return mobConstArrayData(whiteYupvp);
}






CML_API float cmlGetGeneratorMetricScale(CMLMOBGenerator* generator){
  MOB* metricScaleMOB = mobGetKeyObject(generator, cml_Key(CML_GENERATOR_METRIC_SCALE));
  return *mobFloat(metricScaleMOB);
}


CML_API CMLMOBFunctionVector* cmlGetGeneratorFunctions(CMLMOBGenerator* generator){
  return mobGetKeyObject(generator, cml_Key(CML_GENERATOR_FUNCTIONS));
}


CML_API void  cmlSetGeneratorMetricScale(CMLMOBGenerator* generator, float metricScale){
  MOB* metricScaleMOB = mobGetKeyObject(generator, cml_Key(CML_GENERATOR_METRIC_SCALE));
  *mobFloat(metricScaleMOB) = metricScale;
}

CML_API void cmlSetGeneratorFunctions(CMLMOBGenerator* generator, CMLMOBFunctionVector* functions){
  mobSetKeyObject(generator, cml_Key(CML_GENERATOR_FUNCTIONS), functions, MOB_FALSE);
}



CML_API const float* cmlGetGeneratorWhiteXYZRadiometric(CMLMOBGenerator* generator){
  MOB* whiteXYZ = mobGetKeyObject(generator, cml_Key(CML_GENERATOR_WHITE_XYZ));
  if(!whiteXYZ){
    CMLMOBFunction* whiteSpectrum = mobGetKeyObject(generator, cml_Key(CML_GENERATOR_WHITE_SPECTRUM));
    CMLMOBObserver* observer = cmlGetDefaultColorspaceSetting(CML_SETTING_OBSERVER);
    CMLMOBFunctionVector* observerfuncs = cmlGetObserverFunctions(observer);
    CMLMOBFunction* filter0 = cmlGetFunctionVectorFunction(observerfuncs, 0);
    CMLMOBFunction* filter1 = cmlGetFunctionVectorFunction(observerfuncs, 1);
    CMLMOBFunction* filter2 = cmlGetFunctionVectorFunction(observerfuncs, 2);
    whiteXYZ = mobCreateFloatArray(3);
    float* storage = mobArrayFloat(whiteXYZ, 0);
    cml_OneRadiometricToXYZRadiometric(&(storage[0]), &(storage[1]), &(storage[2]), &whiteSpectrum, filter0, filter1, filter2);
    mobSetKeyObject(generator, cml_Key(CML_GENERATOR_WHITE_XYZ), whiteXYZ, MOB_FALSE);
  }
  return mobConstArrayData(whiteXYZ);
}


CML_API const float* cmlGetGeneratorWhiteInvXYZRadiometric(CMLMOBGenerator* generator){
  MOB* whiteInvXYZ = mobGetKeyObject(generator, cml_Key(CML_GENERATOR_WHITE_InvXYZ));
  if(!whiteInvXYZ){
    const float* whiteXYZ = cmlGetGeneratorWhiteXYZRadiometric(generator);
    whiteInvXYZ = mobCreateFloatArray(3);
    float* storage = mobArrayFloat(whiteInvXYZ, 0);
    cmlSet3(storage, cmlInverse(whiteXYZ[0]), cmlInverse(whiteXYZ[1]), cmlInverse(whiteXYZ[2]));
    mobSetKeyObject(generator, cml_Key(CML_GENERATOR_WHITE_InvXYZ), whiteInvXYZ, MOB_FALSE);
  }
  return mobConstArrayData(whiteInvXYZ);
}


CML_API const float* cmlGetGeneratorRedPrimaryYxyRadiometric(CMLMOBGenerator* generator){
  MOB* primaryYxy = mobGetKeyObject(generator, cml_Key(CML_GENERATOR_PRIMARY_RED_Yxy));
  if(!primaryYxy){
    CMLMOBFunctionVector* generatorfuncs = cmlGetGeneratorFunctions(generator);
    CMLMOBFunction* primary0 = cmlGetFunctionVectorFunction(generatorfuncs, 0);
    CMLMOBObserver* observer = cmlGetDefaultColorspaceSetting(CML_SETTING_OBSERVER);
    CMLMOBFunctionVector* observerfuncs = cmlGetObserverFunctions(observer);
    CMLMOBFunction* filter0 = cmlGetFunctionVectorFunction(observerfuncs, 0);
    CMLMOBFunction* filter1 = cmlGetFunctionVectorFunction(observerfuncs, 1);
    CMLMOBFunction* filter2 = cmlGetFunctionVectorFunction(observerfuncs, 2);
    CMLVec3 primaryXYZ;
    cml_OneRadiometricToXYZRadiometric(&(primaryXYZ[0]), &(primaryXYZ[1]), &(primaryXYZ[2]), &primary0, filter0, filter1, filter2);
    primaryYxy = mobCreateFloatArray(3);
    float* storage = mobArrayFloat(primaryYxy, 0);
    cml_OneXYZToYxy(&(storage[0]), &(storage[1]), &(storage[2]), &(primaryXYZ[0]), &(primaryXYZ[1]), &(primaryXYZ[2]), CML_NULL);
    mobSetKeyObject(generator, cml_Key(CML_GENERATOR_PRIMARY_RED_Yxy), primaryYxy, MOB_FALSE);
  }
  return mobConstArrayData(primaryYxy);
}


CML_API const float* cmlGetGeneratorBluePrimaryYxyRadiometric(CMLMOBGenerator* generator){
  MOB* primaryYxy = mobGetKeyObject(generator, cml_Key(CML_GENERATOR_PRIMARY_BLUE_Yxy));
  if(!primaryYxy){
    CMLMOBFunctionVector* generatorfuncs = cmlGetGeneratorFunctions(generator);
    CMLMOBFunction* primary2 = cmlGetFunctionVectorFunction(generatorfuncs, 2);
    CMLMOBObserver* observer = cmlGetDefaultColorspaceSetting(CML_SETTING_OBSERVER);
    CMLMOBFunctionVector* observerfuncs = cmlGetObserverFunctions(observer);
    CMLMOBFunction* filter0 = cmlGetFunctionVectorFunction(observerfuncs, 0);
    CMLMOBFunction* filter1 = cmlGetFunctionVectorFunction(observerfuncs, 1);
    CMLMOBFunction* filter2 = cmlGetFunctionVectorFunction(observerfuncs, 2);
    CMLVec3 primaryXYZ;
    cml_OneRadiometricToXYZRadiometric(&(primaryXYZ[0]), &(primaryXYZ[1]), &(primaryXYZ[2]), &primary2, filter0, filter1, filter2);
    primaryYxy = mobCreateFloatArray(3);
    float* storage = mobArrayFloat(primaryYxy, 0);
    cml_OneXYZToYxy(&(storage[0]), &(storage[1]), &(storage[2]), &(primaryXYZ[0]), &(primaryXYZ[1]), &(primaryXYZ[2]), CML_NULL);
    mobSetKeyObject(generator, cml_Key(CML_GENERATOR_PRIMARY_BLUE_Yxy), primaryYxy, MOB_FALSE);
  }
  return mobConstArrayData(primaryYxy);
}


//CML_API void cmlSetObserverFilterFunctions(CMLObserver* observer, const CMLFunctionVector* filters){
//  cmlReleaseCMOB(observer->filters, observer);
//  observer->filters = cmlRetainCMOB(filters, observer, CML_NULL);
//  cmlUpdateObserverMatrix(observer, CML_NULL);
//  cmlUpdateObserverWhite(observer, observer->white);
//  cmlNotify(observer);
//}
//
//
//CML_API const CMLFunctionVector* cmlGetObserverGeneratorFunctions(const CMLObserver* observer){
//  return observer->generators;
//}
//CML_API void cmlSetObserverGeneratorFunctions(CMLObserver* observer, const CMLFunctionVector* generators){
//  cmlReleaseCMOB(observer->filters, observer);
//  observer->filters = cmlRetainCMOB(generators, observer, cmlUpdateObserverMatrix);
//  cmlUpdateObserverMatrix(observer, CML_NULL);
//  cmlNotify(observer);
//}
//
//
//
//
//
//CML_API float cmlGetObserverMetricScale(const CMLObserver* observer){
//  return observer->metricScale;
//}
//
//
//CML_API void cmlSetObserverMetricScale(CMLObserver* observer, float metricScale){
//  observer->metricScale = metricScale;
//  cmlUpdateObserverNormalization(observer, CML_NULL);
//  cmlNotify(observer);
//}
//
//
//
//
//
//CML_API void cmlGetSpectralColor(const CMLObserver* observer, float* result, float lambda){
//  cmlEvalFunctionVector(observer->filters, result, lambda);
//  if(observer->metricScale){
//    cmlMul3(result, observer->metricScale);
//  }
//}
//
//
//


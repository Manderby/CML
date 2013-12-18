
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.


#include "CML.h"
#include "StateMachine/CMLColorMachineState.h"


CMLAPI CMLConverter* cmlCreateConverter(
                       CMLConverterEvaluator evaluator,
                     CMLConverterConstructor constructor,
                     CMLConverterDesctructor destructor,
                                 const void* input){
  CMLConverter* newconverter = (CMLConverter*)cmlAllocate(sizeof(CMLConverter));
//  newfunction->refcount = 1;
//  newfunction->paramcount = floatparams;
//  if(floatparams){
//    newfunction->params = (float*)cmlAllocate(floatparams * sizeof(float));
//  }else{
//    newfunction->params = NULL;
//  }
  newconverter->data = CML_NULL;
  newconverter->convert = evaluator;
  newconverter->destruct = destructor;
//  newfunction->defrange.stepsize = 0.f;
//  newfunction->defrange.minSampleCoord = CML_DEFAULT_INTEGRATION_MIN;
//  newfunction->defrange.maxSampleCoord = CML_DEFAULT_INTEGRATION_MAX;
//  newfunction->defrange.minNonTrivialCoord = -CML_INFINITY;
//  newfunction->defrange.maxNonTrivialCoord = +CML_INFINITY;
  if(constructor){
    constructor(/*newfunction->params, */&(newconverter->data)/*, &(newfunction->defrange)*/, input);
  }
  return newconverter;
}

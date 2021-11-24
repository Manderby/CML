
#include "CML.h"
#include "StateMachine/CMLColorMachineState.h"





// ///////////////////////////////////
// Function
// ///////////////////////////////////




CML_API CMLFunction* CMLcreateFunction(CMLFunctionEvaluator evaluator, CMLFunctionConstructor constructor, CMLFunctionDesctructor destructor, CMLuint32 floatparams, const void* input){
  CMLFunction* newfunction = (CMLFunction*)cmlAllocate(sizeof(CMLFunction));
  newfunction->refcount = 1;
  newfunction->paramcount = floatparams;
  if(floatparams){
    newfunction->params = (float*)cmlAllocate(floatparams * sizeof(float));
  }else{
    newfunction->params = NULL;
  }
  newfunction->data = CML_NULL;
  newfunction->getValue = evaluator;
  newfunction->destruct = destructor;
  newfunction->defrange.stepsize = 0.f;
  newfunction->defrange.minSampleCoord = CML_DEFAULT_INTEGRATION_MIN;
  newfunction->defrange.maxSampleCoord = CML_DEFAULT_INTEGRATION_MAX;
  newfunction->defrange.minNonTrivialCoord = -CML_INFINITY;
  newfunction->defrange.maxNonTrivialCoord = +CML_INFINITY;
  if(constructor){
    constructor(newfunction->params, &(newfunction->data), &(newfunction->defrange), input);
  }
  return newfunction;
}


CML_API CMLFunction* CMLduplicateFunction(const CMLFunction* func){
  size_t* mutablerefcount = (size_t*)(&(func->refcount));
  // Beware the parantheses!!!
  (*mutablerefcount)++;
  // Return a non-const reference to function.
  return (CMLFunction*)func;
}


CML_API void cmlReleaseFunction(CMLFunction* func){
  if(!func){return;}
  func->refcount--;
  if(!func->refcount){
    if(func->destruct){
      func->destruct(func->data);
      free(func->params);
    }
    free(func);
  }
}

CML_API float CMLeval(const CMLFunction* func, float x){
  return cmlInternalEval(func, x);
}

CML_API float CMLgetFunctionParameter(const CMLFunction* func, size_t index){
  if(func->paramcount > index){
    return func->params[index];
  }else{
    return 0.f;
  }
}







CML_HIDEF CMLDefinitionRange CMLgetDefinitionRangeOf2Functions(const CMLFunction* func1, const CMLFunction* func2, CMLBool multiplicative){
  
  float minsamplecoord1;
  float maxsamplecoord1;
  float minsamplecoord2;
  float maxsamplecoord2;
  
  const CMLDefinitionRange* range1 = &(func1->defrange);
  const CMLDefinitionRange* range2 = &(func2->defrange);
  CMLDefinitionRange newrange;
  
  // first, set the desired stepsize
  if(range1->stepsize == 0.f){newrange.stepsize = range2->stepsize;}
  else if(range2->stepsize == 0.f){newrange.stepsize = range1->stepsize;}
  else if(range1->stepsize < range2->stepsize){newrange.stepsize = range1->stepsize;}
  else{newrange.stepsize = range2->stepsize;}

  // then, set the trivial boundaries
  if(multiplicative){
    // one trivial value will result in a trivial value
    newrange.minNonTrivialCoord = CML_MAX(range1->minNonTrivialCoord, range2->minNonTrivialCoord);
    newrange.maxNonTrivialCoord = CML_MIN(range1->maxNonTrivialCoord, range2->maxNonTrivialCoord);
  }else{
    // a trivial value maybe does not result in a trivial value
    newrange.minNonTrivialCoord = CML_MIN(range1->minNonTrivialCoord, range2->minNonTrivialCoord);
    newrange.maxNonTrivialCoord = CML_MAX(range1->maxNonTrivialCoord, range2->maxNonTrivialCoord);
  }

  // finally, set the sampling coordinates by making sure, they are in the
  // non-trivial range and are aligned with the original data.
  minsamplecoord1 = range1->minSampleCoord;
  maxsamplecoord1 = range1->maxSampleCoord;
  minsamplecoord2 = range2->minSampleCoord;
  maxsamplecoord2 = range2->maxSampleCoord;
  if(minsamplecoord1 < newrange.minNonTrivialCoord){minsamplecoord1 += range1->stepsize * ceilf((newrange.minNonTrivialCoord - range1->minSampleCoord) / range1->stepsize);}
  if(maxsamplecoord1 > newrange.maxNonTrivialCoord){maxsamplecoord1 -= range1->stepsize * ceilf((range1->maxSampleCoord - newrange.maxNonTrivialCoord) / range1->stepsize);}
  if(minsamplecoord2 < newrange.minNonTrivialCoord){minsamplecoord2 += range2->stepsize * ceilf((newrange.minNonTrivialCoord - range2->minSampleCoord) / range2->stepsize);}
  if(maxsamplecoord2 > newrange.maxNonTrivialCoord){maxsamplecoord2 -= range2->stepsize * ceilf((range2->maxSampleCoord - newrange.maxNonTrivialCoord) / range2->stepsize);}

  newrange.minSampleCoord = CML_MIN(minsamplecoord1, minsamplecoord2);
  newrange.maxSampleCoord = CML_MAX(maxsamplecoord1, maxsamplecoord2);

  return newrange;
}


CML_API float CMLfilterFunction(const CMLFunction* func, const CMLFunction* filter){
  size_t samplecount;
  CMLIntegrationMethod type;
  float sum = 0.f;

  CMLDefinitionRange filterrange = CMLgetDefinitionRangeOf2Functions(func, filter, CML_TRUE);
  if(filterrange.minSampleCoord > filterrange.maxSampleCoord){return 0.f;}
  
  #ifndef NDEBUG
    if(filterrange.stepsize < 0.f){cmlError("Negative stepsize in Function.");}
  #endif
  // If the stepsize is 0, the function will be filtered as a continuous
  // function with the default integration stepsize.
  if(filterrange.stepsize == 0.f){filterrange.stepsize = CML_DEFAULT_INTEGRATION_STEPSIZE;}
  samplecount = (size_t)(CMLRound((filterrange.maxSampleCoord - filterrange.minSampleCoord) / filterrange.stepsize)) + 1;
  // If there is only one value to compute, the stepsize is manually set to 1
  // to not normalize the final result with a wrong value.
  if(samplecount == 1){filterrange.stepsize = 1.f;}

  type = CML_DEFAULT_INTEGRATION_TYPE;
  if(samplecount < 2){type = CML_INTEGRATION_SIMPLE;}
  switch(type){
  
  case CML_INTEGRATION_SIMPLE:
    {
      size_t istep;
      // Simple sum computation by adding one by one
      for(istep = 0; istep < samplecount; istep++){
        float x = filterrange.minSampleCoord + (filterrange.stepsize * istep);
        sum += cmlInternalEval(func, x) * cmlInternalEval(filter, x);
      }
    } break;
    
  case CML_INTEGRATION_BINARY_PAIRS:
    {
      size_t istep;
      size_t i;
      float tmpsums[8 * sizeof(size_t)];  // 8 denotes bits per Byte
      memset(tmpsums, 0, sizeof(float) * (8 * sizeof(size_t)));

      // iterative binary sum computation method
      for(istep = 0; istep < samplecount; istep+=2){

        // Compute two neighboring values.
        float x1 = filterrange.minSampleCoord + (filterrange.stepsize * istep);
        float value1 = cmlInternalEval(func, x1) * cmlInternalEval(filter, x1);
        float x2 = filterrange.minSampleCoord + (filterrange.stepsize * (istep + 1));
        float value2 = cmlInternalEval(func, x2) * cmlInternalEval(filter, x2);

        // Add these values together with the temp sums up to the position where
        // the current istep has its first binary 0.
        float walkingsum = value1 + value2;
        char p = 1;
        size_t step = 2;
        while(istep & step){
          walkingsum += tmpsums[p];
          p++;
          step <<= 1;
        }
        // Store the current sum at the position of the subsequent binary 1
        tmpsums[p] = walkingsum;
      }
      // If the count is odd, store the remaining value at position 0.
      if(samplecount & 1){
        tmpsums[0] = cmlInternalEval(func, filterrange.maxSampleCoord) * cmlInternalEval(filter, filterrange.maxSampleCoord);
      }
      // Finally, go though all temp sums and add those to the final sum where
      // samplecount has a binary 1
      for(i=0; i<8 * sizeof(size_t); i++){
        if(samplecount & (1<<i)){
          sum += tmpsums[i];
        }
      }
    } break;

  default:
    #ifndef NDEBUG
      cmlError("Invalid Integration type.");
    #endif
    return 0.f;
    break;
  }

  return sum * filterrange.stepsize;
}


CML_API float CMLgetFunctionMaxValue(const CMLFunction* func){
  size_t samplecount;
  size_t x;
  float max = -CML_INFINITY;
  float stepsize = func->defrange.stepsize;
  if(stepsize == 0){stepsize = CML_DEFAULT_INTEGRATION_STEPSIZE;}
  samplecount = CMLgetSampleCount(func->defrange.minSampleCoord, func->defrange.maxSampleCoord, stepsize);
  for(x = 0; x < samplecount; x ++){
    float coord = func->defrange.minSampleCoord + x * stepsize;
    float value = cmlInternalEval(func, coord);
    if(value > max){max = value;}
  }
  return max;
}


CML_API void CMLgetFunctionDefinitionRange(
                                      const CMLFunction* func,
                                     CMLDefinitionRange* defrange){
  *defrange = func->defrange;
}


CML_API CMLFunction* CMLsampleArrayFunction(const CMLFunction* func, float minimalcoord, float maximalcoord, size_t entrycount, CMLInterpolationMethod interpolationmethod, CMLExtrapolationMethod downextrapolationmethod, CMLExtrapolationMethod upextrapolationmethod){
  size_t i;
  float* buffer = (float*)cmlAllocate(sizeof(float) * entrycount);
  for(i=0; i<entrycount; i++){
    float coord = minimalcoord + ((float)i / (float)(entrycount-1)) * (maximalcoord - minimalcoord);
    buffer[i] = cmlInternalEval(func, coord);
  }
  return CMLcreateArrayFunction(buffer, CML_TRUE, entrycount, minimalcoord, maximalcoord, interpolationmethod, downextrapolationmethod, upextrapolationmethod);
}









// //////////////////////////////////////////////
// Array Function Helper definitions
// //////////////////////////////////////////////

typedef struct CMLInternalArrayFunctionDescriptor CMLInternalArrayFunctionDescriptor;
struct CML_HIDDEN CMLInternalArrayFunctionDescriptor{
  const float* buffer;
  CMLBool ownbuffer;
  size_t entrycount;
  float minimalcoord;
  float maximalcoord;
  CMLInterpolationMethod interpolationmethod;
  CMLExtrapolationMethod downextrapolationmethod;
  CMLExtrapolationMethod upextrapolationmethod;
};

typedef struct CMLInternalArrayFunctionStorage CMLInternalArrayFunctionStorage;
struct CML_HIDDEN CMLInternalArrayFunctionStorage{
  const float* array;
  size_t size;
  CMLBool isowner;

  float mincoord;
  float maxcoord;
  float inverseinterval;
  
  // Note for the future: Even if it looks like this could be faster with a
  // switch statement, it is not. Believe me. I've checked it several times.
  float (*extrapolateDown)(const CMLInternalArrayFunctionStorage* storage, float x);
  float (*extrapolateUp)(const CMLInternalArrayFunctionStorage* storage, float x);
  float (*interpolate)(const CMLInternalArrayFunctionStorage* storage, float indx);
};


// Prototypes:
CML_HIDDEN float CMLInternalArrayFunctionExtrapolateDownClampZero(const CMLInternalArrayFunctionStorage* storage, float x);
CML_HIDDEN float CMLInternalArrayFunctionExtrapolateDownLinearZero(const CMLInternalArrayFunctionStorage* storage, float x);
CML_HIDDEN float CMLInternalArrayFunctionExtrapolateDownClampValue(const CMLInternalArrayFunctionStorage* storage, float x);
CML_HIDDEN float CMLInternalArrayFunctionExtrapolateDownGradient(const CMLInternalArrayFunctionStorage* storage, float x);
CML_HIDDEN float CMLInternalArrayFunctionExtrapolateUpClampZero(const CMLInternalArrayFunctionStorage* storage, float x);
CML_HIDDEN float CMLInternalArrayFunctionExtrapolateUpLinearZero(const CMLInternalArrayFunctionStorage* storage, float x);
CML_HIDDEN float CMLInternalArrayFunctionExtrapolateUpClampValue(const CMLInternalArrayFunctionStorage* storage, float x);
CML_HIDDEN float CMLInternalArrayFunctionExtrapolateUpGradient(const CMLInternalArrayFunctionStorage* storage, float x);
CML_HIDDEN float CMLInternalArrayFunctionInterpolateNone(const CMLInternalArrayFunctionStorage* storage, float indx);
CML_HIDDEN float CMLInternalArrayFunctionInterpolateFloor(const CMLInternalArrayFunctionStorage* storage, float indx);
CML_HIDDEN float CMLInternalArrayFunctionInterpolateBox(const CMLInternalArrayFunctionStorage* storage, float indx);
CML_HIDDEN float CMLInternalArrayFunctionInterpolateInterval(const CMLInternalArrayFunctionStorage* storage, float indx);
CML_HIDDEN float CMLInternalArrayFunctionInterpolateLinear(const CMLInternalArrayFunctionStorage* storage, float indx);


CML_HIDDEN float CMLInternalArrayFunctionExtrapolateDownClampZero(const CMLInternalArrayFunctionStorage* storage, float x){
  x = x;  // no warning
  storage = storage;
  return 0.f;
}

CML_HIDDEN float CMLInternalArrayFunctionExtrapolateDownLinearZero(const CMLInternalArrayFunctionStorage* storage, float x){
  x = (storage->mincoord - x) * storage->inverseinterval;
  if(x > 1.f){
    return 0.f;
  }else{
    return storage->array[0] * (1.f - x);
  }
}

CML_HIDDEN float CMLInternalArrayFunctionExtrapolateDownClampValue(const CMLInternalArrayFunctionStorage* storage, float x){
  x = x;  // no warning
  return storage->array[0];
}

CML_HIDDEN float CMLInternalArrayFunctionExtrapolateDownGradient(const CMLInternalArrayFunctionStorage* storage, float x){
  float indx = (x - storage->mincoord) * storage->inverseinterval;
  return storage->array[0] + (storage->array[1] - storage->array[0]) * indx;
}



CML_HIDDEN float CMLInternalArrayFunctionExtrapolateUpClampZero(const CMLInternalArrayFunctionStorage* storage, float x){
  x = x;  // no warning
  storage = storage;
  return 0.f;
}

CML_HIDDEN float CMLInternalArrayFunctionExtrapolateUpLinearZero(const CMLInternalArrayFunctionStorage* storage, float x){
  x = (x - storage->maxcoord) * storage->inverseinterval;
  if(x > 1.f){
    return 0.f;
  }else{
    return storage->array[storage->size - 1] * (1.f - x);
  }
}

CML_HIDDEN float CMLInternalArrayFunctionExtrapolateUpClampValue(const CMLInternalArrayFunctionStorage* storage, float x){
  x = x;  // no warning
  return storage->array[storage->size - 1];
}

CML_HIDDEN float CMLInternalArrayFunctionExtrapolateUpGradient(const CMLInternalArrayFunctionStorage* storage, float x){
  float indx = (x - storage->maxcoord) * storage->inverseinterval;
  return storage->array[storage->size - 1] + (storage->array[storage->size - 2] - storage->array[storage->size - 1]) * indx;
}




CML_HIDDEN float CMLInternalArrayFunctionInterpolateNone(const CMLInternalArrayFunctionStorage* storage, float indx){
  size_t i = (size_t)indx;
  if((float)(i) == indx){
    return storage->array[i];
  }else{
    return 0.f;
  }
}

CML_HIDDEN float CMLInternalArrayFunctionInterpolateFloor(const CMLInternalArrayFunctionStorage* storage, float indx){
  return storage->array[(size_t)indx];
}

CML_HIDDEN float CMLInternalArrayFunctionInterpolateBox(const CMLInternalArrayFunctionStorage* storage, float indx){
  return storage->array[(size_t)(indx + .5f)];
}

CML_HIDDEN float CMLInternalArrayFunctionInterpolateInterval(const CMLInternalArrayFunctionStorage* storage, float indx){
  return storage->array[(size_t)indx];
}

CML_HIDDEN float CMLInternalArrayFunctionInterpolateLinear(const CMLInternalArrayFunctionStorage* storage, float indx){
  size_t i1 = (size_t)indx;
  size_t i2 = i1 + 1;
  float alpha = indx - (float)(i1);
  return storage->array[i1] - (storage->array[i1] - storage->array[i2]) * alpha;
}







// //////////////////////////////////////////////
// Array Function
// //////////////////////////////////////////////

// Prototypes:
CML_HIDDEN void CMLInternalDestructArrayFunction(void* data);
CML_HIDDEN void CMLInternalConstructArrayFunction(float* params, void** data, CMLDefinitionRange* defrange, const void* input);
CML_HIDDEN float cmlInternalEvaluateArrayFunction(float* params, const void* data, float x);


CML_HIDDEN void CMLInternalDestructArrayFunction(void* data){
  CMLInternalArrayFunctionStorage* storage = (CMLInternalArrayFunctionStorage*)data;
  if(storage->isowner){
    free((void*)storage->array);
  }
  free(storage);
}


CML_HIDDEN void CMLInternalConstructArrayFunction(float* params, void** data, CMLDefinitionRange* defrange, const void* input){
  params = params; // no warning
  CMLInternalArrayFunctionStorage* storage;
  CMLInternalArrayFunctionDescriptor* desc = (CMLInternalArrayFunctionDescriptor*)input;
  *data = cmlAllocate(sizeof(CMLInternalArrayFunctionStorage));
  storage = (CMLInternalArrayFunctionStorage*)(*data);
  storage->array = desc->buffer;
  storage->size = desc->entrycount;
  storage->isowner = desc->ownbuffer;

  #ifndef NDEBUG
    if(storage->size <= 1){
      cmlError("Array Function with 1 or 0 Entries may not work properly yet.");
    }
  #endif

  defrange->minSampleCoord = desc->minimalcoord;
  defrange->maxSampleCoord = desc->maximalcoord;

  switch(desc->downextrapolationmethod){
  case CML_EXTRAPOLATION_CLAMP_ZERO:
    storage->extrapolateDown = &CMLInternalArrayFunctionExtrapolateDownClampZero;
    defrange->minNonTrivialCoord = desc->minimalcoord;
    break;
  case CML_EXTRAPOLATION_LINEAR_ZERO:
    storage->extrapolateDown = &CMLInternalArrayFunctionExtrapolateDownLinearZero;
    defrange->minNonTrivialCoord = desc->minimalcoord - CMLgetStepSize(desc->minimalcoord, desc->maximalcoord, desc->entrycount);
    break;
  case CML_EXTRAPOLATION_CLAMP_VALUE:
    storage->extrapolateDown = &CMLInternalArrayFunctionExtrapolateDownClampValue;
    defrange->minNonTrivialCoord = -CML_INFINITY;
    break;
  case CML_EXTRAPOLATION_GRADIENT:
    storage->extrapolateDown = &CMLInternalArrayFunctionExtrapolateDownGradient;
    defrange->minNonTrivialCoord = -CML_INFINITY;
    break;
  default:
    #ifndef NDEBUG
      cmlError("Undefined Down-Extrapolation method.");
    #endif
    storage->extrapolateDown = CML_NULL;
    break;
  }

  switch(desc->upextrapolationmethod){
  case CML_EXTRAPOLATION_CLAMP_ZERO:
    storage->extrapolateUp   = &CMLInternalArrayFunctionExtrapolateUpClampZero;
    defrange->maxNonTrivialCoord = desc->maximalcoord;
    break;
  case CML_EXTRAPOLATION_LINEAR_ZERO:
    storage->extrapolateUp   = &CMLInternalArrayFunctionExtrapolateUpLinearZero;
    defrange->maxNonTrivialCoord = desc->maximalcoord + CMLgetStepSize(desc->minimalcoord, desc->maximalcoord, desc->entrycount);
    break;
  case CML_EXTRAPOLATION_CLAMP_VALUE:
    storage->extrapolateUp   = &CMLInternalArrayFunctionExtrapolateUpClampValue;
    defrange->maxNonTrivialCoord = CML_INFINITY;
    break;
  case CML_EXTRAPOLATION_GRADIENT:
    storage->extrapolateUp   = &CMLInternalArrayFunctionExtrapolateUpGradient;
    defrange->maxNonTrivialCoord = CML_INFINITY;
    break;
  default:
    #ifndef NDEBUG
      cmlError("Undefined Up-Extrapolation method.");
    #endif
    storage->extrapolateUp = CML_NULL;
    break;
  }

  switch(desc->interpolationmethod){
  case CML_INTERPOLATION_NONE:
    storage->mincoord = desc->minimalcoord;
    storage->maxcoord = desc->maximalcoord;
    storage->interpolate = &CMLInternalArrayFunctionInterpolateNone;
    storage->inverseinterval = (float)(storage->size - 1) / (storage->maxcoord - storage->mincoord);
    break;
  case CML_INTERPOLATION_FLOOR:
    storage->mincoord = desc->minimalcoord;
    storage->maxcoord = desc->maximalcoord + ((desc->maximalcoord - desc->minimalcoord) / (float)(storage->size - 1));
    storage->interpolate = &CMLInternalArrayFunctionInterpolateFloor;
    storage->inverseinterval = (float)(storage->size - 1) / (storage->maxcoord - storage->mincoord);
    break;
  case CML_INTERPOLATION_BOX:
    storage->mincoord = desc->minimalcoord - (.5f * (desc->maximalcoord - desc->minimalcoord) / (float)(storage->size - 1));
    storage->maxcoord = desc->maximalcoord + (.5f * (desc->maximalcoord - desc->minimalcoord) / (float)(storage->size - 1));
    storage->interpolate = &CMLInternalArrayFunctionInterpolateBox;
    storage->inverseinterval = (float)(storage->size - 1) / (storage->maxcoord - storage->mincoord);
    break;
  case CML_INTERPOLATION_INTERVAL:
    storage->mincoord = desc->minimalcoord;
    storage->maxcoord = desc->maximalcoord;
    storage->interpolate = &CMLInternalArrayFunctionInterpolateInterval;
    storage->inverseinterval = (float)(storage->size) / (storage->maxcoord - storage->mincoord);
    break;
  case CML_INTERPOLATION_LINEAR:
    storage->mincoord = desc->minimalcoord;
    storage->maxcoord = desc->maximalcoord;
    storage->interpolate = &CMLInternalArrayFunctionInterpolateLinear;
    storage->inverseinterval = (float)(storage->size - 1) / (storage->maxcoord - storage->mincoord);
    break;
  default:
    #ifndef NDEBUG
      cmlError("Undefined Interpolation method.");
    #endif
    storage->interpolate = CML_NULL;
    break;
  }
  defrange->stepsize = cmlInverse(storage->inverseinterval);
}

CML_HIDDEN float cmlInternalEvaluateArrayFunction(float* params, const void* data, float x){
  params = params; // no warning
  CMLInternalArrayFunctionStorage* storage = (CMLInternalArrayFunctionStorage*)data;
  if(x == storage->mincoord){return storage->array[0];}
  else if(x == storage->maxcoord){return storage->array[storage->size - 1];}
  else if(x < storage->mincoord){return storage->extrapolateDown(storage, x);}
  else if(x > storage->maxcoord){return storage->extrapolateUp(storage, x);}
  else{
    float indx = (x - storage->mincoord) * storage->inverseinterval;
    return storage->interpolate(storage, indx);
  }
}


CML_API CMLFunction* CMLcreateArrayFunction(const float* buffer, CMLBool ownbuffer, size_t entrycount, float minimalcoord, float maximalcoord, CMLInterpolationMethod interpolationmethod, CMLExtrapolationMethod extrapolationmethoddown, CMLExtrapolationMethod extrapolationmethodup){
  CMLInternalArrayFunctionDescriptor desc;
  desc.buffer = buffer;
  desc.ownbuffer = ownbuffer;
  desc.entrycount = entrycount;
  desc.minimalcoord = minimalcoord;
  desc.maximalcoord = maximalcoord;
  desc.interpolationmethod = interpolationmethod;
  desc.downextrapolationmethod = extrapolationmethoddown;
  desc.upextrapolationmethod = extrapolationmethodup;
  return CMLcreateFunction(cmlInternalEvaluateArrayFunction, CMLInternalConstructArrayFunction, CMLInternalDestructArrayFunction, 0, &desc);
}







// //////////////////////////////////////////////
// Blackbody
// //////////////////////////////////////////////

// Prototypes:
CML_HIDDEN void CMLInternalConstructBlackBody(float* params, void** data, CMLDefinitionRange* defrange, const void* input);
CML_HIDDEN void CMLInternalDestructBlackBody(void* data);
CML_HIDDEN float cmlInternalEvaluateBlackBody(float* params, const void* data, float x);


CML_HIDDEN void CMLInternalConstructBlackBody(float* params, void** data, CMLDefinitionRange* defrange, const void* input){
  params = params; // no warning
  float* c;
  float temperature = *((float*)input);
  if(temperature <= 0){
    #ifndef NDEBUG
      cmlError("Temperature must be greater than 0 Kelvin.");
    #endif
    return;
  }
  *data = cmlAllocate(sizeof(float));
  c = (float*)(*data);
  // *c = (CML_PLANCK * CMLIGHT_SPEED_VAC) / (CML_BOLTZMANN * temp);
  if(temperature == CML_INFINITY){
    *c = 0.f;
  }else{
    *c = CML_SECOND_RAD / temperature;
  }
  defrange->minNonTrivialCoord = CML_SINGULARITY;
}


CML_HIDDEN float cmlInternalEvaluateBlackBody(float* params, const void* data, float x){
  params = params; // no warning
  float c;
  float nanolambda;
  // Note: x is expected in [nanometer]
  if(x <= 0){
    #ifndef NDEBUG
      cmlError("Blackbody radiator is only defined for input values greater than 0.");
    #endif
    return 0.f;
  }
  c = *((float*)data);
  nanolambda = x * 1e-9f;
  if(c == 0.f){
    return CML_2PI * CML_PLANCK * CML_LIGHT_SPEED_VAC * CML_LIGHT_SPEED_VAC / (powf(nanolambda, 5.f));
  }else{
    return CML_2PI * CML_PLANCK * CML_LIGHT_SPEED_VAC * CML_LIGHT_SPEED_VAC / (powf(nanolambda, 5.f) * (expf(c / nanolambda) - 1.f));
  }
  // first constant is CML_2PI * CML_PLANCK * CML_LIGHT_SPEED_VAC * CML_LIGHT_SPEED_VAC;
//    return float(.587756042555631108333846414986e-15) / (Pow(nanolambda, float(5.)) * (Exp(c / nanolambda) - float(1.)));
}


CML_HIDDEN void CMLInternalDestructBlackBody(void* data){
  free(data);
}


CML_API CMLFunction* CMLcreateBlackBody(float temperature){
  return CMLcreateFunction(cmlInternalEvaluateBlackBody, CMLInternalConstructBlackBody, CMLInternalDestructBlackBody, 0, &temperature);
}





// //////////////////////////////////////////////
// CIE A illuminant
// //////////////////////////////////////////////

// Prototypes:
CML_HIDDEN void CMLInternalConstructCIEAIlluminant(float* params, void** data, CMLDefinitionRange* defrange, const void* input);
CML_HIDDEN float cmlInternalEvaluateCIEAIlluminant(float* params, const void* data, float x);


CML_HIDDEN void CMLInternalConstructCIEAIlluminant(float* params, void** data, CMLDefinitionRange* defrange, const void* input){
  params = params; // no warning
  data = data;
  input = input;
  defrange->minNonTrivialCoord = CML_SINGULARITY;
}


CML_HIDDEN float cmlInternalEvaluateCIEAIlluminant(float* params, const void* data, float x){
  params = params; // no warning
  float nanolambda;
  data = data;
  #ifndef NDEBUG
    if(x <= 0){cmlError("CIE A illuminant is only defined for input values greater than 0.");}
  #endif
  nanolambda = x * 1e-9f;
  // First constant is 100. * pow(560e-9.,5.);
  // Second constant is exp(1.435e-2 / (2848. * 560e-9)) - 1.;
  // third constant is c2 = (1.435e-2) / (2848.);
  // Note: 1.435e-2 is approximately CML_PLANCK*CML_LIGHT_SPEED_VAC/CML_BOLTZMANN
  // 1.435e7 appears to be the standard used.
  return (.5507317760e-31f / powf(nanolambda, 5.f)) * (8082.19209692894427103001499060f / (expf(.5038623596e-5f / nanolambda) - 1.f));
}


CML_API CMLFunction* CMLcreateCIEAIlluminant(){
  return CMLcreateFunction(cmlInternalEvaluateCIEAIlluminant, CMLInternalConstructCIEAIlluminant, CML_NULL, 0, CML_NULL);
}





// //////////////////////////////////////////////
// CIE D illuminant
// //////////////////////////////////////////////

// Steps: 10nm
// Values from the publicly avaliable distribution of CIE. Original values
// available in 5nm steps but each odd sampling point corresponds to the
// linear interpolation of the even sampling points. Therefore it has been
// converted to 10nm.
#define CML_D_ILLUMINANT_ENTRYCOUNT 54
#define CML_D_ILLUMINANT_MIN   300.f
#define CML_D_ILLUMINANT_MAX   830.f
CML_HIDDEN const float dilluminantS0[CML_D_ILLUMINANT_ENTRYCOUNT] =
  { 0.04f,   6.00f,  29.60f,  55.30f,  57.30f,  61.80f,  61.50f,  68.80f,  63.40f,  65.80f,
   94.80f, 104.80f, 105.90f,  96.80f, 113.90f, 125.60f, 125.50f, 121.30f, 121.30f, 113.50f,
  113.10f, 110.80f, 106.50f, 108.80f, 105.30f, 104.40f, 100.00f,  96.00f,  95.10f,  89.10f,
   90.50f,  90.30f,  88.40f,  84.00f,  85.10f,  81.90f,  82.60f,  84.90f,  81.30f,  71.90f,
   74.30f,  76.40f,  63.30f,  71.70f,  77.00f,  65.20f,  47.70f,  68.60f,  65.00f,  66.00f,
   61.00f,  53.30f,  58.90f,  61.90f};
CML_HIDDEN const float dilluminantS1[CML_D_ILLUMINANT_ENTRYCOUNT] =
  { 0.02f,   4.50f,  22.40f,  42.00f,  40.60f,  41.60f,  38.00f,  42.40f,  38.50f,  35.00f,
   43.40f,  46.30f,  43.90f,  37.10f,  36.70f,  35.90f,  32.60f,  27.90f,  24.30f,  20.10f,
   16.20f,  13.20f,   8.60f,   6.10f,   4.20f,   1.90f,   0.00f,  -1.60f,  -3.50f,  -3.50f,
   -5.80f,  -7.20f,  -8.60f,  -9.50f, -10.90f, -10.70f, -12.00f, -14.00f, -13.60f, -12.00f,
  -13.30f, -12.90f, -10.60f, -11.60f, -12.20f, -10.20f,  -7.80f, -11.20f, -10.40f, -10.60f,
   -9.70f,  -8.30f,  -9.30f,  -9.80f};
CML_HIDDEN const float dilluminantS2[CML_D_ILLUMINANT_ENTRYCOUNT] =
  {0.00f,  2.00f,  4.00f,  8.50f,  7.80f,  6.70f,  5.30f,  6.10f,  3.00f,  1.20f,
  -1.10f, -0.50f, -0.70f, -1.20f, -2.60f, -2.90f, -2.80f, -2.60f, -2.60f, -1.80f,
  -1.50f, -1.30f, -1.20f, -1.00f, -0.50f, -0.30f,  0.00f,  0.20f,  0.50f,  2.10f,
   3.20f,  4.10f,  4.70f,  5.10f,  6.70f,  7.30f,  8.60f,  9.80f, 10.20f,  8.30f,
   9.60f,  8.50f,  7.00f,  7.60f,  8.00f,  6.70f,  5.20f,  7.40f,  6.80f,  7.00f,
   6.40f,  5.50f,  6.10f,  6.50f};

CML_HIDEF void CMLInternalComputeDIlluminantWhitePoint(float* whitepoint, float temp){
  if(temp < 4000.f){temp = 4000.f;}
  if(temp > 25000.f){temp = 25000.f;}
  
  if(temp <= 7000.f){
    whitepoint[0] = ((-4.607e9f / temp + 2.9678e6f) / temp + 0.09911e3f) / temp + 0.244063f;
  }else{
    whitepoint[0] = ((-2.0064e9f / temp + 1.9018e6f) / temp + 0.24748e3f) / temp + 0.23704f;
  }
  whitepoint[1] = -3.f * whitepoint[0] * whitepoint[0] + 2.87f * whitepoint[0] - 0.275f;
}

// todo make temperature a parameter

CML_API CMLFunction* CMLcreateCIEDIlluminant(float temperature){
  float Minv;
  float M1;
  float M2;
  CMLuint32 l;
  float* array;
  float whitepoint[2];
  #ifndef NDEBUG
    if(temperature <= 0){cmlError("Temperature must be greater than 0 Kelvin.");}
  #endif
  // Note that the array will be deleted by the CMLArray.
  array = (float*)cmlAllocate(CML_D_ILLUMINANT_ENTRYCOUNT * sizeof(float));
  CMLInternalComputeDIlluminantWhitePoint(whitepoint, temperature);
  Minv = cmlInverse(0.0241f +  0.2562f * whitepoint[0] -  0.7341f * whitepoint[1]);
  M1 = (-1.3515f -  1.7703f * whitepoint[0] +  5.9114f * whitepoint[1]) * Minv;
  M2 = ( 0.03f   - 31.4424f * whitepoint[0] + 30.0717f * whitepoint[1]) * Minv;
  for(l=0; l<CML_D_ILLUMINANT_ENTRYCOUNT; ++l){
    array[l] = dilluminantS0[l] + M1*dilluminantS1[l] + M2*dilluminantS2[l];
  }
  // Multiple sources suggest that the values are considered to be linearly
  // interpolated.
  return CMLcreateArrayFunction(array, CML_TRUE, CML_D_ILLUMINANT_ENTRYCOUNT, CML_D_ILLUMINANT_MIN, CML_D_ILLUMINANT_MAX, CML_INTERPOLATION_LINEAR, CML_EXTRAPOLATION_LINEAR_ZERO, CML_EXTRAPOLATION_LINEAR_ZERO);
}









// //////////////////////////////////////////////
// Linear Response
// //////////////////////////////////////////////

// Prototypes:
CML_HIDDEN float cmlInternalEvaluateLinearResponse(float* params, const void* data, float x);


CML_HIDDEN float cmlInternalEvaluateLinearResponse(float* params, const void* data, float x){
  params = params; // no warning
  data = data;
  return x;
}


CML_API CMLFunction* CMLcreateLinearResponse(){
  return CMLcreateFunction(cmlInternalEvaluateLinearResponse, CML_NULL, CML_NULL, 0, CML_NULL);
}






// //////////////////////////////////////////////
// Gamma Response
// //////////////////////////////////////////////

// Prototypes:
CML_HIDDEN void CMLInternalConstructGammaResponse(float* params, void** data, CMLDefinitionRange* defrange, const void* input);
CML_HIDDEN float cmlInternalEvaluateGammaResponse(float* params, const void* data, float x);
CML_HIDDEN void CMLInternalDestructGammaResponse(void* data);


CML_HIDDEN void CMLInternalConstructGammaResponse(float* params, void** data, CMLDefinitionRange* defrange, const void* input){
  data = data; // no warning
  defrange = defrange;
  params[0] = *((float*)input);
}


CML_HIDDEN float cmlInternalEvaluateGammaResponse(float* params, const void* data, float x){
  data = data; // no warning
  if(x < 0.f){
    return -powf(-x, params[0]);
  }else{
    return powf(x, params[0]);
  }
}


CML_HIDDEN void CMLInternalDestructGammaResponse(void* data){
  free(data);
}


CML_API CMLFunction* CMLcreateGammaResponse(float gamma){
  return CMLcreateFunction(cmlInternalEvaluateGammaResponse, CMLInternalConstructGammaResponse, CMLInternalDestructGammaResponse, 1, &gamma);
}





// //////////////////////////////////////////////
// Linear Gamma Response
// //////////////////////////////////////////////

typedef struct GammaLinearInputParameters{
  float gamma;
  float offset;
  float linscale;
  float split;
} GammaLinearInputParameters;


// Prototypes:
CML_HIDDEN void CMLInternalConstructGammaLinearResponse(float* params, void** data, CMLDefinitionRange* defrange, const void* input);
CML_HIDDEN float cmlInternalEvaluateGammaLinearResponse(float* params, const void* data, float x);
CML_HIDDEN void CMLInternalDestructGammaLinearResponse(void* data);
typedef struct GammaLinearStruct{
  float invgamma;
  float offset;
  float curvescale;
  float linscale;
  float splitpoint;
} GammaLinearStruct;


CML_HIDDEN void CMLInternalConstructGammaLinearResponse(float* params, void** data, CMLDefinitionRange* defrange, const void* input){
  defrange = defrange;
  params[0] = ((GammaLinearInputParameters*)input)->gamma;
  params[1] = ((GammaLinearInputParameters*)input)->offset;
  params[2] = ((GammaLinearInputParameters*)input)->linscale;
  params[3] = ((GammaLinearInputParameters*)input)->split;
  *data = cmlAllocate(sizeof(GammaLinearStruct));
  ((GammaLinearStruct*)(*data))->invgamma = cmlInverse(params[0]);
  ((GammaLinearStruct*)(*data))->offset = params[1];
  ((GammaLinearStruct*)(*data))->curvescale = params[1] + 1.f;
  ((GammaLinearStruct*)(*data))->linscale = params[2];
  ((GammaLinearStruct*)(*data))->splitpoint = params[3];
}


CML_HIDDEN float cmlInternalEvaluateGammaLinearResponse(float* params, const void* data, float x){
  params = params; // no warning
  if(x > ((GammaLinearStruct*)data)->splitpoint){
    return (((GammaLinearStruct*)data)->curvescale) * powf(x, ((GammaLinearStruct*)data)->invgamma) - ((GammaLinearStruct*)data)->offset;
  }else{
    return ((GammaLinearStruct*)data)->linscale * x;
  }
}


CML_HIDDEN void CMLInternalDestructGammaLinearResponse(void* data){
  free(data);
}


CML_API CMLFunction* CMLcreateGammaLinearResponse(float gamma, float offset, float linscale, float split){
  GammaLinearInputParameters tmpstruct = {gamma, offset, linscale, split};
//                                  offset / (gamma - 1.f) / linscale};
//                                  (linscale * offset - 1.f) / (powf(offset, gamma) - 1.f)};
  return CMLcreateFunction(cmlInternalEvaluateGammaLinearResponse, CMLInternalConstructGammaLinearResponse, CMLInternalDestructGammaLinearResponse, 4, &tmpstruct);
}




// //////////////////////////////////////////////
// Inverse Linear Gamma Response
// //////////////////////////////////////////////

// Prototypes:
CML_HIDDEN void CMLInternalConstructInverseGammaLinearResponse(float* params, void** data, CMLDefinitionRange* defrange, const void* input);
CML_HIDDEN float cmlInternalEvaluateInverseGammaLinearResponse(float* params, const void* data, float x);
CML_HIDDEN void CMLInternalDestructInverseGammaLinearResponse(void* data);
typedef struct InverseGammaLinearStruct{
  float gamma;
  float offset;
  float invcurvescale;
  float invlinscale;
  float splitpoint;
} InverseGammaLinearStruct;

CML_HIDDEN void CMLInternalConstructInverseGammaLinearResponse(float* params, void** data, CMLDefinitionRange* defrange, const void* input){
  params = params; // no warning
  defrange = defrange;
  params[0] = ((GammaLinearInputParameters*)input)->gamma;
  params[1] = ((GammaLinearInputParameters*)input)->offset;
  params[2] = ((GammaLinearInputParameters*)input)->linscale;
  params[3] = ((GammaLinearInputParameters*)input)->split;
  *data = cmlAllocate(sizeof(InverseGammaLinearStruct));
  ((InverseGammaLinearStruct*)(*data))->gamma = params[0];
  ((InverseGammaLinearStruct*)(*data))->offset = params[1];
  ((InverseGammaLinearStruct*)(*data))->invcurvescale = cmlInverse(params[1] + 1.f);
  ((InverseGammaLinearStruct*)(*data))->invlinscale = cmlInverse(params[2]);
  ((InverseGammaLinearStruct*)(*data))->splitpoint = params[3] * params[2];
}


CML_HIDDEN float cmlInternalEvaluateInverseGammaLinearResponse(float* params, const void* data, float x){
  params = params; // no warning
  if(x > ((InverseGammaLinearStruct*)data)->splitpoint){
    return powf((x + ((InverseGammaLinearStruct*)data)->offset) * ((InverseGammaLinearStruct*)data)->invcurvescale, ((InverseGammaLinearStruct*)data)->gamma);
  }else{
    return ((InverseGammaLinearStruct*)data)->invlinscale * x;
  }
}


CML_HIDDEN void CMLInternalDestructInverseGammaLinearResponse(void* data){
  free(data);
}


CML_API CMLFunction* CMLcreateInverseGammaLinearResponse(float gamma, float offset, float linscale, float split){
  GammaLinearInputParameters tmpstruct = {gamma, offset, linscale, split};
//  InverseGammaLinearStruct tmpstruct = { gamma,
//                                  offset,
//                                  cmlInverse(offset + 1.f),
//                                  cmlInverse(linscale),
//                                  split / linscale};
//                                  offset / (gamma - 1.f)};
//                                  linscale * (linscale * offset - 1.f) / (powf(offset, gamma) - 1.f)};
  return CMLcreateFunction(cmlInternalEvaluateInverseGammaLinearResponse, CMLInternalConstructInverseGammaLinearResponse, CMLInternalDestructInverseGammaLinearResponse, 4, &tmpstruct);
}


// //////////////////////////////////////////////
// sRGB Helper Definitions
// //////////////////////////////////////////////

#define CML_SRGB_OFFSET              0.055f
#define CML_SRGB_LIN_SCALE           12.92f
#define CML_SRGB_LIN_INV_SCALE       0.077399380804954f
#define CML_SRGB_SCALE               1.055f
#define CML_SRGB_INV_SCALE           0.947867298578199f
#define CML_SRGB_GAMMA               2.4f
#define CML_SRGB_INV_GAMMA           0.416666666666667f

#define CML_LIN_SRGB_SWITCH          0.040448236277f
#define CML_SRGB_LIN_SWITCH          0.0031306684425f





// //////////////////////////////////////////////
// sRGB -> XYZ Response
// //////////////////////////////////////////////

// Prototypes:
CML_HIDDEN float cmlInternalEvaluatesRGBToXYZResponse(float* params, const void* data, float x);


CML_HIDDEN float cmlInternalEvaluatesRGBToXYZResponse(float* params, const void* data, float x){
  params = params; // no warning
  data = data;
  if(x > CML_LIN_SRGB_SWITCH){
    return powf((x + CML_SRGB_OFFSET) * CML_SRGB_INV_SCALE, CML_SRGB_GAMMA);
  }else if(x < -CML_LIN_SRGB_SWITCH){
    return -powf((-x + CML_SRGB_OFFSET) * CML_SRGB_INV_SCALE, CML_SRGB_GAMMA);
  }else{
    return x * CML_SRGB_LIN_INV_SCALE;
  }
}


CML_API CMLFunction* CMLcreatesRGBToXYZResponse(){
  return CMLcreateFunction(cmlInternalEvaluatesRGBToXYZResponse, CML_NULL, CML_NULL, 0, CML_NULL);
}






// //////////////////////////////////////////////
// XYZ -> sRGB Response
// //////////////////////////////////////////////

// Prototypes:
CML_HIDDEN float cmlInternalEvaluateXYZTosRGBResponse(float* params, const void* data, float x);


CML_HIDDEN float cmlInternalEvaluateXYZTosRGBResponse(float* params, const void* data, float x){
  params = params; // no warning
  data = data;
  if(x > CML_SRGB_LIN_SWITCH){
    return (CML_SRGB_SCALE * powf(x, CML_SRGB_INV_GAMMA) - CML_SRGB_OFFSET);
  }else if(x < -CML_SRGB_LIN_SWITCH){
    return -(CML_SRGB_SCALE * powf(-x, CML_SRGB_INV_GAMMA) - CML_SRGB_OFFSET);
  }else{
    return (x * CML_SRGB_LIN_SCALE);
  }
}


CML_API CMLFunction* CMLcreateXYZTosRGBResponse(){
  return CMLcreateFunction(cmlInternalEvaluateXYZTosRGBResponse, CML_NULL, CML_NULL, 0, CML_NULL);
}




// //////////////////////////////////////////////
// L Star Helper Definitions
// //////////////////////////////////////////////

#define CML_LSTAR_LIN_SWITCH          0.08f                 // 8 / 100
#define CML_LIN_LSTAR_SWITCH          0.008856451679036f    // 216.f / 24389.f
#define CML_LSTAR_LINEAR_SCALE        9.03296296296296296f  // .01 * 24389.f / 27.f
#define CML_LSTAR_LINEAR_INV_SCALE    0.1107056459879f      // 100 * 27.f / 24389.f

#define CML_LSTAR_LIN_SWITCH_STANDARD           0.079995919930638f
#define CML_LIN_LSTAR_SWITCH_STANDARD           0.008856f
#define CML_LSTAR_LINEAR_SCALE_STANDARD         9.033f
#define CML_LSTAR_LINEAR_INV_SCALE_STANDARD     0.110705192073508f






// //////////////////////////////////////////////
// Y -> L Star Response
// //////////////////////////////////////////////

// Prototypes:
CML_HIDDEN float cmlInternalEvaluateYToLStarResponse(float* params, const void* data, float x);


CML_HIDDEN float cmlInternalEvaluateYToLStarResponse(float* params, const void* data, float x){
  params = params; // no warning
  data = data;
  if(x > CML_LIN_LSTAR_SWITCH){
    return cmlInternalfytoLr(CMLCbrt(x));
  }else{
    return x * CML_LSTAR_LINEAR_SCALE;
  }
}

CML_API CMLFunction* CMLcreateYToLStarResponse(){
  return CMLcreateFunction(cmlInternalEvaluateYToLStarResponse, CML_NULL, CML_NULL, 0, CML_NULL);
}







// //////////////////////////////////////////////
// L Star -> Y Response
// //////////////////////////////////////////////

// Prototypes:
CML_HIDDEN float cmlInternalEvaluateLStarToYResponse(float* params, const void* data, float x);


CML_HIDDEN float cmlInternalEvaluateLStarToYResponse(float* params, const void* data, float x){
  params = params; // no warning
  data = data;
  if(x > CML_LSTAR_LIN_SWITCH){
    float fy = cmlInternalLrtofy(x);
    return fy*fy*fy;
  }else{
    return x * CML_LSTAR_LINEAR_INV_SCALE;
  }
}

CML_API CMLFunction* CMLcreateLStarToYResponse(){
  return CMLcreateFunction(cmlInternalEvaluateLStarToYResponse, CML_NULL, CML_NULL, 0, CML_NULL);
}







// //////////////////////////////////////////////
// Linear -> L Star Standard Response
// //////////////////////////////////////////////

// Prototypes:
CML_HIDDEN float cmlInternalEvaluateYToLStarStandardResponse(float* params, const void* data, float x);


CML_HIDDEN float cmlInternalEvaluateYToLStarStandardResponse(float* params, const void* data, float x){
  params = params; // no warning
  data = data;
  if(x > CML_LIN_LSTAR_SWITCH_STANDARD){
    return cmlInternalfytoLr(CMLCbrt(x));
  }else{
    return x * CML_LSTAR_LINEAR_SCALE_STANDARD;
  }
}


CML_API CMLFunction* CMLcreateYToLStarStandardResponse(){
  return CMLcreateFunction(cmlInternalEvaluateYToLStarStandardResponse, CML_NULL, CML_NULL, 0, CML_NULL);
}





// //////////////////////////////////////////////
// L Star -> Linear Response
// //////////////////////////////////////////////

// Prototypes:
CML_HIDDEN float cmlInternalEvaluateLStarToYStandardResponse(float* params, const void* data, float x);


CML_HIDDEN float cmlInternalEvaluateLStarToYStandardResponse(float* params, const void* data, float x){
  params = params; // no warning
  data = data;
  if(x > CML_LSTAR_LIN_SWITCH_STANDARD){
    float fy = cmlInternalLrtofy(x);
    return fy*fy*fy;
  }else{
    return x * CML_LSTAR_LINEAR_INV_SCALE_STANDARD;
  }
}


CML_API CMLFunction* CMLcreateLStarToYStandardResponse(){
  return CMLcreateFunction(cmlInternalEvaluateLStarToYStandardResponse, CML_NULL, CML_NULL, 0, CML_NULL);
}






// //////////////////////////////////////////////
// Dirac Filter
// //////////////////////////////////////////////

// Prototypes:
CML_HIDDEN void CMLInternalConstructDiracFilter(float* params, void** data, CMLDefinitionRange* defrange, const void* input);
CML_HIDDEN void CMLInternalDestructDiracFilter(void* data);
CML_HIDDEN float cmlInternalEvaluateDiracFilter(float* params, const void* data, float x);


CML_HIDDEN void CMLInternalConstructDiracFilter(float* params, void** data, CMLDefinitionRange* defrange, const void* input){
  params = params; // no warning
  float pos = *((float*)input);
  *data = cmlAllocate(sizeof(float));
  *((float*)(*data)) = pos;
  defrange->minSampleCoord = pos;
  defrange->maxSampleCoord = pos;
  defrange->minNonTrivialCoord = pos;
  defrange->maxNonTrivialCoord = pos;
}


CML_HIDDEN void CMLInternalDestructDiracFilter(void* data){
  free(data);
}


CML_HIDDEN float cmlInternalEvaluateDiracFilter(float* params, const void* data, float x){
  params = params; // no warning
  float pos = *((float*)data);
  return (x == pos) ? 1.f: 0.f;
}


CML_API CMLFunction* CMLcreateDiracFilter(float wavelength){
  return CMLcreateFunction(cmlInternalEvaluateDiracFilter, CMLInternalConstructDiracFilter, CMLInternalDestructDiracFilter, 0, &wavelength);
}






// //////////////////////////////////////////////
// Constant Filter
// //////////////////////////////////////////////

// Prototypes:
CML_HIDDEN void CMLInternalConstructConstFilter(float* params, void** data, CMLDefinitionRange* defrange, const void* input);
CML_HIDDEN void CMLInternalDestructConstFilter(void* data);
CML_HIDDEN float cmlInternalEvaluateConstFilter(float* params, const void* data, float x);


CML_HIDDEN void CMLInternalConstructConstFilter(float* params, void** data, CMLDefinitionRange* defrange, const void* input){
  params = params; // no warning
  float value;
  defrange = defrange;
  value = *((float*)input);
  *data = cmlAllocate(sizeof(float));
  *((float*)(*data)) = value;
}


CML_HIDDEN void CMLInternalDestructConstFilter(void* data){
  free(data);
}


CML_HIDDEN float cmlInternalEvaluateConstFilter(float* params, const void* data, float x){
  params = params; // no warning
  x = x;  // No warning
  return *((float*)data);
}


CML_API CMLFunction* CMLcreateConstFilter(float value){
  return CMLcreateFunction(cmlInternalEvaluateConstFilter, CMLInternalConstructConstFilter, CMLInternalDestructConstFilter, 0, &value);
}






// //////////////////////////////////////////////
// Cut Filter
// //////////////////////////////////////////////

typedef struct CMLInternalCutFilterRange CMLInternalCutFilterRange;
struct CML_HIDDEN CMLInternalCutFilterRange{
  float min;
  float max;
};

// Prototypes:
CML_HIDDEN void CMLInternalConstructCutFilter(float* params, void** data, CMLDefinitionRange* defrange, const void* input);
CML_HIDDEN void CMLInternalDestructCutFilter(void* data);
CML_HIDDEN float cmlInternalEvaluateCutFilter(float* params, const void* data, float x);


CML_HIDDEN void CMLInternalConstructCutFilter(float* params, void** data, CMLDefinitionRange* defrange, const void* input){
  params = params; // no warning
  CMLInternalCutFilterRange* range;
  CMLInternalCutFilterRange* inrange = (CMLInternalCutFilterRange*)(input);
  *data = cmlAllocate(sizeof(CMLInternalCutFilterRange));
  range = (CMLInternalCutFilterRange*)(*data);
  range->min = inrange->min;
  range->max = inrange->max;
  defrange->minNonTrivialCoord = inrange->min;
  defrange->maxNonTrivialCoord = inrange->max;
}


CML_HIDDEN void CMLInternalDestructCutFilter(void* data){
  free(data);
}


CML_HIDDEN float cmlInternalEvaluateCutFilter(float* params, const void* data, float x){
  params = params; // no warning
  CMLInternalCutFilterRange* range = (CMLInternalCutFilterRange*)(data);
  return ((x>=range->min) && (x<=range->max)) ? 1.f : 0.f;
}


CML_API CMLFunction* CMLcreateCutFilter(float min, float max){
  CMLInternalCutFilterRange range = {min, max};
  return CMLcreateFunction(cmlInternalEvaluateCutFilter, CMLInternalConstructCutFilter, CMLInternalDestructCutFilter, 0, &range);
}






// //////////////////////////////////////////////
// Composite Function definitions
// //////////////////////////////////////////////

typedef struct CMLInternalFunctionFunctionStorage CMLInternalFunctionFunctionStorage;
struct CML_HIDDEN CMLInternalFunctionFunctionStorage{
  CMLFunction* func1;
  CMLFunction* func2;
};

typedef struct CMLInternalFunctionScalarStorage CMLInternalFunctionScalarStorage;
struct CML_HIDDEN CMLInternalFunctionScalarStorage{
  CMLFunction* func;
  float scalar;
};

typedef struct CMLInternalFunctionFunctionInput CMLInternalFunctionFunctionInput;
struct CML_HIDDEN CMLInternalFunctionFunctionInput{
  const CMLFunction* func1;
  const CMLFunction* func2;
};

typedef struct CMLInternalFunctionScalarInput CMLInternalFunctionScalarInput;
struct CML_HIDDEN CMLInternalFunctionScalarInput{
  const CMLFunction* func;
  float scalar;
};





// //////////////////////////////////////////////
// Function add Function
// //////////////////////////////////////////////

// Prototypes:
CML_HIDDEN void CMLInternalConstructFunctionAddFunction(float* params, void** data, CMLDefinitionRange* defrange, const void* input);
CML_HIDDEN void CMLInternalDestructFunctionAddFunction(void* data);
CML_HIDDEN float cmlInternalEvaluateFunctionAddFunction(float* params, const void* data, float x);


CML_HIDDEN void CMLInternalConstructFunctionAddFunction(float* params, void** data, CMLDefinitionRange* defrange, const void* input){
  params = params; // no warning
  CMLInternalFunctionFunctionStorage* thisdata;
  CMLDefinitionRange newrange;
  CMLInternalFunctionFunctionInput* indata = (CMLInternalFunctionFunctionInput*)(input);
  *data = cmlAllocate(sizeof(CMLInternalFunctionFunctionStorage));
  thisdata = (CMLInternalFunctionFunctionStorage*)(*data);
  thisdata->func1 = CMLduplicateFunction(indata->func1);
  thisdata->func2 = CMLduplicateFunction(indata->func2);
  newrange = CMLgetDefinitionRangeOf2Functions(indata->func1, indata->func2, CML_FALSE);
  *defrange = newrange;
}


CML_HIDDEN void CMLInternalDestructFunctionAddFunction(void* data){
  CMLInternalFunctionFunctionStorage* thisdata = (CMLInternalFunctionFunctionStorage*)data;
  cmlReleaseFunction(thisdata->func1);
  cmlReleaseFunction(thisdata->func2);
  free(data);
}


CML_HIDDEN float cmlInternalEvaluateFunctionAddFunction(float* params, const void* data, float x){
  params = params; // no warning
  CMLInternalFunctionFunctionStorage* thisdata = (CMLInternalFunctionFunctionStorage*)data;
  return cmlInternalEval(thisdata->func1, x) + cmlInternalEval(thisdata->func2, x);
}


CML_API CMLFunction* CMLcreateFunctionAddFunction(const CMLFunction* func1, const CMLFunction* func2){
  CMLInternalFunctionFunctionInput newdata = {func1, func2};
  return CMLcreateFunction(cmlInternalEvaluateFunctionAddFunction, CMLInternalConstructFunctionAddFunction, CMLInternalDestructFunctionAddFunction, 0, &newdata);
}






// //////////////////////////////////////////////
// Function sub Function
// //////////////////////////////////////////////

// Prototypes:
CML_HIDDEN void CMLInternalConstructFunctionSubFunction(float* params, void** data, CMLDefinitionRange* defrange, const void* input);
CML_HIDDEN void CMLInternalDestructFunctionSubFunction(void* data);
CML_HIDDEN float cmlInternalEvaluateFunctionSubFunction(float* params, const void* data, float x);


CML_HIDDEN void CMLInternalConstructFunctionSubFunction(float* params, void** data, CMLDefinitionRange* defrange, const void* input){
  params = params; // no warning
  CMLInternalFunctionFunctionStorage* thisdata;
  CMLDefinitionRange newrange;
  CMLInternalFunctionFunctionInput* indata = (CMLInternalFunctionFunctionInput*)(input);
  *data = cmlAllocate(sizeof(CMLInternalFunctionFunctionStorage));
  thisdata = (CMLInternalFunctionFunctionStorage*)(*data);
  thisdata->func1 = CMLduplicateFunction(indata->func1);
  thisdata->func2 = CMLduplicateFunction(indata->func2);
  newrange = CMLgetDefinitionRangeOf2Functions(indata->func1, indata->func2, CML_FALSE);
  *defrange = newrange;
}


CML_HIDDEN void CMLInternalDestructFunctionSubFunction(void* data){
  CMLInternalFunctionFunctionStorage* thisdata = (CMLInternalFunctionFunctionStorage*)data;
  cmlReleaseFunction(thisdata->func1);
  cmlReleaseFunction(thisdata->func2);
  free(data);
}


CML_HIDDEN float cmlInternalEvaluateFunctionSubFunction(float* params, const void* data, float x){
  params = params; // no warning
  CMLInternalFunctionFunctionStorage* thisdata = (CMLInternalFunctionFunctionStorage*)data;
  return cmlInternalEval(thisdata->func1, x) - cmlInternalEval(thisdata->func2, x);
}


CML_API CMLFunction* CMLcreateFunctionSubFunction(const CMLFunction* func1, const CMLFunction* func2){
  CMLInternalFunctionFunctionInput newdata = {func1, func2};
  return CMLcreateFunction(cmlInternalEvaluateFunctionSubFunction, CMLInternalConstructFunctionSubFunction, CMLInternalDestructFunctionSubFunction, 0, &newdata);
}







// //////////////////////////////////////////////
// Function mul Function
// //////////////////////////////////////////////

// Prototypes:
CML_HIDDEN void CMLInternalConstructFunctionMulFunction(float* params, void** data, CMLDefinitionRange* defrange, const void* input);
CML_HIDDEN void CMLInternalDestructFunctionMulFunction(void* data);
CML_HIDDEN float cmlInternalEvaluateFunctionMulFunction(float* params, const void* data, float x);


CML_HIDDEN void CMLInternalConstructFunctionMulFunction(float* params, void** data, CMLDefinitionRange* defrange, const void* input){
  params = params; // no warning
  CMLInternalFunctionFunctionStorage* thisdata;
  CMLDefinitionRange newrange;
  CMLInternalFunctionFunctionInput* indata = (CMLInternalFunctionFunctionInput*)(input);
  *data = cmlAllocate(sizeof(CMLInternalFunctionFunctionStorage));
  thisdata = (CMLInternalFunctionFunctionStorage*)(*data);
  thisdata->func1 = CMLduplicateFunction(indata->func1);
  thisdata->func2 = CMLduplicateFunction(indata->func2);
  newrange = CMLgetDefinitionRangeOf2Functions(indata->func1, indata->func2, CML_TRUE);
  *defrange = newrange;
}


CML_HIDDEN void CMLInternalDestructFunctionMulFunction(void* data){
  CMLInternalFunctionFunctionStorage* thisdata = (CMLInternalFunctionFunctionStorage*)data;
  cmlReleaseFunction(thisdata->func1);
  cmlReleaseFunction(thisdata->func2);
  free(data);
}


CML_HIDDEN float cmlInternalEvaluateFunctionMulFunction(float* params, const void* data, float x){
  params = params; // no warning
  CMLInternalFunctionFunctionStorage* thisdata = (CMLInternalFunctionFunctionStorage*)data;
  return cmlInternalEval(thisdata->func1, x) * cmlInternalEval(thisdata->func2, x);
}


CML_API CMLFunction* CMLcreateFunctionMulFunction(const CMLFunction* func1, const CMLFunction* func2){
  CMLInternalFunctionFunctionInput newdata = {func1, func2};
  return CMLcreateFunction(cmlInternalEvaluateFunctionMulFunction, CMLInternalConstructFunctionMulFunction, CMLInternalDestructFunctionMulFunction, 0, &newdata);
}








// //////////////////////////////////////////////
// Function div Function
// //////////////////////////////////////////////

// Prototypes:
CML_HIDDEN void CMLInternalConstructFunctionDivFunction(float* params, void** data, CMLDefinitionRange* defrange, const void* input);
CML_HIDDEN void CMLInternalDestructFunctionDivFunction(void* data);
CML_HIDDEN float cmlInternalEvaluateFunctionDivFunction(float* params, const void* data, float x);


CML_HIDDEN void CMLInternalConstructFunctionDivFunction(float* params, void** data, CMLDefinitionRange* defrange, const void* input){
  params = params; // no warning
  CMLInternalFunctionFunctionStorage* thisdata;
  CMLDefinitionRange newrange;
  CMLInternalFunctionFunctionInput* indata = (CMLInternalFunctionFunctionInput*)(input);
  *data = cmlAllocate(sizeof(CMLInternalFunctionFunctionStorage));
  thisdata = (CMLInternalFunctionFunctionStorage*)(*data);
  thisdata->func1 = CMLduplicateFunction(indata->func1);
  thisdata->func2 = CMLduplicateFunction(indata->func2);
  newrange = CMLgetDefinitionRangeOf2Functions(indata->func1, indata->func2, CML_TRUE);
  *defrange = newrange;
}


CML_HIDDEN void CMLInternalDestructFunctionDivFunction(void* data){
  CMLInternalFunctionFunctionStorage* thisdata = (CMLInternalFunctionFunctionStorage*)data;
  cmlReleaseFunction(thisdata->func1);
  cmlReleaseFunction(thisdata->func2);
  free(data);
}


CML_HIDDEN float cmlInternalEvaluateFunctionDivFunction(float* params, const void* data, float x){
  params = params; // no warning
  CMLInternalFunctionFunctionStorage* thisdata = (CMLInternalFunctionFunctionStorage*)data;
  return cmlInternalEval(thisdata->func1, x) / cmlInternalEval(thisdata->func2, x);
}


CML_API CMLFunction* CMLcreateFunctionDivFunction(const CMLFunction* func1, const CMLFunction* func2){
  CMLInternalFunctionFunctionInput newdata = {func1, func2};
  return CMLcreateFunction(cmlInternalEvaluateFunctionDivFunction, CMLInternalConstructFunctionDivFunction, CMLInternalDestructFunctionDivFunction, 0, &newdata);
}






// //////////////////////////////////////////////
// Function mul Scalar
// //////////////////////////////////////////////

// Prototypes:
CML_HIDDEN void CMLInternalConstructFunctionMulScalar(float* params, void** data, CMLDefinitionRange* defrange, const void* input);
CML_HIDDEN void CMLInternalDestructFunctionMulScalar(void* data);
CML_HIDDEN float cmlInternalEvaluateFunctionMulScalar(float* params, const void* data, float x);


CML_HIDDEN void CMLInternalConstructFunctionMulScalar(float* params, void** data, CMLDefinitionRange* defrange, const void* input){
  params = params; // no warning
  CMLInternalFunctionScalarStorage* thisdata;
  CMLInternalFunctionScalarInput* indata = (CMLInternalFunctionScalarInput*)(input);
  *data = cmlAllocate(sizeof(CMLInternalFunctionScalarStorage));
  thisdata = (CMLInternalFunctionScalarStorage*)(*data);
  thisdata->func = CMLduplicateFunction(indata->func);
  thisdata->scalar = indata->scalar;
  *defrange = indata->func->defrange;
}


CML_HIDDEN void CMLInternalDestructFunctionMulScalar(void* data){
  CMLInternalFunctionScalarStorage* thisdata = (CMLInternalFunctionScalarStorage*)data;
  cmlReleaseFunction(thisdata->func);
  free(data);
}


CML_HIDDEN float cmlInternalEvaluateFunctionMulScalar(float* params, const void* data, float x){
  params = params; // no warning
  CMLInternalFunctionScalarStorage* thisdata = (CMLInternalFunctionScalarStorage*)data;
  return cmlInternalEval(thisdata->func, x) * thisdata->scalar;
}


CML_API CMLFunction* CMLcreateFunctionMulScalar(const CMLFunction* func, float scalar){
  CMLInternalFunctionScalarInput newdata = {func, scalar};
  return CMLcreateFunction(cmlInternalEvaluateFunctionMulScalar, CMLInternalConstructFunctionMulScalar, CMLInternalDestructFunctionMulScalar, 0, &newdata);
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

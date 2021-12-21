
#include "../CML.h"
#include "CMLColorMachineState.h"



CML_DEF CMLFunction* cmlCreateFunction(
  CMLFunctionConstructor constructor,
  CMLFunctionDesctructor destructor,
  CMLFunctionEvaluator evaluator,
  size_t dataSize,
  const void* input)
{
  CMLFunction* newFunction = (CMLFunction*)cml_Malloc(sizeof(CMLFunction));
  newFunction->refCount = 1;
  
  newFunction->dataSize = dataSize;
  if(dataSize){
    newFunction->data = cml_Malloc(dataSize);
  }else{
    newFunction->data = CML_NULL;
  }
  
  newFunction->destructor = destructor;
  newFunction->evaluator = evaluator;
  
  newFunction->defRange.stepSize = 0.f;
  newFunction->defRange.minSampleCoord = CML_DEFAULT_INTEGRATION_MIN;
  newFunction->defRange.maxSampleCoord = CML_DEFAULT_INTEGRATION_MAX;
  newFunction->defRange.minNonTrivialCoord = -CML_INFINITY;
  newFunction->defRange.maxNonTrivialCoord = +CML_INFINITY;
  
  if(constructor){
    constructor(newFunction->data, &(newFunction->defRange), input);
  }

  return newFunction;
}



CML_DEF CMLFunction* cmlDuplicateFunction(const CMLFunction* func){
  size_t* mutableRefCount = (size_t*)(&(func->refCount));
  // Beware the parantheses!!!
  (*mutableRefCount)++;
  // Return a non-const reference to function.
  return (CMLFunction*)func;
}



CML_DEF void cmlReleaseFunction(CMLFunction* func){
  if(!func){return;}
  func->refCount--;
  if(!func->refCount){
    if(func->destructor){
      func->destructor(func->data);
    }
    if(func->dataSize){free(func->data);}
    free(func);
  }
}



CML_DEF float cmlEval(const CMLFunction* func, float x){
  return cml_Eval(func, x);
}



CML_DEF void cmlGetFunctionDefinitionRange(const CMLFunction* func, CMLDefinitionRange* defRange){
  *defRange = func->defRange;
}



CML_DEF float cmlGetFunctionMaxValue(const CMLFunction* func){
  float max = -CML_INFINITY;
  float stepSize = func->defRange.stepSize;
  if(stepSize == 0){stepSize = CML_DEFAULT_INTEGRATION_STEPSIZE;}
  size_t sampleCount = cmlGetSampleCount(func->defRange.minSampleCoord, func->defRange.maxSampleCoord, stepSize);
  for(size_t x = 0; x < sampleCount; x ++){
    float coord = func->defRange.minSampleCoord + x * stepSize;
    float value = cml_Eval(func, coord);
    if(value > max){max = value;}
  }
  return max;
}



// Determines a useful definition range when two functions are combined either
// by addition or multiplication. If multiplicative, values which are trivial
// in one function will result in trivial results combined. This function finds
// the smallest useful definitionRange based on that.
CML_HIDEF CMLDefinitionRange cml_GetDefinitionRangeOfTwoFunctions(const CMLFunction* func1, const CMLFunction* func2, CMLBool multiplicative){
  CMLDefinitionRange newRange;
  
  // Set the desired stepSize which is the smaller of the two functions
  // in case they are both discrete. If only one is descrete, that stepsize
  // is used. If both are continuous, the stepsize stays continuous.
  if(func1->defRange.stepSize == 0.f){newRange.stepSize = func2->defRange.stepSize;}
  else if(func2->defRange.stepSize == 0.f){newRange.stepSize = func1->defRange.stepSize;}
  else if(func1->defRange.stepSize < func2->defRange.stepSize){newRange.stepSize = func1->defRange.stepSize;}
  else{newRange.stepSize = func2->defRange.stepSize;}

  // Set the trivial boundaries
  if(multiplicative){
    // one trivial value will result in a trivial value
    newRange.minNonTrivialCoord = CML_MAX(func1->defRange.minNonTrivialCoord, func2->defRange.minNonTrivialCoord);
    newRange.maxNonTrivialCoord = CML_MIN(func1->defRange.maxNonTrivialCoord, func2->defRange.maxNonTrivialCoord);
  }else{
    // one trivial value may NOT result in a trivial value
    newRange.minNonTrivialCoord = CML_MIN(func1->defRange.minNonTrivialCoord, func2->defRange.minNonTrivialCoord);
    newRange.maxNonTrivialCoord = CML_MAX(func1->defRange.maxNonTrivialCoord, func2->defRange.maxNonTrivialCoord);
  }

  // Set the sampling coordinates by making sure, they are in the
  // non-trivial range and are aligned with the original data.
  float minSampleCoord1 = func1->defRange.minSampleCoord;
  float maxsamplecoord1 = func1->defRange.maxSampleCoord;
  float minSampleCoord2 = func2->defRange.minSampleCoord;
  float maxsamplecoord2 = func2->defRange.maxSampleCoord;
  if(minSampleCoord1 < newRange.minNonTrivialCoord){
    minSampleCoord1 += func1->defRange.stepSize * ceilf((newRange.minNonTrivialCoord - func1->defRange.minSampleCoord) / func1->defRange.stepSize);
  }
  if(maxsamplecoord1 > newRange.maxNonTrivialCoord){
    maxsamplecoord1 -= func1->defRange.stepSize * ceilf((func1->defRange.maxSampleCoord - newRange.maxNonTrivialCoord) / func1->defRange.stepSize);
  }
  if(minSampleCoord2 < newRange.minNonTrivialCoord){
    minSampleCoord2 += func2->defRange.stepSize * ceilf((newRange.minNonTrivialCoord - func2->defRange.minSampleCoord) / func2->defRange.stepSize);
  }
  if(maxsamplecoord2 > newRange.maxNonTrivialCoord){
    maxsamplecoord2 -= func2->defRange.stepSize * ceilf((func2->defRange.maxSampleCoord - newRange.maxNonTrivialCoord) / func2->defRange.stepSize);
  }
  newRange.minSampleCoord = CML_MIN(minSampleCoord1, minSampleCoord2);
  newRange.maxSampleCoord = CML_MAX(maxsamplecoord1, maxsamplecoord2);

  return newRange;
}



CML_DEF float cmlFilterFunction(const CMLFunction* func, const CMLFunction* filter){
  float sum = 0.f;

  CMLDefinitionRange filterRange = cml_GetDefinitionRangeOfTwoFunctions(func, filter, CML_TRUE);
  if(filterRange.minSampleCoord > filterRange.maxSampleCoord){return 0.f;}
  
  #if CML_DEBUG
    if(filterRange.stepSize < 0.f){cmlError("Negative stepSize in Function.");}
  #endif
  
  // If the stepSize is 0, the function will be filtered as a continuous
  // function with the default integration stepSize.
  if(filterRange.stepSize == 0.f){filterRange.stepSize = CML_DEFAULT_INTEGRATION_STEPSIZE;}
  size_t sampleCount = cmlGetSampleCount(filterRange.minSampleCoord, filterRange.maxSampleCoord, filterRange.stepSize);
  // If there is only one value to compute, the stepSize is manually set to 1
  // to not normalize the final result with a wrong value.

  CMLIntegrationMethod type = CML_DEFAULT_INTEGRATION_TYPE;
  
  switch(type){
  case CML_INTEGRATION_SIMPLE: {
    size_t iStep;
    // Simple sum computation by adding one by one
    for(iStep = 0; iStep < sampleCount; iStep++){
      float x = filterRange.minSampleCoord + (filterRange.stepSize * iStep);
      sum += cml_Eval(func, x) * cml_Eval(filter, x);
    }
    break; }
    
  case CML_INTEGRATION_BINARY_PAIRS: {
    // This is a highly efficient and accurate integration method developed by
    // Tobias Stamm. It even outperforms a simple for loop by using the memory
    // cache and is much more accurate for well-behaving sampling functions as
    // it combines neighboring values and hence loses much fewer floating point
    // accuracy when summing these up.
    
    float tmpSums[8 * sizeof(size_t)];  // 8 denotes bits per Byte
    memset(tmpSums, 0, sizeof(float) * (8 * sizeof(size_t))); // nullify.

    if(sampleCount > 1){
      for(size_t iStep = 0; iStep < sampleCount; iStep += 2){

        // Compute two neighboring values.
        float x1 = filterRange.minSampleCoord + (filterRange.stepSize * iStep);
        float value1 = cml_Eval(func, x1) * cml_Eval(filter, x1);
        float x2 = filterRange.minSampleCoord + (filterRange.stepSize * (iStep + 1));
        float value2 = cml_Eval(func, x2) * cml_Eval(filter, x2);

        // Add these values together with the temp sums up to the position where
        // the current iStep has its first binary 0.
        float walkingSum = value1 + value2;
        char p = 1; // the current tmpSum as well as the current bit of iStep
        size_t step = 2; // = 2^p
        while(iStep & step){
          walkingSum += tmpSums[p];
          p++;
          step <<= 1;
        }
        // Store the current sum at the position of the subsequent binary 1
        tmpSums[p] = walkingSum;
      }
    }
    
    // If the count is odd, store the remaining value at position 0.
    if(sampleCount & 1){
      tmpSums[0] = cml_Eval(func, filterRange.maxSampleCoord) * cml_Eval(filter, filterRange.maxSampleCoord);
    }
    
    // Finally, go though all temp sums and add those to the final sum where
    // sampleCount has a binary 1
    for(size_t i = 0; i < 8 * sizeof(size_t); i++){
      if(sampleCount & ((size_t)1 << i)){
        sum += tmpSums[i];
      }
    }
    break; }

  default:
    #if CML_DEBUG
      cmlError("Invalid Integration type.");
    #endif
    return 0.f;
    break;
  }

  // Normalizing the result with the delta.
  return (sampleCount == 1) ? sum : sum * filterRange.stepSize;
}



// //////////////////////////////////////////////
// Array Function struct
// //////////////////////////////////////////////

typedef struct CMLArrayFunctionData CMLArrayFunctionData;
struct CML_HDEF CMLArrayFunctionData{
  CMLArrayFunctionInput input;
  
  float minCoord;
  float maxCoord;
  float inverseInterval;
  
  // Note for the future: Even if it looks like this could be faster with a
  // switch statement, it is not. Believe me. I've checked it several times.
  float (*extrapolateDown)(const CMLArrayFunctionData* arrayFunctionData, float x);
  float (*extrapolateUp)(const CMLArrayFunctionData* arrayFunctionData, float x);
  float (*interpolate)(const CMLArrayFunctionData* arrayFunctionData, float index);
};



// ////////////////////////////
// Interpolation methods:
// ////////////////////////////

// Returns the value stored in the array only if the given index is an integer.
CML_HDEF float cml_ArrayFunctionInterpolateNone(const CMLArrayFunctionData* arrayFunctionData, float index){
  size_t i = (size_t)index;
  if((float)(i) == index){
    return arrayFunctionData->input.buffer[i];
  }else{
    return 0.f;
  }
}

// Returns the value stored at floor(index).
CML_HDEF float cml_ArrayFunctionInterpolateFloor(const CMLArrayFunctionData* arrayFunctionData, float index){
  return arrayFunctionData->input.buffer[(size_t)index];
}

// Returns the value stored at round(index).
CML_HDEF float cml_ArrayFunctionInterpolateBox(const CMLArrayFunctionData* arrayFunctionData, float index){
  return arrayFunctionData->input.buffer[(size_t)((float)index + .5f)];
}

// Returns the value stored at floor(index). The difference to the Floor method
// is that the definition range is not extended.
CML_HDEF float cml_ArrayFunctionInterpolateInterval(const CMLArrayFunctionData* arrayFunctionData, float index){
  return arrayFunctionData->input.buffer[(size_t)index];
}

// Returns the value linearily interpolated.
CML_HDEF float cml_ArrayFunctionInterpolateLinear(const CMLArrayFunctionData* arrayFunctionData, float index){
  size_t i1 = (size_t)index;
  size_t i2 = i1 + 1;
  float alpha = index - (float)(i1);
  float floorValue = arrayFunctionData->input.buffer[i1];
  return floorValue + (arrayFunctionData->input.buffer[i2] - floorValue) * alpha;
}



// ////////////////////////////
// Lower Extrapolation methods:
// ////////////////////////////

// Just returns zero.
CML_HDEF float cml_ArrayFunctionExtrapolateDownClampZero(const CMLArrayFunctionData* arrayFunctionData, float x){
  CML_UNUSED(arrayFunctionData);
  CML_UNUSED(x);
  return 0.f;
}

// Linearly interpolates to zero within one index step, then returns zero.
CML_HDEF float cml_ArrayFunctionExtrapolateDownLinearZero(const CMLArrayFunctionData* arrayFunctionData, float x){
  x = (arrayFunctionData->minCoord - x) * arrayFunctionData->inverseInterval;
  if(x > 1.f){
    return 0.f;
  }else{
    return arrayFunctionData->input.buffer[0] * (1.f - x);
  }
}

// Repeats the last value.
CML_HDEF float cml_ArrayFunctionExtrapolateDownClampValue(const CMLArrayFunctionData* arrayFunctionData, float x){
  CML_UNUSED(x);
  return arrayFunctionData->input.buffer[0];
}

// Extrapolates using the gradient between the last two values.
CML_HDEF float cml_ArrayFunctionExtrapolateDownGradient(const CMLArrayFunctionData* arrayFunctionData, float x){
  float index = (x - arrayFunctionData->minCoord) * arrayFunctionData->inverseInterval;
  return arrayFunctionData->input.buffer[0] + (arrayFunctionData->input.buffer[1] - arrayFunctionData->input.buffer[0]) * index;
}



// ////////////////////////////
// Upper Extrapolation methods:
// ////////////////////////////

// Just returns zero.
CML_HDEF float cml_ArrayFunctionExtrapolateUpClampZero(const CMLArrayFunctionData* arrayFunctionData, float x){
  CML_UNUSED(x);
  arrayFunctionData = arrayFunctionData;
  return 0.f;
}

// Linearly interpolates to zero within one index step, then returns zero.
CML_HDEF float cml_ArrayFunctionExtrapolateUpLinearZero(const CMLArrayFunctionData* arrayFunctionData, float x){
  x = (x - arrayFunctionData->maxCoord) * arrayFunctionData->inverseInterval;
  if(x > 1.f){
    return 0.f;
  }else{
    return arrayFunctionData->input.buffer[arrayFunctionData->input.settings.entryCount - 1] * (1.f - x);
  }
}

// Repeats the last value.
CML_HDEF float cml_ArrayFunctionExtrapolateUpClampValue(const CMLArrayFunctionData* arrayFunctionData, float x){
  CML_UNUSED(x);
  return arrayFunctionData->input.buffer[arrayFunctionData->input.settings.entryCount - 1];
}

// Extrapolates using the gradient between the last two values.
CML_HDEF float cml_ArrayFunctionExtrapolateUpGradient(const CMLArrayFunctionData* arrayFunctionData, float x){
  float index = (x - arrayFunctionData->maxCoord) * arrayFunctionData->inverseInterval;
  return arrayFunctionData->input.buffer[arrayFunctionData->input.settings.entryCount - 1] + (arrayFunctionData->input.buffer[arrayFunctionData->input.settings.entryCount - 2] - arrayFunctionData->input.buffer[arrayFunctionData->input.settings.entryCount - 1]) * index;
}



// //////////////////////////////////////////////
// Array Function
// //////////////////////////////////////////////

CML_HDEF void cml_ConstructArrayFunctionInput(void* data, CMLDefinitionRange* defRange, const void* input){
  CMLArrayFunctionData* arrayFunctionData = (CMLArrayFunctionData*)data;
  CMLArrayFunctionInput* inputData = (CMLArrayFunctionInput*)input;

  arrayFunctionData->input = *inputData;

  #if CML_DEBUG
    if(arrayFunctionData->input.settings.entryCount <= 1){
      cmlError("Array Function with 1 or 0 Entries may not work properly yet.");
    }
  #endif

  defRange->minSampleCoord = arrayFunctionData->input.settings.minimalCoord;
  defRange->maxSampleCoord = arrayFunctionData->input.settings.maximalCoord;

  // Set the interpolation method.
  switch(arrayFunctionData->input.settings.interpolationMethod){
  case CML_INTERPOLATION_NONE:
    arrayFunctionData->minCoord = arrayFunctionData->input.settings.minimalCoord;
    arrayFunctionData->maxCoord = arrayFunctionData->input.settings.maximalCoord;
    arrayFunctionData->interpolate = &cml_ArrayFunctionInterpolateNone;
    arrayFunctionData->inverseInterval = (float)(arrayFunctionData->input.settings.entryCount - 1) / (arrayFunctionData->maxCoord - arrayFunctionData->minCoord);
    break;
  case CML_INTERPOLATION_FLOOR:
    arrayFunctionData->minCoord = arrayFunctionData->input.settings.minimalCoord;
    arrayFunctionData->maxCoord = arrayFunctionData->input.settings.maximalCoord + ((arrayFunctionData->input.settings.maximalCoord - arrayFunctionData->input.settings.minimalCoord) / (float)(arrayFunctionData->input.settings.entryCount - 1));
    arrayFunctionData->interpolate = &cml_ArrayFunctionInterpolateFloor;
    arrayFunctionData->inverseInterval = (float)(arrayFunctionData->input.settings.entryCount - 1) / (arrayFunctionData->maxCoord - arrayFunctionData->minCoord);
    break;
  case CML_INTERPOLATION_BOX:
    arrayFunctionData->minCoord = arrayFunctionData->input.settings.minimalCoord - (.5f * (arrayFunctionData->input.settings.maximalCoord - arrayFunctionData->input.settings.minimalCoord) / (float)(arrayFunctionData->input.settings.entryCount - 1));
    arrayFunctionData->maxCoord = arrayFunctionData->input.settings.maximalCoord + (.5f * (arrayFunctionData->input.settings.maximalCoord - arrayFunctionData->input.settings.minimalCoord) / (float)(arrayFunctionData->input.settings.entryCount - 1));
    arrayFunctionData->interpolate = &cml_ArrayFunctionInterpolateBox;
    arrayFunctionData->inverseInterval = (float)(arrayFunctionData->input.settings.entryCount - 1) / (arrayFunctionData->maxCoord - arrayFunctionData->minCoord);
    break;
  case CML_INTERPOLATION_INTERVAL:
    arrayFunctionData->minCoord = arrayFunctionData->input.settings.minimalCoord;
    arrayFunctionData->maxCoord = arrayFunctionData->input.settings.maximalCoord;
    arrayFunctionData->interpolate = &cml_ArrayFunctionInterpolateInterval;
    arrayFunctionData->inverseInterval = (float)(arrayFunctionData->input.settings.entryCount) / (arrayFunctionData->maxCoord - arrayFunctionData->minCoord);
    break;
  case CML_INTERPOLATION_LINEAR:
    arrayFunctionData->minCoord = arrayFunctionData->input.settings.minimalCoord;
    arrayFunctionData->maxCoord = arrayFunctionData->input.settings.maximalCoord;
    arrayFunctionData->interpolate = &cml_ArrayFunctionInterpolateLinear;
    arrayFunctionData->inverseInterval = (float)(arrayFunctionData->input.settings.entryCount - 1) / (arrayFunctionData->maxCoord - arrayFunctionData->minCoord);
    break;
  default:
    #if CML_DEBUG
      cmlError("Undefined interpolation method.");
    #endif
    arrayFunctionData->interpolate = CML_NULL;
    break;
  }

  defRange->stepSize = cmlInverse(arrayFunctionData->inverseInterval);

  // set the lower extrapolation method.
  switch(arrayFunctionData->input.settings.lowerExtrapolationMethod){
  case CML_EXTRAPOLATION_CLAMP_ZERO:
    arrayFunctionData->extrapolateDown = &cml_ArrayFunctionExtrapolateDownClampZero;
    defRange->minNonTrivialCoord = arrayFunctionData->input.settings.minimalCoord;
    break;
  case CML_EXTRAPOLATION_LINEAR_ZERO:
    arrayFunctionData->extrapolateDown = &cml_ArrayFunctionExtrapolateDownLinearZero;
    defRange->minNonTrivialCoord = arrayFunctionData->input.settings.minimalCoord - cmlGetStepSize(arrayFunctionData->input.settings.minimalCoord, arrayFunctionData->input.settings.maximalCoord, arrayFunctionData->input.settings.entryCount);
    break;
  case CML_EXTRAPOLATION_CLAMP_VALUE:
    arrayFunctionData->extrapolateDown = &cml_ArrayFunctionExtrapolateDownClampValue;
    defRange->minNonTrivialCoord = -CML_INFINITY;
    break;
  case CML_EXTRAPOLATION_GRADIENT:
    arrayFunctionData->extrapolateDown = &cml_ArrayFunctionExtrapolateDownGradient;
    defRange->minNonTrivialCoord = -CML_INFINITY;
    break;
  default:
    #if CML_DEBUG
      cmlError("Undefined down-extrapolation method.");
    #endif
    arrayFunctionData->extrapolateDown = CML_NULL;
    break;
  }

  // set the upper extrapolation method.
  switch(arrayFunctionData->input.settings.upperExtrapolationMethod){
  case CML_EXTRAPOLATION_CLAMP_ZERO:
    arrayFunctionData->extrapolateUp   = &cml_ArrayFunctionExtrapolateUpClampZero;
    defRange->maxNonTrivialCoord = arrayFunctionData->input.settings.maximalCoord;
    break;
  case CML_EXTRAPOLATION_LINEAR_ZERO:
    arrayFunctionData->extrapolateUp   = &cml_ArrayFunctionExtrapolateUpLinearZero;
    defRange->maxNonTrivialCoord = arrayFunctionData->input.settings.maximalCoord + cmlGetStepSize(arrayFunctionData->input.settings.minimalCoord, arrayFunctionData->input.settings.maximalCoord, arrayFunctionData->input.settings.entryCount);
    break;
  case CML_EXTRAPOLATION_CLAMP_VALUE:
    arrayFunctionData->extrapolateUp   = &cml_ArrayFunctionExtrapolateUpClampValue;
    defRange->maxNonTrivialCoord = CML_INFINITY;
    break;
  case CML_EXTRAPOLATION_GRADIENT:
    arrayFunctionData->extrapolateUp   = &cml_ArrayFunctionExtrapolateUpGradient;
    defRange->maxNonTrivialCoord = CML_INFINITY;
    break;
  default:
    #if CML_DEBUG
      cmlError("Undefined up-extrapolation method.");
    #endif
    arrayFunctionData->extrapolateUp = CML_NULL;
    break;
  }
}

CML_HDEF const void* cml_GetArrayFunctionInput(void* data){
  CMLArrayFunctionData* arrayFunctionData = (CMLArrayFunctionData*)data;
  return &(arrayFunctionData->input);
}

CML_HDEF void cml_DestructArrayFunction(void* data){
  CMLArrayFunctionData* arrayFunctionData = (CMLArrayFunctionData*)data;
  if(arrayFunctionData->input.ownBuffer){
    free((void*)arrayFunctionData->input.buffer);
  }
}

CML_HDEF float cml_EvaluateArrayFunction(const void* data, float x){
  CMLArrayFunctionData* arrayFunctionData = (CMLArrayFunctionData*)data;
  if(x == arrayFunctionData->minCoord){
    // x is exactly the minimum coordinate.
    return arrayFunctionData->input.buffer[0];
  }else if(x == arrayFunctionData->maxCoord){
    // x is exactly the maximum coordinate.
    return arrayFunctionData->input.buffer[arrayFunctionData->input.settings.entryCount - 1];
  }else if(x > arrayFunctionData->minCoord && x < arrayFunctionData->maxCoord){
    // x is in the interpolation region.
    float index = (x - arrayFunctionData->minCoord) * arrayFunctionData->inverseInterval;
    return arrayFunctionData->interpolate(arrayFunctionData, index);
  }else if(x < arrayFunctionData->minCoord){
    // x is in the extrapolation region downwards.
    return arrayFunctionData->extrapolateDown(arrayFunctionData, x);
  }else{
    // x is in the extrapolation region upwards.
    return arrayFunctionData->extrapolateUp(arrayFunctionData, x);
  }
}

CML_DEF CMLFunction* cmlCreateArrayFunction(CMLArrayFunctionInput input){
 return cmlCreateFunction(
    cml_ConstructArrayFunctionInput,
    cml_DestructArrayFunction,
    cml_EvaluateArrayFunction,
    sizeof(CMLArrayFunctionData),
    &input);
}

CML_DEF CMLFunction* cmlSampleArrayFunction(const CMLFunction* func, CMLArrayFunctionSettings settings){
  float* buffer = (float*)cml_Malloc(sizeof(float) * settings.entryCount);
  for(size_t i = 0; i < settings.entryCount; i++){
    float coord = settings.minimalCoord + ((float)i / (float)(settings.entryCount-1)) * (settings.maximalCoord - settings.minimalCoord);
    buffer[i] = cml_Eval(func, coord);
  }
  
  CMLArrayFunctionInput input = {
    buffer,
    CML_TRUE,
    settings};
  return cmlCreateArrayFunction(input);
}



// //////////////////////////////////////////////
// Blackbody
// //////////////////////////////////////////////

typedef struct CMLBlackBodyData CMLBlackBodyData;
struct CMLBlackBodyData{
  float temp;
  float c;
};

CML_HDEF void cml_ConstructBlackBodyInput(void* data, CMLDefinitionRange* defRange, const void* input){
  CMLBlackBodyData* blackBodyData = (CMLBlackBodyData*)data;
  blackBodyData->temp = *((const float*)input);
  
  if(blackBodyData->temp <= 0){
    #if CML_DEBUG
      cmlError("Temperature must be greater than 0 Kelvin.");
    #endif
    blackBodyData->c = 0.f;
  }else if(blackBodyData->temp == CML_INFINITY){
    blackBodyData->c = 0.f;
  }else{
    // note that CML_SECOND_RAD = (CML_PLANCK * CMLIGHT_SPEED_VAC) / CML_BOLTZMANN;
    blackBodyData->c = CML_SECOND_RAD / blackBodyData->temp;
  }
  
  // Adjust the definition range.
  defRange->minNonTrivialCoord = CML_SINGULARITY;
}

CML_HDEF const void* cml_GetBlackBodyInput(void* data){
  CMLBlackBodyData* blackBodyData = (CMLBlackBodyData*)data;
  return &(blackBodyData->temp);
}

CML_HDEF float cml_EvaluateBlackBody(const void* data, float x){
  CMLBlackBodyData* blackBodyData = (CMLBlackBodyData*)data;

  if(x <= 0){
    #if CML_DEBUG
      cmlError("Blackbody radiator is only defined for input values greater than 0.");
    #endif
    return 0.f;
  }
  
  // x is expected in [nanometer], therefore the multiplication with 1e-9f.
  float nanoLambda = x * 1e-9f;
  float retValue = CML_PI2 * CML_PLANCK * CML_LIGHT_SPEED_VAC * CML_LIGHT_SPEED_VAC / powf(nanoLambda, 5.f);
  if(blackBodyData->c != 0.f){
    retValue /= expf(blackBodyData->c / nanoLambda) - 1.f;
  }
  return retValue;
}

CML_DEF CMLFunction* cmlCreateBlackBody(float temperature){
  return cmlCreateFunction(
    cml_ConstructBlackBodyInput,
    CML_NULL,
    cml_EvaluateBlackBody,
    sizeof(CMLBlackBodyData),
    &temperature);
}



// //////////////////////////////////////////////
// CIE A illuminant
// //////////////////////////////////////////////

CML_HDEF void cml_ConstructCIEAIlluminantInput(void* data, CMLDefinitionRange* defRange, const void* input){
  CML_UNUSED(data);
  CML_UNUSED(input);
  // Adjust the definition range.
  defRange->minNonTrivialCoord = CML_SINGULARITY;
}

CML_HDEF float cml_EvaluateCIEAIlluminant(const void* data, float x){
  CML_UNUSED(data);

  if(x <= 0){
    #if CML_DEBUG
      cmlError("CIE A illuminant is only defined for input values greater than 0.");
    #endif
    return 0.f;
  }

  // x is expected in [nanometer], therefore the multiplication with 1e-9f.
  float nanoLambda = x * 1e-9f;
  // First constant is 100. * pow(560e-9., 5.);
  // Second constant is exp(1.435e-2 / (2848. * 560e-9)) - 1.;
  // third constant is c2 = (1.435e-2) / (2848.);
  // Note: 1.435e-2 is approximately CML_PLANCK * CML_LIGHT_SPEED_VAC / CML_BOLTZMANN
  // 1.435e7 is the standard used in the CIE definition.
  return (.5507317760e-31f / powf(nanoLambda, 5.f)) * (8082.19209692894427103001499060f / (expf(.5038623596e-5f / nanoLambda) - 1.f));
}

CML_DEF CMLFunction* cmlCreateCIEAIlluminant(){
  return cmlCreateFunction(
    cml_ConstructCIEAIlluminantInput,
    CML_NULL,
    cml_EvaluateCIEAIlluminant,
    0,
    CML_NULL);
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
CML_HDEF const float dilluminantS0[CML_D_ILLUMINANT_ENTRYCOUNT] =
  { 0.04f,   6.00f,  29.60f,  55.30f,  57.30f,  61.80f,  61.50f,  68.80f,  63.40f,  65.80f,
   94.80f, 104.80f, 105.90f,  96.80f, 113.90f, 125.60f, 125.50f, 121.30f, 121.30f, 113.50f,
  113.10f, 110.80f, 106.50f, 108.80f, 105.30f, 104.40f, 100.00f,  96.00f,  95.10f,  89.10f,
   90.50f,  90.30f,  88.40f,  84.00f,  85.10f,  81.90f,  82.60f,  84.90f,  81.30f,  71.90f,
   74.30f,  76.40f,  63.30f,  71.70f,  77.00f,  65.20f,  47.70f,  68.60f,  65.00f,  66.00f,
   61.00f,  53.30f,  58.90f,  61.90f};
CML_HDEF const float dilluminantS1[CML_D_ILLUMINANT_ENTRYCOUNT] =
  { 0.02f,   4.50f,  22.40f,  42.00f,  40.60f,  41.60f,  38.00f,  42.40f,  38.50f,  35.00f,
   43.40f,  46.30f,  43.90f,  37.10f,  36.70f,  35.90f,  32.60f,  27.90f,  24.30f,  20.10f,
   16.20f,  13.20f,   8.60f,   6.10f,   4.20f,   1.90f,   0.00f,  -1.60f,  -3.50f,  -3.50f,
   -5.80f,  -7.20f,  -8.60f,  -9.50f, -10.90f, -10.70f, -12.00f, -14.00f, -13.60f, -12.00f,
  -13.30f, -12.90f, -10.60f, -11.60f, -12.20f, -10.20f,  -7.80f, -11.20f, -10.40f, -10.60f,
   -9.70f,  -8.30f,  -9.30f,  -9.80f};
CML_HDEF const float dilluminantS2[CML_D_ILLUMINANT_ENTRYCOUNT] =
  {0.00f,  2.00f,  4.00f,  8.50f,  7.80f,  6.70f,  5.30f,  6.10f,  3.00f,  1.20f,
  -1.10f, -0.50f, -0.70f, -1.20f, -2.60f, -2.90f, -2.80f, -2.60f, -2.60f, -1.80f,
  -1.50f, -1.30f, -1.20f, -1.00f, -0.50f, -0.30f,  0.00f,  0.20f,  0.50f,  2.10f,
   3.20f,  4.10f,  4.70f,  5.10f,  6.70f,  7.30f,  8.60f,  9.80f, 10.20f,  8.30f,
   9.60f,  8.50f,  7.00f,  7.60f,  8.00f,  6.70f,  5.20f,  7.40f,  6.80f,  7.00f,
   6.40f,  5.50f,  6.10f,  6.50f};

CML_HIDEF void cml_ComputeDIlluminantWhitePoint(float* whitePoint, float temp){
  if(temp < 4000.f){temp = 4000.f;}
  if(temp > 25000.f){temp = 25000.f;}
  
  if(temp <= 7000.f){
    whitePoint[0] = ((-4.607e9f / temp + 2.9678e6f) / temp + 0.09911e3f) / temp + 0.244063f;
  }else{
    whitePoint[0] = ((-2.0064e9f / temp + 1.9018e6f) / temp + 0.24748e3f) / temp + 0.23704f;
  }
  whitePoint[1] = -3.f * whitePoint[0] * whitePoint[0] + 2.87f * whitePoint[0] - 0.275f;
}

CML_DEF CMLFunction* cmlCreateCIEDIlluminant(float temperature){
  #if CML_DEBUG
    if(temperature <= 0){cmlError("Temperature must be greater than 0 Kelvin.");}
  #endif
  
  // Note that the array will be deleted by the CMLArray.
  float* array = (float*)cml_Malloc(CML_D_ILLUMINANT_ENTRYCOUNT * sizeof(float));

  float whitePoint[2];
  cml_ComputeDIlluminantWhitePoint(whitePoint, temperature);
  float Minv = cmlInverse(0.0241f +  0.2562f * whitePoint[0] -  0.7341f * whitePoint[1]);
  float M1 = (-1.3515f -  1.7703f * whitePoint[0] +  5.9114f * whitePoint[1]) * Minv;
  float M2 = ( 0.03f   - 31.4424f * whitePoint[0] + 30.0717f * whitePoint[1]) * Minv;
  for(CMLuint32 l = 0; l < CML_D_ILLUMINANT_ENTRYCOUNT; ++l){
    array[l] = dilluminantS0[l] + M1 * dilluminantS1[l] + M2 * dilluminantS2[l];
  }
  
  // Multiple sources suggest that the values are considered to be linearly
  // interpolated.
  CMLArrayFunctionInput input = {
    array,
    CML_TRUE,
    { CML_D_ILLUMINANT_ENTRYCOUNT,
      CML_D_ILLUMINANT_MIN,
      CML_D_ILLUMINANT_MAX,
      CML_INTERPOLATION_LINEAR,
      CML_EXTRAPOLATION_LINEAR_ZERO,
      CML_EXTRAPOLATION_LINEAR_ZERO}};
  return cmlCreateArrayFunction(input);
}



// //////////////////////////////////////////////
// Linear Response
// //////////////////////////////////////////////

CML_HDEF float cml_EvaluateLinearResponse(const void* data, float x){
  CML_UNUSED(data);
  return x;
}

CML_DEF CMLFunction* cmlCreateLinearResponse(){
  return cmlCreateFunction(
    CML_NULL,
    CML_NULL,
    cml_EvaluateLinearResponse,
    0,
    CML_NULL);
}



// //////////////////////////////////////////////
// Gamma Response
// //////////////////////////////////////////////

typedef struct GammaStruct{
  float input;
  float invGamma;
} GammaStruct;

CML_HDEF void cml_ConstructGammaResponseInput(void* data, CMLDefinitionRange* defRange, const void* input){
  CML_UNUSED(defRange);
  GammaStruct* gammaStruct = (GammaStruct*)data;
  gammaStruct->input = *((const float*)input);
  gammaStruct->invGamma = cmlInverse(gammaStruct->input);
}

CML_HDEF const void* cml_GetGammaResponseInput(void* data){
  return data;
}

CML_HDEF float cml_EvaluateGammaResponse(const void* data, float x){
  float invGamma = ((GammaStruct*)data)->invGamma;
  if(x < 0.f){
    return -powf(-x, invGamma);
  }else{
    return powf(x, invGamma);
  }
}

CML_DEF CMLFunction* cmlCreateGammaResponse(float gamma){
  return cmlCreateFunction(
    cml_ConstructGammaResponseInput,
    CML_NULL,
    cml_EvaluateGammaResponse,
    sizeof(GammaStruct),
    &gamma);
}



// //////////////////////////////////////////////
// Inverse Gamma Response
// //////////////////////////////////////////////

CML_HDEF void cml_ConstructInverseGammaResponseInput(void* data, CMLDefinitionRange* defRange, const void* input){
  CML_UNUSED(defRange);
  *((float*)data) = *((const float*)input);
}

CML_HDEF const void* cml_GetInverseGammaResponseInput(void* data){
  return data;
}

CML_HDEF float cml_EvaluateInverseGammaResponse(const void* data, float x){
  float* gamma = (float*)data;
  if(x < 0.f){
    return -powf(-x, *gamma);
  }else{
    return powf(x, *gamma);
  }
}

CML_DEF CMLFunction* cmlCreateInverseGammaResponse(float gamma){
  return cmlCreateFunction(
    cml_ConstructInverseGammaResponseInput,
    CML_NULL,
    cml_EvaluateInverseGammaResponse,
    sizeof(float),
    &gamma);
}



// //////////////////////////////////////////////
// Linear Gamma Response
// //////////////////////////////////////////////

typedef struct GammaLinearStruct{
  GammaLinearInputParameters input;
  float invGamma;
  float curveScale;
} GammaLinearStruct;

CML_HDEF void cml_ConstructGammaLinearResponseInput(void* data, CMLDefinitionRange* defRange, const void* input){
  CML_UNUSED(defRange);
  GammaLinearInputParameters* inputParams = (GammaLinearInputParameters*)input;
  GammaLinearStruct* gammaLinear = (GammaLinearStruct*)data;
  gammaLinear->input = *inputParams;
  gammaLinear->invGamma = cmlInverse(inputParams->gamma);
  gammaLinear->curveScale = inputParams->offset + 1.f;
}

CML_HDEF const void* cml_GetGammaLinearResponseInput(void* data){
  GammaLinearStruct* gammaLinear = (GammaLinearStruct*)data;
  return &gammaLinear->input;
}

CML_HDEF float cml_EvaluateGammaLinearResponse(const void* data, float x){
    GammaLinearStruct* gammaLinear = (GammaLinearStruct*)data;
  if(x > gammaLinear->input.split){
    return gammaLinear->curveScale * powf(x, gammaLinear->invGamma) - gammaLinear->input.offset;
  }else{
    return gammaLinear->input.linScale * x;
  }
}

CML_DEF CMLFunction* cmlCreateGammaLinearResponse(float gamma, float offset, float linScale, float split){
  GammaLinearInputParameters tmpStruct = {gamma, offset, linScale, split};
  return cmlCreateFunction(
    cml_ConstructGammaLinearResponseInput,
    CML_NULL,
    cml_EvaluateGammaLinearResponse,
    sizeof(GammaLinearStruct),
    &tmpStruct);
}



// //////////////////////////////////////////////
// Inverse Linear Gamma Response
// //////////////////////////////////////////////

typedef struct InverseGammaLinearStruct{
  GammaLinearInputParameters input;
  float invCurveScale;
  float invLinScale;
  float splitPoint;
} InverseGammaLinearStruct;

CML_HDEF void cml_ConstructInverseGammaLinearResponseInput(void* data, CMLDefinitionRange* defRange, const void* input){
  CML_UNUSED(defRange);
  GammaLinearInputParameters* inputParams = (GammaLinearInputParameters*)input;
  InverseGammaLinearStruct* invGammaLinear = (InverseGammaLinearStruct*)data;
  invGammaLinear->input = *inputParams;
  invGammaLinear->invCurveScale = cmlInverse(inputParams->offset + 1.f);
  invGammaLinear->invLinScale = cmlInverse(inputParams->linScale);
  invGammaLinear->splitPoint = inputParams->split * inputParams->linScale;
}

CML_HDEF const void* cml_GetInverseGammaLinearResponseInput(void* data){
  InverseGammaLinearStruct* invGammaLinear = (InverseGammaLinearStruct*)data;
  return &invGammaLinear->input;
}

CML_HDEF float cml_EvaluateInverseGammaLinearResponse(const void* data, float x){
  InverseGammaLinearStruct* invGammaLinear = (InverseGammaLinearStruct*)data;
  if(x > invGammaLinear->splitPoint){
    return powf((x + invGammaLinear->input.offset) * invGammaLinear->invCurveScale, invGammaLinear->input.gamma);
  }else{
    return invGammaLinear->invLinScale * x;
  }
}

CML_DEF CMLFunction* cmlCreateInverseGammaLinearResponse(float gamma, float offset, float linScale, float split){
  GammaLinearInputParameters tmpStruct = {gamma, offset, linScale, split};
  return cmlCreateFunction(
    cml_ConstructInverseGammaLinearResponseInput,
    CML_NULL,
    cml_EvaluateInverseGammaLinearResponse,
    sizeof(InverseGammaLinearStruct),
    &tmpStruct);
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

CML_HDEF float cml_EvaluatesRGBToXYZResponse(const void* data, float x){
  data = data;
  if(x > CML_LIN_SRGB_SWITCH){
    return powf((x + CML_SRGB_OFFSET) * CML_SRGB_INV_SCALE, CML_SRGB_GAMMA);
  }else if(x < -CML_LIN_SRGB_SWITCH){
    return -powf((-x + CML_SRGB_OFFSET) * CML_SRGB_INV_SCALE, CML_SRGB_GAMMA);
  }else{
    return x * CML_SRGB_LIN_INV_SCALE;
  }
}


CML_DEF CMLFunction* cmlCreatesRGBToXYZResponse(){
  return cmlCreateFunction(
    CML_NULL,
    CML_NULL,
    cml_EvaluatesRGBToXYZResponse,
    0,
    CML_NULL);
}



// //////////////////////////////////////////////
// XYZ -> sRGB Response
// //////////////////////////////////////////////

CML_HDEF float cml_EvaluateXYZTosRGBResponse(const void* data, float x){
  data = data;
  if(x > CML_SRGB_LIN_SWITCH){
    return (CML_SRGB_SCALE * powf(x, CML_SRGB_INV_GAMMA) - CML_SRGB_OFFSET);
  }else if(x < -CML_SRGB_LIN_SWITCH){
    return -(CML_SRGB_SCALE * powf(-x, CML_SRGB_INV_GAMMA) - CML_SRGB_OFFSET);
  }else{
    return (x * CML_SRGB_LIN_SCALE);
  }
}


CML_DEF CMLFunction* cmlCreateXYZTosRGBResponse(){
  return cmlCreateFunction(
    CML_NULL,
    CML_NULL,
    cml_EvaluateXYZTosRGBResponse,
    0,
    CML_NULL);
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

CML_HDEF float cml_EvaluateYToLStarResponse(const void* data, float x){
  data = data;
  if(x > CML_LIN_LSTAR_SWITCH){
    return cml_fytoLr(cmlCbrt(x));
  }else{
    return x * CML_LSTAR_LINEAR_SCALE;
  }
}

CML_DEF CMLFunction* cmlCreateYToLStarResponse(){
  return cmlCreateFunction(
    CML_NULL,
    CML_NULL,
    cml_EvaluateYToLStarResponse,
    0,
    CML_NULL);
}



// //////////////////////////////////////////////
// L Star -> Y Response
// //////////////////////////////////////////////

CML_HDEF float cml_EvaluateLStarToYResponse(const void* data, float x){
  data = data;
  if(x > CML_LSTAR_LIN_SWITCH){
    float fy = cml_Lrtofy(x);
    return fy*fy*fy;
  }else{
    return x * CML_LSTAR_LINEAR_INV_SCALE;
  }
}

CML_DEF CMLFunction* cmlCreateLStarToYResponse(){
  return cmlCreateFunction(
    CML_NULL,
    CML_NULL,
    cml_EvaluateLStarToYResponse,
    0,
    CML_NULL);
}



// //////////////////////////////////////////////
// Linear -> L Star Standard Response
// //////////////////////////////////////////////

CML_HDEF float cml_EvaluateYToLStarStandardResponse(const void* data, float x){
  data = data;
  if(x > CML_LIN_LSTAR_SWITCH_STANDARD){
    return cml_fytoLr(cmlCbrt(x));
  }else{
    return x * CML_LSTAR_LINEAR_SCALE_STANDARD;
  }
}

CML_DEF CMLFunction* cmlCreateYToLStarStandardResponse(){
  return cmlCreateFunction(
    CML_NULL,
    CML_NULL,
    cml_EvaluateYToLStarStandardResponse,
    0,
    CML_NULL);
}



// //////////////////////////////////////////////
// L Star -> Linear Response
// //////////////////////////////////////////////

CML_HDEF float cml_EvaluateLStarToYStandardResponse(const void* data, float x){
  data = data;
  if(x > CML_LSTAR_LIN_SWITCH_STANDARD){
    float fy = cml_Lrtofy(x);
    return fy*fy*fy;
  }else{
    return x * CML_LSTAR_LINEAR_INV_SCALE_STANDARD;
  }
}

CML_DEF CMLFunction* cmlCreateLStarToYStandardResponse(){
  return cmlCreateFunction(
    CML_NULL,
    CML_NULL,
    cml_EvaluateLStarToYStandardResponse,
    0,
    CML_NULL);
}



// //////////////////////////////////////////////
// Dirac Filter
// //////////////////////////////////////////////

CML_HDEF void cml_ConstructDiracFilterInput(void* data, CMLDefinitionRange* defRange, const void* input){
  float waveLength = *((const float*)input);
  *((float*)data) = waveLength;

  defRange->minSampleCoord = waveLength;
  defRange->maxSampleCoord = waveLength;
  defRange->minNonTrivialCoord = waveLength;
  defRange->maxNonTrivialCoord = waveLength;
}

CML_HDEF const void* cml_GetDiracFilterInput(void* data){
  return data;
}

CML_HDEF float cml_EvaluateDiracFilter(const void* data, float x){
  float pos = *((float*)data);
  return (x == pos) ? 1.f: 0.f;
}


CML_DEF CMLFunction* cmlCreateDiracFilter(float wavelength){
  return cmlCreateFunction(
    cml_ConstructDiracFilterInput,
    CML_NULL,
    cml_EvaluateDiracFilter,
    sizeof(float),
    &wavelength);
}



// //////////////////////////////////////////////
// Constant Filter
// //////////////////////////////////////////////

CML_HDEF void cml_ConstructConstantFilterInput(void* data, CMLDefinitionRange* defRange, const void* input){
  CML_UNUSED(defRange);
  *((float*)data) = *((const float*)input);
}

CML_HDEF const void* cml_GetConstantFilterInput(void* data){
  return data;
}

CML_HDEF float cml_EvaluateConstFilter(const void* data, float x){
  CML_UNUSED(x);
  return *((float*)data);
}


CML_DEF CMLFunction* cmlCreateConstFilter(float value){
  return cmlCreateFunction(
    cml_ConstructConstantFilterInput,
    CML_NULL,
    cml_EvaluateConstFilter,
    sizeof(float),
    &value);
}



// //////////////////////////////////////////////
// Cut Filter
// //////////////////////////////////////////////

typedef struct CML_HDEF CMLCutFilterInput{
  float min;
  float max;
} CMLCutFilterInput;

CML_HDEF void cml_ConstructCutFilterInput(void* data, CMLDefinitionRange* defRange, const void* input){
  CML_UNUSED(input);
  CMLCutFilterInput* range = (CMLCutFilterInput*)input;
  *((CMLCutFilterInput*)data) = *range;
  defRange->minNonTrivialCoord = range->min;
  defRange->maxNonTrivialCoord = range->max;
}

CML_HDEF float cml_EvaluateCutFilter(const void* data, float x){
  CMLCutFilterInput* range = (CMLCutFilterInput*)(data);
  return ((x>=range->min) && (x<=range->max)) ? 1.f : 0.f;
}

CML_DEF CMLFunction* cmlCreateCutFilter(float min, float max){
  CMLCutFilterInput range = {min, max};
  return cmlCreateFunction(
    cml_ConstructCutFilterInput,
    CML_NULL,
    cml_EvaluateCutFilter,
    sizeof(CMLCutFilterInput),
    &range);
}



// //////////////////////////////////////////////
// Composite Function definitions
// //////////////////////////////////////////////

typedef struct CMLFunctionFunctionStorage CMLFunctionFunctionStorage;
struct CML_HDEF CMLFunctionFunctionStorage{
  CMLFunction* func1;
  CMLFunction* func2;
};

typedef struct CMLFunctionScalarStorage CMLFunctionScalarStorage;
struct CML_HDEF CMLFunctionScalarStorage{
  CMLFunction* func1;
  float scalar;
};

typedef struct CMLFunctionFunctionInput CMLFunctionFunctionInput;
struct CML_HDEF CMLFunctionFunctionInput{
  const CMLFunction* func1;
  const CMLFunction* func2;
};

typedef struct CMLFunctionScalarInput CMLFunctionScalarInput;
struct CML_HDEF CMLFunctionScalarInput{
  const CMLFunction* func1;
  float scalar;
};



// //////////////////////////////////////////////
// Function add Function
// //////////////////////////////////////////////

CML_HDEF void cml_ConstructFunctionAddFunction(void* data, CMLDefinitionRange* defRange, const void* input){
  CMLFunctionFunctionStorage* thisdata = (CMLFunctionFunctionStorage*)data;
  CMLFunctionFunctionInput* indata = (CMLFunctionFunctionInput*)(input);
  thisdata->func1 = cmlDuplicateFunction(indata->func1);
  thisdata->func2 = cmlDuplicateFunction(indata->func2);
  CMLDefinitionRange newRange = cml_GetDefinitionRangeOfTwoFunctions(indata->func1, indata->func2, CML_FALSE);
  *defRange = newRange;
}

CML_HDEF void cml_DestructFunctionAddFunction(void* data){
  CMLFunctionFunctionStorage* thisdata = (CMLFunctionFunctionStorage*)data;
  cmlReleaseFunction(thisdata->func1);
  cmlReleaseFunction(thisdata->func2);
}

CML_HDEF float cml_EvaluateFunctionAddFunction(const void* data, float x){
  CMLFunctionFunctionStorage* thisdata = (CMLFunctionFunctionStorage*)data;
  return cml_Eval(thisdata->func1, x) + cml_Eval(thisdata->func2, x);
}

CML_DEF CMLFunction* cmlCreateFunctionAddFunction(const CMLFunction* func1, const CMLFunction* func2){
  CMLFunctionFunctionInput newData = {func1, func2};
  return cmlCreateFunction(
    cml_ConstructFunctionAddFunction,
    cml_DestructFunctionAddFunction,
    cml_EvaluateFunctionAddFunction,
    sizeof(CMLFunctionFunctionStorage),
    &newData);
}



// //////////////////////////////////////////////
// Function sub Function
// //////////////////////////////////////////////

CML_HDEF void cml_ConstructFunctionSubFunction(void* data, CMLDefinitionRange* defRange, const void* input){
  CMLFunctionFunctionStorage* thisdata = (CMLFunctionFunctionStorage*)data;
  CMLFunctionFunctionInput* indata = (CMLFunctionFunctionInput*)(input);
  thisdata->func1 = cmlDuplicateFunction(indata->func1);
  thisdata->func2 = cmlDuplicateFunction(indata->func2);
  CMLDefinitionRange newRange = cml_GetDefinitionRangeOfTwoFunctions(indata->func1, indata->func2, CML_FALSE);
  *defRange = newRange;
}

CML_HDEF void cml_DestructFunctionSubFunction(void* data){
  CMLFunctionFunctionStorage* thisdata = (CMLFunctionFunctionStorage*)data;
  cmlReleaseFunction(thisdata->func1);
  cmlReleaseFunction(thisdata->func2);
}

CML_HDEF float cml_EvaluateFunctionSubFunction(const void* data, float x){
  CMLFunctionFunctionStorage* thisdata = (CMLFunctionFunctionStorage*)data;
  return cml_Eval(thisdata->func1, x) - cml_Eval(thisdata->func2, x);
}

CML_DEF CMLFunction* cmlCreateFunctionSubFunction(const CMLFunction* func1, const CMLFunction* func2){
  CMLFunctionFunctionInput newData = {func1, func2};
  return cmlCreateFunction(
    cml_ConstructFunctionSubFunction,
    cml_DestructFunctionSubFunction,
    cml_EvaluateFunctionSubFunction,
    sizeof(CMLFunctionFunctionInput),
    &newData);
}



// //////////////////////////////////////////////
// Function mul Function
// //////////////////////////////////////////////

CML_HDEF void cml_ConstructFunctionMulFunction(void* data, CMLDefinitionRange* defRange, const void* input){
  CMLFunctionFunctionStorage* thisdata = (CMLFunctionFunctionStorage*)data;
  CMLFunctionFunctionInput* indata = (CMLFunctionFunctionInput*)(input);
  thisdata->func1 = cmlDuplicateFunction(indata->func1);
  thisdata->func2 = cmlDuplicateFunction(indata->func2);
  CMLDefinitionRange newRange = cml_GetDefinitionRangeOfTwoFunctions(indata->func1, indata->func2, CML_TRUE);
  *defRange = newRange;
}

CML_HDEF void cml_DestructFunctionMulFunction(void* data){
  CMLFunctionFunctionStorage* thisdata = (CMLFunctionFunctionStorage*)data;
  cmlReleaseFunction(thisdata->func1);
  cmlReleaseFunction(thisdata->func2);
}

CML_HDEF float cml_EvaluateFunctionMulFunction(const void* data, float x){
  CMLFunctionFunctionStorage* thisdata = (CMLFunctionFunctionStorage*)data;
  return cml_Eval(thisdata->func1, x) * cml_Eval(thisdata->func2, x);
}

CML_DEF CMLFunction* cmlCreateFunctionMulFunction(const CMLFunction* func1, const CMLFunction* func2){
  CMLFunctionFunctionInput newData = {func1, func2};
  return cmlCreateFunction(
    cml_ConstructFunctionMulFunction,
    cml_DestructFunctionMulFunction,
    cml_EvaluateFunctionMulFunction,
    sizeof(CMLFunctionFunctionInput),
    &newData);
}



// //////////////////////////////////////////////
// Function div Function
// //////////////////////////////////////////////

CML_HDEF void cml_ConstructFunctionDivFunction(void* data, CMLDefinitionRange* defRange, const void* input){
  CMLFunctionFunctionStorage* thisdata = (CMLFunctionFunctionStorage*)data;
  CMLFunctionFunctionInput* indata = (CMLFunctionFunctionInput*)(input);
  thisdata->func1 = cmlDuplicateFunction(indata->func1);
  thisdata->func2 = cmlDuplicateFunction(indata->func2);
  CMLDefinitionRange newRange = cml_GetDefinitionRangeOfTwoFunctions(indata->func1, indata->func2, CML_TRUE);
  *defRange = newRange;
}

CML_HDEF void cml_DestructFunctionDivFunction(void* data){
  CMLFunctionFunctionStorage* thisdata = (CMLFunctionFunctionStorage*)data;
  cmlReleaseFunction(thisdata->func1);
  cmlReleaseFunction(thisdata->func2);
}

CML_HDEF float cml_EvaluateFunctionDivFunction(const void* data, float x){
  CMLFunctionFunctionStorage* thisdata = (CMLFunctionFunctionStorage*)data;
  return cml_Eval(thisdata->func1, x) / cml_Eval(thisdata->func2, x);
}

CML_DEF CMLFunction* cmlCreateFunctionDivFunction(const CMLFunction* func1, const CMLFunction* func2){
  CMLFunctionFunctionInput newData = {func1, func2};
  return cmlCreateFunction(
    cml_ConstructFunctionDivFunction,
    cml_DestructFunctionDivFunction,
    cml_EvaluateFunctionDivFunction,
    sizeof(CMLFunctionFunctionInput),
    &newData);
}



// //////////////////////////////////////////////
// Function mul Scalar
// //////////////////////////////////////////////

CML_HDEF void cml_ConstructFunctionMulScalar(void* data, CMLDefinitionRange* defRange, const void* input){
  CMLFunctionScalarStorage* thisdata = (CMLFunctionScalarStorage*)data;
  CMLFunctionScalarInput* indata = (CMLFunctionScalarInput*)(input);
  thisdata->func1 = cmlDuplicateFunction(indata->func1);
  thisdata->scalar = indata->scalar;
  *defRange = indata->func1->defRange;
}

CML_HDEF void cml_DestructFunctionMulScalar(void* data){
  CMLFunctionScalarStorage* thisdata = (CMLFunctionScalarStorage*)data;
  cmlReleaseFunction(thisdata->func1);
}

CML_HDEF float cml_EvaluateFunctionMulScalar(const void* data, float x){
  CMLFunctionScalarStorage* thisdata = (CMLFunctionScalarStorage*)data;
  return cml_Eval(thisdata->func1, x) * thisdata->scalar;
}

CML_DEF CMLFunction* cmlCreateFunctionMulScalar(const CMLFunction* func1, float scalar){
  CMLFunctionScalarInput newData = {func1, scalar};
  return cmlCreateFunction(
    cml_ConstructFunctionMulScalar,
    cml_DestructFunctionMulScalar,
    cml_EvaluateFunctionMulScalar,
    sizeof(CMLFunctionScalarInput),
    &newData);
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

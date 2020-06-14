
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

#include "CML.h"
#include "StateMachine/CMLColorMachineState.h"




// ///////////////////////////////////
// Function
// ///////////////////////////////////



CML_API CMLMOBFunction* cmlCreateFunction(CMLFunctionEvaluator evaluator){
  MOB* function = mobCreateObject(cml_Key(CML_FUNCTION_OBJECT));

  #ifndef NDEBUG
    if(!evaluator){
      cmlError("cmlCreateFunction", "evaluator is Null");
    }
  #endif
  cml_SetFunctionEvaluator(function, evaluator);
  
  CMLDefinitionRange defaultdefrange = {
    0.f,
    CML_DEFAULT_INTEGRATION_MIN,
    CML_DEFAULT_INTEGRATION_MAX,
    -CML_INFINITY,
    +CML_INFINITY
  };
  cmlSetFunctionDefinitionRange(function, &defaultdefrange);

  return function;
}




CML_API float cmlEval(CMLMOBFunction* func, float x){
  return cml_Eval(func, x);
}







CML_HIDDEN CML_INLINE CMLDefinitionRange cmlGetDefinitionRangeOf2Functions(CMLMOBFunction* func1, CMLMOBFunction* func2, CMLBool multiplicative){
  
  float minsamplecoord1;
  float maxsamplecoord1;
  float minsamplecoord2;
  float maxsamplecoord2;
  
  CMLDefinitionRange range1;
  CMLDefinitionRange range2;
  cmlGetFunctionDefinitionRange(func1, &range1);
  cmlGetFunctionDefinitionRange(func2, &range2);
  CMLDefinitionRange newrange;
  
  // first, set the desired stepsize
  if(range1.stepsize == 0.f){newrange.stepsize = range2.stepsize;}
  else if(range2.stepsize == 0.f){newrange.stepsize = range1.stepsize;}
  else if(range1.stepsize < range2.stepsize){newrange.stepsize = range1.stepsize;}
  else{newrange.stepsize = range2.stepsize;}
  
  if(range1.stepsize == 0.f){range1.stepsize = 1.f;}
  if(range2.stepsize == 0.f){range2.stepsize = 1.f;}

  // then, set the trivial boundaries
  if(multiplicative){
    // one trivial value will result in a trivial value
    newrange.minNonTrivialCoord = CML_MAX(range1.minNonTrivialCoord, range2.minNonTrivialCoord);
    newrange.maxNonTrivialCoord = CML_MIN(range1.maxNonTrivialCoord, range2.maxNonTrivialCoord);
  }else{
    // a trivial value maybe does not result in a trivial value
    newrange.minNonTrivialCoord = CML_MIN(range1.minNonTrivialCoord, range2.minNonTrivialCoord);
    newrange.maxNonTrivialCoord = CML_MAX(range1.maxNonTrivialCoord, range2.maxNonTrivialCoord);
  }

  // finally, set the sampling coordinates by making sure, they are in the
  // non-trivial range and are aligned with the original data.
  minsamplecoord1 = range1.minSampleCoord;
  maxsamplecoord1 = range1.maxSampleCoord;
  minsamplecoord2 = range2.minSampleCoord;
  maxsamplecoord2 = range2.maxSampleCoord;
  if(minsamplecoord1 < newrange.minNonTrivialCoord){minsamplecoord1 += range1.stepsize * ceilf((newrange.minNonTrivialCoord - range1.minSampleCoord) / range1.stepsize);}
  if(maxsamplecoord1 > newrange.maxNonTrivialCoord){maxsamplecoord1 -= range1.stepsize * ceilf((range1.maxSampleCoord - newrange.maxNonTrivialCoord) / range1.stepsize);}
  if(minsamplecoord2 < newrange.minNonTrivialCoord){minsamplecoord2 += range2.stepsize * ceilf((newrange.minNonTrivialCoord - range2.minSampleCoord) / range2.stepsize);}
  if(maxsamplecoord2 > newrange.maxNonTrivialCoord){maxsamplecoord2 -= range2.stepsize * ceilf((range2.maxSampleCoord - newrange.maxNonTrivialCoord) / range2.stepsize);}

  newrange.minSampleCoord = CML_MIN(minsamplecoord1, minsamplecoord2);
  newrange.maxSampleCoord = CML_MAX(maxsamplecoord1, maxsamplecoord2);

  return newrange;
}


CML_API float cmlFilterFunction(CMLMOBFunction* func, CMLMOBFunction* filter){
  CMLSize samplecount;
  CMLIntegrationMethod type;
  float sum = 0.f;

  CMLDefinitionRange filterrange = cmlGetDefinitionRangeOf2Functions(func, filter, CML_TRUE);
  if(filterrange.minSampleCoord > filterrange.maxSampleCoord){return 0.f;}
  
  #ifndef NDEBUG
    if(filterrange.stepsize < 0.f){cmlError("cmlFilterFunction", "Negative stepsize in Function.");}
  #endif
  // If the stepsize is 0, the function will be filtered as a continuous
  // function with the default integration stepsize.
  if(filterrange.stepsize == 0.f){filterrange.stepsize = CML_DEFAULT_INTEGRATION_STEPSIZE;}
  samplecount = (CMLSize)(CMLRound((filterrange.maxSampleCoord - filterrange.minSampleCoord) / filterrange.stepsize)) + 1;
  // If there is only one value to compute, the stepsize is manually set to 1
  // to not normalize the final result with a wrong value.
  if(samplecount == 1){filterrange.stepsize = 1.f;}

  type = CML_DEFAULT_INTEGRATION_TYPE;
  if(samplecount < 2){type = CML_INTEGRATION_SIMPLE;}
  switch(type){
  
  case CML_INTEGRATION_SIMPLE:
    {
      CMLSize istep;
      // Simple sum computation by adding one by one
      for(istep = 0; istep < samplecount; istep++){
        float x = filterrange.minSampleCoord + (filterrange.stepsize * istep);
        sum += cml_Eval(func, x) * cml_Eval(filter, x);
      }
    } break;
    
  case CML_INTEGRATION_BINARY_PAIRS:
    {
      CMLSize istep;
      CMLSize i;
      float tmpsums[8 * sizeof(CMLSize)];  // 8 denotes bits per Byte
      memset(tmpsums, 0, sizeof(float) * (8 * sizeof(CMLSize)));

      // iterative binary sum computation method
      for(istep = 0; istep < samplecount; istep+=2){

        // Compute two neighboring values.
        float x1 = filterrange.minSampleCoord + (filterrange.stepsize * istep);
        float value1 = cml_Eval(func, x1) * cml_Eval(filter, x1);
        float x2 = filterrange.minSampleCoord + (filterrange.stepsize * (istep + 1));
        float value2 = cml_Eval(func, x2) * cml_Eval(filter, x2);

        // Add these values together with the temp sums up to the position where
        // the current istep has its first binary 0.
        float walkingsum = value1 + value2;
        char p = 1;
        CMLSize step = 2;
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
        tmpsums[0] = cml_Eval(func, filterrange.maxSampleCoord) * cml_Eval(filter, filterrange.maxSampleCoord);
      }
      // Finally, go though all temp sums and add those to the final sum where
      // samplecount has a binary 1
      for(i=0; i<8 * sizeof(CMLSize); i++){
        if(samplecount & (1<<i)){
          sum += tmpsums[i];
        }
      }
    } break;

  default:
    #ifndef NDEBUG
      cmlError("cmlFilterFunction", "Invalid Integration type.");
    #endif
    return 0.f;
    break;
  }

  return sum * filterrange.stepsize;
}


//CML_API float cmlGetFunctionMaxValue(const CMLFunction* func){
//  CMLSize samplecount;
//  CMLSize x;
//  float max = -CML_INFINITY;
//  float stepsize = func->defrange.stepsize;
//  if(stepsize == 0){stepsize = CML_DEFAULT_INTEGRATION_STEPSIZE;}
//  samplecount = cmlGetSampleCount(func->defrange.minSampleCoord, func->defrange.maxSampleCoord, stepsize);
//  for(x = 0; x < samplecount; x ++){
//    float coord = func->defrange.minSampleCoord + x * stepsize;
//    float value = cml_Eval(func, coord);
//    if(value > max){max = value;}
//  }
//  return max;
//}


CML_API void cmlGetFunctionDefinitionRange(
                                      CMLMOBFunction* function,
                                     CMLDefinitionRange* defrange){
  defrange->stepsize =            *mobKeyFloat(function, cml_Key(CML_FUNCTION_STEPSIZE));
  defrange->minSampleCoord =      *mobKeyFloat(function, cml_Key(CML_FUNCTION_MIN_SAMPLE_COORD));
  defrange->maxSampleCoord =      *mobKeyFloat(function, cml_Key(CML_FUNCTION_MAX_SAMPLE_COORD));
  defrange->minNonTrivialCoord =  *mobKeyFloat(function, cml_Key(CML_FUNCTION_MIN_NON_TRIVIAL_COORD));
  defrange->maxNonTrivialCoord =  *mobKeyFloat(function, cml_Key(CML_FUNCTION_MAX_NON_TRIVIAL_COORD));
}


CML_API void cmlSetFunctionDefinitionRange(
                                      CMLMOBFunction* function,
                                     CMLDefinitionRange* defrange){
  *mobKeyFloat(function, cml_Key(CML_FUNCTION_STEPSIZE)) = defrange->stepsize;
  *mobKeyFloat(function, cml_Key(CML_FUNCTION_MIN_SAMPLE_COORD)) = defrange->minSampleCoord;
  *mobKeyFloat(function, cml_Key(CML_FUNCTION_MAX_SAMPLE_COORD)) = defrange->maxSampleCoord;
  *mobKeyFloat(function, cml_Key(CML_FUNCTION_MIN_NON_TRIVIAL_COORD)) = defrange->minNonTrivialCoord;
  *mobKeyFloat(function, cml_Key(CML_FUNCTION_MAX_NON_TRIVIAL_COORD)) = defrange->maxNonTrivialCoord;
}



CMLFunctionEvaluator cml_GetFunctionEvaluator(CMLMOBFunction* function){
  CMLFunctionEvaluator fun;
  mobGetKeyUnitValue(function, cml_Key(CML_FUNCTION_EVALUATOR), cml_Unit(CML_UNIT_FUNCTION_EVALUATOR), &fun);
  return fun;
}


void cml_SetFunctionEvaluator(CMLMOBFunction* function, CMLFunctionEvaluator evaluator){
  mobSetKeyUnitValue(function, cml_Key(CML_FUNCTION_EVALUATOR), cml_Unit(CML_UNIT_FUNCTION_EVALUATOR), &evaluator);
}



CML_API CMLMOBFunction* cmlSampleArrayFunction(CMLMOBFunction* func, float minimalcoord, float maximalcoord, CMLSize entrycount, CMLInterpolationMethod interpolationmethod, CMLExtrapolationMethod downextrapolationmethod, CMLExtrapolationMethod upextrapolationmethod){
  CMLSize i;
  float* buffer = (float*)naMalloc(sizeof(float) * entrycount);
  for(i=0; i<entrycount; i++){
    float coord = minimalcoord + ((float)i / (float)(entrycount-1)) * (maximalcoord - minimalcoord);
    buffer[i] = cml_Eval(func, coord);
  }
  return cmlCreateMutableArrayFunction(buffer, CML_TRUE, entrycount, minimalcoord, maximalcoord, interpolationmethod, downextrapolationmethod, upextrapolationmethod);
}









// //////////////////////////////////////////////
// Array Function Helper definitions
// //////////////////////////////////////////////



void cml_SetArrayFunctionExtrapolationDown(CMLMOBFunction* function, CMLFunctionEvaluator extrapolator){
  mobSetKeyUnitValue(function, cml_Key(CML_ARRAY_FUNCTION_DOWN_EXTRAPOLATION_FUNCTION), cml_Unit(CML_UNIT_FUNCTION_EVALUATOR), &extrapolator);
}

void cml_SetArrayFunctionInterpolation(CMLMOBFunction* function, CMLFunctionEvaluator interpolator){
  mobSetKeyUnitValue(function, cml_Key(CML_ARRAY_FUNCTION_INTERPOLATION_FUNCTION), cml_Unit(CML_UNIT_FUNCTION_EVALUATOR), &interpolator);
}

void cml_SetArrayFunctionExtrapolationUp(CMLMOBFunction* function, CMLFunctionEvaluator extrapolator){
  mobSetKeyUnitValue(function, cml_Key(CML_ARRAY_FUNCTION_UP_EXTRAPOLATION_FUNCTION), cml_Unit(CML_UNIT_FUNCTION_EVALUATOR), &extrapolator);
}


CMLFunctionEvaluator cml_GetArrayFunctionExtrapolationDown(CMLMOBFunction* function){
  CMLFunctionEvaluator fun;
  mobGetKeyUnitValue(function, cml_Key(CML_ARRAY_FUNCTION_DOWN_EXTRAPOLATION_FUNCTION), cml_Unit(CML_UNIT_FUNCTION_EVALUATOR), &fun);
  return fun;
}

CMLFunctionEvaluator cml_GetArrayFunctionInterpolation(CMLMOBFunction* function){
  CMLFunctionEvaluator fun;
  mobGetKeyUnitValue(function, cml_Key(CML_ARRAY_FUNCTION_INTERPOLATION_FUNCTION), cml_Unit(CML_UNIT_FUNCTION_EVALUATOR), &fun);
  return fun;
}

CMLFunctionEvaluator cml_GetArrayFunctionExtrapolationUp(CMLMOBFunction* function){
  CMLFunctionEvaluator fun;
  mobGetKeyUnitValue(function, cml_Key(CML_ARRAY_FUNCTION_UP_EXTRAPOLATION_FUNCTION), cml_Unit(CML_UNIT_FUNCTION_EVALUATOR), &fun);
  return fun;
}


CML_HIDDEN float CMLInternalArrayFunctionExtrapolateDownClampZero(CMLMOBFunction* function, float x){
  CML_UNUSED(function);
  CML_UNUSED(x);
  return 0.f;
}

CML_HIDDEN float CMLInternalArrayFunctionExtrapolateDownLinearZero(CMLMOBFunction* function, float x){
  float mincoord = *mobKeyFloat(function, cml_Key(CML_FUNCTION_MIN_SAMPLE_COORD));
  float inverseinterval = *mobKeyFloat(function, cml_Key(CML_ARRAY_FUNCTION_INV_INTERVAL));
  MOB* arrayobject = mobGetKeyObject(function, cml_Key(CML_ARRAY_FUNCTION_VALUE_ARRAY));
  const float* array = mobConstArrayData(arrayobject);
  x = (mincoord - x) * inverseinterval;
  if(x > 1.f){
    return 0.f;
  }else{
    return array[0] * (1.f - x);
  }
}

CML_HIDDEN float CMLInternalArrayFunctionExtrapolateDownClampValue(CMLMOBFunction* function, float x){
  CML_UNUSED(x);
  MOB* arrayobject = mobGetKeyObject(function, cml_Key(CML_ARRAY_FUNCTION_VALUE_ARRAY));
  const float* array = mobConstArrayData(arrayobject);
  return array[0];
}

CML_HIDDEN float CMLInternalArrayFunctionExtrapolateDownGradient(CMLMOBFunction* function, float x){
  float mincoord = *mobKeyFloat(function, cml_Key(CML_FUNCTION_MIN_SAMPLE_COORD));
  float inverseinterval = *mobKeyFloat(function, cml_Key(CML_ARRAY_FUNCTION_INV_INTERVAL));
  MOB* arrayobject = mobGetKeyObject(function, cml_Key(CML_ARRAY_FUNCTION_VALUE_ARRAY));
  const float* array = mobConstArrayData(arrayobject);
  float indx = (x - mincoord) * inverseinterval;
  return array[0] + (array[1] - array[0]) * indx;
}



CML_HIDDEN float CMLInternalArrayFunctionExtrapolateUpClampZero(CMLMOBFunction* function, float x){
  CML_UNUSED(function);
  CML_UNUSED(x);
  return 0.f;
}

CML_HIDDEN float CMLInternalArrayFunctionExtrapolateUpLinearZero(CMLMOBFunction* function, float x){
  float maxcoord = *mobKeyFloat(function, cml_Key(CML_FUNCTION_MAX_SAMPLE_COORD));
  float inverseinterval = *mobKeyFloat(function, cml_Key(CML_ARRAY_FUNCTION_INV_INTERVAL));
  MOB* arrayobject = mobGetKeyObject(function, cml_Key(CML_ARRAY_FUNCTION_VALUE_ARRAY));
  const float* array = mobConstArrayData(arrayobject);
  MOBInt entrycount = *mobKeyInt(function, cml_Key(CML_ARRAY_FUNCTION_VALUE_ARRAY_ENTRYCOUNT));
  x = (x - maxcoord) * inverseinterval;
  if(x > 1.f){
    return 0.f;
  }else{
    return array[entrycount - 1] * (1.f - x);
  }
}

CML_HIDDEN float CMLInternalArrayFunctionExtrapolateUpClampValue(CMLMOBFunction* function, float x){
  CML_UNUSED(x);
  MOB* arrayobject = mobGetKeyObject(function, cml_Key(CML_ARRAY_FUNCTION_VALUE_ARRAY));
  const float* array = mobConstArrayData(arrayobject);
  MOBInt entrycount = *mobKeyInt(function, cml_Key(CML_ARRAY_FUNCTION_VALUE_ARRAY_ENTRYCOUNT));
  return array[entrycount - 1];
}

CML_HIDDEN float CMLInternalArrayFunctionExtrapolateUpGradient(CMLMOBFunction* function, float x){
  float mincoord = *mobKeyFloat(function, cml_Key(CML_FUNCTION_MIN_SAMPLE_COORD));
  float inverseinterval = *mobKeyFloat(function, cml_Key(CML_ARRAY_FUNCTION_INV_INTERVAL));
  MOB* arrayobject = mobGetKeyObject(function, cml_Key(CML_ARRAY_FUNCTION_VALUE_ARRAY));
  const float* array = mobConstArrayData(arrayobject);
  MOBInt entrycount = *mobKeyInt(function, cml_Key(CML_ARRAY_FUNCTION_VALUE_ARRAY_ENTRYCOUNT));
  float indx = (x - mincoord) * inverseinterval;
  return array[entrycount - 1] + (array[entrycount - 2] - array[entrycount - 1]) * indx;
}




CML_HIDDEN float CMLInternalArrayFunctionInterpolateNone(CMLMOBFunction* function, float x){
  float mincoord = *mobKeyFloat(function, cml_Key(CML_FUNCTION_MIN_SAMPLE_COORD));
  float inverseinterval = *mobKeyFloat(function, cml_Key(CML_ARRAY_FUNCTION_INV_INTERVAL));
  MOB* arrayobject = mobGetKeyObject(function, cml_Key(CML_ARRAY_FUNCTION_VALUE_ARRAY));
  const float* array = mobConstArrayData(arrayobject);
  float indx = (x - mincoord) * inverseinterval;
  CMLSize i = (CMLSize)indx;
  if((float)(i) == indx){
    return array[i];
  }else{
    return 0.f;
  }
}

CML_HIDDEN float CMLInternalArrayFunctionInterpolateFloor(CMLMOBFunction* function, float x){
  float mincoord = *mobKeyFloat(function, cml_Key(CML_FUNCTION_MIN_SAMPLE_COORD));
  float inverseinterval = *mobKeyFloat(function, cml_Key(CML_ARRAY_FUNCTION_INV_INTERVAL));
  MOB* arrayobject = mobGetKeyObject(function, cml_Key(CML_ARRAY_FUNCTION_VALUE_ARRAY));
  const float* array = mobConstArrayData(arrayobject);
  float indx = (x - mincoord) * inverseinterval;
  return array[(CMLSize)indx];
}

CML_HIDDEN float CMLInternalArrayFunctionInterpolateBox(CMLMOBFunction* function, float x){
  float mincoord = *mobKeyFloat(function, cml_Key(CML_FUNCTION_MIN_SAMPLE_COORD));
  float inverseinterval = *mobKeyFloat(function, cml_Key(CML_ARRAY_FUNCTION_INV_INTERVAL));
  MOB* arrayobject = mobGetKeyObject(function, cml_Key(CML_ARRAY_FUNCTION_VALUE_ARRAY));
  const float* array = mobConstArrayData(arrayobject);
  float indx = (x - mincoord) * inverseinterval;
  return array[(CMLSize)(indx + .5f)];
}

CML_HIDDEN float CMLInternalArrayFunctionInterpolateInterval(CMLMOBFunction* function, float x){
  float mincoord = *mobKeyFloat(function, cml_Key(CML_FUNCTION_MIN_SAMPLE_COORD));
  float inverseinterval = *mobKeyFloat(function, cml_Key(CML_ARRAY_FUNCTION_INV_INTERVAL));
  MOB* arrayobject = mobGetKeyObject(function, cml_Key(CML_ARRAY_FUNCTION_VALUE_ARRAY));
  const float* array = mobConstArrayData(arrayobject);
  float indx = (x - mincoord) * inverseinterval;
  return array[(CMLSize)indx];
}

CML_HIDDEN float CMLInternalArrayFunctionInterpolateLinear(CMLMOBFunction* function, float x){
  float mincoord = *mobKeyFloat(function, cml_Key(CML_FUNCTION_MIN_SAMPLE_COORD));
  float inverseinterval = *mobKeyFloat(function, cml_Key(CML_ARRAY_FUNCTION_INV_INTERVAL));
  MOB* arrayobject = mobGetKeyObject(function, cml_Key(CML_ARRAY_FUNCTION_VALUE_ARRAY));
  const float* array = mobConstArrayData(arrayobject);
  float indx = (x - mincoord) * inverseinterval;
  CMLSize i1 = (CMLSize)indx;
  CMLSize i2 = i1 + 1;
  float alpha = indx - (float)(i1);
  return array[i1] - (array[i1] - array[i2]) * alpha;
}







// //////////////////////////////////////////////
// Array Function
// //////////////////////////////////////////////




CML_HIDDEN void cml_UpdateArrayFunction(CMLMOBFunction* function){

  CMLExtrapolationMethod extrapolationmethoddown = *(CMLExtrapolationMethod*)mobKeyEnum(function, cml_Key(CML_ARRAY_FUNCTION_DOWN_EXTRAPOLATION_METHOD));
  CMLInterpolationMethod interpolationmethod = *(CMLInterpolationMethod*)mobKeyEnum(function, cml_Key(CML_ARRAY_FUNCTION_INTERPOLATION_METHOD));
  CMLExtrapolationMethod extrapolationmethodup = *(CMLExtrapolationMethod*)mobKeyEnum(function, cml_Key(CML_ARRAY_FUNCTION_UP_EXTRAPOLATION_METHOD));

  float mincoord = *mobKeyFloat(function, cml_Key(CML_FUNCTION_MIN_SAMPLE_COORD));
  float maxcoord = *mobKeyFloat(function, cml_Key(CML_FUNCTION_MAX_SAMPLE_COORD));
  MOBInt entrycount = *mobKeyInt(function, cml_Key(CML_ARRAY_FUNCTION_VALUE_ARRAY_ENTRYCOUNT));

  #ifndef NDEBUG
    if(entrycount <= 1){
      cmlError("cml_UpdateArrayFunction", "Array Function with 1 or 0 Entries may not work properly yet.");
    }
  #endif

  switch(extrapolationmethoddown){
  case CML_EXTRAPOLATION_CLAMP_ZERO:
    cml_SetArrayFunctionExtrapolationDown(function, &CMLInternalArrayFunctionExtrapolateDownClampZero);
    *mobKeyFloat(function, cml_Key(CML_FUNCTION_MIN_NON_TRIVIAL_COORD)) = mincoord;
    break;
  case CML_EXTRAPOLATION_LINEAR_ZERO:
    cml_SetArrayFunctionExtrapolationDown(function, &CMLInternalArrayFunctionExtrapolateDownLinearZero);
    *mobKeyFloat(function, cml_Key(CML_FUNCTION_MIN_NON_TRIVIAL_COORD)) = mincoord - cmlGetStepSize(mincoord, maxcoord, (CMLSize)entrycount);
    break;
  case CML_EXTRAPOLATION_CLAMP_VALUE:
    cml_SetArrayFunctionExtrapolationDown(function, &CMLInternalArrayFunctionExtrapolateDownClampValue);
    *mobKeyFloat(function, cml_Key(CML_FUNCTION_MIN_NON_TRIVIAL_COORD)) = -CML_INFINITY;
    break;
  case CML_EXTRAPOLATION_GRADIENT:
    cml_SetArrayFunctionExtrapolationDown(function, &CMLInternalArrayFunctionExtrapolateDownGradient);
    *mobKeyFloat(function, cml_Key(CML_FUNCTION_MIN_NON_TRIVIAL_COORD)) = -CML_INFINITY;
    break;
  default:
    #ifndef NDEBUG
      cmlError("cml_UpdateArrayFunction", "Undefined Down-Extrapolation method.");
    #endif
    cml_SetArrayFunctionExtrapolationDown(function, CML_NULL);
    break;
  }

  switch(extrapolationmethodup){
  case CML_EXTRAPOLATION_CLAMP_ZERO:
    cml_SetArrayFunctionExtrapolationUp(function, &CMLInternalArrayFunctionExtrapolateUpClampZero);
    *mobKeyFloat(function, cml_Key(CML_FUNCTION_MAX_NON_TRIVIAL_COORD)) = maxcoord;
    break;
  case CML_EXTRAPOLATION_LINEAR_ZERO:
    cml_SetArrayFunctionExtrapolationUp(function, &CMLInternalArrayFunctionExtrapolateUpLinearZero);
    *mobKeyFloat(function, cml_Key(CML_FUNCTION_MAX_NON_TRIVIAL_COORD)) = maxcoord + cmlGetStepSize(mincoord, maxcoord, (CMLSize)entrycount);
    break;
  case CML_EXTRAPOLATION_CLAMP_VALUE:
    cml_SetArrayFunctionExtrapolationUp(function, &CMLInternalArrayFunctionExtrapolateUpClampValue);
    *mobKeyFloat(function, cml_Key(CML_FUNCTION_MAX_NON_TRIVIAL_COORD)) = CML_INFINITY;
    break;
  case CML_EXTRAPOLATION_GRADIENT:
    cml_SetArrayFunctionExtrapolationUp(function, &CMLInternalArrayFunctionExtrapolateUpGradient);
    *mobKeyFloat(function, cml_Key(CML_FUNCTION_MAX_NON_TRIVIAL_COORD)) = CML_INFINITY;
    break;
  default:
    #ifndef NDEBUG
      cmlError("CMLInternalConstructArrayFunction", "Undefined Up-Extrapolation method.");
    #endif
    cml_SetArrayFunctionExtrapolationUp(function, CML_NULL);
    break;
  }

  float inverseinterval = 1.f;

  switch(interpolationmethod){
  case CML_INTERPOLATION_NONE:
    *mobKeyFloat(function, cml_Key(CML_FUNCTION_MIN_SAMPLE_COORD)) = mincoord;
    *mobKeyFloat(function, cml_Key(CML_FUNCTION_MAX_SAMPLE_COORD)) = maxcoord;
    inverseinterval = (float)(entrycount - 1) / (maxcoord - mincoord);
    cml_SetArrayFunctionInterpolation(function, &CMLInternalArrayFunctionInterpolateNone);
    break;
  case CML_INTERPOLATION_FLOOR:
    *mobKeyFloat(function, cml_Key(CML_FUNCTION_MIN_SAMPLE_COORD)) = mincoord;
    *mobKeyFloat(function, cml_Key(CML_FUNCTION_MAX_SAMPLE_COORD)) = maxcoord + ((maxcoord - mincoord) / (float)(entrycount - 1));
    inverseinterval = (float)(entrycount - 1) / (maxcoord - mincoord);
    cml_SetArrayFunctionInterpolation(function, &CMLInternalArrayFunctionInterpolateFloor);
    break;
  case CML_INTERPOLATION_BOX:
    *mobKeyFloat(function, cml_Key(CML_FUNCTION_MIN_SAMPLE_COORD)) = mincoord - (.5f * (maxcoord - mincoord) / (float)(entrycount - 1));
    *mobKeyFloat(function, cml_Key(CML_FUNCTION_MAX_SAMPLE_COORD)) = maxcoord + (.5f * (maxcoord - mincoord) / (float)(entrycount - 1));
    inverseinterval = (float)(entrycount - 1) / (maxcoord - mincoord);
    cml_SetArrayFunctionInterpolation(function, &CMLInternalArrayFunctionInterpolateBox);
    break;
  case CML_INTERPOLATION_INTERVAL:
    *mobKeyFloat(function, cml_Key(CML_FUNCTION_MIN_SAMPLE_COORD)) = mincoord;
    *mobKeyFloat(function, cml_Key(CML_FUNCTION_MAX_SAMPLE_COORD)) = maxcoord;
    inverseinterval = (float)(entrycount) / (maxcoord - mincoord);
    cml_SetArrayFunctionInterpolation(function, &CMLInternalArrayFunctionInterpolateInterval);    break;
  case CML_INTERPOLATION_LINEAR:
    *mobKeyFloat(function, cml_Key(CML_FUNCTION_MIN_SAMPLE_COORD)) = mincoord;
    *mobKeyFloat(function, cml_Key(CML_FUNCTION_MAX_SAMPLE_COORD)) = maxcoord;
    inverseinterval = (float)(entrycount - 1) / (maxcoord - mincoord);
    cml_SetArrayFunctionInterpolation(function, &CMLInternalArrayFunctionInterpolateLinear);    break;
    break;
  default:
    #ifndef NDEBUG
      cmlError("CMLInternalConstructArrayFunction", "Undefined Interpolation method.");
    #endif
    cml_SetArrayFunctionInterpolation(function, CML_NULL);
    break;
  }
  *mobKeyFloat(function, cml_Key(CML_ARRAY_FUNCTION_INV_INTERVAL)) = inverseinterval;
  *mobKeyFloat(function, cml_Key(CML_FUNCTION_STEPSIZE)) = cmlInverse(inverseinterval);
}


CML_HIDDEN float cml_EvaluateArrayFunction(CMLMOBFunction* function, float x){
  float mincoord = *mobKeyFloat(function, cml_Key(CML_FUNCTION_MIN_SAMPLE_COORD));
  float maxcoord = *mobKeyFloat(function, cml_Key(CML_FUNCTION_MAX_SAMPLE_COORD));

  CMLFunctionEvaluator evaluator;
  
  if(x < mincoord){
    evaluator = cml_GetArrayFunctionExtrapolationDown(function);
  }else if(x > maxcoord){
    evaluator = cml_GetArrayFunctionExtrapolationUp(function);
  }else{
    evaluator = cml_GetArrayFunctionInterpolation(function);
  }
  return evaluator(function, x);
}


CML_API CMLMOBFunction* cmlCreateConstArrayFunction(const float* buffer, CMLSize entrycount, float mincoord, float maxcoord, CMLInterpolationMethod interpolationmethod, CMLExtrapolationMethod extrapolationmethoddown, CMLExtrapolationMethod extrapolationmethodup){
  CMLMOBFunction* function = cmlCreateFunction(cml_EvaluateArrayFunction);
  *mobKeyFloat(function, cml_Key(CML_FUNCTION_MIN_SAMPLE_COORD)) = mincoord;
  *mobKeyFloat(function, cml_Key(CML_FUNCTION_MAX_SAMPLE_COORD)) = maxcoord;

  *(CMLExtrapolationMethod*)mobKeyEnum(function, cml_Key(CML_ARRAY_FUNCTION_DOWN_EXTRAPOLATION_METHOD)) = extrapolationmethoddown;
  *(CMLInterpolationMethod*)mobKeyEnum(function, cml_Key(CML_ARRAY_FUNCTION_INTERPOLATION_METHOD)) = interpolationmethod;
  *(CMLExtrapolationMethod*)mobKeyEnum(function, cml_Key(CML_ARRAY_FUNCTION_UP_EXTRAPOLATION_METHOD)) = extrapolationmethodup;
  // todo: const cast hack.
  MOB* arrayobject = mobCreateFloatArrayWithBuffer(entrycount, (float*)buffer, NA_FALSE);
  mobSetKeyObject(function, cml_Key(CML_ARRAY_FUNCTION_VALUE_ARRAY), arrayobject, MOB_FALSE);
  *mobKeyInt(function, cml_Key(CML_ARRAY_FUNCTION_VALUE_ARRAY_ENTRYCOUNT)) = entrycount;

  cml_UpdateArrayFunction(function);
  return function;
}


CML_API CMLMOBFunction* cmlCreateMutableArrayFunction(float* buffer, CMLBool ownbuffer, CMLSize entrycount, float mincoord, float maxcoord, CMLInterpolationMethod interpolationmethod, CMLExtrapolationMethod extrapolationmethoddown, CMLExtrapolationMethod extrapolationmethodup){
  CMLMOBFunction* function = cmlCreateFunction(cml_EvaluateArrayFunction);
  *mobKeyFloat(function, cml_Key(CML_FUNCTION_MIN_SAMPLE_COORD)) = mincoord;
  *mobKeyFloat(function, cml_Key(CML_FUNCTION_MAX_SAMPLE_COORD)) = maxcoord;

  *(CMLExtrapolationMethod*)mobKeyEnum(function, cml_Key(CML_ARRAY_FUNCTION_DOWN_EXTRAPOLATION_METHOD)) = extrapolationmethoddown;
  *(CMLInterpolationMethod*)mobKeyEnum(function, cml_Key(CML_ARRAY_FUNCTION_INTERPOLATION_METHOD)) = interpolationmethod;
  *(CMLExtrapolationMethod*)mobKeyEnum(function, cml_Key(CML_ARRAY_FUNCTION_UP_EXTRAPOLATION_METHOD)) = extrapolationmethodup;
  MOB* arrayobject = mobCreateFloatArrayWithBuffer(entrycount, buffer, ownbuffer);
  mobSetKeyObject(function, cml_Key(CML_ARRAY_FUNCTION_VALUE_ARRAY), arrayobject, MOB_FALSE);
  *mobKeyInt(function, cml_Key(CML_ARRAY_FUNCTION_VALUE_ARRAY_ENTRYCOUNT)) = entrycount;

  cml_UpdateArrayFunction(function);
  return function;
}







// //////////////////////////////////////////////
// Blackbody
// //////////////////////////////////////////////

CML_HIDDEN void cml_UpdateBlackBody(CMLMOBFunction* function){
  float temperature = *mobKeyFloat(function, cml_Key(CML_TEMPERATURE_K));
  float c;
  if(temperature <= 0){
    #ifndef NDEBUG
      cmlError("cml_UpdateBlackBody", "Temperature must be greater than 0 Kelvin.");
    #endif
    return;
  }

  if(temperature == CML_INFINITY){
    c = 0.f;
  }else{
    c = NA_SECOND_RAD / temperature;
  }
  *mobKeyFloat(function, cml_Key(CML_BLACKBODY_FACTOR_c)) = c;
}


CML_HIDDEN float cml_EvaluateBlackBody(CMLMOBFunction* function, float x){
  float nanolambda;
  // Note: x is expected in [nanometer]
  if(x <= 0){
    #ifndef NDEBUG
      cmlError("cml_EvaluateBlackBody", "Blackbody radiator is only defined for input values greater than 0.");
    #endif
    return 0.f;
  }
  float c = *mobKeyFloat(function, cml_Key(CML_BLACKBODY_FACTOR_c));
  nanolambda = x * 1e-9f;
  if(c == 0.f){
    return NA_PI2 * NA_PLANCK * NA_LIGHT_SPEED_VAC * NA_LIGHT_SPEED_VAC / (powf(nanolambda, 5.f));
  }else{
    return NA_PI2 * NA_PLANCK * NA_LIGHT_SPEED_VAC * NA_LIGHT_SPEED_VAC / (powf(nanolambda, 5.f) * (expf(c / nanolambda) - 1.f));
  }
  // first constant is NA_PI2 * NA_PLANCK * NA_LIGHT_SPEED_VAC * NA_LIGHT_SPEED_VAC;
//    return float(.587756042555631108333846414986e-15) / (Pow(nanolambda, float(5.)) * (Exp(c / nanolambda) - float(1.)));
}


CML_API CMLMOBFunction* cmlCreateBlackBody(float temperature){
  CMLMOBFunction* function = cmlCreateFunction(cml_EvaluateBlackBody);
  *mobKeyFloat(function, cml_Key(CML_FUNCTION_MIN_NON_TRIVIAL_COORD)) = CML_SINGULARITY;
  *mobKeyFloat(function, cml_Key(CML_TEMPERATURE_K)) = temperature;
  cml_UpdateBlackBody(function);
  return function;
}





// //////////////////////////////////////////////
// CIE A illuminant
// //////////////////////////////////////////////

CML_HIDDEN float cml_EvaluateCIEAIlluminant(CMLMOBFunction* function, float x){
  CML_UNUSED(function);
  #ifndef NDEBUG
    if(x <= 0){cmlError("cml_EvaluateCIEAIlluminant", "CIE A illuminant is only defined for input values greater than 0.");}
  #endif
  float nanolambda = x * 1e-9f;
  // First constant is 100. * pow(560e-9.,5.);
  // Second constant is exp(1.435e-2 / (2848. * 560e-9)) - 1.;
  // third constant is c2 = (1.435e-2) / (2848.);
  // Note: 1.435e-2 is approximately NA_PLANCK*NA_LIGHT_SPEED_VAC/NA_BOLTZMANN
  // 1.435e7 appears to be the standard used.
  return (.5507317760e-31f / powf(nanolambda, 5.f)) * (8082.19209692894427103001499060f / (expf(.5038623596e-5f / nanolambda) - 1.f));
}


CML_API CMLMOBFunction* cmlCreateCIEAIlluminant(){
  CMLMOBFunction* function = cmlCreateFunction(cml_EvaluateCIEAIlluminant);
  *mobKeyFloat(function, cml_Key(CML_FUNCTION_MIN_NON_TRIVIAL_COORD)) = CML_SINGULARITY;
  return function;
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

CML_HIDDEN CML_INLINE void CMLInternalComputeDIlluminantWhite(float* white, float temp){
  if(temp < 4000.f){temp = 4000.f;}
  if(temp > 25000.f){temp = 25000.f;}
  
  if(temp <= 7000.f){
    white[0] = ((-4.607e9f / temp + 2.9678e6f) / temp + 0.09911e3f) / temp + 0.244063f;
  }else{
    white[0] = ((-2.0064e9f / temp + 1.9018e6f) / temp + 0.24748e3f) / temp + 0.23704f;
  }
  white[1] = -3.f * white[0] * white[0] + 2.87f * white[0] - 0.275f;
}

// todo make temperature a parameter

CML_API CMLMOBFunction* cmlCreateCIEDIlluminant(float temperature){
  float Minv;
  float M1;
  float M2;
  CMLuint32 l;
  float* array;
  float white[2];
  #ifndef NDEBUG
    if(temperature <= 0){cmlError("cmlCreateCIEDIlluminant", "Temperature must be greater than 0 Kelvin.");}
  #endif
  // Note that the array will be deleted by the CMLArray.
  array = (float*)naMalloc(CML_D_ILLUMINANT_ENTRYCOUNT * sizeof(float));
  CMLInternalComputeDIlluminantWhite(white, temperature);
  Minv = cmlInverse(0.0241f +  0.2562f * white[0] -  0.7341f * white[1]);
  M1 = (-1.3515f -  1.7703f * white[0] +  5.9114f * white[1]) * Minv;
  M2 = ( 0.03f   - 31.4424f * white[0] + 30.0717f * white[1]) * Minv;
  for(l=0; l<CML_D_ILLUMINANT_ENTRYCOUNT; ++l){
    array[l] = dilluminantS0[l] + M1*dilluminantS1[l] + M2*dilluminantS2[l];
  }
  // Multiple sources suggest that the values are considered to be linearly
  // interpolated.
  return cmlCreateMutableArrayFunction(array, CML_TRUE, CML_D_ILLUMINANT_ENTRYCOUNT, CML_D_ILLUMINANT_MIN, CML_D_ILLUMINANT_MAX, CML_INTERPOLATION_LINEAR, CML_EXTRAPOLATION_LINEAR_ZERO, CML_EXTRAPOLATION_LINEAR_ZERO);
}









// //////////////////////////////////////////////
// Linear Response
// //////////////////////////////////////////////

CML_HIDDEN float cml_EvaluateLinearResponse(CMLMOBFunction* function, float x){
  CML_UNUSED(function);
  return x;
}


CML_API CMLMOBFunction* cmlCreateLinearResponse(){
  return cmlCreateFunction(cml_EvaluateLinearResponse);
}






// //////////////////////////////////////////////
// Gamma Response
// //////////////////////////////////////////////

CML_HIDDEN float cml_EvaluateGammaResponse(CMLMOBFunction* function, float x){
  float gamma = *mobKeyFloat(function, cml_Key(CML_GAMMA));
  if(x < 0.f){
    return -powf(-x, gamma);
  }else{
    return powf(x, gamma);
  }
}

CML_API CMLMOBFunction* cmlCreateGammaResponse(float gamma){
  CMLMOBFunction* function = cmlCreateFunction(cml_EvaluateGammaResponse);
  *mobKeyFloat(function, cml_Key(CML_GAMMA)) = gamma;
  return function;
}





// //////////////////////////////////////////////
// Linear Gamma Response
// //////////////////////////////////////////////


CML_HIDDEN void cml_UpdateGammaLinearResponse(CMLMOBFunction* function){
  float gamma = *mobKeyFloat(function, cml_Key(CML_GAMMA));
  *mobKeyFloat(function, cml_Key(CML_INV_GAMMA)) = cmlInverse(gamma);
  float linscale = *mobKeyFloat(function, cml_Key(CML_LINEAR_SCALE));
  *mobKeyFloat(function, cml_Key(CML_CURVE_SCALE)) = linscale + 1.f;
}


CML_HIDDEN float cml_EvaluateGammaLinearResponse(CMLMOBFunction* function, float x){
  float split = *mobKeyFloat(function, cml_Key(CML_LINEAR_CURVE_SPLIT));
  float linscale = *mobKeyFloat(function, cml_Key(CML_LINEAR_SCALE));
  float curvescale = *mobKeyFloat(function, cml_Key(CML_CURVE_SCALE));
  float invgamma = *mobKeyFloat(function, cml_Key(CML_INV_GAMMA));
  float offset = *mobKeyFloat(function, cml_Key(CML_CURVE_OFFSET));
  if(x > split){
    return curvescale * powf(x, invgamma) - offset;
  }else{
    return linscale * x;
  }
}


CML_API CMLMOBFunction* cmlCreateGammaLinearResponse(float gamma, float offset, float linscale, float split){
  CMLMOBFunction* function = cmlCreateFunction(cml_EvaluateGammaLinearResponse);
  *mobKeyFloat(function, cml_Key(CML_GAMMA)) = gamma;
  *mobKeyFloat(function, cml_Key(CML_CURVE_OFFSET)) = offset;
  *mobKeyFloat(function, cml_Key(CML_LINEAR_SCALE)) = linscale;
  *mobKeyFloat(function, cml_Key(CML_LINEAR_CURVE_SPLIT)) = split;
  cml_UpdateGammaLinearResponse(function);
  return function;
}




// //////////////////////////////////////////////
// Inverse Linear Gamma Response
// //////////////////////////////////////////////


CML_HIDDEN void cml_UpdateInverseGammaLinearResponse(CMLMOBFunction* function){
  float linscale = *mobKeyFloat(function, cml_Key(CML_LINEAR_SCALE));
  *mobKeyFloat(function, cml_Key(CML_INV_LINEAR_SCALE)) = cmlInverse(linscale);
  *mobKeyFloat(function, cml_Key(CML_INV_CURVE_SCALE)) = cmlInverse(linscale + 1.f);
  float split = *mobKeyFloat(function, cml_Key(CML_LINEAR_CURVE_SPLIT));
  *mobKeyFloat(function, cml_Key(CML_INV_LINEAR_CURVE_SPLIT)) = linscale * split;
}


CML_HIDDEN float cml_EvaluateInverseGammaLinearResponse(CMLMOBFunction* function, float x){
  float invsplit = *mobKeyFloat(function, cml_Key(CML_INV_LINEAR_CURVE_SPLIT));
  float invlinscale = *mobKeyFloat(function, cml_Key(CML_INV_LINEAR_SCALE));
  float invcurvescale = *mobKeyFloat(function, cml_Key(CML_INV_CURVE_SCALE));
  float gamma = *mobKeyFloat(function, cml_Key(CML_GAMMA));
  float offset = *mobKeyFloat(function, cml_Key(CML_CURVE_OFFSET));
  if(x > invsplit){
    return powf((x + offset) * invcurvescale, gamma);
  }else{
    return invlinscale * x;
  }
}


CML_API CMLMOBFunction* cmlCreateInverseGammaLinearResponse(float gamma, float offset, float linscale, float split){
  CMLMOBFunction* function = cmlCreateFunction(cml_EvaluateInverseGammaLinearResponse);
  *mobKeyFloat(function, cml_Key(CML_GAMMA)) = gamma;
  *mobKeyFloat(function, cml_Key(CML_CURVE_OFFSET)) = offset;
  *mobKeyFloat(function, cml_Key(CML_LINEAR_SCALE)) = linscale;
  *mobKeyFloat(function, cml_Key(CML_LINEAR_CURVE_SPLIT)) = split;
  cml_UpdateInverseGammaLinearResponse(function);
  return function;
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


CML_HIDDEN float cml_EvaluatesRGBToXYZResponse(CMLMOBFunction* function, float x){
  CML_UNUSED(function);
  if(x > CML_LIN_SRGB_SWITCH){
    return powf((x + CML_SRGB_OFFSET) * CML_SRGB_INV_SCALE, CML_SRGB_GAMMA);
  }else if(x < -CML_LIN_SRGB_SWITCH){
    return -powf((-x + CML_SRGB_OFFSET) * CML_SRGB_INV_SCALE, CML_SRGB_GAMMA);
  }else{
    return x * CML_SRGB_LIN_INV_SCALE;
  }
}


CML_API CMLMOBFunction* cmlCreatesRGBToXYZResponse(){
  CMLMOBFunction* function = cmlCreateFunction(cml_EvaluatesRGBToXYZResponse);
  return function;
}






// //////////////////////////////////////////////
// XYZ -> sRGB Response
// //////////////////////////////////////////////


CML_HIDDEN float cml_EvaluateXYZTosRGBResponse(CMLMOBFunction* function, float x){
  CML_UNUSED(function);
  if(x > CML_SRGB_LIN_SWITCH){
    return (CML_SRGB_SCALE * powf(x, CML_SRGB_INV_GAMMA) - CML_SRGB_OFFSET);
  }else if(x < -CML_SRGB_LIN_SWITCH){
    return -(CML_SRGB_SCALE * powf(-x, CML_SRGB_INV_GAMMA) - CML_SRGB_OFFSET);
  }else{
    return (x * CML_SRGB_LIN_SCALE);
  }
}


CML_API CMLMOBFunction* cmlCreateXYZTosRGBResponse(){
  CMLMOBFunction* function = cmlCreateFunction(cml_EvaluateXYZTosRGBResponse);
  return function;
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


CML_HIDDEN float cml_EvaluateYToLStarResponse(CMLMOBFunction* function, float x){
  CML_UNUSED(function);
  if(x > CML_LIN_LSTAR_SWITCH){
    return cml_fytoLr(CMLCbrt(x));
  }else{
    return x * CML_LSTAR_LINEAR_SCALE;
  }
}

CML_API CMLMOBFunction* cmlCreateYToLStarResponse(){
  CMLMOBFunction* function = cmlCreateFunction(cml_EvaluateYToLStarResponse);
  return function;
}







// //////////////////////////////////////////////
// L Star -> Y Response
// //////////////////////////////////////////////


CML_HIDDEN float cml_EvaluateLStarToYResponse(CMLMOBFunction* function, float x){
  CML_UNUSED(function);
  if(x > CML_LSTAR_LIN_SWITCH){
    float fy = cml_Lrtofy(x);
    return fy*fy*fy;
  }else{
    return x * CML_LSTAR_LINEAR_INV_SCALE;
  }
}

CML_API CMLMOBFunction* cmlCreateLStarToYResponse(){
  CMLMOBFunction* function = cmlCreateFunction(cml_EvaluateLStarToYResponse);
  return function;
}







// //////////////////////////////////////////////
// Linear -> L Star Standard Response
// //////////////////////////////////////////////


CML_HIDDEN float cml_EvaluateYToLStarStandardResponse(CMLMOBFunction* function, float x){
  CML_UNUSED(function);
  if(x > CML_LIN_LSTAR_SWITCH_STANDARD){
    return cml_fytoLr(CMLCbrt(x));
  }else{
    return x * CML_LSTAR_LINEAR_SCALE_STANDARD;
  }
}


CML_API CMLMOBFunction* cmlCreateYToLStarStandardResponse(){
  CMLMOBFunction* function = cmlCreateFunction(cml_EvaluateYToLStarStandardResponse);
  return function;
}





// //////////////////////////////////////////////
// L Star -> Linear Response
// //////////////////////////////////////////////

CML_HIDDEN float cml_EvaluateLStarToYStandardResponse(CMLMOBFunction* function, float x){
  CML_UNUSED(function);
  if(x > CML_LSTAR_LIN_SWITCH_STANDARD){
    float fy = cml_Lrtofy(x);
    return fy*fy*fy;
  }else{
    return x * CML_LSTAR_LINEAR_INV_SCALE_STANDARD;
  }
}


CML_API CMLMOBFunction* cmlCreateLStarToYStandardResponse(){
  CMLMOBFunction* function = cmlCreateFunction(cml_EvaluateLStarToYStandardResponse);
  return function;
}






// //////////////////////////////////////////////
// Dirac Filter
// //////////////////////////////////////////////


CML_HIDDEN float cml_EvaluateDiracFilter(CMLMOBFunction* function, float x){
  float wavelength = *mobKeyFloat(function, cml_Key(CML_FUNCTION_MIN_NON_TRIVIAL_COORD));
  return (x == wavelength) ? 1.f: 0.f;
}


CML_API CMLMOBFunction* cmlCreateDiracFilter(float wavelength){
  CMLMOBFunction* function = cmlCreateFunction(cml_EvaluateDiracFilter);
  *mobKeyFloat(function, cml_Key(CML_FUNCTION_MIN_SAMPLE_COORD)) = wavelength;
  *mobKeyFloat(function, cml_Key(CML_FUNCTION_MAX_SAMPLE_COORD)) = wavelength;
  *mobKeyFloat(function, cml_Key(CML_FUNCTION_MIN_NON_TRIVIAL_COORD)) = wavelength;
  *mobKeyFloat(function, cml_Key(CML_FUNCTION_MAX_NON_TRIVIAL_COORD)) = wavelength;
  return function;
}






// //////////////////////////////////////////////
// Constant Filter
// //////////////////////////////////////////////

CML_HIDDEN float cml_EvaluateConstFilter(CMLMOBFunction* function, float x){
  CML_UNUSED(function);
  CML_UNUSED(x);
  return *mobKeyFloat(function, cml_Key(CML_CONST_VALUE));
}


CML_API CMLMOBFunction* cmlCreateConstFilter(float value){
  CMLMOBFunction* function = cmlCreateFunction(cml_EvaluateConstFilter);
  *mobKeyFloat(function, cml_Key(CML_CONST_VALUE)) = value;
  return function;
}






// //////////////////////////////////////////////
// Cut Filter
// //////////////////////////////////////////////

CML_HIDDEN float cml_EvaluateCutFilter(CMLMOBFunction* function, float x){
  CML_UNUSED(function);
  float min = *mobKeyFloat(function, cml_Key(CML_FUNCTION_MIN_NON_TRIVIAL_COORD));
  float max = *mobKeyFloat(function, cml_Key(CML_FUNCTION_MAX_NON_TRIVIAL_COORD));
  return ((x < min) || (x > max)) ? 0.f : 1.f;
}


CML_API CMLMOBFunction* cmlCreateCutFilter(float min, float max){
  CMLMOBFunction* function = cmlCreateFunction(cml_EvaluateCutFilter);
  *mobKeyFloat(function, cml_Key(CML_FUNCTION_MIN_NON_TRIVIAL_COORD)) = min;
  *mobKeyFloat(function, cml_Key(CML_FUNCTION_MAX_NON_TRIVIAL_COORD)) = max;
  return function;
}




// //////////////////////////////////////////////
// Binomial Filter
// //////////////////////////////////////////////


CML_HIDDEN void cml_UpdateBinomialFilter(CMLMOBFunction* function){
  float n = *mobKeyFloat(function, cml_Key(CML_BINOMIAL_VALUE_n));
  float k = *mobKeyFloat(function, cml_Key(CML_BINOMIAL_VALUE_k));
  float minx = *mobKeyFloat(function, cml_Key(CML_FUNCTION_MIN_NON_TRIVIAL_COORD));
  float maxx = *mobKeyFloat(function, cml_Key(CML_FUNCTION_MAX_NON_TRIVIAL_COORD));
  *mobKeyFloat(function, cml_Key(CML_BINOMIAL_INV_RANGE)) = cmlInverse(maxx - minx);
  *mobKeyFloat(function, cml_Key(CML_BINOMIAL_n_MINUS_k)) = n - k;
  *mobKeyFloat(function, cml_Key(CML_BINOMIAL_BINOM)) = naBinom(n, k);
}

CML_HIDDEN float cml_EvaluateBinomialFilter(CMLMOBFunction* function, float x){
  float minx = *mobKeyFloat(function, cml_Key(CML_FUNCTION_MIN_NON_TRIVIAL_COORD));
  float invrange = *mobKeyFloat(function, cml_Key(CML_BINOMIAL_INV_RANGE));
  float k = *mobKeyFloat(function, cml_Key(CML_BINOMIAL_VALUE_k));
  float nminusk = *mobKeyFloat(function, cml_Key(CML_BINOMIAL_n_MINUS_k));
  float binom = *mobKeyFloat(function, cml_Key(CML_BINOMIAL_BINOM));
  float normx = (x - minx) * invrange;
  return binom * powf(normx, k) * powf(1.f - normx, nminusk);
}

CML_API CMLMOBFunction* cmlCreateBinomialFilter(float minx, float maxx, CMLInt n, CMLInt k){
  CMLMOBFunction* function = cmlCreateFunction(cml_EvaluateBinomialFilter);
  *mobKeyFloat(function, cml_Key(CML_BINOMIAL_VALUE_n)) = n;
  *mobKeyFloat(function, cml_Key(CML_BINOMIAL_VALUE_k)) = k;
  *mobKeyFloat(function, cml_Key(CML_FUNCTION_MIN_NON_TRIVIAL_COORD)) = minx;
  *mobKeyFloat(function, cml_Key(CML_FUNCTION_MAX_NON_TRIVIAL_COORD)) = maxx;
  *mobKeyFloat(function, cml_Key(CML_FUNCTION_MIN_SAMPLE_COORD)) = minx;
  *mobKeyFloat(function, cml_Key(CML_FUNCTION_MAX_SAMPLE_COORD)) = maxx;
  cml_UpdateBinomialFilter(function);
  return function;
}



// //////////////////////////////////////////////
// Gauss Filter
// //////////////////////////////////////////////


CML_HIDDEN void cml_UpdateGaussFilter(CMLMOBFunction* function){
  float sigma = *mobKeyFloat(function, cml_Key(CML_GAUSS_VALUE_sigma));
  *mobKeyFloat(function, cml_Key(CML_GAUSS_VALUE_invsigma)) = cmlInverse(sigma);
}

CML_HIDDEN float cml_EvaluateGaussFilter(CMLMOBFunction* function, float x){
  float mu = *mobKeyFloat(function, cml_Key(CML_GAUSS_VALUE_mu));
  float sigma = *mobKeyFloat(function, cml_Key(CML_GAUSS_VALUE_sigma));
  float invsigma = *mobKeyFloat(function, cml_Key(CML_GAUSS_VALUE_invsigma));
  float powfactor = (x - mu) * invsigma;
  return cmlInverse(sigma * NA_SQRTPI2f) * naExpf(-.5f * powfactor * powfactor);
}


CML_API CMLMOBFunction* cmlCreateGaussFilter(float mu, float sigma){
  CMLMOBFunction* function = cmlCreateFunction(cml_EvaluateGaussFilter);
  *mobKeyFloat(function, cml_Key(CML_GAUSS_VALUE_mu)) = mu;
  *mobKeyFloat(function, cml_Key(CML_GAUSS_VALUE_sigma)) = sigma;
  cml_UpdateGaussFilter(function);
  return function;
}







// //////////////////////////////////////////////
// Function add Function
// //////////////////////////////////////////////


CML_HIDDEN void cml_UpdateFunctionAddFunction(CMLMOBFunction* function){
  CMLMOBFunction* func1 = mobGetKeyObject(function, cml_Key(CML_COMPOSITE_FUNCTION_1));
  CMLMOBFunction* func2 = mobGetKeyObject(function, cml_Key(CML_COMPOSITE_FUNCTION_2));
  CMLDefinitionRange defrange = cmlGetDefinitionRangeOf2Functions(func1, func2, CML_FALSE);
  cmlSetFunctionDefinitionRange(function, &defrange);
}

CML_HIDDEN float cml_EvaluateFunctionAddFunction(CMLMOBFunction* function, float x){
  CMLMOBFunction* func1 = mobGetKeyObject(function, cml_Key(CML_COMPOSITE_FUNCTION_1));
  CMLMOBFunction* func2 = mobGetKeyObject(function, cml_Key(CML_COMPOSITE_FUNCTION_2));
  return cml_Eval(func1, x) + cml_Eval(func2, x);
}

CML_API CMLMOBFunction* cmlCreateFunctionAddFunction(CMLMOBFunction* func1, CMLMOBFunction* func2){
  CMLMOBFunction* function = cmlCreateFunction(cml_EvaluateFunctionAddFunction);
  mobSetKeyObject(function, cml_Key(CML_COMPOSITE_FUNCTION_1), func1, MOB_FALSE);
  mobSetKeyObject(function, cml_Key(CML_COMPOSITE_FUNCTION_2), func2, MOB_FALSE);
  cml_UpdateFunctionAddFunction(function);
  return function;
}






// //////////////////////////////////////////////
// Function sub Function
// //////////////////////////////////////////////

CML_HIDDEN void cml_UpdateFunctionSubFunction(CMLMOBFunction* function){
  CMLMOBFunction* func1 = mobGetKeyObject(function, cml_Key(CML_COMPOSITE_FUNCTION_1));
  CMLMOBFunction* func2 = mobGetKeyObject(function, cml_Key(CML_COMPOSITE_FUNCTION_2));
  CMLDefinitionRange defrange = cmlGetDefinitionRangeOf2Functions(func1, func2, CML_FALSE);
  cmlSetFunctionDefinitionRange(function, &defrange);
}

CML_HIDDEN float cml_EvaluateFunctionSubFunction(CMLMOBFunction* function, float x){
  CMLMOBFunction* func1 = mobGetKeyObject(function, cml_Key(CML_COMPOSITE_FUNCTION_1));
  CMLMOBFunction* func2 = mobGetKeyObject(function, cml_Key(CML_COMPOSITE_FUNCTION_2));
  return cml_Eval(func1, x) - cml_Eval(func2, x);
}

CML_API CMLMOBFunction* cmlCreateFunctionSubFunction(CMLMOBFunction* func1, CMLMOBFunction* func2){
  CMLMOBFunction* function = cmlCreateFunction(cml_EvaluateFunctionSubFunction);
  mobSetKeyObject(function, cml_Key(CML_COMPOSITE_FUNCTION_1), func1, MOB_FALSE);
  mobSetKeyObject(function, cml_Key(CML_COMPOSITE_FUNCTION_2), func2, MOB_FALSE);
  cml_UpdateFunctionSubFunction(function);
  return function;
}






// //////////////////////////////////////////////
// Function mul Function
// //////////////////////////////////////////////

CML_HIDDEN void cml_UpdateFunctionMulFunction(CMLMOBFunction* function){
  CMLMOBFunction* func1 = mobGetKeyObject(function, cml_Key(CML_COMPOSITE_FUNCTION_1));
  CMLMOBFunction* func2 = mobGetKeyObject(function, cml_Key(CML_COMPOSITE_FUNCTION_2));
  CMLDefinitionRange defrange = cmlGetDefinitionRangeOf2Functions(func1, func2, CML_TRUE);
  cmlSetFunctionDefinitionRange(function, &defrange);
}

CML_HIDDEN float cml_EvaluateFunctionMulFunction(CMLMOBFunction* function, float x){
  CMLMOBFunction* func1 = mobGetKeyObject(function, cml_Key(CML_COMPOSITE_FUNCTION_1));
  CMLMOBFunction* func2 = mobGetKeyObject(function, cml_Key(CML_COMPOSITE_FUNCTION_2));
  return cml_Eval(func1, x) * cml_Eval(func2, x);
}

CML_API CMLMOBFunction* cmlCreateFunctionMulFunction(CMLMOBFunction* func1, CMLMOBFunction* func2){
  CMLMOBFunction* function = cmlCreateFunction(cml_EvaluateFunctionMulFunction);
  mobSetKeyObject(function, cml_Key(CML_COMPOSITE_FUNCTION_1), func1, MOB_FALSE);
  mobSetKeyObject(function, cml_Key(CML_COMPOSITE_FUNCTION_2), func2, MOB_FALSE);
  cml_UpdateFunctionMulFunction(function);
  return function;
}








// //////////////////////////////////////////////
// Function div Function
// //////////////////////////////////////////////

CML_HIDDEN void cml_UpdateFunctionDivFunction(CMLMOBFunction* function){
  CMLMOBFunction* func1 = mobGetKeyObject(function, cml_Key(CML_COMPOSITE_FUNCTION_1));
  CMLMOBFunction* func2 = mobGetKeyObject(function, cml_Key(CML_COMPOSITE_FUNCTION_2));
  CMLDefinitionRange defrange = cmlGetDefinitionRangeOf2Functions(func1, func2, CML_TRUE);
  cmlSetFunctionDefinitionRange(function, &defrange);
}

CML_HIDDEN float cml_EvaluateFunctionDivFunction(CMLMOBFunction* function, float x){
  CMLMOBFunction* func1 = mobGetKeyObject(function, cml_Key(CML_COMPOSITE_FUNCTION_1));
  CMLMOBFunction* func2 = mobGetKeyObject(function, cml_Key(CML_COMPOSITE_FUNCTION_2));
  return cml_Eval(func1, x) / cml_Eval(func2, x);
}

CML_API CMLMOBFunction* cmlCreateFunctionDivFunction(CMLMOBFunction* func1, CMLMOBFunction* func2){
  CMLMOBFunction* function = cmlCreateFunction(cml_EvaluateFunctionDivFunction);
  mobSetKeyObject(function, cml_Key(CML_COMPOSITE_FUNCTION_1), func1, MOB_FALSE);
  mobSetKeyObject(function, cml_Key(CML_COMPOSITE_FUNCTION_2), func2, MOB_FALSE);
  cml_UpdateFunctionDivFunction(function);
  return function;
}






// //////////////////////////////////////////////
// Function mul Scalar
// //////////////////////////////////////////////

CML_HIDDEN float cml_EvaluateFunctionMulScalar(CMLMOBFunction* function, float x){
  CMLMOBFunction* func1 = mobGetKeyObject(function, cml_Key(CML_COMPOSITE_FUNCTION_1));
  float factor2 = *mobKeyFloat(function, cml_Key(CML_COMPOSITE_FACTOR_2));
  return cml_Eval(func1, x) * factor2;
}

CML_API CMLMOBFunction* cmlCreateFunctionMulScalar(CMLMOBFunction* func1, float scalar){
  CMLMOBFunction* function = cmlCreateFunction(cml_EvaluateFunctionMulScalar);
  mobSetKeyObject(function, cml_Key(CML_COMPOSITE_FUNCTION_1), func1, MOB_FALSE);
  *mobKeyFloat(function, cml_Key(CML_COMPOSITE_FACTOR_2)) = scalar;
  return function;
}


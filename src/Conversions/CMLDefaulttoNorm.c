
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

#include "CML.h"
#include "CMLInternal.h"


//CML_INLINE void cml_OneUnnormed(float* CML_RESTRICT outptr, const float* CML_RESTRICT inptr){
//  *outptr = *inptr;
//}


CML_INLINE void cml_OneFloatDefaulttoNorm(float* CML_RESTRICT outptr, const float* CML_RESTRICT inptr, float offset, float invrange){
  *outptr = (*inptr - offset) * invrange;
}


CML_INLINE void cml_OneFloatNormtoDefault(float* CML_RESTRICT outptr, const float* CML_RESTRICT inptr, float offset, float range){
  *outptr = offset + *inptr * range;
}



CML_HIDDEN void cml_DefaulttoNorm (CMLOutput out , CMLInput in, CMLSize count){
  float* outptr = (float*)out;
  const float* inptr = (const float*)in;

  MOB* offsets = (MOB*)cmlGetConverterSetting(CML_SETTING_COMPONENTS_OFFSETS, CML_GET_CONVERT);
  MOB* ranges = (MOB*)cmlGetConverterSetting(CML_SETTING_COMPONENTS_RANGES, CML_GET_CONVERT);
  if(cmlGetConverterError()){return;}

  CMLInt componentscount = (CMLInt)mobArrayCount(offsets);
  float* offset = naMalloc(naSizeof(float) * componentscount);
  float* invrange = naMalloc(naSizeof(float) * componentscount);
  NABool needsnorming = CML_FALSE;
  for(CMLInt c=0; c<componentscount; c++){
    offset[c] = *mobArrayFloat(offsets, c);
    if(offset[c] != 0.f){needsnorming = CML_TRUE;}
    invrange[c] = cmlInverse(*mobArrayFloat(ranges, c));
    if(invrange[c] != 1.f){needsnorming = CML_TRUE;}
  }

  if(needsnorming){
    while(count){
      for(CMLInt c=0; c<componentscount; c++){
        cml_OneFloatDefaulttoNorm(outptr, inptr, offset[c], invrange[c]);
        outptr++;
        inptr++;
      }
      count--;
    }
  }else{
    CMLInt storagesize = sizeof(void*); // todo!
    naCopyn(outptr, inptr, storagesize * count);
  }
  
}



CML_HIDDEN void cml_NormtoDefault(CMLOutput out, CMLInput in, CMLSize count){
  float* outptr = (float*)out;
  const float* inptr = (const float*)in;

  MOB* offsets = (MOB*)cmlGetConverterSetting(CML_SETTING_COMPONENTS_OFFSETS, CML_GET_CONVERT);
  MOB* ranges = (MOB*)cmlGetConverterSetting(CML_SETTING_COMPONENTS_RANGES, CML_GET_CONVERT);
  if(cmlGetConverterError()){return;}

  CMLInt componentscount = (CMLInt)mobArrayCount(offsets);
  float* offset = naMalloc(sizeof(float) * componentscount);
  float* range = naMalloc(sizeof(float) * componentscount);
  NABool needsnorming = CML_FALSE;
  for(CMLInt c=0; c<componentscount; c++){
    offset[c] = *mobArrayFloat(offsets, c);
    if(offset[c] != 0.f){needsnorming = CML_TRUE;}
    range[c] = *mobArrayFloat(ranges, c);
    if(range[c] != 1.f){needsnorming = CML_TRUE;}
  }

  if(needsnorming){
    while(count){
      for(CMLInt c=0; c<componentscount; c++){
        cml_OneFloatNormtoDefault(outptr, inptr, offset[c], range[c]);
        outptr++;
        inptr++;
      }
      count--;
    }
  }else{
    CMLInt storagesize = sizeof(void*); // todo!
    naCopyn(outptr, inptr, storagesize * count);
  }
  
}





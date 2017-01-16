
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

#include "CML.h"
#include "CMLInternal.h"


#define CMLINTERNALLabToLch(Lch0, Lch1, Lch2, Lab0, Lab1, Lab2) \
  *Lch0 = *Lab0;\
  float length = cmlLength2(&(*Lab1));\
  if(length == 0.f){\
    *Lch2 = 0.f;\
  }else{\
    *Lch2 = naRadToDegf(atan2f(*Lab2, *Lab1));\
    if(*Lch2 < 0.f){*Lch2 += 360.f;}\
  }\
  *Lch1 = length;



CML_HIDDEN CML_INLINE void cml_OneLabToLch (float* CML_RESTRICT Lch0, float* CML_RESTRICT Lch1, float* CML_RESTRICT Lch2, const float* CML_RESTRICT Lab0, const float* CML_RESTRICT Lab1, const float* CML_RESTRICT Lab2){
  CMLINTERNALLabToLch(Lch0, Lch1, Lch2, Lab0, Lab1, Lab2);
}

CML_HIDDEN CML_INLINE void cml_OneLabToLch_SB(float* CML_RESTRICT buf0, float* CML_RESTRICT buf1, float* CML_RESTRICT buf2){
  CMLINTERNALLabToLch(buf0, buf1, buf2, buf0, buf1, buf2);
}


CML_HIDDEN void cml_LabToLch (CMLOutput out , CMLInput in, CMLSize count){
  if(cmlGetConverterError()){return;}

  while(count){
    const float* Lab0 = cmlNextConstFloatComponent(in);
    const float* Lab1 = cmlNextConstFloatComponent(in);
    const float* Lab2 = cmlNextConstFloatComponent(in);
    float* Lch0 = cmlNextMutableFloatComponent(out);
    float* Lch1 = cmlNextMutableFloatComponent(out);
    float* Lch2 = cmlNextMutableFloatComponent(out);

    cml_OneLabToLch(Lch0, Lch1, Lch2, Lab0, Lab1, Lab2);

    count--;
  }
  
}

CML_HIDDEN void cml_LabToLch_SB(CMLInputOutput buf, CMLSize count){
  if(cmlGetConverterError()){return;}
  
  while(count){
    float* buf0 = cmlNextMutableFloatComponent(buf);
    float* buf1 = cmlNextMutableFloatComponent(buf);
    float* buf2 = cmlNextMutableFloatComponent(buf);

    cml_OneLabToLch_SB(buf0, buf1, buf2);

    count--;
  }
  
}








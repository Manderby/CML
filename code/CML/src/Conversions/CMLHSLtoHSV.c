
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

#include "../CML.h"
#include "../StateMachine/CMLInternal.h"


#define CMLINTERNALHSLToHSV(HSV0, HSV1, HSV2, HSL0, HSL1, HSL2) \
  *HSV0 = *HSL0;\
  *HSV2 = *HSL2 + .5f * *HSL1;\
  if(*HSV2 == 0.f){\
    *HSV1 = *HSL1 / CML_SINGULARITY;\
  }else{\
    *HSV1 = *HSL1 / *HSV2;\
  }



CML_HIDDEN CML_INLINE void cml_OneHSLToHSV (float* CML_RESTRICT HSV0, float* CML_RESTRICT HSV1, float* CML_RESTRICT HSV2, const float* CML_RESTRICT HSL0, const float* CML_RESTRICT HSL1, const float* CML_RESTRICT HSL2){
  CMLINTERNALHSLToHSV(HSV0, HSV1, HSV2, HSL0, HSL1, HSL2);
}

CML_HIDDEN CML_INLINE void cml_OneHSLToHSV_SB(float* CML_RESTRICT buf0, float* CML_RESTRICT buf1, float* CML_RESTRICT buf2){
  CMLINTERNALHSLToHSV(buf0, buf1, buf2, buf0, buf1, buf2);
}



CML_HIDDEN void cml_HSLToHSV (CMLOutput out , CMLInput in, CMLSize count){
  if(cmlGetConverterError()){return;}

  while(count){
    const float* Lab0 = cmlNextConstFloatComponent(in);
    const float* Lab1 = cmlNextConstFloatComponent(in);
    const float* Lab2 = cmlNextConstFloatComponent(in);
    float* Lch0 = cmlNextMutableFloatComponent(out);
    float* Lch1 = cmlNextMutableFloatComponent(out);
    float* Lch2 = cmlNextMutableFloatComponent(out);

    cml_OneHSLToHSV(Lch0, Lch1, Lch2, Lab0, Lab1, Lab2);

    count--;
  }
  
}

CML_HIDDEN void cml_HSLToHSV_SB(CMLInputOutput buf, CMLSize count){
  if(cmlGetConverterError()){return;}

  while(count){
    float* buf0 = cmlNextMutableFloatComponent(buf);
    float* buf1 = cmlNextMutableFloatComponent(buf);
    float* buf2 = cmlNextMutableFloatComponent(buf);

    cml_OneHSLToHSV_SB(buf0, buf1, buf2);

    count--;
  }
  
}








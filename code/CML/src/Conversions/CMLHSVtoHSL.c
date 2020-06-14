
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

#include "../CML.h"
#include "../StateMachine/CMLInternal.h"

#define CMLINTERNALHSVToHSL(HSL0, HSL1, HSL2, HSV0, HSV1, HSV2) \
  *HSL0 = *HSV0;\
  *HSL1 = *HSV1 * *HSV2;\
  *HSL2 = *HSV2 - 0.5f * *HSL1;



CML_HIDDEN CML_INLINE void cml_OneHSVToHSL (float* CML_RESTRICT HSL0, float* CML_RESTRICT HSL1, float* CML_RESTRICT HSL2, const float* CML_RESTRICT HSV0, const float* CML_RESTRICT HSV1, const float* CML_RESTRICT HSV2){
  CMLINTERNALHSVToHSL(HSL0, HSL1, HSL2, HSV0, HSV1, HSV2);
}

CML_HIDDEN CML_INLINE void cml_OneHSVToHSL_SB(float* CML_RESTRICT buf0, float* CML_RESTRICT buf1, float* CML_RESTRICT buf2){
  CMLINTERNALHSVToHSL(buf0, buf1, buf2, buf0, buf1, buf2);
}


CML_HIDDEN void cml_HSVToHSL (CMLOutput out , CMLInput in, CMLSize count){
  if(cmlGetConverterError()){return;}

  while(count){
    const float* HSV0 = cmlNextConstFloatComponent(in);
    const float* HSV1 = cmlNextConstFloatComponent(in);
    const float* HSV2 = cmlNextConstFloatComponent(in);
    float* HSL0 = cmlNextMutableFloatComponent(out);
    float* HSL1 = cmlNextMutableFloatComponent(out);
    float* HSL2 = cmlNextMutableFloatComponent(out);

    cml_OneHSVToHSL(HSL0, HSL1, HSL2, HSV0, HSV1, HSV2);

    count--;
  }
  
}

CML_HIDDEN void cml_HSVToHSL_SB(CMLInputOutput buf, CMLSize count){
  if(cmlGetConverterError()){return;}

  while(count){
    float* buf0 = cmlNextMutableFloatComponent(buf);
    float* buf1 = cmlNextMutableFloatComponent(buf);
    float* buf2 = cmlNextMutableFloatComponent(buf);

    cml_OneHSVToHSL_SB(buf0, buf1, buf2);

    count--;
  }
  
}






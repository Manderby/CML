
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

#include "../CML.h"
#include "../StateMachine/CMLInternal.h"


#define CMLINTERNALLchToLab(Lab0, Lab1, Lab2, Lch0, Lch1, Lch2) \
  if(*Lch1 == 0.f){\
    *Lab2 = 0.f;\
    *Lab1 = 0.f;\
  }else{\
    float hue = naDegToRadf(*Lch2);\
    *Lab2 = sinf(hue) * *Lch1;\
    *Lab1 = cosf(hue) * *Lch1;\
  }\
  *Lab0 = *Lch0;



CML_HIDDEN CML_INLINE void cml_OneLchToLab (float* CML_RESTRICT Lab0, float* CML_RESTRICT Lab1, float* CML_RESTRICT Lab2, const float* CML_RESTRICT Lch0, const float* CML_RESTRICT Lch1, const float* CML_RESTRICT Lch2){
  CMLINTERNALLchToLab(Lab0, Lab1, Lab2, Lch0, Lch1, Lch2);
}

CML_HIDDEN CML_INLINE void cml_OneLchToLab_SB(float* CML_RESTRICT buf0, float* CML_RESTRICT buf1, float* CML_RESTRICT buf2){
  CMLINTERNALLchToLab(buf0, buf1, buf2, buf0, buf1, buf2);
}



CML_HIDDEN void cml_LchToLab (CMLOutput out , CMLInput in, CMLSize count){
  if(cmlGetConverterError()){return;}

  while(count){
    const float* Lab0 = cmlNextConstFloatComponent(in);
    const float* Lab1 = cmlNextConstFloatComponent(in);
    const float* Lab2 = cmlNextConstFloatComponent(in);
    float* Lch0 = cmlNextMutableFloatComponent(out);
    float* Lch1 = cmlNextMutableFloatComponent(out);
    float* Lch2 = cmlNextMutableFloatComponent(out);

    cml_OneLchToLab(Lch0, Lch1, Lch2, Lab0, Lab1, Lab2);

    count--;
  }
  
}

CML_HIDDEN void cml_LchToLab_SB(CMLInputOutput buf, CMLSize count){
  if(cmlGetConverterError()){return;}

  while(count){
    float* buf0 = cmlNextMutableFloatComponent(buf);
    float* buf1 = cmlNextMutableFloatComponent(buf);
    float* buf2 = cmlNextMutableFloatComponent(buf);

    cml_OneLchToLab_SB(buf0, buf1, buf2);

    count--;
  }

}




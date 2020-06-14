
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

#include "../CML.h"
#include "../StateMachine/CMLInternal.h"



// todo: Make it SB
#define CMLINTERNALHSVToRGB(RGB0, RGB1, RGB2, HSV0, HSV1, HSV2) \
  CMLVec3 HSV;\
  cmlSet3(HSV, *HSV0, *HSV1, *HSV2);\
  CMLint8 h0 = (CMLint8)floorf(HSV[0] / 60.f);\
  CMLuint8 h1 = (CMLuint8)((h0 % 6) + 6) % 6;\
  float f = (HSV[0] / 60.f) - h0;\
  float range = HSV[2] * HSV[1];\
  float min = HSV[2] - range;\
  float inc = f * range;\
  float dec = (1.f - f) * range;\
  inc += min;\
  dec += min;\
  switch(h1){\
  case 0: *RGB0 = HSV[2] ; *RGB1 = inc    ; *RGB2 = min    ; break;\
  case 1: *RGB0 = dec    ; *RGB1 = HSV[2] ; *RGB2 = min    ; break;\
  case 2: *RGB0 = min    ; *RGB1 = HSV[2] ; *RGB2 = inc    ; break;\
  case 3: *RGB0 = min    ; *RGB1 = dec    ; *RGB2 = HSV[2] ; break;\
  case 4: *RGB0 = inc    ; *RGB1 = min    ; *RGB2 = HSV[2] ; break;\
  case 5: *RGB0 = HSV[2] ; *RGB1 = min    ; *RGB2 = dec    ; break;\
  default:\
    *RGB0 = 0.f; *RGB1 = 0.f; *RGB2 = 0.f;\
  }



CML_HIDDEN CML_INLINE void cml_OneHSVToRGB (float* CML_RESTRICT RGB0, float* CML_RESTRICT RGB1, float* CML_RESTRICT RGB2, const float* CML_RESTRICT HSV0, const float* CML_RESTRICT HSV1, const float* CML_RESTRICT HSV2){
  CMLINTERNALHSVToRGB(RGB0, RGB1, RGB2, HSV0, HSV1, HSV2);
}

CML_HIDDEN CML_INLINE void cml_OneHSVToRGB_SB(float* CML_RESTRICT buf0, float* CML_RESTRICT buf1, float* CML_RESTRICT buf2){
  CMLINTERNALHSVToRGB(buf0, buf1, buf2, buf0, buf1, buf2);
}



CML_HIDDEN void cml_HSVToRGB (CMLOutput out , CMLInput in, CMLSize count){
  if(cmlGetConverterError()){return;}

  while(count){
    const float* HSV0 = cmlNextConstFloatComponent(in);
    const float* HSV1 = cmlNextConstFloatComponent(in);
    const float* HSV2 = cmlNextConstFloatComponent(in);
    float* RGB0 = cmlNextMutableFloatComponent(out);
    float* RGB1 = cmlNextMutableFloatComponent(out);
    float* RGB2 = cmlNextMutableFloatComponent(out);

    cml_OneHSVToRGB(RGB0, RGB1, RGB2, HSV0, HSV1, HSV2);

    count--;
  }

}

CML_HIDDEN void cml_HSVToRGB_SB(CMLInputOutput buf, CMLSize count){
  if(cmlGetConverterError()){return;}

  while(count){
    float* buf0 = cmlNextMutableFloatComponent(buf);
    float* buf1 = cmlNextMutableFloatComponent(buf);
    float* buf2 = cmlNextMutableFloatComponent(buf);

    cml_OneHSVToRGB_SB(buf0, buf1, buf2);

    count--;
  }

}







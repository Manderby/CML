
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

#include "../CML.h"
#include "../StateMachine/CMLInternal.h"



// todo: Make it SB
#define CMLINTERNALRGBToHSV(HSV0, HSV1, HSV2, RGB0, RGB1, RGB2) \
  float min;\
  float range;\
  CMLVec3 RGB;\
  cmlSet3(RGB, *RGB0, *RGB1, *RGB2);\
  if(RGB[0] < RGB[1]){min = RGB[0]; *HSV2 = RGB[1];}else{min = RGB[1]; *HSV2 = RGB[0];}\
  if(RGB[2] < min){min = RGB[2];}\
  if(RGB[2] > *HSV2){*HSV2 = RGB[2];}\
  range = *HSV2 - min;\
  if(*HSV2 == 0.f){\
    *HSV1 = 0.f;\
  }else{\
    *HSV1 = range / *HSV2;\
  }\
  if(CMLAlmostZero(range)){\
    *HSV0 = 0.f;\
  }else{\
    float invrange = cmlInverse(range);\
    if(*HSV2 == RGB[0])      {*HSV0 = 60.f * (0.f + (RGB[1]-RGB[2]) * invrange);}\
    else if(*HSV2 == RGB[1]) {*HSV0 = 60.f * (2.f + (RGB[2]-RGB[0]) * invrange);}\
    else                      {*HSV0 = 60.f * (4.f + (RGB[0]-RGB[1]) * invrange);}\
    if(*HSV0 < 0.f){*HSV0 += 360.f;}\
  }



CML_HIDDEN CML_INLINE void cml_OneRGBToHSV (float* CML_RESTRICT HSV0, float* CML_RESTRICT HSV1, float* CML_RESTRICT HSV2, const float* CML_RESTRICT RGB0, const float* CML_RESTRICT RGB1, const float* CML_RESTRICT RGB2){
  CMLINTERNALRGBToHSV(HSV0, HSV1, HSV2, RGB0, RGB1, RGB2);
}

CML_HIDDEN CML_INLINE void cml_OneRGBToHSV_SB(float* CML_RESTRICT buf0, float* CML_RESTRICT buf1, float* CML_RESTRICT buf2){
  CMLINTERNALRGBToHSV(buf0, buf1, buf2, buf0, buf1, buf2);
}




CML_HIDDEN void cml_RGBToHSV (CMLOutput out , CMLInput in, CMLSize count){
  if(cmlGetConverterError()){return;}

  while(count){
    const float* RGB0 = cmlNextConstFloatComponent(in);
    const float* RGB1 = cmlNextConstFloatComponent(in);
    const float* RGB2 = cmlNextConstFloatComponent(in);
    float* HSV0 = cmlNextMutableFloatComponent(out);
    float* HSV1 = cmlNextMutableFloatComponent(out);
    float* HSV2 = cmlNextMutableFloatComponent(out);

    cml_OneRGBToHSV(HSV0, HSV1, HSV2, RGB0, RGB1, RGB2);

    count--;
  }
  
}

CML_HIDDEN void cml_RGBToHSV_SB(CMLInputOutput buf, CMLSize count){
  if(cmlGetConverterError()){return;}

  while(count){
    float* buf0 = cmlNextMutableFloatComponent(buf);
    float* buf1 = cmlNextMutableFloatComponent(buf);
    float* buf2 = cmlNextMutableFloatComponent(buf);

    cml_OneRGBToHSV_SB(buf0, buf1, buf2);

    count--;
  }
  
}








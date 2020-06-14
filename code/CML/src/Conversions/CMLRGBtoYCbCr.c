
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

#include "../CML.h"
#include "../StateMachine/CMLInternal.h"



#define CMLINTERNALRGBToYCbCr(YCbCr0, YCbCr1, YCbCr2, RGB0, RGB1, RGB2, redprimaryYxy, blueprimaryYxy, inversewhiteXYZ) \
  float Kr = redprimaryYxy[0] * inversewhiteXYZ[1];\
  float Kb = blueprimaryYxy[0] * inversewhiteXYZ[1];\
  float Y = Kr * *RGB0 + (1.f - Kr - Kb) * *RGB1 + Kb * *RGB2;\
  *YCbCr1 = .5f * (*RGB2 - Y) / (1.f - Kb);\
  *YCbCr2 = .5f * (*RGB0 - Y) / (1.f - Kr);\
  *YCbCr0 = Y / inversewhiteXYZ[1];



CML_HIDDEN CML_INLINE void cml_OneRGBToYCbCr (float* CML_RESTRICT YCbCr0, float* CML_RESTRICT YCbCr1, float* CML_RESTRICT YCbCr2, const float* CML_RESTRICT RGB0, const float* CML_RESTRICT RGB1, const float* CML_RESTRICT RGB2, const CMLVec3 redprimaryYxy, const CMLVec3 blueprimaryYxy, const CMLVec3 inversewhiteXYZ){
  CMLINTERNALRGBToYCbCr(YCbCr0, YCbCr1, YCbCr2, RGB0, RGB1, RGB2, redprimaryYxy, blueprimaryYxy, inversewhiteXYZ);
}



CML_HIDDEN void cml_RGBToYCbCr (CMLOutput out , CMLInput in, CMLSize count){
  CMLMOBGenerator* generator = cmlGetConverterSetting(CML_SETTING_GENERATOR, CML_GET_EQU);
  if(cmlGetConverterError()){return;}

  const float* whiteInvXYZ = cmlGetGeneratorWhiteInvXYZRadiometric(generator);
  const float* redprimaryYxy = cmlGetGeneratorRedPrimaryYxyRadiometric(generator);
  const float* blueprimaryYxy = cmlGetGeneratorBluePrimaryYxyRadiometric(generator);

  while(count){
    const float* RGB0 = cmlNextConstFloatComponent(in);
    const float* RGB1 = cmlNextConstFloatComponent(in);
    const float* RGB2 = cmlNextConstFloatComponent(in);
    float* YCbCr0 = cmlNextMutableFloatComponent(out);
    float* YCbCr1 = cmlNextMutableFloatComponent(out);
    float* YCbCr2 = cmlNextMutableFloatComponent(out);

    cml_OneRGBToYCbCr(YCbCr0, YCbCr1, YCbCr2, RGB0, RGB1, RGB2, redprimaryYxy, blueprimaryYxy, whiteInvXYZ);

    count--;
  }

}




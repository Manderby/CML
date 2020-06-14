
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

#include "../CML.h"
#include "../StateMachine/CMLInternal.h"


#define CMLINTERNALYCbCrToRGB(RGB0, RGB1, RGB2, YCbCr0, YCbCr1, YCbCr2, redprimaryYxy, blueprimaryYxy, inversewhiteXYZ) \
  float Kr = redprimaryYxy[0] * inversewhiteXYZ[1];\
  float Kb = blueprimaryYxy[0] * inversewhiteXYZ[1];\
  float Y = *YCbCr0 * inversewhiteXYZ[1];\
  *RGB0 = 2.f * *YCbCr2 * (1.f - Kr) + Y;\
  *RGB2 = 2.f * *YCbCr1 * (1.f - Kb) + Y;\
  *RGB1 = (Y - Kr * *RGB0 - Kb * *RGB2) / (1.f - Kr - Kb);



CML_HIDDEN CML_INLINE void cml_OneYCbCrToRGB (float* CML_RESTRICT RGB0, float* CML_RESTRICT RGB1, float* CML_RESTRICT RGB2, const float* CML_RESTRICT YCbCr0, const float* CML_RESTRICT YCbCr1, const float* CML_RESTRICT YCbCr2, const CMLVec3 redprimaryYxy, const CMLVec3 blueprimaryYxy, const CMLVec3 inversewhiteXYZ){
  CMLINTERNALYCbCrToRGB(RGB0, RGB1, RGB2, YCbCr0, YCbCr1, YCbCr2, redprimaryYxy, blueprimaryYxy, inversewhiteXYZ);
}



CML_HIDDEN CML_INLINE void cml_OneYCbCrToRGB_SB (float* CML_RESTRICT buf0, float* CML_RESTRICT buf1, float* CML_RESTRICT buf2, const CMLVec3 redprimaryYxy, const CMLVec3 blueprimaryYxy, const CMLVec3 inversewhiteXYZ){
  CMLINTERNALYCbCrToRGB(buf0, buf1, buf2, buf0, buf1, buf2, redprimaryYxy, blueprimaryYxy, inversewhiteXYZ);
}



CML_HIDDEN void cml_YCbCrToRGB (CMLOutput out , CMLInput in, CMLSize count){
  CMLMOBGenerator* generator = cmlGetConverterSetting(CML_SETTING_GENERATOR, CML_GET_EQU);
  if(cmlGetConverterError()){return;}

  const float* whiteInvXYZ = cmlGetGeneratorWhiteInvXYZRadiometric(generator);
  const float* redprimaryYxy = cmlGetGeneratorRedPrimaryYxyRadiometric(generator);
  const float* blueprimaryYxy = cmlGetGeneratorBluePrimaryYxyRadiometric(generator);

  while(count){
    const float* YCbCr0 = cmlNextConstFloatComponent(in);
    const float* YCbCr1 = cmlNextConstFloatComponent(in);
    const float* YCbCr2 = cmlNextConstFloatComponent(in);
    float* RGB0 = cmlNextMutableFloatComponent(out);
    float* RGB1 = cmlNextMutableFloatComponent(out);
    float* RGB2 = cmlNextMutableFloatComponent(out);

    cml_OneYCbCrToRGB(RGB0, RGB1, RGB2, YCbCr0, YCbCr1, YCbCr2, redprimaryYxy, blueprimaryYxy, whiteInvXYZ);

    count--;
  }

}

CML_HIDDEN void cml_YCbCrToRGB_SB (CMLInputOutput buf, CMLSize count){
  CMLMOBGenerator* generator = cmlGetConverterSetting(CML_SETTING_GENERATOR, CML_GET_EQU);
  if(cmlGetConverterError()){return;}

  const float* whiteInvXYZ = cmlGetGeneratorWhiteInvXYZRadiometric(generator);
  const float* redprimaryYxy = cmlGetGeneratorRedPrimaryYxyRadiometric(generator);
  const float* blueprimaryYxy = cmlGetGeneratorBluePrimaryYxyRadiometric(generator);

  while(count){
    float* buf0 = cmlNextMutableFloatComponent(buf);
    float* buf1 = cmlNextMutableFloatComponent(buf);
    float* buf2 = cmlNextMutableFloatComponent(buf);

    cml_OneYCbCrToRGB_SB(buf0, buf1, buf2, redprimaryYxy, blueprimaryYxy, whiteInvXYZ);

    count--;
  }

}







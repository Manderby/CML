
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

#include "../CML.h"
#include "../StateMachine/CMLInternal.h"


CML_HIDDEN CML_INLINE void cml_OneRGBToRadiometric (CMLMOBFunction** spec, const float* CML_RESTRICT RGB0, const float* CML_RESTRICT RGB1, const float* CML_RESTRICT RGB2, CMLMOBFunctionVector* generatorfuncs, CMLMOBFunction* backwardresponseR, CMLMOBFunction* backwardresponseG, CMLMOBFunction* backwardresponseB){
  CMLVec3 newin;
  cmlSet3(newin, *RGB0, *RGB1, *RGB2);
  newin[0] = cml_Eval(backwardresponseR, newin[0]);
  newin[1] = cml_Eval(backwardresponseG, newin[1]);
  newin[2] = cml_Eval(backwardresponseB, newin[2]);
  CMLMOBFunction* newspectrum0 = cmlCreateFunctionMulScalar(cmlGetFunctionVectorFunction(generatorfuncs, 0), newin[0]);
  CMLMOBFunction* newspectrum1 = cmlCreateFunctionMulScalar(cmlGetFunctionVectorFunction(generatorfuncs, 1), newin[1]);
  CMLMOBFunction* newspectrum2 = cmlCreateFunctionMulScalar(cmlGetFunctionVectorFunction(generatorfuncs, 2), newin[2]);
  CMLMOBFunction* newspectrum01 = cmlCreateFunctionAddFunction(newspectrum0, newspectrum1);
  *spec = cmlCreateFunctionAddFunction(newspectrum01, newspectrum2);
}





CML_HIDDEN void cml_RGBToRadiometric(CMLOutput out , CMLInput in, CMLSize count){
  MOB* responsecurves = cmlGetConverterSetting(CML_SETTING_CHANNEL_RESPONSE_CURVES, CML_GET_SUB);
  CMLMOBGenerator* generator = cmlGetConverterSetting(CML_SETTING_GENERATOR, CML_GET_SUB);

  CMLMOBFunctionVector* generatorfuncs = cmlGetGeneratorFunctions(generator);
  CMLMOBFunction* backwardresponseR = cmlGetResponseCurveBackwardFunc(mobGetArrayObject(responsecurves, 0));
  CMLMOBFunction* backwardresponseG = cmlGetResponseCurveBackwardFunc(mobGetArrayObject(responsecurves, 1));
  CMLMOBFunction* backwardresponseB = cmlGetResponseCurveBackwardFunc(mobGetArrayObject(responsecurves, 2));
  if(cmlGetConverterError()){return;}

  while(count){
    const float* RGB0 = cmlNextConstFloatComponent(in);
    const float* RGB1 = cmlNextConstFloatComponent(in);
    const float* RGB2 = cmlNextConstFloatComponent(in);
    CMLMOBFunction** spec = cmlNextMutableFunctionComponent(out);

    cml_OneRGBToRadiometric(spec, RGB0, RGB1, RGB2, generatorfuncs, backwardresponseR, backwardresponseG, backwardresponseB);

    count--;
  }
  
}






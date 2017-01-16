
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

#include "CML.h"
#include "CMLInternal.h"


CML_HIDDEN CML_INLINE void cml_OneRemissionToRadiometric (CMLMOBFunction** out, CMLMOBFunction** in, CMLMOBFunction* illumination){
  *out = cmlCreateFunctionMulFunction(*in, illumination);
}



CML_HIDDEN CMLBool cml_RemissionToRadiometricRequester(){
  cmlRequestConverterSetting(CML_SETTING_ILLUMINATION_SPECTRUM, CML_GET_SUB);
  return CML_TRUE;
}


CML_HIDDEN void cml_RemissionToRadiometric(CMLOutput out, CMLInput in, CMLSize count){
//  CMLMOBFunction* illumination = cmlFetchConverterSetting(0);
  
  CMLMOBFunction* illumination = cmlGetConverterSetting(CML_SETTING_ILLUMINATION_SPECTRUM, CML_GET_SUB);
  if(cmlGetConverterError()){return;}

  while(count){
    CMLMOBFunction** inspec = cmlNextMutableFunctionComponent(in);
    CMLMOBFunction** outspec = cmlNextMutableFunctionComponent(out);

    cml_OneRemissionToRadiometric(outspec, inspec, illumination);

    count--;
  }
}


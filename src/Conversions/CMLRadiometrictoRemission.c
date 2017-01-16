
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

#include "CML.h"
#include "CMLInternal.h"



CML_HIDDEN CML_INLINE void cml_OneRadiometricToRemission (CMLMOBFunction** out, CMLMOBFunction** in, CMLMOBFunction* illumination){
  *out = cmlCreateFunctionDivFunction(*in, illumination);
}





CML_HIDDEN void cml_RadiometricToRemission(CMLOutput out, CMLInput in, CMLSize count){
  CMLMOBFunction* illumination = cmlGetConverterSetting(CML_SETTING_ILLUMINATION_SPECTRUM, CML_GET_ADD);
  if(cmlGetConverterError()){return;}

  while(count){
    CMLMOBFunction** inspec = cmlNextMutableFunctionComponent(in);
    CMLMOBFunction** outspec = cmlNextMutableFunctionComponent(out);

    cml_OneRadiometricToRemission(outspec, inspec, illumination);

    count--;
  }
}


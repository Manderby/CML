
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

#include "../CML.h"
#include "../StateMachine/CMLInternal.h"


CML_HIDDEN float cml_LuvScalarComponentMin(CMLColorspace* colorspace, CMLInt indx){
  CML_UNUSED(colorspace);
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_COLORSPACE_OBJECT), colorspace))
    cmlError("cml_YuvScalarComponentMax", "Given MOB is not a Colorspace\n");
  #endif

  if(indx == 0){
    return 0.f;
  }else{
    return -100.f;
  }
}


CML_HIDDEN float cml_LuvScalarComponentMax(CMLColorspace* colorspace, CMLInt indx){
  CML_UNUSED(colorspace);
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_COLORSPACE_OBJECT), colorspace))
    cmlError("cml_YuvScalarComponentMax", "Given MOB is not a Colorspace\n");
  #endif

  CML_UNUSED(indx);
  return 100.f;
}


CML_HIDDEN void cml_DefineLuvSpaceValences(){
  cmlAddComponent(CML_COMPONENT_CARTESIAN, "L");
  cmlAddComponent(CML_COMPONENT_CARTESIAN, "u");
  cmlAddComponent(CML_COMPONENT_CARTESIAN, "v");
}



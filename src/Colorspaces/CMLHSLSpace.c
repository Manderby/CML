
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

#include "CML.h"
#include "CMLInternal.h"


CML_HIDDEN float cml_HSLScalarComponentMax(CMLColorspace* colorspace, CMLInt indx){
  CML_UNUSED(colorspace);
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_COLORSPACE_OBJECT), colorspace))
    cmlError("cml_YuvScalarComponentMax", "Given MOB is not a Colorspace\n");
  #endif

  if(indx == 0){return 360.f;}
  return 1.f;
}


CML_HIDDEN void cml_DefineHSLSpaceValences(){
  cmlAddComponent(CML_COMPONENT_ANGULAR, "H");
  cmlAddComponent(CML_COMPONENT_RADIAL, "S");
  cmlAddComponent(CML_COMPONENT_CARTESIAN, "L");
  cmlSetMainComponent(2);
}



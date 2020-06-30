
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

#include "../CML.h"
#include "../StateMachine/CMLInternal.h"


CML_HIDDEN void cml_DefineRGBSpaceValences(){
  cmlAddComponent(CML_COMPONENT_CARTESIAN, "R");
  cmlAddComponent(CML_COMPONENT_CARTESIAN, "G");
  cmlAddComponent(CML_COMPONENT_CARTESIAN, "B");
  cmlSetMainComponent(1);
}


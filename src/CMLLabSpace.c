
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

#include "CML.h"
#include "StateMachine/CMLColorMachineState.h"


CMLAPI void cmlDestroyLabSpace(void* labspace);


CMLAPI void cmlDestroyLabSpace(void* labsp){
  CMLLabSpace* labspace = (CMLLabSpace*)labsp;
  cmlReleaseObject(labspace->whitepoint);
  cmlReleaseObject(labspace->responsecurve);
}


CMLAPI const CMLResponseCurve* cmlGetLabSpaceResponseCurve(const CMLLabSpace* labspace){
  return labspace->responsecurve;
}


CMLAPI const CMLWhitepoint* cmlGetLabSpaceWhitepoint(const CMLLabSpace* labspace){
  return labspace->whitepoint;
}




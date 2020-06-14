
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

#include "CML.h"
#include "CMLColorMachineState.h"


CML_API CMLEncoding cmlRegisterEncoding(){
//  CMLEncoding newencoding = naGetStackCount(&(cmlc->encodings));
//  CMLMOBEncoding* newencodingmob = mobCreateEnum(newencoding);
//  // todo
////  CMLMOBEncoding** registeredelement = naNewGrowingSpaceElement(&(cmlc->encodings));
//  *registeredelement = newencodingmob;
//  return newencoding;
  return 0;
}


CML_API void cml_DestroyEncoding(CMLMOBEncoding* encoding){
  mobDestroyObject(encoding);
}

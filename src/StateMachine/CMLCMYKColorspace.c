//
//// (c) Manderim GmbH
//// This is proprietary software. Any use without the explicit acknowledgement
//// of the author of this software is prohibited and any liability is disclamed.
//// Terms of a separate contract may apply.
//
//#include "../CML.h"
//#include "CMLColorMachineState.h"
//
//
//
//
//
//CML_API CMLCMYKTransformType cmlGetCMYKTransform(const CMLColorMachine* cm){
//  return cm->cmykspace.transform;
//}
//
//
//void cmlSetCMYKTransform(CMLColorMachine* cm, CMLCMYKTransformType transform){
//  switch(transform){
//  case CML_CMYK_STANDARD_TRANSFORM:
//    cm->RGBtoCMYK = &CMLInternalRGBtoCMYKStandard;
//    cm->RGBtoCMYK_SB = &CMLInternalRGBtoCMYKStandard_SB;
//    cm->CMYKtoRGB = &CMLInternalCMYKtoRGBStandard;
//    cm->CMYKtoRGB_SB = &CMLInternalCMYKtoRGBStandard_SB;
//    break;
//  case CML_CMYK_UCR_TRANSFORM:
//    cm->RGBtoCMYK = &CMLInternalRGBtoCMYKUCR;
//    cm->RGBtoCMYK_SB = &CMLInternalRGBtoCMYKUCR_SB;
//    cm->CMYKtoRGB = &CMLInternalCMYKtoRGBUCR;
//    cm->CMYKtoRGB_SB = &CMLInternalCMYKtoRGBUCR_SB;
//    break;
//  default:
//    #ifndef NDEBUG
//      cmlError("cmlSetCMYKTransform", "CMYK Transformation undefined.");
//    #endif
//    return;
//    break;
//  }
//  cm->cmykspace.transform = transform;
//}
//

void asdf(){}

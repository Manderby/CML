
#include "../CML.h"
#include "CMLColorMachineState.h"



CML_DEF cml_CMYKTransformType cmlGetCMYKTransform(const CMLColorMachine* cm){
  return cm->cmykSpace.transform;
}


CML_DEF void cmlSetCMYKTransform(CMLColorMachine* cm, cml_CMYKTransformType transform){
  switch(transform){
  case CML_CMYK_STANDARD_TRANSFORM:
    cm->RGBToCMYK    = &cml_RGBToCMYKStandard;
    cm->RGBToCMYK_SB = &cml_RGBToCMYKStandard_SB;
    cm->CMYKToRGB    = &cml_CMYKToRGBStandard;
    cm->CMYKToRGB_SB = &cml_CMYKToRGBStandard_SB;
    break;
  case CML_CMYK_UCR_TRANSFORM:
    cm->RGBToCMYK    = &cml_RGBToCMYKUCR;
    cm->RGBToCMYK_SB = &cml_RGBToCMYKUCR_SB;
    cm->CMYKToRGB    = &cml_CMYKToRGBUCR;
    cm->CMYKToRGB_SB = &cml_CMYKToRGBUCR_SB;
    break;
  default:
    #if CML_DEBUG
      cmlError("CMYK Transformation undefined.");
    #endif
    return;
    break;
  }
  cm->cmykSpace.transform = transform;
}



// This is free and unencumbered software released into the public domain.

// Anyone is free to copy, modify, publish, use, compile, sell, or
// distribute this software, either in source code form or as a compiled
// binary, for any purpose, commercial or non-commercial, and by any
// means.

// In jurisdictions that recognize copyright laws, the author or authors
// of this software dedicate any and all copyright interest in the
// software to the public domain. We make this dedication for the benefit
// of the public at large and to the detriment of our heirs and
// successors. We intend this dedication to be an overt act of
// relinquishment in perpetuity of all present and future rights to this
// software under copyright law.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
// OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.

// For more information, please refer to <http://unlicense.org/>

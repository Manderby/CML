
#include "../CML.h"
#include "CMLColorMachineState.h"


CML_API CMLGrayComputationType cmlGetGrayComputationType(const CMLColorMachine* cm){
  return cm->graySpace.computation;
}


CML_API void cmlSetGrayComputationType(CMLColorMachine* cm, CMLGrayComputationType computation){
  switch(computation){
  case CML_GRAY_FROM_HSL:
    cm->GrayToChanneledBuffer = &cml_GrayToChanneledBufferHSL;
    cm->ChanneledBufferToGray = &cml_ChanneledBufferToGrayHSL;
    break;
  case CML_GRAY_FROM_HSV:
    cm->GrayToChanneledBuffer = &cml_GrayToChanneledBufferHSV;
    cm->ChanneledBufferToGray = &cml_ChanneledBufferToGrayHSV;
    break;
  case CML_GRAY_FROM_G:
    cm->GrayToChanneledBuffer = &cml_GrayToChanneledBufferG;
    cm->ChanneledBufferToGray = &cml_ChanneledBufferToGrayG;
    break;
  case CML_GRAY_FROM_LSTAR:
    cm->GrayToChanneledBuffer = &cml_GrayToChanneledBufferLSTAR;
    cm->ChanneledBufferToGray = &cml_ChanneledBufferToGrayLSTAR;
    break;
  case CML_GRAY_FROM_L:
    cm->GrayToChanneledBuffer = &cml_GrayToChanneledBufferL;
    cm->ChanneledBufferToGray = &cml_ChanneledBufferToGrayL;
    break;
  case CML_GRAY_FROM_Y:
    cm->GrayToChanneledBuffer = &cml_GrayToChanneledBufferY;
    cm->ChanneledBufferToGray = &cml_ChanneledBufferToGrayY;
    break;
  case CML_GRAY_FROM_YPRIME:
    cm->GrayToChanneledBuffer = &cml_GrayToChanneledBufferYPRIME;
    cm->ChanneledBufferToGray = &cml_ChanneledBufferToGrayYPRIME;
    break;
  default:
    #if CML_DEBUG
      cmlError("Gray Computation undefined.");
    #endif
    return;
    break;
  }
  cm->graySpace.computation = computation;
}




//CMLBool              ColorMachine::getGrayChannelInterpretation() const                            {return (s->graySpace.interpretation == CML_MAX_IS_WHITE);}
//void              ColorMachine::setGrayChannelInterpretation(CMLChannelInterpretationType newinterpretation)  {s->graySpace.interpretation = newinterpretation;}



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

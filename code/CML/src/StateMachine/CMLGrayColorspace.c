
#include "../CML.h"
#include "CMLColorMachineState.h"


CML_API CMLGrayComputationType CMLgetGrayComputationType(const CMLColorMachine* cm){
  return cm->grayspace.computation;
}


CML_API void CMLsetGrayComputationType(CMLColorMachine* cm, CMLGrayComputationType computation){
  switch(computation){
  case CML_GRAY_FROM_HSL:
    cm->GraytoChanneledBuffer = &CMLInternalGraytoChanneledBufferHSL;
    cm->ChanneledBuffertoGray = &CMLInternalChanneledBuffertoGrayHSL;
    break;
  case CML_GRAY_FROM_HSV:
    cm->GraytoChanneledBuffer = &CMLInternalGraytoChanneledBufferHSV;
    cm->ChanneledBuffertoGray = &CMLInternalChanneledBuffertoGrayHSV;
    break;
  case CML_GRAY_FROM_G:
    cm->GraytoChanneledBuffer = &CMLInternalGraytoChanneledBufferG;
    cm->ChanneledBuffertoGray = &CMLInternalChanneledBuffertoGrayG;
    break;
  case CML_GRAY_FROM_LSTAR:
    cm->GraytoChanneledBuffer = &CMLInternalGraytoChanneledBufferLSTAR;
    cm->ChanneledBuffertoGray = &CMLInternalChanneledBuffertoGrayLSTAR;
    break;
  case CML_GRAY_FROM_L:
    cm->GraytoChanneledBuffer = &CMLInternalGraytoChanneledBufferL;
    cm->ChanneledBuffertoGray = &CMLInternalChanneledBuffertoGrayL;
    break;
  case CML_GRAY_FROM_Y:
    cm->GraytoChanneledBuffer = &CMLInternalGraytoChanneledBufferY;
    cm->ChanneledBuffertoGray = &CMLInternalChanneledBuffertoGrayY;
    break;
  case CML_GRAY_FROM_YPRIME:
    cm->GraytoChanneledBuffer = &CMLInternalGraytoChanneledBufferYPRIME;
    cm->ChanneledBuffertoGray = &CMLInternalChanneledBuffertoGrayYPRIME;
    break;
  default:
    #ifndef NDEBUG
      cmlError("CMLsetGrayComputationType", "Gray Computation undefined.");
    #endif
    return;
    break;
  }
  cm->grayspace.computation = computation;
}




//CMLBool              ColorMachine::getGrayChannelInterpretation() const                            {return (s->grayspace.interpretation == CML_MAX_IS_WHITE);}
//void              ColorMachine::setGrayChannelInterpretation(CMLChannelInterpretationType newinterpretation)  {s->grayspace.interpretation = newinterpretation;}



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


// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

#include "../CML.h"
#include "CMLColorMachineState.h"


CMLAPI CMLGrayComputationType CMLgetGrayComputationType(const CMLColorMachine* cm){
  return cm->grayspace.computation;
}


CMLAPI void CMLsetGrayComputationType(CMLColorMachine* cm, CMLGrayComputationType computation){
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


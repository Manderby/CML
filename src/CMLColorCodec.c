
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

#include "CML.h"
#include "CMLColorMachineState.h"

CMLAPI CMLuint16 cmlGetColorCodecNumChannels(CMLColorCodec* codec){
  switch(codec->type){
  case CML_CODEC_RGB_uint8: return 3; break;
  default: return 0; break;
  }
}


CMLAPI CMLuint16 cmlGetColorCodecBytesPerColor(CMLColorCodec* codec){
  switch(codec->type){
  case CML_CODEC_RGB_uint8: return 3; break;
  default: return 0; break;
  }
}


// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

#include "CML.h"
#include "StateMachine/CMLColorMachineState.h"


CML_HIDDEN void cmlDestroyCMOB(void* object){
  CML_UNUSED(object);
}






//CML_HIDDEN void CMLInternalGraytoChanneledBufferHSL(const CMLColorMachine* cm, float* CML_RESTRICT buffer , const float* CML_RESTRICT gray){
//  float luminance;
//  cm = cm; // no warning
//  luminance = 1.f - *gray;
//  cmlSet3(buffer, 0.f, 0.f, luminance);
//}
//CML_HIDDEN void CMLInternalGraytoChanneledBufferHSV(const CMLColorMachine* cm, float* CML_RESTRICT buffer , const float* CML_RESTRICT gray){
//  float luminance;
//  cm = cm; // no warning
//  luminance = 1.f - *gray;
//  cmlSet3(buffer, 0.f, 0.f, luminance);
//}
//CML_HIDDEN void CMLInternalGraytoChanneledBufferG(const CMLColorMachine* cm, float* CML_RESTRICT buffer , const float* CML_RESTRICT gray){
//  float luminance;
//  cm = cm; // no warning
//  luminance = 1.f - *gray;
//  cmlSet3(buffer, luminance, luminance, luminance);
//}
//CML_HIDDEN void CMLInternalGraytoChanneledBufferLSTAR(const CMLColorMachine* cm, float* CML_RESTRICT buffer , const float* CML_RESTRICT gray){
//  float luminance;
//  cm = cm; // no warning
//  luminance = 1.f - *gray;
//  cmlSet3(buffer, 100.f * luminance, 0.f, 0.f);
//}
//CML_HIDDEN void CMLInternalGraytoChanneledBufferL(const CMLColorMachine* cm, float* CML_RESTRICT buffer , const float* CML_RESTRICT gray){
//  float luminance;
//  cm = cm; // no warning
//  luminance = 1.f - *gray;
//  cmlSet3(buffer, 100.f * luminance, 0.f, 0.f);
//}
//CML_HIDDEN void CMLInternalGraytoChanneledBufferY(const CMLColorMachine* cm, float* CML_RESTRICT buffer , const float* CML_RESTRICT gray){
//  float luminance = 1.f - *gray;
//  const float* whiteYxy = cmlGetWhiteYxy(cm->observer);
//  cmlSet3(buffer, luminance, whiteYxy[1], whiteYxy[2]);
//}
//CML_HIDDEN void CMLInternalGraytoChanneledBufferYPRIME(const CMLColorMachine* cm, float* CML_RESTRICT buffer , const float* CML_RESTRICT gray){
//  float luminance;
//  cm = cm; // no warning
//  luminance = 1.f - *gray;
//  cmlSet3(buffer, luminance, 0.f, 0.f);
//}
//
//
//
//
//CML_HIDDEN void CMLInternalChanneledBuffertoGrayHSL(const CMLColorMachine* cm, float* CML_RESTRICT gray , const float* CML_RESTRICT buffer){
//  cm = cm; // no warning
//  *gray = 1.f - buffer[2];
//}
//CML_HIDDEN void CMLInternalChanneledBuffertoGrayHSV(const CMLColorMachine* cm, float* CML_RESTRICT gray , const float* CML_RESTRICT buffer){
//  cm = cm; // no warning
//  *gray = 1.f - buffer[2];
//}
//CML_HIDDEN void CMLInternalChanneledBuffertoGrayG(const CMLColorMachine* cm, float* CML_RESTRICT gray , const float* CML_RESTRICT buffer){
//  cm = cm; // no warning
//  *gray = 1.f - buffer[1];
//}
//CML_HIDDEN void CMLInternalChanneledBuffertoGrayLSTAR(const CMLColorMachine* cm, float* CML_RESTRICT gray , const float* CML_RESTRICT buffer){
//  cm = cm; // no warning
//  *gray = 1.f - (buffer[0] * .01f);
//}
//CML_HIDDEN void CMLInternalChanneledBuffertoGrayL(const CMLColorMachine* cm, float* CML_RESTRICT gray , const float* CML_RESTRICT buffer){
//  cm = cm; // no warning
//  *gray = 1.f - (buffer[0] * .01f);
//}
//CML_HIDDEN void CMLInternalChanneledBuffertoGrayY(const CMLColorMachine* cm, float* CML_RESTRICT gray , const float* CML_RESTRICT buffer){
//  cm = cm; // no warning
//  *gray = 1.f - buffer[0];
//}
//CML_HIDDEN void CMLInternalChanneledBuffertoGrayYPRIME(const CMLColorMachine* cm, float* CML_RESTRICT gray , const float* CML_RESTRICT buffer){
//  cm = cm; // no warning
//  *gray = 1.f - buffer[0];
//}




//CML_HIDDEN void CMLInternalXYZToLabCIELAB(const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count){
//  cml_XYZtoCIELAB(out, in, count, cmlGetWhiteInverseXYZ(cmlGetLabSpaceWhite(cm->labspace)), cmlGetResponseCurveForwardFunc(cm->labspace.responseL));
//}
//
//CML_HIDDEN void CMLInternalXYZToLabCIELAB_SB(const CMLColorMachine* cm, float* buf, CMLuint32 count){
//  cml_XYZtoCIELAB_SB(buf, count, cmlGetWhiteInverseXYZ(cmlGetLabSpaceWhite(cm->labspace)), cmlGetResponseCurveForwardFunc(cm->labspace.responseL));
//}
//
//
//CML_HIDDEN void CMLInternalXYZToLabChromaticValence(const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count){
//  const float* whiteInvXYZ = cmlGetWhiteInverseXYZ(cm->observer);
//  while(count){
//
//    float xr = in[0] * whiteInvXYZ[0];
//    float yr = in[1] * whiteInvXYZ[1];
//    float zr = in[2] * whiteInvXYZ[2];
//    
//    float fy = cml_Eval(cmlGetResponseCurveForwardFunc(cm->labspace.responseL), yr);
//    out[0] = 100.f * fy;
//
//    if(fy == 0.f){
//      out[1] = 0.f;
//      out[2] = 0.f;
//    }else{
//      float fyinverse = cmlInverse(fy);
//      out[1] = (xr - yr) * cm->labspace.adamschromaticityvalenceK * 100.f * fyinverse;
//      out[2] = (yr - zr) * cm->labspace.adamschromaticityvalenceK * cm->labspace.adamschromaticityvalenceke * 100.f * fyinverse;
//    }
//
//    in += CML_XYZ_NUMCHANNELS;
//    out += CML_Lab_NUMCHANNELS;
//    count--;
//  }
//}

//CML_HIDDEN void CMLInternalXYZToLabChromaticValence_SB(const CMLColorMachine* cm, float* buf, CMLuint32 count){
//  const float* whiteInvXYZ = cmlGetWhiteInverseXYZ(cm->observer);
//  while(count){
//
//    float xr = buf[0] * whiteInvXYZ[0];
//    float yr = buf[1] * whiteInvXYZ[1];
//    float zr = buf[2] * whiteInvXYZ[2];
//    
//    float fy = cml_Eval(cmlGetResponseCurveForwardFunc(cm->labspace.responseL), yr);
//    buf[0] = 100.f * fy;
//
//    if(fy == 0.f){
//      buf[1] = 0.f;
//      buf[2] = 0.f;
//    }else{
//      float fyinverse = cmlInverse(fy);
//      buf[1] = (xr - yr) * cm->labspace.adamschromaticityvalenceK * 100.f * fyinverse;
//      buf[2] = (yr - zr) * cm->labspace.adamschromaticityvalenceK * cm->labspace.adamschromaticityvalenceke * 100.f * fyinverse;
//    }
//
//    buf += CML_Lab_NUMCHANNELS;
//    count--;
//  }
//}


//CML_HIDDEN void CMLInternalLabToXYZCIELAB (const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count){
//  cml_CIELABtoXYZ(out, in, count, cmlGetWhiteXYZ(cmlGetLabSpaceWhite(cm->labspace)), cmlGetResponseCurveBackwardFunc(cm->labspace.responseL));
//}


//CML_HIDDEN void CMLInternalLabToXYZCIELAB_SB (const CMLColorMachine* cm, float* buf, CMLuint32 count){
//  cml_CIELABtoXYZ_SB(buf, count, cmlGetWhiteXYZ(cmlGetLabSpaceWhite(cm->labspace)), cmlGetResponseCurveBackwardFunc(cm->labspace.responseL));
//}



//CML_HIDDEN void CMLInternalLabToXYZChromaticValence (const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count){
//  const float* whiteXYZ = cmlGetWhiteXYZ(cmlGetLabSpaceWhite(cm->labspace));
//  while(count){
//
//    float xr, yr, zr;
//    
//    float fy = in[0] * .01f;
//    yr = cml_Eval(cmlGetResponseCurveBackwardFunc(cm->labspace.responseL), fy);
//
//    if((cm->labspace.adamschromaticityvalenceK == 0.f) || (cm->labspace.adamschromaticityvalenceke == 0.f)){
//      xr = 0.f;
//      zr = 0.f;
//    }else{
//      xr = yr + fy * in[1] / (cm->labspace.adamschromaticityvalenceK * 100.f);
//      zr = yr - fy * in[2] / (cm->labspace.adamschromaticityvalenceK * cm->labspace.adamschromaticityvalenceke * 100.f);
//    }
//
//    out[0] = xr * whiteXYZ[0];
//    out[1] = yr * whiteXYZ[1];
//    out[2] = zr * whiteXYZ[2];
//
//    in += CML_Lab_NUMCHANNELS;
//    out += CML_XYZ_NUMCHANNELS;
//    count--;
//  }
//}


//CML_HIDDEN void CMLInternalLabToXYZChromaticValence_SB (const CMLColorMachine* cm, float* buf, CMLuint32 count){
//  const float* whiteXYZ = cmlGetWhiteXYZ(cm->observer);
//  while(count){
//
//    float xr, yr, zr;
//    
//    float fy = buf[0] * .01f;
//    yr = cml_Eval(cmlGetResponseCurveBackwardFunc(cm->labspace.responseL), fy);
//
//    if((cm->labspace.adamschromaticityvalenceK == 0.f) || (cm->labspace.adamschromaticityvalenceke == 0.f)){
//      xr = 0.f;
//      zr = 0.f;
//    }else{
//      xr = yr + fy * buf[1] / (cm->labspace.adamschromaticityvalenceK * 100.f);
//      zr = yr - fy * buf[2] / (cm->labspace.adamschromaticityvalenceK * cm->labspace.adamschromaticityvalenceke * 100.f);
//    }
//
//    buf[0] = xr * whiteXYZ[0];
//    buf[1] = yr * whiteXYZ[1];
//    buf[2] = zr * whiteXYZ[2];
//
//    buf += CML_XYZ_NUMCHANNELS;
//    count--;
//  }
//}


//CML_HIDDEN void CMLInternalRGBtoCMYKStandard(const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count){
//  cm = cm; // no warning
//  while(count){
//
//    out[0] = 1.f - in[0];
//    out[1] = 1.f - in[1];
//    out[2] = 1.f - in[2];
//    out[3] = 0.f;
//
//    in += CML_RGB_NUMCHANNELS;
//    out += CML_CMYK_NUMCHANNELS;
//    count--;
//  }
//}
//
//CML_HIDDEN void CMLInternalRGBtoCMYKStandard_SB(const CMLColorMachine* cm, float* buf, CMLuint32 count){
//  cm = cm; // no warning
//  while(count){
//
//    buf[0] = 1.f - buf[0];
//    buf[1] = 1.f - buf[1];
//    buf[2] = 1.f - buf[2];
//    buf[3] = 0.f;
//
//    buf += CML_CMYK_NUMCHANNELS; // todo warning
//    count--;
//  }
//}
//
//
//
//CML_HIDDEN void CMLInternalRGBtoCMYKUCR(const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count){
//  cm = cm; // no warning
//  while(count){
//
//    out[0] = 1.f - in[0];
//    out[1] = 1.f - in[1];
//    out[2] = 1.f - in[2];
//    out[3] = out[0];
//    if(out[1]<out[3]){out[3] = out[1];}
//    if(out[2]<out[3]){out[3] = out[2];}
//    out[0] -= out[3];
//    out[1] -= out[3];
//    out[2] -= out[3];
//
//    in += CML_RGB_NUMCHANNELS;
//    out += CML_CMYK_NUMCHANNELS;
//    count--;
//  }
//}
//
//CML_HIDDEN void CMLInternalRGBtoCMYKUCR_SB(const CMLColorMachine* cm, float* buf, CMLuint32 count){
//  cm = cm; // no warning
//  while(count){
//
//    buf[0] = 1.f - buf[0];
//    buf[1] = 1.f - buf[1];
//    buf[2] = 1.f - buf[2];
//    buf[3] = buf[0];
//    if(buf[1]<buf[3]){buf[3] = buf[1];}
//    if(buf[2]<buf[3]){buf[3] = buf[2];}
//    buf[0] -= buf[3];
//    buf[1] -= buf[3];
//    buf[2] -= buf[3];
//
//    buf += CML_CMYK_NUMCHANNELS; // todo warning
//    count--;
//  }
//}
//
//
//
//CML_HIDDEN void CMLInternalCMYKtoRGBStandard (const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count){
//  cm = cm; // no warning
//  while(count){
//
//    out[0] = 1.f - in[0];
//    out[1] = 1.f - in[1];
//    out[2] = 1.f - in[2];
//
//    in += CML_CMYK_NUMCHANNELS;
//    out += CML_RGB_NUMCHANNELS;
//    count--;
//  }
//}
//
//
//CML_HIDDEN void CMLInternalCMYKtoRGBStandard_SB (const CMLColorMachine* cm, float* buf, CMLuint32 count){
//  cm = cm; // no warning
//  while(count){
//
//    buf[0] = 1.f - buf[0];
//    buf[1] = 1.f - buf[1];
//    buf[2] = 1.f - buf[2];
//
//    buf += CML_RGB_NUMCHANNELS; // todo warning
//    count--;
//  }
//}
//
//
//CML_HIDDEN void CMLInternalCMYKtoRGBUCR (const CMLColorMachine* cm, float* CML_RESTRICT out , const float* CML_RESTRICT in, CMLuint32 count){
//  cm = cm; // no warning
//  while(count){
//
//    out[0] = 1.f - (in[0]+in[3]);
//    out[1] = 1.f - (in[1]+in[3]);
//    out[2] = 1.f - (in[2]+in[3]);
//
//    in += CML_CMYK_NUMCHANNELS;
//    out += CML_RGB_NUMCHANNELS;
//    count--;
//  }
//}
//
//
//CML_HIDDEN void CMLInternalCMYKtoRGBUCR_SB (const CMLColorMachine* cm, float* buf, CMLuint32 count){
//  cm = cm; // no warning
//  while(count){
//
//    buf[0] = 1.f - (buf[0]+buf[3]);
//    buf[1] = 1.f - (buf[1]+buf[3]);
//    buf[2] = 1.f - (buf[2]+buf[3]);
//
//    buf += CML_RGB_NUMCHANNELS; // todo warning
//    count--;
//  }
//}



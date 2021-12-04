
#include "CML.h"
#include "CMLColorMachineState.h"




CML_HIDDEN void cml_GrayToChanneledBufferHSL(const CMLColorMachine* cm, float* CML_RESTRICT buffer, const float* CML_RESTRICT gray){
  float luminance;
  CML_UNUSED(cm);
  luminance = 1.f - *gray;
  cmlSet3(buffer, 0.f, 0.f, luminance);
}
CML_HIDDEN void cml_GrayToChanneledBufferHSV(const CMLColorMachine* cm, float* CML_RESTRICT buffer, const float* CML_RESTRICT gray){
  float luminance;
  CML_UNUSED(cm);
  luminance = 1.f - *gray;
  cmlSet3(buffer, 0.f, 0.f, luminance);
}
CML_HIDDEN void cml_GrayToChanneledBufferG(const CMLColorMachine* cm, float* CML_RESTRICT buffer, const float* CML_RESTRICT gray){
  float luminance;
  CML_UNUSED(cm);
  luminance = 1.f - *gray;
  cmlSet3(buffer, luminance, luminance, luminance);
}
CML_HIDDEN void cml_GrayToChanneledBufferLSTAR(const CMLColorMachine* cm, float* CML_RESTRICT buffer, const float* CML_RESTRICT gray){
  float luminance;
  CML_UNUSED(cm);
  luminance = 1.f - *gray;
  cmlSet3(buffer, 100.f * luminance, 0.f, 0.f);
}
CML_HIDDEN void cml_GrayToChanneledBufferL(const CMLColorMachine* cm, float* CML_RESTRICT buffer, const float* CML_RESTRICT gray){
  float luminance;
  CML_UNUSED(cm);
  luminance = 1.f - *gray;
  cmlSet3(buffer, 100.f * luminance, 0.f, 0.f);
}
CML_HIDDEN void cml_GrayToChanneledBufferY(const CMLColorMachine* cm, float* CML_RESTRICT buffer, const float* CML_RESTRICT gray){
  float luminance = 1.f - *gray;
  const float* whitePointYxy = cmlGetReferenceWhitePointYxy(&(cm->observer));
  cmlSet3(buffer, luminance, whitePointYxy[1], whitePointYxy[2]);
}
CML_HIDDEN void cml_GrayToChanneledBufferYPRIME(const CMLColorMachine* cm, float* CML_RESTRICT buffer, const float* CML_RESTRICT gray){
  float luminance;
  CML_UNUSED(cm);
  luminance = 1.f - *gray;
  cmlSet3(buffer, luminance, 0.f, 0.f);
}




CML_HIDDEN void cml_ChanneledBufferToGrayHSL(const CMLColorMachine* cm, float* CML_RESTRICT gray, const float* CML_RESTRICT buffer){
  CML_UNUSED(cm);
  *gray = 1.f - buffer[2];
}
CML_HIDDEN void cml_ChanneledBufferToGrayHSV(const CMLColorMachine* cm, float* CML_RESTRICT gray, const float* CML_RESTRICT buffer){
  CML_UNUSED(cm);
  *gray = 1.f - buffer[2];
}
CML_HIDDEN void cml_ChanneledBufferToGrayG(const CMLColorMachine* cm, float* CML_RESTRICT gray, const float* CML_RESTRICT buffer){
  CML_UNUSED(cm);
  *gray = 1.f - buffer[1];
}
CML_HIDDEN void cml_ChanneledBufferToGrayLSTAR(const CMLColorMachine* cm, float* CML_RESTRICT gray, const float* CML_RESTRICT buffer){
  CML_UNUSED(cm);
  *gray = 1.f - (buffer[0] * .01f);
}
CML_HIDDEN void cml_ChanneledBufferToGrayL(const CMLColorMachine* cm, float* CML_RESTRICT gray, const float* CML_RESTRICT buffer){
  CML_UNUSED(cm);
  *gray = 1.f - (buffer[0] * .01f);
}
CML_HIDDEN void cml_ChanneledBufferToGrayY(const CMLColorMachine* cm, float* CML_RESTRICT gray, const float* CML_RESTRICT buffer){
  CML_UNUSED(cm);
  *gray = 1.f - buffer[0];
}
CML_HIDDEN void cml_ChanneledBufferToGrayYPRIME(const CMLColorMachine* cm, float* CML_RESTRICT gray, const float* CML_RESTRICT buffer){
  CML_UNUSED(cm);
  *gray = 1.f - buffer[0];
}




CML_HIDDEN void cml_XYZToLabCIELAB(const CMLColorMachine* cm, float* CML_RESTRICT out, const float* CML_RESTRICT in, size_t count){
  cml_XYZToCIELAB(out, in, count, cmlGetReferenceInverseWhitePointXYZ(&(cm->observer)), cm->labSpace.responseL.forwardFunc);
}

CML_HIDDEN void cml_XYZToLabCIELAB_SB(const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign){
  cml_XYZToCIELAB_SB(buf, count, floatAlign, cmlGetReferenceInverseWhitePointXYZ(&(cm->observer)), cm->labSpace.responseL.forwardFunc);
}


CML_HIDDEN void cml_XYZToLabChromaticValence(const CMLColorMachine* cm, float* CML_RESTRICT out, const float* CML_RESTRICT in, size_t count){
  const float* inverseWhitePointXYZ = cmlGetReferenceInverseWhitePointXYZ(&(cm->observer));
  while(count){

    float xr = in[0] * inverseWhitePointXYZ[0];
    float yr = in[1] * inverseWhitePointXYZ[1];
    float zr = in[2] * inverseWhitePointXYZ[2];
    
    float fy = cml_Eval(cm->labSpace.responseL.forwardFunc, yr);
    out[0] = 100.f * fy;

    if(fy == 0.f){
      out[1] = 0.f;
      out[2] = 0.f;
    }else{
      float fyinverse = cmlInverse(fy);
      out[1] = (xr - yr) * cm->labSpace.adamsChromaticityValenceK * 100.f * fyinverse;
      out[2] = (yr - zr) * cm->labSpace.adamsChromaticityValenceK * cm->labSpace.adamsChromaticityValenceke * 100.f * fyinverse;
    }

    in += CML_XYZ_NUMCHANNELS;
    out += CML_Lab_NUMCHANNELS;
    count--;
  }
}

CML_HIDDEN void cml_XYZToLabChromaticValence_SB(const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign){
  const float* inverseWhitePointXYZ = cmlGetReferenceInverseWhitePointXYZ(&(cm->observer));
  while(count){

    float xr = buf[0] * inverseWhitePointXYZ[0];
    float yr = buf[1] * inverseWhitePointXYZ[1];
    float zr = buf[2] * inverseWhitePointXYZ[2];
    
    float fy = cml_Eval(cm->labSpace.responseL.forwardFunc, yr);
    buf[0] = 100.f * fy;

    if(fy == 0.f){
      buf[1] = 0.f;
      buf[2] = 0.f;
    }else{
      float fyinverse = cmlInverse(fy);
      buf[1] = (xr - yr) * cm->labSpace.adamsChromaticityValenceK * 100.f * fyinverse;
      buf[2] = (yr - zr) * cm->labSpace.adamsChromaticityValenceK * cm->labSpace.adamsChromaticityValenceke * 100.f * fyinverse;
    }

    buf += floatAlign;
    count--;
  }
}


CML_HIDDEN void cml_LabToXYZCIELAB (const CMLColorMachine* cm, float* CML_RESTRICT out, const float* CML_RESTRICT in, size_t count){
  cml_CIELABToXYZ(out, in, count, cmlGetReferenceWhitePointXYZ(&(cm->observer)), cm->labSpace.responseL.backwardFunc);
}


CML_HIDDEN void cml_LabToXYZCIELAB_SB (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign){
  cml_CIELABToXYZ_SB(buf, count, floatAlign, cmlGetReferenceWhitePointXYZ(&(cm->observer)), cm->labSpace.responseL.backwardFunc);
}



CML_HIDDEN void cml_LabToXYZChromaticValence (const CMLColorMachine* cm, float* CML_RESTRICT out, const float* CML_RESTRICT in, size_t count){
  const float* whitePointXYZ = cmlGetReferenceWhitePointXYZ(&(cm->observer));
  while(count){

    float xr, yr, zr;
    
    float fy = in[0] * .01f;
    yr = cml_Eval(cm->labSpace.responseL.backwardFunc, fy);

    if((cm->labSpace.adamsChromaticityValenceK == 0.f) || (cm->labSpace.adamsChromaticityValenceke == 0.f)){
      xr = 0.f;
      zr = 0.f;
    }else{
      xr = yr + fy * in[1] / (cm->labSpace.adamsChromaticityValenceK * 100.f);
      zr = yr - fy * in[2] / (cm->labSpace.adamsChromaticityValenceK * cm->labSpace.adamsChromaticityValenceke * 100.f);
    }

    out[0] = xr * whitePointXYZ[0];
    out[1] = yr * whitePointXYZ[1];
    out[2] = zr * whitePointXYZ[2];

    in += CML_Lab_NUMCHANNELS;
    out += CML_XYZ_NUMCHANNELS;
    count--;
  }
}


CML_HIDDEN void cml_LabToXYZChromaticValence_SB (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign){
  const float* whitePointXYZ = cmlGetReferenceWhitePointXYZ(&(cm->observer));
  while(count){

    float xr, yr, zr;
    
    float fy = buf[0] * .01f;
    yr = cml_Eval(cm->labSpace.responseL.backwardFunc, fy);

    if((cm->labSpace.adamsChromaticityValenceK == 0.f) || (cm->labSpace.adamsChromaticityValenceke == 0.f)){
      xr = 0.f;
      zr = 0.f;
    }else{
      xr = yr + fy * buf[1] / (cm->labSpace.adamsChromaticityValenceK * 100.f);
      zr = yr - fy * buf[2] / (cm->labSpace.adamsChromaticityValenceK * cm->labSpace.adamsChromaticityValenceke * 100.f);
    }

    buf[0] = xr * whitePointXYZ[0];
    buf[1] = yr * whitePointXYZ[1];
    buf[2] = zr * whitePointXYZ[2];

    buf += floatAlign;
    count--;
  }
}


CML_HIDDEN void cml_RGBToCMYKStandard(const CMLColorMachine* cm, float* CML_RESTRICT out, const float* CML_RESTRICT in, size_t count){
  CML_UNUSED(cm);
  while(count){

    out[0] = 1.f - in[0];
    out[1] = 1.f - in[1];
    out[2] = 1.f - in[2];
    out[3] = 0.f;

    in += CML_RGB_NUMCHANNELS;
    out += CML_CMYK_NUMCHANNELS;
    count--;
  }
}

CML_HIDDEN void cml_RGBToCMYKStandard_SB(const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign){
  CML_UNUSED(cm);
  while(count){

    buf[0] = 1.f - buf[0];
    buf[1] = 1.f - buf[1];
    buf[2] = 1.f - buf[2];
    buf[3] = 0.f;

    buf += floatAlign;
    count--;
  }
}



CML_HIDDEN void cml_RGBToCMYKUCR(const CMLColorMachine* cm, float* CML_RESTRICT out, const float* CML_RESTRICT in, size_t count){
  CML_UNUSED(cm);
  while(count){

    out[0] = 1.f - in[0];
    out[1] = 1.f - in[1];
    out[2] = 1.f - in[2];
    out[3] = out[0];
    if(out[1]<out[3]){out[3] = out[1];}
    if(out[2]<out[3]){out[3] = out[2];}
    out[0] -= out[3];
    out[1] -= out[3];
    out[2] -= out[3];

    in += CML_RGB_NUMCHANNELS;
    out += CML_CMYK_NUMCHANNELS;
    count--;
  }
}

CML_HIDDEN void cml_RGBToCMYKUCR_SB(const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign){
  CML_UNUSED(cm);
  while(count){

    buf[0] = 1.f - buf[0];
    buf[1] = 1.f - buf[1];
    buf[2] = 1.f - buf[2];
    buf[3] = buf[0];
    if(buf[1]<buf[3]){buf[3] = buf[1];}
    if(buf[2]<buf[3]){buf[3] = buf[2];}
    buf[0] -= buf[3];
    buf[1] -= buf[3];
    buf[2] -= buf[3];

    buf += floatAlign;
    count--;
  }
}



CML_HIDDEN void cml_CMYKToRGBStandard (const CMLColorMachine* cm, float* CML_RESTRICT out, const float* CML_RESTRICT in, size_t count){
  CML_UNUSED(cm);
  while(count){

    out[0] = 1.f - in[0];
    out[1] = 1.f - in[1];
    out[2] = 1.f - in[2];

    in += CML_CMYK_NUMCHANNELS;
    out += CML_RGB_NUMCHANNELS;
    count--;
  }
}


CML_HIDDEN void cml_CMYKToRGBStandard_SB (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign){
  CML_UNUSED(cm);
  while(count){

    buf[0] = 1.f - buf[0];
    buf[1] = 1.f - buf[1];
    buf[2] = 1.f - buf[2];

    buf += floatAlign;
    count--;
  }
}


CML_HIDDEN void cml_CMYKToRGBUCR (const CMLColorMachine* cm, float* CML_RESTRICT out, const float* CML_RESTRICT in, size_t count){
  CML_UNUSED(cm);
  while(count){

    out[0] = 1.f - (in[0]+in[3]);
    out[1] = 1.f - (in[1]+in[3]);
    out[2] = 1.f - (in[2]+in[3]);

    in += CML_CMYK_NUMCHANNELS;
    out += CML_RGB_NUMCHANNELS;
    count--;
  }
}


CML_HIDDEN void cml_CMYKToRGBUCR_SB (const CMLColorMachine* cm, float* buf, size_t count, CMLuint32 floatAlign){
  CML_UNUSED(cm);
  while(count){

    buf[0] = 1.f - (buf[0]+buf[3]);
    buf[1] = 1.f - (buf[1]+buf[3]);
    buf[2] = 1.f - (buf[2]+buf[3]);

    buf += floatAlign;
    count--;
  }
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

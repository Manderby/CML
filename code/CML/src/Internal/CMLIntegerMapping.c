
#include "../CML.h"
#include "CMLColorMachineState.h"



CML_HIDEF void cml_Data8WithFloatFloor(uint8* out, float in, uint8 offset, float range){
  *out = offset + (uint8)(in*range);
}
CML_HIDEF void cml_Data16WithFloatFloor(uint16* out, float in, uint16 offset, float range){
  *out = offset + (uint8)(in*range);
}
CML_HIDEF void cml_Data8WithFloatBox(uint8* out, float in, uint8 offset, float range){
  *out = offset + (uint8)(in*range + .5f);
}
CML_HIDEF void cml_Data16WithFloatBox(uint16* out, float in, uint16 offset, float range){
  *out = offset + (uint8)(in*range + .5f);
}
CML_HIDEF void cml_Data8WithFloatInterval(uint8* out, float in, uint8 offset, float range){
  *out = offset + ((in == 1.f) ? (uint8)range : (uint8)(in*(range + 1.f)));
}
CML_HIDEF void cml_Data16WithFloatInterval(uint16* out, float in, uint16 offset, float range){
  *out = offset + ((in == 1.f) ? (uint16)range : (uint16)(in*(range + 1.f)));
}



CML_HIDEF void cml_Data8WithFloat1Floor(const CMLColorMachine* cm, uint8* CML_RESTRICT out, const float* CML_RESTRICT in){
  cml_Data8WithFloatFloor(&(out[0]), in[0], cm->inputoutput.offset8Bit[0], cm->inputoutput.range8Bit[0]);
}
CML_HIDEF void cml_Data8WithFloat3Floor(const CMLColorMachine* cm, uint8* CML_RESTRICT out, const float* CML_RESTRICT in){
  cml_Data8WithFloatFloor(&(out[0]), in[0], cm->inputoutput.offset8Bit[0], cm->inputoutput.range8Bit[0]);
  cml_Data8WithFloatFloor(&(out[1]), in[1], cm->inputoutput.offset8Bit[1], cm->inputoutput.range8Bit[1]);
  cml_Data8WithFloatFloor(&(out[2]), in[2], cm->inputoutput.offset8Bit[2], cm->inputoutput.range8Bit[2]);
}
CML_HIDEF void cml_Data8WithFloat4Floor(const CMLColorMachine* cm, uint8* CML_RESTRICT out, const float* CML_RESTRICT in){
  cml_Data8WithFloatFloor(&(out[0]), in[0], cm->inputoutput.offset8Bit[0], cm->inputoutput.range8Bit[0]);
  cml_Data8WithFloatFloor(&(out[1]), in[1], cm->inputoutput.offset8Bit[1], cm->inputoutput.range8Bit[1]);
  cml_Data8WithFloatFloor(&(out[2]), in[2], cm->inputoutput.offset8Bit[2], cm->inputoutput.range8Bit[2]);
  cml_Data8WithFloatFloor(&(out[3]), in[3], cm->inputoutput.offset8Bit[3], cm->inputoutput.range8Bit[3]);
}



CML_HIDEF void cml_Data8WithFloat1Box(const CMLColorMachine* cm, uint8* CML_RESTRICT out, const float* CML_RESTRICT in){
  cml_Data8WithFloatBox(&(out[0]), in[0], cm->inputoutput.offset8Bit[0], cm->inputoutput.range8Bit[0]);
}
CML_HIDEF void cml_Data8WithFloat3Box(const CMLColorMachine* cm, uint8* CML_RESTRICT out, const float* CML_RESTRICT in){
  cml_Data8WithFloatBox(&(out[0]), in[0], cm->inputoutput.offset8Bit[0], cm->inputoutput.range8Bit[0]);
  cml_Data8WithFloatBox(&(out[1]), in[1], cm->inputoutput.offset8Bit[1], cm->inputoutput.range8Bit[1]);
  cml_Data8WithFloatBox(&(out[2]), in[2], cm->inputoutput.offset8Bit[2], cm->inputoutput.range8Bit[2]);
}
CML_HIDEF void cml_Data8WithFloat4Box(const CMLColorMachine* cm, uint8* CML_RESTRICT out, const float* CML_RESTRICT in){
  cml_Data8WithFloatBox(&(out[0]), in[0], cm->inputoutput.offset8Bit[0], cm->inputoutput.range8Bit[0]);
  cml_Data8WithFloatBox(&(out[1]), in[1], cm->inputoutput.offset8Bit[1], cm->inputoutput.range8Bit[1]);
  cml_Data8WithFloatBox(&(out[2]), in[2], cm->inputoutput.offset8Bit[2], cm->inputoutput.range8Bit[2]);
  cml_Data8WithFloatBox(&(out[3]), in[3], cm->inputoutput.offset8Bit[3], cm->inputoutput.range8Bit[3]);
}



CML_HIDEF void cml_Data8WithFloat1Interval(const CMLColorMachine* cm, uint8* CML_RESTRICT out, const float* CML_RESTRICT in){
  cml_Data8WithFloatInterval(&(out[0]), in[0], cm->inputoutput.offset8Bit[0], cm->inputoutput.range8Bit[0]);
}
CML_HIDEF void cml_Data8WithFloat3Interval(const CMLColorMachine* cm, uint8* CML_RESTRICT out, const float* CML_RESTRICT in){
  cml_Data8WithFloatInterval(&(out[0]), in[0], cm->inputoutput.offset8Bit[0], cm->inputoutput.range8Bit[0]);
  cml_Data8WithFloatInterval(&(out[1]), in[1], cm->inputoutput.offset8Bit[1], cm->inputoutput.range8Bit[1]);
  cml_Data8WithFloatInterval(&(out[2]), in[2], cm->inputoutput.offset8Bit[2], cm->inputoutput.range8Bit[2]);
}
CML_HIDEF void cml_Data8WithFloat4Interval(const CMLColorMachine* cm, uint8* CML_RESTRICT out, const float* CML_RESTRICT in){
  cml_Data8WithFloatInterval(&(out[0]), in[0], cm->inputoutput.offset8Bit[0], cm->inputoutput.range8Bit[0]);
  cml_Data8WithFloatInterval(&(out[1]), in[1], cm->inputoutput.offset8Bit[1], cm->inputoutput.range8Bit[1]);
  cml_Data8WithFloatInterval(&(out[2]), in[2], cm->inputoutput.offset8Bit[2], cm->inputoutput.range8Bit[2]);
  cml_Data8WithFloatInterval(&(out[3]), in[3], cm->inputoutput.offset8Bit[3], cm->inputoutput.range8Bit[3]);
}



CML_HIDEF void cml_Data16WithFloat1Floor(const CMLColorMachine* cm, uint16* CML_RESTRICT out, const float* CML_RESTRICT in){
  cml_Data16WithFloatFloor(&(out[0]), in[0], cm->inputoutput.offset16Bit[0], cm->inputoutput.range16Bit[0]);
}
CML_HIDEF void cml_Data16WithFloat3Floor(const CMLColorMachine* cm, uint16* CML_RESTRICT out, const float* CML_RESTRICT in){
  cml_Data16WithFloatFloor(&(out[0]), in[0], cm->inputoutput.offset16Bit[0], cm->inputoutput.range16Bit[0]);
  cml_Data16WithFloatFloor(&(out[1]), in[1], cm->inputoutput.offset16Bit[1], cm->inputoutput.range16Bit[1]);
  cml_Data16WithFloatFloor(&(out[2]), in[2], cm->inputoutput.offset16Bit[2], cm->inputoutput.range16Bit[2]);
}
CML_HIDEF void cml_Data16WithFloat4Floor(const CMLColorMachine* cm, uint16* CML_RESTRICT out, const float* CML_RESTRICT in){
  cml_Data16WithFloatFloor(&(out[0]), in[0], cm->inputoutput.offset16Bit[0], cm->inputoutput.range16Bit[0]);
  cml_Data16WithFloatFloor(&(out[1]), in[1], cm->inputoutput.offset16Bit[1], cm->inputoutput.range16Bit[1]);
  cml_Data16WithFloatFloor(&(out[2]), in[2], cm->inputoutput.offset16Bit[2], cm->inputoutput.range16Bit[2]);
  cml_Data16WithFloatFloor(&(out[3]), in[3], cm->inputoutput.offset16Bit[3], cm->inputoutput.range16Bit[3]);
}



CML_HIDEF void cml_Data16WithFloat1Box(const CMLColorMachine* cm, uint16* CML_RESTRICT out, const float* CML_RESTRICT in){
  cml_Data16WithFloatBox(&(out[0]), in[0], cm->inputoutput.offset16Bit[0], cm->inputoutput.range16Bit[0]);
}
CML_HIDEF void cml_Data16WithFloat3Box(const CMLColorMachine* cm, uint16* CML_RESTRICT out, const float* CML_RESTRICT in){
  cml_Data16WithFloatBox(&(out[0]), in[0], cm->inputoutput.offset16Bit[0], cm->inputoutput.range16Bit[0]);
  cml_Data16WithFloatBox(&(out[1]), in[1], cm->inputoutput.offset16Bit[1], cm->inputoutput.range16Bit[1]);
  cml_Data16WithFloatBox(&(out[2]), in[2], cm->inputoutput.offset16Bit[2], cm->inputoutput.range16Bit[2]);
}
CML_HIDEF void cml_Data16WithFloat4Box(const CMLColorMachine* cm, uint16* CML_RESTRICT out, const float* CML_RESTRICT in){
  cml_Data16WithFloatBox(&(out[0]), in[0], cm->inputoutput.offset16Bit[0], cm->inputoutput.range16Bit[0]);
  cml_Data16WithFloatBox(&(out[1]), in[1], cm->inputoutput.offset16Bit[1], cm->inputoutput.range16Bit[1]);
  cml_Data16WithFloatBox(&(out[2]), in[2], cm->inputoutput.offset16Bit[2], cm->inputoutput.range16Bit[2]);
  cml_Data16WithFloatBox(&(out[3]), in[3], cm->inputoutput.offset16Bit[3], cm->inputoutput.range16Bit[3]);
}



CML_HIDEF void cml_Data16WithFloat1Interval(const CMLColorMachine* cm, uint16* CML_RESTRICT out, const float* CML_RESTRICT in){
  cml_Data16WithFloatInterval(&(out[0]), in[0], cm->inputoutput.offset16Bit[0], cm->inputoutput.range16Bit[0]);
}
CML_HIDEF void cml_Data16WithFloat3Interval(const CMLColorMachine* cm, uint16* CML_RESTRICT out, const float* CML_RESTRICT in){
  cml_Data16WithFloatInterval(&(out[0]), in[0], cm->inputoutput.offset16Bit[0], cm->inputoutput.range16Bit[0]);
  cml_Data16WithFloatInterval(&(out[1]), in[1], cm->inputoutput.offset16Bit[1], cm->inputoutput.range16Bit[1]);
  cml_Data16WithFloatInterval(&(out[2]), in[2], cm->inputoutput.offset16Bit[2], cm->inputoutput.range16Bit[2]);
}
CML_HIDEF void cml_Data16WithFloat4Interval(const CMLColorMachine* cm, uint16* CML_RESTRICT out, const float* CML_RESTRICT in){
  cml_Data16WithFloatInterval(&(out[0]), in[0], cm->inputoutput.offset16Bit[0], cm->inputoutput.range16Bit[0]);
  cml_Data16WithFloatInterval(&(out[1]), in[1], cm->inputoutput.offset16Bit[1], cm->inputoutput.range16Bit[1]);
  cml_Data16WithFloatInterval(&(out[2]), in[2], cm->inputoutput.offset16Bit[2], cm->inputoutput.range16Bit[2]);
  cml_Data16WithFloatInterval(&(out[3]), in[3], cm->inputoutput.offset16Bit[3], cm->inputoutput.range16Bit[3]);
}



CML_API void cmlSetIntegerMappingType(CMLColorMachine* cm, CMLIntegerMappingType type){
  switch(type){
  case CML_INTEGER_MAPPING_FLOOR:
    cm->Float1ToData8  = &cml_Data8WithFloat1Floor;
    cm->Float3ToData8  = &cml_Data8WithFloat3Floor;
    cm->Float4ToData8  = &cml_Data8WithFloat4Floor;
    cm->Float1ToData16 = &cml_Data16WithFloat1Floor;
    cm->Float3ToData16 = &cml_Data16WithFloat3Floor;
    cm->Float4ToData16 = &cml_Data16WithFloat4Floor;
    break;
  case CML_INTEGER_MAPPING_BOX:
    cm->Float1ToData8  = &cml_Data8WithFloat1Box;
    cm->Float3ToData8  = &cml_Data8WithFloat3Box;
    cm->Float4ToData8  = &cml_Data8WithFloat4Box;
    cm->Float1ToData16 = &cml_Data16WithFloat1Box;
    cm->Float3ToData16 = &cml_Data16WithFloat3Box;
    cm->Float4ToData16 = &cml_Data16WithFloat4Box;
    break;
  case CML_INTEGER_MAPPING_INTERVAL:
    cm->Float1ToData8  = &cml_Data8WithFloat1Interval;
    cm->Float3ToData8  = &cml_Data8WithFloat3Interval;
    cm->Float4ToData8  = &cml_Data8WithFloat4Interval;
    cm->Float1ToData16 = &cml_Data16WithFloat1Interval;
    cm->Float3ToData16 = &cml_Data16WithFloat3Interval;
    cm->Float4ToData16 = &cml_Data16WithFloat4Interval;
    break;
  default:
    #if CML_DEBUG
      cmlError("Invalid Integer mapping.");
    #endif
    return;
    break;
  }
  cm->inputoutput.integermapping = type;
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


#include "../CML.h"
#include "CMLColorMachineState.h"



CML_HIDEF void cml_FloatToData8Floor(uint8* out, float in, uint8 offset, float range){
  *out = offset + (uint8)(in * range);
}
CML_HIDEF void cml_FloatToData16Floor(uint16* out, float in, uint16 offset, float range){
  *out = offset + (uint8)(in * range);
}
CML_HIDEF void cml_FloatToData8Box(uint8* out, float in, uint8 offset, float range){
  *out = offset + (uint8)(in * range + .5f);
}
CML_HIDEF void cml_FloatToData16Box(uint16* out, float in, uint16 offset, float range){
  *out = offset + (uint8)(in * range + .5f);
}
CML_HIDEF void cml_FloatToData8Interval(uint8* out, float in, uint8 offset, float range){
  *out = offset + ((in == 1.f) ? (uint8)range : (uint8)(in * (range + 1.f)));
}
CML_HIDEF void cml_FloatToData16Interval(uint16* out, float in, uint16 offset, float range){
  *out = offset + ((in == 1.f) ? (uint16)range : (uint16)(in * (range + 1.f)));
}



CML_HIDEF void cml_Float1ToData8Floor(const CMLColorMachine* cm, uint8* CML_RESTRICT out, const float* CML_RESTRICT in){
  cml_FloatToData8Floor(&(out[0]), in[0], cm->inputoutput.offset8Bit[0], cm->inputoutput.range8Bit[0]);
}
CML_HIDEF void cml_Float3ToData8Floor(const CMLColorMachine* cm, uint8* CML_RESTRICT out, const float* CML_RESTRICT in){
  cml_FloatToData8Floor(&(out[0]), in[0], cm->inputoutput.offset8Bit[0], cm->inputoutput.range8Bit[0]);
  cml_FloatToData8Floor(&(out[1]), in[1], cm->inputoutput.offset8Bit[1], cm->inputoutput.range8Bit[1]);
  cml_FloatToData8Floor(&(out[2]), in[2], cm->inputoutput.offset8Bit[2], cm->inputoutput.range8Bit[2]);
}
CML_HIDEF void cml_Float4ToData8Floor(const CMLColorMachine* cm, uint8* CML_RESTRICT out, const float* CML_RESTRICT in){
  cml_FloatToData8Floor(&(out[0]), in[0], cm->inputoutput.offset8Bit[0], cm->inputoutput.range8Bit[0]);
  cml_FloatToData8Floor(&(out[1]), in[1], cm->inputoutput.offset8Bit[1], cm->inputoutput.range8Bit[1]);
  cml_FloatToData8Floor(&(out[2]), in[2], cm->inputoutput.offset8Bit[2], cm->inputoutput.range8Bit[2]);
  cml_FloatToData8Floor(&(out[3]), in[3], cm->inputoutput.offset8Bit[3], cm->inputoutput.range8Bit[3]);
}



CML_HIDEF void cml_Float1ToData8Box(const CMLColorMachine* cm, uint8* CML_RESTRICT out, const float* CML_RESTRICT in){
  cml_FloatToData8Box(&(out[0]), in[0], cm->inputoutput.offset8Bit[0], cm->inputoutput.range8Bit[0]);
}
CML_HIDEF void cml_Float3ToData8Box(const CMLColorMachine* cm, uint8* CML_RESTRICT out, const float* CML_RESTRICT in){
  cml_FloatToData8Box(&(out[0]), in[0], cm->inputoutput.offset8Bit[0], cm->inputoutput.range8Bit[0]);
  cml_FloatToData8Box(&(out[1]), in[1], cm->inputoutput.offset8Bit[1], cm->inputoutput.range8Bit[1]);
  cml_FloatToData8Box(&(out[2]), in[2], cm->inputoutput.offset8Bit[2], cm->inputoutput.range8Bit[2]);
}
CML_HIDEF void cml_Float4ToData8Box(const CMLColorMachine* cm, uint8* CML_RESTRICT out, const float* CML_RESTRICT in){
  cml_FloatToData8Box(&(out[0]), in[0], cm->inputoutput.offset8Bit[0], cm->inputoutput.range8Bit[0]);
  cml_FloatToData8Box(&(out[1]), in[1], cm->inputoutput.offset8Bit[1], cm->inputoutput.range8Bit[1]);
  cml_FloatToData8Box(&(out[2]), in[2], cm->inputoutput.offset8Bit[2], cm->inputoutput.range8Bit[2]);
  cml_FloatToData8Box(&(out[3]), in[3], cm->inputoutput.offset8Bit[3], cm->inputoutput.range8Bit[3]);
}



CML_HIDEF void cml_Float1ToData8Interval(const CMLColorMachine* cm, uint8* CML_RESTRICT out, const float* CML_RESTRICT in){
  cml_FloatToData8Interval(&(out[0]), in[0], cm->inputoutput.offset8Bit[0], cm->inputoutput.range8Bit[0]);
}
CML_HIDEF void cml_Float3ToData8Interval(const CMLColorMachine* cm, uint8* CML_RESTRICT out, const float* CML_RESTRICT in){
  cml_FloatToData8Interval(&(out[0]), in[0], cm->inputoutput.offset8Bit[0], cm->inputoutput.range8Bit[0]);
  cml_FloatToData8Interval(&(out[1]), in[1], cm->inputoutput.offset8Bit[1], cm->inputoutput.range8Bit[1]);
  cml_FloatToData8Interval(&(out[2]), in[2], cm->inputoutput.offset8Bit[2], cm->inputoutput.range8Bit[2]);
}
CML_HIDEF void cml_Float4ToData8Interval(const CMLColorMachine* cm, uint8* CML_RESTRICT out, const float* CML_RESTRICT in){
  cml_FloatToData8Interval(&(out[0]), in[0], cm->inputoutput.offset8Bit[0], cm->inputoutput.range8Bit[0]);
  cml_FloatToData8Interval(&(out[1]), in[1], cm->inputoutput.offset8Bit[1], cm->inputoutput.range8Bit[1]);
  cml_FloatToData8Interval(&(out[2]), in[2], cm->inputoutput.offset8Bit[2], cm->inputoutput.range8Bit[2]);
  cml_FloatToData8Interval(&(out[3]), in[3], cm->inputoutput.offset8Bit[3], cm->inputoutput.range8Bit[3]);
}



CML_HIDEF void cml_Float1ToData16Floor(const CMLColorMachine* cm, uint16* CML_RESTRICT out, const float* CML_RESTRICT in){
  cml_FloatToData16Floor(&(out[0]), in[0], cm->inputoutput.offset16Bit[0], cm->inputoutput.range16Bit[0]);
}
CML_HIDEF void cml_Float3ToData16Floor(const CMLColorMachine* cm, uint16* CML_RESTRICT out, const float* CML_RESTRICT in){
  cml_FloatToData16Floor(&(out[0]), in[0], cm->inputoutput.offset16Bit[0], cm->inputoutput.range16Bit[0]);
  cml_FloatToData16Floor(&(out[1]), in[1], cm->inputoutput.offset16Bit[1], cm->inputoutput.range16Bit[1]);
  cml_FloatToData16Floor(&(out[2]), in[2], cm->inputoutput.offset16Bit[2], cm->inputoutput.range16Bit[2]);
}
CML_HIDEF void cml_Float4ToData16Floor(const CMLColorMachine* cm, uint16* CML_RESTRICT out, const float* CML_RESTRICT in){
  cml_FloatToData16Floor(&(out[0]), in[0], cm->inputoutput.offset16Bit[0], cm->inputoutput.range16Bit[0]);
  cml_FloatToData16Floor(&(out[1]), in[1], cm->inputoutput.offset16Bit[1], cm->inputoutput.range16Bit[1]);
  cml_FloatToData16Floor(&(out[2]), in[2], cm->inputoutput.offset16Bit[2], cm->inputoutput.range16Bit[2]);
  cml_FloatToData16Floor(&(out[3]), in[3], cm->inputoutput.offset16Bit[3], cm->inputoutput.range16Bit[3]);
}



CML_HIDEF void cml_Float1ToData16Box(const CMLColorMachine* cm, uint16* CML_RESTRICT out, const float* CML_RESTRICT in){
  cml_FloatToData16Box(&(out[0]), in[0], cm->inputoutput.offset16Bit[0], cm->inputoutput.range16Bit[0]);
}
CML_HIDEF void cml_Float3ToData16Box(const CMLColorMachine* cm, uint16* CML_RESTRICT out, const float* CML_RESTRICT in){
  cml_FloatToData16Box(&(out[0]), in[0], cm->inputoutput.offset16Bit[0], cm->inputoutput.range16Bit[0]);
  cml_FloatToData16Box(&(out[1]), in[1], cm->inputoutput.offset16Bit[1], cm->inputoutput.range16Bit[1]);
  cml_FloatToData16Box(&(out[2]), in[2], cm->inputoutput.offset16Bit[2], cm->inputoutput.range16Bit[2]);
}
CML_HIDEF void cml_Float4ToData16Box(const CMLColorMachine* cm, uint16* CML_RESTRICT out, const float* CML_RESTRICT in){
  cml_FloatToData16Box(&(out[0]), in[0], cm->inputoutput.offset16Bit[0], cm->inputoutput.range16Bit[0]);
  cml_FloatToData16Box(&(out[1]), in[1], cm->inputoutput.offset16Bit[1], cm->inputoutput.range16Bit[1]);
  cml_FloatToData16Box(&(out[2]), in[2], cm->inputoutput.offset16Bit[2], cm->inputoutput.range16Bit[2]);
  cml_FloatToData16Box(&(out[3]), in[3], cm->inputoutput.offset16Bit[3], cm->inputoutput.range16Bit[3]);
}



CML_HIDEF void cml_Float1ToData16Interval(const CMLColorMachine* cm, uint16* CML_RESTRICT out, const float* CML_RESTRICT in){
  cml_FloatToData16Interval(&(out[0]), in[0], cm->inputoutput.offset16Bit[0], cm->inputoutput.range16Bit[0]);
}
CML_HIDEF void cml_Float3ToData16Interval(const CMLColorMachine* cm, uint16* CML_RESTRICT out, const float* CML_RESTRICT in){
  cml_FloatToData16Interval(&(out[0]), in[0], cm->inputoutput.offset16Bit[0], cm->inputoutput.range16Bit[0]);
  cml_FloatToData16Interval(&(out[1]), in[1], cm->inputoutput.offset16Bit[1], cm->inputoutput.range16Bit[1]);
  cml_FloatToData16Interval(&(out[2]), in[2], cm->inputoutput.offset16Bit[2], cm->inputoutput.range16Bit[2]);
}
CML_HIDEF void cml_Float4ToData16Interval(const CMLColorMachine* cm, uint16* CML_RESTRICT out, const float* CML_RESTRICT in){
  cml_FloatToData16Interval(&(out[0]), in[0], cm->inputoutput.offset16Bit[0], cm->inputoutput.range16Bit[0]);
  cml_FloatToData16Interval(&(out[1]), in[1], cm->inputoutput.offset16Bit[1], cm->inputoutput.range16Bit[1]);
  cml_FloatToData16Interval(&(out[2]), in[2], cm->inputoutput.offset16Bit[2], cm->inputoutput.range16Bit[2]);
  cml_FloatToData16Interval(&(out[3]), in[3], cm->inputoutput.offset16Bit[3], cm->inputoutput.range16Bit[3]);
}



CML_DEF void cmlSetIntegerMappingType(CMLColorMachine* cm, CMLIntegerMappingType type){
  switch(type){
  case CML_INTEGER_MAPPING_FLOOR:
    cm->Float1ToData8  = &cml_Float1ToData8Floor;
    cm->Float3ToData8  = &cml_Float3ToData8Floor;
    cm->Float4ToData8  = &cml_Float4ToData8Floor;
    cm->Float1ToData16 = &cml_Float1ToData16Floor;
    cm->Float3ToData16 = &cml_Float3ToData16Floor;
    cm->Float4ToData16 = &cml_Float4ToData16Floor;
    break;
  case CML_INTEGER_MAPPING_BOX:
    cm->Float1ToData8  = &cml_Float1ToData8Box;
    cm->Float3ToData8  = &cml_Float3ToData8Box;
    cm->Float4ToData8  = &cml_Float4ToData8Box;
    cm->Float1ToData16 = &cml_Float1ToData16Box;
    cm->Float3ToData16 = &cml_Float3ToData16Box;
    cm->Float4ToData16 = &cml_Float4ToData16Box;
    break;
  case CML_INTEGER_MAPPING_INTERVAL:
    cm->Float1ToData8  = &cml_Float1ToData8Interval;
    cm->Float3ToData8  = &cml_Float3ToData8Interval;
    cm->Float4ToData8  = &cml_Float4ToData8Interval;
    cm->Float1ToData16 = &cml_Float1ToData16Interval;
    cm->Float3ToData16 = &cml_Float3ToData16Interval;
    cm->Float4ToData16 = &cml_Float4ToData16Interval;
    break;
  default:
    #if CML_DEBUG
      cmlError("Invalid Integer mapping.");
    #endif
    return;
    break;
  }
  cm->inputoutput.integerMapping = type;
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

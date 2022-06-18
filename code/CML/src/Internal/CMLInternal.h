
#include <stdlib.h>

// todo: make inline functions or ranges
#define CML_MAX(a, b) (((a)>(b))?(a):(b))
#define CML_MIN(a, b) (((a)<(b))?(a):(b))



struct CMLFunction{
  size_t refCount;
  size_t dataSize;
  void* data;
  CMLDefinitionRange defRange;
  CMLFunctionEvaluator evaluator;
  CMLFunctionDesctructor destructor;
};


struct CMLResponseCurve{
  CMLFunction* forwardFunc;     // converting from luminance space
  CMLFunction* backwardFunc;    // converting to luminance space
  CMLResponseCurveType responseType;
};


typedef struct CMLIllumination  CMLIllumination;
struct CMLIllumination{
  CMLIlluminationType           type;
  CMLFunction*                  spectrum;
  float                         temperature;
};

struct CMLObserver{
  CMLObserverType               type;
  CMLFunction*                  specDistFunctions[3];
};


CML_HAPI void cml_ComputeObserverWhitepointsAndRadiometricScale(CMLColorMachine* cm);

// type:                  Defines, what spectral distribution functions to use.
// illumination:          The spectrum function of the desired reference
//                        illumination. This observer will duplicate the
//                        function. If NULL, the illuminatino will not change.
// colorimetricBase:      The Y value of the reference illumination.
//                        In colorimetry, this is usually 1 or 100.
//                        If you use 0, computation is radiometric.
CML_HAPI void cml_InitObserver(
  CMLColorMachine* cm,
  CMLObserver* observer,
  CMLObserverType type,
  const CMLIntegration* integration);

CML_HAPI void cml_SetObserverIllumination(
  CMLColorMachine* cm,
  CMLObserver* observer,
  CMLIllumination* illumination);

CML_HAPI void cml_ClearObserver(CMLColorMachine* cm, CMLObserver* observer);

CML_HAPI CMLObserverType cml_GetObserverType(const CMLObserver* observer);

CML_HAPI CMLFunction* const * cml_GetObserverSpecDistFunctions(const CMLObserver* observer);
CML_HAPI const CMLFunction* cml_GetObserverSpecDistFunction(const CMLObserver* observer, size_t index);


CML_HAPI void cml_InitIlluminationDuplicate(CMLIllumination* illumination, const CMLIllumination* src);
CML_HAPI void cml_InitIlluminationWithType(CMLIllumination* illumination, CMLIlluminationType type, float temperature, CMLFunction* const * specDistFuncs);
CML_HAPI void cml_InitIlluminationWithCustomSpectrum(CMLIllumination* illumination, const CMLFunction* spectrum, CMLFunction* const * specDistFuncs);
CML_HAPI void cml_InitIlluminationWithCustomWhitePoint(CMLIllumination* illumination, const CMLVec3 whitePointYxy);

CML_HAPI void cml_ClearIllumination(CMLIllumination* illumination);

CML_HAPI CMLIlluminationType cml_GetIlluminationType(const CMLIllumination* illumination);
CML_HAPI const CMLFunction* cml_GetIlluminationSpectrum(const CMLIllumination* illumination);
CML_HAPI float cml_GetIlluminationCorrelatedColorTemperature(const CMLIllumination* illumination);



CML_HIDEF float cml_Eval(const CMLFunction* function, float x){
  return function->evaluator(function->data, x);
}






CML_IDEF void* cml_Malloc(size_t size){
  void* ptr; // Declaration before implementation.
  #if CML_DEBUG
    if(size < 1)
      cmlError("size is smaller than 1 .");
  #endif
  ptr = malloc(size);
  #if CML_DEBUG
    if(!ptr)
      {cmlError("out of memory."); exit(1); return CML_NULL;}
    // The exit call has been introduced as this is such a severe problem
    // that all functions rely on its functionality. Here, the debug version
    // differs from the non-debug version.
  #endif
  return ptr;
}


#define cml__START_COUNT_LOOP(count)\
  while(count){

#define cml__END_COUNT_LOOP(outchannels, inchannels)\
    out += outchannels;\
    in += inchannels;\
    count--;\
  }
  
#define cml__END_COUNT_LOOP_SB(numchannels)\
    buf += numchannels;\
    count--;\
  }


// ////////////////////////////////////
// XYZ to Yxy
// ////////////////////////////////////

#define cml_ConvertXYZToYxy(out, in, whitePointYxy) \
  float divisor;\
  divisor = (in[0] + in[1] + in[2]);\
  float Y = in[1];\
  if(divisor == 0.f){\
    if(whitePointYxy){\
      out[2] = whitePointYxy[2];\
      out[1] = whitePointYxy[1];\
    }else{\
      out[2] = 0.f;\
      out[1] = 0.f;\
    }\
  }else{\
    float factor = cmlInverse(divisor);\
    out[2] = in[1] * factor;\
    out[1] = in[0] * factor;\
  }\
  out[0] = Y;

CML_HIDEF void cml_OneXYZToYxy(float* CML_RESTRICT out, const float* CML_RESTRICT in, const CMLVec3 whitePointYxy){
  cml_ConvertXYZToYxy(out, in, whitePointYxy);
}

CML_HIDEF void cml_OneXYZToYxy_SB(float* CML_RESTRICT buf, const CMLVec3 whitePointYxy){
  cml_ConvertXYZToYxy(buf, buf, whitePointYxy);
}

CML_HIDEF void cml_XYZToYxy(float* CML_RESTRICT out, const float* CML_RESTRICT in, const CMLVec3 whitePointYxy, size_t count){
  cml__START_COUNT_LOOP(count);
  cml_OneXYZToYxy(out, in, whitePointYxy);
  cml__END_COUNT_LOOP(CML_Yxy_NUMCHANNELS, CML_XYZ_NUMCHANNELS);
}

CML_HIDEF void cml_XYZToYxy_SB(float* CML_RESTRICT buf, const CMLVec3 whitePointYxy, size_t count, size_t floatAlign){
  cml__START_COUNT_LOOP(count);
  cml_OneXYZToYxy_SB(buf, whitePointYxy);
  cml__END_COUNT_LOOP_SB(floatAlign);
}


// ////////////////////////////////////
// XYZ to RGB
// ////////////////////////////////////

// todo: make mulVec SB
#define cml_ConvertXYZToRGB(out, in, XYZToRGBMatrix, linearToRResponse, linearToGResponse, linearToBResponse) \
  CMLVec3 RGBp;\
  cmlMulMat33Vec3(RGBp, XYZToRGBMatrix, in);\
  out[0] = cml_Eval(linearToRResponse, RGBp[0]);\
  out[1] = cml_Eval(linearToGResponse, RGBp[1]);\
  out[2] = cml_Eval(linearToBResponse, RGBp[2]);

CML_HIDEF void cml_OneXYZToRGB(float* CML_RESTRICT out, const float* CML_RESTRICT in, const CMLMat33 XYZToRGBMatrix, const CMLFunction* linearToRResponse, const CMLFunction* linearToGResponse, const CMLFunction* linearToBResponse){
  cml_ConvertXYZToRGB(out, in, XYZToRGBMatrix, linearToRResponse, linearToGResponse, linearToBResponse);
}

CML_HIDEF void cml_OneXYZToRGB_SB(float* buf, const CMLMat33 XYZToRGBMatrix, const CMLFunction* linearToRResponse, const CMLFunction* linearToGResponse, const CMLFunction* linearToBResponse){
  cml_ConvertXYZToRGB(buf, buf, XYZToRGBMatrix, linearToRResponse, linearToGResponse, linearToBResponse);
}

CML_HIDEF void cml_XYZToRGB(float* CML_RESTRICT out, const float* CML_RESTRICT in, size_t count, const CMLMat33 XYZToRGBMatrix, const CMLFunction* linearToRResponse, const CMLFunction* linearToGResponse, const CMLFunction* linearToBResponse){
  cml__START_COUNT_LOOP(count);
  cml_OneXYZToRGB(out, in, XYZToRGBMatrix, linearToRResponse, linearToGResponse, linearToBResponse);
  cml__END_COUNT_LOOP(CML_RGB_NUMCHANNELS, CML_XYZ_NUMCHANNELS);
}

CML_HIDEF void cml_XYZToRGB_SB(float* buf, size_t count, size_t floatAlign, const CMLMat33 XYZToRGBMatrix, const CMLFunction* linearToRResponse, const CMLFunction* linearToGResponse, const CMLFunction* linearToBResponse){
  cml__START_COUNT_LOOP(count);
  cml_OneXYZToRGB_SB(buf, XYZToRGBMatrix, linearToRResponse, linearToGResponse, linearToBResponse);
  cml__END_COUNT_LOOP_SB(floatAlign);
}


// ////////////////////////////////////
// Yxy to XYZ
// ////////////////////////////////////

#define cml_ConvertYxyToXYZ(out, in, whitePointXYZ) \
  if(in[2] == 0.f){\
    if(whitePointXYZ){\
      out[0] = ((float*)whitePointXYZ)[0];\
      out[2] = ((float*)whitePointXYZ)[2];\
    }else{\
      out[0] = 0.f;\
      out[2] = 0.f;\
    }\
    out[1] = 0.f;\
  }else{\
    out[2]  = in[0] / in[2];\
    float Y = out[2] * in[1];\
    out[1]  = in[0];\
    out[0]  = Y;\
    out[2] -= out[0] + out[1];\
  }

CML_HIDEF void cml_OneYxyToXYZ(float* CML_RESTRICT out, const float* CML_RESTRICT in, const CMLVec3 whitePointXYZ){
  cml_ConvertYxyToXYZ(out, in, whitePointXYZ);
}

CML_HIDEF void cml_OneYxyToXYZ_SB(float* buf, const CMLVec3 whitePointXYZ){
  cml_ConvertYxyToXYZ(buf, buf, whitePointXYZ);
}

CML_HIDEF void cml_YxyToXYZ(float* CML_RESTRICT out, const float* CML_RESTRICT in, const CMLVec3 whitePointXYZ, size_t count){
  cml__START_COUNT_LOOP(count);
  cml_OneYxyToXYZ(out, in, whitePointXYZ);
  cml__END_COUNT_LOOP(CML_XYZ_NUMCHANNELS, CML_Yxy_NUMCHANNELS);
}

CML_HIDEF void cml_YxyToXYZ_SB(float* buf, const CMLVec3 whitePointXYZ, size_t count, size_t floatAlign){
  cml__START_COUNT_LOOP(count);
  cml_OneYxyToXYZ_SB(buf, whitePointXYZ);
  cml__END_COUNT_LOOP_SB(floatAlign);
}

// ////////////////////////////////////
// Yupvp to Yxy
// ////////////////////////////////////


#define cml_ConvertYupvpToYxy(out, in, whitePointYxy) \
  float divisor;\
  out[0] = in[0];\
  divisor = 6.f * in[1] - 16.f * in[2] + 12.f;\
  if(divisor == 0.f){\
    if(whitePointYxy){\
      out[1] = whitePointYxy[1];\
      out[2] = whitePointYxy[2];\
    }else{\
      out[1] = 0.f;\
      out[2] = 0.f;\
    }\
  }else{\
    float factor = cmlInverse(divisor);\
    out[1] = 9.f * in[1] * factor;\
    out[2] = 4.f * in[2] * factor;\
  }

CML_HIDEF void cml_OneYupvpToYxy(float* CML_RESTRICT out, const float* CML_RESTRICT in, const CMLVec3 whitePointYxy){
  cml_ConvertYupvpToYxy(out, in, whitePointYxy);
}
CML_HIDEF void cml_OneYupvpToYxy_SB(float* buf, const CMLVec3 whitePointYxy){
  cml_ConvertYupvpToYxy(buf, buf, whitePointYxy);
}

CML_HIDEF void cml_YupvpToYxy(float* CML_RESTRICT out, const float* CML_RESTRICT in, const CMLVec3 whitePointYxy, size_t count){
  cml__START_COUNT_LOOP(count);
  cml_OneYupvpToYxy(out, in, whitePointYxy);
  cml__END_COUNT_LOOP(CML_Yxy_NUMCHANNELS, CML_Yupvp_NUMCHANNELS);
}

CML_HIDEF void cml_YupvpToYxy_SB(float* buf, const CMLVec3 whitePointYxy, size_t count, size_t floatAlign){
  cml__START_COUNT_LOOP(count);
  cml_OneYupvpToYxy_SB(buf, whitePointYxy);
  cml__END_COUNT_LOOP_SB(floatAlign);
}


// ////////////////////////////////////
// Luv to Yupvp
// ////////////////////////////////////

#define cml_ConvertLuvToYupvp(out, in, whitePointYupvp, LtoLinearResponse) \
  float divisor;\
  float yr;\
  yr = cml_Eval(LtoLinearResponse, in[0] * .01f);\
  divisor = 13.f * in[0];\
  out[0] = yr * whitePointYupvp[0];\
  if(divisor == 0.f){\
    out[1] = whitePointYupvp[1];\
    out[2] = whitePointYupvp[2];\
  }else{\
    float factor = cmlInverse(divisor);\
    out[1] = (in[1] * factor) + whitePointYupvp[1];\
    out[2] = (in[2] * factor) + whitePointYupvp[2];\
  }

CML_HIDEF void cml_OneLuvToYupvp(float* CML_RESTRICT out, const float* CML_RESTRICT in, const CMLVec3 whitePointYupvp, const CMLFunction* LtoLinearResponse){
  cml_ConvertLuvToYupvp(out, in, whitePointYupvp, LtoLinearResponse);
}
CML_HIDEF void cml_OneLuvToYupvp_SB(float* buf, const CMLVec3 whitePointYupvp, const CMLFunction* LtoLinearResponse){
  cml_ConvertLuvToYupvp(buf, buf, whitePointYupvp, LtoLinearResponse);
}

CML_HIDEF void cml_LuvToYupvp(float* CML_RESTRICT out, const float* CML_RESTRICT in, size_t count, const CMLVec3 whitePointYupvp, const CMLFunction* LtoLinearResponse){
  cml__START_COUNT_LOOP(count);
  cml_OneLuvToYupvp(out, in, whitePointYupvp, LtoLinearResponse);
  cml__END_COUNT_LOOP(CML_Yupvp_NUMCHANNELS, CML_Luv_NUMCHANNELS);
}

CML_HIDEF void cml_LuvToYupvp_SB(float* buf, size_t count, size_t floatAlign, const CMLVec3 whitePointYupvp, const CMLFunction* LtoLinearResponse){
  cml__START_COUNT_LOOP(count);
  cml_OneLuvToYupvp_SB(buf, whitePointYupvp, LtoLinearResponse);
  cml__END_COUNT_LOOP_SB(floatAlign);
}



// ////////////////////////////////////
// Yxy to Yupvp
// ////////////////////////////////////


#define cml_ConvertYxyToYupvp(out, in, whitePointYupvp) \
  float divisor;\
  out[0] = in[0];\
  divisor = -2.f * in[1] + 12.f * in[2] + 3.f;\
  if(divisor == 0.f){\
    if(whitePointYupvp){\
      out[1] = whitePointYupvp[1];\
      out[2] = whitePointYupvp[2];\
    }else{\
      out[1] = 0.f;\
      out[2] = 0.f;\
    }\
  }else{\
    float factor = cmlInverse(divisor);\
    out[1] = 4.f * in[1] * factor;\
    out[2] = 9.f * in[2] * factor;\
  }\

CML_HIDEF void cml_OneYxyToYupvp(float* CML_RESTRICT out, const float* CML_RESTRICT in, const CMLVec3 whitePointYupvp){
  cml_ConvertYxyToYupvp(out, in, whitePointYupvp);
}

CML_HIDEF void cml_OneYxyToYupvp_SB(float* buf, const CMLVec3 whitePointYupvp){
  cml_ConvertYxyToYupvp(buf, buf, whitePointYupvp);
}

CML_HIDEF void cml_YxyToYupvp(float* CML_RESTRICT out, const float* CML_RESTRICT in, const CMLVec3 whitePointYupvp, size_t count){
  cml__START_COUNT_LOOP(count);
  cml_OneYxyToYupvp(out, in, whitePointYupvp);
  cml__END_COUNT_LOOP(CML_Yupvp_NUMCHANNELS, CML_Yxy_NUMCHANNELS);
}

CML_HIDEF void cml_YxyToYupvp_SB(float* buf, const CMLVec3 whitePointYupvp, size_t count, size_t floatAlign){
  cml__START_COUNT_LOOP(count);
  cml_OneYxyToYupvp_SB(buf, whitePointYupvp);
  cml__END_COUNT_LOOP_SB(floatAlign);
}



// ////////////////////////////////////
// Yupvp to Luv
// ////////////////////////////////////

#define cml_ConvertYupvpToLuv(out, in, whitePointYupvp, LineartoLResponse) \
  float yr = in[0] / whitePointYupvp[0];\
  float fy = cml_Eval(LineartoLResponse, yr);\
  out[0] = 100.f * fy;\
  out[1] = 13.f * out[0] * (in[1] - whitePointYupvp[1]);\
  out[2] = 13.f * out[0] * (in[2] - whitePointYupvp[2]);

CML_HIDEF void cml_OneYupvpToLuv(float* CML_RESTRICT out, const float* CML_RESTRICT in, const CMLVec3 whitePointYupvp, const CMLFunction* LineartoLResponse){
  cml_ConvertYupvpToLuv(out, in, whitePointYupvp, LineartoLResponse);
}

CML_HIDEF void cml_OneYupvpToLuv_SB(float* buf, const CMLVec3 whitePointYupvp, const CMLFunction* LineartoLResponse){
  cml_ConvertYupvpToLuv(buf, buf, whitePointYupvp, LineartoLResponse);
}

CML_HIDEF void cml_YupvpToLuv(float* CML_RESTRICT out, const float* CML_RESTRICT in, size_t count, const CMLVec3 whitePointYupvp, const CMLFunction* LineartoLResponse){
  cml__START_COUNT_LOOP(count);
  cml_OneYupvpToLuv(out, in, whitePointYupvp, LineartoLResponse);
  cml__END_COUNT_LOOP(CML_Luv_NUMCHANNELS, CML_Yupvp_NUMCHANNELS);
}

CML_HIDEF void cml_YupvpToLuv_SB(float* buf, size_t count, size_t floatAlign, const CMLVec3 whitePointYupvp, const CMLFunction* LineartoLResponse){
  cml__START_COUNT_LOOP(count);
  cml_OneYupvpToLuv_SB(buf, whitePointYupvp, LineartoLResponse);
  cml__END_COUNT_LOOP_SB(floatAlign);
}


// ////////////////////////////////////
// Yupvp to Luv
// ////////////////////////////////////

#define cml_ConvertYuvToYupvp(out, in) \
  out[0] = in[0];\
  out[1] = in[1];\
  out[2] = in[2] * 1.5f;

CML_HIDEF void cml_OneYuvToYupvp(float* CML_RESTRICT out, const float* CML_RESTRICT in){
  cml_ConvertYuvToYupvp(out, in);
}
CML_HIDEF void cml_OneYuvToYupvp_SB(float* buf){
  cml_ConvertYuvToYupvp(buf, buf);
}

CML_HIDEF void cml_YuvToYupvp(float* CML_RESTRICT out, const float* CML_RESTRICT in, size_t count){
  cml__START_COUNT_LOOP(count);
  cml_OneYuvToYupvp(out, in);
  cml__END_COUNT_LOOP(CML_Yupvp_NUMCHANNELS, CML_Yuv_NUMCHANNELS);
}

CML_HIDEF void cml_YuvToYupvp_SB(float* buf, size_t count, size_t floatAlign){
  cml__START_COUNT_LOOP(count);
  cml_OneYuvToYupvp_SB(buf);
  cml__END_COUNT_LOOP_SB(floatAlign);
}


// ////////////////////////////////////
// Luv to Yupvp
// ////////////////////////////////////

#define cml_ConvertYupvpToYuv(out, in) \
  out[0] = in[0];\
  out[1] = in[1];\
  out[2] = in[2] * 0.666666666666667f;

CML_HIDEF void cml_OneYupvpToYuv(float* CML_RESTRICT out, const float* CML_RESTRICT in){
  cml_ConvertYupvpToYuv(out, in);
}
CML_HIDEF void cml_OneYupvpToYuv_SB(float* buf){
  cml_ConvertYupvpToYuv(buf, buf);
}

CML_HIDEF void cml_YupvpToYuv(float* CML_RESTRICT out, const float* CML_RESTRICT in, size_t count){
  cml__START_COUNT_LOOP(count);
  cml_OneYupvpToYuv(out, in);
  cml__END_COUNT_LOOP(CML_Yuv_NUMCHANNELS, CML_Yupvp_NUMCHANNELS);
}

CML_HIDEF void cml_YupvpToYuv_SB(float* buf, size_t count, size_t floatAlign){
  cml__START_COUNT_LOOP(count);
  cml_OneYupvpToYuv_SB(buf);
  cml__END_COUNT_LOOP_SB(floatAlign);
}


// ////////////////////////////////////
// Lab to Lch
// ////////////////////////////////////

#define cml_ConvertLabToLch(out, in) \
  out[0] = in[0];\
  float length = cmlLength2(&(in[1]));\
  if(length == 0.f){\
    out[2] = 0.f;\
  }else{\
    out[2] = cmlRadToDeg(atan2f(in[2], in[1]));\
    if(out[2] < 0.f){out[2] += 360.f;}\
  }\
  out[1] = length;

CML_HIDEF void cml_OneLabToLch(float* CML_RESTRICT out, const float* CML_RESTRICT in){
  cml_ConvertLabToLch(out, in);
}
CML_HIDEF void cml_OneLabToLch_SB(float* buf){
  cml_ConvertLabToLch(buf, buf);
}

CML_HIDEF void cml_LabToLch(float* CML_RESTRICT out, const float* CML_RESTRICT in, size_t count){
  cml__START_COUNT_LOOP(count);
  cml_OneLabToLch(out, in);
  cml__END_COUNT_LOOP(CML_Lch_NUMCHANNELS, CML_Lab_NUMCHANNELS);
}

CML_HIDEF void cml_LabToLch_SB(float* buf, size_t count, size_t floatAlign){
  cml__START_COUNT_LOOP(count);
  cml_OneLabToLch_SB(buf);
  cml__END_COUNT_LOOP_SB(floatAlign);
}


// ////////////////////////////////////
// RGB to XYZ
// ////////////////////////////////////

// todo: make mulVec SB
#define cml_ConvertRGBToXYZ(out, in, RGBToXYZMatrix, RToLinearResponse, GToLinearResponse, BToLinearResponse) \
  float RGBp[3];\
  RGBp[0] = cml_Eval(RToLinearResponse, in[0]);\
  RGBp[1] = cml_Eval(GToLinearResponse, in[1]);\
  RGBp[2] = cml_Eval(BToLinearResponse, in[2]);\
  cmlMulMat33Vec3(out, RGBToXYZMatrix, RGBp);

CML_HIDEF void cml_OneRGBToXYZ(float* CML_RESTRICT out, const float* CML_RESTRICT in, const CMLMat33 RGBToXYZMatrix, const CMLFunction* RToLinearResponse, const CMLFunction* GToLinearResponse, const CMLFunction* BToLinearResponse){
  cml_ConvertRGBToXYZ(out, in, RGBToXYZMatrix, RToLinearResponse, GToLinearResponse, BToLinearResponse);
}
CML_HIDEF void cml_OneRGBToXYZ_SB(float* buf, const CMLMat33 RGBToXYZMatrix, const CMLFunction* RToLinearResponse, const CMLFunction* GToLinearResponse, const CMLFunction* BToLinearResponse){
  cml_ConvertRGBToXYZ(buf, buf, RGBToXYZMatrix, RToLinearResponse, GToLinearResponse, BToLinearResponse);
}

CML_HIDEF void cml_RGBToXYZ(float* CML_RESTRICT out, const float* CML_RESTRICT in, size_t count, const CMLMat33 RGBToXYZMatrix, const CMLFunction* RToLinearResponse, const CMLFunction* GToLinearResponse, const CMLFunction* BToLinearResponse){
  cml__START_COUNT_LOOP(count);
  cml_OneRGBToXYZ(out, in, RGBToXYZMatrix, RToLinearResponse, GToLinearResponse, BToLinearResponse);
  cml__END_COUNT_LOOP(CML_XYZ_NUMCHANNELS, CML_RGB_NUMCHANNELS);
}

CML_HIDEF void cml_RGBToXYZ_SB(float* buf, size_t count, size_t floatAlign, const CMLMat33 RGBToXYZMatrix, const CMLFunction* RToLinearResponse, const CMLFunction* GToLinearResponse, const CMLFunction* BToLinearResponse){
  cml__START_COUNT_LOOP(count);
  cml_OneRGBToXYZ_SB(buf, RGBToXYZMatrix, RToLinearResponse, GToLinearResponse, BToLinearResponse);
  cml__END_COUNT_LOOP_SB(floatAlign);
}


// ////////////////////////////////////
// RGB to YCbCr
// ////////////////////////////////////

#define cml_ConvertRGBToYCbCr(out, in, redPrimaryYxy, bluePrimaryYxy, whitePointXYZInverse) \
  float Kr = redPrimaryYxy[0] * whitePointXYZInverse[1];\
  float Kb = bluePrimaryYxy[0] * whitePointXYZInverse[1];\
  float Y = Kr * in[0] + (1.f - Kr - Kb) * in[1] + Kb * in[2];\
  out[1] = .5f * (in[2] - Y) / (1.f - Kb);\
  out[2] = .5f * (in[0] - Y) / (1.f - Kr);\
  out[0] = Y;

CML_HIDEF void cml_OneRGBToYCbCr(float* CML_RESTRICT out, const float* CML_RESTRICT in, const CMLVec3 redPrimaryYxy, const CMLVec3 bluePrimaryYxy, const CMLVec3 whitePointXYZInverse){
  cml_ConvertRGBToYCbCr(out, in, redPrimaryYxy, bluePrimaryYxy, whitePointXYZInverse);
}
CML_HIDEF void cml_OneRGBToYCbCr_SB(float* buf, const CMLVec3 redPrimaryYxy, const CMLVec3 bluePrimaryYxy, const CMLVec3 whitePointXYZInverse){
  cml_ConvertRGBToYCbCr(buf, buf, redPrimaryYxy, bluePrimaryYxy, whitePointXYZInverse);
}

CML_HIDEF void cml_RGBToYCbCr(float* CML_RESTRICT out, const float* CML_RESTRICT in, size_t count, const CMLVec3 redPrimaryYxy, const CMLVec3 bluePrimaryYxy, const CMLVec3 whitePointXYZInverse){
  cml__START_COUNT_LOOP(count);
  cml_OneRGBToYCbCr(out, in, redPrimaryYxy, bluePrimaryYxy, whitePointXYZInverse);
  cml__END_COUNT_LOOP(CML_YCbCr_NUMCHANNELS, CML_RGB_NUMCHANNELS);
}

CML_HIDEF void cml_RGBToYCbCr_SB(float* buf, size_t count, size_t floatAlign, const CMLVec3 redPrimaryYxy, const CMLVec3 bluePrimaryYxy, const CMLVec3 whitePointXYZInverse){
  cml__START_COUNT_LOOP(count);
  cml_OneRGBToYCbCr_SB(buf, redPrimaryYxy, bluePrimaryYxy, whitePointXYZInverse);
  cml__END_COUNT_LOOP_SB(floatAlign);
}


// ////////////////////////////////////
// HSV to HSL
// ////////////////////////////////////

#define cml_ConvertHSVToHSL(out, in) \
  out[0] = in[0];\
  out[1] = in[1] * in[2];\
  out[2] = in[2] - 0.5f * out[1];


CML_HIDEF void cml_OneHSVToHSL(float* CML_RESTRICT out, const float* CML_RESTRICT in){
  cml_ConvertHSVToHSL(out, in);
}
CML_HIDEF void cml_OneHSVToHSL_SB(float* buf){
  cml_ConvertHSVToHSL(buf, buf);
}

CML_HIDEF void cml_HSVToHSL(float* CML_RESTRICT out, const float* CML_RESTRICT in, size_t count){
  cml__START_COUNT_LOOP(count);
  cml_OneHSVToHSL(out, in);
  cml__END_COUNT_LOOP(CML_HSL_NUMCHANNELS, CML_HSV_NUMCHANNELS);
}

CML_HIDEF void cml_HSVToHSL_SB(float* buf, size_t count, size_t floatAlign){
  cml__START_COUNT_LOOP(count);
  cml_OneHSVToHSL_SB(buf);
  cml__END_COUNT_LOOP_SB(floatAlign);
}


// ////////////////////////////////////
// Lch to Lab
// ////////////////////////////////////

#define cml_ConvertLchToLab(out, in) \
  if(in[1] == 0.f){\
    out[2] = 0.f;\
    out[1] = 0.f;\
  }else{\
    float hue = cmlDegToRad(in[2]);\
    out[2] = sinf(hue) * in[1];\
    out[1] = cosf(hue) * in[1];\
  }\
  out[0] = in[0];

CML_HIDEF void cml_OneLchToLab(float* CML_RESTRICT out, const float* CML_RESTRICT in){
  cml_ConvertLchToLab(out, in);
}
CML_HIDEF void cml_OneLchToLab_SB(float* buf){
  cml_ConvertLchToLab(buf, buf);
}

CML_HIDEF void cml_LchToLab(float* CML_RESTRICT out, const float* CML_RESTRICT in, size_t count){
  cml__START_COUNT_LOOP(count);
  cml_OneLchToLab(out, in);
  cml__END_COUNT_LOOP(CML_Lab_NUMCHANNELS, CML_Lch_NUMCHANNELS);
}

CML_HIDEF void cml_LchToLab_SB(float* buf, size_t count, size_t floatAlign){
  cml__START_COUNT_LOOP(count);
  cml_OneLchToLab_SB(buf);
  cml__END_COUNT_LOOP_SB(floatAlign);
}


// ////////////////////////////////////
// YCbCr to RGB
// ////////////////////////////////////

#define cml_ConvertYCbCrToRGB(out, in, redPrimaryYxy, bluePrimaryYxy, whitePointXYZInverse) \
  float Kr = redPrimaryYxy[0] * whitePointXYZInverse[1];\
  float Kb = bluePrimaryYxy[0] * whitePointXYZInverse[1];\
  float Y = in[0];\
  out[0] = 2.f * in[2] * (1.f - Kr) + Y;\
  out[2] = 2.f * in[1] * (1.f - Kb) + Y;\
  out[1] = (Y - Kr * out[0] - Kb * out[2]) / (1.f - Kr - Kb);


CML_HIDEF void cml_OneYCbCrToRGB(float* CML_RESTRICT out, const float* CML_RESTRICT in, const CMLVec3 redPrimaryYxy, const CMLVec3 bluePrimaryYxy, const CMLVec3 whitePointXYZInverse){
  cml_ConvertYCbCrToRGB(out, in, redPrimaryYxy, bluePrimaryYxy, whitePointXYZInverse);
}
CML_HIDEF void cml_OneYCbCrToRGB_SB(float* buf, const CMLVec3 redPrimaryYxy, const CMLVec3 bluePrimaryYxy, const CMLVec3 whitePointXYZInverse){
  cml_ConvertYCbCrToRGB(buf, buf, redPrimaryYxy, bluePrimaryYxy, whitePointXYZInverse);
}

CML_HIDEF void cml_YCbCrToRGB(float* CML_RESTRICT out, const float* CML_RESTRICT in, size_t count, const CMLVec3 redPrimaryYxy, const CMLVec3 bluePrimaryYxy, const CMLVec3 whitePointXYZInverse){
  cml__START_COUNT_LOOP(count);
  cml_OneYCbCrToRGB(out, in, redPrimaryYxy, bluePrimaryYxy, whitePointXYZInverse);
  cml__END_COUNT_LOOP(CML_RGB_NUMCHANNELS, CML_YCbCr_NUMCHANNELS);
}

CML_HIDEF void cml_YCbCrToRGB_SB(float* buf, size_t count, size_t floatAlign, const CMLVec3 redPrimaryYxy, const CMLVec3 bluePrimaryYxy, const CMLVec3 whitePointXYZInverse){
  cml__START_COUNT_LOOP(count);
  cml_OneYCbCrToRGB_SB(buf, redPrimaryYxy, bluePrimaryYxy, whitePointXYZInverse);
  cml__END_COUNT_LOOP_SB(floatAlign);
}


// ////////////////////////////////////
// HSL to HSV
// ////////////////////////////////////

#define cml_ConvertHSLToHSV(out, in) \
  out[0] = in[0];\
  out[2] = in[2] + .5f * in[1];\
  if(out[2] == 0.f){\
    out[1] = in[1] / CML_SINGULARITY;\
  }else{\
    out[1] = in[1] / out[2];\
  }

CML_HIDEF void cml_OneHSLToHSV(float* CML_RESTRICT out, const float* CML_RESTRICT in){
  cml_ConvertHSLToHSV(out, in);
}
CML_HIDEF void cml_OneHSLToHSV_SB(float* buf){
  cml_ConvertHSLToHSV(buf, buf);
}

CML_HIDEF void cml_HSLToHSV(float* CML_RESTRICT out, const float* CML_RESTRICT in, size_t count){
  cml__START_COUNT_LOOP(count);
  cml_OneHSLToHSV(out, in);
  cml__END_COUNT_LOOP(CML_HSV_NUMCHANNELS, CML_HSL_NUMCHANNELS);
}

CML_HIDEF void cml_HSLToHSV_SB(float* buf, size_t count, size_t floatAlign){
  cml__START_COUNT_LOOP(count);
  cml_OneHSLToHSV_SB(buf);
  cml__END_COUNT_LOOP_SB(floatAlign);
}


// ////////////////////////////////////
// RGB to HSV
// ////////////////////////////////////

// todo: Make it SB
#define cml_ConvertRGBToHSV(out, in) \
  float min;\
  float range;\
  CMLVec3 rgb;\
  cmlCpy3(rgb, in);\
  if(rgb[0] < rgb[1]){min = rgb[0]; out[2] = rgb[1];}else{min = rgb[1]; out[2] = rgb[0];}\
  if(rgb[2] < min){min = rgb[2];}\
  if(rgb[2] > out[2]){out[2] = rgb[2];}\
  range = out[2] - min;\
  if(out[2] == 0.f){\
    out[1] = 0.f;\
  }else{\
    out[1] = range / out[2];\
  }\
  if(cmlAlmostZero(range)){\
    out[0] = 0.f;\
  }else{\
    float invrange = cmlInverse(range);\
    if(out[2] == rgb[0])      {out[0] = 60.f * (0.f + (rgb[1]-rgb[2]) * invrange);}\
    else if(out[2] == rgb[1]) {out[0] = 60.f * (2.f + (rgb[2]-rgb[0]) * invrange);}\
    else                      {out[0] = 60.f * (4.f + (rgb[0]-rgb[1]) * invrange);}\
    if(out[0] < 0.f){out[0] += 360.f;}\
  }

CML_HIDEF void cml_OneRGBToHSV(float* CML_RESTRICT out, const float* CML_RESTRICT in){
  cml_ConvertRGBToHSV(out, in);
}
CML_HIDEF void cml_OneRGBToHSV_SB(float* buf){
  cml_ConvertRGBToHSV(buf, buf);
}

CML_HIDEF void cml_RGBToHSV(float* CML_RESTRICT out, const float* CML_RESTRICT in, size_t count){
  cml__START_COUNT_LOOP(count);
  cml_OneRGBToHSV(out, in);
  cml__END_COUNT_LOOP(CML_HSV_NUMCHANNELS, CML_RGB_NUMCHANNELS);
}

CML_HIDEF void cml_RGBToHSV_SB(float* buf, size_t count, size_t floatAlign){
  cml__START_COUNT_LOOP(count);
  cml_OneRGBToHSV_SB(buf);
  cml__END_COUNT_LOOP_SB(floatAlign);
}


// ////////////////////////////////////
// HSV to RGB
// ////////////////////////////////////

// todo: Make it SB
#define cml_ConvertHSVToRGB(out, in) \
  CMLVec3 hsv;\
  cmlCpy3(hsv, in);\
  size_t h0 = (size_t)floorf(hsv[0] / 60.f);\
  uint8 h1 = (uint8)((h0 % 6) + 6) % 6;\
  float f = (hsv[0] / 60.f) - h0;\
  float range = hsv[2] * hsv[1];\
  float min = hsv[2] - range;\
  float inc = f * range;\
  float dec = (1.f - f) * range;\
  inc += min;\
  dec += min;\
  switch(h1){\
  case 0: out[0] = hsv[2] ; out[1] = inc    ; out[2] = min    ; break;\
  case 1: out[0] = dec    ; out[1] = hsv[2] ; out[2] = min    ; break;\
  case 2: out[0] = min    ; out[1] = hsv[2] ; out[2] = inc    ; break;\
  case 3: out[0] = min    ; out[1] = dec    ; out[2] = hsv[2] ; break;\
  case 4: out[0] = inc    ; out[1] = min    ; out[2] = hsv[2] ; break;\
  case 5: out[0] = hsv[2] ; out[1] = min    ; out[2] = dec    ; break;\
  default:\
    out[0] = 0.f; out[1] = 0.f; out[2] = 0.f;\
  }

CML_HIDEF void cml_OneHSVToRGB(float* CML_RESTRICT out, const float* CML_RESTRICT in){
  cml_ConvertHSVToRGB(out, in);
}
CML_HIDEF void cml_OneHSVToRGB_SB(float* buf){
  cml_ConvertHSVToRGB(buf, buf);
}

CML_HIDEF void cml_HSVToRGB(float* CML_RESTRICT out, const float* CML_RESTRICT in, size_t count){
  cml__START_COUNT_LOOP(count);
  cml_OneHSVToRGB(out, in);
  cml__END_COUNT_LOOP(CML_RGB_NUMCHANNELS, CML_HSV_NUMCHANNELS);
}

CML_HIDEF void cml_HSVToRGB_SB(float* buf, size_t count, size_t floatAlign){
  cml__START_COUNT_LOOP(count);
  cml_OneHSVToRGB_SB(buf);
  cml__END_COUNT_LOOP_SB(floatAlign);
}


// ////////////////////////////////////
// Lr to fy and fy to Lr
// ////////////////////////////////////

#define CML_LSTAR_TRANSFORM_OFFSET    0.16f
#define CML_LSTAR_TRANSFORM_SCALE     1.16f
#define CML_LSTAR_TRANSFORM_INV_SCALE 0.8620689655172f

CML_HIDEF float cml_Lrtofy(float Lr){
  return (Lr + CML_LSTAR_TRANSFORM_OFFSET) * CML_LSTAR_TRANSFORM_INV_SCALE;
}

CML_HIDEF float cml_fytoLr(float fy){
  return fy * CML_LSTAR_TRANSFORM_SCALE - CML_LSTAR_TRANSFORM_OFFSET;
}


// ////////////////////////////////////
// XYZ to CIELAB
// ////////////////////////////////////

#define cml_ConvertXYZToCIELAB(out, in, whitePointXYZInverse, LineartoLResponse) \
  float xr = in[0] * whitePointXYZInverse[0];\
  float yr = in[1] * whitePointXYZInverse[1];\
  float zr = in[2] * whitePointXYZInverse[2];\
  float fx = cml_Lrtofy(cml_Eval(LineartoLResponse, xr));\
  float fy = cml_Lrtofy(cml_Eval(LineartoLResponse, yr));\
  float fz = cml_Lrtofy(cml_Eval(LineartoLResponse, zr));\
  out[0] = 100.f * cml_fytoLr(fy);\
  out[1] = (fx - fy) * 500.f;\
  out[2] = (fy - fz) * 200.f;


CML_HIDEF void cml_OneXYZToCIELAB(float* CML_RESTRICT out, const float* CML_RESTRICT in, const CMLVec3 whitePointXYZInverse, const CMLFunction* LineartoLResponse){
  cml_ConvertXYZToCIELAB(out, in, whitePointXYZInverse, LineartoLResponse);
}
CML_HIDEF void cml_OneXYZToCIELAB_SB(float* buf, const CMLVec3 whitePointXYZInverse, const CMLFunction* LineartoLResponse){
  cml_ConvertXYZToCIELAB(buf, buf, whitePointXYZInverse, LineartoLResponse);
}

CML_HIDEF void cml_XYZToCIELAB(float* CML_RESTRICT out, const float* CML_RESTRICT in, size_t count, const CMLVec3 whitePointXYZInverse, const CMLFunction* LineartoLResponse){
  cml__START_COUNT_LOOP(count);
  cml_OneXYZToCIELAB(out, in, whitePointXYZInverse, LineartoLResponse);
  cml__END_COUNT_LOOP(CML_Lab_NUMCHANNELS, CML_XYZ_NUMCHANNELS);
}

CML_HIDEF void cml_XYZToCIELAB_SB(float* buf, size_t count, size_t floatAlign, const CMLVec3 whitePointXYZInverse, const CMLFunction* LineartoLResponse){
  cml__START_COUNT_LOOP(count);
  cml_OneXYZToCIELAB_SB(buf, whitePointXYZInverse, LineartoLResponse);
  cml__END_COUNT_LOOP_SB(floatAlign);
}


// ////////////////////////////////////
// CIELAB to XYZ
// ////////////////////////////////////

#define cml_ConvertCIELABToXYZ(out, in, whitePointXYZ, LtoLinearResponse) \
    float fy = cml_Lrtofy(.01f * in[0]);\
    float fx = fy + in[1] * .002f;\
    float fz = fy - in[2] * .005f;\
    float xr = cml_Eval(LtoLinearResponse, cml_fytoLr(fx));\
    float yr = cml_Eval(LtoLinearResponse, cml_fytoLr(fy));\
    float zr = cml_Eval(LtoLinearResponse, cml_fytoLr(fz));\
    out[0] = xr * whitePointXYZ[0];\
    out[1] = yr * whitePointXYZ[1];\
    out[2] = zr * whitePointXYZ[2];


CML_HIDEF void cml_OneCIELABToXYZ(float* CML_RESTRICT out, const float* CML_RESTRICT in, const CMLVec3 whitePointXYZ, const CMLFunction* LtoLinearResponse){
  cml_ConvertCIELABToXYZ(out, in, whitePointXYZ, LtoLinearResponse);
}
CML_HIDEF void cml_OneCIELABToXYZ_SB(float* buf, const CMLVec3 whitePointXYZ, const CMLFunction* LtoLinearResponse){
  cml_ConvertCIELABToXYZ(buf, buf, whitePointXYZ, LtoLinearResponse);
}

CML_HIDEF void cml_CIELABToXYZ(float* CML_RESTRICT out, const float* CML_RESTRICT in, size_t count, const CMLVec3 whitePointXYZ, const CMLFunction* LtoLinearResponse){
  cml__START_COUNT_LOOP(count);
  cml_OneCIELABToXYZ(out, in, whitePointXYZ, LtoLinearResponse);
  cml__END_COUNT_LOOP(CML_XYZ_NUMCHANNELS, CML_Lab_NUMCHANNELS);
}


CML_HIDEF void cml_CIELABToXYZ_SB(float* buf, size_t count, size_t floatAlign, const CMLVec3 whitePointXYZ, const CMLFunction* LtoLinearResponse){
  cml__START_COUNT_LOOP(count);
  cml_OneCIELABToXYZ_SB(buf, whitePointXYZ, LtoLinearResponse);
  cml__END_COUNT_LOOP_SB(floatAlign);
}





// ////////////////////////////////////
// Spectrum to XYZ
// ////////////////////////////////////

#define cml_ConvertSpectrumToXYZ(out, in, specDistFuncs, radiometricScale, integration) \
  out[0] = cmlFilterFunction(in, specDistFuncs[0], integration);\
  out[1] = cmlFilterFunction(in, specDistFuncs[1], integration);\
  out[2] = cmlFilterFunction(in, specDistFuncs[2], integration);\
  cmlMul3(out, radiometricScale);    

CML_HIDEF void cml_OneIlluminationSpectrumToXYZ(
  CMLVec3 out,
  const CMLFunction* in,
  CMLFunction* const * specDistFuncs,
  float radiometricScale,
  const CMLIntegration* integration)
{
  cml_ConvertSpectrumToXYZ(out, in, specDistFuncs, radiometricScale, integration);
}

CML_HIDEF void cml_IlluminationSpectrumToXYZ(
  CMLVec3 out,
  const CMLFunction* in,
  size_t count,
  size_t floatAlign,
  const CMLObserver* observer,
  float radiometricScale,
  const CMLIntegration* integration)
{
  cml__START_COUNT_LOOP(count);
  cml_OneIlluminationSpectrumToXYZ(out, in, cml_GetObserverSpecDistFunctions(observer), radiometricScale, integration);
  cml__END_COUNT_LOOP(floatAlign, 1);
}

CML_HIDEF void cml_OneRemissionSpectrumToXYZ(
  CMLVec3 out,
  const CMLFunction* in,
  const CMLFunction* specIll,
  const CMLObserver* observer,
  float radiometricScale,
  const CMLIntegration* integration)
{
  CMLFunction* remIllFunction = cmlCreateFunctionMulFunction(in, specIll);
  cml_OneIlluminationSpectrumToXYZ(out, remIllFunction, cml_GetObserverSpecDistFunctions(observer),  radiometricScale, integration);
  cmlReleaseFunction(remIllFunction);
}

CML_HIDEF void cml_RemissionSpectrumToXYZ(
  CMLVec3 out,
  const CMLFunction* in,
  size_t count,
  size_t floatAlign,
  const CMLFunction* specIll,
  const CMLObserver* observer,
  float radiometricScale,
  const CMLIntegration* integration)
{
  if(specIll){
    cml__START_COUNT_LOOP(count);
    cml_OneRemissionSpectrumToXYZ(out, in, specIll, observer, radiometricScale, integration);
    cml__END_COUNT_LOOP(floatAlign, 1);
  }else{
    float base = radiometricScale * .5f;
    cml__START_COUNT_LOOP(count);
    cmlSet3(out, base, base, base);
    cml__END_COUNT_LOOP(floatAlign, 1);
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

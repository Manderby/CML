
#include "../CML.h"
#include "../Internal/CMLColorMachineState.h"


// ////////////////////////////
// Normed Input
// ////////////////////////////

CML_DEF void cmlNormedInputToCMYK(CMLOutput cmyk, CMLInput input, size_t count){
  const float* in  = (float*)input;
  float* out = (float*)cmyk;
  for(size_t i = 0; i < count; ++i){
    cml_OneNormedInputToCMYK(out, in);
    out += CML_CMYK_CHANNEL_COUNT;
    in += CML_CMYK_CHANNEL_COUNT;
  }
}

CML_DEF void cmlNormedInputToGray(CMLOutput gray, CMLInput input, size_t count){
  const float* in  = (float*)input;
  float* out = (float*)gray;
  for(size_t i = 0; i < count; ++i){
    cml_OneNormedInputToGray(out, in);
    out += CML_GRAY_CHANNEL_COUNT;
    in += CML_GRAY_CHANNEL_COUNT;
  }
}
CML_DEF void cmlNormedInputToHSL(CMLOutput hsl, CMLInput input, size_t count){
  const float* in  = (float*)input;
  float* out = (float*)hsl;
  for(size_t i = 0; i < count; ++i){
    cml_OneNormedInputToHSL(out, in);
    out += CML_HSL_CHANNEL_COUNT;
    in += CML_HSL_CHANNEL_COUNT;
  }
}
CML_DEF void cmlNormedInputToHSV(CMLOutput hsv, CMLInput input, size_t count){
  const float* in  = (float*)input;
  float* out = (float*)hsv;
  for(size_t i = 0; i < count; ++i){
    cml_OneNormedInputToHSV(out, in);
    out += CML_HSV_CHANNEL_COUNT;
    in += CML_HSV_CHANNEL_COUNT;
  }
}
CML_DEF void cmlNormedInputToLab(CMLOutput lab, CMLInput input, size_t count){
  const float* in  = (float*)input;
  float* out = (float*)lab;
  for(size_t i = 0; i < count; ++i){
    cml_OneNormedInputToLab(out, in);
    out += CML_Lab_CHANNEL_COUNT;
    in += CML_Lab_CHANNEL_COUNT;
  }
}
CML_DEF void cmlNormedInputToLch(CMLOutput lch, CMLInput input, size_t count){
  const float* in  = (float*)input;
  float* out = (float*)lch;
  for(size_t i = 0; i < count; ++i){
    cml_OneNormedInputToLch(out, in);
    out += CML_Lch_CHANNEL_COUNT;
    in += CML_Lch_CHANNEL_COUNT;
  }
}
CML_DEF void cmlNormedInputToLuv(CMLOutput luv, CMLInput input, size_t count){
  const float* in  = (float*)input;
  float* out = (float*)luv;
  for(size_t i = 0; i < count; ++i){
    cml_OneNormedInputToLuv(out, in);
    out += CML_Luv_CHANNEL_COUNT;
    in += CML_Luv_CHANNEL_COUNT;
  }
}
CML_DEF void cmlNormedInputToRGB(CMLOutput rgb, CMLInput input, size_t count){
  const float* in  = (float*)input;
  float* out = (float*)rgb;
  for(size_t i = 0; i < count; ++i){
    cml_OneNormedInputToRGB(out, in);
    out += CML_RGB_CHANNEL_COUNT;
    in += CML_RGB_CHANNEL_COUNT;
  }
}
CML_DEF void cmlNormedInputToUVW(CMLOutput uvw, CMLInput input, size_t count){
  const float* in  = (float*)input;
  float* out = (float*)uvw;
  for(size_t i = 0; i < count; ++i){
    cml_OneNormedInputToUVW(out, in);
    out += CML_UVW_CHANNEL_COUNT;
    in += CML_UVW_CHANNEL_COUNT;
  }
}
CML_DEF void cmlNormedInputToXYZ(CMLOutput xyz, CMLInput input, size_t count){
  const float* in  = (float*)input;
  float* out = (float*)xyz;
  for(size_t i = 0; i < count; ++i){
    cml_OneNormedInputToXYZ(out, in);
    out += CML_XYZ_CHANNEL_COUNT;
    in += CML_XYZ_CHANNEL_COUNT;
  }
}
CML_DEF void cmlNormedInputToYCbCr(CMLOutput ycbcr, CMLInput input, size_t count){
  const float* in  = (float*)input;
  float* out = (float*)ycbcr;
  for(size_t i = 0; i < count; ++i){
    cml_OneNormedInputToYCbCr(out, in);
    out += CML_YCbCr_CHANNEL_COUNT;
    in += CML_YCbCr_CHANNEL_COUNT;
  }
}
CML_DEF void cmlNormedInputToYcd(CMLOutput ycd, CMLInput input, size_t count){
  const float* in  = (float*)input;
  float* out = (float*)ycd;
  for(size_t i = 0; i < count; ++i){
    cml_OneNormedInputToYcd(out, in);
    out += CML_Ycd_CHANNEL_COUNT;
    in += CML_Ycd_CHANNEL_COUNT;
  }
}
CML_DEF void cmlNormedInputToYupvp(CMLOutput yupvp, CMLInput input, size_t count){
  const float* in  = (float*)input;
  float* out = (float*)yupvp;
  for(size_t i = 0; i < count; ++i){
    cml_OneNormedInputToYupvp(out, in);
    out += CML_Yupvp_CHANNEL_COUNT;
    in += CML_Yupvp_CHANNEL_COUNT;
  }
}
CML_DEF void cmlNormedInputToYuv(CMLOutput yuv, CMLInput input, size_t count){
  const float* in  = (float*)input;
  float* out = (float*)yuv;
  for(size_t i = 0; i < count; ++i){
    cml_OneNormedInputToYuv(out, in);
    out += CML_Yuv_CHANNEL_COUNT;
    in += CML_Yuv_CHANNEL_COUNT;
  }
}
CML_DEF void cmlNormedInputToYxy(CMLOutput yxy, CMLInput input, size_t count){
  const float* in  = (float*)input;
  float* out = (float*)yxy;
  for(size_t i = 0; i < count; ++i){
    cml_OneNormedInputToYxy(out, in);
    out += CML_Yxy_CHANNEL_COUNT;
    in += CML_Yxy_CHANNEL_COUNT;
  }
}



// ////////////////////////////
// Normed Output
// ////////////////////////////

CML_DEF void cmlCMYKToNormedOutput(CMLOutput output, CMLInput cmyk, size_t count){
  const float* in  = (float*)cmyk;
  float* out = (float*)output;
  for(size_t i = 0; i < count; ++i){
    cml_OneCMYKToNormedOutput(out, in);
    out += CML_CMYK_CHANNEL_COUNT;
    in += CML_CMYK_CHANNEL_COUNT;
  }
}
CML_DEF void cmlGrayToNormedOutput(CMLOutput output, CMLInput gray, size_t count){
  const float* in  = (float*)gray;
  float* out = (float*)output;
  for(size_t i = 0; i < count; ++i){
    cml_OneGrayToNormedOutput(out, in);
    out += CML_GRAY_CHANNEL_COUNT;
    in += CML_GRAY_CHANNEL_COUNT;
  }
}
CML_DEF void cmlHSLToNormedOutput(CMLOutput output, CMLInput hsl, size_t count){
  const float* in  = (float*)hsl;
  float* out = (float*)output;
  for(size_t i = 0; i < count; ++i){
    cml_OneHSLToNormedOutput(out, in);
    out += CML_HSL_CHANNEL_COUNT;
    in += CML_HSL_CHANNEL_COUNT;
  }
}
CML_DEF void cmlHSVToNormedOutput(CMLOutput output, CMLInput hsv, size_t count){
  const float* in  = (float*)hsv;
  float* out = (float*)output;
  for(size_t i = 0; i < count; ++i){
    cml_OneHSVToNormedOutput(out, in);
    out += CML_HSV_CHANNEL_COUNT;
    in += CML_HSV_CHANNEL_COUNT;
  }
}
CML_DEF void cmlLabToNormedOutput(CMLOutput output, CMLInput lab, size_t count){
  const float* in  = (float*)lab;
  float* out = (float*)output;
  for(size_t i = 0; i < count; ++i){
    cml_OneLabToNormedOutput(out, in);
    out += CML_Lab_CHANNEL_COUNT;
    in += CML_Lab_CHANNEL_COUNT;
  }
}
CML_DEF void cmlLchToNormedOutput(CMLOutput output, CMLInput lch, size_t count){
  const float* in  = (float*)lch;
  float* out = (float*)output;
  for(size_t i = 0; i < count; ++i){
    cml_OneLchToNormedOutput(out, in);
    out += CML_Lch_CHANNEL_COUNT;
    in += CML_Lch_CHANNEL_COUNT;
  }
}
CML_DEF void cmlLuvToNormedOutput(CMLOutput output, CMLInput luv, size_t count){
  const float* in  = (float*)luv;
  float* out = (float*)output;
  for(size_t i = 0; i < count; ++i){
    cml_OneLuvToNormedOutput(out, in);
    out += CML_Luv_CHANNEL_COUNT;
    in += CML_Luv_CHANNEL_COUNT;
  }
}
CML_DEF void cmlRGBToNormedOutput(CMLOutput output, CMLInput rgb, size_t count){
  const float* in  = (float*)rgb;
  float* out = (float*)output;
  for(size_t i = 0; i < count; ++i){
    cml_OneRGBToNormedOutput(out, in);
    out += CML_RGB_CHANNEL_COUNT;
    in += CML_RGB_CHANNEL_COUNT;
  }
}
CML_DEF void cmlUVWToNormedOutput(CMLOutput output, CMLInput uvw, size_t count){
  const float* in  = (float*)uvw;
  float* out = (float*)output;
  for(size_t i = 0; i < count; ++i){
    cml_OneUVWToNormedOutput(out, in);
    out += CML_UVW_CHANNEL_COUNT;
    in += CML_UVW_CHANNEL_COUNT;
  }
}
CML_DEF void cmlXYZToNormedOutput(CMLOutput output, CMLInput xyz, size_t count){
  const float* in  = (float*)xyz;
  float* out = (float*)output;
  for(size_t i = 0; i < count; ++i){
    cml_OneXYZToNormedOutput(out, in);
    out += CML_XYZ_CHANNEL_COUNT;
    in += CML_XYZ_CHANNEL_COUNT;
  }
}
CML_DEF void cmlYCbCrToNormedOutput(CMLOutput output, CMLInput ycbcr, size_t count){
  const float* in  = (float*)ycbcr;
  float* out = (float*)output;
  for(size_t i = 0; i < count; ++i){
    cml_OneYCbCrToNormedOutput(out, in);
    out += CML_YCbCr_CHANNEL_COUNT;
    in += CML_YCbCr_CHANNEL_COUNT;
  }
}
CML_DEF void cmlYcdToNormedOutput(CMLOutput output, CMLInput ycd, size_t count){
  const float* in  = (float*)ycd;
  float* out = (float*)output;
  for(size_t i = 0; i < count; ++i){
    cml_OneYcdToNormedOutput(out, in);
    out += CML_Ycd_CHANNEL_COUNT;
    in += CML_Ycd_CHANNEL_COUNT;
  }
}
CML_DEF void cmlYupvpToNormedOutput(CMLOutput output, CMLInput yupvp, size_t count){
  const float* in  = (float*)yupvp;
  float* out = (float*)output;
  for(size_t i = 0; i < count; ++i){
    cml_OneYupvpToNormedOutput(out, in);
    out += CML_Yupvp_CHANNEL_COUNT;
    in += CML_Yupvp_CHANNEL_COUNT;
  }
}
CML_DEF void cmlYuvToNormedOutput(CMLOutput output, CMLInput yuv, size_t count){
  const float* in  = (float*)yuv;
  float* out = (float*)output;
  for(size_t i = 0; i < count; ++i){
    cml_OneYuvToNormedOutput(out, in);
    out += CML_Yuv_CHANNEL_COUNT;
    in += CML_Yuv_CHANNEL_COUNT;
  }
}
CML_DEF void cmlYxyToNormedOutput(CMLOutput output, CMLInput yxy, size_t count){
  const float* in  = (float*)yxy;
  float* out = (float*)output;
  for(size_t i = 0; i < count; ++i){
    cml_OneYxyToNormedOutput(out, in);
    out += CML_Yxy_CHANNEL_COUNT;
    in += CML_Yxy_CHANNEL_COUNT;
  }
}



// ////////////////////////////
// Normed Cartesian Input
// ////////////////////////////

CML_DEF void cmlNormedCartesianInputToHSL(CMLOutput hsl, CMLInput input, size_t count){
  const float* in  = (float*)input;
  float* out = (float*)hsl;
  for(size_t i = 0; i < count; ++i){
    cml_OneNormedCartesianInputToHSL(out, in);
    out += CML_HSL_CHANNEL_COUNT;
    in += CML_HSL_CHANNEL_COUNT;
  }
}
CML_DEF void cmlNormedCartesianInputToHSV(CMLOutput hsv, CMLInput input, size_t count){
  const float* in  = (float*)input;
  float* out = (float*)hsv;
  for(size_t i = 0; i < count; ++i){
    cml_OneNormedCartesianInputToHSV(out, in);
    out += CML_HSV_CHANNEL_COUNT;
    in += CML_HSV_CHANNEL_COUNT;
  }
}
CML_DEF void cmlNormedCartesianInputToLch(CMLOutput lch, CMLInput input, size_t count){
  const float* in  = (float*)input;
  float* out = (float*)lch;
  for(size_t i = 0; i < count; ++i){
    cml_OneNormedCartesianInputToLch(out, in);
    out += CML_Lch_CHANNEL_COUNT;
    in += CML_Lch_CHANNEL_COUNT;
  }
}



// ////////////////////////////
// Normed Cartesian Output
// ////////////////////////////

CML_DEF void cmlHSLToNormedCartesianOutput(CMLOutput output, CMLInput hsl, size_t count){
  const float* in  = (float*)hsl;
  float* out = (float*)output;
  for(size_t i = 0; i < count; ++i){
    cml_OneHSLToNormedCartesianOutput(out, in);
    out += CML_HSL_CHANNEL_COUNT;
    in += CML_HSL_CHANNEL_COUNT;
  }
}
CML_DEF void cmlHSVToNormedCartesianOutput(CMLOutput output, CMLInput hsv, size_t count){
  const float* in  = (float*)hsv;
  float* out = (float*)output;
  for(size_t i = 0; i < count; ++i){
    cml_OneHSVToNormedCartesianOutput(out, in);
    out += CML_HSV_CHANNEL_COUNT;
    in += CML_HSV_CHANNEL_COUNT;
  }
}
CML_DEF void cmlLchToNormedCartesianOutput(CMLOutput output, CMLInput lch, size_t count){
  const float* in  = (float*)lch;
  float* out = (float*)output;
  for(size_t i = 0; i < count; ++i){
    cml_OneLchToNormedCartesianOutput(out, in);
    out += CML_Lch_CHANNEL_COUNT;
    in += CML_Lch_CHANNEL_COUNT;
  }
}



// ////////////////////////////
// Normed Gamut Slice
// ////////////////////////////

CML_DEF CMLOutput cmlCreateNormedGamutSlice(
  CMLColorType colorSpace,
  const size_t dimensions[CML_MAX_NUMBER_OF_CHANNELS],
  const CMLVec4 origin,
  const CMLVec4 range0,
  const CMLVec4 range1,
  const CMLVec4 range2,
  const CMLVec4 range3){
  
  if(colorSpace >= CML_COLOR_COUNT){return NULL;}
  
  size_t numChannels = cmlGetNumChannels(colorSpace);

  CMLVec4 o;
  CMLVec4 r[CML_MAX_NUMBER_OF_CHANNELS];
  if(origin){cmlCpy4(o, origin);}else{cmlSet4(o, 0.f, 0.f, 0.f, 0.f);}
  if(range0){cmlCpy4(r[0], range0);}else{cmlSet4(r[0], 1.f, 0.f, 0.f, 0.f);}
  if(range1){cmlCpy4(r[1], range1);}else{cmlSet4(r[1], 0.f, 1.f, 0.f, 0.f);}
  if(range2){cmlCpy4(r[2], range2);}else{cmlSet4(r[2], 0.f, 0.f, 1.f, 0.f);}
  if(range3){cmlCpy4(r[3], range3);}else{cmlSet4(r[3], 0.f, 0.f, 0.f, 1.f);}
  
  size_t dim[CML_MAX_NUMBER_OF_CHANNELS];
  CMLVec4 invDim;
  size_t totalEntriesCount = 1;
  int32_t dimCount = 0;
  for(size_t d=0; d<CML_MAX_NUMBER_OF_CHANNELS; d++){
    if(dimensions[d] > 1){
      dim[dimCount] = dimensions[d];
      totalEntriesCount *= dimensions[d];
      invDim[dimCount] = 1.f / (dimensions[d] - 1);
      if(dimCount != d){cmlCpy4(r[dimCount], r[d]);}
      dimCount++;
    }
  }

  float* array = (float*)malloc(totalEntriesCount * numChannels * sizeof(float));
  float* ptr = array;
  
  CMLVec4 o1, o2, o3;

  switch(numChannels){
  case 1:
    switch(dimCount){
    case 0:
      cmlCpy1(ptr, o);
      break;
    case 1:
      for(size_t c0 = 0; c0 < dim[0]; ++c0){
        float f0 = (float)c0 * invDim[0];
        *ptr++ = o[0] + f0 * r[0][0];
      }
      break;
    case 2:
      for(size_t c1 = 0; c1 < dim[1]; ++c1){
        float f1 = (float)c1 * invDim[1];
        o1[0] = o[0] + f1 * r[1][0];
        for(size_t c0 = 0; c0 < dim[0]; ++c0){
          float f0 = (float)c0 * invDim[0];
          *ptr++ = o1[0] + f0 * r[0][0];
        }
      }
      break;
    case 3:
      for(size_t c2 = 0; c2 < dim[2]; ++c2){
        float f2 = (float)c2 * invDim[2];
        o2[0] = o[0] + f2 * r[2][0];
        for(size_t c1 = 0; c1 < dim[1]; ++c1){
          float f1 = (float)c1 * invDim[1];
          o1[0] = o2[0] + f1 * r[1][0];
          for(size_t c0 = 0; c0 < dim[0]; ++c0){
            float f0 = (float)c0 * invDim[0];
            *ptr++ = o1[0] + f0 * r[0][0];
          }
        }
      }
      break;
    case 4:
      for(size_t c3 = 0; c3 < dim[3]; ++c3){
        float f3 = (float)c3 * invDim[3];
        o3[0] = o[0] + f3 * r[3][0];
        for(size_t c2 = 0; c2 < dim[2]; ++c2){
          float f2 = (float)c2 * invDim[2];
          o2[0] = o3[0] + f2 * r[2][0];
          for(size_t c1 = 0; c1 < dim[1]; ++c1){
            float f1 = (float)c1 * invDim[1];
            o1[0] = o2[0] + f1 * r[1][0];
            for(size_t c0 = 0; c0 < dim[0]; ++c0){
              float f0 = (float)c0 * invDim[0];
              *ptr++ = o1[0] + f0 * r[0][0];
            }
          }
        }
      }
      break;
    }
    break;

  case 2:
    switch(dimCount){
    case 0:
      cmlCpy2(ptr, o);
      break;
    case 1:
      for(size_t c0 = 0; c0 < dim[0]; ++c0){
        float f0 = (float)c0 * invDim[0];
        *ptr++ = o[0] + f0 * r[0][0];
        *ptr++ = o[1] + f0 * r[0][1];
      }
      break;
    case 2:
      for(size_t c1 = 0; c1 < dim[1]; ++c1){
        float f1 = (float)c1 * invDim[1];
        o1[0] = o[0] + f1 * r[1][0];
        o1[1] = o[1] + f1 * r[1][1];
        for(size_t c0 = 0; c0 < dim[0]; ++c0){
          float f0 = (float)c0 * invDim[0];
          *ptr++ = o1[0] + f0 * r[0][0];
          *ptr++ = o1[1] + f0 * r[0][1];
        }
      }
      break;
    case 3:
      for(size_t c2 = 0; c2 < dim[2]; ++c2){
        float f2 = (float)c2 * invDim[2];
        o2[0] = o[0] + f2 * r[2][0];
        o2[1] = o[1] + f2 * r[2][1];
        for(size_t c1 = 0; c1 < dim[1]; ++c1){
          float f1 = (float)c1 * invDim[1];
          o1[0] = o2[0] + f1 * r[1][0];
          o1[1] = o2[1] + f1 * r[1][1];
          for(size_t c0 = 0; c0 < dim[0]; ++c0){
            float f0 = (float)c0 * invDim[0];
            *ptr++ = o1[0] + f0 * r[0][0];
            *ptr++ = o1[1] + f0 * r[0][1];
          }
        }
      }
      break;
    case 4:
      for(size_t c3 = 0; c3 < dim[3]; ++c3){
        float f3 = (float)c3 * invDim[3];
        o3[0] = o[0] + f3 * r[3][0];
        o3[1] = o[1] + f3 * r[3][1];
        for(size_t c2 = 0; c2 < dim[2]; ++c2){
          float f2 = (float)c2 * invDim[2];
          o2[0] = o3[0] + f2 * r[2][0];
          o2[1] = o3[1] + f2 * r[2][1];
          for(size_t c1 = 0; c1 < dim[1]; ++c1){
            float f1 = (float)c1 * invDim[1];
            o1[0] = o2[0] + f1 * r[1][0];
            o1[1] = o2[1] + f1 * r[1][1];
            for(size_t c0 = 0; c0 < dim[0]; ++c0){
              float f0 = (float)c0 * invDim[0];
              *ptr++ = o1[0] + f0 * r[0][0];
              *ptr++ = o1[1] + f0 * r[0][1];
            }
          }
        }
      }
      break;
    }
    break;

  case 3:
    switch(dimCount){
    case 0:
      cmlCpy3(ptr, o);
      break;
    case 1:
      for(size_t c0 = 0; c0 < dim[0]; ++c0){
        float f0 = (float)c0 * invDim[0];
        *ptr++ = o[0] + f0 * r[0][0];
        *ptr++ = o[1] + f0 * r[0][1];
        *ptr++ = o[2] + f0 * r[0][2];
      }
      break;
    case 2:
      for(size_t c1 = 0; c1 < dim[1]; ++c1){
        float f1 = (float)c1 * invDim[1];
        o1[0] = o[0] + f1 * r[1][0];
        o1[1] = o[1] + f1 * r[1][1];
        o1[2] = o[2] + f1 * r[1][2];
        for(size_t c0 = 0; c0 < dim[0]; ++c0){
          float f0 = (float)c0 * invDim[0];
          *ptr++ = o1[0] + f0 * r[0][0];
          *ptr++ = o1[1] + f0 * r[0][1];
          *ptr++ = o1[2] + f0 * r[0][2];
        }
      }
      break;
    case 3:
      for(size_t c2 = 0; c2 < dim[2]; ++c2){
        float f2 = (float)c2 * invDim[2];
        o2[0] = o[0] + f2 * r[2][0];
        o2[1] = o[1] + f2 * r[2][1];
        o2[2] = o[2] + f2 * r[2][2];
        for(size_t c1 = 0; c1 < dim[1]; ++c1){
          float f1 = (float)c1 * invDim[1];
          o1[0] = o2[0] + f1 * r[1][0];
          o1[1] = o2[1] + f1 * r[1][1];
          o1[2] = o2[2] + f1 * r[1][2];
          for(size_t c0 = 0; c0 < dim[0]; ++c0){
            float f0 = (float)c0 * invDim[0];
            *ptr++ = o1[0] + f0 * r[0][0];
            *ptr++ = o1[1] + f0 * r[0][1];
            *ptr++ = o1[2] + f0 * r[0][2];
          }
        }
      }
      break;
    case 4:
      for(size_t c3 = 0; c3 < dim[3]; ++c3){
        float f3 = (float)c3 * invDim[3];
        o3[0] = o[0] + f3 * r[3][0];
        o3[1] = o[1] + f3 * r[3][1];
        o3[2] = o[2] + f3 * r[3][2];
        for(size_t c2 = 0; c2 < dim[2]; ++c2){
          float f2 = (float)c2 * invDim[2];
          o2[0] = o3[0] + f2 * r[2][0];
          o2[1] = o3[1] + f2 * r[2][1];
          o2[2] = o3[2] + f2 * r[2][2];
          for(size_t c1 = 0; c1 < dim[1]; ++c1){
            float f1 = (float)c1 * invDim[1];
            o1[0] = o2[0] + f1 * r[1][0];
            o1[1] = o2[1] + f1 * r[1][1];
            o1[2] = o2[2] + f1 * r[1][2];
            for(size_t c0 = 0; c0 < dim[0]; ++c0){
              float f0 = (float)c0 * invDim[0];
              *ptr++ = o1[0] + f0 * r[0][0];
              *ptr++ = o1[1] + f0 * r[0][1];
              *ptr++ = o1[2] + f0 * r[0][2];
            }
          }
        }
      }
      break;
    }
    break;

  case 4:
    switch(dimCount){
    case 0:
      cmlCpy4(ptr, o);
      break;
    case 1:
      for(size_t c0 = 0; c0 < dim[0]; ++c0){
        float f0 = (float)c0 * invDim[0];
        *ptr++ = o[0] + f0 * r[0][0];
        *ptr++ = o[1] + f0 * r[0][1];
        *ptr++ = o[2] + f0 * r[0][2];
        *ptr++ = o[3] + f0 * r[0][3];
      }
      break;
    case 2:
      for(size_t c1 = 0; c1 < dim[1]; ++c1){
        float f1 = (float)c1 * invDim[1];
        o1[0] = o[0] + f1 * r[1][0];
        o1[1] = o[1] + f1 * r[1][1];
        o1[2] = o[2] + f1 * r[1][2];
        o1[3] = o[3] + f1 * r[1][3];
        for(size_t c0 = 0; c0 < dim[0]; ++c0){
          float f0 = (float)c0 * invDim[0];
          *ptr++ = o1[0] + f0 * r[0][0];
          *ptr++ = o1[1] + f0 * r[0][1];
          *ptr++ = o1[2] + f0 * r[0][2];
          *ptr++ = o1[3] + f0 * r[0][3];
        }
      }
      break;
    case 3:
      for(size_t c2 = 0; c2 < dim[2]; ++c2){
        float f2 = (float)c2 * invDim[2];
        o2[0] = o[0] + f2 * r[2][0];
        o2[1] = o[1] + f2 * r[2][1];
        o2[2] = o[2] + f2 * r[2][2];
        o2[3] = o[3] + f2 * r[2][3];
        for(size_t c1 = 0; c1 < dim[1]; ++c1){
          float f1 = (float)c1 * invDim[1];
          o1[0] = o2[0] + f1 * r[1][0];
          o1[1] = o2[1] + f1 * r[1][1];
          o1[2] = o2[2] + f1 * r[1][2];
          o1[3] = o2[3] + f1 * r[1][3];
          for(size_t c0 = 0; c0 < dim[0]; ++c0){
            float f0 = (float)c0 * invDim[0];
            *ptr++ = o1[0] + f0 * r[0][0];
            *ptr++ = o1[1] + f0 * r[0][1];
            *ptr++ = o1[2] + f0 * r[0][2];
            *ptr++ = o1[3] + f0 * r[0][3];
          }
        }
      }
      break;
    case 4:
      for(size_t c3 = 0; c3 < dim[3]; ++c3){
        float f3 = (float)c3 * invDim[3];
        o3[0] = o[0] + f3 * r[3][0];
        o3[1] = o[1] + f3 * r[3][1];
        o3[2] = o[2] + f3 * r[3][2];
        o3[3] = o[3] + f3 * r[3][3];
        for(size_t c2 = 0; c2 < dim[2]; ++c2){
          float f2 = (float)c2 * invDim[2];
          o2[0] = o3[0] + f2 * r[2][0];
          o2[1] = o3[1] + f2 * r[2][1];
          o2[2] = o3[2] + f2 * r[2][2];
          o2[3] = o3[3] + f2 * r[2][3];
          for(size_t c1 = 0; c1 < dim[1]; ++c1){
            float f1 = (float)c1 * invDim[1];
            o1[0] = o2[0] + f1 * r[1][0];
            o1[1] = o2[1] + f1 * r[1][1];
            o1[2] = o2[2] + f1 * r[1][2];
            o1[3] = o2[3] + f1 * r[1][3];
            for(size_t c0 = 0; c0 < dim[0]; ++c0){
              float f0 = (float)c0 * invDim[0];
              *ptr++ = o1[0] + f0 * r[0][0];
              *ptr++ = o1[1] + f0 * r[0][1];
              *ptr++ = o1[2] + f0 * r[0][2];
              *ptr++ = o1[3] + f0 * r[0][3];
            }
          }
        }
      }
      break;
    }
    break;
  }
  
  return array;
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


// All converter functions take an input and output parameter. For channeled
// colors, the type float* is assumed.
//
// The return value is either a pointer to the output buffer or NULL in case
// of an error.
//
// When both the input and output buffer is provided by the user, the return
// value will be the same as the provided output parameter.
//
// If the output parameter is NULL, CML will allocate sufficient memory using
// malloc(). The user is responsible for releasing the memory using free().
//
// The input and output parameter can be the same. In this case, CML will
// will convert all values on the same buffer (and hence overwrite the old
// values). Note that CML is optimized for this case and will likely perform
// faster with just one buffer rather than using two separate buffers.
//
// In case the input and output parameter are the same but the output depicts
// values of a colorspace which has MORE channels than the input color space,
// no error is raised (Though, in the debug-version of CML, a warning is
// printed). CML assumes that the programmer knows what he is doing and will
// use the provided buffer both for input and output BUT expects the separate
// input colors to be aligned the same way as the output colors. This means
// for example when converting RGB to CMYK, CML expects the RGB values to be
// stored in the format RGBXRGBXRGBX... where X is one padding float whose
// value will be ignored when converting. Remind yourself that this only holds
// true if input and output point to the same buffer.
//
// Vice versa, if the input and output parameter are the same but the output
// depicts values of a colorspace which has LESS channels than the input
// color space, no error is raised (Though again, in the debug-version of
// CML, a warning is printed). This time, the separate colors of the output
// colorspace will be aligned the same way as the input colors. For example,
// when converting CMYK to RGB, the resulting RGB values will be stored in the
// format RGBXRGBXRGBX... where X is one padding float whose value will be
// undefined and should be ignored.
//
// In the debug-version, every converter function returns NULL on error. In
// the release-version, CML will do no checks, does not return CML_NULL and
// might therefore crash when there is an error. An error occurs if ...
// - ... the input buffer is CML_NULL
// - ... memory allocation was not successfull





// This macro makes it possible to convert with input and output pointers ...
// - ... which are different
// - ... where output is NULL and will be allocated automatically with malloc
// - ... which are the same
//
// After this macro, in and out are defined as float-arrays.
// The sameBuffer variable depicts if out is the same as in.

#if CML_DEBUG
  #define CML_CONVERTER_INOUT_PARAMETER(outsymbol, insymbol, outchannels, inchannels) \
    if(insymbol == CML_NULL){\
      cmlError("Input buffer is NULL.");\
    }\
    float* out;\
    const float* in = insymbol;\
    size_t floatAlign;\
    register CMLBool sameBuffer;\
    if(!outsymbol){\
      out = (float*)cml_Malloc(count * outchannels * sizeof(float));\
      sameBuffer = CML_FALSE;\
      floatAlign = outchannels;\
    }else if(insymbol == outsymbol){\
      if(outchannels > inchannels){\
        cmlError("Output colorspace has too many dimensions to store in buffer. Expecting the input values to be aligned.");\
      }\
      if(outchannels < inchannels){\
        cmlError("Output colorspace has fewer dimensions than usable in the buffer. Writing the output values aligned.");\
      }\
      out = outsymbol;\
      sameBuffer = CML_TRUE;\
      floatAlign = CML_MAX(outchannels,inchannels);\
    }else{\
      out = outsymbol;\
      sameBuffer = CML_FALSE;\
      floatAlign = outchannels;\
    }
#else
  #define CML_CONVERTER_INOUT_PARAMETER(outsymbol, insymbol, outchannels, inchannels) \
    float* out;\
    const float* in = insymbol;\
    size_t floatAlign;\
    register CMLBool sameBuffer;\
    if(!outsymbol){\
      out = (float*)cml_Malloc(count * outchannels * sizeof(float));\
      sameBuffer = CML_FALSE;\
      floatAlign = outchannels;\
    }else if(insymbol == outsymbol){\
      out = outsymbol;\
      sameBuffer = CML_TRUE;\
      floatAlign = CML_MAX(outchannels,inchannels);\
    }else{\
      out = outsymbol;\
      sameBuffer = CML_FALSE;\
      floatAlign = outchannels;\
    }
#endif




#define CML_CONVERTER_MEMCPY(numchannels)\
  if(!sameBuffer){\
    memcpy(out, in, count * numchannels * sizeof(float));\
  }\


#define CML_CONVERTER_FIRST_STEP(firstconverter) \
  if(sameBuffer){\
    (firstconverter ## _SB)(cm, out, count, floatAlign);\
  }else{\
    (firstconverter)(cm, out, in, count);\
  }\



#define CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(outsymbol, insymbol, outchannels) \
  float* out;\
  const CMLFunction* in = insymbol;\
  if(!outsymbol){\
    out = (float*)cml_Malloc(count * outchannels * sizeof(float));\
  }else{\
    out = outsymbol;\
  }\
  CMLBool sameBuffer;\
  float* xyzbuf;\
  size_t floatAlign;\
  if(outchannels < CML_XYZ_NUMCHANNELS){\
    xyzbuf = (float*)cml_Malloc(count * CML_XYZ_NUMCHANNELS * sizeof(float));\
    sameBuffer = CML_FALSE;\
    floatAlign = CML_XYZ_NUMCHANNELS;\
  }else{\
    xyzbuf = out;\
    sameBuffer = CML_TRUE;\
    floatAlign = outchannels;\
  }


// Add return out; as soon as it is soweit.
#define CML_CONVERTER_SPECTRUM_RETURN \
  if(!sameBuffer){free(xyzbuf);}



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

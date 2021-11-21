
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.


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
// The samebuffer variable depicts if out is the same as in.

#ifndef NDEBUG
  #define CML_CONVERTER_INOUT_PARAMETER(outsymbol, insymbol, outchannels, inchannels) \
    if(insymbol == CML_NULL){\
      cmlError("CML_CONVERTER_INOUT_PARAMETER", "Input buffer is NULL.");\
    }\
    float* out;\
    const float* in = insymbol;\
    CMLuint32 floatalign;\
    register CMLBool samebuffer;\
    if(!outsymbol){\
      out = (float*)cmlAllocate(count * outchannels * sizeof(float));\
      samebuffer = CMLFALSE;\
      floatalign = outchannels;\
    }else if(insymbol == outsymbol){\
      if(outchannels > inchannels){\
        cmlError("CML_CONVERTER_INOUT_PARAMETER", "Output colorspace has too many dimensions to store in buffer. Expecting the input values to be aligned.");\
      }\
      if(outchannels < inchannels){\
        cmlError("CML_CONVERTER_INOUT_PARAMETER", "Output colorspace has fewer dimensions than usable in the buffer. Writing the output values aligned.");\
      }\
      out = outsymbol;\
      samebuffer = CMLTRUE;\
      floatalign = CML_MAX(outchannels,inchannels);\
    }else{\
      out = outsymbol;\
      samebuffer = CMLFALSE;\
      floatalign = outchannels;\
    }
#else
  #define CML_CONVERTER_INOUT_PARAMETER(outsymbol, insymbol, outchannels, inchannels) \
    float* out;\
    const float* in = insymbol;\
    CMLuint32 floatalign;\
    register CMLBool samebuffer;\
    if(!outsymbol){\
      out = (float*)cmlAllocate(count * outchannels * sizeof(float));\
      samebuffer = CMLFALSE;\
      floatalign = outchannels;\
    }else if(insymbol == outsymbol){\
      out = outsymbol;\
      samebuffer = CMLTRUE;\
      floatalign = CML_MAX(outchannels,inchannels);\
    }else{\
      out = outsymbol;\
      samebuffer = CMLFALSE;\
      floatalign = outchannels;\
    }
#endif




#define CML_CONVERTER_MEMCPY(numchannels)\
  if(!samebuffer){\
    memcpy(out, in, count * numchannels * sizeof(float));\
  }\


#define CML_CONVERTER_FIRST_STEP(firstconverter) \
  if(samebuffer){\
    (firstconverter ## _SB)(cm, out, count, floatalign);\
  }else{\
    (firstconverter)(cm, out, in, count);\
  }\


// Add return out; as soon as it is soweit.
#define CML_CONVERTER_RETURN





#define CML_CONVERTER_SPECTRUM_INOUT_PARAMETER(outsymbol, insymbol, outchannels) \
  float* out;\
  const CMLFunction* in = insymbol;\
  if(!outsymbol){\
    out = (float*)cmlAllocate(count * outchannels * sizeof(float));\
  }else{\
    out = outsymbol;\
  }\
  CMLBool samebuffer;\
  float* xyzbuf;\
  CMLuint32 floatalign;\
  if(outchannels < CML_XYZ_NUMCHANNELS){\
    xyzbuf = (float*)cmlAllocate(count * CML_XYZ_NUMCHANNELS * sizeof(float));\
    samebuffer = CMLFALSE;\
    floatalign = CML_XYZ_NUMCHANNELS;\
  }else{\
    xyzbuf = out;\
    samebuffer = CMLTRUE;\
    floatalign = outchannels;\
  }


// Add return out; as soon as it is soweit.
#define CML_CONVERTER_SPECTRUM_RETURN \
  if(!samebuffer){free(xyzbuf);}


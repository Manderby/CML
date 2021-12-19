
// This file contains the declarations of all raw color transformations and
// various functions used in color science.
//
// Use this API if you want to do conversions manually. But be aware that this
// API can get slow when lots of data needs to be converted. Use ColorMachines
// instead.
//
// Note that in CML, functions usually return values in the FIRST parameter.
// Usually, the needed space for the return buffer must be provided, CML will
// not allocate buffer memory for you. Also note that there is no overflow
// detection, so make sure, your buffers provide enough space. Note however
// that a function starting with "cmlCreate..." will indeed allocate space
// which needs to be deleted manually. This will furthermore be indicated by an
// additional comment at the corresponding API.



// Convert between XYZ and Yxy.
// When the conversion results in a division by zero the values of the
// whitePoint with Y=0 will be set. When NULL is provided as whitePoint,
// the values will be set to 0.
CML_API void cmlConvertXYZToYxy(
  CMLVec3 yxy,
  const CMLVec3 xyz,
  const CMLVec3 whitePointYxy);

CML_API void cmlConvertYxyToXYZ(
  CMLVec3 xyz,
  const CMLVec3 yxy,
  const CMLVec3 whitePointXYZ);



// Convert between Yxy and Yupvp.
// When the conversion results in a division by zero the values of the
// whitePoint with Y=0 will be set. When NULL is provided as whitePoint,
// the values will be set to 0.
CML_API void cmlConvertYxyToYupvp(
  CMLVec3 yupvp,
  const CMLVec3 yxy,
  const CMLVec3 whitePointYupvp);

CML_API void cmlConvertYupvpToYxy(
  CMLVec3 yxy,
  const CMLVec3 yupvp,
  const CMLVec3 whitePointYxy);



// Convert between Yupvp and Yuv.
CML_API void cmlConvertYupvpToYuv(
  CMLVec3 yuv,
  const CMLVec3 yupvp);

CML_API void cmlConvertYuvToYupvp(
  CMLVec3 yupvp,
  const CMLVec3 yuv);



// Convert between Yupvp and Luv.
CML_API void cmlConvertYupvpToLuv(
  CMLVec3 luv,
  const CMLVec3 yupvp,
  const CMLVec3 whitePointYupvp);

CML_API void cmlConvertLuvToYupvp(
  CMLVec3 yupvp,
  const CMLVec3 luv,
  const CMLVec3 whitePointYupvp);



// Convert between XYZ and Lab.
// Note that the BaseAPI only supports CIELAB. Use ColorMachines if you need
// other Lab spaces like Hunter lab or chromatic valence spaces.
CML_API void cmlConvertXYZToLab(
  CMLVec3 lab,
  const CMLVec3 xyz,
  const CMLVec3 whitePointXYZ);

CML_API void cmlConvertLabToXYZ(
  CMLVec3 xyz,
  const CMLVec3 lab,
  const CMLVec3 whitePointXYZ);



// Convert between Lab and Lch.
CML_API void cmlConvertLabToLch(
  CMLVec3 lch,
  const CMLVec3 lab);

CML_API void cmlConvertLchToLab(
  CMLVec3 lab,
  const CMLVec3 lch);



// Convert between XYZ and RGB.
CML_API void cmlConvertXYZToRGB(
  CMLVec3 rgb,
  const CMLVec3 xyz,
  const CMLMat33 XYZToRGBMatrix,
  const CMLFunction* linearToRResponse,
  const CMLFunction* linearToGResponse,
  const CMLFunction* linearToBResponse);

CML_API void cmlConvertRGBToXYZ(
  CMLVec3 xyz,
  const CMLVec3 rgb,
  const CMLMat33 RGBToXYZMatrix,
  const CMLFunction* RToLinearResponse,
  const CMLFunction* GToLinearResponse,
  const CMLFunction* BToLinearResponse);



// Convert between RGB and YCbCr.
CML_API void cmlConvertRGBToYCbCr(
  CMLVec3 ycbcr,
  const CMLVec3 rgb,
  const CMLVec3 redPrimaryYxy,
  const CMLVec3 bluePrimaryYxy,
  const CMLVec3 whitePointXYZ);

CML_API void cmlConvertYCbCrToRGB(
  CMLVec3 rgb,
  const CMLVec3 ycbcr,
  const CMLVec3 redPrimaryYxy,
  const CMLVec3 bluePrimaryYxy,
  const CMLVec3 whitePointXYZ);



// Convert between RGB and HSV.
CML_API void cmlConvertRGBToHSV(
  CMLVec3 hsv,
  const CMLVec3 rgb);

CML_API void cmlConvertHSVToRGB(
  CMLVec3 rgb,
  const CMLVec3 hsv);



// Betwen HSV and HSL.
CML_API void cmlConvertHSVToHSL(
  CMLVec3 hsl,
  const CMLVec3 hsv);

CML_API void cmlConvertHSLToHSV(
  CMLVec3 hsv,
  const CMLVec3 hsl);



// Betwen Spectrum and XYZ.
// This method always returns a radiometric result. If you would like to have
// a colorimetric result, you need to divide the result by its Y component.
CML_API void cmlConvertIlluminationSpectrumToXYZ(
  CMLVec3 xyz,
  const CMLFunction* specIll,
  const CMLObserver* observer);

// This method always returns a radiometric result. If you would like to have
// a colorimetric result, you need to divide the result by the Y component of
// the white point defined by the illumination.
CML_API void cmlConvertRemissionSpectrumToXYZ(
  CMLVec3 xyz,
  const CMLFunction* specRem,
  const CMLFunction* specIll,
  const CMLObserver* observer);



// Convert between different chromatic adaptation XYZ.

// Computes a chromatic adaptation matrix and returns it in the first parameter.
// Note that you can use the type CML_CHROMATIC_ADAPTATION_NONE to convert
// between whitePoints with different radiometric Y values.
CML_API void cmlComputeChromaticAdaptationMatrix(
  CMLMat33 matrix,
  CMLChromaticAdaptationType adaptationType,
  CMLVec3 adaptedWhitePointYxy,
  CMLVec3 whitePointYxy);

// Convert xyz to the chromatic adapted adaptXYZ
CML_API void cmlConvertXYZToChromaticAdaptedXYZ(
  CMLVec3 adaptXYZ,
  const CMLVec3 xyz,
  const CMLMat33 matrix);



// Returns 3 CMLFunctions denoting the x_, y_ and z_ distribution functions
// of a desired observer. The returned functions must be deleted manually with
// cmlReleaseFunction. If an invalid observer is given or if the observer is
// CML_OBSERVER_CUSTOM, the buffer will be filled with CML_NULL pointers.
CML_API void cmlCreateSpecDistFunctions(
  CMLFunction* functions[3],
  CMLObserverType observerType);



// Creates and returns a new spectrum with the given input parameters. The
// temperature parameter is expected in [Degree Kelvin] for the illumination
// types CML_ILLUMINATION_BLACKBODY and CML_ILLUMINATION_D_ILLUMINANT. For any
// other type, the temperature parameter is ignored. The returned CMLFunction
// must be deleted manually with cmlReleaseFunction. Only types denoting
// built-in illuminations are valid (no custom illuminations).
// Invalid illumination types will return CML_NULL.
CML_API CMLFunction* cmlCreateIlluminationSpectrum(
  CMLIlluminationType illuminationType,
  float temperature);



// Returns the correlated color temperature in [Degree Kelvin] for a given
// whitePoint in Yuv. Currently, the Robertson method is implemented.
// Beware! This function expects Yuv, not Yxy!
CML_API float cmlGetCorrelatedColorTemperature(
  const CMLVec3 whitePointYuv);



// The following three functions return information to predefined RGB color
// spaces. The CML_RGB_CUSTOM space is not valid. If an invalid colorSpaceType
// is provided, the values will be uninitialized.

// Returns all three primaries of a predefined RGB colorspace. Note that
// the Y component of the three primaries will always be 1.
CML_API void cmlGetRGBColorSpacePrimaries(
  CMLRGBColorSpaceType type,
  CMLVec3 primaryRYxy,
  CMLVec3 primaryGYxy,
  CMLVec3 primaryBYxy);
  
// Returns the illumination type of a predefined RGB colorspace.
CML_API CMLIlluminationType cmlGetRGBColorSpaceIlluminationType(
  CMLRGBColorSpaceType type);
  
CML_API CMLResponseCurveType cmlGetRGBColorSpaceResponseCurveType(
  CMLRGBColorSpaceType type);



// Computes the matrix for RGB -> XYZ conversions given the three primaries and
// the whitePoint as Yxy colors. Note that the Y component of the three
// primaries will be changed by this function call. Also note that you can
// choose to have a colorimetric instead of a radiometric computation by simply
// setting the Y component of the whitePoint to 1.
// Also note that in order to get the inverse transformation matrix, simply
// use the cmlInvertMat33 function.
CML_API void cmlComputeRGBToXYZMatrix(
  CMLMat33 rgbToXyzMatrix,
  CMLVec3 primaryRYxy,
  CMLVec3 primaryGYxy,
  CMLVec3 primaryBYxy,
  const CMLVec3 whitePointYxy);



// Returns the number of channels a specific color type uses. If an invalid
// color type is given, the returned value will be 0.
CML_API CMLuint32 cmlGetNumChannels( CMLColorType colorType);



// Returns the minimal or maximal bounds for each channel of a specified color
// type. If an invalid color type is given, the returned values will be
// undefined.
CML_API void cmlGetMinBounds(float* buffer, CMLColorType colorType);
CML_API void cmlGetMaxBounds(float* buffer, CMLColorType colorType);



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

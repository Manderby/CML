
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
// that a function starting with "CMLcreate..." will indeed allocate space
// which needs to be deleted manually. This will furthermore be indicated by an
// additional comment at the corresponding API.



// When the conversion results in a division by zero the values of the
// whitepoint with Y=0 will be set. When NULL is provided as whitepoint,
// the values will be set to 0.
CML_API void CMLconvertXYZtoYxy(  CMLVec3       yxy,
                           const CMLVec3       xyz,
                           const CMLVec3       whitepointYxy);

CML_API void CMLconvertYxytoXYZ(  CMLVec3       xyz,
                           const CMLVec3       yxy,
                           const CMLVec3       whitepointXYZ);

CML_API void CMLconvertYxytoYupvp(CMLVec3       yupvp,
                           const CMLVec3       yxy,
                           const CMLVec3       whitepointYupvp);

CML_API void CMLconvertYupvptoYxy(CMLVec3       yxy,
                           const CMLVec3       yupvp,
                           const CMLVec3       whitepointYxy);


// ///////////////////////////////////////////


CML_API void CMLconvertYupvptoYuv(CMLVec3       yuv,
                           const CMLVec3       yupvp);

CML_API void CMLconvertYuvtoYupvp(CMLVec3       yupvp,
                           const CMLVec3       yuv);


// ///////////////////////////////////////////


CML_API void CMLconvertYupvptoLuv(CMLVec3       luv,
                           const CMLVec3       yupvp,
                           const CMLVec3       whitepointYupvp);

CML_API void CMLconvertLuvtoYupvp(CMLVec3       yupvp,
                           const CMLVec3       luv,
                           const CMLVec3       whitepointYupvp);


// ///////////////////////////////////////////
// Note that the BaseAPI only supports CIELAB. Use ColorMachines if you need
// other Lab spaces like Hunter lab or chromatic valence spaces.

CML_API void CMLconvertXYZtoLab(  CMLVec3       lab,
                           const CMLVec3       xyz,
                           const CMLVec3       whitepointXYZ);

CML_API void CMLconvertLabtoXYZ(  CMLVec3       xyz,
                           const CMLVec3       lab,
                           const CMLVec3       whitepointXYZ);

// ///////////////////////////////////////////


CML_API void CMLconvertLabtoLch(  CMLVec3       lch,
                           const CMLVec3       lab);

CML_API void CMLconvertLchtoLab(  CMLVec3       lab,
                           const CMLVec3       lch);


// ///////////////////////////////////////////


CML_API void CMLconvertXYZtoRGB(  CMLVec3       rgb,
                           const CMLVec3       xyz,
                           const CMLMat33      XYZtoRGBmatrix,
                           const CMLFunction*  LineartoRResponse,
                           const CMLFunction*  LineartoGResponse,
                           const CMLFunction*  LineartoBResponse);

CML_API void CMLconvertRGBtoXYZ(  CMLVec3       xyz,
                           const CMLVec3       rgb,
                           const CMLMat33      RGBtoXYZmatrix,
                           const CMLFunction*  RtoLinearResponse,
                           const CMLFunction*  GtoLinearResponse,
                           const CMLFunction*  BtoLinearResponse);


// ///////////////////////////////////////////


CML_API void CMLconvertRGBtoYCbCr(CMLVec3       ycbcr,
                           const CMLVec3       rgb,
                           const CMLVec3       redprimaryYxy,
                           const CMLVec3       blueprimaryYxy,
                           const CMLVec3       whitepointXYZ);

CML_API void CMLconvertYCbCrtoRGB(CMLVec3       rgb,
                           const CMLVec3       ycbcr,
                           const CMLVec3       redprimaryYxy,
                           const CMLVec3       blueprimaryYxy,
                           const CMLVec3       whitepointXYZ);


// ///////////////////////////////////////////


CML_API void CMLconvertRGBtoHSV(  CMLVec3       hsv,
                           const CMLVec3       rgb);

CML_API void CMLconvertHSVtoRGB(  CMLVec3       rgb,
                           const CMLVec3       hsv);

// ///////////////////////////////////////////


CML_API void CMLconvertHSVtoHSL(  CMLVec3       hsl,
                           const CMLVec3       hsv);

CML_API void CMLconvertHSLtoHSV(  CMLVec3       hsv,
                           const CMLVec3       hsl);


// ///////////////////////////////////////////


// This method always returns a radiometric result. If you would like to have
// a colorimetric result, you need to divide the result by its Y component.
CML_API void CMLconvertIlluminationSpectrumtoXYZ (
                           CMLVec3             xyz,
                     const CMLFunction*        specIll,
                     const CMLObserver*        observer);

// This method always returns a radiometric result. If you would like to have
// a colorimetric result, you need to divide the result by the Y component of
// the white point defined by the illumination.
CML_API void CMLconvertRemissionSpectrumtoXYZ (
                           CMLVec3             xyz,
                     const CMLFunction*        specRem,
                     const CMLFunction*        specIll,
                     const CMLObserver*        observer);


// ///////////////////////////////////////////


// Computes a chromatic adaptation matrix and returns it in the first parameter.
// Note that you can use the type CML_CHROMATIC_ADAPTATION_NONE to convert
// between whitepoints with different radiometric Y values.
CML_API void cmlComputeChromaticAdaptationMatrix(  CMLMat33 matrix,
                                CMLChromaticAdaptationType adaptationtype,
                                                   CMLVec3 adaptedwhitepointYxy,
                                                   CMLVec3 whitepointYxy);


// Convert xyz to the chromatic adapted adaptxyz
CML_API void CMLconvertXYZtoChromaticAdaptedXYZ(  CMLVec3 adaptxyz,
                                           const CMLVec3 xyz,
                                          const CMLMat33 matrix);


// ///////////////////////////////////////////



// Returns 3 CMLFunctions denoting the x_, y_ and z_ distribution functions
// of a desired observer. The returned functions must be deleted manually. If
// an invalid observer is given or if the observer is CML_OBSERVER_CUSTOM, the
// buffer will be filled with CML_NULL pointers.
CML_API void cmlCreateSpecDistFunctions( CMLFunction* functions[3],
                                                 CMLObserverType observer);


// Creates and returns a new spectrum with the given input parameters. The
// temperature parameter is expected in [Degree Kelvin] for the illumination
// types CML_ILLUMINATION_BLACKBODY and CML_ILLUMINATION_D_ILLUMINANT. For any
// other type, the temperature parameter is ignored. The returned CMLFunction
// must be deleted manually. Only types denoting built-in illuminations are
// valid (no custom illuminations). Invalid illumination types will return
// CML_NULL.
CML_API CMLFunction* cmlCreateIlluminationSpectrum(
                                    CMLIlluminationType illuminationtype,
                                    float               temperature);


// Returns the correlated color temperature in [Degree Kelvin] for a given
// whitepoint in Yuv. Currently, the Robertson method is implemented.
// Beware! This function expects Yuv, not Yxy!
CML_API float CMLgetCorrelatedColorTemperature(
                                    const CMLVec3       whitepointYuv);


// The following three functions return information to predefined RGB color
// spaces. The CML_RGB_CUSTOM space is not valid. If an invalid colorspacetype
// is provided, the values will be uninitialized.

// Returns all three primaries of a predefined RGB colorspace. Note that
// the Y component of the three primaries will always be 1.
CML_API void CMLgetRGBColorSpacePrimaries(
                                  CMLRGBColorSpace      colorspacetype,
                                  CMLVec3               primaryRYxy,
                                  CMLVec3               primaryGYxy,
                                  CMLVec3               primaryBYxy);
// Returns the illumination type of a predefined RGB colorspace.
CML_API CMLIlluminationType CMLgetRGBColorSpaceIlluminationType(
                                  CMLRGBColorSpace      colorspacetype);
CML_API CMLResponseCurvePreset CMLgetRGBColorSpaceResponseCurvePreset
                                      (CMLRGBColorSpace colorspacetype);

// Computes the matrix for RGB -> XYZ conversions given the three primaries and
// the whitepoint as Yxy colors. Note that the Y component of the three
// primaries will be changed by this function call. Also note that you can
// choose to have a colorimetric instead of a radiometric computation by simply
// setting the Y component of the whitepoint to 1.
// Also note that in order to get the inverse transformation matrix, simply
// use the cmlInvertMat33 functin.
CML_API void CMLcomputeRGBtoXYZMatrix(
                                              CMLMat33  rgbtoxyzmatrix,
                                              CMLVec3   primaryRYxy,
                                              CMLVec3   primaryGYxy,
                                              CMLVec3   primaryBYxy,
                                        const CMLVec3   whitepointYxy);

// Returns the number of channels a specific color type uses. If an invalid
// color type is given, the returned value will be 0.
CML_API CMLuint32 CMLgetNumChannels( CMLColorType        colorType);


// Returns the minimal or maximal bounds for each channel of a specified color
// type. If an invalid color type is given, the returned values will be
// undefined.
CML_API void CMLgetMinBounds(float* buffer, CMLColorType colorType);
CML_API void CMLgetMaxBounds(float* buffer, CMLColorType colorType);


// The following functions return an ASCII string describing the desired value.
// Do not delete the returned pointers. If an invalid input parameter is given,
// the returned value will be invalid.
CML_API const char* CMLgetColorTypeString               (CMLColorType colorType);
CML_API const char* CMLgetObserverTypeString            (CMLObserverType observertype);
CML_API const char* CMLgetIlluminationTypeString        (CMLIlluminationType illuminationtype);
CML_API const char* CMLgetRGBColorspaceString           (CMLRGBColorSpace colorspacetype);
CML_API const char* CMLgetLabSpaceTypeString            (CMLLabColorSpaceType labspacetype);
CML_API const char* CMLgetRGBResponsePresetString  (CMLResponseCurvePreset preset);
CML_API const char* CMLgetFunctionTypeString       (CMLFunctionType functiontype);
CML_API const char* CMLgetGrayComputationTypeString     (CMLGrayComputationType computationtype);
CML_API const char* CMLgetCMYKTransformTypeString       (CMLCMYKTransformType transformtype);
CML_API const char* CMLgetChromaticAdaptationTypeString (CMLChromaticAdaptationType chromaticadaptationtype);



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

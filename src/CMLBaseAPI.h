
//
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
//
//
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.




// When the conversion results in a division by zero the values of the
// whitepoint with Y=0 will be set. When NULL is provided as whitepoint,
// the values will be set to 0.
CMLAPI void CMLconvertXYZtoYxy(  CMLVec3       Yxy,
                           const CMLVec3       XYZ,
                           const CMLVec3       whitepointYxy);

CMLAPI void CMLconvertYxytoXYZ(  CMLVec3       XYZ,
                           const CMLVec3       Yxy,
                           const CMLVec3       whitepointXYZ);

CMLAPI void CMLconvertYxytoYupvp(CMLVec3       Yupvp,
                           const CMLVec3       Yxy,
                           const CMLVec3       whitepointYupvp);

CMLAPI void CMLconvertYupvptoYxy(CMLVec3       Yxy,
                           const CMLVec3       Yupvp,
                           const CMLVec3       whitepointYxy);


// ///////////////////////////////////////////


CMLAPI void CMLconvertYupvptoYuv(CMLVec3       Yuv,
                           const CMLVec3       Yupvp);

CMLAPI void CMLconvertYuvtoYupvp(CMLVec3       Yupvp,
                           const CMLVec3       Yuv);


// ///////////////////////////////////////////


CMLAPI void CMLconvertYupvptoLuv(CMLVec3       Luv,
                           const CMLVec3       Yupvp,
                           const CMLVec3       whitepointYupvp);

CMLAPI void CMLconvertLuvtoYupvp(CMLVec3       Yupvp,
                           const CMLVec3       Luv,
                           const CMLVec3       whitepointYupvp);


// ///////////////////////////////////////////
// Note that the BaseAPI only supports CIELAB. Use ColorMachines if you need
// other Lab spaces like Hunter lab or chromatic valence spaces.

CMLAPI void CMLconvertXYZtoLab(  CMLVec3       Lab,
                           const CMLVec3       XYZ,
                           const CMLVec3       whitepointXYZ);

CMLAPI void CMLconvertLabtoXYZ(  CMLVec3       XYZ,
                           const CMLVec3       Lab,
                           const CMLVec3       whitepointXYZ);

// ///////////////////////////////////////////


CMLAPI void CMLconvertLabtoLch(  CMLVec3       Lch,
                           const CMLVec3       Lab);

CMLAPI void CMLconvertLchtoLab(  CMLVec3       Lab,
                           const CMLVec3       Lch);


// ///////////////////////////////////////////


CMLAPI void CMLconvertXYZtoRGB(  CMLVec3       RGB,
                           const CMLVec3       XYZ,
                           const CMLMat33      XYZtoRGBmatrix,
                           const CMLFunction*  LineartoRResponse,
                           const CMLFunction*  LineartoGResponse,
                           const CMLFunction*  LineartoBResponse);

CMLAPI void CMLconvertRGBtoXYZ(  CMLVec3       XYZ,
                           const CMLVec3       RGB,
                           const CMLMat33      RGBtoXYZmatrix,
                           const CMLFunction*  RtoLinearResponse,
                           const CMLFunction*  GtoLinearResponse,
                           const CMLFunction*  BtoLinearResponse);


// ///////////////////////////////////////////


CMLAPI void CMLconvertRGBtoYCbCr(CMLVec3       YCbCr,
                           const CMLVec3       RGB,
                           const CMLVec3       redprimaryYxy,
                           const CMLVec3       blueprimaryYxy,
                           const CMLVec3       whitepointXYZ);

CMLAPI void CMLconvertYCbCrtoRGB(CMLVec3       RGB,
                           const CMLVec3       YCbCr,
                           const CMLVec3       redprimaryYxy,
                           const CMLVec3       blueprimaryYxy,
                           const CMLVec3       whitepointXYZ);


// ///////////////////////////////////////////


CMLAPI void CMLconvertRGBtoHSV(  CMLVec3       HSV,
                           const CMLVec3       RGB);

CMLAPI void CMLconvertHSVtoRGB(  CMLVec3       RGB,
                           const CMLVec3       HSV);

// ///////////////////////////////////////////


CMLAPI void CMLconvertHSVtoHSL(  CMLVec3       HSL,
                           const CMLVec3       HSV);

CMLAPI void CMLconvertHSLtoHSV(  CMLVec3       HSV,
                           const CMLVec3       HSL);


// ///////////////////////////////////////////


// This method always returns a radiometric result. If you would like to have
// a colorimetric result, you need to divide the result by its Y component or
// use a whitepoint with the two functions below.
CMLAPI void CMLconvertSpectrumtoRadiometricXYZ (
                           CMLVec3             XYZ,
                     const CMLFunction*        spectrum,
                     const CMLObserver*        observer);

// This method always returns a radiometric result. If you would like to have
// a colorimetric result, you need to divide the result by its Y component.
CMLAPI void CMLconvertIlluminationSpectrumtoXYZ (
                           CMLVec3             XYZ,
                     const CMLFunction*        spectrum,
                     const CMLWhitepoint*      whitepoint);

// This method always returns a radiometric result. If you would like to have
// a colorimetric result, you need to divide the result by the Y component of
// the white point defined by the illumination.
CMLAPI void CMLconvertRemissionSpectrumtoXYZ (
                           CMLVec3             XYZ,
                     const CMLFunction*        spectrum,
                     const CMLWhitepoint*      whitepoint);


// ///////////////////////////////////////////


// Computes a chromatic adaptation matrix and returns it in the first parameter.
// Note that you can use the type CML_CHROMATIC_ADAPTATION_NONE to convert
// between whitepoints with different radiometric Y values.
CMLAPI void cmlComputeChromaticAdaptationMatrix(  CMLMat33 matrix,
                                CMLChromaticAdaptationType adaptationtype,
                                                   CMLVec3 adaptedwhitepointYxy,
                                                   CMLVec3 whitepointYxy);


// Convert XYZ to the chromatic adapted aXYZ
CMLAPI void CMLconvertXYZtoChromaticAdaptedXYZ(  CMLVec3 aXYZ,
                                           const CMLVec3 XYZ,
                                          const CMLMat33 matrix);


// ///////////////////////////////////////////



// Fills the given array with 3 CMLFunctions denoting the x_, y_ and z_ spectral
// distribution functions of a desired observer. These functions must be
// deleted manually. If an invalid observer is given or if the observer is
// CML_OBSERVER_CUSTOM, the array will be filled with CML_NULL pointers.
CMLAPI void cmlCreateSpectralDistributionFunctions(
                                        CMLFunction* functions[3],
                                     CMLObserverType observer);


// Creates and returns a new spectrum with the given input parameters. The
// temperature parameter is expected in [Degree Kelvin] for the illumination
// types CML_ILLUMINATION_BLACKBODY and CML_ILLUMINATION_D_ILLUMINANT. For any
// other type, the temperature parameter is ignored. The returned CMLFunction
// must be deleted manually. Only types denoting built-in illuminations are
// valid (no custom illuminations). Invalid illumination types will return
// CML_NULL.
CMLAPI CMLFunction* cmlCreateIlluminationSpectrum(
                                    CMLIlluminationType illuminationtype,
                                    float               temperature);


// Returns the correlated color temperature in [Degree Kelvin] for a given
// whitepoint in Yuv. Currently, the Robertson method is implemented.
// Beware! This function expects Yuv, not Yxy!
CMLAPI float cmlComputeCorrelatedColorTemperature(
                                    const CMLVec3       whitepointYuv);


// The following three functions return information to predefined RGB color
// spaces. The CML_RGB_CUSTOM space is not valid. If an invalid colorspacetype
// is provided, the values will be uninitialized.

// Returns all three primaries of a predefined RGB colorspace. Note that
// the Y component of the three primaries will always be 1.
CMLAPI void cmlGetRGBSpacePrimaries(
                                  CMLRGBSpaceType      colorspacetype,
                                  CMLVec3               primaryRYxy,
                                  CMLVec3               primaryGYxy,
                                  CMLVec3               primaryBYxy);
// Returns the illumination type of a predefined RGB colorspace.
CMLAPI CMLIlluminationType cmlGetRGBSpaceIlluminationType(
                                  CMLRGBSpaceType      colorspacetype);
CMLAPI CMLResponseCurvePreset cmlGetRGBSpaceResponseCurvePreset
                                      (CMLRGBSpaceType colorspacetype);

// Computes the matrix for RGB -> XYZ conversions given the three primaries and
// the whitepoint as Yxy colors. Note that the Y component of the three
// primaries will be changed by this function call. Also note that you can
// choose to have a colorimetric instead of a radiometric computation by simply
// setting the Y component of the whitepoint to 1.
// Also note that in order to get the inverse transformation matrix, simply
// use the cmlMat33Inverse functin.
CMLAPI void CMLcomputeRGBtoXYZMatrix(
                                              CMLMat33  rgbtoxyzmatrix,
                                              CMLVec3   primaryRYxy,
                                              CMLVec3   primaryGYxy,
                                              CMLVec3   primaryBYxy,
                                        const CMLVec3   whitepointYxy);

// Returns the number of channels a specific color type uses. If an invalid
// color type is given, the returned value will be 0.
CMLAPI CMLuint32 cmlGetNumChannels( CMLColorType        colortype);


// Returns the minimal or maximal bounds for each channel of a specified color
// type. If an invalid color type is given, the returned values will be
// undefined.
CMLAPI void cmlGetMinBounds(float* buffer, CMLColorType colortype);
CMLAPI void cmlGetMaxBounds(float* buffer, CMLColorType colortype);


// The following functions return an ASCII string describing the desired value.
// Do not delete the returned pointers. If an invalid input parameter is given,
// the returned value will be invalid.
CMLAPI const char* cmlGetColorTypeString               (CMLColorType colortype);
CMLAPI const char* cmlGetObserverTypeString            (CMLObserverType observertype);
CMLAPI const char* cmlGetIlluminationTypeString        (CMLIlluminationType illuminationtype);
CMLAPI const char* cmlGetRGBColorspaceString           (CMLRGBSpaceType colorspacetype);
CMLAPI const char* cmlGetLabSpaceTypeString            (CMLLabSpaceType labspacetype);
CMLAPI const char* cmlGetRGBResponsePresetString  (CMLResponseCurvePreset preset);
CMLAPI const char* cmlGetFunctionTypeString       (CMLFunctionType functiontype);
CMLAPI const char* cmlGetGrayComputationTypeString     (CMLGrayComputationType computationtype);
CMLAPI const char* cmlGetCMYKTransformTypeString       (CMLCMYKTransformType transformtype);
CMLAPI const char* cmlGetChromaticAdaptationTypeString (CMLChromaticAdaptationType chromaticadaptationtype);


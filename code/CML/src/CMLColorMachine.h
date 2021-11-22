
// This file contains the API for the ColorMachine structure.
//
// Note that this API is explicitely made for engineers who know what they are
// doing. If you are looking for a simple entry into color transformations,
// see the BaseAPI or the ColorClasses.



// ///////////////////////////////////////////////
// State Machine
// ///////////////////////////////////////////////

// Returns a pointer to 4 Bytes denoting unsigned 8-bit-integers as follows:
// version[0]: Main Version number (technology changes)
// version[1]: Sub Version number (large features, API changes)
// version[2]: Subsub Version number (small features, new API)
// version[3]: Either 0 for release or 1 for debug version
CML_API void                  CMLgetVersion(CMLByte version[4]);

// Create and destroy ColorMachines with these functions:
CML_API CMLColorMachine*      CMLcreateColorMachine(void);
CML_API void                  CMLreleaseColorMachine(CMLColorMachine* cm);

// If you have multiple state changes to set, lock the recomputation, set all
// desired values and release the recomputation. Doing so, the ColorMachine
// will only perform all necessary recomputations once and only once.
CML_API void                  CMLlockRecomputation(CMLColorMachine* cm);
CML_API void                  CMLreleaseRecomputation(CMLColorMachine* cm);

// The integer mapping defines, how floats are mapped to integers.
// Additionally, integers can have lower and upper cutoffs. This means that
// the minimal float values are mapped to the lower cutoffs and the maximal
// float values are mapped to the upper cutoffs. You can define cutoffs for
// channels up to CML_MAX_NUMBER_OF_CHANNELS. Note that cutoffs may also be
// negative.
CML_API CMLIntegerMappingType CMLgetIntegerMappingType(const CMLColorMachine* cm);
CML_API void                  CMLsetIntegerMappingType(CMLColorMachine* cm, CMLIntegerMappingType type);
CML_API void                  CMLget8bitCutoffs(const CMLColorMachine* cm, CMLint32* min, CMLint32* max, CMLuint32 channel);
CML_API void                  CMLset8bitCutoffs(CMLColorMachine* cm, CMLint32 min, CMLint32 max, CMLuint32 channel);
CML_API void                  CMLget16bitCutoffs(const CMLColorMachine* cm, CMLint32* min, CMLint32* max, CMLuint32 channel);
CML_API void                  cmlSet16bitCutoffs(CMLColorMachine* cm, CMLint32 min, CMLint32 max, CMLuint32 channel);

// The radiometric computation flag defines if spectral data shall be converted
// without or with normalization to Y=1. Set CML_TRUE for radiometric and
// CML_FALSE for colorimetric. Default is colorimetric.
//CML_API CMLBool               CMLgetRadiometricComputation(CMLColorMachine* cm);
//CML_API void                  CMLsetRadiometricComputation(CMLColorMachine* cm, CMLBool radiometric);

// The observer defines if the 2 degree or the 10 degree model and what data
// set is used. Initial setting is 2 degrees of CIE recommendation.
CML_API const CMLObserver*    cmlGetObserver(const CMLColorMachine* cm);
CML_API CMLObserverType       CMLgetObserverType(const CMLColorMachine* cm);
CML_API void                  CMLsetObserverType(CMLColorMachine* cm, CMLObserverType newobserver);
CML_API void                  CMLgetSpecDistFunctions(const CMLColorMachine* cm, const CMLFunction* observer[3]);
//CML_API void                  CMLsetSpecDistFunctions(CMLColorMachine* cm, const CMLFunction* observer[3]);
CML_API void                  CMLgetSpectralXYZColor(const CMLColorMachine* cm, CMLVec3 xyz, float lambda);

// The illumination defines the current illumination assumed. This includes
// the whitepoint. Initial setting is the standard illumination of the
// standard RGB colorspace, which for sRGB is D65.
// Note that setting the RGB Colorspace will set the illumination implicitely
// by default.
// Note that the setIlluminationTemperature method will only take effect with
// the Blackbody and custom D illuminant. Otherwise, the input is ignored.
CML_API CMLIlluminationType   CMLgetIlluminationType(CMLColorMachine* cm);
CML_API void                  CMLsetIlluminationType(CMLColorMachine* cm, CMLIlluminationType illuminationtype);
CML_API float                 CMLgetIlluminationTemperature(const CMLColorMachine* cm);
CML_API void                  CMLsetIlluminationTemperature(CMLColorMachine* cm, float temp);
CML_API const CMLFunction*    CMLgetIlluminationSpectrum(const CMLColorMachine* cm);
CML_API void                  CMLsetIlluminationSpectrum(CMLColorMachine* cm, const CMLFunction* spectrum);
CML_API void                  CMLgetWhitePointYxy(const CMLColorMachine* cm, CMLVec3 whitepointYxy);
CML_API void                  CMLsetWhitePointYxy(CMLColorMachine* cm, const float* Yxy);

// These functions set the computation of the Lab space. Default is CIELAB.
// The functions setting K and ke will only take effect if the
// labspace is set to CML_LAB_ADAMS_CROMATIC_VALENCE. Otherwise, the input
// is ignored. When setting a custom response, the gamma parameter will only
// be used with gamma responses.
// Be aware that most Lab spaces (including CIELAB) are relative to a specific
// whitepoint which in CML is defined by the current illumination.
CML_API CMLLabColorSpaceType  CMLgetLabColorSpace(const CMLColorMachine* cm);
CML_API void                  CMLsetLabColorSpace(CMLColorMachine* cm, CMLLabColorSpaceType labspace);
CML_API void                  CMLgetAdamsChromaticityValenceParameters(CMLColorMachine* cm, float* K, float* ke);
CML_API void                  CMLsetAdamsChromaticityValenceParameters(CMLColorMachine* cm, float K, float ke);
CML_API CMLuint8              CMLgetLabLUTSize(const CMLColorMachine* cm);
CML_API void                  CMLsetLabLUTSize(CMLColorMachine* cm, CMLuint8 bits);
CML_API const CMLFunction*    CMLgetLtoLinearResponse(const CMLColorMachine* cm);
CML_API const CMLFunction*    CMLgetLineartoLResponse(const CMLColorMachine* cm);
CML_API const CMLResponseCurve* CMLgetResponseL  (CMLColorMachine* cm);
//CML_API CMLFunctionType       CMLgetLabResponseCurveFunctionType(const CMLColorMachine* cm);
CML_API void                  CMLsetResponseL(CMLColorMachine* cm, CMLResponseCurve* response);
//CML_API float                 CMLgetLabGamma(const CMLColorMachine* cm);

// The RGB colorspace defines, which CMLIlluminationType (including white point)
// and which r, g and b coordinates are used for conversions between XYZ and
// RGB.
// Initial setting is sRGB.
// After setting the colorspace using these methods, the setting will be
// stored and the illumination and conversion matrix will be set accordingly.
// Note that setting the primaries will ignore the Y coordinate but recompute
// the correct values automatically.
// When setting the response curve, gamma will only be used with gamma
// responses. If a value of 0 is used, gamma will be set close to the
// previous response curve. The setResponseRGB function will set the same
// response for R, G and B.
CML_API CMLRGBColorSpace      CMLgetRGBColorSpace(const CMLColorMachine* cm);
CML_API void                  CMLsetRGBColorSpace(CMLColorMachine* cm, CMLRGBColorSpace colorspacetype);
CML_API void                  CMLgetRGBPrimariesYxy(const CMLColorMachine* cm, CMLVec3 primaries[3]);
CML_API void                  CMLsetRGBPrimariesYxy(CMLColorMachine* cm, CMLVec3 primaries[3]);
//CML_API void                  CMLgetRGBtoLinearResponses(const CMLColorMachine* cm, const CMLFunction* responses[3]);
//CML_API void                  CMLgetLineartoRGBResponses(const CMLColorMachine* cm, const CMLFunction* responses[3]);
//CML_API void                  CMLgetRGBResponseTypes(const CMLColorMachine* cm, CMLResponseCurveType responsetypes[3]);
//CML_API void                  CMLgetRGBGammas(const CMLColorMachine* cm, float gammas[3]);
CML_API void                  CMLsetResponseRGB(CMLColorMachine* cm, CMLResponseCurve* response);
CML_API const CMLResponseCurve* CMLgetResponseR  (CMLColorMachine* cm);
CML_API const CMLResponseCurve* CMLgetResponseG  (CMLColorMachine* cm);
CML_API const CMLResponseCurve* CMLgetResponseB  (CMLColorMachine* cm);
CML_API void                  CMLsetResponseR  (CMLColorMachine* cm, CMLResponseCurve* response);
CML_API void                  CMLsetResponseG  (CMLColorMachine* cm, CMLResponseCurve* response);
CML_API void                  CMLsetResponseB  (CMLColorMachine* cm, CMLResponseCurve* response);
CML_API CMLuint8              CMLgetRGBLUTSize(const CMLColorMachine* cm);
CML_API void                  CMLsetRGBLUTSize(CMLColorMachine* cm, CMLuint8 bits);


// Transformation from RGB to CMYK can be achieved using different approaches
// like UCR, GCR or standard transform. Currently, only UCR and standard
// transform is implemented.
// Initial setting is standard transform.
CML_API CMLCMYKTransformType  CMLgetCMYKTransform(const CMLColorMachine* cm);
CML_API void                  CMLsetCMYKTransform(CMLColorMachine* cm, CMLCMYKTransformType transform);

// Transformation from any Color to Gray and vice versa can be achieved using
// different approaches. Initial setting is the computation from the
// L* value (CIELAB).
CML_API CMLGrayComputationType  CMLgetGrayComputationType(const CMLColorMachine* cm);
CML_API void                    CMLsetGrayComputationType(CMLColorMachine* cm, CMLGrayComputationType computation);



// ///////////////////////////////////////////////
// Color conversions
//
// Using ColorMachines, you can convert any color into any other with the
// following conversion functions. You can also get a function pointer to
// one of these conversion function using the CMLgetColorConverter function.
// ///////////////////////////////////////////////

CML_API CMLColorConverter     CMLgetColorConverter(CMLColorType outputsystem, CMLColorType inputsystem);

// Gray Conversions
CML_API void CMLGraytoGray  (const CMLColorMachine* cm, CMLOutput grayd , CMLInput grays , CMLSize count);
CML_API void CMLGraytoXYZ   (const CMLColorMachine* cm, CMLOutput XYZ   , CMLInput gray  , CMLSize count);
CML_API void CMLGraytoYuv   (const CMLColorMachine* cm, CMLOutput Yuv   , CMLInput gray  , CMLSize count);
CML_API void CMLGraytoYupvp (const CMLColorMachine* cm, CMLOutput Yupvp , CMLInput gray  , CMLSize count);
CML_API void CMLGraytoYxy   (const CMLColorMachine* cm, CMLOutput Yxy   , CMLInput gray  , CMLSize count);
CML_API void CMLGraytoLab   (const CMLColorMachine* cm, CMLOutput Lab   , CMLInput gray  , CMLSize count);
CML_API void CMLGraytoLch   (const CMLColorMachine* cm, CMLOutput Lch   , CMLInput gray  , CMLSize count);
CML_API void CMLGraytoLuv   (const CMLColorMachine* cm, CMLOutput Luv   , CMLInput gray  , CMLSize count);
CML_API void CMLGraytoRGB   (const CMLColorMachine* cm, CMLOutput RGB   , CMLInput gray  , CMLSize count);
CML_API void CMLGraytoYCbCr (const CMLColorMachine* cm, CMLOutput YCbCr , CMLInput gray  , CMLSize count);
CML_API void CMLGraytoHSV   (const CMLColorMachine* cm, CMLOutput HSV   , CMLInput gray  , CMLSize count);
CML_API void CMLGraytoHSL   (const CMLColorMachine* cm, CMLOutput HSL   , CMLInput gray  , CMLSize count);
CML_API void CMLGraytoCMYK  (const CMLColorMachine* cm, CMLOutput CMYK  , CMLInput gray  , CMLSize count);

// XYZ Conversions
CML_API void CMLXYZtoGray   (const CMLColorMachine* cm, CMLOutput gray  , CMLInput XYZ   , CMLSize count);
CML_API void CMLXYZtoXYZ    (const CMLColorMachine* cm, CMLOutput XYZd  , CMLInput XYZs  , CMLSize count);
CML_API void CMLXYZtoYuv    (const CMLColorMachine* cm, CMLOutput Yuv   , CMLInput XYZ   , CMLSize count);
CML_API void CMLXYZtoYupvp  (const CMLColorMachine* cm, CMLOutput Yupvp , CMLInput XYZ   , CMLSize count);
CML_API void CMLXYZtoYxy    (const CMLColorMachine* cm, CMLOutput Yxy   , CMLInput XYZ   , CMLSize count);
CML_API void CMLXYZtoLab    (const CMLColorMachine* cm, CMLOutput Lab   , CMLInput XYZ   , CMLSize count);
CML_API void CMLXYZtoLch    (const CMLColorMachine* cm, CMLOutput Lch   , CMLInput XYZ   , CMLSize count);
CML_API void CMLXYZtoLuv    (const CMLColorMachine* cm, CMLOutput Luv   , CMLInput XYZ   , CMLSize count);
CML_API void CMLXYZtoRGB    (const CMLColorMachine* cm, CMLOutput RGB   , CMLInput XYZ   , CMLSize count);
CML_API void CMLXYZtoYCbCr  (const CMLColorMachine* cm, CMLOutput YCbCr , CMLInput XYZ   , CMLSize count);
CML_API void CMLXYZtoHSV    (const CMLColorMachine* cm, CMLOutput HSV   , CMLInput XYZ   , CMLSize count);
CML_API void CMLXYZtoHSL    (const CMLColorMachine* cm, CMLOutput HSL   , CMLInput XYZ   , CMLSize count);
CML_API void CMLXYZtoCMYK   (const CMLColorMachine* cm, CMLOutput CMYK  , CMLInput XYZ   , CMLSize count);

// Yuv Conversions
CML_API void CMLYuvtoGray   (const CMLColorMachine* cm, CMLOutput gray  , CMLInput Yuv   , CMLSize count);
CML_API void CMLYuvtoXYZ    (const CMLColorMachine* cm, CMLOutput XYZ   , CMLInput Yuv   , CMLSize count);
CML_API void CMLYuvtoYuv    (const CMLColorMachine* cm, CMLOutput Yuvd  , CMLInput Yuvs  , CMLSize count);
CML_API void CMLYuvtoYupvp  (const CMLColorMachine* cm, CMLOutput Yupvp , CMLInput Yuv   , CMLSize count);
CML_API void CMLYuvtoYxy    (const CMLColorMachine* cm, CMLOutput Yxy   , CMLInput Yuv   , CMLSize count);
CML_API void CMLYuvtoLab    (const CMLColorMachine* cm, CMLOutput Lab   , CMLInput Yuv   , CMLSize count);
CML_API void CMLYuvtoLch    (const CMLColorMachine* cm, CMLOutput Lch   , CMLInput Yuv   , CMLSize count);
CML_API void CMLYuvtoLuv    (const CMLColorMachine* cm, CMLOutput Luv   , CMLInput Yuv   , CMLSize count);
CML_API void CMLYuvtoRGB    (const CMLColorMachine* cm, CMLOutput RGB   , CMLInput Yuv   , CMLSize count);
CML_API void CMLYuvtoYCbCr  (const CMLColorMachine* cm, CMLOutput YCbCr , CMLInput Yuv   , CMLSize count);
CML_API void CMLYuvtoHSV    (const CMLColorMachine* cm, CMLOutput HSV   , CMLInput Yuv   , CMLSize count);
CML_API void CMLYuvtoHSL    (const CMLColorMachine* cm, CMLOutput HSL   , CMLInput Yuv   , CMLSize count);
CML_API void CMLYuvtoCMYK   (const CMLColorMachine* cm, CMLOutput CMYK  , CMLInput Yuv   , CMLSize count);

// Yupvp Conversions
CML_API void CMLYupvptoGray (const CMLColorMachine* cm, CMLOutput gray  , CMLInput Yupvp , CMLSize count);
CML_API void CMLYupvptoXYZ  (const CMLColorMachine* cm, CMLOutput XYZ   , CMLInput Yupvp , CMLSize count);
CML_API void CMLYupvptoYuv  (const CMLColorMachine* cm, CMLOutput Yuv   , CMLInput Yupvp , CMLSize count);
CML_API void CMLYupvptoYupvp(const CMLColorMachine* cm, CMLOutput Yupvpd,CMLInput Yupvps , CMLSize count);
CML_API void CMLYupvptoYxy  (const CMLColorMachine* cm, CMLOutput Yxy   , CMLInput Yupvp , CMLSize count);
CML_API void CMLYupvptoLab  (const CMLColorMachine* cm, CMLOutput Lab   , CMLInput Yupvp , CMLSize count);
CML_API void CMLYupvptoLch  (const CMLColorMachine* cm, CMLOutput Lch   , CMLInput Yupvp , CMLSize count);
CML_API void CMLYupvptoLuv  (const CMLColorMachine* cm, CMLOutput Luv   , CMLInput Yupvp , CMLSize count);
CML_API void CMLYupvptoRGB  (const CMLColorMachine* cm, CMLOutput RGB   , CMLInput Yupvp , CMLSize count);
CML_API void CMLYupvptoYCbCr(const CMLColorMachine* cm, CMLOutput YCbCr , CMLInput Yupvp , CMLSize count);
CML_API void CMLYupvptoHSV  (const CMLColorMachine* cm, CMLOutput HSV   , CMLInput Yupvp , CMLSize count);
CML_API void CMLYupvptoHSL  (const CMLColorMachine* cm, CMLOutput HSL   , CMLInput Yupvp , CMLSize count);
CML_API void CMLYupvptoCMYK (const CMLColorMachine* cm, CMLOutput CMYK  , CMLInput Yupvp , CMLSize count);

// Yxy Conversions
CML_API void CMLYxytoGray   (const CMLColorMachine* cm, CMLOutput gray  , CMLInput Yxy   , CMLSize count);
CML_API void CMLYxytoXYZ    (const CMLColorMachine* cm, CMLOutput XYZ   , CMLInput Yxy   , CMLSize count);
CML_API void CMLYxytoYuv    (const CMLColorMachine* cm, CMLOutput Yuv   , CMLInput Yxy   , CMLSize count);
CML_API void CMLYxytoYupvp  (const CMLColorMachine* cm, CMLOutput Yupvp , CMLInput Yxy   , CMLSize count);
CML_API void CMLYxytoYxy    (const CMLColorMachine* cm, CMLOutput Yxyd  , CMLInput Yxys  , CMLSize count);
CML_API void CMLYxytoLab    (const CMLColorMachine* cm, CMLOutput Lab   , CMLInput Yxy   , CMLSize count);
CML_API void CMLYxytoLch    (const CMLColorMachine* cm, CMLOutput Lch   , CMLInput Yxy   , CMLSize count);
CML_API void CMLYxytoLuv    (const CMLColorMachine* cm, CMLOutput Luv   , CMLInput Yxy   , CMLSize count);
CML_API void CMLYxytoRGB    (const CMLColorMachine* cm, CMLOutput RGB   , CMLInput Yxy   , CMLSize count);
CML_API void CMLYxytoYCbCr  (const CMLColorMachine* cm, CMLOutput YCbCr , CMLInput Yxy   , CMLSize count);
CML_API void CMLYxytoHSV    (const CMLColorMachine* cm, CMLOutput HSV   , CMLInput Yxy   , CMLSize count);
CML_API void CMLYxytoHSL    (const CMLColorMachine* cm, CMLOutput HSL   , CMLInput Yxy   , CMLSize count);
CML_API void CMLYxytoCMYK   (const CMLColorMachine* cm, CMLOutput CMYK  , CMLInput Yxy   , CMLSize count);

// Lab Conversions
CML_API void CMLLabtoGray   (const CMLColorMachine* cm, CMLOutput gray  , CMLInput Lab   , CMLSize count);
CML_API void CMLLabtoXYZ    (const CMLColorMachine* cm, CMLOutput XYZ   , CMLInput Lab   , CMLSize count);
CML_API void CMLLabtoYuv    (const CMLColorMachine* cm, CMLOutput Yuv   , CMLInput Lab   , CMLSize count);
CML_API void CMLLabtoYupvp  (const CMLColorMachine* cm, CMLOutput Yupvp , CMLInput Lab   , CMLSize count);
CML_API void CMLLabtoYxy    (const CMLColorMachine* cm, CMLOutput Yxy   , CMLInput Lab   , CMLSize count);
CML_API void CMLLabtoLab    (const CMLColorMachine* cm, CMLOutput Labd  , CMLInput Labs  , CMLSize count);
CML_API void CMLLabtoLch    (const CMLColorMachine* cm, CMLOutput Lch   , CMLInput Lab   , CMLSize count);
CML_API void CMLLabtoLuv    (const CMLColorMachine* cm, CMLOutput Luv   , CMLInput Lab   , CMLSize count);
CML_API void CMLLabtoRGB    (const CMLColorMachine* cm, CMLOutput RGB   , CMLInput Lab   , CMLSize count);
CML_API void CMLLabtoYCbCr  (const CMLColorMachine* cm, CMLOutput YCbCr , CMLInput Lab   , CMLSize count);
CML_API void CMLLabtoHSV    (const CMLColorMachine* cm, CMLOutput HSV   , CMLInput Lab   , CMLSize count);
CML_API void CMLLabtoHSL    (const CMLColorMachine* cm, CMLOutput HSL   , CMLInput Lab   , CMLSize count);
CML_API void CMLLabtoCMYK   (const CMLColorMachine* cm, CMLOutput CMYK  , CMLInput Lab   , CMLSize count);

// Lch Conversions
CML_API void CMLLchtoGray   (const CMLColorMachine* cm, CMLOutput gray  , CMLInput Lch   , CMLSize count);
CML_API void CMLLchtoXYZ    (const CMLColorMachine* cm, CMLOutput XYZ   , CMLInput Lch   , CMLSize count);
CML_API void CMLLchtoYuv    (const CMLColorMachine* cm, CMLOutput Yuv   , CMLInput Lch   , CMLSize count);
CML_API void CMLLchtoYupvp  (const CMLColorMachine* cm, CMLOutput Yupvp , CMLInput Lch   , CMLSize count);
CML_API void CMLLchtoYxy    (const CMLColorMachine* cm, CMLOutput Yxy   , CMLInput Lch   , CMLSize count);
CML_API void CMLLchtoLab    (const CMLColorMachine* cm, CMLOutput Lab   , CMLInput Lch   , CMLSize count);
CML_API void CMLLchtoLch    (const CMLColorMachine* cm, CMLOutput Lchd  , CMLInput Lchs  , CMLSize count);
CML_API void CMLLchtoLuv    (const CMLColorMachine* cm, CMLOutput Luv   , CMLInput Lch   , CMLSize count);
CML_API void CMLLchtoRGB    (const CMLColorMachine* cm, CMLOutput RGB   , CMLInput Lch   , CMLSize count);
CML_API void CMLLchtoYCbCr  (const CMLColorMachine* cm, CMLOutput Yuv   , CMLInput Lch   , CMLSize count);
CML_API void CMLLchtoHSV    (const CMLColorMachine* cm, CMLOutput HSV   , CMLInput Lch   , CMLSize count);
CML_API void CMLLchtoHSL    (const CMLColorMachine* cm, CMLOutput HSL   , CMLInput Lch   , CMLSize count);
CML_API void CMLLchtoCMYK   (const CMLColorMachine* cm, CMLOutput CMYK  , CMLInput Lch   , CMLSize count);

// Luv Conversions
CML_API void CMLLuvtoGray   (const CMLColorMachine* cm, CMLOutput gray  , CMLInput Luv   , CMLSize count);
CML_API void CMLLuvtoXYZ    (const CMLColorMachine* cm, CMLOutput XYZ   , CMLInput Luv   , CMLSize count);
CML_API void CMLLuvtoYuv    (const CMLColorMachine* cm, CMLOutput Yuv   , CMLInput Luv   , CMLSize count);
CML_API void CMLLuvtoYupvp  (const CMLColorMachine* cm, CMLOutput Yupvp , CMLInput Luv   , CMLSize count);
CML_API void CMLLuvtoYxy    (const CMLColorMachine* cm, CMLOutput Yxy   , CMLInput Luv   , CMLSize count);
CML_API void CMLLuvtoLab    (const CMLColorMachine* cm, CMLOutput Lab   , CMLInput Luv   , CMLSize count);
CML_API void CMLLuvtoLch    (const CMLColorMachine* cm, CMLOutput Lch   , CMLInput Luv   , CMLSize count);
CML_API void CMLLuvtoLuv    (const CMLColorMachine* cm, CMLOutput Luvd  , CMLInput Luvs  , CMLSize count);
CML_API void CMLLuvtoRGB    (const CMLColorMachine* cm, CMLOutput RGB   , CMLInput Luv   , CMLSize count);
CML_API void CMLLuvtoYCbCr  (const CMLColorMachine* cm, CMLOutput YCbCr , CMLInput Luv   , CMLSize count);
CML_API void CMLLuvtoHSV    (const CMLColorMachine* cm, CMLOutput HSV   , CMLInput Luv   , CMLSize count);
CML_API void CMLLuvtoHSL    (const CMLColorMachine* cm, CMLOutput HSL   , CMLInput Luv   , CMLSize count);
CML_API void CMLLuvtoCMYK   (const CMLColorMachine* cm, CMLOutput CMYK  , CMLInput Luv   , CMLSize count);

// RGB Conversions
CML_API void CMLRGBtoGray   (const CMLColorMachine* cm, CMLOutput gray  , CMLInput RGB   , CMLSize count);
CML_API void CMLRGBtoXYZ    (const CMLColorMachine* cm, CMLOutput XYZ   , CMLInput RGB   , CMLSize count);
CML_API void CMLRGBtoYuv    (const CMLColorMachine* cm, CMLOutput Yuv   , CMLInput RGB   , CMLSize count);
CML_API void CMLRGBtoYupvp  (const CMLColorMachine* cm, CMLOutput Yupvp , CMLInput RGB   , CMLSize count);
CML_API void CMLRGBtoYxy    (const CMLColorMachine* cm, CMLOutput Yxy   , CMLInput RGB   , CMLSize count);
CML_API void CMLRGBtoLab    (const CMLColorMachine* cm, CMLOutput Lab   , CMLInput RGB   , CMLSize count);
CML_API void CMLRGBtoLch    (const CMLColorMachine* cm, CMLOutput Lch   , CMLInput RGB   , CMLSize count);
CML_API void CMLRGBtoLuv    (const CMLColorMachine* cm, CMLOutput Luv   , CMLInput RGB   , CMLSize count);
CML_API void CMLRGBtoRGB    (const CMLColorMachine* cm, CMLOutput RGBd  , CMLInput RGBs  , CMLSize count);
CML_API void CMLRGBtoYCbCr  (const CMLColorMachine* cm, CMLOutput YCbCr , CMLInput RGB   , CMLSize count);
CML_API void CMLRGBtoHSV    (const CMLColorMachine* cm, CMLOutput HSV   , CMLInput RGB   , CMLSize count);
CML_API void CMLRGBtoHSL    (const CMLColorMachine* cm, CMLOutput HSL   , CMLInput RGB   , CMLSize count);
CML_API void CMLRGBtoCMYK   (const CMLColorMachine* cm, CMLOutput CMYK  , CMLInput RGB   , CMLSize count);

// YCbCr Conversions
CML_API void CMLYCbCrtoGray (const CMLColorMachine* cm, CMLOutput gray  , CMLInput YCbCr , CMLSize count);
CML_API void CMLYCbCrtoXYZ  (const CMLColorMachine* cm, CMLOutput XYZ   , CMLInput YCbCr , CMLSize count);
CML_API void CMLYCbCrtoYuv  (const CMLColorMachine* cm, CMLOutput Yuv   , CMLInput YCbCr , CMLSize count);
CML_API void CMLYCbCrtoYupvp(const CMLColorMachine* cm, CMLOutput Yupvp , CMLInput YCbCr , CMLSize count);
CML_API void CMLYCbCrtoYxy  (const CMLColorMachine* cm, CMLOutput Yxy   , CMLInput YCbCr , CMLSize count);
CML_API void CMLYCbCrtoLab  (const CMLColorMachine* cm, CMLOutput Lab   , CMLInput YCbCr , CMLSize count);
CML_API void CMLYCbCrtoLch  (const CMLColorMachine* cm, CMLOutput Lch   , CMLInput YCbCr , CMLSize count);
CML_API void CMLYCbCrtoLuv  (const CMLColorMachine* cm, CMLOutput Luv   , CMLInput YCbCr , CMLSize count);
CML_API void CMLYCbCrtoRGB  (const CMLColorMachine* cm, CMLOutput RGB   , CMLInput YCbCr , CMLSize count);
CML_API void CMLYCbCrtoYCbCr(const CMLColorMachine* cm, CMLOutput YCbCrd, CMLInput YCbCrs, CMLSize count);
CML_API void CMLYCbCrtoHSV  (const CMLColorMachine* cm, CMLOutput HSV   , CMLInput YCbCr , CMLSize count);
CML_API void CMLYCbCrtoHSL  (const CMLColorMachine* cm, CMLOutput HSL   , CMLInput YCbCr , CMLSize count);
CML_API void CMLYCbCrtoCMYK (const CMLColorMachine* cm, CMLOutput CMYK  , CMLInput YCbCr , CMLSize count);

// HSV Conversions
CML_API void CMLHSVtoGray   (const CMLColorMachine* cm, CMLOutput gray  , CMLInput HSV   , CMLSize count);
CML_API void CMLHSVtoXYZ    (const CMLColorMachine* cm, CMLOutput XYZ   , CMLInput HSV   , CMLSize count);
CML_API void CMLHSVtoYuv    (const CMLColorMachine* cm, CMLOutput Yuv   , CMLInput HSV   , CMLSize count);
CML_API void CMLHSVtoYupvp  (const CMLColorMachine* cm, CMLOutput Yupvp , CMLInput HSV   , CMLSize count);
CML_API void CMLHSVtoYxy    (const CMLColorMachine* cm, CMLOutput Yxy   , CMLInput HSV   , CMLSize count);
CML_API void CMLHSVtoLab    (const CMLColorMachine* cm, CMLOutput Lab   , CMLInput HSV   , CMLSize count);
CML_API void CMLHSVtoLch    (const CMLColorMachine* cm, CMLOutput Lch   , CMLInput HSV   , CMLSize count);
CML_API void CMLHSVtoLuv    (const CMLColorMachine* cm, CMLOutput Luv   , CMLInput HSV   , CMLSize count);
CML_API void CMLHSVtoRGB    (const CMLColorMachine* cm, CMLOutput RGB   , CMLInput HSV   , CMLSize count);
CML_API void CMLHSVtoYCbCr  (const CMLColorMachine* cm, CMLOutput YCbCr , CMLInput HSV   , CMLSize count);
CML_API void CMLHSVtoHSV    (const CMLColorMachine* cm, CMLOutput HSVd  , CMLInput HSVs  , CMLSize count);
CML_API void CMLHSVtoHSL    (const CMLColorMachine* cm, CMLOutput HSL   , CMLInput HSV   , CMLSize count);
CML_API void CMLHSVtoCMYK   (const CMLColorMachine* cm, CMLOutput CMYK  , CMLInput HSV   , CMLSize count);

// HSL Conversions
CML_API void CMLHSLtoGray   (const CMLColorMachine* cm, CMLOutput gray  , CMLInput HSL   , CMLSize count);
CML_API void CMLHSLtoXYZ    (const CMLColorMachine* cm, CMLOutput XYZ   , CMLInput HSL   , CMLSize count);
CML_API void CMLHSLtoYuv    (const CMLColorMachine* cm, CMLOutput Yuv   , CMLInput HSL   , CMLSize count);
CML_API void CMLHSLtoYupvp  (const CMLColorMachine* cm, CMLOutput Yupvp , CMLInput HSL   , CMLSize count);
CML_API void CMLHSLtoYxy    (const CMLColorMachine* cm, CMLOutput Yxy   , CMLInput HSL   , CMLSize count);
CML_API void CMLHSLtoLab    (const CMLColorMachine* cm, CMLOutput Lab   , CMLInput HSL   , CMLSize count);
CML_API void CMLHSLtoLch    (const CMLColorMachine* cm, CMLOutput Lch   , CMLInput HSL   , CMLSize count);
CML_API void CMLHSLtoLuv    (const CMLColorMachine* cm, CMLOutput Luv   , CMLInput HSL   , CMLSize count);
CML_API void CMLHSLtoRGB    (const CMLColorMachine* cm, CMLOutput RGB   , CMLInput HSL   , CMLSize count);
CML_API void CMLHSLtoYCbCr  (const CMLColorMachine* cm, CMLOutput YCbCr , CMLInput HSL   , CMLSize count);
CML_API void CMLHSLtoHSV    (const CMLColorMachine* cm, CMLOutput HSV   , CMLInput HSL   , CMLSize count);
CML_API void CMLHSLtoHSL    (const CMLColorMachine* cm, CMLOutput HSLd  , CMLInput HSLs  , CMLSize count);
CML_API void CMLHSLtoCMYK   (const CMLColorMachine* cm, CMLOutput CMYK  , CMLInput HSL   , CMLSize count);

// CMYK Conversions
CML_API void CMLCMYKtoGray  (const CMLColorMachine* cm, CMLOutput gray  , CMLInput CMYK  , CMLSize count);
CML_API void CMLCMYKtoXYZ   (const CMLColorMachine* cm, CMLOutput XYZ   , CMLInput CMYK  , CMLSize count);
CML_API void CMLCMYKtoYuv   (const CMLColorMachine* cm, CMLOutput Yuv   , CMLInput CMYK  , CMLSize count);
CML_API void CMLCMYKtoYupvp (const CMLColorMachine* cm, CMLOutput Yupvp , CMLInput CMYK  , CMLSize count);
CML_API void CMLCMYKtoYxy   (const CMLColorMachine* cm, CMLOutput Yxy   , CMLInput CMYK  , CMLSize count);
CML_API void CMLCMYKtoLab   (const CMLColorMachine* cm, CMLOutput Lab   , CMLInput CMYK  , CMLSize count);
CML_API void CMLCMYKtoLch   (const CMLColorMachine* cm, CMLOutput Lch   , CMLInput CMYK  , CMLSize count);
CML_API void CMLCMYKtoLuv   (const CMLColorMachine* cm, CMLOutput Luv   , CMLInput CMYK  , CMLSize count);
CML_API void CMLCMYKtoRGB   (const CMLColorMachine* cm, CMLOutput RGB   , CMLInput CMYK  , CMLSize count);
CML_API void CMLCMYKtoYCbCr (const CMLColorMachine* cm, CMLOutput YCbCr , CMLInput CMYK  , CMLSize count);
CML_API void CMLCMYKtoHSV   (const CMLColorMachine* cm, CMLOutput HSV   , CMLInput CMYK  , CMLSize count);
CML_API void CMLCMYKtoHSL   (const CMLColorMachine* cm, CMLOutput HSL   , CMLInput CMYK  , CMLSize count);
CML_API void CMLCMYKtoCMYK  (const CMLColorMachine* cm, CMLOutput CMYKd , CMLInput CMYKs , CMLSize count);

// Spectrum Illumination Conversions
CML_API void CMLSpectrumIlluminationtoGray  (const CMLColorMachine* cm, CMLOutput gray  , CMLInput specill, CMLSize count);
CML_API void CMLSpectrumIlluminationtoXYZ   (const CMLColorMachine* cm, CMLOutput XYZ   , CMLInput specill, CMLSize count);
CML_API void CMLSpectrumIlluminationtoYuv   (const CMLColorMachine* cm, CMLOutput Yuv   , CMLInput specill, CMLSize count);
CML_API void CMLSpectrumIlluminationtoYupvp (const CMLColorMachine* cm, CMLOutput Yupvp , CMLInput specill, CMLSize count);
CML_API void CMLSpectrumIlluminationtoYxy   (const CMLColorMachine* cm, CMLOutput Yxy   , CMLInput specill, CMLSize count);
CML_API void CMLSpectrumIlluminationtoLab   (const CMLColorMachine* cm, CMLOutput Lab   , CMLInput specill, CMLSize count);
CML_API void CMLSpectrumIlluminationtoLch   (const CMLColorMachine* cm, CMLOutput Lch   , CMLInput specill, CMLSize count);
CML_API void CMLSpectrumIlluminationtoLuv   (const CMLColorMachine* cm, CMLOutput Luv   , CMLInput specill, CMLSize count);
CML_API void CMLSpectrumIlluminationtoRGB   (const CMLColorMachine* cm, CMLOutput RGB   , CMLInput specill, CMLSize count);
CML_API void CMLSpectrumIlluminationtoYCbCr (const CMLColorMachine* cm, CMLOutput YCbCr , CMLInput specill, CMLSize count);
CML_API void CMLSpectrumIlluminationtoHSV   (const CMLColorMachine* cm, CMLOutput HSV   , CMLInput specill, CMLSize count);
CML_API void CMLSpectrumIlluminationtoHSL   (const CMLColorMachine* cm, CMLOutput HSL   , CMLInput specill, CMLSize count);
CML_API void CMLSpectrumIlluminationtoCMYK  (const CMLColorMachine* cm, CMLOutput CMYK  , CMLInput specill, CMLSize count);

// Spectrum Remission Conversions
CML_API void CMLSpectrumRemissiontoGray  (const CMLColorMachine* cm, CMLOutput gray  , CMLInput specrem, CMLSize count);
CML_API void CMLSpectrumRemissiontoXYZ   (const CMLColorMachine* cm, CMLOutput XYZ   , CMLInput specrem, CMLSize count);
CML_API void CMLSpectrumRemissiontoYuv   (const CMLColorMachine* cm, CMLOutput Yuv   , CMLInput specrem, CMLSize count);
CML_API void CMLSpectrumRemissiontoYupvp (const CMLColorMachine* cm, CMLOutput Yupvp , CMLInput specrem, CMLSize count);
CML_API void CMLSpectrumRemissiontoYxy   (const CMLColorMachine* cm, CMLOutput Yxy   , CMLInput specrem, CMLSize count);
CML_API void CMLSpectrumRemissiontoLab   (const CMLColorMachine* cm, CMLOutput Lab   , CMLInput specrem, CMLSize count);
CML_API void CMLSpectrumRemissiontoLch   (const CMLColorMachine* cm, CMLOutput Lch   , CMLInput specrem, CMLSize count);
CML_API void CMLSpectrumRemissiontoLuv   (const CMLColorMachine* cm, CMLOutput Luv   , CMLInput specrem, CMLSize count);
CML_API void CMLSpectrumRemissiontoRGB   (const CMLColorMachine* cm, CMLOutput RGB   , CMLInput specrem, CMLSize count);
CML_API void CMLSpectrumRemissiontoYCbCr (const CMLColorMachine* cm, CMLOutput YCbCr , CMLInput specrem, CMLSize count);
CML_API void CMLSpectrumRemissiontoHSV   (const CMLColorMachine* cm, CMLOutput HSV   , CMLInput specrem, CMLSize count);
CML_API void CMLSpectrumRemissiontoHSL   (const CMLColorMachine* cm, CMLOutput HSL   , CMLInput specrem, CMLSize count);
CML_API void CMLSpectrumRemissiontoCMYK  (const CMLColorMachine* cm, CMLOutput CMYK  , CMLInput specrem, CMLSize count);



// ////////////////////////////
// Input & Output Conversions
// ////////////////////////////

// Often times, you need to import or export values from files or memory blocks.
// The data may be in a different encoding than used in CML. Therefore you can
// use the following functions to convert 8-Bit and 16-Bit data to the requred
// float data. These functions will adapt the data to the cutoffs and the
// integer mappings of the given machine.

// 8-bit Input Conversions
CML_API void CMLGrayfrom8bitInput (const CMLColorMachine* cm, CMLOutput gray  , CMLInput input, CMLSize count);
CML_API void CMLXYZfrom8bitInput  (const CMLColorMachine* cm, CMLOutput XYZ   , CMLInput input, CMLSize count);
CML_API void CMLYxyfrom8bitInput  (const CMLColorMachine* cm, CMLOutput Yxy   , CMLInput input, CMLSize count);
CML_API void CMLYuvfrom8bitInput  (const CMLColorMachine* cm, CMLOutput Yuv   , CMLInput input, CMLSize count);
CML_API void CMLYupvpfrom8bitInput(const CMLColorMachine* cm, CMLOutput Yupvp , CMLInput input, CMLSize count);
CML_API void CMLLabfrom8bitInput  (const CMLColorMachine* cm, CMLOutput Lab   , CMLInput input, CMLSize count);
CML_API void CMLLchfrom8bitInput  (const CMLColorMachine* cm, CMLOutput Lch   , CMLInput input, CMLSize count);
CML_API void CMLLuvfrom8bitInput  (const CMLColorMachine* cm, CMLOutput Luv   , CMLInput input, CMLSize count);
CML_API void CMLRGBfrom8bitInput  (const CMLColorMachine* cm, CMLOutput RGB   , CMLInput input, CMLSize count);
CML_API void CMLYCbCrfrom8bitInput(const CMLColorMachine* cm, CMLOutput YCbCr , CMLInput input, CMLSize count);
CML_API void CMLHSVfrom8bitInput  (const CMLColorMachine* cm, CMLOutput HSV   , CMLInput input, CMLSize count);
CML_API void CMLHSLfrom8bitInput  (const CMLColorMachine* cm, CMLOutput HSL   , CMLInput input, CMLSize count);
CML_API void CMLCMYKfrom8bitInput (const CMLColorMachine* cm, CMLOutput CMYK  , CMLInput input, CMLSize count);

// 16-bit Input Conversions
CML_API void CMLGrayfrom16bitInput  (const CMLColorMachine* cm, CMLOutput gray  , CMLInput input, CMLSize count);
CML_API void CMLXYZfrom16bitInput   (const CMLColorMachine* cm, CMLOutput XYZ   , CMLInput input, CMLSize count);
CML_API void CMLYxyfrom16bitInput   (const CMLColorMachine* cm, CMLOutput Yxy   , CMLInput input, CMLSize count);
CML_API void CMLYuvfrom16bitInput   (const CMLColorMachine* cm, CMLOutput Yuv   , CMLInput input, CMLSize count);
CML_API void CMLYupvpfrom16bitInput (const CMLColorMachine* cm, CMLOutput Yupvp , CMLInput input, CMLSize count);
CML_API void CMLLabfrom16bitInput   (const CMLColorMachine* cm, CMLOutput Lab   , CMLInput input, CMLSize count);
CML_API void CMLLchfrom16bitInput   (const CMLColorMachine* cm, CMLOutput Lch   , CMLInput input, CMLSize count);
CML_API void CMLLuvfrom16bitInput   (const CMLColorMachine* cm, CMLOutput Luv   , CMLInput input, CMLSize count);
CML_API void CMLRGBfrom16bitInput   (const CMLColorMachine* cm, CMLOutput RGB   , CMLInput input, CMLSize count);
CML_API void CMLYCbCrfrom16bitInput (const CMLColorMachine* cm, CMLOutput YCbCr , CMLInput input, CMLSize count);
CML_API void CMLHSVfrom16bitInput   (const CMLColorMachine* cm, CMLOutput HSV   , CMLInput input, CMLSize count);
CML_API void CMLHSLfrom16bitInput   (const CMLColorMachine* cm, CMLOutput HSL   , CMLInput input, CMLSize count);
CML_API void CMLCMYKfrom16bitInput  (const CMLColorMachine* cm, CMLOutput CMYK  , CMLInput input, CMLSize count);

// 8-bit Output Conversions
CML_API void CMLGrayto8bitOutput  (const CMLColorMachine* cm, CMLOutput output, CMLInput gray , CMLSize count);
CML_API void CMLXYZto8bitOutput   (const CMLColorMachine* cm, CMLOutput output, CMLInput XYZ  , CMLSize count);
CML_API void CMLYxyto8bitOutput   (const CMLColorMachine* cm, CMLOutput output, CMLInput Yxy  , CMLSize count);
CML_API void CMLYuvto8bitOutput   (const CMLColorMachine* cm, CMLOutput output, CMLInput Yuv  , CMLSize count);
CML_API void CMLYupvpto8bitOutput (const CMLColorMachine* cm, CMLOutput output, CMLInput Yupvp, CMLSize count);
CML_API void CMLLabto8bitOutput   (const CMLColorMachine* cm, CMLOutput output, CMLInput Lab  , CMLSize count);
CML_API void CMLLchto8bitOutput   (const CMLColorMachine* cm, CMLOutput output, CMLInput Lch  , CMLSize count);
CML_API void CMLLuvto8bitOutput   (const CMLColorMachine* cm, CMLOutput output, CMLInput Luv  , CMLSize count);
CML_API void CMLRGBto8bitOutput   (const CMLColorMachine* cm, CMLOutput output, CMLInput RGB  , CMLSize count);
CML_API void CMLYCbCrto8bitOutput (const CMLColorMachine* cm, CMLOutput output, CMLInput YCbCr, CMLSize count);
CML_API void CMLHSVto8bitOutput   (const CMLColorMachine* cm, CMLOutput output, CMLInput HSV  , CMLSize count);
CML_API void CMLHSLto8bitOutput   (const CMLColorMachine* cm, CMLOutput output, CMLInput HSL  , CMLSize count);
CML_API void CMLCMYKto8bitOutput  (const CMLColorMachine* cm, CMLOutput output, CMLInput CMYK , CMLSize count);

// 16-bit Output Conversions
CML_API void CMLGrayto16bitOutput (const CMLColorMachine* cm, CMLOutput output, CMLInput gray , CMLSize count);
CML_API void CMLXYZto16bitOutput  (const CMLColorMachine* cm, CMLOutput output, CMLInput XYZ  , CMLSize count);
CML_API void CMLYxyto16bitOutput  (const CMLColorMachine* cm, CMLOutput output, CMLInput Yxy  , CMLSize count);
CML_API void CMLYuvto16bitOutput  (const CMLColorMachine* cm, CMLOutput output, CMLInput Yuv  , CMLSize count);
CML_API void CMLYupvpto16bitOutput(const CMLColorMachine* cm, CMLOutput output, CMLInput Yupvp, CMLSize count);
CML_API void CMLLabto16bitOutput  (const CMLColorMachine* cm, CMLOutput output, CMLInput Lab  , CMLSize count);
CML_API void CMLLchto16bitOutput  (const CMLColorMachine* cm, CMLOutput output, CMLInput Lch  , CMLSize count);
CML_API void CMLLuvto16bitOutput  (const CMLColorMachine* cm, CMLOutput output, CMLInput Luv  , CMLSize count);
CML_API void CMLRGBto16bitOutput  (const CMLColorMachine* cm, CMLOutput output, CMLInput RGB  , CMLSize count);
CML_API void CMLYCbCrto16bitOutput(const CMLColorMachine* cm, CMLOutput output, CMLInput YCbCr, CMLSize count);
CML_API void CMLHSVto16bitOutput  (const CMLColorMachine* cm, CMLOutput output, CMLInput HSV  , CMLSize count);
CML_API void CMLHSLto16bitOutput  (const CMLColorMachine* cm, CMLOutput output, CMLInput HSL  , CMLSize count);
CML_API void CMLCMYKto16bitOutput (const CMLColorMachine* cm, CMLOutput output, CMLInput CMYK , CMLSize count);



// ////////////////////////////
// Normed Conversions
// ////////////////////////////


// In CML, all color values are stored with predefined bounds. These can be
// looked-up in the CMLConstants.h file. Sometimes though it is handy if you
// do not need to care about the bounds of different colorspaces. Therefore,
// in CML, for each colorspace, there exists a normed space where it is
// guaranteed that ALL channels are in the range (0,1). This does not mean
// that the values are clipped to these boundaries but rather more that the
// predefined minimal value of a channel is mapped to 0 and the maximal value
// to 1.
//
// Further more, CML defines additional cartesian conversions for certain
// colorspaces. Many colorspaces are cartesian to begin with, but some, such
// as Lch are in polar coordinates. To simplify the programmers work of
// distinguishing between different coordinate systems and help him computing
// color values using simple linear combinations, there exist conversion
// methods for such colorspaces. Using these conversions will result in a
// cartesian representation of the colors. As these cartesian colorspaces are
// not defined in the literature, they are normed to the range (0,1) just the
// same as the normed spaces described above.
//
// Normed and cartesian spaces are not documented in colorimetry and the
// representation chosen in this library is anything but standardized.
// Therefore, normed spaces are merely a programming simplification, for
// example when creating colors without considering the predefined bounds or
// when calculating colors such as in interpolation.
//
// Normed and cartesian spaces are a helpful tool, but nothing beyound!

// Note that all converter getters return the same function pointer type.
// This gives you as a programmer more freedom but beware of false
// conversions!
CML_API CMLNormedConverter CMLgetNormedInputConverter(CMLColorType colortype);
CML_API CMLNormedConverter CMLgetNormedOutputConverter(CMLColorType colortype);
// Note that those colortypes which are already in cartesian space will
// return the cartesian converter.
CML_API CMLNormedConverter CMLgetNormedCartesianInputConverter(CMLColorType colortype);
CML_API CMLNormedConverter CMLgetNormedCartesianOutputConverter(CMLColorType colortype);

// float Input Conversions from normed range [0,1]
CML_API void CMLGrayfromNormedInput  (CMLOutput gray  , CMLInput input, CMLSize count);
CML_API void CMLXYZfromNormedInput   (CMLOutput XYZ   , CMLInput input, CMLSize count);
CML_API void CMLYxyfromNormedInput   (CMLOutput Yxy   , CMLInput input, CMLSize count);
CML_API void CMLYuvfromNormedInput   (CMLOutput Yuv   , CMLInput input, CMLSize count);
CML_API void CMLYupvpfromNormedInput (CMLOutput Yupvp , CMLInput input, CMLSize count);
CML_API void CMLLabfromNormedInput   (CMLOutput Lab   , CMLInput input, CMLSize count);
CML_API void CMLLchfromNormedInput   (CMLOutput Lch   , CMLInput input, CMLSize count);
CML_API void CMLLuvfromNormedInput   (CMLOutput Luv   , CMLInput input, CMLSize count);
CML_API void CMLRGBfromNormedInput   (CMLOutput RGB   , CMLInput input, CMLSize count);
CML_API void CMLYCbCrfromNormedInput (CMLOutput YCbCr , CMLInput input, CMLSize count);
CML_API void CMLHSVfromNormedInput   (CMLOutput HSV   , CMLInput input, CMLSize count);
CML_API void CMLHSLfromNormedInput   (CMLOutput HSL   , CMLInput input, CMLSize count);
CML_API void CMLCMYKfromNormedInput  (CMLOutput CMYK  , CMLInput input, CMLSize count);

// Output Conversions to normed range [0,1]
CML_API void CMLGraytoNormedOutput (CMLOutput output, CMLInput gray , CMLSize count);
CML_API void CMLXYZtoNormedOutput  (CMLOutput output, CMLInput XYZ  , CMLSize count);
CML_API void CMLYxytoNormedOutput  (CMLOutput output, CMLInput Yxy  , CMLSize count);
CML_API void CMLYuvtoNormedOutput  (CMLOutput output, CMLInput Yuv  , CMLSize count);
CML_API void CMLYupvptoNormedOutput(CMLOutput output, CMLInput Yupvp, CMLSize count);
CML_API void CMLLabtoNormedOutput  (CMLOutput output, CMLInput Lab  , CMLSize count);
CML_API void CMLLchtoNormedOutput  (CMLOutput output, CMLInput Lch  , CMLSize count);
CML_API void CMLLuvtoNormedOutput  (CMLOutput output, CMLInput Luv  , CMLSize count);
CML_API void CMLRGBtoNormedOutput  (CMLOutput output, CMLInput RGB  , CMLSize count);
CML_API void CMLYCbCrtoNormedOutput(CMLOutput output, CMLInput YCbCr, CMLSize count);
CML_API void CMLHSVtoNormedOutput  (CMLOutput output, CMLInput HSV  , CMLSize count);
CML_API void CMLHSLtoNormedOutput  (CMLOutput output, CMLInput HSL  , CMLSize count);
CML_API void CMLCMYKtoNormedOutput (CMLOutput output, CMLInput CMYK , CMLSize count);

// float Input Conversions from normed cartesian range [0,1]
CML_API void CMLLchfromNormedCartesianInput   (CMLOutput Lch   , CMLInput input, CMLSize count);
CML_API void CMLHSVfromNormedCartesianInput   (CMLOutput HSV   , CMLInput input, CMLSize count);
CML_API void CMLHSLfromNormedCartesianInput   (CMLOutput HSL   , CMLInput input, CMLSize count);

// Output Conversions to normed cartesian range [0,1]
CML_API void CMLLchtoNormedCartesianOutput  (CMLOutput output, CMLInput Lch  , CMLSize count);
CML_API void CMLHSVtoNormedCartesianOutput  (CMLOutput output, CMLInput HSV  , CMLSize count);
CML_API void CMLHSLtoNormedCartesianOutput  (CMLOutput output, CMLInput HSL  , CMLSize count);



// ////////////////////////////
// Inversion functions
// ////////////////////////////

// Use these to invert colors. Black becomes white and vice versa.
CML_API void cmlInvertGray   (CMLInputOutput gray , CMLSize count);
CML_API void cmlInvertXYZ    (CMLInputOutput xyz  , CMLSize count);
CML_API void cmlInvertYxy    (CMLInputOutput yxy  , CMLSize count);
CML_API void cmlInvertYuv    (CMLInputOutput Yuv  , CMLSize count);
CML_API void cmlInvertYupvp  (CMLInputOutput Yupvp, CMLSize count);
CML_API void cmlInvertLab    (CMLInputOutput lab  , CMLSize count);
CML_API void cmlInvertLch    (CMLInputOutput lch  , CMLSize count);
CML_API void cmlInvertLuv    (CMLInputOutput luv  , CMLSize count);
CML_API void cmlInvertRGB    (CMLInputOutput rgb  , CMLSize count);
CML_API void cmlInvertYCbCr  (CMLInputOutput ycbcr, CMLSize count);
CML_API void cmlInvertHSV    (CMLInputOutput hsv  , CMLSize count);
CML_API void cmlInvertHSL    (CMLInputOutput hsl  , CMLSize count);
CML_API void cmlInvertCMYK   (CMLInputOutput cmyk , CMLSize count);

// ////////////////////////////
// Clamp functions
// ////////////////////////////

// Use these to clamp colors. No value will be out of range.
CML_API void CMLclampGray  (CMLInputOutput gray , CMLSize count);
CML_API void CMLclampXYZ   (CMLInputOutput xyz  , CMLSize count);
CML_API void CMLclampYxy   (CMLInputOutput yxy  , CMLSize count);
CML_API void CMLclampYuv   (CMLInputOutput Yuv  , CMLSize count);
CML_API void CMLclampYupvp (CMLInputOutput Yupvp, CMLSize count);
CML_API void CMLclampLab   (CMLInputOutput lab  , CMLSize count);
CML_API void CMLclampLch   (CMLInputOutput lch  , CMLSize count);
CML_API void CMLclampLuv   (CMLInputOutput luv  , CMLSize count);
CML_API void CMLclampRGB   (CMLInputOutput rgb  , CMLSize count);
CML_API void CMLclampYCbCr (CMLInputOutput ycbcr, CMLSize count);
CML_API void CMLclampHSV   (CMLInputOutput hsv  , CMLSize count);
CML_API void CMLclampHSL   (CMLInputOutput hsl  , CMLSize count);
CML_API void CMLclampCMYK  (CMLInputOutput cmyk , CMLSize count);



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

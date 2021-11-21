
// This file contains the API for the ColorMachine structure.
//
// Note that this API is explicitely made for engineers who know what they are
// doing. If you are looking for a simple entry into color transformations,
// see the BaseAPI or the ColorClasses.
//
//
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.




// ///////////////////////////////////////////////
// State Machine
// ///////////////////////////////////////////////

// Returns a pointer to 4 Bytes denoting unsigned 8-bit-integers as follows:
// version[0]: Main Version number (technology changes)
// version[1]: Sub Version number (large features, API changes)
// version[2]: Subsub Version number (small features, new API)
// version[3]: Either 0 for release or 1 for debug version
CMLAPI void                  CMLgetVersion(CMLByte version[4]);

// Create and destroy ColorMachines with these functions:
CMLAPI CMLColorMachine*      CMLcreateColorMachine();
CMLAPI void                  CMLreleaseColorMachine(CMLColorMachine* cm);

// If you have multiple state changes to set, lock the recomputation, set all
// desired values and release the recomputation. Doing so, the ColorMachine
// will only perform all necessary recomputations once and only once.
CMLAPI void                  CMLlockRecomputation(CMLColorMachine* cm);
CMLAPI void                  CMLreleaseRecomputation(CMLColorMachine* cm);

// The integer mapping defines, how floats are mapped to integers.
// Additionally, integers can have lower and upper cutoffs. This means that
// the minimal float values are mapped to the lower cutoffs and the maximal
// float values are mapped to the upper cutoffs. You can define cutoffs for
// channels up to CML_MAX_NUMBER_OF_CHANNELS. Note that cutoffs may also be
// negative.
CMLAPI CMLIntegerMappingType CMLgetIntegerMappingType(const CMLColorMachine* cm);
CMLAPI void                  CMLsetIntegerMappingType(CMLColorMachine* cm, CMLIntegerMappingType type);
CMLAPI void                  CMLget8bitCutoffs(const CMLColorMachine* cm, CMLint32* min, CMLint32* max, CMLuint32 channel);
CMLAPI void                  CMLset8bitCutoffs(CMLColorMachine* cm, CMLint32 min, CMLint32 max, CMLuint32 channel);
CMLAPI void                  CMLget16bitCutoffs(const CMLColorMachine* cm, CMLint32* min, CMLint32* max, CMLuint32 channel);
CMLAPI void                  cmlSet16bitCutoffs(CMLColorMachine* cm, CMLint32 min, CMLint32 max, CMLuint32 channel);

// The radiometric computation flag defines if spectral data shall be converted
// without or with normalization to Y=1. Set CMLTRUE for radiometric and
// CMLFALSE for colorimetric. Default is colorimetric.
//CMLAPI CMLBool               CMLgetRadiometricComputation(CMLColorMachine* cm);
//CMLAPI void                  CMLsetRadiometricComputation(CMLColorMachine* cm, CMLBool radiometric);

// The observer defines if the 2 degree or the 10 degree model and what data
// set is used. Initial setting is 2 degrees of CIE recommendation.
CMLAPI const CMLObserver*    cmlGetObserver(const CMLColorMachine* cm);
CMLAPI CMLObserverType       CMLgetObserverType(const CMLColorMachine* cm);
CMLAPI void                  CMLsetObserverType(CMLColorMachine* cm, CMLObserverType newobserver);
CMLAPI void                  CMLgetSpecDistFunctions(const CMLColorMachine* cm, const CMLFunction* observer[3]);
//CMLAPI void                  CMLsetSpecDistFunctions(CMLColorMachine* cm, const CMLFunction* observer[3]);
CMLAPI void                  CMLgetSpectralXYZColor(const CMLColorMachine* cm, CMLVec3 xyz, float lambda);

// The illumination defines the current illumination assumed. This includes
// the whitepoint. Initial setting is the standard illumination of the
// standard RGB colorspace, which for sRGB is D65.
// Note that setting the RGB Colorspace will set the illumination implicitely
// by default.
// Note that the setIlluminationTemperature method will only take effect with
// the Blackbody and custom D illuminant. Otherwise, the input is ignored.
CMLAPI CMLIlluminationType   CMLgetIlluminationType(CMLColorMachine* cm);
CMLAPI void                  CMLsetIlluminationType(CMLColorMachine* cm, CMLIlluminationType illuminationtype);
CMLAPI float                 CMLgetIlluminationTemperature(const CMLColorMachine* cm);
CMLAPI void                  CMLsetIlluminationTemperature(CMLColorMachine* cm, float temp);
CMLAPI const CMLFunction*    CMLgetIlluminationSpectrum(const CMLColorMachine* cm);
CMLAPI void                  CMLsetIlluminationSpectrum(CMLColorMachine* cm, const CMLFunction* spectrum);
CMLAPI void                  CMLgetWhitePointYxy(const CMLColorMachine* cm, CMLVec3 whitepointYxy);
CMLAPI void                  CMLsetWhitePointYxy(CMLColorMachine* cm, const float* Yxy);

// These functions set the computation of the Lab space. Default is CIELAB.
// The functions setting K and ke will only take effect if the
// labspace is set to CML_LAB_ADAMS_CROMATIC_VALENCE. Otherwise, the input
// is ignored. When setting a custom response, the gamma parameter will only
// be used with gamma responses.
// Be aware that most Lab spaces (including CIELAB) are relative to a specific
// whitepoint which in CML is defined by the current illumination.
CMLAPI CMLLabColorSpaceType  CMLgetLabColorSpace(const CMLColorMachine* cm);
CMLAPI void                  CMLsetLabColorSpace(CMLColorMachine* cm, CMLLabColorSpaceType labspace);
CMLAPI void                  CMLgetAdamsChromaticityValenceParameters(CMLColorMachine* cm, float* K, float* ke);
CMLAPI void                  CMLsetAdamsChromaticityValenceParameters(CMLColorMachine* cm, float K, float ke);
CMLAPI CMLuint8              CMLgetLabLUTSize(const CMLColorMachine* cm);
CMLAPI void                  CMLsetLabLUTSize(CMLColorMachine* cm, CMLuint8 bits);
CMLAPI const CMLFunction*    CMLgetLtoLinearResponse(const CMLColorMachine* cm);
CMLAPI const CMLFunction*    CMLgetLineartoLResponse(const CMLColorMachine* cm);
CMLAPI const CMLResponseCurve* CMLgetResponseL  (CMLColorMachine* cm);
//CMLAPI CMLFunctionType       CMLgetLabResponseCurveFunctionType(const CMLColorMachine* cm);
CMLAPI void                  CMLsetResponseL(CMLColorMachine* cm, CMLResponseCurve* response);
//CMLAPI float                 CMLgetLabGamma(const CMLColorMachine* cm);

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
CMLAPI CMLRGBColorSpace      CMLgetRGBColorSpace(const CMLColorMachine* cm);
CMLAPI void                  CMLsetRGBColorSpace(CMLColorMachine* cm, CMLRGBColorSpace colorspacetype);
CMLAPI void                  CMLgetRGBPrimariesYxy(const CMLColorMachine* cm, CMLVec3 primaries[3]);
CMLAPI void                  CMLsetRGBPrimariesYxy(CMLColorMachine* cm, CMLVec3 primaries[3]);
//CMLAPI void                  CMLgetRGBtoLinearResponses(const CMLColorMachine* cm, const CMLFunction* responses[3]);
//CMLAPI void                  CMLgetLineartoRGBResponses(const CMLColorMachine* cm, const CMLFunction* responses[3]);
//CMLAPI void                  CMLgetRGBResponseTypes(const CMLColorMachine* cm, CMLResponseCurveType responsetypes[3]);
//CMLAPI void                  CMLgetRGBGammas(const CMLColorMachine* cm, float gammas[3]);
CMLAPI void                  CMLsetResponseRGB(CMLColorMachine* cm, CMLResponseCurve* response);
CMLAPI const CMLResponseCurve* CMLgetResponseR  (CMLColorMachine* cm);
CMLAPI const CMLResponseCurve* CMLgetResponseG  (CMLColorMachine* cm);
CMLAPI const CMLResponseCurve* CMLgetResponseB  (CMLColorMachine* cm);
CMLAPI void                  CMLsetResponseR  (CMLColorMachine* cm, CMLResponseCurve* response);
CMLAPI void                  CMLsetResponseG  (CMLColorMachine* cm, CMLResponseCurve* response);
CMLAPI void                  CMLsetResponseB  (CMLColorMachine* cm, CMLResponseCurve* response);
CMLAPI CMLuint8              CMLgetRGBLUTSize(const CMLColorMachine* cm);
CMLAPI void                  CMLsetRGBLUTSize(CMLColorMachine* cm, CMLuint8 bits);


// Transformation from RGB to CMYK can be achieved using different approaches
// like UCR, GCR or standard transform. Currently, only UCR and standard
// transform is implemented.
// Initial setting is standard transform.
CMLAPI CMLCMYKTransformType  CMLgetCMYKTransform(const CMLColorMachine* cm);
CMLAPI void                  CMLsetCMYKTransform(CMLColorMachine* cm, CMLCMYKTransformType transform);

// Transformation from any Color to Gray and vice versa can be achieved using
// different approaches. Initial setting is the computation from the
// L* value (CIELAB).
CMLAPI CMLGrayComputationType  CMLgetGrayComputationType(const CMLColorMachine* cm);
CMLAPI void                    CMLsetGrayComputationType(CMLColorMachine* cm, CMLGrayComputationType computation);



// ///////////////////////////////////////////////
// Color conversions
//
// Using ColorMachines, you can convert any color into any other with the
// following conversion functions. You can also get a function pointer to
// one of these conversion function using the CMLgetColorConverter function.
// ///////////////////////////////////////////////

CMLAPI CMLColorConverter     CMLgetColorConverter(CMLColorType outputsystem, CMLColorType inputsystem);

// Gray Conversions
CMLAPI void CMLGraytoGray  (const CMLColorMachine* cm, CMLOutput grayd , CMLInput grays , CMLSize count);
CMLAPI void CMLGraytoXYZ   (const CMLColorMachine* cm, CMLOutput XYZ   , CMLInput gray  , CMLSize count);
CMLAPI void CMLGraytoYuv   (const CMLColorMachine* cm, CMLOutput Yuv   , CMLInput gray  , CMLSize count);
CMLAPI void CMLGraytoYupvp (const CMLColorMachine* cm, CMLOutput Yupvp , CMLInput gray  , CMLSize count);
CMLAPI void CMLGraytoYxy   (const CMLColorMachine* cm, CMLOutput Yxy   , CMLInput gray  , CMLSize count);
CMLAPI void CMLGraytoLab   (const CMLColorMachine* cm, CMLOutput Lab   , CMLInput gray  , CMLSize count);
CMLAPI void CMLGraytoLch   (const CMLColorMachine* cm, CMLOutput Lch   , CMLInput gray  , CMLSize count);
CMLAPI void CMLGraytoLuv   (const CMLColorMachine* cm, CMLOutput Luv   , CMLInput gray  , CMLSize count);
CMLAPI void CMLGraytoRGB   (const CMLColorMachine* cm, CMLOutput RGB   , CMLInput gray  , CMLSize count);
CMLAPI void CMLGraytoYCbCr (const CMLColorMachine* cm, CMLOutput YCbCr , CMLInput gray  , CMLSize count);
CMLAPI void CMLGraytoHSV   (const CMLColorMachine* cm, CMLOutput HSV   , CMLInput gray  , CMLSize count);
CMLAPI void CMLGraytoHSL   (const CMLColorMachine* cm, CMLOutput HSL   , CMLInput gray  , CMLSize count);
CMLAPI void CMLGraytoCMYK  (const CMLColorMachine* cm, CMLOutput CMYK  , CMLInput gray  , CMLSize count);

// XYZ Conversions
CMLAPI void CMLXYZtoGray   (const CMLColorMachine* cm, CMLOutput gray  , CMLInput XYZ   , CMLSize count);
CMLAPI void CMLXYZtoXYZ    (const CMLColorMachine* cm, CMLOutput XYZd  , CMLInput XYZs  , CMLSize count);
CMLAPI void CMLXYZtoYuv    (const CMLColorMachine* cm, CMLOutput Yuv   , CMLInput XYZ   , CMLSize count);
CMLAPI void CMLXYZtoYupvp  (const CMLColorMachine* cm, CMLOutput Yupvp , CMLInput XYZ   , CMLSize count);
CMLAPI void CMLXYZtoYxy    (const CMLColorMachine* cm, CMLOutput Yxy   , CMLInput XYZ   , CMLSize count);
CMLAPI void CMLXYZtoLab    (const CMLColorMachine* cm, CMLOutput Lab   , CMLInput XYZ   , CMLSize count);
CMLAPI void CMLXYZtoLch    (const CMLColorMachine* cm, CMLOutput Lch   , CMLInput XYZ   , CMLSize count);
CMLAPI void CMLXYZtoLuv    (const CMLColorMachine* cm, CMLOutput Luv   , CMLInput XYZ   , CMLSize count);
CMLAPI void CMLXYZtoRGB    (const CMLColorMachine* cm, CMLOutput RGB   , CMLInput XYZ   , CMLSize count);
CMLAPI void CMLXYZtoYCbCr  (const CMLColorMachine* cm, CMLOutput YCbCr , CMLInput XYZ   , CMLSize count);
CMLAPI void CMLXYZtoHSV    (const CMLColorMachine* cm, CMLOutput HSV   , CMLInput XYZ   , CMLSize count);
CMLAPI void CMLXYZtoHSL    (const CMLColorMachine* cm, CMLOutput HSL   , CMLInput XYZ   , CMLSize count);
CMLAPI void CMLXYZtoCMYK   (const CMLColorMachine* cm, CMLOutput CMYK  , CMLInput XYZ   , CMLSize count);

// Yuv Conversions
CMLAPI void CMLYuvtoGray   (const CMLColorMachine* cm, CMLOutput gray  , CMLInput Yuv   , CMLSize count);
CMLAPI void CMLYuvtoXYZ    (const CMLColorMachine* cm, CMLOutput XYZ   , CMLInput Yuv   , CMLSize count);
CMLAPI void CMLYuvtoYuv    (const CMLColorMachine* cm, CMLOutput Yuvd  , CMLInput Yuvs  , CMLSize count);
CMLAPI void CMLYuvtoYupvp  (const CMLColorMachine* cm, CMLOutput Yupvp , CMLInput Yuv   , CMLSize count);
CMLAPI void CMLYuvtoYxy    (const CMLColorMachine* cm, CMLOutput Yxy   , CMLInput Yuv   , CMLSize count);
CMLAPI void CMLYuvtoLab    (const CMLColorMachine* cm, CMLOutput Lab   , CMLInput Yuv   , CMLSize count);
CMLAPI void CMLYuvtoLch    (const CMLColorMachine* cm, CMLOutput Lch   , CMLInput Yuv   , CMLSize count);
CMLAPI void CMLYuvtoLuv    (const CMLColorMachine* cm, CMLOutput Luv   , CMLInput Yuv   , CMLSize count);
CMLAPI void CMLYuvtoRGB    (const CMLColorMachine* cm, CMLOutput RGB   , CMLInput Yuv   , CMLSize count);
CMLAPI void CMLYuvtoYCbCr  (const CMLColorMachine* cm, CMLOutput YCbCr , CMLInput Yuv   , CMLSize count);
CMLAPI void CMLYuvtoHSV    (const CMLColorMachine* cm, CMLOutput HSV   , CMLInput Yuv   , CMLSize count);
CMLAPI void CMLYuvtoHSL    (const CMLColorMachine* cm, CMLOutput HSL   , CMLInput Yuv   , CMLSize count);
CMLAPI void CMLYuvtoCMYK   (const CMLColorMachine* cm, CMLOutput CMYK  , CMLInput Yuv   , CMLSize count);

// Yupvp Conversions
CMLAPI void CMLYupvptoGray (const CMLColorMachine* cm, CMLOutput gray  , CMLInput Yupvp , CMLSize count);
CMLAPI void CMLYupvptoXYZ  (const CMLColorMachine* cm, CMLOutput XYZ   , CMLInput Yupvp , CMLSize count);
CMLAPI void CMLYupvptoYuv  (const CMLColorMachine* cm, CMLOutput Yuv   , CMLInput Yupvp , CMLSize count);
CMLAPI void CMLYupvptoYupvp(const CMLColorMachine* cm, CMLOutput Yupvpd,CMLInput Yupvps , CMLSize count);
CMLAPI void CMLYupvptoYxy  (const CMLColorMachine* cm, CMLOutput Yxy   , CMLInput Yupvp , CMLSize count);
CMLAPI void CMLYupvptoLab  (const CMLColorMachine* cm, CMLOutput Lab   , CMLInput Yupvp , CMLSize count);
CMLAPI void CMLYupvptoLch  (const CMLColorMachine* cm, CMLOutput Lch   , CMLInput Yupvp , CMLSize count);
CMLAPI void CMLYupvptoLuv  (const CMLColorMachine* cm, CMLOutput Luv   , CMLInput Yupvp , CMLSize count);
CMLAPI void CMLYupvptoRGB  (const CMLColorMachine* cm, CMLOutput RGB   , CMLInput Yupvp , CMLSize count);
CMLAPI void CMLYupvptoYCbCr(const CMLColorMachine* cm, CMLOutput YCbCr , CMLInput Yupvp , CMLSize count);
CMLAPI void CMLYupvptoHSV  (const CMLColorMachine* cm, CMLOutput HSV   , CMLInput Yupvp , CMLSize count);
CMLAPI void CMLYupvptoHSL  (const CMLColorMachine* cm, CMLOutput HSL   , CMLInput Yupvp , CMLSize count);
CMLAPI void CMLYupvptoCMYK (const CMLColorMachine* cm, CMLOutput CMYK  , CMLInput Yupvp , CMLSize count);

// Yxy Conversions
CMLAPI void CMLYxytoGray   (const CMLColorMachine* cm, CMLOutput gray  , CMLInput Yxy   , CMLSize count);
CMLAPI void CMLYxytoXYZ    (const CMLColorMachine* cm, CMLOutput XYZ   , CMLInput Yxy   , CMLSize count);
CMLAPI void CMLYxytoYuv    (const CMLColorMachine* cm, CMLOutput Yuv   , CMLInput Yxy   , CMLSize count);
CMLAPI void CMLYxytoYupvp  (const CMLColorMachine* cm, CMLOutput Yupvp , CMLInput Yxy   , CMLSize count);
CMLAPI void CMLYxytoYxy    (const CMLColorMachine* cm, CMLOutput Yxyd  , CMLInput Yxys  , CMLSize count);
CMLAPI void CMLYxytoLab    (const CMLColorMachine* cm, CMLOutput Lab   , CMLInput Yxy   , CMLSize count);
CMLAPI void CMLYxytoLch    (const CMLColorMachine* cm, CMLOutput Lch   , CMLInput Yxy   , CMLSize count);
CMLAPI void CMLYxytoLuv    (const CMLColorMachine* cm, CMLOutput Luv   , CMLInput Yxy   , CMLSize count);
CMLAPI void CMLYxytoRGB    (const CMLColorMachine* cm, CMLOutput RGB   , CMLInput Yxy   , CMLSize count);
CMLAPI void CMLYxytoYCbCr  (const CMLColorMachine* cm, CMLOutput YCbCr , CMLInput Yxy   , CMLSize count);
CMLAPI void CMLYxytoHSV    (const CMLColorMachine* cm, CMLOutput HSV   , CMLInput Yxy   , CMLSize count);
CMLAPI void CMLYxytoHSL    (const CMLColorMachine* cm, CMLOutput HSL   , CMLInput Yxy   , CMLSize count);
CMLAPI void CMLYxytoCMYK   (const CMLColorMachine* cm, CMLOutput CMYK  , CMLInput Yxy   , CMLSize count);

// Lab Conversions
CMLAPI void CMLLabtoGray   (const CMLColorMachine* cm, CMLOutput gray  , CMLInput Lab   , CMLSize count);
CMLAPI void CMLLabtoXYZ    (const CMLColorMachine* cm, CMLOutput XYZ   , CMLInput Lab   , CMLSize count);
CMLAPI void CMLLabtoYuv    (const CMLColorMachine* cm, CMLOutput Yuv   , CMLInput Lab   , CMLSize count);
CMLAPI void CMLLabtoYupvp  (const CMLColorMachine* cm, CMLOutput Yupvp , CMLInput Lab   , CMLSize count);
CMLAPI void CMLLabtoYxy    (const CMLColorMachine* cm, CMLOutput Yxy   , CMLInput Lab   , CMLSize count);
CMLAPI void CMLLabtoLab    (const CMLColorMachine* cm, CMLOutput Labd  , CMLInput Labs  , CMLSize count);
CMLAPI void CMLLabtoLch    (const CMLColorMachine* cm, CMLOutput Lch   , CMLInput Lab   , CMLSize count);
CMLAPI void CMLLabtoLuv    (const CMLColorMachine* cm, CMLOutput Luv   , CMLInput Lab   , CMLSize count);
CMLAPI void CMLLabtoRGB    (const CMLColorMachine* cm, CMLOutput RGB   , CMLInput Lab   , CMLSize count);
CMLAPI void CMLLabtoYCbCr  (const CMLColorMachine* cm, CMLOutput YCbCr , CMLInput Lab   , CMLSize count);
CMLAPI void CMLLabtoHSV    (const CMLColorMachine* cm, CMLOutput HSV   , CMLInput Lab   , CMLSize count);
CMLAPI void CMLLabtoHSL    (const CMLColorMachine* cm, CMLOutput HSL   , CMLInput Lab   , CMLSize count);
CMLAPI void CMLLabtoCMYK   (const CMLColorMachine* cm, CMLOutput CMYK  , CMLInput Lab   , CMLSize count);

// Lch Conversions
CMLAPI void CMLLchtoGray   (const CMLColorMachine* cm, CMLOutput gray  , CMLInput Lch   , CMLSize count);
CMLAPI void CMLLchtoXYZ    (const CMLColorMachine* cm, CMLOutput XYZ   , CMLInput Lch   , CMLSize count);
CMLAPI void CMLLchtoYuv    (const CMLColorMachine* cm, CMLOutput Yuv   , CMLInput Lch   , CMLSize count);
CMLAPI void CMLLchtoYupvp  (const CMLColorMachine* cm, CMLOutput Yupvp , CMLInput Lch   , CMLSize count);
CMLAPI void CMLLchtoYxy    (const CMLColorMachine* cm, CMLOutput Yxy   , CMLInput Lch   , CMLSize count);
CMLAPI void CMLLchtoLab    (const CMLColorMachine* cm, CMLOutput Lab   , CMLInput Lch   , CMLSize count);
CMLAPI void CMLLchtoLch    (const CMLColorMachine* cm, CMLOutput Lchd  , CMLInput Lchs  , CMLSize count);
CMLAPI void CMLLchtoLuv    (const CMLColorMachine* cm, CMLOutput Luv   , CMLInput Lch   , CMLSize count);
CMLAPI void CMLLchtoRGB    (const CMLColorMachine* cm, CMLOutput RGB   , CMLInput Lch   , CMLSize count);
CMLAPI void CMLLchtoYCbCr  (const CMLColorMachine* cm, CMLOutput Yuv   , CMLInput Lch   , CMLSize count);
CMLAPI void CMLLchtoHSV    (const CMLColorMachine* cm, CMLOutput HSV   , CMLInput Lch   , CMLSize count);
CMLAPI void CMLLchtoHSL    (const CMLColorMachine* cm, CMLOutput HSL   , CMLInput Lch   , CMLSize count);
CMLAPI void CMLLchtoCMYK   (const CMLColorMachine* cm, CMLOutput CMYK  , CMLInput Lch   , CMLSize count);

// Luv Conversions
CMLAPI void CMLLuvtoGray   (const CMLColorMachine* cm, CMLOutput gray  , CMLInput Luv   , CMLSize count);
CMLAPI void CMLLuvtoXYZ    (const CMLColorMachine* cm, CMLOutput XYZ   , CMLInput Luv   , CMLSize count);
CMLAPI void CMLLuvtoYuv    (const CMLColorMachine* cm, CMLOutput Yuv   , CMLInput Luv   , CMLSize count);
CMLAPI void CMLLuvtoYupvp  (const CMLColorMachine* cm, CMLOutput Yupvp , CMLInput Luv   , CMLSize count);
CMLAPI void CMLLuvtoYxy    (const CMLColorMachine* cm, CMLOutput Yxy   , CMLInput Luv   , CMLSize count);
CMLAPI void CMLLuvtoLab    (const CMLColorMachine* cm, CMLOutput Lab   , CMLInput Luv   , CMLSize count);
CMLAPI void CMLLuvtoLch    (const CMLColorMachine* cm, CMLOutput Lch   , CMLInput Luv   , CMLSize count);
CMLAPI void CMLLuvtoLuv    (const CMLColorMachine* cm, CMLOutput Luvd  , CMLInput Luvs  , CMLSize count);
CMLAPI void CMLLuvtoRGB    (const CMLColorMachine* cm, CMLOutput RGB   , CMLInput Luv   , CMLSize count);
CMLAPI void CMLLuvtoYCbCr  (const CMLColorMachine* cm, CMLOutput YCbCr , CMLInput Luv   , CMLSize count);
CMLAPI void CMLLuvtoHSV    (const CMLColorMachine* cm, CMLOutput HSV   , CMLInput Luv   , CMLSize count);
CMLAPI void CMLLuvtoHSL    (const CMLColorMachine* cm, CMLOutput HSL   , CMLInput Luv   , CMLSize count);
CMLAPI void CMLLuvtoCMYK   (const CMLColorMachine* cm, CMLOutput CMYK  , CMLInput Luv   , CMLSize count);

// RGB Conversions
CMLAPI void CMLRGBtoGray   (const CMLColorMachine* cm, CMLOutput gray  , CMLInput RGB   , CMLSize count);
CMLAPI void CMLRGBtoXYZ    (const CMLColorMachine* cm, CMLOutput XYZ   , CMLInput RGB   , CMLSize count);
CMLAPI void CMLRGBtoYuv    (const CMLColorMachine* cm, CMLOutput Yuv   , CMLInput RGB   , CMLSize count);
CMLAPI void CMLRGBtoYupvp  (const CMLColorMachine* cm, CMLOutput Yupvp , CMLInput RGB   , CMLSize count);
CMLAPI void CMLRGBtoYxy    (const CMLColorMachine* cm, CMLOutput Yxy   , CMLInput RGB   , CMLSize count);
CMLAPI void CMLRGBtoLab    (const CMLColorMachine* cm, CMLOutput Lab   , CMLInput RGB   , CMLSize count);
CMLAPI void CMLRGBtoLch    (const CMLColorMachine* cm, CMLOutput Lch   , CMLInput RGB   , CMLSize count);
CMLAPI void CMLRGBtoLuv    (const CMLColorMachine* cm, CMLOutput Luv   , CMLInput RGB   , CMLSize count);
CMLAPI void CMLRGBtoRGB    (const CMLColorMachine* cm, CMLOutput RGBd  , CMLInput RGBs  , CMLSize count);
CMLAPI void CMLRGBtoYCbCr  (const CMLColorMachine* cm, CMLOutput YCbCr , CMLInput RGB   , CMLSize count);
CMLAPI void CMLRGBtoHSV    (const CMLColorMachine* cm, CMLOutput HSV   , CMLInput RGB   , CMLSize count);
CMLAPI void CMLRGBtoHSL    (const CMLColorMachine* cm, CMLOutput HSL   , CMLInput RGB   , CMLSize count);
CMLAPI void CMLRGBtoCMYK   (const CMLColorMachine* cm, CMLOutput CMYK  , CMLInput RGB   , CMLSize count);

// YCbCr Conversions
CMLAPI void CMLYCbCrtoGray (const CMLColorMachine* cm, CMLOutput gray  , CMLInput YCbCr , CMLSize count);
CMLAPI void CMLYCbCrtoXYZ  (const CMLColorMachine* cm, CMLOutput XYZ   , CMLInput YCbCr , CMLSize count);
CMLAPI void CMLYCbCrtoYuv  (const CMLColorMachine* cm, CMLOutput Yuv   , CMLInput YCbCr , CMLSize count);
CMLAPI void CMLYCbCrtoYupvp(const CMLColorMachine* cm, CMLOutput Yupvp , CMLInput YCbCr , CMLSize count);
CMLAPI void CMLYCbCrtoYxy  (const CMLColorMachine* cm, CMLOutput Yxy   , CMLInput YCbCr , CMLSize count);
CMLAPI void CMLYCbCrtoLab  (const CMLColorMachine* cm, CMLOutput Lab   , CMLInput YCbCr , CMLSize count);
CMLAPI void CMLYCbCrtoLch  (const CMLColorMachine* cm, CMLOutput Lch   , CMLInput YCbCr , CMLSize count);
CMLAPI void CMLYCbCrtoLuv  (const CMLColorMachine* cm, CMLOutput Luv   , CMLInput YCbCr , CMLSize count);
CMLAPI void CMLYCbCrtoRGB  (const CMLColorMachine* cm, CMLOutput RGB   , CMLInput YCbCr , CMLSize count);
CMLAPI void CMLYCbCrtoYCbCr(const CMLColorMachine* cm, CMLOutput YCbCrd, CMLInput YCbCrs, CMLSize count);
CMLAPI void CMLYCbCrtoHSV  (const CMLColorMachine* cm, CMLOutput HSV   , CMLInput YCbCr , CMLSize count);
CMLAPI void CMLYCbCrtoHSL  (const CMLColorMachine* cm, CMLOutput HSL   , CMLInput YCbCr , CMLSize count);
CMLAPI void CMLYCbCrtoCMYK (const CMLColorMachine* cm, CMLOutput CMYK  , CMLInput YCbCr , CMLSize count);

// HSV Conversions
CMLAPI void CMLHSVtoGray   (const CMLColorMachine* cm, CMLOutput gray  , CMLInput HSV   , CMLSize count);
CMLAPI void CMLHSVtoXYZ    (const CMLColorMachine* cm, CMLOutput XYZ   , CMLInput HSV   , CMLSize count);
CMLAPI void CMLHSVtoYuv    (const CMLColorMachine* cm, CMLOutput Yuv   , CMLInput HSV   , CMLSize count);
CMLAPI void CMLHSVtoYupvp  (const CMLColorMachine* cm, CMLOutput Yupvp , CMLInput HSV   , CMLSize count);
CMLAPI void CMLHSVtoYxy    (const CMLColorMachine* cm, CMLOutput Yxy   , CMLInput HSV   , CMLSize count);
CMLAPI void CMLHSVtoLab    (const CMLColorMachine* cm, CMLOutput Lab   , CMLInput HSV   , CMLSize count);
CMLAPI void CMLHSVtoLch    (const CMLColorMachine* cm, CMLOutput Lch   , CMLInput HSV   , CMLSize count);
CMLAPI void CMLHSVtoLuv    (const CMLColorMachine* cm, CMLOutput Luv   , CMLInput HSV   , CMLSize count);
CMLAPI void CMLHSVtoRGB    (const CMLColorMachine* cm, CMLOutput RGB   , CMLInput HSV   , CMLSize count);
CMLAPI void CMLHSVtoYCbCr  (const CMLColorMachine* cm, CMLOutput YCbCr , CMLInput HSV   , CMLSize count);
CMLAPI void CMLHSVtoHSV    (const CMLColorMachine* cm, CMLOutput HSVd  , CMLInput HSVs  , CMLSize count);
CMLAPI void CMLHSVtoHSL    (const CMLColorMachine* cm, CMLOutput HSL   , CMLInput HSV   , CMLSize count);
CMLAPI void CMLHSVtoCMYK   (const CMLColorMachine* cm, CMLOutput CMYK  , CMLInput HSV   , CMLSize count);

// HSL Conversions
CMLAPI void CMLHSLtoGray   (const CMLColorMachine* cm, CMLOutput gray  , CMLInput HSL   , CMLSize count);
CMLAPI void CMLHSLtoXYZ    (const CMLColorMachine* cm, CMLOutput XYZ   , CMLInput HSL   , CMLSize count);
CMLAPI void CMLHSLtoYuv    (const CMLColorMachine* cm, CMLOutput Yuv   , CMLInput HSL   , CMLSize count);
CMLAPI void CMLHSLtoYupvp  (const CMLColorMachine* cm, CMLOutput Yupvp , CMLInput HSL   , CMLSize count);
CMLAPI void CMLHSLtoYxy    (const CMLColorMachine* cm, CMLOutput Yxy   , CMLInput HSL   , CMLSize count);
CMLAPI void CMLHSLtoLab    (const CMLColorMachine* cm, CMLOutput Lab   , CMLInput HSL   , CMLSize count);
CMLAPI void CMLHSLtoLch    (const CMLColorMachine* cm, CMLOutput Lch   , CMLInput HSL   , CMLSize count);
CMLAPI void CMLHSLtoLuv    (const CMLColorMachine* cm, CMLOutput Luv   , CMLInput HSL   , CMLSize count);
CMLAPI void CMLHSLtoRGB    (const CMLColorMachine* cm, CMLOutput RGB   , CMLInput HSL   , CMLSize count);
CMLAPI void CMLHSLtoYCbCr  (const CMLColorMachine* cm, CMLOutput YCbCr , CMLInput HSL   , CMLSize count);
CMLAPI void CMLHSLtoHSV    (const CMLColorMachine* cm, CMLOutput HSV   , CMLInput HSL   , CMLSize count);
CMLAPI void CMLHSLtoHSL    (const CMLColorMachine* cm, CMLOutput HSLd  , CMLInput HSLs  , CMLSize count);
CMLAPI void CMLHSLtoCMYK   (const CMLColorMachine* cm, CMLOutput CMYK  , CMLInput HSL   , CMLSize count);

// CMYK Conversions
CMLAPI void CMLCMYKtoGray  (const CMLColorMachine* cm, CMLOutput gray  , CMLInput CMYK  , CMLSize count);
CMLAPI void CMLCMYKtoXYZ   (const CMLColorMachine* cm, CMLOutput XYZ   , CMLInput CMYK  , CMLSize count);
CMLAPI void CMLCMYKtoYuv   (const CMLColorMachine* cm, CMLOutput Yuv   , CMLInput CMYK  , CMLSize count);
CMLAPI void CMLCMYKtoYupvp (const CMLColorMachine* cm, CMLOutput Yupvp , CMLInput CMYK  , CMLSize count);
CMLAPI void CMLCMYKtoYxy   (const CMLColorMachine* cm, CMLOutput Yxy   , CMLInput CMYK  , CMLSize count);
CMLAPI void CMLCMYKtoLab   (const CMLColorMachine* cm, CMLOutput Lab   , CMLInput CMYK  , CMLSize count);
CMLAPI void CMLCMYKtoLch   (const CMLColorMachine* cm, CMLOutput Lch   , CMLInput CMYK  , CMLSize count);
CMLAPI void CMLCMYKtoLuv   (const CMLColorMachine* cm, CMLOutput Luv   , CMLInput CMYK  , CMLSize count);
CMLAPI void CMLCMYKtoRGB   (const CMLColorMachine* cm, CMLOutput RGB   , CMLInput CMYK  , CMLSize count);
CMLAPI void CMLCMYKtoYCbCr (const CMLColorMachine* cm, CMLOutput YCbCr , CMLInput CMYK  , CMLSize count);
CMLAPI void CMLCMYKtoHSV   (const CMLColorMachine* cm, CMLOutput HSV   , CMLInput CMYK  , CMLSize count);
CMLAPI void CMLCMYKtoHSL   (const CMLColorMachine* cm, CMLOutput HSL   , CMLInput CMYK  , CMLSize count);
CMLAPI void CMLCMYKtoCMYK  (const CMLColorMachine* cm, CMLOutput CMYKd , CMLInput CMYKs , CMLSize count);

// Spectrum Illumination Conversions
CMLAPI void CMLSpectrumIlluminationtoGray  (const CMLColorMachine* cm, CMLOutput gray  , CMLInput specill, CMLSize count);
CMLAPI void CMLSpectrumIlluminationtoXYZ   (const CMLColorMachine* cm, CMLOutput XYZ   , CMLInput specill, CMLSize count);
CMLAPI void CMLSpectrumIlluminationtoYuv   (const CMLColorMachine* cm, CMLOutput Yuv   , CMLInput specill, CMLSize count);
CMLAPI void CMLSpectrumIlluminationtoYupvp (const CMLColorMachine* cm, CMLOutput Yupvp , CMLInput specill, CMLSize count);
CMLAPI void CMLSpectrumIlluminationtoYxy   (const CMLColorMachine* cm, CMLOutput Yxy   , CMLInput specill, CMLSize count);
CMLAPI void CMLSpectrumIlluminationtoLab   (const CMLColorMachine* cm, CMLOutput Lab   , CMLInput specill, CMLSize count);
CMLAPI void CMLSpectrumIlluminationtoLch   (const CMLColorMachine* cm, CMLOutput Lch   , CMLInput specill, CMLSize count);
CMLAPI void CMLSpectrumIlluminationtoLuv   (const CMLColorMachine* cm, CMLOutput Luv   , CMLInput specill, CMLSize count);
CMLAPI void CMLSpectrumIlluminationtoRGB   (const CMLColorMachine* cm, CMLOutput RGB   , CMLInput specill, CMLSize count);
CMLAPI void CMLSpectrumIlluminationtoYCbCr (const CMLColorMachine* cm, CMLOutput YCbCr , CMLInput specill, CMLSize count);
CMLAPI void CMLSpectrumIlluminationtoHSV   (const CMLColorMachine* cm, CMLOutput HSV   , CMLInput specill, CMLSize count);
CMLAPI void CMLSpectrumIlluminationtoHSL   (const CMLColorMachine* cm, CMLOutput HSL   , CMLInput specill, CMLSize count);
CMLAPI void CMLSpectrumIlluminationtoCMYK  (const CMLColorMachine* cm, CMLOutput CMYK  , CMLInput specill, CMLSize count);

// Spectrum Remission Conversions
CMLAPI void CMLSpectrumRemissiontoGray  (const CMLColorMachine* cm, CMLOutput gray  , CMLInput specrem, CMLSize count);
CMLAPI void CMLSpectrumRemissiontoXYZ   (const CMLColorMachine* cm, CMLOutput XYZ   , CMLInput specrem, CMLSize count);
CMLAPI void CMLSpectrumRemissiontoYuv   (const CMLColorMachine* cm, CMLOutput Yuv   , CMLInput specrem, CMLSize count);
CMLAPI void CMLSpectrumRemissiontoYupvp (const CMLColorMachine* cm, CMLOutput Yupvp , CMLInput specrem, CMLSize count);
CMLAPI void CMLSpectrumRemissiontoYxy   (const CMLColorMachine* cm, CMLOutput Yxy   , CMLInput specrem, CMLSize count);
CMLAPI void CMLSpectrumRemissiontoLab   (const CMLColorMachine* cm, CMLOutput Lab   , CMLInput specrem, CMLSize count);
CMLAPI void CMLSpectrumRemissiontoLch   (const CMLColorMachine* cm, CMLOutput Lch   , CMLInput specrem, CMLSize count);
CMLAPI void CMLSpectrumRemissiontoLuv   (const CMLColorMachine* cm, CMLOutput Luv   , CMLInput specrem, CMLSize count);
CMLAPI void CMLSpectrumRemissiontoRGB   (const CMLColorMachine* cm, CMLOutput RGB   , CMLInput specrem, CMLSize count);
CMLAPI void CMLSpectrumRemissiontoYCbCr (const CMLColorMachine* cm, CMLOutput YCbCr , CMLInput specrem, CMLSize count);
CMLAPI void CMLSpectrumRemissiontoHSV   (const CMLColorMachine* cm, CMLOutput HSV   , CMLInput specrem, CMLSize count);
CMLAPI void CMLSpectrumRemissiontoHSL   (const CMLColorMachine* cm, CMLOutput HSL   , CMLInput specrem, CMLSize count);
CMLAPI void CMLSpectrumRemissiontoCMYK  (const CMLColorMachine* cm, CMLOutput CMYK  , CMLInput specrem, CMLSize count);



// ////////////////////////////
// Input & Output Conversions
// ////////////////////////////

// Often times, you need to import or export values from files or memory blocks.
// The data may be in a different encoding than used in CML. Therefore you can
// use the following functions to convert 8-Bit and 16-Bit data to the requred
// float data. These functions will adapt the data to the cutoffs and the
// integer mappings of the given machine.

// 8-bit Input Conversions
CMLAPI void CMLGrayfrom8bitInput (const CMLColorMachine* cm, CMLOutput gray  , CMLInput input, CMLSize count);
CMLAPI void CMLXYZfrom8bitInput  (const CMLColorMachine* cm, CMLOutput XYZ   , CMLInput input, CMLSize count);
CMLAPI void CMLYxyfrom8bitInput  (const CMLColorMachine* cm, CMLOutput Yxy   , CMLInput input, CMLSize count);
CMLAPI void CMLYuvfrom8bitInput  (const CMLColorMachine* cm, CMLOutput Yuv   , CMLInput input, CMLSize count);
CMLAPI void CMLYupvpfrom8bitInput(const CMLColorMachine* cm, CMLOutput Yupvp , CMLInput input, CMLSize count);
CMLAPI void CMLLabfrom8bitInput  (const CMLColorMachine* cm, CMLOutput Lab   , CMLInput input, CMLSize count);
CMLAPI void CMLLchfrom8bitInput  (const CMLColorMachine* cm, CMLOutput Lch   , CMLInput input, CMLSize count);
CMLAPI void CMLLuvfrom8bitInput  (const CMLColorMachine* cm, CMLOutput Luv   , CMLInput input, CMLSize count);
CMLAPI void CMLRGBfrom8bitInput  (const CMLColorMachine* cm, CMLOutput RGB   , CMLInput input, CMLSize count);
CMLAPI void CMLYCbCrfrom8bitInput(const CMLColorMachine* cm, CMLOutput YCbCr , CMLInput input, CMLSize count);
CMLAPI void CMLHSVfrom8bitInput  (const CMLColorMachine* cm, CMLOutput HSV   , CMLInput input, CMLSize count);
CMLAPI void CMLHSLfrom8bitInput  (const CMLColorMachine* cm, CMLOutput HSL   , CMLInput input, CMLSize count);
CMLAPI void CMLCMYKfrom8bitInput (const CMLColorMachine* cm, CMLOutput CMYK  , CMLInput input, CMLSize count);

// 16-bit Input Conversions
CMLAPI void CMLGrayfrom16bitInput  (const CMLColorMachine* cm, CMLOutput gray  , CMLInput input, CMLSize count);
CMLAPI void CMLXYZfrom16bitInput   (const CMLColorMachine* cm, CMLOutput XYZ   , CMLInput input, CMLSize count);
CMLAPI void CMLYxyfrom16bitInput   (const CMLColorMachine* cm, CMLOutput Yxy   , CMLInput input, CMLSize count);
CMLAPI void CMLYuvfrom16bitInput   (const CMLColorMachine* cm, CMLOutput Yuv   , CMLInput input, CMLSize count);
CMLAPI void CMLYupvpfrom16bitInput (const CMLColorMachine* cm, CMLOutput Yupvp , CMLInput input, CMLSize count);
CMLAPI void CMLLabfrom16bitInput   (const CMLColorMachine* cm, CMLOutput Lab   , CMLInput input, CMLSize count);
CMLAPI void CMLLchfrom16bitInput   (const CMLColorMachine* cm, CMLOutput Lch   , CMLInput input, CMLSize count);
CMLAPI void CMLLuvfrom16bitInput   (const CMLColorMachine* cm, CMLOutput Luv   , CMLInput input, CMLSize count);
CMLAPI void CMLRGBfrom16bitInput   (const CMLColorMachine* cm, CMLOutput RGB   , CMLInput input, CMLSize count);
CMLAPI void CMLYCbCrfrom16bitInput (const CMLColorMachine* cm, CMLOutput YCbCr , CMLInput input, CMLSize count);
CMLAPI void CMLHSVfrom16bitInput   (const CMLColorMachine* cm, CMLOutput HSV   , CMLInput input, CMLSize count);
CMLAPI void CMLHSLfrom16bitInput   (const CMLColorMachine* cm, CMLOutput HSL   , CMLInput input, CMLSize count);
CMLAPI void CMLCMYKfrom16bitInput  (const CMLColorMachine* cm, CMLOutput CMYK  , CMLInput input, CMLSize count);

// 8-bit Output Conversions
CMLAPI void CMLGrayto8bitOutput  (const CMLColorMachine* cm, CMLOutput output, CMLInput gray , CMLSize count);
CMLAPI void CMLXYZto8bitOutput   (const CMLColorMachine* cm, CMLOutput output, CMLInput XYZ  , CMLSize count);
CMLAPI void CMLYxyto8bitOutput   (const CMLColorMachine* cm, CMLOutput output, CMLInput Yxy  , CMLSize count);
CMLAPI void CMLYuvto8bitOutput   (const CMLColorMachine* cm, CMLOutput output, CMLInput Yuv  , CMLSize count);
CMLAPI void CMLYupvpto8bitOutput (const CMLColorMachine* cm, CMLOutput output, CMLInput Yupvp, CMLSize count);
CMLAPI void CMLLabto8bitOutput   (const CMLColorMachine* cm, CMLOutput output, CMLInput Lab  , CMLSize count);
CMLAPI void CMLLchto8bitOutput   (const CMLColorMachine* cm, CMLOutput output, CMLInput Lch  , CMLSize count);
CMLAPI void CMLLuvto8bitOutput   (const CMLColorMachine* cm, CMLOutput output, CMLInput Luv  , CMLSize count);
CMLAPI void CMLRGBto8bitOutput   (const CMLColorMachine* cm, CMLOutput output, CMLInput RGB  , CMLSize count);
CMLAPI void CMLYCbCrto8bitOutput (const CMLColorMachine* cm, CMLOutput output, CMLInput YCbCr, CMLSize count);
CMLAPI void CMLHSVto8bitOutput   (const CMLColorMachine* cm, CMLOutput output, CMLInput HSV  , CMLSize count);
CMLAPI void CMLHSLto8bitOutput   (const CMLColorMachine* cm, CMLOutput output, CMLInput HSL  , CMLSize count);
CMLAPI void CMLCMYKto8bitOutput  (const CMLColorMachine* cm, CMLOutput output, CMLInput CMYK , CMLSize count);

// 16-bit Output Conversions
CMLAPI void CMLGrayto16bitOutput (const CMLColorMachine* cm, CMLOutput output, CMLInput gray , CMLSize count);
CMLAPI void CMLXYZto16bitOutput  (const CMLColorMachine* cm, CMLOutput output, CMLInput XYZ  , CMLSize count);
CMLAPI void CMLYxyto16bitOutput  (const CMLColorMachine* cm, CMLOutput output, CMLInput Yxy  , CMLSize count);
CMLAPI void CMLYuvto16bitOutput  (const CMLColorMachine* cm, CMLOutput output, CMLInput Yuv  , CMLSize count);
CMLAPI void CMLYupvpto16bitOutput(const CMLColorMachine* cm, CMLOutput output, CMLInput Yupvp, CMLSize count);
CMLAPI void CMLLabto16bitOutput  (const CMLColorMachine* cm, CMLOutput output, CMLInput Lab  , CMLSize count);
CMLAPI void CMLLchto16bitOutput  (const CMLColorMachine* cm, CMLOutput output, CMLInput Lch  , CMLSize count);
CMLAPI void CMLLuvto16bitOutput  (const CMLColorMachine* cm, CMLOutput output, CMLInput Luv  , CMLSize count);
CMLAPI void CMLRGBto16bitOutput  (const CMLColorMachine* cm, CMLOutput output, CMLInput RGB  , CMLSize count);
CMLAPI void CMLYCbCrto16bitOutput(const CMLColorMachine* cm, CMLOutput output, CMLInput YCbCr, CMLSize count);
CMLAPI void CMLHSVto16bitOutput  (const CMLColorMachine* cm, CMLOutput output, CMLInput HSV  , CMLSize count);
CMLAPI void CMLHSLto16bitOutput  (const CMLColorMachine* cm, CMLOutput output, CMLInput HSL  , CMLSize count);
CMLAPI void CMLCMYKto16bitOutput (const CMLColorMachine* cm, CMLOutput output, CMLInput CMYK , CMLSize count);



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
CMLAPI CMLNormedConverter CMLgetNormedInputConverter(CMLColorType colortype);
CMLAPI CMLNormedConverter CMLgetNormedOutputConverter(CMLColorType colortype);
// Note that those colortypes which are already in cartesian space will
// return the cartesian converter.
CMLAPI CMLNormedConverter CMLgetNormedCartesianInputConverter(CMLColorType colortype);
CMLAPI CMLNormedConverter CMLgetNormedCartesianOutputConverter(CMLColorType colortype);

// float Input Conversions from normed range [0,1]
CMLAPI void CMLGrayfromNormedInput  (CMLOutput gray  , CMLInput input, CMLSize count);
CMLAPI void CMLXYZfromNormedInput   (CMLOutput XYZ   , CMLInput input, CMLSize count);
CMLAPI void CMLYxyfromNormedInput   (CMLOutput Yxy   , CMLInput input, CMLSize count);
CMLAPI void CMLYuvfromNormedInput   (CMLOutput Yuv   , CMLInput input, CMLSize count);
CMLAPI void CMLYupvpfromNormedInput (CMLOutput Yupvp , CMLInput input, CMLSize count);
CMLAPI void CMLLabfromNormedInput   (CMLOutput Lab   , CMLInput input, CMLSize count);
CMLAPI void CMLLchfromNormedInput   (CMLOutput Lch   , CMLInput input, CMLSize count);
CMLAPI void CMLLuvfromNormedInput   (CMLOutput Luv   , CMLInput input, CMLSize count);
CMLAPI void CMLRGBfromNormedInput   (CMLOutput RGB   , CMLInput input, CMLSize count);
CMLAPI void CMLYCbCrfromNormedInput (CMLOutput YCbCr , CMLInput input, CMLSize count);
CMLAPI void CMLHSVfromNormedInput   (CMLOutput HSV   , CMLInput input, CMLSize count);
CMLAPI void CMLHSLfromNormedInput   (CMLOutput HSL   , CMLInput input, CMLSize count);
CMLAPI void CMLCMYKfromNormedInput  (CMLOutput CMYK  , CMLInput input, CMLSize count);

// Output Conversions to normed range [0,1]
CMLAPI void CMLGraytoNormedOutput (CMLOutput output, CMLInput gray , CMLSize count);
CMLAPI void CMLXYZtoNormedOutput  (CMLOutput output, CMLInput XYZ  , CMLSize count);
CMLAPI void CMLYxytoNormedOutput  (CMLOutput output, CMLInput Yxy  , CMLSize count);
CMLAPI void CMLYuvtoNormedOutput  (CMLOutput output, CMLInput Yuv  , CMLSize count);
CMLAPI void CMLYupvptoNormedOutput(CMLOutput output, CMLInput Yupvp, CMLSize count);
CMLAPI void CMLLabtoNormedOutput  (CMLOutput output, CMLInput Lab  , CMLSize count);
CMLAPI void CMLLchtoNormedOutput  (CMLOutput output, CMLInput Lch  , CMLSize count);
CMLAPI void CMLLuvtoNormedOutput  (CMLOutput output, CMLInput Luv  , CMLSize count);
CMLAPI void CMLRGBtoNormedOutput  (CMLOutput output, CMLInput RGB  , CMLSize count);
CMLAPI void CMLYCbCrtoNormedOutput(CMLOutput output, CMLInput YCbCr, CMLSize count);
CMLAPI void CMLHSVtoNormedOutput  (CMLOutput output, CMLInput HSV  , CMLSize count);
CMLAPI void CMLHSLtoNormedOutput  (CMLOutput output, CMLInput HSL  , CMLSize count);
CMLAPI void CMLCMYKtoNormedOutput (CMLOutput output, CMLInput CMYK , CMLSize count);

// float Input Conversions from normed cartesian range [0,1]
CMLAPI void CMLLchfromNormedCartesianInput   (CMLOutput Lch   , CMLInput input, CMLSize count);
CMLAPI void CMLHSVfromNormedCartesianInput   (CMLOutput HSV   , CMLInput input, CMLSize count);
CMLAPI void CMLHSLfromNormedCartesianInput   (CMLOutput HSL   , CMLInput input, CMLSize count);

// Output Conversions to normed cartesian range [0,1]
CMLAPI void CMLLchtoNormedCartesianOutput  (CMLOutput output, CMLInput Lch  , CMLSize count);
CMLAPI void CMLHSVtoNormedCartesianOutput  (CMLOutput output, CMLInput HSV  , CMLSize count);
CMLAPI void CMLHSLtoNormedCartesianOutput  (CMLOutput output, CMLInput HSL  , CMLSize count);



// ////////////////////////////
// Inversion functions
// ////////////////////////////

// Use these to invert colors. Black becomes white and vice versa.
CMLAPI void CMLinvertGray   (CMLInputOutput gray , CMLSize count);
CMLAPI void CMLinvertXYZ    (CMLInputOutput xyz  , CMLSize count);
CMLAPI void CMLinvertYxy    (CMLInputOutput yxy  , CMLSize count);
CMLAPI void CMLinvertYuv    (CMLInputOutput Yuv  , CMLSize count);
CMLAPI void CMLinvertYupvp  (CMLInputOutput Yupvp, CMLSize count);
CMLAPI void CMLinvertLab    (CMLInputOutput lab  , CMLSize count);
CMLAPI void CMLinvertLch    (CMLInputOutput lch  , CMLSize count);
CMLAPI void CMLinvertLuv    (CMLInputOutput luv  , CMLSize count);
CMLAPI void CMLinvertRGB    (CMLInputOutput rgb  , CMLSize count);
CMLAPI void CMLinvertYCbCr  (CMLInputOutput ycbcr, CMLSize count);
CMLAPI void CMLinvertHSV    (CMLInputOutput hsv  , CMLSize count);
CMLAPI void CMLinvertHSL    (CMLInputOutput hsl  , CMLSize count);
CMLAPI void CMLinvertCMYK   (CMLInputOutput cmyk , CMLSize count);

// ////////////////////////////
// Clamp functions
// ////////////////////////////

// Use these to clamp colors. No value will be out of range.
CMLAPI void CMLclampGray  (CMLInputOutput gray , CMLSize count);
CMLAPI void CMLclampXYZ   (CMLInputOutput xyz  , CMLSize count);
CMLAPI void CMLclampYxy   (CMLInputOutput yxy  , CMLSize count);
CMLAPI void CMLclampYuv   (CMLInputOutput Yuv  , CMLSize count);
CMLAPI void CMLclampYupvp (CMLInputOutput Yupvp, CMLSize count);
CMLAPI void CMLclampLab   (CMLInputOutput lab  , CMLSize count);
CMLAPI void CMLclampLch   (CMLInputOutput lch  , CMLSize count);
CMLAPI void CMLclampLuv   (CMLInputOutput luv  , CMLSize count);
CMLAPI void CMLclampRGB   (CMLInputOutput rgb  , CMLSize count);
CMLAPI void CMLclampYCbCr (CMLInputOutput ycbcr, CMLSize count);
CMLAPI void CMLclampHSV   (CMLInputOutput hsv  , CMLSize count);
CMLAPI void CMLclampHSL   (CMLInputOutput hsl  , CMLSize count);
CMLAPI void CMLclampCMYK  (CMLInputOutput cmyk , CMLSize count);







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
CML_API void                  CMLget8BitCutoffs(const CMLColorMachine* cm, CMLint32* min, CMLint32* max, CMLuint32 channel);
CML_API void                  CMLset8BitCutoffs(CMLColorMachine* cm, CMLint32 min, CMLint32 max, CMLuint32 channel);
CML_API void                  CMLget16BitCutoffs(const CMLColorMachine* cm, CMLint32* min, CMLint32* max, CMLuint32 channel);
CML_API void                  cmlSet16BitCutoffs(CMLColorMachine* cm, CMLint32 min, CMLint32 max, CMLuint32 channel);

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
CML_API void                  CMLsetWhitePointYxy(CMLColorMachine* cm, const float* yxy);

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
// one of these conversion function using the cmlGetColorConverter function.
// ///////////////////////////////////////////////

CML_API CMLColorConverter     cmlGetColorConverter(CMLColorType outputSystem, CMLColorType inputSystem);

// Gray Conversions
CML_API void CMLGraytoGray  (const CMLColorMachine* cm, CMLOutput grayd , CMLInput grays , size_t count);
CML_API void CMLGraytoXYZ   (const CMLColorMachine* cm, CMLOutput xyz   , CMLInput gray  , size_t count);
CML_API void CMLGraytoYuv   (const CMLColorMachine* cm, CMLOutput yuv   , CMLInput gray  , size_t count);
CML_API void CMLGraytoYupvp (const CMLColorMachine* cm, CMLOutput yupvp , CMLInput gray  , size_t count);
CML_API void CMLGraytoYxy   (const CMLColorMachine* cm, CMLOutput yxy   , CMLInput gray  , size_t count);
CML_API void CMLGraytoLab   (const CMLColorMachine* cm, CMLOutput lab   , CMLInput gray  , size_t count);
CML_API void CMLGraytoLch   (const CMLColorMachine* cm, CMLOutput lch   , CMLInput gray  , size_t count);
CML_API void CMLGraytoLuv   (const CMLColorMachine* cm, CMLOutput luv   , CMLInput gray  , size_t count);
CML_API void CMLGraytoRGB   (const CMLColorMachine* cm, CMLOutput rgb   , CMLInput gray  , size_t count);
CML_API void CMLGraytoYCbCr (const CMLColorMachine* cm, CMLOutput ycbcr , CMLInput gray  , size_t count);
CML_API void CMLGraytoHSV   (const CMLColorMachine* cm, CMLOutput hsv   , CMLInput gray  , size_t count);
CML_API void CMLGraytoHSL   (const CMLColorMachine* cm, CMLOutput hsl   , CMLInput gray  , size_t count);
CML_API void CMLGraytoCMYK  (const CMLColorMachine* cm, CMLOutput cmyk  , CMLInput gray  , size_t count);

// XYZ Conversions
CML_API void CMLXYZtoGray   (const CMLColorMachine* cm, CMLOutput gray  , CMLInput xyz   , size_t count);
CML_API void CMLXYZtoXYZ    (const CMLColorMachine* cm, CMLOutput xyzd  , CMLInput xyzs  , size_t count);
CML_API void CMLXYZtoYuv    (const CMLColorMachine* cm, CMLOutput yuv   , CMLInput xyz   , size_t count);
CML_API void CMLXYZtoYupvp  (const CMLColorMachine* cm, CMLOutput yupvp , CMLInput xyz   , size_t count);
CML_API void CMLXYZtoYxy    (const CMLColorMachine* cm, CMLOutput yxy   , CMLInput xyz   , size_t count);
CML_API void CMLXYZtoLab    (const CMLColorMachine* cm, CMLOutput lab   , CMLInput xyz   , size_t count);
CML_API void CMLXYZtoLch    (const CMLColorMachine* cm, CMLOutput lch   , CMLInput xyz   , size_t count);
CML_API void CMLXYZtoLuv    (const CMLColorMachine* cm, CMLOutput luv   , CMLInput xyz   , size_t count);
CML_API void CMLXYZtoRGB    (const CMLColorMachine* cm, CMLOutput rgb   , CMLInput xyz   , size_t count);
CML_API void CMLXYZtoYCbCr  (const CMLColorMachine* cm, CMLOutput ycbcr , CMLInput xyz   , size_t count);
CML_API void CMLXYZtoHSV    (const CMLColorMachine* cm, CMLOutput hsv   , CMLInput xyz   , size_t count);
CML_API void CMLXYZtoHSL    (const CMLColorMachine* cm, CMLOutput hsl   , CMLInput xyz   , size_t count);
CML_API void CMLXYZtoCMYK   (const CMLColorMachine* cm, CMLOutput cmyk  , CMLInput xyz   , size_t count);

// Yuv Conversions
CML_API void CMLYuvtoGray   (const CMLColorMachine* cm, CMLOutput gray  , CMLInput yuv   , size_t count);
CML_API void CMLYuvtoXYZ    (const CMLColorMachine* cm, CMLOutput xyz   , CMLInput yuv   , size_t count);
CML_API void CMLYuvtoYuv    (const CMLColorMachine* cm, CMLOutput yuvd  , CMLInput yuvs  , size_t count);
CML_API void CMLYuvtoYupvp  (const CMLColorMachine* cm, CMLOutput yupvp , CMLInput yuv   , size_t count);
CML_API void CMLYuvtoYxy    (const CMLColorMachine* cm, CMLOutput yxy   , CMLInput yuv   , size_t count);
CML_API void CMLYuvtoLab    (const CMLColorMachine* cm, CMLOutput lab   , CMLInput yuv   , size_t count);
CML_API void CMLYuvtoLch    (const CMLColorMachine* cm, CMLOutput lch   , CMLInput yuv   , size_t count);
CML_API void CMLYuvtoLuv    (const CMLColorMachine* cm, CMLOutput luv   , CMLInput yuv   , size_t count);
CML_API void CMLYuvtoRGB    (const CMLColorMachine* cm, CMLOutput rgb   , CMLInput yuv   , size_t count);
CML_API void CMLYuvtoYCbCr  (const CMLColorMachine* cm, CMLOutput ycbcr , CMLInput yuv   , size_t count);
CML_API void CMLYuvtoHSV    (const CMLColorMachine* cm, CMLOutput hsv   , CMLInput yuv   , size_t count);
CML_API void CMLYuvtoHSL    (const CMLColorMachine* cm, CMLOutput hsl   , CMLInput yuv   , size_t count);
CML_API void CMLYuvtoCMYK   (const CMLColorMachine* cm, CMLOutput cmyk  , CMLInput yuv   , size_t count);

// Yupvp Conversions
CML_API void CMLYupvptoGray (const CMLColorMachine* cm, CMLOutput gray  , CMLInput yupvp , size_t count);
CML_API void CMLYupvptoXYZ  (const CMLColorMachine* cm, CMLOutput xyz   , CMLInput yupvp , size_t count);
CML_API void CMLYupvptoYuv  (const CMLColorMachine* cm, CMLOutput yuv   , CMLInput yupvp , size_t count);
CML_API void CMLYupvptoYupvp(const CMLColorMachine* cm, CMLOutput yupvpd, CMLInput yupvps, size_t count);
CML_API void CMLYupvptoYxy  (const CMLColorMachine* cm, CMLOutput yxy   , CMLInput yupvp , size_t count);
CML_API void CMLYupvptoLab  (const CMLColorMachine* cm, CMLOutput lab   , CMLInput yupvp , size_t count);
CML_API void CMLYupvptoLch  (const CMLColorMachine* cm, CMLOutput lch   , CMLInput yupvp , size_t count);
CML_API void CMLYupvptoLuv  (const CMLColorMachine* cm, CMLOutput luv   , CMLInput yupvp , size_t count);
CML_API void CMLYupvptoRGB  (const CMLColorMachine* cm, CMLOutput rgb   , CMLInput yupvp , size_t count);
CML_API void CMLYupvptoYCbCr(const CMLColorMachine* cm, CMLOutput ycbcr , CMLInput yupvp , size_t count);
CML_API void CMLYupvptoHSV  (const CMLColorMachine* cm, CMLOutput hsv   , CMLInput yupvp , size_t count);
CML_API void CMLYupvptoHSL  (const CMLColorMachine* cm, CMLOutput hsl   , CMLInput yupvp , size_t count);
CML_API void CMLYupvptoCMYK (const CMLColorMachine* cm, CMLOutput cmyk  , CMLInput yupvp , size_t count);

// Yxy Conversions
CML_API void CMLYxytoGray   (const CMLColorMachine* cm, CMLOutput gray  , CMLInput yxy   , size_t count);
CML_API void CMLYxytoXYZ    (const CMLColorMachine* cm, CMLOutput xyz   , CMLInput yxy   , size_t count);
CML_API void CMLYxytoYuv    (const CMLColorMachine* cm, CMLOutput yuv   , CMLInput yxy   , size_t count);
CML_API void CMLYxytoYupvp  (const CMLColorMachine* cm, CMLOutput yupvp , CMLInput yxy   , size_t count);
CML_API void CMLYxytoYxy    (const CMLColorMachine* cm, CMLOutput yxyd  , CMLInput yxys  , size_t count);
CML_API void CMLYxytoLab    (const CMLColorMachine* cm, CMLOutput lab   , CMLInput yxy   , size_t count);
CML_API void CMLYxytoLch    (const CMLColorMachine* cm, CMLOutput lch   , CMLInput yxy   , size_t count);
CML_API void CMLYxytoLuv    (const CMLColorMachine* cm, CMLOutput luv   , CMLInput yxy   , size_t count);
CML_API void CMLYxytoRGB    (const CMLColorMachine* cm, CMLOutput rgb   , CMLInput yxy   , size_t count);
CML_API void CMLYxytoYCbCr  (const CMLColorMachine* cm, CMLOutput ycbcr , CMLInput yxy   , size_t count);
CML_API void CMLYxytoHSV    (const CMLColorMachine* cm, CMLOutput hsv   , CMLInput yxy   , size_t count);
CML_API void CMLYxytoHSL    (const CMLColorMachine* cm, CMLOutput hsl   , CMLInput yxy   , size_t count);
CML_API void CMLYxytoCMYK   (const CMLColorMachine* cm, CMLOutput cmyk  , CMLInput yxy   , size_t count);

// Lab Conversions
CML_API void CMLLabtoGray   (const CMLColorMachine* cm, CMLOutput gray  , CMLInput lab   , size_t count);
CML_API void CMLLabtoXYZ    (const CMLColorMachine* cm, CMLOutput xyz   , CMLInput lab   , size_t count);
CML_API void CMLLabtoYuv    (const CMLColorMachine* cm, CMLOutput yuv   , CMLInput lab   , size_t count);
CML_API void CMLLabtoYupvp  (const CMLColorMachine* cm, CMLOutput yupvp , CMLInput lab   , size_t count);
CML_API void CMLLabtoYxy    (const CMLColorMachine* cm, CMLOutput yxy   , CMLInput lab   , size_t count);
CML_API void CMLLabtoLab    (const CMLColorMachine* cm, CMLOutput labd  , CMLInput labs  , size_t count);
CML_API void CMLLabtoLch    (const CMLColorMachine* cm, CMLOutput lch   , CMLInput lab   , size_t count);
CML_API void CMLLabtoLuv    (const CMLColorMachine* cm, CMLOutput luv   , CMLInput lab   , size_t count);
CML_API void CMLLabtoRGB    (const CMLColorMachine* cm, CMLOutput rgb   , CMLInput lab   , size_t count);
CML_API void CMLLabtoYCbCr  (const CMLColorMachine* cm, CMLOutput ycbcr , CMLInput lab   , size_t count);
CML_API void CMLLabtoHSV    (const CMLColorMachine* cm, CMLOutput hsv   , CMLInput lab   , size_t count);
CML_API void CMLLabtoHSL    (const CMLColorMachine* cm, CMLOutput hsl   , CMLInput lab   , size_t count);
CML_API void CMLLabtoCMYK   (const CMLColorMachine* cm, CMLOutput cmyk  , CMLInput lab   , size_t count);

// Lch Conversions
CML_API void CMLLchtoGray   (const CMLColorMachine* cm, CMLOutput gray  , CMLInput lch   , size_t count);
CML_API void CMLLchtoXYZ    (const CMLColorMachine* cm, CMLOutput xyz   , CMLInput lch   , size_t count);
CML_API void CMLLchtoYuv    (const CMLColorMachine* cm, CMLOutput yuv   , CMLInput lch   , size_t count);
CML_API void CMLLchtoYupvp  (const CMLColorMachine* cm, CMLOutput yupvp , CMLInput lch   , size_t count);
CML_API void CMLLchtoYxy    (const CMLColorMachine* cm, CMLOutput yxy   , CMLInput lch   , size_t count);
CML_API void CMLLchtoLab    (const CMLColorMachine* cm, CMLOutput lab   , CMLInput lch   , size_t count);
CML_API void CMLLchtoLch    (const CMLColorMachine* cm, CMLOutput lchd  , CMLInput lchs  , size_t count);
CML_API void CMLLchtoLuv    (const CMLColorMachine* cm, CMLOutput luv   , CMLInput lch   , size_t count);
CML_API void CMLLchtoRGB    (const CMLColorMachine* cm, CMLOutput rgb   , CMLInput lch   , size_t count);
CML_API void CMLLchtoYCbCr  (const CMLColorMachine* cm, CMLOutput ycbcr , CMLInput lch   , size_t count);
CML_API void CMLLchtoHSV    (const CMLColorMachine* cm, CMLOutput hsv   , CMLInput lch   , size_t count);
CML_API void CMLLchtoHSL    (const CMLColorMachine* cm, CMLOutput hsl   , CMLInput lch   , size_t count);
CML_API void CMLLchtoCMYK   (const CMLColorMachine* cm, CMLOutput cmyk  , CMLInput lch   , size_t count);

// Luv Conversions
CML_API void CMLLuvtoGray   (const CMLColorMachine* cm, CMLOutput gray  , CMLInput luv   , size_t count);
CML_API void CMLLuvtoXYZ    (const CMLColorMachine* cm, CMLOutput xyz   , CMLInput luv   , size_t count);
CML_API void CMLLuvtoYuv    (const CMLColorMachine* cm, CMLOutput yuv   , CMLInput luv   , size_t count);
CML_API void CMLLuvtoYupvp  (const CMLColorMachine* cm, CMLOutput yupvp , CMLInput luv   , size_t count);
CML_API void CMLLuvtoYxy    (const CMLColorMachine* cm, CMLOutput yxy   , CMLInput luv   , size_t count);
CML_API void CMLLuvtoLab    (const CMLColorMachine* cm, CMLOutput lab   , CMLInput luv   , size_t count);
CML_API void CMLLuvtoLch    (const CMLColorMachine* cm, CMLOutput lch   , CMLInput luv   , size_t count);
CML_API void CMLLuvtoLuv    (const CMLColorMachine* cm, CMLOutput luvd  , CMLInput luvs  , size_t count);
CML_API void CMLLuvtoRGB    (const CMLColorMachine* cm, CMLOutput rgb   , CMLInput luv   , size_t count);
CML_API void CMLLuvtoYCbCr  (const CMLColorMachine* cm, CMLOutput ycbcr , CMLInput luv   , size_t count);
CML_API void CMLLuvtoHSV    (const CMLColorMachine* cm, CMLOutput hsv   , CMLInput luv   , size_t count);
CML_API void CMLLuvtoHSL    (const CMLColorMachine* cm, CMLOutput hsl   , CMLInput luv   , size_t count);
CML_API void CMLLuvtoCMYK   (const CMLColorMachine* cm, CMLOutput cmyk  , CMLInput luv   , size_t count);

// RGB Conversions
CML_API void CMLRGBtoGray   (const CMLColorMachine* cm, CMLOutput gray  , CMLInput rgb   , size_t count);
CML_API void CMLRGBtoXYZ    (const CMLColorMachine* cm, CMLOutput xyz   , CMLInput rgb   , size_t count);
CML_API void CMLRGBtoYuv    (const CMLColorMachine* cm, CMLOutput yuv   , CMLInput rgb   , size_t count);
CML_API void CMLRGBtoYupvp  (const CMLColorMachine* cm, CMLOutput yupvp , CMLInput rgb   , size_t count);
CML_API void CMLRGBtoYxy    (const CMLColorMachine* cm, CMLOutput yxy   , CMLInput rgb   , size_t count);
CML_API void CMLRGBtoLab    (const CMLColorMachine* cm, CMLOutput lab   , CMLInput rgb   , size_t count);
CML_API void CMLRGBtoLch    (const CMLColorMachine* cm, CMLOutput lch   , CMLInput rgb   , size_t count);
CML_API void CMLRGBtoLuv    (const CMLColorMachine* cm, CMLOutput luv   , CMLInput rgb   , size_t count);
CML_API void CMLRGBtoRGB    (const CMLColorMachine* cm, CMLOutput rgbd  , CMLInput rgbs  , size_t count);
CML_API void CMLRGBtoYCbCr  (const CMLColorMachine* cm, CMLOutput ycbcr , CMLInput rgb   , size_t count);
CML_API void CMLRGBtoHSV    (const CMLColorMachine* cm, CMLOutput hsv   , CMLInput rgb   , size_t count);
CML_API void CMLRGBtoHSL    (const CMLColorMachine* cm, CMLOutput hsl   , CMLInput rgb   , size_t count);
CML_API void CMLRGBtoCMYK   (const CMLColorMachine* cm, CMLOutput cmyk  , CMLInput rgb   , size_t count);

// YCbCr Conversions
CML_API void CMLYCbCrtoGray (const CMLColorMachine* cm, CMLOutput gray  , CMLInput ycbcr , size_t count);
CML_API void CMLYCbCrtoXYZ  (const CMLColorMachine* cm, CMLOutput xyz   , CMLInput ycbcr , size_t count);
CML_API void CMLYCbCrtoYuv  (const CMLColorMachine* cm, CMLOutput yuv   , CMLInput ycbcr , size_t count);
CML_API void CMLYCbCrtoYupvp(const CMLColorMachine* cm, CMLOutput yupvp , CMLInput ycbcr , size_t count);
CML_API void CMLYCbCrtoYxy  (const CMLColorMachine* cm, CMLOutput yxy   , CMLInput ycbcr , size_t count);
CML_API void CMLYCbCrtoLab  (const CMLColorMachine* cm, CMLOutput lab   , CMLInput ycbcr , size_t count);
CML_API void CMLYCbCrtoLch  (const CMLColorMachine* cm, CMLOutput lch   , CMLInput ycbcr , size_t count);
CML_API void CMLYCbCrtoLuv  (const CMLColorMachine* cm, CMLOutput luv   , CMLInput ycbcr , size_t count);
CML_API void CMLYCbCrtoRGB  (const CMLColorMachine* cm, CMLOutput rgb   , CMLInput ycbcr , size_t count);
CML_API void CMLYCbCrtoYCbCr(const CMLColorMachine* cm, CMLOutput ycbcrd, CMLInput ycbcrs, size_t count);
CML_API void CMLYCbCrtoHSV  (const CMLColorMachine* cm, CMLOutput hsv   , CMLInput ycbcr , size_t count);
CML_API void CMLYCbCrtoHSL  (const CMLColorMachine* cm, CMLOutput hsl   , CMLInput ycbcr , size_t count);
CML_API void CMLYCbCrtoCMYK (const CMLColorMachine* cm, CMLOutput cmyk  , CMLInput ycbcr , size_t count);

// HSV Conversions
CML_API void CMLHSVtoGray   (const CMLColorMachine* cm, CMLOutput gray  , CMLInput hsv   , size_t count);
CML_API void CMLHSVtoXYZ    (const CMLColorMachine* cm, CMLOutput xyz   , CMLInput hsv   , size_t count);
CML_API void CMLHSVtoYuv    (const CMLColorMachine* cm, CMLOutput yuv   , CMLInput hsv   , size_t count);
CML_API void CMLHSVtoYupvp  (const CMLColorMachine* cm, CMLOutput yupvp , CMLInput hsv   , size_t count);
CML_API void CMLHSVtoYxy    (const CMLColorMachine* cm, CMLOutput yxy   , CMLInput hsv   , size_t count);
CML_API void CMLHSVtoLab    (const CMLColorMachine* cm, CMLOutput lab   , CMLInput hsv   , size_t count);
CML_API void CMLHSVtoLch    (const CMLColorMachine* cm, CMLOutput lch   , CMLInput hsv   , size_t count);
CML_API void CMLHSVtoLuv    (const CMLColorMachine* cm, CMLOutput luv   , CMLInput hsv   , size_t count);
CML_API void CMLHSVtoRGB    (const CMLColorMachine* cm, CMLOutput rgb   , CMLInput hsv   , size_t count);
CML_API void CMLHSVtoYCbCr  (const CMLColorMachine* cm, CMLOutput ycbcr , CMLInput hsv   , size_t count);
CML_API void CMLHSVtoHSV    (const CMLColorMachine* cm, CMLOutput hsvd  , CMLInput hsvs  , size_t count);
CML_API void CMLHSVtoHSL    (const CMLColorMachine* cm, CMLOutput hsl   , CMLInput hsv   , size_t count);
CML_API void CMLHSVtoCMYK   (const CMLColorMachine* cm, CMLOutput cmyk  , CMLInput hsv   , size_t count);

// HSL Conversions
CML_API void CMLHSLtoGray   (const CMLColorMachine* cm, CMLOutput gray  , CMLInput hsl   , size_t count);
CML_API void CMLHSLtoXYZ    (const CMLColorMachine* cm, CMLOutput xyz   , CMLInput hsl   , size_t count);
CML_API void CMLHSLtoYuv    (const CMLColorMachine* cm, CMLOutput yuv   , CMLInput hsl   , size_t count);
CML_API void CMLHSLtoYupvp  (const CMLColorMachine* cm, CMLOutput yupvp , CMLInput hsl   , size_t count);
CML_API void CMLHSLtoYxy    (const CMLColorMachine* cm, CMLOutput yxy   , CMLInput hsl   , size_t count);
CML_API void CMLHSLtoLab    (const CMLColorMachine* cm, CMLOutput lab   , CMLInput hsl   , size_t count);
CML_API void CMLHSLtoLch    (const CMLColorMachine* cm, CMLOutput lch   , CMLInput hsl   , size_t count);
CML_API void CMLHSLtoLuv    (const CMLColorMachine* cm, CMLOutput luv   , CMLInput hsl   , size_t count);
CML_API void CMLHSLtoRGB    (const CMLColorMachine* cm, CMLOutput rgb   , CMLInput hsl   , size_t count);
CML_API void CMLHSLtoYCbCr  (const CMLColorMachine* cm, CMLOutput ycbcr , CMLInput hsl   , size_t count);
CML_API void CMLHSLtoHSV    (const CMLColorMachine* cm, CMLOutput hsv   , CMLInput hsl   , size_t count);
CML_API void CMLHSLtoHSL    (const CMLColorMachine* cm, CMLOutput hsld  , CMLInput hsls  , size_t count);
CML_API void CMLHSLtoCMYK   (const CMLColorMachine* cm, CMLOutput cmyk  , CMLInput hsl   , size_t count);

// CMYK Conversions
CML_API void CMLCMYKtoGray  (const CMLColorMachine* cm, CMLOutput gray  , CMLInput cmyk  , size_t count);
CML_API void CMLCMYKtoXYZ   (const CMLColorMachine* cm, CMLOutput xyz   , CMLInput cmyk  , size_t count);
CML_API void CMLCMYKtoYuv   (const CMLColorMachine* cm, CMLOutput yuv   , CMLInput cmyk  , size_t count);
CML_API void CMLCMYKtoYupvp (const CMLColorMachine* cm, CMLOutput yupvp , CMLInput cmyk  , size_t count);
CML_API void CMLCMYKtoYxy   (const CMLColorMachine* cm, CMLOutput yxy   , CMLInput cmyk  , size_t count);
CML_API void CMLCMYKtoLab   (const CMLColorMachine* cm, CMLOutput lab   , CMLInput cmyk  , size_t count);
CML_API void CMLCMYKtoLch   (const CMLColorMachine* cm, CMLOutput lch   , CMLInput cmyk  , size_t count);
CML_API void CMLCMYKtoLuv   (const CMLColorMachine* cm, CMLOutput luv   , CMLInput cmyk  , size_t count);
CML_API void CMLCMYKtoRGB   (const CMLColorMachine* cm, CMLOutput rgb   , CMLInput cmyk  , size_t count);
CML_API void CMLCMYKtoYCbCr (const CMLColorMachine* cm, CMLOutput ycbcr , CMLInput cmyk  , size_t count);
CML_API void CMLCMYKtoHSV   (const CMLColorMachine* cm, CMLOutput hsv   , CMLInput cmyk  , size_t count);
CML_API void CMLCMYKtoHSL   (const CMLColorMachine* cm, CMLOutput hsl   , CMLInput cmyk  , size_t count);
CML_API void CMLCMYKtoCMYK  (const CMLColorMachine* cm, CMLOutput cmykd , CMLInput cmyks , size_t count);

// Spectrum Illumination Conversions
CML_API void CMLSpectrumIlluminationtoGray  (const CMLColorMachine* cm, CMLOutput gray  , CMLInput specill, size_t count);
CML_API void CMLSpectrumIlluminationtoXYZ   (const CMLColorMachine* cm, CMLOutput xyz   , CMLInput specill, size_t count);
CML_API void CMLSpectrumIlluminationtoYuv   (const CMLColorMachine* cm, CMLOutput yuv   , CMLInput specill, size_t count);
CML_API void CMLSpectrumIlluminationtoYupvp (const CMLColorMachine* cm, CMLOutput yupvp , CMLInput specill, size_t count);
CML_API void CMLSpectrumIlluminationtoYxy   (const CMLColorMachine* cm, CMLOutput yxy   , CMLInput specill, size_t count);
CML_API void CMLSpectrumIlluminationtoLab   (const CMLColorMachine* cm, CMLOutput lab   , CMLInput specill, size_t count);
CML_API void CMLSpectrumIlluminationtoLch   (const CMLColorMachine* cm, CMLOutput lch   , CMLInput specill, size_t count);
CML_API void CMLSpectrumIlluminationtoLuv   (const CMLColorMachine* cm, CMLOutput luv   , CMLInput specill, size_t count);
CML_API void CMLSpectrumIlluminationtoRGB   (const CMLColorMachine* cm, CMLOutput rgb   , CMLInput specill, size_t count);
CML_API void CMLSpectrumIlluminationtoYCbCr (const CMLColorMachine* cm, CMLOutput ycbcr , CMLInput specill, size_t count);
CML_API void CMLSpectrumIlluminationtoHSV   (const CMLColorMachine* cm, CMLOutput hsv   , CMLInput specill, size_t count);
CML_API void CMLSpectrumIlluminationtoHSL   (const CMLColorMachine* cm, CMLOutput hsl   , CMLInput specill, size_t count);
CML_API void CMLSpectrumIlluminationtoCMYK  (const CMLColorMachine* cm, CMLOutput cmyk  , CMLInput specill, size_t count);

// Spectrum Remission Conversions
CML_API void CMLSpectrumRemissiontoGray  (const CMLColorMachine* cm, CMLOutput gray  , CMLInput specrem, size_t count);
CML_API void CMLSpectrumRemissiontoXYZ   (const CMLColorMachine* cm, CMLOutput xyz   , CMLInput specrem, size_t count);
CML_API void CMLSpectrumRemissiontoYuv   (const CMLColorMachine* cm, CMLOutput yuv   , CMLInput specrem, size_t count);
CML_API void CMLSpectrumRemissiontoYupvp (const CMLColorMachine* cm, CMLOutput yupvp , CMLInput specrem, size_t count);
CML_API void CMLSpectrumRemissiontoYxy   (const CMLColorMachine* cm, CMLOutput yxy   , CMLInput specrem, size_t count);
CML_API void CMLSpectrumRemissiontoLab   (const CMLColorMachine* cm, CMLOutput lab   , CMLInput specrem, size_t count);
CML_API void CMLSpectrumRemissiontoLch   (const CMLColorMachine* cm, CMLOutput lch   , CMLInput specrem, size_t count);
CML_API void CMLSpectrumRemissiontoLuv   (const CMLColorMachine* cm, CMLOutput luv   , CMLInput specrem, size_t count);
CML_API void CMLSpectrumRemissiontoRGB   (const CMLColorMachine* cm, CMLOutput rgb   , CMLInput specrem, size_t count);
CML_API void CMLSpectrumRemissiontoYCbCr (const CMLColorMachine* cm, CMLOutput ycbcr , CMLInput specrem, size_t count);
CML_API void CMLSpectrumRemissiontoHSV   (const CMLColorMachine* cm, CMLOutput hsv   , CMLInput specrem, size_t count);
CML_API void CMLSpectrumRemissiontoHSL   (const CMLColorMachine* cm, CMLOutput hsl   , CMLInput specrem, size_t count);
CML_API void CMLSpectrumRemissiontoCMYK  (const CMLColorMachine* cm, CMLOutput cmyk  , CMLInput specrem, size_t count);



// ////////////////////////////
// Input & Output Conversions
// ////////////////////////////

// Often times, you need to import or export values from files or memory blocks.
// The data may be in a different encoding than used in CML. Therefore you can
// use the following functions to convert 8-Bit and 16-Bit data to the requred
// float data. These functions will adapt the data to the cutoffs and the
// integer mappings of the given machine.

// 8-bit Input Conversions
CML_API void cmlData8ToGray (const CMLColorMachine* cm, CMLOutput gray  , CMLInput input, size_t count);
CML_API void cmlData8ToXYZ  (const CMLColorMachine* cm, CMLOutput xyz   , CMLInput input, size_t count);
CML_API void cmlData8ToYxy  (const CMLColorMachine* cm, CMLOutput yxy   , CMLInput input, size_t count);
CML_API void cmlData8ToYuv  (const CMLColorMachine* cm, CMLOutput yuv   , CMLInput input, size_t count);
CML_API void cmlData8ToYupvp(const CMLColorMachine* cm, CMLOutput yupvp , CMLInput input, size_t count);
CML_API void cmlData8ToLab  (const CMLColorMachine* cm, CMLOutput lab   , CMLInput input, size_t count);
CML_API void cmlData8ToLch  (const CMLColorMachine* cm, CMLOutput lch   , CMLInput input, size_t count);
CML_API void cmlData8ToLuv  (const CMLColorMachine* cm, CMLOutput luv   , CMLInput input, size_t count);
CML_API void cmlData8ToRGB  (const CMLColorMachine* cm, CMLOutput rgb   , CMLInput input, size_t count);
CML_API void cmlData8ToYCbCr(const CMLColorMachine* cm, CMLOutput ycbcr , CMLInput input, size_t count);
CML_API void cmlData8ToHSV  (const CMLColorMachine* cm, CMLOutput hsv   , CMLInput input, size_t count);
CML_API void cmlData8ToHSL  (const CMLColorMachine* cm, CMLOutput hsl   , CMLInput input, size_t count);
CML_API void cmlData8ToCMYK (const CMLColorMachine* cm, CMLOutput cmyk  , CMLInput input, size_t count);

// 16-bit Input Conversions
CML_API void cmlData16ToGray  (const CMLColorMachine* cm, CMLOutput gray  , CMLInput input, size_t count);
CML_API void cmlData16ToXYZ   (const CMLColorMachine* cm, CMLOutput xyz   , CMLInput input, size_t count);
CML_API void cmlData16ToYxy   (const CMLColorMachine* cm, CMLOutput yxy   , CMLInput input, size_t count);
CML_API void cmlData16ToYuv   (const CMLColorMachine* cm, CMLOutput yuv   , CMLInput input, size_t count);
CML_API void cmlData16ToYupvp (const CMLColorMachine* cm, CMLOutput yupvp , CMLInput input, size_t count);
CML_API void cmlData16ToLab   (const CMLColorMachine* cm, CMLOutput lab   , CMLInput input, size_t count);
CML_API void cmlData16ToLch   (const CMLColorMachine* cm, CMLOutput lch   , CMLInput input, size_t count);
CML_API void cmlData16ToLuv   (const CMLColorMachine* cm, CMLOutput luv   , CMLInput input, size_t count);
CML_API void cmlData16ToRGB   (const CMLColorMachine* cm, CMLOutput rgb   , CMLInput input, size_t count);
CML_API void cmlData16ToYCbCr (const CMLColorMachine* cm, CMLOutput ycbcr , CMLInput input, size_t count);
CML_API void cmlData16ToHSV   (const CMLColorMachine* cm, CMLOutput hsv   , CMLInput input, size_t count);
CML_API void cmlData16ToHSL   (const CMLColorMachine* cm, CMLOutput hsl   , CMLInput input, size_t count);
CML_API void cmlData16ToCMYK  (const CMLColorMachine* cm, CMLOutput cmyk  , CMLInput input, size_t count);

// 8-bit Output Conversions
CML_API void cmlGrayToData8  (const CMLColorMachine* cm, CMLOutput output, CMLInput gray , size_t count);
CML_API void cmlXYZToData8   (const CMLColorMachine* cm, CMLOutput output, CMLInput xyz  , size_t count);
CML_API void cmlYxyToData8   (const CMLColorMachine* cm, CMLOutput output, CMLInput yxy  , size_t count);
CML_API void cmlYuvToData8   (const CMLColorMachine* cm, CMLOutput output, CMLInput yuv  , size_t count);
CML_API void cmlYupvpToData8 (const CMLColorMachine* cm, CMLOutput output, CMLInput yupvp, size_t count);
CML_API void cmlLabToData8   (const CMLColorMachine* cm, CMLOutput output, CMLInput lab  , size_t count);
CML_API void cmlLchToData8   (const CMLColorMachine* cm, CMLOutput output, CMLInput lch  , size_t count);
CML_API void cmlLuvToData8   (const CMLColorMachine* cm, CMLOutput output, CMLInput luv  , size_t count);
CML_API void cmlRGBToData8   (const CMLColorMachine* cm, CMLOutput output, CMLInput rgb  , size_t count);
CML_API void cmlYCbCrToData8 (const CMLColorMachine* cm, CMLOutput output, CMLInput ycbcr, size_t count);
CML_API void cmlHSVToData8   (const CMLColorMachine* cm, CMLOutput output, CMLInput hsv  , size_t count);
CML_API void cmlHSLToData8   (const CMLColorMachine* cm, CMLOutput output, CMLInput hsl  , size_t count);
CML_API void cmlCMYKToData8  (const CMLColorMachine* cm, CMLOutput output, CMLInput cmyk , size_t count);

// 16-bit Output Conversions
CML_API void cmlGrayToData16 (const CMLColorMachine* cm, CMLOutput output, CMLInput gray , size_t count);
CML_API void cmlXYZToData16  (const CMLColorMachine* cm, CMLOutput output, CMLInput xyz  , size_t count);
CML_API void cmlYxyToData16  (const CMLColorMachine* cm, CMLOutput output, CMLInput yxy  , size_t count);
CML_API void cmlYuvToData16  (const CMLColorMachine* cm, CMLOutput output, CMLInput yuv  , size_t count);
CML_API void cmlYupvpToData16(const CMLColorMachine* cm, CMLOutput output, CMLInput yupvp, size_t count);
CML_API void cmlLabToData16  (const CMLColorMachine* cm, CMLOutput output, CMLInput lab  , size_t count);
CML_API void cmlLchToData16  (const CMLColorMachine* cm, CMLOutput output, CMLInput lch  , size_t count);
CML_API void cmlLuvToData16  (const CMLColorMachine* cm, CMLOutput output, CMLInput luv  , size_t count);
CML_API void cmlRGBToData16  (const CMLColorMachine* cm, CMLOutput output, CMLInput rgb  , size_t count);
CML_API void cmlYCbCrToData16(const CMLColorMachine* cm, CMLOutput output, CMLInput ycbcr, size_t count);
CML_API void cmlHSVToData16  (const CMLColorMachine* cm, CMLOutput output, CMLInput hsv  , size_t count);
CML_API void cmlHSLToData16  (const CMLColorMachine* cm, CMLOutput output, CMLInput hsl  , size_t count);
CML_API void cmlCMYKToData16 (const CMLColorMachine* cm, CMLOutput output, CMLInput cmyk , size_t count);



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
CML_API CMLNormedConverter cmlGetNormedInputConverter(CMLColorType colorType);
CML_API CMLNormedConverter cmlGetNormedOutputConverter(CMLColorType colorType);
// Note that those colortypes which are already in cartesian space will
// return the cartesian converter.
CML_API CMLNormedConverter cmlGetNormedCartesianInputConverter(CMLColorType colorType);
CML_API CMLNormedConverter cmlGetNormedCartesianOutputConverter(CMLColorType colorType);

// float Input Conversions from normed range [0,1]
CML_API void cmlNormedInputToGray  (CMLOutput gray  , CMLInput input, size_t count);
CML_API void cmlNormedInputToXYZ   (CMLOutput xyz   , CMLInput input, size_t count);
CML_API void cmlNormedInputToYxy   (CMLOutput yxy   , CMLInput input, size_t count);
CML_API void cmlNormedInputToYuv   (CMLOutput yuv   , CMLInput input, size_t count);
CML_API void cmlNormedInputToYupvp (CMLOutput yupvp , CMLInput input, size_t count);
CML_API void cmlNormedInputToLab   (CMLOutput lab   , CMLInput input, size_t count);
CML_API void cmlNormedInputToLch   (CMLOutput lch   , CMLInput input, size_t count);
CML_API void cmlNormedInputToLuv   (CMLOutput luv   , CMLInput input, size_t count);
CML_API void cmlNormedInputToRGB   (CMLOutput rgb   , CMLInput input, size_t count);
CML_API void cmlNormedInputToYCbCr (CMLOutput ycbcr , CMLInput input, size_t count);
CML_API void cmlNormedInputToHSV   (CMLOutput hsv   , CMLInput input, size_t count);
CML_API void cmlNormedInputToHSL   (CMLOutput hsl   , CMLInput input, size_t count);
CML_API void cmlNormedInputToCMYK  (CMLOutput cmyk  , CMLInput input, size_t count);

// Output Conversions to normed range [0,1]
CML_API void cmlGrayToNormedOutput (CMLOutput output, CMLInput gray , size_t count);
CML_API void cmlXYZToNormedOutput  (CMLOutput output, CMLInput xyz  , size_t count);
CML_API void cmlYxyToNormedOutput  (CMLOutput output, CMLInput yxy  , size_t count);
CML_API void cmlYuvToNormedOutput  (CMLOutput output, CMLInput yuv  , size_t count);
CML_API void cmlYupvpToNormedOutput(CMLOutput output, CMLInput yupvp, size_t count);
CML_API void cmlLabToNormedOutput  (CMLOutput output, CMLInput lab  , size_t count);
CML_API void cmlLchToNormedOutput  (CMLOutput output, CMLInput lch  , size_t count);
CML_API void cmlLuvToNormedOutput  (CMLOutput output, CMLInput luv  , size_t count);
CML_API void cmlRGBToNormedOutput  (CMLOutput output, CMLInput rgb  , size_t count);
CML_API void cmlYCbCrToNormedOutput(CMLOutput output, CMLInput ycbcr, size_t count);
CML_API void cmlHSVToNormedOutput  (CMLOutput output, CMLInput hsv  , size_t count);
CML_API void cmlHSLToNormedOutput  (CMLOutput output, CMLInput hsl  , size_t count);
CML_API void cmlCMYKToNormedOutput (CMLOutput output, CMLInput cmyk , size_t count);

// float Input Conversions from normed cartesian range [0,1]
CML_API void cmlNormedCartesianInputToLch   (CMLOutput lch   , CMLInput input, size_t count);
CML_API void cmlNormedCartesianInputToHSV   (CMLOutput hsv   , CMLInput input, size_t count);
CML_API void cmlNormedCartesianInputToHSL   (CMLOutput hsl   , CMLInput input, size_t count);

// Output Conversions to normed cartesian range [0,1]
CML_API void cmlLchToNormedCartesianOutput  (CMLOutput output, CMLInput lch  , size_t count);
CML_API void cmlHSVToNormedCartesianOutput  (CMLOutput output, CMLInput hsv  , size_t count);
CML_API void cmlHSLToNormedCartesianOutput  (CMLOutput output, CMLInput hsl  , size_t count);



// ////////////////////////////
// Inversion functions
// ////////////////////////////

// Use these to invert colors. Black becomes white and vice versa.
CML_API void cmlInvertGray   (CMLInputOutput gray , size_t count);
CML_API void cmlInvertXYZ    (CMLInputOutput xyz  , size_t count);
CML_API void cmlInvertYxy    (CMLInputOutput yxy  , size_t count);
CML_API void cmlInvertYuv    (CMLInputOutput yuv  , size_t count);
CML_API void cmlInvertYupvp  (CMLInputOutput yupvp, size_t count);
CML_API void cmlInvertLab    (CMLInputOutput lab  , size_t count);
CML_API void cmlInvertLch    (CMLInputOutput lch  , size_t count);
CML_API void cmlInvertLuv    (CMLInputOutput luv  , size_t count);
CML_API void cmlInvertRGB    (CMLInputOutput rgb  , size_t count);
CML_API void cmlInvertYCbCr  (CMLInputOutput ycbcr, size_t count);
CML_API void cmlInvertHSV    (CMLInputOutput hsv  , size_t count);
CML_API void cmlInvertHSL    (CMLInputOutput hsl  , size_t count);
CML_API void cmlInvertCMYK   (CMLInputOutput cmyk , size_t count);

// ////////////////////////////
// Clamp functions
// ////////////////////////////

// Use these to clamp colors. No value will be out of range.
CML_API void cmlClampGray  (CMLInputOutput gray , size_t count);
CML_API void cmlClampXYZ   (CMLInputOutput xyz  , size_t count);
CML_API void cmlClampYxy   (CMLInputOutput yxy  , size_t count);
CML_API void cmlClampYuv   (CMLInputOutput yuv  , size_t count);
CML_API void cmlClampYupvp (CMLInputOutput yupvp, size_t count);
CML_API void cmlClampLab   (CMLInputOutput lab  , size_t count);
CML_API void cmlClampLch   (CMLInputOutput lch  , size_t count);
CML_API void cmlClampLuv   (CMLInputOutput luv  , size_t count);
CML_API void cmlClampRGB   (CMLInputOutput rgb  , size_t count);
CML_API void cmlClampYCbCr (CMLInputOutput ycbcr, size_t count);
CML_API void cmlClampHSV   (CMLInputOutput hsv  , size_t count);
CML_API void cmlClampHSL   (CMLInputOutput hsl  , size_t count);
CML_API void cmlClampCMYK  (CMLInputOutput cmyk , size_t count);



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

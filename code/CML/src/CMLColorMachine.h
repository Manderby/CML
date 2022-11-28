
// This file contains the API for the ColorMachine structure.
//
// Note that this API is explicitely made for engineers who know what they are
// doing. If you are looking for a simple entry into color transformations,
// see the BaseAPI or the ColorClasses.



// ///////////////////////////////////////////////
// State Machine
// ///////////////////////////////////////////////

// Returns the current version number.
CML_API int                   cmlGetVersion(void);

// Create and destroy ColorMachines with these functions:
CML_API CMLColorMachine*      cmlCreateColorMachine(void);
CML_API void                  cmlReleaseColorMachine(CMLColorMachine* cm);

// If you have multiple state changes to set, lock the recomputation, set all
// desired values and release the recomputation. Doing so, the ColorMachine
// will only perform all necessary recomputations once and only once.
CML_API void                  cmlLockRecomputation(CMLColorMachine* cm);
CML_API void                  cmlReleaseRecomputation(CMLColorMachine* cm);

// The integration method defines how integration (for example for spectral
// functions) will be computed. There is a simple method which is commonly
// used in many other color implementations or a more accurate and faster
// computation called "Binary Pairs" which is the default for CML.
// The stepSize denotes the delta-Lambda which is used when continuous
// functions need to be integrated.
CML_API CMLIntegrationMethod  cmlGetIntegrationMethod(const CMLColorMachine* cm);
CML_API void                  cmlSetIntegrationMethod(CMLColorMachine* cm, CMLIntegrationMethod integrationMethod);
CML_API float                 cmlGetIntegrationStepSize(const CMLColorMachine* cm);
CML_API void                  cmlSetIntegrationStepSize(CMLColorMachine* cm, float stepSize);

// The integer mapping defines, how floats are mapped to integers.
// Additionally, integers can have lower and upper cutoffs. This means that
// the minimal float values are mapped to the lower cutoffs and the maximal
// float values are mapped to the upper cutoffs. You can define cutoffs for
// channels up to CML_MAX_NUMBER_OF_CHANNELS. Note that cutoffs may also be
// negative.
CML_API CMLIntegerMappingType cmlGetIntegerMappingType(const CMLColorMachine* cm);
CML_API void                  cmlSetIntegerMappingType(CMLColorMachine* cm, CMLIntegerMappingType type);
CML_API void                  cmlGet8BitCutoffs(const CMLColorMachine* cm, uint8* min, uint8* max, size_t channel);
CML_API void                  cmlSet8BitCutoffs(CMLColorMachine* cm, uint8 min, uint8 max, size_t channel);
CML_API void                  cmlGet16BitCutoffs(const CMLColorMachine* cm, uint16* min, uint16* max, size_t channel);
CML_API void                  cmlSet16BitCutoffs(CMLColorMachine* cm, uint16 min, uint16 max, size_t channel);

// The observer defines if the 2 degree or the 10 degree model and what data
// set is used. Initial setting is 2 degrees of CIE recommendation.
CML_API CMLObserverType       cmlGetObserverType(const CMLColorMachine* cm);
CML_API float                 cmlGetRadiometricScale(const CMLColorMachine* cm);
CML_API float                 cmlGetColorimetricBase(const CMLColorMachine* cm);
CML_API void                  cmlSetColorimetricBase(CMLColorMachine* cm, float colorimetricBase);
CML_API void                  cmlSetObserverType(CMLColorMachine* cm, CMLObserverType type);
CML_API const CMLFunction*    cmlGetSpecDistFunction(const CMLColorMachine* cm, int index);
CML_API void                  cmlGetSpectralXYZColor(const CMLColorMachine* cm, CMLVec3 xyz, float lambda);

CML_API CMLIlluminationType   cmlGetIlluminationType(const CMLColorMachine* cm);
CML_API const CMLFunction*    cmlGetIlluminationSpectrum(const CMLColorMachine* cm);
CML_API const float*          cmlGetWhitePointXYZ(const CMLColorMachine* cm);
CML_API const float*          cmlGetWhitePointXYZInverse(const CMLColorMachine* cm);
CML_API const float*          cmlGetWhitePointYxy(const CMLColorMachine* cm);
CML_API const float*          cmlGetWhitePointYupvp(const CMLColorMachine* cm);
CML_API const float*          cmlGetWhitePointYuv(const CMLColorMachine* cm);

// The illumination defines the current illumination assumed. This includes
// the whitePoint. Initial setting is the standard illumination of the
// standard RGB colorspace, which for sRGB is D65.
// Note that setting the RGB ColorSpace will set the illumination implicitely
// by default.
CML_API void                  cmlSetIlluminationType(CMLColorMachine* cm, CMLIlluminationType illuminationType);
// Returns the stored temperature for all standard illuminations, D illuminants
// and blackbody curves. Retuns 0 for custom spectra and custom whitepoint. Use
// cmlGetCorrelatedColorTemperature to compute the correlated temperature using
// the Robertos method.
CML_API float                 cmlGetIlluminationTemperature(const CMLColorMachine* cm);
// The setIlluminationTemperature method will only take effect with
// the Blackbody and custom D illuminant. Otherwise, the input is ignored.
CML_API void                  cmlSetIlluminationTemperature(CMLColorMachine* cm, float temp);
CML_API void                  cmlSetIlluminationSpectrum(CMLColorMachine* cm, const CMLFunction* spectrum);
CML_API void                  cmlSetReferenceWhitePointYxy(CMLColorMachine* cm, const float* yxy);

// These functions set the computation of the Lab space. Default is CIELAB.
// The functions setting K and ke will only take effect if the
// labSpace is set to CML_LAB_ADAMS_CROMATIC_VALENCE. Otherwise, the input
// is ignored. When setting a custom response, the gamma parameter will only
// be used with gamma responses.
// Be aware that most Lab spaces (including CIELAB) are relative to a specific
// whitePoint which in CML is defined by the current illumination.
CML_API CMLLabColorSpaceType    cmlGetLabColorSpace(const CMLColorMachine* cm);
CML_API void                    cmlSetLabColorSpace(CMLColorMachine* cm, CMLLabColorSpaceType labSpace);
CML_API void                    cmlGetAdamsChromaticityValenceParameters(CMLColorMachine* cm, float* K, float* ke);
CML_API void                    cmlSetAdamsChromaticityValenceParameters(CMLColorMachine* cm, float K, float ke);
CML_API uint8                   cmlGetLabLUTSize(const CMLColorMachine* cm);
CML_API void                    cmlSetLabLUTSize(CMLColorMachine* cm, uint8 bits);
CML_API const CMLFunction*      cmlGetLtoLinearResponse(const CMLColorMachine* cm);
CML_API const CMLFunction*      cmlGetLineartoLResponse(const CMLColorMachine* cm);
CML_API const CMLResponseCurve* cmlGetResponseL(CMLColorMachine* cm);
CML_API void                    cmlSetResponseL(CMLColorMachine* cm, CMLResponseCurve* response);
CML_API void                    cmlSetDeltaEComputation(CMLColorMachine* cm, CMLDeltaEComputationType computation);
// There exist different Delta-E computations, simple and complex ones.
// Initial setting is Delta-E-1976 (the euclidian distance).
// After setting the compuation model, all subsequent delta-E computations
// will be computed accordingly.
CML_API float                 deltaE(CMLColorMachine* cm, const float* CML_RESTRICT lab1, const float* CML_RESTRICT lab2);

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
typedef struct GammaLinearInputParameters{
  float gamma;
  float offset;
  float linScale;
  float split;
} GammaLinearInputParameters;

CML_API CMLRGBColorSpaceType    cmlGetRGBColorSpaceType(const CMLColorMachine* cm);
CML_API void                    cmlSetRGBColorSpaceType(CMLColorMachine* cm, CMLRGBColorSpaceType type);
CML_API void                    cmlGetRGBPrimariesYxy(const CMLColorMachine* cm, CMLVec3 primaries[3]);
CML_API void                    cmlSetRGBPrimariesYxy(CMLColorMachine* cm, CMLVec3 primaries[3]);
CML_DEF void                    cmlGetCustomGammaLinearParametersRGB(CMLColorMachine* cm, GammaLinearInputParameters parameters[3]);
CML_API void                    cmlSetCustomGammaLinearParametersRGB(CMLColorMachine* cm, const GammaLinearInputParameters* parameters);
CML_API void                    cmlGetRGBResponseTypes(const CMLColorMachine* cm, CMLResponseCurveType types[3]);
CML_API const CMLResponseCurve* cmlGetResponseR(CMLColorMachine* cm);
CML_API const CMLResponseCurve* cmlGetResponseG(CMLColorMachine* cm);
CML_API const CMLResponseCurve* cmlGetResponseB(CMLColorMachine* cm);
CML_API const GammaLinearInputParameters* cmlGetCustomGammaLinearParametersR(const CMLColorMachine* cm);
CML_API const GammaLinearInputParameters* cmlGetCustomGammaLinearParametersG(const CMLColorMachine* cm);
CML_API const GammaLinearInputParameters* cmlGetCustomGammaLinearParametersB(const CMLColorMachine* cm);
CML_API void                   cmlSetResponseRGB(CMLColorMachine* cm, CMLResponseCurve* response);
CML_API void                   cmlSetResponseR(CMLColorMachine* cm, CMLResponseCurve* response);
CML_API void                   cmlSetResponseG(CMLColorMachine* cm, CMLResponseCurve* response);
CML_API void                   cmlSetResponseB(CMLColorMachine* cm, CMLResponseCurve* response);
CML_API uint8                  cmlGetRGBLUTSize(const CMLColorMachine* cm);
CML_API void                   cmlSetRGBLUTSize(CMLColorMachine* cm, uint8 bits);


// Transformation from RGB to CMYK can be achieved using different approaches
// like UCR, GCR or standard transform. Currently, only UCR and standard
// transform is implemented.
// Initial setting is standard transform.
CML_API cml_CMYKTransformType  cmlGetCMYKTransform(const CMLColorMachine* cm);
CML_API void                  cmlSetCMYKTransform(CMLColorMachine* cm, cml_CMYKTransformType transform);

// Transformation from any Color to Gray and vice versa can be achieved using
// different approaches. Initial setting is the computation from the
// L* value (CIELAB).
CML_API CMLGrayComputationType  cmlGetGrayComputationType(const CMLColorMachine* cm);
CML_API void                    cmlSetGrayComputationType(CMLColorMachine* cm, CMLGrayComputationType computation);



// ///////////////////////////////////////////////
// Color conversions
//
// Using ColorMachines, you can convert any color into any other with the
// following conversion functions. You can also get a function pointer to
// one of these conversion function using the cmlGetColorConverter function.
// ///////////////////////////////////////////////

CML_API CMLColorConverter     cmlGetColorConverter(CMLColorType outputSystem, CMLColorType inputSystem);

// CMYK Conversions
CML_API void cmlCMYKToCMYK  (const CMLColorMachine* cm, CMLOutput cmykd, CMLInput cmyks, size_t count);
CML_API void cmlCMYKToGray  (const CMLColorMachine* cm, CMLOutput gray,  CMLInput cmyk,  size_t count);
CML_API void cmlCMYKToHSL   (const CMLColorMachine* cm, CMLOutput hsl,   CMLInput cmyk,  size_t count);
CML_API void cmlCMYKToHSV   (const CMLColorMachine* cm, CMLOutput hsv,   CMLInput cmyk,  size_t count);
CML_API void cmlCMYKToLab   (const CMLColorMachine* cm, CMLOutput lab,   CMLInput cmyk,  size_t count);
CML_API void cmlCMYKToLch   (const CMLColorMachine* cm, CMLOutput lch,   CMLInput cmyk,  size_t count);
CML_API void cmlCMYKToLuv   (const CMLColorMachine* cm, CMLOutput luv,   CMLInput cmyk,  size_t count);
CML_API void cmlCMYKToRGB   (const CMLColorMachine* cm, CMLOutput rgb,   CMLInput cmyk,  size_t count);
CML_API void cmlCMYKToUVW   (const CMLColorMachine* cm, CMLOutput uvw,   CMLInput cmyk,  size_t count);
CML_API void cmlCMYKToXYZ   (const CMLColorMachine* cm, CMLOutput xyz,   CMLInput cmyk,  size_t count);
CML_API void cmlCMYKToYCbCr (const CMLColorMachine* cm, CMLOutput ycbcr, CMLInput cmyk,  size_t count);
CML_API void cmlCMYKToYcd   (const CMLColorMachine* cm, CMLOutput ycd,   CMLInput cmyk,  size_t count);
CML_API void cmlCMYKToYupvp (const CMLColorMachine* cm, CMLOutput yupvp, CMLInput cmyk,  size_t count);
CML_API void cmlCMYKToYuv   (const CMLColorMachine* cm, CMLOutput yuv,   CMLInput cmyk,  size_t count);
CML_API void cmlCMYKToYxy   (const CMLColorMachine* cm, CMLOutput yxy,   CMLInput cmyk,  size_t count);

// Gray Conversions
CML_API void cmlGrayToGray  (const CMLColorMachine* cm, CMLOutput grayd, CMLInput grays, size_t count);
CML_API void cmlGrayToCMYK  (const CMLColorMachine* cm, CMLOutput cmyk,  CMLInput gray,  size_t count);
CML_API void cmlGrayToHSL   (const CMLColorMachine* cm, CMLOutput hsl,   CMLInput gray,  size_t count);
CML_API void cmlGrayToHSV   (const CMLColorMachine* cm, CMLOutput hsv,   CMLInput gray,  size_t count);
CML_API void cmlGrayToLab   (const CMLColorMachine* cm, CMLOutput lab,   CMLInput gray,  size_t count);
CML_API void cmlGrayToLch   (const CMLColorMachine* cm, CMLOutput lch,   CMLInput gray,  size_t count);
CML_API void cmlGrayToLuv   (const CMLColorMachine* cm, CMLOutput luv,   CMLInput gray,  size_t count);
CML_API void cmlGrayToRGB   (const CMLColorMachine* cm, CMLOutput rgb,   CMLInput gray,  size_t count);
CML_API void cmlGrayToUVW   (const CMLColorMachine* cm, CMLOutput uvw,   CMLInput gray,  size_t count);
CML_API void cmlGrayToXYZ   (const CMLColorMachine* cm, CMLOutput xyz,   CMLInput gray,  size_t count);
CML_API void cmlGrayToYCbCr (const CMLColorMachine* cm, CMLOutput ycbcr, CMLInput gray,  size_t count);
CML_API void cmlGrayToYcd   (const CMLColorMachine* cm, CMLOutput ycd,   CMLInput gray,  size_t count);
CML_API void cmlGrayToYupvp (const CMLColorMachine* cm, CMLOutput yupvp, CMLInput gray,  size_t count);
CML_API void cmlGrayToYuv   (const CMLColorMachine* cm, CMLOutput yuv,   CMLInput gray,  size_t count);
CML_API void cmlGrayToYxy   (const CMLColorMachine* cm, CMLOutput yxy,   CMLInput gray,  size_t count);

// HSL Conversions
CML_API void cmlHSLToCMYK   (const CMLColorMachine* cm, CMLOutput cmyk,  CMLInput hsl,  size_t count);
CML_API void cmlHSLToGray   (const CMLColorMachine* cm, CMLOutput gray,  CMLInput hsl,  size_t count);
CML_API void cmlHSLToHSL    (const CMLColorMachine* cm, CMLOutput hsld,  CMLInput hsls, size_t count);
CML_API void cmlHSLToHSV    (const CMLColorMachine* cm, CMLOutput hsv,   CMLInput hsl,  size_t count);
CML_API void cmlHSLToLab    (const CMLColorMachine* cm, CMLOutput lab,   CMLInput hsl,  size_t count);
CML_API void cmlHSLToLch    (const CMLColorMachine* cm, CMLOutput lch,   CMLInput hsl,  size_t count);
CML_API void cmlHSLToLuv    (const CMLColorMachine* cm, CMLOutput luv,   CMLInput hsl,  size_t count);
CML_API void cmlHSLToRGB    (const CMLColorMachine* cm, CMLOutput rgb,   CMLInput hsl,  size_t count);
CML_API void cmlHSLToUVW    (const CMLColorMachine* cm, CMLOutput uvw,   CMLInput hsl,  size_t count);
CML_API void cmlHSLToXYZ    (const CMLColorMachine* cm, CMLOutput xyz,   CMLInput hsl,  size_t count);
CML_API void cmlHSLToYCbCr  (const CMLColorMachine* cm, CMLOutput ycbcr, CMLInput hsl,  size_t count);
CML_API void cmlHSLToYcd    (const CMLColorMachine* cm, CMLOutput ycd,   CMLInput hsl,  size_t count);
CML_API void cmlHSLToYupvp  (const CMLColorMachine* cm, CMLOutput yupvp, CMLInput hsl,  size_t count);
CML_API void cmlHSLToYuv    (const CMLColorMachine* cm, CMLOutput yuv,   CMLInput hsl,  size_t count);
CML_API void cmlHSLToYxy    (const CMLColorMachine* cm, CMLOutput yxy,   CMLInput hsl,  size_t count);

// HSV Conversions
CML_API void cmlHSVToCMYK   (const CMLColorMachine* cm, CMLOutput cmyk,  CMLInput hsv,  size_t count);
CML_API void cmlHSVToGray   (const CMLColorMachine* cm, CMLOutput gray,  CMLInput hsv,  size_t count);
CML_API void cmlHSVToHSL    (const CMLColorMachine* cm, CMLOutput hsl,   CMLInput hsv,  size_t count);
CML_API void cmlHSVToHSV    (const CMLColorMachine* cm, CMLOutput hsvd,  CMLInput hsvs, size_t count);
CML_API void cmlHSVToLab    (const CMLColorMachine* cm, CMLOutput lab,   CMLInput hsv,  size_t count);
CML_API void cmlHSVToLch    (const CMLColorMachine* cm, CMLOutput lch,   CMLInput hsv,  size_t count);
CML_API void cmlHSVToLuv    (const CMLColorMachine* cm, CMLOutput luv,   CMLInput hsv,  size_t count);
CML_API void cmlHSVToRGB    (const CMLColorMachine* cm, CMLOutput rgb,   CMLInput hsv,  size_t count);
CML_API void cmlHSVToUVW    (const CMLColorMachine* cm, CMLOutput uvw,   CMLInput hsv,  size_t count);
CML_API void cmlHSVToXYZ    (const CMLColorMachine* cm, CMLOutput xyz,   CMLInput hsv,  size_t count);
CML_API void cmlHSVToYCbCr  (const CMLColorMachine* cm, CMLOutput ycbcr, CMLInput hsv,  size_t count);
CML_API void cmlHSVToYcd    (const CMLColorMachine* cm, CMLOutput ycd,   CMLInput hsv,  size_t count);
CML_API void cmlHSVToYupvp  (const CMLColorMachine* cm, CMLOutput yupvp, CMLInput hsv,  size_t count);
CML_API void cmlHSVToYuv    (const CMLColorMachine* cm, CMLOutput yuv,   CMLInput hsv,  size_t count);
CML_API void cmlHSVToYxy    (const CMLColorMachine* cm, CMLOutput yxy,   CMLInput hsv,  size_t count);

// Lab Conversions
CML_API void cmlLabToCMYK   (const CMLColorMachine* cm, CMLOutput cmyk,  CMLInput lab,  size_t count);
CML_API void cmlLabToGray   (const CMLColorMachine* cm, CMLOutput gray,  CMLInput lab,  size_t count);
CML_API void cmlLabToHSL    (const CMLColorMachine* cm, CMLOutput hsl,   CMLInput lab,  size_t count);
CML_API void cmlLabToHSV    (const CMLColorMachine* cm, CMLOutput hsv,   CMLInput lab,  size_t count);
CML_API void cmlLabToLab    (const CMLColorMachine* cm, CMLOutput labd,  CMLInput labs, size_t count);
CML_API void cmlLabToLch    (const CMLColorMachine* cm, CMLOutput lch,   CMLInput lab,  size_t count);
CML_API void cmlLabToLuv    (const CMLColorMachine* cm, CMLOutput luv,   CMLInput lab,  size_t count);
CML_API void cmlLabToRGB    (const CMLColorMachine* cm, CMLOutput rgb,   CMLInput lab,  size_t count);
CML_API void cmlLabToUVW    (const CMLColorMachine* cm, CMLOutput uvw,   CMLInput lab,  size_t count);
CML_API void cmlLabToXYZ    (const CMLColorMachine* cm, CMLOutput xyz,   CMLInput lab,  size_t count);
CML_API void cmlLabToYCbCr  (const CMLColorMachine* cm, CMLOutput ycbcr, CMLInput lab,  size_t count);
CML_API void cmlLabToYcd    (const CMLColorMachine* cm, CMLOutput ycd,   CMLInput lab,  size_t count);
CML_API void cmlLabToYupvp  (const CMLColorMachine* cm, CMLOutput yupvp, CMLInput lab,  size_t count);
CML_API void cmlLabToYuv    (const CMLColorMachine* cm, CMLOutput yuv,   CMLInput lab,  size_t count);
CML_API void cmlLabToYxy    (const CMLColorMachine* cm, CMLOutput yxy,   CMLInput lab,  size_t count);

// Lch Conversions
CML_API void cmlLchToCMYK   (const CMLColorMachine* cm, CMLOutput cmyk,  CMLInput lch,  size_t count);
CML_API void cmlLchToGray   (const CMLColorMachine* cm, CMLOutput gray,  CMLInput lch,  size_t count);
CML_API void cmlLchToHSV    (const CMLColorMachine* cm, CMLOutput hsv,   CMLInput lch,  size_t count);
CML_API void cmlLchToHSL    (const CMLColorMachine* cm, CMLOutput hsl,   CMLInput lch,  size_t count);
CML_API void cmlLchToLab    (const CMLColorMachine* cm, CMLOutput lab,   CMLInput lch,  size_t count);
CML_API void cmlLchToLch    (const CMLColorMachine* cm, CMLOutput lchd,  CMLInput lchs, size_t count);
CML_API void cmlLchToLuv    (const CMLColorMachine* cm, CMLOutput luv,   CMLInput lch,  size_t count);
CML_API void cmlLchToRGB    (const CMLColorMachine* cm, CMLOutput rgb,   CMLInput lch,  size_t count);
CML_API void cmlLchToUVW    (const CMLColorMachine* cm, CMLOutput uvw,   CMLInput lch,  size_t count);
CML_API void cmlLchToXYZ    (const CMLColorMachine* cm, CMLOutput xyz,   CMLInput lch,  size_t count);
CML_API void cmlLchToYCbCr  (const CMLColorMachine* cm, CMLOutput ycbcr, CMLInput lch,  size_t count);
CML_API void cmlLchToYcd    (const CMLColorMachine* cm, CMLOutput ycd,   CMLInput lch,  size_t count);
CML_API void cmlLchToYupvp  (const CMLColorMachine* cm, CMLOutput yupvp, CMLInput lch,  size_t count);
CML_API void cmlLchToYuv    (const CMLColorMachine* cm, CMLOutput yuv,   CMLInput lch,  size_t count);
CML_API void cmlLchToYxy    (const CMLColorMachine* cm, CMLOutput yxy,   CMLInput lch,  size_t count);

// Luv Conversions
CML_API void cmlLuvToGray   (const CMLColorMachine* cm, CMLOutput gray,  CMLInput luv,  size_t count);
CML_API void cmlLuvToCMYK   (const CMLColorMachine* cm, CMLOutput cmyk,  CMLInput luv,  size_t count);
CML_API void cmlLuvToHSL    (const CMLColorMachine* cm, CMLOutput hsl,   CMLInput luv,  size_t count);
CML_API void cmlLuvToHSV    (const CMLColorMachine* cm, CMLOutput hsv,   CMLInput luv,  size_t count);
CML_API void cmlLuvToLab    (const CMLColorMachine* cm, CMLOutput lab,   CMLInput luv,  size_t count);
CML_API void cmlLuvToLch    (const CMLColorMachine* cm, CMLOutput lch,   CMLInput luv,  size_t count);
CML_API void cmlLuvToLuv    (const CMLColorMachine* cm, CMLOutput luvd,  CMLInput luvs, size_t count);
CML_API void cmlLuvToRGB    (const CMLColorMachine* cm, CMLOutput rgb,   CMLInput luv,  size_t count);
CML_API void cmlLuvToUVW    (const CMLColorMachine* cm, CMLOutput uvw,   CMLInput luv,  size_t count);
CML_API void cmlLuvToXYZ    (const CMLColorMachine* cm, CMLOutput xyz,   CMLInput luv,  size_t count);
CML_API void cmlLuvToYCbCr  (const CMLColorMachine* cm, CMLOutput ycbcr, CMLInput luv,  size_t count);
CML_API void cmlLuvToYcd    (const CMLColorMachine* cm, CMLOutput ycd,   CMLInput luv,  size_t count);
CML_API void cmlLuvToYupvp  (const CMLColorMachine* cm, CMLOutput yupvp, CMLInput luv,  size_t count);
CML_API void cmlLuvToYuv    (const CMLColorMachine* cm, CMLOutput yuv,   CMLInput luv,  size_t count);
CML_API void cmlLuvToYxy    (const CMLColorMachine* cm, CMLOutput yxy,   CMLInput luv,  size_t count);

// RGB Conversions
CML_API void cmlRGBToGray   (const CMLColorMachine* cm, CMLOutput gray,  CMLInput rgb,  size_t count);
CML_API void cmlRGBToCMYK   (const CMLColorMachine* cm, CMLOutput cmyk,  CMLInput rgb,  size_t count);
CML_API void cmlRGBToHSL    (const CMLColorMachine* cm, CMLOutput hsl,   CMLInput rgb,  size_t count);
CML_API void cmlRGBToHSV    (const CMLColorMachine* cm, CMLOutput hsv,   CMLInput rgb,  size_t count);
CML_API void cmlRGBToLab    (const CMLColorMachine* cm, CMLOutput lab,   CMLInput rgb,  size_t count);
CML_API void cmlRGBToLch    (const CMLColorMachine* cm, CMLOutput lch,   CMLInput rgb,  size_t count);
CML_API void cmlRGBToLuv    (const CMLColorMachine* cm, CMLOutput luv,   CMLInput rgb,  size_t count);
CML_API void cmlRGBToRGB    (const CMLColorMachine* cm, CMLOutput rgbd,  CMLInput rgbs, size_t count);
CML_API void cmlRGBToUVW    (const CMLColorMachine* cm, CMLOutput uvw,   CMLInput rgb,  size_t count);
CML_API void cmlRGBToXYZ    (const CMLColorMachine* cm, CMLOutput xyz,   CMLInput rgb,  size_t count);
CML_API void cmlRGBToYCbCr  (const CMLColorMachine* cm, CMLOutput ycbcr, CMLInput rgb,  size_t count);
CML_API void cmlRGBToYcd    (const CMLColorMachine* cm, CMLOutput ycd,   CMLInput rgb,  size_t count);
CML_API void cmlRGBToYupvp  (const CMLColorMachine* cm, CMLOutput yupvp, CMLInput rgb,  size_t count);
CML_API void cmlRGBToYuv    (const CMLColorMachine* cm, CMLOutput yuv,   CMLInput rgb,  size_t count);
CML_API void cmlRGBToYxy    (const CMLColorMachine* cm, CMLOutput yxy,   CMLInput rgb,  size_t count);

// Spectrum Illumination Conversions
CML_API void cmlSpectrumIlluminationToCMYK  (const CMLColorMachine* cm, CMLOutput cmyk,  CMLInput specIll, size_t count);
CML_API void cmlSpectrumIlluminationToGray  (const CMLColorMachine* cm, CMLOutput gray,  CMLInput specIll, size_t count);
CML_API void cmlSpectrumIlluminationToHSL   (const CMLColorMachine* cm, CMLOutput hsl,   CMLInput specIll, size_t count);
CML_API void cmlSpectrumIlluminationToHSV   (const CMLColorMachine* cm, CMLOutput hsv,   CMLInput specIll, size_t count);
CML_API void cmlSpectrumIlluminationToLab   (const CMLColorMachine* cm, CMLOutput lab,   CMLInput specIll, size_t count);
CML_API void cmlSpectrumIlluminationToLch   (const CMLColorMachine* cm, CMLOutput lch,   CMLInput specIll, size_t count);
CML_API void cmlSpectrumIlluminationToLuv   (const CMLColorMachine* cm, CMLOutput luv,   CMLInput specIll, size_t count);
CML_API void cmlSpectrumIlluminationToRGB   (const CMLColorMachine* cm, CMLOutput rgb,   CMLInput specIll, size_t count);
CML_API void cmlSpectrumIlluminationToUVW   (const CMLColorMachine* cm, CMLOutput uvw,   CMLInput specIll, size_t count);
CML_API void cmlSpectrumIlluminationToXYZ   (const CMLColorMachine* cm, CMLOutput xyz,   CMLInput specIll, size_t count);
CML_API void cmlSpectrumIlluminationToYCbCr (const CMLColorMachine* cm, CMLOutput ycbcr, CMLInput specIll, size_t count);
CML_API void cmlSpectrumIlluminationToYcd   (const CMLColorMachine* cm, CMLOutput ycd,   CMLInput specIll, size_t count);
CML_API void cmlSpectrumIlluminationToYupvp (const CMLColorMachine* cm, CMLOutput yupvp, CMLInput specIll, size_t count);
CML_API void cmlSpectrumIlluminationToYuv   (const CMLColorMachine* cm, CMLOutput yuv,   CMLInput specIll, size_t count);
CML_API void cmlSpectrumIlluminationToYxy   (const CMLColorMachine* cm, CMLOutput yxy,   CMLInput specIll, size_t count);

// Spectrum Remission Conversions
CML_API void cmlSpectrumRemissionToCMYK  (const CMLColorMachine* cm, CMLOutput cmyk,  CMLInput specRem, size_t count);
CML_API void cmlSpectrumRemissionToGray  (const CMLColorMachine* cm, CMLOutput gray,  CMLInput specRem, size_t count);
CML_API void cmlSpectrumRemissionToHSL   (const CMLColorMachine* cm, CMLOutput hsl,   CMLInput specRem, size_t count);
CML_API void cmlSpectrumRemissionToHSV   (const CMLColorMachine* cm, CMLOutput hsv,   CMLInput specRem, size_t count);
CML_API void cmlSpectrumRemissionToLab   (const CMLColorMachine* cm, CMLOutput lab,   CMLInput specRem, size_t count);
CML_API void cmlSpectrumRemissionToLch   (const CMLColorMachine* cm, CMLOutput lch,   CMLInput specRem, size_t count);
CML_API void cmlSpectrumRemissionToLuv   (const CMLColorMachine* cm, CMLOutput luv,   CMLInput specRem, size_t count);
CML_API void cmlSpectrumRemissionToRGB   (const CMLColorMachine* cm, CMLOutput rgb,   CMLInput specRem, size_t count);
CML_API void cmlSpectrumRemissionToUVW   (const CMLColorMachine* cm, CMLOutput uvw,   CMLInput specRem, size_t count);
CML_API void cmlSpectrumRemissionToXYZ   (const CMLColorMachine* cm, CMLOutput xyz,   CMLInput specRem, size_t count);
CML_API void cmlSpectrumRemissionToYCbCr (const CMLColorMachine* cm, CMLOutput ycbcr, CMLInput specRem, size_t count);
CML_API void cmlSpectrumRemissionToYcd   (const CMLColorMachine* cm, CMLOutput ycd,   CMLInput specRem, size_t count);
CML_API void cmlSpectrumRemissionToYupvp (const CMLColorMachine* cm, CMLOutput yupvp, CMLInput specRem, size_t count);
CML_API void cmlSpectrumRemissionToYuv   (const CMLColorMachine* cm, CMLOutput yuv,   CMLInput specRem, size_t count);
CML_API void cmlSpectrumRemissionToYxy   (const CMLColorMachine* cm, CMLOutput yxy,   CMLInput specRem, size_t count);

// UVW Conversions
CML_API void cmlUVWToCMYK   (const CMLColorMachine* cm, CMLOutput cmyk,  CMLInput uvw,  size_t count);
CML_API void cmlUVWToGray   (const CMLColorMachine* cm, CMLOutput gray,  CMLInput uvw,  size_t count);
CML_API void cmlUVWToHSL    (const CMLColorMachine* cm, CMLOutput hsl,   CMLInput uvw,  size_t count);
CML_API void cmlUVWToHSV    (const CMLColorMachine* cm, CMLOutput hsv,   CMLInput uvw,  size_t count);
CML_API void cmlUVWToLab    (const CMLColorMachine* cm, CMLOutput lab,   CMLInput uvw,  size_t count);
CML_API void cmlUVWToLch    (const CMLColorMachine* cm, CMLOutput lch,   CMLInput uvw,  size_t count);
CML_API void cmlUVWToLuv    (const CMLColorMachine* cm, CMLOutput luv,   CMLInput uvw,  size_t count);
CML_API void cmlUVWToRGB    (const CMLColorMachine* cm, CMLOutput rgb,   CMLInput uvw,  size_t count);
CML_API void cmlUVWToUVW    (const CMLColorMachine* cm, CMLOutput uvwd,  CMLInput uvws, size_t count);
CML_API void cmlUVWToXYZ    (const CMLColorMachine* cm, CMLOutput xyz,   CMLInput uvw,  size_t count);
CML_API void cmlUVWToYCbCr  (const CMLColorMachine* cm, CMLOutput ycbcr, CMLInput uvw,  size_t count);
CML_API void cmlUVWToYcd    (const CMLColorMachine* cm, CMLOutput ycd,   CMLInput uvw,  size_t count);
CML_API void cmlUVWToYupvp  (const CMLColorMachine* cm, CMLOutput yupvp, CMLInput uvw,  size_t count);
CML_API void cmlUVWToYuv    (const CMLColorMachine* cm, CMLOutput yuv,   CMLInput uvw,  size_t count);
CML_API void cmlUVWToYxy    (const CMLColorMachine* cm, CMLOutput yxy,   CMLInput uvw,  size_t count);

// XYZ Conversions
CML_API void cmlXYZToCMYK   (const CMLColorMachine* cm, CMLOutput cmyk,  CMLInput xyz,  size_t count);
CML_API void cmlXYZToGray   (const CMLColorMachine* cm, CMLOutput gray,  CMLInput xyz,  size_t count);
CML_API void cmlXYZToHSL    (const CMLColorMachine* cm, CMLOutput hsl,   CMLInput xyz,  size_t count);
CML_API void cmlXYZToHSV    (const CMLColorMachine* cm, CMLOutput hsv,   CMLInput xyz,  size_t count);
CML_API void cmlXYZToLab    (const CMLColorMachine* cm, CMLOutput lab,   CMLInput xyz,  size_t count);
CML_API void cmlXYZToLch    (const CMLColorMachine* cm, CMLOutput lch,   CMLInput xyz,  size_t count);
CML_API void cmlXYZToLuv    (const CMLColorMachine* cm, CMLOutput luv,   CMLInput xyz,  size_t count);
CML_API void cmlXYZToRGB    (const CMLColorMachine* cm, CMLOutput rgb,   CMLInput xyz,  size_t count);
CML_API void cmlXYZToUVW    (const CMLColorMachine* cm, CMLOutput uvw,   CMLInput xyz,  size_t count);
CML_API void cmlXYZToXYZ    (const CMLColorMachine* cm, CMLOutput xyzd,  CMLInput xyzs, size_t count);
CML_API void cmlXYZToYCbCr  (const CMLColorMachine* cm, CMLOutput ycbcr, CMLInput xyz,  size_t count);
CML_API void cmlXYZToYcd    (const CMLColorMachine* cm, CMLOutput ycd,   CMLInput xyz,  size_t count);
CML_API void cmlXYZToYupvp  (const CMLColorMachine* cm, CMLOutput yupvp, CMLInput xyz,  size_t count);
CML_API void cmlXYZToYuv    (const CMLColorMachine* cm, CMLOutput yuv,   CMLInput xyz,  size_t count);
CML_API void cmlXYZToYxy    (const CMLColorMachine* cm, CMLOutput yxy,   CMLInput xyz,  size_t count);

// YCbCr Conversions
CML_API void cmlYCbCrToCMYK (const CMLColorMachine* cm, CMLOutput cmyk,   CMLInput ycbcr,  size_t count);
CML_API void cmlYCbCrToGray (const CMLColorMachine* cm, CMLOutput gray,   CMLInput ycbcr,  size_t count);
CML_API void cmlYCbCrToHSL  (const CMLColorMachine* cm, CMLOutput hsl,    CMLInput ycbcr,  size_t count);
CML_API void cmlYCbCrToHSV  (const CMLColorMachine* cm, CMLOutput hsv,    CMLInput ycbcr,  size_t count);
CML_API void cmlYCbCrToLab  (const CMLColorMachine* cm, CMLOutput lab,    CMLInput ycbcr,  size_t count);
CML_API void cmlYCbCrToLch  (const CMLColorMachine* cm, CMLOutput lch,    CMLInput ycbcr,  size_t count);
CML_API void cmlYCbCrToLuv  (const CMLColorMachine* cm, CMLOutput luv,    CMLInput ycbcr,  size_t count);
CML_API void cmlYCbCrToRGB  (const CMLColorMachine* cm, CMLOutput rgb,    CMLInput ycbcr,  size_t count);
CML_API void cmlYCbCrToUVW  (const CMLColorMachine* cm, CMLOutput uvw,    CMLInput ycbcr,  size_t count);
CML_API void cmlYCbCrToXYZ  (const CMLColorMachine* cm, CMLOutput xyz,    CMLInput ycbcr,  size_t count);
CML_API void cmlYCbCrToYCbCr(const CMLColorMachine* cm, CMLOutput ycbcrd, CMLInput ycbcrs, size_t count);
CML_API void cmlYCbCrToYcd  (const CMLColorMachine* cm, CMLOutput ycd,    CMLInput ycbcr,  size_t count);
CML_API void cmlYCbCrToYupvp(const CMLColorMachine* cm, CMLOutput yupvp,  CMLInput ycbcr,  size_t count);
CML_API void cmlYCbCrToYuv  (const CMLColorMachine* cm, CMLOutput yuv,    CMLInput ycbcr,  size_t count);
CML_API void cmlYCbCrToYxy  (const CMLColorMachine* cm, CMLOutput yxy,    CMLInput ycbcr,  size_t count);

// Ycd Conversions
CML_API void cmlYcdToCMYK   (const CMLColorMachine* cm, CMLOutput cmyk,  CMLInput ycd,  size_t count);
CML_API void cmlYcdToGray   (const CMLColorMachine* cm, CMLOutput gray,  CMLInput ycd,  size_t count);
CML_API void cmlYcdToHSL    (const CMLColorMachine* cm, CMLOutput hsl,   CMLInput ycd,  size_t count);
CML_API void cmlYcdToHSV    (const CMLColorMachine* cm, CMLOutput hsv,   CMLInput ycd,  size_t count);
CML_API void cmlYcdToLab    (const CMLColorMachine* cm, CMLOutput lab,   CMLInput ycd,  size_t count);
CML_API void cmlYcdToLch    (const CMLColorMachine* cm, CMLOutput lch,   CMLInput ycd,  size_t count);
CML_API void cmlYcdToLuv    (const CMLColorMachine* cm, CMLOutput luv,   CMLInput ycd,  size_t count);
CML_API void cmlYcdToRGB    (const CMLColorMachine* cm, CMLOutput rgb,   CMLInput ycd,  size_t count);
CML_API void cmlYcdToUVW    (const CMLColorMachine* cm, CMLOutput uvw,   CMLInput ycd,  size_t count);
CML_API void cmlYcdToXYZ    (const CMLColorMachine* cm, CMLOutput xyz,   CMLInput ycd,  size_t count);
CML_API void cmlYcdToYCbCr  (const CMLColorMachine* cm, CMLOutput ycbcr, CMLInput ycd,  size_t count);
CML_API void cmlYcdToYcd    (const CMLColorMachine* cm, CMLOutput ycdd,  CMLInput ycds, size_t count);
CML_API void cmlYcdToYupvp  (const CMLColorMachine* cm, CMLOutput yupvp, CMLInput ycd,  size_t count);
CML_API void cmlYcdToYuv    (const CMLColorMachine* cm, CMLOutput yuv,   CMLInput ycd,  size_t count);
CML_API void cmlYcdToYxy    (const CMLColorMachine* cm, CMLOutput yxy,   CMLInput ycd,  size_t count);

// Yupvp Conversions
CML_API void cmlYupvpToCMYK (const CMLColorMachine* cm, CMLOutput cmyk,   CMLInput yupvp,  size_t count);
CML_API void cmlYupvpToGray (const CMLColorMachine* cm, CMLOutput gray,   CMLInput yupvp,  size_t count);
CML_API void cmlYupvpToHSL  (const CMLColorMachine* cm, CMLOutput hsl,    CMLInput yupvp,  size_t count);
CML_API void cmlYupvpToHSV  (const CMLColorMachine* cm, CMLOutput hsv,    CMLInput yupvp,  size_t count);
CML_API void cmlYupvpToLab  (const CMLColorMachine* cm, CMLOutput lab,    CMLInput yupvp,  size_t count);
CML_API void cmlYupvpToLch  (const CMLColorMachine* cm, CMLOutput lch,    CMLInput yupvp,  size_t count);
CML_API void cmlYupvpToLuv  (const CMLColorMachine* cm, CMLOutput luv,    CMLInput yupvp,  size_t count);
CML_API void cmlYupvpToRGB  (const CMLColorMachine* cm, CMLOutput rgb,    CMLInput yupvp,  size_t count);
CML_API void cmlYupvpToUVW  (const CMLColorMachine* cm, CMLOutput uvw,    CMLInput yupvp,  size_t count);
CML_API void cmlYupvpToXYZ  (const CMLColorMachine* cm, CMLOutput xyz,    CMLInput yupvp,  size_t count);
CML_API void cmlYupvpToYCbCr(const CMLColorMachine* cm, CMLOutput ycbcr,  CMLInput yupvp,  size_t count);
CML_API void cmlYupvpToYcd  (const CMLColorMachine* cm, CMLOutput ycd,    CMLInput yupvp,  size_t count);
CML_API void cmlYupvpToYupvp(const CMLColorMachine* cm, CMLOutput yupvpd, CMLInput yupvps, size_t count);
CML_API void cmlYupvpToYuv  (const CMLColorMachine* cm, CMLOutput yuv,    CMLInput yupvp,  size_t count);
CML_API void cmlYupvpToYxy  (const CMLColorMachine* cm, CMLOutput yxy,    CMLInput yupvp,  size_t count);

// Yuv Conversions
CML_API void cmlYuvToCMYK   (const CMLColorMachine* cm, CMLOutput cmyk,  CMLInput yuv,  size_t count);
CML_API void cmlYuvToGray   (const CMLColorMachine* cm, CMLOutput gray,  CMLInput yuv,  size_t count);
CML_API void cmlYuvToHSL    (const CMLColorMachine* cm, CMLOutput hsl,   CMLInput yuv,  size_t count);
CML_API void cmlYuvToHSV    (const CMLColorMachine* cm, CMLOutput hsv,   CMLInput yuv,  size_t count);
CML_API void cmlYuvToLab    (const CMLColorMachine* cm, CMLOutput lab,   CMLInput yuv,  size_t count);
CML_API void cmlYuvToLch    (const CMLColorMachine* cm, CMLOutput lch,   CMLInput yuv,  size_t count);
CML_API void cmlYuvToLuv    (const CMLColorMachine* cm, CMLOutput luv,   CMLInput yuv,  size_t count);
CML_API void cmlYuvToRGB    (const CMLColorMachine* cm, CMLOutput rgb,   CMLInput yuv,  size_t count);
CML_API void cmlYuvToUVW    (const CMLColorMachine* cm, CMLOutput uvw,   CMLInput yuv,  size_t count);
CML_API void cmlYuvToXYZ    (const CMLColorMachine* cm, CMLOutput xyz,   CMLInput yuv,  size_t count);
CML_API void cmlYuvToYCbCr  (const CMLColorMachine* cm, CMLOutput ycbcr, CMLInput yuv,  size_t count);
CML_API void cmlYuvToYcd    (const CMLColorMachine* cm, CMLOutput ycd,   CMLInput yuv,  size_t count);
CML_API void cmlYuvToYupvp  (const CMLColorMachine* cm, CMLOutput yupvp, CMLInput yuv,  size_t count);
CML_API void cmlYuvToYuv    (const CMLColorMachine* cm, CMLOutput yuvd,  CMLInput yuvs, size_t count);
CML_API void cmlYuvToYxy    (const CMLColorMachine* cm, CMLOutput yxy,   CMLInput yuv,  size_t count);

// Yxy Conversions
CML_API void cmlYxyToCMYK   (const CMLColorMachine* cm, CMLOutput cmyk,  CMLInput yxy,  size_t count);
CML_API void cmlYxyToGray   (const CMLColorMachine* cm, CMLOutput gray,  CMLInput yxy,  size_t count);
CML_API void cmlYxyToHSL    (const CMLColorMachine* cm, CMLOutput hsl,   CMLInput yxy,  size_t count);
CML_API void cmlYxyToHSV    (const CMLColorMachine* cm, CMLOutput hsv,   CMLInput yxy,  size_t count);
CML_API void cmlYxyToLab    (const CMLColorMachine* cm, CMLOutput lab,   CMLInput yxy,  size_t count);
CML_API void cmlYxyToLch    (const CMLColorMachine* cm, CMLOutput lch,   CMLInput yxy,  size_t count);
CML_API void cmlYxyToLuv    (const CMLColorMachine* cm, CMLOutput luv,   CMLInput yxy,  size_t count);
CML_API void cmlYxyToRGB    (const CMLColorMachine* cm, CMLOutput rgb,   CMLInput yxy,  size_t count);
CML_API void cmlYxyToUVW    (const CMLColorMachine* cm, CMLOutput uvw,   CMLInput yxy,  size_t count);
CML_API void cmlYxyToXYZ    (const CMLColorMachine* cm, CMLOutput xyz,   CMLInput yxy,  size_t count);
CML_API void cmlYxyToYCbCr  (const CMLColorMachine* cm, CMLOutput ycbcr, CMLInput yxy,  size_t count);
CML_API void cmlYxyToYcd    (const CMLColorMachine* cm, CMLOutput ycd,   CMLInput yxy,  size_t count);
CML_API void cmlYxyToYupvp  (const CMLColorMachine* cm, CMLOutput yupvp, CMLInput yxy,  size_t count);
CML_API void cmlYxyToYuv    (const CMLColorMachine* cm, CMLOutput yuv,   CMLInput yxy,  size_t count);
CML_API void cmlYxyToYxy    (const CMLColorMachine* cm, CMLOutput yxyd,  CMLInput yxys, size_t count);



// ////////////////////////////
// Input & Output Conversions
// ////////////////////////////

// Often times, you need to import or export values from files or memory blocks.
// The data may be in a different encoding than used in CML. Therefore you can
// use the following functions to convert 8-Bit and 16-Bit data to the requred
// float data. These functions will adapt the data to the cutoffs and the
// integer mappings of the given machine.

// 8-bit Input Conversions
CML_API void cmlData8ToCMYK (const CMLColorMachine* cm, CMLOutput cmyk,  CMLInput input, size_t count);
CML_API void cmlData8ToGray (const CMLColorMachine* cm, CMLOutput gray,  CMLInput input, size_t count);
CML_API void cmlData8ToHSL  (const CMLColorMachine* cm, CMLOutput hsl,   CMLInput input, size_t count);
CML_API void cmlData8ToHSV  (const CMLColorMachine* cm, CMLOutput hsv,   CMLInput input, size_t count);
CML_API void cmlData8ToLab  (const CMLColorMachine* cm, CMLOutput lab,   CMLInput input, size_t count);
CML_API void cmlData8ToLch  (const CMLColorMachine* cm, CMLOutput lch,   CMLInput input, size_t count);
CML_API void cmlData8ToLuv  (const CMLColorMachine* cm, CMLOutput luv,   CMLInput input, size_t count);
CML_API void cmlData8ToRGB  (const CMLColorMachine* cm, CMLOutput rgb,   CMLInput input, size_t count);
CML_API void cmlData8ToUVW  (const CMLColorMachine* cm, CMLOutput uvw,   CMLInput input, size_t count);
CML_API void cmlData8ToXYZ  (const CMLColorMachine* cm, CMLOutput xyz,   CMLInput input, size_t count);
CML_API void cmlData8ToYCbCr(const CMLColorMachine* cm, CMLOutput ycbcr, CMLInput input, size_t count);
CML_API void cmlData8ToYcd  (const CMLColorMachine* cm, CMLOutput ycd,   CMLInput input, size_t count);
CML_API void cmlData8ToYupvp(const CMLColorMachine* cm, CMLOutput yupvp, CMLInput input, size_t count);
CML_API void cmlData8ToYuv  (const CMLColorMachine* cm, CMLOutput yuv,   CMLInput input, size_t count);
CML_API void cmlData8ToYxy  (const CMLColorMachine* cm, CMLOutput yxy,   CMLInput input, size_t count);

CML_API CMLColorConverter cmlGetData8InputConverter(CMLColorType colorType);

// 16-bit Input Conversions
CML_API void cmlData16ToCMYK  (const CMLColorMachine* cm, CMLOutput cmyk,  CMLInput input, size_t count);
CML_API void cmlData16ToGray  (const CMLColorMachine* cm, CMLOutput gray,  CMLInput input, size_t count);
CML_API void cmlData16ToHSL   (const CMLColorMachine* cm, CMLOutput hsl,   CMLInput input, size_t count);
CML_API void cmlData16ToHSV   (const CMLColorMachine* cm, CMLOutput hsv,   CMLInput input, size_t count);
CML_API void cmlData16ToLab   (const CMLColorMachine* cm, CMLOutput lab,   CMLInput input, size_t count);
CML_API void cmlData16ToLch   (const CMLColorMachine* cm, CMLOutput lch,   CMLInput input, size_t count);
CML_API void cmlData16ToLuv   (const CMLColorMachine* cm, CMLOutput luv,   CMLInput input, size_t count);
CML_API void cmlData16ToRGB   (const CMLColorMachine* cm, CMLOutput rgb,   CMLInput input, size_t count);
CML_API void cmlData16ToUVW   (const CMLColorMachine* cm, CMLOutput uvw,   CMLInput input, size_t count);
CML_API void cmlData16ToXYZ   (const CMLColorMachine* cm, CMLOutput xyz,   CMLInput input, size_t count);
CML_API void cmlData16ToYCbCr (const CMLColorMachine* cm, CMLOutput ycbcr, CMLInput input, size_t count);
CML_API void cmlData16ToYcd   (const CMLColorMachine* cm, CMLOutput ycd,   CMLInput input, size_t count);
CML_API void cmlData16ToYupvp (const CMLColorMachine* cm, CMLOutput yupvp, CMLInput input, size_t count);
CML_API void cmlData16ToYuv   (const CMLColorMachine* cm, CMLOutput yuv,   CMLInput input, size_t count);
CML_API void cmlData16ToYxy   (const CMLColorMachine* cm, CMLOutput yxy,   CMLInput input, size_t count);

CML_API CMLColorConverter cmlGetData16InputConverter(CMLColorType colorType);

// 8-bit Output Conversions
CML_API void cmlCMYKToData8  (const CMLColorMachine* cm, CMLOutput output, CMLInput cmyk,  size_t count);
CML_API void cmlGrayToData8  (const CMLColorMachine* cm, CMLOutput output, CMLInput gray,  size_t count);
CML_API void cmlHSLToData8   (const CMLColorMachine* cm, CMLOutput output, CMLInput hsl,   size_t count);
CML_API void cmlHSVToData8   (const CMLColorMachine* cm, CMLOutput output, CMLInput hsv,   size_t count);
CML_API void cmlLabToData8   (const CMLColorMachine* cm, CMLOutput output, CMLInput lab,   size_t count);
CML_API void cmlLchToData8   (const CMLColorMachine* cm, CMLOutput output, CMLInput lch,   size_t count);
CML_API void cmlLuvToData8   (const CMLColorMachine* cm, CMLOutput output, CMLInput luv,   size_t count);
CML_API void cmlRGBToData8   (const CMLColorMachine* cm, CMLOutput output, CMLInput rgb,   size_t count);
CML_API void cmlUVWToData8   (const CMLColorMachine* cm, CMLOutput output, CMLInput uvw,   size_t count);
CML_API void cmlXYZToData8   (const CMLColorMachine* cm, CMLOutput output, CMLInput xyz,   size_t count);
CML_API void cmlYCbCrToData8 (const CMLColorMachine* cm, CMLOutput output, CMLInput ycbcr, size_t count);
CML_API void cmlYcdToData8   (const CMLColorMachine* cm, CMLOutput output, CMLInput ycd,   size_t count);
CML_API void cmlYupvpToData8 (const CMLColorMachine* cm, CMLOutput output, CMLInput yupvp, size_t count);
CML_API void cmlYuvToData8   (const CMLColorMachine* cm, CMLOutput output, CMLInput yuv,   size_t count);
CML_API void cmlYxyToData8   (const CMLColorMachine* cm, CMLOutput output, CMLInput yxy,   size_t count);

CML_API CMLColorConverter cmlGetData8OutputConverter(CMLColorType colorType);

// 16-bit Output Conversions
CML_API void cmlCMYKToData16 (const CMLColorMachine* cm, CMLOutput output, CMLInput cmyk,  size_t count);
CML_API void cmlGrayToData16 (const CMLColorMachine* cm, CMLOutput output, CMLInput gray,  size_t count);
CML_API void cmlHSLToData16  (const CMLColorMachine* cm, CMLOutput output, CMLInput hsl,   size_t count);
CML_API void cmlHSVToData16  (const CMLColorMachine* cm, CMLOutput output, CMLInput hsv,   size_t count);
CML_API void cmlLabToData16  (const CMLColorMachine* cm, CMLOutput output, CMLInput lab,   size_t count);
CML_API void cmlLchToData16  (const CMLColorMachine* cm, CMLOutput output, CMLInput lch,   size_t count);
CML_API void cmlLuvToData16  (const CMLColorMachine* cm, CMLOutput output, CMLInput luv,   size_t count);
CML_API void cmlRGBToData16  (const CMLColorMachine* cm, CMLOutput output, CMLInput rgb,   size_t count);
CML_API void cmlUVWToData16  (const CMLColorMachine* cm, CMLOutput output, CMLInput uvw,   size_t count);
CML_API void cmlXYZToData16  (const CMLColorMachine* cm, CMLOutput output, CMLInput xyz,   size_t count);
CML_API void cmlYCbCrToData16(const CMLColorMachine* cm, CMLOutput output, CMLInput ycbcr, size_t count);
CML_API void cmlYcdToData16  (const CMLColorMachine* cm, CMLOutput output, CMLInput ycd,   size_t count);
CML_API void cmlYupvpToData16(const CMLColorMachine* cm, CMLOutput output, CMLInput yupvp, size_t count);
CML_API void cmlYuvToData16  (const CMLColorMachine* cm, CMLOutput output, CMLInput yuv,   size_t count);
CML_API void cmlYxyToData16  (const CMLColorMachine* cm, CMLOutput output, CMLInput yxy,   size_t count);

CML_API CMLColorConverter cmlGetData16OutputConverter(CMLColorType colorType);


// ////////////////////////////
// Inversion functions
// ////////////////////////////

// Use these to invert colors. Black becomes white and vice versa.
CML_API void cmlInvertCMYK   (CMLInputOutput cmyk,  size_t count);
CML_API void cmlInvertGray   (CMLInputOutput gray,  size_t count);
CML_API void cmlInvertHSL    (CMLInputOutput hsl,   size_t count);
CML_API void cmlInvertHSV    (CMLInputOutput hsv,   size_t count);
CML_API void cmlInvertLab    (CMLInputOutput lab,   size_t count);
CML_API void cmlInvertLch    (CMLInputOutput lch,   size_t count);
CML_API void cmlInvertLuv    (CMLInputOutput luv,   size_t count);
CML_API void cmlInvertRGB    (CMLInputOutput rgb,   size_t count);
CML_API void cmlInvertUVW    (CMLInputOutput uvw,   size_t count);
CML_API void cmlInvertXYZ    (CMLInputOutput xyz,   size_t count);
CML_API void cmlInvertYCbCr  (CMLInputOutput ycbcr, size_t count);
CML_API void cmlInvertYcd    (CMLInputOutput ycd,   size_t count);
CML_API void cmlInvertYupvp  (CMLInputOutput yupvp, size_t count);
CML_API void cmlInvertYuv    (CMLInputOutput yuv,   size_t count);
CML_API void cmlInvertYxy    (CMLInputOutput yxy,   size_t count);

CML_API CMLColorMutator cmlGetInverter(CMLColorType colorType);


// ////////////////////////////
// Clamp functions
// ////////////////////////////

// Use these to clamp colors. No value will be out of range.
CML_API void cmlClampCMYK  (CMLInputOutput cmyk,  size_t count);
CML_API void cmlClampGray  (CMLInputOutput gray,  size_t count);
CML_API void cmlClampHSL   (CMLInputOutput hsl,   size_t count);
CML_API void cmlClampHSV   (CMLInputOutput hsv,   size_t count);
CML_API void cmlClampLab   (CMLInputOutput lab,   size_t count);
CML_API void cmlClampLch   (CMLInputOutput lch,   size_t count);
CML_API void cmlClampLuv   (CMLInputOutput luv,   size_t count);
CML_API void cmlClampRGB   (CMLInputOutput rgb,   size_t count);
CML_API void cmlClampUVW   (CMLInputOutput uvw,   size_t count);
CML_API void cmlClampXYZ   (CMLInputOutput xyz,   size_t count);
CML_API void cmlClampYCbCr (CMLInputOutput ycbcr, size_t count);
CML_API void cmlClampYcd   (CMLInputOutput ycd,   size_t count);
CML_API void cmlClampYupvp (CMLInputOutput yupvp, size_t count);
CML_API void cmlClampYuv   (CMLInputOutput yuv,   size_t count);
CML_API void cmlClampYxy   (CMLInputOutput yxy,   size_t count);

CML_API CMLColorMutator cmlGetClamper(CMLColorType colorType);


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
CML_API void cmlNormedInputToCMYK  (CMLOutput cmyk,  CMLInput input, size_t count);
CML_API void cmlNormedInputToGray  (CMLOutput gray,  CMLInput input, size_t count);
CML_API void cmlNormedInputToHSL   (CMLOutput hsl,   CMLInput input, size_t count);
CML_API void cmlNormedInputToHSV   (CMLOutput hsv,   CMLInput input, size_t count);
CML_API void cmlNormedInputToLab   (CMLOutput lab,   CMLInput input, size_t count);
CML_API void cmlNormedInputToLch   (CMLOutput lch,   CMLInput input, size_t count);
CML_API void cmlNormedInputToLuv   (CMLOutput luv,   CMLInput input, size_t count);
CML_API void cmlNormedInputToRGB   (CMLOutput rgb,   CMLInput input, size_t count);
CML_API void cmlNormedInputToUVW   (CMLOutput uvw,   CMLInput input, size_t count);
CML_API void cmlNormedInputToXYZ   (CMLOutput xyz,   CMLInput input, size_t count);
CML_API void cmlNormedInputToYCbCr (CMLOutput ycbcr, CMLInput input, size_t count);
CML_API void cmlNormedInputToYcd   (CMLOutput ycd,   CMLInput input, size_t count);
CML_API void cmlNormedInputToYupvp (CMLOutput yupvp, CMLInput input, size_t count);
CML_API void cmlNormedInputToYuv   (CMLOutput yuv,   CMLInput input, size_t count);
CML_API void cmlNormedInputToYxy   (CMLOutput yxy,   CMLInput input, size_t count);

// Output Conversions to normed range [0,1]
CML_API void cmlCMYKToNormedOutput (CMLOutput output, CMLInput cmyk,  size_t count);
CML_API void cmlGrayToNormedOutput (CMLOutput output, CMLInput gray,  size_t count);
CML_API void cmlHSLToNormedOutput  (CMLOutput output, CMLInput hsl,   size_t count);
CML_API void cmlHSVToNormedOutput  (CMLOutput output, CMLInput hsv,   size_t count);
CML_API void cmlLabToNormedOutput  (CMLOutput output, CMLInput lab,   size_t count);
CML_API void cmlLchToNormedOutput  (CMLOutput output, CMLInput lch,   size_t count);
CML_API void cmlLuvToNormedOutput  (CMLOutput output, CMLInput luv,   size_t count);
CML_API void cmlRGBToNormedOutput  (CMLOutput output, CMLInput rgb,   size_t count);
CML_API void cmlUVWToNormedOutput  (CMLOutput output, CMLInput uvw,   size_t count);
CML_API void cmlXYZToNormedOutput  (CMLOutput output, CMLInput xyz,   size_t count);
CML_API void cmlYCbCrToNormedOutput(CMLOutput output, CMLInput ycbcr, size_t count);
CML_API void cmlYcdToNormedOutput  (CMLOutput output, CMLInput ycd,   size_t count);
CML_API void cmlYupvpToNormedOutput(CMLOutput output, CMLInput yupvp, size_t count);
CML_API void cmlYuvToNormedOutput  (CMLOutput output, CMLInput yuv,   size_t count);
CML_API void cmlYxyToNormedOutput  (CMLOutput output, CMLInput yxy,   size_t count);

// float Input Conversions from normed cartesian range [0,1]
CML_API void cmlNormedCartesianInputToLch   (CMLOutput lch, CMLInput input, size_t count);
CML_API void cmlNormedCartesianInputToHSV   (CMLOutput hsv, CMLInput input, size_t count);
CML_API void cmlNormedCartesianInputToHSL   (CMLOutput hsl, CMLInput input, size_t count);

// Output Conversions to normed cartesian range [0,1]
CML_API void cmlLchToNormedCartesianOutput  (CMLOutput output, CMLInput lch, size_t count);
CML_API void cmlHSVToNormedCartesianOutput  (CMLOutput output, CMLInput hsv, size_t count);
CML_API void cmlHSLToNormedCartesianOutput  (CMLOutput output, CMLInput hsl, size_t count);



// ////////////////////////////
// Normed Gamut Slice
// ////////////////////////////

// Creates a one-, two-, three- or four-dimensional array filled with normed
// color values in the given colorspace.
//
// This function is named Slice because it is used very often for getting
// two-dimensional surfaces out of a three-dimensional body. But using this
// function, you can get any part of any body in up to four dimensions.
//
// The numbers given in the dimensions parameter depict the number of steps per
// dimension. For example, the parameter dimensions={20, 40, 0, 0} will create
// a two-dimensional array with 20 steps in the primary and 40 steps
// in the secondary axis.
//
// In the dimensions-parameter, the value 0 will be interpreted as 1. This
// means that in the example above, you can write dimensions={20, 40, 1, 1}
// which does exactly the same thing. This has been introduced to simplify
// the work of any programmer who often juggles around with different
// dimension-settings. This also means that the function always returns an
// array with at least 1 color entry.
//
// The returned array is filled with a linear combination of normed color values
// in the given colorspace. The range of the values for all channels can be
// given by the remaining parameters. The origin parameter defines the origin
// of the linear combination. The next four parameters defines the
// range of the primary, secondary, ternary and quaternary dimension.
//
// All of the origin- and range-parameters can be set to NULL. In this case, a
// default origin and range will be assumed. The default origin
// is 0 and the default range is 1 for the channel depicted by the dimension and
// 0 elsewhere. Note that if the stepSize of a dimension is 0 or 1, the range of
// that dimension is unused.
//
// Only the values of the channels available in the given colorspace
// will be considered. The rest of the CMLVec4-values is ignored.
//
// Let's assume in the above example, that the colorspace is RGB and the
// following parameters are given:
// origin = {0, .5,  1, 0};
// range0 = {1,  0,  0, 0};
// range1 = {0,  0, -1, 0};
// range2 = NULL;
// range3 = NULL;
// This will result in a color plane where in primary dimension, the red
// component goes from 0 to 1 and in secondary dimension, the blue component
// goes from 1 to 0. The green component is .5 always. The parameters range2
// and range3 are ignored as the number of steps is 0 or 1 respectively. 
//
// Note that the returned arrays are always stored as one-dimensional row-first
// C-Arrays. Therefore, a two-dimensional array must be addressed with
// DesiredColor = returnedarray[y * dim[0] * numchannels + x * numchannels];
// where according to the example above, dim[0] would be 20 and numchannels
// would be 3.
//
// To convert the resulting values to non-normed color-coordinates, simply
// convert the whole array using the appropriate fromNormedInput-Converter.
// In the example above, this would be cmlNormedInputToRGB. Note that you
// need to provide the buffer for this conversion by yourself. The required
// number of bytes can be computed like this:
// numbytes = dim[0] * dim[1] * dim[2] * dim[3] * numchannels * sizeof(float);
// (Beware of 0-Entries in dim!)
//
// The returned array must be deleted manually by the user with free();
//
// This function does only work with channeled color types. Any other
// colorspace will return NULL.

CML_API CMLOutput cmlCreateNormedGamutSlice(
  CMLColorType colorspace,
  const size_t dimensions[CML_MAX_NUMBER_OF_CHANNELS],
  const CMLVec4 origin,
  const CMLVec4 range0,
  const CMLVec4 range1,
  const CMLVec4 range2,
  const CMLVec4 range3);

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


// Following are enumerations of all built-in parameters.
// More will come if desired.



// Enumerates the predefined color types
typedef enum{
  CML_COLOR_GRAY = 0,
  CML_COLOR_XYZ,    // CIE 1931
  CML_COLOR_Yxy,
  CML_COLOR_Yuv,    // CIE 1960 (UCS)
  CML_COLOR_Yupvp,  // CIE 1976
  CML_COLOR_Lab,
  CML_COLOR_Lch,
  CML_COLOR_Luv,    // CIE 1976
  CML_COLOR_RGB,
  CML_COLOR_YCbCr,
  CML_COLOR_HSV,
  CML_COLOR_HSL,
  CML_COLOR_CMYK,
  CML_COLOR_SPECTRUM_ILLUMINATION,
  CML_COLOR_SPECTRUM_REMISSION,
  CML_NUMBER_OF_COLORTYPES
} CMLColorType;

// Enumerates the predefined integration computation types
typedef enum{
  CML_INTEGRATION_SIMPLE = 0,
  CML_INTEGRATION_BINARY_PAIRS,
  CML_NUMBER_OF_INTEGRATION_TYPES
} CMLIntegrationMethod;

// Enumerates the predefined integer mapping types
typedef enum{
  CML_INTEGER_MAPPING_FLOOR = 0,
  CML_INTEGER_MAPPING_BOX,
  CML_INTEGER_MAPPING_INTERVAL,
  CML_NUMBER_OF_INTEGER_MAPPING_TYPES
} CMLIntegerMappingType;

// Enumerates the predefined observers
typedef enum{
  CML_OBSERVER_2DEG_CIE_1931 = 0,
  CML_OBSERVER_10DEG_CIE_1964,
  CML_OBSERVER_2DEG_JUDD_1951,
  CML_OBSERVER_2DEG_JUDD_VOS_1978,
  CML_OBSERVER_CUSTOM,
  CML_NUMBER_OF_OBSERVERS
} CMLObserverType;

// Enumerates the predefined illuminations
typedef enum{
  CML_ILLUMINATION_BLACKBODY = 0,
  CML_ILLUMINATION_A_CIE,
  CML_ILLUMINATION_A_EXACT,
  CML_ILLUMINATION_B,
  CML_ILLUMINATION_C,
  CML_ILLUMINATION_D_ILLUMINANT,
  CML_ILLUMINATION_D50,
  CML_ILLUMINATION_D55,
  CML_ILLUMINATION_D65,
  CML_ILLUMINATION_D75,
  CML_ILLUMINATION_D93,
  CML_ILLUMINATION_E,
  CML_ILLUMINATION_F1,
  CML_ILLUMINATION_F2,
  CML_ILLUMINATION_F3,
  CML_ILLUMINATION_F4,
  CML_ILLUMINATION_F5,
  CML_ILLUMINATION_F6,
  CML_ILLUMINATION_F7,
  CML_ILLUMINATION_F8,
  CML_ILLUMINATION_F9,
  CML_ILLUMINATION_F10,
  CML_ILLUMINATION_F11,
  CML_ILLUMINATION_F12,
  CML_ILLUMINATION_XENON,
  CML_ILLUMINATION_CUSTOM_WHITEPOINT,
  CML_ILLUMINATION_CUSTOM_SPECTRUM,
  CML_NUMBER_OF_ILLUMINATIONS
} CMLIlluminationType;

// Enumerates the predefined RGB colorspaces
typedef enum{
  CML_RGB_ADOBE_98 = 0,
  CML_RGB_APPLE,
  CML_RGB_BEST,
  CML_RGB_BETA,
  CML_RGB_BRUCE,
  CML_RGB_CIE,
  CML_RGB_COLORMATCH,
  CML_RGB_DON4,
  CML_RGB_EBU_MONITOR,
  CML_RGB_ECI,
  CML_RGB_EKTA_SPACE_PS5,
  CML_RGB_HDTV,
  CML_RGB_REC_BT_601_525,
  CML_RGB_REC_BT_601_625,
  CML_RGB_REC_BT_709,
  CML_RGB_REC_BT_2020,
  CML_RGB_KODAK_DC,
  CML_RGB_NTSC_53,
  CML_RGB_PAL_SECAM_EBU,
  CML_RGB_ROMM_PROPHOTO,
  CML_RGB_SMPTE_C,
  CML_RGB_SRGB,
  CML_RGB_WIDE_GAMUT,
  CML_RGB_CUSTOM,
  CML_NUMBER_OF_RGB_SPACES
} CMLRGBColorSpace;

// Enumerates the predefined Lab colorspaces
typedef enum{
  CML_LAB_CIELAB = 0,
  CML_LAB_CUSTOM_L,
  CML_LAB_HUNTER_APPROXIMATE,
  CML_LAB_HUNTER_ORIGINAL,
  CML_LAB_ADAMS_CROMATIC_VALENCE,
  CML_NUMBER_OF_LAB_SPACES
} CMLLabColorSpaceType;

// Enumerates the predefined response curves
typedef enum{
  CML_RESPONSE_LINEAR = 0,
  CML_RESPONSE_SQRT,
  CML_RESPONSE_GAMMA_ADOBE_98,
  CML_RESPONSE_GAMMA_1_8,
  CML_RESPONSE_GAMMA_1_9,
  CML_RESPONSE_GAMMA_2_2,
  CML_RESPONSE_GAMMA_LINEAR_REC_BT_10BIT,
  CML_RESPONSE_GAMMA_LINEAR_REC_BT_12BIT,
  CML_RESPONSE_SRGB,
  CML_RESPONSE_LSTAR,
  CML_RESPONSE_LSTAR_STANDARD,
  CML_NUMBER_OF_RESPONSE_CURVE_PRESETS
} CMLResponseCurvePreset;

// Enumerates the predefined function types
typedef enum{
  CML_FUNCTION_LINEAR = 0,
  CML_FUNCTION_SQRT,
  CML_FUNCTION_GAMMA,
  CML_FUNCTION_GAMMA_LINEAR,
  CML_FUNCTION_SRGB,
  CML_FUNCTION_LSTAR,
  CML_FUNCTION_LSTAR_STANDARD,
  CML_NUMBER_OF_FUNCTION_TYPES
} CMLFunctionType;

// Enumerates the predefined Gray computations.
typedef enum{
  CML_GRAY_FROM_HSL = 0,  // HSL
  CML_GRAY_FROM_HSV,      // HSV
  CML_GRAY_FROM_G,        // RGB
  CML_GRAY_FROM_LSTAR,    // CIELAB, Luv
  CML_GRAY_FROM_L,        // Lab
  CML_GRAY_FROM_Y,        // XYZ, Yxy, Yuv
  CML_GRAY_FROM_YPRIME,   // YCbCr
  CML_NUMBER_OF_GRAY_COMPUTATIONS
} CMLGrayComputationType;

// Enumerates the predefined RGB to CMYK conversions
typedef enum{
  CML_CMYK_STANDARD_TRANSFORM = 0,
  CML_CMYK_UCR_TRANSFORM,
  CML_NUMBER_OF_CMYK_TRANSFORMS
} CMLCMYKTransformType;

// Enumerates the predefined chromatic adaptations
typedef enum{
  CML_CHROMATIC_ADAPTATION_NONE = 0,
  CML_CHROMATIC_ADAPTATION_XYZ_SCALING,
  CML_CHROMATIC_ADAPTATION_BRADFORD,
  CML_CHROMATIC_ADAPTATION_VON_KRIES,
  CML_NUMBER_OF_CHROMATIC_ADAPTATIONS
} CMLChromaticAdaptationType;

// Enumerates the predefined interpolation methods of array functions
typedef enum{
  CML_INTERPOLATION_NONE = 0,
  CML_INTERPOLATION_FLOOR,
  CML_INTERPOLATION_BOX,
  CML_INTERPOLATION_INTERVAL,
  CML_INTERPOLATION_LINEAR
} CMLInterpolationMethod;

// Enumerates the predefined extrapolation methods of array functions
// If you are uncertain, you should probably choose LINEAR_ZERO.
typedef enum{
  CML_EXTRAPOLATION_CLAMP_ZERO = 0, // 0 outside definition
  CML_EXTRAPOLATION_LINEAR_ZERO,    // linear to 0 in one stepsize, then 0
  CML_EXTRAPOLATION_CLAMP_VALUE,    // last value repeating
  CML_EXTRAPOLATION_GRADIENT        // last gradient repeating
} CMLExtrapolationMethod;



// Some typedefs which are used later in the API:

typedef struct CMLColorMachine    CMLColorMachine;
typedef struct CMLFunction        CMLFunction;
typedef struct CMLResponseCurve   CMLResponseCurve;
typedef struct CMLObserver        CMLObserver;
typedef struct CMLIllumination    CMLIllumination;
typedef struct CMLDefinitionRange CMLDefinitionRange;

typedef void*                     CMLOutput;
typedef const void*               CMLInput;
typedef void*                     CMLInputOutput;

typedef void (*CMLColorConverter)(
  const CMLColorMachine*,
  CMLOutput,
  CMLInput,
  size_t);
                                          
typedef void (*CMLNormedConverter)(
  CMLOutput,
  CMLInput,
  size_t);



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

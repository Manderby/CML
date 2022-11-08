
// Enumerates the predefined color types
typedef enum{
  CML_COLOR_CMYK,
  CML_COLOR_GRAY,
  CML_COLOR_HSL,
  CML_COLOR_HSV,
  CML_COLOR_Lab,
  CML_COLOR_Lch,
  CML_COLOR_Luv,    // CIE 1976
  CML_COLOR_RGB,
  CML_COLOR_SPECTRUM_ILLUMINATION,
  CML_COLOR_SPECTRUM_REMISSION,
  CML_COLOR_XYZ,    // CIE 1931
  CML_COLOR_YCbCr,
  CML_COLOR_Ycd,
  CML_COLOR_Yupvp,  // CIE 1976
  CML_COLOR_Yuv,    // CIE 1960 (UCS)
  CML_COLOR_Yxy,

  CML_COLOR_COUNT
} CMLColorType;

// Enumerates the predefined integration computation methods.
//
// Simple: Simple sum computation by adding one by one.
// Binary pairs: Highly efficient and accurate integration method developed by
//   Tobias Stamm. It even outperforms a simple for loop by using the memory
//   cache and is much more accurate for well-behaving sampling functions as
//   it combines neighboring values and hence loses much fewer floating point
//   accuracy when summing these up.
typedef enum{
  CML_INTEGRATION_SIMPLE = 0,
  CML_INTEGRATION_BINARY_PAIRS,
  CML_INTEGRATION_COUNT
} CMLIntegrationMethod;

// Enumerates the predefined integer mapping types.
// If you are uncertain, you should probably choose FLOOR.
//
// In CML, all color computations are done in floating point precision. When
// importing or exporting color values on the other hand, very often 8-bit or
// 16-bit integer values are expected. Mapping integers to floats is rather
// straight-forward: floatvalue = intValue / maxIntValue
// When looking for example at a 2-bit integer, the following mapping will be
// performed:
//   0                       1                       2                       3
//   |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|
//   0                      1/3                     2/3                      1
//
// When mapping from floats to integers on the other hand, the conversion is
// not straight forward. In the following diagram, three methods are shown.
// - A (Floor),
// - B (Box)
// - C (Interval)
//
// Floor (F): intValue = floor(v * maxIntValue)
// The most common method. With this method, only the input value 1 will be
// mapped to maxIntValue. A value even slightly smaller than 1 (0.99999) will
// be mapped to maxIntValue - 1.
//
// Box (B): intValue = floor(v * maxIntValue + 0.5)
// This mapping method maps values around 0 and 1 better to the corresponding
// integer value.
//
// Interval (I): intValue = floor(v * (maxIntValue + 1))   if v < 1.0
//               intValue = maxIntValue                    if v == 1.0
// This last method evenly distributes all values but takes a longer time to
// convert.
//
// v 0    1/12  2/12  3/12  4/12  5/12  6/12  7/12  8/12  9/12 10/12 11/12   1
//   +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
// F |            0          |           1           |          2            3
//   +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
// B |     0     |           1           |          2            |     3     |
//   +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
// I |        0        |        1        |        2        |        3        |
//   +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
typedef enum{
  CML_INTEGER_MAPPING_FLOOR = 0,
  CML_INTEGER_MAPPING_BOX,
  CML_INTEGER_MAPPING_INTERVAL,
  CML_INTEGER_MAPPING_COUNT
} CMLIntegerMappingType;

// Enumerates the predefined observers
typedef enum{
  CML_OBSERVER_2DEG_CIE_1931 = 0,
  CML_OBSERVER_10DEG_CIE_1964,
//  CML_OBSERVER_2DEG_ISO_13655,
  CML_OBSERVER_2DEG_JUDD_1951,
  CML_OBSERVER_2DEG_JUDD_VOS_1978,
//  CML_OBSERVER_2DEG_SHAW_FAIRCHILD_1997,
  CML_OBSERVER_CUSTOM,
  CML_OBSERVER_COUNT
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
  CML_ILLUMINATION_COUNT
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
  CML_RGB_CUSTOM,           // custom RGB is always the last one.
  CML_RGB_COUNT
} CMLRGBColorSpaceType;

// Enumerates the predefined Lab colorspaces
typedef enum{
  CML_LAB_CIELAB = 0,
  CML_LAB_CUSTOM_L,
  CML_LAB_HUNTER_APPROXIMATE,
  CML_LAB_HUNTER_ORIGINAL,
  CML_LAB_ADAMS_CROMATIC_VALENCE,
  CML_LAB_COUNT
} CMLLabColorSpaceType;

typedef enum{
  CML_DELTA_E_1976,
  CML_DELTA_E_COUNT
} CMLDeltaEComputationType;

// Enumerates the predefined response curves
typedef enum{
  CML_RESPONSE_UNDEFINED = 0,
  CML_RESPONSE_LINEAR,
  CML_RESPONSE_GAMMA_1_8,
  CML_RESPONSE_GAMMA_1_9,
  CML_RESPONSE_GAMMA_2_0,
  CML_RESPONSE_GAMMA_ADOBE_98,
  CML_RESPONSE_GAMMA_2_2,
  CML_RESPONSE_GAMMA_LINEAR_REC_BT_10BIT,
  CML_RESPONSE_GAMMA_LINEAR_REC_BT_12BIT,
  CML_RESPONSE_SRGB,
  CML_RESPONSE_LSTAR,
  CML_RESPONSE_LSTAR_STANDARD,
  CML_RESPONSE_CUSTOM_GAMMA,        // custom gammas are always the last ones.
  CML_RESPONSE_CUSTOM_GAMMA_LINEAR,
  CML_RESPONSE_COUNT
} CMLResponseCurveType;

// Enumerates the predefined function types
typedef enum{
  CML_FUNCTION_UNDEFINED = 0,
  CML_FUNCTION_LINEAR,
  CML_FUNCTION_SQRT,
  CML_FUNCTION_GAMMA,
  CML_FUNCTION_GAMMA_LINEAR,
  CML_FUNCTION_SRGB,
  CML_FUNCTION_LSTAR,
  CML_FUNCTION_LSTAR_STANDARD,
  CML_FUNCTION_COUNT
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
  CML_GRAY_COUNT
} CMLGrayComputationType;

// Enumerates the predefined RGB to CMYK conversions
typedef enum{
  CML_CMYK_STANDARD_TRANSFORM = 0,
  CML_CMYK_UCR_TRANSFORM,
  CML_CMYK_COUNT
} cml_CMYKTransformType;

// Enumerates the predefined chromatic adaptations
typedef enum{
  CML_CHROMATIC_ADAPTATION_NONE = 0,
  CML_CHROMATIC_ADAPTATION_XYZ_SCALING,
  CML_CHROMATIC_ADAPTATION_BRADFORD,
  CML_CHROMATIC_ADAPTATION_VON_KRIES,
  CML_CHROMATIC_ADAPTATION_COUNT
} CMLChromaticAdaptationType;

// Enumerates the predefined interpolation methods of array functions.
// If you are uncertain, you should probably choose either linear or floor.
//
// In the following table, you can see the output of an interpolation
// given two sampling points 1.00 and 2.00. Values denoted with "out"
// are not in the interpolation range anymore and will be covered by
// the extrapolation method.
//
// Samples:                  X                 X
// Input value:  0.49  0.50  1.00  1.49  1.50  2.00  2.49  2.50  3.00
// --------------------------------------------------------------------
// None:         out   out   1.00  0.00  0.00  2.00  out   out   out
// Floor:        out   out   1.00  1.00  1.00  2.00  2.00  2.00  out
// Box:          out   1.00  1.00  1.00  2.00  2.00  2.00  out   out
// Interval:     out   out   1.00  1.00  1.00  2.00  out   out   out
// Linear:       out   out   1.00  1.49  1.50  2.00  out   out   out
typedef enum{
  CML_INTERPOLATION_NONE = 0,
  CML_INTERPOLATION_FLOOR,
  CML_INTERPOLATION_BOX,
  CML_INTERPOLATION_INTERVAL,
  CML_INTERPOLATION_LINEAR
} CMLInterpolationMethod;

// Enumerates the predefined extrapolation methods of array functions
// If you are uncertain, you should probably choose LINEAR_ZERO.
//
// In the following table, you can see the output of an extrapolation
// upwards given two sampling points 1.00 and 2.00. Using the method for
// extrapolation downwards is just mirrored.
// Note that the range in which extrapolation takes place is determined by the
// interpolation method, see above. Here, "Linear" is assumed.
//
// Samples:      X     X
// Input value:  1.00  2.00  2.25  2.50  2.75  3.00  3.25
// ------------------------------------------------------
// Clamp Zero:   1.00  2.00  0.00  0.00  0.00  0.00  0.00
// Linear Zero:  1.00  2.00  1.50  1.00  0.50  0.00  0.00
// Clamp Value:  1.00  2.00  2.00  2.00  2.00  2.00  2.00
// Gradient:     1.00  2.00  2.25  2.50  2.75  3.00  3.25
typedef enum{
  CML_EXTRAPOLATION_CLAMP_ZERO = 0, // 0 outside definition
  CML_EXTRAPOLATION_LINEAR_ZERO,    // linear to 0 in one stepSize, then 0
  CML_EXTRAPOLATION_CLAMP_VALUE,    // last value repeating
  CML_EXTRAPOLATION_GRADIENT        // last gradient repeating
} CMLExtrapolationMethod;



// The following functions return an ASCII string describing the desired value.
// Do not delete the returned pointers. If an invalid input parameter is given,
// the returned value will be invalid.
CML_API const char* cmlGetColorTypeString               (CMLColorType colorType);
CML_API const char* cmlGetIntegrationMethodString       (CMLIntegrationMethod integrationMethod);
CML_API const char* cmlGetIntegerMappingString          (CMLIntegerMappingType integerMappingType);
CML_API const char* cmlGetObserverTypeString            (CMLObserverType observerType);
CML_API const char* cmlGetIlluminationTypeString        (CMLIlluminationType illuminationType);
CML_API const char* cmlGetRGBColorSpaceTypeString       (CMLRGBColorSpaceType type);
CML_API const char* cmlGetLabSpaceTypeString            (CMLLabColorSpaceType labSpaceType);
CML_API const char* cmlGetRGBResponseTypeString         (CMLResponseCurveType type);
CML_API const char* cmlGetFunctionTypeString            (CMLFunctionType functionType);
CML_API const char* cmlGetGrayComputationTypeString     (CMLGrayComputationType computationType);
CML_API const char* cmlGetCMYKTransformTypeString       (cml_CMYKTransformType transformType);
CML_API const char* cmlGetChromaticAdaptationTypeString (CMLChromaticAdaptationType chromaticAdaptationType);



// Some typedefs which are used later in the API:
typedef struct CMLColorMachine    CMLColorMachine;
typedef struct CMLFunction        CMLFunction;
typedef struct CMLObserver        CMLObserver;
typedef struct CMLResponseCurve   CMLResponseCurve;
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

typedef void (*CMLColorMutator)(
  CMLInputOutput,
  size_t);

typedef struct CMLIntegration CMLIntegration;
struct CMLIntegration{
  CMLIntegrationMethod          method;
  float                         stepSize;
};

// Any new ColorMachine has the following default settings:
#define CML_DEFAULT_INTEGRATION_METHOD          CML_INTEGRATION_BINARY_PAIRS
#define CML_DEFAULT_INTEGER_MAPPING             CML_INTEGER_MAPPING_FLOOR
#define CML_DEFAULT_2DEG_OBSERVER               CML_OBSERVER_2DEG_CIE_1931
#define CML_DEFAULT_10DEG_OBSERVER              CML_OBSERVER_10DEG_CIE_1964
#define CML_DEFAULT_8BIT_FLOOR_CUTOFF           0
#define CML_DEFAULT_8BIT_CEIL_CUTOFF            255
#define CML_DEFAULT_16BIT_FLOOR_CUTOFF          0
#define CML_DEFAULT_16BIT_CEIL_CUTOFF           65535
#define CML_DEFAULT_LAB_COLORSPACE              CML_LAB_CIELAB
#define CML_DEFAULT_LAB_LUT_SIZE                32
#define CML_DEFAULT_RGB_COLORSPACE              CML_RGB_SRGB
#define CML_DEFAULT_RGB_LUT_SIZE                32
#define CML_DEFAULT_CMYK_TRANSFORM              CML_CMYK_STANDARD_TRANSFORM
#define CML_DEFAULT_GRAY_COMPUTATION            CML_GRAY_FROM_LSTAR
#define CML_DEFAULT_CHROMATIC_ADAPTATION        CML_CHROMATIC_ADAPTATION_NONE

// The following defaults are used for integration and the cmlFilterFunction
// method with continuous functions.
#define CML_DEFAULT_INTEGRATION_MIN             300.f
#define CML_DEFAULT_INTEGRATION_MAX             830.f
#define CML_DEFAULT_INTEGRATION_STEPSIZE        1.f

// Definitions of the properties of the colorspaces.
#define CML_GRAY_NUMCHANNELS  1
#define CML_GRAY_MIN          0.f
#define CML_GRAY_MAX          1.f

#define CML_XYZ_NUMCHANNELS 3
#define CML_XYZ_X_MIN       0.f
#define CML_XYZ_X_MAX       1.f
#define CML_XYZ_Y_MIN       0.f
#define CML_XYZ_Y_MAX       1.f
#define CML_XYZ_Z_MIN       0.f
#define CML_XYZ_Z_MAX       1.f

#define CML_Yxy_NUMCHANNELS 3
#define CML_Yxy_Y_MIN       0.f
#define CML_Yxy_Y_MAX       1.f
#define CML_Yxy_x_MIN       0.f
#define CML_Yxy_x_MAX       1.f
#define CML_Yxy_y_MIN       0.f
#define CML_Yxy_y_MAX       1.f

#define CML_Yuv_NUMCHANNELS 3
#define CML_Yuv_Y_MIN       0.f
#define CML_Yuv_Y_MAX       1.f
#define CML_Yuv_u_MIN       0.f
#define CML_Yuv_u_MAX       (2.f / 3.f)
#define CML_Yuv_v_MIN       0.f
#define CML_Yuv_v_MAX       (4.f / 9.f)

#define CML_Yupvp_NUMCHANNELS 3
#define CML_Yupvp_Y_MIN     0.f
#define CML_Yupvp_Y_MAX     1.f
#define CML_Yupvp_up_MIN    0.f
#define CML_Yupvp_up_MAX    (2.f / 3.f)
#define CML_Yupvp_vp_MIN    0.f
#define CML_Yupvp_vp_MAX    (2.f / 3.f)

#define CML_Ycd_NUMCHANNELS 3
#define CML_Ycd_Y_MIN       0.f
#define CML_Ycd_Y_MAX       1.f
#define CML_Ycd_c_MIN       0.f
#define CML_Ycd_c_MAX       30.f
#define CML_Ycd_d_MIN       0.f
#define CML_Ycd_d_MAX       4.f

#define CML_Lab_NUMCHANNELS 3
#define CML_Lab_L_MIN       0.f
#define CML_Lab_L_MAX       100.f
#define CML_Lab_a_MIN       -128.f
#define CML_Lab_a_MAX       128.f
#define CML_Lab_b_MIN       -128.f
#define CML_Lab_b_MAX       128.f

#define CML_Lch_NUMCHANNELS 3
#define CML_Lch_L_MIN       0.f
#define CML_Lch_L_MAX       100.f
#define CML_Lch_c_MIN       0.f
#define CML_Lch_c_MAX       128.f
#define CML_Lch_h_MIN       0.f
#define CML_Lch_h_MAX       360.f

#define CML_Luv_NUMCHANNELS 3
#define CML_Luv_L_MIN       0.f
#define CML_Luv_L_MAX       100.f
#define CML_Luv_u_MIN       -100.f
#define CML_Luv_u_MAX       100.f
#define CML_Luv_v_MIN       -100.f
#define CML_Luv_v_MAX       100.f

#define CML_RGB_NUMCHANNELS 3
#define CML_RGB_R_MIN       0.f
#define CML_RGB_R_MAX       1.f
#define CML_RGB_G_MIN       0.f
#define CML_RGB_G_MAX       1.f
#define CML_RGB_B_MIN       0.f
#define CML_RGB_B_MAX       1.f

#define CML_YCbCr_NUMCHANNELS 3
#define CML_YCbCr_Y_MIN     0.f
#define CML_YCbCr_Y_MAX     1.f
#define CML_YCbCr_Cb_MIN    -0.5f
#define CML_YCbCr_Cb_MAX    0.5f
#define CML_YCbCr_Cr_MIN    -0.5f
#define CML_YCbCr_Cr_MAX    0.5f

#define CML_HSV_NUMCHANNELS 3
#define CML_HSV_H_MIN       0.f
#define CML_HSV_H_MAX       360.f
#define CML_HSV_S_MIN       0.f
#define CML_HSV_S_MAX       1.f
#define CML_HSV_V_MIN       0.f
#define CML_HSV_V_MAX       1.f

#define CML_HSL_NUMCHANNELS 3
#define CML_HSL_H_MIN       0.f
#define CML_HSL_H_MAX       360.f
#define CML_HSL_S_MIN       0.f
#define CML_HSL_S_MAX       1.f
#define CML_HSL_L_MIN       0.f
#define CML_HSL_L_MAX       1.f

#define CML_CMYK_NUMCHANNELS 4
#define CML_CMYK_C_MIN       0.f
#define CML_CMYK_C_MAX       1.f
#define CML_CMYK_M_MIN       0.f
#define CML_CMYK_M_MAX       1.f
#define CML_CMYK_Y_MIN       0.f
#define CML_CMYK_Y_MAX       1.f
#define CML_CMYK_K_MIN       0.f
#define CML_CMYK_K_MAX       1.f


// When standardizing the A, B, C and D illuminants, CML_SECOND_RAD had a
// different value. Therefore, a D-Illuminant like D50 does not corresponds
// precisely to 5000 K but rather more to approximately 5003 K. Use the
// following multiplication constants to correct the temperatures.
//
// The official correction factor for the D illuminant is 0.01438 But by
// comparing the CIE values for D illuminations D50 and D65 with the official
// tabulated values, a more accurate correction factor has been determined.
//
// For reference, the following two correction factors have been determined
// and the resulting factor is the average of those two:
// D50: 0.0143814240220373000
// D65: 0.0143813942536130000
#define CML_A_TEMPERATURE_CORRECTION_FACTOR (CML_SECOND_RAD / 1.435e-2f)
#define CML_D_TEMPERATURE_CORRECTION_FACTOR (CML_SECOND_RAD / 1.438141e-2f)

// Or simply use the following constants of some well known illuminations:
#define CML_TEMPERATURE_A        (2848.f * CML_A_TEMPERATURE_CORRECTION_FACTOR)
#define CML_TEMPERATURE_D50      (5000.f * CML_D_TEMPERATURE_CORRECTION_FACTOR)
#define CML_TEMPERATURE_D55      (5500.f * CML_D_TEMPERATURE_CORRECTION_FACTOR)
#define CML_TEMPERATURE_D65      (6500.f * CML_D_TEMPERATURE_CORRECTION_FACTOR)
#define CML_TEMPERATURE_D75      (7500.f * CML_D_TEMPERATURE_CORRECTION_FACTOR)
#define CML_TEMPERATURE_D93      (9300.f * CML_D_TEMPERATURE_CORRECTION_FACTOR)

// In CML, all D illuminants are computed with the official datasets of CIE.
// The datasets are normalized at the following wavelengths:
#define CML_NORMALIZATION_WAVELENGTH_10NM 560.f
#define CML_NORMALIZATION_WAVELENGTH_5NM  555.f

// Currently, CML supports channeled colors of up to 4 channels
#define CML_MAX_NUMBER_OF_CHANNELS 4

#define CML_ADAMS_CHROMATICITY_HUNTER_APPROX_K  (175.f / 198.04f)
#define CML_ADAMS_CHROMATICITY_HUNTER_APPROX_KE (70.f  / 218.11f)
#define CML_ADAMS_CHROMATICITY_HUNTER_ORIGINAL_K  (175.f / 100.f)
#define CML_ADAMS_CHROMATICITY_HUNTER_ORIGINAL_KE (70.f / 175.f)


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

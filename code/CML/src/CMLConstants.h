
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

// Any new ColorMachine has the following default settings:

#define CML_DEFAULT_INTEGRATION_TYPE            CML_INTEGRATION_BINARY_PAIRS
#define CML_DEFAULT_INTEGER_MAPPING             CML_INTEGER_MAPPING_INTERVAL
#define CML_DEFAULT_2DEG_OBSERVER               CML_FUNVEC_OBSERVER_2DEG_CIE_1931
#define CML_DEFAULT_10DEG_OBSERVER              CML_FUNVEC_OBSERVER_10DEG_CIE_1964
#define CML_DEFAULT_8BIT_FLOOR_CUTOFF           0
#define CML_DEFAULT_8BIT_CEIL_CUTOFF            255
#define CML_DEFAULT_16BIT_FLOOR_CUTOFF          0
#define CML_DEFAULT_16BIT_CEIL_CUTOFF           65535
#define CML_DEFAULT_LAB_COLORSPACE              CML_LAB_CIELAB
#define CML_DEFAULT_LAB_LUT_SIZE                32
#define CML_DEFAULT_RGB_COLORSPACE              CML_RGB_sRGB
#define CML_DEFAULT_RGB_LUT_SIZE                32
#define CML_DEFAULT_CMYK_TRANSFORM              CML_CMYK_STANDARD_TRANSFORM
#define CML_DEFAULT_GRAY_COMPUTATION            CML_GRAY_FROM_LSTAR
#define CML_DEFAULT_CHROMATIC_ADAPTATION        CML_CHROMATIC_ADAPTATION_NONE

// The following defaults are used for integration and the cmlFilterFunction
// method with continuous functions.

#define CML_DEFAULT_INTEGRATION_MIN             300.f
#define CML_DEFAULT_INTEGRATION_MAX             830.f
#define CML_DEFAULT_INTEGRATION_STEPSIZE        1.f


// When standardizing the A, B, C and D illuminants, NA_SECOND_RAD had a
// different value. Therefore, a D-Illuminant like D50 does not corresponds
// precisely to 5000 K but rather more to approximately 5003 K. Use the
// following multiplication constants to correct the temperatures.

#define CML_A_TEMPERATURE_CORRECTION_FACTOR (NA_SECOND_RAD / 1.435e-2f)
#define CML_D_TEMPERATURE_CORRECTION_FACTOR (NA_SECOND_RAD / 1.438e-2f)

// Or simply use the following constants of some well known illuminations:

#define CML_TEMPERATURE_A     (2848.f * CML_A_TEMPERATURE_CORRECTION_FACTOR)
#define CML_TEMPERATURE_D50   (5000.f * CML_D_TEMPERATURE_CORRECTION_FACTOR)
#define CML_TEMPERATURE_D55   (5500.f * CML_D_TEMPERATURE_CORRECTION_FACTOR)
#define CML_TEMPERATURE_D65   (6500.f * CML_D_TEMPERATURE_CORRECTION_FACTOR)
#define CML_TEMPERATURE_D75   (7500.f * CML_D_TEMPERATURE_CORRECTION_FACTOR)
#define CML_TEMPERATURE_D93   (9300.f * CML_D_TEMPERATURE_CORRECTION_FACTOR)

// In CML, all D illuminants are computed with the official datasets of CIE.
// The datasets are normalized at the following wavelengths:

#define CML_NORMALIZATION_WAVELENGTH  555.f

// Currently, CML supports channeled colors of up to 4 channels

#define CML_MAX_NUMBER_OF_CHANNELS 4




// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

// Any new ColorMachine has the following default settings:

#define CML_DEFAULT_INTEGRATION_TYPE            CML_INTEGRATION_BINARY_PAIRS
#define CML_DEFAULT_INTEGER_MAPPING             CML_INTEGER_MAPPING_INTERVAL
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
#define CML_Yuv_u_MAX       (2.f/3.f)
#define CML_Yuv_v_MIN       0.f
#define CML_Yuv_v_MAX       (4.f/9.f)

#define CML_Yupvp_NUMCHANNELS 3
#define CML_Yupvp_Y_MIN     0.f
#define CML_Yupvp_Y_MAX     1.f
#define CML_Yupvp_up_MIN    0.f
#define CML_Yupvp_up_MAX    (2.f/3.f)
#define CML_Yupvp_vp_MIN    0.f
#define CML_Yupvp_vp_MAX    (2.f/3.f)

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

#define CML_A_TEMPERATURE_CORRECTION_FACTOR (CML_SECOND_RAD / 1.435e-2f)
#define CML_D_TEMPERATURE_CORRECTION_FACTOR (CML_SECOND_RAD / 1.438e-2f)

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



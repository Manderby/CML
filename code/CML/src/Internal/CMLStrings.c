
#include "CML.h"
#include "cml_.h"

CML_HIDDEN static const char* colortypestrings[CML_NUMBER_OF_COLORTYPES] = {
  "Gray",
  "XYZ",
  "Yxy",
  "Yuv",
  "Yu\'v\'",
  "Lab",
  "Lch",
  "Luv",
  "RGB",
  "YCbCr",
  "HSV",
  "HSL",
  "CMYK",
  "Illumination Spectrum",
  "Remission Spectrum"
};

CML_HIDDEN static const char* observerstrings[CML_NUMBER_OF_OBSERVERS] = {
//  "1931 2 deg (1 nm steps)",                  // CML_OBSERVER_2DEG_1931
//  "1964 10 deg (1 nm steps)",                 // CML_OBSERVER_10DEG_1964
  "CIE 1931 2 deg",     // CML_OBSERVER_2DEG_CIE_1931 (5 nm steps)
  "CIE 1964 10 deg",    // CML_OBSERVER_10DEG_CIE_1964 (5 nm steps)
//  "ISO-13655 2 deg",     // CML_OBSERVER_2DEG_ISO_13655 (10 nm steps)
  "Judd 1951 2 deg",            // CML_OBSERVER_2DEG_JUDD_1951 (10 nm steps)
  "Judd Vos 1978 2 deg",         // CML_OBSERVER_2DEG_JUDD_VOS_1978 (5 nm steps)
//  "Stiles Burch 1955 2 deg (5 nm steps)",     // CML_OBSERVER_2DEG_STILES_BURCH_1955
//  "Shaw Fairchild 1997 2 deg (5 nm steps)",   // CML_OBSERVER_2DEG_SHAW_FAIRCHILD_1997
  "Custom Observer",                          // CML_OBSERVER_CUSTOM
};

CML_HIDDEN static const char* illuminationstrings[CML_NUMBER_OF_ILLUMINATIONS] = {
  "Blackbody",                        // CML_ILLUMINATION_BLACKBODY
  "A (CIE Standard)",                 // CML_ILLUMINATION_A_CIE
  "A (with Planck locus shift)",      // CML_ILLUMINATION_A_EXACT
  "B",                                // CML_ILLUMINATION_B
  "C",                                // CML_ILLUMINATION_C
  "D Illuminant",                     // CML_ILLUMINATION_D_ILLUMINANT
  "D50",                              // CML_ILLUMINATION_D50
  "D55",                              // CML_ILLUMINATION_D55
  "D65",                              // CML_ILLUMINATION_D65
  "D75",                              // CML_ILLUMINATION_D75
  "D93",                              // CML_ILLUMINATION_D93
  "E",                                // CML_ILLUMINATION_E
  "F1 (Daylight)",                    // CML_ILLUMINATION_F1
  "F2 (Cool White)",                  // CML_ILLUMINATION_F2
  "F3 (White)",                       // CML_ILLUMINATION_F3
  "F4 (Warm White)",                  // CML_ILLUMINATION_F4
  "F5 (Daylight)",                    // CML_ILLUMINATION_F5
  "F6 (Lite White)",                  // CML_ILLUMINATION_F6
  "F7 (D65 Simulator)",               // CML_ILLUMINATION_F7
  "F8 (D50 Simulator)",               // CML_ILLUMINATION_F8
  "F9 (Cool White Deluxe)",           // CML_ILLUMINATION_F9
  "F10 (Philips TL85, Ultralume 50)", // CML_ILLUMINATION_F10
  "F11 (Philips TL84, Ultralume 40)", // CML_ILLUMINATION_F11
  "F12 (Philips TL83, Ultralume 30)", // CML_ILLUMINATION_F12
  "Spectrocam Xenon Lamp",            // CML_ILLUMINATION_XENON
  "Custom Whitepoint",                // CML_ILLUMINATION_CUSTOM_WHITEPOINT
  "Custom Spectrum",                  // CML_ILLUMINATION_CUSTOM_SPECTRUM
};

CML_HIDDEN static const char* rgbspacestrings[CML_NUMBER_OF_RGB_SPACES] = {
  "Adobe 98",             // CML_RGB_ADOBE_98
  "Apple",                // CML_RGB_APPLE
  "Best",                 // CML_RGB_BEST
  "Beta",                 // CML_RGB_BETA
  "Bruce",                // CML_RGB_BRUCE
  "CIE"  ,                // CML_RGB_CIE
  "ColorMatch",           // CML_RGB_COLORMATCH
  "Don 4",                // CML_RGB_DON4
  "EBU Monitor",          // CML_RGB_EBU_MONITOR
  "EDI",                  // CML_RGB_ECI
  "Ekta Space PS5",       // CML_RGB_EKTA_SPACE_PS5
  "HDTV",                 // CML_RGB_HDTV
  "Rec. BT.601 (525)",    // CML_RGB_REC_BT_601_525
  "Rec. BT.601 (625)",    // CML_RGB_REC_BT_601_625
  "Rec. BT.709",          // CML_RGB_REC_BT_709
  "Rec. BT.2020",         // CML_RGB_REC_BT_2020
  "Kodak DC",             // CML_RGB_KODAK_DC
  "NTSC 53"  ,            // CML_RGB_NTSC_53
  "PAL/SECAM (EBU 3213)", // CML_RGB_PAL_SECAM_EBU
  "ROMM (Prophoto)",      // CML_RGB_ROMM_PROPHOTO
  "SMPTE-C",              // CML_RGB_SMPTE_C
  "sRGB (IEC 61966 2.1)", // CML_RGB_SRGB
  "Wide Gamut",           // CML_RGB_WIDE_GAMUT
  "Custom",               // CML_RGB_WIDE_GAMUT
};

CML_HIDDEN static const char* labspacestrings[CML_NUMBER_OF_LAB_SPACES] = {
  "CIELAB L*a*b* 1976",           // CML_LAB_CIELAB
  "Custom L",                     // CML_LAB_CUSTOM_L
  "Hunter Lab 1948 Approximated", // CML_LAB_HUNTER_APPROXIMATE
  "Hunter Lab 1948 Original",     // CML_LAB_HUNTER_ORIGINAL
  "Adams chromatic valence",      // CML_LAB_ADAMS_CROMATIC_VALENCE
};

CML_HIDDEN static const char* functionTypestrings[CML_NUMBER_OF_FUNCTION_TYPES] = {
  "Linear",           // CML_FUNCTION_LINEAR
  "Sqrt",             // CML_FUNCTION_SQRT
  "Gamma",            // CML_FUNCTION_GAMMA
  "Gamma, Offset, Linear",   // CML_FUNCTION_GAMMA_LINEAR
  "sRGB",             // CML_FUNCTION_SRGB
  "L*",               // CML_FUNCTION_LSTAR
  "L* Standard",      // CML_FUNCTION_LSTAR_STANDARD
};

CML_HIDDEN static const char* rgbresponsepresetstrings[CML_NUMBER_OF_RESPONSE_CURVE_PRESETS] = {
  "Linear",           // CML_FUNCTION_LINEAR
  "Sqrt",             // CML_FUNCTION_SQRT
  "Gamma Adobe 98",   // CML_RESPONSE_GAMMA_ADOBE_98
  "Gamma 1.8",        // CML_RESPONSE_GAMMA_1_8
  "Gamma 1.9",        // CML_RESPONSE_GAMMA_1_9
  "Gamma 2.2",        // CML_RESPONSE_GAMMA_2_2
  "Gamma Rec BT 10 Bit", // CML_RESPONSE_GAMMA_LINEAR_REC_BT_10BIT
  "Gamma Rec BT 12 Bit", // CML_RESPONSE_GAMMA_LINEAR_REC_BT_12BIT
  "sRGB",             // CML_FUNCTION_SRGB
  "L*",               // CML_FUNCTION_LSTAR
  "L* Standard",      // CML_FUNCTION_LSTAR_STANDARD
};

CML_HIDDEN static const char* graycomputationstrings[CML_NUMBER_OF_GRAY_COMPUTATIONS] = {
  "L (HSL)",              // CML_GRAY_FROM_HSL
  "V (HSV)",              // CML_GRAY_FROM_HSV
  "G (RGB)",              // CML_GRAY_FROM_G
  "L* (CIELAB, Luv)",     // CML_GRAY_FROM_LSTAR
  "L (Lab, Lch)",         // CML_GRAY_FROM_L
  "Y (XYZ, Yxy, Yuv)",    // CML_GRAY_FROM_Y
  "Y' (YCbCr)",           // CML_GRAY_FROM_YPRIME
};

CML_HIDDEN static const char* cmyktransformstrings[CML_NUMBER_OF_CMYK_TRANSFORMS] = {
  "Standard",           // CML_CMYK_STANDARD_TRANSFORM
  "UCR",                // CML_CMYK_UCR_TRANSFORM
//  "GCR",              // CML_CMYK_GCR_TRANSFORM
};

CML_HIDDEN static const char* chromaticAdaptationstrings[CML_NUMBER_OF_CHROMATIC_ADAPTATIONS] = {
  "No adaptation",      // CML_CHROMATIC_ADAPTATION_NONE
  "XYZ scaling",        // CML_CHROMATIC_ADAPTATION_XYZ_SCALING
  "Bradford",           // CML_CHROMATIC_ADAPTATION_BRADFORD
  "Von Kries"           // CML_CHROMATIC_ADAPTATION_VON_KRIES
};


CML_API const char* cmlGetColorTypeString(CMLColorType colorType){
  return colortypestrings[colorType];
}
CML_API const char* cmlGetObserverTypeString(CMLObserverType observerType){
  return observerstrings[observerType];
}
CML_API const char* cmlGetIlluminationTypeString(CMLIlluminationType illuminationType){
  return illuminationstrings[illuminationType];
}
CML_API const char* cmlGetChromaticAdaptationTypeString(CMLChromaticAdaptationType chromaticAdaptationType){
  return chromaticAdaptationstrings[chromaticAdaptationType];
}
CML_API const char* cmlGetLabSpaceTypeString(CMLLabColorSpaceType labSpaceType){
  return labspacestrings[labSpaceType];
}
CML_API const char* cmlGetRGBResponsePresetString(CMLResponseCurvePreset preset){
  return rgbresponsepresetstrings[preset];
}
CML_API const char* cmlGetFunctionTypeString(CMLFunctionType functionType){
  return functionTypestrings[functionType];
}
CML_API const char* cmlGetRGBColorspaceString(CMLRGBColorSpace colorSpaceType){
  return rgbspacestrings[colorSpaceType];
}
CML_API const char* cmlGetCMYKTransformTypeString(CMLCMYKTransformType transformType){
  return cmyktransformstrings[transformType];
}
CML_API const char* cmlGetGrayComputationTypeString(CMLGrayComputationType computationType){
  return graycomputationstrings[computationType];
}



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

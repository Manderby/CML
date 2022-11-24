
#include "../CML.h"
#include "CMLInternal.h"

CML_HDEF const char* colorTypeStrings[CML_COLOR_COUNT] = {
  "CMYK",
  "Gray",
  "HSL",
  "HSV",
  "Lab",
  "Lch",
  "Luv",
  "RGB",
  "Illumination Spectrum",
  "Remission Spectrum",
  "UVW",
  "XYZ",
  "YCbCr",
  "Ycd",
  "Yu\'v\'",
  "Yuv",
  "Yxy",
};

CML_HDEF const char* integrationMethodStrings[CML_INTEGRATION_COUNT] = {
  "Simple",
  "Binary Pairs",
};

CML_HDEF const char* integerMappingStrings[CML_INTEGER_MAPPING_COUNT] = {
  "Floor",
  "Box",
  "Interval",
};

CML_HDEF const char* observerStrings[CML_OBSERVER_COUNT] = {
  "CIE 1931 2 deg",              // CML_OBSERVER_2DEG_CIE_1931 (5 nm steps)
  "CIE 1964 10 deg",             // CML_OBSERVER_10DEG_CIE_1964 (5 nm steps)
  "ISO-13655 2 deg",             // CML_OBSERVER_2DEG_ISO_13655 (10 nm steps)
  "Judd 1951 2 deg",             // CML_OBSERVER_2DEG_JUDD_1951 (10 nm steps)
  "Judd Vos 1978 2 deg",         // CML_OBSERVER_2DEG_JUDD_VOS_1978 (5 nm steps)
  "Shaw Fairchild 1997 2 deg",   // CML_OBSERVER_2DEG_SHAW_FAIRCHILD_1997 (5 nm steps)
  "Custom Observer",             // CML_OBSERVER_CUSTOM
};

CML_HDEF const char* illuminationStrings[CML_ILLUMINATION_COUNT] = {
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
  "Custom WhitePoint",                // CML_ILLUMINATION_CUSTOM_WHITEPOINT
  "Custom Spectrum",                  // CML_ILLUMINATION_CUSTOM_SPECTRUM
};

CML_HDEF const char* rgbColorSpaceStrings[CML_RGB_COUNT] = {
  "Adobe 98",             // CML_RGB_ADOBE_98
  "Apple",                // CML_RGB_APPLE
  "Best",                 // CML_RGB_BEST
  "Beta",                 // CML_RGB_BETA
  "Bruce",                // CML_RGB_BRUCE
  "CIE",                  // CML_RGB_CIE
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
  "NTSC 53",              // CML_RGB_NTSC_53
  "PAL/SECAM (EBU 3213)", // CML_RGB_PAL_SECAM_EBU
  "ROMM (Prophoto)",      // CML_RGB_ROMM_PROPHOTO
  "SMPTE-C",              // CML_RGB_SMPTE_C
  "sRGB (IEC 61966 2.1)", // CML_RGB_SRGB
  "Wide Gamut",           // CML_RGB_WIDE_GAMUT
  "Custom",               // CML_RGB_WIDE_GAMUT
};

CML_HDEF const char* labColorSpaceStrings[CML_LAB_COUNT] = {
  "CIELAB L*a*b* 1976",           // CML_LAB_CIELAB
  "Custom L",                     // CML_LAB_CUSTOM_L
  "Hunter Lab 1948 Approximated", // CML_LAB_HUNTER_APPROXIMATE
  "Hunter Lab 1948 Original",     // CML_LAB_HUNTER_ORIGINAL
  "Adams chromatic valence",      // CML_LAB_ADAMS_CROMATIC_VALENCE
};

CML_HDEF const char* functionTypeStrings[CML_FUNCTION_COUNT] = {
  "Undefined",             // CML_FUNCTION_UNDEFINED
  "Linear",                // CML_FUNCTION_LINEAR
  "Sqrt",                  // CML_FUNCTION_SQRT
  "Gamma",                 // CML_FUNCTION_GAMMA
  "Gamma, Offset, Linear", // CML_FUNCTION_GAMMA_LINEAR
  "sRGB",                  // CML_FUNCTION_SRGB
  "L*",                    // CML_FUNCTION_LSTAR
  "L* Standard",           // CML_FUNCTION_LSTAR_STANDARD
};

CML_HDEF const char* rgbResponseTypeStrings[CML_RESPONSE_COUNT] = {
  "Undefined",             // CML_RESPONSE_UNDEFINED
  "Linear",                // CML_RESPONSE_LINEAR
  "Gamma 1.8",             // CML_RESPONSE_GAMMA_1_8
  "Gamma 1.9",             // CML_RESPONSE_GAMMA_1_9
  "Gamma 2.0",             // CML_RESPONSE_GAMMA_2_0
  "Gamma Adobe 98",        // CML_RESPONSE_GAMMA_ADOBE_98
  "Gamma 2.2",             // CML_RESPONSE_GAMMA_2_2
  "Gamma Rec BT 10 Bit",   // CML_RESPONSE_GAMMA_LINEAR_REC_BT_10BIT
  "Gamma Rec BT 12 Bit",   // CML_RESPONSE_GAMMA_LINEAR_REC_BT_12BIT
  "sRGB",                  // CML_RESPONSE_SRGB
  "L*",                    // CML_RESPONSE_LSTAR
  "L* Standard",           // CML_RESPONSE_LSTAR_STANDARD
  "Custom Gamma",          // CML_RESPONSE_CUSTOM_GAMMA
  "Custom Gamma + Linear", // CML_RESPONSE_CUSTOM_GAMMA_LINEAR
};

CML_HDEF const char* grayComputationStrings[CML_GRAY_COUNT] = {
  "L (HSL)",             // CML_GRAY_FROM_HSL
  "V (HSV)",             // CML_GRAY_FROM_HSV
  "G (RGB)",             // CML_GRAY_FROM_G
  "L* (CIELAB, Luv)",    // CML_GRAY_FROM_LSTAR
  "L (Lab, Lch)",        // CML_GRAY_FROM_L
  "Y (XYZ, Yxy, Yuv)",   // CML_GRAY_FROM_Y
  "Y' (YCbCr)",          // CML_GRAY_FROM_YPRIME
};

CML_HDEF const char* cmykTransformStrings[CML_CMYK_COUNT] = {
  "Standard",            // CML_CMYK_STANDARD_TRANSFORM
  "UCR",                 // CML_CMYK_UCR_TRANSFORM
//  "GCR",               // CML_CMYK_GCR_TRANSFORM
};

CML_HDEF const char* chromaticAdaptationStrings[CML_CHROMATIC_ADAPTATION_COUNT] = {
  "No adaptation",       // CML_CHROMATIC_ADAPTATION_NONE
  "XYZ scaling",         // CML_CHROMATIC_ADAPTATION_XYZ_SCALING
  "Bradford",            // CML_CHROMATIC_ADAPTATION_BRADFORD
  "Von Kries"            // CML_CHROMATIC_ADAPTATION_VON_KRIES
};



CML_DEF const char* cmlGetColorTypeString(CMLColorType colorType){
  return colorTypeStrings[colorType];
}
CML_DEF const char* cmlGetObserverTypeString(CMLObserverType observerType){
  return observerStrings[observerType];
}
CML_DEF const char* cmlGetIntegrationMethodString(CMLIntegrationMethod integrationMethod){
  return integrationMethodStrings[integrationMethod];
}
CML_DEF const char* cmlGetIntegerMappingString(CMLIntegerMappingType integerMappingType){
  return integerMappingStrings[integerMappingType];
}
CML_DEF const char* cmlGetIlluminationTypeString(CMLIlluminationType illuminationType){
  return illuminationStrings[illuminationType];
}
CML_DEF const char* cmlGetChromaticAdaptationTypeString(CMLChromaticAdaptationType chromaticAdaptationType){
  return chromaticAdaptationStrings[chromaticAdaptationType];
}
CML_DEF const char* cmlGetLabColorSpaceTypeString(CMLLabColorSpaceType type){
  return labColorSpaceStrings[type];
}
CML_DEF const char* cmlGetRGBResponseTypeString(CMLResponseCurveType type){
  return rgbResponseTypeStrings[type];
}
CML_DEF const char* cmlGetFunctionTypeString(CMLFunctionType functionType){
  return functionTypeStrings[functionType];
}
CML_DEF const char* cmlGetRGBColorSpaceTypeString(CMLRGBColorSpaceType type){
  return rgbColorSpaceStrings[type];
}
CML_DEF const char* cmlGetCMYKTransformTypeString(cml_CMYKTransformType transformType){
  return cmykTransformStrings[transformType];
}
CML_DEF const char* cmlGetGrayComputationTypeString(CMLGrayComputationType computationType){
  return grayComputationStrings[computationType];
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

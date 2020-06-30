
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

#include "CML.h"
#include "StateMachine/CMLColorMachineState.h"
#include "NAString.h"
#include <stdarg.h>


CML_HIDDEN CMLContext* cmlc; // the current active CML context






CML_HIDDEN CMLColorspaceClass* cml_GetContextColorspaceClass(CMLColorspaceType colorspaceType, CMLEncoding encoding){
  CMLColorspaceAbstract* abstract = cml_GetContextColorspaceAbstract(colorspaceType);
  CMLMOBEncoding* encodingMOB = cml_GetContextEncodingMOB(encoding);
  CMLColorspaceClass* colorspaceClass = mobGetKeyObject(abstract, encodingMOB);
  if(!colorspaceClass){
    #ifndef NDEBUG
      cmlError("cml_GetContextColorspaceClass", "Colorspace class not registered. Will automatically create a default implementation...");
    #endif
    cmlRegisterMinMaxComponentFunctions(colorspaceType, encoding, CML_NULL, CML_NULL);
    colorspaceClass = mobGetKeyObject(abstract, encodingMOB);
    #ifndef NDEBUG
      if(!colorspaceClass)
        cmlError("cml_GetContextColorspaceClass", "Fatal error. Automatically created colorspace class not present.");
    #endif
  }
  return colorspaceClass;
}


CML_API CMLContext* cmlActivateContext(CMLContext* context){
  if(context){
    cmlc = context;
    mobActivateContext(cmlc->mobc);
  }else{
    context = naAlloc(CMLContext);
    
    #ifndef NDEBUG
      context->version = -CML_VERSION;
    #else
      context->version = CML_VERSION;
    #endif

    // Set the new context as the active context and build up the whole
    // library from scratch.
    cmlc = context;
    cmlc->curobject = CML_NULL;
    cmlc->mobc = mobActivateContext(MOB_NULL);
    
    cmlc->objectKeys[CML_FUNCTION_OBJECT] = mobCreateString("CML_Function");
    cmlc->objectKeys[CML_FUNCTION_VECTOR_OBJECT] = mobCreateString("CML_Function_Vector");
    cmlc->objectKeys[CML_ILLUMINATION_OBJECT] = mobCreateString("CML_Illumination");
    cmlc->objectKeys[CML_RESPONSE_CURVE_OBJECT] = mobCreateString("CML_Response_Curve");
    cmlc->objectKeys[CML_COLORSPACE_OBJECT] = mobCreateString("CML_Colorspace");
    cmlc->objectKeys[CML_COLORSPACE_ABSTRACT_OBJECT] = mobCreateString("CML_Colorspace_Abstract_Class");
    cmlc->objectKeys[CML_COLORSPACE_CLASS_OBJECT] = mobCreateString("CML_Colorspace_Class");
    cmlc->objectKeys[CML_COMPONENT_OBJECT] = mobCreateString("CML_Component");
    cmlc->objectKeys[CML_SETTING_CLASS_OBJECT] = mobCreateString("Colorspace Setting");
    cmlc->objectKeys[CML_CONVERTER_UNIT_OBJECT] = mobCreateString("CML_Converter");
    cmlc->objectKeys[CML_CONVERTER_CLASS_OBJECT] = mobCreateString("CML_Converter_Class");
    cmlc->objectKeys[CML_FUNCTION_STEPSIZE] = mobCreateString("Integration stepsize");
    cmlc->objectKeys[CML_FUNCTION_MIN_SAMPLE_COORD] = mobCreateString("Minimum coordinate with interpolation data");
    cmlc->objectKeys[CML_FUNCTION_MAX_SAMPLE_COORD] = mobCreateString("Maximum coordinate with interpolation data");
    cmlc->objectKeys[CML_FUNCTION_MIN_NON_TRIVIAL_COORD] = mobCreateString("Minimum coordinate for integration");
    cmlc->objectKeys[CML_FUNCTION_MAX_NON_TRIVIAL_COORD] = mobCreateString("Maximum coordinate for integration");
    cmlc->objectKeys[CML_FUNCTION_EVALUATOR] = mobCreateString("Evaluation function");
    cmlc->objectKeys[CML_TEMPERATURE_K] = mobCreateString("Temperature in [Kelvin]");
    cmlc->objectKeys[CML_BLACKBODY_FACTOR_c] = mobCreateString("Blackbody computation factor c");
    cmlc->objectKeys[CML_GAMMA] = mobCreateString("Gamma");
    cmlc->objectKeys[CML_INV_GAMMA] = mobCreateString("Inverse Gamma");
    cmlc->objectKeys[CML_CURVE_OFFSET] = mobCreateString("Offset");
    cmlc->objectKeys[CML_LINEAR_SCALE] = mobCreateString("Scale factor of linear part");
    cmlc->objectKeys[CML_INV_LINEAR_SCALE] = mobCreateString("Inverse scale factor of linear part");
    cmlc->objectKeys[CML_CURVE_SCALE] = mobCreateString("Scale factor of curve part");
    cmlc->objectKeys[CML_INV_CURVE_SCALE] = mobCreateString("Inverse scale factor of curve part");
    cmlc->objectKeys[CML_LINEAR_CURVE_SPLIT] = mobCreateString("Split point between linear and curve part");
    cmlc->objectKeys[CML_INV_LINEAR_CURVE_SPLIT] = mobCreateString("Inverse split point between linear and curve part");
    cmlc->objectKeys[CML_CONST_VALUE] = mobCreateString("Constant value");
    cmlc->objectKeys[CML_BINOMIAL_VALUE_n] = mobCreateString("Binomial distribution value n");
    cmlc->objectKeys[CML_BINOMIAL_VALUE_k] = mobCreateString("Binomial distribution value k");
    cmlc->objectKeys[CML_BINOMIAL_n_MINUS_k] = mobCreateString("Binomial distribution n - k");
    cmlc->objectKeys[CML_BINOMIAL_BINOM] = mobCreateString("Binomial distribution binomial coefficient");
    cmlc->objectKeys[CML_BINOMIAL_INV_RANGE] = mobCreateString("Inverse of binomial distribution range");
    cmlc->objectKeys[CML_GAUSS_VALUE_mu] = mobCreateString("Gauss distribution mu coefficient");
    cmlc->objectKeys[CML_GAUSS_VALUE_sigma] = mobCreateString("Gauss distribution sigma coefficient");
    cmlc->objectKeys[CML_GAUSS_VALUE_invsigma] = mobCreateString("Gauss distribution inverse sigma coefficient");
    cmlc->objectKeys[CML_COMPOSITE_FUNCTION_1] = mobCreateString("Composite function 1");
    cmlc->objectKeys[CML_COMPOSITE_FUNCTION_2] = mobCreateString("Composite function 2");
    cmlc->objectKeys[CML_COMPOSITE_FACTOR_2] = mobCreateString("Composite factor 2");
    cmlc->objectKeys[CML_ARRAY_FUNCTION_DOWN_EXTRAPOLATION_METHOD] = mobCreateString("Method for extrapolating values below definition range");
    cmlc->objectKeys[CML_ARRAY_FUNCTION_INTERPOLATION_METHOD] = mobCreateString("Method for interpolating values");
    cmlc->objectKeys[CML_ARRAY_FUNCTION_UP_EXTRAPOLATION_METHOD] = mobCreateString("Method for extrapolating values above definition range");
    cmlc->objectKeys[CML_ARRAY_FUNCTION_DOWN_EXTRAPOLATION_FUNCTION] = mobCreateString("Callback for extrapolating values below definition range");
    cmlc->objectKeys[CML_ARRAY_FUNCTION_INTERPOLATION_FUNCTION] = mobCreateString("Callback for interpolating values");
    cmlc->objectKeys[CML_ARRAY_FUNCTION_UP_EXTRAPOLATION_FUNCTION] = mobCreateString("Callback for extrapolating values above definition range");
    cmlc->objectKeys[CML_ARRAY_FUNCTION_INV_INTERVAL] = mobCreateString("Inverse of interval");
    cmlc->objectKeys[CML_ARRAY_FUNCTION_VALUE_ARRAY] = mobCreateString("Array storing float values");
    cmlc->objectKeys[CML_ARRAY_FUNCTION_VALUE_ARRAY_ENTRYCOUNT] = mobCreateString("The number of entries in the array");

    cmlc->objectKeys[CML_SETTING_DEFAULT_OBJECT] = mobCreateString("Default object for setting");

    cmlc->objectKeys[CML_RESPONSE_CURVE_TYPE] = mobCreateString("The curve type");
    cmlc->objectKeys[CML_RESPONSE_CURVE_FORWARD_FUNCTION] = mobCreateString("Forward function (From XYZ)");
    cmlc->objectKeys[CML_RESPONSE_CURVE_BACKWARD_FUNCTION] = mobCreateString("Backward function (To XYZ)");
    cmlc->objectKeys[CML_FUNCTION_VECTOR_NORMALIZATION_WAVELENGTH] = mobCreateString("Normalization wavelength");
    cmlc->objectKeys[CML_FUNCTION_VECTOR_MAIN_FUNCTION_INDEX] = mobCreateString("Main function index");
    cmlc->objectKeys[CML_FUNCTION_VECTOR_NORMALIZATION_FACTOR] = mobCreateString("Normalization factor");
    cmlc->objectKeys[CML_FUNCTION_VECTOR_PRESET] = mobCreateString("Preset number");
    cmlc->objectKeys[CML_FUNCTION_VECTOR_COUNT] = mobCreateString("Number of functions");
    cmlc->objectKeys[CML_FUNCTION_VECTOR_FUNCTIONS] = mobCreateString("The functions");
    cmlc->objectKeys[CML_COLORSPACE_ABSTRACT_TYPE] = mobCreateString("Type of colorspace class");
    cmlc->objectKeys[CML_COLORSPACE_CLASS_ENCODING] = mobCreateString("Encoding of colorspace class");
    cmlc->objectKeys[CML_COLORSPACE_CLASS] = mobCreateString("Class of Colorspace");
    cmlc->objectKeys[CML_COLORSPACE_ABSTRACT] = mobCreateString("Abstract Class of Colorspace");

    cmlc->objectKeys[CML_COLORSPACE_ABSTRACT_COMPONENT] = mobCreateString("Colorspace class component");
    cmlc->objectKeys[CML_COLORSPACE_ABSTRACT_MAIN_COMPONENT_INDEX] = mobCreateString("Colorspace class main component");
    cmlc->objectKeys[CML_COLORSPACE_ABSTRACT_NAME] = mobCreateString("Colorspace name");
    cmlc->objectKeys[CML_COLORSPACE_CLASS_REQUIRED_SETTING_CLASSES] = mobCreateString("Colorspace class required settings");
    cmlc->objectKeys[CML_COLORSPACE_CLASS_OUT_CONVERTER_CLASSES] = mobCreateString("List of out converters");
    cmlc->objectKeys[CML_COLORSPACE_CLASS_IN_CONVERTER_CLASSES] = mobCreateString("List of in converters");
    cmlc->objectKeys[CML_COLORSPACE_ABSTRACT_DEFAULT_SETTING_CONSTRUCTOR] = mobCreateString("Default constructor of settings of a colorspace class");
    cmlc->objectKeys[CML_COLORSPACE_CLASS_MIN_COMPONENT_FUNCTION] = mobCreateString("Min function for colorspace component");
    cmlc->objectKeys[CML_COLORSPACE_CLASS_MAX_COMPONENT_FUNCTION] = mobCreateString("Max function for colorspace component");

    cmlc->objectKeys[CML_COMPONENT_TYPE] = mobCreateString("Color Component Type");
    cmlc->objectKeys[CML_COMPONENT_NAME] = mobCreateString("Color Component Label");

    cmlc->objectKeys[CML_CONVERTER_CONSTRUCTOR] = mobCreateString("Converter constructor");
    cmlc->objectKeys[CML_CONVERTER_UNIT_DST_COLORSPACE] = mobCreateString("Destination colorspace");
    cmlc->objectKeys[CML_CONVERTER_UNIT_SRC_COLORSPACE] = mobCreateString("Source colorspace");

    cmlc->objectKeys[CML_ERROR] = mobCreateString("Error number");

    cmlc->objectKeys[CML_CONVERTER_CLASS_DST_COLORSPACE_CLASS] = mobCreateString("Dst Colorspace class");
    cmlc->objectKeys[CML_CONVERTER_CLASS_SRC_COLORSPACE_CLASS] = mobCreateString("Src Colorspace class");
    cmlc->objectKeys[CML_SETTING_CLASS_NAME] = mobCreateString("Setting class name");
    cmlc->objectKeys[CML_COLORSPACE_SETTING_CLASS_CONSTRUCTOR] = mobCreateString("Colorspace Setting class constructor");
    cmlc->objectKeys[CML_CONVERTER_SETTING_CLASS_CONSTRUCTOR] = mobCreateString("Converter Setting class constructor");
    cmlc->objectKeys[CML_SETTING_CLASS_ID] = mobCreateString("Setting class ID");

    cmlc->objectKeys[CML_CONVERTER_UNIT_COST] = mobCreateString("Computation cost of converter unit");
    cmlc->objectKeys[CML_CONVERTER_CLASS_EQUS_SETTING] = mobCreateString("ConverterClass equs setting of SettingClass");
    cmlc->objectKeys[CML_CONVERTER_CLASS_ADDS_SETTING] = mobCreateString("ConverterClass adds setting of SettingClass");
    cmlc->objectKeys[CML_CONVERTER_CLASS_SUBS_SETTING] = mobCreateString("ConverterClass subs setting of SettingClass");
    cmlc->objectKeys[CML_CONVERTER_CLASS_ALTS_SETTING] = mobCreateString("ConverterClass alts setting of SettingClass");
    cmlc->objectKeys[CML_CONVERTER_CLASS_CONS_SETTING] = mobCreateString("ConverterClass cons setting of SettingClass");

    cmlc->objectKeys[CML_CONVERTER_CLASS_REQUESTER] = mobCreateString("ConverterClass requester");
    cmlc->objectKeys[CML_CONVERTER_CLASS_EVALUATOR] = mobCreateString("ConverterClass evaluator");
    cmlc->objectKeys[CML_CONVERTER_CLASS_EVALUATOR_SB] = mobCreateString("ConverterClass SB evaluator");

    cmlc->objectKeys[CML_OBSERVER_METRIC_SCALE] = mobCreateString("Metric scale of observer");
    cmlc->objectKeys[CML_OBSERVER_FUNCTIONS] = mobCreateString("Functions of observer");
    cmlc->objectKeys[CML_OBSERVER_ADAPTATION_WHITE_SPECTRUM] = mobCreateString("Adaptation spectrum of observer");
    cmlc->objectKeys[CML_OBSERVER_ADAPTATION_WHITE_XYZ] = mobCreateString("Adaptation XYZ of observer");
    cmlc->objectKeys[CML_OBSERVER_ADAPTATION_WHITE_InvXYZ] = mobCreateString("Adaptation InvXYZ of observer");
    cmlc->objectKeys[CML_OBSERVER_ADAPTATION_WHITE_Yxy] = mobCreateString("Adaptation Yxy of observer");
    cmlc->objectKeys[CML_OBSERVER_ADAPTATION_WHITE_Yupvp] = mobCreateString("Adaptation Yupvp of observer");

    cmlc->objectKeys[CML_GENERATOR_METRIC_SCALE] = mobCreateString("Metric scale of generator");
    cmlc->objectKeys[CML_GENERATOR_FUNCTIONS] = mobCreateString("Functions of generator");
    cmlc->objectKeys[CML_GENERATOR_WHITE_SPECTRUM] = mobCreateString("White spectrum of generator");
    cmlc->objectKeys[CML_GENERATOR_WHITE_XYZ] = mobCreateString("White XYZ of observer");
    cmlc->objectKeys[CML_GENERATOR_WHITE_InvXYZ] = mobCreateString("White InvXYZ of observer");
    cmlc->objectKeys[CML_GENERATOR_PRIMARY_RED_Yxy] = mobCreateString("Red Yxy primary of observer");
    cmlc->objectKeys[CML_GENERATOR_PRIMARY_BLUE_Yxy] = mobCreateString("Blue Yxy primary of observer");

    cmlc->objectKeys[CML_COLOR_COLORSPACE] = mobCreateString("Colorspace of color");

    #ifndef NDEBUG
      if(sizeof(CMLColorspaceSettingConstructor) != sizeof(CMLConverterSettingConstructor))
        naCrash("Cannot store function pointers");
    #endif
    cmlc->informationUnits[CML_UNIT_FUNCTION_EVALUATOR]                   = mobRegisterUnit(sizeof(CMLFunctionEvaluator), "Function evaluator");
    cmlc->informationUnits[CML_UNIT_COLORSPACE_SETTING_CONSTRUCTOR]       = mobRegisterUnit(sizeof(CMLColorspaceSettingConstructor), "Colorspace Setting constructor");
    cmlc->informationUnits[CML_UNIT_CONVERTER_SETTING_CONSTRUCTOR]        = mobRegisterUnit(sizeof(CMLConverterSettingConstructor), "Converter Setting constructor");
    cmlc->informationUnits[CML_UNIT_COLORSPACE_COMPONENT_MINMAX_FUNCTION] = mobRegisterUnit(sizeof(CMLMinMaxComponentFunction), "Colorspace component minmax function");
    cmlc->informationUnits[CML_UNIT_CONVERTER_REQUESTER]                  = mobRegisterUnit(sizeof(CMLConverterRequester), "Converter requester");
    cmlc->informationUnits[CML_UNIT_CONVERTER_EVALUATOR]                  = mobRegisterUnit(sizeof(CMLConverterEvaluator), "Converter evaluator");
    cmlc->informationUnits[CML_UNIT_CONVERTER_EVALUATOR_SB]               = mobRegisterUnit(sizeof(CMLConverterSBEvaluator), "Converter SB evaluator");

    // Bootstrap all Colorspace Settings
    naInitStack(&(context->settingClasses), sizeof(CMLSettingClass*), 2);
    cml_BOOTSTRAPRegisterColorspaceSettingClass(CML_SETTING_OBSERVER,                 "Observer",                         cml_CreateSettingObserver);
    cml_BOOTSTRAPRegisterColorspaceSettingClass(CML_SETTING_GENERATOR,                "Generator",                        cml_CreateSettingGenerator);
    cml_BOOTSTRAPRegisterColorspaceSettingClass(CML_SETTING_CHANNEL_RESPONSE_CURVES,  "Response curves",                  cml_CreateSettingResponseCurves);
    cml_BOOTSTRAPRegisterColorspaceSettingClass(CML_SETTING_ILLUMINATION_SPECTRUM,    "Illumination spectrum",            cml_CreateSettingIlluminationSpectrum);
    
    // Bootstrap all Converter Settings
    cml_BOOTSTRAPRegisterConverterSettingClass(CML_SETTING_OBS_TO_GEN_MATRIX,         "Observer to Generator matrix",     cml_CreateSettingObsToGenMatrix);
    cml_BOOTSTRAPRegisterConverterSettingClass(CML_SETTING_GEN_TO_OBS_MATRIX,         "Generator to Observer matrix",     cml_CreateSettingGenToObsMatrix);
    cml_BOOTSTRAPRegisterConverterSettingClass(CML_SETTING_COMPONENTS_OFFSETS,        "Normalization offsets",            cml_CreateSettingComponentsOffsets);
    cml_BOOTSTRAPRegisterConverterSettingClass(CML_SETTING_COMPONENTS_RANGES,         "Normalization ranges",             cml_CreateSettingComponentsRanges);

    // Bootstrap all Encodings
    naInitStack(&(context->encodings), sizeof(CMLMOBEncoding*), 2);
    cml_BOOTSTRAPRegisterEncoding(CML_ENCODING_NORM);
    cml_BOOTSTRAPRegisterEncoding(CML_ENCODING_FLOAT);

    // Bootstrap all Colorspaces
    naInitStack(&(context->colorspaceabstracts), sizeof(CMLColorspaceClass*), 2);
    cml_BOOTSTRAPRegisterColorspaceType(CML_Radiometric,  "Radiometric space",  cml_DefineRadiometricSpaceValences);
    cml_BOOTSTRAPRegisterColorspaceType(CML_Remission,    "Remission space",    cml_DefineRemissionSpaceValences);
    cml_BOOTSTRAPRegisterColorspaceType(CML_XYZ,          "XYZ space",          cml_DefineXYZSpaceValences);
    cml_BOOTSTRAPRegisterColorspaceType(CML_Yxy,          "Yxy space",          cml_DefineYxySpaceValences);
    cml_BOOTSTRAPRegisterColorspaceType(CML_Yupvp,        "Yu\'v\' space",      cml_DefineYupvpSpaceValences);
    cml_BOOTSTRAPRegisterColorspaceType(CML_Yuv,          "Yuv space",          cml_DefineYuvSpaceValences);
    cml_BOOTSTRAPRegisterColorspaceType(CML_Luv,          "Luv space",          cml_DefineLuvSpaceValences);
    cml_BOOTSTRAPRegisterColorspaceType(CML_Lab,          "Lab space",          cml_DefineLabSpaceValences);
    cml_BOOTSTRAPRegisterColorspaceType(CML_Lch,          "Lch space",          cml_DefineLchSpaceValences);
    cml_BOOTSTRAPRegisterColorspaceType(CML_RGB,          "RGB space",          cml_DefineRGBSpaceValences);
    cml_BOOTSTRAPRegisterColorspaceType(CML_YCbCr,        "YCbCr space",        cml_DefineYCbCrSpaceValences);
    cml_BOOTSTRAPRegisterColorspaceType(CML_HSV,          "HSV space",          cml_DefineHSVSpaceValences);
    cml_BOOTSTRAPRegisterColorspaceType(CML_HSL,          "HSL space",          cml_DefineHSLSpaceValences);

    // Manually prepare the colorspace classes
    cmlRegisterMinMaxComponentFunctions(CML_Radiometric, CML_ENCODING_FLOAT, CML_NULL, CML_NULL);
    cmlRegisterMinMaxComponentFunctions(CML_Remission,   CML_ENCODING_FLOAT, CML_NULL, CML_NULL);
    cmlRegisterMinMaxComponentFunctions(CML_XYZ,         CML_ENCODING_FLOAT, CML_NULL, cml_XYZScalarComponentMax);
    cmlRegisterMinMaxComponentFunctions(CML_Yxy,         CML_ENCODING_FLOAT, CML_NULL, cml_YxyScalarComponentMax);
    cmlRegisterMinMaxComponentFunctions(CML_Yupvp,       CML_ENCODING_FLOAT, CML_NULL, cml_YupvpScalarComponentMax);
    cmlRegisterMinMaxComponentFunctions(CML_Yuv,         CML_ENCODING_FLOAT, CML_NULL, cml_YuvScalarComponentMax);
    cmlRegisterMinMaxComponentFunctions(CML_Luv,         CML_ENCODING_FLOAT, cml_LuvScalarComponentMin, cml_LuvScalarComponentMax);
    cmlRegisterMinMaxComponentFunctions(CML_Lab,         CML_ENCODING_FLOAT, cml_LabScalarComponentMin, cml_LabScalarComponentMax);
    cmlRegisterMinMaxComponentFunctions(CML_Lch,         CML_ENCODING_FLOAT, CML_NULL, cml_LchScalarComponentMax);
    cmlRegisterMinMaxComponentFunctions(CML_RGB,         CML_ENCODING_FLOAT, CML_NULL, CML_NULL);
    cmlRegisterMinMaxComponentFunctions(CML_YCbCr,       CML_ENCODING_FLOAT, cml_YCbCrScalarComponentMin, cml_YCbCrScalarComponentMax);
    cmlRegisterMinMaxComponentFunctions(CML_HSV,         CML_ENCODING_FLOAT, CML_NULL, cml_HSVScalarComponentMax);
    cmlRegisterMinMaxComponentFunctions(CML_HSL,         CML_ENCODING_FLOAT, CML_NULL, cml_HSLScalarComponentMax);

    // Create all converterUnits
    cmlRegisterConverterUnit(CML_Radiometric, CML_ENCODING_FLOAT, CML_Remission,    CML_ENCODING_FLOAT, cml_RemissionToRadiometricRequester, cml_RemissionToRadiometric,   CML_NULL);
    cmlRegisterConverterUnit(CML_Remission,   CML_ENCODING_FLOAT, CML_Radiometric,  CML_ENCODING_FLOAT, CML_NULL, cml_RadiometricToRemission,   CML_NULL);
//    cmlRegisterConverterUnit(CML_XYZ,         CML_ENCODING_FLOAT, CML_Radiometric,  CML_ENCODING_FLOAT, CML_NULL,        cml_RadiometricToXYZ,         CML_NULL);
//    cmlRegisterConverterUnit(CML_Radiometric, CML_ENCODING_FLOAT, CML_RGB,          CML_ENCODING_FLOAT, CML_NULL,                cml_RGBToRadiometric,         CML_NULL);
    cmlRegisterConverterUnit(CML_Yxy,         CML_ENCODING_FLOAT, CML_XYZ,          CML_ENCODING_FLOAT, CML_NULL,                cml_XYZToYxy,                 cml_XYZToYxy_SB);
    cmlRegisterConverterUnit(CML_XYZ,         CML_ENCODING_FLOAT, CML_Yxy,          CML_ENCODING_FLOAT, CML_NULL,                cml_YxyToXYZ,                 cml_YxyToXYZ_SB);
    cmlRegisterConverterUnit(CML_Yupvp,       CML_ENCODING_FLOAT, CML_Yxy,          CML_ENCODING_FLOAT, CML_NULL,              cml_YxyToYupvp,               cml_YxyToYupvp_SB);
    cmlRegisterConverterUnit(CML_Yxy,   CML_ENCODING_FLOAT, CML_Yupvp,  CML_ENCODING_FLOAT, CML_NULL, cml_YupvpToYxy,               cml_YupvpToYxy_SB);
    cmlRegisterConverterUnit(CML_Yuv,   CML_ENCODING_FLOAT, CML_Yupvp,  CML_ENCODING_FLOAT, CML_NULL, cml_YupvpToYuv,               cml_YupvpToYuv_SB);
    cmlRegisterConverterUnit(CML_Yupvp, CML_ENCODING_FLOAT, CML_Yuv,    CML_ENCODING_FLOAT, CML_NULL, cml_YuvToYupvp,               cml_YuvToYupvp_SB);
    cmlRegisterConverterUnit(CML_Luv,   CML_ENCODING_FLOAT, CML_Yupvp,  CML_ENCODING_FLOAT, CML_NULL, cml_YupvpToLuv,               cml_YupvpToLuv_SB);
    cmlRegisterConverterUnit(CML_Yupvp, CML_ENCODING_FLOAT, CML_Luv,    CML_ENCODING_FLOAT, CML_NULL, cml_LuvToYupvp,               cml_LuvToYupvp_SB);
    cmlRegisterConverterUnit(CML_Lab,   CML_ENCODING_FLOAT, CML_XYZ,    CML_ENCODING_FLOAT, CML_NULL, cml_XYZToLab,                 cml_XYZToLab_SB);
    cmlRegisterConverterUnit(CML_XYZ,   CML_ENCODING_FLOAT, CML_Lab,    CML_ENCODING_FLOAT, CML_NULL, cml_LabToXYZ,                 CML_NULL);
    cmlRegisterConverterUnit(CML_Lch,   CML_ENCODING_FLOAT, CML_Lab,    CML_ENCODING_FLOAT, CML_NULL, cml_LabToLch,                 cml_LabToLch_SB);
    cmlRegisterConverterUnit(CML_Lab,   CML_ENCODING_FLOAT, CML_Lch,    CML_ENCODING_FLOAT, CML_NULL, cml_LchToLab,                 cml_LchToLab_SB);
    cmlRegisterConverterUnit(CML_RGB,   CML_ENCODING_FLOAT, CML_XYZ,    CML_ENCODING_FLOAT, CML_NULL, cml_XYZToRGB,                 cml_XYZToRGB_SB);
    cmlRegisterConverterUnit(CML_XYZ,   CML_ENCODING_FLOAT, CML_RGB,    CML_ENCODING_FLOAT, CML_NULL, cml_RGBToXYZ,                 cml_RGBToXYZ_SB);
    cmlRegisterConverterUnit(CML_YCbCr, CML_ENCODING_FLOAT, CML_RGB,    CML_ENCODING_FLOAT, CML_NULL, cml_RGBToYCbCr,               CML_NULL);
    cmlRegisterConverterUnit(CML_RGB,   CML_ENCODING_FLOAT, CML_YCbCr,  CML_ENCODING_FLOAT, CML_NULL, cml_YCbCrToRGB,               cml_YCbCrToRGB_SB);
    cmlRegisterConverterUnit(CML_HSV,   CML_ENCODING_FLOAT, CML_RGB,    CML_ENCODING_FLOAT, CML_NULL, cml_RGBToHSV,                 cml_RGBToHSV_SB);
    cmlRegisterConverterUnit(CML_RGB,   CML_ENCODING_FLOAT, CML_HSV,    CML_ENCODING_FLOAT, CML_NULL, cml_HSVToRGB,                 cml_HSVToRGB_SB);
    cmlRegisterConverterUnit(CML_HSL,   CML_ENCODING_FLOAT, CML_HSV,    CML_ENCODING_FLOAT, CML_NULL, cml_HSVToHSL,                 cml_HSVToHSL_SB);
    cmlRegisterConverterUnit(CML_HSV,   CML_ENCODING_FLOAT, CML_HSL,    CML_ENCODING_FLOAT, CML_NULL, cml_HSLToHSV,                 cml_HSLToHSV_SB);

  }
  
  return context;
}


CML_API CMLInt cmlGetContextVersion(CMLContext* context){
  return context->version;
}



CML_API CMLContext* cmlCurrentContext(){
  return cmlc;
}



CML_API void cmlDestroyContext(CMLContext* context){
//  NAInt entriescount = naGetStackCount(&(context->colorspaceabstracts));
//  CMLColorspaceAbstract** colorspaceabstract = naGetGrowingSpaceMutablePointer(&(context->colorspaceabstracts));
//  while(entriescount){
//    cml_DestroyColorspaceAbstract(*colorspaceabstract);
//    colorspaceabstract++;
//    entriescount--;
//  }
  naForeachStackMutable(&(context->colorspaceabstracts), (NAMutator)cml_DestroyColorspaceAbstract);
  naClearStack(&(context->colorspaceabstracts));

//  entriescount = naGetStackCount(&(context->settingClasses));
//  CMLSettingClass** settingClass = naGetGrowingSpaceMutablePointer(&(context->settingClasses));
//  while(entriescount){
//    cml_DestroySettingClass(*settingClass);
//    settingClass++;
//    entriescount--;
//  }
  naForeachStackMutable(&(context->settingClasses), (NAMutator)cml_DestroySettingClass);
  naClearStack(&(context->settingClasses));

//  entriescount = naGetStackCount(&(context->encodings));
//  CMLMOBEncoding** encodings = naGetGrowingSpaceMutablePointer(&(context->encodings));
//  while(entriescount){
//    cml_DestroyEncoding(*encodings);
//    encodings++;
//    entriescount--;
//  }
  naForeachStackMutable(&(context->encodings), (NAMutator)cml_DestroyEncoding);
  naClearStack(&(context->encodings));

  #ifndef NDEBUG
    if(context->curobject){
      cmlError("cmlDestroyContext", "Operation still in progress. Leaking object.");
    }
  #endif

  mobDestroyContext(context->mobc);
}




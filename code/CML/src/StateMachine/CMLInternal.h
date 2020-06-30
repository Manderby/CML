
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.


#if CML_COMPILE_ON_WIN
  #define CML_HIDDEN
#elif CML_COMPILE_ON_MAC
  #define CML_HIDDEN       __attribute__ ((visibility("hidden")))
#else
  #define CML_HIDDEN       __attribute__ ((visibility("hidden")))
#endif


// todo: make inline functions or ranges
#define CML_MAX(a, b) (((a)>(b))?(a):(b))
#define CML_MIN(a, b) (((a)<(b))?(a):(b))

#define CML_UNUSED(x) (void)(x)

#define CML_MAX_CONVERTER_CHAIN_ELEMENTS 100
#define CML_BENCHMARKCOUNT 1000


typedef struct CMLConverterChainElement      CMLConverterChainElement;

#include "../MOBInternal.h"

typedef struct MOB    CMLConverterUnit;
typedef struct MOB    CMLConverterClass;


typedef enum{
  CML_FUNCTION_OBJECT,
  CML_FUNCTION_VECTOR_OBJECT,
  CML_ILLUMINATION_OBJECT,
  CML_RESPONSE_CURVE_OBJECT,
  CML_COLORSPACE_OBJECT,
  CML_COLORSPACE_ABSTRACT_OBJECT,
  CML_COLORSPACE_CLASS_OBJECT,
  CML_COMPONENT_OBJECT,
  CML_SETTING_CLASS_OBJECT,
  CML_CONVERTER_UNIT_OBJECT,
  CML_CONVERTER_CLASS_OBJECT,
  CML_FUNCTION_STEPSIZE,
  CML_FUNCTION_MIN_SAMPLE_COORD,
  CML_FUNCTION_MAX_SAMPLE_COORD,
  CML_FUNCTION_MIN_NON_TRIVIAL_COORD,
  CML_FUNCTION_MAX_NON_TRIVIAL_COORD,
  CML_FUNCTION_EVALUATOR,
  CML_TEMPERATURE_K,
  CML_BLACKBODY_FACTOR_c,
  CML_GAMMA,
  CML_INV_GAMMA,
  CML_CURVE_OFFSET,
  CML_LINEAR_SCALE,
  CML_INV_LINEAR_SCALE,
  CML_CURVE_SCALE,
  CML_INV_CURVE_SCALE,
  CML_LINEAR_CURVE_SPLIT,
  CML_INV_LINEAR_CURVE_SPLIT,
  CML_CONST_VALUE,
  CML_BINOMIAL_VALUE_n,
  CML_BINOMIAL_VALUE_k,
  CML_BINOMIAL_n_MINUS_k,
  CML_BINOMIAL_BINOM,
  CML_BINOMIAL_INV_RANGE,
  CML_GAUSS_VALUE_mu,
  CML_GAUSS_VALUE_sigma,
  CML_GAUSS_VALUE_invsigma,
  CML_COMPOSITE_FUNCTION_1,
  CML_COMPOSITE_FUNCTION_2,
  CML_COMPOSITE_FACTOR_2,
  CML_ARRAY_FUNCTION_DOWN_EXTRAPOLATION_METHOD,
  CML_ARRAY_FUNCTION_INTERPOLATION_METHOD,
  CML_ARRAY_FUNCTION_UP_EXTRAPOLATION_METHOD,
  CML_ARRAY_FUNCTION_DOWN_EXTRAPOLATION_FUNCTION,
  CML_ARRAY_FUNCTION_INTERPOLATION_FUNCTION,
  CML_ARRAY_FUNCTION_UP_EXTRAPOLATION_FUNCTION,
  CML_ARRAY_FUNCTION_INV_INTERVAL,
  CML_ARRAY_FUNCTION_VALUE_ARRAY,
  CML_ARRAY_FUNCTION_VALUE_ARRAY_ENTRYCOUNT,
  CML_SETTING_DEFAULT_OBJECT,
  CML_RESPONSE_CURVE_TYPE,
  CML_RESPONSE_CURVE_FORWARD_FUNCTION,
  CML_RESPONSE_CURVE_BACKWARD_FUNCTION,
  CML_FUNCTION_VECTOR_NORMALIZATION_WAVELENGTH,
  CML_FUNCTION_VECTOR_MAIN_FUNCTION_INDEX,
  CML_FUNCTION_VECTOR_NORMALIZATION_FACTOR,
  CML_FUNCTION_VECTOR_PRESET,
  CML_FUNCTION_VECTOR_COUNT,
  CML_FUNCTION_VECTOR_FUNCTIONS,
  CML_COLORSPACE_ABSTRACT_TYPE,
  CML_COLORSPACE_CLASS_ENCODING,
  CML_COLORSPACE_CLASS,
  CML_COLORSPACE_ABSTRACT,

  CML_COLORSPACE_ABSTRACT_COMPONENT,
  CML_COLORSPACE_ABSTRACT_MAIN_COMPONENT_INDEX,
  CML_COLORSPACE_ABSTRACT_NAME,
  CML_COLORSPACE_CLASS_REQUIRED_SETTING_CLASSES,
  CML_COLORSPACE_CLASS_OUT_CONVERTER_CLASSES,
  CML_COLORSPACE_CLASS_IN_CONVERTER_CLASSES,
  CML_COLORSPACE_ABSTRACT_DEFAULT_SETTING_CONSTRUCTOR,
  CML_COLORSPACE_CLASS_MIN_COMPONENT_FUNCTION,
  CML_COLORSPACE_CLASS_MAX_COMPONENT_FUNCTION,
  CML_COMPONENT_TYPE,
  CML_COMPONENT_NAME,
  CML_CONVERTER_CONSTRUCTOR,
  CML_CONVERTER_UNIT_DST_COLORSPACE,
  CML_CONVERTER_UNIT_SRC_COLORSPACE,
  CML_ERROR,
  CML_CONVERTER_CLASS_DST_COLORSPACE_CLASS,
  CML_CONVERTER_CLASS_SRC_COLORSPACE_CLASS,
  CML_SETTING_CLASS_NAME,
  CML_COLORSPACE_SETTING_CLASS_CONSTRUCTOR,
  CML_CONVERTER_SETTING_CLASS_CONSTRUCTOR,
  CML_SETTING_CLASS_ID,

  CML_CONVERTER_UNIT_COST,
  CML_CONVERTER_CLASS_EQUS_SETTING,
  CML_CONVERTER_CLASS_ADDS_SETTING,
  CML_CONVERTER_CLASS_SUBS_SETTING,
  CML_CONVERTER_CLASS_ALTS_SETTING,
  CML_CONVERTER_CLASS_CONS_SETTING,
  
  CML_CONVERTER_CLASS_REQUESTER,
  CML_CONVERTER_CLASS_EVALUATOR,
  CML_CONVERTER_CLASS_EVALUATOR_SB,

  CML_OBSERVER_METRIC_SCALE,
  CML_OBSERVER_FUNCTIONS,
  CML_OBSERVER_ADAPTATION_WHITE_SPECTRUM,
  CML_OBSERVER_ADAPTATION_WHITE_XYZ,
  CML_OBSERVER_ADAPTATION_WHITE_InvXYZ,
  CML_OBSERVER_ADAPTATION_WHITE_Yxy,
  CML_OBSERVER_ADAPTATION_WHITE_Yupvp,

  CML_GENERATOR_METRIC_SCALE,
  CML_GENERATOR_FUNCTIONS,
  CML_GENERATOR_WHITE_SPECTRUM,
  CML_GENERATOR_WHITE_XYZ,
  CML_GENERATOR_WHITE_InvXYZ,
  CML_GENERATOR_PRIMARY_RED_Yxy,
  CML_GENERATOR_PRIMARY_BLUE_Yxy,

  CML_COLOR_COLORSPACE,

  CML_OBJECT_KEYS_COUNT
} CML_KeyID;


typedef enum{
  CML_UNIT_FUNCTION_EVALUATOR,
  CML_UNIT_COLORSPACE_SETTING_CONSTRUCTOR,
  CML_UNIT_CONVERTER_SETTING_CONSTRUCTOR,
  CML_UNIT_COLORSPACE_COMPONENT_MINMAX_FUNCTION,
  CML_UNIT_CONVERTER_REQUESTER,
  CML_UNIT_CONVERTER_EVALUATOR,
  CML_UNIT_CONVERTER_EVALUATOR_SB,
  CML_INFORMATION_UNITS_COUNT
} CML_UnitID;





// CMLContext hidden API
CML_HIDDEN CMLColorspaceClass* cml_GetContextColorspaceClass(CMLColorspaceType colorspaceType, CMLEncoding encoding);

CML_HIDDEN CML_INLINE MOB* cml_Key(CML_KeyID key);
CML_HIDDEN CML_INLINE MOBUnitID cml_Unit(CML_UnitID unit);
CML_HIDDEN CML_INLINE void cml_BOOTSTRAPRegisterColorspaceType(CMLColorspaceType desiredcolorspaceType, const char* name, CMLColorspaceValenceDefiner valencedefiner);
CML_HIDDEN CML_INLINE void cml_BOOTSTRAPRegisterColorspaceSettingClass(CMLSettingID desiredsettingClassid, const char* name, CMLColorspaceSettingConstructor defaultconstructor);
CML_HIDDEN CML_INLINE void cml_BOOTSTRAPRegisterEncoding(CMLEncoding desiredencoding);
CML_HIDDEN CML_INLINE void cml_BOOTSTRAPRegisterConverterSettingClass(CMLSettingID desiredsettingClassid, const char* name, CMLConverterSettingConstructor defaultconstructor);
CML_HIDDEN CML_INLINE CMLColorspaceAbstract* cml_GetContextColorspaceAbstract(CMLColorspaceType colorspaceType);
CML_HIDDEN CML_INLINE CMLMOBEncoding* cml_GetContextEncodingMOB(CMLEncoding encoding);
CML_HIDDEN CML_INLINE CMLSettingClass* cml_GetContextSettingClass(CMLSettingID settingClassID);


// CMLColorspaceAbstract hidden API
CML_HIDDEN CMLColorspaceAbstract* cml_CreateColorspaceAbstract(CMLColorspaceType id, const char* name);

CML_HIDDEN CML_INLINE void cml_DestroyColorspaceAbstract                  (CMLColorspaceAbstract* colorspaceabstract);
CML_HIDDEN CML_INLINE CMLInt cml_GetColorspaceAbstractComponentsCount     (CMLColorspaceAbstract* colorspaceabstract);
CML_HIDDEN CML_INLINE CMLInt cml_GetColorspaceAbstractMainComponentIndex  (CMLColorspaceAbstract* colorspaceabstract);
CML_HIDDEN CML_INLINE CMLComponent* cml_GetColorspaceAbstractComponent    (CMLColorspaceAbstract* colorspaceabstract, CMLInt indx);
CML_HIDDEN CML_INLINE CMLColorspaceType cml_GetColorspaceAbstractType     (CMLColorspaceAbstract* colorspaceabstract);
CML_HIDDEN CML_INLINE NAString* cml_GetColorspaceAbstractName             (CMLColorspaceAbstract* colorspaceabstract);


// CMLColorspaceClass hidden API
CML_HIDDEN CMLColorspaceClass* cml_CreateColorspaceClass(CMLColorspaceAbstract* colorspaceabstract, CMLMinMaxComponentFunction minfunction, CMLMinMaxComponentFunction maxfunction);
CML_HIDDEN void cml_DebugColorspaceClass(CMLColorspaceClass* colorspaceClass);
CML_HIDDEN void cml_AddColorspaceClassRequiredSetting(CMLColorspaceClass* colorspaceClass, CMLSettingClass* settingClass);
CML_HIDDEN CMLInt cml_GetColorspaceClassStorageSize(const CMLColorspaceClass* colorspaceClass);

CML_HIDDEN CML_INLINE void cml_DestroyColorspaceClass                               (CMLColorspaceClass* colorspaceClass);
CML_HIDDEN CML_INLINE NAString* cml_GetColorspaceClassName                          (const CMLColorspaceClass* colorspaceClass);
CML_HIDDEN CML_INLINE CMLColorspaceAbstract* cml_GetColorspaceClassAbstract         (const CMLColorspaceClass* colorspaceClass);
CML_HIDDEN CML_INLINE CMLEncoding cml_GetColorspaceClassEncoding                    (const CMLColorspaceClass* colorspaceClass);
CML_HIDDEN CML_INLINE CMLComponent* cml_GetColorspaceClassComponent                 (const CMLColorspaceClass* colorspaceClass, CMLInt indx);
CML_HIDDEN CML_INLINE CMLMinMaxComponentFunction cml_GetColorspaceClassMinFunction  (const CMLColorspaceClass* colorspaceClass);
CML_HIDDEN CML_INLINE CMLMinMaxComponentFunction cml_GetColorspaceClassMaxFunction  (const CMLColorspaceClass* colorspaceClass);


// CMLColorspace hidden API
CML_HIDDEN CMLColorspace* cml_CreateBlankColorspace(CMLColorspaceClass* colorspaceClass);
CML_HIDDEN void cml_DebugColorspace(CMLColorspace* colorspace);
CML_HIDDEN CMLBool cml_EqualColorspace(CMLColorspace* space1, CMLColorspace* space2);
CML_API CMLColorspace* cml_CreateColorspaceOfConverterGoal(CMLColorspace* srcspace, CMLConverterClass* converterClass, CMLColorspace* goalspace);

CML_HIDDEN CML_INLINE const CMLColorspaceClass* cml_GetColorspaceClass(const CMLColorspace* colorspace);
CML_HIDDEN CML_INLINE CMLSetting* cml_GetColorspaceSetting(CMLColorspace* colorspace, CMLSettingClass* settingClass);
CML_HIDDEN CML_INLINE void cml_SetColorspaceSetting(CMLColorspace* colorspace, CMLSettingClass* settingClass, CMLSetting* setting);


// CMLSetting hidden API
CML_HIDDEN CML_INLINE CMLSetting* cml_GetSettingClassDefaultColorspaceSetting(CMLSettingClass* settingClass);


// CMLComponent hidden API
CML_HIDDEN CML_INLINE NAString* cml_GetComponentName(CMLComponent* component);
CML_HIDDEN CML_INLINE CMLComponentType cml_GetComponentType(CMLComponent* component);
CML_HIDDEN CML_INLINE CMLInt cml_GetComponentSize(CMLComponent* component);


// CMLEncoding hidden API
CML_API void cml_DestroyEncoding(CMLMOBEncoding* encoding);


// CMLConverterClass hidden API
CML_HIDDEN void cml_DebugConverterClass(CMLConverterClass* converterClass);
CML_HIDDEN void cml_AddConverterClassRequiredSettingsAsEqu(CMLConverterClass* converterClass, CMLColorspaceClass* colorspaceClass);
CML_API NABool cml_HasConverterClassSettingTreatment(const CMLConverterClass* converterClass, const CMLSettingClass* settingClass);

CML_HIDDEN CML_INLINE CMLColorspaceClass* cml_GetConverterClassDstColorspaceClass(CMLConverterClass* converterClass);
CML_HIDDEN CML_INLINE CMLColorspaceClass* cml_GetConverterClassSrcColorspaceClass(CMLConverterClass* converterClass);
CML_HIDDEN CML_INLINE CMLConverterEvaluator cml_GetConverterClassEvaluator(const CMLConverterClass* converterClass);
CML_HIDDEN CML_INLINE CMLConverterSBEvaluator cml_GetConverterClassEvaluatorSB(const CMLConverterClass* converterClass);
CML_HIDDEN CML_INLINE CMLBool cml_HasConverterClassEquSetting(const CMLConverterClass* converterClass, const CMLSettingClass* settingClass);
CML_HIDDEN CML_INLINE CMLBool cml_HasConverterClassAltSetting(const CMLConverterClass* converterClass, const CMLSettingClass* settingClass);
CML_HIDDEN CML_INLINE CMLBool cml_HasConverterClassAddSetting(const CMLConverterClass* converterClass, const CMLSettingClass* settingClass);
CML_HIDDEN CML_INLINE CMLBool cml_HasConverterClassSubSetting(const CMLConverterClass* converterClass, const CMLSettingClass* settingClass);
CML_HIDDEN CML_INLINE CMLBool cml_HasConverterClassConSetting(const CMLConverterClass* converterClass, const CMLSettingClass* settingClass);
CML_HIDDEN CML_INLINE void cml_AddConverterClassEquSetting(CMLConverterClass* converterClass, CMLSettingClass* settingClass);
CML_HIDDEN CML_INLINE void cml_AddConverterClassAddSetting(CMLConverterClass* converterClass, CMLSettingClass* settingClass);
CML_HIDDEN CML_INLINE void cml_AddConverterClassSubSetting(CMLConverterClass* converterClass, CMLSettingClass* settingClass);
CML_HIDDEN CML_INLINE void cml_AddConverterClassAltSetting(CMLConverterClass* converterClass, CMLSettingClass* settingClass);
CML_HIDDEN CML_INLINE void cml_AddConverterClassConSetting(CMLConverterClass* converterClass, CMLSettingClass* settingClass);
CML_HIDDEN CML_INLINE CMLSetting* cml_GetConverterUnitSetting(CMLConverterUnit* converterUnit, CMLSettingClass* settingClass);


// CMLConverterUnit hidden API
CML_HIDDEN CMLConverterUnit* cml_CreateConverterUnit(CMLConverterClass* converterClass, CMLColorspace* dstspace, CMLColorspace* srcspace);
CML_HIDDEN void cml_DestroyConverterUnit(CMLConverterUnit* converterUnit);
CML_HIDDEN float cml_BenchmarkConverterUnit(CMLConverterUnit* converterUnit);

CML_HIDDEN CML_INLINE CMLColorspace* cml_GetConverterUnitDstColorspace(CMLConverterUnit* converterUnit);
CML_HIDDEN CML_INLINE CMLColorspace* cml_GetConverterUnitSrcColorspace(CMLConverterUnit* converterUnit);
CML_HIDDEN CML_INLINE const CMLConverterClass* cml_GetConverterUnitClass(const CMLConverterUnit* converterUnit);


// CMLColor hidden API
CML_HIDDEN CML_INLINE CMLColorspace* cml_GetColorColorspace(CMLColor* color);












MOB* cml_CreateGenToObsMatrix(CMLMOBFunctionVector* filters, CMLMOBFunctionVector* generators);
MOB* cml_CreateObsToGenMatrix(CMLMOBFunctionVector* filters, CMLMOBFunctionVector* generators);



CML_HIDDEN CMLSetting* cml_CreateSettingObserver(CMLColorspaceType colorspaceType);
CML_HIDDEN CMLSetting* cml_CreateSettingGenerator(CMLColorspaceType colorspaceType);
CML_HIDDEN CMLSetting* cml_CreateSettingResponseCurves(CMLColorspaceType colorspaceType);
CML_HIDDEN CMLSetting* cml_CreateSettingIlluminationSpectrum(CMLColorspaceType colorspaceType);

CML_HIDDEN CMLSetting* cml_CreateSettingObsToGenMatrix(CMLColorspace* dstspace, CMLColorspace* srcspace);
CML_HIDDEN CMLSetting* cml_CreateSettingGenToObsMatrix(CMLColorspace* dstspace, CMLColorspace* srcspace);
CML_HIDDEN CMLSetting* cml_CreateSettingComponentsOffsets(CMLColorspace* dstspace, CMLColorspace* srcspace);
CML_HIDDEN CMLSetting* cml_CreateSettingComponentsRanges(CMLColorspace* dstspace, CMLColorspace* srcspace);


CML_HIDDEN CMLSettingID cml_GetSettingClassID(CMLSettingClass* settingClass);
CML_HIDDEN void cml_DestroySettingClass(CMLSettingClass* settingClass);
CML_HIDDEN NAString* cml_GetSettingClassName(CMLSettingClass* settingClass);
CML_HIDDEN void cml_DebugSettingClass(CMLSettingClass* settingClass);
CML_HIDDEN void cml_DebugSetting(CMLSetting* setting);




CML_HIDDEN float cml_XYZScalarComponentMax  (CMLColorspace* colorspace, CMLInt indx);
CML_HIDDEN float cml_YxyScalarComponentMax  (CMLColorspace* colorspace, CMLInt indx);
CML_HIDDEN float cml_YupvpScalarComponentMax(CMLColorspace* colorspace, CMLInt indx);
CML_HIDDEN float cml_YuvScalarComponentMax  (CMLColorspace* colorspace, CMLInt indx);
CML_HIDDEN float cml_LuvScalarComponentMin  (CMLColorspace* colorspace, CMLInt indx);
CML_HIDDEN float cml_LuvScalarComponentMax  (CMLColorspace* colorspace, CMLInt indx);
CML_HIDDEN float cml_LabScalarComponentMin  (CMLColorspace* colorspace, CMLInt indx);
CML_HIDDEN float cml_LabScalarComponentMax  (CMLColorspace* colorspace, CMLInt indx);
CML_HIDDEN float cml_LchScalarComponentMax  (CMLColorspace* colorspace, CMLInt indx);
CML_HIDDEN float cml_HSVScalarComponentMax  (CMLColorspace* colorspace, CMLInt indx);
CML_HIDDEN float cml_HSLScalarComponentMax  (CMLColorspace* colorspace, CMLInt indx);
CML_HIDDEN float cml_YCbCrScalarComponentMin(CMLColorspace* colorspace, CMLInt indx);
CML_HIDDEN float cml_YCbCrScalarComponentMax(CMLColorspace* colorspace, CMLInt indx);

CML_HIDDEN void cml_DefineRadiometricSpaceValences  (void);
CML_HIDDEN void cml_DefineRemissionSpaceValences    (void);
CML_HIDDEN void cml_DefineXYZSpaceValences          (void);
CML_HIDDEN void cml_DefineYxySpaceValences          (void);
CML_HIDDEN void cml_DefineYupvpSpaceValences        (void);
CML_HIDDEN void cml_DefineYuvSpaceValences          (void);
CML_HIDDEN void cml_DefineLuvSpaceValences          (void);
CML_HIDDEN void cml_DefineLabSpaceValences          (void);
CML_HIDDEN void cml_DefineLchSpaceValences          (void);
CML_HIDDEN void cml_DefineRGBSpaceValences          (void);
CML_HIDDEN void cml_DefineYCbCrSpaceValences        (void);
CML_HIDDEN void cml_DefineHSVSpaceValences          (void);
CML_HIDDEN void cml_DefineHSLSpaceValences          (void);

CML_HIDDEN CMLBool cml_RemissionToRadiometricRequester();

CML_HIDDEN void cml_RemissionToRadiometric            (CMLOutput out, CMLInput in, CMLSize count);
CML_HIDDEN void cml_RadiometricToRemission            (CMLOutput out, CMLInput in, CMLSize count);
CML_HIDDEN void cml_RadiometricToXYZ                  (CMLOutput out , CMLInput in, CMLSize count);
CML_HIDDEN void cml_RGBToRadiometric                  (CMLOutput out , CMLInput in, CMLSize count);
CML_HIDDEN void cml_XYZToYxy                          (CMLOutput out , CMLInput in, CMLSize count);
CML_HIDDEN void cml_XYZToYxy_SB                       (CMLInputOutput buf, CMLSize count);
CML_HIDDEN void cml_YxyToXYZ                          (CMLOutput out , CMLInput in, CMLSize count);
CML_HIDDEN void cml_YxyToXYZ_SB                       (CMLInputOutput buf, CMLSize count);
CML_HIDDEN void cml_YxyToYupvp                        (CMLOutput out , CMLInput in, CMLSize count);
CML_HIDDEN void cml_YxyToYupvp_SB                     (CMLInputOutput buf, CMLSize count);
CML_HIDDEN void cml_YupvpToYxy                        (CMLOutput out , CMLInput in, CMLSize count);
CML_HIDDEN void cml_YupvpToYxy_SB                     (CMLInputOutput buf, CMLSize count);
CML_HIDDEN void cml_YupvpToYuv                        (CMLOutput out , CMLInput in, CMLSize count);
CML_HIDDEN void cml_YupvpToYuv_SB                     (CMLInputOutput buf, CMLSize count);
CML_HIDDEN void cml_YupvpToYuv                        (CMLOutput out , CMLInput in, CMLSize count);
CML_HIDDEN void cml_YupvpToYuv_SB                     (CMLInputOutput buf, CMLSize count);
CML_HIDDEN void cml_YuvToYupvp                        (CMLOutput out , CMLInput in, CMLSize count);
CML_HIDDEN void cml_YuvToYupvp_SB                     (CMLInputOutput buf, CMLSize count);
CML_HIDDEN void cml_YupvpToLuv                        (CMLOutput out , CMLInput in, CMLSize count);
CML_HIDDEN void cml_YupvpToLuv_SB                     (CMLInputOutput buf, CMLSize count);
CML_HIDDEN void cml_LuvToYupvp                        (CMLOutput out , CMLInput in, CMLSize count);
CML_HIDDEN void cml_LuvToYupvp_SB                     (CMLInputOutput buf, CMLSize count);
CML_HIDDEN void cml_XYZToLab                          (CMLOutput out , CMLInput in, CMLSize count);
CML_HIDDEN void cml_XYZToLab_SB                       (CMLInputOutput buf, CMLSize count);
CML_HIDDEN void cml_LabToXYZ                          (CMLOutput out , CMLInput in, CMLSize count);
CML_HIDDEN void cml_LabToLch                          (CMLOutput out , CMLInput in, CMLSize count);
CML_HIDDEN void cml_LabToLch_SB                       (CMLInputOutput buf, CMLSize count);
CML_HIDDEN void cml_LchToLab                          (CMLOutput out , CMLInput in, CMLSize count);
CML_HIDDEN void cml_LchToLab_SB                       (CMLInputOutput buf, CMLSize count);
CML_HIDDEN void cml_XYZToRGB                          (CMLOutput out , CMLInput in, CMLSize count);
CML_HIDDEN void cml_XYZToRGB_SB                       (CMLInputOutput buf, CMLSize count);
CML_HIDDEN void cml_RGBToXYZ                          (CMLOutput out , CMLInput in, CMLSize count);
CML_HIDDEN void cml_RGBToXYZ_SB                       (CMLInputOutput buf, CMLSize count);
CML_HIDDEN void cml_RGBToYCbCr                        (CMLOutput out , CMLInput in, CMLSize count);
CML_HIDDEN void cml_YCbCrToRGB                        (CMLOutput out , CMLInput in, CMLSize count);
CML_HIDDEN void cml_YCbCrToRGB_SB                     (CMLInputOutput buf, CMLSize count);
CML_HIDDEN void cml_RGBToHSV                          (CMLOutput out , CMLInput in, CMLSize count);
CML_HIDDEN void cml_RGBToHSV_SB                       (CMLInputOutput buf, CMLSize count);
CML_HIDDEN void cml_HSVToRGB                          (CMLOutput out , CMLInput in, CMLSize count);
CML_HIDDEN void cml_HSVToRGB_SB                       (CMLInputOutput buf, CMLSize count);
CML_HIDDEN void cml_HSVToHSL                          (CMLOutput out , CMLInput in, CMLSize count);
CML_HIDDEN void cml_HSVToHSL_SB                       (CMLInputOutput buf, CMLSize count);
CML_HIDDEN void cml_HSLToHSV                          (CMLOutput out , CMLInput in, CMLSize count);
CML_HIDDEN void cml_HSLToHSV_SB                       (CMLInputOutput buf, CMLSize count);

CML_HIDDEN void cml_DefaulttoNorm                     (CMLOutput out , CMLInput in, CMLSize count);
CML_HIDDEN void cml_NormtoDefault                     (CMLOutput out , CMLInput in, CMLSize count);



extern CMLContext* cmlc;


#include "NAStack.h"
#include "NAList.h"












struct CML_HIDDEN CMLIllumination{
  MOB*                     object;
  CMLIlluminationType           type;
  const CMLMOBFunction*            spectrum;
  float                         temperature;
  CMLVec3                       radiometricXYZ;
};

// Converts between Spectra and relative luminance space
struct CML_HIDDEN CMLObserver{
  MOB*                     object;
  CMLMOBFunctionVector*      filters;
  CMLMOBFunctionVector*      generators;
  CMLMat33                      generatorMatrix;
  const CMLMOBFunction*            white;
  CMLVec3                       whiteXYZ;
  CMLVec3                       whiteInvXYZ;
  CMLVec3                       whiteYxy;
  CMLVec3                       whiteYupvp;
  float                         whiteScale;
  float                         metricScale;
  float                         totalScale;
};

//struct CML_HIDDEN CMLRGBSpace{
//  MOB*                     object;
//  CMLRGBSpaceType               type;
//  const CMLObserver*            observer;
//  CMLVec3                       primariesYxy[3];
//  const MOB*       responsecurves[3];
//  CMLMat33                      matrix;
//  CMLMat33                      matrixinv;
////  CMLuint8                      lutsize;
//};





struct CMLContext{
  CMLInt          version;
  NAStack  colorspaceabstracts;
  NAStack  settingClasses;
  NAStack  encodings;
  MOB*            objectKeys[CML_OBJECT_KEYS_COUNT];
  MOBUnitID       informationUnits[CML_INFORMATION_UNITS_COUNT];
  MOB*            curobject;

  MOBContext*     mobc;
};


struct CMLConverter{
  float cost;
  NAList elements;
};

struct CMLConverterChainElement{
  CMLConverterUnit* converterUnit;
  CMLColorspace* dstspace;
  void* dstbuf;
  void** pointerbuf;
};






CML_HIDDEN CML_INLINE float cml_Eval(CMLMOBFunction* function, float x){
  CMLFunctionEvaluator evaluator = cml_GetFunctionEvaluator(function);
  return evaluator(function, x);
}









CML_HIDDEN void cmlDestroyCMOB(void* object);




CML_HIDDEN CML_INLINE const void* cmlRetainCMOB(const void* object, void* listener, CMLCallback callback){
  CML_UNUSED(listener);
  CML_UNUSED(callback);
  return object;
}





// ////////////////////////////////////
// Lr to fy and fy to Lr
// ////////////////////////////////////

#define CML_LSTAR_TRANSFORM_OFFSET    0.16f
#define CML_LSTAR_TRANSFORM_SCALE     1.16f
#define CML_LSTAR_TRANSFORM_INV_SCALE 0.8620689655172f

CML_HIDDEN CML_INLINE float cml_Lrtofy(float Lr){
  return (Lr + CML_LSTAR_TRANSFORM_OFFSET) * CML_LSTAR_TRANSFORM_INV_SCALE;
}

CML_HIDDEN CML_INLINE float cml_fytoLr(float fy){
  return fy * CML_LSTAR_TRANSFORM_SCALE - CML_LSTAR_TRANSFORM_OFFSET;
}





CML_HIDDEN CML_INLINE void cml_OneRadiometricToXYZRadiometric (float* CML_RESTRICT XYZ0, float* CML_RESTRICT XYZ1, float* CML_RESTRICT XYZ2, CMLMOBFunction** spec, CMLMOBFunction* filter0, CMLMOBFunction* filter1, CMLMOBFunction* filter2){
  *XYZ0 = cmlFilterFunction(*spec, filter0);
  *XYZ1 = cmlFilterFunction(*spec, filter1);
  *XYZ2 = cmlFilterFunction(*spec, filter2);
}


// Careful: index 1 and 2 are often reversed.
#define CMLINTERNALXYZToYxy(Yxy0, Yxy1, Yxy2, XYZ0, XYZ1, XYZ2, whiteYxy) \
  float divisor;\
  divisor = (*XYZ0 + *XYZ1 + *XYZ2);\
  float Y = *XYZ1;\
  if(divisor == 0.f){\
    if(whiteYxy){\
      *Yxy2 = whiteYxy[2];\
      *Yxy1 = whiteYxy[1];\
    }else{\
      *Yxy2 = 0.f;\
      *Yxy1 = 0.f;\
    }\
  }else{\
    float factor = cmlInverse(divisor);\
    *Yxy2 = *XYZ1 * factor;\
    *Yxy1 = *XYZ0 * factor;\
  }\
  *Yxy0 = Y;


CML_HIDDEN CML_INLINE void cml_OneXYZToYxy (float* CML_RESTRICT Yxy0, float* CML_RESTRICT Yxy1, float* CML_RESTRICT Yxy2, const float* CML_RESTRICT XYZ0, const float* CML_RESTRICT XYZ1, const float* CML_RESTRICT XYZ2, const float* CML_RESTRICT whiteYxy){
  CMLINTERNALXYZToYxy(Yxy0, Yxy1, Yxy2, XYZ0, XYZ1, XYZ2, whiteYxy);
}


#define CMLINTERNALYxyToXYZ(XYZ0, XYZ1, XYZ2, Yxy0, Yxy1, Yxy2, whiteXYZ) \
  if(*Yxy2 == 0.f){\
    if(whiteXYZ){\
      *XYZ0 = ((float*)whiteXYZ)[0];\
      *XYZ2 = ((float*)whiteXYZ)[2];\
    }else{\
      *XYZ0 = 0.f;\
      *XYZ2 = 0.f;\
    }\
    *XYZ1 = 0.f;\
  }else{\
    *XYZ2  = *Yxy0 / *Yxy2;\
    float Y = *XYZ2 * *Yxy1;\
    *XYZ1  = *Yxy0;\
    *XYZ0  = Y;\
    *XYZ2 -= *XYZ0 + *XYZ1;\
  }



CML_HIDDEN CML_INLINE void cml_OneYxyToXYZ (float* CML_RESTRICT XYZ0, float* CML_RESTRICT XYZ1, float* CML_RESTRICT XYZ2, const float* CML_RESTRICT Yxy0, const float* CML_RESTRICT Yxy1, const float* CML_RESTRICT Yxy2, const float* CML_RESTRICT whiteXYZ){
  CMLINTERNALYxyToXYZ(XYZ0, XYZ1, XYZ2, Yxy0, Yxy1, Yxy2, whiteXYZ);
}


#define CMLINTERNALYxyToYupvp(Yupvp0, Yupvp1, Yupvp2, Yxy0, Yxy1, Yxy2, whiteYupvp) \
  float divisor;\
  *Yupvp0 = *Yxy0;\
  divisor = -2.f * *Yxy1 + 12.f * *Yxy2 + 3.f;\
  if(divisor == 0.f){\
    if(whiteYupvp){\
      *Yupvp1 = whiteYupvp[1];\
      *Yupvp2 = whiteYupvp[2];\
    }else{\
      *Yupvp1 = 0.f;\
      *Yupvp2 = 0.f;\
    }\
  }else{\
    float factor = cmlInverse(divisor);\
    *Yupvp1 = 4.f * *Yxy1 * factor;\
    *Yupvp2 = 9.f * *Yxy2 * factor;\
  }\



CML_HIDDEN CML_INLINE void cml_OneYxyToYupvp (float* CML_RESTRICT Yupvp0, float* CML_RESTRICT Yupvp1, float* CML_RESTRICT Yupvp2, const float* CML_RESTRICT Yxy0, const float* CML_RESTRICT Yxy1, const float* CML_RESTRICT Yxy2, const float* CML_RESTRICT whiteYupvp){
  CMLINTERNALYxyToYupvp(Yupvp0, Yupvp1, Yupvp2, Yxy0, Yxy1, Yxy2, whiteYupvp);
}


#include "../CMLInlines.h"



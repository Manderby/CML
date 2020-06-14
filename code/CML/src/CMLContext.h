
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.


#include "NAString.h"


// ///////////////////////////////
// Context
// ///////////////////////////////

// CML uses a context to store all information. You can switch the context
// using the following function. When you send CML_NULL as a parameter, a new
// context ist generated.
CML_API CMLContext*           cmlActivateContext(CMLContext* context);

// To manage and dispose CML context, you can use the following functions:
CML_API CMLContext*           cmlCurrentContext();
CML_API void                  cmlDestroyContext(CMLContext* context);

// Returns a CMLInt denoting a version number. If the number is positive, the
// context runs as a release, if it is negative, it runs as a debug context.
// Debug contexts are only available upon special request to the author.
CML_API CMLInt                cmlGetContextVersion(CMLContext* context);



// ///////////////////////////////
// Using Colorspaces and Converters
// ///////////////////////////////

// You can create and destroy any colorspace using the following functions:
CML_API CMLColorspace* cmlCreateColorspace( CMLColorspaceType colorspaceType,
                                                  CMLEncoding encoding);
CML_API void cmlDestroyColorspace(             CMLColorspace* colorspace);


// If you want to convert color values between two color spaces, simply create
// a new converter with the following function.
CML_API CMLConverter* cmlCreateConverter(
                           CMLColorspace* dstspace,
                           CMLColorspace* srcspace);
CML_API void cmlDestroyConverter(CMLConverter* converter);

// You can then use this converter to convert any input to any output.
// If out is CML_NULL, a new array of color values will be created.
// You can also set out equal to in.
// The count defines, how many color values are to be expected in the buffers.
CML_API void cmlConvert(       CMLConverter* converter,
                              CMLInputOutput out,
                              CMLInputOutput in,
                                      CMLInt count);

// If you have CMLColor objects, you can convert them using the following
// function. If you already have a converter, which is capable of converting
// the two colors, you can speed up conversion by giving that converter as an
// argument. If converter is CML_NULL, the necessary converter is automatically
// computed.
CML_API void cmlConvertColor(CMLConverter* converter, CMLColor* dstcolor, CMLColor* srccolor);

// If you are wondering how the conversion is done, use the following function
// which prints out some debugging information:
CML_API void cml_Debug_FinalConverter(CMLConverter* converter);


// ///////////////////////////////
// Accessing Information of Colorspaces
// ///////////////////////////////


// Every colorspace stores a number of settings which characterize the space.
// You can access and alter the settings using the following functions:
CML_API CMLSetting* cmlGetColorspaceSetting(   CMLColorspace* colorspace,
                                                 CMLSettingID settingClassID);
CML_API void cmlSetColorspaceSetting(          CMLColorspace* colorspace,
                                                 CMLSettingID settingClassID,
                                                  CMLSetting* setting);

// With the following functions, you can access general information of the
// colorspaces:
CML_API CMLColorspaceType cmlGetColorspaceType(CMLColorspace* colorspace);
CML_API float cmlGetColorspaceComponentMin    (CMLColorspace* colorspace,
                                                       CMLInt indx);
CML_API float cmlGetColorspaceComponentMax    (CMLColorspace* colorspace,
                                                       CMLInt indx);

// Returns the size in bytes needed to store one color
CML_API CMLInt cmlGetColorspaceStorageSize(CMLColorspace* colorspace);



// ///////////////////////////////
// Custom Colorspaces
// ///////////////////////////////

// You can create your own custom color spaces. You start doing so by first
// defining a new colorspace type. The name can for example be "Lch" and the
// valencedefiner must point to a function which defines, what kind of values
// are stored per color. See below.
CML_API CMLColorspaceType cmlRegisterColorspaceType(
                                         const char* name,
                         CMLColorspaceValenceDefiner valencedefiner);

// The valencedefiner will be called upon registration of the new type and you
// can define the valences using the following functions:
//
// cmlAddComponent will add a new component to the colorspace (in the order
// you define them). You can label them and give them a semantic interpretation.
// for example "L" is a cartesian, "c" is a radial and "h" is an angular axis.
// The type also defines if the valence is a scalar or a function (used for
// arbitrary spectra). You are free to use as many components and in any order
// you like. All components will be availabe during conversion.
//
// cmlSetMainComponent will give a hint on which of the components is the main
// component. This normally is the luminance-channel or visible-light-channel
// but with RGB for example, green was chosen. This is merely a hint which
// helps to estimate good values. Beware that the component must already be
// defined using cmlAddComponent. If you do not use this function, the index 0
// is automatically assumed to contain the main component.
//
// You can not use these functions outside of a valencedefiner.
CML_API void cmlAddComponent( CMLComponentType componentType,
                                        const char* label);
CML_API void cmlSetMainComponent(            CMLInt indx);

// After registration, you can access the component information using the
// following functions:
CML_API CMLInt cmlGetComponentsCount        (CMLColorspaceType colorspaceType);
CML_API CMLInt cmlGetMainComponentIndex     (CMLColorspaceType colorspaceType);
CML_API CMLComponentType cmlGetComponentType(CMLColorspaceType colorspaceType,
                                                        CMLInt indx);
CML_API const NAString* cmlGetComponentName (CMLColorspaceType colorspaceType,
                                                        CMLInt indx);

// After registration of a new colorspace type, you can define codecs. Every
// colorspace type can have as many codecs as you want. Later on, you can
// define converters which will convert from one to any other encoding. When
// you define an encoding for a colorspace, you have to provide the information
// what the minimal and maximal values for every component of the colorspace
// are. You can do this by providing each a function for the minimal and one
// for the maximal values which returns a float value denoting the minimal or
// maximal value of the color component index requested. If you do not provide
// these functions (use CML_NULL), the values are assumed to be in [0, 1].
//
// These min and max functions will be called when cmlGetColorspaceComponentMin
// or cmlGetColorspaceComponentMax is called. Inside the function, you get a
// CMLColorspace parameter which you can freely use with the getter-functions
// further below and thus compute the min and max based on the actual settings
// of the given colorspace.
//
// You probably will first be providing a float encoding.
//
// Note that a so called "norm" encoding is automatically created. The "normed"
// encoding defines all components to be in the range of [0, 1]. If the
// encoding you choose is a standard encoding, you do not need to define
// converters which convert your desired encoding into the "normed" encoding.
// Such conversion is automatically provided.
//
// todo.
CML_API void cmlRegisterMinMaxComponentFunctions(
                                      CMLColorspaceType colorspaceType,
                                            CMLEncoding encoding,
                             CMLMinMaxComponentFunction minfunction,
                             CMLMinMaxComponentFunction maxfunction);

// If you do not have a standard encoding, you can define your own. Use the
// following function to register your own encoding.
CML_API CMLEncoding cmlRegisterEncoding();






// ///////////////////////////////
// Custom Settings
// ///////////////////////////////

CML_API CMLSettingID cmlRegisterColorspaceSettingClass(
                                                const char* name,
                            CMLColorspaceSettingConstructor defaultconstructor);


CML_API CMLSettingID cmlRegisterConverterSettingClass(
                                                const char* name,
                             CMLConverterSettingConstructor defaultconstructor);

CML_API CMLSetting* cmlGetDefaultColorspaceSetting(CMLSettingID settingClassID);
CML_API CMLSetting* cmlGetDefaultConverterSetting(
                                          CMLSettingID settingClassID,
                                             CMLColorspace* dstspace,
                                             CMLColorspace* srcspace);



// /////////////////////////////
// Custom Converter Units
// /////////////////////////////

// You can simply register your own implementation of a conversion between
// two colorspace classes.
//
// The evaluator will get the input and output values in two separate buffers
// The evaluatorSB will get only one buffer and must read the values from it
// as well as write the result into the same space. SB =  SameBuffer
// If you are not able to provide a SB evaluator, just use CML_NULL.
CML_API void cmlRegisterConverterUnit(  CMLColorspaceType dstcolorspaceType,
                                              CMLEncoding dstencoding,
                                        CMLColorspaceType srccolorspaceType,
                                              CMLEncoding srcencoding,
                                    CMLConverterRequester requester,
                                    CMLConverterEvaluator evaluator,
                                  CMLConverterSBEvaluator evaluatorSB);


// /////////////////////////////
// Implementing the conversion
// /////////////////////////////

// In the implementation of your evaluator function, you can use the following
// functions. You can not use them outside of your evaluator function.

// The following function will return a specific setting. The method defines
// from where the setting will be gathered:
//  CML_GET_EQU     The setting must be present and equal in both src and dst.
//  CML_GET_ADD     The setting is present only in dst
//  CML_GET_SUB     The setting is present only in src
//  CML_GET_ALTDST  The setting is present in both spaces but dst will be used.
//  CML_GET_ALTSRC  The setting is present in both spaces but src will be used.
//  CML_GET_CONVERT The setting is present only during conversion.
// The CML_GET_ALTDST and CML_GET_ALTSRC expect both two colorspaces to have
// the setting defined but storing different settings.
CML_API CMLSetting* cmlRequestConverterSetting(CMLSettingID settingClassID, CMLGetMethod method);
CML_API CMLSetting* cmlGetConverterSetting(CMLSettingID settingClassID, CMLGetMethod method);

// After gathering all settings, you must check for errors and return
// immediately if there was any error.
CML_API CMLError cmlGetConverterError();

// You can create your own errors.
CML_API void cmlSetConverterError(CMLError errornum);


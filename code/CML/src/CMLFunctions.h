
// A CMLFunction is an arbitrary float->float function which may define a
// spectrum, a response curve, a filter or anything else. In CML, you can
// create many predefined functions as well as your own custom functions.
//
// Note that CMLFunctions use a reference counter. When a function is created,
// this counter is set to 1. By calling one of the methods cmlDuplicateFunction
// or cmlReleaseFunction, you can increase or decrese the counter. When the
// counter becomes 0, the CMLFunction will automatically deallocate itself.
// Do not call free() or delete on a CMLFunction!


// //////////////////////////////////////////
// Creating new Functions:
// //////////////////////////////////////////

// All of the following functions return a CMLFunction pointer with a reference
// count of 1.

// Spectra:
// Defines spectral data as radiance per wavelength.
// The input to these functions is expected to be in the unit [nanometer].
CML_API CMLFunction* cmlCreateBlackBody(float temperature);
CML_API CMLFunction* cmlCreateCIEAIlluminant(void);
CML_API CMLFunction* cmlCreateCIEDIlluminant(float temperature);

// Response Curves:
// All response curves operate in the [0,1]-range. The following functions are
// built-in to CML and operate on any value, even negative ones. The gamma
// and sRGB responses map negatives values as follows: f(-x) = -f(x). The LStar
// responses simply expand the linear curvature.
// Note that response curves for the Lab space also should operate on the
// [0,1]-range. They will be converted to the [0,100]-range automatically.
//
// The GammaLinearResponse is computed according to the following formula:
// (1+offset) * powf(x, 1/gamma) - offset    if x => split
// x * linScale                              if x <  split

typedef struct GammaLinearInputParameters{
  float gamma;
  float offset;
  float linScale;
  float split;
} GammaLinearInputParameters;

CML_API CMLFunction* cmlCreateLinearResponse(void);
CML_API CMLFunction* cmlCreateGammaResponse(float gamma);
CML_API CMLFunction* cmlCreateGammaLinearResponse(float linScale, float offset, float gamma, float split);
CML_API CMLFunction* cmlCreateInverseGammaLinearResponse(float linScale, float offset, float gamma, float split);
CML_API CMLFunction* cmlCreatesRGBToXYZResponse(void);
CML_API CMLFunction* cmlCreateXYZTosRGBResponse(void);
CML_API CMLFunction* cmlCreateYToLStarResponse(void);
CML_API CMLFunction* cmlCreateLStarToYResponse(void);
CML_API CMLFunction* cmlCreateYToLStarStandardResponse(void);
CML_API CMLFunction* cmlCreateLStarToYStandardResponse(void);

// Filter Functions:
// Use these functions to filter spectra. Filters are used for componentwise
// multiplication of a spectrum. Therefore, they return values relative to 1.
CML_API CMLFunction* cmlCreateDiracFilter(float wavelength);
CML_API CMLFunction* cmlCreateConstFilter(float value);
CML_API CMLFunction* cmlCreateCutFilter(float min, float max);

// Composite Functions:
// You can combine functions like mathematical functions. All operations will
// then be performed componentwise.
CML_API CMLFunction* cmlCreateFunctionAddFunction( const CMLFunction* func1, const CMLFunction* func2);
CML_API CMLFunction* cmlCreateFunctionSubFunction( const CMLFunction* func1, const CMLFunction* func2);
CML_API CMLFunction* cmlCreateFunctionMulFunction( const CMLFunction* func1, const CMLFunction* func2);
CML_API CMLFunction* cmlCreateFunctionDivFunction( const CMLFunction* func1, const CMLFunction* func2);
CML_API CMLFunction* cmlCreateFunctionMulScalar(   const CMLFunction* func,  float scalar);

// Array Functions:

// Use the following struct to define, how an array function shall handle
// the array values and its interpolation and extrapolation.
typedef struct CMLArrayFunctionSettings CMLArrayFunctionSettings;
struct CMLArrayFunctionSettings{
  size_t entryCount;
  float minimalCoord;
  float maximalCoord;
  CMLInterpolationMethod interpolationMethod;
  CMLExtrapolationMethod lowerExtrapolationMethod;
  CMLExtrapolationMethod upperExtrapolationMethod;
};

// This struct is used to create an array with an existing buffer array.
// The ownBuffer parameter depicts if the function shall take ownership of the
// buffer. If this parameter is CML_TRUE, the buffer will automatically be
// deallocated with free() when the function is no longer needed. If you choose
// to do so, make sure the buffer is allocated with malloc.
// todo: allow arbitrary destructor methods.
typedef struct CMLArrayFunctionInput CMLArrayFunctionInput;
struct CMLArrayFunctionInput{
  const float* buffer;
  CMLBool ownBuffer;
  CMLArrayFunctionSettings settings;
};

// Use this function to crate arbitrary functions where an array with
// sampling points is given.
CML_API CMLFunction* cmlCreateArrayFunction(CMLArrayFunctionInput input);

// If you already have an (arbitrary) function and you want to convert it to an
// array function (very much like a lookup-table), use the following method.
// The result is an ArrayFunction without any references to the original func.
CML_API CMLFunction* cmlSampleArrayFunction(
  const CMLFunction* func,
  CMLArrayFunctionSettings settings);



// //////////////////////////////////////////
// Working with Functions:
// //////////////////////////////////////////

// Evaluates the given function at coordinate x
CML_API float cmlEval(const CMLFunction* func, float x);

// Computes the weighted sum of the given function which is multiplied with
// the given filter.
CML_API float cmlFilterFunction(const CMLFunction* func, const CMLFunction* filter);

// Returns the maximal value of the given function in the coordinate range.
CML_API float cmlGetFunctionMaxValue(const CMLFunction* func);

// Places information about the definition range of the given function in the
// provided DefinitionRange structure.
CML_API void cmlGetFunctionDefinitionRange(const CMLFunction* func, CMLDefinitionRange* defRange);

// Increments the reference count of the given function and returns a non-const
// pointer.
CML_API CMLFunction* cmlDuplicateFunction(const CMLFunction* func);

// Decrements the reference count of the given function. If the reference count
// reaches 0, the function automatically deallocates itself.
CML_API void cmlReleaseFunction(CMLFunction* func);



// //////////////////////////////////////////
// Creating custom Functions:
// //////////////////////////////////////////

// You can create your own CMLFunctions and feed them to CML. To do so, you
// can implement three callback functions:

// The CONSTRUCTOR: This callback function is called when a new instance of
// your CMLFunction gets created.
//
// The params pointer points to an array of floats containing as many parameters
// as have been declared by cmlCreateFunction. When the constructor is called,
// enough memory is allocated, but the contents are uninitialized. You have
// to manually write the parameters inside. If the function expects zero
// parameters, "params" is NULL.
//
// The data handle is a storage free to use. You can allocate memory to the
// "data" pointer. This data will be stored with each instance of your custom
// CMLFunction. To do so, your allocation code should look something like this:
// *data = malloc(sizeof(MyCustomStorage));
// If you are using C++, you can also use any appropriate new-operator.
//
// The "input" parameter is the argument which you pass to cmlCreateFunction.
// The "defRange" parameter is a pointer to a CMLDefinitionRange structure
// which stores additional informations about your function. You can manipulate
// this definition range arbitrarily. See explanation below.
typedef void  (*CMLFunctionConstructor)(
  float* params,
  void** data,
  CMLDefinitionRange* defRange,
  const void* input);

// The DESTRUCTOR: This callback function is called when an instance of your
// CMLFunction gets deallocated.
//
// Perform any cleanup and deallocate the data pointer if you did allocate
// memory. This should look something like this:
// free(data);
// Or use the appropriate delete operator if you are using C++.
typedef void  (*CMLFunctionDesctructor)(
  void*  data);

// You need to test whether input is CML_NULL.
// Upon calling cmlCreateFunction, this function will be called right after
// the constructor function (if any) with the input argument being CML_NULL.
// This allows you to initialize the definitionRange.
typedef void (*CMLFunctionInputSetter)(
  void* data,
  CMLDefinitionRange* defRange,
  const void* input);

typedef const void* (*CMLFunctionInputGetter)(
  void* data);

// The EVALUATOR: This callback function is called whenever cmlEval is called.
//
// Perform any computation necessary and return the function result.
// The "x" parameter denotes the coordinate where you should evaluate.
// The "data" parameter is a pointer to whatever data you have allocated in
// the constructor callback function. The "params" parameter is a pointer to
// your input parameters. If you have no constructor defined, this
// parameter will be CML_NULL.
//
// Be advised to write a comment on what unit the input values are expected.
typedef float (*CMLFunctionEvaluator)(
  float* params,
  const void* data,
  float x);



// Use cmlCreateFunction to create an instance of your own CMLFunction.
// The "evaluator" parameter must be a valid function pointer, all other
// parameters can be CML_NULL. The floatParamCount parameter denotes the
// number of float parameters the function stores. They will be available
// in the constructor and evaluator as array of floats. The input parameter
// can by any kind of data which will be available to the constructor.
CML_API CMLFunction* cmlCreateFunction(
  CMLFunctionConstructor constructor,
  CMLFunctionDesctructor destructor,
  CMLFunctionInputSetter inputSetter,
  CMLFunctionInputGetter inputGetter,
  CMLFunctionEvaluator evaluator,
  CMLuint32 floatParamCount,
  const void* input,
  size_t dataSize);

// Set any kind of input a function requires. The function will store these
// parameters as a copy and can later be retrieved using the getter function.
CML_API void cmlSetFunctionInput(CMLFunction* func, const void* input);
CML_API const void* cmlGetFunctionInput(const CMLFunction* func);


// //////////////////////////////////////////
// Definition Range
// //////////////////////////////////////////

// The following struct can be used for custom CMLFunctions to indicate, where
// integration or filtering is useful. The cmlFilterFunction method queries
// this data to decide, how to integrate the function. To provide the necessary
// data of you custom class, alter the values in your custom constructor.
//
// Currently, integration can only be performed in a discrete manner in CML.
// Using the provided data, CMLFunction will automatically try to integrate in
// such a way that as few interpolation steps as necessary will be made.
// 
// Note the example description below.

struct CMLDefinitionRange {
  // Defines the size between sampling points. If stepSize is 0, the function
  // is considered to be continuous. The default value is 0.
  float stepSize;
  
  // Defines, where the sampling should start and where it should end. These
  // variables should NOT be set to -CML_INFINITY or +CML_INFINITY, otherwise
  // the integration will take infinite time. The default values are
  // CML_DEFAULT_INTEGRATION_MIN and CML_DEFAULT_INTEGRATION_MAX
  float minSampleCoord;
  float maxSampleCoord;
  
  // Defines, where the function is defined, meaning, where a value which is
  // non-trivial will be returned. These variables may be set to -CML_INFINITY
  // or +CML_INFINITY, if desirable. The default values are -CML_INFINITY and
  // +CML_INFINITY.
  float minNonTrivialCoord;
  float maxNonTrivialCoord;
};

// Example: A spectral function may have sampling points, starting at 380nm
// and ending at 780nm with a step of 10nm. Therefore, stepSize would be set to
// 10, minSampleCoord to 380 and maxSampleCoord to 780.

// Implicitely, this defines a total number of 41 sampling points. CML will
// automatically compute this.

// Let's assume that outside of the sampling range, the values are extrapolated
// such that the spectrum smoothly decays to zero in the range down to 300nm
// and up to 800nm. Therefore, the non-trivial entries should be set
// accordingly.
//
// If you have for example a function which is only defined for values >= 0,
// you would set minNonTrivialCoord to 0. If zero should not be included, you
// may set minNonTrivialCoord to +CML_SINGULARITY.



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

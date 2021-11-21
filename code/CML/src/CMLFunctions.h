
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.


// A CMLFunction is an arbitrary float->float function which may define a
// spectrum, a response curve, a filter or anything else. In CML, you can
// create many predefined functions as well as your own cutsom functions.
//
// Note that CMLFunctions use a reference counter. When a function is created,
// this counter is set to 1. By calling one of the methods CMLduplicateFunction
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

CMLAPI CMLFunction* CMLcreateBlackBody(float temperature);
CMLAPI CMLFunction* CMLcreateCIEAIlluminant();
CMLAPI CMLFunction* CMLcreateCIEDIlluminant(float temperature);

// Response Curves:
// All response curves operate in the [0,1]-range. The following functions are
// built-in to CML and operate on any value, even negative ones. The gamma
// and sRGB responses map negatives values as follows: f(-x) = -f(x).
// The LStar responses simply expand the linear curvature.
// Note that response curves for the Lab space also should operate on the
// [0,1]-range. They will be converted to the [0,100]-range automatically.

CMLAPI CMLFunction* CMLcreateLinearResponse();
CMLAPI CMLFunction* CMLcreateGammaResponse(float gamma);
CMLAPI CMLFunction* CMLcreateGammaLinearResponse(float linscale, float offset, float gamma, float split);
CMLAPI CMLFunction* CMLcreateInverseGammaLinearResponse(float linscale, float offset, float gamma, float split);
CMLAPI CMLFunction* CMLcreatesRGBToXYZResponse();
CMLAPI CMLFunction* CMLcreateXYZTosRGBResponse();
CMLAPI CMLFunction* CMLcreateYToLStarResponse();
CMLAPI CMLFunction* CMLcreateLStarToYResponse();
CMLAPI CMLFunction* CMLcreateYToLStarStandardResponse();
CMLAPI CMLFunction* CMLcreateLStarToYStandardResponse();

// Filter Functions:
// Use these functions to filter spectra. Filters are used for componentwise
// multiplication of a sectrum. Therefore, they return values relative to 1
// but unlike probability distribution functions, they do not necessarily need
// to be normalized to 1.

CMLAPI CMLFunction* CMLcreateDiracFilter(float wavelength);
CMLAPI CMLFunction* CMLcreateConstFilter(float value);
CMLAPI CMLFunction* CMLcreateCutFilter(float min, float max);

// Composite Functions:
// You can combine functions like mathematical functions. All operations will
// then be performed componentwise.

CMLAPI CMLFunction* CMLcreateFunctionAddFunction( const CMLFunction* func1,
                                                  const CMLFunction* func2);
CMLAPI CMLFunction* CMLcreateFunctionSubFunction( const CMLFunction* func1,
                                                  const CMLFunction* func2);
CMLAPI CMLFunction* CMLcreateFunctionMulFunction( const CMLFunction* func1,
                                                  const CMLFunction* func2);
CMLAPI CMLFunction* CMLcreateFunctionDivFunction( const CMLFunction* func1,
                                                  const CMLFunction* func2);
CMLAPI CMLFunction* CMLcreateFunctionMulScalar(   const CMLFunction* func,
                                                               float scalar);

// Array Functions:
// Use the following function to crate arbitrary functions where an array with
// sampling points is given. The ownbuffer parameter depicts if the function
// shall take ownership of the buffer. If this parameter is CMLTRUE, the buffer
// will automatically be deallocated with free() when the function is no longer
// needed. If you choose to do so, make sure the buffer is allocated with
// malloc.

CMLAPI CMLFunction* CMLcreateArrayFunction(
                              const float* buffer,
                                   CMLBool ownbuffer,
                                   CMLSize entrycount,
                                     float minimalcoord,
                                     float maximalcoord,
                    CMLInterpolationMethod interpolationmethod,
                    CMLExtrapolationMethod downextrapolationmethod,
                    CMLExtrapolationMethod upextrapolationmethod);

// If you already have an (arbitrary) function and you want to convert it to an
// array function, use the following method:

CMLAPI CMLFunction* CMLsampleArrayFunction(
                        const CMLFunction* func,
                                     float minimalcoord,
                                     float maximalcoord,
                                   CMLSize entrycount,
                    CMLInterpolationMethod interpolationmethod,
                    CMLExtrapolationMethod downextrapolationmethod,
                    CMLExtrapolationMethod upextrapolationmethod);





// //////////////////////////////////////////
// Working with Functions:
// //////////////////////////////////////////

// Evaluates the given function at coordinate x
CMLAPI float CMLeval(                 const CMLFunction* func,
                                                   float x);

// Returns the desired parameter of the function, if it exists. Returns 0
// otherwise. The index is 0-based.
CMLAPI float CMLgetFunctionParameter( const CMLFunction* func,
                                                   CMLSize index);

// Performs a filter operation with the two given functions
CMLAPI float CMLfilterFunction(       const CMLFunction* func,
                                      const CMLFunction* filter);

// Returns the maximal value of the given function in the coordinate range.
CMLAPI float CMLgetFunctionMaxValue(  const CMLFunction* func);

// Places information about the definition range of the given function in the
// provided DefinitionRange structure.
CMLAPI void CMLgetFunctionDefinitionRange(
                                      const CMLFunction* func,
                                     CMLDefinitionRange* defrange);

// Increments the reference count of the given function and returns a non-const
// pointer.
CMLAPI CMLFunction* CMLduplicateFunction(
                                      const CMLFunction* func);

// Decrements the reference count of the given function. If the reference count
// reaches 0, the function automatically deallocates itself.
CMLAPI void cmlReleaseFunction(             CMLFunction* func);




// //////////////////////////////////////////
// Creating custom Functions:
// //////////////////////////////////////////

// You can create your own CMLFunctions and feed them to CML. To do so, you
// can implement three callback functions:



// The CONSTRUCTOR: This callback function is called when a new instance of
// your CMLFunction gets created.
//
// The params pointer points to an array of floats containing as many parameters
// as have been declared by CMLcreateFunction. When the constructor is called,
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
// Note that the advantage of the "params" parameter is that the memory is
// allocated and deallocated automatically for you and the parameters stored
// there can be accessed by a call to CMLgetFunctionParameter.
//
// The "input" parameter is the argument which you pass to CMLcreateFunction.
// The "defrange" parameter is a pointer to a CMLDefinitionRange structure
// which stores additional informations about your function. You can manipulate
// this definition range arbitrarily. See explanation below.
typedef void  (*CMLFunctionConstructor)(
                                    float* params,
                                    void** data,
                       CMLDefinitionRange* defrange,
                               const void* input);

// The EVALUATOR: This callback function is called whenever CMLeval is called.
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

// The DESTRUCTOR: This callback function is called when an instance of your
// CMLFunction gets deallocated.
//
// Perform any cleanup and deallocate the data pointer if you did allocate
// memory. This should look something like this:
// free(data);
// Or use the appropriate delete operator if you are using C++.
typedef void  (*CMLFunctionDesctructor)(
                                    void*  data);


// Use the CMLcreateFunction to create an instance of your own CMLFunction.
// The "evaluator" parameter must be a valid function pointer, all other
// parameters can be CML_NULL. floatparams denotes the number of float input
// parameters the function contains. They will be available in the constructor
// and evaluator as array of floats.
CMLAPI CMLFunction* CMLcreateFunction(
                       CMLFunctionEvaluator evaluator,
                     CMLFunctionConstructor constructor,
                     CMLFunctionDesctructor destructor,
                                  CMLuint32 floatparams,
                                const void* input);




// //////////////////////////////////////////
// Definition Range
// //////////////////////////////////////////

// The following struct can be used for custom CMLFunctions to indicate, where
// integration or filtering is useful. The CMLfilterFunction method queries
// this data to decide, how to integrate the function. To provide the necessary
// data of you custom class, alter the values in your custom constructor.
//
// Currently, integration can only be performed in a discrete manner in CML.
// Using the provided data, CMLFunction will automatically try to integrate in
// such a way that as few interpolation steps as necessary will be made.
// 
// Note the example description below.

struct CMLDefinitionRange {
  // Defines the size between sampling points. If stepsize is 0, the function
  // is considered to be continuous. The default value is 0.
  float stepsize;
  
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
// and ending at 780nm with a step of 10nm. Therefore, stepsize would be set to
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




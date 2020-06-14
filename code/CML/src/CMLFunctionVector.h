
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.


// A CMLFunctionVector stores one or more CMLFunctions with a common purpose.
// For example, the spectral distribution functions of XYZ-Observers are
// treated as a CMLFunctionVector.
//
// A CMLFunctionVector defines a main function, speaking: The function which
// shall be the reference. For example, the spectral distribution functions
// define the y_-Function to be the main function.
//
// If desired, all computations with a CMLFunctionVector will automatically be
// normalized to the value of the main function at a given wavelength. If that
// wavelength is set to 0, no normalization takes place.
//
// You can freely replace all functions as you like. But the number of
// functions stored in a CMLFunctionVector can NOT be altered after the
// structure has been created.


// Creates a CMLFunctionVector from a given preset.
CML_API CMLMOBFunctionVector* cmlCreateFunctionVector(
                                              CMLFunctionVectorPreset preset);

// Creates a CMLFunctionVector with the given number of functions. All
// functions will be initialized with a Function returning constant 1. The
// mainfunctionIndex as well as the normalizationWavelength will be set to 0.
CML_API CMLMOBFunctionVector* cmlCreateFunctionVectorWithCount(
                                              CMLInt functioncount);


CML_API CMLMOBFunctionVector* cmlCreateGeneratorFunctionsFromIlluminationSpectrum(CMLMOBFunction* illumination, CMLInt count);
//CML_API CMLFunctionVector* cmlCreateFilterFunctionsFromIlluminationSpectrum(const CMLFunctionVector* filterfuncs, const CMLFunction* illumination, CMLInt count, CMLVec3 whiteXYZ);


// Returns the number of functions stored in this CMLFunctionVector.
CML_API CMLInt cmlGetFunctionVectorCount(CMLMOBFunctionVector* funvec);

CML_API float cmlGetFunctionVectorNormalizationFactor(CMLMOBFunctionVector* funvec);


// Evaluates all functions in the vector at the given point x and stores
// the resulting values in the result array.
CML_API void cmlEvalFunctionVector(   CMLMOBFunctionVector* funvec,
                                                       float* result,
                                                        float x);

// Gets or sets the function with the given index.
CML_API CMLMOBFunction* cmlGetFunctionVectorFunction(
                                  CMLMOBFunctionVector* funvec,
                                                    CMLInt indx);
CML_API void               cmlSetFunctionVectorFunction(
                                        CMLMOBFunctionVector* funvec,
                                                    CMLInt indx,
                                        CMLMOBFunction* function);


// Gets or sets the index of the main function. For example for XYZ curves,
// this would be index 1 (the Y function)
CML_API CMLInt cmlGetFunctionVectorMainFunctionIndex(
                        CMLMOBFunctionVector* funcol);
CML_API void  cmlSetFunctionVectorMainFunctionIndex(
                              CMLMOBFunctionVector* funcol,
                                              CMLInt mainfunctionindex);

// Gets or sets the wavelength in [nm] of where the main function shall
// be normalized. If that wavelength is set to 0, no normalization takes place.
CML_API float cmlGetFunctionVectorNormalizationWavelength(
                        CMLMOBFunctionVector* funcol);
CML_API void  cmlSetFunctionVectorNormalizationWavelength(
                              CMLMOBFunctionVector* funcol,
                                               float normalizationWavelength);




// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.


CML_API CMLIllumination* cmlCreateIlluminationWithPreset(CMLIlluminationType type, float temperature);
CML_API CMLIllumination* cmlCreateIlluminationWithCustomSpectrum(const CMLMOBFunction* spectrum);
//CML_API CMLIllumination* cmlCreateIlluminationWithCustomWhite(const CMLVec3 whiteYxy);

CML_API CMLIlluminationType cmlGetIlluminationType(const CMLIllumination* illumination);
CML_API const CMLMOBFunction* cmlGetIlluminationSpectrum(const CMLIllumination* illumination);
CML_API float cmlGetCorrelatedColorTemperature(const CMLIllumination* illumination);

// Creates and returns a new spectrum with the given input parameters. The
// temperature parameter is expected in [Degree Kelvin] for the illumination
// types CML_ILLUMINATION_BLACKBODY and CML_ILLUMINATION_D_ILLUMINANT. For any
// other type, the temperature parameter is ignored. The returned CMLFunction
// must be deleted manually. Only types denoting built-in illuminations are
// valid (no custom illuminations). Invalid illumination types will return
// CML_NULL.
CML_API CMLMOBFunction* cmlCreateIlluminationSpectrum(
                                    CMLIlluminationType illuminationtype,
                                    float               temperature);


// Returns the correlated color temperature in [Degree Kelvin] for a given
// white in Yuv. Currently, the Robertson method is implemented.
// Beware! This function expects Yuv, not Yxy!
CML_API float cmlComputeCorrelatedColorTemperature(
                                    const CMLVec3       whiteYuv);


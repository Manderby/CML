
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.


CMLAPI CMLIllumination* cmlCreateIlluminationWithPreset(CMLIlluminationType type, float temperature);
CMLAPI CMLIllumination* cmlCreateIlluminationWithCustomSpectrum(const CMLFunction* spectrum);
CMLAPI CMLIllumination* cmlCreateIlluminationWithCustomWhitepoint(const CMLVec3 whitepointYxy);

CMLAPI CMLIlluminationType cmlGetIlluminationType(const CMLIllumination* illumination);
CMLAPI const CMLFunction* cmlGetIlluminationSpectrum(const CMLIllumination* illumination);
CMLAPI float cmlGetCorrelatedColorTemperature(const CMLIllumination* illumination);
CMLAPI void cmlGetIlluminationRadiometricXYZ(const CMLIllumination* illumination, float* dest, const CMLObserver* observer);




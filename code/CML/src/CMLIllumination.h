
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.


CMLAPI CMLIllumination* cmlCreateIlluminationDuplicate(CMLIllumination* illumination, const CMLIllumination* src);
CMLAPI CMLIllumination* cmlCreateIlluminationWithPreset(CMLIllumination* illumination, CMLIlluminationType type, float temperature);
CMLAPI CMLIllumination* cmlCreateIlluminationWithCustomSpectrum(CMLIllumination* illumination, const CMLFunction* spectrum, const CMLObserver* observer);
CMLAPI CMLIllumination* cmlCreateIlluminationWithCustomWhitepoint(CMLIllumination* illumination, const CMLVec3 whitepointYxy);

CMLAPI void cmlClearIllumination  (CMLIllumination* illumination);
CMLAPI void cmlDestroyIllumination(CMLIllumination* illumination);

CMLAPI CMLIlluminationType cmlGetIlluminationType(const CMLIllumination* illumination);
CMLAPI const CMLFunction* cmlGetIlluminationSpectrum(const CMLIllumination* illumination);
CMLAPI float cmlGetCorrelatedColorTemperature(const CMLIllumination* illumination);
CMLAPI void cmlGetIlluminationRadiometricXYZ(const CMLIllumination* illumination, float* dest, const CMLObserver* observer);




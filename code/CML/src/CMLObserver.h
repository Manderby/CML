
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

// type:                  Defines, what spectral distribution functions to use.
// illuminationSpectrum:  The spectrum function of the desired reference
//                        illumination. This observer will duplicate the
//                        function.
// colorimetricBase:      The Y value of the reference illumination.
//                        In colorimetry, this is usually 1 or 100.
//                        If you use 0, computation is radiometric.
CMLAPI CMLObserver* cmlCreateObserverWithIllumination(
                                            CMLObserver* observer,
                                         CMLObserverType type,
                                        CMLIllumination* illumination,
                                                   float colorimetricBase);

CMLAPI void cmlClearObserver  (CMLObserver* observer);
CMLAPI void cmlDestroyObserver(CMLObserver* observer);

CMLAPI float                  cmlGetObserverRadiometricScale     (const CMLObserver* observer);
CMLAPI float                  cmlGetObserverColorimetricBase     (const CMLObserver* observer);
CMLAPI const CMLFunction*     cmlGetObserverSpecDistFunction     (const CMLObserver* observer, CMLInt index);

CMLAPI CMLObserverType        cmlGetObserverType                 (const CMLObserver* observer);

CMLAPI const CMLIllumination* cmlGetReferenceIllumination        (const CMLObserver* observer);
CMLAPI const CMLFunction*     cmlGetReferenceIlluminationSpectrum(const CMLObserver* observer);
CMLAPI const float*           cmlGetReferenceWhitepointXYZ       (const CMLObserver* observer);
CMLAPI const float*           cmlGetReferenceInverseWhitepointXYZ(const CMLObserver* observer);
CMLAPI const float*           cmlGetReferenceWhitepointYxy       (const CMLObserver* observer);
CMLAPI const float*           cmlGetReferenceWhitepointYupvp     (const CMLObserver* observer);

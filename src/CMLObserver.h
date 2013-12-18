
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.


// Creates a new observer object with the given type. If an invalid type or
// CML_OBSERVER_CUSTOM is given, CML_NULL will be returned.
CMLAPI CMLObserver* cmlCreateObserverWithPreset(CMLObserverType type);

// Returns the type of the observer
CMLAPI CMLObserverType    cmlGetObserverType( const CMLObserver* observer);

// Returns the desired spectral distribution function.
CMLAPI const CMLFunction* cmlGetObserverSpectralDistributionFunction(
                                              const CMLObserver* observer,
                                                          CMLInt index);

// Fills the given xyz array with the spectral color at wavelength lambda. If
// you want to normalize the resulting values, you have to manually multiply
// the whole xyz vector with a normalization constant. Usually, the inverse of
// the Y value of the spectral XYZ color at CML_NORMALIZATION_WAVELENGTH is
// used as that constant.
CMLAPI void cmlGetSpectralColorXYZ(   const CMLObserver* observer,
                                                 CMLVec3 xyz,
                                                   float lambda);



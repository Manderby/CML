//
//// (c) Manderim GmbH
//// This is proprietary software. Any use without the explicit acknowledgement
//// of the author of this software is prohibited and any liability is disclamed.
//// Terms of a separate contract may apply.
//
//// CMLObserver
////
//// An observer stores the spectral distribution functions of the primary
//// dimensions of sight. Currently, there are only three functions possible.
//// Several presets are available.
////
//// A preset is valid only if it is one of the CMLFunctionVectorPreset enumeration
//// type. The CML_FUNVEC_OBSERVER_CUSTOM and CML_NUMBER_OF_OBSERVERS constants are
//// invalid.
////
//// When spectral colors are required, an observer is normalized at a specific
//// wavelength. The y_ function will evaluate to 1 at that wavelength.
////
//// An observer can either be radiometric or colorimetric. When the observer
//// is colorimetric, it is adapted to a certain white. All the XYZ values
//// computed with this observer will be relative to that white.
//
//// There are three normalization factors in CMLObserver:
//// 1. Normalization-Wavelength. This wavelength denotes the coordinate at which
////    the main spectral distribution function will be normed. For standard
////    observers, this wavelength is usually 555 or 560 nm.
//// 2. White-Normalization. The White (often called white) defines the
////    color of full intensity. If an observer is adapted to a certain white,
////    all dependent colors are considered to be adapted. Adapted colors can
////    be expressed relative to that white. If no white is given, the computed
////    values will not be normalized. (Mathematically, this is the same as if
////    the E illumination (artificial constant illumination) was chosen)
//// 3. Metric norm. If set to 0, the setting of the white-normalization (2)
////    has no effect, which corresponds to radiometric color handling. If set
////    to anything else than 0, computations of filtered values (for example
////    computing XYZ out of spectra) will be normed to the given white (2) and
////    then multiplied with the given metric norm (3). In colorimetry, this
////    norm usually is 1 or 100. In radiometry, it's application is rare but
////    you can for example set the metric norm to 300 representing the
////    luminance of a monitor in the unit [cd/m2].
//
//
//
//
//// Creates a new observer object with the given preset. Returns CML_NULL if
//// the given preset is invalid.
//// If a white is given, the observer is considered colorimetric relative
//// to the given white. If the white is CML_NULL, the observer is
//// considered radiometric.
//// The metricScale is a scale factor for the Y component. For colorimetry, the
//// values 1 or 100 are often used. For radiometry, you can use anything for
//// metricScale. If you use 1, the values are considered to be in [cd/m2].
//CML_API CMLObserver* cmlCreateObserverWithPresetAndWhite(
//                                  CMLFunctionVectorPreset preset,
//                                     CMLIllumination* white,
//                                              float metricScale);
//
//
//CML_API const CMLFunction* cmlGetObserverWhite(const CMLObserver* observer);
//CML_API void               cmlSetObserverWhite(      CMLObserver* observer,
//                                                 CMLIllumination* white);
//
//


CML_API float                 cmlGetObserverMetricScale                     (CMLMOBObserver* observer);
CML_API CMLMOBFunctionVector* cmlGetObserverFunctions                       (CMLMOBObserver* observer);

CML_API void                  cmlSetObserverMetricScale                     (CMLMOBObserver* observer,
                                                                                       float metricScale);

CML_API const float*          cmlGetObserverAdaptationWhiteXYZRadiometric   (CMLMOBObserver* observer);
CML_API const float*          cmlGetObserverAdaptationWhiteInvXYZRadiometric(CMLMOBObserver* observer);
CML_API const float*          cmlGetObserverAdaptationWhiteYxyRadiometric   (CMLMOBObserver* observer);
CML_API const float*          cmlGetObserverAdaptationWhiteYupvpRadiometric (CMLMOBObserver* observer);





CML_API float                 cmlGetGeneratorMetricScale                    (CMLMOBGenerator* generator);
CML_API CMLMOBFunctionVector* cmlGetGeneratorFunctions                      (CMLMOBGenerator* generator);

CML_API void                  cmlSetGeneratorMetricScale                    (CMLMOBGenerator* generator,
                                                                                       float metricScale);
CML_API void                  cmlSetGeneratorFunctions                      (CMLMOBGenerator* generator,
                                                                        CMLMOBFunctionVector* functions);

CML_API const float*          cmlGetGeneratorWhiteXYZRadiometric            (CMLMOBGenerator* generator);
CML_API const float*          cmlGetGeneratorWhiteInvXYZRadiometric         (CMLMOBGenerator* generator);
CML_API const float*          cmlGetGeneratorRedPrimaryYxyRadiometric       (CMLMOBGenerator* generator);
CML_API const float*          cmlGetGeneratorBluePrimaryYxyRadiometric      (CMLMOBGenerator* generator);



//CML_API const float*          cmlGetGeneratorAdaptationWhiteYxyRadiometric  (CMLMOBGenerator* observer);
//CML_API const float*          cmlGetGeneratorAdaptationWhiteYupvpRadiometric(CMLMOBGenerator* observer);


//// Gets or sets the filter functions. The filter functions are x_, y_ and z_
//// for a standard observer for example.
//CML_API void                 cmlSetObserverFilterFunctions(
//                                        CMLObserver* observer,
//                            const CMLFunctionVector* filters);
//
//
//// Gets or sets the generator functions.
//CML_API const CMLFunctionVector*  cmlGetObserverGeneratorFunctions(
//                                  const CMLObserver* observer);
//CML_API void                      cmlSetObserverGeneratorFunctions(
//                                        CMLObserver* observer,
//                            const CMLFunctionVector* generators);
//
//
//// Get or set the scaling of Y values resulting from computation with this
//// observer.
//CML_API float cmlGetObserverMetricScale(const CMLObserver* observer);
//CML_API void  cmlSetObserverMetricScale(      CMLObserver* observer,
//                                                     float metricScale);
//
//
//// ////////////////////////////////
//// Other methods:
//// ////////////////////////////////
//
//// Fills the given result array with the spectral color at wavelength lambda.
//// The result will be normalized and scaled by the metric scale of this
//// observer.
//CML_API void cmlGetSpectralColor(     const CMLObserver* observer,
//                                                  float* result,
//                                                   float lambda);
//



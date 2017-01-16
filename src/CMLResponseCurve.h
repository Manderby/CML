
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.




CML_API CMLMOBResponseCurve* cmlCreateResponseCurveWithPreset(
                                    CMLResponseCurvePreset preset);

CML_API CMLMOBResponseCurve* cmlCreateResponseCurveGammaLinear(
                                                     float gamma,
                                                     float offset,
                                                     float linscale,
                                                     float split);

// ForwardFunc points away from XYZ, BackwardFunc towards it. Meaning:
// For an RGB space, ForwardFunc is needed for the transformation XYZ->RGB
// whereas BackwardFunc is needed for the transformation RGB->XYZ.
// For an Lab space, ForwardFunc is needed for the transformation XYZ->Lab
// whereas BackwardFunc is needed for the transformation Lab->XYZ.

CML_API CMLMOBFunction* cmlGetResponseCurveForwardFunc(CMLMOBResponseCurve* curve);
CML_API CMLMOBFunction* cmlGetResponseCurveBackwardFunc(CMLMOBResponseCurve* curve);
CML_API CMLFunctionType cmlGetResponseCurveFunctionType(CMLMOBResponseCurve* curve);




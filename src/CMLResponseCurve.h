
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.




CMLAPI CMLResponseCurve* cmlCreateResponseCurveWithPreset(
                                    CMLResponseCurvePreset preset);

CMLAPI CMLResponseCurve* cmlCreateResponseCurveWith4ParamsFunction(
                                                     float param0,
                                                     float param1,
                                                     float param2,
                                                     float param3);

// ForwardFunc points away from XYZ, BackwardFunc towards it. Meaning:
// For an RGB space, ForwardFunc is needed for the transformation XYZ->RGB
// whereas BackwardFunc is needed for the transformation RGB->XYZ.
// For an Lab space, ForwardFunc is needed for the transformation XYZ->Lab
// whereas BackwardFunc is needed for the transformation Lab->XYZ.
CMLAPI CMLFunction* cmlGetResponseCurveForwardFunc(const CMLResponseCurve* curve);
CMLAPI CMLFunction* cmlGetResponseCurveBackwardFunc(const CMLResponseCurve* curve);
//CMLAPI CMLFunctionType cmlGetResponseCurveForwardFunctionType(const CMLResponseCurve* curve);
CMLAPI float cmlGetResponseCurveParam0(const CMLResponseCurve* curve);
CMLAPI float cmlGetResponseCurveParam1(const CMLResponseCurve* curve);
CMLAPI float cmlGetResponseCurveParam2(const CMLResponseCurve* curve);
CMLAPI float cmlGetResponseCurveParam3(const CMLResponseCurve* curve);




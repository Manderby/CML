
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.




CMLAPI CMLResponseCurve* cmlCreateResponseCurveWith4ParamsFunction(
                                         CMLResponseCurve* curve,
//                                           CMLFunctionType type,
                                                     float param0,
                                                     float param1,
                                                     float param2,
                                                     float param3);

CMLAPI CMLResponseCurve* cmlCreateResponseCurveCopy(CMLResponseCurve* dstcurve, CMLResponseCurve* srccurve);

CMLAPI CMLResponseCurve* cmlCreateResponseCurveWithPreset(
                                        CMLResponseCurve* curve,
                                   CMLResponseCurvePreset preset);

CMLAPI void CMLclearResponseCurve(CMLResponseCurve* curve);
CMLAPI void CMLdestroyResponseCurve(CMLResponseCurve* curve);

// ForwardFunc points away from XYZ, BackwardFunc towards it. Meaning:
// For an RGB space, ForwardFunc is needed for the transformation XYZ->RGB
// whereas BackwardFunc is needed for the transformation RGB->XYZ.
// For an Lab space, ForwardFunc is needed for the transformation XYZ->Lab
// whereas BackwardFunc is needed for the transformation Lab->XYZ.
CMLAPI CMLFunction* CMLgetResponseCurveFunc(const CMLResponseCurve* curve);
CMLAPI CMLFunction* CMLgetResponseCurveInvFunc(const CMLResponseCurve* curve);
//CMLAPI CMLFunctionType CMLgetResponseCurveFunctionType(const CMLResponseCurve* curve);
CMLAPI float CMLgetResponseCurveParam0(const CMLResponseCurve* curve);
CMLAPI float CMLgetResponseCurveParam1(const CMLResponseCurve* curve);
CMLAPI float CMLgetResponseCurveParam2(const CMLResponseCurve* curve);
CMLAPI float CMLgetResponseCurveParam3(const CMLResponseCurve* curve);





// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.


CMLAPI CMLRGBSpace* cmlCreateRGBSpaceWithPreset(CMLRGBSpaceType type, const CMLObserver* observer);

CMLAPI const float* cmlGetRGBSpaceInverseMatrix(const CMLRGBSpace* rgbspace);
CMLAPI const float* cmlGetRGBSpacePrimaryYxy(const CMLRGBSpace* rgbspace, CMLInt index);

CMLAPI const CMLResponseCurve* cmlGetRGBSpaceResponseCurve(const CMLRGBSpace* rgbspace, CMLInt index);
CMLAPI const CMLWhitepoint* cmlGetRGBSpaceWhitepoint(const CMLRGBSpace* rgbspace);
CMLAPI CMLRGBSpaceType cmlGetRGBSpaceType(const CMLRGBSpace* rgbspace);



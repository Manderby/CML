
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

//
//CML_API CMLRGBSpace* cmlCreateRGBSpaceWithPreset(CMLRGBSpaceType type, const CMLObserver* observer);
//
//CML_API const float* cmlGetRGBSpaceInverseMatrix(const CMLRGBSpace* rgbspace);
//CML_API const float* cmlGetRGBSpacePrimaryYxy(const CMLRGBSpace* rgbspace, CMLInt index);
//
//CML_API const CMLResponseCurve* cmlGetRGBSpaceResponseCurve(const CMLRGBSpace* rgbspace, CMLInt index);
//CML_API const CMLObserver* cmlGetRGBSpaceObserver(const CMLRGBSpace* rgbspace);
//CML_API CMLRGBSpaceType cmlGetRGBSpaceType(const CMLRGBSpace* rgbspace);
//
//
//// The following three functions return information to predefined RGB color
//// spaces. The CML_RGB_CUSTOM space is not valid. If an invalid colorspaceType
//// is provided, the values will be uninitialized.

// Returns all three primaries of a predefined RGB colorspace. Note that
// the Y component of the three primaries will always be 1.
CML_API void cmlGetRGBSpacePrimaries(
                                  CMLRGBSpaceType      colorspaceType,
                                  CMLVec3               primaryRYxy,
                                  CMLVec3               primaryGYxy,
                                  CMLVec3               primaryBYxy);

// Computes the matrix for RGB -> XYZ conversions given the three primaries and
// the white as Yxy colors. Note that the Y component of the three
// primaries will be changed by this function call. Also note that you can
// choose to have a colorimetric instead of a radiometric computation by simply
// setting the Y component of the white to 1.
// Also note that in order to get the inverse transformation matrix, simply
// use the cmlMat33Inverse functin.
//CML_API void CMLcomputeRGBToXYZMatrix(
//                                              CMLMat33  rgbtoxyzmatrix,
//                                              CMLVec3   primaryRYxy,
//                                              CMLVec3   primaryGYxy,
//                                              CMLVec3   primaryBYxy,
//                                        const CMLVec3   whiteYxy);



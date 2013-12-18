
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.



// illuminationSpectrum:  The spectrum function of the desired reference
//                        illumination. This observer will duplicate the
//                        function.
// colorimetricBase:      The Y value of the reference illumination.
//                        In colorimetry, this is usually 1 or 100.
//                        If you use 0, computation is radiometric.
CMLAPI CMLWhitepoint* cmlCreateWhitepointWithIllumination(
                                  const CMLIllumination* illumination,
                                      const CMLObserver* observer,
                                                   float colorimetricBase);

CMLAPI float cmlGetWhitepointRadiometricScale(const CMLWhitepoint* whitepoint);
CMLAPI float cmlGetWhitepointColorimetricBase(const CMLWhitepoint* whitepoint);
CMLAPI const CMLObserver*     cmlGetWhitepointObserver(const CMLWhitepoint* whitepoint);
CMLAPI const CMLIllumination* cmlGetWhitepointIllumination(const CMLWhitepoint* whitepoint);

CMLAPI const float* cmlGetWhitepointXYZ(const CMLWhitepoint* whitepoint);
CMLAPI const float* cmlGetWhitepointInverseXYZ(const CMLWhitepoint* whitepoint);
CMLAPI const float* cmlGetWhitepointYxy(const CMLWhitepoint* whitepoint);
CMLAPI const float* cmlGetWhitepointYupvp(const CMLWhitepoint* whitepoint);

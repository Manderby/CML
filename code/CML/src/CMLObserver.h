
// type:                  Defines, what spectral distribution functions to use.
// illumination:          The spectrum function of the desired reference
//                        illumination. This observer will duplicate the
//                        function.
// colorimetricBase:      The Y value of the reference illumination.
//                        In colorimetry, this is usually 1 or 100.
//                        If you use 0, computation is radiometric.
CML_API CMLObserver* cmlCreateObserver(
  CMLObserver* observer,
  CMLObserverType type,
  CMLIllumination* illumination,
  float colorimetricBase);

CML_API void cmlClearObserver  (CMLObserver* observer);
CML_API void cmlDestroyObserver(CMLObserver* observer);

CML_API float                  cmlGetObserverRadiometricScale     (const CMLObserver* observer);
CML_API float                  cmlGetObserverColorimetricBase     (const CMLObserver* observer);
CML_API const CMLFunction*     cmlGetObserverSpecDistFunction     (const CMLObserver* observer, CMLInt index);

CML_API CMLObserverType        cml_GetObserverType                 (const CMLObserver* observer);

CML_API const CMLIllumination* cmlGetReferenceIllumination        (const CMLObserver* observer);
CML_API const CMLFunction*     cmlGetReferenceIlluminationSpectrum(const CMLObserver* observer);
CML_API const float*           cmlGetReferenceWhitepointXYZ       (const CMLObserver* observer);
CML_API const float*           cmlGetReferenceInverseWhitepointXYZ(const CMLObserver* observer);
CML_API const float*           cmlGetReferenceWhitepointYxy       (const CMLObserver* observer);
CML_API const float*           cmlGetReferenceWhitepointYupvp     (const CMLObserver* observer);



// This is free and unencumbered software released into the public domain.

// Anyone is free to copy, modify, publish, use, compile, sell, or
// distribute this software, either in source code form or as a compiled
// binary, for any purpose, commercial or non-commercial, and by any
// means.

// In jurisdictions that recognize copyright laws, the author or authors
// of this software dedicate any and all copyright interest in the
// software to the public domain. We make this dedication for the benefit
// of the public at large and to the detriment of our heirs and
// successors. We intend this dedication to be an overt act of
// relinquishment in perpetuity of all present and future rights to this
// software under copyright law.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
// OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.

// For more information, please refer to <http://unlicense.org/>

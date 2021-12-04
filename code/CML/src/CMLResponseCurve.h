
// A response curve stores a pair of value transformation functions. Values
// in XYZ are considered to be "Linear" in the sense of radiometic intensity.
// The higher the value though, a human observer perceyves fewer luminance
// differences. Therefore, one uses response curves, to convert linear values
// into perceyved values.
//
// The two functions stored in a response curve are:
// - The forward function "Func" which always points away from XYZ.
// - The backward function "InvFunc" which always points towards XYZ.
// More precise:
//
// For an RGB space, Func is needed for the transformation XYZ->RGB
// whereas InvFunc is needed for the transformation RGB->XYZ.
// For an Lab space, Func is needed for the transformation XYZ->Lab
// whereas InvFunc is needed for the transformation Lab->XYZ.



// Allocates memory for a response curve. Values are uninitialized. You must
// deallocate the memory using free().
CML_API CMLResponseCurve* cmlAllocResponseCurve(void);

// Initializes a response curve to an empty state.
CML_API void cmlInitResponseCurve(CMLResponseCurve* curve);

// Initializes the response curve with the values of the src.
CML_API void cmlInitResponseCurveWithCopy(
  CMLResponseCurve* dstCurve,
  CMLResponseCurve* srcCurve);

// Initializes the response curve with the predefined values defined by preset.
CML_API void cmlInitResponseCurveWithPreset(
  CMLResponseCurve* curve,
  CMLResponseCurvePreset preset);

// Initializes the response curve with a curve containing a gamma with an
// offset and linear part split at a certain position.
CML_API void cmlInitResponseCurveWith4ParamsFunction(
  CMLResponseCurve* curve,
  float gamma,
  float offset,
  float linScale,
  float split);

// Clears all entries. Values are uninitialized afterwards. You must either
// call a cmlInitResponseCurveXXX function or free() afterwards.
CML_API void cmlClearResponseCurve(CMLResponseCurve* curve);



// Getter for the two functions.
CML_API const CMLFunction* cmlGetResponseCurveFunc(const CMLResponseCurve* curve);
CML_API const CMLFunction* cmlGetResponseCurveInvFunc(const CMLResponseCurve* curve);

// Returns the function type used in this curve.
CML_API CMLFunctionType cmlGetResponseCurveFunctionType(const CMLResponseCurve* curve);

// Getter for the parameters of the curve, if applicable.
CML_API float cmlGetResponseCurveParam0(const CMLResponseCurve* curve);
CML_API float cmlGetResponseCurveParam1(const CMLResponseCurve* curve);
CML_API float cmlGetResponseCurveParam2(const CMLResponseCurve* curve);
CML_API float cmlGetResponseCurveParam3(const CMLResponseCurve* curve);



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

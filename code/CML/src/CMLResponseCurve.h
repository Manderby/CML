
CML_API CMLResponseCurve* cmlCreateResponseCurveWith4ParamsFunction(
                                         CMLResponseCurve* curve,
//                                           CMLFunctionType type,
                                                     float param0,
                                                     float param1,
                                                     float param2,
                                                     float param3);

CML_API CMLResponseCurve* cmlCreateResponseCurveCopy(CMLResponseCurve* dstcurve, CMLResponseCurve* srccurve);

CML_API CMLResponseCurve* cmlCreateResponseCurveWithPreset(
                                        CMLResponseCurve* curve,
                                   CMLResponseCurvePreset preset);

CML_API void CMLclearResponseCurve(CMLResponseCurve* curve);
CML_API void CMLdestroyResponseCurve(CMLResponseCurve* curve);

// ForwardFunc points away from XYZ, BackwardFunc towards it. Meaning:
// For an RGB space, ForwardFunc is needed for the transformation XYZ->RGB
// whereas BackwardFunc is needed for the transformation RGB->XYZ.
// For an Lab space, ForwardFunc is needed for the transformation XYZ->Lab
// whereas BackwardFunc is needed for the transformation Lab->XYZ.
CML_API CMLFunction* CMLgetResponseCurveFunc(const CMLResponseCurve* curve);
CML_API CMLFunction* CMLgetResponseCurveInvFunc(const CMLResponseCurve* curve);
//CML_API CMLFunctionType CMLgetResponseCurveFunctionType(const CMLResponseCurve* curve);
CML_API float CMLgetResponseCurveParam0(const CMLResponseCurve* curve);
CML_API float CMLgetResponseCurveParam1(const CMLResponseCurve* curve);
CML_API float CMLgetResponseCurveParam2(const CMLResponseCurve* curve);
CML_API float CMLgetResponseCurveParam3(const CMLResponseCurve* curve);



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

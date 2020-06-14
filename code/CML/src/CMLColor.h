
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.


CML_API CMLColor* cmlCreateRadiometric(CMLColorspace* colorspace, CMLMOBFunction* spectrum);
CML_API CMLColor* cmlCreateXYZ(CMLColorspace* colorspace, float X, float Y, float Z);
CML_API CMLColor* cmlCreateNormXYZ(CMLColorspace* colorspace, float X, float Y, float Z);
CML_API CMLColor* cmlCreateYxy(CMLColorspace* colorspace, float Y, float x, float y);
CML_API CMLColor* cmlCreateYupvp(CMLColorspace* colorspace, float Y, float up, float vp);
CML_API CMLColor* cmlCreateYuv(CMLColorspace* colorspace, float Y, float u, float v);
CML_API CMLColor* cmlCreateLuv(CMLColorspace* colorspace, float L, float u, float v);
CML_API CMLColor* cmlCreateLab(CMLColorspace* colorspace, float L, float a, float b);
CML_API CMLColor* cmlCreateLch(CMLColorspace* colorspace, float L, float c, float h);
CML_API CMLColor* cmlCreateRGB(CMLColorspace* colorspace, float R, float G, float B);
CML_API CMLColor* cmlCreateHSV(CMLColorspace* colorspace, float H, float S, float V);
CML_API CMLColor* cmlCreateHSL(CMLColorspace* colorspace, float H, float S, float L);
CML_API CMLColor* cmlCreateYCbCr(CMLColorspace* colorspace, float Y, float Cb, float Cr);

CML_API CMLColor* cmlCreateColor(CMLColorspace* dstcolorspace, CMLColor* srccolor);

CML_API void* cmlCreateColorStorage(CMLColor* color);
CML_API void cmlFillColorWithBuf(CMLColor* color, void* buf);

CML_API const void* cmlGetColorData(CMLColor* color);

CML_API void cmlSetColorFloatComponent(CMLColor* color, CMLInt indx, float value);
CML_API void cmlSetColorFunctionComponent(CMLColor* color, CMLInt indx, CMLMOBFunction* value);
CML_API float cmlGetColorFloatComponent(CMLColor* color, CMLInt indx);
CML_API struct MOB* cmlGetColorFunctionComponent(CMLColor* color, CMLInt indx);

CML_API void cmlDebugColor(CMLColor* color);

CML_API void cmlDestroyColor(CMLColor* color);

CML_API CMLColorspace* cmlGetColorColorspace(CMLColor* color);

//void cml_ReattachColorBuffer(CMLColor* dstcolor, void* outbuf);


// This function will create a new color with the given colorspace. The newly
// created color will be returned in the colorptr argument. The void* returned
// by the function points to the storage in memory where the values are stored.
// Values storing functions will be initialized with CML_NULL, other values
// are uninitialized. These values are guaranteed to be in an array as long as
// the colorspace does not store mixed components. Colorspaces with mixed
// components will return CML_NULL and any initialization must be performed
// with cmlSetColorXXXComponent.
CML_API CMLColor* cmlCreateColorspaceColor(CMLColorspace* colorspace);


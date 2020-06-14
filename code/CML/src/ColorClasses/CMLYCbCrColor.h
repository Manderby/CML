//
//// YCbCrColor is a 3-dimensional vector
//// Y-Range: (0,1),       Y-Component
//// Cb-Range: (-.5,.5),   Cb-Component
//// Cr-Range: (-.5,.5),   Cr-Component
//// The bounds are defined as constants in CMLConstants.h
////
//// (c) Manderim GmbH
//// This is proprietary software. Any use without the explicit acknowledgement
//// of the author of this software is prohibited and any liability is disclamed.
//// Terms of a separate contract may apply.
//
//class YCbCrColor : public Color{
//  float color[3];
//public:
//
//  // ///////////////////////////////////////
//  // Constructors and initialization methods
//  // ///////////////////////////////////////
//
//  YCbCrColor();
//  ~YCbCrColor();
//
//  YCbCrColor(float Y, float Cb, float Cr);
//  YCbCrColor(const Color& anycolor);
//  YCbCrColor(const YCbCrColor& ycbcr);
//
//  void init(float Y, float Cb, float Cr);
//  YCbCrColor& operator =(const Color& anycolor);
//  YCbCrColor& operator =(const YCbCrColor& ycbcr);
//
//  // ///////////////////////////////////////
//  // Mathematical operators in cartesian space
//  // ///////////////////////////////////////
//
//  YCbCrColor operator +() const;
//  YCbCrColor operator -() const;
//
//  YCbCrColor operator +(const Color& anycolor) const;
//  YCbCrColor operator -(const Color& anycolor) const;
//  YCbCrColor operator *(const float factor) const;
//  YCbCrColor operator /(const float divisor) const;
//
//  YCbCrColor& operator +=(const Color& anycolor);
//  YCbCrColor& operator -=(const Color& anycolor);
//  YCbCrColor& operator *=(float factor);
//  YCbCrColor& operator /=(float divisor);
//
//  float dot(const YCbCrColor& luv) const;
//  float length() const;
//
//  CMLBool operator ==(const YCbCrColor& ycbcr) const;
//  CMLBool operator !=(const YCbCrColor& ycbcr) const;
//
//  // ///////////////////////////////////////
//  // various methods
//  // ///////////////////////////////////////
//
//  operator const float*() const;  // Accessor
//  operator       float*();        // Mutator
//
//  YCbCrColor getInverse();
//  void invert();
//  
//  CMLBool insideY();
//  CMLBool insideCb();
//  CMLBool insideCr();
//  CMLBool inside();
//  void clamp();
//
//  CMLuint32 getNumChannels() const;
//
//  // ///////////////////////////////////////
//  // Converting to different color spaces
//  // ///////////////////////////////////////
//
//  CMLColorType getColorType() const;
//
//  void from8bitBuffer(const CMLByte* input);  
//  void from16bitBuffer(const CMLWord* input);  
//  void fromFloatBuffer(const float* input);  
//  void to8bitBuffer(CMLByte* output) const;
//  void to16bitBuffer(CMLWord* output) const;
//  void toFloatBuffer(float* output) const;
//
//  void fromNormedBuffer(const float* input);  
//  void toNormedBuffer(float* output) const;
//  void fromNormedCartesianBuffer(const float* input);  
//  void toNormedCartesianBuffer(float* output) const;
//
//  void fromGrayBuffer (const float* src);
//  void fromXYZBuffer  (const float* src);
//  void fromYuvBuffer  (const float* src);
//  void fromYupvpBuffer(const float* src);
//  void fromYxyBuffer  (const float* src);
//  void fromLabBuffer  (const float* src);
//  void fromLchBuffer  (const float* src);
//  void fromLuvBuffer  (const float* src);
//  void fromRGBBuffer  (const float* src);
//  void fromYCbCrBuffer(const float* src);
//  void fromHSVBuffer  (const float* src);
//  void fromHSLBuffer  (const float* src);
//  void fromCMYKBuffer (const float* src);
//
//  void toGrayBuffer(float* dest) const;
//  void toXYZBuffer(float* dest) const;
//  void toYuvBuffer(float* dest) const;
//  void toYupvpBuffer(float* dest) const;
//  void toYxyBuffer(float* dest) const;
//  void toLabBuffer(float* dest) const;
//  void toLchBuffer(float* dest) const;
//  void toLuvBuffer(float* dest) const;
//  void toRGBBuffer(float* dest) const;
//  void toYCbCrBuffer(float* dest) const;
//  void toHSVBuffer(float* dest) const;
//  void toHSLBuffer(float* dest) const;
//  void toCMYKBuffer(float* dest) const;
//
//};
//

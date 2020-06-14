//
//// XYZColor is a 3-dimensional vector
//// X-Range: (0, 1), X-Axis
//// Y-Range: (0, 1), Y-Axis
//// Z-Range: (0, 1), Z-Axis
//// The bounds are defined as constants in CMLConstants.h
////
//// Be aware that the Y component is defined to be based on 1, not 100.
////
//// (c) Manderim GmbH
//// This is proprietary software. Any use without the explicit acknowledgement
//// of the author of this software is prohibited and any liability is disclamed.
//// Terms of a separate contract may apply.
//
//class XYZColor : public Color{
//  float color[3];
//public:
//
//  // ///////////////////////////////////////
//  // Constructors and initialization methods
//  // ///////////////////////////////////////
//
//  XYZColor();
//  ~XYZColor();
//
//  XYZColor(float X, float Y, float Z);
//  XYZColor(const Color& anycolor);
//  XYZColor(const XYZColor& xyz);
//
//  void init(float X, float Y, float Z);
//  XYZColor& operator =(const Color& anycolor);
//  XYZColor& operator =(const XYZColor& xyz);
//
//  // ///////////////////////////////////////
//  // Mathematical operators in cartesian space
//  // ///////////////////////////////////////
//
//  XYZColor operator +() const;
//  XYZColor operator -() const;
//
//  XYZColor  operator +(const Color& anycolor) const;
//  XYZColor  operator -(const Color& anycolor) const;
//  XYZColor  operator *(const float factor) const;
//  XYZColor  operator /(const float divisor) const;
//
//  XYZColor& operator +=(const Color& anycolor);
//  XYZColor& operator -=(const Color& anycolor);
//  XYZColor& operator *=(float factor);
//  XYZColor& operator /=(float divisor);
//
//  float dot(const XYZColor& xyz) const;
//  float length() const;
//
//  CMLBool operator ==(const XYZColor& xyz) const;
//  CMLBool operator !=(const XYZColor& xyz) const;
//
//  // ///////////////////////////////////////
//  // various methods
//  // ///////////////////////////////////////
//
//  operator const float*() const;  // Accessor
//  operator       float*();        // Mutator
//
//  XYZColor getInverse();
//  void invert();
//  
//  CMLBool insideX();
//  CMLBool insideY();
//  CMLBool insideZ();
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
// 
//};
//

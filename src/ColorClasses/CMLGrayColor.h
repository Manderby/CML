//
//// GrayColor is a 1-dimensional value
//// Range: (0,1)
//// The bounds are defined as constants in CMLConstants.h
//// The interpretation of this value depends on the interpretation setting of the
//// ColorMachine, default is: 0 represents white, 1 represents black.
////
//// (c) Manderim GmbH
//// This is proprietary software. Any use without the explicit acknowledgement
//// of the author of this software is prohibited and any liability is disclamed.
//// Terms of a separate contract may apply.
//
//class GrayColor : public Color{
//  float color[1];
//public:
//  
//  // ///////////////////////////////////////
//  // Constructors and initialization methods
//  // ///////////////////////////////////////
//
//  GrayColor();
//  ~GrayColor();
//
//  GrayColor(float gray);
//  GrayColor(const Color& anycolor);
//  GrayColor(const GrayColor& gray);
//  
//  void init(float gray);
//  GrayColor& operator =(const Color& anycolor);
//  GrayColor& operator =(const GrayColor& gray);
//
//  // ///////////////////////////////////////
//  // Mathematical operators in cartesian space
//  // ///////////////////////////////////////
//
//  GrayColor operator +() const;
//  GrayColor operator -() const;
//
//  GrayColor operator +(const Color& anycolor) const;
//  GrayColor operator -(const Color& anycolor) const;
//  GrayColor operator *(const float factor) const;
//  GrayColor operator /(const float divisor) const;
//
//  GrayColor& operator +=(const Color& anycolor);
//  GrayColor& operator -=(const Color& anycolor);
//  GrayColor& operator *=(float factor);
//  GrayColor& operator /=(float divisor);
//
//  float dot(const GrayColor& gray) const;
//  float length() const;
//
//  CMLBool operator ==(const GrayColor& gray) const;
//  CMLBool operator !=(const GrayColor& gray) const;
//
//  // ///////////////////////////////////////
//  // various methods
//  // ///////////////////////////////////////
//
//  operator const float*() const;  // Accessor
//  operator       float*();        // Mutator
//
//  GrayColor getInverse() const;
//  void invert();
//
//  CMLBool inside() const;
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

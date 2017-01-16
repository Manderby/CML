//
//// YupvpColor is a 3-dimensional vector
//// Y-Range: (0, 1),   Y-Axis
//// U-Range: (0, 1),   U-Component
//// V-Range: (0, 0.5),   V-Component
//// The bounds are defined as constants in CMLConstants.h
//
//// Be aware that the Y component is defined to be based on 1, not 100.
//// Note that V-Values close to or equal to 0.5 may lead to strong
//// fluctuations
////
//// (c) Manderim GmbH
//// This is proprietary software. Any use without the explicit acknowledgement
//// of the author of this software is prohibited and any liability is disclamed.
//// Terms of a separate contract may apply.
//
//class YupvpColor : public Color{
//  float color[3];
//public:
//
//  // ///////////////////////////////////////
//  // Constructors and initialization methods
//  // ///////////////////////////////////////
//
//  YupvpColor();
//  ~YupvpColor();
//
//  YupvpColor(float Y, float U, float V);
//  YupvpColor(const Color& anycolor);
//  YupvpColor(const YupvpColor& Yupvp);
//
//  void init(float Y, float U, float V);
//  YupvpColor& operator =(const Color& anycolor);
//  YupvpColor& operator =(const YupvpColor& Yupvp);
//
//  // ///////////////////////////////////////
//  // Mathematical operators in cartesian space
//  // ///////////////////////////////////////
//
//  YupvpColor operator +() const;
//  YupvpColor operator -() const;
//
//  YupvpColor  operator +(const Color& anycolor) const;
//  YupvpColor  operator -(const Color& anycolor) const;
//  YupvpColor  operator *(const float factor) const;
//  YupvpColor  operator /(const float divisor) const;
//
//  YupvpColor& operator +=(const Color& anycolor);
//  YupvpColor& operator -=(const Color& anycolor);
//  YupvpColor& operator *=(float factor);
//  YupvpColor& operator /=(float divisor);
//
//  float dot(const YupvpColor& Yupvp) const;
//  float length() const;
//
//  CMLBool operator ==(const YupvpColor& Yupvp) const;
//  CMLBool operator !=(const YupvpColor& Yupvp) const;
//
//  // ///////////////////////////////////////
//  // various methods
//  // ///////////////////////////////////////
//
//  operator const float*() const;  // Accessor
//  operator       float*();        // Mutator
//
//  YupvpColor getInverse();
//  void invert();
//
//  CMLBool insideY();
//  CMLBool insideU();
//  CMLBool insideV();
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
//  void fromYupvpBuffer  (const float* src);
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

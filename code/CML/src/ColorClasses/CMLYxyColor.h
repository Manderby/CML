
// YxyColor is a 3-dimensional vector
// Y-Range: (0,1),  Y-Axis
// x-Range: (0,1),   x-Component
// y-Range: (0,1),   y-Component
// The bounds are defined as constants in CMLConstants.h
//
// Be aware that the Y component is defined to be based on 1, not 100.
//
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

class YxyColor : public Color{
  float color[3];
public:

  // ///////////////////////////////////////
  // Constructors and initialization methods
  // ///////////////////////////////////////

  YxyColor();
  ~YxyColor();

  YxyColor(float Y, float x, float y);
  YxyColor(const Color& anycolor);
  YxyColor(const YxyColor& yxy);

  void init(float Y, float x, float y);
  YxyColor& operator =(const Color& anycolor);
  YxyColor& operator =(const YxyColor& yxy);

  // ///////////////////////////////////////
  // Mathematical operators in cartesian space
  // ///////////////////////////////////////

  YxyColor operator +() const;
  YxyColor operator -() const;

  YxyColor  operator +(const Color& anycolor) const;
  YxyColor  operator -(const Color& anycolor) const;
  YxyColor  operator *(const float factor) const;
  YxyColor  operator /(const float divisor) const;

  YxyColor& operator +=(const Color& anycolor);
  YxyColor& operator -=(const Color& anycolor);
  YxyColor& operator *=(float factor);
  YxyColor& operator /=(float divisor);

  float dot(const YxyColor& yxy) const;
  float length() const;

  CMLBool operator ==(const YxyColor& yxy) const;
  CMLBool operator !=(const YxyColor& yxy) const;

  // ///////////////////////////////////////
  // various methods
  // ///////////////////////////////////////

  operator const float*() const;  // Accessor
  operator       float*();        // Mutator

  YxyColor getInverse();
  void invert();

  CMLBool insideY();
  CMLBool insidex();
  CMLBool insidey();
  CMLBool inside();
  void clamp();

  CMLuint32 getNumChannels() const;

  // ///////////////////////////////////////
  // Converting to different color spaces
  // ///////////////////////////////////////

  CMLColorType getColorType() const;

  void from8bitBuffer(const CMLByte* input);  
  void from16bitBuffer(const CMLWord* input);  
  void fromFloatBuffer(const float* input);  
  void to8bitBuffer(CMLByte* output) const;
  void to16bitBuffer(CMLWord* output) const;
  void toFloatBuffer(float* output) const;

  void fromNormedBuffer(const float* input);  
  void toNormedBuffer(float* output) const;
  void fromNormedCartesianBuffer(const float* input);  
  void toNormedCartesianBuffer(float* output) const;

  void fromGrayBuffer (const float* src);
  void fromXYZBuffer  (const float* src);
  void fromYuvBuffer  (const float* src);
  void fromYupvpBuffer(const float* src);
  void fromYxyBuffer  (const float* src);
  void fromLabBuffer  (const float* src);
  void fromLchBuffer  (const float* src);
  void fromLuvBuffer  (const float* src);
  void fromRGBBuffer  (const float* src);
  void fromYCbCrBuffer(const float* src);
  void fromHSVBuffer  (const float* src);
  void fromHSLBuffer  (const float* src);
  void fromCMYKBuffer (const float* src);

  void toGrayBuffer(float* dest) const;
  void toXYZBuffer(float* dest) const;
  void toYuvBuffer(float* dest) const;
  void toYupvpBuffer(float* dest) const;
  void toYxyBuffer(float* dest) const;
  void toLabBuffer(float* dest) const;
  void toLchBuffer(float* dest) const;
  void toLuvBuffer(float* dest) const;
  void toRGBBuffer(float* dest) const;
  void toYCbCrBuffer(float* dest) const;
  void toHSVBuffer(float* dest) const;
  void toHSLBuffer(float* dest) const;
  void toCMYKBuffer(float* dest) const;

};


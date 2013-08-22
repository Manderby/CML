
// LchColor is a 3-dimensional vector
// L-Range: (0,100),  0 represents black, 100 represents white
// c-Range: (0, 128), chromaticity
// h-Range: (0, 360), hue
// The bounds are defined as constants in CMLConstants.h
//
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.


class LchColor : public Color{
  float color[3];
public:

  // ///////////////////////////////////////
  // Constructors and initialization methods
  // ///////////////////////////////////////

  LchColor();
  ~LchColor();

  LchColor(float L, float c, float h);
  LchColor(const Color& anycolor);
  LchColor(const LchColor& lch);

  void init(float L, float c, float h);
  LchColor& operator =(const Color& anycolor);
  LchColor& operator =(const LchColor& lch);

  // ///////////////////////////////////////
  // Mathematical operators in cartesian space
  // Lch is not cartesian. Internally, Lab will be used. See implementation.
  // ///////////////////////////////////////

  LchColor operator +() const;
  LchColor operator -() const;

  LchColor operator +(const Color& anycolor) const;
  LchColor operator -(const Color& anycolor) const;
  LchColor operator *(const float factor) const;
  LchColor operator /(const float divisor) const;

  LchColor& operator +=(const Color& addcolor);
  LchColor& operator -=(const Color& anycolor);
  LchColor& operator *=(float factor);
  LchColor& operator /=(float divisor);

  float dot(const LchColor& lch) const;
  float length() const;

  CMLBool operator ==(const LchColor& lch) const;
  CMLBool operator !=(const LchColor& lch) const;

  // ///////////////////////////////////////
  // various methods
  // ///////////////////////////////////////

  operator const float*() const;  // Accessor
  operator       float*();        // Mutator

  LchColor getInverse();
  void invert();

  CMLBool insideL();
  CMLBool insidec();
  CMLBool insideh();
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



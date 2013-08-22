
// HSVColor is a 3-dimensional vector
// H-Range: (0,360), hue in degrees
// S-Range: (0,1),   saturation
// V-Range: (0,1),   value
// The bounds are defined as constants in CMLConstants.h
//
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

class HSVColor : public Color{
  float color[3];
public:

  // ///////////////////////////////////////
  // Constructors and initialization methods
  // ///////////////////////////////////////

  HSVColor();
  ~HSVColor();

  HSVColor(float H, float S, float V);
  HSVColor(const Color& anycolor);
  HSVColor(const HSVColor& hsv);

  void init(float H, float S, float V);
  HSVColor& operator =(const Color& anycolor);
  HSVColor& operator =(const HSVColor& hsv);

  // ///////////////////////////////////////
  // Mathematical operators in cartesian space
  // HSV is not cartesian. Internally, RGB will be used. See implementation.
  // ///////////////////////////////////////

  HSVColor operator +() const;
  HSVColor operator -() const;

  HSVColor operator +(const Color& color) const;
  HSVColor operator -(const Color& anycolor) const;
  HSVColor operator *(const float factor) const;
  HSVColor operator /(const float divisor) const;

  HSVColor& operator +=(const Color& anycolor);
  HSVColor& operator -=(const Color& anycolor);
  HSVColor& operator *=(float factor);
  HSVColor& operator /=(float divisor);

  float dot(const HSVColor& hsv) const;
  float length() const;

  CMLBool operator ==(const HSVColor& hsv) const;
  CMLBool operator !=(const HSVColor& hsv) const;

  // ///////////////////////////////////////
  // various methods
  // ///////////////////////////////////////

  operator const float*() const;  // Accessor
  operator       float*();        // Mutator

  HSVColor getInverse();
  void invert();
  
  CMLBool insideH();
  CMLBool insideS();
  CMLBool insideV();
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
  void fromYupvpBuffer(const float* src);
  void fromXYZBuffer  (const float* src);
  void fromYuvBuffer  (const float* src);
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


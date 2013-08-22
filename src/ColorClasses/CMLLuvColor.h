
// LuvColor is a 3-dimensional vector
// L-Range: (0,100), 0 represents black, 100 represents white
// u-Range: (-100,100), u-Axis
// v-Range: (-100,100), v-Axis
// The bounds are defined as constants in CMLConstants.h
//
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

class LuvColor : public Color{
  float color[3];
public:

  // ///////////////////////////////////////
  // Constructors and initialization methods
  // ///////////////////////////////////////

  LuvColor();
  ~LuvColor();

  LuvColor(float L, float u, float v);
  LuvColor(const Color& anycolor);
  LuvColor(const LuvColor& luv);

  void init(float L, float u, float v);
  LuvColor& operator =(const Color& anycolor);
  LuvColor& operator =(const LuvColor& luv);

  // ///////////////////////////////////////
  // Mathematical operators in cartesian space
  // ///////////////////////////////////////

  LuvColor operator +() const;
  LuvColor operator -() const;

  LuvColor operator +(const Color& anycolor) const;
  LuvColor operator -(const Color& anycolor) const;
  LuvColor operator *(const float factor) const;
  LuvColor operator /(const float divisor) const;

  LuvColor& operator +=(const Color& anycolor);
  LuvColor& operator -=(const Color& anycolor);
  LuvColor& operator *=(float factor);
  LuvColor& operator /=(float divisor);

  float dot(const LuvColor& luv) const;
  float length() const;

  CMLBool operator ==(const LuvColor& luv) const;
  CMLBool operator !=(const LuvColor& luv) const;

  // ///////////////////////////////////////
  // various methods
  // ///////////////////////////////////////

  operator const float*() const;  // Accessor
  operator       float*();        // Mutator

  LuvColor getInverse();
  void invert();
  
  CMLBool insideL();
  CMLBool insideu();
  CMLBool insidev();
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


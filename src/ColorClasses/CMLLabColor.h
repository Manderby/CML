
// LabColor is a 3-dimensional vector
// L-Range: (0,100), 0 represents black, 100 represents white
// a-Range: (-128,128), a-Axis
// b-Range: (-128,128), b-Axis
// The bounds are defined as constants in CMLConstants.h
//
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

class LabColor : public Color{
  float color[3];
public:

  // ///////////////////////////////////////
  // Constructors and initialization methods
  // ///////////////////////////////////////

  LabColor();
  ~LabColor();

  LabColor(float L);
  LabColor(float L, float a, float b);
  LabColor(const Color& anycolor);
  LabColor(const LabColor& lab);

  void init(float L, float a, float b);
  LabColor& operator =(const Color& anycolor);
  LabColor& operator =(const LabColor& lab);

  // ///////////////////////////////////////
  // Mathematical operators in cartesian space
  // ///////////////////////////////////////

  LabColor operator +() const;
  LabColor operator -() const;

  LabColor operator +(const Color& anycolor) const;
  LabColor operator -(const Color& anycolor) const;
  LabColor operator *(const float factor) const;
  LabColor operator /(const float divisor) const;

  LabColor& operator +=(const Color& anycolor);
  LabColor& operator -=(const Color& anycolor);
  LabColor& operator *=(float factor);
  LabColor& operator /=(float divisor);

  float dot(const LabColor& lab) const;
  float length() const;

  CMLBool operator ==(const LabColor& lab) const;
  CMLBool operator !=(const LabColor& lab) const;

  // ///////////////////////////////////////
  // various methods
  // ///////////////////////////////////////

  operator const float*() const;  // Accessor
  operator       float*();        // Mutator

  LabColor getInverse();
  void invert();
  
  CMLBool insideL();
  CMLBool insidea();
  CMLBool insideb();
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




// SpectralColor is a 1-dimensional function
// The range may be arbitrary
//
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.


class SpectralColor : public Color{

  CMLFunction* spectrum;
  CMLBool bodycolor;

public:

  // ///////////////////////////////////////
  // Constructors and initialization methods
  // ///////////////////////////////////////
  
  // Note that SpectralColor takes ownerwhip of the input CMLFunction. This
  // means that you should not release the CMLFunction after calling the
  // constructor or the init method. If you have a const CMLFunction on the
  // other hand, you need to duplicate the function to create a SpectralColor.
  
  SpectralColor();
  ~SpectralColor();

  SpectralColor(float value);
  SpectralColor(CMLFunction* spectrum, CMLBool bodycolor);
  SpectralColor(const Color& anycolor);
  SpectralColor(const SpectralColor& speccolor);

  SpectralColor& init(CMLFunction* spectrum, CMLBool bodycolor);
  SpectralColor& operator =(const Color& anycolor);
  SpectralColor& operator =(const SpectralColor& speccolor);

  // ///////////////////////////////////////
  // Mathematical operators in cartesian space
  // ///////////////////////////////////////

  SpectralColor operator +() const;
  SpectralColor operator -() const;

  SpectralColor operator +(const SpectralColor& speccolor) const;
  SpectralColor operator -(const SpectralColor& speccolor) const;
  SpectralColor operator *(float factor) const;
  SpectralColor operator /(float divisor) const;

  SpectralColor& operator +=(const Color& anycolor);
  SpectralColor& operator -=(const Color& anycolor);
  SpectralColor& operator *=(float factor);
  SpectralColor& operator /=(float divisor);
  
//  // componentwise multiplication of remissioncolor and emissioncolor
//  SpectralColor operator *(const SpectralColor& speccolor) const;
//  SpectralColor& operator *=(const Color& anycolor);

  // This method currently always returns 0 for spectral colors. There might
  // be a special use in the future. Don't use it.
  CML_INLINE float length() const{return 0.f;}

  // ///////////////////////////////////////
  // various methods
  // ///////////////////////////////////////

  // This method currently always returns inf for spectral colors. There might
  // be a different use in the future. Don't use it.
  CML_INLINE CMLuint32 getNumChannels() const {return (CMLuint32)-1;}

  // This method currently does nothing for spectral colors. There might
  // be a different use in the future. Don't use it.
  void clamp(){}

  CMLBool isBodyColor() const;
//  float getMaxValue() const;
  
  const CMLFunction* getSpectrum() const;

  // Currently, the float* accessor and mutator always return CML_NULL. There
  // might be a different use in the future. Don't use it.
  operator const float*() const;  // Accessor
  operator       float*();        // Mutator

  // ///////////////////////////////////////
  // Converting to different color spaces
  // ///////////////////////////////////////

  CMLColorType getColorType() const;

  SpectralColor toSpectral() const;

  // Currently, the 8, 16 and float buffer methods do nothing. There might be
  // a different use in the future. Don't use it.
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

  // also, the following inport methods do nothing.
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

  // The following methods work fine.
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

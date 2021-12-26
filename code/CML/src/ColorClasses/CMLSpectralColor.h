
// SpectralColor is a 1-dimensional function
// The range may be arbitrary



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
  CML_INLINE float length() const {return 0.f;}

  // ///////////////////////////////////////
  // various methods
  // ///////////////////////////////////////

  // This method currently always returns inf for spectral colors. There might
  // be a different use in the future. Don't use it.
  CML_INLINE size_t getNumChannels() const {return (size_t) -1;}

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
  void from8BitBuffer(const uint8* input);  
  void from16BitBuffer(const uint16* input);  
  void fromFloatBuffer(const float* input);  
  void to8BitBuffer(uint8* output) const;
  void to16BitBuffer(uint16* output) const;
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



// This is free and unencumbered software released into the public domain.

// Anyone is free to copy, modify, publish, use, compile, sell, or
// distribute this software, either in source code form or as a compiled
// binary, for any purpose, commercial or non-commercial, and by any
// means.

// In jurisdictions that recognize copyright laws, the author or authors
// of this software dedicate any and all copyright interest in the
// software to the public domain. We make this dedication for the benefit
// of the public at large and to the detriment of our heirs and
// successors. We intend this dedication to be an overt act of
// relinquishment in perpetuity of all present and future rights to this
// software under copyright law.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
// OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.

// For more information, please refer to <http://unlicense.org/>


// YupvpColor is a 3-dimensional vector
// Y-Range: (0, 1),   Y-Axis
// U-Range: (0, 1),   U-Component
// V-Range: (0, 0.5),   V-Component
// The bounds are defined as constants in CMLConstants.h

// Be aware that the Y component is defined to be based on 1, not 100.
// Note that V-Values close to or equal to 0.5 may lead to strong
// fluctuations

class CML_API YupvpColor : public Color{
  float color[3];
public:

  // ///////////////////////////////////////
  // Constructors and initialization methods
  // ///////////////////////////////////////

  YupvpColor();
  ~YupvpColor();

  YupvpColor(float Y, float U, float V);
  YupvpColor(const Color& anycolor);
  YupvpColor(const YupvpColor& yupvp);

  void init(float Y, float U, float V);
  YupvpColor& operator =(const Color& anycolor);
  YupvpColor& operator =(const YupvpColor& yupvp);

  // ///////////////////////////////////////
  // Mathematical operators in cartesian space
  // ///////////////////////////////////////

  YupvpColor operator +() const;
  YupvpColor operator -() const;

  YupvpColor  operator +(const Color& anycolor) const;
  YupvpColor  operator -(const Color& anycolor) const;
  YupvpColor  operator *(const float factor) const;
  YupvpColor  operator /(const float divisor) const;

  YupvpColor& operator +=(const Color& anycolor);
  YupvpColor& operator -=(const Color& anycolor);
  YupvpColor& operator *=(float factor);
  YupvpColor& operator /=(float divisor);

  float dot(const YupvpColor& yupvp) const;
  float length() const;

  CMLBool operator ==(const YupvpColor& yupvp) const;
  CMLBool operator !=(const YupvpColor& yupvp) const;

  // ///////////////////////////////////////
  // various methods
  // ///////////////////////////////////////

  operator const float*() const;  // Accessor
  operator       float*();        // Mutator

  YupvpColor getInverse();
  void invert();

  CMLBool insideY();
  CMLBool insideU();
  CMLBool insideV();
  CMLBool inside();
  void clamp();

  size_t getNumChannels() const;

  // ///////////////////////////////////////
  // Converting to different color spaces
  // ///////////////////////////////////////

  CMLColorType getColorType() const;

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

  void fromGrayBuffer (const float* src);
  void fromXYZBuffer  (const float* src);
  void fromYuvBuffer  (const float* src);
  void fromYupvpBuffer  (const float* src);
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

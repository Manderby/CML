
// RGBColor is a 3-dimensional vector
// R-Range: (0,1), 0 represents no red, 1 represents full red
// G-Range: (0,1), 0 represents no green, 1 represents full green
// B-Range: (0,1), 0 represents no blue, 1 represents full blue
// The bounds are defined as constants in CMLConstants.h

class CML_API RGBColor : public Color{
  float color[3];
public:

  // ///////////////////////////////////////
  // Constructors and initialization methods
  // ///////////////////////////////////////

  RGBColor();
  ~RGBColor();

  RGBColor(float R, float G, float B);
  RGBColor(const Color& anycolor);
  RGBColor(const RGBColor& rgb);
  
  void init(float R, float G, float B);
  RGBColor& operator =(const Color& anycolor);
  RGBColor& operator =(const RGBColor& rgb);

  // ///////////////////////////////////////
  // Mathematical operators in cartesian space
  // ///////////////////////////////////////

  RGBColor operator +() const;
  RGBColor operator -() const;

  RGBColor operator +(const Color& anycolor) const;
  RGBColor operator -(const Color& anycolor) const;
  RGBColor operator *(const float factor) const;
  RGBColor operator /(const float divisor) const;

  RGBColor& operator +=(const Color& anycolor);
  RGBColor& operator -=(const Color& anycolor);
  RGBColor& operator *=(float factor);
  RGBColor& operator /=(float divisor);

  float dot(const RGBColor& rgb) const;
  float length() const;

  CMLBool operator ==(const RGBColor& rgb) const;
  CMLBool operator !=(const RGBColor& rgb) const;

  // ///////////////////////////////////////
  // various methods
  // ///////////////////////////////////////

  operator const float*() const;  // Accessor
  operator       float*();        // Mutator

  RGBColor getInverse();
  void invert();

  CMLBool insideR();
  CMLBool insideG();
  CMLBool insideB();
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


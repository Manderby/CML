
// CML Color implementation.
//
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

#include "../CML.h"


#if CML_COMPILE_ON_MAC
  // Mac OS X uses some symbols which are equal to the classes provided with
  // this library. But as quickdraw is deprecated, this should not be a problem
  // to exclude it from compilation.
  #define __QUICKDRAW__
  #define __QD__
  #define __QUICKDRAWTYPES__
  #define __QUICKDRAWAPI__
  #define __HISHAPE__
  #define __ICONS__
  #define __AXUIELEMENT__
#endif



// Prototypes
class GrayColor;
class XYZColor;
class YuvColor;
class YupvpColor;
class YxyColor;
class LabColor;
class LchColor;
class LuvColor;
class RGBColor;
class YCbCrColor;
class HSVColor;
class HSLColor;
class CMYKColor;
class SpectralColor;

// The machine which is needed for the color classes:
extern CMLColorMachine* cmlcm;
void CMLsetMachineForColorClasses(CMLColorMachine* cm);


// Base class for all Colors
//
// The Color class and all its descendants serve as a simplified API for quick
// implementations.
//
// Please consider that the following applies for all Color descendants:
// - Values given as arguments are copied at all times.
// - These classes use virtual methods, therefore more space is required and
//   not all function calls can be inlined. Therefore any use in large arrays
//   is not recommended.
//
// If you have a time critical code, try to use the methods of the
// ColorMachine directly. This is what these classes will do in the end anyway.
// The Color classes are much more comfortable to use for quick coding though.

class Color{
public:

  Color();
  virtual ~Color();

  virtual Color& operator =(const Color& anycolor) = 0;

  // Converts the color classes into each other.
  GrayColor             toGray()      const;
  XYZColor              toXYZ()       const;
  YuvColor              toYuv()       const;
  YupvpColor            toYupvp()     const;
  YxyColor              toYxy()       const;
  LabColor              toLab()       const;
  LchColor              toLch()       const;
  LuvColor              toLuv()       const;
  RGBColor              toRGB()       const;
  YCbCrColor            toYCbCr()     const;
  HSVColor              toHSV()       const;
  HSLColor              toHSL()       const;
  CMYKColor             toCMYK()      const;
  virtual SpectralColor toSpectral()  const; // not fully functional.

  virtual CMLColorType getColorType() const = 0;

  // Converts the buffer from the given space to the color class.
  virtual void fromBuffer(const float* src, CMLColorType inputtype);
  virtual void fromGrayBuffer (const float* src) = 0;
  virtual void fromXYZBuffer  (const float* src) = 0;
  virtual void fromYuvBuffer  (const float* src) = 0;
  virtual void fromYupvpBuffer(const float* src) = 0;
  virtual void fromYxyBuffer  (const float* src) = 0;
  virtual void fromLabBuffer  (const float* src) = 0;
  virtual void fromLchBuffer  (const float* src) = 0;
  virtual void fromLuvBuffer  (const float* src) = 0;
  virtual void fromRGBBuffer  (const float* src) = 0;
  virtual void fromYCbCrBuffer(const float* src) = 0;
  virtual void fromHSVBuffer  (const float* src) = 0;
  virtual void fromHSLBuffer  (const float* src) = 0;
  virtual void fromCMYKBuffer (const float* src) = 0;

  // Converts the color to the desired space and puts the result in an array.
  virtual void toBuffer(float* dest, CMLColorType outputtype) const;
  virtual void toGrayBuffer (float* dest)   const = 0;
  virtual void toXYZBuffer  (float* dest)   const = 0;
  virtual void toYuvBuffer  (float* dest)   const = 0;
  virtual void toYupvpBuffer(float* dest)   const = 0;
  virtual void toYxyBuffer  (float* dest)   const = 0;
  virtual void toLabBuffer  (float* dest)   const = 0;
  virtual void toLchBuffer  (float* dest)   const = 0;
  virtual void toLuvBuffer  (float* dest)   const = 0;
  virtual void toRGBBuffer  (float* dest)   const = 0;
  virtual void toYCbCrBuffer(float* dest)   const = 0;
  virtual void toHSVBuffer  (float* dest)   const = 0;
  virtual void toHSLBuffer  (float* dest)   const = 0;
  virtual void toCMYKBuffer (float* dest)   const = 0;

  
  // Converting from or to input-output buffers.
  virtual void from8bitBuffer(const CMLByte* input)       = 0;  
  virtual void from16bitBuffer(const CMLWord* input)      = 0;  
  virtual void fromFloatBuffer(const float* input)        = 0;  
  virtual void to8bitBuffer(CMLByte* output) const        = 0;
  virtual void to16bitBuffer(CMLWord* output) const       = 0;
  virtual void toFloatBuffer(float* output) const         = 0;

  // Converting from or to normed buffers. More information about normed
  // buffers can be read in the ColorMachine.h file.
  virtual void fromNormedBuffer(const float* input)           = 0;  
  virtual void toNormedBuffer(float* output) const            = 0;
  virtual void fromNormedCartesianBuffer(const float* input)  = 0;  
  virtual void toNormedCartesianBuffer(float* output) const   = 0;

  // Cartesian methods. Note that non-cartesian spaces like Lch or HSV are
  // handeled internally using a cartesian space, so you can use these methods
  // without any problem even for those non-cartesian spaces.
  virtual Color& operator +=(const Color& anycolor) = 0;
  virtual Color& operator -=(const Color& anycolor) = 0;
  virtual Color& operator *=(float factor) = 0;
  virtual Color& operator /=(float divisor) = 0;

  virtual float length() const = 0;
  virtual void clamp() = 0;
  virtual CMLuint32 getNumChannels() const = 0;

  virtual operator const float*() const = 0;  // Accessor
  virtual operator       float*() = 0;        // Mutator
};


#include "CMLGrayColor.h"
#include "CMLXYZColor.h"
#include "CMLYxyColor.h"
#include "CMLYuvColor.h"
#include "CMLYupvpColor.h"
#include "CMLLabColor.h"
#include "CMLLchColor.h"
#include "CMLLuvColor.h"
#include "CMLRGBColor.h"
#include "CMLYCbCrColor.h"
#include "CMLHSVColor.h"
#include "CMLHSLColor.h"
#include "CMLCMYKColor.h"
#include "CMLSpectralColor.h"


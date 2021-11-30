
#include <stdio.h>
#include <ColorClasses/CMLColor.h>


int main(){

  // Welcome to the C++ example of the Color Machine Library (CML)
  //
  // In this file, some examples are shown on how to use CML with C++ classes.
  //
  // Feel free to experiment. For further information, please refer to the many
  // comments in the Header-Files of CML.

  printf("Working with CML C++ classes\n");

  // CML provides a folder with header- and implementation-files which you can
  // include and compile with your project. These classes provide easy access
  // to the most commonly used color conversions.
  
  // The files are located at YourIncludeDirectory/CML/ColorClasses and
  // you can load all classes by including the CMLColor.h file as seen above.
  
  // First thing you need to know: All color classes require one globally shared
  // color machine which they will access by a pointer. You can create a machine
  // and use the cmlSetMachineForColorClasses method to set this global pointer:
  
  cmlSetMachineForColorClasses(CMLcreateColorMachine());

  // Don't forget to release this machine when you quit your application. See
  // below.





  printf("\nConstructing, getting and setting objects\n");
  
  // ///////////////////////////////////////////
  // Constructing, setting, getting
  // ///////////////////////////////////////////

  // Now, we can simply create a color:
  RGBColor orange(1.f, .3f, 0.f);
  
  // You can set and get all channel components by using the bracketing []
  // operator:
  
  orange[1] = .5f;
  printf("RGB Color: %f, %f, %f\n", orange[0], orange[1], orange[2]);
  
  // Note that there also exist default constructors and init methods. The
  // default constructors do nothing at all. The init methods do the same
  // thing as the constructors.
  
  // To convert one color into another, simply use the assing = operator:

  XYZColor xyz;
  xyz = orange;
  printf("XYZ Color: %f, %f, %f\n", xyz[0], xyz[1], xyz[2]);

  // Or if you prefer to be expressive, use the toXXX() method:

  xyz = orange.toXYZ();
  printf("XYZ Color: %f, %f, %f\n", xyz[0], xyz[1], xyz[2]);

  // If you are wondering if the conversion goes in both ways:
  
  orange = xyz;
  printf("RGB Color: %f, %f, %f\n", orange[0], orange[1], orange[2]);
  
  
  
  


  printf("\nArithmetic methods\n");
  
  // ///////////////////////////////////////////
  // Arithmetic methods
  // ///////////////////////////////////////////

  // You can use the default mathematical operators with color classes:
  
  RGBColor lightblue(.2f, 1.f, 1.f);
  RGBColor combinedcolor = orange + lightblue;
  printf("Combined Color: %f, %f, %f\n", combinedcolor[0], combinedcolor[1], combinedcolor[2]);

  // This is not particularly meaningful but if for example, we divide this
  // combined color by 2, we get the average of orange and lightblue:
  
  combinedcolor /= 2.f;
  printf("Averaged Color: %f, %f, %f\n", combinedcolor[0], combinedcolor[1], combinedcolor[2]);
  
  // Note that this also works with color spaces which normally would not be
  // easily averageable, like the Lch colorspace which by its nature, is
  // described in a polar coordinate system. Such colorspaces will be converted
  // to a cartesian space and the result will be computed with these values.
  
  LchColor lch1(50.f, .85f, 75.f);
  LchColor lch2(50.f, .9f, 70.f);
  LchColor lchaverage = (lch1 + lch2) / 2.f;
  printf("Averaged Lch: %f, %f, %f\n", lchaverage[0], lchaverage[1], lchaverage[2]);

  // Or for example, if you would like to know the distance between two colors:
  
  float dist = (lch1 - lch2).length();
  printf("Lch distance: %f\n", dist);





  
  printf("\nOther methods\n");
  
  // ///////////////////////////////////////////
  // Other methods
  // ///////////////////////////////////////////

  // Many Color classes have additional methods which you can use. For example
  // inverting colors:
  
  RGBColor inverseorange = orange.getInverse();
  printf("Inverse Orange: %f, %f, %f\n", inverseorange[0], inverseorange[1], inverseorange[2]);

  // Or if you need your colors to be clamped to the minimal and maximal bounds:
  
  HSVColor hsv(35124.f, 1.5f, -0.1f);
  hsv.clamp();
  printf("Clamped HSV: %f, %f, %f\n", hsv[0], hsv[1], hsv[2]);


  
  
  
  
  printf("\nInput / Output methods\n");
  
  // ///////////////////////////////////////////
  // Input / Output methods
  // ///////////////////////////////////////////

  // Often times, your application provides color data in a different format
  // than it is used in CML. Use the from- and to-conversion methods to feed
  // the CML classes with your data.
  
  unsigned char rgbdata[3] = {255, 128, 51};
  RGBColor inputrgb;
  inputrgb.from8BitBuffer(rgbdata);
  printf("Input RGB: %f, %f, %f\n", inputrgb[0], inputrgb[1], inputrgb[2]);



  
  
  printf("\nCleaning up and quitting...");

  /////////////////////////////////////////////////////////////////////////
  // Cleaning up
  /////////////////////////////////////////////////////////////////////////

  // The global ColorMachine remains in memory as long as you like. At the end
  // of your application, you can release it:
  
  cmlReleaseColorMachine(cmlcm);

  printf(" Bye\n");

  //printf("\nPress enter to quit.\n");
  //fgetc(stdin);

  return 0;
}



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

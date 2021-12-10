
#include <stdio.h>
#include "Timer.h"
#include <CML.h>


int main(){
  // Welcome to the example of the Color Machine Library (CML)
  //
  // In this file, some examples are shown on how to use CML. Feel free to
  // experiment. For further information, please refer to the many comments in
  // the Header-Files of CML.
  
  printf("CML Version: %d\n", cmlGetVersion());
  
  // Try switching between Debug and Release configurations to get the best
  // out of the example.
  
  
  
  
  printf("\nData storage:\n");

  // ///////////////////////////////////////////////////////////////////////
  // Data Storage
  // ///////////////////////////////////////////////////////////////////////
  
  // All color data in CML are stored as floats (32 Bit). Colors which have
  // multiple channels store the values in a simple float array. You can use
  // the CMLVec typedefs found in CMLMath.h:
  
  CMLVec3 orange = {1.f, .5f, 0.f};
  printf("Orange in RGB: %f, %f, %f\n", orange[0], orange[1], orange[2]);
  
  // Or you can simply use float arrays:
    
  float xyz[3];

  // Some data will be stored in special C-structs like a CMLFunction. These
  // will be explained below in the section about spectral data.
  





  
  // ///////////////////////////////////////////////////////////////////////
  // Using Color Machines
  // ///////////////////////////////////////////////////////////////////////

  printf("\nWorking with Color Machines:\n");

  // ColorMachines provide many special methods used in colorimetry and color
  // science. They are based on a state machine (hence the name). This means:
  // You as a programmer can control the current state of a ColorMachine. As
  // soon as you configured the machine to your desires, you simply feed it
  // with all the data you want and the ColorMachine will do the appropriate
  // conversions.

  // The following function creates a new ColorMachine. You can deallocate
  // the machine later with cmlReleaseColorMachine().

  CMLColorMachine* cm = cmlCreateColorMachine();

  // Note that a new machine sets sRGB as the default RGB colorspace.
  // Now for example, converting RGB to XYZ is as simple as that:
  
  cmlRGBToXYZ(cm, xyz, orange, 1);
  printf("Orange in XYZ: %f, %f, %f\n", xyz[0], xyz[1], xyz[2]);

  // Note that in CML, the destination parameter always comes before the source
  // parameter.
  
  // As another example, we convert the RGB orange into a HSV orange:

  CMLVec3 hsv;
  cmlRGBToHSV(cm, hsv, orange, 1);
  printf("Orange in HSV: %f, %f, %f\n", hsv[0], hsv[1], hsv[2]);
      
  // Even conversions over multiple colorspaces are no more difficult than
  // that. For example we want to convert the HSV orange to Lch. For this, the
  // value needs to be converted from HSV to RGB, then to XYZ, then to Lab and
  // finally to Lch.

  CMLVec3 lch;
  cmlHSVToLch(cm, lch, hsv, 1);
  printf("Orange in Lch: %f, %f, %f\n", lch[0], lch[1], lch[2]);

  // As discussed above, the default RGB colorspace of a newly created
  // ColorMachine is sRGB. But you can change that easily for example to
  // Adobe 98:
  
  cmlSetRGBColorSpaceType(cm, CML_RGB_ADOBE_98);
  printf("Current RGB colorspace: %s\n",
    cmlGetRGBColorSpaceTypeString(cmlGetRGBColorSpaceType(cm)));

  // Now, as we have changed the RGB colorspace, when converting back the
  // xyz value of our orange color to RGB, we get different RGB values:

  cmlXYZToRGB(cm, orange, xyz, 1);
  printf("Adobe 98 RGB:  %f, %f, %f\n", orange[0], orange[1], orange[2]);

  // You can also set many more states of the machine. For example, we will
  // change the Observer to 10 Degree and the Illumination to a D illuminant
  // with 5555 degree Kelvin

  cmlSetObserverType(cm, CML_OBSERVER_10DEG_CIE_1964);
  cmlSetIlluminationType(cm, CML_ILLUMINATION_D_ILLUMINANT);
  cmlSetIlluminationTemperature(cm, 5555.f);

  // These settings will all be handeled one by one and therefore the color
  // machine will recompute itself after each setting. To avoid recomputation
  // when multiple settings need to be done, see methods cmlLockRecomputation
  // and cmlReleaseRecomputation for more speed.

  // After setting the state of the machine, several states can be read out.
  // For example:

  CMLVec3 wpYxy;
  cmlGetWhitePointYxy(cm, wpYxy);
  printf("Current whitepoint: %f, %f, %f\n", wpYxy[0], wpYxy[1], wpYxy[2]);
  
  // Note that cmlGetWhitePointYxy will always return a radiometric Yxy color.
  // This means that the Y component may NOT be 1.
  
  // Also note that by the time, due to our changes of the state machine, a
  // custom illuminant has been set but the RGB primaries remain the same as
  // before (which was Adobe 98). As this is a non-standard situation, the
  // resulting RGB colorspace is "Custom":
  
  printf("Current RGB colorspace: %s\n",
    cmlGetRGBColorSpaceTypeString(cmlGetRGBColorSpaceType(cm)));

  // As we still have the orange stored in xyz, let's see what the RGB value
  // of that orange is in this strange RGB colorspace...

  cmlXYZToRGB(cm, orange, xyz, 1);
  printf("Orange in RGB: %f, %f, %f\n", orange[0], orange[1], orange[2]);



  

  printf("\nConverting lots of data:\n");

  /////////////////////////////////////////////////////////////////////////
  // Converting many, many data
  /////////////////////////////////////////////////////////////////////////

  // Most conversion methods of the ColorMachine have a count parameter (the
  // last one) which denotes the number of colors to convert. By using this
  // last parameter, whole arrays of colors can be converted with one single
  // instruction.
  //
  // To illustrate this, we create a fresh ColorMachine and do a speed test.
  
  CMLColorMachine* cm2 = cmlCreateColorMachine();
  
  // Let's do this with some large arrays:
  size_t millionColors = 10;
  // Adjust this number, if the following computation is running too fast or
  // too slow on your computer

  // First, we create two arrays: One with the input values and one which will
  // hold the output values. We are initializing the input array with random
  // RGB values:
  printf("Preparing %i million random RGB values to convert to Lab... ",
    (int)millionColors);
  fflush(stdout);
  CMLTimer timer;

  float *randValues = (float*)malloc(sizeof(float)*millionColors*1000000*3);
  float *outValues  = (float*)malloc(sizeof(float)*millionColors*1000000*3);
  if(randValues && outValues){
    for(size_t i = 0; i < millionColors * 1000000; i++){
      randValues[i * 3 + 0] = rand()/(float)RAND_MAX;
      randValues[i * 3 + 1] = rand()/(float)RAND_MAX;
      randValues[i * 3 + 2] = rand()/(float)RAND_MAX;
      outValues[i * 3 + 0] = 0.f;
      outValues[i * 3 + 1] = 0.f;
      outValues[i * 3 + 2] = 0.f;
    }
    printf("Done\n");
    fflush(stdout);

    // Now, let's convert the values and measure the time.
    printf("Converting array with float precision... ");
    fflush(stdout);

    timer = cmlStartTimer();
  
    cmlRGBToLab(cm2, outValues, randValues, millionColors * 1000000);
  
    printf("Done after %1.02f seconds\n", cmlTimerGetSeconds(timer));
    fflush(stdout);
  }else{
    printf("Insufficient memory\n");
    fflush(stdout);
  }

  // Many conversions get even faster, if a lookup table (LUT) is used.
  // Not with the Debug-Version though!
  // You can choose anything from 1 to 16 Bit. Any other number will disable
  // the LUT. It is recommended to use the number 32 to disable the LUT as an
  // indication that all computation will be done with floats.
  
  cmlSetRGBLUTSize(cm2, 16);
  cmlSetLabLUTSize(cm2, 16);

  printf("Converting array with 16 Bit LUT... ");
  fflush(stdout);

  timer = cmlStartTimer();
  
  cmlRGBToLab(cm2, outValues, randValues, millionColors * 1000000);
  
  printf("Done after %1.02f seconds\n", cmlTimerGetSeconds(timer));
  fflush(stdout);


  free(outValues);
  free(randValues);








  printf("\nWorking with spectral data:\n");

  /////////////////////////////////////////////////////////////////////////
  // Using spectral data
  /////////////////////////////////////////////////////////////////////////

  // First note that there are two kinds of spectral colors:
  // Illuminations and Bodycolors.
  //
  // An illumination spectrum defines the spectrum of an illumination and
  // stands for its own. Converting an illuminant spectrum to XYZ for example
  // may have any desirable unit which is given by the spectrum. For example,
  // measuring the illumination spectrum of the sunlight and feeding a
  // spectral color with this measurement will result in very high XYZ values
  // like 100000 lux for the Y value. Measuring a darkened room may for
  // example result in Y-Values of 0.01
  //
  // A bodycolor spectrum depicts a sample which is illuminated by a light
  // source. The light of that sample which, in the end, is seen by the
  // observer (or measurement device) usually is characterized by the amount
  // (as a multiplication factor) of light re-emitted (or transmitted) to the
  // observer. Therefore, a remission spectrum usally is in the range (0, 1).
  // Values greater than 1 may occur for example for fluorescent samples.

  // If you have spectral data, use a CMLFunction. We create a fresh machine
  // to illustrate this with an example:
  
  CMLColorMachine* cm3 = cmlCreateColorMachine();
 
  // Let's assume you have an array of float values, filled with the spectral
  // sampling points of a light source. Additionally, you know the wavelengths
  // of the minimal and maximal sampling point.
  const CMLuint32 dataCount = 10; 
  float luminanceData[10] = { 22.f,  74.f, 280.f, 506.f, 638.f,
                             477.f, 361.f, 164.f,  63.f,  13.f};
  float minLambda = 400.f;
  float maxLambda = 800.f;

  // With these informations, you can create a CMLFunction representing
  // this spectrum.
  
  // CMLFunctions are self-organizing. If a CMLFunction is used in more than
  // one place, it will remain in memory as long as there is at least one
  // place using that CMLFunction. If the second argument (ownbuffer) is set
  // to CML_TRUE, the given buffer will be deallocated with free() when the
  // CMLFunction is no longer used. Therefore, you should use malloc to
  // allocate memory for your data. As we use a local array in this example,
  // we need to set ownbuffer to CML_FALSE.
  
  // The function further more requires the number of values in the buffer,
  // the minimum and maximum wavelength and additionally, three parameters
  // which define how interpolation and extrapolation shall be performed. Note
  // that for spectral data, the minimum and maximum are expected to be in the
  // unit [nanometer].

  CMLArrayFunctionSettings arrayFuncSettings = {
    dataCount,
    minLambda,
    maxLambda,
    CML_INTERPOLATION_LINEAR,
    CML_EXTRAPOLATION_LINEAR_ZERO,
    CML_EXTRAPOLATION_LINEAR_ZERO};

  CMLArrayFunctionInput luminanceFuncInput = {
    luminanceData,
    /*ownbuffer:*/ CML_FALSE,
    arrayFuncSettings};

  CMLFunction* luminanceFunction = cmlCreateArrayFunction(luminanceFuncInput);
  
  // This function instance can now be used. For example, you can retrieve the
  // value at 500 nm:

  printf("Spectral data at 500 nm: %f\n", cmlEval(luminanceFunction, 500.f));
    
  // You can do the same thing by filtering the luminanceFunction with a Dirac
  // filter. In mathematical terms, this is an integral over the product of
  // two functions.
  CMLFunction* dirac = cmlCreateDiracFilter(500.f);
  printf("Dirac filter at 500 nm: %f\n",
      cmlFilterFunction(luminanceFunction, dirac));
  cmlReleaseFunction(dirac);
  
  // You can use a CMLFunction for example, to set this spectrum as the
  // illumination spectrum of the machine:

  cmlSetIlluminationSpectrum(cm3, luminanceFunction);
  cmlGetWhitePointYxy(cm3, wpYxy);
  printf("New whitepoint: %f, %f, %f\n", wpYxy[0], wpYxy[1], wpYxy[2]);

  // Remember that the Y component of the whitepoint returned by the
  // cmlGetWhitePointYxy function will always be a radiometric value.

  // Now we create a remission color:
  
  float remissionData[10] = {  .2f, .3f, .6f, .7f, 1.f,
                              1.2f, .9f, .6f, .2f, .0f};

  CMLArrayFunctionInput remissionFuncInput = {
    remissionData,
    /*ownbuffer:*/ CML_FALSE,
    arrayFuncSettings};

  CMLFunction* remissionFunction = cmlCreateArrayFunction(remissionFuncInput);

  // We can convert this function to an XYZ value. As this is a remission
  // conversion, the function will multiply with the current illumination
  // (which we just set to our illumination function).
  
  cmlSpectrumRemissionToXYZ(cm3, xyz, remissionFunction, 1);
  printf("Colorimetric Remission XYZ: %f, %f, %f\n",  xyz[0], xyz[1], xyz[2]);

  // Note that by default, a ColorMachine converts to colorimetric values.
  // If you are interested in radiometric values, simply multiply the values
  // with the Y component of the whitepoint (which, as we just discussed,
  // always contains a radiometric Y value):

  cmlMul3(xyz, wpYxy[0]);
  printf("Radiometric Remission XYZ: %f, %f, %f\n",
    xyz[0], xyz[1], xyz[2]);

  // Or change the computation of the ColorMachine to radiometric and recompute
  // the color again. Note that the resulting values might be slightly different
  // due to numerical errors.
  
//  cmlSetRadiometricComputation(cm3, CML_TRUE);
  cmlSpectrumRemissionToXYZ(cm3, xyz, remissionFunction, 1);
  printf("Radiometric Remission XYZ: %f, %f, %f\n", xyz[0], xyz[1], xyz[2]);

  // In case you wonder what happends if you have a bodycolor reflecting the
  // illumination spectrum perfectly:

  CMLVec3 yxy;
  CMLFunction* constFunction = cmlCreateConstFilter(1.f);
  cmlSpectrumRemissionToYxy(cm3, yxy, constFunction, 1);
  printf("Lambertian surface: %f, %f, %f\n", yxy[0], yxy[1], yxy[2]);
  
  // It should result in the same as the whitepoint printed above.

  // Don't forget to release the functions if no longer needed.

  cmlReleaseFunction(constFunction);
  cmlReleaseFunction(remissionFunction);
  cmlReleaseFunction(luminanceFunction);
  
  // Beware! When changing a ColorMachine to radiometric computation, all
  // Y-related colors have a different meaning but they will not be converted
  // automatically. You should only use radiometric computation if you really
  // know what you are doing!









  printf("\nWorking without the use of ColorMachines: The BaseAPI:\n");

  // ///////////////////////////////////////////////////////////////////////
  // Using the Base API
  // ///////////////////////////////////////////////////////////////////////

  // In BaseAPI.h, you find the most basic color functions used in CML. They
  // are here for programmers who like to do everything manually. But note
  // that the code can get very complicated.
  //
  // A way simpler way of using CML is the use of Color Machines. See above.
  //
  
  // If you want to convert one color into another, use the CMLconvertXXX
  // functions of the BaseAPI:
  
  cmlConvertRGBToHSV(hsv, orange);
  printf("HSV color: %f, %f, %f\n", hsv[0], hsv[1], hsv[2]);

  // Some conversion need more parameters though. And this is where color
  // computation becomes more and more complex. For example, if we want to
  // convert the orange from RGB to XYZ, we need the response curves of the
  // three channels as well as the transformation matrix. To compute the,
  // matrix, we need the three primaries as well as a whitepoint. In the
  // following example, we use sRGB as the desired RGB colorspace. This means
  // that we need the whitepoint of D65, which we need to compute first, which
  // in turn, requires the choice of the appropriate spectal distribution
  // functions.

  // Here is the complete computation:

  // Get all needed information for sRGB:
  CMLVec3 primariesYxy[3];
  CMLIlluminationType illuminationtype =
    cmlGetRGBColorSpaceIlluminationType(CML_RGB_SRGB);
  cmlGetRGBColorSpacePrimaries(CML_RGB_SRGB,
    primariesYxy[0], primariesYxy[1], primariesYxy[2]);

  // Compute the colorimetric whitepoint:
  CMLIllumination* illumination = cmlCreateIlluminationWithType(
    CML_NULL, illuminationtype, 0);
  CMLObserver* observer = cmlCreateObserver(
    CML_NULL, CML_OBSERVER_2DEG_CIE_1931, illumination, 100.f);
  const float* sRGBwp = cmlGetReferenceWhitePointYxy(observer);
  
  // Compute the matrix and prepare the response curve:
  CMLMat33 RGBToXYZMatrix;
  cmlComputeRGBToXYZMatrix(RGBToXYZMatrix, primariesYxy[0], primariesYxy[1], primariesYxy[2], sRGBwp);
  CMLFunction* sRGBResponse = cmlCreatesRGBToXYZResponse();
  
  // Convert the color:
  cmlConvertRGBToXYZ(xyz, orange, RGBToXYZMatrix, sRGBResponse, sRGBResponse, sRGBResponse);
  printf("XYZ color: %f, %f, %f\n", xyz[0], xyz[1], xyz[2]);

  // Release all functions.
  cmlReleaseFunction(sRGBResponse);
  cmlDestroyIllumination(illumination);
  cmlDestroyObserver(observer);
  
  // As you can see, such conversions get very complicated very quickly. You
  // CAN do everything manually with the BaseAPI as just shown ...
  // ... but then again, take a look at how RGB to XYZ conversion is done
  // using a Colormachine:
  
  CMLColorMachine* cm4 = cmlCreateColorMachine();
  cmlRGBToXYZ(cm4, xyz, orange, 1);
  printf("XYZ color: %f, %f, %f\n", xyz[0], xyz[1], xyz[2]);
  
  


    
  printf("\nCleaning up and quitting...");

  // ///////////////////////////////////////////////////////////////////////
  // Cleaning up
  // ///////////////////////////////////////////////////////////////////////

  // Remember that ColorMachine objects remain in memory as long as you like.
  // You have to release each machine by yourself.

  cmlReleaseColorMachine(cm);
  cmlReleaseColorMachine(cm2);
  cmlReleaseColorMachine(cm3);
  cmlReleaseColorMachine(cm4);
  
  printf(" Bye\n");

  printf("\nPress enter to quit.\n");
  fgetc(stdin);

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

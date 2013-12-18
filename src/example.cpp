
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.


#include <stdio.h>
#include "Timer.h"
#include <CML/CML.h>


int main(){

//  double bblinscale = 1.f;
////  double bblinscale = 12.92f;
//  double bbinvgamma = 0.416666666666667f;
////  double bboffset = .5f;
//  double bboffset = .055f;
//  double bbtest1 = 0.f;
//  double bbtest2 = 1.f;
//  int goleft = 1;
//  int goright = 1;
//  double step = 1.f;
//  double bestdiv = 1.;
//  
//  int offsetfixed = 1;
//  
//  double curlinscale = bblinscale;
//  double curoffset = bboffset;
//  double x;
//
//  while(1){
//    
//    if(goleft){
//      if(offsetfixed){
//        curlinscale = bblinscale - step;
//      }else{
//        curoffset = bboffset - step;
//      }
//      goleft = 2;
//    }else{
//      if(goright){
//        if(offsetfixed){
//          curlinscale = bblinscale + step;
//        }else{
//          curoffset = bboffset + step;
//        }
//        goright = 2;
//      }else{
//        step /= 2.f;
//        goleft = 1;
//        goright = 1;
//        continue;
//      }
//    }
//
//    x = exp((log(curlinscale / (bbinvgamma * (1. + curoffset)))) / (-1. + bbinvgamma));
//
//    if(isnan(x)){
//      if(goleft == 2){goleft = 0;}
//      if(goright == 2){goright = 0;}
//      continue;
//    }
//    
//    bbtest1 = (1.f+curoffset) * pow(x, bbinvgamma) - curoffset;
//    bbtest2 = x * curlinscale;
//
////    printf("%1.18f %1.18f %1.18f\n", bboffset, bblinscale, x);
////    printf("%1.18f %1.18f %1.18f\n\n", step, bbtest1, bbtest2);
//    
//    if(bbtest1 == bbtest2){break;}
//    
//    double curdiv = fabs(bbtest1 - bbtest2);
////    if(curdiv < 1e-18){break;}
//    if(curdiv < bestdiv){
//      bestdiv = curdiv;
//      if(offsetfixed){
//        bblinscale = curlinscale;
//      }else{
//        bboffset = curoffset;
//      }
//      if(goleft == 2){goright = 0;}
//      if(goright == 2){goleft = 0;}
//    }else{
//      if(goleft == 2){goleft = 0;}
//      if(goright == 2){goright = 0;}
//    }
//    
//  }
//
//  printf("%1.18f %1.18f %1.18f %1.18f\n\n", bboffset, x*bblinscale, bblinscale, x);
//
//  double bbgamma = 1. / bbinvgamma;
//  printf("%1.18f %1.18f %1.18f\n\n", bboffset, bboffset / (bbgamma - 1),
//    (pow(1. + bboffset, bbgamma) * pow(bbgamma - 1., bbgamma - 1.)) / ((pow(bboffset, bbgamma-1.)) * (pow(bbgamma, bbgamma))));
//    
//  printf("%1.18f %1.18f %1.18f\n\n", bboffset, bboffset / (bbgamma - 1),
//    bboffset/(exp(log((bbgamma * bboffset)/(bbgamma + bbgamma * bboffset - 1. - bboffset)) * bbgamma) * (bbgamma - 1.)));
//
//  float txyz[3];
//  float tyxy[3];
//  CMLconvertYxytoXYZ(txyz, tyxy, NULL);




  // Welcome to the example of the Color Machine Library (CML)
  //
  // In this file, some examples are shown on how to use CML. Feel free to
  // experiment. For further information, please refer to the many comments in
  // the Header-Files of CML.

  // The version is denoted by 4 unsigned 8-bit integers. The last one is
  // either 0 for Release or 1 for Debug.
  
  CMLByte version[4];
  cmlGetVersion(version);
  printf("CML Version: %u.%u.%u (%s)\n", version[0], version[1], version[2], version[3]?"Debug":"Release");
  
  // The Debug version is only available to you upon special request to the
  // author. In the Debug version, a lot of security tests are performed and
  // errors or warnings are printed to the standard output. Due to excessive
  // tests, it can be very verbose and WAY slower than the release version.
  // Do NOT use the Debug-Version for releases.
  
  
  
  
  
  
  printf("\nData storage:\n");

  // ///////////////////////////////////////////////////////////////////////
  // Data Storage
  // ///////////////////////////////////////////////////////////////////////
  
  // All color data in CML are stored as floats (32 Bit). Colors which have
  // multiple channels store the values in a simple float array. You can use
  // the CMLVec typedefs found in CMLDefinitions.h:
  
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

  // ColorMachines provides many special methods used in colorimetry and color
  // science. They are based on a state machine (hence the name). This means:
  // You as a programmer can control the current state of a ColorMachine. As
  // soon as you configured the machine to your desires, you simply feed it
  // with all the data you want and the ColorMachine will do the appropriate
  // conversions.

  // The following function creates a new ColorMachine. You can deallocate
  // the machine later with CMLreleaseColorMachine().

  CMLColorMachine* cm = cmlCreateColorMachine();

  // Note that a new machine sets sRGB as the default RGB colorspace.
  // Now for example, converting RGB to XYZ is as simple as that:
  
  CMLRGBtoXYZ(cm, xyz, orange, 1);
  printf("Orange in XYZ: %f, %f, %f\n", xyz[0], xyz[1], xyz[2]);

  // Note that in CML, the destination parameter always comes before the source
  // parameter.
  
  // As another example, we convert the RGB orange into a HSV orange:

  CMLVec3 hsv;
  CMLRGBtoHSV(cm, hsv, orange, 1);
  printf("Orange in HSV: %f, %f, %f\n", hsv[0], hsv[1], hsv[2]);
      
  // Even conversions over multiple colorspaces are no more difficult than
  // that. For example we want to convert the HSV orange to Lch. For this, the
  // value needs to be converted from HSV to RGB, then to XYZ, then to Lab and
  // finally to Lch.

  CMLVec3 lch;
  CMLHSVtoLch(cm, lch, hsv, 1);
  printf("Orange in Lch: %f, %f, %f\n", lch[0], lch[1], lch[2]);

  // Now, the default RGB colorspace of a newly created ColorMachine is sRGB.
  // But you can change that easily for example to Adobe 98:
  
  cmlSetRGBSpace(cm, CML_RGB_ADOBE_98);
  printf("Current RGB colorspace: %s\n", cmlGetRGBColorspaceString(cmlGetRGBSpace(cm)));

  // Now, when converting back the xyz value of our orange color to RGB, we
  // get different RGB values:

  CMLXYZtoRGB(cm, orange, xyz, 1);
  printf("Adobe 98 RGB:  %f, %f, %f\n", orange[0], orange[1], orange[2]);

  // You can also set many more states of the machine. For example, we will
  // change the Observer to 10 Degree and the Illumination to a D illuminant
  // with 5555 degree Kelvin

  cmlSetObserverType(cm, CML_OBSERVER_10DEG_CIE_1964);
  cmlSetIlluminationType(cm, CML_ILLUMINATION_D_ILLUMINANT);
  cmlSetIlluminationTemperature(cm, 5555.f);

  // These settings will all be handeled one by one and therefore the color
  // machine will recompute itself after each setting. To avoid recomputation
  // when multiple settings need to be done, see methods CMLlockRecomputation
  // and CMLreleaseRecomputation for more speed.

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
  
  printf("Current RGB colorspace: %s\n", cmlGetRGBColorspaceString(cmlGetRGBSpace(cm)));

  // As we still have the orange stored in xyz, let's see what the RGB value
  // of that orange is in this strange RGB colorspace...

  CMLXYZtoRGB(cm, orange, xyz, 1);
  printf("Deformed orange is now in RGB: %f, %f, %f\n", orange[0], orange[1], orange[2]);



  





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
  CMLSize millioncolors = 10;
  // Adjust this number, if the following computation is running too fast or
  // too slow on your computer

  // First, we create two arrays: One with the input values and one which will
  // hold the output values. We are initializing the input array with random
  // RGB values:
  printf("Preparing %i million random RGB values to convert to Lab... ", millioncolors);
  fflush(stdout);
  float *randvalues = (float*)malloc(sizeof(float)*millioncolors*1000000*3);
  float *outvalues  = (float*)malloc(sizeof(float)*millioncolors*1000000*3);
  for(CMLSize i=0; i<millioncolors*1000000; i++){
    randvalues[i*3 + 0] = rand()/(float)RAND_MAX;
    randvalues[i*3 + 1] = rand()/(float)RAND_MAX;
    randvalues[i*3 + 2] = rand()/(float)RAND_MAX;
    outvalues[i*3 + 0] = 0.f;
    outvalues[i*3 + 1] = 0.f;
    outvalues[i*3 + 2] = 0.f;
  }
  printf("Done\n");
  fflush(stdout);

  CMLTimer timer;

  // Now, let's convert the values.

  printf("Converting array with float precision... ");
  fflush(stdout);
  timer = CMLStartTimer();
  
  CMLRGBtoLab(cm2, outvalues, randvalues, millioncolors*1000000);
  
  printf("Done after %1.02f seconds\n", CMLTimerGetSeconds(timer));
  fflush(stdout);

  // Many conversions get even faster, if a lookup table (LUT) is used.
  // Not with the Debug-Version though!
  // You can choose anything from 1 to 16 Bit. Any other number will disable
  // the LUT. It is recommended to use the number 32 to disable the LUT as an
  // indication that all computation will be done with floats.
  
  cmlSetRGBLUTSize(cm2, 16);
  cmlSetLabLUTSize(cm2, 16);

  printf("Converting array with 16 Bit LUT... ");
  fflush(stdout);
  timer = CMLStartTimer();
  
  CMLRGBtoLab(cm2, outvalues, randvalues, millioncolors*1000000);
  
  printf("Done after %1.02f seconds\n", CMLTimerGetSeconds(timer));
  fflush(stdout);


  free(outvalues);
  free(randvalues);








  printf("\nWorking with spectral data:\n");

  /////////////////////////////////////////////////////////////////////////
  // Using spectral data
  /////////////////////////////////////////////////////////////////////////

  // First note that there are two kinds of spectral colors:
  // Illuminations and Bodycolors.
  //
  // An illumination spectrum defines the spectrum of an illumination and stands
  // for its own. Converting an illuminant spectrum to XYZ for example may have
  // any desirable unit which is given by the spectrum. For example, measuring
  // the illumination spectrum of the sunlight and feeding a spectral color
  // with this measurement will result in very high XYZ values like 100000 lux
  // for the Y value. Measuring a darkened room may for example result in
  // Y-Values of 0.01
  //
  // A bodycolor spectrum depicts a sample which is illuminated by a light
  // source. The light of that sample which, in the end, is seen by the observer
  // (or measurement device) usually is characterized by the amount (as a
  // multiplication factor) of light re-emitted (or transmitted) to the
  // observer. Therefore, a remission spectrum usally is in the range (0, 1).
  // Values greater than 1 may occur for example for fluorescent samples.

  // If you have spectral data, use a CMLFunction. We create a fresh machine
  // to illustrate this with an example:
  
  CMLColorMachine* cm3 = cmlCreateColorMachine();
 
  // Let's assume you have an array of float values, filled with the spectral
  // sampling points of a light source. Additionally, you know the wavelengths
  // of the minimal and maximal sampling point.
  const CMLuint32 datacount = 10; 
  float luminancedata[10] = { 22.f,  74.f, 280.f, 506.f, 638.f,
                             477.f, 361.f, 164.f,  63.f,  13.f};
  float minlambda = 400.f;
  float maxlambda = 800.f;

  // With these informations, you can simply create a CMLFunction representing
  // this spectrum:

  CMLFunction* luminancefunction = cmlCreateArrayFunction(
                                      luminancedata,
                                      CMLFALSE,
                                      datacount,
                                      minlambda,
                                      maxlambda,
                                      CML_INTERPOLATION_LINEAR,
                                      CML_EXTRAPOLATION_LINEAR_ZERO,
                                      CML_EXTRAPOLATION_LINEAR_ZERO);

  // CMLFunctions are self-organizing. If a CMLFunction is used in more than
  // one place, it will remain in memory as long as there is at least one place
  // using that CMLFunction. If the second argument (ownbuffer) is set to
  // CMLTRUE, the given buffer will be deallocated with free() when the
  // CMLFunction is no longer used. Therefore, you should use malloc to allocate
  // memory for your data. As we use a local array in this example, we need to
  // set ownbuffer to CMLFALSE.
  
  // The function call further more requires the number of values in the buffer,
  // the minimum and maximum wavelength and additionally, three parameters which
  // define how interpolation and extrapolation shall be performed. Note that
  // for spectral data, the minimum and maximum are expected to be in the
  // unit [nanometer].
  
  // This function instance can now be used. For example, you can retrieve the
  // value at 555 nm:

  printf("Spectral data at 500 nm: %f\n", cmlEval(luminancefunction, 500.f));
  
  
  // You can do the same thing by filtering the luminancefunction with a Dirac
  // filter:
  CMLFunction* dirac = cmlCreateDiracFilter(500.f);
  printf("Spectral data at 500 nm: %f\n", cmlFilterFunction(luminancefunction, dirac));
  cmlReleaseFunction(dirac);
  
  // You can use this function for example, to set this spectrum as the
  // illumination spectrum of the machine:

  cmlSetIlluminationSpectrum(cm3, luminancefunction);
  cmlGetWhitePointYxy(cm3, wpYxy);
  printf("New whitepoint: %f, %f, %f\n", wpYxy[0], wpYxy[1], wpYxy[2]);

  // Remember that the Y component of the whitepoint returned by the
  // cmlGetWhitePointYxy function will always be a radiometric value.

  // Now we create a remission color:
  
  float remissiondata[10] = {  .2f, .3f, .6f, .7f, 1.f,
                              1.2f, .9f, .6f, .2f, .0f};

  CMLFunction* remissionfunction = cmlCreateArrayFunction(
                                      remissiondata,
                                      CMLFALSE,
                                      datacount,
                                      minlambda,
                                      maxlambda,
                                      CML_INTERPOLATION_LINEAR,
                                      CML_EXTRAPOLATION_LINEAR_ZERO,
                                      CML_EXTRAPOLATION_LINEAR_ZERO);

  // We can convert this function to an XYZ value. As this is a remission
  // conversion, the function will multiply with the current illumination
  // (which we just set to our illumination function).
  
  CMLSpectrumRemissiontoXYZ(cm3, xyz, remissionfunction, 1);
  printf("Colorimetric Remission in XYZ: %f, %f, %f\n", xyz[0], xyz[1], xyz[2]);

  // Note that by default, a ColorMachine converts to colorimetric values.
  // If you are interested in radiometric values, simply multiply the values
  // with the Y component of the whitepoint (which, as we just discussed,
  // always contains a radiometric Y value):

  cmlMul3(xyz, wpYxy[0]);
  printf("Radiometric Remission in XYZ: %f, %f, %f\n", xyz[0], xyz[1], xyz[2]);

  // Or change the computation of the ColorMachine to radiometric and recompute
  // the color again. Note that the resulting values might be slightly different
  // due to numerical errors.
  
//  cmlSetRadiometricComputation(cm3, CMLTRUE);
  CMLSpectrumRemissiontoXYZ(cm3, xyz, remissionfunction, 1);
  printf("Radiometric Remission in XYZ: %f, %f, %f\n", xyz[0], xyz[1], xyz[2]);

  // In case you wonder what happends if you have a bodycolor reflecting the
  // illumination spectrum perfectly:

  CMLVec3 yxy;
  CMLFunction* constfunction = cmlCreateConstFilter(1.f);
  CMLSpectrumRemissiontoYxy(cm3, yxy, constfunction, 1);
  printf("Lambertian surface: %f, %f, %f\n", yxy[0], yxy[1], yxy[2]);

  // It should be the same as the whitepoint printed above.

  // Don't forget to release the functions if no longer needed.

  cmlReleaseFunction(constfunction);
  cmlReleaseFunction(remissionfunction);
  cmlReleaseFunction(luminancefunction);
  
  // Beware! When changing a ColorMachine to radiometric computation, all
  // Y-related colors have a different meaning but they will not be converted
  // automatically. You should only use radiometric computation if you really
  // know what you are doing!









  printf("\nWorking with the BaseAPI:\n");

  // ///////////////////////////////////////////////////////////////////////
  // Using the Base API
  // ///////////////////////////////////////////////////////////////////////

  // In BaseAPI.h, you find the most basic color functions used in CML. They
  // are here for programmers who like to do everything manually. But note that
  // the code can get very complicated.
  //
  // A way simpler way of using CML is the use of Color Machines. See above.
  //
  
  // If you want to convert one color into another, use the CMLconvertXXX
  // functions of the BaseAPI:
  
  CMLconvertRGBtoHSV(hsv, orange);
  printf("HSV color: %f, %f, %f\n", hsv[0], hsv[1], hsv[2]);

  // Some conversion need more parameters though. And this is where color
  // computation becomes more and more complex. For example, if we want to
  // convert the orange from RGB to XYZ, we need the response curves of the
  // three channels as well as the transformation matrix. To compute the matrix,
  // we need the three primaries as well as a whitepoint. In the following
  // example, we use sRGB as the desired RGB colorspace. This means that we
  // need the whitepoint of D65, which we need to compute first, which in turn,
  // requires the choice of the appropriate spectal distribution functions.

  // Here is the complete computation:

  // Get all needed information for sRGB:
  CMLVec3 primariesYxy[3];
//  float gamma;
  CMLIlluminationType illuminationtype = cmlGetRGBSpaceIlluminationType(CML_RGB_SRGB);
  cmlGetRGBSpacePrimaries(CML_RGB_SRGB, primariesYxy[0], primariesYxy[1], primariesYxy[2]);

  // Compute the colorimetric whitepoint:
  CMLIllumination* illumination = cmlCreateIlluminationWithPreset(illuminationtype, 0);
  CMLObserver* observer = cmlCreateObserverWithIllumination(CML_OBSERVER_2DEG_CIE_1931, illumination, 100.f);
//  CMLFunction* illumination = cmlCreateIlluminationSpectrum(illuminationtype, 0.f);
//  CMLVec3 wpXYZ;
//  CMLFunction* specdistfuncs[3];
//  cmlCreateSpectralDistributionFunctions(specdistfuncs, CML_OBSERVER_2DEG_CIE_1931);
//  CMLconvertIlluminationSpectrumtoXYZ(wpXYZ, illumination, specdistfuncs[0], specdistfuncs[1], specdistfuncs[2]);
//  cmlDiv3(wpXYZ, wpXYZ[1]);
//  CMLconvertXYZtoYxy(wpYxy, wpXYZ, CML_NULL);
  const float* srgbwp = cmlGetWhitepointYxy(observer);
  
  // Compute the matrix and prepare the response curve:
  CMLMat33 rgbtoxyzmatrix;
  CMLcomputeRGBtoXYZMatrix(rgbtoxyzmatrix, primariesYxy[0], primariesYxy[1], primariesYxy[2], srgbwp);
  CMLFunction* srgbresponse = cmlCreatesRGBToXYZResponse();
  
  // Convert the color:
  CMLconvertRGBtoXYZ(xyz, orange, rgbtoxyzmatrix, srgbresponse, srgbresponse, srgbresponse);
  printf("XYZ color: %f, %f, %f\n", xyz[0], xyz[1], xyz[2]);

  // Release all functions.
  cmlReleaseFunction(srgbresponse);
  cmlReleaseIllumination(illumination);
  cmlReleaseObserver(observer);
  
  // As you can see, such conversions get very complicated very quickly. You
  // CAN do everything manually with the BaseAPI as just shown ...
  // ... but then again, take a look at how RGB to XYZ conversion is done
  // using a Colormachine:
  
  CMLColorMachine* cm4 = cmlCreateColorMachine();
  CMLRGBtoXYZ(cm4, xyz, orange, 1);
  printf("XYZ color: %f, %f, %f\n", xyz[0], xyz[1], xyz[2]);
  
  






  
  printf("\nCleaning up and quitting...");

  /////////////////////////////////////////////////////////////////////////
  // Cleaning up
  /////////////////////////////////////////////////////////////////////////

  // Remember that ColorMachine objects remain in memory as long as you like.
  // You have to release each machine by yourself.

  CMLreleaseColorMachine(cm);
  CMLreleaseColorMachine(cm2);
  CMLreleaseColorMachine(cm3);
  CMLreleaseColorMachine(cm4);
  
  printf(" Bye\n");

  printf("\nPress enter to quit.\n");
  fgetc(stdin);

  return 0;
}



// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.


#include <stdio.h>
//#include "Timer.h"
#include <CML/CML.h>
#include "NARandom.h"
#include "NADateTime.h"




int main(){

  // ///////////////////////////////////////////////
  // Welcome to the example of the Color Machine Library (CML)
  //
  // In this file, some examples are shown on how to use CML. Feel free to
  // experiment. For further information, please refer to the many comments in
  // the Header-Files of CML.
  // ///////////////////////////////////////////////

  // To start using CML, you must activate a CML context. Store the returned
  // pointer to correctly clean up your memory at the end.
  
  CMLContext* cmlcontext = cmlActivateContext(CML_NULL);

  // The version is denoted by 4 unsigned 8-bit integers. The last one is
  // either 0 for Release or 1 for Debug.
  
  CMLInt version = cmlGetContextVersion(cmlcontext);
  printf("CML Version: %d (%s)\n",  abs(version), (version<0)?"Debug":"Release");
  
  // The Debug version is only available to you upon special request to the
  // author. In the Debug version, a lot of security tests are performed and
  // errors or warnings are printed to the standard output. Due to excessive
  // tests, it can be very verbose and WAY slower than the release version.
  // Do NOT use the Debug-Version for releases.
  
  
  
  
  
  // Let's start with the obvious: Convert a color.
  
  

//  #define TESTSIZE 10000000
//  float* intest = (float*)malloc(3*TESTSIZE*sizeof(float));
////  float* outtest = (float*)malloc(3*TESTSIZE*sizeof(float));
//  for(CMLInt i=0; i<TESTSIZE; i++){
//    intest[i*3+0] = naUniformRandZEf();
//    intest[i*3+1] = naUniformRandZEf();
//    intest[i*3+2] = naUniformRandZEf();
//  }
  
  
  float myXYZ[3] = {.3, .4, .5};
//  float myYxy[3] = {21.263693, 0.640000, 0.330000};
//  float myYupvp[3] = {80., .2, .2};
//  float myYuv[3] = {80., .2, .2};
//  float myLuv[3] = {30., .6, .4};
  float myLab[3] = {75., 30, -30};
//  float myLch[3] = {75., 50, 120.};
  float myRGB[3] = {.5, .2, .7};
//  float myYCbCr[3] = {50., .4, -.2};
//  float myHSV[3] = {45, .5, .7};
//  float myHSL[3] = {45, .8, .4};
//  CMLMOBFunction* illum50 = cmlCreateCIEDIlluminant(CML_TEMPERATURE_D50);
//  CMLMOBFunction* illum65 = cmlCreateCIEDIlluminant(CML_TEMPERATURE_D65);
//  CMLMOBFunction* illumE = cmlCreateIlluminationSpectrum(CML_ILLUMINATION_E, 0.f);
//  CMLMOBFunction* onefunc = cmlCreateConstFilter(1.);
//  CMLMOBFunction* outfunc;
  
//  CMLColorspace* RadiometricSpace = cmlCreateColorspace(CML_Radiometric, CML_ENCODING_NORM);
  CMLColorspace* RadiometricSpace2 = cmlCreateColorspace(CML_Radiometric, CML_ENCODING_FLOAT);
//  CMLColorspace* ColorimetricSpace = cmlCreateColorspace(CML_Remission);
  CMLColorspace* XYZSpace = cmlCreateColorspace(CML_XYZ, CML_ENCODING_FLOAT);
//  CMLColorspace* XYZNormSpace = cmlCreateColorspace(CML_XYZ, CML_ENCODING_NORM);
//  CMLColorspace* YxySpace = cmlCreateColorspace(CML_Yxy, CML_ENCODING_FLOAT);
//  CMLColorspace* YupvpSpace = cmlCreateColorspace(CML_Yupvp, CML_ENCODING_FLOAT);
//  CMLColorspace* YuvSpace = cmlCreateColorspace(CML_Yuv, CML_ENCODING_FLOAT);
//  CMLColorspace* LuvSpace = cmlCreateColorspace(CML_Luv, CML_ENCODING_FLOAT);
  CMLColorspace* LabSpace = cmlCreateColorspace(CML_Lab, CML_ENCODING_FLOAT);
//  CMLColorspace* LchSpace = cmlCreateColorspace(CML_Lch, CML_ENCODING_FLOAT);
  CMLColorspace* RGBSpace = cmlCreateColorspace(CML_RGB, CML_ENCODING_FLOAT);
//  CMLColorspace* YCbCrSpace = cmlCreateColorspace(CML_YCbCr, CML_ENCODING_FLOAT);
//  CMLColorspace* HSVSpace = cmlCreateColorspace(CML_HSV, CML_ENCODING_FLOAT);
//  CMLColorspace* HSLSpace = cmlCreateColorspace(CML_HSL, CML_ENCODING_FLOAT);


  CMLColor* SpectrumColor = cmlCreateRadiometric(RadiometricSpace2, cmlCreateIlluminationSpectrum(CML_ILLUMINATION_D50, 0.f));
  CMLColor* XYZColor = cmlCreateXYZ(XYZSpace, myXYZ[0], myXYZ[1], myXYZ[2]);
//  CMLColor* XYZColor = cmlCreateXYZ(XYZSpace, 30, 40, 80);
//  CMLColor* XYZNormColor = cmlCreateNormXYZ(XYZNormSpace, myXYZ[0], myXYZ[1], myXYZ[2]);
//  CMLColor* YxyColor = cmlCreateYxy(YxySpace, myYxy[0], myYxy[1], myYxy[2]);
//  CMLColor* YupvpColor = cmlCreateYupvp(YupvpSpace, myYupvp[0], myYupvp[1], myYupvp[2]);
//  CMLColor* YuvColor = cmlCreateYuv(YuvSpace, myYuv[0], myYuv[1], myYuv[2]);
//  CMLColor* LuvColor = cmlCreateLuv(LuvSpace, myLuv[0], myLuv[1], myLuv[2]);
  CMLColor* LabColor = cmlCreateLab(LabSpace, myLab[0], myLab[1], myLab[2]);
//  CMLColor* HSVColor = cmlCreateHSV(HSVSpace, myHSV[0], myHSV[1], myHSV[2]);

  CMLColor* RGBColor = cmlCreateRGB(RGBSpace, myRGB[0], myRGB[1], myRGB[2]);

//  cmlDebugColor(XYZColor);
//  cmlDebugColor(YxyColor);
  cmlDebugColor(RGBColor);
  
  cmlConvertColor(CML_NULL, XYZColor, RGBColor);

  CMLColor* test = cmlCreateColor(RadiometricSpace2, LabColor);
  cmlDebugColor(LabColor);
  cmlDebugColor(SpectrumColor);
  cmlDebugColor(test);

  CMLMOBFunction* spec = cmlGetColorFunctionComponent(test, 0);
  for(float l=300.f; l<830.f; l+=10.f){
    printf("%f\n", cmlEval(spec, l));
  }


//  CMLColor* test = cmlCreateColor(LuvSpace, YxyColor);
//  cmlDebugColor(test);

//  CMLConverter* myconverter;
//  myconverter = cmlCreateConverter(RGBSpace, RGBSpace);
//  cmlConvertColor(myconverter, RGBColor, RGBColor);
//  cmlDebugColor(RGBColor);
//




  // Remember the pointer we stored when we first created the context? Simply
  // use that pointer to clean up everything.
  cmlDestroyContext(cmlcontext);

  return 0;
}



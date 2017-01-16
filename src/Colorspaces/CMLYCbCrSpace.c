
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

#include "CML.h"
#include "CMLInternal.h"


CML_HIDDEN float cml_YCbCrScalarComponentMin(CMLColorspace* colorspace, CMLInt indx){
  CML_UNUSED(colorspace);
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_COLORSPACE_OBJECT), colorspace))
    cmlError("cml_YuvScalarComponentMax", "Given MOB is not a Colorspace\n");
  #endif

  if(indx == 0){return 0.f;}
  return -.5f;
}


CML_HIDDEN float cml_YCbCrScalarComponentMax(CMLColorspace* colorspace, CMLInt indx){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_COLORSPACE_OBJECT), colorspace))
    cmlError("cml_YuvScalarComponentMax", "Given MOB is not a Colorspace\n");
  #endif

  if(indx == 0){
    MOB* generator = cmlGetColorspaceSetting(colorspace, CML_SETTING_GENERATOR);
    float metricScale = cmlGetGeneratorMetricScale(generator);
    if(metricScale){
      return metricScale;
    }else{
      const float* whiteXYZ = cmlGetGeneratorWhiteXYZRadiometric(generator);
      return whiteXYZ[1];
    }
  }
  return .5f;
}


CML_HIDDEN void cml_DefineYCbCrSpaceValences(){
  cmlAddComponent(CML_COMPONENT_CARTESIAN, "Y");
  cmlAddComponent(CML_COMPONENT_CARTESIAN, "Cb");
  cmlAddComponent(CML_COMPONENT_CARTESIAN, "Cr");
}



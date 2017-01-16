
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

#include "CML.h"
#include "CMLInternal.h"



CML_HIDDEN float cml_YxyScalarComponentMax(CMLColorspace* colorspace, CMLInt indx){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_COLORSPACE_OBJECT), colorspace))
    cmlError("cml_YxyScalarComponentMax", "Given MOB is not a Colorspace\n");
  #endif

  if(indx != 0){return 1.f;}
  
  MOB* observer = cmlGetColorspaceSetting(colorspace, CML_SETTING_OBSERVER);
  float metricScale = cmlGetObserverMetricScale(observer);
  if(metricScale){
    return metricScale;
  }else{
    const float* whiteYxy = cmlGetObserverAdaptationWhiteYxyRadiometric(observer);
    return whiteYxy[0];
  }
}



CML_HIDDEN void cml_DefineYxySpaceValences(){
  cmlAddComponent(CML_COMPONENT_CARTESIAN, "Y");
  cmlAddComponent(CML_COMPONENT_CARTESIAN, "x");
  cmlAddComponent(CML_COMPONENT_CARTESIAN, "y");
}






// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

#include "../CML.h"
#include "../StateMachine/CMLInternal.h"



CML_HIDDEN float cml_XYZScalarComponentMax(CMLColorspace* colorspace, CMLInt indx){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_COLORSPACE_OBJECT), colorspace))
    cmlError("cml_XYZScalarComponentMax", "Given MOB is not a Colorspace\n");
  #endif

  MOB* observer = cmlGetColorspaceSetting(colorspace, CML_SETTING_OBSERVER);
  float metricScale = cmlGetObserverMetricScale(observer);
  if(metricScale){
    return metricScale;
  }else{
    const float* whiteXYZ = cmlGetObserverAdaptationWhiteXYZRadiometric(observer);
    return whiteXYZ[indx];
  }
}


CML_HIDDEN void cml_DefineXYZSpaceValences(){
  cmlAddComponent(CML_COMPONENT_CARTESIAN, "X");
  cmlAddComponent(CML_COMPONENT_CARTESIAN, "Y");
  cmlAddComponent(CML_COMPONENT_CARTESIAN, "Z");
  cmlSetMainComponent(1);
}





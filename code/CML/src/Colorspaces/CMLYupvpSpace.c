
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

#include "../CML.h"
#include "../StateMachine/CMLInternal.h"


CML_HIDDEN float cml_YupvpScalarComponentMax(CMLColorspace* colorspace, CMLInt indx){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_COLORSPACE_OBJECT), colorspace))
    cmlError("cml_YupvpScalarComponentMax", "Given MOB is not a Colorspace\n");
  #endif

  if(indx == 1){return 1.f;}
  if(indx == 2){return .75f;}
  
  MOB* observer = cmlGetColorspaceSetting(colorspace, CML_SETTING_OBSERVER);
  float metricScale = cmlGetObserverMetricScale(observer);
  if(metricScale){
    return metricScale;
  }else{
    const float* whiteYupvp = cmlGetObserverAdaptationWhiteYupvpRadiometric(observer);
    return whiteYupvp[0];
  }
}


CML_HIDDEN void cml_DefineYupvpSpaceValences(){
  cmlAddComponent(CML_COMPONENT_CARTESIAN, "Y");
  cmlAddComponent(CML_COMPONENT_CARTESIAN, "u\'");
  cmlAddComponent(CML_COMPONENT_CARTESIAN, "v\'");
}




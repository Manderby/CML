
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

#include "../CML.h"
#include "../StateMachine/CMLInternal.h"






CML_HIDDEN CML_INLINE void cml_OneRadiometricToXYZ (float* CML_RESTRICT XYZ0, float* CML_RESTRICT XYZ1, float* CML_RESTRICT XYZ2, CMLMOBFunction** spec, CMLMOBFunction* filter0, CMLMOBFunction* filter1, CMLMOBFunction* filter2, float metricScale, const float* CML_RESTRICT whitepointXYZ){
  cml_OneRadiometricToXYZRadiometric(XYZ0, XYZ1, XYZ2, spec, filter0, filter1, filter2);
  *XYZ0 = *XYZ0 * metricScale / whitepointXYZ[1];
  *XYZ1 = *XYZ1 * metricScale / whitepointXYZ[1];
  *XYZ2 = *XYZ2 * metricScale / whitepointXYZ[1];
}





CML_HIDDEN void cml_RadiometricToXYZ(CMLOutput out, CMLInput in, CMLSize count){
  CMLMOBObserver* observer = cmlGetConverterSetting(CML_SETTING_OBSERVER, CML_GET_ADD);
  if(cmlGetConverterError()){return;}

  CMLMOBFunctionVector* filterfuncs = cmlGetObserverFunctions(observer);
  CMLInt filtercount = cmlGetFunctionVectorCount(filterfuncs);
  if(filtercount != 3){
    cmlSetConverterError(CML_SETTING_INAPPROPRIATE_FOR_CONVERSION);
    return;
  }

  CMLMOBFunction* filter0 = cmlGetFunctionVectorFunction(filterfuncs, 0);
  CMLMOBFunction* filter1 = cmlGetFunctionVectorFunction(filterfuncs, 1);
  CMLMOBFunction* filter2 = cmlGetFunctionVectorFunction(filterfuncs, 2);
  const float* whiteXYZ = cmlGetObserverAdaptationWhiteXYZRadiometric(observer);
  float metricScale = cmlGetObserverMetricScale(observer);
  CMLVec3 radiometricwhitepointXYZ;

  if(!metricScale){
    // Adjust locally
    metricScale = 1.f;
    cmlSet3(radiometricwhitepointXYZ, 1.f, 1.f, 1.f);
    whiteXYZ = radiometricwhitepointXYZ;
  }
  
  while(count){
    CMLMOBFunction** spec = cmlNextMutableFunctionComponent(in);
    float* XYZ0 = cmlNextMutableFloatComponent(out);
    float* XYZ1 = cmlNextMutableFloatComponent(out);
    float* XYZ2 = cmlNextMutableFloatComponent(out);

    cml_OneRadiometricToXYZ(XYZ0, XYZ1, XYZ2, spec, filter0, filter1, filter2, metricScale, whiteXYZ);

    count--;
  }
}





// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

#include "CML.h"
#include "StateMachine/CMLColorMachineState.h"
#include "NAString.h"




CML_API CMLSettingID cmlRegisterColorspaceSettingClass(const char* name, CMLColorspaceSettingConstructor defaultconstructor){
  NA_UNUSED(name);
  NA_UNUSED(defaultconstructor);
//  // todo: check if name already exists.
//
//  CMLSettingID newsettingClassid = (CMLSettingID)naGetStackCount(&(cmlc->settingClasses));
//
//  CMLSettingClass* newclass = mobCreateObject(cml_Key(CML_SETTING_CLASS_OBJECT));
//  // todo
////  naNewStringWithFormat(mobKeyString(newclass, cml_Key(CML_SETTING_CLASS_NAME)), name);
//  mobSetKeyUnitValue(newclass, cml_Key(CML_COLORSPACE_SETTING_CLASS_CONSTRUCTOR), cml_Unit(CML_UNIT_COLORSPACE_SETTING_CONSTRUCTOR), &defaultconstructor);
//  *(CMLSettingID*)mobKeyEnum(newclass, cml_Key(CML_SETTING_CLASS_ID)) = newsettingClassid;
//
//  CMLSettingClass** registeredelement = naPushStack(&(cmlc->settingClasses));
//  *registeredelement = newclass;
//  return newsettingClassid;
  return 0;
}




CML_API CMLSettingID cmlRegisterConverterSettingClass(const char* name, CMLConverterSettingConstructor defaultconstructor){
  NA_UNUSED(name);
  NA_UNUSED(defaultconstructor);
//  // todo: check if name already exists.
//
//  CMLSettingID newsettingClassid = (CMLSettingID)naGetStackCount(&(cmlc->settingClasses));
//
//  CMLSettingClass* newclass = mobCreateObject(cml_Key(CML_SETTING_CLASS_OBJECT));
//  // todo
////  naNewStringWithFormat(mobKeyString(newclass, cml_Key(CML_SETTING_CLASS_NAME)), name);
//  mobSetKeyUnitValue(newclass, cml_Key(CML_CONVERTER_SETTING_CLASS_CONSTRUCTOR), cml_Unit(CML_UNIT_CONVERTER_SETTING_CONSTRUCTOR), &defaultconstructor);
//  *(CMLSettingID*)mobKeyEnum(newclass, cml_Key(CML_SETTING_CLASS_ID)) = newsettingClassid;
//  
//  CMLSettingClass** registeredelement = naPushStack(&(cmlc->settingClasses));
//  *registeredelement = newclass;
//  return newsettingClassid;
  return 0;
}


CML_API CMLSetting* cmlGetDefaultColorspaceSetting(CMLSettingID settingClassID){
  CMLSettingClass* settingClass = cml_GetContextSettingClass(settingClassID);
  return cml_GetSettingClassDefaultColorspaceSetting(settingClass);
}


CML_API CMLSetting* cmlGetDefaultConverterSetting(CMLSettingID settingClassID, CMLColorspace* dstspace, CMLColorspace* srcspace){
  CMLSettingClass* settingClass = cml_GetContextSettingClass(settingClassID);
  return cml_GetSettingClassDefaultConverterSetting(settingClass, dstspace, srcspace);
}



CML_HIDDEN void cml_DestroySettingClass(CMLSettingClass* settingClass){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_SETTING_CLASS_OBJECT), settingClass))
    cmlError("cml_DestroySettingClass", "Given MOB is not a SettingClass\n");
  #endif
  mobDestroyObject(settingClass);
}


CML_HIDDEN CMLSettingID cml_GetSettingClassID(CMLSettingClass* settingClass){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_SETTING_CLASS_OBJECT), settingClass))
    cmlError("cml_GetSettingClassID", "Given MOB is not a SettingClass\n");
  #endif
  return *(CMLSettingID*)mobKeyEnum(settingClass, cml_Key(CML_SETTING_CLASS_ID));
}

CML_HIDDEN NAString* cml_GetSettingClassName(CMLSettingClass* settingClass){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_SETTING_CLASS_OBJECT), settingClass))
    cmlError("cml_GetSettingClassName", "Given MOB is not a SettingClass\n");
  #endif
  return mobKeyString(settingClass, cml_Key(CML_SETTING_CLASS_NAME));
}



CML_HIDDEN void cml_DebugSettingClass(CMLSettingClass* settingClass){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_SETTING_CLASS_OBJECT), settingClass))
    cmlError("cml_DebugSettingClass", "Given MOB is not a SettingClass\n");
  #endif
  NAString* namestring = mobKeyString(settingClass, cml_Key(CML_SETTING_CLASS_NAME));
  printf("Setting Class \"%s\"\n", naGetStringUTF8Pointer(namestring));
}

CML_HIDDEN void cml_DebugSetting(CMLSetting* setting){

  // todo
  CML_UNUSED(setting);
}













CML_HIDDEN CMLSetting* cml_CreateSettingObserver(){
  CMLMOBObserver* observer = mobCreateEmptyObject();
  MOB* adaptationspectrum = cmlCreateConstFilter(1.f);
  MOB* observerfuncs = cmlCreateFunctionVectorWithCount(3);
  cmlSetFunctionVectorFunction(observerfuncs, 0, cmlCreateBinomialFilter(CML_DEFAULT_INTEGRATION_MIN, CML_DEFAULT_INTEGRATION_MAX, 2, 0));
  cmlSetFunctionVectorFunction(observerfuncs, 1, cmlCreateBinomialFilter(CML_DEFAULT_INTEGRATION_MIN, CML_DEFAULT_INTEGRATION_MAX, 2, 1));
  cmlSetFunctionVectorFunction(observerfuncs, 2, cmlCreateBinomialFilter(CML_DEFAULT_INTEGRATION_MIN, CML_DEFAULT_INTEGRATION_MAX, 2, 2));
  MOB* metricScale = mobCreateFloat(0.f);
  
  mobSetKeyObject(observer, cml_Key(CML_OBSERVER_FUNCTIONS), observerfuncs, MOB_FALSE);
  mobSetKeyObject(observer, cml_Key(CML_OBSERVER_ADAPTATION_WHITE_SPECTRUM), adaptationspectrum, MOB_FALSE);
  mobSetKeyObject(observer, cml_Key(CML_OBSERVER_METRIC_SCALE), metricScale, MOB_FALSE);
  return observer;
}


CML_HIDDEN CMLSetting* cml_CreateSettingGenerator(){
  CMLMOBGenerator* generator = mobCreateEmptyObject();
  MOB* whitespectrum = cmlCreateConstFilter(1.f);
  MOB* generatorfuncs = cmlCreateFunctionVectorWithCount(3);
  cmlSetFunctionVectorFunction(generatorfuncs, 0, cmlCreateBinomialFilter(CML_DEFAULT_INTEGRATION_MIN, CML_DEFAULT_INTEGRATION_MAX, 2, 0));
  cmlSetFunctionVectorFunction(generatorfuncs, 1, cmlCreateBinomialFilter(CML_DEFAULT_INTEGRATION_MIN, CML_DEFAULT_INTEGRATION_MAX, 2, 1));
  cmlSetFunctionVectorFunction(generatorfuncs, 2, cmlCreateBinomialFilter(CML_DEFAULT_INTEGRATION_MIN, CML_DEFAULT_INTEGRATION_MAX, 2, 2));
  MOB* metricScale = mobCreateFloat(0.f);
  
  mobSetKeyObject(generator, cml_Key(CML_GENERATOR_FUNCTIONS), generatorfuncs, MOB_FALSE);
  mobSetKeyObject(generator, cml_Key(CML_GENERATOR_WHITE_SPECTRUM), whitespectrum, MOB_FALSE);
  mobSetKeyObject(generator, cml_Key(CML_GENERATOR_METRIC_SCALE), metricScale, MOB_FALSE);
  return generator;
}


CML_HIDDEN CMLSetting* cml_CreateSettingResponseCurves(){
  MOB* forwardfuncs = mobCreateArray(3);
  mobSetArrayObject(forwardfuncs, 0, cmlCreateResponseCurveWithPreset(CML_RESPONSE_LINEAR));
  mobSetArrayObject(forwardfuncs, 1, cmlCreateResponseCurveWithPreset(CML_RESPONSE_LINEAR));
  mobSetArrayObject(forwardfuncs, 2, cmlCreateResponseCurveWithPreset(CML_RESPONSE_LINEAR));
  return forwardfuncs;
}



CML_HIDDEN CMLSetting* cml_CreateSettingIlluminationSpectrum(){
  return cmlCreateConstFilter(1.f);
}





CML_HIDDEN CMLSetting* cml_CreateSettingObsToGenMatrix(CMLColorspace* dstspace, CMLColorspace* srcspace){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_COLORSPACE_OBJECT), dstspace))
    cmlError("cml_CreateSettingObsToGenMatrix", "Given MOB is not a Colorspace\n");
  if(!mobEqual(cml_Key(CML_COLORSPACE_OBJECT), srcspace))
    cmlError("cml_CreateSettingObsToGenMatrix", "Given MOB is not a Colorspace\n");
  #endif
  CMLMOBObserver* observer = cmlGetColorspaceSetting(srcspace, CML_SETTING_OBSERVER);
  CMLMOBGenerator* generator = cmlGetColorspaceSetting(dstspace, CML_SETTING_GENERATOR);
  if(!observer || !generator){return CML_NULL;}
  CMLMOBFunctionVector* observerfuncs = cmlGetObserverFunctions(observer);
  CMLMOBFunctionVector* generatorfuncs = cmlGetGeneratorFunctions(generator);
  return cml_CreateObsToGenMatrix(observerfuncs, generatorfuncs);
}



CML_HIDDEN CMLSetting* cml_CreateSettingGenToObsMatrix(CMLColorspace* dstspace, CMLColorspace* srcspace){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_COLORSPACE_OBJECT), dstspace))
    cmlError("cml_CreateSettingGenToObsMatrix", "Given MOB is not a Colorspace\n");
  if(!mobEqual(cml_Key(CML_COLORSPACE_OBJECT), srcspace))
    cmlError("cml_CreateSettingGenToObsMatrix", "Given MOB is not a Colorspace\n");
  #endif
  CMLMOBObserver* observer = cmlGetColorspaceSetting(dstspace, CML_SETTING_OBSERVER);
  CMLMOBGenerator* generator = cmlGetColorspaceSetting(srcspace, CML_SETTING_GENERATOR);
  if(!observer || !generator){return CML_NULL;}
  CMLMOBFunctionVector* observerfuncs = cmlGetObserverFunctions(observer);
  CMLMOBFunctionVector* generatorfuncs = cmlGetGeneratorFunctions(generator);
  return cml_CreateGenToObsMatrix(observerfuncs, generatorfuncs);
}



CML_HIDDEN CMLSetting* cml_CreateSettingComponentsOffsets(CMLColorspace* dstspace, CMLColorspace* srcspace){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_COLORSPACE_OBJECT), dstspace))
    cmlError("cml_CreateSettingComponentsOffsets", "Given MOB is not a Colorspace\n");
  if(!mobEqual(cml_Key(CML_COLORSPACE_OBJECT), srcspace))
    cmlError("cml_CreateSettingComponentsOffsets", "Given MOB is not a Colorspace\n");
  #endif
  const CMLColorspaceClass* dstcolorspaceClass = cml_GetColorspaceClass(dstspace);
  const CMLColorspaceClass* srccolorspaceClass = cml_GetColorspaceClass(srcspace);
  CMLInt componentscount = cmlGetComponentsCount(cml_GetColorspaceAbstractType(cml_GetColorspaceClassAbstract(dstcolorspaceClass)));
  MOB* offsets = mobCreateFloatArray(componentscount);

  CMLEncoding encoding = cml_GetColorspaceClassEncoding(srccolorspaceClass);
  CMLColorspace* desiredcolorspace;
  const CMLColorspaceClass* desiredcolorspaceClass;
  if(encoding == CML_ENCODING_NORM){
    desiredcolorspace = dstspace;
    desiredcolorspaceClass = dstcolorspaceClass;
  }else{
    desiredcolorspace = srcspace;
    desiredcolorspaceClass = srccolorspaceClass;
  }
  
  for(CMLInt c=0; c<componentscount; c++){
    CMLComponentType componentType = cmlGetComponentType(cml_GetColorspaceAbstractType(cml_GetColorspaceClassAbstract(desiredcolorspaceClass)), c);
    float offsetvalue;
    switch(componentType){
    case CML_COMPONENT_CARTESIAN:
    case CML_COMPONENT_RADIAL:
    case CML_COMPONENT_ANGULAR:
      offsetvalue = cmlGetColorspaceComponentMin(desiredcolorspace, c);
      break;
    case CML_COMPONENT_FUNCTION:
      offsetvalue = 0.f;
      break;
    }
    *mobArrayFloat(offsets, c) = offsetvalue;
  }
  return offsets;
}


CML_HIDDEN CMLSetting* cml_CreateSettingComponentsRanges(CMLColorspace* dstspace, CMLColorspace* srcspace){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_COLORSPACE_OBJECT), dstspace))
    cmlError("cml_CreateSettingComponentsRanges", "Given MOB is not a Colorspace\n");
  if(!mobEqual(cml_Key(CML_COLORSPACE_OBJECT), srcspace))
    cmlError("cml_CreateSettingComponentsRanges", "Given MOB is not a Colorspace\n");
  #endif
  const CMLColorspaceClass* dstcolorspaceClass = cml_GetColorspaceClass(dstspace);
  const CMLColorspaceClass* srccolorspaceClass = cml_GetColorspaceClass(srcspace);
  CMLInt componentscount = cmlGetComponentsCount(cml_GetColorspaceAbstractType(cml_GetColorspaceClassAbstract(dstcolorspaceClass)));
  MOB* ranges = mobCreateFloatArray(componentscount);

  CMLEncoding encoding = cml_GetColorspaceClassEncoding(srccolorspaceClass);
//  CMLEncoding encodingdst = cml_GetColorspaceClassEncoding(dstcolorspaceClass);
  CMLColorspace* desiredcolorspace;
  const CMLColorspaceClass* desiredcolorspaceClass;
  if(encoding == CML_ENCODING_NORM){
    desiredcolorspace = dstspace;
    desiredcolorspaceClass = dstcolorspaceClass;
  }else{
    desiredcolorspace = srcspace;
    desiredcolorspaceClass = srccolorspaceClass;
  }

  for(CMLInt c=0; c<componentscount; c++){
    CMLComponentType componentType = cmlGetComponentType(cml_GetColorspaceAbstractType(cml_GetColorspaceClassAbstract(desiredcolorspaceClass)), c);
    float rangevalue;
    switch(componentType){
    case CML_COMPONENT_CARTESIAN:
    case CML_COMPONENT_RADIAL:
    case CML_COMPONENT_ANGULAR:
      rangevalue = cmlGetColorspaceComponentMax(desiredcolorspace, c) - cmlGetColorspaceComponentMin(desiredcolorspace, c);
      break;
    case CML_COMPONENT_FUNCTION:
      rangevalue = 1.f;
      break;
    }
    *mobArrayFloat(ranges, c) = rangevalue;
  }
  return ranges;
}





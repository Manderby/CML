
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.


#include "CML.h"
#include "CMLColorMachineState.h"
#include "NAString.h"



CML_HIDDEN CMLColorspace* cml_CreateBlankColorspace(CMLColorspaceClass* colorspaceClass){  
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_COLORSPACE_CLASS_OBJECT), colorspaceClass))
    cmlError("cml_CreateBlankColorspace", "Given MOB is not a Colorspace class\n");
  #endif
  // Create an instatiation of the given colorspace class and store all
  // necessary values
  return mobCreateSubObject(colorspaceClass, cml_Key(CML_COLORSPACE_OBJECT));
}



CML_API CMLColorspace* cmlCreateColorspace(CMLColorspaceType colorspaceType, CMLEncoding encoding){
  CMLColorspaceClass* colorspaceClass = cml_GetContextColorspaceClass(colorspaceType, encoding);
  CMLColorspace* colorspace = cml_CreateBlankColorspace(colorspaceClass);

  // Fill the blank space with required settings.
  CMLSettingClass* requiredsettingClass = MOB_NULL;
  while(mobNextKeyObject(colorspaceClass, cml_Key(CML_COLORSPACE_CLASS_REQUIRED_SETTING_CLASSES), &requiredsettingClass)){
    CMLSetting* newsetting = cml_GetSettingClassDefaultColorspaceSetting(requiredsettingClass);
    cml_SetColorspaceSetting(colorspace, requiredsettingClass, newsetting);
  }

  return colorspace;
}



CML_API void cmlDestroyColorspace(CMLColorspace* colorspace){
  if(!colorspace){return;}
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_COLORSPACE_OBJECT), colorspace))
    cmlError("cmlDestroyColorspace", "Given MOB is not a Colorspace\n");
  #endif
  mobDestroyObject(colorspace);
}



CML_API CMLSetting* cmlGetColorspaceSetting(CMLColorspace* colorspace, CMLSettingID settingClassID){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_COLORSPACE_OBJECT), colorspace))
    cmlError("cmlGetColorspaceSetting", "Given MOB is not a Colorspace\n");
  #endif
  CMLSettingClass* settingClass = cml_GetContextSettingClass(settingClassID);
  CMLSetting* setting = cml_GetColorspaceSetting(colorspace, settingClass);
  if(!setting){
    CMLColorspaceClass* colorspaceClass = (CMLColorspaceClass*)cml_GetColorspaceClass(colorspace); // todo: hack
    cml_AddColorspaceClassRequiredSetting(colorspaceClass, settingClass);
    setting = cml_GetColorspaceSetting(colorspace, settingClass);
  }
  return setting;
}



CML_API void cmlSetColorspaceSetting(CMLColorspace* colorspace, CMLSettingID settingClassID, CMLSetting* setting){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_COLORSPACE_OBJECT), colorspace))
    cmlError("cmlSetColorspaceSetting", "Given MOB is not a Colorspace\n");
  if(!setting)
    cmlError("cmlSetColorspaceSetting", "setting should not be null");
  #endif
  CMLSettingClass* settingClass = cml_GetContextSettingClass(settingClassID);
  cml_SetColorspaceSetting(colorspace, settingClass, setting);
}



CML_API CMLColorspaceType cmlGetColorspaceType(CMLColorspace* colorspace){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_COLORSPACE_OBJECT), colorspace))
    cmlError("cmlGetColorspaceStorageSize", "Given MOB is not a Colorspace\n");
  #endif
  const CMLColorspaceClass* colorspaceClass = cml_GetColorspaceClass(colorspace);
  CMLColorspaceAbstract* colorspaceabstract = cml_GetColorspaceClassAbstract(colorspaceClass);
  return cml_GetColorspaceAbstractType(colorspaceabstract);
}



CML_API float cmlGetColorspaceComponentMin(CMLColorspace* colorspace, CMLInt indx){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_COLORSPACE_OBJECT), colorspace))
    cmlError("cmlGetColorspaceComponentMin", "Given MOB is not a Colorspace\n");
  #endif
  const CMLColorspaceClass* colorspaceClass = cml_GetColorspaceClass(colorspace);
  CMLMinMaxComponentFunction minfunc = cml_GetColorspaceClassMinFunction(colorspaceClass);
  if(minfunc){
    return minfunc(colorspace, indx);
  }else{
    return 0.f;
  }
}



CML_API float cmlGetColorspaceComponentMax(CMLColorspace* colorspace, CMLInt indx){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_COLORSPACE_OBJECT), colorspace))
    cmlError("cmlGetColorspaceComponentMax", "Given MOB is not a Colorspace\n");
  #endif
  const CMLColorspaceClass* colorspaceClass = cml_GetColorspaceClass(colorspace);
  CMLMinMaxComponentFunction maxfunc = cml_GetColorspaceClassMaxFunction(colorspaceClass);
  if(maxfunc){
    return maxfunc(colorspace, indx);
  }else{
    return 1.f;
  }
}




CML_HIDDEN void cml_DebugColorspace(CMLColorspace* colorspace){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_COLORSPACE_OBJECT), colorspace))
    cmlError("cml_DebugColorspace", "Given MOB is not a Colorspace\n");
  #endif
  const CMLColorspaceClass* colorspaceClass = cml_GetColorspaceClass(colorspace);
  NAString* classname = cml_GetColorspaceClassName(colorspaceClass);
  printf("-- Debugging colorspace of class %s\n", naGetStringUTF8Pointer(classname));
  printf("Storing the following required settings:\n");
  CMLSettingClass* requiredsettingClass = MOB_NULL;
  while(mobNextKeyObject(colorspaceClass, cml_Key(CML_COLORSPACE_CLASS_REQUIRED_SETTING_CLASSES), &requiredsettingClass)){
    NAString* settingClassname = cml_GetSettingClassName(requiredsettingClass);
    CMLSetting* setting = mobGetKeyObject(colorspace, requiredsettingClass);
    printf("%s: %p\n", naGetStringUTF8Pointer(settingClassname), (void*)setting);
  }
}




CML_HIDDEN CMLBool cml_EqualColorspace(CMLColorspace* space1, CMLColorspace* space2){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_COLORSPACE_OBJECT), space1))
    cmlError("cml_EqualColorspace", "Given MOB is not a Colorspace\n");
  if(!mobEqual(cml_Key(CML_COLORSPACE_OBJECT), space2))
    cmlError("cml_EqualColorspace", "Given MOB is not a Colorspace\n");
  #endif
  const CMLColorspaceClass* colorspaceClass1 = cml_GetColorspaceClass(space1);
  const CMLColorspaceClass* colorspaceClass2 = cml_GetColorspaceClass(space2);
  if(colorspaceClass1 != colorspaceClass2){return CML_FALSE;}
  
  MOB* requiredsettingClass = MOB_NULL;
  while(mobNextKeyObject(colorspaceClass1, cml_Key(CML_COLORSPACE_CLASS_REQUIRED_SETTING_CLASSES), &requiredsettingClass)){
    MOB* cursetting1 = mobGetKeyObject(space1, requiredsettingClass);
    MOB* cursetting2 = mobGetKeyObject(space2, requiredsettingClass);
    #ifndef NDEBUG
      if(!cursetting1 || !cursetting2)
        cmlError("cml_EqualColorspace", "Required setting is not available.");
    #endif
    if(!mobEqual(cursetting1, cursetting2)){return CML_FALSE;}
  }
  return CML_TRUE;
}




CML_API CMLColorspace* cml_CreateColorspaceOfConverterGoal(CMLColorspace* srcspace, CMLConverterClass* converterClass, CMLColorspace* goalspace){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_COLORSPACE_OBJECT), goalspace))
    cmlError("cml_CreateColorspaceOfConverterGoal", "Given MOB is not a Colorspace\n");
  if(!mobEqual(cml_Key(CML_COLORSPACE_OBJECT), srcspace))
    cmlError("cml_CreateColorspaceOfConverterGoal", "Given MOB is not a Colorspace\n");
  #endif

  CMLColorspaceClass* converterdstcolorspaceClass = cml_GetConverterClassDstColorspaceClass(converterClass);
  
  #ifndef NDEBUG
    CMLColorspaceClass* convertersrccolorspaceClass = cml_GetConverterClassSrcColorspaceClass(converterClass);
    const CMLColorspaceClass* srccolorspaceClass = cml_GetColorspaceClass(srcspace);
    if(convertersrccolorspaceClass != srccolorspaceClass)
      cmlError("cml_CreateColorspaceOfConverterGoal", "srcspace does not correspond to source of converter class");
  #endif
  
  CMLColorspace* newspace = cml_CreateBlankColorspace(converterdstcolorspaceClass);

  // Go through all settings whose handling is defined in the converter class
  // and treat them accordingly in the new space.
  CMLSettingClass* settingClass;

  settingClass = MOB_NULL;
  while(mobNextKeyObject(converterClass, cml_Key(CML_CONVERTER_CLASS_SUBS_SETTING), &settingClass)){
    // This setting must be removed. Don't add it to the new space.
  }

  settingClass = MOB_NULL;
  while(mobNextKeyObject(converterClass, cml_Key(CML_CONVERTER_CLASS_EQUS_SETTING), &settingClass)){
    // The settings must be equal in both colorspaces. Take the source one
    // in case the goal space is different, in which case this converter
    // will maybe fail eventually. It is nontheless possible that it might not
    // fail. For example when a later converter unit alts the same setting
    // again or subs and later adds the setting.
    CMLSetting* srcsetting = cml_GetColorspaceSetting(srcspace, settingClass);
    cml_SetColorspaceSetting(newspace, settingClass, srcsetting);
  }

  settingClass = MOB_NULL;
  while(mobNextKeyObject(converterClass, cml_Key(CML_CONVERTER_CLASS_ALTS_SETTING), &settingClass)){
    // The setting must be available in both colorspaces but can be different.
    // Take the goal setting.
    CMLSetting* goalsetting = cml_GetColorspaceSetting(goalspace, settingClass);
    if(!goalsetting){
      // The goal colorspace does not define this setting. This can happen if
      // the goal space is still some converters away and the current setting
      // is just a temporary setting. We therefore are assuming one.
      goalsetting = cml_GetSettingClassDefaultColorspaceSetting(settingClass);
    }
    cml_SetColorspaceSetting(newspace, settingClass, goalsetting);
  }
  
  settingClass = MOB_NULL;
  while(mobNextKeyObject(converterClass, cml_Key(CML_CONVERTER_CLASS_ADDS_SETTING), &settingClass)){
    // This setting needs to be added to the space. As we will not find it in
    // src, we might find it in goal.
    CMLSetting* goalsetting = cml_GetColorspaceSetting(goalspace, settingClass);
    if(!goalsetting){
      // The goal colorspace does not define this setting. This can happen if
      // the goal space is still some converters away and the current setting
      // is just a temporary setting. We therefore are assuming one.
      goalsetting = cml_GetSettingClassDefaultColorspaceSetting(settingClass);
    }
    cml_SetColorspaceSetting(newspace, settingClass, goalsetting);
  }
  
  // Converter Settings (CON) are not handeled by this function as converter
  // settings are stored in the converters, not the colorspaces.
  
  return newspace;
}




CML_API CMLInt cmlGetColorspaceStorageSize(CMLColorspace* colorspace){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_COLORSPACE_OBJECT), colorspace))
    cmlError("cmlGetColorspaceStorageSize", "Given MOB is not a Colorspace\n");
  #endif
  
  const CMLColorspaceClass* colorspaceClass = cml_GetColorspaceClass(colorspace);
  return cml_GetColorspaceClassStorageSize(colorspaceClass);
}






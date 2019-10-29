
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.



// //////////////////////////////////
// CONTEXT
// //////////////////////////////////




CML_HIDDEN CML_INLINE MOB* cml_Key(CML_KeyID key){
  #ifndef NDEBUG
  if(key >= CML_OBJECT_KEYS_COUNT)
    cmlError("cml_Key", "Given Key ID does not exist.\n");
  #endif
  return cmlc->objectKeys[key];
}



CML_HIDDEN CML_INLINE MOBUnitID cml_Unit(CML_UnitID unit){
  #ifndef NDEBUG
  if(unit >= CML_INFORMATION_UNITS_COUNT)
    cmlError("cml_Unit", "Given Unit ID does not exist.\n");
  #endif
  return cmlc->informationUnits[unit];
}



CML_HIDDEN CML_INLINE void cml_BOOTSTRAPRegisterColorspaceType(CMLColorspaceType desiredcolorspaceType, const char* name, CMLColorspaceValenceDefiner valencedefiner){
  CMLColorspaceType returnedcolorspaceType = cmlRegisterColorspaceType(name, valencedefiner);
  #ifndef NDEBUG
    if(returnedcolorspaceType != desiredcolorspaceType){
      cmlCrash("cml_BOOTSTRAPRegisterColorspaceType", "Fatal error: Bootstrapping failed. Colorspace has wrong enumeration value.");
      exit(1);
    }
  #else
    CML_UNUSED(desiredcolorspaceType);
    CML_UNUSED(returnedcolorspaceType);
  #endif
}



CML_HIDDEN CML_INLINE void cml_BOOTSTRAPRegisterColorspaceSettingClass(CMLSettingID desiredsettingClassid, const char* name, CMLColorspaceSettingConstructor defaultconstructor){
  CMLSettingID returnedsettingClassid = cmlRegisterColorspaceSettingClass(name, defaultconstructor);
  #ifndef NDEBUG
    if(returnedsettingClassid != desiredsettingClassid){
      cmlCrash("cml_BOOTSTRAPRegisterColorspaceSettingClass", "Fatal error: Bootstrapping failed. Setting class has wrong enumeration value.");
      exit(1);
    }
  #else
    CML_UNUSED(desiredsettingClassid);
    CML_UNUSED(returnedsettingClassid);
  #endif
}



CML_HIDDEN CML_INLINE void cml_BOOTSTRAPRegisterEncoding(CMLEncoding desiredencoding){
  CMLEncoding returnedencoding = cmlRegisterEncoding();
  #ifndef NDEBUG
    if(returnedencoding != desiredencoding){
      cmlCrash("cml_BOOTSTRAPRegisterEncoding", "Fatal error: Bootstrapping failed. Encoding has wrong enumeration value.");
      exit(1);
    }
  #else
    CML_UNUSED(desiredencoding);
    CML_UNUSED(returnedencoding);
  #endif
}



CML_HIDDEN CML_INLINE void cml_BOOTSTRAPRegisterConverterSettingClass(CMLSettingID desiredsettingClassid, const char* name, CMLConverterSettingConstructor defaultconstructor){
  CMLSettingID returnedsettingClassid = cmlRegisterConverterSettingClass(name, defaultconstructor);
  #ifndef NDEBUG
    if(returnedsettingClassid != desiredsettingClassid){
      cmlCrash("cml_BOOTSTRAPRegisterColorspaceSettingClass", "Fatal error: Bootstrapping failed. Setting class has wrong enumeration value.");
      exit(1);
    }
  #else
    CML_UNUSED(desiredsettingClassid);
    CML_UNUSED(returnedsettingClassid);
  #endif
}



CML_HIDDEN CML_INLINE CMLColorspaceAbstract* cml_GetContextColorspaceAbstract(CMLColorspaceType colorspaceType){
  CMLInt abstractscount = (CMLInt)naGetStackCount(&(cmlc->colorspaceabstracts));
  if((CMLInt)colorspaceType >= abstractscount){
    #ifndef NDEBUG
      cmlError("cml_GetContextColorspaceAbstract", "Colorspace type not registered.");
    #endif
    return CML_NULL;
  }
  return NA_NULL;  // todo
//  return *(CMLColorspaceAbstract**)naGetGrowingSpaceMutableElement(&(cmlc->colorspaceabstracts), colorspaceType);
}



CML_HIDDEN CML_INLINE CMLMOBEncoding* cml_GetContextEncodingMOB(CMLEncoding encoding){
  CMLInt encodingscount = (CMLInt)naGetStackCount(&(cmlc->encodings));
  if((CMLInt)encoding >= encodingscount){
    #ifndef NDEBUG
      cmlError("cml_GetContextEncodingMOB", "Encoding not registered.");
    #endif
    return CML_NULL;
  }else{
  return NA_NULL;  // todo
//    return *(CMLMOBEncoding**)naGetGrowingSpaceMutableElement(&(cmlc->encodings), encoding);
  }
}



CML_HIDDEN CML_INLINE CMLSettingClass* cml_GetContextSettingClass(CMLSettingID settingClassID){
  CMLInt classescount = (CMLInt)naGetStackCount(&(cmlc->settingClasses));
  if((CMLInt)settingClassID >= classescount){
    #ifndef NDEBUG
      cmlError("cml_GetContextSettingClass", "Setting class not registered.");
    #endif
    return CML_NULL;
  }else{
  return NA_NULL;  // todo
//    return *(CMLSettingClass**)naGetGrowingSpaceMutableElement(&(cmlc->settingClasses), settingClassID);
  }
}


// //////////////////////////////////
// COLORSPACE ABSTRACT
// //////////////////////////////////


CML_HIDDEN CML_INLINE void cml_DestroyColorspaceAbstract(CMLColorspaceAbstract* colorspaceabstract){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_COLORSPACE_ABSTRACT_OBJECT), colorspaceabstract))
    cmlError("cml_DestroyColorspaceAbstract", "Given MOB is not a Colorspace abstract class\n");
  #endif
  mobDestroyObject(colorspaceabstract);
}


CML_HIDDEN CML_INLINE CMLInt cml_GetColorspaceAbstractComponentsCount(CMLColorspaceAbstract* colorspaceabstract){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_COLORSPACE_ABSTRACT_OBJECT), colorspaceabstract))
    cmlError("cml_DestroyColorspaceAbstract", "Given MOB is not a Colorspace abstract class\n");
  #endif
  return (CMLInt)mobCountKeyValues(colorspaceabstract, cml_Key(CML_COLORSPACE_ABSTRACT_COMPONENT));
}


CML_HIDDEN CML_INLINE CMLInt cml_GetColorspaceAbstractMainComponentIndex(CMLColorspaceAbstract* colorspaceabstract){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_COLORSPACE_ABSTRACT_OBJECT), colorspaceabstract))
    cmlError("cml_DestroyColorspaceAbstract", "Given MOB is not a Colorspace abstract class\n");
  #endif
  return (CMLInt)*mobKeyInt(colorspaceabstract, cml_Key(CML_COLORSPACE_ABSTRACT_MAIN_COMPONENT_INDEX));
}


CML_HIDDEN CML_INLINE CMLComponent* cml_GetColorspaceAbstractComponent(CMLColorspaceAbstract* colorspaceabstract, CMLInt indx){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_COLORSPACE_ABSTRACT_OBJECT), colorspaceabstract))
    cmlError("cml_DestroyColorspaceAbstract", "Given MOB is not a Colorspace abstract class\n");
  #endif
  return mobGetKeyObjectWithIndex(colorspaceabstract, cml_Key(CML_COLORSPACE_ABSTRACT_COMPONENT), indx);
}


CML_HIDDEN CML_INLINE CMLColorspaceType cml_GetColorspaceAbstractType(CMLColorspaceAbstract* colorspaceabstract){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_COLORSPACE_ABSTRACT_OBJECT), colorspaceabstract))
    cmlError("cml_GetColorspaceAbstractType", "Given MOB is not an abstract Colorspace class\n");
  #endif
  return *(CMLColorspaceType*)mobKeyEnum(colorspaceabstract, cml_Key(CML_COLORSPACE_ABSTRACT_TYPE));
}


CML_HIDDEN CML_INLINE NAString* cml_GetColorspaceAbstractName(CMLColorspaceAbstract* colorspaceabstract){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_COLORSPACE_ABSTRACT_OBJECT), colorspaceabstract))
    cmlError("cml_GetColorspaceAbstractType", "Given MOB is not an abstract Colorspace class\n");
  #endif
  return mobKeyString(colorspaceabstract, cml_Key(CML_COLORSPACE_ABSTRACT_NAME));
}



// //////////////////////////////////
// COLORSPACE CLASS
// //////////////////////////////////


CML_HIDDEN CML_INLINE void cml_DestroyColorspaceClass(CMLColorspaceClass* colorspaceClass){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_COLORSPACE_CLASS_OBJECT), colorspaceClass))
    cmlError("cml_DestroyColorspaceClass", "Given MOB is not a Colorspace class\n");
  #endif
  mobDestroyObject(colorspaceClass);
}


CML_HIDDEN CML_INLINE NAString* cml_GetColorspaceClassName(const CMLColorspaceClass* colorspaceClass){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_COLORSPACE_CLASS_OBJECT), colorspaceClass))
    cmlError("cml_GetColorspaceClassName", "Given MOB is not a Colorspace class\n");
  #endif
  CMLColorspaceAbstract* colorspaceabstract = cml_GetColorspaceClassAbstract(colorspaceClass);
  return cml_GetColorspaceAbstractName(colorspaceabstract);
}


CML_HIDDEN CML_INLINE CMLColorspaceAbstract* cml_GetColorspaceClassAbstract(const CMLColorspaceClass* colorspaceClass){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_COLORSPACE_CLASS_OBJECT), colorspaceClass))
    cmlError("cml_GetColorspaceClassName", "Given MOB is not a Colorspace class\n");
  #endif
  return mobGetKeyObject(colorspaceClass, cml_Key(CML_COLORSPACE_ABSTRACT));
}


CML_HIDDEN CML_INLINE CMLEncoding cml_GetColorspaceClassEncoding(const CMLColorspaceClass* colorspaceClass){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_COLORSPACE_CLASS_OBJECT), colorspaceClass))
    cmlError("cml_GetColorspaceClassEncoding", "Given MOB is not a Colorspace class\n");
  #endif
  CMLColorspaceAbstract* colorspaceabstract = cml_GetColorspaceClassAbstract(colorspaceClass);
  const CMLMOBEncoding* encodingMOB = mobGetKey(colorspaceabstract, colorspaceClass);
  return (CMLEncoding)mobConstEnum(encodingMOB);
}


CML_HIDDEN CML_INLINE CMLComponent* cml_GetColorspaceClassComponent(const CMLColorspaceClass* colorspaceClass, CMLInt indx){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_COLORSPACE_CLASS_OBJECT), colorspaceClass))
    cmlError("cml_GetColorspaceClassEncoding", "Given MOB is not a Colorspace class\n");
  #endif
  CMLColorspaceAbstract* colorspaceabstract = cml_GetColorspaceClassAbstract(colorspaceClass);
  return cml_GetColorspaceAbstractComponent(colorspaceabstract, indx);
}


CML_HIDDEN CML_INLINE CMLMinMaxComponentFunction cml_GetColorspaceClassMinFunction(const CMLColorspaceClass* colorspaceClass){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_COLORSPACE_CLASS_OBJECT), colorspaceClass))
    cmlError("cml_GetColorspaceClassEncoding", "Given MOB is not a Colorspace class\n");
  #endif
  CMLMinMaxComponentFunction fun;
  mobGetKeyUnitValue(colorspaceClass, cml_Key(CML_COLORSPACE_CLASS_MIN_COMPONENT_FUNCTION), cml_Unit(CML_UNIT_COLORSPACE_COMPONENT_MINMAX_FUNCTION), &fun);
  return fun;
}


CML_HIDDEN CML_INLINE CMLMinMaxComponentFunction cml_GetColorspaceClassMaxFunction(const CMLColorspaceClass* colorspaceClass){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_COLORSPACE_CLASS_OBJECT), colorspaceClass))
    cmlError("cml_GetColorspaceClassEncoding", "Given MOB is not a Colorspace class\n");
  #endif
  CMLMinMaxComponentFunction fun;
  mobGetKeyUnitValue(colorspaceClass, cml_Key(CML_COLORSPACE_CLASS_MAX_COMPONENT_FUNCTION), cml_Unit(CML_UNIT_COLORSPACE_COMPONENT_MINMAX_FUNCTION), &fun);
  return fun;
}



// //////////////////////////////////
// COLORSPACE
// //////////////////////////////////


CML_HIDDEN CML_INLINE const CMLColorspaceClass* cml_GetColorspaceClass(const CMLColorspace* colorspace){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_COLORSPACE_OBJECT), colorspace))
    cmlError("cml_GetColorspaceClass", "Given MOB is not a Colorspace\n");
  #endif
  return mobGetObjectParent(colorspace);
}



CML_HIDDEN CML_INLINE CMLSetting* cml_GetColorspaceSetting(CMLColorspace* colorspace, CMLSettingClass* settingClass){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_COLORSPACE_OBJECT), colorspace))
    cmlError("cml_GetColorspaceSetting", "Given MOB is not a Colorspace\n");
  #endif
  return mobGetKeyObject(colorspace, settingClass);
}



CML_HIDDEN CML_INLINE void cml_SetColorspaceSetting(CMLColorspace* colorspace, CMLSettingClass* settingClass, CMLSetting* setting){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_COLORSPACE_OBJECT), colorspace))
    cmlError("cml_SetColorspaceSetting", "Given MOB is not a Colorspace\n");
  if(!setting)
    cmlError("cml_SetColorspaceSetting", "setting should not be null");
  #endif
  mobSetKeyObject(colorspace, settingClass, setting, MOB_FALSE);
}





// //////////////////////////////////
// SETTING
// //////////////////////////////////


CML_HIDDEN CML_INLINE CMLSetting* cml_GetSettingClassDefaultColorspaceSetting(CMLSettingClass* settingClass){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_SETTING_CLASS_OBJECT), settingClass))
    cmlError("cml_GetSettingClassDefaultConverterSetting", "Given MOB is not a setting class\n");
  #endif
  CMLColorspaceSettingConstructor constructor;
  mobGetKeyUnitValue(settingClass, cml_Key(CML_COLORSPACE_SETTING_CLASS_CONSTRUCTOR), cml_Unit(CML_UNIT_COLORSPACE_SETTING_CONSTRUCTOR), &constructor);
  return constructor();
}



CML_HIDDEN CML_INLINE CMLSetting* cml_GetSettingClassDefaultConverterSetting(CMLSettingClass* settingClass, CMLColorspace* dstspace, CMLColorspace* srcspace){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_SETTING_CLASS_OBJECT), settingClass))
    cmlError("cml_GetSettingClassDefaultConverterSetting", "Given MOB is not a setting class\n");
  if(!mobEqual(cml_Key(CML_COLORSPACE_OBJECT), dstspace))
    cmlError("cml_GetSettingClassDefaultConverterSetting", "Given MOB is not a Colorspace\n");
  if(!mobEqual(cml_Key(CML_COLORSPACE_OBJECT), srcspace))
    cmlError("cml_GetSettingClassDefaultConverterSetting", "Given MOB is not a Colorspace\n");
  #endif
  CMLConverterSettingConstructor constructor;
  mobGetKeyUnitValue(settingClass, cml_Key(CML_CONVERTER_SETTING_CLASS_CONSTRUCTOR), cml_Unit(CML_UNIT_CONVERTER_SETTING_CONSTRUCTOR), &constructor);
  return constructor(dstspace, srcspace);
}



// //////////////////////////////////
// COMPONENT
// //////////////////////////////////



CML_HIDDEN CML_INLINE NAString* cml_GetComponentName(CMLComponent* component){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_COMPONENT_OBJECT), component))
    cmlError("cml_GetComponentName", "Given MOB is not a Component\n");
  #endif
  return mobKeyString(component, cml_Key(CML_COMPONENT_NAME));
}



CML_HIDDEN CML_INLINE CMLComponentType cml_GetComponentType(CMLComponent* component){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_COMPONENT_OBJECT), component))
    cmlError("cml_GetComponentType", "Given MOB is not a Component\n");
  #endif
  return *(CMLComponentType*)mobKeyEnum(component, cml_Key(CML_COMPONENT_TYPE));
}



CML_HIDDEN CML_INLINE CMLInt cml_GetComponentSize(CMLComponent* component){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_COMPONENT_OBJECT), component))
    cmlError("cml_GetComponentType", "Given MOB is not a Component\n");
  #endif
  CMLComponentType type = cml_GetComponentType(component);
  switch(type){
  case CML_COMPONENT_CARTESIAN:
  case CML_COMPONENT_RADIAL:
  case CML_COMPONENT_ANGULAR:
    return sizeof(float);
    break;
  case CML_COMPONENT_FUNCTION:
    return sizeof(CMLMOBFunction*);
    break;
  }
}



// //////////////////////////////////
// CONVERTER CLASS
// //////////////////////////////////



CML_HIDDEN CML_INLINE CMLColorspaceClass* cml_GetConverterClassDstColorspaceClass(CMLConverterClass* converterClass){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_CONVERTER_CLASS_OBJECT), converterClass))
    cmlError("cml_GetConverterClassDstColorspaceClass", "Given MOB is not a Colorspace class\n");
  #endif
  return mobGetKeyObject(converterClass, cml_Key(CML_CONVERTER_CLASS_DST_COLORSPACE_CLASS));
}



CML_HIDDEN CML_INLINE CMLColorspaceClass* cml_GetConverterClassSrcColorspaceClass(CMLConverterClass* converterClass){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_CONVERTER_CLASS_OBJECT), converterClass))
    cmlError("cml_GetConverterClassSrcColorspaceClass", "Given MOB is not a Colorspace class\n");
  #endif
  return mobGetKeyObject(converterClass, cml_Key(CML_CONVERTER_CLASS_SRC_COLORSPACE_CLASS));
}


CML_HIDDEN CML_INLINE CMLConverterEvaluator cml_GetConverterClassEvaluator(const CMLConverterClass* converterClass){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_CONVERTER_CLASS_OBJECT), converterClass))
    cmlError("cml_GetConverterClassEvaluator", "Given MOB is not a Colorspace class\n");
  #endif
  CMLConverterEvaluator fun;
  mobGetKeyUnitValue(converterClass, cml_Key(CML_CONVERTER_CLASS_EVALUATOR), cml_Unit(CML_UNIT_CONVERTER_EVALUATOR), &fun);
  return fun;
}



CML_HIDDEN CML_INLINE CMLConverterSBEvaluator cml_GetConverterClassEvaluatorSB(const CMLConverterClass* converterClass){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_CONVERTER_CLASS_OBJECT), converterClass))
    cmlError("cml_GetConverterClassEvaluatorSB", "Given MOB is not a Colorspace class\n");
  #endif
  CMLConverterSBEvaluator fun;
  mobGetKeyUnitValue(converterClass, cml_Key(CML_CONVERTER_CLASS_EVALUATOR_SB), cml_Unit(CML_UNIT_CONVERTER_EVALUATOR_SB), &fun);
  return fun;
}



CML_HIDDEN CML_INLINE CMLBool cml_HasConverterClassEquSetting(const CMLConverterClass* converterClass, const CMLSettingClass* settingClass){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_SETTING_CLASS_OBJECT), settingClass))
    cmlError("cml_HasConverterClassEquSetting", "Given MOB is not a SettingClass\n");
  #endif
  return mobHasKeyObjectValue(converterClass, cml_Key(CML_CONVERTER_CLASS_EQUS_SETTING), settingClass);
}



CML_HIDDEN CML_INLINE CMLBool cml_HasConverterClassAltSetting(const CMLConverterClass* converterClass, const CMLSettingClass* settingClass){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_SETTING_CLASS_OBJECT), settingClass))
    cmlError("cml_HasConverterClassAltSetting", "Given MOB is not a SettingClass\n");
  #endif
  return mobHasKeyObjectValue(converterClass, cml_Key(CML_CONVERTER_CLASS_ALTS_SETTING), settingClass);
}



CML_HIDDEN CML_INLINE CMLBool cml_HasConverterClassAddSetting(const CMLConverterClass* converterClass, const CMLSettingClass* settingClass){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_SETTING_CLASS_OBJECT), settingClass))
    cmlError("cml_HasConverterClassAddSetting", "Given MOB is not a SettingClass\n");
  #endif
  return mobHasKeyObjectValue(converterClass, cml_Key(CML_CONVERTER_CLASS_ADDS_SETTING), settingClass);
}



CML_HIDDEN CML_INLINE CMLBool cml_HasConverterClassSubSetting(const CMLConverterClass* converterClass, const CMLSettingClass* settingClass){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_SETTING_CLASS_OBJECT), settingClass))
    cmlError("cml_HasConverterClassSubSetting", "Given MOB is not a SettingClass\n");
  #endif
  return mobHasKeyObjectValue(converterClass, cml_Key(CML_CONVERTER_CLASS_SUBS_SETTING), settingClass);
}



CML_HIDDEN CML_INLINE CMLBool cml_HasConverterClassConSetting(const CMLConverterClass* converterClass, const CMLSettingClass* settingClass){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_SETTING_CLASS_OBJECT), settingClass))
    cmlError("cml_HasConverterClassConSetting", "Given MOB is not a SettingClass\n");
  #endif
  return mobHasKeyObjectValue(converterClass, cml_Key(CML_CONVERTER_CLASS_CONS_SETTING), settingClass);
}



CML_HIDDEN CML_INLINE void cml_AddConverterClassEquSetting(CMLConverterClass* converterClass, CMLSettingClass* settingClass){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_CONVERTER_CLASS_OBJECT), converterClass))
    cmlError("cml_AddConverterClassAddSetting", "Given MOB is not a Converter class\n");
  if(!mobEqual(cml_Key(CML_SETTING_CLASS_OBJECT), settingClass))
    cmlError("cml_AddConverterClassAddSetting", "Given MOB is not a Setting class\n");
  #endif
  mobSetKeyObject(converterClass, cml_Key(CML_CONVERTER_CLASS_EQUS_SETTING), settingClass, MOB_TRUE);

  MOB* dstspaceclass = cml_GetConverterClassDstColorspaceClass(converterClass);
  cml_AddColorspaceClassRequiredSetting(dstspaceclass, settingClass);

  MOB* srcspaceclass = cml_GetConverterClassSrcColorspaceClass(converterClass);
  cml_AddColorspaceClassRequiredSetting(srcspaceclass, settingClass);
}



CML_HIDDEN CML_INLINE void cml_AddConverterClassAddSetting(CMLConverterClass* converterClass, CMLSettingClass* settingClass){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_CONVERTER_CLASS_OBJECT), converterClass))
    cmlError("cml_AddConverterClassAddSetting", "Given MOB is not a Converter class\n");
  if(!mobEqual(cml_Key(CML_SETTING_CLASS_OBJECT), settingClass))
    cmlError("cml_AddConverterClassAddSetting", "Given MOB is not a Setting class\n");
  #endif
  mobSetKeyObject(converterClass, cml_Key(CML_CONVERTER_CLASS_ADDS_SETTING), settingClass, MOB_TRUE);

  CMLColorspaceClass* dstspaceclass = cml_GetConverterClassDstColorspaceClass(converterClass);
  cml_AddColorspaceClassRequiredSetting(dstspaceclass, settingClass);
}      



CML_HIDDEN CML_INLINE void cml_AddConverterClassSubSetting(CMLConverterClass* converterClass, CMLSettingClass* settingClass){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_CONVERTER_CLASS_OBJECT), converterClass))
    cmlError("cml_AddConverterClassAddSetting", "Given MOB is not a Converter class\n");
  if(!mobEqual(cml_Key(CML_SETTING_CLASS_OBJECT), settingClass))
    cmlError("cml_AddConverterClassAddSetting", "Given MOB is not a Setting class\n");
  #endif
  mobSetKeyObject(converterClass, cml_Key(CML_CONVERTER_CLASS_SUBS_SETTING), settingClass, MOB_TRUE);
  
  MOB* srcspaceclass = cml_GetConverterClassSrcColorspaceClass(converterClass);
  cml_AddColorspaceClassRequiredSetting(srcspaceclass, settingClass);
}



CML_HIDDEN CML_INLINE void cml_AddConverterClassAltSetting(CMLConverterClass* converterClass, CMLSettingClass* settingClass){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_CONVERTER_CLASS_OBJECT), converterClass))
    cmlError("cml_AddConverterClassAddSetting", "Given MOB is not a Converter class\n");
  if(!mobEqual(cml_Key(CML_SETTING_CLASS_OBJECT), settingClass))
    cmlError("cml_AddConverterClassAddSetting", "Given MOB is not a Setting class\n");
  #endif
  mobSetKeyObject(converterClass, cml_Key(CML_CONVERTER_CLASS_ALTS_SETTING), settingClass, MOB_TRUE);

  MOB* dstspaceclass = cml_GetConverterClassDstColorspaceClass(converterClass);
  cml_AddColorspaceClassRequiredSetting(dstspaceclass, settingClass);
  
  MOB* srcspaceclass = cml_GetConverterClassSrcColorspaceClass(converterClass);
  cml_AddColorspaceClassRequiredSetting(srcspaceclass, settingClass);
}



CML_HIDDEN CML_INLINE void cml_AddConverterClassConSetting(CMLConverterClass* converterClass, CMLSettingClass* settingClass){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_CONVERTER_CLASS_OBJECT), converterClass))
    cmlError("cml_AddConverterClassAddSetting", "Given MOB is not a Converter class\n");
  if(!mobEqual(cml_Key(CML_SETTING_CLASS_OBJECT), settingClass))
    cmlError("cml_AddConverterClassAddSetting", "Given MOB is not a Setting class\n");
  #endif
  mobSetKeyObject(converterClass, cml_Key(CML_CONVERTER_CLASS_CONS_SETTING), settingClass, MOB_TRUE);
  
  CMLConverterUnit* converterUnit = CML_NULL;
  while(mobNextSubKeyObject(converterClass, cml_Key(CML_CONVERTER_UNIT_OBJECT), &converterUnit)){
    CMLColorspace* dstspace = cml_GetConverterUnitDstColorspace(converterUnit);
    CMLColorspace* srcspace = cml_GetConverterUnitSrcColorspace(converterUnit);
    CMLSetting* newsetting = cml_GetSettingClassDefaultConverterSetting(settingClass, dstspace, srcspace);
    mobSetKeyObject(converterUnit, settingClass, newsetting, MOB_FALSE);
  }
  
}




// //////////////////////////////////
// CONVERTER UNIT
// //////////////////////////////////


CML_HIDDEN CML_INLINE CMLSetting* cml_GetConverterUnitSetting(CMLConverterUnit* converterUnit, CMLSettingClass* settingClass){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_CONVERTER_UNIT_OBJECT), converterUnit))
    cmlError("cml_AddConverterClassAddSetting", "Given MOB is not a Converter unit\n");
  if(!mobEqual(cml_Key(CML_SETTING_CLASS_OBJECT), settingClass))
    cmlError("cml_AddConverterClassAddSetting", "Given MOB is not a Setting class\n");
  #endif
  return mobGetKeyObject(converterUnit, settingClass);
}



CML_HIDDEN CML_INLINE CMLColorspace* cml_GetConverterUnitDstColorspace(CMLConverterUnit* converterUnit){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_CONVERTER_UNIT_OBJECT), converterUnit))
    cmlError("cml_AddConverterClassAddSetting", "Given MOB is not a Converter unit\n");
  #endif
  return mobGetKeyObject(converterUnit, cml_Key(CML_CONVERTER_UNIT_DST_COLORSPACE));
}



CML_HIDDEN CML_INLINE CMLColorspace* cml_GetConverterUnitSrcColorspace(CMLConverterUnit* converterUnit){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_CONVERTER_UNIT_OBJECT), converterUnit))
    cmlError("cml_AddConverterClassAddSetting", "Given MOB is not a Converter unit\n");
  #endif
  return mobGetKeyObject(converterUnit, cml_Key(CML_CONVERTER_UNIT_SRC_COLORSPACE));
}



CML_HIDDEN CML_INLINE const CMLConverterClass* cml_GetConverterUnitClass(const CMLConverterUnit* converterUnit){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_CONVERTER_UNIT_OBJECT), converterUnit))
    cmlError("cml_AddConverterClassAddSetting", "Given MOB is not a Converter unit\n");
  #endif
  return mobGetObjectParent(converterUnit);
}



// //////////////////////////////////
// COLOR
// //////////////////////////////////



CML_HIDDEN CML_INLINE CMLColorspace* cml_GetColorColorspace(CMLColor* color){
  return mobGetKeyObject(color, cml_Key(CML_COLOR_COLORSPACE));
}


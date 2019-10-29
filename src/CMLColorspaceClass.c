
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.


#include "CML.h"
#include "CMLColorMachineState.h"
#include "NAStack.h"
#include "NAString.h"



CML_HIDDEN CMLColorspaceClass* cml_CreateColorspaceClass(CMLColorspaceAbstract* colorspaceabstract, CMLMinMaxComponentFunction minfunction, CMLMinMaxComponentFunction maxfunction){
  CMLColorspaceClass* newcolorspaceClass = mobCreateObject(cml_Key(CML_COLORSPACE_CLASS_OBJECT));
  mobSetKeyObject(newcolorspaceClass, cml_Key(CML_COLORSPACE_ABSTRACT), colorspaceabstract, MOB_FALSE);
  mobSetKeyUnitValue(newcolorspaceClass, cml_Key(CML_COLORSPACE_CLASS_MIN_COMPONENT_FUNCTION), cml_Unit(CML_UNIT_COLORSPACE_COMPONENT_MINMAX_FUNCTION), &minfunction);
  mobSetKeyUnitValue(newcolorspaceClass, cml_Key(CML_COLORSPACE_CLASS_MAX_COMPONENT_FUNCTION), cml_Unit(CML_UNIT_COLORSPACE_COMPONENT_MINMAX_FUNCTION), &maxfunction);
  return newcolorspaceClass;
}





CML_HIDDEN void cml_DebugColorspaceClass(CMLColorspaceClass* colorspaceClass){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_COLORSPACE_CLASS_OBJECT), colorspaceClass))
    cmlError("cml_DebugColorspaceClass", "Given MOB is not a Colorspace class\n");
  #endif
  printf("--- Debugging colorspace class:\n");
  if(!mobEqual(cml_Key(CML_COLORSPACE_CLASS_OBJECT), colorspaceClass)){
    printf("Given MOB is not a ColorspaceClass\n");
    return;
  }
  CMLColorspaceType colorspaceType = cml_GetColorspaceAbstractType(cml_GetColorspaceClassAbstract(colorspaceClass));
  NAString* colorspaceClassname = cml_GetColorspaceClassName(colorspaceClass);
  CMLInt componentscount = cmlGetComponentsCount(colorspaceType);
  printf("Colorspace Class \"%s\" with ID %d\n", naGetStringUTF8Pointer(colorspaceClassname), colorspaceType);
  printf("Storing %d valence components\n", componentscount);

  printf("Requires the following settings:\n");
  CMLSettingClass* settingClass = MOB_NULL;
  while(mobNextKeyObject(colorspaceClass, cml_Key(CML_COLORSPACE_CLASS_REQUIRED_SETTING_CLASSES), &settingClass)){
    CMLSettingID settingClassID = cml_GetSettingClassID(settingClass);
    NAString* settingClassname = cml_GetSettingClassName(settingClass);
    printf("\"%s\" with ID %d\n", naGetStringUTF8Pointer(settingClassname), settingClassID);
  }
  printf("---\n");
}




CML_HIDDEN void cml_AddColorspaceClassRequiredSetting(CMLColorspaceClass* colorspaceClass, CMLSettingClass* settingClass){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_COLORSPACE_CLASS_OBJECT), colorspaceClass))
    cmlError("cml_AddColorspaceClassRequiredSetting", "Given MOB is not a Colorspace class\n");
  #endif
  
  // If this colorspace class has already defined the given setting class as
  // required, simply return.
  if(mobHasKeyObjectValue(colorspaceClass, cml_Key(CML_COLORSPACE_CLASS_REQUIRED_SETTING_CLASSES), settingClass)){return;}
  // Otherwise, store the given setting class as required.
  mobSetKeyObject(colorspaceClass, cml_Key(CML_COLORSPACE_CLASS_REQUIRED_SETTING_CLASSES), settingClass, MOB_TRUE);
  
  // Store a default setting for all colorspaces of this colorspace class.
  MOB* curspace = MOB_NULL;
  while(mobNextSubKeyObject(colorspaceClass, cml_Key(CML_COLORSPACE_OBJECT), &curspace)){
    if(!cml_GetColorspaceSetting(curspace, settingClass)){
      CMLSetting* defaultsettingobj = cml_GetSettingClassDefaultColorspaceSetting(settingClass);
      #ifndef NDEBUG
        if(!defaultsettingobj)
          cmlError("cml_AddColorspaceClassRequiredSetting", "Fatal error. The setting default is not implemented. Application will likely crash.\n");
      #endif
      cml_SetColorspaceSetting(curspace, settingClass, defaultsettingobj);
    }
  }
  
  // Then go through all converters from and to this colorspace class and
  // set the get methods.
  CMLConverterClass* converterClass;
  
  converterClass = MOB_NULL;
  while(mobNextKeyObject(colorspaceClass, cml_Key(CML_COLORSPACE_CLASS_OUT_CONVERTER_CLASSES), &converterClass)){
    const MOB* settingmethod = mobGetKey(converterClass, settingClass);
    if(!settingmethod){
      // We assume the converter class to equ the setting.
      cml_AddConverterClassEquSetting(converterClass, settingClass);
    }else{
      if(mobEqual(settingmethod, cml_Key(CML_CONVERTER_CLASS_ADDS_SETTING))){
        #ifndef NDEBUG
          cmlError("cml_AddColorspaceClassRequiredSetting", "Clash: Previous out converter unit defined src colorspace class to not have the setting, but the current converter unit defines otherwise.");
        #endif
      }
    }
  }


  converterClass = MOB_NULL;
  while(mobNextKeyObject(colorspaceClass, cml_Key(CML_COLORSPACE_CLASS_IN_CONVERTER_CLASSES), &converterClass)){
    const MOB* settingmethod = mobGetKey(converterClass, settingClass);
    if(!settingmethod){
      // We assume the converter class to equ the setting.
      cml_AddConverterClassEquSetting(converterClass, settingClass);
    }else{
      if(mobEqual(settingmethod, cml_Key(CML_CONVERTER_CLASS_SUBS_SETTING))){
        #ifndef NDEBUG
          cmlError("cml_AddColorspaceClassRequiredSetting", "Clash: Previous in converter unit defined dst colorspace class to not have the setting, but the current converter unit defines otherwise.");
        #endif
      }
    }
  }
}






CML_API void cmlRegisterMinMaxComponentFunctions(CMLColorspaceType colorspaceType, CMLEncoding encoding, CMLMinMaxComponentFunction minfunction, CMLMinMaxComponentFunction maxfunction){
  CMLColorspaceAbstract* colorspaceabstract = cml_GetContextColorspaceAbstract(colorspaceType);
  CMLMOBEncoding* encodingMOB = cml_GetContextEncodingMOB(encoding);
  
  CMLColorspaceClass* newcolorspaceClass = cml_CreateColorspaceClass(colorspaceabstract, minfunction, maxfunction);
  mobSetKeyObject(colorspaceabstract, encodingMOB, newcolorspaceClass, MOB_FALSE);

  if((encoding != CML_ENCODING_NORM)){
    // Add any converters from and to norm
    #ifndef NDEBUG
    CMLColorspaceClass* normedcolorspaceClass = mobGetKeyObject(colorspaceabstract, cml_GetContextEncodingMOB(CML_ENCODING_NORM));
    if(!normedcolorspaceClass){
      cmlError("cml_GetContextColorspaceClass", "No normed colorspace available. Bad thing!");
      return;
    }
    #endif

    // Create converters for the new encoding
    cmlRegisterConverterUnit(colorspaceType, encoding, colorspaceType, CML_ENCODING_NORM, CML_NULL, cml_NormtoDefault, CML_NULL);
    cmlRegisterConverterUnit(colorspaceType, CML_ENCODING_NORM, colorspaceType, encoding, CML_NULL, cml_DefaulttoNorm, CML_NULL);
  }

}



CML_HIDDEN CMLInt cml_GetColorspaceClassStorageSize(const CMLColorspaceClass* colorspaceClass){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_COLORSPACE_CLASS_OBJECT), colorspaceClass))
    cmlError("cmlGetColorspaceStorageSize", "Given MOB is not a Colorspace\n");
  #endif
  
  CMLColorspaceAbstract* colorspaceabstract = cml_GetColorspaceClassAbstract(colorspaceClass);
  CMLInt totalsize = 0;
  
  CMLComponent* component = MOB_NULL;
  while(mobNextKeyObject(colorspaceabstract, cml_Key(CML_COLORSPACE_ABSTRACT_COMPONENT), &component)){
    totalsize += cml_GetComponentSize(component); // todo: dependent on encoding
  }
  return totalsize;
}



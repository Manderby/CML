
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

#include "CML.h"
#include "StateMachine/CMLColorMachineState.h"



CML_HIDDEN void cml_DebugConverterClass(CMLConverterClass* converterClass){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_CONVERTER_CLASS_OBJECT), converterClass))
    cmlError("cml_DebugColorspace", "Given MOB is not a Colorspace\n");
  #endif
  printf("-- Converter Class:\n");
  NAString* srcname = cml_GetColorspaceClassName(cml_GetConverterClassSrcColorspaceClass(converterClass));
  NAString* dstname = cml_GetColorspaceClassName(cml_GetConverterClassDstColorspaceClass(converterClass));
  printf("Converting from %s to %s\n", naGetStringConstUTF8Pointer(srcname), naGetStringConstUTF8Pointer(dstname));
  printf("--\n");
}



CML_HIDDEN void cmlRegisterConverterUnit(CMLColorspaceType dstcolorspaceType, CMLEncoding dstencoding, CMLColorspaceType srccolorspaceType, CMLEncoding srcencoding, CMLConverterRequester requester, CMLConverterEvaluator evaluator, CMLConverterSBEvaluator evaluatorSB){
  CMLColorspaceClass* dstcolorspaceClass = cml_GetContextColorspaceClass(dstcolorspaceType, dstencoding);
  CMLColorspaceClass* srccolorspaceClass = cml_GetContextColorspaceClass(srccolorspaceType, srcencoding);

  // Create a new converter class.
  CMLConverterClass* converterClass = mobCreateObject(cml_Key(CML_CONVERTER_CLASS_OBJECT));

  // Store the colorspace classes.
  mobSetKeyObject(converterClass, cml_Key(CML_CONVERTER_CLASS_DST_COLORSPACE_CLASS), dstcolorspaceClass, MOB_FALSE);
  mobSetKeyObject(converterClass, cml_Key(CML_CONVERTER_CLASS_SRC_COLORSPACE_CLASS), srccolorspaceClass, MOB_FALSE);

  // Store the function pointers.
  mobSetKeyUnitValue(converterClass, cml_Key(CML_CONVERTER_CLASS_REQUESTER), cml_Unit(CML_UNIT_CONVERTER_REQUESTER), &requester);
  mobSetKeyUnitValue(converterClass, cml_Key(CML_CONVERTER_CLASS_EVALUATOR), cml_Unit(CML_UNIT_CONVERTER_EVALUATOR), &evaluator);
  mobSetKeyUnitValue(converterClass, cml_Key(CML_CONVERTER_CLASS_EVALUATOR_SB), cml_Unit(CML_UNIT_CONVERTER_EVALUATOR_SB), &evaluatorSB);

  // Make the src and dst colorspace classes aware of the new converter class.
  mobSetKeyObject(srccolorspaceClass, cml_Key(CML_COLORSPACE_CLASS_OUT_CONVERTER_CLASSES), converterClass, MOB_TRUE);
  mobSetKeyObject(dstcolorspaceClass, cml_Key(CML_COLORSPACE_CLASS_IN_CONVERTER_CLASSES), converterClass, MOB_TRUE);
  
  // todo: converterClass object should be released as it is now stored as a
  // connection between two colorspace classes.
  
  // Test the converter unit to gather information about the required settings:
  if(cmlc->curobject){
    printf("Nested registration. Aborting");
    return;
  }

  CMLColorspace* dstspace = cmlCreateColorspace(dstcolorspaceType, dstencoding);
  CMLColorspace* srcspace = cmlCreateColorspace(srccolorspaceType, srcencoding);
  CMLConverterUnit* converterUnit = cml_CreateConverterUnit(converterClass, dstspace, srcspace);
  cmlc->curobject = converterUnit;
  if(requester){requester();}
  evaluator(CML_NULL, CML_NULL, 0);
  cmlc->curobject = CML_NULL;
  cmlDestroyColorspace(dstspace);
  cmlDestroyColorspace(srcspace);
  cml_DestroyConverterUnit(converterUnit);
 
  // Now, all settings somehow required by the converter unit are set. But some
  // settings may not have been touched by the converter unit although they are
  // required for both colorspaces. We therefore attach all non-used settings
  // of one colorspace class to the other as a required setting. In both ways.
  cml_AddConverterClassRequiredSettingsAsEqu(converterClass, dstcolorspaceClass);
  cml_AddConverterClassRequiredSettingsAsEqu(converterClass, srccolorspaceClass);
}





CML_API void cml_AddConverterClassRequiredSettingsAsEqu(CMLConverterClass* converterClass, CMLColorspaceClass* colorspaceClass){
  CMLSettingClass* requiredsettingClass = MOB_NULL;
  while(mobNextKeyObject(colorspaceClass, cml_Key(CML_COLORSPACE_CLASS_REQUIRED_SETTING_CLASSES), &requiredsettingClass)){
    if(!cml_HasConverterClassSettingTreatment(converterClass, requiredsettingClass)){
      cml_AddConverterClassEquSetting(converterClass, requiredsettingClass);
    }
  }
}



CML_API NABool cml_HasConverterClassSettingTreatment(const CMLConverterClass* converterClass, const CMLSettingClass* settingClass){
  if(cml_HasConverterClassAddSetting(converterClass, settingClass)){return NA_TRUE;}
  if(cml_HasConverterClassSubSetting(converterClass, settingClass)){return NA_TRUE;}
  if(cml_HasConverterClassEquSetting(converterClass, settingClass)){return NA_TRUE;}
  if(cml_HasConverterClassAltSetting(converterClass, settingClass)){return NA_TRUE;}
  if(cml_HasConverterClassConSetting(converterClass, settingClass)){return NA_TRUE;}
  return NA_FALSE;
}



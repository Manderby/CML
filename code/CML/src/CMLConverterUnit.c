
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

#include "CML.h"
#include "StateMachine/CMLColorMachineState.h"
#include "NARandom.h"
#include "NADateTime.h"




CML_HIDDEN CMLConverterUnit* cml_CreateConverterUnit(CMLConverterClass* converterClass, CMLColorspace* dstspace, CMLColorspace* srcspace){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_COLORSPACE_OBJECT), dstspace))
    cmlError("cml_CreateConverterUnit", "Given dst space is not a Colorspace\n");
  if(!mobEqual(cml_Key(CML_COLORSPACE_OBJECT), srcspace))
    cmlError("cml_CreateConverterUnit", "Given src space is not a Colorspace\n");
  #endif

  CMLConverterUnit* converterUnit = mobCreateSubObject(converterClass, cml_Key(CML_CONVERTER_UNIT_OBJECT));
  mobSetKeyObject(converterUnit, cml_Key(CML_CONVERTER_UNIT_DST_COLORSPACE), dstspace, MOB_FALSE);
  mobSetKeyObject(converterUnit, cml_Key(CML_CONVERTER_UNIT_SRC_COLORSPACE), srcspace, MOB_FALSE);
  *(CMLError*)mobKeyEnum(converterUnit, cml_Key(CML_ERROR)) = CML_NO_ERROR;

  // Add all required con settings for this converter unit
  CMLSettingClass* requiredsettingClass = MOB_NULL;
  while(mobNextKeyObject(converterClass, cml_Key(CML_CONVERTER_CLASS_CONS_SETTING), &requiredsettingClass)){
    CMLSetting* newsetting = cml_GetSettingClassDefaultConverterSetting(requiredsettingClass, dstspace, srcspace);
    mobSetKeyObject(converterUnit, requiredsettingClass, newsetting, MOB_FALSE);
  }

  return converterUnit;
}



CML_HIDDEN void cml_DestroyConverterUnit(CMLConverterUnit* converterUnit){
  mobDestroyObject(converterUnit);
}




CML_HIDDEN float cml_BenchmarkConverterUnit(CMLConverterUnit* converterUnit){
  CMLColorspace* dstspace = cml_GetConverterUnitDstColorspace(converterUnit);
  CMLColorspace* srcspace = cml_GetConverterUnitSrcColorspace(converterUnit);
  void* testout = naMalloc(cmlGetColorspaceStorageSize(dstspace) * CML_BENCHMARKCOUNT);
  void* testin = naMalloc(cmlGetColorspaceStorageSize(srcspace) * CML_BENCHMARKCOUNT);

  const CMLConverterClass* converterClass = cml_GetConverterUnitClass(converterUnit);
  CMLConverterEvaluator evaluator = cml_GetConverterClassEvaluator(converterClass);

  CMLColorspaceType srctype = cml_GetColorspaceAbstractType(cml_GetColorspaceClassAbstract(cml_GetColorspaceClass(srcspace)));
  CMLInt componentscount = cmlGetComponentsCount(srctype);
  void* testinptr = testin;
  float* floatptr;
  CMLMOBFunction** functionptr;
  for(CMLInt i=0; i<CML_BENCHMARKCOUNT; i++){
    for(CMLInt c=0; c<componentscount; c++){
      switch(cmlGetComponentType(srctype, c)){
      case CML_COMPONENT_CARTESIAN:
      case CML_COMPONENT_RADIAL:
      case CML_COMPONENT_ANGULAR:
        floatptr = cmlNextMutableFloatComponent(testinptr);
        *floatptr = naUniformRandZEf();
        break;
      case CML_COMPONENT_FUNCTION:
        functionptr = cmlNextMutableFunctionComponent(testinptr);
        *functionptr = cmlCreateIlluminationSpectrum(CML_ILLUMINATION_D_ILLUMINANT, naUniformRandZEf() * 10000.f);
        break;
      }
    }
  }
  
  cmlc->curobject = converterUnit;
  NADateTime start = naMakeDateTimeNow();
  evaluator(testout, testin, CML_BENCHMARKCOUNT);
  NADateTime end = naMakeDateTimeNow();
  cmlc->curobject = CML_NULL;
  
  float cost = naGetDateTimeDifference(&end, &start);
  *mobKeyFloat(converterUnit, cml_Key(CML_CONVERTER_UNIT_COST)) = cost;

  free(testin);
  free(testout);
  return cost;
}



CML_API CMLSetting* cmlRequestConverterSetting(CMLSettingID settingClassID, CMLGetMethod method){
  if(!cmlc->curobject || !mobEqual(cmlc->curobject, cml_Key(CML_CONVERTER_UNIT_OBJECT))){
    printf("You can use this function only during conversion.");
    return CML_NULL;
  }
  CMLConverterUnit* converterUnit = cmlc->curobject;
  CMLSettingClass* settingClass = cml_GetContextSettingClass(settingClassID);

  CMLSetting* setting = cml_GetConverterUnitSetting(converterUnit, settingClass);
  if(!setting){setting = cmlGetConverterSetting(settingClassID, method);}

  return setting;
}



//CML_API CMLSetting* cmlFetchConverterSetting(CMLInt indx){
//  if(!cmlc->curobject || !mobEqual(cmlc->curobject, cml_Key(CML_CONVERTER_UNIT_OBJECT))){
//    printf("You can use this function only during conversion.");
//    return CML_NULL;
//  }
//  CMLConverterUnit* converterUnit = cmlc->curobject;
//}



CML_API CMLSetting* cmlGetConverterSetting(CMLSettingID settingClassID, CMLGetMethod method){
  if(!cmlc->curobject || !mobEqual(cmlc->curobject, cml_Key(CML_CONVERTER_UNIT_OBJECT))){
    printf("You can use this function only during conversion.");
    return CML_NULL;
  }
  CMLConverterUnit* converterUnit = cmlc->curobject;
  CMLConverterClass* converterClass = (CMLConverterClass*)cml_GetConverterUnitClass(converterUnit); // todo: hack
  CMLSettingClass* settingClass = cml_GetContextSettingClass(settingClassID);
  CMLColorspace* dstspace = cml_GetConverterUnitDstColorspace(converterUnit);
  CMLColorspace* srcspace = cml_GetConverterUnitSrcColorspace(converterUnit);

  switch(method){
  case CML_GET_EQU:
    // Both colorspaces are dependent on the setting and must be equal
    if(!cml_HasConverterClassEquSetting(converterClass, settingClass)){
      #ifndef NDEBUG
        if(cml_HasConverterClassSettingTreatment(converterClass, settingClass))
          cmlError("cmlGetConverterSetting", "EQU Setting already handeled by converter but in a different way.");
      #endif
      cml_AddConverterClassEquSetting(converterClass, settingClass);
      cmlSetConverterError(CML_MISSING_SETTING_DURING_CONVERSION);
    }
    return cml_GetColorspaceSetting(srcspace, settingClass);
    break;
    
  case CML_GET_ADD:
    // Only the dst space is dependent on the setting.
    if(!cml_HasConverterClassAddSetting(converterClass, settingClass)){
      #ifndef NDEBUG
        if(cml_HasConverterClassSettingTreatment(converterClass, settingClass))
          cmlError("cmlGetConverterSetting", "ADD Setting already handeled by converter but in a different way.");
      #endif
      cml_AddConverterClassAddSetting(converterClass, settingClass);
      cmlSetConverterError(CML_MISSING_SETTING_DURING_CONVERSION);
    }
    return cml_GetColorspaceSetting(dstspace, settingClass);
    break;
    
  case CML_GET_SUB:
    // Only the src space is dependent on the setting.
    if(!cml_HasConverterClassSubSetting(converterClass, settingClass)){
      #ifndef NDEBUG
        if(cml_HasConverterClassSettingTreatment(converterClass, settingClass))
          cmlError("cmlGetConverterSetting", "SUB Setting already handeled by converter but in a different way.");
      #endif
      cml_AddConverterClassSubSetting(converterClass, settingClass);
      cmlSetConverterError(CML_MISSING_SETTING_DURING_CONVERSION);
    }
    return cml_GetColorspaceSetting(srcspace, settingClass);
    break;
    
  case CML_GET_ALTDST:
    // Both colorspaces are dependent on the setting but can be unequal
    if(!cml_HasConverterClassAltSetting(converterClass, settingClass)){
      #ifndef NDEBUG
        if(cml_HasConverterClassSettingTreatment(converterClass, settingClass))
          cmlError("cmlGetConverterSetting", "ALTDST Setting already handeled by converter but in a different way.");
      #endif
      cml_AddConverterClassAltSetting(converterClass, settingClass);
      cmlSetConverterError(CML_MISSING_SETTING_DURING_CONVERSION);
    }
    return cml_GetColorspaceSetting(dstspace, settingClass);
    break;

  case CML_GET_ALTSRC:
    // Both colorspaces are dependent on the setting but can be unequal
    if(!cml_HasConverterClassAltSetting(converterClass, settingClass)){
      #ifndef NDEBUG
        if(cml_HasConverterClassSettingTreatment(converterClass, settingClass))
          cmlError("cmlGetConverterSetting", "ALTSRC Setting already handeled by converter but in a different way.");
      #endif
      cml_AddConverterClassAltSetting(converterClass, settingClass);
      cmlSetConverterError(CML_MISSING_SETTING_DURING_CONVERSION);
    }
    return cml_GetColorspaceSetting(srcspace, settingClass);
    break;

  case CML_GET_CONVERT:
    // The setting must be present in the CMLConverterUnit
    if(!cml_HasConverterClassConSetting(converterClass, settingClass)){
      #ifndef NDEBUG
        if(cml_HasConverterClassSettingTreatment(converterClass, settingClass))
          cmlError("cmlGetConverterSetting", "CONVERT Setting already handeled by converter but in a different way.");
      #endif
      cml_AddConverterClassConSetting(converterClass, settingClass);
      cmlSetConverterError(CML_MISSING_SETTING_DURING_CONVERSION);
    }
    return cml_GetConverterUnitSetting(converterUnit, settingClass);
    break;
    
  default:
    #ifndef NDEBUG
      cmlError("cmlGetConverterSetting", "Critical error: Undefined method.");
    #endif
    cmlSetConverterError(CML_WRONG_GET_METHOD);
    return CML_NULL;
    break;
  }
}




CML_API CMLError cmlGetConverterError(){
  if(!cmlc->curobject || !mobEqual(cmlc->curobject, cml_Key(CML_CONVERTER_UNIT_OBJECT))){
    printf("You can use this function only during conversion.");
    return CML_NO_ERROR;
  }
  CMLConverterUnit* converterUnit = cmlc->curobject;
  return *(CMLError*)mobKeyEnum(converterUnit, cml_Key(CML_ERROR));
}



CML_API void cmlSetConverterError(CMLError errornum){
  if(!cmlc->curobject || !mobEqual(cmlc->curobject, cml_Key(CML_CONVERTER_UNIT_OBJECT))){
    printf("You can use this function only during conversion.");
  }
  CMLConverterUnit* converterUnit = cmlc->curobject;
  *(CMLError*)mobKeyEnum(converterUnit, cml_Key(CML_ERROR)) = errornum;
}



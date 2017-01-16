
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.


#include "CML.h"
#include "CMLColorMachineState.h"



CML_HIDDEN CMLColorspaceAbstract* cml_CreateColorspaceAbstract(CMLColorspaceType type, const char* name){
  CMLColorspaceAbstract* colorspaceabstract = mobCreateObject(cml_Key(CML_COLORSPACE_ABSTRACT_OBJECT));
  *(CMLColorspaceType*)mobKeyEnum(colorspaceabstract, cml_Key(CML_COLORSPACE_ABSTRACT_TYPE)) = type;
  naCreateStringWithUTF8CStringLiteral(mobKeyString(colorspaceabstract, cml_Key(CML_COLORSPACE_ABSTRACT_NAME)), name);
  return colorspaceabstract;
}



CML_API CMLColorspaceType cmlRegisterColorspaceType(const char* name, CMLColorspaceValenceDefiner valencedefiner){
  // todo: check if the componentType and label is valid
  CMLColorspaceType newcolorspaceType;
  
  if(cmlc->curobject){
    printf("Other operation in progress. Aborting current registration.\n");
    newcolorspaceType = -1;
  }else{
    // The new colorspace class ID is just the next integer number of the array
    // of colorspace abstracts registered in this context.
    newcolorspaceType = naGetGrowingSpaceCount(&(cmlc->colorspaceabstracts));
    CMLColorspaceAbstract* newabstract = cml_CreateColorspaceAbstract(newcolorspaceType, name);
    *mobKeyInt(newabstract, cml_Key(CML_COLORSPACE_ABSTRACT_MAIN_COMPONENT_INDEX)) = 0;

    // Call the valence definer as a registration process.
    cmlc->curobject = newabstract;
    valencedefiner();
    cmlc->curobject = CML_NULL;
    
    // Check if there is at least one component stored.
    MOBInt componentscount = cml_GetColorspaceAbstractComponentsCount(newabstract);
    if(!componentscount){
      #ifndef NDEBUG
        cmlError("cmlRegisterColorspaceType", "The colorspace abstract does not store any valences.");
      #endif
      cml_DestroyColorspaceAbstract(newabstract);
      newcolorspaceType = -1;
    }else{
      // If everything is ok, add the class to the registered classes
      CMLColorspaceAbstract** registeredelement = naNewGrowingSpaceElement(&(cmlc->colorspaceabstracts));
      *registeredelement = newabstract;
      
      // Artificially create a normed colorspace
      cmlRegisterMinMaxComponentFunctions(newcolorspaceType, CML_ENCODING_NORM, CML_NULL, CML_NULL);
    }
  }
  return newcolorspaceType;
}



CML_API void cmlAddComponent(CMLComponentType componentType, const char* label){
  if(!cmlc->curobject || !mobEqual(cmlc->curobject, cml_Key(CML_COLORSPACE_ABSTRACT_OBJECT))){
    #ifndef NDEBUG
      cmlError("cmlAddComponent", "You can use this function only while registering a new colorspace type.");
    #endif
    return;
  }
  // todo: check if the componentType and label are valid
  
  CMLComponent* component;
  component = mobCreateObject(cml_Key(CML_COMPONENT_OBJECT));
  *(CMLComponentType*)mobKeyEnum(component, cml_Key(CML_COMPONENT_TYPE)) = componentType;
  naCreateStringWithUTF8CStringLiteral(mobKeyString(component, cml_Key(CML_COMPONENT_NAME)), label);

  mobSetKeyObject(cmlc->curobject, cml_Key(CML_COLORSPACE_ABSTRACT_COMPONENT), component, MOB_TRUE);
}



CML_API void cmlSetMainComponent(CMLInt indx){
  if(!cmlc->curobject || !mobEqual(cmlc->curobject, cml_Key(CML_COLORSPACE_ABSTRACT_OBJECT))){
    #ifndef NDEBUG
      cmlError("cmlSetMainComponent", "You can use this function only while registering a new colorspace class.");
    #endif
    return;
  }
  // todo: check if the index is valid
  *mobKeyInt(cmlc->curobject, cml_Key(CML_COLORSPACE_ABSTRACT_MAIN_COMPONENT_INDEX)) = indx;
}



CML_API CMLInt cmlGetComponentsCount(CMLColorspaceType colorspaceType){
  // todo: check if the type is valid
  CMLColorspaceAbstract* colorspaceabstract = cml_GetContextColorspaceAbstract(colorspaceType);
  return cml_GetColorspaceAbstractComponentsCount(colorspaceabstract);
}


CML_API CMLInt cmlGetMainComponentIndex(CMLColorspaceType colorspaceType){
  CMLColorspaceAbstract* colorspaceabstract = cml_GetContextColorspaceAbstract(colorspaceType);
  return cml_GetColorspaceAbstractMainComponentIndex(colorspaceabstract);
}


CML_API CMLComponentType cmlGetComponentType(CMLColorspaceType colorspaceType, CMLInt indx){
  // todo: check if the type is valid
  CMLColorspaceAbstract* colorspaceabstract = cml_GetContextColorspaceAbstract(colorspaceType);
  CMLComponent* component = cml_GetColorspaceAbstractComponent(colorspaceabstract, indx);
  return cml_GetComponentType(component);
}


CML_API const NAString* cmlGetComponentName(CMLColorspaceType colorspaceType, CMLInt indx){
  // todo: check if the type is valid
  CMLColorspaceAbstract* colorspaceabstract = cml_GetContextColorspaceAbstract(colorspaceType);
  CMLComponent* component = cml_GetColorspaceAbstractComponent(colorspaceabstract, indx);
  return cml_GetComponentName(component);
}




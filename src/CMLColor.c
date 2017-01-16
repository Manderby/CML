
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

#include "CML.h"
#include "CMLColorMachineState.h"


CML_API CMLColor* cmlCreateColorspaceColor(CMLColorspace* colorspace){
  CMLColorspaceType colorspacetype = cmlGetColorspaceType(colorspace);
  CMLInt componentscount = cmlGetComponentsCount(cmlGetColorspaceType(colorspace));
  CMLComponentType componentType = cmlGetComponentType(cmlGetColorspaceType(colorspace), cmlGetMainComponentIndex(colorspacetype));
  // todo: how to handle mixed color components?
  
  CMLColor* newcolor;
  
  switch(componentType){
  case CML_COMPONENT_CARTESIAN:
  case CML_COMPONENT_RADIAL:
  case CML_COMPONENT_ANGULAR:
    newcolor = mobCreateFloatArray(componentscount);
    break;
  case CML_COMPONENT_FUNCTION:
    newcolor = mobCreateArray(componentscount);
    break;
  }
  mobSetKeyObject(newcolor, cml_Key(CML_COLOR_COLORSPACE), colorspace, MOB_FALSE);
  return newcolor;
}





CML_API CMLColor* cmlCreateRadiometric(CMLColorspace* colorspace, CMLMOBFunction* spectrum){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_COLORSPACE_OBJECT), colorspace))
    cmlError("cmlCreateRadiometric", "Given MOB is not a Colorspace\n");
  #endif

  CMLColorspaceType colorspaceType = cml_GetColorspaceAbstractType(cml_GetColorspaceClassAbstract(cml_GetColorspaceClass(colorspace)));
  if(colorspaceType != CML_Radiometric){
    #ifndef NDEBUG
      cmlError("cmlCreateRadiometric", "Given colorspace is not a Radiometric space");
    #endif
    return CML_NULL;
  }
  CMLColor* newcolor = cmlCreateColorspaceColor(colorspace);
  mobSetArrayObject(newcolor, 0, spectrum);
  return newcolor;
}


CML_API CMLColor* cmlCreateXYZ(CMLColorspace* colorspace, float X, float Y, float Z){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_COLORSPACE_OBJECT), colorspace))
    cmlError("cmlCreateXYZ", "Given MOB is not a Colorspace\n");
  #endif

  CMLColorspaceType colorspaceType = cml_GetColorspaceAbstractType(cml_GetColorspaceClassAbstract(cml_GetColorspaceClass(colorspace)));
  if(colorspaceType != CML_XYZ){
    #ifndef NDEBUG
      cmlError("cmlCreateXYZ", "Given colorspace is not a XYZ space");
    #endif
    return CML_NULL;
  }
  CMLColor* newcolor = cmlCreateColorspaceColor(colorspace);
  CMLVec3 storage = {X, Y, Z};
  cmlFillColorWithBuf(newcolor, storage);
  return newcolor;
}


CML_API CMLColor* cmlCreateNormXYZ(CMLColorspace* colorspace, float X, float Y, float Z){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_COLORSPACE_OBJECT), colorspace))
    cmlError("cmlCreateNormXYZ", "Given MOB is not a Colorspace\n");
  #endif

  CMLColorspaceType colorspaceType = cml_GetColorspaceAbstractType(cml_GetColorspaceClassAbstract(cml_GetColorspaceClass(colorspace)));
  if(colorspaceType != CML_XYZ){
    #ifndef NDEBUG
      cmlError("cmlCreateNormXYZ", "Given colorspace is not a XYZ space");
    #endif
    return CML_NULL;
  }
  CMLColor* newcolor = cmlCreateColorspaceColor(colorspace);
  CMLVec3 storage = {X, Y, Z};
  cmlFillColorWithBuf(newcolor, storage);
  return newcolor;
}


CML_API CMLColor* cmlCreateYxy(CMLColorspace* colorspace, float Y, float x, float y){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_COLORSPACE_OBJECT), colorspace))
    cmlError("cmlCreateYxy", "Given MOB is not a Colorspace\n");
  #endif

  CMLColorspaceType colorspaceType = cml_GetColorspaceAbstractType(cml_GetColorspaceClassAbstract(cml_GetColorspaceClass(colorspace)));
  if(colorspaceType != CML_Yxy){
    #ifndef NDEBUG
      cmlError("cmlCreateYxy", "Given colorspace is not an Yxy space");
    #endif
    return CML_NULL;
  }
  CMLColor* newcolor = cmlCreateColorspaceColor(colorspace);
  CMLVec3 storage = {Y, x, y};
  cmlFillColorWithBuf(newcolor, storage);
  return newcolor;
}


CML_API CMLColor* cmlCreateYupvp(CMLColorspace* colorspace, float Y, float up, float vp){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_COLORSPACE_OBJECT), colorspace))
    cmlError("cmlCreateYupvp", "Given MOB is not a Colorspace\n");
  #endif

  CMLColorspaceType colorspaceType = cml_GetColorspaceAbstractType(cml_GetColorspaceClassAbstract(cml_GetColorspaceClass(colorspace)));
  if(colorspaceType != CML_Yupvp){
    #ifndef NDEBUG
      cmlError("cmlCreateYupvp", "Given colorspace is not an Yupvp space");
    #endif
    return CML_NULL;
  }
  CMLColor* newcolor = cmlCreateColorspaceColor(colorspace);
  CMLVec3 storage = {Y, up, vp};
  cmlFillColorWithBuf(newcolor, storage);
  return newcolor;
}


CML_API CMLColor* cmlCreateYuv(CMLColorspace* colorspace, float Y, float u, float v){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_COLORSPACE_OBJECT), colorspace))
    cmlError("cmlCreateYuv", "Given MOB is not a Colorspace\n");
  #endif

  CMLColorspaceType colorspaceType = cml_GetColorspaceAbstractType(cml_GetColorspaceClassAbstract(cml_GetColorspaceClass(colorspace)));
  if(colorspaceType != CML_Yuv){
    #ifndef NDEBUG
      cmlError("cmlCreateYupvp", "Given colorspace is not an Yuv space");
    #endif
    return CML_NULL;
  }
  CMLColor* newcolor = cmlCreateColorspaceColor(colorspace);
  CMLVec3 storage = {Y, u, v};
  cmlFillColorWithBuf(newcolor, storage);
  return newcolor;
}


CML_API CMLColor* cmlCreateLuv(CMLColorspace* colorspace, float L, float u, float v){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_COLORSPACE_OBJECT), colorspace))
    cmlError("cmlCreateLuv", "Given MOB is not a Colorspace\n");
  #endif

  CMLColorspaceType colorspaceType = cml_GetColorspaceAbstractType(cml_GetColorspaceClassAbstract(cml_GetColorspaceClass(colorspace)));
  if(colorspaceType != CML_Luv){
    #ifndef NDEBUG
      cmlError("cmlCreateYupvp", "Given colorspace is not an Luv space");
    #endif
    return CML_NULL;
  }
  CMLColor* newcolor = cmlCreateColorspaceColor(colorspace);
  CMLVec3 storage = {L, u, v};
  cmlFillColorWithBuf(newcolor, storage);
  return newcolor;
}


CML_API CMLColor* cmlCreateLab(CMLColorspace* colorspace, float L, float a, float b){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_COLORSPACE_OBJECT), colorspace))
    cmlError("cmlCreateLab", "Given MOB is not a Colorspace\n");
  #endif

  CMLColorspaceType colorspaceType = cml_GetColorspaceAbstractType(cml_GetColorspaceClassAbstract(cml_GetColorspaceClass(colorspace)));
  if(colorspaceType != CML_Lab){
    #ifndef NDEBUG
      cmlError("cmlCreateYupvp", "Given colorspace is not an Lab space");
    #endif
    return CML_NULL;
  }
  CMLColor* newcolor = cmlCreateColorspaceColor(colorspace);
  CMLVec3 storage = {L, a, b};
  cmlFillColorWithBuf(newcolor, storage);
  return newcolor;
}


CML_API CMLColor* cmlCreateLch(CMLColorspace* colorspace, float L, float c, float h){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_COLORSPACE_OBJECT), colorspace))
    cmlError("cmlCreateLch", "Given MOB is not a Colorspace\n");
  #endif

  CMLColorspaceType colorspaceType = cml_GetColorspaceAbstractType(cml_GetColorspaceClassAbstract(cml_GetColorspaceClass(colorspace)));
  if(colorspaceType != CML_Lch){
    #ifndef NDEBUG
      cmlError("cmlCreateYupvp", "Given colorspace is not an Lch space");
    #endif
    return CML_NULL;
  }
  CMLColor* newcolor = cmlCreateColorspaceColor(colorspace);
  CMLVec3 storage = {L, c, h};
  cmlFillColorWithBuf(newcolor, storage);
  return newcolor;
}


CML_API CMLColor* cmlCreateRGB(CMLColorspace* colorspace, float R, float G, float B){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_COLORSPACE_OBJECT), colorspace))
    cmlError("cmlCreateRGB", "Given MOB is not a Colorspace\n");
  #endif

  CMLColorspaceType colorspaceType = cml_GetColorspaceAbstractType(cml_GetColorspaceClassAbstract(cml_GetColorspaceClass(colorspace)));
  if(colorspaceType != CML_RGB){
    #ifndef NDEBUG
      cmlError("cmlCreateRGB", "Given colorspace is not an RGB space");
    #endif
    return CML_NULL;
  }
  CMLColor* newcolor = cmlCreateColorspaceColor(colorspace);
  CMLVec3 storage = {R, G, B};
  cmlFillColorWithBuf(newcolor, storage);
  return newcolor;
}


CML_API CMLColor* cmlCreateHSV(CMLColorspace* colorspace, float H, float S, float V){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_COLORSPACE_OBJECT), colorspace))
    cmlError("cmlCreateHSV", "Given MOB is not a Colorspace\n");
  #endif

  CMLColorspaceType colorspaceType = cml_GetColorspaceAbstractType(cml_GetColorspaceClassAbstract(cml_GetColorspaceClass(colorspace)));
  if(colorspaceType != CML_HSV){
    #ifndef NDEBUG
      cmlError("cmlCreateHSV", "Given colorspace is not an HSV space");
    #endif
    return CML_NULL;
  }
  CMLColor* newcolor = cmlCreateColorspaceColor(colorspace);
  CMLVec3 storage = {H, S, V};
  cmlFillColorWithBuf(newcolor, storage);
  return newcolor;
}


CML_API CMLColor* cmlCreateHSL(CMLColorspace* colorspace, float H, float S, float L){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_COLORSPACE_OBJECT), colorspace))
    cmlError("cmlCreateHSL", "Given MOB is not a Colorspace\n");
  #endif

  CMLColorspaceType colorspaceType = cml_GetColorspaceAbstractType(cml_GetColorspaceClassAbstract(cml_GetColorspaceClass(colorspace)));
  if(colorspaceType != CML_HSL){
    #ifndef NDEBUG
      cmlError("cmlCreateHSL", "Given colorspace is not an HSL space");
    #endif
    return CML_NULL;
  }
  CMLColor* newcolor = cmlCreateColorspaceColor(colorspace);
  CMLVec3 storage = {H, S, L};
  cmlFillColorWithBuf(newcolor, storage);
  return newcolor;
}


CML_API CMLColor* cmlCreateYCbCr(CMLColorspace* colorspace, float Y, float Cb, float Cr){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_COLORSPACE_OBJECT), colorspace))
    cmlError("cmlCreateYCbCr", "Given MOB is not a Colorspace\n");
  #endif

  CMLColorspaceType colorspaceType = cml_GetColorspaceAbstractType(cml_GetColorspaceClassAbstract(cml_GetColorspaceClass(colorspace)));
  if(colorspaceType != CML_YCbCr){
    #ifndef NDEBUG
      cmlError("cmlCreateYCbCr", "Given colorspace is not an YCbCr space");
    #endif
    return CML_NULL;
  }
  CMLColor* newcolor = cmlCreateColorspaceColor(colorspace);
  CMLVec3 storage = {Y, Cb, Cr};
  cmlFillColorWithBuf(newcolor, storage);
  return newcolor;
}




CML_API void* cmlCreateColorStorage(CMLColor* color){
  CMLColorspace* colorspace = cml_GetColorColorspace(color);
  const CMLColorspaceClass* colorspaceClass = cml_GetColorspaceClass(colorspace);
  CMLColorspaceType colorspaceType = cml_GetColorspaceAbstractType(cml_GetColorspaceClassAbstract(colorspaceClass));
  CMLInt componentscount = cmlGetComponentsCount(cml_GetColorspaceAbstractType(cml_GetColorspaceClassAbstract(colorspaceClass)));
  void* data = naAllocate(cmlGetColorspaceStorageSize(colorspace));
  void* dataptr = data;
  for(CMLInt c=0; c<componentscount; c++){
    switch(cmlGetComponentType(colorspaceType, c)){
    case CML_COMPONENT_CARTESIAN:
    case CML_COMPONENT_RADIAL:
    case CML_COMPONENT_ANGULAR:
      *cmlNextMutableFloatComponent(dataptr) = cmlGetColorFloatComponent(color, c);
      break;
    case CML_COMPONENT_FUNCTION:
      *cmlNextMutableFunctionComponent(dataptr) = mobGetArrayObject(color, c);
      break;
    }
  }
  return data;
}


CML_API void cmlFillColorWithBuf(CMLColor* color, void* buf){
  CMLColorspace* colorspace = cml_GetColorColorspace(color);
  const CMLColorspaceClass* colorspaceClass = cml_GetColorspaceClass(colorspace);
  CMLColorspaceType colorspaceType = cml_GetColorspaceAbstractType(cml_GetColorspaceClassAbstract(colorspaceClass));
  CMLInt componentscount = cmlGetComponentsCount(cml_GetColorspaceAbstractType(cml_GetColorspaceClassAbstract(colorspaceClass)));
//  void* data = naAllocate(cmlGetColorspaceStorageSize(colorspace));
  void* dataptr = buf;
  for(CMLInt c=0; c<componentscount; c++){
    switch(cmlGetComponentType(colorspaceType, c)){
    case CML_COMPONENT_CARTESIAN:
    case CML_COMPONENT_RADIAL:
    case CML_COMPONENT_ANGULAR:
      cmlSetColorFloatComponent(color, c, *cmlNextMutableFloatComponent(dataptr));;
      break;
    case CML_COMPONENT_FUNCTION:
      cmlSetColorFunctionComponent(color, c, *cmlNextMutableFunctionComponent(dataptr));
      break;
    }
  }
}



CML_API CMLColor* cmlCreateColor(CMLColorspace* dstcolorspace, CMLColor* srccolor){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_COLORSPACE_OBJECT), dstcolorspace))
    cmlError("cmlCreateColor", "Given MOB is not a Colorspace\n");
  #endif

  void* srcdata = cmlCreateColorStorage(srccolor);
  
  CMLColorspace* srccolorspace = mobGetKeyObject(srccolor, cml_Key(CML_COLOR_COLORSPACE));
  void* dstdata = naAllocate(cmlGetColorspaceStorageSize(dstcolorspace));

  CMLColor* newcolor = cmlCreateColorspaceColor(dstcolorspace);

  CMLConverter* myconverter = cmlCreateConverter(dstcolorspace, srccolorspace);
  cmlConvert(myconverter, dstdata, srcdata, 1);

  cmlFillColorWithBuf(newcolor, dstdata);

  free(srcdata);
  free(dstdata);

  mobSetKeyObject(newcolor, cml_Key(CML_COLOR_COLORSPACE), dstcolorspace, MOB_FALSE);
  return newcolor;
}


CML_API const void* cmlGetColorData(CMLColor* color){
  return mobConstArrayData(color);
}


CML_API void cmlSetColorFloatComponent(CMLColor* color, CMLInt indx, float value){
  *mobArrayFloat(color, indx) = value;
}


CML_API void cmlSetColorFunctionComponent(CMLColor* color, CMLInt indx, CMLMOBFunction* value){
  mobSetArrayObject(color, indx, value);
}


CML_API float cmlGetColorFloatComponent(CMLColor* color, CMLInt indx){
  return *mobArrayFloat(color, indx);
}

CML_API MOB* cmlGetColorFunctionComponent(CMLColor* color, CMLInt indx){
  MOB* desiredmob = mobGetArrayObject(color, indx);
  return desiredmob;
}


CML_API void cmlDebugColor(CMLColor* color){
  CMLColorspace* colorspace = mobGetKeyObject(color, cml_Key(CML_COLOR_COLORSPACE));
  CMLColorspaceType colorspacetype = cmlGetColorspaceType(colorspace);
  const CMLColorspaceClass* colorspaceClass = cml_GetColorspaceClass(colorspace);
  CMLColorspaceAbstract* colorspaceabstract = cml_GetColorspaceClassAbstract(colorspaceClass);
  const CMLByte* data;
  CMLComponentType componentType = cmlGetComponentType(cmlGetColorspaceType(colorspace), cmlGetMainComponentIndex(colorspacetype));
  switch(componentType){
  case CML_COMPONENT_CARTESIAN:
  case CML_COMPONENT_RADIAL:
  case CML_COMPONENT_ANGULAR:
    data = mobConstArrayData(color);
    break;
  case CML_COMPONENT_FUNCTION:
    data = mobConstArrayObjectData(color);
    break;
  }

  CMLComponent* component = MOB_NULL;
  while(mobNextKeyObject(colorspaceabstract, cml_Key(CML_COLORSPACE_ABSTRACT_COMPONENT), &component)){
    NAString* componentname = cml_GetComponentName(component);
    switch(componentType){
      case CML_COMPONENT_CARTESIAN:
      case CML_COMPONENT_RADIAL:
      case CML_COMPONENT_ANGULAR:
        printf("%s=%f ", naGetStringConstUTF8Pointer(componentname), *((float*)data));
        data += sizeof(float);
        break;
      case CML_COMPONENT_FUNCTION:
        printf("%s=Function ", naGetStringConstUTF8Pointer(componentname));
        data += sizeof(CMLMOBFunction);
        break;
      default:
        #ifndef NDEBUG
          cmlError("cmlDebugColor", "Unknown component type. Can not continue.");
        #endif
        return;
      break;
    }
  }
  printf("\n");
}


CML_API void cmlDestroyColor(CMLColor* color){
  mobDestroyObject(color);
}

CML_API CMLColorspace* cmlGetColorColorspace(CMLColor* color){
  return cml_GetColorColorspace(color);
}



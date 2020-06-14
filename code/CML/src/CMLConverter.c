
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.


#include "CML.h"
#include "StateMachine/CMLColorMachineState.h"
#include "NAHeap.h"
#include "NAList.h"
#include "NAString.h"
#include "NARandom.h"
#include "NADateTime.h"



CML_HIDDEN CMLConverterChainElement* cml_CreateConverterChainElement(CMLColorspace* dstspace){
  CMLConverterChainElement* newelement = naAlloc(CMLConverterChainElement);
  newelement->converterUnit = CML_NULL;
  newelement->dstbuf = CML_NULL;
  newelement->dstspace = dstspace;  // todo: retain
  return newelement;
}



CML_HIDDEN void cml_DestroyConverterChainElement(CMLConverterChainElement* element){
  // todo: release all pointers;
//  cml_DestroyConverterUnit(element->converterUnit);
//  cmlDestroyColorspace(element->dstspace);
  free(element);
}





CML_API CMLConverter* cmlCreateConverter(
                           CMLColorspace* dstspace,
                           CMLColorspace* srcspace){
  #ifndef NDEBUG
  if(!mobEqual(cml_Key(CML_COLORSPACE_OBJECT), dstspace))
    cmlError("cmlCreateConverter", "Given MOB is not a Colorspace\n");
  if(!mobEqual(cml_Key(CML_COLORSPACE_OBJECT), srcspace))
    cmlError("cmlCreateConverter", "Given MOB is not a Colorspace\n");
  #endif
  CMLConverter* converter = naAlloc(CMLConverter);
  converter->cost = 0.f;
  naInitList(&(converter->elements));

  naAddListFirstMutable(&(converter->elements), cml_CreateConverterChainElement(srcspace));
  naAddListLastMutable(&(converter->elements), cml_CreateConverterChainElement(dstspace));

  return converter;
}



CML_API void cmlDestroyConverter(CMLConverter* converter){
  naForeachListMutable(&(converter->elements), (NAMutator)cml_DestroyConverterChainElement);
  naClearList(&(converter->elements));
}




// The converter is expected to have at least two elements. The last
// elements depicts the goal space and the element just before the last ist
// the one element which needs to be connected to the goal.
CML_HIDDEN NABool cml_ConnectConverterChain(CMLConverter* converter, CMLConverterChainElement* dstelement, CMLConverterChainElement* srcelement, CMLInt recursioncount){

  NA_UNUSED(converter);
  NA_UNUSED(dstelement);
  NA_UNUSED(srcelement);
  NA_UNUSED(recursioncount);
//
//  if(recursioncount > 50){
//    #ifndef NDEBUG
//      cmlError("cml_ConnectConverterChain", "Too many recursions.");
//    #endif
//    return CML_FALSE;
//  }
//
//  CMLConverterClass* curconverterClass = MOB_NULL;
//  while(mobNextKeyObject(cml_GetColorspaceClass(srcelement->dstspace), cml_Key(CML_COLORSPACE_CLASS_OUT_CONVERTER_CLASSES), &curconverterClass)){
//    CMLColorspace* newdstspace = cml_CreateColorspaceOfConverterGoal(srcelement->dstspace, curconverterClass, dstelement->dstspace);
//    // Check if the new space equals the goal:
//    if(cml_EqualColorspace(dstelement->dstspace, newdstspace)){
//      dstelement->converterUnit = cml_CreateConverterUnit(curconverterClass, dstelement->dstspace, srcelement->dstspace);
//      cmlDestroyColorspace(newdstspace);
//      return NA_TRUE;
//    }else{
//      // We are not yet at the goal, but maybe we find a way from here...
//
//      // Check if the new space equals one of the previous spaces:
//      CMLBool dump = CML_FALSE;
//      naFirstListElement(&(converter->elements));
//      CMLConverterChainElement* curelement = naGetListMutableContent(&(converter->elements));
//      while(curelement){
//        if(cml_EqualColorspace(newdstspace, curelement->dstspace)){
//          dump = CML_TRUE;
//          break;
//        }
//        naNextListElement(&(converter->elements));
//        curelement = naGetListMutableContent(&(converter->elements));
//      }
//
//      if(!dump){
//        // Temporarily add a new element to the list
//        CMLConverterChainElement* newelement = cml_CreateConverterChainElement(newdstspace);
//        naLastListElement(&(converter->elements));
//        naAddListElementBefore(&(converter->elements), newelement);
//        
//        // Check if the new list can connect till the end.
//        NABool success = cml_ConnectConverterChain(converter, dstelement, newelement, recursioncount+1);
//        if(success){
//          // Add the chain element, converter and the colorspace to the chain.
//          newelement->converterUnit = cml_CreateConverterUnit(curconverterClass, newdstspace, srcelement->dstspace);
//          return NA_TRUE;
//        }else{
//          // Relocate the element within the list (wight have changed) and
//          // remove it.
//          naLastListElement(&(converter->elements));
//          naRemoveListElementPrev(&(converter->elements));
//          
//          cml_DestroyConverterChainElement(newelement);
//        }
//      }
//
//      // Destroy all allocated structures
//      cmlDestroyColorspace(newdstspace);
//    }
//    
//  }
  return NA_FALSE;
}



CML_API void cmlConvertColor(CMLConverter* converter, CMLColor* dstcolor, CMLColor* srccolor){
  CMLBool releaseconverter = CML_FALSE;
  CMLColorspace* dstcolorspace = cmlGetColorColorspace(dstcolor);
  if(!converter){
    converter = cmlCreateConverter(cml_GetColorColorspace(dstcolor), cml_GetColorColorspace(srccolor));
    releaseconverter = CML_TRUE;
  }
  
  void* srcdata = cmlCreateColorStorage(srccolor);
  void* dstdata = naMalloc(cmlGetColorspaceStorageSize(dstcolorspace));

  cmlConvert(converter, dstdata, srcdata, 1);
  cmlFillColorWithBuf(dstcolor, dstdata);

  free(srcdata);
  free(dstdata);
  if(releaseconverter){cmlDestroyConverter(converter);}
}



CML_API void cmlConvert(CMLConverter* converter, CMLInputOutput out, CMLInputOutput in, CMLInt count){
  NA_UNUSED(converter);
  NA_UNUSED(out);
  NA_UNUSED(in);
  NA_UNUSED(count);

//  CMLError error = CML_NO_ERROR;
//  CMLConverterChainElement* cur;
//  CMLInt chaincount;
//
//  naLastListElement(&(converter->elements));
//  CMLConverterChainElement* last = naGetListMutableContent(&(converter->elements));
//  if(!last->converterUnit){
//    error = CML_CONVERSION_NOT_FOUND_YET;
//  }else{
//    last->dstbuf = out;
//    // The last element of the chain will be a dummy element, storing some
//    // dummy converter with a dst colorspace class which equals the src class
//    // of the whole converter.
//
//    // This is the first element of the chain. Do not allocate space here.
//    
//    naFirstListElement(&(converter->elements));
//    cur = naGetListMutableContent(&(converter->elements));
//    cur->dstbuf = (void*)in;  // todo HACK
//    
//    // create all buffers needed.
//    chaincount = (CMLInt)naGetListCount(&(converter->elements));
//    for(CMLInt i=1; i<chaincount - 1; i++){
//      naNextListElement(&(converter->elements));
//      cur = naGetListMutableContent(&(converter->elements));
//      CMLSize colorspacesize = cmlGetColorspaceStorageSize(cml_GetConverterUnitDstColorspace(cur->converterUnit));
//      cur->dstbuf = naMalloc(colorspacesize * count);
//    }
//    
//    // Now, we are at the beginning of the converter chain. Start converting.
//    naFirstListElement(&(converter->elements));
//    cur = naGetListMutableContent(&(converter->elements));
//    CMLConverterChainElement* prev = cur;
//    chaincount = (CMLInt)naGetListCount(&(converter->elements));
//    for(CMLInt i=1; i<chaincount; i++){
//      naNextListElement(&(converter->elements));
//      cur = naGetListMutableContent(&(converter->elements));
//
//      const CMLConverterClass* curconverterClass = cml_GetConverterUnitClass(cur->converterUnit);
//      cmlc->curobject = cur->converterUnit;
//      
//      if(prev->dstbuf == cur->dstbuf){
//        CMLConverterSBEvaluator evaluatorsb = cml_GetConverterClassEvaluatorSB(curconverterClass);
//        evaluatorsb(cur->dstbuf, count);
//      }else{
//        CMLConverterEvaluator evaluator = cml_GetConverterClassEvaluator(curconverterClass);
//        evaluator(cur->dstbuf, prev->dstbuf, count);
//      }
//
//      error = cmlGetConverterError();
//      cmlc->curobject = CML_NULL;
//
//      if(error){break;}
//      prev = cur;
//    }
//
//    // Now, everything is converted. Clean up the buffers.
//    naFirstListElement(&(converter->elements));
//    cur = naGetListMutableContent(&(converter->elements));
//    chaincount = (CMLInt)naGetListCount(&(converter->elements));
//    for(CMLInt i=1; i<chaincount - 1; i++){
//      naNextListElement(&(converter->elements));
//      cur = naGetListMutableContent(&(converter->elements));
//      free(cur->dstbuf);
//      cur->dstbuf = CML_NULL;
//    }
//  }
//    
//  if(error){
//    // Delete all converters and colorspaces of all elements between the first
//    // and last.
//    naFirstListElement(&(converter->elements));
//    naNextListElement(&(converter->elements));
//    cur = naGetListMutableContent(&(converter->elements));
//    chaincount = (CMLInt)naGetListCount(&(converter->elements));
//    for(CMLInt i=1; i<chaincount - 1; i++){
//      cml_DestroyConverterChainElement(naRemoveListElementCurrent(&(converter->elements), NA_TRUE));
//    }
//
//    // Get the first element.
//    naFirstListElement(&(converter->elements));
//    CMLConverterChainElement* firstelement = naGetListMutableContent(&(converter->elements));
//
//    // Delete the converter of the last element.
//    naLastListElement(&(converter->elements));
//    CMLConverterChainElement* lastelement = naGetListMutableContent(&(converter->elements));
//    cml_DestroyConverterUnit(lastelement->converterUnit);
//    lastelement->converterUnit = CML_NULL;
//
//    // Start all over and recompute the evaluation again.
//    CMLBool success = cml_ConnectConverterChain(converter, lastelement, firstelement, 0);
//    if(success){
//      cmlConvert(converter, out, in, count);
//    }else{
//      #ifndef NDEBUG
//        cmlError("cmlConvert", "Unable to convert. No conversion found.\n");
//      #endif
//    }
//    
//  }
}


CML_API void cml_Debug_FinalConverter(CMLConverter* converter){
  NA_UNUSED(converter);
//  printf("--- Debugging Converter:\n");
//  naFirstListElement(&(converter->elements));
//  CMLConverterChainElement* curelement = naGetListMutableContent(&(converter->elements));
//  NAString* converterUnitname = cml_GetColorspaceClassName(cml_GetColorspaceClass(curelement->dstspace));
//  printf("%s", naGetStringUTF8Pointer(converterUnitname));
//  naNextListElement(&(converter->elements));
//  curelement = naGetListMutableContent(&(converter->elements));
//  while(curelement){
//    converterUnitname = cml_GetColorspaceClassName(cml_GetColorspaceClass(curelement->dstspace));
//    float cost = cml_BenchmarkConverterUnit(curelement->converterUnit);
//    printf(" ->(%f) %s", cost, naGetStringUTF8Pointer(converterUnitname));
//    naNextListElement(&(converter->elements));
//    curelement = naGetListMutableContent(&(converter->elements));
//  }
//  
//  printf("\n");
//  naFirstListElement(&(converter->elements));
//  curelement = naGetListMutableContent(&(converter->elements));
//  while(curelement){
//    cml_DebugColorspace(curelement->dstspace);
//    naNextListElement(&(converter->elements));
//    curelement = naGetListMutableContent(&(converter->elements));
//  }
}








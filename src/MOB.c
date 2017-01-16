
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

#include "MOBInternal.h"
#include "NAString.h"
#include "NASystem.h"




// The context pointer
MOBContext* mobc;




// //////////////////////////////
// CONTEXT
// //////////////////////////////



MOBContext* mobActivateContext(MOBContext* context){
  if(context){
    mobc = context;
  }else{
    // If no context is given, create a new one.
    context = (MOBContext*)naAllocate(sizeof(MOBContext));
    mobc = context;
    
    naCreateGrowingSpace(&(context->unitpools), sizeof(MOBPool), 0);
    
    // Bootstrapping: Manually create the cells cell.
    // The cells cell will have cell index 0
    
    MOBPool* curpool;
    
    // Create the cell containing cells
    curpool = naNewGrowingSpaceElement(&(context->unitpools));
    curpool->bytesize = sizeof(MOBCell);
    curpool->curcell = mob_CreateCellCell();
    curpool->firstcell = curpool->curcell;

    // After this, the Cells cell is fully initialized.
        
    // Create the information units
    MOBInt newu;

    newu = mobRegisterUnit(sizeof(MOB), "MOB");
    #ifndef NDEBUG
      if(newu != MOB_UNIT_MOB){mobError("mobActivateContext", "MOB unit has bad number.");}
    #endif

    newu = mobRegisterUnit(sizeof(MOBInt), "Int");
    #ifndef NDEBUG
      if(newu != MOB_UNIT_INT){mobError("mobActivateContext", "Int unit has bad number.");}
    #endif

    newu = mobRegisterUnit(sizeof(float), "Float");
    #ifndef NDEBUG
      if(newu != MOB_UNIT_FLOAT){mobError("mobActivateContext", "Float unit has bad number.");}
    #endif

    newu = mobRegisterUnit(sizeof(NAString), "String");
    #ifndef NDEBUG
      if(newu != MOB_UNIT_STRING){mobError("mobActivateContext", "String unit has bad number.");}
    #endif

    newu = mobRegisterUnit(sizeof(MOBInt), "Enum");
    #ifndef NDEBUG
      if(newu != MOB_UNIT_ENUM){mobError("mobActivateContext", "Enum unit has bad number.");}
    #endif


    newu = mobRegisterUnit(sizeof(MOB), "Array");
    #ifndef NDEBUG
      if(newu != MOB_UNIT_ARRAY){mobError("mobActivateContext", "Array unit has bad number.");}
    #endif




    // Create the keys
    context->keys[MOB_KEY_ARRAY] = mobCreateString("Array");
    context->keys[MOB_KEY_ARRAY_COUNT] = mobCreateString("Array element count");
    context->keys[MOB_KEY_ARRAY_FIRST] = mobCreateString("First element of array");
    context->keys[MOB_KEY_LIST] = mobCreateString("List");
    context->keys[MOB_KEY_LIST_COUNT] = mobCreateString("List element count");
    context->keys[MOB_KEY_LIST_FIRST] = mobCreateString("First element of list");
    context->keys[MOB_KEY_LIST_LAST] = mobCreateString("Last element of list");

  }
  return mobc;
}


MOBContext* mobCurrentContext(void){
  return mobc;
}


void mobDestroyContext(MOBContext* context){
  for(MOBInt i=0; i<MOB_KEYS_COUNT; i++){
    mobDestroyObject(context->keys[i]);
  }
  for(MOBInt i=0; i<naGetGrowingSpaceCount(&(context->unitpools)); i++){
    mob_DestroyUnitPool(mob_getUnitPool(i));
  }
}





// /////////////////////////////////////
// POOL and UNIT
// /////////////////////////////////////

MOBUnitID mobRegisterUnit(MOBInt bytesize, const char* name){
  NA_UNUSED_PARAMETER(name);  // todo
  // todo: check name and duplicates

  #ifndef NDEBUG
    if(bytesize <= 0)
      mobError("mobRegisterUnit", "Typesize invalid");
  #endif
  
  MOBInt newu = naGetGrowingSpaceCount(&(mobc->unitpools));
  MOBPool* newpool = naNewGrowingSpaceElement(&(mobc->unitpools));
  
  newpool->bytesize = bytesize;
  newpool->curcell= mob_CreateCell(newu, MOB_CELL_ELEMENTS_COUNT, MOB_NULL, MOB_FALSE);
  newpool->firstcell = newpool->curcell;

  return newu;
}


MOB_INLINE void mob_DestroyUnitPool(MOBPool* pool){
  MOBCell* curcell = pool->firstcell;
  MOBCell* nextcell;
  while(curcell){
    nextcell = curcell->nextcell;
    mob_DestroyCell(curcell);
    curcell = nextcell;
  }
}


MOB_INLINE MOBPool* mob_getUnitPool(MOBUnitID u){
  #ifndef NDEBUG
    if(u < 0)
      mobError("mob_getUnitPool", "pool index underflow");
    if(u >= naGetGrowingSpaceCount(&(mobc->unitpools)))
      mobError("mob_getUnitPool", "pool index overflow");
  #endif
  return (MOBPool*)naGetGrowingSpaceMutableElement(&(mobc->unitpools), u);
}


MOB_INLINE void mob_addUnitCellWithFreeSpace(MOBCell* cell){
  MOBPool* pool = mob_getUnitPool(cell->u);
  pool->curcell->nextcell = cell;
  pool->curcell = cell;
}


MOB_INLINE void mob_addUnitCellFull(MOBCell* cell){
  MOBPool* pool = mob_getUnitPool(cell->u);
  cell->nextcell = pool->firstcell;
  pool->firstcell = cell;
}


MOB_INLINE MOBCell* mob_getUnitCell(MOBUnitID u){
  return mob_getUnitPool(u)->curcell;
}


MOB_INLINE MOBInt mob_GetUnitByteSize(MOBUnitID u){
  return mob_getUnitPool(u)->bytesize;
}






// //////////////////////////////
// CELL
// //////////////////////////////


MOB_INLINE MOBInt mob_GetCellElementsCount(MOBCell* cell){
  return cell->nextindex;
  // note that this might likely change in the future when cobs are actually
  // recycled.
}


MOB_INLINE COB* mob_GetCellCOBWithIndex(MOBCell* cell, MOBInt indx){
  #ifndef NDEBUG
    if(indx < 0)
      mobError("mob_GetCellCOBWithIndex", "index underflow");
    if(indx >= naGetArrayCount(&(cell->dataarray)))
      mobError("mob_GetCellCOBWithIndex", "index overflow");
  #endif
  return &(cell->cellobjects[indx]);
}


MOB_INLINE void mob_InitCell(MOBCell* cell, MOBUnitID u, MOBInt count, void* buffer, MOBBool ownbuffer){
  if(buffer){
    naCreateArrayWithMutableBuffer(&(cell->dataarray), buffer, mob_GetUnitByteSize(u), count, ownbuffer);
  }else{
    naCreateArrayWithCount(&(cell->dataarray), mob_GetUnitByteSize(u), count, NA_NULL);
  }
  cell->cellobjects = mobAllocate(count * sizeof(COB));
  cell->u = u;
  cell->nextindex = 0;
  cell->nextcell = MOB_NULL;
}


MOB_INLINE void mob_DestroyCell(MOBCell* cell){
  naClearArray(&(cell->dataarray), NA_NULL);
  free(cell->cellobjects);
}


MOB_INLINE MOBCell* mob_CreateCellCell(){
  void* cellcelldata = mobAllocate(MOB_CELL_ELEMENTS_COUNT * sizeof(MOBCell));
  MOBCell* newcell = (MOBCell*)cellcelldata; // addressing the first entry.

  mob_InitCell(newcell, MOB_UNIT_CELL, MOB_CELL_ELEMENTS_COUNT, cellcelldata, NA_TRUE);
  
  // Init the first element. It contains this cell.
  mob_CreateCOBWithCell(newcell);

  return newcell;
}


MOB_INLINE MOBCell* mob_CreateCell(MOBUnitID u, MOBInt count, void* buffer, MOBBool ownbuffer){
  // Note that this function could be done using mob_CreateCOBs(0, 1)->p but it
  // introduces several conditions and hence is much cleaner and faster
  // as a separate function.

  // First, make sure, we can create 1 more cell.
  MOBCell* cellcell = mob_getUnitCell(MOB_UNIT_CELL);
  if(mob_GetCellElementsCount(cellcell) == MOB_CELL_ELEMENTS_COUNT){
    // The current cellcell has no more space. Create a new cellcell.
    cellcell = mob_CreateCellCell();
    // and add that cell to the pool
    mob_addUnitCellWithFreeSpace(cellcell);
  }
  
  MOBCell* newcell = mob_CreateCOBWithCell(cellcell)->p;
  mob_InitCell(newcell, u, count, buffer, ownbuffer);

  return newcell;
}





// //////////////////////////////
// COB
// //////////////////////////////


MOB_INLINE COB* mob_CreateCOBWithCell(MOBCell* cell){
  #ifndef NDEBUG
    if(mob_GetCellElementsCount(cell) + 1 > MOB_CELL_ELEMENTS_COUNT)
      mobError("mob_CreateCOBWithCell", "Critical Error: Cell has no more space. This function should be called after ensuring that there is at least one more COB available.");
  #endif

  COB* newcob = mob_GetCellCOBWithIndex(cell, cell->nextindex);
  newcob->cell  = cell;
  newcob->v     = cell->nextindex;
  newcob->p     = naGetArrayMutableElement(&(newcob->cell->dataarray), newcob->v);
  naCreateList(&(newcob->listeners));
  cell->nextindex++;
  return newcob;
}


MOB_INLINE void mob_DestroyCOB(COB* cob){
  #ifndef NDEBUG
    if(naGetListCount(&(cob->listeners)))
      mobError("mob_DestroyCOB", "There are still listeners for this COB. This function should be called after all listeners have been removed.");
  #endif
  naClearList(&(cob->listeners), MOB_NULL);
}


MOB_INLINE void mob_ObserveCOB(COB* cob, MOB* observer){
  naAddListElementLast(&(cob->listeners), observer);
}


MOB_INLINE void mob_UnObserveCOB(COB* cob, MOB* observer){
  NABool found = naLocateListElement(&(cob->listeners), observer);
  if(found){
    naRemoveListElementCurrent(&(cob->listeners), NA_FALSE);
    if(naGetListCount(&(cob->listeners)) == 0){mob_DestroyCOB(cob);}
  }else{
    #ifndef NDEBUG
      mobError("mob_UnObserveCOB", "MOB not found in observer list");
    #endif
  }
}


COB* mob_CreateCOBs(MOBUnitID u, MOBInt count){
  #ifndef NDEBUG
    if(u == MOB_UNIT_CELL)
      mobError("mob_CreateCOBs", "Do not use this function with unit 0");
  #endif
  
  // First, make sure, we have a cell with enough space.
  MOBCell* unitcell = mob_getUnitCell(u);
  if(mob_GetCellElementsCount(unitcell) + count >= MOB_CELL_ELEMENTS_COUNT){
    // The current cell has insufficient space. Create a new cell with enough
    // of it. Create a new cell.
    if(count * 2 > MOB_CELL_ELEMENTS_COUNT){
      // If the desired count is larger than half of a regular cell, create
      // a separate cell alltogether
      unitcell = mob_CreateCell(u, count, MOB_NULL, MOB_FALSE);
      mob_addUnitCellFull(unitcell);
    }else{
      unitcell = mob_CreateCell(u, MOB_CELL_ELEMENTS_COUNT, MOB_NULL, MOB_FALSE);
      mob_addUnitCellWithFreeSpace(unitcell);
    }
  }

  // Then, go through all elements and initialize as many COBs as desired.
  MOBInt startindex = unitcell->nextindex;
  for(MOBInt i=0; i<count; i++){
    mob_CreateCOBWithCell(unitcell);
  }
  
  return mob_GetCellCOBWithIndex(unitcell, startindex);
}




// ///////////////////////////////////////////
// MOB
// ///////////////////////////////////////////


MOB_INLINE void mob_AddOutgoingMOB(MOB* endmob, MOB* startmob){
  naAddListElementLast(&(startmob->outpointers), endmob);
}


MOB_INLINE void mob_AddIncomingMOB(MOB* endmob, MOB* startmob){
  naAddListElementLast(&(endmob->inpointers), startmob);
}


void mob_RemoveOutgoingMOB(MOB* endmob, MOB* startmob){
  NABool found = naLocateListElement(&(startmob->outpointers), endmob);
  if(found){
    naRemoveListElementCurrent(&(startmob->outpointers), NA_FALSE);
  }else{
    #ifndef NDEBUG
      mobError("mob_RemoveOutgoingMOB", "MOB not found in List");
    #endif
  }
}


void mob_RemoveIncomingMOB(MOB* endmob, MOB* startmob){
  NABool found = naLocateListElement(&(endmob->inpointers), startmob);
  if(found){
    naRemoveListElementCurrent(&(endmob->inpointers), NA_FALSE);
  }else{
    #ifndef NDEBUG
      mobError("mob_RemoveIncomingMOB", "MOB not found in List");
    #endif
  }
}


MOB_INLINE void mob_FromHasVanished(MOB* mob, MOB* vanishedmob){
  vanishedmob = vanishedmob;
  mobDestroyObject(mob);
}


MOB_INLINE void mob_ToHasVanished(MOB* mob, MOB* vanishedmob){
  vanishedmob = vanishedmob;
  mobDestroyObject(mob);
}


MOB_INLINE void mob_ListenedObjectHasVanished(MOB* mob, MOB* vanishedmob){
  vanishedmob = vanishedmob;
  mobDestroyObject(mob);
}


MOB_INLINE void mob_FillMOB(COB* selfcob, MOB* f, MOB* t, COB* datacob){
  #ifndef NDEBUG
    if(!f || !t)
      mobError("mob_FillMOB", "f and t must be non-null");
  #endif
  MOB* mob = selfcob->p;
  mob->selfcob = selfcob;
  mob->f = f;
  mob->t = t;
  mob->datacob = datacob;
  // Create the lists before observing
  naCreateList(&(mob->outpointers));
  naCreateList(&(mob->inpointers));
  // Observe and track this mob and the cobs.
  mob_ObserveCOB(mob->selfcob, mob);
  mob_AddOutgoingMOB(mob, f);
  mob_AddIncomingMOB(t, mob);
  if(mob->datacob){
    mob_ObserveCOB(mob->datacob, mob);
  }
}


MOB_INLINE MOB* mob_CreateMOB(MOB* f, MOB* t, COB* datacob){
  COB* selfcob = mob_CreateCOBs(MOB_UNIT_MOB, 1);
  if(!f){f = selfcob->p;}
  if(!t){t = selfcob->p;}
  mob_FillMOB(selfcob, f, t, datacob);
  return selfcob->p;
}


MOB_INLINE MOB* mob_CreateArrayMOB(MOB* f, MOB* t, MOBInt count){
  MOB* array = mob_CreateIntMOB(f, t, count); // todo: make Array its own type.
  COB* selfcobarray = mob_CreateCOBs(MOB_UNIT_MOB, count);
  COB* selfcobptr = selfcobarray;

  // Fill the first MOB and set it as the first element of the array.
  mob_FillMOB(selfcobptr, array, array, MOB_NULL);
  mobSetKeyObject(array, mobc->keys[MOB_KEY_ARRAY_FIRST], selfcobptr->p, MOB_FALSE);
  selfcobptr++;

  for(MOBInt i=1; i<count; i++){
    mob_FillMOB(selfcobptr, array, array, MOB_NULL);
    selfcobptr++;
  }
  return array;
}


MOB_INLINE MOB* mob_CreateArrayMOBWithUnit(MOB* f, MOB* t, MOBInt count, MOBUnitID u, void* buffer, MOBBool ownbuffer){
  MOB* array = mob_CreateIntMOB(f, t, count); // todo: Array its own type.
  COB* selfcobarray = mob_CreateCOBs(MOB_UNIT_MOB, count);
  COB* selfcobptr = selfcobarray;

  COB* datacobarray;
  if(buffer){
    // First, create a new cell
    MOBCell* newcell = mob_CreateCell(u, count, buffer, ownbuffer);
    // Attach it to the pool at a place nobody cares.
    mob_addUnitCellFull(newcell);
    // Then, go through all elements and initialize the COBs
    for(MOBInt i=0; i<count; i++){
      mob_CreateCOBWithCell(newcell);
    }
    datacobarray = mob_GetCellCOBWithIndex(newcell, 0);
  }else{
    datacobarray = mob_CreateCOBs(u, count);
  }
  COB* datacobptr = datacobarray;

  // Fill the first MOB and set it as the first element of the array.
  mob_FillMOB(selfcobptr, array, array, datacobptr);
  mobSetKeyObject(array, mobc->keys[MOB_KEY_ARRAY_FIRST], selfcobptr->p, MOB_FALSE);
  selfcobptr++;
  datacobptr++;

  for(MOBInt i=1; i<count; i++){
    mob_FillMOB(selfcobptr, array, array, datacobptr);
    selfcobptr++;
    datacobptr++;
  }
  return array;
}


void mobDestroyObject(MOB* mob){
  MOB* curmob;
  if(!mob){return;}
  
  // First, we detach from the data COB and remove all traces to f and t.
  if(mob->datacob){mob_UnObserveCOB(mob->datacob, mob);}
  mob_RemoveOutgoingMOB(mob, mob->f);
  mob_RemoveIncomingMOB(mob->t, mob);

  // Then we notify all MOBs dependent on this MOB as f
  naFirstListElement(&(mob->outpointers));
  curmob = naGetListMutableContent(&(mob->outpointers));
  while(curmob){
    if(mob != curmob){
      mob_FromHasVanished(curmob, mob);
    }else{
      naRemoveListElementCurrent(&(mob->outpointers), NA_FALSE);
    }
    naFirstListElement(&(mob->outpointers));
    curmob = naGetListMutableContent(&(mob->outpointers));
  }

  // Then we notify all MOBs dependent on this MOB as t
  naFirstListElement(&(mob->inpointers));
  curmob = naGetListMutableContent(&(mob->inpointers));
  while(curmob){
    if(mob != curmob){
      mob_ToHasVanished(curmob, mob);
    }else{
      naRemoveListElementCurrent(&(mob->inpointers), NA_FALSE);
    }
    naFirstListElement(&(mob->inpointers));
    curmob = naGetListMutableContent(&(mob->inpointers));
  }

  // Then we notify all MOBs listening to this MOB
  while(1){
    naFirstListElement(&(mob->selfcob->listeners));
    curmob = naGetListMutableContent(&(mob->selfcob->listeners));
    while(mob == curmob){
      naNextListElement(&(mob->selfcob->listeners));
      curmob = naGetListMutableContent(&(mob->selfcob->listeners));
    }
    if(!curmob){break;}
    mob_ListenedObjectHasVanished(curmob, mob);
  }

  // Finally, we clear all lists and unobserve the selfcob which ultimately
  // will auto-erase the cob and hence this MOB.
  naClearList(&(mob->outpointers), MOB_NULL);
  naClearList(&(mob->inpointers), MOB_NULL);
  mob_UnObserveCOB(mob->selfcob, mob);
}








// ///////////////////////////////////////////
// Unit MOBs
// ///////////////////////////////////////////


MOB_INLINE MOB* mob_GetMOBStoredInMOB(MOB* mob){
  #ifndef NDEBUG
    if((mob->datacob) && (mob->datacob->cell->u != MOB_UNIT_MOB)){
      mobError("mob_GetMOBStoredInMOB", "Given COB does not represent a MOB.");
    }
  #endif
  if(mob->datacob){
    return (MOB*)mob->datacob->p;
  }else{
    return MOB_NULL;
  }
}


MOB_INLINE MOB* mob_CreateMOBWithUnit(MOB* f, MOB* t, MOBUnitID u){
  COB* newcob = mob_CreateCOBs(u, 1);
  return mob_CreateMOB(f, t, newcob);
}


MOB_INLINE MOB* mob_CreateObjectMOB(MOB* f, MOB* t, MOB* value){
  if(value){
    return mob_CreateMOB(f, t, value->selfcob);
  }else{
    return mob_CreateMOB(f, t, MOB_NULL);
  }
}

MOB_INLINE void mob_AlterCOBtoMOB(MOB* mob, MOB* newvalueMOB){
  if(mob->datacob){mob_UnObserveCOB(mob->datacob, mob);}
  mob->datacob = newvalueMOB->selfcob;
  if(mob->datacob){mob_ObserveCOB(mob->datacob, mob);}
}


MOB_INLINE MOB* mob_GetMOBMatchingFromTo(const MOB* from, const MOB* to, MOB* prevvalue){
  #ifndef NDEBUG
    if(!from || !to)
      mobError("mob_GetMOBMatchingFromTo", "from and to must be non-null");
  #endif
  // Search in the one list which is smaller
  if(naGetListCount(&(from->outpointers)) < naGetListCount(&(to->inpointers))){
    naFirstListElement(&(from->outpointers));
    const MOB* curmob = naGetListConstContent(&(from->outpointers));
    if(prevvalue){
      while(curmob){
        if((curmob->t == to) && (curmob->datacob->p == prevvalue)){
          naNextListElement(&(from->outpointers));
          curmob = naGetListConstContent(&(from->outpointers));
          break;
        }
        naNextListElement(&(from->outpointers));
        curmob = naGetListConstContent(&(from->outpointers));
      }
    }
    while(curmob){
      if(curmob->t == to){return (MOB*)curmob;} // todo: hack
      naNextListElement(&(from->outpointers));
      curmob = naGetListConstContent(&(from->outpointers));
    }
  }else{
    naFirstListElement(&(to->inpointers));
    const MOB* curmob = naGetListConstContent(&(to->inpointers));
    if(prevvalue){
      while(curmob){
        if((curmob->f == from) && (curmob->datacob->p == prevvalue)){
          naNextListElement(&(to->inpointers));
          curmob = naGetListConstContent(&(to->inpointers));
          break;
        }
        naNextListElement(&(to->inpointers));
        curmob = naGetListConstContent(&(to->inpointers));
      }
    }
    while(curmob){
      if(curmob->f == from){return (MOB*)curmob;}   // todo hack
      naNextListElement(&(to->inpointers));
      curmob = naGetListConstContent(&(to->inpointers));
    }
  }
  return MOB_NULL;
}


MOB_INLINE MOB* mob_GetMOBMatchingSubKey(const MOB* parent, const MOB* key, MOB* prevobj){
  #ifndef NDEBUG
    if(!parent || !key)
      mobError("mob_GetMOBMatchingSubKey", "from and to must be non-null");
  #endif
  naFirstListElement(&(parent->outpointers));
  const MOB* curmob = naGetListConstContent(&(parent->outpointers));
  if(prevobj){
    while(curmob){
      if((curmob->t == curmob) && (curmob == prevobj)){
        naNextListElement(&(parent->outpointers));
        curmob = naGetListConstContent(&(parent->outpointers));
        break;
      }
      naNextListElement(&(parent->outpointers));
      curmob = naGetListConstContent(&(parent->outpointers));
    }
  }
  while(curmob){
    if((curmob->t == curmob) && (curmob->datacob->p == key->datacob->p)){return (MOB*)curmob;}  // todo: hack
    naNextListElement(&(parent->outpointers));
    curmob = naGetListConstContent(&(parent->outpointers));
  }
  return MOB_NULL;
}


MOB_INLINE const MOB* mob_GetMOBMatchingFromToValue(const MOB* from, const MOB* to, const MOB* value){
  #ifndef NDEBUG
    if(!from || !to || !value)
      mobError("mob_GetMOBMatchingFromToValue", "from to and value must be non-null");
  #endif
  // Search in the one list which is smaller
  if(naGetListCount(&(from->outpointers)) < naGetListCount(&(to->inpointers))){
    naFirstListElement(&(from->outpointers));
    const MOB* curmob = naGetListConstContent(&(from->outpointers));
    while(curmob){
      if((curmob->t == to) && (curmob->datacob->p == value)){return curmob;}
      naNextListElement(&(from->outpointers));
      curmob = naGetListConstContent(&(from->outpointers));
    }
  }else{
    naFirstListElement(&(to->inpointers));
    const MOB* curmob = naGetListConstContent(&(to->inpointers));
    while(curmob){
      if((curmob->f == from) && (curmob->datacob->p == value)){return curmob;}
      naNextListElement(&(to->inpointers));
      curmob = naGetListConstContent(&(to->inpointers));
    }
  }
  return MOB_NULL;
}


MOB_INLINE MOB* mob_CreateIntMOB(MOB* f, MOB* t, MOBInt value){
  MOB* newmob = mob_CreateMOBWithUnit(f, t, MOB_UNIT_INT);
  *(MOBInt*)(newmob->datacob->p) = value;
  return newmob;
}
MOB_INLINE MOB* mob_CreateFloatMOB(MOB* f, MOB* t, float value){
  MOB* newmob = mob_CreateMOBWithUnit(f, t, MOB_UNIT_FLOAT);
  *(float*)(newmob->datacob->p) = value;
  return newmob;
}
MOB_INLINE MOB* mob_CreateStringMOB(MOB* f, MOB* t, const char* value){
  MOB* newmob = mob_CreateMOBWithUnit(f, t, MOB_UNIT_STRING);
  if(value){naCreateStringWithFormat((NAString*)(newmob->datacob->p), "%s", value);}
  return newmob;
}
MOB_INLINE MOB* mob_CreateEnumMOB(MOB* f, MOB* t, MOBInt value){
  MOB* newmob = mob_CreateMOBWithUnit(f, t, MOB_UNIT_ENUM);
  *(MOBInt*)(newmob->datacob->p) = value;
  return newmob;
}
MOB_INLINE MOB* mob_CreateUnitValueMOB(MOB* f, MOB* t, MOBUnitID u, void* value){
  MOB* newmob = mob_CreateMOBWithUnit(f, t, u);
  if(value){naCpyn((newmob->datacob->p), value, mob_GetUnitByteSize(u));}
  return newmob;
}


MOB* mobCreateInt(MOBInt value){
  return mob_CreateIntMOB(MOB_NULL, MOB_NULL, value);
}
MOB* mobCreateFloat(float value){
  return mob_CreateFloatMOB(MOB_NULL, MOB_NULL, value);
}
MOB* mobCreateString(NAUTF8Char* value){
  return mob_CreateStringMOB(MOB_NULL, MOB_NULL, value);
}
MOB* mobCreateEnum(MOBInt value){
  return mob_CreateEnumMOB(MOB_NULL, MOB_NULL, value);
}
MOB* mobCreateUnitValue(MOBUnitID unitID, void* value){
  return mob_CreateUnitValueMOB(MOB_NULL, MOB_NULL, unitID, value);
}


MOBInt* mobInt(MOB* obj){
  #ifndef NDEBUG
    if(obj->datacob->cell->u != MOB_UNIT_INT)
      mobError("mobInt", "Object does not store an int");
  #endif
  return (MOBInt*)(obj->datacob->p);
}
float* mobFloat(MOB* obj){
  #ifndef NDEBUG
    if(obj->datacob->cell->u != MOB_UNIT_FLOAT)
      mobError("mobFloat", "Object does not store a float");
  #endif
  return (float*)(obj->datacob->p);
}
NAString* mobString(MOB* obj){
  #ifndef NDEBUG
    if(obj->datacob->cell->u != MOB_UNIT_STRING)
      mobError("mobString", "Object does not store a string");
  #endif
  return (NAString*)(obj->datacob->p);
}
MOBInt* mobEnum(MOB* obj){
  #ifndef NDEBUG
    if(obj->datacob->cell->u != MOB_UNIT_ENUM)
      mobError("mobEnum", "Object does not store an enum");
  #endif
  return (MOBInt*)(obj->datacob->p);
}
void mobUnitValue(MOB* obj, MOBUnitID unitID, void** bufptr){
  #ifndef NDEBUG
    if(obj->datacob->cell->u != unitID)
      mobError("mobUnitValue", "Object does not store the desired unit");
  #else
    unitID = unitID; // todo
  #endif
  *bufptr = (void*)(obj->datacob->p);
}


MOBInt mobConstInt(const MOB* obj){
  #ifndef NDEBUG
    if(obj->datacob->cell->u != MOB_UNIT_INT)
      mobError("mobInt", "Object does not store an int");
  #endif
  return *(const MOBInt*)(obj->datacob->p);
}
float mobConstFloat(const MOB* obj){
  #ifndef NDEBUG
    if(obj->datacob->cell->u != MOB_UNIT_FLOAT)
      mobError("mobFloat", "Object does not store a float");
  #endif
  return *(const float*)(obj->datacob->p);
}
const NAString* mobConstString(const MOB* obj){
  #ifndef NDEBUG
    if(obj->datacob->cell->u != MOB_UNIT_STRING)
      mobError("mobString", "Object does not store a string");
  #endif
  return (const NAString*)(obj->datacob->p);
}
MOBInt mobConstEnum(const MOB* obj){
  #ifndef NDEBUG
    if(obj->datacob->cell->u != MOB_UNIT_ENUM)
      mobError("mobEnum", "Object does not store an enum");
  #endif
  return *(const MOBInt*)(obj->datacob->p);
}


const void* mobConstData(const MOB* obj){
  // todo: Caching for non-value data. Dangerous otherwise
  return obj->datacob->p;
}


MOB* mobCreateEmptyObject(){
  return mob_CreateMOB(MOB_NULL, MOB_NULL, MOB_NULL);
}
MOB* mobCreateObject(MOB* key){
  COB* keycob = key->datacob;
  return mob_CreateMOB(MOB_NULL, MOB_NULL, keycob);
}
void mobSetObject(MOB* obj, MOB* valueobject){
  #ifndef NDEBUG
    if((obj->datacob) && (obj->datacob->cell->u != MOB_UNIT_MOB))
      mobError("mobSetObject", "Object does not store a MOB");
  #endif
  mob_AlterCOBtoMOB(obj, valueobject);
}
MOB* mobGetObject(MOB* obj){
  #ifndef NDEBUG
    if((obj->datacob) && (obj->datacob->cell->u != MOB_UNIT_MOB))
      mobError("mobGetObject", "Object does not store a MOB");
  #endif
  return mob_GetMOBStoredInMOB(obj);
}


MOB* mobCreateSubObject(MOB* parent, MOB* key){
  COB* keycob = key->datacob;
  return mob_CreateMOB(parent, MOB_NULL, keycob);
}
const MOB* mobGetObjectParent(const MOB* obj){
  #ifndef NDEBUG
    if(obj->t != obj)
      mobError("mobGetObjectParent", "Object is not a sub");
  #endif
  return obj->f;
}


MOB* mobCreateArray(MOBInt count){
  return mob_CreateArrayMOB(MOB_NULL, MOB_NULL, count);
}
void mobSetArrayObject(MOB* array, MOBInt indx, MOB* newobj){
  MOB* firstentry = mobGetKeyObject(array, mobc->keys[MOB_KEY_ARRAY_FIRST]);
  MOB* desiredelement = firstentry->selfcob[indx].p;
  mob_AlterCOBtoMOB(desiredelement, newobj);
}
MOB* mobGetArrayObject(MOB* array, MOBInt indx){
  MOB* firstentry = mobGetKeyObject(array, mobc->keys[MOB_KEY_ARRAY_FIRST]);
  MOB* desiredelement = firstentry->selfcob[indx].p;
  return mob_GetMOBStoredInMOB(desiredelement);
}


MOB* mobCreateFloatArray(MOBInt count){
  return mob_CreateArrayMOBWithUnit(MOB_NULL, MOB_NULL, count, MOB_UNIT_FLOAT, MOB_NULL, MOB_FALSE);
}
MOB* mobCreateEnumArray(MOBInt count){
  return mob_CreateArrayMOBWithUnit(MOB_NULL, MOB_NULL, count, MOB_UNIT_ENUM, MOB_NULL, MOB_FALSE);
}

MOB* mobCreateFloatArrayWithBuffer(MOBInt count, void* buffer, MOBBool ownbuffer){
  return mob_CreateArrayMOBWithUnit(MOB_NULL, MOB_NULL, count, MOB_UNIT_FLOAT, buffer, ownbuffer);
}

MOBInt mobArrayCount(MOB* array){
  return *mobInt(array);
}

const void* mobConstArrayData(MOB* array){
  // todo: Caching for non-pure data. Will not work otherwise!
  MOB* firstentry = mobGetKeyObject(array, mobc->keys[MOB_KEY_ARRAY_FIRST]);
  return firstentry->datacob->p;
}

void* mobArrayData(MOB* array){
  // todo: check if array pure
  MOB* firstentry = mobGetKeyObject(array, mobc->keys[MOB_KEY_ARRAY_FIRST]);
  return firstentry->datacob->p;
}

const void* mobConstArrayObjectData(MOB* array){
  // todo: check if array pure
  MOB* firstentry = mobGetKeyObject(array, mobc->keys[MOB_KEY_ARRAY_FIRST]);
  return firstentry->selfcob->p;
}

void* mobArrayObjectData(MOB* array){
  // todo: check if array pure
  MOB* firstentry = mobGetKeyObject(array, mobc->keys[MOB_KEY_ARRAY_FIRST]);
  return firstentry->selfcob->p;
}

float* mobArrayFloat(MOB* array, MOBInt indx){
  MOB* firstentry = mobGetKeyObject(array, mobc->keys[MOB_KEY_ARRAY_FIRST]);
  MOB* desiredelement = firstentry->selfcob[indx].p;
  if(!desiredelement){desiredelement = mob_CreateFloatMOB(array, array, 0.f);}
  #ifndef NDEBUG
    if(desiredelement->datacob->cell->u != MOB_UNIT_FLOAT)
      mobError("mobKeyFloat", "Object does not store a float");
  #endif
  return (float*)(desiredelement->datacob->p);
}

MOBInt* mobArrayEnum(MOB* array, MOBInt indx){
  MOB* firstentry = mobGetKeyObject(array, mobc->keys[MOB_KEY_ARRAY_FIRST]);
  MOB* desiredelement = firstentry->selfcob[indx].p;
  if(!desiredelement){desiredelement = mob_CreateEnumMOB(array, array, 0.f);}
  #ifndef NDEBUG
    if(desiredelement->datacob->cell->u != MOB_UNIT_ENUM)
      mobError("mobKeyEnum", "Object does not store an Enum");
  #endif
  return (MOBInt*)(desiredelement->datacob->p);
}


MOBInt* mobKeyInt(MOB* obj, MOB* key){
  MOB* mob = mob_GetMOBMatchingFromTo(key, obj, MOB_NULL);
  if(!mob){mob = mob_CreateIntMOB(key, obj, 0);}
  #ifndef NDEBUG
    if(mob->datacob->cell->u != MOB_UNIT_INT)
      mobError("mobKeyInt", "Object does not store an int");
  #endif
  return (MOBInt*)(mob->datacob->p);
}
float* mobKeyFloat(MOB* obj, MOB* key){
  MOB* mob = mob_GetMOBMatchingFromTo(key, obj, MOB_NULL);
  if(!mob){mob = mob_CreateFloatMOB(key, obj, 0.f);}
  #ifndef NDEBUG
    if(mob->datacob->cell->u != MOB_UNIT_FLOAT)
      mobError("mobKeyFloat", "Object does not store a float");
  #endif
  return (float*)(mob->datacob->p);
}
NAString* mobKeyString(MOB* obj, MOB* key){
  MOB* mob = mob_GetMOBMatchingFromTo(key, obj, MOB_NULL);
  if(!mob){mob = mob_CreateStringMOB(key, obj, MOB_NULL);}
  #ifndef NDEBUG
    if(mob->datacob->cell->u != MOB_UNIT_STRING)
      mobError("mobKeyString", "Object does not store a string");
  #endif
  return (NAString*)(mob->datacob->p);
}
MOBInt* mobKeyEnum(MOB* obj, MOB* key){
  MOB* mob = mob_GetMOBMatchingFromTo(key, obj, MOB_NULL);
  if(!mob){mob = mob_CreateEnumMOB(key, obj, 0);}
  #ifndef NDEBUG
    if(mob->datacob->cell->u != MOB_UNIT_ENUM)
      mobError("mobKeyEnum", "Object does not store an enum");
  #endif
  return (MOBInt*)(mob->datacob->p);
}


MOBInt mobConstKeyInt(const MOB* obj, MOB* key){
  MOB* mob = mob_GetMOBMatchingFromTo(key, obj, MOB_NULL);
  #ifndef NDEBUG
    if(mob->datacob->cell->u != MOB_UNIT_INT)
      mobError("mobKeyInt", "Object does not store an int");
  #endif
  if(!mob){return 0;}
  return *(MOBInt*)(mob->datacob->p);
}
float mobConstKeyFloat(const MOB* obj, MOB* key){
  MOB* mob = mob_GetMOBMatchingFromTo(key, obj, MOB_NULL);
  #ifndef NDEBUG
    if(mob->datacob->cell->u != MOB_UNIT_FLOAT)
      mobError("mobKeyFloat", "Object does not store a float");
  #endif
  if(!mob){return 0.f;}
  return *(float*)(mob->datacob->p);
}
const NAString* mobConstKeyString(const MOB* obj, MOB* key){
  MOB* mob = mob_GetMOBMatchingFromTo(key, obj, MOB_NULL);
  #ifndef NDEBUG
    if(mob->datacob->cell->u != MOB_UNIT_STRING)
      mobError("mobKeyString", "Object does not store a string");
  #endif
  if(!mob){return MOB_NULL;}
  return (const NAString*)(mob->datacob->p);
}
MOBInt mobConstKeyEnum(const MOB* obj, MOB* key){
  MOB* mob = mob_GetMOBMatchingFromTo(key, obj, MOB_NULL);
  #ifndef NDEBUG
    if(mob->datacob->cell->u != MOB_UNIT_ENUM)
      mobError("mobKeyEnum", "Object does not store an enum");
  #endif
  if(!mob){return 0;}
  return *(MOBInt*)(mob->datacob->p);
}


void mobGetKeyUnitValue(const MOB* obj, MOB* key, MOBUnitID unitID, void* buf){
  MOB* mob = mob_GetMOBMatchingFromTo(key, obj, MOB_NULL);
  #ifndef NDEBUG
    if(mob->datacob->cell->u != unitID)
      mobError("mobSetKeyUnitValue", "Object does not store the desired unit");
  #endif
  if(!mob){return;}
  naCpyn(buf, (mob->datacob->p), mob_GetUnitByteSize(unitID));
}
void mobSetKeyUnitValue(MOB* obj, MOB* key, MOBUnitID unitID, void* buf){
  MOB* mob = mob_GetMOBMatchingFromTo(key, obj, MOB_NULL);
  if(!mob){mob = mob_CreateUnitValueMOB(key, obj, unitID, MOB_NULL);}
  #ifndef NDEBUG
    if(mob->datacob->cell->u != unitID)
      mobError("mobSetKeyUnitValue", "Object does not store the desired unit");
  #endif
  naCpyn((mob->datacob->p), buf, mob_GetUnitByteSize(unitID));
}


MOB* mobGetKeyObject(const MOB* obj, const MOB* key){
  MOB* mob = mob_GetMOBMatchingFromTo(key, obj, MOB_NULL);
  if(!mob){return MOB_NULL;}
  #ifndef NDEBUG
    if((mob->datacob) && (mob->datacob->cell->u != MOB_UNIT_MOB))
      mobError("mobGetKeyObject", "Object does not store an object");
  #endif
  if(mob->datacob){
    return (MOB*)(mob->datacob->p);
  }else{
    return MOB_NULL;
  }
}
MOB* mobNextKeyObject(const MOB* obj, const MOB* key, MOB** objbuf){
  MOB* mob = mob_GetMOBMatchingFromTo(key, obj, *objbuf);
  if(!mob){return MOB_NULL;}
  #ifndef NDEBUG
    if((mob->datacob) && (mob->datacob->cell->u != MOB_UNIT_MOB))
      mobError("mobGetKeyObject", "Object does not store an object");
  #endif
  if(mob->datacob){
    *objbuf = (MOB*)(mob->datacob->p);
  }else{
    *objbuf = MOB_NULL;
  }
  return *objbuf;
}
MOB* mobNextSubKeyObject(const MOB* parent, const MOB* key, MOB** objbuf){
  *objbuf = mob_GetMOBMatchingSubKey(parent, key, *objbuf);
  return *objbuf;
}
MOB* mobGetKeyObjectWithIndex(MOB* obj, MOB* key, MOBInt indx){
  MOB* curmob = mobGetKeyObject(obj, key);
  while(indx){
    mobNextKeyObject(obj,  key, &curmob);
    indx--;
  }
  return curmob;
}
void mobSetKeyObject(MOB* obj, MOB* key, MOB* valueobject, MOBBool allowmultiple){
  if(allowmultiple){
    mob_CreateObjectMOB(key, obj, valueobject);
  }else{
    MOB* mob = mob_GetMOBMatchingFromTo(key, obj, MOB_NULL);
    if(!mob){
      mob = mob_CreateObjectMOB(key, obj, valueobject);
    }else{
      #ifndef NDEBUG
        if((mob->datacob) && (mob->datacob->cell->u != MOB_UNIT_MOB))
          mobError("mobSetKeyObject", "Object does not store an object");
      #endif
      mob_AlterCOBtoMOB(mob, valueobject);
    }
  }
}
MOBBool mobHasKeyObjectValue(const MOB* obj, const MOB* key, const MOB* value){
  const MOB* mob = mob_GetMOBMatchingFromToValue(key, obj, value);
  return (mob != MOB_NULL);
}
MOBInt mobCountKeyValues(MOB* obj, MOB* key){
  MOBInt count = 0;
  naFirstListElement(&(obj->inpointers));
  MOB* curobj = naGetListMutableContent(&(obj->inpointers));
  while(curobj){
    if(curobj->f == key){
      count++;
    }
    naNextListElement(&(obj->inpointers));
    curobj = naGetListMutableContent(&(obj->inpointers));
  }
  return count;
}
void mobDestroyValues(MOB* obj, MOB* value){
  while(1){
    naFirstListElement(&(obj->inpointers));
    MOB* curobj = naGetListMutableContent(&(obj->inpointers));
    while(curobj){
      if(curobj->datacob && curobj->datacob->p == value){
        mobDestroyObject(curobj);
        break;
      }
      naNextListElement(&(obj->inpointers));
      curobj = naGetListMutableContent(&(obj->inpointers));
    }
    if(!curobj){return;}
  }
}
const MOB* mobGetKey(const MOB* obj, const MOB* value){
  naFirstListElement(&(obj->inpointers));
  const MOB* curobj = naGetListConstContent(&(obj->inpointers));
  while(curobj){
    if(curobj->datacob->p == value){
      return curobj->f;
    }
    naNextListElement(&(obj->inpointers));
    curobj = naGetListConstContent(&(obj->inpointers));
  }
  return MOB_NULL;
}





MOBBool mobEqual(const MOB* mob1, const MOB* mob2){
  return mob1->datacob == mob2->datacob;
}



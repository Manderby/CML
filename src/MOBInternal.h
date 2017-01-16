
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.


// This Header file exists as there are many hidden APIs needed in MOB.c and
// it simply is cumbersome to not have them in a separate file.

#include "MOB.h"
#include "NAList.h"
#include "NAGrowingSpace.h"




#define MOB_INLINE NA_INLINE static 
#define MOB_CELL_ELEMENTS_COUNT 127
#define mobAllocate naAllocate
#define mobError naError
#define MOBByte NAByte


typedef enum{
  MOB_KEY_ARRAY,
  MOB_KEY_ARRAY_COUNT,
  MOB_KEY_ARRAY_FIRST,
  MOB_KEY_LIST,
  MOB_KEY_LIST_COUNT,
  MOB_KEY_LIST_FIRST,
  MOB_KEY_LIST_LAST,
  MOB_KEYS_COUNT
} MOBKey;


typedef enum{
  MOB_UNIT_CELL,
  MOB_UNIT_MOB,
  MOB_UNIT_INT,
  MOB_UNIT_FLOAT,
  MOB_UNIT_STRING,
  MOB_UNIT_ENUM,

  MOB_UNIT_ARRAY,
  MOB_INFORMATION_UNITS_COUNT
} MOBInformationUnit;


// /////////////////////////
// Internal struct definitions
// /////////////////////////

// Forward declarations
typedef struct COB        COB;
typedef struct MOBCell    MOBCell;
typedef struct MOBPool    MOBPool;
typedef struct MOBProgram MOBProgram;

// In the database, a (c,v)-Tuple represents a COB needed to locate ANY value.
// c denotes the cellID and v denotes the index within that cell.
//
// Here in object-oriented mode, c is rather more stored as the cell object
// itself instead of the CellID. Only when serializing to a file, the cells
// will be enumerated and the CellID will therefore be generated dynamically.
// 
// An object instantiation of a data point. Used to address the data and manage
// all listeners to that data. There exists exactly ONE COB for every
// (c,v)-Tuple.
struct COB{
  MOBCell*        cell;         // The cell the value is stored in.
  MOBInt          v;            // the index of the value inside the cell
  void*           p;            // The pointer pointing to the actual data.
  NAList          listeners;    // MOBs listening to that value.
};

// A cell stores a multitude of COBs and provides a compact raw data space
// referenced by the COBs.
struct MOBCell{
  NAArray         dataarray;    // The array storing the raw data.
  COB*            cellobjects;  // An array of COBs.
  MOBInt          u;            // The unit ID
  MOBInt          nextindex;    // The next free index (used for dynamic)
  MOBCell*        nextcell;     // The next cell (used for dynamic)
};

struct MOB{
  COB*            selfcob;
  MOB*            f;
  MOB*            t;
  COB*            datacob;
  NAList          outpointers;  // A list of MOBs
  NAList          inpointers;   // A list of MOBs
};

struct MOBPool{
  MOBInt          bytesize;
  MOBCell*        firstcell;
  MOBCell*        curcell;
};

struct MOBContext{
  NAGrowingSpace  unitpools;
  MOB*            keys[MOB_KEYS_COUNT];
};



// Function used for dynamics. Might change in the future
MOB_INLINE MOBInt mob_GetCellElementsCount(MOBCell* cell);

// Returns a specific COB
MOB_INLINE COB* mob_GetCellCOBWithIndex(MOBCell* cell, MOBInt indx);
MOB_INLINE void* mob_GetCellDataWithIndex(MOBCell* cell, MOBInt indx);

// Returns the raw data pointer to the specified element
MOB_INLINE       void* mob_GetCOBData(COB* cob);

// Initializes one COB of the given cell and returns it. Only call this
// function if you are sure that the cell has sufficient space!
MOB_INLINE COB* mob_CreateCOBWithCell(MOBCell* cell);

MOB_INLINE void mob_DestroyCell(MOBCell* cell);


// Creates a new, uninitialized cell.
MOB_INLINE MOBCell*  mob_CreateCellCell();
MOB_INLINE MOBCell*  mob_CreateCell(MOBUnitID u, MOBInt count, void* buffer, MOBBool ownbuffer);

// Ensures enough space for the given number of elements with the given unit
// and returns a pointer to the first cob. The cobs and the data is guaranteed
// to be sequential.
COB* mob_CreateCOBs(MOBUnitID u, MOBInt count);

MOB_INLINE void mob_DestroyUnitPool(MOBPool* pool);


// Returns the elements pool of a given unit id
MOB_INLINE MOBPool* mob_getUnitPool(MOBUnitID id);

MOB_INLINE void mob_addUnitCellWithFreeSpace(MOBCell* cell);

// Returns the current cell of the given unit id
MOB_INLINE MOBCell* mob_getUnitCell(MOBUnitID unit);


MOB_INLINE MOBInt mob_GetUnitByteSize(MOBUnitID unit);





MOB_INLINE MOB* mob_GetMOBStoredInMOB(MOB* mob);

MOB_INLINE void mob_AddOutgoingMOB(MOB* endmob, MOB* startmob);
MOB_INLINE void mob_AddIncomingMOB(MOB* endmob, MOB* startmob);
MOB_INLINE void mob_RemoveOutgoingMOB(MOB* endmob, MOB* startmob);
MOB_INLINE void mob_RemoveIncomingMOB(MOB* endmob, MOB* startmob);

MOB_INLINE void mob_FillMOB(COB* selfcob, MOB* f, MOB* t, COB* datacob);
MOB_INLINE MOB* mob_CreateMOB(MOB* f, MOB* t, COB* datacob);

MOB_INLINE void mob_FromHasVanished(MOB* mob, MOB* vanishedmob);
MOB_INLINE void mob_ToHasVanished(MOB* mob, MOB* vanishedmob);
MOB_INLINE void mob_ListenedObjectHasVanished(MOB* mob, MOB* vanishedmob);


// Creates an object storing one uninitialized unit
MOB_INLINE MOB* mob_CreateMOBWithUnit(MOB* f, MOB* t, MOBUnitID unit);

MOB_INLINE MOB* mob_CreateStringMOB(MOB* f, MOB* t, const char* value);
MOB_INLINE MOB* mob_CreateFloatMOB(MOB* f, MOB* t, float value);
MOB_INLINE MOB* mob_CreateIntMOB(MOB* f, MOB* t, MOBInt value);
MOB_INLINE MOB* mob_CreateEnumMOB(MOB* f, MOB* t, MOBInt value);
MOB_INLINE MOB* mob_CreateObjectMOB(MOB* f, MOB* t, MOB* value);
MOB_INLINE MOB* mob_CreateUnitValueMOB(MOB* f, MOB* t, MOBUnitID u, void* value);





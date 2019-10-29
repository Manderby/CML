
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

#include "NAString.h"

#define MOB_NULL            NA_NULL
#define MOB_FALSE           NA_FALSE
#define MOB_TRUE            NA_TRUE
//#define MOB_PROGRAM         0

typedef NABool              MOBBool;
typedef NAInt               MOBInt;
typedef MOBInt MOBUnitID;
typedef struct MOBContext   MOBContext;
typedef struct MOB          MOB;

typedef MOB                 MOBList;



// Activates the given context or creates a new one if NULL is given. Returns
// the new context.
MOBContext*     mobActivateContext(MOBContext* context);
// Returns the context which is currently running.
MOBContext*     mobCurrentContext (void);
// Destroys all data of the given context.
void            mobDestroyContext (MOBContext* context);



// Registers a new information unit and returns its identifying id.
MOBUnitID       mobRegisterUnit   (MOBInt bytesize, const char* name);



// /////////////////////
// Working with Objects
// /////////////////////

// MOB objects can store many things. They can store values or a reference
// to another object. They can be anonymous or identifiable by a key.
//
// All data is stored somewhere in memory which is automatically managed. You
// do not need to allocate or free memory.


// /////////////////////
// Value Objects
// /////////////////////

// Value objects are standalone-objects with no root. They exist without being
// attached to any other object and hence will rest in memory as long as you
// do not call mobDestroyObject.
//
// Creating value-objects:
// Creates an object storing the given value. The returned mob is stored and
// managed automatically in memory. You can access the value with the
// functions further below.
//
// mobCreateInt:        Creates an object storing an Int.
// mobCreateFloat:      Creates an object storing a float.
// mobCreateString:     Creates an object storing a string. The value must be
//                      given as an NAUTF8Char* string and will be copied.
//                      The value can later be accessed as an NAString.
// mobCreateEnum:       Creates an object storing an enumeration value.
// mobCreateUnitValue:  Creates an object storing a value with a custom unit.
//                      The data whose pointer you provide will be copied.

MOB*            mobCreateInt            (MOBInt value);
MOB*            mobCreateFloat          (float value);
MOB*            mobCreateString         (NAUTF8Char* value);
MOB*            mobCreateEnum           (MOBInt value);
MOB*            mobCreateUnitValue      (MOBUnitID unitID, void* value);

// Accessing the value of value-objects
// Returns a mutable pointer to the storage of the desired type stored within
// the given object. If the object does not store the desired type, behaviour
// is undefined. You can both get and set the value using these functions.
MOBInt*         mobInt                  (MOB* obj);
float*          mobFloat                (MOB* obj);
NAString*       mobString               (MOB* obj);
MOBInt*         mobEnum                 (MOB* obj);
// Getting a unit value requires you to provide a pointer to a buffer capable
// of storing a pointer to the buffer
void            mobUnitValue            (MOB* obj,
                                    MOBUnitID unitID,
                                       void** bufptr);

// If you want const access to the value stored, you can use the following
// functions:
MOBInt          mobConstInt             (const MOB* obj);
float           mobConstFloat           (const MOB* obj);
const NAString* mobConstString          (const MOB* obj);
MOBInt          mobConstEnum            (const MOB* obj);
// For a value-object, you can also have direct access to the data stored. Only
// const though.
const void*     mobConstData            (const MOB* obj);

// mobCreateEmptyObject:
// With this function, you can create an empty object. Can be used as a key
// for example. Or as an annonymous object which gets attached multiple
// key-value pairs (see below).
//
// mobCreateObject:
// Creates a new object referencing the given object. The valueobject is not
// copied but referenced. For example, you can create an object which
// references to an object called "Car". This would make the newly created
// MOB an independent, stand-alone representative of that referenced object.
// Note that you can only create the object but not access its value directly.
// You have to use the getter and setter function.
MOB*            mobCreateEmptyObject    ();
MOB*            mobCreateObject         (MOB* valueobject);
void            mobSetObject            (MOB* obj, MOB* valueobject);
MOB*            mobGetObject            (MOB* obj);

// You can also create objects as a sub of another object.
MOB*            mobCreateSubObject      (MOB* parent, MOB* key);
const MOB*      mobGetObjectParent      (const MOB* obj);

// Destroys a value-object. All objects which are dependent on this object
// (for example its key-value objects) will get a deletion notification.
void            mobDestroyObject        (MOB* obj);


// /////////////////////
// Array Objects and Array Elements
// /////////////////////

// Arrays store an array of objects pointing to whatever value is stored in
// the elements. Every single element can have a different type. You can not,
// however, access the element-objects directly but you must use the array
// access functions further below.

// Create Arrays pre-filled with specific base types:
//
// When a new array is created, sufficient consecutive space will be provided
// to store the desired kind of elements. It is therefore completely fine to
// use the first element pointer using the access methods below for default
// C-style array initialization. But beware that this is only valid for
// first-time initialization. During further runtime of your application, the
// objects of the array may point at different values than the one initially
// provided. Use of mobConstArrayData is recommended.
MOB*            mobCreateFloatArray     (MOBInt count);
MOB*            mobCreateEnumArray      (MOBInt count);

MOB*            mobCreateFloatArrayWithBuffer(
                                         MOBInt count,
                                          void* buffer,
                                        MOBBool ownbuffer);

MOBInt          mobArrayCount           (MOB* array);

// When you have an array consisting of a base type, you can directly access
// the underlying data with the following function. The use of this function
// is highly recommended as it simplifies your programming and takes into
// account any changes that the array has been going through and automatically
// caches data. Beware that the data ist const. Accessing it as a mutator by
// casting will result in undefined behaviour.
const void*     mobConstArrayData       (MOB* array);
void*           mobArrayData            (MOB* array);
const void*     mobConstArrayObjectData (MOB* array);
void*           mobArrayObjectData      (MOB* array);

// Array access functions:
// For any base type, access and alter the desired value with these functions:
// If the element at the desired index does not store the desired type,
// behaviour is undefined. If the storage of the element is yet undefined
// (which can happen if you use mobCreateArray), a new element with the desired
// type will automatically be created.
float*          mobArrayFloat           (MOB* array, MOBInt indx);
MOBInt*         mobArrayEnum            (MOB* array, MOBInt indx);

// You can also create an array of objects storing any kind of value. The
// elements of the resulting array are empty and can be initialized by the
// object-element access functions below.
MOB*            mobCreateArray          (MOBInt count);

// If your array element stores an Object, use the following getters and
// setters. Note that if you access an element with the get method and that
// element has not been set yet, MOB_NULL will be returned.
void            mobSetArrayObject       (MOB* array, MOBInt indx, MOB* newobj);
MOB*            mobGetArrayObject       (MOB* array, MOBInt indx);


// /////////////////////
// Key-Value Objects
// /////////////////////

// A key-value is a unique value which can be addressed by a specific key and
// being attached / attributed to another object. For example an object "Car"
// has the Int value "4" stored with the key "Number of wheels".
//
// There can be only 1 value per key.
//
// A key can be any MOB object. You can use an object storing a name, a number
// or anything. If you use mobCreateEmptyObject(), you get an anonymous object
// storing no value at all. You can use this object as a key which can only
// be used with the knwledge of the memory address MOB* of this MOB.
//
// Accessing and Mutating key-value objects
// Returns a mutable pointer capable of storing a value of the desired type
// and being attached to the given object as a key-value. You can both get
// and set the value using these methods. If the key-value does not exist
// yet, it will automatically be created.
MOBInt*         mobKeyInt               (MOB* obj, MOB* key);
float*          mobKeyFloat             (MOB* obj, MOB* key);
NAString*       mobKeyString            (MOB* obj, MOB* key);
MOBInt*         mobKeyEnum              (MOB* obj, MOB* key);
// Getting a key unit value requires you to provide a pointer to a buffer
// capable of storing a pointer to the buffer

// If you want const access to the value stored, you can use the following
// functions. Note that Null is returned, if the key does not exist:
MOBInt          mobConstKeyInt          (const MOB* obj, MOB* key);
float           mobConstKeyFloat        (const MOB* obj, MOB* key);
const NAString* mobConstKeyString       (const MOB* obj, MOB* key);
MOBInt          mobConstKeyEnum         (const MOB* obj, MOB* key);

// Getting a key unit value requires you to provide a pointer to a buffer
// capable of storing a pointer to the buffer
void            mobGetKeyUnitValue (const MOB* obj,
                                          MOB* key,
                                     MOBUnitID unitID,
                                         void* valuebuf);
void            mobSetKeyUnitValue      (MOB* obj,
                                         MOB* key,
                                    MOBUnitID unitID,
                                        void* valuebuf);

// You can also reference other objects as a value. For example, an object
// "Car" has a value-object "Customer" stored with the key "Rent". Note
// that the value-object is referenced, not copied.
//
// Use the following getter and setter functions to reference such objects.
// If allowmultiple is set to MOB_FALSE, only one valueobject will be stored
// and successing calls with MOB_FALSE will overwrite the object stored in key.
// If allowmultiple is set to MOB_FALSE, you can collect multiple objects
// under the same key. The resulting collection is ordered as a list and
// appending will always occur at the tail.
void            mobSetKeyObject         (MOB* obj,
                                         MOB* key,
                                         MOB* valueobject,
                                      MOBBool allowmultiple);
// Retrieve the object with a key with the following function. If you store
// multiple objects under the same key, this function retrieve the first one.
// To access more objects, use mobNextKeyObject.
MOB*            mobGetKeyObject         (const MOB* obj,
                                         const MOB* key);
// Note that the get function will return MOB_NULL if the key does not exist.

// If you store multiple objects per key, you can access them sequentially
// with a call to the following function. The objbuf holds a pointer to the
// previous mob. In the beginning, this pointer shall be MOB_NULL. After the
// function, objbuf will contain the new element and the exact same pointer
// is returned. If there is no more object, MOB_NULL is returned.
//
// With this function, you can easily iterate through all objects of a key:
// MOB* curobj = MOB_NULL;
// while(mobNextKeyObject(containerobj, key, &curobj)){...}
MOB*            mobNextKeyObject        (const MOB* obj,
                                         const MOB* key,
                                              MOB** objbuf);

// In the same way, you can retrieve the object with the given key which is a
// sub of the given parent.
MOB*            mobNextSubKeyObject     (const MOB* parent,
                                         const MOB* key,
                                              MOB** objbuf);

// Same thing but with the given index
MOB*            mobGetKeyObjectWithIndex(MOB* obj,
                                         MOB* key,
                                       MOBInt indx);

// Returns MOB_TRUE if a key object with the given value exists in obj.
MOBBool         mobHasKeyObjectValue    ( const MOB* obj,
                                          const MOB* key,
                                          const MOB* value);

// Returns the number of values stored in key for the given object.
// Returns 0 if key is not existant in the given obj.
// Returns 1 if allowmultiple was set to MOB_TRUE in mobSetKeyObject.
// Returns any appropriate number otherwise.
MOBInt          mobCountKeyValues       (MOB* obj, MOB* key);

// Destroys all key values of obj with the given value, no matter which key.
void            mobDestroyValues        (MOB* obj, MOB* value);

// Returns the key of a given value stored in obj.
const MOB*      mobGetKey               (const MOB* obj, const MOB* value);



// Returns true if the two objects refer to the same data.
MOBBool         mobEqual(const MOB* mob1, const MOB* mob2);











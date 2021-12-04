
// Base definitions of CML
// Defines some useful types, macros and functions. Default stuff.



#include <sys/types.h>  // base types
#include <stdlib.h>     // Just for the NULL
#include <string.h>     // memset and memcpy



// ////////////////////////////////////////////
// System detection
// ////////////////////////////////////////////

#if (defined _WIN64) || (defined _WIN32) || (defined WIN32)
  #define CML_COMPILE_ON_WIN 1
#elif (defined __APPLE__)
  #define CML_COMPILE_ON_MAC_OSX 1
#else
  #warning This system may not be supported by CML
#endif



// ////////////////////////////////////////////
// System dependent macros and type definitions
// ////////////////////////////////////////////

#if CML_COMPILE_ON_WIN
  #define CML_INLINE _inline
  #ifndef CML_INLINE
    #define CML_INLINE __inline
  #endif
  #define CML_LINKER_NO_EXPORT
  #define CML_LINKER_EXPORT         __declspec(dllexport)
  #define CML_DEBUG_FUNCTIONSYMBOL __FUNCTION__

  typedef signed __int32    CMLint32;
  typedef unsigned __int32  CMLuint32;
  typedef unsigned __int16  CMLuint16;
  typedef unsigned __int8   CMLuint8;
  typedef signed __int8     CMLint8;
  
#elif CML_COMPILE_ON_MAC_OSX
  #define CML_INLINE inline
  #define CML_LINKER_NO_EXPORT      __attribute__ ((visibility("hidden")))
  #define CML_LINKER_EXPORT         __attribute__ ((visibility("default")))
  #define CML_DEBUG_FUNCTIONSYMBOL __func__
  
  typedef int32_t           CMLint32;
  typedef u_int32_t         CMLuint32;
  typedef u_int16_t         CMLuint16;
  typedef u_int8_t          CMLuint8;
  typedef int8_t            CMLint8;
  
#else
  #define CML_INLINE inline
  #define CML_LINKER_NO_EXPORT
  #define CML_LINKER_EXPORT
  #define CML_DEBUG_FUNCTIONSYMBOL __func__

  typedef signed int        CMLint32;
  typedef unsigned int      CMLuint32;
  typedef unsigned short    CMLuint16;
  typedef unsigned char     CMLuint8;
  typedef signed char       CMLint8;
#endif



#define CML_API   CML_LINKER_EXPORT
#define CML_DEF   CML_LINKER_EXPORT
#define CML_HAPI  CML_LINKER_NO_EXPORT
#define CML_HDEF  CML_LINKER_NO_EXPORT
#define CML_IAPI  static CML_INLINE
#define CML_IDEF  static CML_INLINE
#define CML_HIDEF static CML_INLINE CML_LINKER_NO_EXPORT

typedef CMLint32      CMLInt;
typedef CMLuint16     CMLWord;
typedef CMLuint8      CMLByte;

typedef int           CMLBool;
#define CML_TRUE      1
#define CML_FALSE     0
#define CML_NULL      NULL
#define CML_UNUSED(x) (void)x



// ////////////////////////////////////////////
// Definitions for Debugging.
// Use CML_DEBUG to define whether error checks shall be reported via stderr
// or not. Default is 1 if NDEBUG is undefined, 0 otherwise.
// ////////////////////////////////////////////

#ifndef CML_DEBUG
  #if CML_DEBUG
    #define CML_DEBUG 1
  #else
    #define CML_DEBUG 0
  #endif
#endif

#if CML_DEBUG
  #if CML_COMPILE_ON_WIN
    #include <io.h>
    #include <share.h>
    #include <direct.h>
    #include "windows.h"
    
  #elif CML_COMPILE_ON_MAC_OSX
    #include <unistd.h>
    
  #else
    #include <unistd.h>
  #endif
  
  #include <string.h>
  #include <stdio.h>

  CML_API void cml_Error(const char* functionSymbol, const char* text);

  // This is the error reporting function. It outputs a string to the stderr
  // and prefixes the function the error occured in.
  #define cmlError(text)\
    cml_Error(CML_DEBUG_FUNCTIONSYMBOL, text)
    
#endif



// This is free and unencumbered software released into the public domain.

// Anyone is free to copy, modify, publish, use, compile, sell, or
// distribute this software, either in source code form or as a compiled
// binary, for any purpose, commercial or non-commercial, and by any
// means.

// In jurisdictions that recognize copyright laws, the author or authors
// of this software dedicate any and all copyright interest in the
// software to the public domain. We make this dedication for the benefit
// of the public at large and to the detriment of our heirs and
// successors. We intend this dedication to be an overt act of
// relinquishment in perpetuity of all present and future rights to this
// software under copyright law.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
// OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.

// For more information, please refer to <http://unlicense.org/>



#include <CML.h>

// This class is a timer. It returns the elapsed time with microsecond accuracy
#if CML_COMPILE_ON_WIN
  #include <windows.h>
  //class Timer{
  //  LARGE_INTEGER startusecs;
  //public:
  //  Timer(){init();}
  //  void init(){QueryPerformanceCounter(&startusecs);}
  //  float getSeconds(){
  //    LARGE_INTEGER ticspersec;
  //    QueryPerformanceFrequency(&ticspersec);
  //    LARGE_INTEGER curusecs;
  //    QueryPerformanceCounter(&curusecs);
  //    return (float)(curusecs.QuadPart - startusecs.QuadPart) / (float)ticspersec.QuadPart;
  //  }
  //};
  typedef LARGE_INTEGER CMLTimer;
  static CMLTimer CMLTimerGetAbsoluteUSeconds(){
    CMLTimer value;
    QueryPerformanceCounter(&value);
    return value;
  }
  static CMLTimer CMLStartTimer(){
    return CMLTimerGetAbsoluteUSeconds();
  }
  static float CMLTimerGetSeconds(CMLTimer timer){
    CMLTimer ticspersec;
    CMLTimer curusecs;
    QueryPerformanceFrequency(&ticspersec);
    curusecs = CMLTimerGetAbsoluteUSeconds();
    return (float)(curusecs.QuadPart - timer.QuadPart) / (float)ticspersec.QuadPart;
  }
#else
  #include <sys/time.h>
//  class Timer{
//    time_t startusecs;
//  public:
//    Timer(){init();}
//    void init(){startusecs = getAbsoluteUSeconds();}
//    float getSeconds(){return (float)(getAbsoluteUSeconds() - startusecs) / 1000000.f;}
//    static time_t getAbsoluteUSeconds(){
//      struct timeval value;
//      gettimeofday(&value, NULL);
//      return value.tv_sec * 1000000 + value.tv_usec;
//    }
//  };
  typedef time_t CMLTimer;
  static CMLTimer CMLTimerGetAbsoluteUSeconds(){
    struct timeval value;
    gettimeofday(&value, NULL);
    return value.tv_sec * 1000000 + value.tv_usec;
  }
  static CMLTimer CMLStartTimer(){
    return CMLTimerGetAbsoluteUSeconds();
  }
  static float CMLTimerGetSeconds(CMLTimer timer){
    return (float)(CMLTimerGetAbsoluteUSeconds() - timer) / 1000000.f;
  }
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

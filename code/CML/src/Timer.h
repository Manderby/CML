
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.


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

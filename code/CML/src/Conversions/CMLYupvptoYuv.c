
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

#include "../CML.h"
#include "../StateMachine/CMLInternal.h"


#define CMLINTERNALYupvpToYuv(Yuv0, Yuv1, Yuv2, Yupvp0, Yupvp1, Yupvp2) \
  *Yuv0 = *Yupvp0;\
  *Yuv1 = *Yupvp1;\
  *Yuv2 = *Yupvp2 * 0.666666666666667f;



CML_HIDDEN CML_INLINE void cml_OneYupvpToYuv (float* CML_RESTRICT Yuv0, float* CML_RESTRICT Yuv1, float* CML_RESTRICT Yuv2, const float* CML_RESTRICT Yupvp0, const float* CML_RESTRICT Yupvp1, const float* CML_RESTRICT Yupvp2){
  CMLINTERNALYupvpToYuv(Yuv0, Yuv1, Yuv2, Yupvp0, Yupvp1, Yupvp2);
}

CML_HIDDEN CML_INLINE void cml_OneYupvpToYuv_SB(float* CML_RESTRICT buf0, float* CML_RESTRICT buf1, float* CML_RESTRICT buf2){
  CMLINTERNALYupvpToYuv(buf0, buf1, buf2, buf0, buf1, buf2);
}



CML_HIDDEN void cml_YupvpToYuv (CMLOutput out , CMLInput in, CMLSize count){
  if(cmlGetConverterError()){return;}

  while(count){
    const float* Yupvp0 = cmlNextConstFloatComponent(in);
    const float* Yupvp1 = cmlNextConstFloatComponent(in);
    const float* Yupvp2 = cmlNextConstFloatComponent(in);
    float* Yuv0 = cmlNextMutableFloatComponent(out);
    float* Yuv1 = cmlNextMutableFloatComponent(out);
    float* Yuv2 = cmlNextMutableFloatComponent(out);

    cml_OneYupvpToYuv(Yuv0, Yuv1, Yuv2, Yupvp0, Yupvp1, Yupvp2);

    count--;
  }

}

CML_HIDDEN void cml_YupvpToYuv_SB(CMLInputOutput buf, CMLSize count){
  if(cmlGetConverterError()){return;}

  while(count){
    float* buf0 = cmlNextMutableFloatComponent(buf);
    float* buf1 = cmlNextMutableFloatComponent(buf);
    float* buf2 = cmlNextMutableFloatComponent(buf);

    cml_OneYupvpToYuv_SB(buf0, buf1, buf2);

    count--;
  }

}



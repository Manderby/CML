
// (c) Manderim GmbH
// This is proprietary software. Any use without the explicit acknowledgement
// of the author of this software is prohibited and any liability is disclamed.
// Terms of a separate contract may apply.

#include "CML.h"
#include "CMLInternal.h"



#define CMLINTERNALYuvToYupvp(Yupvp0, Yupvp1, Yupvp2, Yuv0, Yuv1, Yuv2) \
  *Yupvp0 = *Yuv0;\
  *Yupvp1 = *Yuv1;\
  *Yupvp2 = *Yuv2 * 1.5f;



CML_HIDDEN CML_INLINE void cml_OneYuvToYupvp (float* CML_RESTRICT Yupvp0, float* CML_RESTRICT Yupvp1, float* CML_RESTRICT Yupvp2, const float* CML_RESTRICT Yuv0, const float* CML_RESTRICT Yuv1, const float* CML_RESTRICT Yuv2){
  CMLINTERNALYuvToYupvp(Yupvp0, Yupvp1, Yupvp2, Yuv0, Yuv1, Yuv2);
}

CML_HIDDEN CML_INLINE void cml_OneYuvToYupvp_SB(float* CML_RESTRICT buf0, float* CML_RESTRICT buf1, float* CML_RESTRICT buf2){
  CMLINTERNALYuvToYupvp(buf0, buf1, buf2, buf0, buf1, buf2);
}


CML_HIDDEN void cml_YuvToYupvp (CMLOutput out , CMLInput in, CMLSize count){
  if(cmlGetConverterError()){return;}

  while(count){
    const float* Yuv0 = cmlNextConstFloatComponent(in);
    const float* Yuv1 = cmlNextConstFloatComponent(in);
    const float* Yuv2 = cmlNextConstFloatComponent(in);
    float* Yupvp0 = cmlNextMutableFloatComponent(out);
    float* Yupvp1 = cmlNextMutableFloatComponent(out);
    float* Yupvp2 = cmlNextMutableFloatComponent(out);

    cml_OneYuvToYupvp(Yupvp0, Yupvp1, Yupvp2, Yuv0, Yuv1, Yuv2);

    count--;
  }

}

CML_HIDDEN void cml_YuvToYupvp_SB(CMLInputOutput buf, CMLSize count){
  if(cmlGetConverterError()){return;}

  while(count){
    float* buf0 = cmlNextMutableFloatComponent(buf);
    float* buf1 = cmlNextMutableFloatComponent(buf);
    float* buf2 = cmlNextMutableFloatComponent(buf);

    cml_OneYuvToYupvp_SB(buf0, buf1, buf2);

    count--;
  }

}

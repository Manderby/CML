
#include "../CML.h"
#include "CMLColorMachineState.h"



// All data here is normalized such that the Y-value at 555 nm should be 1.
// For 10 nm steps 560 nm is used.

// The following values are from www.cie.co.at

// Steps: 5nm
#define CML_X2VALENCES_CIE1931_MIN 380.f
#define CML_X2VALENCES_CIE1931_MAX 780.f
#define CML_X2VALENCES_CIE1931_NUM 81
CML_HIDDEN static const float x2valencesCIE1931[CML_X2VALENCES_CIE1931_NUM] = {
  0.001368f, 0.002236f, 0.004243f, 0.007650f, 0.014310f, 0.023190f, 0.043510f, 0.077630f, 0.134380f, 0.214770f,
  0.283900f, 0.328500f, 0.348280f, 0.348060f, 0.336200f, 0.318700f, 0.290800f, 0.251100f, 0.195360f, 0.142100f,
  0.095640f, 0.057950f, 0.032010f, 0.014700f, 0.004900f, 0.002400f, 0.009300f, 0.029100f, 0.063270f, 0.109600f,
  0.165500f, 0.225750f, 0.290400f, 0.359700f, 0.433450f, 0.512050f, 0.594500f, 0.678400f, 0.762100f, 0.842500f,
  0.916300f, 0.978600f, 1.026300f, 1.056700f, 1.062200f, 1.045600f, 1.002600f, 0.938400f, 0.854450f, 0.751400f,
  0.642400f, 0.541900f, 0.447900f, 0.360800f, 0.283500f, 0.218700f, 0.164900f, 0.121200f, 0.087400f, 0.063600f,
  0.046770f, 0.032900f, 0.022700f, 0.015840f, 0.011359f, 0.008111f, 0.005790f, 0.004109f, 0.002899f, 0.002049f,
  0.001440f, 0.001000f, 0.000690f, 0.000476f, 0.000332f, 0.000235f, 0.000166f, 0.000117f, 0.000083f, 0.000059f,
  0.000042f};

#define CML_Y2VALENCES_CIE1931_MIN 380.f
#define CML_Y2VALENCES_CIE1931_MAX 780.f
#define CML_Y2VALENCES_CIE1931_NUM 81
CML_HIDDEN static const float y2valencesCIE1931[CML_Y2VALENCES_CIE1931_NUM] = {
  0.000039f, 0.000064f, 0.000120f, 0.000217f, 0.000396f, 0.000640f, 0.001210f, 0.002180f, 0.004000f, 0.007300f,
  0.011600f, 0.016840f, 0.023000f, 0.029800f, 0.038000f, 0.048000f, 0.060000f, 0.073900f, 0.090980f, 0.112600f,
  0.139020f, 0.169300f, 0.208020f, 0.258600f, 0.323000f, 0.407300f, 0.503000f, 0.608200f, 0.710000f, 0.793200f,
  0.862000f, 0.914850f, 0.954000f, 0.980300f, 0.994950f, 1.000000f, 0.995000f, 0.978600f, 0.952000f, 0.915400f,
  0.870000f, 0.816300f, 0.757000f, 0.694900f, 0.631000f, 0.566800f, 0.503000f, 0.441200f, 0.381000f, 0.321000f,
  0.265000f, 0.217000f, 0.175000f, 0.138200f, 0.107000f, 0.081600f, 0.061000f, 0.044580f, 0.032000f, 0.023200f,
  0.017000f, 0.011920f, 0.008210f, 0.005723f, 0.004102f, 0.002929f, 0.002091f, 0.001484f, 0.001047f, 0.000740f,
  0.000520f, 0.000361f, 0.000249f, 0.000172f, 0.000120f, 0.000085f, 0.000060f, 0.000042f, 0.000030f, 0.000021f,
  0.000015f};

#define CML_Z2VALENCES_CIE1931_MIN 380.f
#define CML_Z2VALENCES_CIE1931_MAX 645.f
#define CML_Z2VALENCES_CIE1931_NUM 54
CML_HIDDEN static const float z2valencesCIE1931[CML_Z2VALENCES_CIE1931_NUM] = {
  0.006450f, 0.010550f, 0.020050f, 0.036210f, 0.067850f, 0.110200f, 0.207400f, 0.371300f, 0.645600f, 1.039050f,
  1.385600f, 1.622960f, 1.747060f, 1.782600f, 1.772110f, 1.744100f, 1.669200f, 1.528100f, 1.287640f, 1.041900f,
  0.812950f, 0.616200f, 0.465180f, 0.353300f, 0.272000f, 0.212300f, 0.158200f, 0.111700f, 0.078250f, 0.057250f,
  0.042160f, 0.029840f, 0.020300f, 0.013400f, 0.008750f, 0.005750f, 0.003900f, 0.002750f, 0.002100f, 0.001800f,
  0.001650f, 0.001400f, 0.001100f, 0.001000f, 0.000800f, 0.000600f, 0.000340f, 0.000240f, 0.000190f, 0.000100f, 
  0.000050f, 0.000030f, 0.000020f, 0.000010f};


// Steps: 5nm
#define CML_X10VALENCES_CIE1964_MIN 380.f
#define CML_X10VALENCES_CIE1964_MAX 780.f
#define CML_X10VALENCES_CIE1964_NUM 81
CML_HIDDEN static const float x10valencesCIE1964[CML_X10VALENCES_CIE1964_NUM] = {
  0.000160f, 0.000662f, 0.002362f, 0.007242f, 0.019110f, 0.043400f, 0.084736f, 0.140638f, 0.204492f, 0.264737f,
  0.314679f, 0.357719f, 0.383734f, 0.386726f, 0.370702f, 0.342957f, 0.302273f, 0.254085f, 0.195618f, 0.132349f,
  0.080507f, 0.041072f, 0.016172f, 0.005132f, 0.003816f, 0.015444f, 0.037465f, 0.071358f, 0.117749f, 0.172953f,
  0.236491f, 0.304213f, 0.376772f, 0.451584f, 0.529826f, 0.616053f, 0.705224f, 0.793832f, 0.878655f, 0.951162f,
  1.014160f, 1.074300f, 1.118520f, 1.134300f, 1.123990f, 1.089100f, 1.030480f, 0.950740f, 0.856297f, 0.754930f,
  0.647467f, 0.535110f, 0.431567f, 0.343690f, 0.268329f, 0.204300f, 0.152568f, 0.112210f, 0.081261f, 0.057930f,
  0.040851f, 0.028623f, 0.019941f, 0.013842f, 0.009577f, 0.006605f, 0.004553f, 0.003145f, 0.002175f, 0.001506f,
  0.001045f, 0.000727f, 0.000508f, 0.000356f, 0.000251f, 0.000178f, 0.000126f, 0.000090f, 0.000065f, 0.000046f,
  0.000033f};

#define CML_Y10VALENCES_CIE1964_MIN 380.f
#define CML_Y10VALENCES_CIE1964_MAX 780.f
#define CML_Y10VALENCES_CIE1964_NUM 81
CML_HIDDEN static const float y10valencesCIE1964[CML_Y10VALENCES_CIE1964_NUM] = {
  0.000017f, 0.000072f, 0.000253f, 0.000769f, 0.002004f, 0.004509f, 0.008756f, 0.014456f, 0.021391f, 0.029497f,
  0.038676f, 0.049602f, 0.062077f, 0.074704f, 0.089456f, 0.106256f, 0.128201f, 0.152761f, 0.185190f, 0.219940f,
  0.253589f, 0.297665f, 0.339133f, 0.395379f, 0.460777f, 0.531360f, 0.606741f, 0.685660f, 0.761757f, 0.823330f,
  0.875211f, 0.923810f, 0.961988f, 0.982200f, 0.991761f, 0.999110f, 0.997340f, 0.982380f, 0.955552f, 0.915175f,
  0.868934f, 0.825623f, 0.777405f, 0.720353f, 0.658341f, 0.593878f, 0.527963f, 0.461834f, 0.398057f, 0.339554f,
  0.283493f, 0.228254f, 0.179828f, 0.140211f, 0.107633f, 0.081187f, 0.060281f, 0.044096f, 0.031800f, 0.022602f,
  0.015905f, 0.011130f, 0.007749f, 0.005375f, 0.003718f, 0.002565f, 0.001768f, 0.001222f, 0.000846f, 0.000586f,
  0.000407f, 0.000284f, 0.000199f, 0.000140f, 0.000098f, 0.000070f, 0.000050f, 0.000036f, 0.000025f, 0.000018f,
  0.000013f};

#define CML_Z10VALENCES_CIE1964_MIN 380.f
#define CML_Z10VALENCES_CIE1964_MAX 555.f
#define CML_Z10VALENCES_CIE1964_NUM 36
CML_HIDDEN static const float z10valencesCIE1964[CML_Z10VALENCES_CIE1964_NUM] = {
  0.000705f, 0.002928f, 0.010482f, 0.032344f, 0.086011f, 0.197120f, 0.389366f, 0.656760f, 0.972542f, 1.282500f,
  1.553480f, 1.798500f, 1.967280f, 2.027300f, 1.994800f, 1.900700f, 1.745370f, 1.554900f, 1.317560f, 1.030200f,
  0.772125f, 0.570060f, 0.415254f, 0.302356f, 0.218502f, 0.159249f, 0.112044f, 0.082248f, 0.060709f, 0.043050f,
  0.030451f, 0.020584f, 0.013676f, 0.007918f, 0.003988f, 0.001091f};


// The following values are from ISO-13655
// Warning: These are precomputed with D50!!!

//// Steps: 10nm
//#define CML_X2VALENCES_ISO13655_MIN 370.f
//#define CML_X2VALENCES_ISO13655_MAX 770.f
//#define CML_X2VALENCES_ISO13655_NUM 41
//CML_HIDDEN static const float x2valencesISO13655[CML_X2VALENCES_ISO13655_NUM] = {
//  0.001f, 0.003f, 0.012f, 0.060f, 0.234f, 0.775f, 1.610f, 2.453f, 2.777f, 2.500f,
//  1.717f, 0.861f, 0.283f, 0.040f, 0.088f, 0.593f, 1.590f, 2.799f, 4.207f, 5.657f,
//  7.132f, 8.540f, 9.255f, 9.835f, 9.469f, 8.009f, 5.926f, 4.171f, 2.609f, 1.541f,
//  0.855f, 0.434f, 0.194f, 0.097f, 0.050f, 0.022f, 0.012f, 0.006f, 0.002f, 0.001f,
//  0.001f};
//
//#define CML_Y2VALENCES_ISO13655_MIN 400.f
//#define CML_Y2VALENCES_ISO13655_MAX 750.f
//#define CML_Y2VALENCES_ISO13655_NUM 36
//CML_HIDDEN static const float y2valencesISO13655[CML_Y2VALENCES_ISO13655_NUM] = {
//  0.002f, 0.006f, 0.023f, 0.066f, 0.162f, 0.313f, 0.514f, 0.798f, 1.239f, 1.839f,
//  2.948f, 4.632f, 6.587f, 8.308f, 9.197f, 9.650f, 9.471f, 8.902f, 8.112f, 6.829f,
//  5.838f, 4.753f, 3.573f, 2.443f, 1.629f, 0.984f, 0.570f, 0.313f, 0.158f, 0.070f,
//  0.035f, 0.018f, 0.008f, 0.004f, 0.002f, 0.001f};
//
//#define CML_Z2VALENCES_ISO13655_MIN 360.f
//#define CML_Z2VALENCES_ISO13655_MAX 630.f
//#define CML_Z2VALENCES_ISO13655_NUM 28
//CML_HIDDEN static const float z2valencesISO13655[CML_Z2VALENCES_ISO13655_NUM] = {
//   0.001f,  0.005f, 0.013f, 0.057f, 0.285f, 1.113f, 3.723f, 7.862f, 12.309f, 14.647f,
//  14.346f, 11.299f, 7.309f, 4.128f, 2.466f, 1.447f, 0.736f, 0.401f,  0.196f,  0.085f,
//   0.037f,  0.020f, 0.015f, 0.010f, 0.007f, 0.004f, 0.002f, 0.001f};


// The following values are from www.cvrl.org

// Step: 10 nm
#define CML_X2VALENCES_JUDD1951_MIN 370.f
#define CML_X2VALENCES_JUDD1951_MAX 770.f
#define CML_X2VALENCES_JUDD1951_NUM 41
CML_HIDDEN static const float x2valencesJudd1951[CML_X2VALENCES_JUDD1951_NUM] = {
  0.0008f, 0.0045f, 0.0201f, 0.0611f, 0.1267f, 0.2285f, 0.3081f, 0.3312f, 0.2888f, 0.2323f,
  0.1745f, 0.0920f, 0.0318f, 0.0048f, 0.0093f, 0.0636f, 0.1668f, 0.2926f, 0.4364f, 0.5970f,
  0.7642f, 0.9159f, 1.0225f, 1.0544f, 0.9922f, 0.8432f, 0.6327f, 0.4404f, 0.2787f, 0.1619f,
  0.0858f, 0.0459f, 0.0222f, 0.0113f, 0.0057f, 0.0028f, 0.0015f, 0.0005f, 0.0003f, 0.0002f,
  0.0001f};
#define CML_Y2VALENCES_JUDD1951_MIN 370.f
#define CML_Y2VALENCES_JUDD1951_MAX 760.f
#define CML_Y2VALENCES_JUDD1951_NUM 40
CML_HIDDEN static const float y2valencesJudd1951[CML_Y2VALENCES_JUDD1951_NUM] = {
  0.0001f, 0.0004f, 0.0015f, 0.0045f, 0.0093f, 0.0175f, 0.0273f, 0.0379f, 0.0468f, 0.0600f,
  0.0910f, 0.1390f, 0.2080f, 0.3230f, 0.5030f, 0.7100f, 0.8620f, 0.9540f, 0.9950f, 0.9950f,
  0.9520f, 0.8700f, 0.7570f, 0.6310f, 0.5030f, 0.3810f, 0.2650f, 0.1750f, 0.1070f, 0.0610f,
  0.0320f, 0.0170f, 0.0082f, 0.0041f, 0.0021f, 0.0011f, 0.0005f, 0.0002f, 0.0001f, 0.0001f};
#define CML_Z2VALENCES_JUDD1951_MIN 370.f
#define CML_Z2VALENCES_JUDD1951_MAX 630.f
#define CML_Z2VALENCES_JUDD1951_NUM 27
CML_HIDDEN static const float z2valencesJudd1951[CML_Z2VALENCES_JUDD1951_NUM] = {
  0.0046f, 0.0224f, 0.0925f, 0.2799f, 0.5835f, 1.0622f, 1.4526f, 1.6064f, 1.4717f, 1.2880f,
  1.1133f, 0.7552f, 0.4461f, 0.2644f, 0.1541f, 0.0763f, 0.0412f, 0.0200f, 0.0088f, 0.0039f,
  0.0020f, 0.0016f, 0.0011f, 0.0007f, 0.0003f, 0.0002f, 0.0001f};



// Step: 5 nm
#define CML_X2VALENCES_JUDDVOS1978_MIN 380.f
#define CML_X2VALENCES_JUDDVOS1978_MAX 825.f
#define CML_X2VALENCES_JUDDVOS1978_NUM 90
CML_HIDDEN static const float x2valencesJuddVos1978[CML_X2VALENCES_JUDDVOS1978_NUM] = {
  2.689900e-003f, 5.310500e-003f, 1.078100e-002f, 2.079200e-002f, 3.798100e-002f, 6.315700e-002f, 9.994100e-002f, 1.582400e-001f, 2.294800e-001f, 2.810800e-001f,
  3.109500e-001f, 3.307200e-001f, 3.333600e-001f, 3.167200e-001f, 2.888200e-001f, 2.596900e-001f, 2.327600e-001f, 2.099900e-001f, 1.747600e-001f, 1.328700e-001f,
  9.194400e-002f, 5.698500e-002f, 3.173100e-002f, 1.461300e-002f, 4.849100e-003f, 2.321500e-003f, 9.289900e-003f, 2.927800e-002f, 6.379100e-002f, 1.108100e-001f,
  1.669200e-001f, 2.276800e-001f, 2.926900e-001f, 3.622500e-001f, 4.363500e-001f, 5.151300e-001f, 5.974800e-001f, 6.812100e-001f, 7.642500e-001f, 8.439400e-001f,
  9.163500e-001f, 9.770300e-001f, 1.023000e+000f, 1.051300e+000f, 1.055000e+000f, 1.036200e+000f, 9.923900e-001f, 9.286100e-001f, 8.434600e-001f, 7.398300e-001f,
  6.328900e-001f, 5.335100e-001f, 4.406200e-001f, 3.545300e-001f, 2.786200e-001f, 2.148500e-001f, 1.616100e-001f, 1.182000e-001f, 8.575300e-002f, 6.307700e-002f,
  4.583400e-002f, 3.205700e-002f, 2.218700e-002f, 1.561200e-002f, 1.109800e-002f, 7.923300e-003f, 5.653100e-003f, 4.003900e-003f, 2.825300e-003f, 1.994700e-003f,
  1.399400e-003f, 9.698000e-004f, 6.684700e-004f, 4.614100e-004f, 3.207300e-004f, 2.257300e-004f, 1.597300e-004f, 1.127500e-004f, 7.951300e-005f, 5.608700e-005f,
  3.954100e-005f, 2.785200e-005f, 1.959700e-005f, 1.377000e-005f, 9.670000e-006f, 6.791800e-006f, 4.770600e-006f, 3.355000e-006f, 2.353400e-006f, 1.637700e-006f};
#define CML_Y2VALENCES_JUDDVOS1978_MIN 380.f
#define CML_Y2VALENCES_JUDDVOS1978_MAX 825.f
#define CML_Y2VALENCES_JUDDVOS1978_NUM 90
CML_HIDDEN static const float y2valencesJuddVos1978[CML_Y2VALENCES_JUDDVOS1978_NUM] = {
  2.000000e-004f, 3.955600e-004f, 8.000000e-004f, 1.545700e-003f, 2.800000e-003f, 4.656200e-003f, 7.400000e-003f, 1.177900e-002f, 1.750000e-002f, 2.267800e-002f,
  2.730000e-002f, 3.258400e-002f, 3.790000e-002f, 4.239100e-002f, 4.680000e-002f, 5.212200e-002f, 6.000000e-002f, 7.294200e-002f, 9.098000e-002f, 1.128400e-001f,
  1.390200e-001f, 1.698700e-001f, 2.080200e-001f, 2.580800e-001f, 3.230000e-001f, 4.054000e-001f, 5.030000e-001f, 6.081100e-001f, 7.100000e-001f, 7.951000e-001f,
  8.620000e-001f, 9.150500e-001f, 9.540000e-001f, 9.800400e-001f, 9.949500e-001f, 1.000100e+000f, 9.950000e-001f, 9.787500e-001f, 9.520000e-001f, 9.155800e-001f,
  8.700000e-001f, 8.162300e-001f, 7.570000e-001f, 6.948300e-001f, 6.310000e-001f, 5.665400e-001f, 5.030000e-001f, 4.417200e-001f, 3.810000e-001f, 3.205200e-001f,
  2.650000e-001f, 2.170200e-001f, 1.750000e-001f, 1.381200e-001f, 1.070000e-001f, 8.165200e-002f, 6.100000e-002f, 4.432700e-002f, 3.200000e-002f, 2.345400e-002f,
  1.700000e-002f, 1.187200e-002f, 8.210000e-003f, 5.772300e-003f, 4.102000e-003f, 2.929100e-003f, 2.091000e-003f, 1.482200e-003f, 1.047000e-003f, 7.401500e-004f,
  5.200000e-004f, 3.609300e-004f, 2.492000e-004f, 1.723100e-004f, 1.200000e-004f, 8.462000e-005f, 6.000000e-005f, 4.244600e-005f, 3.000000e-005f, 2.121000e-005f,
  1.498900e-005f, 1.058400e-005f, 7.465600e-006f, 5.259200e-006f, 3.702800e-006f, 2.607600e-006f, 1.836500e-006f, 1.295000e-006f, 9.109200e-007f, 6.356400e-007f};
#define CML_Z2VALENCES_JUDDVOS1978_MIN 380.f
#define CML_Z2VALENCES_JUDDVOS1978_MAX 825.f
#define CML_Z2VALENCES_JUDDVOS1978_NUM 90
CML_HIDDEN static const float z2valencesJuddVos1978[CML_Z2VALENCES_JUDDVOS1978_NUM] = {
  1.226000e-002f, 2.422200e-002f, 4.925000e-002f, 9.513500e-002f, 1.740900e-001f, 2.901300e-001f, 4.605300e-001f, 7.316600e-001f, 1.065800e+000f, 1.314600e+000f,
  1.467200e+000f, 1.579600e+000f, 1.616600e+000f, 1.568200e+000f, 1.471700e+000f, 1.374000e+000f, 1.291700e+000f, 1.235600e+000f, 1.113800e+000f, 9.422000e-001f,
  7.559600e-001f, 5.864000e-001f, 4.466900e-001f, 3.411600e-001f, 2.643700e-001f, 2.059400e-001f, 1.544500e-001f, 1.091800e-001f, 7.658500e-002f, 5.622700e-002f,
  4.136600e-002f, 2.935300e-002f, 2.004200e-002f, 1.331200e-002f, 8.782300e-003f, 5.857300e-003f, 4.049300e-003f, 2.921700e-003f, 2.277100e-003f, 1.970600e-003f,
  1.806600e-003f, 1.544900e-003f, 1.234800e-003f, 1.117700e-003f, 9.056400e-004f, 6.946700e-004f, 4.288500e-004f, 3.181700e-004f, 2.559800e-004f, 1.567900e-004f,
  9.769400e-005f, 6.894400e-005f, 5.116500e-005f, 3.601600e-005f, 2.423800e-005f, 1.691500e-005f, 1.190600e-005f, 8.148900e-006f, 5.600600e-006f, 3.954400e-006f,
  2.791200e-006f, 1.917600e-006f, 1.313500e-006f, 9.151900e-007f, 6.476700e-007f, 4.635200e-007f, 3.330400e-007f, 2.382300e-007f, 1.702600e-007f, 1.220700e-007f,
  8.710700e-008f, 6.145500e-008f, 4.316200e-008f, 3.037900e-008f, 2.155400e-008f, 1.549300e-008f, 1.120400e-008f, 8.087300e-009f, 5.834000e-009f, 4.211000e-009f,
  3.038300e-009f, 2.190700e-009f, 1.577800e-009f, 1.134800e-009f, 8.156500e-010f, 5.862600e-010f, 4.213800e-010f, 3.031900e-010f, 2.175300e-010f, 1.547600e-010f};


// Step: 5 nm
//#define CML_X2VALENCES_SHAWFAIRCHILD1997_MIN 400.f
//#define CML_X2VALENCES_SHAWFAIRCHILD1997_MAX 700.f
//#define CML_X2VALENCES_SHAWFAIRCHILD1997_NUM 61
//CML_HIDDEN static const float x2valencesShawFairchild1997[CML_X2VALENCES_SHAWFAIRCHILD1997_NUM] = {
//   0.050035085f,  0.10599540f,  0.17570524f,  0.26369069f,  0.34385256f,  0.36314044f,  0.35022338f,  0.35921696f,   0.37057582f,   0.37027683f,
//   0.31092719f,   0.24467905f,  0.21495057f,  0.16408854f,  0.15609086f,  0.10496585f,  0.053550350f, 0.016029866f, -0.010473666f, -0.020635411f,
//  -0.020599591f, -0.010774255f, 0.013507015f, 0.045305699f, 0.082609321f, 0.13244251f,  0.18966495f,  0.24710489f,   0.30272442f,   0.36362744f,
//   0.43329425f,   0.50816654f,  0.57883305f,  0.66085495f,  0.75701632f,  0.84336950f,  0.91608703f,  0.98348582f,   1.0386456f,    1.0699974f,
//   1.0751974f,    1.0492333f,   1.0010173f,   0.92955516f,  0.83907524f,  0.74332961f,  0.64179542f,  0.53031723f,   0.42814376f,   0.34048130f,
//   0.26368241f,   0.19677558f,  0.14402031f,  0.10472063f,  0.076398767f, 0.054311075f, 0.037000030f, 0.026240015f,  0.018750015f,  0.012892199f,
//   0.0081198003f};
//#define CML_Y2VALENCES_SHAWFAIRCHILD1997_MIN 400.f
//#define CML_Y2VALENCES_SHAWFAIRCHILD1997_MAX 700.f
//#define CML_Y2VALENCES_SHAWFAIRCHILD1997_NUM 61
//CML_HIDDEN static const float y2valencesShawFairchild1997[CML_Y2VALENCES_SHAWFAIRCHILD1997_NUM] = {
//  0.00073439190f, 0.0010295739f, 0.0011050375f, -0.00057123313f, -0.0015421159f, -0.0050492258f, -0.0060441241f, -0.0050340813f, -0.00046015829f, 0.0043453053f,
//  0.014594307f,   0.028653705f,  0.047841334f,   0.078039315f,    0.11339641f,    0.15326829f,    0.18931877f,    0.22596008f,    0.26950734f,    0.32894461f,
//  0.39924943f,    0.48161678f,   0.56603317f,    0.65284913f,     0.73864212f,    0.80870955f,    0.86388621f,    0.90168525f,    0.92331427f,    0.94508269f,
//  0.96035974f,    0.96084837f,   0.94474215f,    0.93248079f,     0.92686312f,    0.89683591f,    0.85193527f,    0.81446493f,    0.77206051f,    0.71732417f,
//  0.65749412f,    0.59544590f,   0.53033945f,    0.46382662f,     0.39929743f,    0.33905951f,    0.28179144f,    0.22775797f,    0.18104592f,    0.14195030f,
//  0.10887196f,    0.081491712f,  0.059933233f,   0.043516174f,    0.031399280f,   0.022402933f,   0.015787610f,   0.011178068f,   0.0078482427f,  0.0054361119f,
//  0.0036285556f};
//#define CML_Z2VALENCES_SHAWFAIRCHILD1997_MIN 400.f
//#define CML_Z2VALENCES_SHAWFAIRCHILD1997_MAX 700.f
//#define CML_Z2VALENCES_SHAWFAIRCHILD1997_NUM 61
//CML_HIDDEN static const float z2valencesShawFairchild1997[CML_Z2VALENCES_SHAWFAIRCHILD1997_NUM] = {
//  0.19346810f,     0.37355444f,    0.62641781f,    0.98559734f,    1.3578634f,     1.5413908f,     1.6258281f,      1.7422823f,      1.8184109f,      1.7982693f,
//  1.6624945f,      1.4917210f,     1.3537111f,     1.2543216f,     1.1444894f,     0.94078221f,    0.73058355f,     0.55774101f,     0.42026628f,     0.31970216f,
//  0.24388223f,     0.18951860f,    0.14567319f,    0.11603887f,    0.094972125f,   0.077803903f,   0.065288720f,    0.055235267f,    0.046945157f,    0.039405440f,
//  0.033042398f,    0.026944585f,   0.021626844f,   0.016807242f,   0.011642648f,   0.0061489002f,  0.00061480026f, -0.0044002687f,  -0.0090514735f,  -0.013048603f,
//  -0.016063598f,  -0.018035874f,  -0.019053770f,  -0.019163305f,  -0.018371066f,  -0.016810570f,  -0.014805852f,   -0.012650736f,   -0.010513405f,   -0.0085481723f,
//  -0.0067628649f, -0.0051813692f, -0.0038792081f, -0.0028536093f, -0.0020731313f, -0.0014924891f, -0.0010704383f,  -0.00075273042f, -0.00052400943f, -0.00036054897f,
//  -0.00025295701f};





CML_HIDDEN void cml_recomputeObserver(CMLColorMachine* cm){
  if(cm->recomputationLockCount){cm->recomputationMask |= CML_COLORMACHINE_RECOMPUTE_OBSERVER; return;}
  
  // There is nothing to be done here. At least not currently. Maybe in the
  // future. Note: Photopic and Scotopic.
  
  cml_recomputeIllumination(cm);
}


CML_API void cmlCreateSpecDistFunctions(CMLFunction* functions[3], CMLObserverType observer){
  switch(observer){
//  case CML_OBSERVER_2DEG_1931:
//    functions[0] = new CMLArrayFunction(CML_X2VALENCES_1931_MIN, CML_X2VALENCES_1931_MAX, CMLArray(x2valences1931, CML_FALSE, CML_X2VALENCES_1931_NUM), CML_INTERPOLATION_LINEAR, CML_EXTRAPOLATION_LINEAR_ZERO);
//    functions[1] = new CMLArrayFunction(CML_Y2VALENCES_1931_MIN, CML_Y2VALENCES_1931_MAX, CMLArray(y2valences1931, CML_FALSE, CML_Y2VALENCES_1931_NUM), CML_INTERPOLATION_LINEAR, CML_EXTRAPOLATION_LINEAR_ZERO);
//    functions[2] = new CMLArrayFunction(CML_Z2VALENCES_1931_MIN, CML_Z2VALENCES_1931_MAX, CMLArray(z2valences1931, CML_FALSE, CML_Z2VALENCES_1931_NUM), CML_INTERPOLATION_LINEAR, CML_EXTRAPOLATION_LINEAR_ZERO);
//    break;
//  case CML_OBSERVER_10DEG_1964:
//    functions[0] = new CMLArrayFunction(CML_X10VALENCES_1964_MIN, CML_X10VALENCES_1964_MAX, CMLArray(x10valences1964, CML_FALSE, CML_X10VALENCES_1964_NUM), CML_INTERPOLATION_LINEAR, CML_EXTRAPOLATION_LINEAR_ZERO);
//    functions[1] = new CMLArrayFunction(CML_Y10VALENCES_1964_MIN, CML_Y10VALENCES_1964_MAX, CMLArray(y10valences1964, CML_FALSE, CML_Y10VALENCES_1964_NUM), CML_INTERPOLATION_LINEAR, CML_EXTRAPOLATION_LINEAR_ZERO);
//    functions[2] = new CMLArrayFunction(CML_Z10VALENCES_1964_MIN, CML_Z10VALENCES_1964_MAX, CMLArray(z10valences1964, CML_FALSE, CML_Z10VALENCES_1964_NUM), CML_INTERPOLATION_LINEAR, CML_EXTRAPOLATION_LINEAR_ZERO);
//    break;
  case CML_OBSERVER_2DEG_CIE_1931:
    functions[0] = cmlCreateArrayFunction(x2valencesCIE1931, CML_FALSE, CML_X2VALENCES_CIE1931_NUM, CML_X2VALENCES_CIE1931_MIN, CML_X2VALENCES_CIE1931_MAX, CML_INTERPOLATION_LINEAR, CML_EXTRAPOLATION_LINEAR_ZERO, CML_EXTRAPOLATION_LINEAR_ZERO);
    functions[1] = cmlCreateArrayFunction(y2valencesCIE1931, CML_FALSE, CML_Y2VALENCES_CIE1931_NUM, CML_Y2VALENCES_CIE1931_MIN, CML_Y2VALENCES_CIE1931_MAX, CML_INTERPOLATION_LINEAR, CML_EXTRAPOLATION_LINEAR_ZERO, CML_EXTRAPOLATION_LINEAR_ZERO);
    functions[2] = cmlCreateArrayFunction(z2valencesCIE1931, CML_FALSE, CML_Z2VALENCES_CIE1931_NUM, CML_Z2VALENCES_CIE1931_MIN, CML_Z2VALENCES_CIE1931_MAX, CML_INTERPOLATION_LINEAR, CML_EXTRAPOLATION_LINEAR_ZERO, CML_EXTRAPOLATION_LINEAR_ZERO);
    break;
  case CML_OBSERVER_10DEG_CIE_1964:
    functions[0] = cmlCreateArrayFunction(x10valencesCIE1964, CML_FALSE, CML_X10VALENCES_CIE1964_NUM, CML_X10VALENCES_CIE1964_MIN, CML_X10VALENCES_CIE1964_MAX, CML_INTERPOLATION_LINEAR, CML_EXTRAPOLATION_LINEAR_ZERO, CML_EXTRAPOLATION_LINEAR_ZERO);
    functions[1] = cmlCreateArrayFunction(y10valencesCIE1964, CML_FALSE, CML_Y10VALENCES_CIE1964_NUM, CML_Y10VALENCES_CIE1964_MIN, CML_Y10VALENCES_CIE1964_MAX, CML_INTERPOLATION_LINEAR, CML_EXTRAPOLATION_LINEAR_ZERO, CML_EXTRAPOLATION_LINEAR_ZERO);
    functions[2] = cmlCreateArrayFunction(z10valencesCIE1964, CML_FALSE, CML_Z10VALENCES_CIE1964_NUM, CML_Z10VALENCES_CIE1964_MIN, CML_Z10VALENCES_CIE1964_MAX, CML_INTERPOLATION_LINEAR, CML_EXTRAPOLATION_LINEAR_ZERO, CML_EXTRAPOLATION_LINEAR_ZERO);
    break;
//  case CML_OBSERVER_2DEG_ISO_13655:
//    functions[0] = cmlCreateArrayFunction(x2valencesISO13655, CML_FALSE, CML_X2VALENCES_ISO13655_NUM, CML_X2VALENCES_ISO13655_MIN, CML_X2VALENCES_ISO13655_MAX, CML_INTERPOLATION_LINEAR, CML_EXTRAPOLATION_LINEAR_ZERO, CML_EXTRAPOLATION_LINEAR_ZERO);
//    functions[1] = cmlCreateArrayFunction(y2valencesISO13655, CML_FALSE, CML_Y2VALENCES_ISO13655_NUM, CML_Y2VALENCES_ISO13655_MIN, CML_Y2VALENCES_ISO13655_MAX, CML_INTERPOLATION_LINEAR, CML_EXTRAPOLATION_LINEAR_ZERO, CML_EXTRAPOLATION_LINEAR_ZERO);
//    functions[2] = cmlCreateArrayFunction(z2valencesISO13655, CML_FALSE, CML_Z2VALENCES_ISO13655_NUM, CML_Z2VALENCES_ISO13655_MIN, CML_Z2VALENCES_ISO13655_MAX, CML_INTERPOLATION_LINEAR, CML_EXTRAPOLATION_LINEAR_ZERO, CML_EXTRAPOLATION_LINEAR_ZERO);
//    break;
  case CML_OBSERVER_2DEG_JUDD_1951:
    functions[0] = cmlCreateArrayFunction(x2valencesJudd1951, CML_FALSE, CML_X2VALENCES_JUDD1951_NUM, CML_X2VALENCES_JUDD1951_MIN, CML_X2VALENCES_JUDD1951_MAX, CML_INTERPOLATION_LINEAR, CML_EXTRAPOLATION_LINEAR_ZERO, CML_EXTRAPOLATION_LINEAR_ZERO);
    functions[1] = cmlCreateArrayFunction(y2valencesJudd1951, CML_FALSE, CML_Y2VALENCES_JUDD1951_NUM, CML_Y2VALENCES_JUDD1951_MIN, CML_Y2VALENCES_JUDD1951_MAX, CML_INTERPOLATION_LINEAR, CML_EXTRAPOLATION_LINEAR_ZERO, CML_EXTRAPOLATION_LINEAR_ZERO);
    functions[2] = cmlCreateArrayFunction(z2valencesJudd1951, CML_FALSE, CML_Z2VALENCES_JUDD1951_NUM, CML_Z2VALENCES_JUDD1951_MIN, CML_Z2VALENCES_JUDD1951_MAX, CML_INTERPOLATION_LINEAR, CML_EXTRAPOLATION_LINEAR_ZERO, CML_EXTRAPOLATION_LINEAR_ZERO);
    break;
  case CML_OBSERVER_2DEG_JUDD_VOS_1978:
    functions[0] = cmlCreateArrayFunction(x2valencesJuddVos1978, CML_FALSE, CML_X2VALENCES_JUDDVOS1978_NUM, CML_X2VALENCES_JUDDVOS1978_MIN, CML_X2VALENCES_JUDDVOS1978_MAX, CML_INTERPOLATION_LINEAR, CML_EXTRAPOLATION_LINEAR_ZERO, CML_EXTRAPOLATION_LINEAR_ZERO);
    functions[1] = cmlCreateArrayFunction(y2valencesJuddVos1978, CML_FALSE, CML_Y2VALENCES_JUDDVOS1978_NUM, CML_Y2VALENCES_JUDDVOS1978_MIN, CML_Y2VALENCES_JUDDVOS1978_MAX, CML_INTERPOLATION_LINEAR, CML_EXTRAPOLATION_LINEAR_ZERO, CML_EXTRAPOLATION_LINEAR_ZERO);
    functions[2] = cmlCreateArrayFunction(z2valencesJuddVos1978, CML_FALSE, CML_Z2VALENCES_JUDDVOS1978_NUM, CML_Z2VALENCES_JUDDVOS1978_MIN, CML_Z2VALENCES_JUDDVOS1978_MAX, CML_INTERPOLATION_LINEAR, CML_EXTRAPOLATION_LINEAR_ZERO, CML_EXTRAPOLATION_LINEAR_ZERO);
    break;
//  case CML_OBSERVER_2DEG_STILES_BURCH_1955:
//    functions[0] = new CMLArrayFunction(CML_X2VALENCES_STILESBURCH1955_MIN, CML_X2VALENCES_STILESBURCH1955_MAX, CMLArray(x2valencesStilesBurch1955, CML_FALSE, CML_X2VALENCES_STILESBURCH1955_NUM), CML_INTERPOLATION_LINEAR, CML_EXTRAPOLATION_LINEAR_ZERO);
//    functions[1] = new CMLArrayFunction(CML_Y2VALENCES_STILESBURCH1955_MIN, CML_Y2VALENCES_STILESBURCH1955_MAX, CMLArray(y2valencesStilesBurch1955, CML_FALSE, CML_Y2VALENCES_STILESBURCH1955_NUM), CML_INTERPOLATION_LINEAR, CML_EXTRAPOLATION_LINEAR_ZERO);
//    functions[2] = new CMLArrayFunction(CML_Z2VALENCES_STILESBURCH1955_MIN, CML_Z2VALENCES_STILESBURCH1955_MAX, CMLArray(z2valencesStilesBurch1955, CML_FALSE, CML_Z2VALENCES_STILESBURCH1955_NUM), CML_INTERPOLATION_LINEAR, CML_EXTRAPOLATION_LINEAR_ZERO);
//    break;
//  case CML_OBSERVER_2DEG_SHAW_FAIRCHILD_1997:
//    functions[0] = new CMLArrayFunction(CML_X2VALENCES_SHAWFAIRCHILD1997_MIN, CML_X2VALENCES_SHAWFAIRCHILD1997_MAX, CMLArray(x2valencesShawFairchild1997, CML_FALSE, CML_X2VALENCES_SHAWFAIRCHILD1997_NUM), CML_INTERPOLATION_LINEAR, CML_EXTRAPOLATION_LINEAR_ZERO);
//    functions[1] = new CMLArrayFunction(CML_Y2VALENCES_SHAWFAIRCHILD1997_MIN, CML_Y2VALENCES_SHAWFAIRCHILD1997_MAX, CMLArray(y2valencesShawFairchild1997, CML_FALSE, CML_Y2VALENCES_SHAWFAIRCHILD1997_NUM), CML_INTERPOLATION_LINEAR, CML_EXTRAPOLATION_LINEAR_ZERO);
//    functions[2] = new CMLArrayFunction(CML_Z2VALENCES_SHAWFAIRCHILD1997_MIN, CML_Z2VALENCES_SHAWFAIRCHILD1997_MAX, CMLArray(z2valencesShawFairchild1997, CML_FALSE, CML_Z2VALENCES_SHAWFAIRCHILD1997_NUM), CML_INTERPOLATION_LINEAR, CML_EXTRAPOLATION_LINEAR_ZERO);
//    break;
  default:
    functions[0] = CML_NULL;
    functions[1] = CML_NULL;
    functions[2] = CML_NULL;
    #if CML_DEBUG
      cmlError("Observer state unknown");
    #endif
    break;
  }
}



//CML_API CMLBool cmlGetRadiometricComputation(CMLColorMachine* cm){
//  return cm->observer.radiometric;
//}
//
//CML_API void cmlSetRadiometricComputation(CMLColorMachine* cm, CMLBool newradiometric){
//  cm->observer.radiometric = newradiometric;
//  cml_recomputeObserver(cm);
//}


CML_API const CMLObserver*    cmlGetObserver(const CMLColorMachine* cm){
  return &(cm->observer);
}


CML_API CMLObserverType cmlGetObserverType(const CMLColorMachine* cm){
  return cml_GetObserverType(&(cm->observer));
}


CML_API void cmlSetObserverType(CMLColorMachine* cm, CMLObserverType newobserverType){

    float newcolorimetricBase = cmlGetObserverColorimetricBase(&(cm->observer));
    CMLIllumination newillumination;
    cmlCreateIlluminationDuplicate(&newillumination, cmlGetReferenceIllumination(&(cm->observer)));
    cmlClearObserver(&(cm->observer));
    cmlCreateObserver(&(cm->observer), newobserverType, &newillumination, newcolorimetricBase);
    cmlClearIllumination(&newillumination);

//  cm->observer.state = newobserver;
//  cmlReleaseFunction(cm->observer.functions[0]);
//  cmlReleaseFunction(cm->observer.functions[1]);
//  cmlReleaseFunction(cm->observer.functions[2]);
//  cmlCreateSpecDistFunctions(cm->observer.functions, newobserver);
  cml_recomputeObserver(cm);
}


CML_API void cmlGetSpecDistFunctions(const CMLColorMachine* cm, const CMLFunction* observer[3]){
  observer[0] = cmlGetObserverSpecDistFunction(&(cm->observer), 0);
  observer[1] = cmlGetObserverSpecDistFunction(&(cm->observer), 1);
  observer[2] = cmlGetObserverSpecDistFunction(&(cm->observer), 2);
}


//CML_API void cmlSetSpecDistFunctions(CMLColorMachine* cm, const CMLFunction* observer[3]){
//  CMLFunction* tmpfun;
//  cm->observer.state = CML_OBSERVER_CUSTOM;
//  tmpfun = cm->observer.functions[0];
//  cm->observer.functions[0] = cmlDuplicateFunction(observer[0]);
//  cmlReleaseFunction(tmpfun);
//  tmpfun = cm->observer.functions[1];
//  cm->observer.functions[1] = cmlDuplicateFunction(observer[1]);
//  cmlReleaseFunction(tmpfun);
//  tmpfun = cm->observer.functions[2];
//  cm->observer.functions[2] = cmlDuplicateFunction(observer[2]);
//  cmlReleaseFunction(tmpfun);
//  cml_recomputeObserver(cm);
//}


CML_API void cmlGetSpectralXYZColor(const CMLColorMachine* cm, CMLVec3 xyz, float lambda){
//  if(!(cm->observer.functions[0])){
//    #if CML_DEBUG
//      cmlError("Spectral distribution function unavailable.");
//    #endif
//    cmlSet3(xyz, 0.f, 0.f, 0.f);
//  }else{
    cmlSet3(  xyz,
              cml_Eval(cmlGetObserverSpecDistFunction(&(cm->observer), 0), lambda),
              cml_Eval(cmlGetObserverSpecDistFunction(&(cm->observer), 1), lambda),
              cml_Eval(cmlGetObserverSpecDistFunction(&(cm->observer), 2), lambda));
//  }
}

CML_API CMLObserver* cmlCreateObserver(
                                            CMLObserver* observer,
                                         CMLObserverType type,
                                        CMLIllumination* illumination,
                                                   float colorimetricBase){
  observer = cmlAllocateIfNull(observer, sizeof(CMLObserver));
  observer->BALFtype = type;
  cmlCreateSpecDistFunctions(observer->BALFspecdistfunctions, observer->BALFtype);
  cmlCreateIlluminationDuplicate(&(observer->BALFillumination), illumination);

  // Set the radiometric scale temporarily to 0 to compute the radiometric XYZ.
  observer->BALFradiometricScale = 0.;
  cmlGetIlluminationRadiometricXYZ(illumination, observer->BALFwhitePointXYZ, observer);

  if(colorimetricBase){
    observer->BALFradiometricScale = colorimetricBase / observer->BALFwhitePointXYZ[1];
    cmlSet3(observer->BALFwhitePointXYZ, observer->BALFwhitePointXYZ[0] * observer->BALFradiometricScale,
                                         colorimetricBase,
                                         observer->BALFwhitePointXYZ[2] * observer->BALFradiometricScale);
  }
  cmlSet3(observer->BALFinverseWhitePointXYZ, cmlInverse(observer->BALFwhitePointXYZ[0]),
                                              cmlInverse(observer->BALFwhitePointXYZ[1]),
                                              cmlInverse(observer->BALFwhitePointXYZ[2]));
  cml_OneXYZToYxy(observer->BALFwhitePointYxy, observer->BALFwhitePointXYZ, CML_NULL);
  cml_OneYxyToYupvp(observer->BALFwhitePointYupvp, observer->BALFwhitePointYxy, CML_NULL);
  return observer;
}



CML_API void cmlClearObserver(CMLObserver* observer){
  cmlReleaseFunction(observer->BALFspecdistfunctions[0]);
  cmlReleaseFunction(observer->BALFspecdistfunctions[1]);
  cmlReleaseFunction(observer->BALFspecdistfunctions[2]);
  cmlClearIllumination(&(observer->BALFillumination));
}

CML_API void cmlDestroyObserver(CMLObserver* observer){
  cmlClearObserver(observer);
  free(observer);
}



CML_API float cmlGetObserverRadiometricScale(const CMLObserver* observer){
  if(observer->BALFradiometricScale){
    return observer->BALFradiometricScale;
  }else{
    return 1.f; // when radiometricScale is 0, computation is radiometric.
  }
}


CML_API float cmlGetObserverColorimetricBase(const CMLObserver* observer){
  if(observer->BALFradiometricScale){
    return observer->BALFwhitePointXYZ[1];
  }else{
    return 0.f; // when radiometricScale is 0, computation is radiometric
  }
}


CML_API const CMLFunction* cmlGetObserverSpecDistFunction(const CMLObserver* observer, CMLInt index){
  return observer->BALFspecdistfunctions[index];
}


CML_API CMLObserverType cml_GetObserverType(const CMLObserver* observer){
  return observer->BALFtype;
}

CML_API const CMLIllumination* cmlGetReferenceIllumination(const CMLObserver* observer){
  return &(observer->BALFillumination);
}

CML_API const CMLFunction* cmlGetReferenceIlluminationSpectrum(const CMLObserver* observer){
  return cml_GetIlluminationSpectrum(&(observer->BALFillumination));
}

CML_API const float* cmlGetReferenceWhitePointXYZ(const CMLObserver* observer){
  return observer->BALFwhitePointXYZ;
}

CML_API const float* cmlGetReferenceInverseWhitePointXYZ(const CMLObserver* observer){
  return observer->BALFinverseWhitePointXYZ;
}

CML_API const float* cmlGetReferenceWhitePointYxy(const CMLObserver* observer){
  return observer->BALFwhitePointYxy;
}

CML_API const float* cmlGetReferenceWhitePointYupvp(const CMLObserver* observer){
  return observer->BALFwhitePointYupvp;
}





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

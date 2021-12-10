
#include "../CML.h"
#include "CMLColorMachineState.h"


// Common values for several illumination spectra.
#define CML_ILLUMINATIONSPECTRUM_MIN 380.f
#define CML_ILLUMINATIONSPECTRUM_MAX 780.f
#define CML_ILLUMINATIONSPECTRUM_NUM 81

// The values of the B illuminant are from "The CIE Colorimetric Standards and
// Their Use", 1931, Table V
// Steps: 5nm
CML_HIDDEN static const float billuminant[] = {
    22.4f,  26.85f,  31.30f, 36.18f,  41.30f,  46.62f,  52.1f,   57.7f,   63.2f,  68.37f,
    73.1f,  77.31f,  80.8f,  83.44f,  85.4f,   86.88f,  88.3f,   90.08f,  92.0f,  93.75f,
    95.2f,  96.23f,  96.5f,  95.71f,  94.2f,   92.37f,  90.70f,  89.65f,  89.5f,  90.43f,
    92.2f,  94.46f,  96.9f,  99.16f, 101.0f,  102.2f,  102.8f,  102.92f, 102.6f, 101.90f,
   101.0f, 100.07f,  99.2f,  98.4f,   98.0f,   98.08f,  98.5f,   99.06f,  99.7f, 100.36f,
   101.0f, 101.56f, 102.2f, 103.05f, 103.9f,  104.59f, 105.0f,  105.08f, 104.9f, 104.55f,
   103.9f, 102.84f, 101.6f, 100.38f,  99.1f,   97.7f,   96.2f,   94.6f,   92.9f,  91.1f,
    89.4f,  88.0f,   86.9f,  85.9f,   85.2f,   84.8f,   84.7f,   84.9f,   85.4f,  86.1f,
    87.0f};
// The values of the C illuminant are from "The CIE Colorimetric Standards and
// Their Use", 1931, Table V
// Steps: 5nm
CML_HIDDEN static const float cilluminant[] = {
    33.0f,  39.92f,  47.4f,  55.17f,  63.3f,  71.81f,  80.6f,  89.53f,  98.1f, 105.8f,
   112.4f, 117.75f, 121.5f, 123.45f, 124.0f, 123.6f,  123.1f, 123.3f,  123.8f, 124.09f,
   123.9f, 122.92f, 120.7f, 116.9f,  112.1f, 106.98f, 102.3f,  98.81f,  96.9f,  96.78f,
    98.0f,  99.94f, 102.1f, 103.95f, 105.2f, 105.67f, 105.3f, 104.11f, 102.3f, 100.15f,
    97.8f,  95.43f,  93.2f,  91.22f,  89.7f,  88.83f,  88.4f,  88.19f,  88.1f,  88.06f,
    88.0f,  87.86f,  87.8f,  87.99f,  88.2f,  88.2f,   87.9f,  87.22f,  86.3f,  85.3f,
    84.0f,  82.21f,  80.2f,  78.24f,  76.3f,  74.36f,  72.4f,  70.4f,   68.3f,  66.3f,
    64.4f,  62.8f,   61.5f,  60.2f,   59.2f,  58.5f,   58.1f,  58.0f,   58.2f,  58.5f,
    59.1f};
// The values of the F illuminants have been found on wikipedia
// Steps: 5nm
CML_HIDDEN static const float f1illuminant[] = {
    1.87f,  2.36f,  2.94f,  3.47f,  5.17f, 19.49f,  6.13f,  6.24f,  7.01f,  7.79f,
    8.56f, 43.67f, 16.94f, 10.72f, 11.35f, 11.89f, 12.37f, 12.75f, 13.f,   13.15f,
   13.23f, 13.17f, 13.13f, 12.85f, 12.52f, 12.2f,  11.83f, 11.5f,  11.22f, 11.05f,
   11.03f, 11.18f, 11.53f, 27.74f, 17.05f, 13.55f, 14.33f, 15.01f, 15.52f, 18.29f,
   19.55f, 15.48f, 14.91f, 14.15f, 13.22f, 12.19f, 11.12f, 10.03f,  8.95f,  7.96f,
    7.02f,  6.2f,   5.42f,  4.73f,  4.15f,  3.64f,  3.2f,   2.81f,  2.47f,  2.18f,
    1.93f,  1.72f,  1.67f,  1.43f,  1.29f,  1.19f,  1.08f,  0.96f,  0.88f,  0.81f,
    0.77f,  0.75f,  0.73f,  0.68f,  0.69f,  0.64f,  0.68f,  0.69f,  0.61f,  0.52f,
    0.43f};
CML_HIDDEN static const float f2illuminant[] = {
   1.18f,  1.48f,  1.84f,  2.15f,  3.44f, 15.69f,  3.85f,  3.74f,  4.19f,  4.62f,
   5.06f, 34.98f, 11.81f,  6.27f,  6.63f,  6.93f,  7.19f,  7.4f,   7.54f,  7.62f,
   7.65f,  7.62f,  7.62f,  7.45f,  7.28f,  7.15f,  7.05f,  7.04f,  7.16f,  7.47f,
   8.04f,  8.88f, 10.01f, 24.88f, 16.64f, 14.59f, 16.16f, 17.56f, 18.62f, 21.47f,
  22.79f, 19.29f, 18.66f, 17.73f, 16.54f, 15.21f, 13.8f,  12.36f, 10.95f,  9.65f,
   8.4f,   7.32f,  6.31f,  5.43f,  4.68f,  4.02f,  3.45f,  2.96f,  2.55f,  2.19f,
   1.89f,  1.64f,  1.53f,  1.27f,  1.1f,   0.99f,  0.88f,  0.76f,  0.68f,  0.61f,
   0.56f,  0.54f,  0.51f,  0.47f,  0.47f,  0.43f,  0.46f,  0.47f,  0.4f,   0.33f,
   0.27f};
CML_HIDDEN static const float f3illuminant[] = {
   0.82f,  1.02f,  1.26f,  1.44f,  2.57f, 14.36f,  2.7f,   2.45f,  2.73f,  3.f,
   3.28f, 31.85f,  9.47f,  4.02f,  4.25f,  4.44f,  4.59f,  4.72f,  4.8f,   4.86f,
   4.87f,  4.85f,  4.88f,  4.77f,  4.67f,  4.62f,  4.62f,  4.73f,  4.99f,  5.48f,
   6.25f,  7.34f,  8.78f, 23.82f, 16.14f, 14.59f, 16.63f, 18.49f, 19.95f, 23.11f,
  24.69f, 21.41f, 20.85f, 19.93f, 18.67f, 17.22f, 15.65f, 14.04f, 12.45f, 10.95f,
   9.51f,  8.27f,  7.11f,  6.09f,  5.22f,  4.45f,  3.8f,   3.23f,  2.75f,  2.33f,
   1.99f,  1.7f,   1.55f,  1.27f,  1.09f,  0.96f,  0.83f,  0.71f,  0.62f,  0.54f,
   0.49f,  0.46f,  0.43f,  0.39f,  0.39f,  0.35f,  0.38f,  0.39f,  0.33f,  0.28f,
   0.21f};
CML_HIDDEN static const float f4illuminant[] = {
   0.57f,  0.7f,   0.87f,  0.98f,  2.01f, 13.75f,  1.95f,  1.59f,  1.76f,  1.93f,
   2.1f,  30.28f,  8.03f,  2.55f,  2.7f,   2.82f,  2.91f,  2.99f,  3.04f,  3.08f,
   3.09f,  3.09f,  3.14f,  3.06f,  3.f,    2.98f,  3.01f,  3.14f,  3.41f,  3.9f,
   4.69f,  5.81f,  7.32f, 22.59f, 15.11f, 13.88f, 16.33f, 18.68f, 20.64f, 24.28f,
  26.26f, 23.28f, 22.94f, 22.14f, 20.91f, 19.43f, 17.74f, 16.f,   14.42f, 12.56f,
  10.93f,  9.52f,  8.18f,  7.01f,  6.f,    5.11f,  4.36f,  3.69f,  3.13f,  2.64f,
   2.24f,  1.91f,  1.7f,   1.39f,  1.18f,  1.03f,  0.88f,  0.74f,  0.64f,  0.54f,
   0.49f,  0.46f,  0.42f,  0.37f,  0.37f,  0.33f,  0.35f,  0.36f,  0.31f,  0.26f,
   0.19f};
CML_HIDDEN static const float f5illuminant[] = {  // exactly the same numbers have been found in argyll
   1.87f,  2.35f,  2.92f,  3.45f,  5.1f,  18.91f,  6.f,    6.11f,  6.85f,  7.58f,
   8.31f, 40.76f, 16.06f, 10.32f, 10.91f, 11.4f,  11.83f, 12.17f, 12.4f,  12.54f,
  12.58f, 12.52f, 12.47f, 12.2f,  11.89f, 11.61f, 11.33f, 11.1f,  10.96f, 10.97f,
  11.16f, 11.54f, 12.12f, 27.78f, 17.73f, 14.47f, 15.2f,  15.77f, 16.1f,  18.54f,
  19.5f,  15.39f, 14.64f, 13.72f, 12.69f, 11.57f, 10.45f,  9.35f,  8.29f,  7.32f,
   6.41f,  5.63f,  4.9f,   4.26f,  3.72f,  3.25f,  2.83f,  2.49f,  2.19f,  1.93f,
   1.71f,  1.52f,  1.43f,  1.26f,  1.13f,  1.05f,  0.96f,  0.85f,  0.78f,  0.72f,
   0.68f,  0.67f,  0.65f,  0.61f,  0.62f,  0.59f,  0.62f,  0.64f,  0.55f,  0.47f,
   0.4f};
CML_HIDDEN static const float f6illuminant[] = {
   1.05f,  1.31f,  1.63f,  1.9f,   3.11f, 14.8f,   3.43f,  3.3f,   3.68f,  4.07f,
   4.45f, 32.61f, 10.74f,  5.48f,  5.78f,  6.03f,  6.25f,  6.41f,  6.52f,  6.58f,
   6.59f,  6.56f,  6.56f,  6.42f,  6.28f,  6.2f,   6.19f,  6.3f,   6.6f,   7.12f,
   7.94f,  9.07f, 10.49f, 25.22f, 17.46f, 15.63f, 17.22f, 18.53f, 19.43f, 21.97f,
  23.01f, 19.41f, 18.56f, 17.42f, 16.09f, 14.64f, 13.15f, 11.68f, 10.25f,  8.96f,
   7.74f,  6.69f,  5.71f,  4.87f,  4.16f,  3.55f,  3.02f,  2.57f,  2.2f,   1.87f,
   1.6f,   1.37f,  1.29f,  1.05f,  0.91f,  0.81f,  0.71f,  0.61f,  0.54f,  0.48f,
   0.44f,  0.43f,  0.4f,   0.37f,  0.38f,  0.35f,  0.39f,  0.41f,  0.33f,  0.26f,
   0.21f};
CML_HIDDEN static const float f7illuminant[] = {
   2.56f,  3.18f,  3.84f,  4.53f,  6.15f, 19.37f,  7.37f,  7.05f,  7.71f,  8.41f,
   9.15f, 44.14f, 17.52f, 11.35f, 12.f,   12.58f, 13.08f, 13.45f, 13.71f, 13.88f,
  13.95f, 13.93f, 13.82f, 13.64f, 13.43f, 13.25f, 13.08f, 12.93f, 12.78f, 12.6f,
  12.44f, 12.33f, 12.26f, 29.52f, 17.05f, 12.44f, 12.58f, 12.72f, 12.83f, 15.46f,
  16.75f, 12.83f, 12.67f, 12.45f, 12.19f, 11.89f, 11.6f,  11.35f, 11.12f, 10.95f,
  10.76f, 10.42f, 10.11f, 10.04f, 10.02f, 10.11f,  9.87f,  8.65f,  7.27f,  6.44f,
   5.83f,  5.41f,  5.04f,  4.57f,  4.12f,  3.77f,  3.46f,  3.08f,  2.73f,  2.47f,
   2.25f,  2.06f,  1.9f,   1.75f,  1.62f,  1.54f,  1.45f,  1.32f,  1.17f,  0.99f,
   0.81f};
CML_HIDDEN static const float f8illuminant[] = {  // exactly the same numbers have been found in argyll
   1.21f,  1.5f,   1.81f,  2.13f,  3.17f, 13.08f,  3.83f,  3.45f,  3.86f,  4.42f,
   5.09f, 34.1f,  12.42f,  7.68f,  8.6f,   9.46f, 10.24f, 10.84f, 11.33f, 11.71f,
  11.98f, 12.17f, 12.28f, 12.32f, 12.35f, 12.44f, 12.55f, 12.68f, 12.77f, 12.72f,
  12.6f,  12.43f, 12.22f, 28.96f, 16.51f, 11.79f, 11.76f, 11.77f, 11.84f, 14.61f,
  16.11f, 12.34f, 12.53f, 12.72f, 12.92f, 13.12f, 13.34f, 13.61f, 13.87f, 14.07f,
  14.2f,  14.16f, 14.13f, 14.34f, 14.5f,  14.46f, 14.f,   12.58f, 10.99f,  9.98f,
   9.22f,  8.62f,  8.07f,  7.39f,  6.71f,  6.16f,  5.63f,  5.03f,  4.46f,  4.02f,
   3.66f,  3.36f,  3.09f,  2.85f,  2.65f,  2.51f,  2.37f,  2.15f,  1.89f,  1.61f,
   1.32f};
CML_HIDDEN static const float f9illuminant[] = {
   0.9f,   1.12f,  1.36f,  1.6f,   2.59f, 12.8f,   3.05f,  2.56f,  2.86f,  3.3f,
   3.82f, 32.62f, 10.77f,  5.84f,  6.57f,  7.25f,  7.86f,  8.35f,  8.75f,  9.06f,
   9.31f,  9.48f,  9.61f,  9.68f,  9.74f,  9.88f, 10.04f, 10.26f, 10.48f, 10.63f,
  10.76f, 10.96f, 11.18f, 27.71f, 16.29f, 12.28f, 12.74f, 13.21f, 13.65f, 16.57f,
  18.14f, 14.55f, 14.65f, 14.66f, 14.61f, 14.5f,  14.39f, 14.4f,  14.47f, 14.62f,
  14.72f, 14.55f, 14.4f,  14.58f, 14.88f, 15.51f, 15.47f, 13.2f,  10.57f,  9.18f,
   8.25f,  7.57f,  7.03f,  6.35f,  5.72f,  5.25f,  4.8f,   4.29f,  3.8f,   3.43f,
   3.12f,  2.86f,  2.64f,  2.43f,  2.26f,  2.14f,  2.02f,  1.83f,  1.61f,  1.38f,
   1.12f};
CML_HIDDEN static const float f10illuminant[] = {
   1.11f,  0.63f,  0.62f,  0.57f,  1.48f, 12.16f,  2.12f,  2.7f,   3.74f,  5.14f,
   6.75f, 34.39f, 14.86f, 10.4f,  10.76f, 10.67f, 10.11f,  9.27f,  8.29f,  7.29f,
   7.91f, 16.64f, 16.73f, 10.44f,  5.94f,  3.34f,  2.35f,  1.88f,  1.59f,  1.47f,
   1.8f,   5.71f, 40.98f, 73.69f, 33.61f,  8.24f,  3.38f,  2.47f,  2.14f,  4.86f,
  11.45f, 14.79f, 12.16f,  8.97f,  6.52f,  8.81f, 44.12f, 34.55f, 12.09f, 12.15f,
  10.52f,  4.43f,  1.95f,  2.19f,  3.19f,  2.77f,  2.29f,  2.f,    1.52f,  1.35f,
   1.47f,  1.79f,  1.74f,  1.02f,  1.14f,  3.32f,  4.49f,  2.05f,  0.49f,  0.24f,
   0.21f,  0.21f,  0.24f,  0.24f,  0.21f,  0.17f,  0.21f,  0.22f,  0.17f,  0.12f,
   0.09f};
CML_HIDDEN static const float f11illuminant[] = {
   0.91f,  0.63f,  0.46f,  0.37f,  1.29f, 12.68f,  1.59f,  1.79f,  2.46f,  3.33f,
   4.49f, 33.94f, 12.13f,  6.95f,  7.19f,  7.12f,  6.72f,  6.13f,  5.46f,  4.79f,
   5.66f, 14.29f, 14.96f,  8.97f,  4.72f,  2.33f,  1.47f,  1.1f,   0.89f,  0.83f,
   1.18f,  4.9f,  39.59f, 72.84f, 32.61f,  7.52f,  2.83f,  1.96f,  1.67f,  4.43f,
  11.28f, 14.76f, 12.73f,  9.74f,  7.33f,  9.72f, 55.27f, 42.58f, 13.18f, 13.16f,
  12.26f,  5.11f,  2.07f,  2.34f,  3.58f,  3.01f,  2.48f,  2.14f,  1.54f,  1.33f,
   1.46f,  1.94f,  2.f,    1.2f,   1.35f,  4.1f,   5.58f,  2.51f,  0.57f,  0.27f,
   0.23f,  0.21f,  0.24f,  0.24f,  0.2f,   0.24f,  0.32f,  0.26f,  0.16f,  0.12f,
   0.09f};
CML_HIDDEN static const float f12illuminant[] = {
   0.96f,  0.64f,  0.45f,  0.33f,  1.19f, 12.48f,  1.12f,  0.94f,  1.08f,  1.37f,
   1.78f, 29.05f,  7.9f,   2.65f,  2.71f,  2.65f,  2.49f,  2.33f,  2.1f,   1.91f,
   3.01f, 10.83f, 11.88f,  6.88f,  3.43f,  1.49f,  0.92f,  0.71f,  0.6f,   0.63f,
   1.1f,   4.56f, 34.4f,  65.4f,  29.48f,  7.16f,  3.08f,  2.47f,  2.27f,  5.09f,
  11.96f, 15.32f, 14.27f, 11.86f,  9.28f, 12.31f, 68.53f, 53.02f, 14.67f, 14.38f,
  14.71f,  6.46f,  2.57f,  2.75f,  4.18f,  3.44f,  2.81f,  2.42f,  1.64f,  1.36f,
   1.49f,  2.14f,  2.34f,  1.42f,  1.61f,  5.04f,  6.98f,  3.19f,  0.71f,  0.3f,
   0.26f,  0.23f,  0.28f,  0.28f,  0.21f,  0.17f,  0.21f,  0.19f,  0.15f,  0.1f,
   0.05f};


#define CML_XENON_ILLUMINATIONSPECTRUM_MIN 325.f
#define CML_XENON_ILLUMINATIONSPECTRUM_MAX 795.f
#define CML_XENON_ILLUMINATIONSPECTRUM_NUM 95
CML_HIDDEN static const float xenonilluminant[] = {
   0.220794f, 0.240550f, 0.281212f, 0.363042f, 0.493282f, 0.582279f, 0.657489f, 0.715563f, 0.797559f, 0.916343f,
   1.066625f, 1.228461f, 1.298467f, 1.373143f, 1.457366f, 1.496117f, 1.509290f, 1.573544f, 1.596359f, 1.495740f,
   1.477898f, 1.521371f, 1.479780f, 1.453196f, 1.532119f, 1.548128f, 1.503433f, 1.428481f, 1.357290f, 1.354425f,
   1.317263f, 1.237048f, 1.169737f, 1.109248f, 1.085784f, 1.080186f, 1.104001f, 1.131713f, 1.161153f, 1.158589f,
   1.148998f, 1.123934f, 1.077395f, 1.017907f, 1.026532f, 1.045921f, 1.083780f, 1.081868f, 1.048489f, 1.021549f,
   0.993572f, 0.956559f, 0.942657f, 0.952544f, 0.957087f, 0.958472f, 0.945666f, 0.923988f, 0.890418f, 0.852044f,
   0.812935f, 0.792055f, 0.791141f, 0.825459f, 0.829230f, 0.818171f, 0.851752f, 0.913113f, 1.038844f, 1.116913f,
   1.164211f, 1.133376f, 1.109062f, 1.129427f, 1.086885f, 0.991213f, 0.924226f, 0.875499f, 0.894231f, 0.922219f,
   0.960372f, 0.896142f, 0.819477f, 0.879305f, 0.912777f, 0.908489f, 0.775942f, 0.598118f, 0.532988f, 0.484102f,
   0.465986f, 0.414848f, 0.346473f, 0.324622f, 0.309978f};


// Found at brucelindbloom.com
#define CML_ROBERTSON_SAMPLECOUNT 31
CML_HIDDEN static const float robertsonrt[] = {
  CML_SINGULARITY,10.0e-6f,  20.0e-6f,  30.0e-6f,  40.0e-6f,  50.0e-6f,  60.0e-6f,  70.0e-6f,  80.0e-6f,  90.0e-6f,
  100.0e-6f, 125.0e-6f, 150.0e-6f, 175.0e-6f, 200.0e-6f, 225.0e-6f, 250.0e-6f, 275.0e-6f, 300.0e-6f, 325.0e-6f,
  350.0e-6f, 375.0e-6f, 400.0e-6f, 425.0e-6f, 450.0e-6f, 475.0e-6f, 500.0e-6f, 525.0e-6f, 550.0e-6f, 575.0e-6f,
  600.0e-6f};
CML_HIDDEN static const float robertsonu[] = {
  0.18006f, 0.18066f, 0.18133f, 0.18208f, 0.18293f, 0.18388f, 0.18494f, 0.18611f, 0.18740f, 0.18880f,
  0.19032f, 0.19462f, 0.19962f, 0.20525f, 0.21142f, 0.21807f, 0.22511f, 0.23247f, 0.24010f, 0.24792f,
  0.25591f, 0.26400f, 0.27218f, 0.28039f, 0.28863f, 0.29685f, 0.30505f, 0.31320f, 0.32129f, 0.32931f,
  0.33724f};
CML_HIDDEN static const float robertsonv[] = {
  0.26352f, 0.26589f, 0.26846f, 0.27119f, 0.27407f, 0.27709f, 0.28021f, 0.28342f, 0.28668f, 0.28997f,
  0.29326f, 0.30141f, 0.30921f, 0.31647f, 0.32312f, 0.32909f, 0.33439f, 0.33904f, 0.34308f, 0.34655f,
  0.34951f, 0.35200f, 0.35407f, 0.35577f, 0.35714f, 0.35823f, 0.35907f, 0.35968f, 0.36011f, 0.36038f,
  0.36051f};
CML_HIDDEN static const float robertsont[] = {
  -0.24341f, -0.25479f, -0.26876f, -0.28539f, -0.30470f, -0.32675f, -0.35156f, -0.37915f, -0.40955f, -0.44278f,
  -0.47888f, -0.58204f, -0.70471f, -0.84901f, -1.0182f, -1.2168f, -1.4512f, -1.7298f, -2.0637f, -2.4681f,
  -2.9641f, -3.5814f, -4.3633f, -5.3762f, -6.7262f, -8.5955f, -11.324f, -15.628f, -23.325f, -40.770f,
  -116.45f };




CML_HDEF CMLArrayFunctionSettings cml_getCommonIlluminationSpectrumSettings(void){
  CMLArrayFunctionSettings settings = {
    CML_ILLUMINATIONSPECTRUM_NUM,
    CML_ILLUMINATIONSPECTRUM_MIN,
    CML_ILLUMINATIONSPECTRUM_MAX,
    CML_INTERPOLATION_LINEAR,
    CML_EXTRAPOLATION_LINEAR_ZERO,
    CML_EXTRAPOLATION_LINEAR_ZERO};
  return settings;
}

CML_DEF CMLFunction* cmlCreateIlluminationSpectrum(CMLIlluminationType illuminationType, float temperature){  
  switch(illuminationType){
  case CML_ILLUMINATION_BLACKBODY:
    return cmlCreateBlackBody(temperature);
    break;
  case CML_ILLUMINATION_A_CIE:
    return cmlCreateCIEAIlluminant();
    break;
  case CML_ILLUMINATION_A_EXACT:
    return cmlCreateBlackBody(CML_TEMPERATURE_A);
    break;
  case CML_ILLUMINATION_B: {
    CMLArrayFunctionInput input = {billuminant, CML_FALSE, cml_getCommonIlluminationSpectrumSettings()};
    return cmlCreateArrayFunction(input);
    break; }
  case CML_ILLUMINATION_C: {
    CMLArrayFunctionInput input = {cilluminant, CML_FALSE, cml_getCommonIlluminationSpectrumSettings()};
    return cmlCreateArrayFunction(input);
    break; }
  case CML_ILLUMINATION_D_ILLUMINANT:
    return cmlCreateCIEDIlluminant(temperature);
    break;
  case CML_ILLUMINATION_D50:
    return cmlCreateCIEDIlluminant(CML_TEMPERATURE_D50);
    break;
  case CML_ILLUMINATION_D55:
    return cmlCreateCIEDIlluminant(CML_TEMPERATURE_D55);
    break;
  case CML_ILLUMINATION_D65:
    return cmlCreateCIEDIlluminant(CML_TEMPERATURE_D65);
    break;
  case CML_ILLUMINATION_D75:
    return cmlCreateCIEDIlluminant(CML_TEMPERATURE_D75);
    break;
  case CML_ILLUMINATION_D93:
    return cmlCreateCIEDIlluminant(CML_TEMPERATURE_D93);
    break;
  case CML_ILLUMINATION_E:
    return cmlCreateConstFilter(1.f);
    break;
  case CML_ILLUMINATION_F1: {
    CMLArrayFunctionInput input = {f1illuminant, CML_FALSE, cml_getCommonIlluminationSpectrumSettings()};
    return cmlCreateArrayFunction(input);
    break; }
  case CML_ILLUMINATION_F2: {
    CMLArrayFunctionInput input = {f2illuminant, CML_FALSE, cml_getCommonIlluminationSpectrumSettings()};
    return cmlCreateArrayFunction(input);
    break; }
  case CML_ILLUMINATION_F3: {
    CMLArrayFunctionInput input = {f3illuminant, CML_FALSE, cml_getCommonIlluminationSpectrumSettings()};
    return cmlCreateArrayFunction(input);
    break; }
  case CML_ILLUMINATION_F4: {
    CMLArrayFunctionInput input = {f4illuminant, CML_FALSE, cml_getCommonIlluminationSpectrumSettings()};
    return cmlCreateArrayFunction(input);
    break; }
  case CML_ILLUMINATION_F5: {
    CMLArrayFunctionInput input = {f5illuminant, CML_FALSE, cml_getCommonIlluminationSpectrumSettings()};
    return cmlCreateArrayFunction(input);
    break; }
  case CML_ILLUMINATION_F6: {
    CMLArrayFunctionInput input = {f6illuminant, CML_FALSE, cml_getCommonIlluminationSpectrumSettings()};
    return cmlCreateArrayFunction(input);
    break; }
  case CML_ILLUMINATION_F7: {
    CMLArrayFunctionInput input = {f7illuminant, CML_FALSE, cml_getCommonIlluminationSpectrumSettings()};
    return cmlCreateArrayFunction(input);
    break; }
  case CML_ILLUMINATION_F8: {
    CMLArrayFunctionInput input = {f8illuminant, CML_FALSE, cml_getCommonIlluminationSpectrumSettings()};
    return cmlCreateArrayFunction(input);
    break; }
  case CML_ILLUMINATION_F9: {
    CMLArrayFunctionInput input = {f9illuminant, CML_FALSE, cml_getCommonIlluminationSpectrumSettings()};
    return cmlCreateArrayFunction(input);
    break; }
  case CML_ILLUMINATION_F10: {
    CMLArrayFunctionInput input = {f10illuminant, CML_FALSE, cml_getCommonIlluminationSpectrumSettings()};
    return cmlCreateArrayFunction(input);
    break; }
  case CML_ILLUMINATION_F11: {
    CMLArrayFunctionInput input = {f11illuminant, CML_FALSE, cml_getCommonIlluminationSpectrumSettings()};
    return cmlCreateArrayFunction(input);
    break; }
  case CML_ILLUMINATION_F12: {
    CMLArrayFunctionInput input = {f12illuminant, CML_FALSE, cml_getCommonIlluminationSpectrumSettings()};
    return cmlCreateArrayFunction(input);
    break; }
  case CML_ILLUMINATION_XENON: {
    CMLArrayFunctionInput input = {
      xenonilluminant,
      CML_FALSE,
      { CML_XENON_ILLUMINATIONSPECTRUM_NUM,
        CML_XENON_ILLUMINATIONSPECTRUM_MIN,
        CML_XENON_ILLUMINATIONSPECTRUM_MAX,
        CML_INTERPOLATION_LINEAR,
        CML_EXTRAPOLATION_LINEAR_ZERO,
        CML_EXTRAPOLATION_LINEAR_ZERO}};
    return cmlCreateArrayFunction(input);
    break; }
  default:
    #if CML_DEBUG
      cmlError("Illumination type invalid.");
    #endif
    return CML_NULL;
    break;
  }
}


CML_DEF float cmlGetCorrelatedColorTemperature(const CMLVec3 whitePointYuv){
  float temperature = 0.f;
  float dm = 0.f;

  for(size_t i = 0; i < CML_ROBERTSON_SAMPLECOUNT; i++) {
    float di = (whitePointYuv[2] - robertsonv[i]) - robertsont[i] * (whitePointYuv[1] - robertsonu[i]);
    if ((i > 0) && (di*dm < 0.f)){
      float p;
      // found lines bounding (us, vs) : i-1 and i
      di /= sqrtf(1.f + robertsont[i-0] * robertsont[i-0]);
      dm /= sqrtf(1.f + robertsont[i-1] * robertsont[i-1]);
      p = dm / (dm - di); // interpolation parameter, 0. : i-1, 1. : i
      temperature = cmlInverse((robertsonrt[i] - robertsonrt[i-1]) * p + robertsonrt[i-1]);
      break;
    }
    dm = di;
  }

  return temperature;
}





CML_HIDDEN void cml_recomputeIllumination(CMLColorMachine* cm){
//  CMLVec3 computationwhitePoint;

  if(cm->recomputationLockCount){cm->recomputationMask |= CML_COLORMACHINE_RECOMPUTE_ILLUMINATION; return;}
  
//  if(cm->illumination.spectrum){
//    cml_IlluminationSpectrumToXYZ(cm->illumination.whitePointXYZ, cm->illumination.spectrum, (const CMLFunction* const *)(cm->observer.functions));
//    cml_XYZToYxy(cm->illumination.whitePointYxy, cm->illumination.whitePointXYZ, CML_NULL, 1);
//  }
//
//  if(cm->observer.radiometric){
//    cmlCpy3(computationwhitePoint, cm->illumination.whitePointYxy);
//  }else{
//    cmlSet3(computationwhitePoint, 1.f, cm->illumination.whitePointYxy[1], cm->illumination.whitePointYxy[2]);
//  }
//  cml_YxyToXYZ(cm->illumination.whitePointXYZ, computationwhitePoint, CML_NULL, 1);
//  cmlSet3(cm->illumination.inverseWhitePointXYZ, cmlInverse(cm->illumination.whitePointXYZ[0]), cmlInverse(cm->illumination.whitePointXYZ[1]), cmlInverse(cm->illumination.whitePointXYZ[2]));
//  cml_YxyToYupvp(cm->illumination.whitePointYupvp, computationwhitePoint, CML_NULL, 1);

  // Now, all whitePoints are computed.

  // Compute the correlated color temperature:
//  switch(cm->illumination.state){
//  case CML_ILLUMINATION_BLACKBODY:
//  case CML_ILLUMINATION_D_ILLUMINANT:
//    // the temperature is already set.
//    break;
//  case CML_ILLUMINATION_A_CIE:
//    cm->illumination.temperature = 2848.f;
//    break;
//  case CML_ILLUMINATION_A_EXACT:
//    cm->illumination.temperature = CML_TEMPERATURE_A;
//    break;
//  case CML_ILLUMINATION_D50:
//    cm->illumination.temperature = CML_TEMPERATURE_D50;
//    break;
//  case CML_ILLUMINATION_D55:
//    cm->illumination.temperature = CML_TEMPERATURE_D55;
//    break;
//  case CML_ILLUMINATION_D65:
//    cm->illumination.temperature = CML_TEMPERATURE_D65;
//    break;
//  case CML_ILLUMINATION_D75:
//    cm->illumination.temperature = CML_TEMPERATURE_D75;
//    break;
//  case CML_ILLUMINATION_D93:
//    cm->illumination.temperature = CML_TEMPERATURE_D93;
//    break;
//  default:
//    // Any other illumination is computed using Robertson
//    {
//      CMLVec3 whitePointYuv;
//      cml_YupvpToYuv(whitePointYuv, cm->illumination.whitePointYupvp, 1);
//      cm->illumination.temperature = cmlGetCorrelatedColorTemperature(whitePointYuv);
//    }
//    break;
//  }

  cml_recomputeLabColorSpace(cm);
  cml_recomputeAdamsChromaticityValenceSpace(cm);  
  cml_recomputeRGBColorSpace(cm);
}


CML_DEF CMLIlluminationType   cmlGetIlluminationType(CMLColorMachine* cm){
  return cml_GetIlluminationType(cmlGetReferenceIllumination(&(cm->observer)));
}


CML_DEF void cmlSetIlluminationType(CMLColorMachine* cm, CMLIlluminationType illuminationType){
  if(illuminationType == CML_ILLUMINATION_CUSTOM_SPECTRUM){return;}

  CMLObserverType newobserverType = cml_GetObserverType(&(cm->observer));
  float newcolorimetricBase = cmlGetObserverColorimetricBase(&(cm->observer));
  CMLIllumination* newillumination = cmlCreateIlluminationWithType(CML_NULL, illuminationType, cmlGetIlluminationTemperature(cm));
  cmlClearObserver(&(cm->observer));
  cmlCreateObserver(&(cm->observer), newobserverType, newillumination, newcolorimetricBase);
  cmlClearIllumination(newillumination);

//  cm->illumination.state = illuminationType;
//  cmlReleaseFunction(cm->illumination.spectrum);
//
//  if(cm->illumination.state == CML_ILLUMINATION_CUSTOM_WHITEPOINT){
//    cm->illumination.temperature = 0.f;
//  }
  
  // Recompute the white point
  cml_recomputeIllumination(cm);
}


CML_DEF float cmlGetIlluminationTemperature(const CMLColorMachine* cm){
  return cmlGetIlluminationCorrelatedColorTemperature(cmlGetReferenceIllumination(&(cm->observer)));
//  return cm->illumination.temperature;
}


CML_DEF void cmlSetIlluminationTemperature(CMLColorMachine* cm, float temp){
  CMLIlluminationType illtype = cml_GetIlluminationType(cmlGetReferenceIllumination(&(cm->observer)));
  if((illtype == CML_ILLUMINATION_BLACKBODY) || (illtype == CML_ILLUMINATION_D_ILLUMINANT)){

    CMLObserverType newobserverType = cml_GetObserverType(&(cm->observer));
    float newcolorimetricBase = cmlGetObserverColorimetricBase(&(cm->observer));
    CMLIllumination* newillumination = cmlCreateIlluminationWithType(CML_NULL, illtype, temp);
    cmlClearObserver(&(cm->observer));
    cmlCreateObserver(&(cm->observer), newobserverType, newillumination, newcolorimetricBase);
    cmlClearIllumination(newillumination);


//    cm->illumination.temperature = temp;
//    cmlReleaseFunction(cm->illumination.spectrum);
//    if(cm->illumination.state == CML_ILLUMINATION_BLACKBODY){
//      cm->illumination.spectrum = cmlCreateBlackBody(cm->illumination.temperature);
//    }else{
//      cm->illumination.spectrum = cmlCreateCIEDIlluminant(cm->illumination.temperature);
//    }
    cml_recomputeIllumination(cm);
  #if CML_DEBUG
  }else{
    cmlError("Call only effective for Blackbody and custom D illuminants.");
  #endif
  }
}


CML_DEF const CMLFunction* cmlGetIlluminationSpectrum(const CMLColorMachine* cm){
  return cmlGetReferenceIlluminationSpectrum(&(cm->observer));
}


CML_DEF void cmlSetIlluminationSpectrum(CMLColorMachine* cm, const CMLFunction* newspectrum){
  if(!newspectrum){return;}

    CMLObserverType newobserverType = cml_GetObserverType(&(cm->observer));
    float newcolorimetricBase = cmlGetObserverColorimetricBase(&(cm->observer));
    CMLIllumination* newillumination = cmlCreateIlluminationWithCustomSpectrum(CML_NULL, newspectrum, &(cm->observer));
    cmlClearObserver(&(cm->observer));
    cmlCreateObserver(&(cm->observer), newobserverType, newillumination, newcolorimetricBase);
    cmlClearIllumination(newillumination);

//  cmlReleaseFunction(cm->illumination.spectrum);
//  cm->illumination.spectrum = cmlDuplicateFunction(newspectrum);
//  cm->illumination.state = CML_ILLUMINATION_CUSTOM_SPECTRUM;
  cml_recomputeIllumination(cm);
}


CML_DEF void cmlGetWhitePointYxy(const CMLColorMachine* cm, CMLVec3 whitePointYxy){
  cmlCpy3(whitePointYxy, cmlGetReferenceWhitePointYxy(&(cm->observer)));
}


CML_DEF void cmlSetWhitePointYxy(CMLColorMachine* cm, const float* yxy){

    CMLObserverType newobserverType = cml_GetObserverType(&(cm->observer));
    float newcolorimetricBase = cmlGetObserverColorimetricBase(&(cm->observer));
    CMLIllumination* newillumination = cmlCreateIlluminationWithCustomWhitePoint(CML_NULL, yxy);
    cmlClearObserver(&(cm->observer));
    cmlCreateObserver(&(cm->observer), newobserverType, newillumination, newcolorimetricBase);
    cmlClearIllumination(newillumination);

//  cm->illumination.state = CML_ILLUMINATION_CUSTOM_WHITEPOINT;
//  cmlReleaseFunction(cm->illumination.spectrum);
//  cm->illumination.spectrum = CML_NULL;
//  cmlCpy3(cm->illumination.whitePointYxy, yxy);
  cml_recomputeIllumination(cm);
}

CML_DEF CMLIllumination* cmlCreateIlluminationDuplicate(CMLIllumination* illumination, const CMLIllumination* src){
  illumination = cml_AllocateIfNull(illumination, sizeof(CMLIllumination));
  illumination->BALFtype = src->BALFtype;
  illumination->BALFtemperature = src->BALFtemperature;
  if(src->BALFspectrum){
    illumination->BALFspectrum = cmlDuplicateFunction(src->BALFspectrum);
  }else{
    illumination->BALFspectrum = CML_NULL;
  }
  cmlCpy3(illumination->BALFradiometricXYZ, src->BALFradiometricXYZ);
  return illumination;
}


CML_DEF CMLIllumination* cmlCreateIlluminationWithType(CMLIllumination* illumination, CMLIlluminationType type, float temperature){
  #if CML_DEBUG
    if(type != CML_ILLUMINATION_BLACKBODY &&
      type != CML_ILLUMINATION_D_ILLUMINANT &&
      type != CML_ILLUMINATION_D50 &&
      type != CML_ILLUMINATION_D55 &&
      type != CML_ILLUMINATION_D65 &&
      type != CML_ILLUMINATION_D75 &&
      type != CML_ILLUMINATION_D93 &&
      temperature != 0)
      cmlError("Temperature should be zero except for blackbody or D illuminant type.");
  #endif

  illumination = cml_AllocateIfNull(illumination, sizeof(CMLIllumination));
  illumination->BALFtype = type;
  illumination->BALFtemperature = temperature;
  illumination->BALFspectrum = cmlCreateIlluminationSpectrum(illumination->BALFtype, illumination->BALFtemperature);

  switch(illumination->BALFtype){
  case CML_ILLUMINATION_BLACKBODY:
    // temperature is already set.
    if(!illumination->BALFtemperature){illumination->BALFtemperature = CML_TEMPERATURE_A;}
    break;
  case CML_ILLUMINATION_A_CIE:
    illumination->BALFtemperature = 2848.f;
    break;
  case CML_ILLUMINATION_A_EXACT:
    illumination->BALFtemperature = CML_TEMPERATURE_A;
    break;
  case CML_ILLUMINATION_D_ILLUMINANT:
    // temperature is already set.
    if(!illumination->BALFtemperature){illumination->BALFtemperature = CML_TEMPERATURE_D65;}
    break;
  case CML_ILLUMINATION_D50:
    illumination->BALFtemperature = CML_TEMPERATURE_D50;
    break;
  case CML_ILLUMINATION_D55:
    illumination->BALFtemperature = CML_TEMPERATURE_D55;
    break;
  case CML_ILLUMINATION_D65:
    illumination->BALFtemperature = CML_TEMPERATURE_D65;
    break;
  case CML_ILLUMINATION_D75:
    illumination->BALFtemperature = CML_TEMPERATURE_D75;
    break;
  case CML_ILLUMINATION_D93:
    illumination->BALFtemperature = CML_TEMPERATURE_D93;
    break;
  default:
    // Any other illumination is computed using Robertson
    {
      illumination->BALFtemperature = 0.f;
//      CMLVec3 whitePointYuv;
//      cml_OneYupvpToYuv(whitePointYuv, cm->illumination.whitePointYupvp);
//      cm->illumination.temperature = cmlGetCorrelatedColorTemperature(whitePointYuv);
    }
    break;
  }
  return illumination;
}


CML_DEF CMLIllumination* cmlCreateIlluminationWithCustomSpectrum(CMLIllumination* illumination, const CMLFunction* spectrum, const CMLObserver* observer){
  illumination = cml_AllocateIfNull(illumination, sizeof(CMLIllumination));
  illumination->BALFtype = CML_ILLUMINATION_CUSTOM_SPECTRUM;
  illumination->BALFtemperature = 0.f;
  illumination->BALFspectrum = cmlDuplicateFunction(spectrum);

  cml_OneIlluminationSpectrumToXYZ(illumination->BALFradiometricXYZ, illumination->BALFspectrum, observer);

  CMLVec3 whitePointYxy;
  CMLVec3 whitePointYupvp;
  CMLVec3 whitePointYuv;
  cml_OneXYZToYxy(whitePointYxy, illumination->BALFradiometricXYZ, CML_NULL);
  cml_OneYxyToYupvp(whitePointYupvp, whitePointYxy, CML_NULL);
  cml_OneYupvpToYuv(whitePointYuv, whitePointYupvp);
  illumination->BALFtemperature = cmlGetCorrelatedColorTemperature(whitePointYuv);

  return illumination;
}


CML_DEF CMLIllumination* cmlCreateIlluminationWithCustomWhitePoint(CMLIllumination* illumination, const CMLVec3 whitePointYxy){
  illumination = cml_AllocateIfNull(illumination, sizeof(CMLIllumination));
  illumination->BALFtype = CML_ILLUMINATION_CUSTOM_WHITEPOINT;
  illumination->BALFspectrum = NULL;
  
  cml_OneYxyToXYZ(illumination->BALFradiometricXYZ, whitePointYxy, CML_NULL);

  CMLVec3 whitePointYupvp;
  CMLVec3 whitePointYuv;
  cml_OneYxyToYupvp(whitePointYupvp, whitePointYxy, CML_NULL);
  cml_OneYupvpToYuv(whitePointYuv, whitePointYupvp);
  illumination->BALFtemperature = cmlGetCorrelatedColorTemperature(whitePointYuv);

  return illumination;
}



CML_DEF void cmlClearIllumination(CMLIllumination* illumination){
  cmlReleaseFunction(illumination->BALFspectrum);
}


CML_DEF void cmlDestroyIllumination(CMLIllumination* illumination){
  cmlClearIllumination(illumination);
  free(illumination);
}




CML_DEF CMLIlluminationType cml_GetIlluminationType(const CMLIllumination* illumination){
  return illumination->BALFtype;
}

CML_DEF const CMLFunction* cml_GetIlluminationSpectrum(const CMLIllumination* illumination){
  return illumination->BALFspectrum;
}


CML_DEF float cmlGetIlluminationCorrelatedColorTemperature(const CMLIllumination* illumination){
//  if(!illumination->BALFtemperature){
//    // Computation takes long. Compute on demand.
//    return 0.f;
////    CMLVec3 whitePointYuv;
////    cml_OneYupvpToYuv(whitePointYuv, cm->illumination.whitePointYupvp);
////    cm->illumination.temperature = cmlGetCorrelatedColorTemperature(whitePointYuv);
//  }
  if(!illumination->BALFtemperature){return CML_TEMPERATURE_D65;}
  return illumination->BALFtemperature;
}

CML_DEF void cmlGetIlluminationRadiometricXYZ(const CMLIllumination* illumination, float* dest, const CMLObserver* observer){
  if(illumination->BALFspectrum){
    cml_OneIlluminationSpectrumToXYZ(dest, illumination->BALFspectrum, observer);
  }else{
    cmlCpy3(dest, illumination->BALFradiometricXYZ);
  }
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

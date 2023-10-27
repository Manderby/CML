cmake_minimum_required(VERSION 3.13)
project(CML)

set(TARGET_NAME CML)
add_library(${TARGET_NAME} STATIC)

set_target_properties(${TARGET_NAME} PROPERTIES LINKER_LANGUAGE C)
set(CMAKE_CXX_STANDARD 99)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (MSVC)
  # multi processor compilation
  target_compile_options(${TARGET_NAME} PRIVATE /MP)
else()
endif()



set(primaryHeaderFiles
  src/CML.h
  src/CMLBaseAPI.h  src/CMLColorMachine.h  src/CMLDefinitions.h  src/CMLEnvironment.h  src/CMLFunctions.h  src/CMLMath.h  src/CMLResponseCurve.h
)

set(conversionFiles
  src/Conversions/CMLClamp.c  src/Conversions/CMLCMYKConversions.c  src/Conversions/CMLColorMachineConversions.c  src/Conversions/CMLGrayConversions.c  src/Conversions/CMLHSLConversions.c  src/Conversions/CMLHSVConversions.c  src/Conversions/CMLInputOutputConversions.c  src/Conversions/CMLInvert.c  src/Conversions/CMLLabConversions.c  src/Conversions/CMLLchConversions.c  src/Conversions/CMLLuvConversions.c  src/Conversions/CMLNormedConversions.c  src/Conversions/CMLRGBConversions.c  src/Conversions/CMLSpectralConversions.c  src/Conversions/CMLUVWConversions.c  src/Conversions/CMLXYZConversions.c  src/Conversions/CMLYCbCrConversions.c  src/Conversions/CMLYcdConversions.c  src/Conversions/CMLYupvpConversions.c  src/Conversions/CMLYuvConversions.c  src/Conversions/CMLYxyConversions.c
)

set(internalFiles
  src/Internal/CMLBaseAPI.c  src/Internal/CMLChromaticAdaptation.c  src/Internal/CMLCMYKColorspace.c  src/Internal/CMLColorMachine.c  src/Internal/CMLColorMachineState.h  src/Internal/CMLConverterMacros.h  src/Internal/CMLFunctions.c  src/Internal/CMLGrayColorspace.c  src/Internal/CMLIllumination.c  src/Internal/CMLIntegerMapping.c  src/Internal/CMLInternal.c  src/Internal/CMLInternal.h  src/Internal/CMLLabColorspace.c  src/Internal/CMLNormedConversions.h  src/Internal/CMLObserver.c  src/Internal/CMLResponseCurve.c  src/Internal/CMLRGBColorspace.c  src/Internal/CMLStrings.c  src/Internal/CMLunused.h
)

source_group("src" FILES ${primaryHeaderFiles})
target_sources(${TARGET_NAME} PRIVATE ${primaryHeaderFiles})
source_group("src/Conversions" FILES ${conversionFiles})
target_sources(${TARGET_NAME} PRIVATE ${conversionFiles})
source_group("src/Internal" FILES ${internalFiles})
target_sources(${TARGET_NAME} PRIVATE ${internalFiles})


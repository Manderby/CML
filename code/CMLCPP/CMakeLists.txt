cmake_minimum_required(VERSION 3.13)
project(CMLCPP)

set(TARGET_NAME CMLCPP)
add_library(${TARGET_NAME} STATIC)

set_target_properties(${TARGET_NAME} PROPERTIES LINKER_LANGUAGE CPP)
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (MSVC)
  # multi processor compilation
  target_compile_options(${TARGET_NAME} PRIVATE /MP)
else()
endif()



set(headerFiles
  src/CMLCMYKColor.h
  src/CMLColor.h
  src/CMLGrayColor.h
  src/CMLHSLColor.h
  src/CMLHSVColor.h
  src/CMLLabColor.h
  src/CMLLchColor.h
  src/CMLLuvColor.h
  src/CMLRGBColor.h
  src/CMLSpectralColor.h
  src/CMLXYZColor.h
  src/CMLYCbCrColor.h
  src/CMLYupvpColor.h
  src/CMLYuvColor.h
  src/CMLYxyColor.h
)

set(sourceFiles
  src/CMLCMYKColor.cpp
  src/CMLColor.cpp
  src/CMLGrayColor.cpp
  src/CMLHSLColor.cpp
  src/CMLHSVColor.cpp
  src/CMLLabColor.cpp
  src/CMLLchColor.cpp
  src/CMLLuvColor.cpp
  src/CMLRGBColor.cpp
  src/CMLSpectralColor.cpp
  src/CMLXYZColor.cpp
  src/CMLYCbCrColor.cpp
  src/CMLYupvpColor.cpp
  src/CMLYuvColor.cpp
  src/CMLYxyColor.cpp
)

source_group("Header Files" FILES ${headerFiles})
target_sources(${TARGET_NAME} PRIVATE ${headerFiles})
source_group("Source Files" FILES ${sourceFiles})
target_sources(${TARGET_NAME} PRIVATE ${sourceFiles})



# ######### Linking to CML ################

set(CML_DIR "../CML")
target_include_directories(${TARGET_NAME} PRIVATE ${CML_DIR}/src)
add_subdirectory(${CML_DIR} CML)
target_link_libraries(${TARGET_NAME} PRIVATE CML)


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
  src/CMLBaseAPI.h
)

set(conversionFiles
  src/Conversions/CMLClamp.c
)

set(internalFiles
  src/Internal/CMLBaseAPI.c
)

source_group("src" FILES ${primaryHeaderFiles})
target_sources(${TARGET_NAME} PRIVATE ${primaryHeaderFiles})
source_group("src/Conversions" FILES ${conversionFiles})
target_sources(${TARGET_NAME} PRIVATE ${conversionFiles})
source_group("src/Internal" FILES ${internalFiles})
target_sources(${TARGET_NAME} PRIVATE ${internalFiles})

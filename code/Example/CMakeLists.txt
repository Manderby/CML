cmake_minimum_required(VERSION 3.13)
project(Example)

set(TARGET_NAME Example)
add_executable(${TARGET_NAME})

set(CMAKE_CXX_STANDARD 99)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (MSVC)
  # multi processor compilation
  target_compile_options(${TARGET_NAME} PRIVATE /MP)
else()
endif()


# ######### Sources ################

set(sourceFiles
  src/example.c
  src/Timer.h
)

source_group("" FILES ${sourceFiles})
target_sources(${TARGET_NAME} PRIVATE ${sourceFiles})



# ######### Linking to CML ################

set(CML_DIR "../CML")
target_include_directories(${TARGET_NAME} PRIVATE ${CML_DIR}/src)
add_subdirectory(${CML_DIR} CML)
target_link_libraries(${TARGET_NAME} PRIVATE CML)


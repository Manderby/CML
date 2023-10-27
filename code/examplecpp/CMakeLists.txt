cmake_minimum_required(VERSION 3.13)
project(ExampleCPP)

set(TARGET_NAME ExampleCPP)
add_executable(${TARGET_NAME})

set_target_properties(${TARGET_NAME} PROPERTIES LINKER_LANGUAGE CPP)
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (MSVC)
  # multi processor compilation
  target_compile_options(${TARGET_NAME} PRIVATE /MP)
else()
endif()


# ######### Sources ################

set(sourceFiles
  src/examplecpp.cpp
)

source_group("" FILES ${sourceFiles})
target_sources(${TARGET_NAME} PRIVATE ${sourceFiles})



# ######### Linking to CMLCPP ################

set(CMLCPP_DIR "../CMLCPP")
target_include_directories(${TARGET_NAME} PRIVATE ${CMLCPP_DIR}/src)
add_subdirectory(${CMLCPP_DIR} CMLCPP)
target_link_libraries(${TARGET_NAME} PRIVATE CMLCPP)

set(CML_DIR "../CML")
target_include_directories(${TARGET_NAME} PRIVATE ${CML_DIR}/src)

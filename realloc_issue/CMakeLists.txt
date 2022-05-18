cmake_minimum_required(VERSION 3.16)

project(multi_thread)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../wamr wamr)
include_directories(${wamr_INCLUDE})

add_subdirectory(app)


get_filename_component(WASI_SDK_DIR $ENV{WASI_SDK_HOME} ABSOLUTE)
message("WASI_SDK_DIR=${WASI_SDK_DIR}")

include(ExternalProject)
ExternalProject_Add(
    script
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/script
    BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/script
    CMAKE_CACHE_ARGS
    -DWASI_SDK_PREFIX:FILEPATH=${WASI_SDK_DIR}
    -DCMAKE_TOOLCHAIN_FILE:FILEPATH=${WASI_SDK_DIR}/share/cmake/wasi-sdk.cmake
    -DCMAKE_TRY_COMPILE_TARGET_TYPE:STRING=STATIC_LIBRARY
    -DWAMR_ROOT_DIR:FILEPATH=${WAMR_ROOT_DIR}
    -DWASM_OUT_DIR:FILEPATH=${CMAKE_CURRENT_BINARY_DIR}
    INSTALL_COMMAND ""
    BUILD_ALWAYS 1
)

add_dependencies(
    app
    script
)
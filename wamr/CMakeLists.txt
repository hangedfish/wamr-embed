cmake_minimum_required(VERSION 3.16)

project(wamr)

set(WAMR_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/wasm-micro-runtime)
set(WAMR_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/wasm-micro-runtime PARENT_SCOPE)

set(wamr_INCLUDE ${WAMR_ROOT_DIR}/core/iwasm/include PARENT_SCOPE)

string(TOLOWER ${CMAKE_SYSTEM_NAME} WAMR_BUILD_PLATFORM)
set (WAMR_BUILD_INTERP 1)
set (WAMR_BUILD_FAST_INTERP 1)
set (WAMR_BUILD_AOT 0)
set (WAMR_BUILD_LIBC_WASI 1)
set (WAMR_BUILD_LIBC_BUILTIN 1)
set (WAMR_BUILD_LIB_PTHREAD 1)

set(CMAKE_C_STANDARD 11)


set(WAMR_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/wasm-micro-runtime)
include (${WAMR_ROOT_DIR}/build-scripts/runtime_lib.cmake)

add_library(
    iwasm
    STATIC
    ${WAMR_RUNTIME_LIB_SOURCE}
    )

target_link_libraries (
    iwasm
    m
    dl
    pthread
)

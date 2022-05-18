cmake_minimum_required(VERSION 3.16)

project(script)

set(CMAKE_CXX_STANDARD 20)

set(script_sources
    script.cpp
)

if(${CMAKE_SYSTEM_NAME} STREQUAL "WASI")
    set(BUILD_FOR_WASM 1)
    set(CMAKE_EXECUTABLE_SUFFIX ".wasm")
else()
    set(BUILD_FOR_WASM 0)
endif()

add_executable(
    script
    ${script_sources}
)

if(${BUILD_FOR_WASM})
    target_link_options(
        script
        PRIVATE
        -Wl,--export=__heap_base
        -Wl,--export=__data_end
        -Wl,--allow-undefined
        -Wl,--no-entry
        -Wl,--export=test
        -mexec-model=reactor
        -nostdlib
    )

    add_custom_command(
        TARGET script
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:script>" "${WASM_OUT_DIR}" VERBATIM
    )
endif()


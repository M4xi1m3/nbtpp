cmake_minimum_required(VERSION 3.16)
project(nbtpp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Grab all sources
file(GLOB SOURCES "src/*.cpp" "src/*/*.cpp")

# Use standard install dirs
include(GNUInstallDirs)

# this is the "object library" target: compiles the sources only once
add_library(NBTPP_OBJECTS OBJECT ${SOURCES})

# shared libraries need PIC
set_property(TARGET NBTPP_OBJECTS PROPERTY POSITION_INDEPENDENT_CODE 1)

# shared and static libraries built from the same object files
add_library(nbtpp SHARED $<TARGET_OBJECTS:NBTPP_OBJECTS>)
add_library(nbtpp_static STATIC $<TARGET_OBJECTS:NBTPP_OBJECTS>)

# Add stde as a dependency
if(NOT HAS_STDE)
    message(WARNING "Downloading stde...")
    configure_file(CMakeLists.txt.in stde-download/CMakeLists.txt)

    execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/stde-download"
    )
    execute_process(COMMAND "${CMAKE_COMMAND}" --build .
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/stde-download"
    )

    add_subdirectory(${CMAKE_SOURCE_DIR}/external/stde)

    set(STDE_HEADERS ${CMAKE_SOURCE_DIR}/external/stde/include)
endif()
target_link_libraries(nbtpp stde)
target_link_libraries(nbtpp_static stde_static)

# Set include directory for the library and the examples
target_include_directories(NBTPP_OBJECTS PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/nbtpp>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)
target_include_directories(NBTPP_OBJECTS PUBLIC
    ${STDE_HEADERS}
    PRIVATE src)

# Add tests executable
add_executable(nbtpptests example/tests.cpp)

target_include_directories(nbtpptests PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE example)
target_include_directories(nbtpptests PUBLIC
    ${STDE_HEADERS}
    $<INSTALL_INTERFACE:include>
    PRIVATE example)

target_link_libraries(nbtpptests nbtpp_static)


cmake_minimum_required(VERSION 3.16)
project(nbtpp)

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
add_subdirectory(external/stde)
target_link_libraries(nbtpp stde)
target_link_libraries(nbtpp_static stde_static)

# Set include directory for the library and the examples
target_include_directories(NBTPP_OBJECTS PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/nbtpp>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)
target_include_directories(NBTPP_OBJECTS PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/external/stde/include>
    PRIVATE src)


# Add install for shared lib
install(TARGETS ${PROJECT_NAME} EXPORT nbtppConfig
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})

# Add install for includes
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})

# Add install for config
install(EXPORT nbtppConfig DESTINATION share/nbtpp/cmake)
export(TARGETS ${PROJECT_NAME} FILE nbtppConfig.cmake)

# Add tests executable
add_executable(nbtpptests example/tests.cpp)

target_include_directories(nbtpptests PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE example)
target_include_directories(nbtpptests PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/external/stde/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE example)

target_link_libraries(nbtpptests nbtpp_static)


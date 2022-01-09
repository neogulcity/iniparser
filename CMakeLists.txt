# Miminum required version of CMake.
cmake_minimum_required(VERSION 3.11)

# Project info
project(
    iniparser
    VERSION 1.0.0
    DESCRIPTION "Basic iniparser"
    LANGUAGES CXX
)

# Cache variables
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set variable 'srcPath' to ./src
set(srcPath ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Find spdlog.
find_package(spdlog CONFIG REQUIRED)

# Checking build type
if (CMAKE_BUILD_TYPE STREQUAL "")
    # Build type is not set.
    message(STATUS "Build type was unspecified, set to Release")
    set(CMAKE_BUILD_TYPE Release)
else ()
    message(STATUS "Build type specified as '${CMAKE_BUILD_TYPE}'")
endif ()

# Making debug definition.
if (${CMAKE_BUILD_TYPE} STREQUAL Debug)
    set_directory_properties(PROPERTIES COMPILE_DEFINITIONS "_DEBUG")
else ()
    set_directory_properties(PROPERTIES COMPILE_DEFINITIONS "NDEBUG")
endif ()

# Make library file.
add_library(
    ${PROJECT_NAME}
    STATIC
    ${srcPath}/iniparser.cpp
    ${srcPath}/Utility.cpp
)

# Set library include directories
target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    ${srcPath}
)

# Link spdlog.
target_link_libraries(
	${PROJECT_NAME}
	PRIVATE
	spdlog::spdlog_header_only
)

# Compile options.
target_compile_options(
    ${PROJECT_NAME}
    PRIVATE
    -Wall
    -Werror
)

# Set start project for Visual Studio.
if (MSVC)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
endif ()

# Making package
configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/iniparserConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/iniparser
)

target_include_directories(iniparser
    PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

set_property(TARGET iniparser PROPERTY VERSION ${PROJECT_VERSION})
set_property(TARGET iniparser PROPERTY SOVERSION 3)
set_property(TARGET iniparser PROPERTY
  INTERFACE_iniparser_MAJOR_VERSION 3)
set_property(TARGET iniparser APPEND PROPERTY
  COMPATIBLE_INTERFACE_STRING iniparser_MAJOR_VERSION
)

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/iniparserConfigVersion.cmake"
  VERSION "${version}"
  COMPATIBILITY AnyNewerVersion
)

install(TARGETS iniparser
        EXPORT iniparserTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(FILES src/iniparser.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/iniparser
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/iniparserConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/iniparserConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/iniparser
)

install(EXPORT iniparserTargets
        FILE iniparserTargets.cmake
        NAMESPACE iniparser::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/iniparser
)

export(EXPORT iniparserTargets
       FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/iniparserTargets.cmake"
       NAMESPACE iniparser::
)
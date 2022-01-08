# Miminum required version of CMake.
cmake_minimum_required(VERSION 3.11)

# Project info
project(
    iniparser
    VERSION 1.0.0
    DESCRIPTION "Basic iniparser"
    LANGUAGES CXX
)

# Set variable 'srcPath' to ./src
set(srcPath ${CMAKE_SOURCE_DIR}/src)

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
add_executable(
    ${PROJECT_NAME}
    ${srcPath}/main.cpp
    ${srcPath}/Utility.cpp
)

# Link spdlog.
target_link_libraries(
	${PROJECT_NAME}
	PRIVATE
	spdlog::spdlog_header_only
)

# Set start project for Visual Studio.
if (MSVC)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
endif ()
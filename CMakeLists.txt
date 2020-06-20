CMAKE_MINIMUM_REQUIRED (VERSION 3.5)
PROJECT (SimpleUtils)

#-------------------------------------------------------------------------------
# Set Compiler
#-------------------------------------------------------------------------------
SET( CMAKE_CXX_STANDARD 11)
SET( CMAKE_CXX_STANDARD_REQUIRED ON )
ADD_COMPILE_OPTIONS ( -g -Wall -Wextra )

#-------------------------------------------------------------------------------
# Set Configure
#-------------------------------------------------------------------------------
SET(SIMPLE_SUTIL_TARGET_NAME ${PROJECT_NAME})

#-------------------------------------------------------------------------------
# Set Build Variable
#-------------------------------------------------------------------------------
SET(PROJECT_DIR ${PROJECT_SOURCE_DIR})
SET(BUILD_DIR_EXAMPLES ${CMAKE_SOURCE_DIR}/build/bin)

SET(SUTIL_INCLUDES
    ${PROJECT_DIR}/include
)

#-------------------------------------------------------------------------------
# Set SubDirectory
#-------------------------------------------------------------------------------
add_subdirectory(example)

#-------------------------------------------------------------------------------
# Set gTest
#-------------------------------------------------------------------------------
include(cmake/googletest.cmake)

fetch_googletest(
    ${PROJECT_SOURCE_DIR}/cmake
    ${PROJECT_BINARY_DIR}/googletest
)

enable_testing()

add_subdirectory(tests)
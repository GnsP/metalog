# This file is part of metalog, a free software.
# Use, modification and distribution is subject to the BSD 2-clause license.
# See accompanying file LICENSE.txt for its full text.

cmake_minimum_required(VERSION 2.8.3)

option(BUILD_TESTS "build test scripts" ON)

project(metalog CXX)

find_package(Boost 1.51 REQUIRED)

set(METALOG_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(METALOG_INCLUDE_DIRS ${METALOG_INCLUDE_DIR} ${Boost_INCLUDE_DIRS})

file(GLOB_RECURSE METALOG_HEADERS ${METALOG_INCLUDE_DIR}/*.hpp)

add_custom_target(metalog SOURCES ${METALOG_HEADERS})
install(FILES ${METALOG_HEADERS} DESTINATION include)

if(BUILD_TESTS)
    add_subdirectory(test EXCLUDE_FROM_ALL)
endif()


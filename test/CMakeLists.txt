# This file is part of munify, a free software.
# Use, modification and distribution is subject to the BSD 2-clause license.
# See accompanying file LICENSE.txt for its full text.

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(EnableExtraCompilerWarnings)
include(DisableCompilerExtensions)
include(TargetUtils)

function(standard_flag STANDARD RESULT)
    if(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
        set(${RESULT} "-std=c++${STANDARD}" PARENT_SCOPE)
    endif()
endfunction()

enable_testing()

globally_disable_compiler_extensions()
globally_enable_extra_compiler_warnings()
string(REGEX REPLACE "-Weffc\\+\\+" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})

file(GLOB_RECURSE MUNIFY_TEST_HEADERS "*.hpp")
file(GLOB_RECURSE MUNIFY_TEST_SOURCES "*.cpp")

include_directories(${MUNIFY_INCLUDE_DIRS})
link_directories(${MUNIFY_LIBRARY_DIRS})

set(SUPPORTED_STANDARDS "03;11")
foreach(STANDARD ${SUPPORTED_STANDARDS})
    standard_flag(${STANDARD} STANDARD_FLAG)
    foreach(SOURCE ${MUNIFY_TEST_SOURCES})
        string(REGEX REPLACE ".*[/\\](.*\)[.]cpp" "\\1_test_CXX${STANDARD}" TARGET ${SOURCE})
        add_binary_target(
            EXECUTABLE ${TARGET}
            LANGUAGE "CXX"
            SOURCES ${SOURCE} ${MUNIFY_TEST_HEADERS}
            LIBRARIES ${MUNIFY_LIBRARIES}
            ADITIONAL_FLAGS ${STANDARD_FLAG}
            DEPENDENCIES munify
        )
        add_test(${TARGET} ${CMAKE_CURRENT_BINARY_DIR}/${TARGET})
    endforeach()
    set(TEST_TARGETS ${TEST_TARGETS} ${TARGET})
endforeach()

add_custom_target(tests DEPENDS ${TEST_TARGETS})
add_custom_command(
    TARGET tests
    COMMENT "unity tests"
    POST_BUILD
    COMMAND ${CMAKE_CTEST_COMMAND}
    ARGS --output-on-failure
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

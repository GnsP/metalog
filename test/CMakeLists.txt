# This file is part of munify, a free software.
# Use, modification and distribution is subject to the BSD 2-clause license.
# See accompanying file LICENSE.txt for its full text.

enable_testing()

include_directories(${MUNIFY_INCLUDE_DIRS})

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic-errors")
    set(SUPPORTED_STANDARDS "03" "11")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weverything -pedantic-errors")
    set(SUPPORTED_STANDARDS "03" "11")
endif()

file(GLOB_RECURSE MUNIFY_TEST_HEADERS "*.hpp")
file(GLOB_RECURSE MUNIFY_TEST_SOURCES "*.cpp")

function(add_test_target_for_each SOURCES HEADERS ADITIONAL_CXX_FLAGS DEPENDENCIES LIBS SUFIX RESULT)
    set(TEST_TARGETS "")
    foreach(SOURCE ${SOURCES})
        string(REGEX REPLACE ".*[/\\](.*\)[.]cpp" "\\1${SUFIX}" TEST_TARGET ${SOURCE})
        add_executable(${TEST_TARGET} ${SOURCE} ${HEADERS})
        if(ADITIONAL_CXX_FLAGS)
            set_target_properties(${TEST_TARGET} PROPERTIES COMPILE_FLAGS ${ADITIONAL_CXX_FLAGS})
        endif()
        if(DEPENDENCIES)
            add_dependencies(${TEST_TARGET} ${DEPENDENCIES})
        endif()
        if(LIBS)
            target_link_libraries(${TEST_TARGET} ${LIBS})
        endif()
        add_test(${TEST_TARGET} ${CMAKE_CURRENT_BINARY_DIR}/${TEST_TARGET})
        set(TEST_TARGETS ${TEST_TARGETS} ${TEST_TARGET})
    endforeach()
    set(${RESULT} ${TEST_TARGETS} PARENT_SCOPE)
endfunction()

function(standard_flag COMPILER STANDARD RESULT)
    if(${COMPILER} STREQUAL "GNU" OR ${COMPILER} STREQUAL "CLANG")
        set(${RESULT} "-std=c++${STANDARD}" PARENT_SCOPE)
    endif()
endfunction()

set(TEST_TARGETS "")
foreach(STANDARD ${SUPPORTED_STANDARDS})
    standard_flag("${CMAKE_CXX_COMPILER_ID}" ${STANDARD} STANDARD_FLAG)
    add_test_target_for_each("${MUNIFY_TEST_SOURCES}" "${MUNIFY_TEST_HEADERS}" "${STANDARD_FLAG}" munify "" "_test_cxx${STANDARD}" RESULT)
    set(TEST_TARGETS "${TEST_TARGETS} ${RESULT}")
endforeach()

add_custom_target(ctest COMMAND ${CMAKE_CTEST_COMMAND} DEPENDS ${TEST_TARGETS})

# This file is part of munify, a free software.
# Use, modification and distribution is subject to the BSD 2-clause license.
# See accompanying file LICENSE.txt for its full text.

enable_testing()

include_directories(${MUNIFY_INCLUDE_DIRS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic-errors")

file(GLOB_RECURSE MUNIFY_TEST_HEADERS "*.hpp")
file(GLOB_RECURSE MUNIFY_TEST_SOURCES "*.cpp")

function(add_test_target_for_each SOURCES HEADERS CXX_FLAGS DEPENDENCIES LIBS SUFIX RESULT)
    set(TEST_TARGETS "")
    foreach(SOURCE ${SOURCES})
        string(REGEX REPLACE ".*[/\\](.*\)[.]cpp" "\\1${SUFIX}" TEST_TARGET ${SOURCE})
        add_executable(${TEST_TARGET} ${SOURCE} ${HEADERS})
        if(CXX_FLAGS)
            set_target_properties(${TEST_TARGET} PROPERTIES COMPILE_FLAGS ${CXX_FLAGS})
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

add_test_target_for_each("${MUNIFY_TEST_SOURCES}" "${MUNIFY_TEST_HEADERS}" "-std=c++11" munify "" "_test_11" TEST_TARGETS_11)
add_test_target_for_each("${MUNIFY_TEST_SOURCES}" "${MUNIFY_TEST_HEADERS}" "-std=c++03" munify "" "_test_03" TEST_TARGETS_03)

set(TEST_TARGETS ${TEST_TARGETS_11} ${TEST_TARGETS_03})
add_custom_target(ctest COMMAND ${CMAKE_CTEST_COMMAND} DEPENDS ${TEST_TARGETS})

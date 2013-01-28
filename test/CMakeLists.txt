# This file is part of munify, a free software.
# Use, modification and distribution is subject to the BSD 2-clause license.
# See accompanying file LICENSE.txt for its full text.

enable_testing()

include_directories(${MUNIFY_INCLUDE_DIRS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -ansi -std=c++0x")

file(GLOB_RECURSE MUNIFY_TEST_HEADERS "*.hpp")
file(GLOB_RECURSE MUNIFY_TEST_SOURCES "*.cpp")

foreach(SOURCE ${MUNIFY_TEST_SOURCES}) 
    string(REGEX REPLACE ".*[/\\](.*\)[.]cpp" "\\1_test" TEST_TARGET ${SOURCE})
    add_executable(${TEST_TARGET} ${SOURCE} ${MUNIFY_TEST_HEADERS})
    add_dependencies(${TEST_TARGET} m4th)
    target_link_libraries(${TEST_TARGET})
    add_test(${TEST_TARGET} ${CMAKE_CURRENT_BINARY_DIR}/${TEST_TARGET})
    list(APPEND TEST_TARGETS ${TEST_TARGET})
endforeach(SOURCE)

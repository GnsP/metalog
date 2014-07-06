# This file is part of munify, a free software.
# Use, modification and distribution is subject to the BSD 2-clause license.
# See accompanying file LICENSE.txt for its full text.

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(CompilerUtils)
include(EnableExtraCompilerWarnings)
include(DisableCompilerExtensions)
include(TargetUtils)

enable_testing()

globally_disable_compiler_extensions()
globally_enable_extra_compiler_warnings()

file(GLOB_RECURSE MUNIFY_TEST_HEADERS "*.hpp")
file(GLOB_RECURSE MUNIFY_TEST_SOURCES "*.cpp")

include_directories(${MUNIFY_INCLUDE_DIRS})
link_directories(${MUNIFY_LIBRARY_DIRS})

set(SUPPORTED_STANDARDS "C++03;C++11")
foreach(DIALECT ${SUPPORTED_STANDARDS})
    language_dialect_flags("CXX" ${DIALECT} DIALECT_FLAGS)
    foreach(SOURCE ${MUNIFY_TEST_SOURCES})
        string(REGEX REPLACE ".*[/\\](.*\)[.]cpp" "\\1_test_${DIALECT}" TARGET ${SOURCE})
        add_binary_target(
            EXECUTABLE ${TARGET}
            LANGUAGE "CXX"
            SOURCES ${SOURCE} ${MUNIFY_TEST_HEADERS}
            LIBRARIES ${MUNIFY_LIBRARIES}
            ADITIONAL_FLAGS ${DIALECT_FLAGS}
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

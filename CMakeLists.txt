cmake_minimum_required(VERSION 3.0)
project(regex_dp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -fprofile-arcs -ftest-coverage ${CMAKE_CXX_FLAGS_DEBUG}")
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/)

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
        ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL)

include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB_RECURSE SOURCES src/*.cpp main/*.cpp)
add_executable(regex_dp ${SOURCES})

file(GLOB_RECURSE TEST_SOURCES src/*.cpp src_tests/*.cpp)
add_executable(tester ${TEST_SOURCES})
target_include_directories(tester PRIVATE "${gtest_SOURCE_DIR}/include")
target_link_libraries(tester gtest_main gcov)
target_compile_options(tester PRIVATE "--coverage")

if (CMAKE_BUILD_TYPE MATCHES Debug)
    include(CodeCoverage)
    setup_target_for_coverage(${PROJECT_NAME}_coverage tester coverage)
    setup_target_for_coverage_cobertura(${PROJECT_NAME}_cobertura tester coverage --gtest_output=xml:coverage.junit.xml)
endif()

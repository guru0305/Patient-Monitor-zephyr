cmake_minimum_required(VERSION 3.20)

project(PatientMonitorTests LANGUAGES CXX)

option(ENABLE_COVERAGE "Enable coverage reporting" OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ------------------------------------------------------------
# GoogleTest
# ------------------------------------------------------------
include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_MakeAvailable(googletest)

enable_testing()

# ------------------------------------------------------------
# Production Sources
# ------------------------------------------------------------
set(PROJECT_SOURCES
    ../src/observer/Subject.cpp
    ../src/datasource/SineWaveSource.cpp
    ../src/datasource/FakeVitalSource.cpp
    ../src/model/DataModel.cpp
    ../src/alarm/AlarmEngine.cpp
    ../src/controller/ViewController.cpp


    stubs/threads/UIMessageQueue.cpp
)

# ------------------------------------------------------------
# Test Sources
# ------------------------------------------------------------
set(TEST_SOURCES
    test_main.cpp

    observer/test_Subject.cpp

    datasource/test_SineWaveSource.cpp
    datasource/test_FakeVitalSource.cpp

    model/test_DataModel.cpp
    controller/test_ViewController.cpp
    alarm/test_AlarmEngine.cpp
)

# ------------------------------------------------------------
# Test Executable
# ------------------------------------------------------------
add_executable(PatientMonitorTests
    ${PROJECT_SOURCES}
    ${TEST_SOURCES}
)

# ------------------------------------------------------------
# Coverage
# ------------------------------------------------------------
if(ENABLE_COVERAGE)

    message(STATUS "Coverage Enabled")

    target_compile_options(PatientMonitorTests PRIVATE
        -O0
        -g
        --coverage
    )

    target_link_options(PatientMonitorTests PRIVATE
        --coverage
    )

endif()

# ------------------------------------------------------------
# Include Directories
# ------------------------------------------------------------
target_include_directories(PatientMonitorTests PRIVATE
    ${PROJECT_SOURCE_DIR}/stubs
    ${PROJECT_SOURCE_DIR}/../include
    ${PROJECT_SOURCE_DIR}
)

# ------------------------------------------------------------
# Libraries
# ------------------------------------------------------------
target_link_libraries(PatientMonitorTests PRIVATE
    GTest::gtest
    GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(PatientMonitorTests)

# ------------------------------------------------------------
# Coverage Report
# ------------------------------------------------------------
find_program(LCOV_EXECUTABLE lcov)
find_program(GENHTML_EXECUTABLE genhtml)

if(ENABLE_COVERAGE AND LCOV_EXECUTABLE AND GENHTML_EXECUTABLE)

    add_custom_target(coverage
        DEPENDS PatientMonitorTests

        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/PatientMonitorTests

        COMMAND ${LCOV_EXECUTABLE}
            --capture
            --directory .
            --rc branch_coverage=1
            --ignore-errors mismatch,inconsistent,unused
            --output-file coverage.info

        COMMAND ${LCOV_EXECUTABLE}
            --remove coverage.info
            "/usr/*"
            "*/_deps/*"
            "*/tests/*"
            #"*/include/observer/IObserver.hpp"
            --rc branch_coverage=1
            --ignore-errors mismatch,inconsistent,unused
            --output-file coverage.info

        COMMAND ${GENHTML_EXECUTABLE}
            coverage.info
            --branch-coverage
            --output-directory coverage

        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}

        COMMENT "Generating Coverage Report"
    )

    add_custom_target(clean_coverage

        COMMAND find . -name "*.gcda" -delete
        COMMAND find . -name "*.gcov" -delete
        COMMAND ${CMAKE_COMMAND} -E rm -f coverage.info

        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}

        COMMENT "Cleaning Coverage Files"
    )

endif()
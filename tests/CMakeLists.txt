cmake_minimum_required(VERSION 3.20)

project(PatientMonitorTests LANGUAGES C CXX)

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
    ../src/datasource/AdcSource.cpp
    ../src/model/DataModel.cpp
    ../src/alarm/AlarmEngine.cpp
    ../src/controller/ApplicationController.cpp
    ../src/controller/ViewController.cpp
    ../src/ui/DashboardView.cpp
    ../src/ui/ScreenBuilder.cpp
    ../src/threads/SensorThread.cpp
    ../src/threads/AlarmThread.cpp
    ../src/threads/LVGLThread.cpp

    ../assets/heart.c
    ../assets/spo2.c
    ../assets/rr.c

    stubs/zephyr/drivers/uart.cpp
    stubs/threads/UIMessageQueue.cpp
    stubs/zephyr/device.cpp
    stubs/zephyr/usb/usb_device.cpp
    stubs/zephyr/kernel.cpp
)

# ------------------------------------------------------------
# Test Sources
# ------------------------------------------------------------
set(TEST_SOURCES
    test_main.cpp

    observer/test_Subject.cpp

    datasource/test_SineWaveSource.cpp
    datasource/test_FakeVitalSource.cpp
    datasource/test_AdcSource.cpp

    model/test_DataModel.cpp
    controller/test_ViewController.cpp
    controller/test_ApplicationController.cpp
    alarm/test_AlarmEngine.cpp

    threads/test_SensorThread.cpp
    threads/test_AlarmThread.cpp
    threads/test_LVGLThread.cpp

    ui/test_ScreenBuilder.cpp
    ui/test_DashboardView.cpp
)

set(LV_BUILD_CONF_PATH
    "${CMAKE_CURRENT_SOURCE_DIR}/../lv_conf.h"
    CACHE FILEPATH "LVGL configuration"
)

add_subdirectory(
    ${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty/lvgl
    ${CMAKE_BINARY_DIR}/lvgl
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
        -fno-exceptions
        -fno-rtti
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

    ${PROJECT_SOURCE_DIR}/../thirdparty/lvgl
    ${PROJECT_SOURCE_DIR}/../thirdparty/lvgl/src
)

# ------------------------------------------------------------
# Libraries
# ------------------------------------------------------------
target_link_libraries(PatientMonitorTests PRIVATE
    GTest::gtest
    GTest::gtest_main
    lvgl
)

target_compile_definitions(PatientMonitorTests PRIVATE
    UNIT_TEST
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
            "*/thirdparty/lvgl/*"
            --rc branch_coverage=1
            --ignore-errors mismatch,inconsistent,unused
            --output-file coverage.info

        COMMAND ${GENHTML_EXECUTABLE}
            coverage.info
            --branch-coverage
            --no-function-coverage
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
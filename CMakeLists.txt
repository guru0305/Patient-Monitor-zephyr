cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(PatientMonitor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

target_include_directories(app PRIVATE
    include
)

target_sources(app PRIVATE

    app/main.cpp

    src/controller/ApplicationController.cpp
    src/controller/ViewController.cpp

    src/datasource/SineWaveSource.cpp
    src/datasource/FakeVitalSource.cpp
    src/datasource/AdcSource.cpp

    src/model/DataModel.cpp

    src/alarm/AlarmEngine.cpp

    src/observer/Subject.cpp

    src/ui/DashboardView.cpp
    src/ui/ScreenBuilder.cpp

    src/threads/SensorThread.cpp
    src/threads/LVGLThread.cpp
    src/threads/AlarmThread.cpp
    src/threads/UIMessageQueue.cpp

    assets/heart.c
    assets/spo2.c
    assets/rr.c
)
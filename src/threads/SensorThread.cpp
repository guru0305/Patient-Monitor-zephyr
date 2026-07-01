#include "threads/SensorThread.hpp"

#include <zephyr/kernel.h>

#include "controller/ApplicationController.hpp"

namespace
{
ApplicationController* controller_ = nullptr;

void SensorThreadEntry(
    void*,
    void*,
    void*)
{
    while (true)
    {
        if (controller_ != nullptr)
        {
            controller_->Update();
        }

        k_sleep(K_SECONDS(1));
    }
}
}

void InitSensorThread(ApplicationController& controller)
{
    controller_ = &controller;
}

K_THREAD_DEFINE(
    sensor_thread,
    2048,
    SensorThreadEntry,
    nullptr,
    nullptr,
    nullptr,
    5,
    0,
    0);
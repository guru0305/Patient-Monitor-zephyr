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
    uint16_t ecg_counter = 0;

    while (true)
    {
        controller_->UpdateECG();

        ecg_counter++;

        if (ecg_counter >= 250)
        {
            ecg_counter = 0;

            controller_->UpdateVitals();
        }

        k_sleep(K_MSEC(4));
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
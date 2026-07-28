#include "threads/SensorThread.hpp"
#include "datasource/AdcSource.hpp"
#include <zephyr/kernel.h>

#include "controller/ApplicationController.hpp"

namespace
{
ApplicationController* controller_ = nullptr;
AdcSource* adc_source_ = nullptr;

K_SEM_DEFINE(sensor_ready_sem, 0, 1);

void SensorThreadEntry(void*, void*, void*)
{
    k_sem_take(&sensor_ready_sem, K_FOREVER);

    uint16_t ecg_counter = 0;

    while (true)
    {
        adc_source_->Process();

        while (adc_source_->HasSample())
        {
            adc_source_->PopSample();
            controller_->UpdateECG();
        }

        ecg_counter++;

        if (ecg_counter >= 250)
        {
            ecg_counter = 0;
            controller_->UpdateVitals();
        }

        k_sleep(K_MSEC(4));
    }
}
}  // namespace

void InitSensorThread(ApplicationController& controller,
                      AdcSource& adc_source)
{
    controller_ = &controller;
    adc_source_ = &adc_source;

    k_sem_give(&sensor_ready_sem);
}

K_THREAD_DEFINE(
    sensor_thread, 2048, SensorThreadEntry,
    nullptr, nullptr, nullptr,
    4, 0, 0);
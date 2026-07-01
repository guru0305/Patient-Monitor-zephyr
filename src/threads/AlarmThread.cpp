#include "threads/AlarmThread.hpp"

#include <zephyr/kernel.h>

#include "alarm/AlarmEngine.hpp"

namespace
{

AlarmEngine* alarm_ = nullptr;

void AlarmThreadEntry(
    void*,
    void*,
    void*)
{
    while (true)
    {
        if (alarm_ != nullptr)
        {
            alarm_->CheckThresholds();
        }

        k_sleep(K_MSEC(50));
    }
}

}

void InitAlarmThread(AlarmEngine& alarm)
{
    alarm_ = &alarm;
}

K_THREAD_DEFINE(
    alarm_thread,
    2048,
    AlarmThreadEntry,
    nullptr,
    nullptr,
    nullptr,
    4,
    0,
    0);
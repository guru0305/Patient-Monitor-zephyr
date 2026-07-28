#include "threads/AlarmThread.hpp"

#include <zephyr/kernel.h>

#include "alarm/AlarmEngine.hpp"

namespace
{

AlarmEngine* alarm_ = nullptr;

K_SEM_DEFINE(alarm_ready_sem, 0, 1);

void AlarmThreadEntry(
    void*,
    void*,
    void*)
{
    k_sem_take(&alarm_ready_sem, K_FOREVER);

    while (true)
    {
        alarm_->CheckThresholds();

        k_sleep(K_MSEC(50));
    }
}

}

void InitAlarmThread(AlarmEngine& alarm)
{
    alarm_ = &alarm;
    k_sem_give(&alarm_ready_sem);
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
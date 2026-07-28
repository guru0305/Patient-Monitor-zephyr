#include "threads/LVGLThread.hpp"
#include "threads/UIMessageQueue.hpp"

#include <zephyr/kernel.h>
#include "lvgl.h"

namespace
{

DashboardView* dashboard_ = nullptr;
ScreenBuilder* screen_builder_ = nullptr;

K_SEM_DEFINE(lvgl_ready_sem, 0, 1);

void LVGLThreadEntry(
    void*,
    void*,
    void*)
{
    k_sem_take(&lvgl_ready_sem, K_FOREVER);

    screen_builder_->build();

    UIMessage message;

    message.patient_data = {};
    message.alarm_state = {};

    uint32_t frame_count = 0;
    int64_t last_time = k_uptime_get();

    while (true)
    {
        while (k_msgq_get(
            &ui_message_queue,
            &message,
            K_NO_WAIT) == 0)
        {

        }

        dashboard_->Update(
            message.patient_data,
            message.alarm_state);
        
        lv_timer_handler();

        frame_count++;

        int64_t current_time = k_uptime_get();

        if ((current_time - last_time) >= 1000)
        {
            printk("FPS: %u\n", frame_count);

            frame_count = 0;
            last_time = current_time;
        }

        k_sleep(K_MSEC(5));
    }
}

}

void InitLVGLThread(
    DashboardView& dashboard,
    ScreenBuilder& screen_builder)
{
    dashboard_ = &dashboard;
    screen_builder_ = &screen_builder;
    k_sem_give(&lvgl_ready_sem);
}

K_THREAD_DEFINE(
    lvgl_thread,
    4096,
    LVGLThreadEntry,
    nullptr,
    nullptr,
    nullptr,
    5,
    0,
    0);
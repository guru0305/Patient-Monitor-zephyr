#include "threads/LVGLThread.hpp"
#include "threads/UIMessageQueue.hpp"

#include <zephyr/kernel.h>
#include "lvgl.h"

namespace
{

DashboardView* dashboard_ = nullptr;
ScreenBuilder* screen_builder_ = nullptr;

void LVGLThreadEntry(
    void*,
    void*,
    void*)
{
    if (screen_builder_ != nullptr)
    {
        screen_builder_->build();
    }

    UIMessage message;

    while (true)
    {
        while (k_msgq_get(
            &ui_message_queue,
            &message,
            K_NO_WAIT) == 0)
        {
            if (dashboard_ != nullptr)
            {
                dashboard_->Update(
                    message.patient_data,
                    message.alarm_state);
            }
        }

        lv_timer_handler();

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
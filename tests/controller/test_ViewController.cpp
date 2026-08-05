#include <gtest/gtest.h>

#include "controller/ViewController.hpp"
#include "model/DataModel.hpp"
#include "alarm/AlarmEngine.hpp"
#include "threads/UIMessageQueue.hpp"
#include "ui/DashboardView.hpp"
#include "ui/ScreenBuilder.hpp"
#include "lvgl.h"
#include "others/test/lv_test_display.h"

TEST(ViewControllerTest, NotifySendsMessageToQueue)
{
    lv_init();

    lv_display_t* display = lv_test_display_create(480, 320);

    DataModel model;
    AlarmEngine alarm(model);

    ScreenBuilder builder;
    builder.build();

    DashboardView view(builder, model);

    ViewController controller(
        model,
        alarm,
        view);

    PatientData data{};
    data.hr = 80;
    data.spo2 = 98;
    data.rr = 16;
    data.sys = 120;
    data.dias = 80;

    model.set_patient_data(data);
    alarm.CheckThresholds();

    mock_msgq_return = 0;

    controller.notify();

    EXPECT_EQ(mock_last_message.patient_data.hr, 80);
    EXPECT_EQ(mock_last_message.patient_data.spo2, 98);
    EXPECT_EQ(mock_last_message.patient_data.rr, 16);
    EXPECT_EQ(mock_last_message.patient_data.sys, 120);
    EXPECT_EQ(mock_last_message.patient_data.dias, 80);

    EXPECT_FALSE(mock_last_message.alarm_state.hr_alarm);
    EXPECT_FALSE(mock_last_message.alarm_state.spo2_alarm);
    EXPECT_FALSE(mock_last_message.alarm_state.rr_alarm);
    EXPECT_FALSE(mock_last_message.alarm_state.sys_alarm);
    EXPECT_FALSE(mock_last_message.alarm_state.dias_alarm);

    lv_display_delete(display);
    lv_deinit();
}

TEST(ViewControllerTest, QueueFullBranchIsExecuted)
{
    lv_init();

    lv_display_t* display = lv_test_display_create(480, 320);

    DataModel model;
    AlarmEngine alarm(model);

    ScreenBuilder builder;
    builder.build();

    DashboardView view(builder, model);

    ViewController controller(
        model,
        alarm,
        view);

    mock_msgq_return = -1;

    controller.notify();

    SUCCEED();

    lv_display_delete(display);
    lv_deinit();
}
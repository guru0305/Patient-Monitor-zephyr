#include <gtest/gtest.h>

#include "lvgl.h"
#include "others/test/lv_test_display.h"

#include "ui/ScreenBuilder.hpp"
#include "ui/DashboardView.hpp"
#include "model/DataModel.hpp"

class DashboardViewTest : public ::testing::Test
{
protected:
    lv_display_t* display = nullptr;

    ScreenBuilder builder;
    DataModel model;

    void SetUp() override
    {
        lv_init();

        display = lv_test_display_create(480, 320);

        builder.build();
    }

    void TearDown() override
    {
        if(display)
        {
            lv_display_delete(display);
        }

        lv_deinit();
    }
};

TEST_F(DashboardViewTest, ConstructorDoesNotCrash)
{
    DashboardView view(builder, model);

    SUCCEED();
}

TEST_F(DashboardViewTest, UpdateWithoutAlarmAndWithoutECGSamples)
{
    DashboardView view(builder, model);

    PatientData data{};

    data.hr = 80;
    data.spo2 = 98;
    data.rr = 16;
    data.sys = 120;
    data.dias = 80;
    data.mean = 93;
    data.monitor_status = MonitorStatus::Connected;

    AlarmState alarm{};

    alarm.priority = AlarmPriority::None;

    view.Update(data, alarm);

    EXPECT_STREQ(
        lv_label_get_text(builder.GetHRValueLabel()),
        "80");

    EXPECT_STREQ(
        lv_label_get_text(builder.GetSPO2ValueLabel()),
        "98");

    EXPECT_STREQ(
        lv_label_get_text(builder.GetRRValueLabel()),
        "16");

    EXPECT_STREQ(
        lv_label_get_text(builder.GetSYSValueLabel()),
        "120");

    EXPECT_STREQ(
        lv_label_get_text(builder.GetDIASValueLabel()),
        "80");

    EXPECT_STREQ(
        lv_label_get_text(builder.GetMEANValueLabel()),
        "93");

    EXPECT_STREQ(
        lv_label_get_text(builder.GetStatusLabel()),
        "•CONNECTED");

    EXPECT_STREQ(
        lv_label_get_text(builder.GetAlarmLabel()),
        LV_SYMBOL_BELL " NO ACTIVE ALARMS");
}

TEST_F(DashboardViewTest, UpdateWithECGSample)
{
    DashboardView view(builder, model);

    PatientData data{};

    data.hr = 80;
    data.spo2 = 98;
    data.rr = 16;
    data.sys = 120;
    data.dias = 80;
    data.mean = 93;
    data.monitor_status = MonitorStatus::Connected;

    AlarmState alarm{};
    alarm.priority = AlarmPriority::None;

    model.PushECGSample(150);
    model.PushECGSample(175);

    view.Update(data, alarm);

    SUCCEED();
}

TEST_F(DashboardViewTest, UpdateWithSYSAlarm)
{
    DashboardView view(builder, model);

    PatientData data{};

    data.hr = 80;
    data.spo2 = 98;
    data.rr = 16;
    data.sys = 170;
    data.dias = 80;
    data.mean = 110;
    data.monitor_status = MonitorStatus::Connected;

    AlarmState alarm{};

    alarm.sys_alarm = true;
    alarm.priority = AlarmPriority::High;
    alarm.message = "HIGH SYS";

    view.Update(data, alarm);

    EXPECT_STREQ(
        lv_label_get_text(builder.GetAlarmLabel()),
        LV_SYMBOL_WARNING " HIGH SYS");
}

TEST_F(DashboardViewTest, UpdateWithDIASAlarm)
{
    DashboardView view(builder, model);

    PatientData data{};

    data.hr = 80;
    data.spo2 = 98;
    data.rr = 16;
    data.sys = 120;
    data.dias = 110;
    data.mean = 113;
    data.monitor_status = MonitorStatus::Connected;

    AlarmState alarm{};

    alarm.dias_alarm = true;
    alarm.priority = AlarmPriority::High;
    alarm.message = "HIGH DIAS";

    view.Update(data, alarm);

    EXPECT_STREQ(
        lv_label_get_text(builder.GetAlarmLabel()),
        LV_SYMBOL_WARNING " HIGH DIAS");
}
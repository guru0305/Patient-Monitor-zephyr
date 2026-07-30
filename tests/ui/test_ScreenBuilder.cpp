#include <gtest/gtest.h>

#include "lvgl.h"
#include "others/test/lv_test_display.h"
#include "ui/ScreenBuilder.hpp"

class ScreenBuilderTest : public ::testing::Test
{
protected:

    lv_display_t * display = nullptr;

    void SetUp() override
    {
        lv_init();

        display = lv_test_display_create(480, 320);
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

TEST_F(ScreenBuilderTest, BuildDoesNotCrash)
{
    ScreenBuilder builder;

    builder.build();

    SUCCEED();
}

TEST_F(ScreenBuilderTest, UpdateHRWithoutAlarmUpdatesLabel)
{
    ScreenBuilder builder;

    builder.build();

    builder.UpdateHR(85, false);

    EXPECT_STREQ(
        lv_label_get_text(builder.GetHRValueLabel()),
        "85");
}

TEST_F(ScreenBuilderTest, UpdateHRWithAlarmUpdatesLabel)
{
    ScreenBuilder builder;

    builder.build();

    builder.UpdateHR(120, true);

    EXPECT_STREQ(
        lv_label_get_text(builder.GetHRValueLabel()),
        "120");
}

TEST_F(ScreenBuilderTest, UpdateHRAlarmOffClearsAlarmState)
{
    ScreenBuilder builder;

    builder.build();

    builder.UpdateHR(80, false);

    EXPECT_FALSE(builder.GetHRAlarmState());
}

TEST_F(ScreenBuilderTest, UpdateHRAlarmOnSetsAlarmState)
{
    ScreenBuilder builder;

    builder.build();

    builder.UpdateHR(150, true);

    EXPECT_TRUE(builder.GetHRAlarmState());
}

TEST_F(ScreenBuilderTest, UpdateSPO2UpdatesLabel)
{
    ScreenBuilder builder;

    builder.build();

    builder.UpdateSPO2(97, false);

    EXPECT_STREQ(
        lv_label_get_text(builder.GetSPO2ValueLabel()),
        "97");
}

TEST_F(ScreenBuilderTest, UpdateRRUpdatesLabel)
{
    ScreenBuilder builder;

    builder.build();

    builder.UpdateRR(18, false);

    EXPECT_STREQ(
        lv_label_get_text(builder.GetRRValueLabel()),
        "18");
}

TEST_F(ScreenBuilderTest, UpdateSYSUpdatesLabel)
{
    ScreenBuilder builder;

    builder.build();

    builder.UpdateSYS(120, false, false);

    EXPECT_STREQ(
        lv_label_get_text(builder.GetSYSValueLabel()),
        "120");
}

TEST_F(ScreenBuilderTest, UpdateDIASUpdatesLabel)
{
    ScreenBuilder builder;

    builder.build();

    builder.UpdateDIAS(80, false, false);

    EXPECT_STREQ(
        lv_label_get_text(builder.GetDIASValueLabel()),
        "80");
}

TEST_F(ScreenBuilderTest, UpdateMEANUpdatesLabel)
{
    ScreenBuilder builder;

    builder.build();

    builder.UpdateMEAN(93);

    EXPECT_STREQ(
        lv_label_get_text(builder.GetMEANValueLabel()),
        "93");
}

TEST_F(ScreenBuilderTest, UpdateAlarmBarNone)
{
    ScreenBuilder builder;

    builder.build();

    builder.UpdateAlarmBar("Normal", AlarmPriority::None);

    EXPECT_STREQ(
        lv_label_get_text(builder.GetAlarmLabel()),
        "Normal");
}

TEST_F(ScreenBuilderTest, UpdateAlarmBarHigh)
{
    ScreenBuilder builder;

    builder.build();

    builder.UpdateAlarmBar("SpO2 LOW", AlarmPriority::High);

    EXPECT_STREQ(
        lv_label_get_text(builder.GetAlarmLabel()),
        "SpO2 LOW");
}

TEST_F(ScreenBuilderTest, MonitorStatusConnected)
{
    ScreenBuilder builder;

    builder.build();

    builder.UpdateMonitorStatus(MonitorStatus::Connected);

    EXPECT_STREQ(
        lv_label_get_text(builder.GetStatusLabel()),
        "•CONNECTED");
}

TEST_F(ScreenBuilderTest, MonitorStatusDisconnected)
{
    ScreenBuilder builder;

    builder.build();

    builder.UpdateMonitorStatus(MonitorStatus::Disconnected);

    EXPECT_STREQ(
        lv_label_get_text(builder.GetStatusLabel()),
        "•DISCONNECTED");
}

TEST_F(ScreenBuilderTest, MonitorStatusLeadConnected)
{
    ScreenBuilder builder;

    builder.build();

    builder.UpdateMonitorStatus(MonitorStatus::CheckLeads);

    EXPECT_STREQ(
        lv_label_get_text(builder.GetStatusLabel()),
        "•CHECK LEADS");
}

TEST_F(ScreenBuilderTest, FlashTimerCallbackExecutes)
{
    ScreenBuilder builder;

    builder.build();

    builder.UpdateHR(120, true);

    ASSERT_NE(builder.GetFlashTimer(), nullptr);

    ScreenBuilder::InvokeFlashTimer(builder.GetFlashTimer());

    ScreenBuilder::InvokeFlashTimer(builder.GetFlashTimer());

    SUCCEED();
}

TEST_F(ScreenBuilderTest, UpdateAlarmBarMedium)
{
    ScreenBuilder builder;

    builder.build();

    builder.UpdateAlarmBar("RR HIGH", AlarmPriority::Medium);

    EXPECT_STREQ(
        lv_label_get_text(builder.GetAlarmLabel()),
        "RR HIGH");
}

TEST_F(ScreenBuilderTest, FlashTimerCallbackWithRRAlarm)
{
    ScreenBuilder builder;

    builder.build();

    builder.UpdateRR(25, true);

    ASSERT_NE(builder.GetFlashTimer(), nullptr);

    ScreenBuilder::InvokeFlashTimer(builder.GetFlashTimer());

    ScreenBuilder::InvokeFlashTimer(builder.GetFlashTimer());

    SUCCEED();
}

TEST_F(ScreenBuilderTest, FlashTimerCallbackWithSPO2Alarm)
{
    ScreenBuilder builder;

    builder.build();

    builder.UpdateSPO2(85, true);

    ASSERT_NE(builder.GetFlashTimer(), nullptr);

    ScreenBuilder::InvokeFlashTimer(builder.GetFlashTimer());

    ScreenBuilder::InvokeFlashTimer(builder.GetFlashTimer());

    SUCCEED();
}

TEST_F(ScreenBuilderTest, FlashTimerCallbackWithSYSAlarm)
{
    ScreenBuilder builder;

    builder.build();

    builder.UpdateSYS(150, true, true);

    ASSERT_NE(builder.GetFlashTimer(), nullptr);

    ScreenBuilder::InvokeFlashTimer(builder.GetFlashTimer());

    ScreenBuilder::InvokeFlashTimer(builder.GetFlashTimer());

    SUCCEED();
}

TEST_F(ScreenBuilderTest, FlashTimerCallbackWithDIASAlarm)
{
    ScreenBuilder builder;

    builder.build();

    builder.UpdateDIAS(95, true, true);

    ASSERT_NE(builder.GetFlashTimer(), nullptr);

    ScreenBuilder::InvokeFlashTimer(builder.GetFlashTimer());

    ScreenBuilder::InvokeFlashTimer(builder.GetFlashTimer());

    SUCCEED();
}

TEST_F(ScreenBuilderTest, AddECGSampleDoesNotCrash)
{
    ScreenBuilder builder;

    builder.build();

    builder.AddECGSample(123);

    SUCCEED();
}

TEST_F(ScreenBuilderTest, UpdateAlarmBarInvalidPriority)
{
    ScreenBuilder builder;

    builder.build();

    builder.UpdateAlarmBar(
        "Invalid",
        static_cast<AlarmPriority>(255));

    EXPECT_STREQ(
        lv_label_get_text(builder.GetAlarmLabel()),
        "Invalid");
}

TEST_F(ScreenBuilderTest, UpdateMonitorStatusInvalidValue)
{
    ScreenBuilder builder;

    builder.build();

    builder.UpdateMonitorStatus(
        static_cast<MonitorStatus>(255));

    SUCCEED();
}
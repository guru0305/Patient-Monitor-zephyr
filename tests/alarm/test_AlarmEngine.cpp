#include <gtest/gtest.h>

#include "alarm/AlarmEngine.hpp"
#include "model/PatientData.hpp"

TEST(AlarmEngineTest, NoAlarmsForNormalVitals)
{
    DataModel model;
    AlarmEngine alarm(model);

    PatientData data{};
    data.hr = 80;
    data.spo2 = 98;
    data.rr = 16;
    data.sys = 120;
    data.dias = 80;

    model.set_patient_data(data);

    alarm.CheckThresholds();

    AlarmState state = alarm.get_alarm_state();

    EXPECT_FALSE(state.hr_alarm);
    EXPECT_FALSE(state.spo2_alarm);
    EXPECT_FALSE(state.rr_alarm);
    EXPECT_FALSE(state.sys_alarm);
    EXPECT_FALSE(state.dias_alarm);
}

TEST(AlarmEngineTest, HeartRateHighAlarm)
{
    DataModel model;
    AlarmEngine alarm(model);

    PatientData data{};
    data.hr = 110;

    model.set_patient_data(data);

    alarm.CheckThresholds();

    EXPECT_TRUE(alarm.get_alarm_state().hr_alarm);
}

TEST(AlarmEngineTest, HeartRateLowAlarm)
{
    DataModel model;
    AlarmEngine alarm(model);

    PatientData data{};
    data.hr = 50;

    model.set_patient_data(data);

    alarm.CheckThresholds();

    EXPECT_TRUE(alarm.get_alarm_state().hr_alarm);
}

TEST(AlarmEngineTest, Spo2LowAlarm)
{
    DataModel model;
    AlarmEngine alarm(model);

    PatientData data{};
    data.spo2 = 85;

    model.set_patient_data(data);

    alarm.CheckThresholds();

    EXPECT_TRUE(alarm.get_alarm_state().spo2_alarm);
}

TEST(AlarmEngineTest, RespiratoryRateHighAlarm)
{
    DataModel model;
    AlarmEngine alarm(model);

    PatientData data{};
    data.rr = 25;

    model.set_patient_data(data);

    alarm.CheckThresholds();

    EXPECT_TRUE(alarm.get_alarm_state().rr_alarm);
}

TEST(AlarmEngineTest, RespiratoryRateLowAlarm)
{
    DataModel model;
    AlarmEngine alarm(model);

    PatientData data{};
    data.rr = 8;

    model.set_patient_data(data);

    alarm.CheckThresholds();

    EXPECT_TRUE(alarm.get_alarm_state().rr_alarm);
}

TEST(AlarmEngineTest, SystolicPressureAlarm)
{
    DataModel model;
    AlarmEngine alarm(model);

    PatientData data{};
    data.sys = 150;

    model.set_patient_data(data);

    alarm.CheckThresholds();

    EXPECT_TRUE(alarm.get_alarm_state().sys_alarm);
}

TEST(AlarmEngineTest, DiastolicPressureAlarm)
{
    DataModel model;
    AlarmEngine alarm(model);

    PatientData data{};
    data.dias = 95;

    model.set_patient_data(data);

    alarm.CheckThresholds();

    EXPECT_TRUE(alarm.get_alarm_state().dias_alarm);
}

TEST(AlarmEngineTest, SystolicPressureLowAlarm)
{
    DataModel model;
    AlarmEngine alarm(model);

    PatientData data{};
    data.sys = 70;

    model.set_patient_data(data);

    alarm.CheckThresholds();

    EXPECT_TRUE(alarm.get_alarm_state().sys_alarm);
}

TEST(AlarmEngineTest, DiastolicPressureLowAlarm)
{
    DataModel model;
    AlarmEngine alarm(model);

    PatientData data{};
    data.dias = 50;

    model.set_patient_data(data);

    alarm.CheckThresholds();

    EXPECT_TRUE(alarm.get_alarm_state().dias_alarm);
}
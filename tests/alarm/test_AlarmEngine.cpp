#include <gtest/gtest.h>

#include "alarm/AlarmEngine.hpp"
#include "model/PatientData.hpp"

static PatientData NormalVitals()
{
    PatientData data{};

    data.hr   = 80;
    data.spo2 = 98;
    data.rr   = 16;
    data.sys  = 120;
    data.dias = 80;
    data.mean = 93;

    return data;
}

TEST(AlarmEngineTest, NoAlarmsForNormalVitals)
{
    DataModel model;
    AlarmEngine alarm(model);

    PatientData data = NormalVitals();

    model.set_patient_data(data);

    alarm.CheckThresholds();

    AlarmState state = alarm.get_alarm_state();

    EXPECT_FALSE(state.hr_alarm);
    EXPECT_FALSE(state.spo2_alarm);
    EXPECT_FALSE(state.rr_alarm);
    EXPECT_FALSE(state.sys_alarm);
    EXPECT_FALSE(state.dias_alarm);

    EXPECT_EQ(state.type, AlarmType::None);
    EXPECT_EQ(state.priority, AlarmPriority::None);
}

TEST(AlarmEngineTest, HeartRateHighAlarm)
{
    DataModel model;
    AlarmEngine alarm(model);

    PatientData data = NormalVitals();
    data.hr = 121;

    model.set_patient_data(data);

    alarm.CheckThresholds();

    AlarmState state = alarm.get_alarm_state();

    EXPECT_TRUE(state.hr_alarm);
    EXPECT_EQ(state.type, AlarmType::HR_HIGH);
    EXPECT_EQ(state.priority, AlarmPriority::Medium);
}

TEST(AlarmEngineTest, HeartRateLowAlarm)
{
    DataModel model;
    AlarmEngine alarm(model);

    PatientData data = NormalVitals();
    data.hr = 50;

    model.set_patient_data(data);

    alarm.CheckThresholds();

    AlarmState state = alarm.get_alarm_state();

    EXPECT_TRUE(state.hr_alarm);
    EXPECT_EQ(state.type, AlarmType::HR_LOW);
    EXPECT_EQ(state.priority, AlarmPriority::Medium);
}

TEST(AlarmEngineTest, Spo2LowAlarm)
{
    DataModel model;
    AlarmEngine alarm(model);

    PatientData data = NormalVitals();
    data.spo2 = 85;

    model.set_patient_data(data);

    alarm.CheckThresholds();

    AlarmState state = alarm.get_alarm_state();

    EXPECT_TRUE(state.spo2_alarm);
    EXPECT_EQ(state.type, AlarmType::SPO2_LOW);
    EXPECT_EQ(state.priority, AlarmPriority::High);
}

TEST(AlarmEngineTest, RespiratoryRateHighAlarm)
{
    DataModel model;
    AlarmEngine alarm(model);

    PatientData data = NormalVitals();
    data.rr = 25;

    model.set_patient_data(data);

    alarm.CheckThresholds();

    AlarmState state = alarm.get_alarm_state();

    EXPECT_TRUE(state.rr_alarm);
    EXPECT_EQ(state.type, AlarmType::RR_HIGH);
    EXPECT_EQ(state.priority, AlarmPriority::Medium);
}

TEST(AlarmEngineTest, RespiratoryRateLowAlarm)
{
    DataModel model;
    AlarmEngine alarm(model);

    PatientData data = NormalVitals();
    data.rr = 8;

    model.set_patient_data(data);

    alarm.CheckThresholds();

    AlarmState state = alarm.get_alarm_state();

    EXPECT_TRUE(state.rr_alarm);
    EXPECT_EQ(state.type, AlarmType::RR_LOW);
    EXPECT_EQ(state.priority, AlarmPriority::Medium);
}

TEST(AlarmEngineTest, SystolicPressureHighAlarm)
{
    DataModel model;
    AlarmEngine alarm(model);

    PatientData data = NormalVitals();
    data.sys = 150;

    model.set_patient_data(data);

    alarm.CheckThresholds();

    AlarmState state = alarm.get_alarm_state();

    EXPECT_TRUE(state.sys_alarm);
    EXPECT_EQ(state.type, AlarmType::SYS_HIGH);
    EXPECT_EQ(state.priority, AlarmPriority::High);
}

TEST(AlarmEngineTest, SystolicPressureLowAlarm)
{
    DataModel model;
    AlarmEngine alarm(model);

    PatientData data = NormalVitals();
    data.sys = 70;

    model.set_patient_data(data);

    alarm.CheckThresholds();

    AlarmState state = alarm.get_alarm_state();

    EXPECT_TRUE(state.sys_alarm);
    EXPECT_EQ(state.type, AlarmType::SYS_LOW);
    EXPECT_EQ(state.priority, AlarmPriority::High);
}

TEST(AlarmEngineTest, DiastolicPressureHighAlarm)
{
    DataModel model;
    AlarmEngine alarm(model);

    PatientData data = NormalVitals();
    data.dias = 95;

    model.set_patient_data(data);

    alarm.CheckThresholds();

    AlarmState state = alarm.get_alarm_state();

    EXPECT_TRUE(state.dias_alarm);
    EXPECT_EQ(state.type, AlarmType::DIAS_HIGH);
    EXPECT_EQ(state.priority, AlarmPriority::High);
}

TEST(AlarmEngineTest, DiastolicPressureLowAlarm)
{
    DataModel model;
    AlarmEngine alarm(model);

    PatientData data = NormalVitals();
    data.dias = 50;

    model.set_patient_data(data);

    alarm.CheckThresholds();

    AlarmState state = alarm.get_alarm_state();

    EXPECT_TRUE(state.dias_alarm);
    EXPECT_EQ(state.type, AlarmType::DIAS_LOW);
    EXPECT_EQ(state.priority, AlarmPriority::High);
}
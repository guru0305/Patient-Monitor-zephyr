#pragma once

enum class AlarmPriority
{
    None,
    Medium,
    High
};

enum class AlarmType
{
    None,

    HR_HIGH,
    HR_LOW,

    RR_HIGH,
    RR_LOW,

    SPO2_LOW,

    SYS_HIGH,
    SYS_LOW,

    DIAS_HIGH,
    DIAS_LOW
};

struct AlarmState
{
    AlarmType type = AlarmType::None;
    AlarmPriority priority = AlarmPriority::None;
    const char* message = "";

    bool hr_alarm;
    bool rr_alarm;
    bool spo2_alarm;
    bool sys_alarm;
    bool dias_alarm;
};
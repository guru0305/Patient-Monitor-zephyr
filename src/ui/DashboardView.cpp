#include "ui/DashboardView.hpp"
#include<cstdio>

DashboardView::DashboardView(
    ScreenBuilder& screen_builder,
    DataModel& model)
    :
    screen_builder_(screen_builder),
    model_(model)
{
}

void DashboardView::Update(
    const PatientData& data,
    const AlarmState& alarm_state)
{
    bool bp_alarm = alarm_state.sys_alarm || alarm_state.dias_alarm;

    screen_builder_.UpdateHR(data.hr,alarm_state.hr_alarm);
    screen_builder_.UpdateSPO2(data.spo2,alarm_state.spo2_alarm);
    screen_builder_.UpdateRR(data.rr,alarm_state.rr_alarm);
    screen_builder_.UpdateSYS(data.sys,alarm_state.sys_alarm,bp_alarm);
    screen_builder_.UpdateDIAS(data.dias,alarm_state.dias_alarm,bp_alarm);
    screen_builder_.UpdateMEAN(data.mean);
    uint16_t samples[32];

    uint32_t bytes = model_.PopECGSamples(
        reinterpret_cast<uint8_t*>(samples),
        sizeof(samples));

    uint32_t count = bytes / sizeof(uint16_t);

    for(uint32_t i = 0; i < count; i++)
    {
        screen_builder_.AddECGSample(samples[i]);
    }

    char alarm_text[64];

    if(alarm_state.hr_alarm)
    {
        snprintf(alarm_text,
                sizeof(alarm_text),
                LV_SYMBOL_WARNING " HR ALARM (HR : %u BPM)",
                data.hr);

        screen_builder_.UpdateAlarmBar(alarm_text, true);

    }
    else if(alarm_state.spo2_alarm)
    {
        snprintf(alarm_text,
                sizeof(alarm_text),
                LV_SYMBOL_WARNING " SPO2 ALARM (SPO2 : %u%%)",
                data.spo2);

        screen_builder_.UpdateAlarmBar(alarm_text, true);
    }
    else if(alarm_state.rr_alarm)
    {
        snprintf(alarm_text,
                sizeof(alarm_text),
                LV_SYMBOL_WARNING " RR ALARM (RR : %u RPM)",
                data.rr);

        screen_builder_.UpdateAlarmBar(alarm_text, true);
    }
    else if(alarm_state.sys_alarm)
    {
        snprintf(alarm_text,
                sizeof(alarm_text),
                LV_SYMBOL_WARNING " SYS ALARM (SYS : %u mmHg)",
                data.sys);

        screen_builder_.UpdateAlarmBar(alarm_text, true);
    }
    else if(alarm_state.dias_alarm)
    {
        snprintf(alarm_text,
                sizeof(alarm_text),
                LV_SYMBOL_WARNING " DIAS ALARM (DIAS : %u mmHg)",
                data.dias);

        screen_builder_.UpdateAlarmBar(alarm_text, true);
    }
    else
    {
        screen_builder_.UpdateAlarmBar(
            LV_SYMBOL_BELL " NO ACTIVE ALARMS",false
        );
    }
}
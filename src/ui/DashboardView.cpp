#include "ui/DashboardView.hpp"

DashboardView::DashboardView(
    ScreenBuilder& screen_builder)
    : screen_builder_(screen_builder)
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
    screen_builder_.AddECGSample(data.ecg);

    if(alarm_state.hr_alarm)
    {
        screen_builder_.UpdateAlarmBar(
            LV_SYMBOL_WARNING " HR ALARM",true
        );

    }
    else if(alarm_state.spo2_alarm)
    {
        screen_builder_.UpdateAlarmBar(
            LV_SYMBOL_WARNING " SPO2 ALARM",true
        );
    }
    else if(alarm_state.rr_alarm)
    {
        screen_builder_.UpdateAlarmBar(
            LV_SYMBOL_WARNING " RR ALARM",true
        );
    }
    else if(alarm_state.sys_alarm || alarm_state.dias_alarm)
    {
        screen_builder_.UpdateAlarmBar(
            LV_SYMBOL_WARNING " BP ALARM",true
        );
    }
    else
    {
        screen_builder_.UpdateAlarmBar(
            LV_SYMBOL_BELL " NO ACTIVE ALARMS",false
        );
    }
}
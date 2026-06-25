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
    screen_builder_.UpdateHR(data.hr);
    screen_builder_.UpdateSPO2(data.spo2);
    screen_builder_.UpdateRR(data.rr);
    screen_builder_.UpdateSYS(data.sys);
    screen_builder_.UpdateDIAS(data.dias);
    screen_builder_.UpdateMEAN(data.mean);

    if(alarm_state.hr_alarm)
    {
        screen_builder_.UpdateAlarmBar(
            LV_SYMBOL_WARNING " HR LOW",true
        );

    }
    else if(alarm_state.spo2_alarm)
    {
        screen_builder_.UpdateAlarmBar(
            LV_SYMBOL_WARNING " SPO2 LOW",true
        );
    }
    else if(alarm_state.rr_alarm)
    {
        screen_builder_.UpdateAlarmBar(
            LV_SYMBOL_WARNING " RR LOW",true
        );
    }
    else if(alarm_state.bp_alarm)
    {
        screen_builder_.UpdateAlarmBar(
            LV_SYMBOL_WARNING " BP LOW",true
        );
    }
    // else if(alarm_state.ecg_alarm)
    // {
    //     screen_builder_.UpdateAlarmBar(
    //         LV_SYMBOL_WARNING " ECG HIGH"
    //     );
    // }
    else
    {
        screen_builder_.UpdateAlarmBar(
            LV_SYMBOL_BELL " NO ACTIVE ALARMS",false
        );
    }
}
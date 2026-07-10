#ifndef SCREEN_BUILDER_H
#define SCREEN_BUILDER_H
#include "lvgl.h"

class ScreenBuilder
{
    public:
        void build();
        void UpdateHR(uint8_t hr,bool hr_alarm);
        void UpdateSPO2(uint8_t spo2,bool spo2_alarm);
        void UpdateRR(uint8_t rr,bool rr_alarm);
        void UpdateSYS(uint8_t sys,bool sys_alarm,bool bp_alarm);
        void UpdateDIAS(uint8_t dias,bool dias_alarm, bool bp_alarm);
        void UpdateMEAN(uint8_t mean);
        void UpdateAlarmBar(const char* text, bool state);
        void AddECGSample(uint16_t sample);
        void UpdateFlashState(lv_obj_t* obj, bool alarm);

    private:
        void create_header();
        void create_alarmtab();
        void create_hr_panel();
        void create_spo2_panel();
        void create_NIBP_panel();
        void create_rr_panel();
        void create_ecg_panel();
        void create_hr_animation(lv_obj_t* heart_icon);
        void create_rr_animation(lv_obj_t* rr_icon);
        void StartFlash(lv_obj_t* obj);
        void StopFlash(lv_obj_t* obj);

        // main screen components
        lv_obj_t* main_screen;
        lv_obj_t* header;
        lv_obj_t* header_label;

        // alarm components
        lv_obj_t* alarm_outer_panel;
        lv_obj_t* alarm_panel;
        lv_obj_t* alarm_label;

        // hr components
        lv_obj_t* hr_panel;
        lv_obj_t* hr_label;
        lv_obj_t* hr_value_label;
        lv_obj_t* hr_unit_label;
        lv_obj_t* heart_icon;

        // spo2 components
        lv_obj_t* spo2_panel;
        lv_obj_t* spo2_label;
        lv_obj_t* spo2_value_label;
        lv_obj_t* spo2_unit_label;
        lv_obj_t* spo2_icon;

        // rr components
        lv_obj_t* rr_panel;
        lv_obj_t* rr_label;
        lv_obj_t* rr_value_label;
        lv_obj_t* rr_unit_label;
        lv_obj_t* rr_icon;

        // NIBP components
        lv_obj_t* NIBP_panel;
        lv_obj_t* NIBP_label;
        lv_obj_t* systolic_value_label;
        lv_obj_t* diastolic_value_label;
        lv_obj_t* mean_value_label;
        lv_obj_t* mean_unit_label;
        lv_obj_t* separator;
        lv_obj_t* unit_label;
        
        // ecg
        lv_obj_t* ecg_panel;
        lv_obj_t* ecg_label;
        lv_obj_t* ecg_chart;
        lv_chart_series_t* ecg_series;
        

};

#endif
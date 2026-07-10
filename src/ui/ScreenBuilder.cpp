#include "ui/ScreenBuilder.hpp"
#include "lvgl.h"
#include<cmath>
#include<cstdio>

extern const lv_image_dsc_t heart;
extern const lv_image_dsc_t spo2;
extern const lv_image_dsc_t rr;

static void heart_anim_cb(void* var, int32_t value)
{
    lv_image_set_scale((lv_obj_t*)var, value);
}

static void rr_anim_cb(void* var, int32_t value)
{
    lv_image_set_scale((lv_obj_t*)var, value);
}

static void flash_cb(void * var, int32_t value)
{
    lv_obj_set_style_bg_opa((lv_obj_t *)var,value ? LV_OPA_COVER : LV_OPA_0, LV_PART_MAIN);    
}

void ScreenBuilder::UpdateHR(uint8_t hr,bool hr_state)
{
    char buffer[8];
    snprintf(buffer,sizeof(buffer),"%u",hr);
    lv_label_set_text(hr_value_label,buffer);
    lv_obj_set_style_bg_color(hr_value_label,lv_color_hex(0Xff0000), LV_PART_MAIN);
    lv_obj_set_style_text_color(hr_value_label,hr_state ?lv_color_hex(0Xffffff) : lv_color_hex(0x00FF00), LV_PART_MAIN);
    lv_obj_set_style_border_color(hr_panel, hr_state ? lv_color_hex(0xff0000) : lv_color_hex(0X008b8b), LV_PART_MAIN);
    UpdateFlashState(hr_value_label, hr_state);
}

void ScreenBuilder::UpdateSPO2(uint8_t spo2,bool spo2_state)
{
    char buffer[8];
    snprintf(buffer,sizeof(buffer),"%u",spo2);
    lv_label_set_text(spo2_value_label,buffer);
    lv_obj_set_style_bg_color(spo2_value_label,lv_color_hex(0Xff0000), LV_PART_MAIN);
    lv_obj_set_style_text_color(spo2_value_label,spo2_state ?lv_color_hex(0Xffffff) : lv_color_hex(0x00ffff), LV_PART_MAIN);
    lv_obj_set_style_border_side(spo2_panel,spo2_state ? LV_BORDER_SIDE_FULL : (lv_border_side_t)(LV_BORDER_SIDE_BOTTOM | LV_BORDER_SIDE_LEFT | LV_BORDER_SIDE_RIGHT), LV_PART_MAIN);
    lv_obj_set_style_border_color(spo2_panel, spo2_state ? lv_color_hex(0xff0000) : lv_color_hex(0X008b8b), LV_PART_MAIN);
    UpdateFlashState(spo2_value_label, spo2_state);
}

void ScreenBuilder::UpdateRR(uint8_t rr,bool rr_state)
{
    char buffer[8];
    snprintf(buffer,sizeof(buffer),"%u",rr);
    lv_label_set_text(rr_value_label,buffer);
    lv_obj_set_style_bg_color(rr_value_label,lv_color_hex(0Xff0000), LV_PART_MAIN);
    lv_obj_set_style_text_color(rr_value_label,rr_state ?lv_color_hex(0Xffffff) : lv_color_hex(0xffff00), LV_PART_MAIN);
    lv_obj_set_style_border_side(rr_panel,rr_state ? LV_BORDER_SIDE_FULL : (lv_border_side_t)(LV_BORDER_SIDE_BOTTOM | LV_BORDER_SIDE_LEFT | LV_BORDER_SIDE_RIGHT), LV_PART_MAIN);
    lv_obj_set_style_border_color(rr_panel, rr_state ? lv_color_hex(0xff0000) : lv_color_hex(0X008b8b), LV_PART_MAIN);
    UpdateFlashState(rr_value_label, rr_state);
}

void ScreenBuilder::UpdateSYS(uint8_t sys,bool sys_state,bool bp_alarm)
{
    char buffer[8];
    snprintf(buffer,sizeof(buffer),"%u",sys);
    lv_label_set_text(systolic_value_label,buffer);
    lv_obj_set_style_bg_color(systolic_value_label,lv_color_hex(0Xff0000), LV_PART_MAIN);
    lv_obj_set_style_text_color(systolic_value_label,sys_state ?lv_color_hex(0Xffffff) : lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_set_style_border_side(NIBP_panel,bp_alarm ? LV_BORDER_SIDE_FULL : (lv_border_side_t)(LV_BORDER_SIDE_BOTTOM | LV_BORDER_SIDE_LEFT | LV_BORDER_SIDE_RIGHT), LV_PART_MAIN);
    lv_obj_set_style_border_color(NIBP_panel, bp_alarm ? lv_color_hex(0xff0000) : lv_color_hex(0X008b8b), LV_PART_MAIN);
    UpdateFlashState(systolic_value_label, sys_state);

}

void ScreenBuilder::UpdateDIAS(uint8_t dias,bool dias_state,bool bp_alarm)
{
    char buffer[8];
    snprintf(buffer,sizeof(buffer),"%u",dias);
    lv_label_set_text(diastolic_value_label,buffer);
    lv_obj_set_style_bg_color(diastolic_value_label,lv_color_hex(0Xff0000), LV_PART_MAIN);
    lv_obj_set_style_text_color(diastolic_value_label,dias_state ?lv_color_hex(0Xffffff) : lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_set_style_border_side(NIBP_panel,bp_alarm ? LV_BORDER_SIDE_FULL : (lv_border_side_t)(LV_BORDER_SIDE_BOTTOM | LV_BORDER_SIDE_LEFT | LV_BORDER_SIDE_RIGHT), LV_PART_MAIN);
    lv_obj_set_style_border_color(NIBP_panel, bp_alarm ? lv_color_hex(0xff0000) : lv_color_hex(0X008b8b), LV_PART_MAIN);
    UpdateFlashState(diastolic_value_label, dias_state);
}

void ScreenBuilder::UpdateMEAN(uint8_t mean)
{
    char buffer[8];
    snprintf(buffer,sizeof(buffer),"%u",mean);
    lv_label_set_text(mean_value_label,buffer);
}

void ScreenBuilder::AddECGSample(uint16_t sample)
{
    //std::cout << sample << std::endl;
    lv_chart_set_next_value(ecg_chart, ecg_series, sample);
}

void ScreenBuilder::UpdateAlarmBar(const char* text, bool state)
{
    lv_label_set_text(alarm_label,text);
    lv_obj_set_style_bg_color(alarm_panel,state ? lv_color_hex(0x0d0000) : lv_color_hex(0x002200), LV_PART_MAIN);
    lv_obj_set_style_border_color(alarm_panel,state ? lv_color_hex(0xff0000) : lv_color_hex(0x00ff00), LV_PART_MAIN);
    lv_obj_set_style_text_color(alarm_label,state ? lv_color_hex(0xff0000) : lv_color_hex(0x00ff00), LV_PART_MAIN);
}

void ScreenBuilder::UpdateFlashState(lv_obj_t* obj, bool alarm)
{
    bool flashing = (lv_anim_get(obj, flash_cb) != nullptr);

    if(alarm && !flashing)
    {
        StartFlash(obj);
    }
    else if(!alarm && flashing)
    {
        StopFlash(obj);
    }
}

void ScreenBuilder::build()
{
    main_screen = lv_scr_act();
    lv_obj_set_style_bg_color(main_screen, lv_color_hex(0X000000), LV_PART_MAIN);
    lv_obj_remove_flag(main_screen, LV_OBJ_FLAG_SCROLLABLE);

    create_header();
    create_alarmtab();
    create_hr_panel();
    create_spo2_panel();
    create_NIBP_panel();
    create_rr_panel();
    create_ecg_panel();
}

void ScreenBuilder::create_header()
{
    // header panel
    header = lv_obj_create(main_screen);
    lv_obj_set_size(header, 370, 20);
    lv_obj_align(header, LV_ALIGN_TOP_MID, -55, 0);
    lv_obj_set_style_bg_color(header, lv_color_hex(0X000000), LV_PART_MAIN);
    lv_obj_set_style_radius(header, 1, LV_PART_MAIN);
    lv_obj_clear_flag(header, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_border_color(header, lv_color_hex(0X008b8b), LV_PART_MAIN);
    lv_obj_set_style_border_width(header, 2, LV_PART_MAIN);
    lv_obj_set_style_border_side(header, (lv_border_side_t)(LV_BORDER_SIDE_TOP | LV_BORDER_SIDE_LEFT | LV_BORDER_SIDE_BOTTOM), LV_PART_MAIN);

    // header label
    header_label = lv_label_create(header);
    lv_label_set_text(header_label, "BED 01");
    lv_obj_align(header_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_text_color(header_label, lv_color_hex(0xFFffff), LV_PART_MAIN);
    lv_obj_set_style_text_font(header_label, &lv_font_montserrat_16, LV_PART_MAIN);
    lv_obj_clear_flag(header_label, LV_OBJ_FLAG_SCROLLABLE);

}

void ScreenBuilder::create_alarmtab()
{
    // alarm outer panel
    alarm_outer_panel = lv_obj_create(main_screen);
    lv_obj_set_size(alarm_outer_panel, 370, 52);
    lv_obj_align(alarm_outer_panel, LV_ALIGN_TOP_LEFT, 0, 20);
    lv_obj_set_style_bg_color(alarm_outer_panel, lv_color_hex(0x000000), LV_PART_MAIN);
    lv_obj_set_style_border_width(alarm_outer_panel, 2, LV_PART_MAIN);
    lv_obj_set_style_border_color(alarm_outer_panel, lv_color_hex(0X008b8b), LV_PART_MAIN);
    lv_obj_set_style_radius(alarm_outer_panel, 0, LV_PART_MAIN);
    lv_obj_set_style_border_side(alarm_outer_panel, LV_BORDER_SIDE_LEFT, LV_PART_MAIN);
    lv_obj_clear_flag( alarm_outer_panel, LV_OBJ_FLAG_SCROLLABLE);

    // alarm panel
    alarm_panel = lv_obj_create(alarm_outer_panel);
    lv_obj_set_size(alarm_panel, 364, 46);
    lv_obj_center(alarm_panel);
    lv_obj_set_style_bg_color(alarm_panel, lv_color_hex(0x002200), LV_PART_MAIN);
    lv_obj_set_style_border_color(alarm_panel, lv_color_hex(0x00FF00), LV_PART_MAIN);
    lv_obj_set_style_border_width(alarm_panel, 2, LV_PART_MAIN);
    lv_obj_clear_flag( alarm_panel, LV_OBJ_FLAG_SCROLLABLE);

    // alarm text
    alarm_label = lv_label_create(alarm_panel);
    lv_label_set_text(alarm_label, "NO ACTIVE ALARMS");
    lv_obj_set_style_text_font(alarm_label, &lv_font_montserrat_18, LV_PART_MAIN);
    lv_obj_set_style_text_color(alarm_label, lv_color_hex(0x00FF00), LV_PART_MAIN);
    lv_obj_align(alarm_label, LV_ALIGN_CENTER, 0, 0);

}

void ScreenBuilder::StartFlash(lv_obj_t* obj)
{
    lv_anim_t anim;
    lv_anim_init(&anim);

    lv_anim_set_var(&anim, obj);
    lv_anim_set_exec_cb(&anim, flash_cb);

    lv_anim_set_values(&anim, 1, 0);
    lv_anim_set_path_cb(&anim, lv_anim_path_step);
    lv_anim_set_duration(&anim, 150);
    lv_anim_set_playback_duration(&anim, 150);
    lv_anim_set_repeat_count(&anim, LV_ANIM_REPEAT_INFINITE);

    lv_anim_start(&anim);
}

void ScreenBuilder::StopFlash(lv_obj_t* obj)
{
    lv_anim_delete(obj, flash_cb);

    lv_obj_set_style_bg_opa(
        obj,
        LV_OPA_0,
        LV_PART_MAIN);
}

void ScreenBuilder::create_hr_panel()
{
    // hr panel
    hr_panel = lv_obj_create(main_screen);
    lv_obj_set_size(hr_panel, 110, 60);
    lv_obj_align(hr_panel, LV_ALIGN_TOP_RIGHT, 0, 0);
    lv_obj_set_style_bg_color(hr_panel, lv_color_hex(0X000000), LV_PART_MAIN);
    lv_obj_set_style_radius(hr_panel, 1, LV_PART_MAIN);
    lv_obj_clear_flag(hr_panel, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_border_color(hr_panel, lv_color_hex(0X008b8b), LV_PART_MAIN);
    lv_obj_set_style_border_width(hr_panel, 2, LV_PART_MAIN);

    // hr label
    hr_label = lv_label_create(hr_panel);
    lv_label_set_text(hr_label, "HR");
    lv_obj_align(hr_label, LV_ALIGN_TOP_LEFT, -10, -10);
    lv_obj_set_style_text_color(hr_label, lv_color_hex(0x008b8b), LV_PART_MAIN);
    lv_obj_set_style_text_font(hr_label, &lv_font_montserrat_10, LV_PART_MAIN);
    lv_obj_clear_flag(hr_label, LV_OBJ_FLAG_SCROLLABLE);

    // hr value label
    hr_value_label = lv_label_create(hr_panel);
    lv_label_set_text(hr_value_label, "--");
    lv_obj_align(hr_value_label, LV_ALIGN_CENTER, -10, 5);
    lv_obj_set_style_text_color(hr_value_label, lv_color_hex(0x00FF00), LV_PART_MAIN);
    lv_obj_set_style_text_font(hr_value_label, &lv_font_montserrat_28, LV_PART_MAIN);
    lv_obj_clear_flag(hr_value_label, LV_OBJ_FLAG_SCROLLABLE);

    // hr unit label
    hr_unit_label = lv_label_create(hr_panel);
    lv_label_set_text(hr_unit_label, "bpm");        
    lv_obj_align(hr_unit_label, LV_ALIGN_BOTTOM_RIGHT, 10, 10);
    lv_obj_set_style_text_color(hr_unit_label, lv_color_hex(0x008b8b), LV_PART_MAIN);
    lv_obj_set_style_text_font(hr_unit_label, &lv_font_montserrat_12, LV_PART_MAIN);
    lv_obj_clear_flag(hr_unit_label, LV_OBJ_FLAG_SCROLLABLE);

    // heart icon
    heart_icon = lv_image_create(hr_panel);
    lv_image_set_src(heart_icon, &heart);
    lv_image_set_scale(heart_icon, 130);
    lv_obj_set_style_img_recolor(heart_icon, lv_color_hex(0x00ff00), LV_PART_MAIN);
    lv_obj_set_style_img_recolor_opa(heart_icon, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_align(heart_icon, LV_ALIGN_TOP_RIGHT, 10, -10);
    create_hr_animation(heart_icon);
    
}

void ScreenBuilder::create_hr_animation(lv_obj_t* heart_icon)
{
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, heart_icon);
    lv_anim_set_exec_cb(&a, heart_anim_cb);
    lv_anim_set_values(&a, 125, 135);
    lv_anim_set_time(&a, 300);
    lv_anim_set_playback_time(&a, 300);
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
    //lv_anim_set_cb(&a, heart_anim_cb);
    lv_anim_start(&a);
}

void ScreenBuilder::create_spo2_panel()
{
    // spo2 panel
    spo2_panel = lv_obj_create(main_screen);
    lv_obj_set_size(spo2_panel, 110, 60);
    lv_obj_align(spo2_panel, LV_ALIGN_TOP_RIGHT, 0, 60);
    lv_obj_set_style_bg_color(spo2_panel, lv_color_hex(0X000000), LV_PART_MAIN);
    lv_obj_set_style_radius(spo2_panel, 1, LV_PART_MAIN);
    lv_obj_clear_flag(spo2_panel, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_border_color(spo2_panel, lv_color_hex(0X008b8b), LV_PART_MAIN);
    lv_obj_set_style_border_width(spo2_panel, 2, LV_PART_MAIN);
    lv_obj_set_style_border_side(spo2_panel, (lv_border_side_t)(LV_BORDER_SIDE_BOTTOM | LV_BORDER_SIDE_LEFT | LV_BORDER_SIDE_RIGHT), LV_PART_MAIN);

    // spo2 label
    spo2_label = lv_label_create(spo2_panel);
    lv_label_set_text(spo2_label, "SpO2");
    lv_obj_align(spo2_label, LV_ALIGN_TOP_LEFT, -10, -10);
    lv_obj_set_style_text_color(spo2_label, lv_color_hex(0x008b8b), LV_PART_MAIN);
    lv_obj_set_style_text_font(spo2_label, &lv_font_montserrat_10, LV_PART_MAIN);
    lv_obj_clear_flag(spo2_label, LV_OBJ_FLAG_SCROLLABLE);

    // spo2 value label
    spo2_value_label = lv_label_create(spo2_panel);
    lv_label_set_text(spo2_value_label, "--");
    lv_obj_align(spo2_value_label, LV_ALIGN_CENTER, -10, 5);
    lv_obj_set_style_text_color(spo2_value_label, lv_color_hex(0x00ffff), LV_PART_MAIN);
    lv_obj_set_style_text_font(spo2_value_label, &lv_font_montserrat_28, LV_PART_MAIN);
    lv_obj_clear_flag(spo2_value_label, LV_OBJ_FLAG_SCROLLABLE);

    // spo2 unit label
    spo2_unit_label = lv_label_create(spo2_panel);        
    lv_label_set_text(spo2_unit_label, "%");
    lv_obj_align(spo2_unit_label, LV_ALIGN_BOTTOM_RIGHT, 10, 10);
    lv_obj_set_style_text_color(spo2_unit_label, lv_color_hex(0x008b8b), LV_PART_MAIN);
    lv_obj_set_style_text_font(spo2_unit_label, &lv_font_montserrat_12, LV_PART_MAIN);
    lv_obj_clear_flag(spo2_unit_label, LV_OBJ_FLAG_SCROLLABLE);

    // spo2 icon
    spo2_icon = lv_image_create(spo2_panel);
    lv_image_set_src(spo2_icon, &spo2);
    lv_image_set_scale(spo2_icon, 160);
    lv_obj_align(spo2_icon, LV_ALIGN_TOP_RIGHT, 10, -10);
    lv_obj_set_style_img_recolor(spo2_icon, lv_color_hex(0x00ffff), LV_PART_MAIN);
    lv_obj_set_style_img_recolor_opa(spo2_icon, LV_OPA_COVER, LV_PART_MAIN);
}

void ScreenBuilder::create_rr_panel()
{
    // rr panel
    rr_panel = lv_obj_create(main_screen);
    lv_obj_set_size(rr_panel, 110, 60);
    lv_obj_align(rr_panel, LV_ALIGN_TOP_RIGHT, 0, 120);
    lv_obj_set_style_bg_color(rr_panel, lv_color_hex(0X000000), LV_PART_MAIN);
    lv_obj_set_style_radius(rr_panel, 1, LV_PART_MAIN);
    lv_obj_clear_flag(rr_panel, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_border_color(rr_panel, lv_color_hex(0X008b8b), LV_PART_MAIN);
    lv_obj_set_style_border_width(rr_panel, 2, LV_PART_MAIN);
    lv_obj_set_style_border_side(rr_panel, (lv_border_side_t)(LV_BORDER_SIDE_BOTTOM | LV_BORDER_SIDE_LEFT | LV_BORDER_SIDE_RIGHT), LV_PART_MAIN);

    // rr label
    rr_label = lv_label_create(rr_panel);
    lv_label_set_text(rr_label, "RR");
    lv_obj_align(rr_label, LV_ALIGN_TOP_LEFT, -10, -10);
    lv_obj_set_style_text_color(rr_label, lv_color_hex(0x008b8b), LV_PART_MAIN);
    lv_obj_set_style_text_font(rr_label, &lv_font_montserrat_10, LV_PART_MAIN);
    lv_obj_clear_flag(rr_label, LV_OBJ_FLAG_SCROLLABLE);

    // rr value label
    rr_value_label = lv_label_create(rr_panel);
    lv_label_set_text(rr_value_label, "--");
    lv_obj_align(rr_value_label, LV_ALIGN_CENTER, -10, 0);
    lv_obj_set_style_text_color(rr_value_label, lv_color_hex(0xFFFF00), LV_PART_MAIN);
    lv_obj_set_style_text_font(rr_value_label, &lv_font_montserrat_28, LV_PART_MAIN);
    lv_obj_clear_flag(rr_value_label, LV_OBJ_FLAG_SCROLLABLE);

    // rr unit label
    rr_unit_label = lv_label_create(rr_panel);
    lv_label_set_text(rr_unit_label, "rpm");        
    lv_obj_align(rr_unit_label, LV_ALIGN_BOTTOM_RIGHT, 10, 10);
    lv_obj_set_style_text_color(rr_unit_label, lv_color_hex(0x008b8b), LV_PART_MAIN);
    lv_obj_set_style_text_font(rr_unit_label, &lv_font_montserrat_12, LV_PART_MAIN);
    lv_obj_clear_flag(rr_unit_label, LV_OBJ_FLAG_SCROLLABLE);

    // rr icon
    rr_icon = lv_image_create(rr_panel);
    lv_image_set_src(rr_icon, &rr);
    lv_image_set_scale(rr_icon, 160);
    lv_obj_align(rr_icon, LV_ALIGN_TOP_RIGHT, 10, -10);
    lv_obj_set_style_img_recolor(rr_icon, lv_color_hex(0xffff00), LV_PART_MAIN);
    lv_obj_set_style_img_recolor_opa(rr_icon, LV_OPA_COVER, LV_PART_MAIN);
    create_rr_animation(rr_icon);
}

void ScreenBuilder::create_rr_animation(lv_obj_t* rr_icon)
{
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, rr_icon);
    lv_anim_set_exec_cb(&a, rr_anim_cb);
    lv_anim_set_values(&a, 140, 200);
    lv_anim_set_duration(&a, 1200);
    lv_anim_set_playback_duration(&a, 1200);
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&a);
}

void ScreenBuilder::create_NIBP_panel()
{
    // NIBP panel
    NIBP_panel = lv_obj_create(main_screen);
    lv_obj_set_size(NIBP_panel, 110, 92);
    lv_obj_align(NIBP_panel, LV_ALIGN_TOP_RIGHT, 0, 180);
    lv_obj_set_style_bg_color(NIBP_panel, lv_color_hex(0X000000), LV_PART_MAIN);
    lv_obj_set_style_radius(NIBP_panel, 1, LV_PART_MAIN);
    lv_obj_clear_flag(NIBP_panel, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_border_color(NIBP_panel, lv_color_hex(0X008b8b), LV_PART_MAIN);
    lv_obj_set_style_border_width(NIBP_panel, 2, LV_PART_MAIN);
    lv_obj_set_style_border_side(NIBP_panel, (lv_border_side_t)(LV_BORDER_SIDE_BOTTOM | LV_BORDER_SIDE_LEFT | LV_BORDER_SIDE_RIGHT), LV_PART_MAIN);

    // NIBP label
    NIBP_label = lv_label_create(NIBP_panel);
    lv_label_set_text(NIBP_label, "NIBP");
    lv_obj_align(NIBP_label, LV_ALIGN_TOP_LEFT, -10, -10);
    lv_obj_set_style_text_color(NIBP_label, lv_color_hex(0x008b8b), LV_PART_MAIN);
    lv_obj_set_style_text_font(NIBP_label, &lv_font_montserrat_10, LV_PART_MAIN);
    lv_obj_clear_flag(NIBP_label, LV_OBJ_FLAG_SCROLLABLE);

    // systolic value label
    systolic_value_label = lv_label_create(NIBP_panel);
    lv_label_set_text(systolic_value_label, "--");
    lv_obj_align(systolic_value_label, LV_ALIGN_CENTER, -15, -15);
    lv_obj_set_style_text_color(systolic_value_label, lv_color_hex(0xFFFFff), LV_PART_MAIN);
    lv_obj_set_style_text_font(systolic_value_label, &lv_font_montserrat_26, LV_PART_MAIN);
    lv_obj_clear_flag(systolic_value_label, LV_OBJ_FLAG_SCROLLABLE);

    // diastolic value label
    diastolic_value_label = lv_label_create(NIBP_panel);
    lv_label_set_text(diastolic_value_label, "--");
    lv_obj_align(diastolic_value_label, LV_ALIGN_CENTER, -15, 25);
    lv_obj_set_style_text_color(diastolic_value_label, lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_set_style_text_font(diastolic_value_label, &lv_font_montserrat_26, LV_PART_MAIN);
    lv_obj_clear_flag(diastolic_value_label, LV_OBJ_FLAG_SCROLLABLE);

    // mean value label
    mean_value_label = lv_label_create(NIBP_panel);
    lv_label_set_text(mean_value_label, "(-)");
    lv_obj_align(mean_value_label, LV_ALIGN_CENTER, 30, 5);
    lv_obj_set_style_text_color(mean_value_label, lv_color_hex(0x90a4ae), LV_PART_MAIN);
    lv_obj_set_style_text_font(mean_value_label, &lv_font_montserrat_16, LV_PART_MAIN);

    // mean unit label
    mean_unit_label = lv_label_create(NIBP_panel);
    lv_label_set_text(mean_unit_label, "MEAN");
    lv_obj_align(mean_unit_label, LV_ALIGN_CENTER, 30, -15);
    lv_obj_set_style_text_color(mean_unit_label, lv_color_hex(0x008b8b), LV_PART_MAIN);
    lv_obj_set_style_text_font(mean_unit_label, &lv_font_montserrat_10, LV_PART_MAIN);

    // separator line
    separator = lv_obj_create(NIBP_panel);
    lv_obj_set_size(separator, 40, 1);
    lv_obj_align(separator, LV_ALIGN_CENTER, -15, 5);
    lv_obj_set_style_bg_color(separator, lv_color_hex(0x008b8b), LV_PART_MAIN);
    lv_obj_clear_flag(separator, LV_OBJ_FLAG_SCROLLABLE);  
    
    // unit label
    unit_label = lv_label_create(NIBP_panel); 
    lv_label_set_text(unit_label, "mmHg");
    lv_obj_align(unit_label, LV_ALIGN_BOTTOM_RIGHT, 10, 10);   
    lv_obj_set_style_text_color(unit_label, lv_color_hex(0x008b8b), LV_PART_MAIN);
    lv_obj_set_style_text_font(unit_label, &lv_font_montserrat_10, LV_PART_MAIN);
    lv_obj_clear_flag(unit_label, LV_OBJ_FLAG_SCROLLABLE);

}

void ScreenBuilder::create_ecg_panel()
{
    // ecg panel
    ecg_panel = lv_obj_create(main_screen);
    lv_obj_set_size(ecg_panel, 370, 200);
    lv_obj_align(ecg_panel, LV_ALIGN_CENTER, -55, 36);
    lv_obj_set_style_bg_color(ecg_panel, lv_color_hex(0X000000), LV_PART_MAIN);
    lv_obj_set_style_radius(ecg_panel, 1, LV_PART_MAIN);
    lv_obj_clear_flag(ecg_panel, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_border_width(ecg_panel, 2, LV_PART_MAIN);
    lv_obj_set_style_border_side(ecg_panel, (lv_border_side_t)(LV_BORDER_SIDE_TOP | LV_BORDER_SIDE_BOTTOM | LV_BORDER_SIDE_LEFT ), LV_PART_MAIN);
    lv_obj_set_style_border_color(ecg_panel, lv_color_hex(0X008b8b), LV_PART_MAIN);
    lv_obj_set_style_pad_all(ecg_panel, 0, LV_PART_MAIN);

    // ecg chart
    ecg_chart = lv_chart_create(ecg_panel);
    lv_obj_set_size(ecg_chart, 366, 194);
    lv_obj_align(ecg_chart, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_set_style_border_width(ecg_chart, 2, LV_PART_MAIN);
    lv_obj_set_style_bg_color(ecg_chart, lv_color_hex(0X000000), LV_PART_MAIN);
    lv_chart_set_type(ecg_chart, LV_CHART_TYPE_LINE);
    lv_chart_set_range(ecg_chart, LV_CHART_AXIS_PRIMARY_Y, 0, 250);
    lv_chart_set_point_count(ecg_chart, 150);
    lv_obj_set_style_size(ecg_chart, 0,0, LV_PART_INDICATOR);
    lv_obj_set_style_line_width(ecg_chart, 3, LV_PART_INDICATOR);
    lv_chart_set_div_line_count(ecg_chart, 20, 30);
    lv_obj_set_style_line_opa(ecg_chart, LV_OPA_20, LV_PART_MAIN);
    ecg_series = lv_chart_add_series(ecg_chart, lv_color_hex(0x00ff00), LV_CHART_AXIS_PRIMARY_Y);
    for(int i=0;i<120;i++)
    {
        lv_chart_set_next_value(ecg_chart,ecg_series,125);
    }

    // ecg label
    ecg_label = lv_label_create(ecg_panel);
    lv_label_set_text(ecg_label, "ECG");
    lv_obj_align(ecg_label, LV_ALIGN_TOP_LEFT, 10, 10);
    lv_obj_set_style_text_color(ecg_label, lv_color_hex(0x008b8b), LV_PART_MAIN);
    lv_obj_set_style_text_font(ecg_label, &lv_font_montserrat_18, LV_PART_MAIN);
    lv_obj_clear_flag(ecg_label, LV_OBJ_FLAG_SCROLLABLE);
    
    
}


#pragma once
#include "model/DataModel.hpp"
#include <zephyr/kernel.h>

struct AlarmState
{
    bool hr_alarm = false;
    bool spo2_alarm = false;
    bool rr_alarm = false;
    bool sys_alarm = false;
    bool dias_alarm = false;
};

class AlarmEngine
{
    private:
        // we need model obj in alarm so we created a refernce 
        DataModel& model_; 
        AlarmState alarm_state_;
        k_mutex alarm_mutex_;


        // thresh
        static constexpr const uint8_t hr_low_threshold   = 60;
        static constexpr const uint8_t hr_high_threshold = 100;
        static constexpr const uint8_t spo2_low_threshold = 90;
        static constexpr const uint8_t rr_low_threshold   = 12;
        static constexpr const uint8_t rr_high_threshold = 20;
        static constexpr const uint8_t sys_low_threshold  = 90;
        static constexpr const uint8_t sys_high_threshold = 140;
        static constexpr const uint8_t dias_low_threshold = 60;
        static constexpr const uint8_t dias_high_threshold = 90;


    public:
        // we used explicit because so we have valid parameterisation 
        explicit AlarmEngine(DataModel& model);
        AlarmState get_alarm_state();
        void CheckThresholds();
};
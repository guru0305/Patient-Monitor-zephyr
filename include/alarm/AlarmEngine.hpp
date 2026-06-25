#pragma once
#include "observer/IObserver.hpp"
#include "model/DataModel.hpp"

struct AlarmState
{
    bool ecg_alarm = false;
    bool hr_alarm = false;
    bool spo2_alarm = false;
    bool rr_alarm = false;
    bool bp_alarm = false;
};

class AlarmEngine : public IObserver
{
    private:
        // we need model obj in alarm so we created a refernce 
        DataModel& model_; 
        AlarmState alarm_state_;

        void CheckThresholds();

        // thresh
        const uint16_t ecg_threshold = 200 ; 
        const uint8_t hr_low_threshold   = 60;
        const uint8_t hr_high_threshold = 85;
        const uint8_t spo2_low_threshold = 90;
        const uint8_t rr_low_threshold   = 12;
        const uint8_t sys_low_threshold  = 100;

    public:
        // we used explicit because so we have valid parameterisation 
        explicit AlarmEngine(DataModel& model);
        const AlarmState& get_alarm_state() const ;
        void notify() override;
};
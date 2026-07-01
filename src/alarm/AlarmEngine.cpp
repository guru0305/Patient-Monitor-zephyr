#include "alarm/AlarmEngine.hpp"

AlarmEngine::AlarmEngine(DataModel& model) : model_(model)
{
    // we used : model_(model) refernce must be intialized before constr

    k_mutex_init(&alarm_mutex_);
}

AlarmState AlarmEngine::get_alarm_state()
{
    AlarmState copy;

    k_mutex_lock(&alarm_mutex_, K_FOREVER);

    copy = alarm_state_;

    k_mutex_unlock(&alarm_mutex_);

    return copy;
}

void AlarmEngine :: CheckThresholds()
{
    const PatientData& data =  model_.get_patient_data();

    k_mutex_lock(&alarm_mutex_, K_FOREVER);
    
    alarm_state_.hr_alarm = (data.hr >= hr_high_threshold || data.hr <= hr_low_threshold);
    alarm_state_.spo2_alarm = (data.spo2 <= spo2_low_threshold);
    alarm_state_.rr_alarm = (data.rr >= rr_high_threshold || data.rr <= rr_low_threshold );
    alarm_state_.sys_alarm = (data.sys >= sys_high_threshold || data.sys <= sys_low_threshold); 
    alarm_state_.dias_alarm = (data.dias >= dias_high_threshold || data.dias <= dias_low_threshold);

    k_mutex_unlock(&alarm_mutex_);

}


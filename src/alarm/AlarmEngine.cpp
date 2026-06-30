#include "alarm/AlarmEngine.hpp"

AlarmEngine::AlarmEngine(DataModel& model) : model_(model)
{
    // we used : model_(model) refernce must be intialized before constr
}

const AlarmState&
AlarmEngine::get_alarm_state() const
{
    return alarm_state_;
}

void AlarmEngine :: notify()
{
    CheckThresholds();
}

void AlarmEngine :: CheckThresholds()
{
    const PatientData& data =  model_.get_patient_data();
    
    alarm_state_.hr_alarm = (data.hr >= hr_high_threshold || data.hr <= hr_low_threshold);
    alarm_state_.spo2_alarm = (data.spo2 <= spo2_low_threshold);
    alarm_state_.rr_alarm = (data.rr >= rr_high_threshold || data.rr <= rr_low_threshold );
    alarm_state_.sys_alarm = (data.sys >= sys_high_threshold || data.sys <= sys_low_threshold); 
    alarm_state_.dias_alarm = (data.dias >= dias_high_threshold || data.dias <= dias_low_threshold);

}


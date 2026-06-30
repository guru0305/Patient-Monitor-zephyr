#include "controller/ViewController.hpp"


ViewController::ViewController(
    DataModel& model,
    AlarmEngine& alarm,
    DashboardView& view)
    :
    model_(model),
    alarm_(alarm),
    view_(view)
{
}

void ViewController::notify()
{
    const PatientData& data =
        model_.get_patient_data();

    const AlarmState& alarm_state =
        alarm_.get_alarm_state();

    view_.Update(data,alarm_state);
}
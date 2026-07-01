#include "controller/ViewController.hpp"
#include "threads/UIMessageQueue.hpp"

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
    UIMessage message;

    message.patient_data = model_.get_patient_data();
    message.alarm_state  = alarm_.get_alarm_state();

    int ret = k_msgq_put(
        &ui_message_queue,
        &message,
        K_NO_WAIT);

    if (ret != 0)
    {
        // Queue full: drop this frame.
    }
}
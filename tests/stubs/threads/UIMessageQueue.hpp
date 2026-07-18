#pragma once

#include <zephyr/kernel.h>

#include "model/PatientData.hpp"
#include "alarm/AlarmEngine.hpp"

struct UIMessage
{
    PatientData patient_data;
    AlarmState alarm_state;
};

extern k_msgq ui_message_queue;
extern UIMessage mock_last_message;

extern int mock_msgq_return;
extern void* mock_last_msg;
#pragma once

#include <zephyr/kernel.h>

#include "model/PatientData.hpp"
#include "alarm/AlarmEngine.hpp"

struct UIMessage
{
    PatientData patient_data;
    AlarmState alarm_state;
};

extern struct k_msgq ui_message_queue;

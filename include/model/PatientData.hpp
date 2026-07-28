// So this is a container only it act as a single object 

#pragma once
#include "model/MonitorStatus.hpp"
#include<cstdint>

struct PatientData
{
    uint8_t hr;
    uint8_t spo2;
    uint8_t rr;
    uint8_t sys;
    uint8_t dias;
    uint8_t mean;

    MonitorStatus monitor_status = MonitorStatus::Disconnected;

};
#pragma once

#include "model/PatientData.hpp"
#include "alarm/AlarmEngine.hpp"

class DashboardView
{
public:

    DashboardView() = default;

    void Update(
        const PatientData&,
        const AlarmState&)
    {
    }
};
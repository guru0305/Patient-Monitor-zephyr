#pragma once

#include "model/PatientData.hpp"
#include "alarm/AlarmEngine.hpp"
#include "ui/ScreenBuilder.hpp"

class DashboardView
{
    private:
        ScreenBuilder& screen_builder_;
    public:
        explicit DashboardView(ScreenBuilder& screen_builder);

        void Update(
            const PatientData& data,
            const AlarmState& alarm_state);
};
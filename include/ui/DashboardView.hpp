#pragma once

#include "model/PatientData.hpp"
#include "alarm/AlarmEngine.hpp"
#include "ui/ScreenBuilder.hpp"
#include "model/DataModel.hpp"
#include "alarm/AlarmTypes.hpp"

class DashboardView
{
    private:
        ScreenBuilder& screen_builder_;
        DataModel& model_;
    public:
        explicit DashboardView(ScreenBuilder& screen_builder, DataModel& model);

        void Update(
            const PatientData& data,
            const AlarmState& alarm_state);
};
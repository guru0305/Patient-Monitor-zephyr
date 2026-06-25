#ifndef VIEW_CONTROLLER_HPP
#define VIEW_CONTROLLER_HPP

#include "observer/IObserver.hpp"
#include "model/DataModel.hpp"
#include "alarm/AlarmEngine.hpp"
#include "ui/DashboardView.hpp"

class ViewController : public IObserver
{
private:
    DataModel& model_;
    AlarmEngine& alarm_;
    DashboardView& view_;

public:
    ViewController(
        DataModel& model,
        AlarmEngine& alarm,
        DashboardView& view);

    void notify() override;
};

#endif
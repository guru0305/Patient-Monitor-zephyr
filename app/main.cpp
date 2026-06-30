#include <zephyr/kernel.h>
#include "lvgl.h"

#include "ui/ScreenBuilder.hpp"
#include "datasource/SineWaveSource.hpp"
#include "model/DataModel.hpp"
#include "controller/ApplicationController.hpp"
#include "alarm/AlarmEngine.hpp"
#include "ui/DashboardView.hpp"
#include "controller/ViewController.hpp"

int main()
{
    SineWaveSource source;
    DataModel model;
    FakeVitalSource vital_source;

    ScreenBuilder screen_builder;

    ApplicationController controller(
        source,
        vital_source,
        model);

    AlarmEngine alarm(model);

    DashboardView dashboard(screen_builder);

    ViewController view_controller(
        model,
        alarm,
        dashboard);

    screen_builder.build();

    model.attach(&alarm);
    model.attach(&view_controller);

    int64_t last_update = k_uptime_get();

    while (true)
    {
        lv_timer_handler();

        if ((k_uptime_get() - last_update) >= 1000)
        {
            controller.Update();
            last_update = k_uptime_get();
        }

        k_sleep(K_MSEC(5));
    }

    return 0;
}
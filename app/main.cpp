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
    SineWaveSource sn;
    DataModel mod;
    FakeVitalSource vit;

    ScreenBuilder builder;

    ApplicationController controller(sn, vit, mod);

    AlarmEngine alarm(mod);
    DashboardView dash(builder);

    ViewController vcontroller(mod, alarm, dash);

    builder.build();

    mod.attach(&alarm);
    mod.attach(&vcontroller);

    while (true)
    {
        controller.Update();

        lv_timer_handler();

        k_sleep(K_MSEC(20));
    }

    return 0;
}
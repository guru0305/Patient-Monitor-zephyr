#include <zephyr/kernel.h>
#include "lvgl.h"

#include "ui/ScreenBuilder.hpp"
#include "datasource/SineWaveSource.hpp"
#include "datasource/AdcSource.hpp"
#include "model/DataModel.hpp"
#include "controller/ApplicationController.hpp"
#include "alarm/AlarmEngine.hpp"
#include "ui/DashboardView.hpp"
#include "controller/ViewController.hpp"
#include "threads/SensorThread.hpp"
#include "threads/LVGLThread.hpp"
#include "threads/AlarmThread.hpp"

int main()
{
    SineWaveSource source;
    DataModel model;
    FakeVitalSource vital_source;
    AdcSource adc;
    ScreenBuilder screen_builder;
    ApplicationController controller(adc, vital_source, model);
    AlarmEngine alarm(model);
    DashboardView dashboard(screen_builder,model);
    ViewController view_controller(model, alarm, dashboard);

    if (!adc.Init())
    {
        printk("Failed to initialize AdcSource\n");
    }

    model.attach(&view_controller);

    InitSensorThread(controller, adc);
    InitAlarmThread(alarm);
    InitLVGLThread(dashboard,screen_builder);

    while (true)
    {
        k_sleep(K_FOREVER);
    }

    return 0;
}
#pragma once

class ApplicationController;
class AdcSource;

void InitSensorThread(ApplicationController& controller,
                      AdcSource& adc_source);

#ifdef UNIT_TEST
void RunSensorThreadForTest();
#endif
#include "datasource/FakeVitalSource.hpp"

VitalSigns FakeVitalSource :: GetVitals()
{
    if(count >= 18)
    {
        count=0;
    }

    VitalSigns vital;

    vital.hr = hr[count];
    vital.rr = rr[count];
    vital.spo2 = spo2[count];

    vital.sys = sys[count];
    vital.dias = dias[count];
    vital.mean = (2 * (dias[count]) + sys[count]) / 3 ;

    count++;

    return vital;

}
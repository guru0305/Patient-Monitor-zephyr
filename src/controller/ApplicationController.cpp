#include "controller/ApplicationController.hpp"

ApplicationController::ApplicationController(
    IDataSource& source,
    FakeVitalSource& vital_source,
    DataModel& model)
    :
    source_(source),
    model_(model),
    vital_source_(vital_source)
    
{
}

void ApplicationController::UpdateVitals()
{
    PatientData data{};
    VitalSigns vital = vital_source_.GetVitals();

    data.hr = vital.hr;
    data.spo2 = vital.spo2;
    data.rr = vital.rr;
    data.dias = vital.dias;
    data.sys = vital.sys;
    data.mean = vital.mean;

    data.monitor_status = source_.GetMonitorStatus();  
    
    model_.set_patient_data(data);
}

void ApplicationController::UpdateECG()
{
    uint16_t ecg_sample = source_.GetSample();

    model_.PushECGSample(ecg_sample);
}
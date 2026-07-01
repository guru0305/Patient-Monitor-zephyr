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

void ApplicationController::Update()
{
    PatientData data{};
    VitalSigns vital = vital_source_.GetVitals();

    uint16_t ecg_sample = source_.GetSample();

    data.ecg = ecg_sample;
    data.hr = vital.hr;
    data.spo2 = vital.spo2;
    data.rr = vital.rr;
    data.dias = vital.dias;
    data.sys = vital.sys;
    data.mean = vital.mean;

    model_.PushECGSample(ecg_sample);

    model_.set_patient_data(data);
}
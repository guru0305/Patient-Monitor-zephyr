#include "controller/ApplicationController.hpp"

ApplicationController::ApplicationController(
    IDataSource& source,
    FakeVitalSource& vital_source,
    DataModel& model)
    :
    source_(source),
    vital_source_(vital_source),
    model_(model)
{
}

void ApplicationController::Update()
{
    PatientData data{};
    VitalSigns vital = vital_source_.GetVitals();

    data.ecg = source_.GetSample();
    data.hr = vital.hr;
    data.spo2 = vital.spo2;
    data.rr = vital.rr;
    data.dias = vital.dias;
    data.sys = vital.sys;
    data.mean = vital.mean;

    model_.set_patient_data(data);
}
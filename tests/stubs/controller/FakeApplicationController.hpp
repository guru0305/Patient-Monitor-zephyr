#pragma once

#include "datasource/IDataSource.hpp"
#include "datasource/FakeVitalSource.hpp"
#include "model/DataModel.hpp"

class FakeApplicationController
{
public:
    int update_ecg_calls = 0;
    int update_vitals_calls = 0;

    FakeApplicationController(
        IDataSource&,
        FakeVitalSource&,
        DataModel&)
    {
    }

    void UpdateECG()
    {
        update_ecg_calls++;
    }

    void UpdateVitals()
    {
        update_vitals_calls++;
    }
};
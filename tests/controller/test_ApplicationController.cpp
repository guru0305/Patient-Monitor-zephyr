#include <gtest/gtest.h>

#include "controller/ApplicationController.hpp"

#include "datasource/SineWaveSource.hpp"
#include "datasource/FakeVitalSource.hpp"

#include "model/DataModel.hpp"

TEST(ApplicationControllerTest, ConstructorDoesNotCrash)
{
    SineWaveSource source;
    FakeVitalSource vital_source;
    DataModel model;

    ApplicationController controller(
        source,
        vital_source,
        model);

    SUCCEED();
}

TEST(ApplicationControllerTest, UpdateVitalsCopiesAllFieldsToModel)
{
    SineWaveSource source;
    FakeVitalSource vital_source;
    DataModel model;

    ApplicationController controller(
        source,
        vital_source,
        model);

    controller.UpdateVitals();

    PatientData data = model.get_patient_data();

    EXPECT_EQ(data.hr, 75);
    EXPECT_EQ(data.spo2, 97);
    EXPECT_EQ(data.rr, 16);
    EXPECT_EQ(data.sys, 118);
    EXPECT_EQ(data.dias, 78);
    EXPECT_EQ(data.mean, 91);

    EXPECT_EQ(
        data.monitor_status,
        MonitorStatus::Connected);
}

TEST(ApplicationControllerTest, UpdateECGPushesSampleIntoModel)
{
    SineWaveSource source;
    FakeVitalSource vital_source;
    DataModel model;

    ApplicationController controller(
        source,
        vital_source,
        model);

    controller.UpdateECG();

    uint16_t sample = 0;

    uint32_t bytes = model.PopECGSamples(
        reinterpret_cast<uint8_t*>(&sample),
        sizeof(sample));

    EXPECT_EQ(bytes, sizeof(uint16_t));

    // Expected first ECG sample from SineWaveSource
    EXPECT_EQ(sample, 120);
}
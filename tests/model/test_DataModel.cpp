#include <gtest/gtest.h>

#include "model/DataModel.hpp"

TEST(DataModelTest, SetAndGetPatientData)
{
    DataModel model;

    PatientData data{};
    data.hr = 72;
    data.spo2 = 98;
    data.rr = 16;
    data.sys = 120;
    data.dias = 80;
    data.mean = 93;

    model.set_patient_data(data);

    PatientData result = model.get_patient_data();

    EXPECT_EQ(result.hr, 72);
    EXPECT_EQ(result.spo2, 98);
    EXPECT_EQ(result.rr, 16);
    EXPECT_EQ(result.sys, 120);
    EXPECT_EQ(result.dias, 80);
    EXPECT_EQ(result.mean, 93);
}

TEST(DataModelTest, PatientDataCanBeOverwritten)
{
    DataModel model;

    PatientData first{};
    first.hr = 60;

    PatientData second{};
    second.hr = 95;

    model.set_patient_data(first);
    model.set_patient_data(second);

    EXPECT_EQ(model.get_patient_data().hr, 95);
}

TEST(DataModelTest, PushAndPopSingleECGSample)
{
    DataModel model;

    uint16_t sample = 1234;

    model.PushECGSample(sample);

    uint16_t output = 0;

    uint32_t bytes =
        model.PopECGSamples(
            reinterpret_cast<uint8_t*>(&output),
            sizeof(output));

    EXPECT_EQ(bytes, sizeof(sample));
    EXPECT_EQ(output, sample);
}

TEST(DataModelTest, PushAndPopMultipleSamples)
{
    DataModel model;

    uint16_t samples[] =
    {
        100,
        200,
        300
    };

    for (auto s : samples)
        model.PushECGSample(s);

    uint16_t output[3]{};

    uint32_t bytes =
        model.PopECGSamples(
            reinterpret_cast<uint8_t*>(output),
            sizeof(output));

    EXPECT_EQ(bytes, sizeof(samples));

    EXPECT_EQ(output[0], 100);
    EXPECT_EQ(output[1], 200);
    EXPECT_EQ(output[2], 300);
}

TEST(DataModelTest, PopEmptyBufferReturnsZero)
{
    DataModel model;

    uint16_t output = 0;

    uint32_t bytes =
        model.PopECGSamples(
            reinterpret_cast<uint8_t*>(&output),
            sizeof(output));

    EXPECT_EQ(bytes, 0);
}
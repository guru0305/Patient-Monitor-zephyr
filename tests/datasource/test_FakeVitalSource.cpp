#include <gtest/gtest.h>

#include "datasource/FakeVitalSource.hpp"

TEST(FakeVitalSourceTest, FirstVitalSignsAreCorrect)
{
    FakeVitalSource source;

    VitalSigns vital = source.GetVitals();

    EXPECT_EQ(vital.hr,   75);
    EXPECT_EQ(vital.spo2, 97);
    EXPECT_EQ(vital.rr,   16);

    EXPECT_EQ(vital.sys,  118);
    EXPECT_EQ(vital.dias, 78);
    EXPECT_EQ(vital.mean, 91);
}

TEST(FakeVitalSourceTest, MeanPressureIsCalculatedCorrectly)
{
    FakeVitalSource source;

    for (int i = 0; i < 18; ++i)
    {
        VitalSigns vital = source.GetVitals();

        uint8_t expected =
            (2 * vital.dias + vital.sys) / 3;

        EXPECT_EQ(vital.mean, expected);
    }
}

TEST(FakeVitalSourceTest, SequenceWrapsAfterEighteenSamples)
{
    FakeVitalSource source;

    VitalSigns first = source.GetVitals();

    for (int i = 1; i < 64; ++i)
    {
        source.GetVitals();
    }

    VitalSigns wrapped = source.GetVitals();

    EXPECT_EQ(first.hr,   wrapped.hr);
    EXPECT_EQ(first.spo2, wrapped.spo2);
    EXPECT_EQ(first.rr,   wrapped.rr);
    EXPECT_EQ(first.sys,  wrapped.sys);
    EXPECT_EQ(first.dias, wrapped.dias);
    EXPECT_EQ(first.mean, wrapped.mean);
}
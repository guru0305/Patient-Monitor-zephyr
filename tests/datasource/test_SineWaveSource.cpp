#include <gtest/gtest.h>

#include "datasource/SineWaveSource.hpp"

TEST(SineWaveSourceTest, FirstSampleIsCorrect)
{
    SineWaveSource source;

    EXPECT_EQ(source.GetSample(), 120);
}

TEST(SineWaveSourceTest, SamplesRemainWithinRange)
{
    SineWaveSource source;

    for(int i = 0; i < 1000; ++i)
    {
        uint16_t sample = source.GetSample();

        EXPECT_GE(sample, 20);
        EXPECT_LE(sample, 220);
    }
}

TEST(SineWaveSourceTest, ConsecutiveSamplesChange)
{
    SineWaveSource source;

    uint16_t first = source.GetSample();

    bool changed = false;

    for(int i = 0; i < 20; ++i)
    {
        if(source.GetSample() != first)
        {
            changed = true;
            break;
        }
    }

    EXPECT_TRUE(changed);
}
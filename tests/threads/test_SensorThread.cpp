#include <gtest/gtest.h>
#include <setjmp.h>

#define private public
#include "datasource/AdcSource.hpp"
#undef private

#include "datasource/FakeVitalSource.hpp"
#include "controller/ApplicationController.hpp"
#include "model/DataModel.hpp"
#include "threads/SensorThread.hpp"

#include <zephyr/kernel.h>

TEST(SensorThreadTest, ThreadExecutesOneIteration)
{
    DataModel model;

    AdcSource adc;

    ASSERT_TRUE(adc.Init());

    const char* input = "123,0\n";

    ring_buf_put(
        &adc.rx_ring_,
        reinterpret_cast<const uint8_t*>(input),
        strlen(input));

    FakeVitalSource vital;

    ApplicationController app(
        adc,
        vital,
        model);

    InitSensorThread(app, adc);

    mock_sem_take_count = 0;
    mock_sleep_count = 0;
    mock_sleep_limit = 1;

    if (setjmp(mock_thread_exit) == 0)
    {
        RunSensorThreadForTest();
    }

    EXPECT_EQ(mock_sem_take_count, 1);
    EXPECT_EQ(mock_sleep_count, 1);
}

TEST(SensorThreadTest, UpdateVitalsAfter250Iterations)
{
    DataModel model;

    AdcSource adc;

    ASSERT_TRUE(adc.Init());

    const char* input = "123,0\n";

    for (int i = 0; i < 250; i++)
    {
        ring_buf_put(
            &adc.rx_ring_,
            reinterpret_cast<const uint8_t*>(input),
            strlen(input));
    }

    FakeVitalSource vital;

    ApplicationController app(
        adc,
        vital,
        model);

    InitSensorThread(app, adc);

    mock_sem_take_count = 0;
    mock_sleep_count = 0;
    mock_sleep_limit = 250;

    RunSensorThreadForTest();

    EXPECT_EQ(mock_sem_take_count, 1);
    EXPECT_EQ(mock_sleep_count, 250);
}
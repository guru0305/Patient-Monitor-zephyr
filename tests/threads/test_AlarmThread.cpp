#include <gtest/gtest.h>

#include "threads/AlarmThread.hpp"

#include "alarm/AlarmEngine.hpp"
#include "model/DataModel.hpp"

#include <zephyr/kernel.h>

TEST(AlarmThreadTest, InitAlarmThreadGivesSemaphore)
{
    DataModel model;
    AlarmEngine alarm(model);

    mock_sem_give_count = 0;

    InitAlarmThread(alarm);

    EXPECT_EQ(mock_sem_give_count, 1);
}

TEST(AlarmThreadTest, ThreadExecutesOneIteration)
{
    DataModel model;
    AlarmEngine alarm(model);

    InitAlarmThread(alarm);

    mock_sleep_count = 0;
    mock_sleep_limit = 1;
    mock_sem_take_count = 0;

    RunAlarmThreadForTest();

    EXPECT_EQ(mock_sem_take_count, 1);
    EXPECT_EQ(mock_sleep_count, 1);
}
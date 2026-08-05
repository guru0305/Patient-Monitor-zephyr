#include <gtest/gtest.h>

#include "lvgl.h"
#include "others/test/lv_test_display.h"

#include "threads/LVGLThread.hpp"
#include "ui/ScreenBuilder.hpp"
#include "ui/DashboardView.hpp"
#include "model/DataModel.hpp"

#include <zephyr/kernel.h>

class LVGLThreadTest : public ::testing::Test
{
protected:

    lv_display_t* display = nullptr;

    void SetUp() override
    {
        lv_init();

        display = lv_test_display_create(480, 320);
    }

    void TearDown() override
    {
        if(display)
        {
            lv_display_delete(display);
        }

        lv_deinit();
    }
};

TEST_F(LVGLThreadTest, InitLVGLThreadGivesSemaphore)
{
    ScreenBuilder screen;

    screen.build();

    DataModel model;

    DashboardView dashboard(screen, model);

    mock_sem_give_count = 0;

    InitLVGLThread(dashboard, screen);

    EXPECT_EQ(mock_sem_give_count, 1);
}

TEST_F(LVGLThreadTest, ThreadExecutesOneIteration)
{
    ScreenBuilder screen;
    screen.build();

    DataModel model;
    DashboardView dashboard(screen, model);

    InitLVGLThread(dashboard, screen);

    mock_sem_take_count = 0;
    mock_sleep_count = 0;

    mock_sleep_limit = 1;
    mock_msgq_get_return = -1;
    mock_uptime = 0;

    if (setjmp(mock_thread_exit) == 0)
    {
        RunLVGLThreadForTest();
    }

    EXPECT_EQ(mock_sem_take_count, 1);
    EXPECT_EQ(mock_sleep_count, 1);
}

TEST_F(LVGLThreadTest, ProcessesMultipleMessages)
{
    ScreenBuilder screen;
    screen.build();

    DataModel model;
    DashboardView dashboard(screen, model);

    InitLVGLThread(dashboard, screen);

    mock_sem_take_count = 0;
    mock_sleep_count = 0;

    mock_sleep_limit = 1;

    mock_uptime = 0;

    mock_msgq_sequence[0] = 0;
    mock_msgq_sequence[1] = 0;
    mock_msgq_sequence[2] = -1;

    mock_msgq_sequence_size = 3;
    mock_msgq_sequence_index = 0;

    RunLVGLThreadForTest();

    EXPECT_EQ(mock_sem_take_count, 1);
    EXPECT_EQ(mock_sleep_count, 1);
}
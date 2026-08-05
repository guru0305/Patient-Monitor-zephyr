#include <zephyr/kernel.h>
#include <setjmp.h>
#include <cstdarg>

jmp_buf mock_thread_exit;

int mock_sleep_count = 0;
int mock_sleep_limit = 0;

int mock_sem_take_count = 0;
int mock_sem_give_count = 0;


int64_t mock_uptime = 0;

int mock_uptime_calls = 0;

int mock_msgq_sequence[10];
int mock_msgq_sequence_size = 0;
int mock_msgq_sequence_index = 0;

int64_t k_uptime_get()
{
    if (mock_uptime_calls++ == 0)
    {
        return 0;
    }

    return 1000;
}

int mock_msgq_get_return = -1;

int k_msgq_get(
    k_msgq* queue,
    void* data,
    int32_t timeout)
{
    (void)queue;
    (void)data;
    (void)timeout;

    if (mock_msgq_sequence_index < mock_msgq_sequence_size)
    {
        return mock_msgq_sequence[mock_msgq_sequence_index++];
    }

    return -1;
}

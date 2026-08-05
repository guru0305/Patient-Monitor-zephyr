#pragma once

#include <stdint.h>
#include <setjmp.h>
#include <zephyr/sys/printk.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    int dummy;
} k_mutex;

#define K_FOREVER (-1)
typedef int k_timeout_t;

#define K_MSEC(ms) (ms)

#define K_THREAD_DEFINE(...) \
    static int dummy_thread

extern jmp_buf mock_thread_exit;

static inline void k_mutex_init(k_mutex* mutex)
{
    (void)mutex;
}

static inline int k_mutex_lock(k_mutex* mutex, int32_t timeout)
{
    (void)mutex;
    (void)timeout;
    return 0;
}

static inline int k_mutex_unlock(k_mutex* mutex)
{
    (void)mutex;
    return 0;
}

extern int mock_sleep_count;
extern int mock_sleep_limit;

extern int mock_msgq_sequence[10];
extern int mock_msgq_sequence_size;
extern int mock_msgq_sequence_index;

static inline void k_sleep(k_timeout_t timeout)
{
    (void)timeout;

    mock_sleep_count++;

    if (mock_sleep_limit > 0 &&
        mock_sleep_count >= mock_sleep_limit)
    {
        longjmp(mock_thread_exit, 1);
    }
}

typedef struct
{
    int count;
} k_sem;

#define K_SEM_DEFINE(name, initial, limit) \
    k_sem name = { initial }

extern int mock_sem_take_count;
extern int mock_sem_give_count;

static inline int k_sem_take(k_sem* sem, k_timeout_t timeout)
{
    (void)sem;
    (void)timeout;

    mock_sem_take_count++;

    return 0;
}

static inline void k_sem_give(k_sem* sem)
{
    (void)sem;

    mock_sem_give_count++;
}

// ----------------------------------------------------
// Message Queue Stub
// ----------------------------------------------------

typedef struct
{
    int dummy;
} k_msgq;

#define K_NO_WAIT 0

int k_msgq_put(
    k_msgq* queue,
    const void* data,
    int32_t timeout);

extern int64_t mock_uptime;
extern int mock_msgq_get_return;

int64_t k_uptime_get(void);

int k_msgq_get(
    k_msgq* queue,
    void* data,
    int32_t timeout);

#ifdef __cplusplus
}
#endif
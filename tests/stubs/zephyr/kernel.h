#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    int dummy;
} k_mutex;

#define K_FOREVER (-1)

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

#ifdef __cplusplus
}
#endif
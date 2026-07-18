#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct ring_buf
{
    uint8_t* buffer;
    uint32_t size;
    uint32_t head;
    uint32_t tail;
};

static inline void ring_buf_init(
    struct ring_buf* rb,
    uint32_t size,
    uint8_t* storage)
{
    rb->buffer = storage;
    rb->size = size;
    rb->head = 0;
    rb->tail = 0;
}

static inline uint32_t ring_buf_put(
    struct ring_buf* rb,
    const uint8_t* data,
    uint32_t length)
{
    uint32_t written = 0;

    while (written < length)
    {
        uint32_t next = (rb->head + 1) % rb->size;

        if (next == rb->tail)
            break;

        rb->buffer[rb->head] = data[written];

        rb->head = next;
        ++written;
    }

    return written;
}

static inline uint32_t ring_buf_get(
    struct ring_buf* rb,
    uint8_t* data,
    uint32_t length)
{
    uint32_t read = 0;

    while ((read < length) && (rb->tail != rb->head))
    {
        data[read] = rb->buffer[rb->tail];

        rb->tail = (rb->tail + 1) % rb->size;

        ++read;
    }

    return read;
}

#ifdef __cplusplus
}
#endif
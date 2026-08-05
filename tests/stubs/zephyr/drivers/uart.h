#pragma once

#include <stdint.h>
#include <stddef.h>

struct device;

typedef void (*uart_irq_callback_user_data_t)(
    const struct device*,
    void*);

extern int mock_uart_fifo_read_return;
extern bool mock_uart_irq_update_return;
extern bool mock_uart_irq_rx_ready_return;

extern uint8_t mock_uart_fifo_data[256];

inline int uart_fifo_read(
    const struct device*,
    uint8_t* data,
    int size)
{
    for(int i = 0; i < mock_uart_fifo_read_return && i < size; i++)
    {
        data[i] = mock_uart_fifo_data[i];
    }

    return mock_uart_fifo_read_return;
}

inline bool uart_irq_update(const struct device*)
{
    return mock_uart_irq_update_return;
}

inline bool uart_irq_rx_ready(const struct device*)
{
    return mock_uart_irq_rx_ready_return;
}

inline void uart_irq_callback_user_data_set(
    const struct device*,
    uart_irq_callback_user_data_t,
    void*)
{
}

inline void uart_irq_rx_enable(const struct device*)
{
}
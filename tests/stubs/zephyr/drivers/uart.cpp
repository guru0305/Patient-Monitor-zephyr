#include <zephyr/drivers/uart.h>

int mock_uart_fifo_read_return = 0;

bool mock_uart_irq_update_return = true;
bool mock_uart_irq_rx_ready_return = false;

uint8_t mock_uart_fifo_data[256] = {};
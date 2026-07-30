#include "datasource/AdcSource.hpp"
#include <zephyr/usb/usb_device.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/sys/printk.h>
#include <zephyr/device.h>
#include <cstdlib>

#define CDC_ACM_NODE DT_NODELABEL(cdc_acm_uart0)

bool AdcSource::Init()
{
    usb_dev_ = DEVICE_DT_GET(CDC_ACM_NODE);

    if (!device_is_ready(usb_dev_))
    {
        return false;
    }

    int ret = usb_enable(NULL);
    if (ret)
    {
        return false;
    }

    ring_buf_init(&rx_ring_, RX_RING_SIZE, rx_ring_storage_);

    uart_irq_callback_user_data_set(usb_dev_, &AdcSource::UartIsr, this);
    uart_irq_rx_enable(usb_dev_);

    return true;
}

void AdcSource::UartIsr(const struct device* dev, void* user_data)
{
    AdcSource* self = static_cast<AdcSource*>(user_data);

    if (!uart_irq_update(dev))
    {
        return;
    }

    if (uart_irq_rx_ready(dev))
    {
        self->HandleIsr();
    }
}

void AdcSource::HandleIsr()
{
    uint8_t chunk[32];

    int n = uart_fifo_read(usb_dev_, chunk, sizeof(chunk));

    if (n > 0)
    {
        // If the ring fills (consumer too slow), oldest bytes are dropped
        // via return value ignored here on purpose: bounded, no blocking in ISR.
        ring_buf_put(&rx_ring_, chunk, static_cast<uint32_t>(n));
    }
}

void AdcSource::Process()
{
    uint8_t byte;
    size_t consumed = 0;

    while (consumed < MAX_BYTES_PER_CALL &&
           ring_buf_get(&rx_ring_, &byte, 1) == 1)
    {
        consumed++;

        if (byte == '\r' || byte == '\n')
        {
            if (line_index_ > 0)
            {
                line_buffer_[line_index_] = '\0';
                char* token = strtok(line_buffer_, ",");

                if(token != nullptr)
                {
                    uint16_t sample = static_cast<uint16_t>(atoi(token));

                    token = strtok(nullptr, ",");

                    if(token != nullptr)
                    {
                        uint8_t status = static_cast<uint8_t>(atoi(token));

                        switch(status)
                        {
                            case 0:
                                monitor_status_ = MonitorStatus::Connected;
                                break;

                            case 1:
                                monitor_status_ = MonitorStatus::CheckLeads;
                                break;

                            default:
                                monitor_status_ = MonitorStatus::Disconnected;
                                break;
                        }
                    }

                    PushToFifo(sample);
                }
                line_index_ = 0;
            }
        }
        else if (line_index_ < sizeof(line_buffer_) - 1)
        {
            line_buffer_[line_index_++] = byte;
        }
    }
}

uint16_t AdcSource::GetSample()
{
    return sample_;
}

void AdcSource::PushToFifo(uint16_t sample)
{
    if (fifo_count_ >= SAMPLE_FIFO_SIZE)
    {
        // Drop oldest sample if full
        fifo_tail_ = (fifo_tail_ + 1) % SAMPLE_FIFO_SIZE;
        fifo_count_--;
    }

    sample_fifo_[fifo_head_] = sample;
    fifo_head_ = (fifo_head_ + 1) % SAMPLE_FIFO_SIZE;
    fifo_count_++;
}

bool AdcSource::HasSample()
{
    return fifo_count_ > 0;
}

uint16_t AdcSource::PopSample()
{
    if (fifo_count_ == 0)
    {
        return sample_;
    }

    sample_ = sample_fifo_[fifo_tail_];

    fifo_tail_ = (fifo_tail_ + 1) % SAMPLE_FIFO_SIZE;
    fifo_count_--;

    return sample_;
}

MonitorStatus AdcSource::GetMonitorStatus() const
{
    return monitor_status_;
}
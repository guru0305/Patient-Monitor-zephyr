#pragma once

#include <zephyr/device.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/sys/ring_buffer.h>
#include "model/MonitorStatus.hpp"
#include "datasource/IDataSource.hpp"
#include <cstring>

class AdcSource : public IDataSource
{
public:
    bool Init();
    void Process();
    uint16_t GetSample() override;

    bool HasSample();
    uint16_t PopSample();

    MonitorStatus GetMonitorStatus() const override;

private:
    static constexpr size_t RX_RING_SIZE = 256;
    static constexpr size_t MAX_BYTES_PER_CALL = 64;

    static constexpr size_t SAMPLE_FIFO_SIZE = 64;

    const struct device* usb_dev_;

    uint8_t rx_ring_storage_[RX_RING_SIZE];
    struct ring_buf rx_ring_;

    char line_buffer_[16];
    uint8_t line_index_ = 0;

    uint16_t sample_fifo_[SAMPLE_FIFO_SIZE];
    size_t fifo_head_ = 0;
    size_t fifo_tail_ = 0;
    size_t fifo_count_ = 0;

    uint16_t sample_ = 0;
    MonitorStatus monitor_status_ = MonitorStatus::Disconnected;

    static void UartIsr(const struct device* dev, void* user_data);
    void HandleIsr();

    void PushToFifo(uint16_t sample);
};
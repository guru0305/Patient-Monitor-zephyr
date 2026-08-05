#include <gtest/gtest.h>
#include <zephyr/usb/usb_device.h>
#define private public
#include "datasource/AdcSource.hpp"
#undef private

TEST(AdcSourceTest, ConstructorDoesNotCrash)
{
    AdcSource adc;

    SUCCEED();
}

TEST(AdcSourceTest, InitFailsWhenDeviceIsNotReady)
{
    AdcSource adc;

    mock_device_is_ready = false;

    EXPECT_FALSE(adc.Init());
}

TEST(AdcSourceTest, InitFailsWhenUsbEnableFails)
{
    AdcSource adc;

    mock_device_is_ready = true;
    mock_usb_enable_return = -1;

    EXPECT_FALSE(adc.Init());
}

TEST(AdcSourceTest, InitSucceeds)
{
    AdcSource adc;

    mock_device_is_ready = true;
    mock_usb_enable_return = 0;

    EXPECT_TRUE(adc.Init());
}

TEST(AdcSourceTest, UartIsrReturnsWhenUpdateFails)
{
    AdcSource adc;

    mock_device_is_ready = true;
    mock_usb_enable_return = 0;

    ASSERT_TRUE(adc.Init());

    mock_uart_irq_update_return = false;
    mock_uart_irq_rx_ready_return = false;

    AdcSource::UartIsr(&mock_device, &adc);

    SUCCEED();
}

TEST(AdcSourceTest, UartIsrReturnsWhenRxNotReady)
{
    AdcSource adc;

    mock_device_is_ready = true;
    mock_usb_enable_return = 0;

    ASSERT_TRUE(adc.Init());

    mock_uart_irq_update_return = true;
    mock_uart_irq_rx_ready_return = false;

    AdcSource::UartIsr(&mock_device, &adc);

    SUCCEED();
}

TEST(AdcSourceTest, UartIsrCallsHandleIsr)
{
    AdcSource adc;

    mock_device_is_ready = true;
    mock_usb_enable_return = 0;

    ASSERT_TRUE(adc.Init());

    mock_uart_irq_update_return = true;
    mock_uart_irq_rx_ready_return = true;

    mock_uart_fifo_read_return = 0;

    AdcSource::UartIsr(&mock_device, &adc);

    SUCCEED();
}

TEST(AdcSourceTest, HandleIsrStoresBytesInRingBuffer)
{
    AdcSource adc;

    mock_device_is_ready = true;
    mock_usb_enable_return = 0;

    ASSERT_TRUE(adc.Init());

    mock_uart_irq_update_return = true;
    mock_uart_irq_rx_ready_return = true;

    mock_uart_fifo_read_return = 3;

    mock_uart_fifo_data[0] = '1';
    mock_uart_fifo_data[1] = '2';
    mock_uart_fifo_data[2] = '\n';

    AdcSource::UartIsr(&mock_device, &adc);

    SUCCEED();
}

TEST(AdcSourceTest, ProcessParsesConnectedSample)
{
    AdcSource adc;

    ASSERT_TRUE(adc.Init());

    const char* input = "123,0\n";

    ring_buf_put(
        &adc.rx_ring_,
        reinterpret_cast<const uint8_t*>(input),
        strlen(input));

    adc.Process();

    EXPECT_EQ(adc.GetMonitorStatus(), MonitorStatus::Connected);

    EXPECT_TRUE(adc.HasSample());

    EXPECT_EQ(adc.PopSample(), 123);

    EXPECT_EQ(adc.GetSample(), 123);

    EXPECT_FALSE(adc.HasSample());
}

TEST(AdcSourceTest, ProcessParsesCheckLeadsStatus)
{
    AdcSource adc;

    mock_device_is_ready = true;
    mock_usb_enable_return = 0;

    ASSERT_TRUE(adc.Init());

    const char* input = "100,1\n";

    ring_buf_put(
        &adc.rx_ring_,
        reinterpret_cast<const uint8_t*>(input),
        strlen(input));

    adc.Process();

    EXPECT_EQ(adc.GetMonitorStatus(), MonitorStatus::CheckLeads);

    EXPECT_TRUE(adc.HasSample());

    EXPECT_EQ(adc.PopSample(), 100);

    EXPECT_FALSE(adc.HasSample());
}

TEST(AdcSourceTest, ProcessParsesDisconnectedStatus)
{
    AdcSource adc;

    mock_device_is_ready = true;
    mock_usb_enable_return = 0;

    ASSERT_TRUE(adc.Init());

    const char* input = "200,7\n";

    ring_buf_put(
        &adc.rx_ring_,
        reinterpret_cast<const uint8_t*>(input),
        strlen(input));

    adc.Process();

    EXPECT_EQ(adc.GetMonitorStatus(), MonitorStatus::Disconnected);
    EXPECT_TRUE(adc.HasSample());
    EXPECT_EQ(adc.PopSample(), 200);
}

TEST(AdcSourceTest, ProcessWithoutStatusToken)
{
    AdcSource adc;

    mock_device_is_ready = true;
    mock_usb_enable_return = 0;

    ASSERT_TRUE(adc.Init());

    const char* input = "321\n";

    ring_buf_put(
        &adc.rx_ring_,
        reinterpret_cast<const uint8_t*>(input),
        strlen(input));

    adc.Process();

    EXPECT_TRUE(adc.HasSample());
    EXPECT_EQ(adc.PopSample(), 321);
}

TEST(AdcSourceTest, ProcessEmptyLine)
{
    AdcSource adc;

    mock_device_is_ready = true;
    mock_usb_enable_return = 0;

    ASSERT_TRUE(adc.Init());

    const char* input = "\n";

    ring_buf_put(
        &adc.rx_ring_,
        reinterpret_cast<const uint8_t*>(input),
        strlen(input));

    adc.Process();

    EXPECT_FALSE(adc.HasSample());
}

TEST(AdcSourceTest, ProcessCarriageReturn)
{
    AdcSource adc;

    mock_device_is_ready = true;
    mock_usb_enable_return = 0;

    ASSERT_TRUE(adc.Init());

    const char* input = "555,0\r";

    ring_buf_put(
        &adc.rx_ring_,
        reinterpret_cast<const uint8_t*>(input),
        strlen(input));

    adc.Process();

    EXPECT_EQ(adc.GetMonitorStatus(), MonitorStatus::Connected);
    EXPECT_EQ(adc.PopSample(), 555);
}

TEST(AdcSourceTest, ProcessVeryLongLine)
{
    AdcSource adc;

    mock_device_is_ready = true;
    mock_usb_enable_return = 0;

    ASSERT_TRUE(adc.Init());

    const char* input = "12345678901234567890\n";

    ring_buf_put(
        &adc.rx_ring_,
        reinterpret_cast<const uint8_t*>(input),
        strlen(input));

    adc.Process();

    SUCCEED();
}

TEST(AdcSourceTest, PushToFifoOverflowDropsOldest)
{
    AdcSource adc;

    for(int i = 0; i < 65; ++i)
    {
        adc.PushToFifo(i);
    }

    EXPECT_TRUE(adc.HasSample());

    EXPECT_EQ(adc.PopSample(), 1);
}

TEST(AdcSourceTest, PopSampleFromEmptyFifo)
{
    AdcSource adc;

    EXPECT_FALSE(adc.HasSample());

    EXPECT_EQ(adc.PopSample(), 0);
}

TEST(AdcSourceTest, ProcessStopsAtMaxBytesPerCall)
{
    AdcSource adc;

    mock_device_is_ready = true;
    mock_usb_enable_return = 0;

    ASSERT_TRUE(adc.Init());

    for(int i = 0; i < 80; ++i)
    {
        uint8_t c = '1';
        ring_buf_put(&adc.rx_ring_, &c, 1);
    }

    adc.Process();

    SUCCEED();
}
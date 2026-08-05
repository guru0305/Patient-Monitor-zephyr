#pragma once

struct device
{
};

extern device mock_device;

#define DEVICE_DT_GET(node) (&mock_device)

extern bool mock_device_is_ready;

inline bool device_is_ready(const device*)
{
    return mock_device_is_ready;
}
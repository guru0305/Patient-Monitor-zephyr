#pragma once

#include "model/MonitorStatus.hpp"
#include <cstdint>

class IDataSource
{
public:
    virtual uint16_t GetSample() = 0;

    virtual MonitorStatus GetMonitorStatus() const = 0;

    virtual ~IDataSource() = default;
};
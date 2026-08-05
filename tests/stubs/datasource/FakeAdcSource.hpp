#pragma once

#include <stdint.h>

#include "datasource/IDataSource.hpp"
#include "model/MonitorStatus.hpp"

class FakeAdcSource : public IDataSource
{
public:

    int process_calls = 0;

    int samples_available = 0;

    uint16_t sample = 123;

    bool Init()
    {
        return true;
    }

    void Process()
    {
        process_calls++;
    }

    bool HasSample()
    {
        return samples_available > 0;
    }

    uint16_t PopSample()
    {
        samples_available--;

        return sample;
    }

    uint16_t GetSample() override
    {
        return sample;
    }

    MonitorStatus GetMonitorStatus() const override
    {
        return MonitorStatus::Connected;
    }
};
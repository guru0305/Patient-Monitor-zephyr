#pragma once

#include <cstdint>

class IDataSource
{
public:
    virtual uint16_t GetSample() = 0;
};
#pragma once

#include "datasource/IDataSource.hpp"
#include <cstdint>

class SineWaveSource : public IDataSource
{
public:
    uint16_t GetSample() override;

private:
    uint32_t sample_index_ = 0;
};
#pragma once

#include "datasource/IDataSource.hpp"

class AdcSource : public IDataSource
{
public:
    uint16_t GetSample() override;
};
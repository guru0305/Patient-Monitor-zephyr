#pragma once

#include "observer/IObserver.hpp"

class MockObserver : public IObserver
{
public:
    int notify_count = 0;

    void notify() override
    {
        ++notify_count;
    }
};
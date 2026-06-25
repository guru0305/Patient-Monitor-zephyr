#pragma once 

#include "IObserver.hpp"
#include<cstdint>

class Subject
{
    private:
    IObserver* observer_list[10];
    uint8_t observer_count = 0;

    public:
    void attach(IObserver* observer);
    void notify_observers(); // used to noftify all observer
};
#pragma once 

class IObserver
{
    public:
     virtual void notify() = 0; // used to get notification
     virtual ~IObserver() = default;
    
};
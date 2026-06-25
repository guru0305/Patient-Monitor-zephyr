#include "observer/Subject.hpp"
#include "observer/IObserver.hpp"

void Subject::attach(IObserver* observer)
{
    observer_list[observer_count] = observer;
    observer_count++;
}

void Subject::notify_observers()
{
    for(int i=0;i<observer_count;i++)
    {
        observer_list[i]->notify();
    }
    
}
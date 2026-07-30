#include <gtest/gtest.h>

#include "observer/Subject.hpp"
#include "observer/MockObserver.hpp"

TEST(SubjectTest, NotifyWithoutObserversDoesNotCrash)
{
    Subject subject;

    subject.notify_observers();
    SUCCEED();
}

TEST(SubjectTest, NotifyOneObserver)
{
    Subject subject;
    MockObserver observer;

    subject.attach(&observer);
    subject.notify_observers();

    EXPECT_EQ(observer.notify_count, 1);
}

TEST(IObserverTest, VirtualDestructorIsExecuted)
{
    IObserver* observer = new MockObserver();

    delete observer;

    SUCCEED();
}
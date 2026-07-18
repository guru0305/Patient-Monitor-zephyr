#include <gtest/gtest.h>

#include "observer/Subject.hpp"
#include "observer/MockObserver.hpp"

TEST(SubjectTest, NotifyWithoutObserversDoesNotCrash)
{
    Subject subject;

    EXPECT_NO_THROW(subject.notify_observers());
}

TEST(SubjectTest, NotifyOneObserver)
{
    Subject subject;
    MockObserver observer;

    subject.attach(&observer);
    subject.notify_observers();

    EXPECT_EQ(observer.notify_count, 1);
}
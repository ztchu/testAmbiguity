#include "time.h"

#include <chrono>
#include <iostream>

std::chrono::milliseconds CurrentTime()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
}



void TestRunningTime()
{
    auto startClock = CurrentTime();
    for (auto i = 0; i < INT_MAX; ++i);
    auto endClock = CurrentTime();
    std::cout << endClock.count() - startClock.count() << std::endl;
}
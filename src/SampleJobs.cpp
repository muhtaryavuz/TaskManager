#include "SampleJobs.h"
#include <chrono>
#include <ctime>
#include <thread>


bool Job1::execute()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));

    return true;
}

bool Job2::execute()
{
    std::this_thread::sleep_for(std::chrono::seconds(2));

    return false;
}
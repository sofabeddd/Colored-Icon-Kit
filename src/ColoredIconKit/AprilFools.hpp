#pragma once

#include <ctime>

class AprilFools {
public:
    static bool isAprilFools();
};



bool AprilFools::isAprilFools() {
    std::time_t time;
    std::tm* local_time = std::localtime(&time);

    return (local_time->tm_mon == 2 && local_time->tm_mday == 21);
}
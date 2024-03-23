
#include "AprilFools.hpp"

bool isAprilFools() {
    std::time_t time = std::time(nullptr);
    std::tm* local_time = std::localtime(&time);

    return (local_time->tm_mon == 3 && local_time->tm_mday == 1);
}
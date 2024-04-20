#include <ctime>

#include "Utility.hpp"

bool isAprilFools() {
    std::time_t time = std::time(nullptr);
    std::tm* local_time = std::localtime(&time);

    return (local_time->tm_mon == 3 && local_time->tm_mday == 1);
}

bool variables::update_installed = false;
int variables::page_number = 0;
IconType variables::icon_type = IconType::Cube;
#pragma once

#include <Geode/Geode.hpp>

using namespace geode::prelude;

class ModSettings {
public:
    static bool centerIcons();
    static bool colorLockedIcons();
    static bool hideIconLocks();
    static bool showLockedDetail();

    static GLubyte lockOpacity();
    static GLubyte lockedIconOpacity();
};



bool ModSettings::centerIcons() {
    return Mod::get()->getSettingValue<bool>("center-icons");
}

bool ModSettings::colorLockedIcons() {
    return Mod::get()->getSettingValue<bool>("color-locked-icons");
}

bool ModSettings::hideIconLocks() {
    return Mod::get()->getSettingValue<bool>("hide-icon-locks");
}

bool ModSettings::showLockedDetail() {
    return Mod::get()->getSettingValue<bool>("show-locked-detail");
}

GLubyte ModSettings::lockOpacity() {
    return GLubyte {static_cast<unsigned char>(Mod::get()->getSettingValue<int64_t>("lock-opacity"))};
}

GLubyte ModSettings::lockedIconOpacity() {
    return GLubyte {static_cast<unsigned char>(Mod::get()->getSettingValue<int64_t>("locked-icon-opacity"))};
}
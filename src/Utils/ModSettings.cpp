#include "ModSettings.hpp"

bool ModSettings::automaticUpdates() {
    return Mod::get()->getSettingValue<bool>("automatic-updates");
}

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
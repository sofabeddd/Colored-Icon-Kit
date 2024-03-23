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
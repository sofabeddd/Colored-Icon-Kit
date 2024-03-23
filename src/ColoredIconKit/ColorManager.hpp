#pragma once

#include <random>

#include "AprilFools.hpp"

#include <Geode/Geode.hpp>

using namespace geode::prelude;

class ColorManager {
private:
    struct PlayerColorInfo {
    public:
        bool has_glow_enabled;

        ccColor3B player_color_glow;
        ccColor3B player_color_primary;
        ccColor3B player_color_secondary;
    };

    static PlayerColorInfo getPlayerColorInfo();

    static bool getRandomState();
    static ccColor3B getRandomColor();

public:
    static bool hasGlowEnabled();

    static ccColor3B getColorGlow();
    static ccColor3B getColorPrimary();
    static ccColor3B getColorSecondary();
};
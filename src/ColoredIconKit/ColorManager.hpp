#pragma once

#include <random>

#include <Geode/Geode.hpp>

#include "AprilFools.hpp"

using namespace geode::prelude;

class ColorManager {
public:
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



bool ColorManager::getRandomState() {
    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::bernoulli_distribution distribution(0.5);

    return distribution(generator);
}

ccColor3B ColorManager::getRandomColor() {
    GameManager* game_manager = GameManager::sharedState();

    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<int> distribution(0, 105);

    return game_manager->colorForIdx(distribution(generator));
}

ColorManager::PlayerColorInfo ColorManager::getPlayerColorInfo() {
    GameManager* game_manager = GameManager::sharedState();

    return PlayerColorInfo {
            (AprilFools::isAprilFools()) ? ColorManager::getRandomState() : game_manager->getPlayerGlow(),
            (AprilFools::isAprilFools()) ? ColorManager::getRandomColor() : game_manager->colorForIdx(game_manager->getPlayerGlowColor()),
            (AprilFools::isAprilFools()) ? ColorManager::getRandomColor() : game_manager->colorForIdx(game_manager->getPlayerColor()),
            (AprilFools::isAprilFools()) ? ColorManager::getRandomColor() : game_manager->colorForIdx(game_manager->getPlayerColor2())
    };
}

bool ColorManager::hasGlowEnabled() {
    return ColorManager::getPlayerColorInfo().has_glow_enabled;
}

ccColor3B ColorManager::getColorGlow() {
    return ColorManager::getPlayerColorInfo().player_color_glow;
}

ccColor3B ColorManager::getColorPrimary() {
    return ColorManager::getPlayerColorInfo().player_color_primary;
}

ccColor3B ColorManager::getColorSecondary() {
    return ColorManager::getPlayerColorInfo().player_color_secondary;
}
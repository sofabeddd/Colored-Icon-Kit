#include "ColorManager.hpp"
#include "Utility.hpp"

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
            (isAprilFools()) ? ColorManager::getRandomState() : game_manager->getPlayerGlow(),
            (isAprilFools()) ? ColorManager::getRandomColor() : game_manager->colorForIdx(game_manager->getPlayerGlowColor()),
            (isAprilFools()) ? ColorManager::getRandomColor() : game_manager->colorForIdx(game_manager->getPlayerColor()),
            (isAprilFools()) ? ColorManager::getRandomColor() : game_manager->colorForIdx(game_manager->getPlayerColor2())
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
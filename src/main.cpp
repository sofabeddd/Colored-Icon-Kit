#include <ctime>
#include <random>

#include <Geode/Geode.hpp>
#include <Geode/modify/CharacterColorPage.hpp>
#include <Geode/modify/GJGarageLayer.hpp>
#include <Geode/modify/GJItemIcon.hpp>
#include <Geode/modify/SimplePlayer.hpp>

using namespace geode::prelude;

class AprilFools {
public:
    static bool isAprilFools() {
        std::time_t t = std::time(nullptr);
        std::tm* current_time = std::localtime(&t);

        if (current_time != nullptr) {
            return current_time->tm_mon == 3 && current_time->tm_mday == 1;
        }

        return false;
    }

    static ccColor3B getRandomColor() {
        auto game_manager = GameManager::sharedState();

        return game_manager->colorForIdx(AprilFools::randomInteger(0, 105));
    }

    static int randomInteger(int min, int max) {
        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_int_distribution<int> distribution(min, max);

        return distribution(generator);
    }

    static bool randomChance(float chance) {
        float randomFloat = static_cast<float>(randomInteger(0, 100)) / 100.0f;
        return randomFloat <= chance;
    }
};


class $modify(IconKitRefresher, CharacterColorPage) {
public:
    static void refreshPage() {
        auto running_scene = CCDirector::sharedDirector()->getRunningScene();

        if (getChildOfType<GJGarageLayer>(running_scene, 0)) {
            auto garage_layer = typeinfo_cast<GJGarageLayer *>(CCDirector::sharedDirector()->getRunningScene()->getChildByID("GJGarageLayer"));

            auto prev_button = garage_layer->getChildByID("prev-page-menu")->getChildByID("prev-button");
            auto next_button = garage_layer->getChildByID("next-page-menu")->getChildByID("next-button");

            garage_layer->onArrow(prev_button);
            garage_layer->onArrow(next_button);
        }
    }

    void onClose(CCObject* sender) {
        CharacterColorPage::onClose(sender);

        IconKitRefresher::refreshPage();
    }
};

class $modify(ColoredIconKit, GJGarageLayer) {
public:
    struct PlayerColorInfo {
    public:
        bool has_glow_enabled;
        ccColor3B primary;
        ccColor3B secondary;
        ccColor3B glow;
    };

    struct ModSettings {
        bool hide_locks;
        bool color_locked_icons;
        GLubyte lock_opacity;
        GLubyte locked_icon_opacity;
        bool locked_icon_detail;
    };

    ModSettings getModSettings() {
        auto mod = Mod::get();

        return ModSettings {
            mod->getSettingValue<bool>("hide-locks"),
            mod->getSettingValue<bool>("color-locked-icons"),
            GLubyte { static_cast<unsigned char>(mod->getSettingValue<int64_t>("lock-opacity")) },
            GLubyte { static_cast<unsigned char>(mod->getSettingValue<int64_t>("locked-icon-opacity")) },
            mod->getSettingValue<bool>("locked-icon-detail")
        };
    }

    PlayerColorInfo getPlayerColorInfo() {
        auto game_manager = GameManager::sharedState();

        return ColoredIconKit::PlayerColorInfo {
            game_manager->getPlayerGlow(),
            game_manager->colorForIdx(game_manager->getPlayerColor()),
            game_manager->colorForIdx(game_manager->getPlayerColor2()),
            game_manager->colorForIdx(game_manager->getPlayerGlowColor())
        };
    }

    void hideLock(GJItemIcon* item_icon, const ModSettings& mod_settings) {
        CCObject* current_child;

        CCARRAY_FOREACH(item_icon->getChildren(), current_child) {
            auto sprite = typeinfo_cast<CCSprite*>(current_child);

            if (sprite->getZOrder() == 10) {
                sprite->setVisible(!mod_settings.hide_locks);
                sprite->setOpacity(mod_settings.lock_opacity);
                sprite->setOpacityModifyRGB(true);
            }
        }
    }

    void colorIcon(GJItemIcon* item_icon, const ModSettings& mod_settings) {
        bool is_locked = item_icon->getChildren()->count() == 2;

        auto player_color_info = getPlayerColorInfo();

        auto simple_player = getChildOfType<SimplePlayer>(item_icon, 0);
        auto sprite_primary_color = getChildOfType<CCSprite>(simple_player, 0);
        auto sprite_secondary_color = getChildOfType<CCSprite>(sprite_primary_color, 0);
        auto sprite_glow_color = getChildOfType<CCSprite>(sprite_primary_color, -2);

        if (is_locked) {
            sprite_primary_color->setOpacity(mod_settings.locked_icon_opacity);
            CCObject* current_child;

            CCARRAY_FOREACH(sprite_primary_color->getChildren(), current_child) {
                auto sprite = typeinfo_cast<CCSprite*>(current_child);

                sprite->setOpacity(mod_settings.hide_locks);

                if (mod_settings.locked_icon_detail) {
                    if (sprite->getZOrder() == -3) continue;
                    if (sprite->boundingBox().size != CCSize { 6.5f, 6.5f }) sprite->setVisible(true);
                }
            }

            if (mod_settings.locked_icon_detail) {
                CCARRAY_FOREACH(sprite_primary_color->getChildren(), current_child) {
                    auto sprite = typeinfo_cast<CCSprite*>(current_child);

                    if (sprite->getZOrder() == -3) continue;
                    if (sprite->boundingBox().size != CCSize { 6.5f, 6.5f }) sprite->setVisible(true);
                }
            }

            if (!mod_settings.color_locked_icons) return;
        }

        sprite_glow_color->setVisible(player_color_info.has_glow_enabled);
        sprite_primary_color->setColor(player_color_info.primary);
        sprite_secondary_color->setColor(player_color_info.secondary);
        sprite_glow_color->setColor(player_color_info.glow);
    }

    void colorRobot(GJItemIcon* item_icon) {

    }

    void colorSpider(GJItemIcon* item_icon) {

    }

    void colorIconPage(IconType icon_type, CCArray* icon_array) {

        CCObject* current_child;
        CCARRAY_FOREACH(icon_array, current_child) {
            auto menu_item = typeinfo_cast<CCMenuItemSpriteExtra*>(current_child);
            auto item_icon = getChildOfType<GJItemIcon>(menu_item, 0);

            if (getModSettings().hide_locks) hideLock(item_icon, getModSettings());

            switch (icon_type) {
                case IconType::Robot:
                    ColoredIconKit::colorRobot(item_icon);
                    break;

                case IconType::Spider:
                    ColoredIconKit::colorSpider(item_icon);
                    break;

                case IconType::DeathEffect:
                    break;

                case IconType::Special:
                    break;

                default:
                    ColoredIconKit::colorIcon(item_icon, getModSettings());
                    break;
            }
        }
    }

    static void onModify(auto& self) {
        (void) self.setHookPriority("GJGarageLayer::setupPage", -10000);
    }

    void setupPage(int pageNumber, IconType iconType) {
        GJGarageLayer::setupPage(pageNumber, iconType);

        auto list_button_bar = getChildOfType<ListButtonBar>(this, 0);
        auto boom_scroll_layer = getChildOfType<BoomScrollLayer>(list_button_bar, 0);
        auto extended_layer = getChildOfType<ExtendedLayer>(boom_scroll_layer, 0);
        auto list_button_page = getChildOfType<ListButtonPage>(extended_layer, 0);
        auto menu = getChildOfType<CCMenu>(list_button_page, 0);

        auto icons = menu->getChildren();

        ColoredIconKit::colorIconPage(iconType, icons);
    }
};
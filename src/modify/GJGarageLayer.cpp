#include <Geode/modify/GJGarageLayer.hpp>
#include <Geode/loader/Index.hpp>

#include "../ui/popups/Changelog.hpp"
#include "../utils/Utility.hpp"

using namespace geode::prelude;

class $modify(GJGarageLayer) {
public:
    bool init() {
        if (!GJGarageLayer::init()) return false;

        #ifdef GEODE_IS_MACOS
        if (!Mod::get()->setSavedValue("shown-mac-disclaimer", true)) {
            auto macos_alert = FLAlertLayer::create(
                    "Colored Icon Kit",
                    "You appear to be on <cg>Mac OS</c>, which this mod does <cr>not fully support</c>.\n\nYou can still preview your colors here, but they will not live update when changed; you will have to exit and re-enter the icon kit for those changes to take place.",
                    "OK"
            );

            macos_alert->m_scene = this;
            macos_alert->show();
        }
        #endif

        if (Mod::get()->hasAvailableUpdate()) {

        }

        if (!Mod::get()->setSavedValue("shown-changelog-" + Mod::get()->getVersion().toString(), true)) {
            auto changelog_popup = Changelog::create();

            changelog_popup->m_scene = this;
            changelog_popup->show();
        }

        return true;
    }

    void setupPage(int p0, IconType p1) {
        GJGarageLayer::setupPage(variables::page_number = p0, variables::icon_type = p1);
    }
};

#include "UI/ChangelogPopup.hpp"

#include <Geode/modify/CharacterColorPage.hpp>
#include <Geode/modify/GJGarageLayer.hpp>

using namespace geode::prelude;

int page_number;
IconType icon_type;

class $modify(CharacterColorPage) {
    #ifndef GEODE_IS_MACOS
    void onClose(CCObject* sender) {
        CharacterColorPage::onClose(sender);

        auto garage_layer = typeinfo_cast<GJGarageLayer*>(CCDirector::sharedDirector()->getRunningScene()->getChildByID("GJGarageLayer"));
        garage_layer->setupPage(page_number, icon_type);
    }
    #endif
};

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

        auto changelog_popup = ChangelogPopup::create();

        changelog_popup->m_scene = this;
        changelog_popup->show();

        return true;
    }

    void setupPage(int p0, IconType p1) {
        GJGarageLayer::setupPage(page_number = p0, icon_type = p1);
    }
};
#include <Geode/Geode.hpp>
#include <Geode/modify/CharacterColorPage.hpp>

#include "../utils/Utility.hpp"

using namespace geode::prelude;

class $modify(CharacterColorPage) {
    #ifndef GEODE_IS_MACOS
    void onClose(CCObject* sender) {
        CharacterColorPage::onClose(sender);

        auto garage_layer = typeinfo_cast<GJGarageLayer*>(CCDirector::sharedDirector()->getRunningScene()->getChildByID("GJGarageLayer"));
        garage_layer->setupPage(variables::page_number, variables::icon_type);
    }
    #endif
};
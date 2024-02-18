#include <Geode/Geode.hpp>

#include <Geode/modify/CharacterColorPage.hpp>
#include <Geode/modify/GJItemIcon.hpp>
#include <Geode/modify/SimplePlayer.hpp>

using namespace geode::prelude;

class $modify(SimplePlayer) {
    bool init(int p0) {
        if (!SimplePlayer::init(p0)) return false;

        auto game_manager = GameManager::get();
        if (game_manager->getPlayerGlow()) this->setGlowOutline(game_manager->colorForIdx(game_manager->getPlayerGlowColor()));

        return true;
    }
};

class $modify(GJItemIcon) {
    static GJItemIcon* create(UnlockType p0, int p1, cocos2d::ccColor3B p2, cocos2d::ccColor3B p3, bool p4, bool p5, bool p6, cocos2d::ccColor3B p7) {
        auto game_manager = GameManager::get();
        return GJItemIcon::create(p0, p1, game_manager->colorForIdx(game_manager->getPlayerColor()), game_manager->colorForIdx(game_manager->getPlayerColor2()), false, true, true, game_manager->colorForIdx(game_manager->getPlayerGlowColor()));

    }
};

class $modify(CharacterColorPage) {
    void onClose(CCObject* sender) {
        CharacterColorPage::onClose(sender);

        auto garage_layer = dynamic_cast<GJGarageLayer*>(CCDirector::sharedDirector()->getRunningScene()->getChildByID("GJGarageLayer"));

        auto prev_button = garage_layer->getChildByID("prev-page-menu")->getChildByID("prev-button");
        auto next_button = garage_layer->getChildByID("next-page-menu")->getChildByID("next-button");

        garage_layer->onArrow(prev_button);
        garage_layer->onArrow(next_button);
    }
};

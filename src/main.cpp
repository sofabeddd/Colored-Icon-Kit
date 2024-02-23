#include <Geode/Geode.hpp>

#include <Geode/modify/CharacterColorPage.hpp>
#include <Geode/modify/CreatorLayer.hpp>
#include <Geode/modify/GJGarageLayer.hpp>
#include <Geode/modify/GJItemIcon.hpp>
#include <Geode/modify/InfoLayer.hpp>
#include <Geode/modify/LeaderboardsLayer.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>
#include <Geode/modify/LevelLeaderboard.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/ProfilePage.hpp>
#include <Geode/modify/SimplePlayer.hpp>

using namespace geode::prelude;

bool override_glow = true;

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

class $modify(CreatorLayer) {
    void onTreasureRoom(CCObject* sender) {
        CreatorLayer::onTreasureRoom(sender);

        override_glow = true;
    }
};

class $modify(GJGarageLayer) {
    void onBack(CCObject* sender) {
        GJGarageLayer::onBack(sender);

        override_glow = true;
    }
};


class $modify(GJItemIcon) {
    static GJItemIcon* create(UnlockType p0, int p1, cocos2d::ccColor3B p2, cocos2d::ccColor3B p3, bool p4, bool p5, bool p6, cocos2d::ccColor3B p7) {
        auto game_manager = GameManager::get();
        return GJItemIcon::create(p0, p1, game_manager->colorForIdx(game_manager->getPlayerColor()), game_manager->colorForIdx(game_manager->getPlayerColor2()), p4, p5, p6, p7);

    }
};

class $modify(InfoLayer) {
    bool init(GJGameLevel* p0, GJUserScore* p1, GJLevelList* p2) {
        if (!InfoLayer::init(p0, p1, p2)) return false;

        override_glow = false;
        return true;
    }

    void onClose(CCObject* sender) {
        InfoLayer::onClose(sender);

        override_glow = true;
    }
};

class $modify(LeaderboardsLayer) {
    bool init(LeaderboardState p0) {
        if (!LeaderboardsLayer::init(p0)) return false;

        override_glow = false;
        return true;
    }
};

class $modify(LevelInfoLayer) {
    bool init(GJGameLevel* p0, bool p1) {
        if (!LevelInfoLayer::init(p0, p1)) return false;

        override_glow = true;
        return true;
    }

    void onBack(CCObject* sender) {
        LevelInfoLayer::onBack(sender);

        override_glow = false;
    }
};

class $modify(LevelLeaderboard) {
    bool init(GJGameLevel* p0, LevelLeaderboardType p1, LevelLeaderboardMode p2) {
        if (!LevelLeaderboard::init(p0, p1, p2)) return false;

        override_glow = false;
        return true;
    }

    void onClose(CCObject* sender) {
        LevelLeaderboard::onClose(sender);

        override_glow = true;
    }
};

class $modify(MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        override_glow = true;
        return true;
    }
};

class $modify(ProfilePage) {
    bool init(int accountID, bool ownProfile) {
        if (!ProfilePage::init(accountID, ownProfile)) return false;

        override_glow = false;
        return true;
    }

    void onClose(CCObject* sender) {
        ProfilePage::onClose(sender);

        auto running_scene = CCDirector::sharedDirector()->getRunningScene();
        if (m_ownProfile) override_glow = true;
    }

    void onFriends(CCObject* sender) {
        ProfilePage::onFriends(sender);

        override_glow = false;
    }

    void onRequests(CCObject* sender) {
        ProfilePage::onRequests(sender);

        override_glow = false;
    }

};

class $modify(SimplePlayer) {
    bool init(int p0) {
        if (!SimplePlayer::init(p0)) return false;

        auto game_manager = GameManager::get();

        if (override_glow) {
            setGlowOutline(game_manager->colorForIdx(game_manager->getPlayerGlowColor()));
        }

        return true;
    }
};

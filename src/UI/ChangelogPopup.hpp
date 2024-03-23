#pragma once

#include <fstream>
#include <sstream>

#include <Geode/Geode.hpp>
#include <Geode/utils/web.hpp>

using namespace geode::prelude;

class ChangelogPopup : public Popup<> {
    bool setup() override;
    void onClose(CCObject* sender) override;

    gd::string getChangelogData();

public:
    static ChangelogPopup* create();

    void onBuyMeACoffee(CCObject* sender);
    void onDiscord(CCObject* sender);
    void onGeometryDash(CCObject* sender);
    void onGitHub(CCObject* sender);
    void onYouTube(CCObject* sender);
};
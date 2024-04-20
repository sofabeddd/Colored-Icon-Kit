#pragma once

#include <fstream>
#include <sstream>

#include <Geode/Geode.hpp>
#include <Geode/utils/web.hpp>

using namespace geode::prelude;

class Changelog : public Popup<> {
protected:
    bool setup() override;
    void onClose(CCObject* sender) override;

    gd::string getChangelogData();

public:
    static Changelog* create();

    void onBuyMeACoffee(CCObject* sender);
    void onDiscord(CCObject* sender);
    void onGeometryDash(CCObject* sender);
    void onGitHub(CCObject* sender);
    void onYouTube(CCObject* sender);
};
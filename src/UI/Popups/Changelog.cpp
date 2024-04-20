
#include "Changelog.hpp"

bool Changelog::setup() {
    this->m_noElasticity = true;

    auto game_manager = GameManager::sharedState();

    setID("Changelog");
    setTitle(Mod::get()->getName() + " | Changelog");

    this->m_title->setPosition(this->m_title->getPosition() - CCPoint { 0.f, 3.f });
    this->m_closeBtn->setPosition(CCPoint { 12.f, this->m_buttonMenu->boundingBox().getMaxY() - 12.f });

    auto changelog = MDTextArea::create(getChangelogData(), CCSize { 350.f,  200.f });
    auto scrollbar = Scrollbar::create(changelog->getScrollLayer());
    auto developer_info = CCLabelBMFont::create(("developed by " + Mod::get()->getDevelopers()[0]).c_str(), "bigFont.fnt");
    auto socials_menu = CCMenu::create();

    socials_menu->setAnchorPoint(this->m_buttonMenu->getAnchorPoint());

    changelog->setPosition(this->boundingBox().getMidX() - 6.f, this->boundingBox().getMidY() + 7.f);
    scrollbar->setPosition(changelog->boundingBox().getMaxX() + 16.f, changelog->boundingBox().getMidY());
    developer_info->setPosition(this->boundingBox().getMidX(), changelog->boundingBox().getMinY() - 12.5f);
    socials_menu->setPosition(this->boundingBox().getMidX(), changelog->boundingBox().getMinY() - 35.f);

    typeinfo_cast<CCScale9Sprite*>(scrollbar->getChildren()->objectAtIndex(0))->setOpacity(GLubyte { 75 });
    developer_info->setScale(0.375f);

    this->addChild(changelog);
    this->addChild(scrollbar);
    this->addChild(developer_info);

    auto buymeacoffee_icon = CCSprite::create("buymeacoffee.png"_spr);
    auto discord_icon = CCSprite::createWithSpriteFrameName("gj_discordIcon_001.png");
    auto geometrydash_icon = GJItemIcon::create(UnlockType::Cube, 35, game_manager->colorForIdx(33), game_manager->colorForIdx(40), false, false, false, game_manager->colorForIdx(40));
    auto github_icon = CCSprite::createWithSpriteFrameName("geode.loader/github.png");
    auto youtube_icon = CCSprite::createWithSpriteFrameName("gj_ytIcon_001.png");

    auto simple_player = getChildOfType<SimplePlayer>(geometrydash_icon, 0);
    auto player_sprite = getChildOfType<CCSprite>(simple_player, 0);
    auto glow_sprite =  getChildOfType<CCSprite>(player_sprite, -2);

    glow_sprite->setVisible(true);
    glow_sprite->setColor(game_manager->colorForIdx(12));

    float button_scale = 0.75f;

    buymeacoffee_icon->setScale(button_scale);
    discord_icon->setScale(button_scale);
    geometrydash_icon->setScale(button_scale);
    github_icon->setScale(button_scale);
    youtube_icon->setScale(button_scale);

    CCMenuItemSpriteExtra* social_buttons[] = {
            CCMenuItemSpriteExtra::create(
                    buymeacoffee_icon, socials_menu,
                    menu_selector(Changelog::onBuyMeACoffee)
            ),
            CCMenuItemSpriteExtra::create(
                    discord_icon, socials_menu,
                    menu_selector(Changelog::onDiscord)
            ),
            CCMenuItemSpriteExtra::create(
                    geometrydash_icon, socials_menu,
                    menu_selector(Changelog::onGeometryDash)
            ),
            CCMenuItemSpriteExtra::create(
                    github_icon, socials_menu,
                    menu_selector(Changelog::onGitHub)
            ),
            CCMenuItemSpriteExtra::create(
                    youtube_icon, socials_menu,
                    menu_selector(Changelog::onYouTube)
            )
    };

    socials_menu->setContentSize(CCSize { 200.f, 20.f });
    socials_menu->alignItemsHorizontallyWithPadding(10.f);

    float position = -75.f * (button_scale + 0.5f);

    for (auto button : social_buttons) {
        socials_menu->addChild(button);
        button->setPosition(position += 25.f * (button_scale + 0.5f), 0.f);
    }

    socials_menu->updateLayout(true);
    this->addChild(socials_menu);

    return true;
}

void Changelog::onClose(CCObject* sender) {
    Popup::onClose(sender);
}

gd::string Changelog::getChangelogData() {
    std::ifstream changelog_file(Mod::get()->getBinaryPath().parent_path() / "changelog.md");
    std::ostringstream latest_changes;

    if (changelog_file) {
        latest_changes << changelog_file.rdbuf();
    }

    else {
        latest_changes << "## <cr>failed to open changelog file</c>";
    }

    return latest_changes.str();
}

Changelog* Changelog::create() {
    auto ret = new Changelog;
    if (ret->initAnchored(400.f, 300.f)) {
        ret->autorelease();

        return ret;
    }

    CC_SAFE_DELETE(ret);
    return nullptr;
}

void Changelog::onBuyMeACoffee(cocos2d::CCObject*) {
    web::openLinkInBrowser("https://www.buymeacoffee.com/sofabeddd");
}

void Changelog::onDiscord(cocos2d::CCObject*) {
    web::openLinkInBrowser("https://discordapp.com/users/560247410522324993");
}

void Changelog::onGeometryDash(cocos2d::CCObject*) {
    auto profile = ProfilePage::create(7976112, false);
    profile->show();
}

void Changelog::onGitHub(cocos2d::CCObject*) {
    web::openLinkInBrowser("https://github.com/sofabeddd");
}

void Changelog::onYouTube(cocos2d::CCObject*) {
    web::openLinkInBrowser("https://www.youtube.com/@sofabeddd?sub_confirmation=1");
}
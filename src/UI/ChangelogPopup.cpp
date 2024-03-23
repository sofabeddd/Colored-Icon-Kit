
#include "ChangelogPopup.hpp"

bool ChangelogPopup::setup() {
    this->m_noElasticity = true;

    setID("ChangelogPopup");
    setTitle("Colored Icon Kit | Changelog");

    this->m_title->setPosition(this->m_title->getPosition() - CCPoint { 0.f, 3.f });
    this->m_closeBtn->setPosition(CCPoint { 12.f, this->m_buttonMenu->boundingBox().getMaxY() - 12.f });

    auto changelog = MDTextArea::create(getChangelogData(), CCSize { 350.f,  200.f });
    auto scrollbar = Scrollbar::create(changelog->getScrollLayer());
    auto developer_info = CCLabelBMFont::create("developed by sofabeddd", "bigFont.fnt");
    auto socials_menu = CCMenu::create();

    socials_menu->setAnchorPoint(this->m_buttonMenu->getAnchorPoint());

    changelog->setPosition(this->boundingBox().getMidX() - 6.f, this->boundingBox().getMidY() + 7.f);
    scrollbar->setPosition(changelog->boundingBox().getMaxX() + 16.f, changelog->boundingBox().getMidY());
    developer_info->setPosition(this->boundingBox().getMidX(), changelog->boundingBox().getMinY() - 10.f);
    socials_menu->setPosition(this->boundingBox().getMidX(), changelog->boundingBox().getMinY() - 30.f);

    typeinfo_cast<CCScale9Sprite*>(scrollbar->getChildren()->objectAtIndex(0))->setOpacity(GLubyte { 75 });
    developer_info->setScale(0.375f);

    this->addChild(changelog);
    this->addChild(scrollbar);
    this->addChild(developer_info);
    this->addChild(socials_menu);

    auto buymeacoffee_button = CCMenuItemSpriteExtra::create(
            CCSprite::create("buymeacoffee.png"), socials_menu,
            menu_selector(ChangelogPopup::onBuyMeACoffee)
    );

    socials_menu->addChild(buymeacoffee_button);

    socials_menu->updateLayout();
    
    return true;
}

void ChangelogPopup::onClose(CCObject* sender) {
    Popup::onClose(sender);
}

gd::string ChangelogPopup::getChangelogData() {
    std::ifstream changelog_file(Mod::get()->getResourcesDir() / "changelog.md");
    std::ostringstream latest_changes;

    if (changelog_file) {
        latest_changes << changelog_file.rdbuf();
    }

    else {
        latest_changes << "<cr>failed to open changelog file</c>";
    }

    return latest_changes.str();
}

ChangelogPopup* ChangelogPopup::create() {
    auto ret = new ChangelogPopup;
    if (ret->initAnchored(400.f, 300.f)) {
        ret->autorelease();

        return ret;
    }

    CC_SAFE_DELETE(ret);
    return nullptr;
}

void ChangelogPopup::onBuyMeACoffee(cocos2d::CCObject*) {
    web::openLinkInBrowser("https://www.buymeacoffee.com/sofabeddd");
}

void ChangelogPopup::onDiscord(cocos2d::CCObject *sender) {
    web::openLinkInBrowser("https://discordapp.com/users/560247410522324993");
}

void ChangelogPopup::onGeometryDash(cocos2d::CCObject *sender) {
    web::openLinkInBrowser("user:7976112");
}

void ChangelogPopup::onGitHub(cocos2d::CCObject *sender) {
    web::openLinkInBrowser("https://github.com/sofabeddd");
}

void ChangelogPopup::onYouTube(cocos2d::CCObject *sender) {
    web::openLinkInBrowser("https://www.youtube.com/@sofabeddd?sub_confirmation=1");
}
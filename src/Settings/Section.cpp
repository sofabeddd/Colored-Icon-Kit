#include "Section.hpp"

#include <utility>

SectionValue::SectionValue(const std::string& key, const std::string& modID, std::string placeholder) :
        SettingValue(key, modID),
        m_placeholder(std::move(placeholder)) {}


bool SectionValue::load(const matjson::Value& json) {
    return true;
}

bool SectionValue::save(matjson::Value& json) const {
    return true;
}

SettingNode* SectionValue::createNode(float width) {
    return SectionNode::create(this, width);
}



bool SectionNode::init(SectionValue* value, float width) {
    if (!SettingNode::init(value)) return false;

    this->setContentSize({ width, 40.f });

    auto section_name = Mod::get()->getSettingDefinition(value->getKey())->get<CustomSetting>()->json->get<std::string>("name");
    auto section_text = CCLabelBMFont::create(section_name.c_str(), "goldFont.fnt");

    section_text->setPosition({ this->boundingBox().getMidX(), this->boundingBox().getMidY() });
    this->addChild(section_text);

    return true;
}

void SectionNode::commit() {
    this->dispatchCommitted();
}

void SectionNode::resetToDefault() {}

bool SectionNode::hasNonDefaultValue() {
    return true;
}

bool SectionNode::hasUncommittedChanges() {
    return false;
}

SectionNode* SectionNode::create(SectionValue* value, float width) {
    auto ret = new SectionNode;

    if (ret->init(value, width)) {
        ret->autorelease();
        return ret;
    }

    CC_SAFE_DELETE(ret);
    return nullptr;
}
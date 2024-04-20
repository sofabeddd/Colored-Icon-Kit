#pragma once
#include <Geode/Geode.hpp>
#include <Geode/loader/SettingNode.hpp>

using namespace geode::prelude;

class SectionValue : public SettingValue {
protected:
    std::string m_placeholder;

public:
    SectionValue(const std::string& key, const std::string& modID, std::string placeholder);

    bool load(const matjson::Value& json) override;
    bool save(matjson::Value& json) const override;

    SettingNode* createNode(float width) override;
};

class SectionNode : public SettingNode {
protected:
    bool init(SectionValue* value, float width);

public:
    static SectionNode* create(SectionValue* value, float width);

    void commit() override;
    void resetToDefault() override;

    bool hasNonDefaultValue() override;
    bool hasUncommittedChanges() override;
};

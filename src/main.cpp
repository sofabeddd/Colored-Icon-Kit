#include <Geode/Geode.hpp>
#include <Geode/loader/Index.hpp>

#include "utils/ModSettings.hpp"
#include "utils/Utility.hpp"

using namespace geode::prelude;

$on_mod(Loaded) {
    if (!Mod::get()->hasAvailableUpdate() || !ModSettings::automaticUpdates()) return;

    auto index = Index::get();
    auto mod = index->getItem(Mod::get());

    if (index->canInstall(mod).isOk()) {
        Notification::create(Mod::get()->getName() + " | Installing Update")->show();

        EventListener<ModInstallFilter>(MiniFunction<EventListener<ModInstallFilter>::Callback>([](ModInstallEvent* event) {
            if (std::holds_alternative<UpdateFinished>(event->status)) {
                Notification::create(Mod::get()->getName() + " | Update Installed")->show();
                variables::update_installed = true;
            }
        }), ModInstallFilter(Mod::get()->getID()));

        index->install(mod);
    }

    else {
        Notification::create(Mod::get()->getName() + " | Update Failed")->show();
    }
}
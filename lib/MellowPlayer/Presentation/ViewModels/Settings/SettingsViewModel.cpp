#include "SettingsViewModel.hpp"

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Presentation;

SettingsViewModel::SettingsViewModel(Settings& settings, ThemeViewModel& themeViewModel, QObject* parent)
        : QObject(parent), settings(settings), settingViewModelFactory(themeViewModel), categories(new SettingsCategoryListModel(this, "name"))
{
    for (SettingsCategory* category : settings.getCategories()) {
        if (category->getKey() != "private")
            categories->append(new SettingsCategoryViewModel(themeViewModel, category, this));
    }
    categories->append(new CustomSettingsCategoryViewModel(
            tr("Services"), u8"\ue405", "qrc:/MellowPlayer/Presentation/Views/MellowPlayer/SettingsPages/ServiceSettingsPage.qml",
            themeViewModel, this));
    categories->append(new CustomSettingsCategoryViewModel(
            tr("Cache"), u8"\ue872", "qrc:/MellowPlayer/Presentation/Views/MellowPlayer/SettingsPages/CacheSettingsPage.qml",
            themeViewModel, this));
}

SettingViewModel* SettingsViewModel::get(int key)
{
    SettingKey::Keys settingKey = static_cast<SettingKey::Keys>(key);
    Setting& setting = settings.get(settingKey);
    return settingViewModelFactory.create(setting, nullptr);
}

SettingsCategoryListModel* SettingsViewModel::getCategories() const
{
    return categories;
}

void SettingsViewModel::restoreDefaults()
{
    settings.restoreDefaults();
}

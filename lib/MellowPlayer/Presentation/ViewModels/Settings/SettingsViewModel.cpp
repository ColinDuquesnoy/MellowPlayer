#include "SettingsViewModel.hpp"
#include <MellowPlayer/Domain/Settings/Settings.hpp>
#include <MellowPlayer/Domain/Settings/SettingsCategory.hpp>


using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;

SettingsViewModel::SettingsViewModel(Settings& settings, ThemeViewModel& themeViewModel, QObject* parent)
        : QObject(parent), settings_(settings), factory_(themeViewModel), categories_(new SettingsCategoryListModel(this, "name"))
{
    for (SettingsCategory* category : settings.categories()) {
        if (category->key() != "private")
            categories_->append(new SettingsCategoryViewModel(themeViewModel, category, this));
    }
    categories_->append(new CustomSettingsCategoryViewModel(
    "Services", u8"\ue405", "qrc:/MellowPlayer/Presentation/Views/MellowPlayer/SettingsPages/ServiceSettingsPage.qml", themeViewModel, this));
    categories_->append(new CustomSettingsCategoryViewModel(
    "Cache", u8"\ue872", "qrc:/MellowPlayer/Presentation/Views/MellowPlayer/SettingsPages/CacheSettingsPage.qml", themeViewModel, this));
}

SettingViewModel* SettingsViewModel::get(int key)
{
    SettingKey::Keys settingKey = static_cast<SettingKey::Keys>(key);
    Setting& setting = settings_.get(settingKey);
    return factory_.create(setting, nullptr);
}

SettingsCategoryListModel* SettingsViewModel::categories() const
{
    return categories_;
}

void SettingsViewModel::restoreDefaults()
{
    settings_.restoreDefaults();
}

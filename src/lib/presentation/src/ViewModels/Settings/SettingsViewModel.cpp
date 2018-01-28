#include <MellowPlayer/Presentation/ViewModels/Settings/SettingsViewModel.hpp>
#include <MellowPlayer/Domain/Settings/Settings.hpp>
#include <MellowPlayer/Domain/Settings/SettingsCategory.hpp>
#include <QtQml/QtQml>


using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;

SettingsViewModel::SettingsViewModel(Settings& settings,
                                     ThemeViewModel& themeViewModel,
                                     IContextProperties& contextProperties)
        : ContextProperty("_settings", this, contextProperties),
          settings_(settings),
          factory_(themeViewModel),
          categories_(new SettingsCategoryListModel(this, "name"))
{
    for (SettingsCategory* category : settings.categories()) {
        if (category->key() != "private")
            categories_->append(new SettingsCategoryViewModel(themeViewModel, category, this));
    }
    categories_->append(new CustomSettingsCategoryViewModel(
    "Streaming Services", u8"\ue405", "SettingsPages/ServiceSettingsPage.qml", themeViewModel, this));
    categories_->append(new CustomSettingsCategoryViewModel(
    "Cache", u8"\ue872", "SettingsPages/CacheSettingsPage.qml", themeViewModel, this));
}

SettingViewModel* SettingsViewModel::get(int key)
{
    SettingKey::Keys settingKey = static_cast<SettingKey::Keys>(key);
    Setting& setting = settings_.get(settingKey);
    return factory_.create(setting, this);
}

SettingsCategoryListModel* SettingsViewModel::categories() const
{
    return categories_;
}

void SettingsViewModel::restoreDefaults()
{
    settings_.restoreDefaults();
}

void SettingsViewModel::initialize(IQmlApplicationEngine& qmlApplicationEngine)
{
    qmlRegisterUncreatableType<SettingKey>("MellowPlayer", 3, 0, "SettingKey", "SettingKey cannot be instantiated from QML");
    ContextProperty::initialize(qmlApplicationEngine);
}

#include <MellowPlayer/Presentation/ViewModels/Settings/SettingsCategoryViewModel.hpp>
#include <MellowPlayer/Domain/Settings/SettingsCategory.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;

SettingsCategoryViewModel::SettingsCategoryViewModel(ThemeViewModel& themeViewModel, SettingsCategory* settingsCategory, QObject* parent)
        : QObject(parent),
          settingsCategory_(settingsCategory),
          settingsListModel_(new SettingListModel(this, "name")),
          settingViewModelFactory_(themeViewModel)
{
    if (settingsCategory != nullptr)
        for (Setting* setting : settingsCategory->toList())
            settingsListModel_->append(settingViewModelFactory_.create(*setting, this));
}

QString SettingsCategoryViewModel::name() const
{
    return settingsCategory_ != nullptr ? settingsCategory_->name() : "";
}

QString SettingsCategoryViewModel::icon() const
{
    return settingsCategory_ != nullptr ? settingsCategory_->icon() : "";
}

QString SettingsCategoryViewModel::qmlComponent() const
{
    return "SettingsPages/AutomaticSettingsPage.qml";
}

SettingListModel* SettingsCategoryViewModel::settingsModel()
{
    return settingsListModel_;
}

void SettingsCategoryViewModel::restoreDefaults()
{
    settingsCategory_->restoreDefaults();
}

CustomSettingsCategoryViewModel::CustomSettingsCategoryViewModel(const QString& name, const QString& icon, const QString& qmlComponent,
                                                                 ThemeViewModel& themeViewModel, QObject* parent)
        : SettingsCategoryViewModel(themeViewModel, nullptr, parent), name_(name), icon_(icon), qmlComponent_(qmlComponent)
{
}

QString CustomSettingsCategoryViewModel::name() const
{
    return name_;
}

QString CustomSettingsCategoryViewModel::icon() const
{
    return icon_;
}

QString CustomSettingsCategoryViewModel::qmlComponent() const
{
    return qmlComponent_;
}

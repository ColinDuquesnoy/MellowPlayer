#include "ThemeViewModel.hpp"
#include <MellowPlayer/Domain/Settings/Setting.hpp>
#include <MellowPlayer/Domain/Settings/Settings.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingService.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingServicesController.hpp>
#include <MellowPlayer/Domain/Theme/IThemeLoader.hpp>

#include <QDebug>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;

ThemeViewModel::ThemeViewModel(StreamingServicesController& streamingServices, Settings& settings, IThemeLoader& themeLoader)
        : streamingServices_(streamingServices),
          loader_(themeLoader),
          accentColorSetting_(settings.get(SettingKey::APPEARANCE_ACCENT)),
          themeSetting_(settings.get(SettingKey::APPEARANCE_THEME)),
          backgroundSetting_(settings.get(SettingKey::APPEARANCE_BACKGROUND)),
          foregroundSetting_(settings.get(SettingKey::APPEARANCE_FOREGROUND)),
          primaryBackgroundSetting_(settings.get(SettingKey::APPEARANCE_PRIMARY_BACKGROUND)),
          primaryForegroundSetting_(settings.get(SettingKey::APPEARANCE_PRIMARY_FOREGROUND)),
          secondaryBackgroundSetting_(settings.get(SettingKey::APPEARANCE_SECONDARY_BACKGROUND)),
          secondaryForegroundSetting_(settings.get(SettingKey::APPEARANCE_SECONDARY_FOREGROUND)),
          currentTheme_(customTheme())
{
    connect(&streamingServices, &StreamingServicesController::currentChanged, this, &ThemeViewModel::onCurrentServiceChanged);
    connect(&accentColorSetting_, &Setting::valueChanged, this, &ThemeViewModel::update);
    connect(&themeSetting_, &Setting::valueChanged, this, &ThemeViewModel::update);
    connect(&backgroundSetting_, &Setting::valueChanged, this, &ThemeViewModel::update);
    connect(&foregroundSetting_, &Setting::valueChanged, this, &ThemeViewModel::update);
    connect(&primaryBackgroundSetting_, &Setting::valueChanged, this, &ThemeViewModel::update);
    connect(&primaryForegroundSetting_, &Setting::valueChanged, this, &ThemeViewModel::update);
    connect(&secondaryBackgroundSetting_, &Setting::valueChanged, this, &ThemeViewModel::update);
    connect(&secondaryForegroundSetting_, &Setting::valueChanged, this, &ThemeViewModel::update);
    connect(&streamingServices, &StreamingServicesController::added, this, &ThemeViewModel::onServiceAdded);

    collectThemes();
    update();
}

bool ThemeViewModel::isDark() const
{
    return isDark(currentTheme_.background);
}

QString ThemeViewModel::accent() const
{
    return currentTheme_.accent;
}

QString ThemeViewModel::background() const
{
    return currentTheme_.background;
}

QString ThemeViewModel::foreground() const
{
    return currentTheme_.foreground;
}

QString ThemeViewModel::primary() const
{
    return currentTheme_.primary;
}

QString ThemeViewModel::primaryForeground() const
{
    return currentTheme_.primaryForeground;
}

QString ThemeViewModel::secondary() const
{
    return currentTheme_.secondary;
}

QString ThemeViewModel::secondaryForeground() const
{
    return currentTheme_.secondaryForeground;
}

void ThemeViewModel::update()
{
    StreamingService* currentService = streamingServices_.current();
    QString current = themeSetting_.value().toString();
    if (currentService != nullptr && isAdaptiveTheme() && !currentService->theme().isEmpty()) {
        Theme theme = currentService->theme();
        availableThemes_["Adaptive"] = theme;
        fromTheme(theme);
    } else if (isAdaptiveTheme())
        fromTheme(availableThemes_["Default"]);
    else if (current == "Custom")
        fromTheme(customTheme());
    else
        fromTheme(availableThemes_[current]);
}

bool ThemeViewModel::isAdaptiveTheme() const
{
    return themeSetting_.value().toString() == "Adaptive";
}

void ThemeViewModel::onCurrentServiceChanged(StreamingService* streamingService)
{
    connect(streamingService, &StreamingService::themeChanged, this, &ThemeViewModel::update, Qt::UniqueConnection);

    if (streamingService != nullptr)
        update();
}

void ThemeViewModel::setAccent(const QString& value)
{
    if (value == currentTheme_.accent)
        return;

    currentTheme_.accent = value;
    emit accentChanged();
}

void ThemeViewModel::setBackground(const QString& value)
{
    if (value == currentTheme_.background)
        return;

    currentTheme_.background = value;
    emit backgroundChanged();
    emit isDarkChanged();
}

void ThemeViewModel::setForeground(const QString& value)
{
    if (value == currentTheme_.foreground)
        return;

    currentTheme_.foreground = value;
    emit foregroundChanged();
}

void ThemeViewModel::setPrimary(const QString& value)
{
    if (value == currentTheme_.primary)
        return;

    currentTheme_.primary = value;
    emit primaryChanged();
}

void ThemeViewModel::setPrimaryForeground(const QString& value)
{
    if (value == currentTheme_.primaryForeground)
        return;

    currentTheme_.primaryForeground = value;
    emit primaryForegroundChanged();
}

void ThemeViewModel::setSecondary(const QString& value)
{
    if (value == currentTheme_.secondary)
        return;

    currentTheme_.secondary = value;
    emit secondaryChanged();
}

void ThemeViewModel::setSecondaryForeground(const QString& value)
{
    if (value == currentTheme_.secondaryForeground)
        return;

    currentTheme_.secondaryForeground = value;
    emit secondaryForegroundChanged();
}

void ThemeViewModel::fromTheme(const Theme& newTheme)
{
    setAccent(newTheme.accent);
    setBackground(newTheme.background);
    setForeground(newTheme.foreground);
    setPrimary(newTheme.primary);
    setPrimaryForeground(newTheme.primaryForeground);
    setSecondary(newTheme.secondary);
    setSecondaryForeground(newTheme.secondaryForeground);
}

double ThemeViewModel::colorScaleFactor(const QString& color) const
{
    const int lightnessMax = 164;
    const float darkerFactor = 1.05f;
    const float lighterFactor = 1.2f;

    if (QColor(color).lightness() > lightnessMax)
        return darkerFactor;
    return lighterFactor;
}

bool ThemeViewModel::isDark(const QString& color) const
{
    QColor c(color);
    int lightness = c.lightness();
    int ffCount = 0;
    if (c.red() > 250)
        ffCount++;
    if (c.green() > 250)
        ffCount++;
    if (c.blue() > 250)
        ffCount++;
    return lightness < 164 && ffCount < 2;
}

Theme ThemeViewModel::customTheme() const
{
    return Theme{accentColorSetting_.value().toString(),        backgroundSetting_.value().toString(),
                 foregroundSetting_.value().toString(),         primaryBackgroundSetting_.value().toString(),
                 primaryForegroundSetting_.value().toString(),  secondaryBackgroundSetting_.value().toString(),
                 secondaryForegroundSetting_.value().toString()};
}

void ThemeViewModel::collectThemes()
{
    availableThemes_["Adaptive"] = currentTheme_;
    availableThemes_["Ambiance"] = loader_.load(":/MellowPlayer/Domain/Theme/Ambiance.json");
    availableThemes_["Breeze"] = loader_.load(":/MellowPlayer/Domain/Theme/Breeze.json");
    availableThemes_["BreezeDark"] = loader_.load(":/MellowPlayer/Domain/Theme/BreezeDark.json");
    availableThemes_["Midna"] = loader_.load(":/MellowPlayer/Domain/Theme/Midna.json");
    availableThemes_["MidnaDark"] = loader_.load(":/MellowPlayer/Domain/Theme/MidnaDark.json");
    availableThemes_["Custom"] = customTheme();
    availableThemes_["Default"] = loader_.load(":/MellowPlayer/Domain/Theme/Default.json");

    for (auto service : streamingServices_.toList()) {
        availableThemes_[service->name()] = service->theme();
    }
}

void ThemeViewModel::onServiceAdded(StreamingService* service)
{
    availableThemes_[service->name()] = service->theme();
}

QStringList ThemeViewModel::availableThemes() const
{
    QStringList themes = availableThemes_.keys();
    themes.sort();
    return themes;
}

Theme ThemeViewModel::theme(const QString& themeName) const
{
    return availableThemes_[themeName];
}

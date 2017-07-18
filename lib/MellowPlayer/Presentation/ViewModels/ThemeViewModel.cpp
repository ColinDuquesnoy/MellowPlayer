#include <MellowPlayer/Application/StreamingServices/StreamingService.hpp>
#include <MellowPlayer/Application/StreamingServices/StreamingServicesController.hpp>
#include <MellowPlayer/Application/Settings/Setting.hpp>
#include <MellowPlayer/Application/Settings/Settings.hpp>
#include <MellowPlayer/Application/Theme/IThemeLoader.hpp>
#include "ThemeViewModel.hpp"

#include <QDebug>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Application;
using namespace MellowPlayer::Presentation;

ThemeViewModel::ThemeViewModel(StreamingServicesController& streamingServices, Settings& settings,
                               IThemeLoader& themeLoader) :
        streamingServices(streamingServices),
        loader(themeLoader),
        accentColorSetting(settings.get(SettingKey::APPEARANCE_ACCENT)),
        themeSetting(settings.get(SettingKey::APPEARANCE_THEME)),
        backgroundSetting(settings.get(SettingKey::APPEARANCE_BACKGROUND)),
        foregroundSetting(settings.get(SettingKey::APPEARANCE_FOREGROUND)),
        primaryBackgroundSetting(settings.get(SettingKey::APPEARANCE_PRIMARY_BACKGROUND)),
        primaryForegroundSetting(settings.get(SettingKey::APPEARANCE_PRIMARY_FOREGROUND)),
        secondaryBackgroundSetting(settings.get(SettingKey::APPEARANCE_SECONDARY_BACKGROUND)),
        secondaryForegroundSetting(settings.get(SettingKey::APPEARANCE_SECONDARY_FOREGROUND)),
        currentTheme(getCustomTheme()) {
    connect(&streamingServices, &StreamingServicesController::currentChanged, this,
            &ThemeViewModel::onCurrentServiceChanged);
    connect(&accentColorSetting, &Setting::valueChanged, this, &ThemeViewModel::update);
    connect(&themeSetting, &Setting::valueChanged, this, &ThemeViewModel::update);
    connect(&backgroundSetting, &Setting::valueChanged, this, &ThemeViewModel::update);
    connect(&foregroundSetting, &Setting::valueChanged, this, &ThemeViewModel::update);
    connect(&primaryBackgroundSetting, &Setting::valueChanged, this, &ThemeViewModel::update);
    connect(&primaryForegroundSetting, &Setting::valueChanged, this, &ThemeViewModel::update);
    connect(&secondaryBackgroundSetting, &Setting::valueChanged, this, &ThemeViewModel::update);
    connect(&secondaryForegroundSetting, &Setting::valueChanged, this, &ThemeViewModel::update);
    connect(&streamingServices, &StreamingServicesController::added, this,
            &ThemeViewModel::onServiceAdded);

    collectThemes();
    update();
}

bool ThemeViewModel::isDark() const {
    return isDark(currentTheme.background);
}

QString ThemeViewModel::getAccent() const {
    return currentTheme.accent;
}

QString ThemeViewModel::getBackground() const {
    return currentTheme.background;
}

QString ThemeViewModel::getForeground() const {
    return currentTheme.foreground;
}

QString ThemeViewModel::getPrimary() const {
    return currentTheme.primary;
}

QString ThemeViewModel::getPrimaryForeground() const {
    return currentTheme.primaryForeground;
}

QString ThemeViewModel::getSecondary() const {
    return currentTheme.secondary;
}

QString ThemeViewModel::getSecondaryForeground() const {
    return currentTheme.secondaryForeground;
}

void ThemeViewModel::update() {
    StreamingService* currentService = streamingServices.getCurrent();
    QString currentTheme = themeSetting.getValue().toString();
    if (currentService != nullptr && isAdaptiveTheme() && !currentService->getTheme().isEmpty()) {
        Theme theme = currentService->getTheme();
        availableThemes["Adaptive"] = theme;
        fromTheme(theme);
    }
    else if (isAdaptiveTheme())
        fromTheme(availableThemes["Default"]);
    else if (currentTheme == "Custom")
        fromTheme(getCustomTheme());
    else
        fromTheme(availableThemes[currentTheme]);
}

bool ThemeViewModel::isAdaptiveTheme() const {
    return themeSetting.getValue().toString() ==  "Adaptive";
}

void ThemeViewModel::onCurrentServiceChanged(StreamingService* streamingService) {
    connect(streamingService, &StreamingService::themeChanged, this, &ThemeViewModel::update, Qt::UniqueConnection);
    
    if (streamingService != nullptr)
        update();
}

void ThemeViewModel::setAccent(const QString& value) {
    if (value == currentTheme.accent)
        return;

    currentTheme.accent = value;
    emit accentChanged();
}

void ThemeViewModel::setBackground(const QString& value) {
    if (value == currentTheme.background)
        return;

    currentTheme.background = value;
    emit backgroundChanged();
    emit isDarkChanged();
}

void ThemeViewModel::setForeground(const QString& value) {
    if (value == currentTheme.foreground)
        return;

    currentTheme.foreground = value;
    emit foregroundChanged();
}

void ThemeViewModel::setPrimary(const QString& value) {
    if (value == currentTheme.primary)
        return;

    currentTheme.primary = value;
    emit primaryChanged();
}

void ThemeViewModel::setPrimaryForeground(const QString& value) {
    if (value == currentTheme.primaryForeground)
        return;

    currentTheme.primaryForeground = value;
    emit primaryForegroundChanged();
}

void ThemeViewModel::setSecondary(const QString& value) {
    if (value == currentTheme.secondary)
        return;

    currentTheme.secondary = value;
    emit secondaryChanged();
}

void ThemeViewModel::setSecondaryForeground(const QString& value) {
    if (value == currentTheme.secondaryForeground)
        return;

    currentTheme.secondaryForeground = value;
    emit secondaryForegroundChanged();
}

void ThemeViewModel::fromTheme(const Theme& newTheme) {
    setAccent(newTheme.accent);
    setBackground(newTheme.background);
    setForeground(newTheme.foreground);
    setPrimary(newTheme.primary);
    setPrimaryForeground(newTheme.primaryForeground);
    setSecondary(newTheme.secondary);
    setSecondaryForeground(newTheme.secondaryForeground);
}

double ThemeViewModel::getColorScaleFactor(const QString& color) const {
    const int lightnessMax = 164;
    const float darkerFactor = 1.05;
    const float lighterFactor = 1.2;

    if (QColor(color).lightness() > lightnessMax)
        return darkerFactor;
    return lighterFactor;
}

bool ThemeViewModel::isDark(const QString &color) const {
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

Theme ThemeViewModel::getCustomTheme() const {
    return Theme {
        accentColorSetting.getValue().toString(),
        backgroundSetting.getValue().toString(),
        foregroundSetting.getValue().toString(),
        primaryBackgroundSetting.getValue().toString(),
        primaryForegroundSetting.getValue().toString(),
        secondaryBackgroundSetting.getValue().toString(),
        secondaryForegroundSetting.getValue().toString()
    };
}

void ThemeViewModel::collectThemes() {
    availableThemes["Adaptive"] = currentTheme;
    availableThemes["Breeze"] = loader.load(":/MellowPlayer/Application/Theme/Breeze.json");
    availableThemes["BreezeDark"] = loader.load(":/MellowPlayer/Application/Theme/BreezeDark.json");
    availableThemes["Custom"] = getCustomTheme();
    availableThemes["Default"] = loader.load(":/MellowPlayer/Application/Theme/Default.json");

    for(auto service: streamingServices.getAll()) {
        availableThemes[service->getName()] = service->getTheme();
    }
}

void ThemeViewModel::onServiceAdded(StreamingService *service) {
    availableThemes[service->getName()] = service->getTheme();
}

QStringList ThemeViewModel::getAvailableThemes() const {
    QStringList themes = availableThemes.keys();
    themes.sort();
    return themes;
}

Theme ThemeViewModel::getTheme(const QString& themeName) const {
    return availableThemes[themeName];
}

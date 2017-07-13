#include <MellowPlayer/Application/StreamingServices/StreamingService.hpp>
#include <MellowPlayer/Application/StreamingServices/StreamingServicesController.hpp>
#include <MellowPlayer/Application/Settings/Setting.hpp>
#include <MellowPlayer/Application/Settings/Settings.hpp>
#include <MellowPlayer/Application/Style/IStyleLoader.hpp>
#include "StyleViewModel.hpp"

#include <QDebug>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Application;
using namespace MellowPlayer::Presentation;

StyleViewModel::StyleViewModel(StreamingServicesController& streamingServices, Settings& settings,
                               IStyleLoader& styleLoader) :
        useServiceStyle(true),
        streamingServices(streamingServices),
        styleLoader(styleLoader),
        accentColorSetting(settings.get(SettingKey::APPEARANCE_ACCENT)),
        themeSetting(settings.get(SettingKey::APPEARANCE_THEME)),
        backgroundSetting(settings.get(SettingKey::APPEARANCE_BACKGROUND)),
        foregroundSetting(settings.get(SettingKey::APPEARANCE_FOREGROUND)),
        primaryBackgroundSetting(settings.get(SettingKey::APPEARANCE_PRIMARY_BACKGROUND)),
        primaryForegroundSetting(settings.get(SettingKey::APPEARANCE_PRIMARY_FOREGROUND)),
        secondaryBackgroundSetting(settings.get(SettingKey::APPEARANCE_SECONDARY_BACKGROUND)),
        secondaryForegroundSetting(settings.get(SettingKey::APPEARANCE_SECONDARY_FOREGROUND)),
        currentStyle(getCustomStyle()) {
    connect(&streamingServices, &StreamingServicesController::currentChanged, this,
            &StyleViewModel::onCurrentServiceChanged);
    connect(&accentColorSetting, &Setting::valueChanged, this, &StyleViewModel::updateStyle);
    connect(&themeSetting, &Setting::valueChanged, this, &StyleViewModel::updateStyle);
    connect(&backgroundSetting, &Setting::valueChanged, this, &StyleViewModel::updateStyle);
    connect(&foregroundSetting, &Setting::valueChanged, this, &StyleViewModel::updateStyle);
    connect(&primaryBackgroundSetting, &Setting::valueChanged, this, &StyleViewModel::updateStyle);
    connect(&primaryForegroundSetting, &Setting::valueChanged, this, &StyleViewModel::updateStyle);
    connect(&secondaryBackgroundSetting, &Setting::valueChanged, this, &StyleViewModel::updateStyle);
    connect(&secondaryForegroundSetting, &Setting::valueChanged, this, &StyleViewModel::updateStyle);
    connect(&streamingServices, &StreamingServicesController::added, this,
            &StyleViewModel::onServiceAdded);

    collectStyles();
}

QString StyleViewModel::getTheme() const {
    return isDark(currentStyle.background) ? "dark" : "light";
}

QString StyleViewModel::getAccent() const {
    return currentStyle.accent;
}

QString StyleViewModel::getBackground() const {
    return currentStyle.background;
}

QString StyleViewModel::getForeground() const {
    return currentStyle.foreground;
}

QString StyleViewModel::getPrimary() const {
    return currentStyle.primary;
}

QString StyleViewModel::getPrimaryForeground() const {
    return currentStyle.primaryForeground;
}

QString StyleViewModel::getSecondary() const {
    return currentStyle.secondary;
}

QString StyleViewModel::getSecondaryForeground() const {
    return currentStyle.secondaryForeground;
}

void StyleViewModel::updateStyle() {
    StreamingService* currentService = streamingServices.getCurrent();
    if (useServiceStyle && currentService != nullptr && isAdaptiveTheme() &&
        !currentService->getStyle().isEmpty()) {
        Style style = currentService->getStyle();
        availableStyles["Adaptive"] = style;
        fromStyle(style);
    }
    else
        fromStyle(availableStyles[themeSetting.getValue().toString()]);
}

bool StyleViewModel::isAdaptiveTheme() const {
    return themeSetting.getValue().toString() ==  "Adaptive";
}

void StyleViewModel::onCurrentServiceChanged(StreamingService* streamingService) {
    connect(streamingService, &StreamingService::styleChanged, this, &StyleViewModel::updateStyle, Qt::UniqueConnection);
    
    if (streamingService != nullptr)
        updateStyle();
}

void StyleViewModel::setAccent(const QString& value) {
    if (value == currentStyle.accent)
        return;

    currentStyle.accent = value;
    emit accentChanged();
}

void StyleViewModel::setBackground(const QString& value) {
    if (value == currentStyle.background)
        return;

    currentStyle.background = value;
    emit backgroundChanged();
    emit themeChanged();
}

void StyleViewModel::setForeground(const QString& value) {
    if (value == currentStyle.foreground)
        return;

    currentStyle.foreground = value;
    emit foregroundChanged();
}

void StyleViewModel::setPrimary(const QString& value) {
    if (value == currentStyle.primary)
        return;

    currentStyle.primary = value;
    emit primaryChanged();
}

void StyleViewModel::setPrimaryForeground(const QString& value) {
    if (value == currentStyle.primaryForeground)
        return;

    currentStyle.primaryForeground = value;
    emit primaryForegroundChanged();
}

void StyleViewModel::setSecondary(const QString& value) {
    if (value == currentStyle.secondary)
        return;

    currentStyle.secondary = value;
    emit secondaryChanged();
}

void StyleViewModel::setSecondaryForeground(const QString& value) {
    if (value == currentStyle.secondaryForeground)
        return;

    currentStyle.secondaryForeground = value;
    emit secondaryForegroundChanged();
}

void StyleViewModel::fromStyle(const Style& newStyle) {
    setAccent(newStyle.accent);
    setBackground(newStyle.background);
    setForeground(newStyle.foreground);
    setPrimary(newStyle.primary);
    setPrimaryForeground(newStyle.primaryForeground);
    setSecondary(newStyle.secondary);
    setSecondaryForeground(newStyle.secondaryForeground);
}

double StyleViewModel::getColorScaleFactor(const QString& color) const {
    if (QColor(color).lightness() > 164)
        return 1.05;
    return 1.2;
}

bool StyleViewModel::isDark(const QString &color) const {
    return QColor(color).lightness() < 164;
}

Style StyleViewModel::getCustomStyle() {
    return Style {
            accentColorSetting.getValue().toString(),
            backgroundSetting.getValue().toString(),
            foregroundSetting.getValue().toString(),
            primaryBackgroundSetting.getValue().toString(),
            primaryForegroundSetting.getValue().toString(),
            secondaryBackgroundSetting.getValue().toString(),
            secondaryForegroundSetting.getValue().toString()
    };
}

void StyleViewModel::collectStyles() {
    availableStyles["Default"] = styleLoader.load(":/MellowPlayer/Application/Style/DefaultStyle.json");
    availableStyles["Custom"] = getCustomStyle();
    for(auto service: streamingServices.getAll()) {
        availableStyles[service->getName()] = service->getStyle();
    }
    availableStyles["Adaptive"] = currentStyle;
    emit availableStylesChanged();
}

void StyleViewModel::onServiceAdded(StreamingService *service) {
    availableStyles[service->getName()] = service->getStyle();
    emit availableStylesChanged();
}

QStringList StyleViewModel::getAvailableStyles() const {
    return availableStyles.keys();
}

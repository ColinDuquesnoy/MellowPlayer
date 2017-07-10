#include <MellowPlayer/Application/StreamingServices/StreamingService.hpp>
#include <MellowPlayer/Application/StreamingServices/StreamingServicesController.hpp>
#include <MellowPlayer/Application/Settings/Setting.hpp>
#include <MellowPlayer/Application/Settings/Settings.hpp>
#include "StyleViewModel.hpp"

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Application;
using namespace MellowPlayer::Presentation;

StyleViewModel::StyleViewModel(StreamingServicesController& streamingServices, Settings& settings) :
        useServiceStyle(true),
        streamingServices(streamingServices),
        accentColorSetting(settings.get(SettingKey::APPEARANCE_ACCENT)),
        adaptiveThemeSetting(settings.get(SettingKey::APPEARANCE_ADAPTIVE_THEME)),
        backgroundSetting(settings.get(SettingKey::APPEARANCE_BACKGROUND)),
        foregroundSetting(settings.get(SettingKey::APPEARANCE_FOREGROUND)),
        primaryBackgroundSetting(settings.get(SettingKey::APPEARANCE_PRIMARY_BACKGROUND)),
        primaryForegroundSetting(settings.get(SettingKey::APPEARANCE_PRIMARY_FOREGROUND)),
        secondaryBackgroundSetting(settings.get(SettingKey::APPEARANCE_SECONDARY_BACKGROUND)),
        secondaryForegroundSetting(settings.get(SettingKey::APPEARANCE_SECONDARY_FOREGROUND)),
        style(getDefaultStyle()) {
    connect(&streamingServices, &StreamingServicesController::currentChanged, this,
            &StyleViewModel::onCurrentServiceChanged);
    connect(&accentColorSetting, &Setting::valueChanged, this, &StyleViewModel::updateStyle);
    connect(&adaptiveThemeSetting, &Setting::valueChanged, this, &StyleViewModel::updateStyle);
    connect(&backgroundSetting, &Setting::valueChanged, this, &StyleViewModel::updateStyle);
    connect(&foregroundSetting, &Setting::valueChanged, this, &StyleViewModel::updateStyle);
    connect(&primaryBackgroundSetting, &Setting::valueChanged, this, &StyleViewModel::updateStyle);
    connect(&primaryForegroundSetting, &Setting::valueChanged, this, &StyleViewModel::updateStyle);
    connect(&secondaryBackgroundSetting, &Setting::valueChanged, this, &StyleViewModel::updateStyle);
    connect(&secondaryForegroundSetting, &Setting::valueChanged, this, &StyleViewModel::updateStyle);
}

QString StyleViewModel::getTheme() const {
    return isDark(style.background) ? "dark" : "light";
}

QString StyleViewModel::getAccent() const {
    return style.accent;
}

QString StyleViewModel::getBackground() const {
    return style.background;
}

QString StyleViewModel::getForeground() const {
    return style.foreground;
}

QString StyleViewModel::getPrimary() const {
    return style.primary;
}

QString StyleViewModel::getPrimaryForeground() const {
    return style.primaryForeground;
}

QString StyleViewModel::getSecondary() const {
    return style.secondary;
}

QString StyleViewModel::getSecondaryForeground() const {
    return style.secondaryForeground;
}

bool StyleViewModel::getUseServiceStyle() const {
    return useServiceStyle;
}

void StyleViewModel::setUseServiceStyle(bool value) {
    if (value == useServiceStyle)
        return;

    useServiceStyle = value;
    emit useServiceStyleChanged();
    updateStyle();
}

void StyleViewModel::updateStyle() {
    StreamingService* currentService = streamingServices.getCurrent();
    if (useServiceStyle && currentService != nullptr && adaptiveThemeSetting.getValue().toBool() &&
            !currentService->getStyle().isEmpty())
        fromStyle(currentService->getStyle());
    else
        fromStyle(getDefaultStyle());
}

void StyleViewModel::onCurrentServiceChanged(StreamingService* streamingService) {
    if (streamingService != nullptr)
        updateStyle();
}

void StyleViewModel::setAccent(const QString& value) {
    if (value == style.accent)
        return;

    style.accent = value;
    emit accentChanged();
}

void StyleViewModel::setBackground(const QString& value) {
    if (value == style.background)
        return;

    style.background = value;
    emit backgroundChanged();
    emit themeChanged();
}

void StyleViewModel::setForeground(const QString& value) {
    if (value == style.foreground)
        return;

    style.foreground = value;
    emit foregroundChanged();
}

void StyleViewModel::setPrimary(const QString& value) {
    if (value == style.primary)
        return;

    style.primary = value;
    emit primaryChanged();
}

void StyleViewModel::setPrimaryForeground(const QString& value) {
    if (value == style.primaryForeground)
        return;

    style.primaryForeground = value;
    emit primaryForegroundChanged();
}

void StyleViewModel::setSecondary(const QString& value) {
    if (value == style.secondary)
        return;

    style.secondary = value;
    emit secondaryChanged();
}

void StyleViewModel::setSecondaryForeground(const QString& value) {
    if (value == style.secondaryForeground)
        return;

    style.secondaryForeground = value;
    emit secondaryForegroundChanged();
}

void StyleViewModel::fromStyle(const StreamingServiceStyle& newStyle) {
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

StreamingServiceStyle StyleViewModel::getDefaultStyle() {
    return StreamingServiceStyle {
            accentColorSetting.getValue().toString(),
            backgroundSetting.getValue().toString(),
            foregroundSetting.getValue().toString(),
            primaryBackgroundSetting.getValue().toString(),
            primaryForegroundSetting.getValue().toString(),
            secondaryBackgroundSetting.getValue().toString(),
            secondaryForegroundSetting.getValue().toString()
    };
}

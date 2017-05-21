#pragma once

#include <QtCore/QObject>
#include <QtCore/QVariant>
#include "MellowPlayer/Macros.hpp"

BEGIN_MELLOWPLAYER_NAMESPACE(UseCases)

class ISettingsProvider;
class ApplicationSettings;
class SettingsCategory;

class Setting: public QObject {
    Q_OBJECT
public:
    struct Data {
        QString name;
        QString key;
        QString type;
        QVariant defaultValue;
        QString enableCondition;
    };

    Setting(ISettingsProvider& settingsProvider, ApplicationSettings& appSettings, SettingsCategory& category,
            const Data& data);

    void resolveDependency();

    const QString& getKey() const;
    const QString& getName() const;
    const QString& getType() const;
    QVariant getDefaultValue() const;

    QVariant getValue() const;
    void setValue(const QVariant& value);

    bool isEnabled() const;

signals:
    void isEnabledChanged();
    void valueChanged();

private slots:
    void onParentValueChanged();

private:
    QString getFullKey() const;

    ISettingsProvider& settingsProvider;
    ApplicationSettings& appSettings;
    SettingsCategory& category;
    Data data;
    bool notOperator = false;
    Setting* parentSetting = nullptr;
};

END_MELLOWPLAYER_NAMESPACE

#pragma once

#include <QtCore/QJsonArray>
#include <QtCore/QObject>
#include <QtCore/QList>
#include <MellowPlayer/Macros.hpp>

BEGIN_MELLOWPLAYER_NAMESPACE(UseCases)

class Settings;
class Setting;
class ISettingsProvider;

class SettingsCategory: public QObject {
    Q_OBJECT
public:
    struct Data {
        QJsonArray parameters;
        QString name;
        QString icon;
        QString key;
    };

    SettingsCategory(const Data& data, Settings* appSettings);
    void resolveDependencies();

    const QString& getName() const;
    const QString& getIcon() const;
    const QString& getKey() const;
    const QList<Setting*>& getSettings() const;

    Setting& getSetting(const QString& key) const;

private:
    Data data;
    QList<Setting*> settings;
};

END_MELLOWPLAYER_NAMESPACE

#pragma once

#include <QString>
#include <QVariant>
#include <MellowPlayer/Macros.hpp>
#include <MellowPlayer/Application/Notifications/Notifications.hpp>

BEGIN_MELLOWPLAYER_NAMESPACE(Application)

class ISettingsProvider {
public:
    virtual ~ISettingsProvider() = default;

    virtual void clear() = 0;

    virtual QVariant getValue(const QString& key, const QVariant& defaultValue = QVariant()) const = 0;
    virtual void setValue(const QString& key, const QVariant& value) = 0;
};

END_MELLOWPLAYER_NAMESPACE
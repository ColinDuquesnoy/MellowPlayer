#pragma once

#include <MellowPlayer/Application/Settings/ISettingsProvider.hpp>
#include <QSettings>

namespace MellowPlayer::Infrastructure
{
    class QSettingsProvider : public Application::ISettingsProvider
    {
    public:
        QSettingsProvider();

        void clear() override;

        QVariant getValue(const QString& key, const QVariant& defaultValue = QVariant()) const override;
        void setValue(const QString& key, const QVariant& value) override;

    private:
        QSettings qSettings;
    };
}

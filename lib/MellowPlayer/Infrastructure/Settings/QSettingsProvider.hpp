#pragma once

#include <MellowPlayer/Domain/Settings/ISettingsProvider.hpp>
#include <QSettings>

namespace MellowPlayer::Infrastructure
{
    class QSettingsProvider : public Domain::ISettingsProvider
    {
    public:
        QSettingsProvider();

        void clear() override;

        QVariant value(const QString& key, const QVariant& defaultValue = QVariant()) const override;
        void setValue(const QString& key, const QVariant& value) override;

    private:
        QSettings qSettings_;
    };
}

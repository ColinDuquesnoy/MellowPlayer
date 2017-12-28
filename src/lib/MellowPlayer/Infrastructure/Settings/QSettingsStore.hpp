#pragma once

#include <MellowPlayer/Domain/Settings/ISettingsStore.hpp>
#include <QSettings>

namespace MellowPlayer::Infrastructure
{
    class QSettingsStore : public Domain::ISettingsStore
    {
    public:
        QSettingsStore(const QString& orgName="MellowPlayer");

        void clear() override;

        QVariant value(const QString& key, const QVariant& defaultValue = QVariant()) const override;
        void setValue(const QString& key, const QVariant& value) override;

    private:
        QSettings qSettings_;
    };
}

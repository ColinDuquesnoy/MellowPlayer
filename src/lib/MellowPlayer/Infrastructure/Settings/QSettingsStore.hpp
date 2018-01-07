#pragma once

#include <memory>
#include <QSettings>
#include <MellowPlayer/Domain/Settings/ISettingsStore.hpp>

namespace MellowPlayer::Infrastructure
{
    class QSettingsStore : public Domain::ISettingsStore
    {
    public:
        QSettingsStore();

        void setOrganizationName(const QString& orgName);

        void clear() override;

        QVariant value(const QString& key, const QVariant& defaultValue = QVariant()) const override;
        void setValue(const QString& key, const QVariant& value) override;

    private:
        std::unique_ptr<QSettings> qSettings_;
    };
}

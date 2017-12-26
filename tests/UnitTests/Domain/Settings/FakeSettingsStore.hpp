#pragma once

#include <MellowPlayer/Domain/Settings/ISettingsStore.hpp>

namespace MellowPlayer::Domain::Tests
{
    class FakeSettingsStore : public ISettingsStore
    {
    public:
        QVariant value(const QString& key, const QVariant& defaultValue=QVariant()) const override
        {
            if (values_.contains(key))
                return values_[key];
            return defaultValue;
        }

        void setValue(const QString& key, const QVariant& value) override
        {
            values_[key] = value;
        }

        void clear() override
        {
            values_.clear();
        }

    private:
        QMap<QString, QVariant> values_;
    };
}
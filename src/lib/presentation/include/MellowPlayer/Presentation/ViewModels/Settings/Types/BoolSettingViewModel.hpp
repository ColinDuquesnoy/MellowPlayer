#pragma once

#include "SettingViewModel.hpp"

namespace MellowPlayer::Domain
{
    class Setting;
}

namespace MellowPlayer::Presentation
{
    class BoolSettingViewModel : public SettingViewModel
    {
        Q_OBJECT
        Q_PROPERTY(bool value READ getValue WRITE setValue NOTIFY valueChanged)
    public:
        BoolSettingViewModel(Domain::Setting& setting, QObject* parent = nullptr);

        bool getValue() const;
        QString qmlComponent() override;

    signals:
        void valueChanged();

    public slots:
        void setValue(bool value);

    protected slots:
        void onValueChanged() override;
    };
}

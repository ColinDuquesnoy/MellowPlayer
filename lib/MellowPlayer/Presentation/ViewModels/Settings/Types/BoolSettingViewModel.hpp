#pragma once

#include "SettingViewModel.hpp"
#include <MellowPlayer/Application/Settings/Setting.hpp>

namespace MellowPlayer::Presentation
{
    class BoolSettingViewModel : public SettingViewModel
    {
        Q_OBJECT
        Q_PROPERTY(bool value READ getValue WRITE setValue NOTIFY valueChanged)
    public:
        BoolSettingViewModel(Application::Setting& setting, QObject* parent = nullptr);

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

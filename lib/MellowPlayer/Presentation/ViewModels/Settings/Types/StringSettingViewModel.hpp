#pragma once

#include "SettingViewModel.hpp"

namespace MellowPlayer::Presentation
{
    class StringSettingViewModel : public SettingViewModel
    {
        Q_OBJECT
        Q_PROPERTY(QString value READ getValue WRITE setValue NOTIFY valueChanged)
    public:
        StringSettingViewModel(Domain::Setting& setting, QObject* parent = nullptr);

        virtual QString getValue() const;
        QString qmlComponent() override;

    public slots:
        void setValue(QString value);

    signals:
        void valueChanged();

    protected slots:
        void onValueChanged() override;
    };
}

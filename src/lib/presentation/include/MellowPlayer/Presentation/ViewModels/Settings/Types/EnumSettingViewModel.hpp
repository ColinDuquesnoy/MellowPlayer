#pragma once

#include "SettingViewModel.hpp"

namespace MellowPlayer::Presentation
{
    class EnumSettingViewModel : public SettingViewModel
    {
        Q_OBJECT
        Q_PROPERTY(QString value READ getValue WRITE setValue NOTIFY valueChanged)
        Q_PROPERTY(QStringList values READ values CONSTANT)
    public:
        EnumSettingViewModel(Domain::Setting& setting, QObject* parent = nullptr);

        QString getValue() const;
        virtual QStringList values() const;
        QString qmlComponent() override;

    signals:
        void valueChanged();

    public slots:
        void setValue(QString value);

    protected slots:
        void onValueChanged() override;
    };
}

#pragma once

#include "SettingViewModel.hpp"
#include <QColor>

namespace MellowPlayer::Presentation
{
    class ColorSettingViewModel : public SettingViewModel
    {
        Q_OBJECT
        Q_PROPERTY(QColor value READ getValue WRITE setValue NOTIFY valueChanged)
    public:
        ColorSettingViewModel(Domain::Setting& setting, QObject* parent = nullptr);

        QColor getValue() const;
        QString qmlComponent() override;

    signals:
        void valueChanged();

    public slots:
        void setValue(QColor value);

    protected slots:
        void onValueChanged() override;
    };
}

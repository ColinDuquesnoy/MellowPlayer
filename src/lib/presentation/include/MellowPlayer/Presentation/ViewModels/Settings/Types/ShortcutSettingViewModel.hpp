#pragma once

#include "SettingViewModel.hpp"

namespace MellowPlayer::Presentation
{
    class ShortcutSettingViewModel : public SettingViewModel
    {
        Q_OBJECT
        Q_PROPERTY(QString value READ getValue WRITE setValue NOTIFY valueChanged)
    public:
        ShortcutSettingViewModel(Domain::Setting& setting, QObject* parent = nullptr);

        QString getValue() const;
        QString qmlComponent() override;
        Q_INVOKABLE QString keySequenceToString(int key, int modifiers);
        Q_INVOKABLE bool isValidKeySequence(int key, int modifiers);

    signals:
        void valueChanged();

    public slots:
        void setValue(QString value);

    protected slots:
        void onValueChanged() override;
    };
}

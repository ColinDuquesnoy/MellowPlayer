#pragma once

#include "SettingViewModel.hpp"
#include <MellowPlayer/Application/Settings/Setting.hpp>
#include <MellowPlayer/Application/Updater/UpdateChannel.hpp>

namespace MellowPlayer::Presentation
{
    class UpdateChannelSettingViewModel : public SettingViewModel
    {
        Q_OBJECT
        Q_PROPERTY(QString value READ value WRITE setValue NOTIFY valueChanged)
        Q_PROPERTY(QStringList values READ values CONSTANT)
    public:
        UpdateChannelSettingViewModel(Application::Setting& setting, QObject* parent = nullptr);

        QString value() const;
        QStringList values() const;
        QString qmlComponent() override;

    signals:
        void valueChanged();

    public slots:
        void setValue(QString value);

    protected slots:
        void onValueChanged() override;

    private:
        UpdateChannelStringer stringer_;
    };
}

#pragma once

#include "SettingViewModel.hpp"
#include <MellowPlayer/Application/Settings/Setting.hpp>
#include <MellowPlayer/Application/Updater/UpdateChannel.hpp>

namespace MellowPlayer::Presentation
{
    class UpdateChannelSettingViewModel : public SettingViewModel
    {
        Q_OBJECT
        Q_PROPERTY(QString value READ getValue WRITE setValue NOTIFY valueChanged)
        Q_PROPERTY(QStringList values READ getValues CONSTANT)
    public:
        UpdateChannelSettingViewModel(Application::Setting& setting, QObject* parent = nullptr);

        QString getValue() const;
        QStringList getValues() const;
        QString getQmlComponent() override;

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

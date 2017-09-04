#pragma once

#include <QObject>

namespace MellowPlayer::Application
{
    enum class UpdateChannel
    {
        Stable,
        Beta,
        Continuous,
    };
}

class UpdateChannelStringer : public QObject
{
    Q_OBJECT
public:
    QString stable() const
    {
        return tr("Stable");
    }
    QString beta() const
    {
        return tr("Beta");
    }
    QString continuous() const
    {
        return tr("Continuous");
    }

    QString toString(MellowPlayer::Application::UpdateChannel channelType) const
    {
        QString string;

        switch (channelType) {
            case MellowPlayer::Application::UpdateChannel::Stable:
                string = stable();
                break;
            case MellowPlayer::Application::UpdateChannel::Beta:
                string = beta();
                break;
            case MellowPlayer::Application::UpdateChannel::Continuous:
                string = continuous();
                break;
        }

        return string;
    }

    MellowPlayer::Application::UpdateChannel fromString(const QString& channelName) const
    {
        MellowPlayer::Application::UpdateChannel channel;

        if (channelName == continuous())
            channel = MellowPlayer::Application::UpdateChannel::Continuous;
        else if (channelName == beta())
            channel = MellowPlayer::Application::UpdateChannel::Beta;
        else
            channel = MellowPlayer::Application::UpdateChannel::Stable;

        return channel;
    }
};

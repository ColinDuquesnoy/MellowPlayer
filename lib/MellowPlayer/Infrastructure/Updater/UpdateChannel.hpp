#pragma once

#include <QObject>

namespace MellowPlayer::Infrastructure
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

    QString toString(MellowPlayer::Infrastructure::UpdateChannel channelType) const
    {
        QString string;

        switch (channelType) {
            case MellowPlayer::Infrastructure::UpdateChannel::Stable:
                string = stable();
                break;
            case MellowPlayer::Infrastructure::UpdateChannel::Beta:
                string = beta();
                break;
            case MellowPlayer::Infrastructure::UpdateChannel::Continuous:
                string = continuous();
                break;
        }

        return string;
    }

    MellowPlayer::Infrastructure::UpdateChannel fromString(const QString& channelName) const
    {
        MellowPlayer::Infrastructure::UpdateChannel channel;

        if (channelName == continuous())
            channel = MellowPlayer::Infrastructure::UpdateChannel::Continuous;
        else if (channelName == beta())
            channel = MellowPlayer::Infrastructure::UpdateChannel::Beta;
        else
            channel = MellowPlayer::Infrastructure::UpdateChannel::Stable;

        return channel;
    }
};

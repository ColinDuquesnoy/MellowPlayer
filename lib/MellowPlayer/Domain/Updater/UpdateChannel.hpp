#pragma once

#include <QObject>

namespace MellowPlayer::Domain
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

    QString toString(MellowPlayer::Domain::UpdateChannel channelType) const
    {
        QString string;

        switch (channelType) {
            case MellowPlayer::Domain::UpdateChannel::Stable:
                string = stable();
                break;
            case MellowPlayer::Domain::UpdateChannel::Beta:
                string = beta();
                break;
            case MellowPlayer::Domain::UpdateChannel::Continuous:
                string = continuous();
                break;
        }

        return string;
    }

    MellowPlayer::Domain::UpdateChannel fromString(const QString& channelName) const
    {
        MellowPlayer::Domain::UpdateChannel channel;

        if (channelName == continuous())
            channel = MellowPlayer::Domain::UpdateChannel::Continuous;
        else if (channelName == beta())
            channel = MellowPlayer::Domain::UpdateChannel::Beta;
        else
            channel = MellowPlayer::Domain::UpdateChannel::Stable;

        return channel;
    }
};

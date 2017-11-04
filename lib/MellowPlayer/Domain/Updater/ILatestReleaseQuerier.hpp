#pragma once

#include "UpdateChannel.hpp"
#include <QtCore/QObject>

namespace MellowPlayer::Domain
{
    class Release;

    class ILatestReleaseQuerier : public QObject
    {
        Q_OBJECT
    public:
        virtual ~ILatestReleaseQuerier() = default;

        virtual void setChannel(UpdateChannel channel) = 0;
        virtual void query() = 0;

    signals:
        void latestReceived(const Release* release);
    };
}

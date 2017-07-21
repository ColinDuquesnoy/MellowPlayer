#pragma once

#include "UpdateChannel.hpp"
#include <QtCore/QObject>

namespace MellowPlayer::Application
{
    class Release;

    class IReleaseQuerier : public QObject
    {
        Q_OBJECT
    public:
        virtual ~IReleaseQuerier() = default;

        virtual void setChannel(UpdateChannel channel) = 0;
        virtual void getLatest() = 0;

    signals:
        void latestReceived(const Release *release);
    };
}

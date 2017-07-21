#pragma once

#include <MellowPlayer/Application/Updater/Release.hpp>
#include <QtCore/QByteArray>
#include <QtCore/QJsonDocument>

namespace MellowPlayer::Application
{
    class GithubReleasesReplyParser : public QObject
    {
        Q_OBJECT
    public:
        void parse(const QByteArray &replyData);
        void stop();

    signals:
        void ready(const Release *release);

    private:
        bool stopRequested_ = false;
    };
}

#pragma once

#include <QtCore/QObject>

class QByteArray;

namespace MellowPlayer::Application
{
    class Release;

    class GithubReleasesReplyParser : public QObject
    {
        Q_OBJECT
    public:
        void parse(const QByteArray& replyData);
        void stop();

    signals:
        void ready(const Release* release);

    private:
        bool stopRequested_ = false;
    };
}

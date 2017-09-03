#pragma once

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <MellowPlayer/Application/Updater/ILatestReleaseQuerier.hpp>
#include <MellowPlayer/Application/Updater/UpdateChannel.hpp>
#include <MellowPlayer/Application/Updater/Github/GithubReleasesReplyParser.hpp>

namespace MellowPlayer::Application
{
    class IHttpClient;
    class ILogger;
    class Release;

    class LatestGithubReleaseQuerier : public ILatestReleaseQuerier
    {
    public:
        explicit LatestGithubReleaseQuerier(IHttpClient& httpClient);

        void setChannel(UpdateChannel channel) override;
        void query() override;

    private slots:
        void onReplyReceived(const QByteArray& replyData);
        void onReleaseReady(const Release* release);
        bool accept(const Release* release);

    private:
        ILogger& logger_;
        GithubReleasesReplyParser replyParser_;
        IHttpClient& httpClient_;
        UpdateChannel channel_ = UpdateChannel::Stable;
        bool found_ = false;
    };
}

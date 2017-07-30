#pragma once

#include "GithubReleasesReplyParser.hpp"
#include <MellowPlayer/Application/Updater/IHttpClient.hpp>
#include <MellowPlayer/Application/Updater/ILatestReleaseQuerier.hpp>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

namespace MellowPlayer::Application
{
    class ILogger;

    class LatestGithubReleaseQuerier : public ILatestReleaseQuerier
    {
    public:
        explicit LatestGithubReleaseQuerier(IHttpClient& httpClient);

        void setChannel(Application::UpdateChannel channel) override;
        void query() override;

    private slots:
        void onReplyReceived(const QByteArray& replyData);
        void onReleaseReady(const Application::Release* release);
        bool accept(const Application::Release* release);

    private:
        ILogger& logger_;
        GithubReleasesReplyParser replyParser_;
        IHttpClient& httpClient_;
        Application::UpdateChannel channel_ = Application::UpdateChannel::Stable;
        bool found_ = false;
    };
}

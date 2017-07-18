#pragma once

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <MellowPlayer/Application/Updater/IReleaseQuerier.hpp>
#include <MellowPlayer/Application/Updater/IHttpClient.hpp>
#include "GithubReleasesReplyParser.hpp"

namespace MellowPlayer::Application {

    class ILogger;

    class GithubReleaseQuerier: public IReleaseQuerier {
    public:
        GithubReleaseQuerier(IHttpClient& httpClient);

        void setChannel(Application::UpdateChannel channel) override;
        void getLatest() override;

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

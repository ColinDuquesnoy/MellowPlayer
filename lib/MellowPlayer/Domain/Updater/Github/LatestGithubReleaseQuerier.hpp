#pragma once

#include <MellowPlayer/Domain/Updater/ILatestReleaseQuerier.hpp>
#include <MellowPlayer/Domain/Updater/UpdateChannel.hpp>
#include <MellowPlayer/Domain/Updater/Github/GithubReleasesReplyParser.hpp>

namespace MellowPlayer::Domain
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

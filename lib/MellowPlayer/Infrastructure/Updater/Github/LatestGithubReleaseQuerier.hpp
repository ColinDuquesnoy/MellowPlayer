#pragma once

#include <MellowPlayer/Infrastructure/Updater/ILatestReleaseQuerier.hpp>
#include <MellowPlayer/Infrastructure/Updater/UpdateChannel.hpp>
#include <MellowPlayer/Infrastructure/Updater/Github/GithubReleasesReplyParser.hpp>

namespace MellowPlayer::Domain
{
    class ILogger;
}

namespace MellowPlayer::Infrastructure
{
    class IHttpClient;
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
        Domain::ILogger& logger_;
        GithubReleasesReplyParser replyParser_;
        IHttpClient& httpClient_;
        UpdateChannel channel_ = UpdateChannel::Stable;
        bool found_ = false;
    };
}

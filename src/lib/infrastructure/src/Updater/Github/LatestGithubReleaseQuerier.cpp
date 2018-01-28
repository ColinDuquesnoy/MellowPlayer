#include <MellowPlayer/Infrastructure/Updater/Github/LatestGithubReleaseQuerier.hpp>
#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <MellowPlayer/Domain/Logging/Loggers.hpp>
#include <MellowPlayer/Domain/Logging/LoggingMacros.hpp>
#include <MellowPlayer/Infrastructure/Network/IHttpClient.hpp>
#include <MellowPlayer/Infrastructure/Updater/Release.hpp>


#define CONTINUOUS_RELEASE_NAME "Continuous"

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;

LatestGithubReleaseQuerier::LatestGithubReleaseQuerier(IHttpClient& httpClient)
        : logger_(Loggers::logger("LatestGithubReleaseQuerier")), httpClient_(httpClient)
{
    connect(&httpClient, &IHttpClient::replyReceived, this, &LatestGithubReleaseQuerier::onReplyReceived);
    connect(&replyParser_, &GithubReleasesReplyParser::ready, this, &LatestGithubReleaseQuerier::onReleaseReady);
}

void LatestGithubReleaseQuerier::setChannel(UpdateChannel channel)
{
    channel_ = channel;
}

void LatestGithubReleaseQuerier::query()
{
    LOG_DEBUG(logger_, "getting releases");
    found_ = false;
    httpClient_.get("https://api.github.com/repos/ColinDuquesnoy/MellowPlayer/releases");
}

void LatestGithubReleaseQuerier::onReplyReceived(const QByteArray& replyData)
{
    LOG_DEBUG(logger_, "Reply recevied");
    LOG_TRACE(logger_, "reply data: " << replyData.toStdString());
    replyParser_.parse(replyData);
    if (!found_) {
        LOG_DEBUG(logger_, "no release found");
        emit latestReceived(nullptr);
    }
}

void LatestGithubReleaseQuerier::onReleaseReady(const Release* release)
{
    if (release != nullptr && accept(release)) {
        LOG_DEBUG(logger_, "Latest release found: " << release->name());
        emit latestReceived(release);
        replyParser_.stop();
        found_ = true;
    }
}

bool LatestGithubReleaseQuerier::accept(const Release* release)
{
    bool accepted = false;

    switch (channel_) {
        case UpdateChannel::Continuous:
            accepted = release->name() == CONTINUOUS_RELEASE_NAME;
            break;
        case UpdateChannel::Beta:
            accepted = release->isPreRelease() && release->name() != CONTINUOUS_RELEASE_NAME;
            break;
        case UpdateChannel::Stable:
            accepted = !release->isPreRelease() && release->name() != CONTINUOUS_RELEASE_NAME;
            break;
    }

    return accepted;
}

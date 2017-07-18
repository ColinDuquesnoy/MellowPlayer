#include <QtCore/QJsonDocument>
#include <MellowPlayer/Application/Logging/LoggingManager.hpp>
#include <MellowPlayer/Application/Updater/Release.hpp>
#include "GithubReleaseQuerier.hpp"


#define CONTINUOUS_RELEASE_NAME "Continuous"

using namespace MellowPlayer::Application;

GithubReleaseQuerier::GithubReleaseQuerier(IHttpClient& httpClient):
        logger_(LoggingManager::instance().getLogger("GithubReleaseQuerier")), httpClient_(httpClient)
{
    connect(&httpClient, &IHttpClient::replyReceived, this, &GithubReleaseQuerier::onReplyReceived);
    connect(&replyParser_, &GithubReleasesReplyParser::ready, this, &GithubReleaseQuerier::onReleaseReady);
}

void GithubReleaseQuerier::setChannel(UpdateChannel channel)
{
    channel_ = channel;
}

void GithubReleaseQuerier::getLatest()
{
    LOG_DEBUG(logger_, "getting releases");
    found_ = false;
    httpClient_.get("https://api.github.com/repos/ColinDuquesnoy/MellowPlayer/releases");
}

void GithubReleaseQuerier::onReplyReceived(const QByteArray& replyData)
{
    LOG_DEBUG(logger_, "Reply recevied");
    LOG_TRACE(logger_, "reply data: " << replyData.toStdString());
    replyParser_.parse(replyData);
    if (!found_) {
        LOG_DEBUG(logger_, "no release found");
        emit latestReceived(nullptr);
    }
}

void GithubReleaseQuerier::onReleaseReady(const Release* release)
{
    if (release != nullptr && accept(release)) {
        LOG_DEBUG(logger_, "Latest release found: " << release->getName());
        emit latestReceived(release);
        replyParser_.stop();
        found_ = true;
    }
}

bool GithubReleaseQuerier::accept(const Release* release)
{
    bool accepted = false;

    switch (channel_) {
        case UpdateChannel::Continuous:
            accepted = release->getName() == CONTINUOUS_RELEASE_NAME;
            break;
        case UpdateChannel::Beta:
            accepted = release->isPreRelease() && release->getName() != CONTINUOUS_RELEASE_NAME;
            break;
        case UpdateChannel::Stable:
            accepted = !release->isPreRelease() && release->getName() != CONTINUOUS_RELEASE_NAME;
            break;
    }

    return accepted;
}

#include <QtCore/QJsonDocument>
#include <MellowPlayer/Application/Updater/Release.hpp>
#include "GithubReleaseQuerier.hpp"


#define CONTINUOUS_RELEASE_NAME "Continuous"

using namespace MellowPlayer::Application;

GithubReleaseQuerier::GithubReleaseQuerier(IHttpClient& httpClient):
        httpClient_(httpClient) {
    connect(&httpClient, &IHttpClient::replyReceived,
            this, &GithubReleaseQuerier::onReplyReceived);
    connect(&replyParser_, &GithubReleasesReplyParser::ready, this, &GithubReleaseQuerier::onReleaseReady);
}

void GithubReleaseQuerier::setChannel(UpdateChannel channel) {
    channel_ = channel;
}

void GithubReleaseQuerier::getLatest() {
    httpClient_.get("https://api.github.com/repos/ColinDuquesnoy/MellowPlayer/releases");
}

void GithubReleaseQuerier::onReplyReceived(const QByteArray& replyData) {
    replyParser_.parse(replyData);
}

void GithubReleaseQuerier::onReleaseReady(const Release* release) {
    if (release != nullptr && accept(release)) {
        emit latestReceived(release);
        replyParser_.stop();
    }
}

bool GithubReleaseQuerier::accept(const Release* release) {
    bool accepted;

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

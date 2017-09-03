#include "FakeHttpClient.hpp"
#include <MellowPlayer/Application/Updater/IHttpClient.hpp>
#include "Utils/Helpers.hpp"

void FakeHttpClient::get(const QString&)
{
    emit replyReceived(getValidReplyData());
}

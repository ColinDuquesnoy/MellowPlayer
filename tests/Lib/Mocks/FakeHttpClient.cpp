#include "FakeHttpClient.hpp"
#include <MellowPlayer/Domain/Updater/IHttpClient.hpp>
#include "Utils/Helpers.hpp"

void FakeHttpClient::get(const QString&)
{
    emit replyReceived(getValidReplyData());
}

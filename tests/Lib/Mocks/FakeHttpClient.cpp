#include "FakeHttpClient.hpp"
#include <MellowPlayer/Infrastructure/Network/IHttpClient.hpp>
#include <Utils/Helpers.hpp>

void FakeHttpClient::get(const QString&)
{
    emit replyReceived(getValidReplyData());
}

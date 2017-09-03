#include "FakeHttpClient.hpp"
#include "Utils/Helpers.hpp"

void FakeHttpClient::get(const QString&)
{
    emit replyReceived(getValidReplyData());
}

#pragma once

#include <MellowPlayer/Infrastructure/Network/IHttpClient.hpp>

using namespace MellowPlayer::Infrastructure;

class FakeHttpClient : public IHttpClient
{
public:
    void get(const QString& url) override;
};

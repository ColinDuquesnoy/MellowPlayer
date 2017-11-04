#pragma once

#include <MellowPlayer/Domain/Updater/IHttpClient.hpp>

using namespace MellowPlayer::Domain;

class FakeHttpClient : public IHttpClient
{
public:
    void get(const QString& url) override;
};

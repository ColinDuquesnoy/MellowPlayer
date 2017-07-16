#pragma once

#include <MellowPlayer/Application/Updater/IHttpClient.hpp>

using namespace MellowPlayer::Application;

class FakeHttpClient: public IHttpClient {
public:
    void get(const QString& url) override;
};



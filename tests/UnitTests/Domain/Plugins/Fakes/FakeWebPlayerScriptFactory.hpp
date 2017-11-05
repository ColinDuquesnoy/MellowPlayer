#pragma once

#include <QString>
#include <MellowPlayer/Domain/BoostDIFactory.hpp>
#include "UnitTests/Domain/Plugins/Mocks/MockWebPlayerScript.hpp"
#include <QtCore/QList>
#include <QtCore/QMap>

namespace MellowPlayer::Domain::Tests
{
    class ValidFakeWebPlayerScript: public MockWebPlayerScript
    {
    public:
        ValidFakeWebPlayerScript(const QString& path)
        {
            path_ = path;

            ON_CALL(*this, load()).WillByDefault(testing::Invoke([&]()
            {
                code_ = "function update\n"
                        "function play\n"
                        "function pause\n"
                        "function goNext\n"
                        "function goPrevious\n"
                        "function setVolume\n"
                        "function addToFavorites\n"
                        "function removeFromFavorites\n"
                        "function seekToPosition\n";
            }));
        }
    };

    class InvalidFakeWebPlayerScript: public MockWebPlayerScript
    {
    public:
        InvalidFakeWebPlayerScript(const QString& path)
        {
            path_ = path;

            ON_CALL(*this, load()).WillByDefault(testing::Invoke([&]()
            {
                code_ = "invalid";
                if (!isValid())
                    throw std::runtime_error("invalid script");
            }));
        }
    };

    class FakeWebPlayerScriptFactory: public IFactory<WebPlayerScript, QString>
    {
    public:
        std::unique_ptr<WebPlayerScript> create(QString&& path) override
        {
            std::unique_ptr<WebPlayerScript> script;
            if (createValidScripts)
                 script = std::make_unique<testing::NiceMock<ValidFakeWebPlayerScript>>(path);
            else
                 script = std::make_unique<testing::NiceMock<InvalidFakeWebPlayerScript>>(path);
            callCount++;
            callsParam.append(path);
            return script;
        }

        bool createValidScripts = true;
        QMap<QString, QString> fileContents;
        QList<QString> callsParam;
        int callCount = 0;
    };
}
#pragma once

#include <gmock/gmock.h>

namespace MellowPlayer::Domain::Tests
{
    class MockPluginMetadata: public PluginMetadata
    {
    public:
        MockPluginMetadata() = default;
        MockPluginMetadata(const QString& name,
                           const QString& version,
                           const QString& author,
                           const QString& authorUrl,
                           const QString& logo)
        {
            ON_CALL(*this, load()).WillByDefault(testing::Invoke([=]()
            {
                name_ = name;
                version_ = version;
                author_ = author;
                authorUrl_ = authorUrl;
                logo_ = logo;
            }));
        }

        MOCK_METHOD0(load, void());
    };
}
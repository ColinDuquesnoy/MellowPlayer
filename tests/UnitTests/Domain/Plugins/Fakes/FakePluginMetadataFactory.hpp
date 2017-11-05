#pragma once

#include <QString>
#include <MellowPlayer/Domain/BoostDIFactory.hpp>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <UnitTests/Domain/Plugins/Mocks/MockPluginMetadata.hpp>
#include <MellowPlayer/Domain/Plugins/PluginMetadata.hpp>

namespace MellowPlayer::Domain::Tests
{
    class FakePluginMetadataFactory: public IFactory<Domain::PluginMetadata, QString>
    {
    public:
        std::unique_ptr<PluginMetadata> create(QString&& path) override
        {
            auto metadata = std::make_unique<testing::NiceMock<MockPluginMetadata>>("FooBar", "1.0.0", "Foo", "https://foo.org", "logo.svg");
            callCount++;
            callsParam.append(path);
            return metadata;
        }
        QList<QString> callsParam;
        int callCount = 0;
    };
}
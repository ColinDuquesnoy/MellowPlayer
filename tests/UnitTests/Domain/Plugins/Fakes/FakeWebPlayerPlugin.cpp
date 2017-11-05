#include "FakeWebPlayerPlugin.hpp"
#include <MellowPlayer/Domain/Plugins/PluginMetadata.hpp>
#include <MellowPlayer/Domain/Plugins/WebPlayerScript.hpp>
#include <UnitTests/Domain/Plugins/Mocks/MockPluginMetadata.hpp>
#include <UnitTests/Domain/Plugins/Mocks/MockWebPlayerScript.hpp>

using namespace std;
using namespace testing;
using namespace MellowPlayer::Domain::Tests;

FakeWebPlayerPlugin::FakeWebPlayerPlugin()
{
    ON_CALL(*this, load()).WillByDefault(Invoke([&]()
        {
            metadata_ = make_shared<MockPluginMetadata>("FooBar", "1.0.0", "Foo", "https://foo.org", "logo.svg");
            metadata_->load();
            path_ = "/path/to/plugin";
            url_ = "https://webplayerservice.com";
            isEnabled_ = true;

            script_ = make_shared<MockWebPlayerScript>("code");
        }));
}


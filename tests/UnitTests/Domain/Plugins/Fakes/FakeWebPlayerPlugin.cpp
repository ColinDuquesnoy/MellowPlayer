#include "FakeWebPlayerPlugin.hpp"
#include "FakeWebPlayerScriptFactory.hpp"
#include <MellowPlayer/Domain/Plugins/PluginMetadata.hpp>
#include <MellowPlayer/Domain/Plugins/WebPlayerScript.hpp>

using namespace std;
using namespace testing;
using namespace MellowPlayer::Domain::Tests;

FakeWebPlayerPlugin::FakeWebPlayerPlugin()
{
    ON_CALL(*this, load()).WillByDefault(Invoke([&]()
        {
            metadata_ = make_shared<PluginMetadata>();
            metadata_->updateLogo("logo.svg");
            metadata_->updateAuthor("Foo");
            metadata_->updateAuthorUrl("https://foo.org");
            metadata_->updateName("FooBar");
            metadata_->updateVersion("1.0.0");
            path_ = "/path/to/plugin";

            url_ = "https://webplayerservice.com";
            isEnabled_ = true;

            script_ = make_shared<ValidFakeWebPlayerScript>(path() + "/integration.js");
        }));
}


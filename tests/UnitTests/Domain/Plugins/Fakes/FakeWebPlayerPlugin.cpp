#include "FakeWebPlayerPlugin.hpp"
#include <MellowPlayer/Domain/Plugins/PluginMetadata.hpp>
#include <MellowPlayer/Domain/Plugins/WebPlayerScript.hpp>

using namespace std;
using namespace MellowPlayer::Domain::Tests;

void FakeWebPlayerPlugin::load()
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

    QString code = "function update\n"
            "function play\n"
            "function pause\n"
            "function goNext\n"
            "function goPrevious\n"
            "function setVolume\n"
            "function addToFavorites\n"
            "function removeFromFavorites\n"
            "function seekToPosition\n";
    script_ = make_shared<WebPlayerScript>(code, path() + "/integration.js");
}

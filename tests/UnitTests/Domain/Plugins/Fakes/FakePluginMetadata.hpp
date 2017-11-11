#pragma once

#include <QString>
#include <MellowPlayer/Domain/Plugins/PluginMetadata.hpp>

namespace MellowPlayer::Domain::Tests
{
    class FakePluginMetadata: public PluginMetadata
    {
    public:
        FakePluginMetadata(const QString& name,
                           const QString& version,
                           const QString& author,
                           const QString& authorUrl,
                           const QString& logo)
        {
            name_ = name;
            version_ = version;
            author_ = author;
            authorUrl_ = authorUrl;
            logo_ = logo;
        }

        virtual void load() override {

        }
    };
}
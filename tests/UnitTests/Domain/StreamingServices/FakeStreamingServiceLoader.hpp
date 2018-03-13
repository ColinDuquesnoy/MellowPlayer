#pragma once

#include <MellowPlayer/Domain/StreamingServices/IStreamingServiceLoader.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingService.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingServiceMetadata.hpp>
#include <MellowPlayer/Domain/Theme/Theme.hpp>
#include <QList>
#include <catch/catch.hpp>
#include <memory>

namespace MellowPlayer::Domain::Tests
{
    class FakeStreamingServiceLoader : public IStreamingServiceLoader
    {
    public:
        QList<std::shared_ptr<StreamingService>> load() const override
        {
            QList<std::shared_ptr<StreamingService>> list;

            list.append(createPlugin("Deezer"));
            list.append(createPlugin("Spotify"));
            list.append(createPlugin("Mixcloud"));
            list.append(createPlugin("Soundcloud"));

            return list;
        }

        static Theme defaultTheme() {
            static Theme defaultTheme = {"#ff00ff", "#00ff00", "#ff0000", "#ffff00", "#faebdc", "#fedcba", "#abcdef"};
            return defaultTheme;
        }

    private:
        static std::unique_ptr<StreamingService> createPlugin(const QString& name)
        {
            StreamingServiceMetadata metadata;
            metadata.name = name;
            metadata.url = "http://" + name.toLower() + ".com";
            return std::make_unique<StreamingService>(metadata, defaultTheme());
        }
    };
}

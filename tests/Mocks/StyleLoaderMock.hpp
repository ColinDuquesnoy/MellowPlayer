#pragma once
#include <fakeit.hpp>
#include <memory>
#include <MellowPlayer/Application/Style/IStyleLoader.hpp>
#include <MellowPlayer/Application/Style/Style.hpp>

using namespace MellowPlayer::Application;
using namespace fakeit;

class StyleLoaderMock {
public:
    static Mock<IStyleLoader> get() {
        Mock<IStyleLoader> mock;
        When(Method(mock, load)).AlwaysDo([](const QString&){
            auto randomColors = [](int count) {
                QVector<QColor> colors;
                float currentHue = 0.0;
                for (int i = 0; i < count; i++){
                    colors.push_back( QColor::fromHslF(currentHue, 1.0, 0.5) );
                    currentHue += 0.618033988749895f;
                    currentHue = std::fmod(currentHue, 1.0f);
                }
                return colors;
            };

            auto colors = randomColors(7);

            Style style;
            style.accent = colors[0].name();
            style.background = colors[1].name();
            style.foreground = colors[2].name();
            style.primary = colors[3].name();
            style.primaryForeground = colors[4].name();
            style.secondary = colors[5].name();
            style.secondaryForeground = colors[6].name();

            return style;

        });
        return mock;
    }
};


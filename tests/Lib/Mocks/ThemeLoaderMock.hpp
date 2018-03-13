#pragma once
#include <fakeit/fakeit.hpp>
#include <memory>
#include <QColor>
#include <MellowPlayer/Domain/Theme/IThemeLoader.hpp>
#include <MellowPlayer/Domain/Theme/Theme.hpp>
#include <cmath>

using namespace MellowPlayer::Domain;
using namespace fakeit;

class ThemeLoaderMock {
public:
    static Mock<IThemeLoader> get() {
        Mock<IThemeLoader> mock;
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

            Theme theme;
            theme.accent = colors[0].name();
            theme.background = colors[1].name();
            theme.foreground = colors[2].name();
            theme.primary = colors[3].name();
            theme.primaryForeground = colors[4].name();
            theme.secondary = colors[5].name();
            theme.secondaryForeground = colors[6].name();

            return theme;

        });
        return mock;
    }
};


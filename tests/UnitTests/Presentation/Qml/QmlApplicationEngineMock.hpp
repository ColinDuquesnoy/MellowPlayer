#pragma once

#include <MellowPlayer/Presentation/Qml/IQmlApplicationEngine.hpp>
#include <gmock/gmock.h>
#include <QString>
#include <QObject>
#include <QUrl>

namespace MellowPlayer::Presentation::Tests
{
    class QmlApplicationEngineMock: public IQmlApplicationEngine
    {
    public:
        MOCK_METHOD2(setContextProperty, void(const QString&, QObject*));
        MOCK_METHOD1(addImportPath, void(const QString&));
        MOCK_METHOD1(load, void(const QUrl&));
    };
}

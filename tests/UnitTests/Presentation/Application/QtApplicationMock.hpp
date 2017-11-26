#pragma once

#include <gmock/gmock.h>
#include <QtGui/QFont>
#include <QtGui/QIcon>

namespace MellowPlayer::Presentation::Tests
{
    class QtApplicationMock: public IQtApplication
    {
    public:
        MOCK_METHOD1(setApplicationName, void(QString));
        MOCK_METHOD1(setApplicationDisplayName, void(QString));
        MOCK_METHOD1(setApplicationVersion, void(QString));
        MOCK_METHOD1(setOrganizationDomain, void(QString));
        MOCK_METHOD1(setOrganizationName, void(QString));
        MOCK_METHOD1(setWindowIcon, void(const QIcon&));
        MOCK_METHOD0(exec, int());
        MOCK_METHOD1(exit, void(int));
        MOCK_METHOD1(installTranslator, void(QTranslator*));
        MOCK_METHOD1(setFont, void(const QFont&));
    };

}

#pragma once

#include <QtGui/QFont>
#include <QtGui/QIcon>
#include <MellowPlayer/Infrastructure/Application/QtApplication.hpp>

namespace MellowPlayer::Infrastructure::Tests
{
    class FakeQtApplication: public IQtApplication
    {
    public:
        void setApplicationName(QString value) override
        {
            appName = value;
        }

        void setApplicationDisplayName(QString value) override
        {
            appDisplayName = value;
        }

        void setApplicationVersion(QString value) override
        {
            appVersion = value;
        }

        void setOrganizationDomain(QString value) override
        {
            orgDomain = value;
        }

        void setOrganizationName(QString value) override
        {
            orgName = value;
        }

        void installTranslator(QTranslator* value) override
        {
            translator = value;
        }

        void setWindowIcon(const QIcon&) override
        {
            isIconSet = true;
        }

        int run() override
        {
            isRunning = true;
            return returnCodeToUseInExec;
        }

        void exit(int returnCode) override
        {
            requestedExitCode = returnCode;
        }

        void setFont(const QFont&) override
        {
            isFontSet = true;
        }

        QString appName;
        QString appDisplayName;
        QString appVersion;
        QString orgDomain;
        QString orgName;
        QTranslator* translator = nullptr;
        bool isIconSet = false;
        bool isFontSet = false;
        bool isRunning = false;
        int requestedExitCode = -1;
        int returnCodeToUseInExec = 0;
    };

}

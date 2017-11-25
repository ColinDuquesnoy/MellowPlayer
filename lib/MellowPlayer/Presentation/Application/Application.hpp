#pragma once

#include <MellowPlayer/Infrastructure/Application/IApplication.hpp>
#include <QApplication>
#include <QTranslator>
#include "QtApplication.hpp"

class ApplicationStrings : public QObject
{
Q_OBJECT
public:
    QString builtOnStr() const
    {
        return tr("Built on %1 at %2 (%3, %4 bit) with Qt %5");
    }
};

namespace MellowPlayer::Presentation
{
    class Application : public Infrastructure::IApplication
    {
    public:
        Application(IQtApplication& qtApplication);

        void initialize() override;
        int run() override;
        void quit() override;
        void restart() override;
        void restoreWindow() override;

    private:
        void setupTranslations();
        void registerMetaTypes();
        void setupFont();

        IQtApplication& qtApp_;
        QTranslator translator_;
        bool restartRequested_;
    };
}


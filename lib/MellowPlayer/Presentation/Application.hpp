#pragma once

#include <MellowPlayer/Infrastructure/Application/IApplication.hpp>
#include <MellowPlayer/Presentation/Qml/ContextProperty.hpp>
#include <QApplication>
#include <QTranslator>
#include <MellowPlayer/Infrastructure/Application/QtApplication.hpp>

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
    class Application : public Infrastructure::IApplication, public ContextProperty
    {
        Q_OBJECT
    public:
        Application(Infrastructure::IQtApplication& qtApplication, IContextProperties& contextProperties);

        // ContextProperty
        QString name() const override;
        QObject* asQObject() override;

        // IApplication
        void initialize() override;
        int run() override;
        void quit() override;
        void restart() override;
        void restoreWindow() override;

        Q_INVOKABLE void requestQuit();

    signals:
        void quitRequest();

    private:
        void setupTranslations();
        void registerMetaTypes();
        void setupFont();

        Infrastructure::IQtApplication& qtApp_;
        QTranslator translator_;
        bool restartRequested_;
    };
}


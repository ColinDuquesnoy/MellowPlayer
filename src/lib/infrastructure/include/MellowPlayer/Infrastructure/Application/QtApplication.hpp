#pragma once

#include <QtWidgets/QApplication>

class QTranslator;
class QIcon;

namespace MellowPlayer::Infrastructure
{
    class IQtApplication : public QObject
    {
        Q_OBJECT
    public:
        virtual void setApplicationName(QString value) = 0;
        virtual void setApplicationDisplayName(QString value) = 0;
        virtual void setApplicationVersion(QString value) = 0;
        virtual void setOrganizationDomain(QString value) = 0;
        virtual void setOrganizationName(QString value) = 0;
        virtual void setWindowIcon(const QIcon& icon) = 0;

        virtual int run() = 0;
        virtual void exit(int returnCode) = 0;

        virtual void installTranslator(QTranslator* translator) = 0;
        virtual void setFont(const QFont& font) = 0;

    signals:
        void aboutToQuit();
        void commitDataRequest();
    };

    class QtApplication: public IQtApplication
    {
    public:
        QtApplication(QApplication& qApplication);

        void setApplicationName(QString name) override;
        void setApplicationDisplayName(QString displayName) override;
        void setApplicationVersion(QString version) override;
        void setOrganizationDomain(QString domain) override;
        void setOrganizationName(QString name) override;
        void setWindowIcon(const QIcon& icon) override;

        int run() override;
        void exit(int returnCode) override;

        void installTranslator(QTranslator* translator) override;
        void setFont(const QFont& font) override;

    private:
        QApplication& qApplication_;

    };
}

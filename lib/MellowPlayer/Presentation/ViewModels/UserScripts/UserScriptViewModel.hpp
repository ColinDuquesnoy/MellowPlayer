#pragma once

#include <QObject>

namespace MellowPlayer::Application
{
    class IUserScript;
}

namespace MellowPlayer::Presentation
{
    class UserScriptViewModel: public QObject
    {
        Q_OBJECT
        Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
        Q_PROPERTY(QString code READ code CONSTANT)
        Q_PROPERTY(QString path READ path CONSTANT)
    public:
        UserScriptViewModel(Application::IUserScript& model, QObject* parent= nullptr);

        QString name() const;
        void setName(const QString& name);

        QString code() const;
        QString path() const;

        Application::IUserScript& model();

    signals:
        void nameChanged();

    private:
        Application::IUserScript& model_;

    };
}

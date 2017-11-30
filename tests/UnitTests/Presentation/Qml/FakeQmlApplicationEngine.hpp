#pragma once

#include <MellowPlayer/Presentation/Qml/IQmlApplicationEngine.hpp>
#include <QString>
#include <QObject>
#include <QUrl>
#include <QtCore/QMap>

namespace MellowPlayer::Presentation::Tests
{
    class FakeQmlApplicationEngine: public IQmlApplicationEngine
    {
    public:
        void setContextProperty(const QString& name, QObject* object) override
        {
            contextProperties_[name] = object;
        }

        bool hasContextProperty(const QString& name)
        {
            return contextProperties_.contains(name);
        }

        QObject* contextProperty(const QString& name) const
        {
            return contextProperties_[name];
        }

        void addImportPath(const QString& path) override
        {
            importPaths_.append(path);
        }

        int importPathsCount()
        {
            return importPaths_.count();
        }

        void load(const QUrl& url) override
        {
            loadedUrl_ = url;
        }

        bool isLoaded() const
        {
            return !loadedUrl_.isEmpty();
        }

    private:
        QMap<QString, QObject*> contextProperties_;
        QStringList importPaths_;
        QUrl loadedUrl_;
    };
}

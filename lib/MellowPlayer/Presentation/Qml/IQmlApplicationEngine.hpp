#pragma once

#include <QObject>
#include <QString>
#include <QUrl>

namespace MellowPlayer::Presentation
{
    /**
     * Wraps most QQmlApplicationEngine methods in order to simplify unit tests.
     */
    class IQmlApplicationEngine
    {
    public:
        virtual ~IQmlApplicationEngine() = default;

        /**
         * Sets a context property on the root QQmlContext.
         *
         * @param name Name of the property to set
         * @param object QObject property
         */
        virtual void setContextProperty(const QString& name, QObject* object) = 0;

        /**
         * Adds a path to the QML import path list.
         *
         * @param path Path to add
         */
        virtual void addImportPath(const QString& path) = 0;

        /**
         * Loads the specified QML document.
         *
         * @param url Url to the QML document to load.
         */
        virtual void load(const QUrl& url) = 0;
    };
}

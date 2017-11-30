#pragma once

#include <MellowPlayer/Presentation/Qml/ContextProperty.hpp>
#include <QObject>

namespace MellowPlayer::Presentation
{
    class IQmlApplicationEngine;

    class IMainWindow
    {
    public:
        virtual ~IMainWindow() = default;

        virtual void load() = 0;
        virtual void show() = 0;
        virtual void hide() = 0;
    };

    class MainWindow: public QObject, public ContextProperty, public IMainWindow
    {
        Q_OBJECT
        Q_PROPERTY(bool visible READ isVisible WRITE setVisible NOTIFY visibleChanged)
    public:
        MainWindow(IContextProperties& contextProperties, IQmlApplicationEngine& qmlApplicationEngine);

        // ContextProperty implementation
        QString name() const override;
        QObject* asQObject() override;

        // IMainWindow implementation
        void load() override;
        void show() override;
        void hide() override;

        // Properties for QML
        bool isVisible() const;

    public slots:
        void setVisible(bool visible);

    signals:
        void visibleChanged();

    private:
        IQmlApplicationEngine& qmlApplicationEngine_;
        bool visible_;
    };
}

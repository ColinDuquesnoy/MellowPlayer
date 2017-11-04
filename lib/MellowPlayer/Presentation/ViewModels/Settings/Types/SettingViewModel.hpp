#pragma once

#include <QtCore/QObject>

namespace MellowPlayer::Domain
{
    class Setting;
}

namespace MellowPlayer::Presentation
{
    class SettingViewModel : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(QString name READ name CONSTANT)
        Q_PROPERTY(QString toolTip READ toolTip CONSTANT)
        Q_PROPERTY(QString type READ type CONSTANT)
        Q_PROPERTY(QString qmlComponent READ qmlComponent CONSTANT)
        Q_PROPERTY(bool enabled READ enabled NOTIFY enabledChanged)
    public:
        SettingViewModel(Domain::Setting& setting, QObject* parent = nullptr);

        QString name() const;
        QString toolTip() const;
        QString type() const;
        virtual QString qmlComponent() = 0;
        bool enabled() const;

    signals:
        void enabledChanged();

    protected slots:
        virtual void onValueChanged() = 0;

    protected:
        Domain::Setting& setting_;

    private slots:
        void onEnabledChanged();
    };
}

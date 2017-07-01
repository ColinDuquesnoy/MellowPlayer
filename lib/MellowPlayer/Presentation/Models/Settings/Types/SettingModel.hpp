#pragma once

#include <MellowPlayer/Application/Settings/Setting.hpp>

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class SettingModel: public QObject {
    Q_OBJECT
    Q_PROPERTY(QString name READ getName CONSTANT)
    Q_PROPERTY(QString toolTip READ getToolTip CONSTANT)
    Q_PROPERTY(QString type READ getType CONSTANT)
    Q_PROPERTY(QString qmlComponent READ getQmlComponent CONSTANT)
    Q_PROPERTY(bool enabled READ getEnabled NOTIFY enabledChanged)
public:
    SettingModel(Application::Setting& setting, QObject* parent=nullptr);

    QString getName() const;
    QString getToolTip() const;
    QString getType() const;
    virtual QString getQmlComponent() = 0;
    bool getEnabled() const;

signals:
    void enabledChanged();

protected slots:
    virtual void onValueChanged() = 0;

protected:
    Application::Setting& setting;

private slots:
    void onIsEnabledChanged();
};

END_MELLOWPLAYER_NAMESPACE

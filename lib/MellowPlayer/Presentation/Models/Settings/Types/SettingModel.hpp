#pragma once

#include <MellowPlayer/UseCases/Settings/Setting.hpp>

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class SettingModel: public QObject {
    Q_OBJECT
    Q_PROPERTY(QString name READ getName CONSTANT)
    Q_PROPERTY(QString type READ getType CONSTANT)
    Q_PROPERTY(bool enabled READ getEnabled NOTIFY enabledChanged)
public:
    SettingModel(UseCases::Setting& setting, QObject* parent);

    QString getName() const;
    QString getType() const;
    bool getEnabled() const;

signals:
    void enabledChanged();

protected slots:
    virtual void onValueChanged() = 0;

protected:
    UseCases::Setting& setting;

private slots:
    void onIsEnabledChanged();
};

END_MELLOWPLAYER_NAMESPACE

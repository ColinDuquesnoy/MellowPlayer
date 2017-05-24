#pragma once

#include <MellowPlayer/UseCases/Settings/Setting.hpp>
#include "SettingModel.hpp"

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class EnumSettingModel: public SettingModel {
    Q_OBJECT
    Q_PROPERTY(QString value READ getValue WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(QStringList values READ getValues CONSTANT)
public:
    EnumSettingModel(UseCases::Setting& setting, QObject* parent);

    QString getValue() const;
    QStringList getValues() const;
    QString getQmlComponent() override;

signals:
    void valueChanged();

public slots:
    void setValue(QString value);

protected slots:
    void onValueChanged() override;

};

END_MELLOWPLAYER_NAMESPACE
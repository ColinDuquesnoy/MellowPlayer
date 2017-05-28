#pragma once

#include <MellowPlayer/UseCases/Settings/Setting.hpp>
#include "SettingModel.hpp"

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class StringSettingModel: public SettingModel {
    Q_OBJECT
    Q_PROPERTY(QString value READ getValue WRITE setValue NOTIFY valueChanged)
public:
    StringSettingModel(UseCases::Setting& setting, QObject* parent);

    QString getValue() const;
    QString getQmlComponent() override;

public slots:
    void setValue(QString value);

signals:
    void valueChanged();

protected slots:
    void onValueChanged() override;

};

END_MELLOWPLAYER_NAMESPACE
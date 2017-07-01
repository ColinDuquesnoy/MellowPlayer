#pragma once

#include <MellowPlayer/Application/Settings/Setting.hpp>
#include "SettingModel.hpp"

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class BoolSettingModel: public SettingModel {
    Q_OBJECT
    Q_PROPERTY(bool value READ getValue WRITE setValue NOTIFY valueChanged)
public:
    BoolSettingModel(Application::Setting& setting, QObject* parent=nullptr);

    bool getValue() const;
    QString getQmlComponent() override;

signals:
    void valueChanged();

public slots:
    void setValue(bool value);

protected slots:
    void onValueChanged() override;

};

END_MELLOWPLAYER_NAMESPACE

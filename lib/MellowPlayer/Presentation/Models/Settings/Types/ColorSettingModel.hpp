#pragma once

#include <QColor>
#include <MellowPlayer/UseCases/Settings/Setting.hpp>
#include "SettingModel.hpp"

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class ColorSettingModel: public SettingModel {
    Q_OBJECT
    Q_PROPERTY(QColor value READ getValue WRITE setValue NOTIFY valueChanged)
public:
    ColorSettingModel(UseCases::Setting& setting, QObject* parent);

    QColor getValue() const;
    QString getQmlComponent() override;

signals:
    void valueChanged();

public slots:
    void setValue(QColor value);

protected slots:
    void onValueChanged() override;

};

END_MELLOWPLAYER_NAMESPACE
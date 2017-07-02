#pragma once

#include <QColor>
#include <MellowPlayer/Application/Settings/Setting.hpp>
#include "SettingViewModel.hpp"

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class ColorSettingViewModel: public SettingViewModel {
    Q_OBJECT
    Q_PROPERTY(QColor value READ getValue WRITE setValue NOTIFY valueChanged)
public:
    ColorSettingViewModel(Application::Setting& setting, QObject* parent=nullptr);

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

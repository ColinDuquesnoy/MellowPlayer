#pragma once

#include <MellowPlayer/Application/Settings/Setting.hpp>
#include "SettingViewModel.hpp"

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class BoolSettingViewModel: public SettingViewModel {
    Q_OBJECT
    Q_PROPERTY(bool value READ getValue WRITE setValue NOTIFY valueChanged)
public:
    BoolSettingViewModel(Application::Setting& setting, QObject* parent=nullptr);

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

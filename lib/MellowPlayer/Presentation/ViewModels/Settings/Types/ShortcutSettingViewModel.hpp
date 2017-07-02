#pragma once

#include <MellowPlayer/Application/Settings/Setting.hpp>
#include "SettingViewModel.hpp"

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class ShortcutSettingViewModel: public SettingViewModel {
    Q_OBJECT
    Q_PROPERTY(QString value READ getValue WRITE setValue NOTIFY valueChanged)
public:
    ShortcutSettingViewModel(Application::Setting& setting, QObject* parent=nullptr);

    QString getValue() const;
    QString getQmlComponent() override;
    Q_INVOKABLE QString keySequenceToString(int key, int modifiers);
    Q_INVOKABLE bool isValidKeySequence(int key, int modifiers);

signals:
    void valueChanged();

public slots:
    void setValue(QString value);

protected slots:
    void onValueChanged() override;

};

END_MELLOWPLAYER_NAMESPACE

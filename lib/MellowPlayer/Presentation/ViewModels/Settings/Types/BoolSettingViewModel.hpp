#pragma once

#include <MellowPlayer/Application/Settings/Setting.hpp>
#include "SettingViewModel.hpp"

namespace MellowPlayer::Presentation {

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

}

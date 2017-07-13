#pragma once

#include "EnumSettingViewModel.hpp"

namespace MellowPlayer::Presentation {

    class StyleViewModel;

    class StyleSettingViewModel: public EnumSettingViewModel {
        Q_OBJECT
    public:
        StyleSettingViewModel(Application::Setting& setting, QObject* parent,
                              StyleViewModel& styleViewModel);
        QStringList getValues() const override;

    private:
        StyleViewModel& styleViewModel;
    };
}

#pragma once

#include <MellowPlayer/Presentation/ViewModels/Settings/Types/StringSettingViewModel.hpp>

namespace MellowPlayer::Presentation
{
    class UserAgentStringSettingViewModel : public StringSettingViewModel
    {
    public:
        UserAgentStringSettingViewModel(Domain::Setting& setting, QObject* parent = nullptr);

        QString getValue() const override;
    };
}

#include "ThemeSettingViewModel.hpp"
#include <MellowPlayer/Presentation/ViewModels/ThemeViewModel.hpp>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Presentation;

ThemeSettingViewModel::ThemeSettingViewModel(Setting &setting, QObject *parent,
                                             ThemeViewModel &themeViewModel):
    EnumSettingViewModel(setting, parent), themeViewModel(themeViewModel) {

}

QStringList ThemeSettingViewModel::getValues() const {
    return themeViewModel.getAvailableThemes();
}

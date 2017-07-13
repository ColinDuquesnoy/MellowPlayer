#include "StyleSettingViewModel.hpp"
#include <MellowPlayer/Presentation/ViewModels/StyleViewModel.hpp>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Presentation;

StyleSettingViewModel::StyleSettingViewModel(Setting &setting, QObject *parent,
                                             StyleViewModel &styleViewModel):
    EnumSettingViewModel(setting, parent), styleViewModel(styleViewModel) {

}

QStringList StyleSettingViewModel::getValues() const {
    return styleViewModel.getAvailableStyles();
}

#include "catch.hpp"
#include "DI.hpp"
#include <MellowPlayer/Application/Settings/Setting.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/SettingsViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/BoolSettingViewModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/Settings/Types/StringSettingViewModel.hpp>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Presentation;

TEST_CASE("SettingsViewModelTests") {
    ScopedScope scope;
    auto injector = getTestInjector(scope);
    Settings& settings = injector.create<Settings&>();
    StyleViewModel& styleViewModel = injector.create<StyleViewModel&>();
    SettingsViewModel viewModel(settings, styleViewModel);

    SECTION("get") {
        SettingViewModel* settingModel = viewModel.get(SettingKey::NOTIFICATIONS_ENABLED);
        REQUIRE(settingModel != nullptr);
    }

    SECTION("getCategories") {
        int extraCategories = 2;
        REQUIRE(viewModel.getCategories()->count() - extraCategories == (settings.getCategories().count() - 1));
    }
}

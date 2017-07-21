#include <MellowPlayer/Presentation/ViewModels/UpdaterViewModel.hpp>
#include <Utils/DependencyPool.hpp>
#include <catch.hpp>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Tests;

SCENARIO("check for updates")
{
    DependencyPool pool;
    Updater &updater = pool.getUpdater();
    UpdaterViewModel &viewModel = pool.getUpdaterViewModel();

    GIVEN("current version is 2.2.4 from April 2017")
    {
        Release currentRelease("2.2.4", QDate::fromString("2017-04-29", Qt::ISODate));
        updater.setCurrentRelease(&currentRelease);

        REQUIRE(!viewModel.isBusy());
        REQUIRE(!viewModel.isVisible());
        REQUIRE(viewModel.getUrl().isEmpty());
        REQUIRE(viewModel.getStatusString().isEmpty());
        REQUIRE(!viewModel.isInstallEnabled());
        REQUIRE(viewModel.getProgress() == -1);

        WHEN("checking for updates")
        {
            viewModel.check();
            REQUIRE(!viewModel.isBusy());

            THEN("an update is available")
            {
                REQUIRE(viewModel.isVisible());
                REQUIRE(!viewModel.getUrl().isEmpty());

                AND_WHEN("closing the pane")
                {
                    viewModel.close();

                    THEN("visible changed but all other properties remains")
                    {
                        REQUIRE(!viewModel.isVisible());

                        REQUIRE(!viewModel.getUrl().isEmpty());
                    }
                }

                AND_WHEN("clicking on install")
                {
                    viewModel.install();

                    THEN("progress bar appear and updater starts downloading")
                    {
                        REQUIRE(viewModel.isBusy());
                    }
                }
            }
        }
    }

    GIVEN("current version is 3.0 from August 2017")
    {
        Release currentRelease("3.0", QDate::fromString("2017-08-12", Qt::ISODate));
        updater.setCurrentRelease(&currentRelease);

        REQUIRE(!viewModel.isBusy());
        REQUIRE(!viewModel.isVisible());
        REQUIRE(viewModel.getUrl().isEmpty());
        REQUIRE(viewModel.getStatusString().isEmpty());
        REQUIRE(!viewModel.isInstallEnabled());
        REQUIRE(viewModel.getProgress() == -1);

        WHEN("checking for updates")
        {
            viewModel.check();
            REQUIRE(!viewModel.isBusy());

            THEN("no update is available")
            {
                REQUIRE(!viewModel.isVisible());
                REQUIRE(viewModel.getUrl().isEmpty());
            }
        }
    }
}

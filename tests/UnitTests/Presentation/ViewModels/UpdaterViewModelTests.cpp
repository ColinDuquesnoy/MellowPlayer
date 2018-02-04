#include <catch/catch.hpp>
#include <Utils/DependencyPool.hpp>
#include <MellowPlayer/Presentation/ViewModels/UpdaterViewModel.hpp>
#include <MellowPlayer/Infrastructure/Updater/Updater.hpp>
#include <MellowPlayer/Infrastructure/Updater/Release.hpp>

using namespace MellowPlayer::Infrastructure;
using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Tests;

SCENARIO("check for updates")
{
    DependencyPool pool;
    Updater& updater = pool.getUpdater();
    UpdaterViewModel& viewModel = pool.getUpdaterViewModel();

    GIVEN("current version is 2.2.4 from April 2017")
    {
        Release currentRelease("2.2.4", QDate::fromString("2017-04-29", Qt::ISODate));
        updater.setCurrentRelease(&currentRelease);

        REQUIRE(!viewModel.busy());
        REQUIRE(!viewModel.visible());
        REQUIRE(viewModel.url().isEmpty());
        REQUIRE(viewModel.status().isEmpty());
        REQUIRE(!viewModel.installEnabled());
        REQUIRE(viewModel.progress() == -1);

        WHEN("checking for updates")
        {
            viewModel.check();
            REQUIRE(!viewModel.busy());

            THEN("an update is available")
            {
                REQUIRE(viewModel.visible());
                REQUIRE(!viewModel.url().isEmpty());

                AND_WHEN("closing the pane")
                {
                    viewModel.close();

                    THEN("visible changed but all other properties remains")
                    {
                        REQUIRE(!viewModel.visible());

                        REQUIRE(!viewModel.url().isEmpty());
                    }
                }

                AND_WHEN("clicking on install")
                {
                    viewModel.install();

                    THEN("progress bar appear and updater starts downloading")
                    {
                        REQUIRE(viewModel.busy());
                    }
                }
            }
        }
    }

    GIVEN("current version is 3.0 from August 2017")
    {
        Release currentRelease("3.0", QDate::fromString("2017-08-12", Qt::ISODate));
        updater.setCurrentRelease(&currentRelease);

        REQUIRE(!viewModel.busy());
        REQUIRE(!viewModel.visible());
        REQUIRE(viewModel.url().isEmpty());
        REQUIRE(viewModel.status().isEmpty());
        REQUIRE(!viewModel.installEnabled());
        REQUIRE(viewModel.progress() == -1);

        WHEN("checking for updates")
        {
            viewModel.check();
            REQUIRE(!viewModel.busy());

            THEN("no update is available")
            {
                REQUIRE(!viewModel.visible());
                REQUIRE(viewModel.url().isEmpty());
            }
        }
    }
}

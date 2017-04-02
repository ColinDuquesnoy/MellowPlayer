#include <catch.hpp>
#include <DI.hpp>
#include <MellowPlayer/Presentation/Models/ListModel.hpp>
#include <Mocks/ApplicationSettingsMock.hpp>

USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Presentation)

TEST_CASE("GenericListModelTests") {
    StreamingServiceListModel model;
    auto appSettingsMock = ApplicationSettingsMock::get();
    ScopedScope scope;
    auto injector = getTestInjector(scope);
    PlayerService& playerService = injector.create<PlayerService&>();
    REQUIRE(model.rowCount() == 0);

    SECTION("add") {
        PluginMetadata metadata;
        metadata.name = "Deezer";
        metadata.url = "https://deezer.com";
        Plugin service(metadata);
        StreamingServiceModel serviceModel(service, appSettingsMock.get(), playerService);

        model.append(&serviceModel);
        REQUIRE(model.rowCount() == 1);

        SECTION("take") {
            model.remove(&serviceModel);
            REQUIRE(model.rowCount() == 0);

            SECTION("invalidData") {
                auto data = model.data(model.index(0, 0), StreamingServiceListModel::Object);
                REQUIRE(bool(data.isNull() && !data.isValid()));
            }
        }

        SECTION("data") {
            auto data = model.data(model.index(0, 0), StreamingServiceListModel::Object);
            REQUIRE(bool(!data.isNull() && data.isValid()));
            auto obj = data.value<QObject*>();
            REQUIRE(obj->property("name").toString().toStdString() == "Deezer");
        }
    }

    SECTION("roleNames") {
        REQUIRE(model.roleNames().count() == 1);
    }
}
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
    PlayersService& playersService = injector.create<PlayersService&>();
    REQUIRE(model.rowCount() == 0);

    SECTION("add_Test") {
        PluginMetadata metadata;
        metadata.name = "Deezer";
        metadata.url = "https://deezer.com";
        Plugin service(metadata);
        StreamingServiceModel serviceModel(service, appSettingsMock.get(), playersService);

        model.append(&serviceModel);
        REQUIRE(model.rowCount() == 1);

        SECTION("take_Test") {
            model.remove(&serviceModel);
            REQUIRE(model.rowCount() == 0);

            SECTION("invalidData") {
                auto data = model.data(model.index(0, 0), StreamingServiceListModel::Object);
                REQUIRE(bool(data.isNull() && !data.isValid()));
            }
        }

        SECTION("data_Test") {
            auto data = model.data(model.index(0, 0), StreamingServiceListModel::Object);
            REQUIRE(bool(!data.isNull() && data.isValid()));
            auto obj = data.value<QObject*>();
            REQUIRE(obj->property("name").toString().toStdString() == "Deezer");
        }
    }

    SECTION("roleNames_Test") {
        REQUIRE(model.roleNames().count() == 1);
    }
}
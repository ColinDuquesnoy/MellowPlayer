#include <catch.hpp>
#include <MellowPlayer/Presentation.hpp>

USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Presentation)



TEST_CASE("GenericListModelTests") {
    StreamingServicesModel model;
    REQUIRE(model.rowCount() == 0);

    SECTION("add_Test") {
        PluginMetadata metadata;
        metadata.name = "Deezer";
        metadata.url = "https://deezer.com";
        StreamingService service(metadata);

        model.add(&service);
        REQUIRE(model.rowCount() == 1);

        SECTION("take_Test") {
            model.take(&service);
            REQUIRE(model.rowCount() == 0);

            SECTION("invalidData") {
                auto data = model.data(model.index(0, 0), StreamingServicesModel::Object);
                REQUIRE(bool(data.isNull() && !data.isValid()));
            }
        }

        SECTION("data_Test") {
            auto data = model.data(model.index(0, 0), StreamingServicesModel::Object);
            REQUIRE(bool(!data.isNull() && data.isValid()));
            auto obj = data.value<QObject*>();
            REQUIRE(obj->property("name").toString().toStdString() == "Deezer");
        }
    }

    SECTION("roleNames_Test") {
        REQUIRE(model.roleNames().count() == 1);
    }
}
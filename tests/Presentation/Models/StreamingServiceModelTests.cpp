#include <catch.hpp>
#include <MellowPlayer/Presentation.hpp>

USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Presentation)



TEST_CASE("StreamingServicesModel") {
    StreamingServicesModel model;
    REQUIRE(model.rowCount() == 0);

//    auto data = model.data(model.index(-1, -1), StreamingServicesModel::StreamingServiceRole);
//    REQUIRE(bool(data.isNull() && !data.isValid()));

    SECTION("addService") {
        PluginMetadata metadata;
        metadata.name = "Deezer";
        metadata.url = "https://deezer.com";
        StreamingService service(metadata);

        model.addService(&service);
        REQUIRE(model.rowCount() == 1);

        SECTION("data") {
            auto data = model.data(model.index(0, 0), StreamingServicesModel::StreamingServiceRole);
            REQUIRE(bool(!data.isNull() && data.isValid()));
            auto obj = data.value<QObject*>();
            REQUIRE(obj->property("name").toString().toStdString() == "Deezer");
        }

        SECTION("removeService") {
            model.removeService(&service);
            REQUIRE(model.rowCount() == 0);

            SECTION("invalidData") {
                auto data = model.data(model.index(0, 0), StreamingServicesModel::StreamingServiceRole);
                REQUIRE(bool(data.isNull() && !data.isValid()));
            }
        }
    }
}
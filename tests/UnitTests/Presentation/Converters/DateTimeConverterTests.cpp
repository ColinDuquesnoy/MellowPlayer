#include <MellowPlayer/Presentation/Converters/DateTimeConverter.hpp>
#include <QDateTime>
#include <catch/catch.hpp>

using namespace MellowPlayer::Presentation;

TEST_CASE("DateConverterTests", "[UnitTest]")
{
    DateTimeConverter converter;

    QDateTime today = QDateTime::currentDateTime();
    QDateTime yesterday = today.addDays(-1);
    QDateTime lastWeek = today.addDays(-6);
    QDateTime lastMonth = today.addDays(-20);
    QDateTime lastYear = today.addDays(-60);
    QDateTime beforeLastYear = today.addDays(-380);

    SECTION("dateToCategory today")
    {
        REQUIRE(converter.dateToCategory(today) == "Today");
    }

    SECTION("dateToCategory yesterday")
    {
        REQUIRE(converter.dateToCategory(yesterday) == "Yesterday");
    }

    SECTION("dateToCategory last week")
    {
        REQUIRE(converter.dateToCategory(lastWeek) == "Last week");
    }

    SECTION("dateToCategory last month")
    {
        REQUIRE(converter.dateToCategory(lastMonth).toStdString() == "Last month");
    }

    SECTION("dateToCategory last year")
    {
        REQUIRE(converter.dateToCategory(lastYear).toStdString() == "Last year");
    }

    SECTION("dateToCategory before last year")
    {
        REQUIRE(converter.dateToCategory(beforeLastYear) == "Years ago");
    }

    SECTION("dateToString")
    {
        REQUIRE(!converter.dateToString(today).isEmpty());
        REQUIRE(converter.dateToString(today) != converter.timeToString(today));
    }

    SECTION("timeToString")
    {
        REQUIRE(!converter.dateToString(today).isEmpty());
        REQUIRE(converter.dateToString(today) != converter.timeToString(today));
    }
}

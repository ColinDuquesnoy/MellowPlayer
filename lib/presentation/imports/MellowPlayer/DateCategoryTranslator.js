function translate(dateCategory) {
    switch (dateCategory) {
    case "Today":
        return qsTr("Today");
    case "Yesterday":
        return qsTr("Yesterday");
    case "Last week":
        return qsTr("Last week");
    case "Last month":
        return qsTr("Last month");
    case "Last year":
        return qsTr("Last year");
    case "Years ago":
        return qsTr("Years ago");
    }
}

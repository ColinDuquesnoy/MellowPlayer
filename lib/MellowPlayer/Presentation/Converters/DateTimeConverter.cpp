#include "DateTimeConverter.h"

USE_MELLOWPLAYER_NAMESPACE(Presentation)


QString DateTimeConverter::dateToCategory(const QDateTime &dateTime) const {
    QDate date = dateTime.date();
    QDate today = QDateTime::currentDateTime().date();
    QDate yesterday = today.addDays(-1);
    QDate lastWeek = today.addDays(-7);
    QDate lastMonth = today.addMonths(-1);
    QDate lastYear = today.addYears(-1);

    if (date == today)
        return tr("Today");
    else if (date == yesterday)
        return tr("Yesterday");
    else if (date >= lastWeek)
        return tr("Last week");
    else if (date >= lastMonth)
        return tr("Last month");
    else if (date >= lastYear)
        return tr("Last year");
    else
        return tr("All time");
}

QString DateTimeConverter::dateToString(const QDateTime &dateTime) const {
    return dateTime.date().toString(Qt::DateFormat::SystemLocaleShortDate);
}

QString DateTimeConverter::timeToString(const QDateTime &dateTime) const {
    return dateTime.time().toString(Qt::DateFormat::SystemLocaleShortDate);
}

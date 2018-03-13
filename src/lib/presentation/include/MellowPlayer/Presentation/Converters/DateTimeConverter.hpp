#pragma once

#include <QObject>

class QDateTime;

namespace MellowPlayer::Presentation {

    class DateTimeConverter: public QObject {
        Q_OBJECT
    public:
        Q_INVOKABLE QString dateToCategory(const QDateTime &dateTime) const;
        Q_INVOKABLE QString dateToString(const QDateTime &dateTime) const;
        Q_INVOKABLE QString timeToString(const QDateTime &dateTime) const;
    };

}

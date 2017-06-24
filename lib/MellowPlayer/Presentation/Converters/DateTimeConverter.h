#pragma once

#include <QObject>
#include <QDateTime>
#include <MellowPlayer/Macros.hpp>

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class DateTimeConverter: public QObject {
public:
    Q_INVOKABLE QString dateToCategory(const QDateTime &dateTime) const;
    Q_INVOKABLE QString dateToString(const QDateTime &dateTime) const;
    Q_INVOKABLE QString timeToString(const QDateTime &dateTime) const;
};

END_MELLOWPLAYER_NAMESPACE

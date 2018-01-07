#pragma once

#include <QVariant>

QVariantMap getSongVariantMap(QString title, QString uniqueId, bool playing = true, QString artist = "artistName");
QString readFile(const QString& path);
bool writeFile(const QString& path, const QString& content);
QByteArray getValidReplyData();

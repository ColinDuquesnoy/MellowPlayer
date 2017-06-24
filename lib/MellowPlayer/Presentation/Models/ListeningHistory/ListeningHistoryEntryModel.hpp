#pragma once

#include <MellowPlayer/Application/ListeningHistory/ListeningHistoryEntry.hpp>
#include <MellowPlayer/Presentation/Converters/DateTimeConverter.h>

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class ListeningHistoryEntryModel: public QObject {
    Q_PROPERTY(int entryId READ getEntryId CONSTANT)
    Q_PROPERTY(QString songId READ getSongId CONSTANT)
    Q_PROPERTY(QString title READ getTitle CONSTANT)
    Q_PROPERTY(QString artist READ getArtist CONSTANT)
    Q_PROPERTY(QString artUrl READ getArtUrl CONSTANT)
    Q_PROPERTY(QString service READ getService CONSTANT)
    Q_PROPERTY(QString date READ getDate CONSTANT)
    Q_PROPERTY(QString time READ getTime CONSTANT)
    Q_PROPERTY(QString dateCategory READ getDateCategory CONSTANT)
    Q_OBJECT
public:
    ListeningHistoryEntryModel(const Application::ListeningHistoryEntry& entry, QObject* parent = nullptr);

    int getEntryId() const { return entry.id; }
    QString getSongId() const;
    QString getTitle() const;
    QString getArtist() const;
    QString getArtUrl() const;
    QString getService() const;
    QString getDate() const;
    QString getTime() const;
    QString getDateCategory() const;

private:
    Application::ListeningHistoryEntry entry;
    DateTimeConverter dateTimeConverter;
};

END_MELLOWPLAYER_NAMESPACE

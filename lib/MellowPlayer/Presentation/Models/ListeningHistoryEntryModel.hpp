#pragma once

#include <MellowPlayer/Entities/ListeningHistoryEntry.hpp>
#include "ListModel.hpp"

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class ListeningHistoryEntryModel: public QObject {
    Q_PROPERTY(QString songId READ getSongId CONSTANT)
    Q_PROPERTY(QString title READ getTitle CONSTANT)
    Q_PROPERTY(QString artist READ getArtist CONSTANT)
    Q_PROPERTY(QString artUrl READ getArtUrl CONSTANT)
    Q_PROPERTY(QString service READ getService CONSTANT)
    Q_PROPERTY(QString date READ getDate CONSTANT)
    Q_PROPERTY(QString time READ getTime CONSTANT)
    Q_OBJECT
public:
    ListeningHistoryEntryModel(const Entities::ListeningHistoryEntry& entry, QObject* parent = nullptr);

    QString getSongId() const;
    QString getTitle() const;
    QString getArtist() const;
    QString getArtUrl() const;
    QString getService() const;
    QString getDate() const;
    QString getTime() const;

private:
    Entities::ListeningHistoryEntry entry;
};

using ListeningHistoryEntryListModel = ListModel<ListeningHistoryEntryModel>;

END_MELLOWPLAYER_NAMESPACE

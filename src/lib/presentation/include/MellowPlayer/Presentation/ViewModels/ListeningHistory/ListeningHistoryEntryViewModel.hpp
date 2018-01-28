#pragma once

#include <MellowPlayer/Domain/ListeningHistory/ListeningHistoryEntry.hpp>
#include <MellowPlayer/Presentation/Converters/DateTimeConverter.hpp>

namespace MellowPlayer::Presentation
{
    class ListeningHistoryEntryViewModel : public QObject
    {
        Q_PROPERTY(int entryId READ entryId CONSTANT)
        Q_PROPERTY(QString songId READ songId CONSTANT)
        Q_PROPERTY(QString title READ title CONSTANT)
        Q_PROPERTY(QString artist READ artist CONSTANT)
        Q_PROPERTY(QString artUrl READ artUrl CONSTANT)
        Q_PROPERTY(QString service READ service CONSTANT)
        Q_PROPERTY(QString date READ date CONSTANT)
        Q_PROPERTY(QString time READ time CONSTANT)
        Q_PROPERTY(QString dateCategory READ dateCategory CONSTANT)
        Q_OBJECT
    public:
        ListeningHistoryEntryViewModel(const Domain::ListeningHistoryEntry& entry, QObject* parent = nullptr);

        int entryId() const;
        QString songId() const;
        QString title() const;
        QString artist() const;
        QString artUrl() const;
        QString service() const;
        QString date() const;
        QString time() const;
        QString dateCategory() const;

    private:
        Domain::ListeningHistoryEntry entry_;
        DateTimeConverter dateTimeConverter_;
    };
}

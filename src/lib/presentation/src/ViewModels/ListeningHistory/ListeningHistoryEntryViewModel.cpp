#include <MellowPlayer/Presentation/ViewModels/ListeningHistory/ListeningHistoryEntryViewModel.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;

ListeningHistoryEntryViewModel::ListeningHistoryEntryViewModel(const ListeningHistoryEntry& entry, QObject* parent) : QObject(parent), entry_(entry)
{
}

QString ListeningHistoryEntryViewModel::songId() const
{
    return entry_.songUniqueId;
}

QString ListeningHistoryEntryViewModel::title() const
{
    return entry_.songTitle;
}

QString ListeningHistoryEntryViewModel::artist() const
{
    return entry_.artist;
}

QString ListeningHistoryEntryViewModel::artUrl() const
{
    return entry_.artUrl;
}

QString ListeningHistoryEntryViewModel::service() const
{
    return entry_.serviceName;
}

QString ListeningHistoryEntryViewModel::date() const
{
    return dateTimeConverter_.dateToString(entry_.dateTime());
}

QString ListeningHistoryEntryViewModel::time() const
{
    return dateTimeConverter_.timeToString(entry_.dateTime());
}

QString ListeningHistoryEntryViewModel::dateCategory() const
{
    return dateTimeConverter_.dateToCategory(entry_.dateTime());
}
int ListeningHistoryEntryViewModel::entryId() const
{
    return entry_.id;
}

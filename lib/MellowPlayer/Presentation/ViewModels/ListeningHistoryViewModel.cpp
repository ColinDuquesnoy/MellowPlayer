#include "ListeningHistoryViewModel.hpp"

USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Presentation)

ListeningHistoryViewModel::ListeningHistoryViewModel(ListeningHistory& listeningHistory) {
    connect(&listeningHistory, &ListeningHistory::entryAdded, this, &ListeningHistoryViewModel::onEntryAdded);
    connect(&listeningHistory, &ListeningHistory::entryRemoved, this, &ListeningHistoryViewModel::onEntryRemoved);
    connect(&listeningHistory, &ListeningHistory::entriesCleared, this, &ListeningHistoryViewModel::onEntriesCleared);

    for(auto entry: listeningHistory.getEntries())
        onEntryAdded(entry);
}

ListeningHistoryEntryListModel* ListeningHistoryViewModel::getModel() {
    return &model;
}

void ListeningHistoryViewModel::onEntryAdded(const ListeningHistoryEntry& entry) {
    model.prepend(new ListeningHistoryEntryModel(entry, this));
}

void ListeningHistoryViewModel::onEntryRemoved(int index) {
    model.removeAt(index);
}

void ListeningHistoryViewModel::onEntriesCleared() {
    model.clear();
}

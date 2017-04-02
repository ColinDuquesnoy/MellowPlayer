#include <MellowPlayer/UseCases/Services/ListeningHistoryService.hpp>
#include "ListeningHistoryViewModel.hpp"
#include "QQmlObjectListModel.hpp"

USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Presentation)

ListeningHistoryViewModel::ListeningHistoryViewModel(ListeningHistoryService& listeningHistory):
        model(new QQmlObjectListModel<ListeningHistoryEntryModel>(this) ) {
    connect(&listeningHistory, &ListeningHistoryService::entryAdded, this, &ListeningHistoryViewModel::onEntryAdded);
    connect(&listeningHistory, &ListeningHistoryService::entryRemoved, this, &ListeningHistoryViewModel::onEntryRemoved);
    connect(&listeningHistory, &ListeningHistoryService::entriesCleared, this, &ListeningHistoryViewModel::onEntriesCleared);

    for(auto entry: listeningHistory.getEntries())
        onEntryAdded(entry);
}

QAbstractListModel* ListeningHistoryViewModel::getModel() {
    return model;
}

void ListeningHistoryViewModel::onEntryAdded(const ListeningHistoryEntry& entry) {
    model->prepend(new ListeningHistoryEntryModel(entry, this));
}

void ListeningHistoryViewModel::onEntryRemoved(int index) {
    model->remove(index);
}

void ListeningHistoryViewModel::onEntriesCleared() {
    model->clear();
}

#include <MellowPlayer/UseCases/Services/ListeningHistoryService.hpp>
#include "ListeningHistoryViewModel.hpp"
#include "QQmlObjectListModel.hpp"

USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Presentation)

ListeningHistoryViewModel::ListeningHistoryViewModel(ListeningHistoryService& listeningHistory):
        listeningHistoryService(listeningHistory),
        sourceListModel(new QQmlObjectListModel<ListeningHistoryEntryModel>(this)),
        proxyListModel(sourceListModel) {
    connect(&listeningHistory, &ListeningHistoryService::entryAdded, this, &ListeningHistoryViewModel::onEntryAdded);
    connect(&listeningHistory, &ListeningHistoryService::entryRemoved, this, &ListeningHistoryViewModel::onEntryRemoved);
    connect(&listeningHistory, &ListeningHistoryService::entriesCleared, this, &ListeningHistoryViewModel::onEntriesCleared);

    proxyListModel.setSourceModel(sourceListModel);
}

QAbstractItemModel* ListeningHistoryViewModel::getModel() {
    return &proxyListModel;
}

void ListeningHistoryViewModel::onEntryAdded(const ListeningHistoryEntry& entry) {
    sourceListModel->prepend(new ListeningHistoryEntryModel(entry, this));
}

void ListeningHistoryViewModel::onEntryRemoved(int index) {
    sourceListModel->remove(index);
}

void ListeningHistoryViewModel::onEntriesCleared() {
    sourceListModel->clear();
}

void ListeningHistoryViewModel::initialize() {
    listeningHistoryService.initialize();
    for(auto entry: listeningHistoryService.getEntries())
        onEntryAdded(entry);
}

void ListeningHistoryViewModel::disableService(const QString &serviceName, bool disable) {
    proxyListModel.disableService(serviceName, disable);
}

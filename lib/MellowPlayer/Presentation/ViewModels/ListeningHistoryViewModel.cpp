#include <MellowPlayer/UseCases/Services/ListeningHistoryService.hpp>
#include "ListeningHistoryViewModel.hpp"
#include "QQmlObjectListModel.hpp"

USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Presentation)

ListeningHistoryViewModel::ListeningHistoryViewModel(ListeningHistoryService& listeningHistory):
        listeningHistoryService(listeningHistory),
        sourceListModel(new QQmlObjectListModel<ListeningHistoryEntryModel>(this, "title", "entryId")),
        proxyListModel(sourceListModel) {
    proxyListModel.setSourceModel(sourceListModel);
}

QAbstractItemModel* ListeningHistoryViewModel::getModel() {
    return &proxyListModel;
}

void ListeningHistoryViewModel::onEntryAdded(const ListeningHistoryEntry& entry) {
    sourceListModel->prepend(new ListeningHistoryEntryModel(entry, this));
}

void ListeningHistoryViewModel::onEntryRemoved(int entryId) {
    sourceListModel->remove(sourceListModel->getByUid(QString("%1").arg(entryId)));
}

void ListeningHistoryViewModel::initialize() {
    connect(&listeningHistoryService, &ListeningHistoryService::entryAdded, this, &ListeningHistoryViewModel::onEntryAdded);
    connect(&listeningHistoryService, &ListeningHistoryService::entryRemoved, this, &ListeningHistoryViewModel::onEntryRemoved);
    listeningHistoryService.initialize();
    for(auto entry: listeningHistoryService.getEntries())
        onEntryAdded(entry);
}

void ListeningHistoryViewModel::disableService(const QString &serviceName, bool disable) {
    proxyListModel.disableService(serviceName, disable);
}

void ListeningHistoryViewModel::setSearchFilter(const QString& searchFilter) {
    proxyListModel.setSearchFilter(searchFilter);
}

void ListeningHistoryViewModel::removeById(int id) {
    listeningHistoryService.removeById(id);
}

void ListeningHistoryViewModel::removeByDateCategory(const QString &dateCategory) {
    QList<int> toRemove;
    for(int i = 0; i < sourceListModel->count(); ++i) {
        ListeningHistoryEntryModel* entry = sourceListModel->at(i);
        if (entry->getDateCategory() == dateCategory)
            toRemove.append(entry->getEntryId());
    }
    listeningHistoryService.removeManyById(toRemove);
}

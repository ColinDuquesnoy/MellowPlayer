#include <MellowPlayer/Application/ListeningHistory/ListeningHistory.hpp>
#include "ListeningHistoryModel.hpp"
#include "QQmlObjectListModel.hpp"

USING_MELLOWPLAYER_NAMESPACE(Application)
USING_MELLOWPLAYER_NAMESPACE(Application)
USING_MELLOWPLAYER_NAMESPACE(Presentation)

ListeningHistoryModel::ListeningHistoryModel(ListeningHistory& listeningHistory):
        listeningHistoryService(listeningHistory),
        sourceListModel(new QQmlObjectListModel<ListeningHistoryEntryModel>(this, "title", "entryId")),
        proxyListModel(sourceListModel) {
    proxyListModel.setSourceModel(sourceListModel);
}

QAbstractItemModel* ListeningHistoryModel::getFilteredModel() {
    return &proxyListModel;
}

QAbstractItemModel *ListeningHistoryModel::getSourceModel()
{
    return sourceListModel;
}

void ListeningHistoryModel::onEntryAdded(const ListeningHistoryEntry& entry) {
    sourceListModel->prepend(new ListeningHistoryEntryModel(entry, this));
}

void ListeningHistoryModel::onEntryRemoved(int entryId) {
    sourceListModel->remove(sourceListModel->getByUid(QString("%1").arg(entryId)));
}

void ListeningHistoryModel::initialize() {
    connect(&listeningHistoryService, &ListeningHistory::entryAdded, this, &ListeningHistoryModel::onEntryAdded);
    connect(&listeningHistoryService, &ListeningHistory::entryRemoved, this, &ListeningHistoryModel::onEntryRemoved);
    listeningHistoryService.initialize();
    for(auto entry: listeningHistoryService.getEntries())
        onEntryAdded(entry);
}

void ListeningHistoryModel::disableService(const QString &serviceName, bool disable) {
    proxyListModel.disableService(serviceName, disable);
}

void ListeningHistoryModel::setSearchFilter(const QString& searchFilter) {
    proxyListModel.setSearchFilter(searchFilter);
}

void ListeningHistoryModel::removeById(int id) {
    listeningHistoryService.removeById(id);
}

void ListeningHistoryModel::removeByDateCategory(const QString &dateCategory) {
    QList<int> toRemove;
    for(int i = 0; i < sourceListModel->count(); ++i) {
        ListeningHistoryEntryModel* entry = sourceListModel->at(i);
        if (entry->getDateCategory() == dateCategory)
            toRemove.append(entry->getEntryId());
    }
    listeningHistoryService.removeManyById(toRemove);
}

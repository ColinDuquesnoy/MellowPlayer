#include "ListeningHistoryViewModel.hpp"
#include <MellowPlayer/Application/ListeningHistory/ListeningHistory.hpp>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Application;
using namespace MellowPlayer::Presentation;

ListeningHistoryViewModel::ListeningHistoryViewModel(ListeningHistory& listeningHistory)
        : listeningHistoryService(listeningHistory),
          sourceModel(new QQmlObjectListModel<ListeningHistoryEntryViewModel>(this, "title", "entryId")),
          proxyModel(sourceModel)
{
    proxyModel.setSourceModel(sourceModel);
}

ListeningHistoryProxyListModel* ListeningHistoryViewModel::getModel()
{
    return &proxyModel;
}

void ListeningHistoryViewModel::onEntryAdded(const ListeningHistoryEntry& entry)
{
    sourceModel->prepend(new ListeningHistoryEntryViewModel(entry, this));
}

void ListeningHistoryViewModel::onEntryRemoved(int entryId)
{
    sourceModel->remove(sourceModel->getByUid(QString("%1").arg(entryId)));
}

void ListeningHistoryViewModel::initialize()
{
    connect(&listeningHistoryService, &ListeningHistory::entryAdded, this, &ListeningHistoryViewModel::onEntryAdded);
    connect(&listeningHistoryService, &ListeningHistory::entryRemoved, this, &ListeningHistoryViewModel::onEntryRemoved);
    listeningHistoryService.initialize();
    for (auto entry : listeningHistoryService.getEntries())
        onEntryAdded(entry);
}

void ListeningHistoryViewModel::disableService(const QString& serviceName, bool disable)
{
    proxyModel.disableService(serviceName, disable);
}

void ListeningHistoryViewModel::setSearchFilter(const QString& searchFilter)
{
    proxyModel.setSearchFilter(searchFilter);
}

void ListeningHistoryViewModel::removeById(int id)
{
    listeningHistoryService.removeById(id);
}

void ListeningHistoryViewModel::removeByDateCategory(const QString& dateCategory)
{
    QList<int> toRemove;
    for (int i = 0; i < sourceModel->count(); ++i) {
        ListeningHistoryEntryViewModel* entry = sourceModel->at(i);
        if (entry->getDateCategory() == dateCategory)
            toRemove.append(entry->getEntryId());
    }
    listeningHistoryService.removeManyById(toRemove);
}

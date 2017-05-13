#include <QQmlObjectListModel.hpp>
#include "ListeningHistoryEntryProxyListModel.hpp"
#include "QQmlObjectListModel.hpp"

USE_MELLOWPLAYER_NAMESPACE(Presentation)

ListeningHistoryEntryProxyListModel::ListeningHistoryEntryProxyListModel(
        QQmlObjectListModel<ListeningHistoryEntryModel> *sourceModel): sourceModel(sourceModel) {
    setSourceModel(sourceModel);
    setDynamicSortFilter(true);
}

void ListeningHistoryEntryProxyListModel::disableService(const QString &serviceName, bool disable) {
    if (disable)
        disabledServices.append(serviceName);
    else
        disabledServices.removeOne(serviceName);
    invalidateFilter();
}

void ListeningHistoryEntryProxyListModel::setSearchFilter(const QString &newSearchFilter) {
    searchFilter = newSearchFilter;
    invalidateFilter();
}

bool ListeningHistoryEntryProxyListModel::filterAcceptsRow(int sourceRow, const QModelIndex&) const {
    ListeningHistoryEntryModel* entry = sourceModel->at(sourceRow);
    if (disabledServices.contains(entry->getService()))
        return false;
    if (searchFilter.isEmpty())
        return true;
    else
        return !entry->getTitle().contains(searchFilter) && !entry->getArtist().contains(searchFilter);
}

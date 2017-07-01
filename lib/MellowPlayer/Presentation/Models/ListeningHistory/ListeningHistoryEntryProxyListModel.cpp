#include <QQmlObjectListModel.hpp>
#include "ListeningHistoryEntryProxyListModel.hpp"
#include "QQmlObjectListModel.hpp"

USING_MELLOWPLAYER_NAMESPACE(Presentation)

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
    searchFilter = newSearchFilter.toLower();
    invalidateFilter();
}

bool ListeningHistoryEntryProxyListModel::filterAcceptsRow(int sourceRow, const QModelIndex&) const {
    ListeningHistoryEntryModel* entry = sourceModel->at(sourceRow);
    if (disabledServices.contains(entry->getService()))
        return false;
    if (searchFilter.isEmpty())
        return true;
    else {
        bool titleContainsFilter = entry->getTitle().toLower().contains(searchFilter.toLower());
        bool artistContainsFilter = entry->getArtist().toLower().contains(searchFilter.toLower());
        return titleContainsFilter || artistContainsFilter;
    }
}

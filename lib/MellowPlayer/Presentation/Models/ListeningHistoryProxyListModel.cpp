#include "ListeningHistoryProxyListModel.hpp"

using namespace MellowPlayer::Presentation;

ListeningHistoryProxyListModel::ListeningHistoryProxyListModel(
QQmlObjectListModel<ListeningHistoryEntryViewModel> *sourceModel)
        : sourceModel(sourceModel)
{
    setSourceModel(sourceModel);
    setDynamicSortFilter(true);
}

void ListeningHistoryProxyListModel::disableService(const QString &serviceName, bool disable)
{
    if (disable)
        disabledServices.append(serviceName);
    else
        disabledServices.removeOne(serviceName);
    invalidateFilter();
}

void ListeningHistoryProxyListModel::setSearchFilter(const QString &newSearchFilter)
{
    searchFilter = newSearchFilter.toLower();
    invalidateFilter();
}

bool ListeningHistoryProxyListModel::filterAcceptsRow(int sourceRow, const QModelIndex &) const
{
    ListeningHistoryEntryViewModel *entry = sourceModel->at(sourceRow);
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

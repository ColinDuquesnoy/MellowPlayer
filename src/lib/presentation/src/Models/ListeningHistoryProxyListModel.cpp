#include <MellowPlayer/Presentation/Models/ListeningHistoryProxyListModel.hpp>

using namespace MellowPlayer::Presentation;

ListeningHistoryProxyListModel::ListeningHistoryProxyListModel(QQmlObjectListModel<ListeningHistoryEntryViewModel>* sourceModel)
        : sourceModel_(sourceModel)
{
    setSourceModel(sourceModel);
    setDynamicSortFilter(true);
}

void ListeningHistoryProxyListModel::disableService(const QString& serviceName, bool disable)
{
    if (disable)
        disabledServices_.append(serviceName);
    else
        disabledServices_.removeOne(serviceName);
    invalidateFilter();
}

void ListeningHistoryProxyListModel::setSearchFilter(const QString& newSearchFilter)
{
    searchFilter_ = newSearchFilter.toLower();
    invalidateFilter();
}

bool ListeningHistoryProxyListModel::filterAcceptsRow(int sourceRow, const QModelIndex&) const
{
    ListeningHistoryEntryViewModel* entry = sourceModel_->at(sourceRow);
    if (disabledServices_.contains(entry->service()))
        return false;
    if (searchFilter_.isEmpty())
        return true;
    else {
        bool titleContainsFilter = entry->title().toLower().contains(searchFilter_.toLower());
        bool artistContainsFilter = entry->artist().toLower().contains(searchFilter_.toLower());
        return titleContainsFilter || artistContainsFilter;
    }
}

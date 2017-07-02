#pragma once

#include <QList>
#include <QSortFilterProxyModel>
#include <MellowPlayer/Macros.hpp>
#include "MellowPlayer/Presentation/ViewModels/ListeningHistory/ListeningHistoryEntryViewModel.hpp"
#include "ListeningHistoryListModel.hpp"

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class ListeningHistoryProxyListModel: public QSortFilterProxyModel {
public:
    ListeningHistoryProxyListModel(ListeningHistoryListModel* sourceModel);

    void disableService(const QString& serviceName, bool disable);
    void setSearchFilter(const QString& newSearchFilter);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex & sourceParent) const override;

private:
    QQmlObjectListModel<ListeningHistoryEntryViewModel>* sourceModel;
    QList<QString> disabledServices;
    QString searchFilter;
};

END_MELLOWPLAYER_NAMESPACE

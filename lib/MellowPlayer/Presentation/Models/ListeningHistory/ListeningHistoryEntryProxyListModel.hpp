#pragma once

#include <QList>
#include <QSortFilterProxyModel>
#include <MellowPlayer/Macros.hpp>
#include "ListeningHistoryEntryModel.hpp"

template <class T> class QQmlObjectListModel;


BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class ListeningHistoryEntryProxyListModel: public QSortFilterProxyModel {
public:
    ListeningHistoryEntryProxyListModel(QQmlObjectListModel<ListeningHistoryEntryModel>* sourceModel);

    void disableService(const QString& serviceName, bool disable);
    void setSearchFilter(const QString& newSearchFilter);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex & sourceParent) const override;

private:
    QQmlObjectListModel<ListeningHistoryEntryModel>* sourceModel;
    QList<QString> disabledServices;
    QString searchFilter;
};

END_MELLOWPLAYER_NAMESPACE

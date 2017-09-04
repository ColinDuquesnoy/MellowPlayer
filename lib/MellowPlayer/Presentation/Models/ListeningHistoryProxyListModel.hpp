#pragma once

#include "ListeningHistoryListModel.hpp"
#include "MellowPlayer/Presentation/ViewModels/ListeningHistory/ListeningHistoryEntryViewModel.hpp"
#include <QList>
#include <QSortFilterProxyModel>

namespace MellowPlayer::Presentation
{
    class ListeningHistoryProxyListModel : public QSortFilterProxyModel
    {
    public:
        explicit ListeningHistoryProxyListModel(ListeningHistoryListModel* sourceModel);

        void disableService(const QString& serviceName, bool disable);
        void setSearchFilter(const QString& newSearchFilter);

    protected:
        bool filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const override;

    private:
        QQmlObjectListModel<ListeningHistoryEntryViewModel>* sourceModel_;
        QList<QString> disabledServices_;
        QString searchFilter_;
    };
}

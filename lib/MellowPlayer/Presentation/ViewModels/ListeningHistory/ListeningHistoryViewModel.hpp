#pragma once

#include <MellowPlayer/Presentation/Models/ListeningHistoryProxyListModel.hpp>
#include <MellowPlayer/Presentation/ViewModels/ListeningHistory/ListeningHistoryEntryViewModel.hpp>
#include <QAbstractListModel>

namespace MellowPlayer::Application
{
    class ListeningHistory;
}

namespace MellowPlayer::Presentation
{
    class ListeningHistoryViewModel : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(QAbstractItemModel* model READ model CONSTANT)
    public:
        explicit ListeningHistoryViewModel(Application::ListeningHistory& listeningHistory);

        void initialize();
        ListeningHistoryProxyListModel* model();
        Q_INVOKABLE void disableService(const QString& serviceName, bool disable);
        Q_INVOKABLE void setSearchFilter(const QString& searchFilter);
        Q_INVOKABLE void removeById(int entryId);
        Q_INVOKABLE void removeByDateCategory(const QString& dateCategory);

    private slots:
        void onEntryAdded(const Application::ListeningHistoryEntry& entry);
        void onEntryRemoved(int entryId);

    private:
        Application::ListeningHistory& listeningHistoryService_;
        ListeningHistoryListModel* sourceModel_;
        ListeningHistoryProxyListModel proxyModel_;
    };
}

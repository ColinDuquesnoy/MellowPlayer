#pragma once

#include <QAbstractListModel>
#include <MellowPlayer/Presentation/ViewModels/ListeningHistory/ListeningHistoryEntryViewModel.hpp>
#include <MellowPlayer/Presentation/Models/ListeningHistoryProxyListModel.hpp>

namespace MellowPlayer::Application {

    class ListeningHistory;

}

namespace MellowPlayer::Presentation {

    class ListeningHistoryViewModel: public QObject {
        Q_OBJECT
        Q_PROPERTY(QAbstractItemModel* model READ getModel CONSTANT)
    public:
        ListeningHistoryViewModel(Application::ListeningHistory& listeningHistory);

        void initialize();
        ListeningHistoryProxyListModel* getModel();
        Q_INVOKABLE void disableService(const QString &serviceName, bool disable);
        Q_INVOKABLE void setSearchFilter(const QString& searchFilter);
        Q_INVOKABLE void removeById(int entryId);
        Q_INVOKABLE void removeByDateCategory(const QString &dateCategory);

    private slots:
        void onEntryAdded(const Application::ListeningHistoryEntry& entry);
        void onEntryRemoved(int entryId);

    private:
        Application::ListeningHistory& listeningHistoryService;
        ListeningHistoryListModel* sourceModel;
        ListeningHistoryProxyListModel proxyModel;
    };

}

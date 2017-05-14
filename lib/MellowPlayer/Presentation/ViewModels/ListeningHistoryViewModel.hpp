#pragma once

#include <QAbstractListModel>
#include <MellowPlayer/Presentation/Models/ListeningHistoryEntryModel.hpp>
#include <MellowPlayer/Presentation/Models/ListeningHistoryEntryProxyListModel.hpp>

PREDECLARE_MELLOWPLAYER_CLASS(UseCases, ListeningHistoryService)
template <class T> class QQmlObjectListModel;

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class ListeningHistoryViewModel: public QObject {
    Q_OBJECT
    Q_PROPERTY(QAbstractItemModel* model READ getModel CONSTANT)
public:
    ListeningHistoryViewModel(UseCases::ListeningHistoryService& listeningHistory);

    void initialize();
    QAbstractItemModel* getModel();
    Q_INVOKABLE void disableService(const QString &serviceName, bool disable);
    Q_INVOKABLE void setSearchFilter(const QString& searchFilter);
    Q_INVOKABLE void removeById(int entryId);
    Q_INVOKABLE void removeByDateCategory(const QString &dateCategory);

private slots:
    void onEntryAdded(const Entities::ListeningHistoryEntry& entry);
    void onEntryRemoved(int entryId);
    void onEntriesCleared();

private:
    UseCases::ListeningHistoryService& listeningHistoryService;
    QQmlObjectListModel<ListeningHistoryEntryModel>* sourceListModel;
    ListeningHistoryEntryProxyListModel proxyListModel;
};

END_MELLOWPLAYER_NAMESPACE

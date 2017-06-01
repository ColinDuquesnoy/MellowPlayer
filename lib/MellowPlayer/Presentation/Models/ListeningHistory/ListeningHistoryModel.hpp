#pragma once

#include <QAbstractListModel>
#include <MellowPlayer/Presentation/Models/ListeningHistory/ListeningHistoryEntryModel.hpp>
#include <MellowPlayer/Presentation/Models/ListeningHistory/ListeningHistoryEntryProxyListModel.hpp>

PREDECLARE_MELLOWPLAYER_CLASS(Application, ListeningHistoryService)
template <class T> class QQmlObjectListModel;

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class ListeningHistoryModel: public QObject {
    Q_OBJECT
    Q_PROPERTY(QAbstractItemModel* filteredModel READ getFilteredModel CONSTANT)
    Q_PROPERTY(QAbstractItemModel* sourceModel READ getSourceModel CONSTANT)
public:
    ListeningHistoryModel(Application::ListeningHistoryService& listeningHistory);

    void initialize();
    QAbstractItemModel* getFilteredModel();
    QAbstractItemModel* getSourceModel();
    Q_INVOKABLE void disableService(const QString &serviceName, bool disable);
    Q_INVOKABLE void setSearchFilter(const QString& searchFilter);
    Q_INVOKABLE void removeById(int entryId);
    Q_INVOKABLE void removeByDateCategory(const QString &dateCategory);

private slots:
    void onEntryAdded(const Entities::ListeningHistoryEntry& entry);
    void onEntryRemoved(int entryId);

private:
    Application::ListeningHistoryService& listeningHistoryService;
    QQmlObjectListModel<ListeningHistoryEntryModel>* sourceListModel;
    ListeningHistoryEntryProxyListModel proxyListModel;
};

END_MELLOWPLAYER_NAMESPACE

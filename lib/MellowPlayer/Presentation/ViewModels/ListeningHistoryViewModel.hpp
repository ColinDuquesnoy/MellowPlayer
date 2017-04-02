#pragma once

#include <QAbstractListModel>
#include <MellowPlayer/Presentation/Models/ListeningHistoryEntryModel.hpp>

PREDECLARE_MELLOWPLAYER_CLASS(UseCases, ListeningHistoryService)
template <class T> class QQmlObjectListModel;

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class ListeningHistoryViewModel: public QObject {
    Q_PROPERTY(QAbstractListModel* model READ getModel CONSTANT)
    Q_OBJECT
public:
    ListeningHistoryViewModel(UseCases::ListeningHistoryService& listeningHistory);

    QAbstractListModel* getModel();

private slots:
    void onEntryAdded(const Entities::ListeningHistoryEntry& entry);
    void onEntryRemoved(int index);
    void onEntriesCleared();

private:
    QQmlObjectListModel<ListeningHistoryEntryModel>* model;
};

END_MELLOWPLAYER_NAMESPACE

#pragma once

#include <MellowPlayer/Presentation/Models/ListeningHistoryProxyListModel.hpp>
#include <MellowPlayer/Presentation/Qml/ContextProperty.hpp>

namespace MellowPlayer::Domain
{
    class ListeningHistory;
}

namespace MellowPlayer::Presentation
{
    class ListeningHistoryViewModel : public QObject, public ContextProperty
    {
        Q_OBJECT
        Q_PROPERTY(QAbstractItemModel* model READ model CONSTANT)
    public:
        ListeningHistoryViewModel(Domain::ListeningHistory& listeningHistory, IContextProperties& contextProperties);

        using ContextProperty::initialize;
        void initialize();
        ListeningHistoryProxyListModel* model();
        Q_INVOKABLE void disableService(const QString& serviceName, bool disable);
        Q_INVOKABLE void setSearchFilter(const QString& searchFilter);
        Q_INVOKABLE void removeById(int entryId);
        Q_INVOKABLE void removeByDateCategory(const QString& dateCategory);

    private slots:
        void onEntryAdded(const Domain::ListeningHistoryEntry& entry);
        void onEntryRemoved(int entryId);

    private:
        Domain::ListeningHistory& listeningHistoryService_;
        ListeningHistoryListModel* sourceModel_;
        ListeningHistoryProxyListModel proxyModel_;
    };
}

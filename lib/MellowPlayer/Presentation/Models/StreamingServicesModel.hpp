#pragma once

#include <QAbstractListModel>
#include <MellowPlayer/Macros.hpp>
#include <MellowPlayer/Entities/StreamingService.hpp>

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class StreamingServicesModel: public QAbstractListModel {
Q_OBJECT
public:
    enum Roles { StreamingServiceRole };

    StreamingServicesModel();

    void addService(Entities::StreamingService* streamingService);
    void removeService(Entities::StreamingService* streamingService);
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QList<Entities::StreamingService*> getServices() { return services; }

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<Entities::StreamingService*> services;
};

END_MELLOWPLAYER_NAMESPACE

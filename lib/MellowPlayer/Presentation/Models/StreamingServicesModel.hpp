#pragma once

#include <QAbstractListModel>
#include <MellowPlayer/Macros.hpp>
#include <MellowPlayer/UseCases/StreamingService.hpp>

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

class StreamingServicesModel: public QAbstractListModel {
Q_OBJECT
public:
    enum Roles { StreamingServiceRole };

    StreamingServicesModel();

    void addService(UseCases::StreamingService* streamingService);
    void removeService(UseCases::StreamingService* streamingService);
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QList<UseCases::StreamingService*> getServices() { return services; }
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<UseCases::StreamingService*> services;
};

END_MELLOWPLAYER_NAMESPACE

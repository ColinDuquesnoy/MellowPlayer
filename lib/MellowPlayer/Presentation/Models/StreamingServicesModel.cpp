#include "StreamingServicesModel.hpp"

USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(Presentation)

StreamingServicesModel::StreamingServicesModel()
    : QAbstractListModel() {}

void StreamingServicesModel::addService(StreamingService* streamingService) {
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    services.append(streamingService);
    endInsertRows();
}

void StreamingServicesModel::removeService(StreamingService* streamingService) {
    auto index = services.indexOf(streamingService);
    beginRemoveRows(QModelIndex(), index, index);
    services.removeAt(index);
    endRemoveRows();
}

int StreamingServicesModel::rowCount(const QModelIndex&) const {
    return services.count();
}

QVariant StreamingServicesModel::data(const QModelIndex& index, int) const {
    if (index.row() < 0 || index.row() >= rowCount())
        return QVariant();
    QVariant data;
    data.setValue(services[index.row()]);
    return data;
//    return QVariant::fromValue<QObject*>(services[index.row()]);
}

QHash<int, QByteArray> StreamingServicesModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[StreamingServiceRole] = "service";
    return roles;
}


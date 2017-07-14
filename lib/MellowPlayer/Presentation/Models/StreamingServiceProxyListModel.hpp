#pragma once

#include <QtCore/QSortFilterProxyModel>
#include "StreamingServiceListModel.hpp"

namespace MellowPlayer::Presentation {

    class StreamingServiceProxyListModel: public QSortFilterProxyModel {
    public:
        StreamingServiceProxyListModel(StreamingServiceListModel* sourceListModel);

    protected:
        bool filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const override;
        bool lessThan(const QModelIndex& sourceLeft, const QModelIndex& sourceRight) const override;

    private:
        StreamingServiceListModel* sourceListModel;

    };

}


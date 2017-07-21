#include "StreamingServiceProxyListModel.hpp"

using namespace MellowPlayer::Presentation;

StreamingServiceProxyListModel::StreamingServiceProxyListModel(StreamingServiceListModel *sourceListModel) : sourceListModel(sourceListModel)
{
    setDynamicSortFilter(false);
    setSourceModel(sourceListModel);
    sort(0);
}

bool StreamingServiceProxyListModel::filterAcceptsRow(int sourceRow, const QModelIndex &) const
{
    StreamingServiceViewModel *viewModel = sourceListModel->at(sourceRow);

    if (viewModel->getSortOrder() == -1)
        viewModel->setSortOrder(sourceRow);

    return sourceListModel->at(sourceRow)->isEnabled();
}

bool MellowPlayer::Presentation::StreamingServiceProxyListModel::lessThan(const QModelIndex &sourceLeft, const QModelIndex &sourceRight) const
{
    StreamingServiceViewModel *left = sourceListModel->at(sourceLeft.row());
    StreamingServiceViewModel *right = sourceListModel->at(sourceRight.row());

    return left->getSortOrder() < right->getSortOrder();
}

void StreamingServiceProxyListModel::update()
{
    invalidate();
}

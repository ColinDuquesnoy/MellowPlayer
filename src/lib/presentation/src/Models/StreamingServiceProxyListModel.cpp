#include <MellowPlayer/Presentation/Models/StreamingServiceProxyListModel.hpp>

using namespace MellowPlayer::Presentation;

StreamingServiceProxyListModel::StreamingServiceProxyListModel(StreamingServiceListModel* sourceListModel) : sourceListModel_(sourceListModel)
{
    setDynamicSortFilter(false);
    setSourceModel(sourceListModel);
    sort(0);
}

bool StreamingServiceProxyListModel::filterAcceptsRow(int sourceRow, const QModelIndex&) const
{
    StreamingServiceViewModel* viewModel = sourceListModel_->at(sourceRow);

    if (viewModel->sortOrder() == -1)
        viewModel->setSortOrder(sourceRow);

    return sourceListModel_->at(sourceRow)->isEnabled();
}

bool MellowPlayer::Presentation::StreamingServiceProxyListModel::lessThan(const QModelIndex& sourceLeft, const QModelIndex& sourceRight) const
{
    StreamingServiceViewModel* left = sourceListModel_->at(sourceLeft.row());
    StreamingServiceViewModel* right = sourceListModel_->at(sourceRight.row());

    return left->sortOrder() < right->sortOrder();
}

void StreamingServiceProxyListModel::update()
{
    invalidate();
}

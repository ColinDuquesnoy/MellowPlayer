#pragma once

#include <QString>
#include <QList>
#include "Filter.hpp"

namespace MellowPlayer::Infrastructure
{
    class TokenizedFilters
    {
    public:
        TokenizedFilters(const QString& filters);
        TokenizedFilters(const QList<Filter>& filters);

        QString join() const;

        typedef typename QList<Filter>::const_iterator const_iterator;
        const_iterator begin(void) const;
        const_iterator end(void) const;

    private:
        QList<Filter> filters_;
    };
}

#pragma once

#include <QString>
#include "Filter.hpp"


namespace MellowPlayer::Infrastructure
{
    class FilterConverter
    {
    public:
        FilterConverter();

        QString toString(Filter filter) const;
        Filter fromString(const QString& filterString) const;

    private:
        QString linux_;
        QString appImage_;
        QString windows_;
        QString osx_;
        QString all_;
    };
}

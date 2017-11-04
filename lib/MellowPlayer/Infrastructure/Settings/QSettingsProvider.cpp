#include "QSettingsProvider.hpp"

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;
using namespace std;

QSettingsProvider::QSettingsProvider() : qSettings_()
{
}

void QSettingsProvider::clear()
{
    qSettings_.clear();
}

QVariant QSettingsProvider::value(const QString& key, const QVariant& defaultValue) const
{
    return qSettings_.value(key, defaultValue);
}

void QSettingsProvider::setValue(const QString& key, const QVariant& value)
{
    qSettings_.setValue(key, value);
}

#include "QSettingsProvider.hpp"

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Application;
using namespace MellowPlayer::Infrastructure;
using namespace std;

QSettingsProvider::QSettingsProvider() : qSettings()
{
}

void QSettingsProvider::clear()
{
    qSettings.clear();
}

QVariant QSettingsProvider::getValue(const QString &key, const QVariant &defaultValue) const
{
    return qSettings.value(key, defaultValue);
}

void QSettingsProvider::setValue(const QString &key, const QVariant &value)
{
    qSettings.setValue(key, value);
}

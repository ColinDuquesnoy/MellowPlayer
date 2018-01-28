#include <MellowPlayer/Infrastructure/Settings/QSettingsStore.hpp>

using namespace std;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;

QSettingsStore::QSettingsStore() : qSettings_(make_unique<QSettings>("MellowPlayer", "3"))
{
}

void QSettingsStore::setOrganizationName(const QString &orgName)
{
    qSettings_ = make_unique<QSettings>(orgName, "3");
}

void QSettingsStore::clear()
{
    qSettings_->clear();
}

QVariant QSettingsStore::value(const QString& key, const QVariant& defaultValue) const
{
    return qSettings_->value(key, defaultValue);
}

void QSettingsStore::setValue(const QString& key, const QVariant& value)
{
    qSettings_->setValue(key, value);
}

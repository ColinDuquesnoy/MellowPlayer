#include "QSettingsProvider.hpp"

USING_MELLOWPLAYER_NAMESPACE(Application)
USING_MELLOWPLAYER_NAMESPACE(Application)
USING_MELLOWPLAYER_NAMESPACE(Infrastructure)
using namespace std;

QSettingsProvider::QSettingsProvider(): qSettings() {

}

void QSettingsProvider::clear() {
    qSettings.clear();
}

QVariant QSettingsProvider::getValue(const QString& key, const QVariant& defaultValue) const {
    return qSettings.value(key, defaultValue);
}

void QSettingsProvider::setValue(const QString& key, const QVariant& value) {
    qSettings.setValue(key, value);
}

#include "QSettingsProvider.hpp"

USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)
using namespace std;

const QString QSettingsProvider::CURRENT_SERVICE_KEY = "currentService";

QSettingsProvider::QSettingsProvider(): qSettings() {

}

void QSettingsProvider::clear() {
    qSettings.clear();
}

QString QSettingsProvider::getCurrentService() const {
    return qSettings.value(CURRENT_SERVICE_KEY, "").toString();
}

void QSettingsProvider::setCurrentService(const QString& service) {
    qSettings.setValue(CURRENT_SERVICE_KEY, service);
}

QVariant QSettingsProvider::getValue(const QString& key, const QVariant& defaultValue) const {
    return qSettings.value(key, defaultValue);
}

void QSettingsProvider::setValue(const QString& key, const QVariant& value) {
    qSettings.setValue(key, value);
}

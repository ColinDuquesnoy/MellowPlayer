#include <QtWebEngineWidgets/QWebEngineProfile>
#include "UserAgentStringSettingViewModel.hpp"

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;

UserAgentStringSettingViewModel::UserAgentStringSettingViewModel(Setting& setting, QObject* parent)
        : StringSettingViewModel(setting, parent)
{

}

QString UserAgentStringSettingViewModel::getValue() const
{
    QString value = StringSettingViewModel::getValue();

    if (value.isEmpty()) {
        QWebEngineProfile profile("Default");
        value = profile.httpUserAgent();
    }

    return value;
}

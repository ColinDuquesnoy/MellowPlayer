#include <QtCore/QObject>
#include <MellowPlayer/Presentation/Notifications/Presenters/Linux/LibnotifyStrings.hpp>

using namespace std;

string LibnotifyStrings::open() const {
    return QObject::trUtf8("Open").toStdString().c_str();
}

#include <QtCore/QObject>
#include "LibnotifyStrings.hpp"

using namespace std;

string LibnotifyStrings::open() const {
    return QObject::trUtf8("Open").toStdString().c_str();
}

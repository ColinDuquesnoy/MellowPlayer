import QtQuick 2.9
import QtQuick.Layouts 1.3

Rectangle {
    color: _theme.isDark(_theme.background) ? Qt.lighter(_theme.background) : Qt.darker(_theme.background, 1.1)
    height: 1
}

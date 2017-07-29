import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import MellowPlayer 3.0
import ".."

Page {
    id: settingsPage

    signal closeRequested()

    header: ToolBar {
        id: toolBar

        Material.primary: _theme.primary
        Material.foreground: _theme.primaryForeground
        Material.theme: _theme.isDark(_theme.primary) ? Material.Dark : Material.Light

        RowLayout {
            anchors.fill: parent

            Item {
                Layout.fillWidth: true
            }

            ToolButton {
                id: btBack

                font { family: MaterialIcons.family; pixelSize: 24 }
                hoverEnabled: true
                text: MaterialIcons.icon_keyboard_arrow_right
                onClicked: settingsPage.closeRequested()
                Tooltip {
                    y: toolBar.implicitHeight
                    text: qsTr("Back")
                }

                Shortcut {
                    sequence: _settings.get(SettingKey.SHORTCUTS_SETTINGS)
                    onActivated: settingsPage.closeRequested()
                }
            }
        }

        Label {
            anchors.centerIn: parent
            font.pixelSize: 16
            text: settingsPageList.currentItem.category
        }
    }

    RowLayout {
        anchors.fill: parent
        spacing: 0

        Pane {
            padding: 0

            Layout.fillHeight: true
            Layout.maximumWidth: 256
            Layout.minimumWidth: 256

            Material.background: _theme.secondary
            Material.foreground: _theme.secondaryForeground
            Material.elevation: 4
            Material.theme: _theme.isDark(_theme.secondary) ? Material.Dark : Material.Light

            ColumnLayout {
                anchors.fill: parent

                Component {
                    id: settingsCategoryDelegate

                    ItemDelegate {
                        property string category: model.name

                        height: 60; width: parent.width
                        hoverEnabled: true

                        contentItem: RowLayout {
                            anchors.fill: parent
                            anchors.margins: 20
                            spacing: 10

                            Label {
                                text: model.icon
                                font.family: MaterialIcons.family
                                font.pixelSize: 24
                            }

                            Label {
                                verticalAlignment: "AlignVCenter"
                                text: model.name
                                font.pixelSize: 20
                            }

                            Item { Layout.fillWidth: true; }
                        }

                        onClicked: settingsPageList.currentIndex = index
                    }
                }

                ListView {
                    id: settingsPageList

                    highlight: Rectangle {
                        color: _theme.isDark(_theme.secondary) ? "#10ffffff" : "#10000000"

                        Rectangle {
                            anchors.top: parent.top
                            anchors.left: parent.left
                            anchors.bottom: parent.bottom

                            width: 3
                            color: _theme.accent
                        }
                    }
                    highlightMoveDuration: 200
                    model: _settings.categories
                    delegate: settingsCategoryDelegate
                    interactive: false

                    Layout.fillHeight: true
                    Layout.fillWidth: true
                }

                Button {
                    id: btRestoreDefaults

                    flat: true
                    highlighted: true
                    hoverEnabled: true
                    text: qsTr("Restore all to defaults")
                    onClicked: messageBoxConfirmRestore.open()

                    Layout.fillWidth: true
                    Layout.leftMargin: 4
                    Layout.rightMargin: 4

                    Tooltip {
                        text: qsTr('Restore all _settings to their <b>default value</b>.')
                    }
                }
            }
        }

        StackLayout {
            clip: true
            currentIndex: settingsPageList.currentIndex

            Layout.fillHeight: true
            Layout.fillWidth: true

            Repeater {
                model: _settings.categories

                Loader {
                    anchors.fill: parent
                    source: model.qmlComponent
                }
            }
        }
    }

    MessageBoxDialog {
        id: messageBoxConfirmRestore

        standardButtons: Dialog.Yes | Dialog.No
        message: qsTr("Are you sure you want to restore all _settings to their default values?")
        title: qsTr("Confirm restore defaults")
        x: settingsPage.width / 2 - width / 2
        y: settingsPage.height / 2 - height / 2

        onAccepted: _settings.restoreDefaults()
    }

    NewPluginWizard {
        id: wizardNewPlugin

        height: 540; width: 960
        x: parent.width / 2 - width / 2; y: parent.height / 2 - height / 2
    }
}
